#ifndef SERIAL_HPP_
#define SERIAL_HPP_

#include <libraries/std/types/CTypes.hpp>
#include <libraries/std/io/IOPort.hpp>
#include <kernel/devices/bios.hpp>

namespace drvs {
    class Serial {
        public:
            static void init();
            static void putstr(uint8 *str);
            static void putchar(uint8 c);

            static void putEcosLogo();
            static void putTask(uint8 *str, bool done);
    };
}


#endif /* !SERIAL_HPP_ */
