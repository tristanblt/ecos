#ifndef ENTITY_HPP_
#define ENTITY_HPP_

namespace ecs {
    class Entity {
        public:
            Entity() = default;
            ~Entity() = default;

            void addComponent();

        protected:
        private:
    };
}

#endif /* !ENTITY_HPP_ */
