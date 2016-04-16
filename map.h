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

/// Should I be returning the pair or the second element


template <typename T, typename S>
class MapNode{
    friend class Map<T,S>;
    friend class MapIterator<T,S>;

private:
    MapNode() : element(), right(nullptr), left(nullptr), parent(nullptr){}
    MapNode(const pair<T,S> & e, MapNode * right0, MapNode * left0, MapNode * parent0);
    ~MapNode(){ delete &element; }

    /*pair<T,S> element;

    MapNode<T,S> * left;
    MapNode<T,S> * right;
    MapNode<T,S> * parent;
    */




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
    MapIterator() : pNode(NULL){}
    T & operator*() const{return (pNode->element).second; }
    T * operator->() const{return &((pNode->element).second);}
    bool operator==(const MapIterator<T,S> & iter) const{return pNode == iter.pNode;}
    bool operator!=(const MapIterator<T,S> & iter) const{return pNode != iter.pNode;}
    MapIterator<T,S> & operator++(); // prefix
    MapIterator<T,S> & operator--();
    MapIterator<T,S> operator++(int); // postfix
    MapIterator<T,S> operator--(int);

private:
    explicit MapIterator(MapNode<T,S> * p) : pNode(p){}
    MapNode<T,S> * pNode;
};

/// FIX THIS YO. Do I go right or left?

template <typename T, typename S>
inline MapIterator<T,S> & MapIterator<T,S>::operator++(){ //prefix
    pNode = pNode->right;
    return *this;
}

template <typename T, typename S>
inline MapIterator<T,S> & MapIterator<T,S>::operator--(){
    pNode = pNode->left;
    return *this;
}

/// FIX THIS YO. Do I go right or left?

template <typename T, typename S>
inline MapIterator<T,S> MapIterator<T,S>::operator++(int){ //postfix
    MapIterator<T,S> temp = *this;
    pNode = pNode-> right;
    return temp;
}

template <typename T, typename S>
inline MapIterator<T,S> MapIterator<T,S>::operator--(int){
    MapIterator<T,S> temp = *this;
    pNode = pNode -> parent;
    return temp;
}







template <typename T, typename S>
class Map{
public:
    typedef MapIterator<T,S> iterator;

    Map() : mapSize(0), pHeadNode(NULL) {}
    Map(const Map & m) { transfer(m); }
    ~Map();
    void transfer(Map<T,S> & m);
    Map<T,S>& operator=(const Map<T,S> & m);
    S& operator[](const iterator & iter)const;

    int size() const;
    bool empty() const;
    iterator head() const;
    iterator begin() const;
    iterator end() const;
    iterator min(const iterator iter) const;
    iterator max(const iterator iter) const;
    int count(const T & element) const;
    iterator find(const T & element) const;
    bool insert(const pair<T,S> & element);
    bool erase(const S & key);
    bool erase(const iterator & iter);
    void clear();
    void swap(Map<T,S> & m);

private:
    int mapSize;
    MapNode<T,S> * pHeadNode;
    MapNode<T,S>* min(MapNode<T,S>* node) const;
    MapNode<T,S>* max(MapNode<T,S>* node) const;
    void transplant(MapNode<T,S>* u, MapNode<T,S>* v);
};

template <typename T, typename S>
inline Map<T,S>::~Map(){
    clear();
    //delete pHeadNode;
}

template <typename T, typename S>
inline void Map<T,S>::transfer(Map<T,S> & m){
    /// transfer all the things from m to original.
    mapSize = m.size();
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
    return mapSize;
}

template <typename T, typename S>
inline bool Map<T,S>::empty() const{
    return mapSize == 0;
}

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::head() const{
    return iterator(pHeadNode);
}

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::begin() const{
    return MapIterator<T,S>(min(pHeadNode));
}

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::end() const{
    return MapIterator<T,S>(max(pHeadNode));
}

template <typename T, typename S>
inline MapNode<T,S>* Map<T,S>::min(MapNode<T,S>* node) const{
    MapNode<T,S>* tempNode = node;
    while(tempNode->left != nullptr){
        tempNode = tempNode->left;
    }
    return tempNode;
}

template <typename T, typename S>
inline MapNode<T,S>* Map<T,S>::max(MapNode<T,S>* node) const{
    MapNode<T,S>* tempNode = node;
    while(tempNode->right != nullptr){
        tempNode = tempNode->right;
    }
    return tempNode;
}

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::min(const Map<T,S>::iterator iter) const{
    MapNode<T,S>* node = iter.pNode;
    while(node->left != nullptr){
        node = node->left;
    }
    return MapIterator<T,S>(node);
}

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::max(const Map<T,S>::iterator iter) const{
    MapNode<T,S>* node = iter.pNode;
    while(node->right != nullptr){
        node = node->right;
    }
    return MapIterator<T,S>(node);
}

template <typename T, typename S>
inline int Map<T,S>::count(const T & element) const{
    MapIterator<T,S> iter = find(element);
    return iter != NULL;
}

template <typename T, typename S>
inline typename Map<T,S>::iterator Map<T,S>::find(const T & element) const{
    /// find the things in the list
    return NULL;
}

template <typename T, typename S>
inline bool Map<T,S>::insert(const pair<T,S> & element){
    if(pHeadNode == NULL){
        pHeadNode = new MapNode<T,S>(element, nullptr, nullptr, nullptr);
    }else{
        MapNode<T,S>* y;
        MapNode<T,S>* x = pHeadNode;
        while(x != nullptr){
            y = x;
            if(element.first == (x->element).first){
                return false;
            }else if(element.first < (x->element).first){
                x = x->left;
            }else{
                x = x->right;
            }
        }
        if(element.first < (y->element).first){
            y->left = new MapNode<T,S>(element, nullptr, nullptr, y);
        }else{
            y->right = new MapNode<T,S>(element, nullptr, nullptr, y);
        }
    }
    ++mapSize;
    return true;
}

template <typename T, typename S>
inline bool Map<T,S>::erase(const S & key){
    MapIterator<T,S> iter = find(key);
    return erase(iter);
}

template <typename T, typename S>
inline bool Map<T,S>::erase(const Map<T,S>::iterator & iter){
    MapNode<T,S>* z = iter.pNode;
    if(z->left == nullptr){
        transplant(z, z->right);
    }else if(z->right == nullptr){
        transplant(z, z->left);
    }else{
        MapNode<T,S>* y = min(z->right);
        if(y != z->right){
            transplant(y, y->right);
            y->right = z->right;
            z->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    //delete z;
    --mapSize;
    return true;
}

template <typename T, typename S>
void Map<T,S>::transplant(MapNode<T,S>* u, MapNode<T,S>* v){
    if(pHeadNode == u){
        pHeadNode = v;
        v->parent = nullptr;
    }else{
        MapNode<T,S>* temp = u->parent;
        if(temp->left == u){
            temp->left = v;
        }else{
            temp->right = v;
        }
        v->parent = temp;
    }
}

template <typename T, typename S>
inline void Map<T,S>::clear(){
    /// erase all the things
    mapSize = 0;
}

template <typename T, typename S>
inline void Map<T,S>::swap(Map<T,S> & m){
    Map<T,S> temp = new Map<T,S>();
    temp.transfer(m);
    m.transfer(this);
    this.transfer(temp);
}


