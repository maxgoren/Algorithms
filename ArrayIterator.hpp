#ifndef ARRAY_ITERATOR_HPP
#define ARRAY_ITERATOR_HPP
#include "Iterator.hpp"

template <class T>
class ArrayIterator : public Iterator<T> {
    private:
        int currPos;
        T* arrayPtr;
        int N;
    public:
        ArrayIterator(T* arr, int n) {
            arrayPtr = arr;
            currPos = 0;
            N = n;
        }
        ~ArrayIterator() { }
        T& operator*() {
            return arrayPtr[currPos];
        }
        void first() {
            currPos = 0;
        }
        void next() {
            currPos++;
        }
        bool done() {
            return currPos == N;
        }
        T& value() {
            return arrayPtr[currPos];
        }
        
};


#endif