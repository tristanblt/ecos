#ifndef ASYSTEM_HPP_
#define ASYSTEM_HPP_

#include "interfaces/ISystem.hpp"

namespace ecs {
    class Ecos;

    class ASystem : public ISystem {
        public:
            void setEcos(Ecos *ecos);

        protected:
            Ecos *_ecos;
    };
}

#endif /* !ASYSTEM_HPP_ */
