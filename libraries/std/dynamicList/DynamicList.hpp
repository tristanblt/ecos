#ifndef DYNAMICLIST_HPP_
#define DYNAMICLIST_HPP_

#include <libraries/std/types/CTypes.hpp>
#include <kernel/panic.hpp>
#include <drivers/serial/Serial.hpp>

void *malloc(uint32 size);
void free(void *ptr);

namespace std {
    template <typename T>
    class DynamicList {
        public:
            DynamicList()
            {
                _list = nullptr;
                _count = 0;

            }

            ~DynamicList()
            {

            }

            T *add()
            {
                T *element = new T();

                if (!element)
                    PANIC("new() fail");
                addElementToList(element);
                return (element);
            }

            T *add(T *element)
            {
                addElementToList(element);
                return (element);
            }

            T *operator[](uint32 index)
            {
                if (index >= _count)
                    return (nullptr);
                return ((T *)_list[index]);
            }

            uint32 size()
            {
                return (_count);
            }

        private:
            void addElementToList(T *element)
            {
                T **savedList = _list;

                _count++;
                _list = (T **)malloc(sizeof(T *) * (_count + 1));
                if (!_list)
                    PANIC("new() fail");
                if (savedList) {
                    for (uint32 i = 0; i < (_count - 1); i++)
                        _list[i] = savedList[i];
                    free(savedList);
                }
                _list[_count - 1] = element;
                _list[_count] = nullptr;
            }

            T **_list;
            uint32 _count;
    };
}

#endif /* !DYNAMICLIST_HPP_ */
