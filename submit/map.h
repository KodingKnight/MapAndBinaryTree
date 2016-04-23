#include "binTree.h"

template <typename T, typename S>
class Map;

template <typename T, typename S>
class MapIterator;

template <typename T, typename S>
class MapNode;

using std::pair;

// For debugging purposes
//#include <iostream>
//using std::cout;

template <typename T, typename S>
class MapIterator{
    friend class Map<T,S>;

public:
    MapIterator() : treeIter(){}
    pair<T,S> & operator*() const{return *treeIter; }
    pair<T,S> * operator->() const{return &(*treeIter);}
    bool operator==(const MapIterator<T,S> & iter) const{return treeIter == iter.treeIter;}
    bool operator!=(const MapIterator<T,S> & iter) const{return treeIter != iter.treeIter;}
    MapIterator<T,S> & operator++(); // prefix
    MapIterator<T,S> & operator--();
    MapIterator<T,S> operator++(int); // postfix
    MapIterator<T,S> operator--(int);

private:
    explicit MapIterator(BinTreeIterator<pair<T,S>> iter) : treeIter(iter){}
    //MapNode<T,S> * pNode;
    BinTreeIterator<pair<T,S>> treeIter;
};

template <typename T, typename S>
inline MapIterator<T,S> & MapIterator<T,S>::operator++(){ //prefix
    treeIter.successor();
    return *this;
}

template <typename T, typename S>
inline MapIterator<T,S> & MapIterator<T,S>::operator--(){
    treeIter.predecessor();
    return *this;
}

template <typename T, typename S>
inline MapIterator<T,S> MapIterator<T,S>::operator++(int){ //postfix
    MapIterator<T,S> temp = *this;
    treeIter.successor();
    return temp;
}

template <typename T, typename S>
inline MapIterator<T,S> MapIterator<T,S>::operator--(int){
    MapIterator<T,S> temp = *this;
    treeIter.predecessor();
    return temp;
}







template <typename T, typename S>
class Map{
public:
    typedef MapIterator<T,S> iterator;

    Map() : binTree() {}
    Map(Map<T,S> & m) { transfer(m); }
    ~Map();
    void transfer(Map<T,S> & m);
    Map<T,S>& operator=(const Map<T,S> & m);
    S& operator[](const T & element);

    int size() const;
    bool empty() const;
    iterator begin() const;
    iterator end() const;
    int count(const T & element) const;
    iterator find(const T & element) const;
    iterator find(const pair<T,S> & element) const;
    bool insert(const pair<T,S> & element);
    bool erase(const T & key);
    bool erase(const iterator & iter);
    void clear();
    void swap(Map<T,S> & m);

private:
    BinTree<pair<T,S>> binTree;
};

template <typename T, typename S>
inline Map<T,S>::~Map(){
    clear();
}

template <typename T, typename S>
inline void Map<T,S>::transfer(Map<T,S> & m){
    binTree = m.binTree;
}

template <typename T, typename S>
inline Map<T,S>& Map<T,S>::operator=(const Map<T,S> & m){
    transfer(m);
    return *this;
}

template <typename T, typename S>
inline S& Map<T,S>::operator[](const T & element){
    MapIterator<T,S> iter;
    //MapIterator<T,S> emptyIter;
    iter = find(element);
    //if(iter == emptyIter){
    //    insert(pair<T,S>(element, NULL));
    //}
    return iter->second;
}

template <typename T, typename S>
inline int Map<T,S>::size() const{
    return binTree.size();
}

template <typename T, typename S>
inline bool Map<T,S>::empty() const{
    return binTree.size() == 0;
}

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::begin() const{
    return iterator(binTree.min(binTree.head()));
}

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::end() const{
    return iterator(binTree.max(binTree.head()));
}

template <typename T, typename S>
inline int Map<T,S>::count(const T & element) const{
    MapIterator<T,S> emptyIter;
    return find(element) != emptyIter;
}

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::find(const pair<T,S> & element) const{
    return iterator(binTree.find(element));
}

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::find(const T & element) const{
    BinTreeIterator<pair<T,S>> iter = binTree.head();
    BinTreeIterator<pair<T,S>> emptyIter;
    while(iter != emptyIter && iter->first != element){
        if(element < iter->first){
            iter.left();
            //cout << "left ";
        }else{
            iter.right();
            //cout << "right ";
        }
    }
    return iterator(iter);
}

template <typename T, typename S>
inline bool Map<T,S>::insert(const pair<T,S> & element){
    return binTree.insert(element);
}

template <typename T, typename S>
inline bool Map<T,S>::erase(const T & key){
    MapIterator<T,S> iter = find(key);
    return erase(iter);
}

template <typename T, typename S>
inline bool Map<T,S>::erase(const Map<T,S>::iterator & iter){
    return binTree.erase(iter.treeIter);
}

template <typename T, typename S>
inline void Map<T,S>::clear(){
    binTree.clear();
}

template <typename T, typename S>
inline void Map<T,S>::swap(Map<T,S> & m){
    binTree.swap(m.binTree);
}


