#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

namespace ecs {
    class ISystem {
        public:
            virtual void start() {};
            // virtual void update() {};
            // virtual void stop() {};
    };
}

#endif /* !ISYSTEM_HPP_ */
