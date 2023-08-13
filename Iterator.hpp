#ifndef ITERATOR_HPP
#define ITERATOR_HPP

template <class T>
class Iterator {
    public:
        virtual ~Iterator() { }
        virtual void first() = 0;
        virtual void next() = 0;
        virtual bool done() = 0;
        virtual T& value() = 0;
};


#endif