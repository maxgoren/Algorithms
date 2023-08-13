#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include "Linked.hpp"
#include "../Iterator/Iterable.hpp"
#include "../Iterator/Iterable.hpp"
using std::cout;
using std::endl;

template <class T>
class List : public Iterable<T> {
    private:
        class node : public DLinked<node> {
            public:
            T info;
            node(T i, node* p, node* n) {
                this->prev = p;
                this->next = n;
                info = i;
            }
            node(T i) {
                this->prev = nullptr;
                this->next = nullptr;
                info = i;
            }
            node() {
                this->prev = nullptr;
                this->next = nullptr;
            }
        };
        node* head;
        node* z;
        int n;
    public:
        List() {
            z = new node;
            head = new node;
            z->next = z;
            head->next = z;
            z->prev = head;
            head->prev = head;
            n = 0;
        }
        ~List() {
            while (head != z) {
                node* x = head;
                head = head->next;
                delete x;
            }
            if (z) delete z;
        }
        int size() {
            return n;
        }
        bool empty() {
            return head->next == z;
        }
        void pushFront(T info) {
            head->next = new node(info, head, head->next);
            head->next->next->prev = head->next;
            n++;
        }
        void pushBack(T info) {
            z->prev = new node(info, z->prev, z);
            z->prev->prev->next = z->prev;
            n++;
        }
        void insertAfter(T existingItem, T toInsert) {
            node* it = head->next;
            while (it != z) {
                if (it->info == existingItem) {
                    break;
                }
                it = it->next;
            }
            if (it == z) {
                pushBack(toInsert);
            } else {
                node* t = new node(toInsert, it, it->next);
                it->next->prev = t;
                it->next = t;
                n++;
            }
        }
        void insertBefore(T existingItem, T toInsert) {
            node* x = head->next;
            node* p = head;
            while (x != z) {
                if (x->info == existingItem) {
                    break;
                }
                p = x;
                x = x->next;
            }
            node* t = new node(toInsert, p, x);
            t->next->prev = t;
            p->next = t;
            n++;
        }
        T get(int pos) {
            int i = 0;
            node* it = head->next;
            while(it != z) {
                it = it->next;
                i++;
            }
            return it->value;
        }
        void erase(T info) {
            node* x = head->next;
            node* p = head;
            while (x != z) {
                if (x->info == info)
                    break;
                p = x;
                x = x->next;
            }
            if (x == z) return;
            p->next = p->next->next;
            p->next->prev = p;
            delete x;
            n--;
        }
        T popFront() {
            T ret = head->next->info;
            node* t = head->next;
            head->next = head->next->next;
            head->next->prev = head;
            delete t;
            n--;
            return ret;
        }
        T popBack() {
            T ret = z->prev->info;
            node* t = z->prev;
            z->prev = z->prev->prev;
            z->prev->next = z;
            delete t;
            n--;
            return ret;
        }
        void show() {
            for (node* it = head->next; it != z; it = it->next) {
                cout<<it->info<<" ";
            }
            cout<<endl;
        }
    private:
        class ListIteratorBase : public Iterator<T> {
            private:
                node* curr;
                node* begin;
                node* end;
                T ret;
            public:
                ListIteratorBase(node* start, node* zed) {
                    curr = start;
                    begin = start;
                    end = zed;
                }
                void first() {
                    curr = begin;
                    ret = curr->info;
                }
                void next() {
                    curr->info = ret;
                    curr = curr->next;
                    if (curr != nullptr) {
                        ret = curr->info;
                    }
                }
                bool done() {
                    return curr == end;
                }
                T& value() {
                    return ret;
                }
        };
        Iterator<T>* iterator() const {
            return new ListIteratorBase(head->next, z);
        }
    public:
        class ListIterator {
            private:
                ListIteratorBase* itr;
                //ListIterator(const ListIterator&);
                ListIterator& operator=(const ListIterator&);
            public:
                ListIterator(ListIteratorBase* it) : itr(it) { }
                ~ListIterator() { delete itr; }
                ListIteratorBase* operator->() {
                    return itr;
                }
                ListIteratorBase* operator*() {
                    return itr;
                }
        };
        ListIterator getIterator() {
            return ListIterator(new ListIteratorBase(head->next, z));
        }
};

#endif