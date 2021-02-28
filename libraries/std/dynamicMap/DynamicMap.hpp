#ifndef DYNAMICMAP_HPP_
#define DYNAMICMAP_HPP_

#include <libraries/std/types/CTypes.hpp>
#include <kernel/panic.hpp>
#include <drivers/serial/Serial.hpp>
#include <libraries/std/dynamicList/DynamicList.hpp>

void *malloc(uint32 size);
void free(void *ptr);

namespace std {
    template <typename U, typename T>
    struct Pair {
        Pair(U f, T *s) :
            first(f),
            second(s)
        {}
        ~Pair() = default;

        U first;
        T *second;
    };

    template <typename U, typename T>
    class DynamicMap {
        public:
            DynamicMap() = default;
            ~DynamicMap() = default;

            T *add(U index, T *element)
            {
                _list.add(new Pair<U, T>(index, element));
                return (element);
            }

            T *operator[](U index)
            {
                for (uint32 i = 0; i < size(); i++)
                    if (index == _list[i]->first)
                        return (_list[i]->second);
                return (nullptr);
            }

            DynamicList<T> getAll(U index)
            {
                DynamicList<T> list;

                for (uint32 i = 0; i < size(); i++)
                    if (index == _list[i]->first)
                        list.add(_list[i]->second);
                return (list);
            }

            uint32 size()
            {
                return (_list.size());
            }

        private:
            DynamicList<Pair<U, T>> _list;
    };
}

#endif /* !DYNAMICMAP_HPP_ */
