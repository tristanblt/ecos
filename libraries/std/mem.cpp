#include <libraries/std/types.hpp>

void memcpy8(void *src, void *dst, uint32_t size)
{
    uint32_t i = 0;

    for (; i < size; i++)
        ((uint8_t *)dst)[i] = ((uint8_t *)src)[i];
}

void memcpy32(void *src, void *dst, uint32_t size)
{
    uint32_t i = 0;

    for (; i < size; i++)
        ((uint32_t *)dst)[i] = ((uint32_t *)src)[i];
}

void *memset8(void *dest, uint8_t val, uint32_t len)
{
    uint8_t *ptr = (uint8_t *)dest;

    while (len-- > 0)
        *ptr++ = val;
    return (dest);
}

void *memset32(void *dest, uint32_t val, uint32_t len)
{
    uint32_t *ptr = (uint32_t *)dest;

    while (len-- > 0)
        *ptr++ = val;
    return (dest);
}