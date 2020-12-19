#ifndef VIDEO_HPP_
#define VIDEO_HPP_

#include <libraries/std/types/CTypes.hpp>

struct vector2d {
    uint32 x;
    uint32 y;
};

struct rect {
    uint32 x;
    uint32 y;
    uint32 w;
    uint32 h;
};

#pragma pack(1)
union color {
    uint32  value;
    struct {
        uint8 a;
        uint8 r;
        uint8 g;
        uint8 b;
    };
};

#endif /* !VIDEO_HPP_ */
