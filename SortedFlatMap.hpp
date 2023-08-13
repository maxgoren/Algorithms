#ifndef SORTED_FLAT_MAP_HPP
#define SORTED_FLAT_MAP_HPP
#include <iostream>
#include "Map.hpp"
#include "MapEntry.hpp"
#include "../Iterator/ArrayIterator.hpp"
#include "../Iterator/Iterable.hpp"
#include "../Iterator/Iterator.hpp"
using std::cout;
using std::endl;

template <class K, class V>
class SortedFlatMap : public Map<K,V>, public Iterable<MapEntry<K,V>> {
    private:
        int n;
        int maxN;
        MapEntry<K,V>* table;
        void grow() {
            MapEntry<K,V>* tmp = new MapEntry<K,V>[2*maxN];
            for (int i = 0; i < n; i++)
                tmp[i] = table[i];
            delete [] table;
            table = tmp;
            maxN *= 2;
        }
        void shrink() {
            MapEntry<K,V>* tmp = new MapEntry<K,V>[maxN/2 + 1];
            for (int i = 0; i < n; i++)
                tmp[i] = table[i];
            delete [] table;
            table = tmp;
            maxN /= 2;
        }
        int search(K key) {
            int l = 0;
            int r = n-1;
            int res = -1;
            while (r >= l) {
                int m = (l+r)/2;
                if (key == table[m].key) { res = m; r = m - 1;}
                else if (key < table[m].key) {
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            return res;
        }
    public:
    SortedFlatMap(int max = 5) {
        maxN = max;
        n = 0;
        table = new MapEntry<K,V>[maxN];
    }
    ~SortedFlatMap() {
        delete [] table;
    }
    void insert(K key, V info) {
        if (n + 1 == maxN) grow();
        int j = n;
        while (j > 0 && table[j-1].key > key) {
            table[j] = table[j - 1];
            j--;
        }
        table[j].key = key;
        table[j].value = info;
        n++;
    }
    V find(K key) {
        int idx = search(key);
        if (idx == -1) return V();
        return table[idx].value;
    }
    void erase(K key) {
        int p = maxN/2;
        if (n - 1 == p && n > 5) shrink();
        int idx = search(key);
        if (idx == -1) return;
        int j = idx;
        while (idx+1 <= n) {
            table[idx] = table[idx+1];
            idx++;
        }
        n--;
    }
    int size() {
        return n;
    }
    bool empty() {
        return n == 0;
    }
    void show() {
        for (int i = 0; i < n; i++)
            cout<<table[i].key<<" ";
        cout<<endl;
    }
    Iterator<MapEntry<K,V>>* iterator() const {
        return new ArrayIterator<MapEntry<K,V>>(table, n);
    }
};

#endif