template <typename T>
class BinTree;

template <typename T>
class BinTreeIterator;

template <typename T>
class BinTreeNode;

///using std::pair;


/// For debugging purposes (remove later)
#include <iostream>
using std::cout;

template <typename T>
class BinTreeNode{
    friend class BinTree<T>;
    friend class BinTreeIterator<T>;

private:
    BinTreeNode() : element(), right(nullptr), left(nullptr), parent(nullptr){}
    BinTreeNode(const T & e, BinTreeNode * right0, BinTreeNode * left0, BinTreeNode * parent0);
    ~BinTreeNode(){ delete &element; }

    T element;

    BinTreeNode<T> * left;
    BinTreeNode<T> * right;
    BinTreeNode<T> * parent;

    BinTreeNode<T>& operator=(const BinTreeNode<T> & node);
    BinTreeNode<T>& operator==(const BinTreeNode<T> & node) const;
    BinTreeNode<T>& operator!=(const BinTreeNode<T> & node) const;
};



template <typename T>
BinTreeNode<T>::BinTreeNode(const T & e, BinTreeNode * right0, BinTreeNode * left0, BinTreeNode * parent0) :
    element(e), left(left0), right(right0), parent(parent0){}

template <typename T>
BinTreeNode<T>& BinTreeNode<T>::operator=(const BinTreeNode<T> & node){
    element = node.element;
    left = node.left;
    right = node.right;
    parent = node.parent;
}

/// How should this work?
/*
bool operator==(const BinTreeNode<T> & node) const{
    return (element == node.element && element == node.element);
}

bool operator!=(const BinTreeNode<T> & node) const{
    return (element != node.element || element != node.element);
}
*/




template <typename T>
class BinTreeIterator{
    friend class BinTree<T>;

public:
    BinTreeIterator() : pNode(NULL){}
    T & operator*() const{return pNode->element; }
    T * operator->() const{return &(pNode->element);}
    bool operator==(const BinTreeIterator<T> & iter) const{return pNode == iter.pNode;}
    bool operator!=(const BinTreeIterator<T> & iter) const{return pNode != iter.pNode;}
    BinTreeIterator<T> & operator++(); // prefix
    BinTreeIterator<T> & operator--();
    BinTreeIterator<T> operator++(int); // postfix
    BinTreeIterator<T> operator--(int);
    BinTreeIterator<T> & parent();
    BinTreeIterator<T> & left();
    BinTreeIterator<T> & right();
    BinTreeIterator<T> & successor();
    BinTreeIterator<T> & predecessor();\

private:
    //iterator min(const iterator iter) const;
    //iterator max(const iterator iter) const;
    BinTreeNode<T>* min(BinTreeNode<T>* node) const;
    BinTreeNode<T>* max(BinTreeNode<T>* node) const;

private:
    explicit BinTreeIterator(BinTreeNode<T> * p) : pNode(p){}
    BinTreeNode<T> * pNode;
};

template <typename T>
inline BinTreeIterator<T> & BinTreeIterator<T>::operator++(){ //prefix
    pNode = pNode->right;
    return *this;
}

template <typename T>
inline BinTreeIterator<T> & BinTreeIterator<T>::operator--(){
    pNode = pNode->left;
    return *this;
}

template <typename T>
inline BinTreeIterator<T> BinTreeIterator<T>::operator++(int){ //postfix
    BinTreeIterator<T> temp = *this;
    pNode = pNode-> right;
    return temp;
}

template <typename T>
inline BinTreeIterator<T> BinTreeIterator<T>::operator--(int){
    BinTreeIterator<T> temp = *this;
    pNode = pNode -> left;
    return temp;
}


template <typename T>
inline BinTreeIterator<T> & BinTreeIterator<T>::parent(){
    pNode = pNode->parent;
    return *this;
}

template <typename T>
inline BinTreeIterator<T> & BinTreeIterator<T>::left(){
    pNode = pNode->left;
    return *this;
}

template <typename T>
inline BinTreeIterator<T> & BinTreeIterator<T>::right(){
    pNode = pNode->right;
    return *this;
}

