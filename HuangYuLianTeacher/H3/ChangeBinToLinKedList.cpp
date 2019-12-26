//
// Created by Dell on 2019/12/26.
//
#include <iostream>

using namespace std;

template<class T>
struct BinTreeNode {
    T data;
    BinTreeNode<T> *child[2];

    BinTreeNode(T x) : data(x) {
        child[0] = nullptr;
        child[1] = nullptr;
    }
};


template<class T>
class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(T a[], int size);

    ~BinaryTree();

    void createTree();

    void makeEmpty(BinTreeNode<T> *subTree);

private:
    BinTreeNode<T> *root;
};

template<class T>
BinaryTree<T>::BinaryTree(T *a, int size) {

}

template<class T>
BinaryTree<T>::~BinaryTree() {
    makeEmpty(root);
}

template<class T>
void BinaryTree<T>::createTree() {

}

template<class T>
void BinaryTree<T>::makeEmpty(BinTreeNode<T> *subTree) {

}
