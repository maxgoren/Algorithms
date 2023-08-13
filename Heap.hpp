#ifndef HEAP_HPP
#define HEAP_HPP
#include <functional>
#include "PriorityQueue.hpp"

template <class T, typename Comp = std::less<T>>
class Heap : public PriorityQueue<T, Comp> {
    private:
        T* heap;
        int maxN;
        int n;
        void grow() {
            T* tmp = new T[2*maxN];
            for (int i = 0; i < n; i++)
                tmp[i] = heap[i];
            delete [] heap;
            heap = tmp;
            maxN *= 2;
        }
        void shrink() {
            T* tmp = new T[maxN/2 + 1];
            for (int i = 0; i < n; i++)
                tmp[i] = heap[i];
            delete [] heap;
            heap = tmp;
            maxN /= 2;
        }
        void exch(int l, int r) {
            T tmp = heap[l];
            heap[l] = heap[r];
            heap[r] = tmp;
        }
        bool compare(int l, int r) {
            return Comp()(heap[l], heap[r]);
        }
        void downheap(int k) {
            while (2*k <= n) {
                int j = k+k;
                if (j < n && compare(j, j+1)) j++;
                if (!compare(k, j)) break;
                exch(k, j); k = j;
            }
        }
        void upheap(int k) {
            while (k > 1 && compare(k/2, k)) {
                exch(k, k/2);
                k = k/2;
            }
        }
    public:
        Heap(int max = 50) {
            heap = new T[max];
            maxN = max;
            n = 0;
        }
        ~Heap() {
            delete [] heap;
        }
        int size() {
            return n;
        }
        bool empty() {
            return n == 0;
        }
        void push(T info) {
            if (n+1 == maxN) grow();
            heap[++n] = info;
            upheap(n);
        }
        T& peek() {
            return heap[1];
        }
        T pop() {
            exch(1, n--);
            downheap(1);
            return heap[n+1];
        }
};

#endif