template <typename T>
inline BinTreeNode<T>* BinTreeIterator<T>::min(BinTreeNode<T>* node) const{
    BinTreeNode<T>* tempNode = node;
    while(tempNode->left != nullptr){
        tempNode = tempNode->left;
    }
    return tempNode;
}

template <typename T>
inline BinTreeNode<T>* BinTreeIterator<T>::max(BinTreeNode<T>* node) const{
    BinTreeNode<T>* tempNode = node;
    while(tempNode->right != nullptr){
        tempNode = tempNode->right;
    }
    return tempNode;
}

template <typename T>
inline BinTreeIterator<T>& BinTreeIterator<T>::successor(){
    if(pNode->right != nullptr){
        pNode = min(pNode->right);
    }else{
        BinTreeNode<T>* newNode = pNode->parent;
        while(newNode != nullptr && newNode->right == pNode){
            pNode = newNode;
            newNode = pNode->parent;
        }
        pNode = newNode;
    }
    return *this;
}

template <typename T>
inline BinTreeIterator<T> & BinTreeIterator<T>::predecessor(){
    if(pNode->left != nullptr){
        pNode = max(pNode->left);
    }else{
        BinTreeNode<T>* newNode = pNode->parent;
        while(newNode != nullptr && newNode->left == pNode){
            pNode = newNode;
            newNode = pNode->parent;
        }
        pNode = newNode;
    }
    return *this;
}









template <typename T>
class BinTree{
public:
    typedef BinTreeIterator<T> iterator;

    BinTree() : BinTreeSize(0), pHeadNode(NULL) {}
    //BinTree(const BinTree & tree) { transfer(tree); }
    ~BinTree();
    void transfer(BinTree<T> tree);
    BinTree<T>& operator=(const BinTree<T> & m);
    T& operator[](const iterator & iter)const;

    int size() const;
    bool empty() const;
    iterator head() const;
    iterator begin() const;
    iterator end() const;
    iterator min(const iterator iter) const;
    iterator max(const iterator iter) const;
    int count(const T & element) const;
    iterator find(const T & element) const;
    bool insert(const T & element);
    bool erase(const T & key);
    bool erase(const iterator & iter);
    void clear();
    void swap(BinTree<T> & m);

private:
    int BinTreeSize;
    BinTreeNode<T> * pHeadNode;
    BinTreeNode<T>* min(BinTreeNode<T>* node) const;
    BinTreeNode<T>* max(BinTreeNode<T>* node) const;
    void transplant(BinTreeNode<T>* u, BinTreeNode<T>* v);
    void notInorder(BinTreeNode<T>* node, void (*func) (BinTreeNode<T>* node));
    void deleatSubTree(BinTreeNode<T>* node);
    void copySubTree(BinTreeNode<T>* node);
};

template <typename T>
inline BinTree<T>::~BinTree(){
    clear();
}

template <typename T>
inline void BinTree<T>::transfer(BinTree<T> tree){
    copySubTree(tree.pHeadNode);
    BinTreeSize = tree.size();
    /// why does this call clear?

    /// when I uncomment my copy contructor, it gets called instead.
}

template <typename T>
inline BinTree<T>& BinTree<T>::operator=(const BinTree<T> & tree){
    transfer(tree);
    return *this;
}

template <typename T>
inline T& BinTree<T>::operator[](const BinTree<T>::iterator & iter) const{
    return *iter;
}

template <typename T>
inline int BinTree<T>::size() const{
    return BinTreeSize;
}

template <typename T>
inline bool BinTree<T>::empty() const{
    return BinTreeSize == 0;
}

template <typename T>
inline typename BinTree<T>::iterator BinTree<T>::head() const{
    return iterator(pHeadNode);
}

template <typename T>
inline typename BinTree<T>::iterator BinTree<T>::begin() const{
    return BinTreeIterator<T>(min(pHeadNode));
}

template <typename T>
inline typename BinTree<T>::iterator BinTree<T>::end() const{
    return BinTreeIterator<T>(max(pHeadNode));
}

template <typename T>
inline BinTreeNode<T>* BinTree<T>::min(BinTreeNode<T>* node) const{
    BinTreeNode<T>* tempNode = node;
    while(tempNode->left != nullptr){
        tempNode = tempNode->left;
    }
    return tempNode;
}

