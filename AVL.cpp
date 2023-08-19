#include <iostream>
#include <cstring>
#include "../Stack/Stack.hpp"
using namespace std;



template <class T>
class AVL {
    private:
        struct node {
            T info;
            int height;
            node* left;
            node* right;
            node(T i) {
                info = i;
                height = 0;
                left = nullptr;
                right = nullptr;
            }
        };
        typedef node* link;
        link head;
        int height(link h) {
            return (h == nullptr) ? -1:h->height;
        }
        int balFactor(link h) {
            if (h == nullptr) return -1;
            return height(h->left) - height(h->right);
        }
        link rotL(link h) {
            link x = h->right;
            h->right = x->left;
            x->left = h;
            h->height = 1 + max(height(h->left), height(h->right));
            x->height = 1 + max(height(x->left), height(x->right));
            return x;
        }
        link rotR(link h) {
            link x = h->left;
            h->left = x->right;
            x->right = h;
            h->height = 1 + max(height(h->left), height(h->right));
            x->height = 1 + max(height(x->left), height(x->right));
            return x;
        }
        link insert(link h, T info) {
            if (h == nullptr)
                return new node(info);
            if (info < h->info) {
                h->left = insert(h->left, info);
            } else {
                h->right = insert(h->right, info);
            }
            h->height = 1 + max(height(h->left), height(h->right));
            if (balFactor(h) < -1) {
                if (balFactor(h->right) > 0) {
                    h->right = rotR(h->right);
                }
                h = rotL(h);
            } else if (balFactor(h) > 1) { 
                if (balFactor(h->left) < 0) {
                    h->left = rotL(h->left);
                }
                h = rotR(h);
            }
            return h;
        }
        void visit(link h) {
            if (h != nullptr) {
                cout<<h->info<<" ";
                visit(h->left);
                visit(h->right);
            }
        }
        void sort(link h) {
            if (h != nullptr) {
                sort(h->left);
                cout<<h->info<<" ";
                sort(h->right);
            }
        }
        int arrIndex;
        void gather(link h, T a[]) {
            if (h != nullptr) {
                gather(h->left,a);
                a[arrIndex++] = h->info;
                gather(h->right,a);
            }
        }
        void cleanup(link h) {
            if (h != nullptr) {
                cleanup(h->left);
                cleanup(h->right);
                delete h;
            }
        }
    public:
        AVL() {
            head = nullptr;
        }
        ~AVL() {
            cleanup(head);
        }
        void insert(T info) {
            head = insert(head, info);
        }
        void show() {
            visit(head);
            cout<<endl;
        }
        void sort() {
            sort(head);
            cout<<endl;
        }
        void sorted(T a[], int N) {
            cleanup(head);
            for (int i = 0; i < N; i++)
                head = insert(head, a[i]);
            sort();
            arrIndex = 0;
            gather(head, a);
        }
        class AVLIterator {
            private:
                node* root;
                node* curr;
                Stack<node*> sf;
            public:
                AVLIterator(node* root_) {
                    root = root_;
                    curr = root_;
                }
        };
};



int main() {
    AVL<char> tr;
    char sed[20] = "ASEARCHINGEXAMPLE";
    tr.sorted(sed, strlen(sed));
    for (int i = 0; i < strlen(sed); i++)
        cout<<sed[i]<<" ";
    cout<<endl;
    return 0;
}