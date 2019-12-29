//
// Created by Dell on 2019/12/28.
//
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

template<class T>
class SeqFullBinaryTree {
public:
    SeqFullBinaryTree() : currentSize(0), elements(nullptr) {
        nullValue = T();
    }

    SeqFullBinaryTree(T *a, int size, T nullValue);


    ~SeqFullBinaryTree() {
        delete[]elements;
    }

    void createTree(T *a, int size, T nullValue);

private:
    int currentSize;
    T *elements;
    T RefValue;//判断为空的值
};

template<class T>
SeqFullBinaryTree<T>::SeqFullBinaryTree(T *a, int size, T nullValue) {
    createTree(a, size, nullValue);
}

template<class T>
void SeqFullBinaryTree<T>::createTree(T *a, int size, T nullValue) {
    RefValue = nullValue;
    currentSize = size;
}




