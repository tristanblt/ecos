#include <kernel/arch.hpp>
#include <kernel/memory/mm.hpp>

#define BITMAP_SIZE 0x20000

uint32_t framesCount, frameIdx;
uint32_t framesFree;
uint8_t physicalBitmap[BITMAP_SIZE];

void frameSet(uint32_t i)
{
    physicalBitmap[i / 8] = 1 << (i % 8);
    framesFree--;
}

void frameSetAddress(uint32_t addr)
{
    uint32_t i;

    i = addr / FRAME_SIZE;
    physicalBitmap[i / 8] = 1 << (i % 8);
    framesFree--;
}

void frameUnset(uint32_t i)
{
    if (i > framesCount)
        return;
    physicalBitmap[i / 8] &= ~(1 << (i % 8));
    framesFree++;
}

void frameUnsetAddress(uint32_t addr)
{
    uint32_t i;

    i = addr / FRAME_SIZE;
    if (i > framesCount)
        return;
    physicalBitmap[i / 8] &= ~(1 << (i % 8));
    framesFree++;
}

void frameSetup(uint32_t memSize, uint32_t reservedStart, uint32_t reservedEnd)
{
    uint32_t i;

    framesCount = memSize / FRAME_SIZE;
    framesFree = framesCount;
    frameIdx = 0;
    for (i = reservedStart; i < reservedEnd; i += FRAME_SIZE) {
        frameSetAddress(i);
        frameIdx++;
    }
}

uint32_t frameGetBlk(uint32_t blkSz)
{
    uint32_t blkLeft, blkStart, i, iByte, iBit;

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
    return ((uint32_t)(blkStart * FRAME_SIZE));
}

uint32_t frameGet()
{
    uint32_t iByte, iBit, i;

    if (framesFree == 0)
        return 0;
    for (i = frameIdx; i < framesCount; i++) {
        iByte = i / 8;
        iBit = i % 8;

        if (physicalBitmap[iByte] && (1 << iBit))
            continue;
        frameSet(i);
        frameIdx++;
        return ((uint32_t)((iByte * 8 + iBit) * FRAME_SIZE));
    }
    frameIdx = 0;
    return (frameGet());
}

void frameFree(uint32_t addr)
{
    frameUnsetAddress(addr);
}

uint32_t frameCount()
{
    return (framesCount);
}

uint32_t frameFreeCount()
{
    return (framesFree);
}
