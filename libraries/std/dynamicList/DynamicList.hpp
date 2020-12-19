#ifndef DYNAMICLIST_HPP_
#define DYNAMICLIST_HPP_

#include <libraries/std/types/CTypes.hpp>
#include <kernel/panic.hpp>

void *malloc(uint32 size);
void free(void *ptr);

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
            T *element = (T *)malloc(sizeof(T));

            if (!element)
                PANIC("malloc() fail");
            addElementToList(element);
            return (element);
        }

        T *add(T *element)
        {
            addElementToList(element);
            return (element);
        }

    private:
        void addElementToList(T *element)
        {
            void **savedList = _list;

            _count++;
            _list = (void **)malloc(sizeof(void *) * (_count + 1));
            if (!_list)
                PANIC("malloc() fail");
            if (savedList) {
                for (uint32 i = 0; i < (_count - 1); i++)
                    _list[i] = savedList[i];
                free(savedList);
            }
            _list[_count - 1] = element;
            _list[_count] = nullptr;
        }

        void **_list;
        uint32 _count;
};

#endif /* !DYNAMICLIST_HPP_ */
