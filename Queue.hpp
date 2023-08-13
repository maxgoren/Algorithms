#ifndef QUEUE_HPP
#define QUEUE_HPP

template <class T>
class Queue {
    private:
        struct node {
            T info;
            node* next;
            node(T info) {
                this->info = info;
                this->next = next;
            }
        };
        node* head;
        node* back;
        int count;
    public:
        Queue() {
            count = 0;
            head = nullptr;
            back = nullptr;
        }
        ~Queue() {
            node* x = head;
            while (x != nullptr) {
                node* t = x;
                x = x->next;
                delete t;
            }
        }
        int size() const {
            return count;
        }
        bool empty() const {
            return head == nullptr;
        }
        void push(T info) {
            node* t = new node(info);
            if (empty()) {
                head = t;
                back = t;
            } else {
                back->next = t;
                back = t;
            }
            count++;
        }
        T& front() {
            return head->info;
        }
        T pop() {
            T ret = head->info;
            node* t = head;
            head = head->next;
            delete t;
            count--;
            return ret;
        }
};

#endif