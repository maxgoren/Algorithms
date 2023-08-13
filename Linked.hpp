#ifndef LINKED_HPP
#define LINKED_HPP

template <class T>
class Linked {
    public:
        T* next;
        Linked(T* n) {
            next = n;
        }
        Linked() {
            next = nullptr;
        }
};

template <class T>
class DLinked : public Linked<T> {
    public:
        T* prev;
        DLinked(T* p, T* n) {
            this->next = n;
            prev = p;
        }
        DLinked() {
            this->next = nullptr;
            this->prev = nullptr;
        }
};


#endif