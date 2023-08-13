#ifndef ITERABLE_HPP
#define ITERABLE_HPP
#include "Iterator.hpp"

template <class T>
class Iterable {
    public:
        virtual Iterator<T>* iterator() const = 0;
};


#endif