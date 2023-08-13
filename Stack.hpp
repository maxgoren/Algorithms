#ifndef STACK_HPP
#define STACK_HPP

template <class T>
class Stack {
    private:
        T* stack;
        int maxN;
        int n;
        void grow() {
            T* tmp = new T[2*maxN];
            for (int i = 0; i < n; i++)
                tmp[i] = stack[i];
            delete [] stack;
            stack = tmp;
            maxN *= 2;
        }
        void shrink() {
            T* tmp = new T[maxN/2 + 1];
            for (int i = 0; i < n; i++)
                tmp[i] = stack[i];
            delete [] stack;
            stack = tmp;
            maxN /= 2;
        }
    public:
        Stack(int max = 50) {
            maxN = max;
            stack = new T[maxN];
            n = 0;
        }
        ~Stack() {
            delete [] stack;
        }
        bool empty() {
            return n == 0;
        }
        int size() {
            return n;
        }
        void push(T info) {
            if (n+1 == maxN) grow();
            stack[++n] = info;
        }
        T& top() {
            return stack[n-1];
        }
        T pop() {
            return stack[n--];
        }
};

#endif