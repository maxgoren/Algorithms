#ifndef MAP_ENTRY_HPP
#define MAP_ENTRY_HPP

template <class K, class V>
class MapEntry {
    public:
        K key;
        V value;
        MapEntry(K key, V value) {
            this->key = key;
            this->value = value;
        }
        MapEntry() {
            
        }
};

#endif