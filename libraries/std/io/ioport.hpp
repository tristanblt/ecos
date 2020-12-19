#ifndef IOPORT_HPP_
#define IOPORT_HPP_

#include <libraries/std/types/CTypes.hpp>

namespace std {
    class IOPort {
        public:
            static void enable(void);
            static void disable(void);
            static void outPortB(uint32 port, uint8 value);
            static void outPortW(uint32 port, uint16 value);
            static void outPortL(uint32 port, uint32 value);
            static unsigned char inPortB(uint32 port);
            static uint16 inPortW(uint32 port);
            static uint32 inPortL(uint32 port);
    };
}

#endif /* !IOPORT_HPP_ */
