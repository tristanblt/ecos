#include <kernel/arch.hpp>
#include <kernel/memory/mm.hpp>

#define BITMAP_SIZE 0x20000

uint32 framesCount, frameIdx;
uint32 framesFree;
uint8 physicalBitmap[BITMAP_SIZE];

void frameSet(uint32 i)
{
    physicalBitmap[i / 8] = 1 << (i % 8);
    framesFree--;
}

void frameSetAddress(uint32 addr)
{
    uint32 i;

    i = addr / FRAME_SIZE;
    physicalBitmap[i / 8] = 1 << (i % 8);
    framesFree--;
}

void frameUnset(uint32 i)
{
    if (i > framesCount)
        return;
    physicalBitmap[i / 8] &= ~(1 << (i % 8));
    framesFree++;
}

void frameUnsetAddress(uint32 addr)
{
    uint32 i;

    i = addr / FRAME_SIZE;
    if (i > framesCount)
        return;
    physicalBitmap[i / 8] &= ~(1 << (i % 8));
    framesFree++;
}

void frameSetup(uint32 memSize, uint32 reservedStart, uint32 reservedEnd)
{
    uint32 i;

    framesCount = memSize / FRAME_SIZE;
    framesFree = framesCount;
    frameIdx = 0;
    for (i = reservedStart; i < reservedEnd; i += FRAME_SIZE) {
        frameSetAddress(i);
        frameIdx++;
    }
}

uint32 frameGetBlk(uint32 blkSz)
{
    uint32 blkLeft, blkStart, i, iByte, iBit;

    blkLeft = blkSz;
    for (i = 0; i < framesCount; i++) {
        iByte = i / 8;
        iBit = i % 8;

        if (physicalBitmap[iByte] && (1 << iBit)) {
            if (blkLeft < blkSz)
                blkLeft = blkSz;
            continue;
        }
        if (blkLeft == blkSz)
            blkStart = i;
        blkLeft--;
        if (blkLeft == 0)
            break;
    }
    for (i = blkStart; i < (blkStart + blkSz); i++)
        frameSet(i);
    frameIdx += blkSz;
    return ((uint32)(blkStart * FRAME_SIZE));
}

uint32 frameGet()
{
    uint32 iByte, iBit, i;

    if (framesFree == 0)
        return 0;
    for (i = frameIdx; i < framesCount; i++) {
        iByte = i / 8;
        iBit = i % 8;

        if (physicalBitmap[iByte] && (1 << iBit))
            continue;
        frameSet(i);
        frameIdx++;
        return ((uint32)((iByte * 8 + iBit) * FRAME_SIZE));
    }
    frameIdx = 0;
    return (frameGet());
}

void frameFree(uint32 addr)
{
    frameUnsetAddress(addr);
}

uint32 frameCount()
{
    return (framesCount);
}

uint32 frameFreeCount()
{
    return (framesFree);
}
