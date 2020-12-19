#ifndef MEMORY_HPP_
#define MEMORY_HPP_

#include <libraries/std/types/CTypes.hpp>

namespace std {
    class Memory {
        public:
            static void cpy8(void *src, void *dst, uint32 size);
            static void cpy32(void *src, void *dst, uint32 size);
            static void *set8(void *dest, uint8 val, uint32 len);
            static void *set32(void *dest, uint32 val, uint32 len);
    };
}

#endif /* !MEMORY_HPP_ */
