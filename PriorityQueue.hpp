#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP
#include <functional>

template <class T, class Comp = std::less<T>>
class PriorityQueue {
    public:
        virtual void push(T item) = 0;
        virtual T    pop() = 0;
        virtual T&   peek() = 0;
        virtual int  size() = 0;
        virtual bool empty() = 0;
};

#endif