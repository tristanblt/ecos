#ifndef IDOF_HPP_
#define IDOF_HPP_

namespace ecs {
    class IDOf {
        public:
            template <typename T>
            static int component() {
                static int id = _componentCounter++;
                return (id);
            }

            template <typename T>
            static int system() {
                static int id = _systemCounter++;
                return (id);
            }

            static int _componentCounter;
            static int _systemCounter;
    };
}

#endif /* !IDOF_HPP_ */