#ifndef SORTED_TREE_MAP_HPP
#define SORTED_TREE_MAP_HPP
#include <iostream>
#include "Map.hpp"
#include "MapEntry.hpp"
using std::cout;
using std::endl;

template <class K, class V>
class SortedTreeMap : public Map<K,V> {
    private:
        class node : public MapEntry<K,V> {
            public:
            bool color;
            node* left;
            node* right;
            node(K k, V val, bool c, node* ll, node* rr) : MapEntry<K,V>(k, val) {
                color = c;
                left = ll; right = rr;
            }
            node(const node& o) {
                this->key = o.key;
                this->value = o.value;
                this->color = o.color;
                this->left = o.left;
                this->right = o.right;
            }
        };
        node *head, *z, *x, *p, *g, *gg;
        int n;
        node* rotate(K key, node* y) {
            node *c, *gc;
            c = (key < y->key) ? y->left:y->right;
            if (key < c->key) {
                gc = c->left; c->left = gc->right; gc->right = c;
            } else {
                gc = c->right; c->right = gc->left; gc->left = c;
            }
            if (key < y->key) y->left = gc; else y->right = gc;
            return gc;
        }
        void split(K key) {
            x->color = true; x->left->color = false; x->right->color = false;
            if (p->color) {
                g->color = true;
                if (key < p->key != key < g->key) p = rotate(key, g);
                x = rotate(key,gg);
                x->color = false;
            }
        }
        void sort(node* h) {
            if (h != z) {
                sort(h->left);
                cout<<h->key<<" ";
                sort(h->right);
            }
        }
        node* min(node* h) {
            node* q = h;
            while (q->left != z) q = q->left;
            return q;
        }
        node* eraseMin(node* h) {
            if (h->left == z)
                return h->right;
            h->left = eraseMin(h->left);
            return h;
        }
        void cleanUp(node* h) {
            if (h != z) {
                cleanUp(h->left);
                cleanUp(h->right);
                delete h;
            }
        }
    public:
        SortedTreeMap() {
            z = new node(std::numeric_limits<K>::max(), std::numeric_limits<V>::max(), false, nullptr, nullptr);
            z->left = z; z->right = z;
            head = new node(std::numeric_limits<K>::min(), std::numeric_limits<V>::min(), false, z, z);
            n = 0;
        }
        ~SortedTreeMap() {
            cleanUp(head->right);
            delete z;
            delete head;
        }
        bool empty() {
            return head->right == z;
        }
        int size() {
            return n;
        }
        void insert(K key, V value) {
            x = head; p = x; g = p;
            while (x != z) {
                gg = g; g = p; p = x;
                x = (key < x->key) ? x->left:x->right;
                if (x->left->color && x->right->color)
                    split(key);
            }
            x = new node(key, value, true, z, z);
            if (key < p->key) p->left = x;
            else p->right = x;
            split(key);
            n++;
            head->right->color = false;
        }
        void erase(K key) {
            x = head->right; p = head;
            while (x != z) {
                if (key == x->key)
                    break;
                p = x;
                x = (key < x->key) ? x->left:x->right;
            }
            if (x == z) return; //not found.
            node* t = x;
          
            if (x->right == z) {
                x = x->left;
            } else if (x->right->left == z) {
                x = x->right; x->left = t->left;
            } else {
                node* c = x->right;
                while (c->left->left != z) c = c->left;
                x = c->left; c->left = x->right;
                x->right = t->right; x->left = t->left;
            }
            if (key < p->key) p->left = x;
            else p->right = x;
            delete t;
            n--;
        }
        V find(K key) {
            x = head->right;
            while (x != z) {
                if (key == x->key)
                    return x->value;
                x = (key < x->key) ? x->left:x->right;
            }
            return z->value;
        }
        void show() {
            sort(head->right);
            cout<<endl;
        }
};

#endif