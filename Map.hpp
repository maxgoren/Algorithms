#ifndef MAP_HPP
#define MAP_HPP

template <class K, class V>
class Map {
    public:
    virtual void insert(K key, V value) = 0;
    virtual V find(K key) = 0;
    virtual void erase(K key) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void show() = 0;
};

#endif