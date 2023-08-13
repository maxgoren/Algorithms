#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include "Map.hpp"
#include "LinkedSortedMap.hpp"

template <class K, class V>
class HashMap : public Map<K,V> {
    private:
        LinkedSortedMap<K,V>* table;
        int maxN;
        int n;
    public:
        HashMap(int max = 100) {
            maxN = max;
            n = 0;
            table = new LinkedSortedMap<K,V>[maxN];
        }
        ~HashMap() {
            delete [] table;
        }
        void insert(K key, V value) {
            int index = std::hash<K>()(key) % maxN;
            table[index].insert(key, value);
            n++;
        }
        void erase(K key) {
            int index = std::hash<K>()(key) % maxN;
            int pre = table[index].size();
            table[index].erase(key);
            if (table->size() < pre)
                n--;
        }
        V find(K key) {
            int index = std::hash<K>()(key) % maxN;
            return table[index].find(key);
        }
        void show() {
            for (int i = 0; i < maxN; i++) {
                if (!table[i].empty())
                    table[i].show();
            }
        }
        bool empty() {
            return n == 0;
        }
        int size() {
            return n;
        }
};

#endif