template <typename T>
inline BinTreeNode<T>* BinTree<T>::max(BinTreeNode<T>* node) const{
    BinTreeNode<T>* tempNode = node;
    while(tempNode->right != nullptr){
        tempNode = tempNode->right;
    }
    return tempNode;
}

template <typename T>
inline typename BinTree<T>::iterator BinTree<T>::min(const BinTree<T>::iterator iter) const{
    BinTreeNode<T>* node = iter.pNode;
    while(node->left != nullptr){
        node = node->left;
    }
    return BinTreeIterator<T>(node);
}

template <typename T>
inline typename BinTree<T>::iterator BinTree<T>::max(const BinTree<T>::iterator iter) const{
    BinTreeNode<T>* node = iter.pNode;
    while(node->right != nullptr){
        node = node->right;
    }
    return BinTreeIterator<T>(node);
}

template <typename T>
inline int BinTree<T>::count(const T & element) const{
    BinTreeIterator<T> iter = find(element);
    return iter != NULL;
}

template <typename T>
inline typename BinTree<T>::iterator BinTree<T>::find(const T & element) const{
    BinTreeIterator<T> iter = head();
    while(iter.pNode != nullptr && *iter != element){
        if(element < *iter){
            iter.left();
        }else{
            iter.right();
        }
    }
    return iter;
}

template <typename T>
inline bool BinTree<T>::insert(const T & element){
    if(pHeadNode == NULL){
        pHeadNode = new BinTreeNode<T>(element, nullptr, nullptr, nullptr);
    }else{
        BinTreeNode<T>* y;
        BinTreeNode<T>* x = pHeadNode;
        while(x != nullptr){
            y = x;
            if(element == x->element){
                return false;
            }else if(element < x->element){
                x = x->left;
            }else{
                x = x->right;
            }
        }
        if(element < y->element){
            y->left = new BinTreeNode<T>(element, nullptr, nullptr, y);
        }else{
            y->right = new BinTreeNode<T>(element, nullptr, nullptr, y);
        }
    }
    ++BinTreeSize;
    return true;
}

template <typename T>
inline bool BinTree<T>::erase(const T & key){
    BinTreeIterator<T> iter = find(key);
    return erase(iter);
}

template <typename T>
inline bool BinTree<T>::erase(const BinTree<T>::iterator & iter){
    BinTreeNode<T>* z = iter.pNode;
    if(z->left == nullptr){
        transplant(z, z->right);
    }else if(z->right == nullptr){
        transplant(z, z->left);
    }else{
        BinTreeNode<T>* y = min(z->right);
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
    --BinTreeSize;
    return true;
}

template <typename T>
void BinTree<T>::transplant(BinTreeNode<T>* u, BinTreeNode<T>* v){
    if(pHeadNode == u){
        pHeadNode = v;
        v->parent = nullptr;
    }else{
        BinTreeNode<T>* temp = u->parent;
        if(temp->left == u){
            temp->left = v;
        }else{
            temp->right = v;
        }
        v->parent = temp;
    }
}

template <typename T>
inline void BinTree<T>::clear(){
    deleatSubTree(pHeadNode);
    pHeadNode = nullptr;
    BinTreeSize = 0;
}

template <typename T>
inline void BinTree<T>::swap(BinTree<T> & m){
    BinTree<T> temp = new BinTree<T>();
    temp.transfer(m);
    m.transfer(this);
    this.transfer(temp);
}

template <typename T>
void BinTree<T>::notInorder(BinTreeNode<T>* node, void (*func) (BinTreeNode<T>* node)){
    if(node != nullptr){
        notInorder(node->left, func);
        notInorder(node->right, func);
        func(node);
    }
}

template <typename T>
void BinTree<T>::deleatSubTree(BinTreeNode<T>* node){
    if(node != nullptr){
        deleatSubTree(node->left);
        deleatSubTree(node->right);
        //delete node;
        cout << node->element << '\n';
    }
}

template <typename T>
void BinTree<T>::copySubTree(BinTreeNode<T>* node){
    if(node != nullptr){
        insert(node->element);
        copySubTree(node->left);
        copySubTree(node->right);
    }
}


