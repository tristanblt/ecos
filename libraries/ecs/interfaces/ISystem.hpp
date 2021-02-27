#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

namespace ecs {
    class ISystem {
        public:
            virtual void start() = 0;
            virtual void update() = 0;
            virtual void stop() = 0;
    };
}

#endif /* !ISYSTEM_HPP_ */
