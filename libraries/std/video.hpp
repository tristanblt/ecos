#ifndef VIDEO_HPP_
#define VIDEO_HPP_

#include <libraries/std/types.hpp>

typedef struct vector2d {
    uint32_t x;
    uint32_t y;
} vector2d_t;

typedef struct rect {
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
} rect_t;

#pragma pack(1)
typedef union color {
    uint32_t  value;
    struct {
        uint8_t a;
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
} color_t;

#endif /* !VIDEO_HPP_ */
