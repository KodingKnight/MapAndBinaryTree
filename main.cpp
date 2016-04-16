#include <iostream>
#include "binTree.h"

using namespace std;

int main(){

    BinTree<int> myBinTree;
    /*
    myBinTree.insert(pair<int,int>(3,3));
    myBinTree.insert(pair<int,int>(2,2));
    myBinTree.insert(pair<int,int>(1,1));
    myBinTree.insert(pair<int,int>(5,5));
    */

    myBinTree.insert(3);
    myBinTree.insert(2);
    myBinTree.insert(1);
    myBinTree.insert(5);


    BinTreeIterator<int> iter = myBinTree.begin();
    iter.parent();

    BinTreeIterator<int> iter_count = myBinTree.head();
    for(int i = 0; i < 3; i++){
        cout << *(iter_count) << '\n';
        --iter_count;
    }

    myBinTree.erase(iter);
    myBinTree.insert(2);

    cout << '\n';
    iter_count = myBinTree.head();
    for(int i = 0; i < 2; i++){
        cout << *(iter_count) << '\n';
        --iter_count;
    }

    iter = myBinTree.begin();
    cout << '\t' << *(++iter) << '\n' << '\n';

    iter = myBinTree.begin();
    iter = iter.successor();
    cout << *iter << endl << endl;


    /*
    cout << endl << endl; //<< *myBinTree.begin() << endl;
    myBinTree.clear();
    cout << endl << endl << endl; //<< *myBinTree.begin();
    */




    BinTree<int> newBinTree;// = BinTree<int,int>(myBinTree);
    newBinTree = myBinTree;

    cout << endl << endl;

    iter_count = newBinTree.head();
    for(int i = 0; i < 2; i++){
        cout << *(iter_count) << '\n';
        --iter_count;
    }
    cout << '\t' << *((iter.parent()).right()) << '\n' << '\n';

    //cout << *(myBinTree.begin()) << '\n';
    //cout << *(myBinTree.head()) << '\n';
    //cout << *(myBinTree.end()) << '\n';
    //myBinTree.erase(myBinTree.begin());

    cout << endl << endl;
    /// then my delete prints spew out more lines

    return 0;
}

