#ifndef LINKED_SORTED_MAP_HPP
#define LINKED_SORTED_MAP_HPP
#include <iostream>
#include <limits>
#include "Map.hpp"
#include "MapEntry.hpp"
#include "../Iterator/Iterable.hpp"
#include "../Iterator/Iterator.hpp"
#include "../List/Linked.hpp"
using std::cout;
using std::endl;
using std::numeric_limits;

template <class K, class V>
class LinkedSortedMap : public Map<K,V>, public Iterable<MapEntry<K,V>> {
    private:
        class node : public MapEntry<K,V>, public Linked<node> {
            public:
            node(K key, V value, node* next) {
                this->key = key;
                this->value = value;
                this->next = next;
            }
        };
    node* head;
    node* z;
    int count;
    public:
        class ListIterator : public Iterator<MapEntry<K,V>> {
            private:
                node* curr;
                node* begin;
                node* end;
                MapEntry<K,V> ret;
            public:
                ListIterator(node* start, node* zed) {
                    curr = start;
                    begin = start;
                    end = zed;
                }
                void first() {
                    curr = begin;
                    ret.key = curr->key;
                    ret.value = curr->value;
                }
                void next() {
                    curr->key = ret.key;
                    curr->value = ret.value;
                    curr = curr->next;
                    if (curr != nullptr) {
                        ret.key = curr->value;
                        ret.value = curr->value;
                    }
                }
                bool done() {
                    return curr == end;
                }
                MapEntry<K,V>& value() {
                    return ret;
                }
        };
    public:
    LinkedSortedMap() {
        z = new node(std::numeric_limits<K>::max(),std::numeric_limits<V>::max(),z);
        head = new node(0,0,z);
        count = 0;
    }
    ~LinkedSortedMap() {
        while (head != z) {
            node *x = head;
            head = head->next;
            delete x;
        }
        delete z;
    }
    void insert(K key, V value) {
        node* x = head;
        while (key > x->next->key) x = x->next;
        node* t = new node(key, value, x->next);
        x->next = t;
        count++;
    }
    V find(K key) {
        node* x = head;
        while (x != z) {
            if (key == x->key)
                return x->value;
            x = x->next;
        }
        return head->value;
    }
    void show() {
        for (node* x = head->next; x != z; x = x->next)
            cout<<x->key<<" ";
        cout<<endl;
    }
    void erase(K key) {
        node* x = head;
        while (x->next->key != key) x = x->next;
        if (x->next != z) {
            node* t = x->next;
            x->next = x->next->next;
            delete t;
            count--;
        }
    }
    bool empty() {
        return head->next == z;
    }
    int size() {
        return count;
    }
    Iterator<MapEntry<K,V>>* iterator() const {
        return new ListIterator(head, z);
    }
};

#endif