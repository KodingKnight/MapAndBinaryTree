#include <iostream>
#include "map.h"

using namespace std;

// I worked with myself

// This acts as a testbench

int main(){

    Map<int,int> myMap;

    cout << myMap.empty() << endl;

    myMap.insert(pair<int,int>(3,6));
    myMap.insert(pair<int,int>(2,4));
    myMap.insert(pair<int,int>(1,2));
    myMap.insert(pair<int,int>(5,10));
    myMap.insert(pair<int,int>(6,12));
    myMap.insert(pair<int,int>(7,14));
    myMap[99] = 5;
    myMap[100];
    myMap[99] = 198;


    Map<int,int> newMap = myMap;

/*
    // Testing for copy constructor
    // comment out things below this in order to use this

    Map<int,int>* newMap = new Map<int,int>(myMap);
    // newMap.transfer(myMap);


    MapIterator<int,int> iter = myMap.begin();
    myMap.erase(iter);
    MapIterator<int,int> iter2 = newMap->begin();
    newMap->erase(iter2);
    newMap->erase(newMap->begin());
    cout << myMap.begin()->second;
    cout << newMap->begin()->second;
*/


    cout << myMap.size() << endl;
    cout << myMap.empty() << endl;

    MapIterator<int,int> iter = myMap.begin();
    cout << (*iter).first << ' ' << iter->first << ' ' << iter->second << endl;

    cout << endl;
    for (int i = 0; i < myMap.size(); ++i){
        cout << iter->first << ' ' << iter->second << endl;
        ++iter;
    }
    cout << endl;

    MapIterator<int,int> iterNew = (newMap.begin());
    for (int i = 0; i < newMap.size(); ++i){
       cout << iterNew->first << ' ' << iterNew->second << endl;
        ++iterNew;
    }
    cout << endl;

    iter = myMap.end();
    cout << iter->first << ' ' << iter->second << endl;

    cout << myMap.count(2) << endl;
    cout << myMap.count(5) << endl;

    cout << myMap.find(1)->first << ' ' << myMap.find(1)->second << endl;
    cout << myMap.find(5)->first << ' ' << myMap.find(5)->second << endl;
    // cout << myMap.find(8)->first << ' ' << myMap.find(8)->second << endl;
    // The line above should segfault because there is nothing there to dereference

    cout << myMap.erase(2) << endl;
    cout << myMap.erase(2) << endl;
    // cout << myMap.find(2)->first << ' ' << myMap.find(2)->second << endl;
    // The line above should segfault because there is nothing there to dereference
    cout << myMap.find(1)->first << ' ' << myMap.find(1)->second << endl;
    cout << "myMap[3] = " << myMap[3] << endl;

    cout << myMap.erase(myMap.begin()) << endl;
    // cout << myMap.find(2)->first << ' ' << myMap.find(2)->second << endl;
    // cout << myMap.find(1)->first << ' ' << myMap.find(1)->second << endl;
    // The lines above should segfault because there is nothing there to dereference
    cout << "myMap[3] = " << myMap[3] << endl << endl;

    iter = myMap.end();
    for (int i = 0; i < myMap.size(); ++i){
        cout << iter->first << ' ' << iter->second << endl;
        --iter;
    }
    cout << endl;

    iterNew = newMap.end();
    for (int i = 0; i < newMap.size(); ++i){
       cout << iterNew->first << ' ' << iterNew->second << endl;
        --iterNew;
    }
    cout << endl;

    myMap.swap(newMap);
    cout << "myMap[2] = " << myMap[2] << endl << endl;
    //cout << "newMap[2] = " << newMap[2] << endl;
    // The line above should segfault because there is nothing there to dereference

    iter = myMap.end();
    for (int i = 0; i < myMap.size(); ++i){
        cout << iter->first << ' ' << iter->second << endl;
        --iter;
    }
    cout << endl;

    iterNew = newMap.end();
    for (int i = 0; i < newMap.size(); ++i){
       cout << iterNew->first << ' ' << iterNew->second << endl;
        --iterNew;
    }
    cout << endl;

    iter = myMap.begin();
    iterNew = newMap.begin();
    cout << (iter != iterNew) << ' ';
    iterNew = myMap.begin();
    cout << (iter != iterNew) << ' ';
    ++iterNew;
    cout << (iter != iterNew) << endl;

    myMap.clear();
    cout << myMap.size() << endl;
    cout << myMap.empty() << endl;


/*
    //Testing for BinTree

    BinTree<int> myBinTree;

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
*/
    /*
    cout << endl << endl; //<< *myBinTree.begin() << endl;
    myBinTree.clear();
    cout << endl << endl << endl; //<< *myBinTree.begin();
    */
/*
    iter = myBinTree.begin();
    cout << '\t' << *(++iter) << '\n' << '\n';

    BinTree<int> newBinTree; //= BinTree<int>(myBinTree);
    newBinTree = myBinTree;


    cout << endl << endl;

    iter_count = newBinTree.head();
    for(int i = 0; i < 2; i++){
        cout << *(iter_count) << '\n';
        --iter_count;
    }
    iter = newBinTree.begin();
    cout << '\t' << *(++iter) << '\n' << '\n';

    //cout << *(myBinTree.begin()) << '\n';
    //cout << *(myBinTree.head()) << '\n';
    //cout << *(myBinTree.end()) << '\n';
    //myBinTree.erase(myBinTree.begin());
*/
    return 0;
}

