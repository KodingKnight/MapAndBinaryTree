#include "binTree.h"

template <typename T, typename S>
class Map;

template <typename T, typename S>
class MapIterator;

template <typename T, typename S>
class MapNode;

using std::pair;


/// For debugging purposes (remove later)
#include <iostream>
using std::cout;

/*
template <typename T, typename S>
class MapNode{
    friend class Map<T,S>;
    friend class MapIterator<T,S>;

private:
    MapNode() : element(), right(nullptr), left(nullptr), parent(nullptr){}
    MapNode(const pair<T,S> & e, MapNode * right0, MapNode * left0, MapNode * parent0);
    ~MapNode(){ delete &element; }

    pair<T,S> element;

    MapNode<T,S> * left;
    MapNode<T,S> * right;
    MapNode<T,S> * parent;


    MapNode<T,S>& operator=(const MapNode<T,S> & node);
    MapNode<T,S>& operator==(const MapNode<T,S> & node) const;
    MapNode<T,S>& operator!=(const MapNode<T,S> & node) const;
};



template <typename T, typename S>
MapNode<T,S>::MapNode(const pair<T,S> & e, MapNode * right0, MapNode * left0, MapNode * parent0) :
    element(e), left(left0), right(right0), parent(parent0){}

template <typename T, typename S>
MapNode<T,S>& MapNode<T,S>::operator=(const MapNode<T,S> & node){
    element = node.element;
    left = node.left;
    right = node.right;
    parent = node.parent;
}

*/

/// How should this work?
/*
bool operator==(const MapNode<T,S> & node) const{
    return (element.first == node.element.first && element.second == node.element.second);
}

bool operator!=(const MapNode<T,S> & node) const{
    return (element.first != node.element.first || element.second != node.element.second);
}
*/




template <typename T, typename S>
class MapIterator{
    friend class Map<T,S>;

public:
    MapIterator() : treeIter(){}
    T & operator*() const{return *treeIter; }
    T * operator->() const{return &(*treeIter);}
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

/// FIX THIS YO. Do I go right or left?

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

/// FIX THIS YO. Do I go right or left?

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
    Map(const Map & m) { transfer(m); }
    ~Map();
    void transfer(Map<T,S> & m);
    Map<T,S>& operator=(const Map<T,S> & m);
    S& operator[](const iterator & iter)const;

    int size() const;
    bool empty() const;
    iterator begin() const;
    iterator end() const;
    int count(const pair<T,S> & element) const;
    iterator find(const pair<T,S> & element) const;
    bool insert(const pair<T,S> & element);
    bool erase(const T & key);
    bool erase(const iterator & iter);
    void clear();
    void swap(Map<T,S> & m);

private:
    BinTree<pair<T,S>> binTree;

    iterator find(const T & element) const;
};

template <typename T, typename S>
inline Map<T,S>::~Map(){
    binTree.clear();
    //delete pHeadNode;
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
inline S& Map<T,S>::operator[](const Map<T,S>::iterator & iter) const{
    return *iter;
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
inline int Map<T,S>::count(const pair<T,S> & element) const{
    return binTree.find(element) != NULL;
}

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::find(const pair<T,S> & element) const{
    return iterator(binTree.find(element));
}

/// Change (*iter).second to iter->second

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::find(const T & element) const{
    BinTreeIterator<pair<T,S>> iter = binTree.head();
    while(iter != nullptr && (*iter).first != element){
        if(element < (*iter).second){
            iter.left();
        }else{
            iter.right();
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


