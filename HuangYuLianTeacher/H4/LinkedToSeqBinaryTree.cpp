//
// Created by Dell on 2020/1/2.
//

#include <iostream>
#include <cassert>
#include <stack>

using namespace std;

enum orderType {
    preOrder, inOrder, postOrder
};


template<class T>
struct BinTreeNode {
    T data;
    BinTreeNode<T> *child[2];

    explicit BinTreeNode(T x) : data(x) {
        child[0] = nullptr;
        child[1] = nullptr;
    }
};


template<class T>
class BinaryTree {
public:

    BinaryTree() : root(nullptr) {}

    BinaryTree(T *a, int arraySize, T endValue);

    ~BinaryTree();

    void create(T *a, int arraySize, T endValue);

    void destroy(BinTreeNode<T> *t);

    void ThreeOrder(orderType order);

    void ChangeToSeq(T *&a, int &size);

    int SizeNonRecursionByPreOrder();

private:
    BinTreeNode<T> *root;
    T RefValue;
};

template<class T>
BinaryTree<T>::BinaryTree(T *a, int arraySize, T endValue) {
    root = nullptr;
    create(a, arraySize, endValue);
}

template<class T>
BinaryTree<T>::~BinaryTree() {
    destroy(root);
}

template<class T>
void BinaryTree<T>::destroy(BinTreeNode<T> *t) {
    if (t != nullptr) {
        destroy(t->child[0]);
        destroy(t->child[1]);
        delete t;
    }
}

template<class T>
void BinaryTree<T>::create(T *a, int arraySize, T endValue) {
    stack<BinTreeNode<T> *> st;
    BinTreeNode<T> *p = nullptr, *q = nullptr;
    root = new BinTreeNode<T>(a[0]);
    assert(root != nullptr);
    RefValue = endValue;
    st.push(root);
    int d = 0; //d == 0时候往左边
    for (int i = 1; i < arraySize; i++) {
        if (a[i] != RefValue) {
            p = new BinTreeNode<T>(a[i]);
            // 将其父节点取出来，把父节点连上它然后在把他们入栈
            q = st.top();
            st.pop();
            q->child[d] = p;
            st.push(q);
            st.push(p);
            d = 0;
            //往左边走，下一次for循环可能生成的是新结点的左孩子
        } else {
            if (d == 1) {
                //回去后只需考虑右子树情况
                //如果此时d还为1证明该结点没用了
                st.pop();
            } else  //往右边
                d = 1;
        }
    }
}

template<class T>
void BinaryTree<T>::ThreeOrder(orderType order) {
    stack<BinTreeNode<T> *> st;
    stack<int> stFlag; //放标志
    BinTreeNode<T> *t = root;
    int flag = 0;
    while (t != nullptr || !st.empty()) {
        while (t != nullptr) {
            if (order == preOrder)
                cout << t->data << " ";
            st.push(t);
            stFlag.push(0);
            t = t->child[0];
        }
        if (!st.empty()) {
            t = st.top();
            st.pop();
            flag = stFlag.top();
            stFlag.pop();
            if (flag == 1) {//该结点是第二次进栈出来的
                if (order == postOrder)
                    cout << t->data << " ";
                t = nullptr;
            } else {
                if (order == inOrder)
                    cout << t->data << " ";
                st.push(t);
                stFlag.push(1);
                t = t->child[1];
            } //else
        } //if
    } //while
}

//a为传入的指针，size为返回的数组的大小
template<class T>
void BinaryTree<T>::ChangeToSeq(T *&a, int &size) {
    size = SizeNonRecursionByPreOrder();
    a = new T[size];
    for (int i = 0; i < size; i++)
        a[i] = RefValue;
    stack<BinTreeNode<T> *> st;
    stack<int> stSeq;
    BinTreeNode<T> *p = root;
    int v = 0;
    while (p != nullptr || !st.empty()) {
        while (p != nullptr) {
            st.push(p);
            stSeq.push(v);
            a[v] = p->data;
            p = p->child[0];
            v = 2 * v + 1;
        }
        if (!st.empty()) {
            p = st.top();
            st.pop();
            v = stSeq.top();
            stSeq.pop();
            p = p->child[1];
            v = v * 2 + 2;
        }
    }
    for (int i = 0; i < size; i++)
        cout << a[i] << endl;
}

template<class T>
int BinaryTree<T>::SizeNonRecursionByPreOrder() {
    if (root == nullptr)
        return 0;
    stack<BinTreeNode<T> *> S;
    BinTreeNode<T> *p = root;
    int size = 0;  //结点计数器
    do {
        while (p != nullptr) {
            S.push(p);
            size++;
            p = p->child[0];
        }
        if (!S.empty()) {
            p = S.top();
            S.pop();
            p = p->child[1];
        }
    } while (p != nullptr || !S.empty());
    return size;
}


int main() {
    char test[23] = {'a' ,'b', 'd', 'h', '#', '#', 'i', '#', '#',
                   'e', 'j', '#', '#', 'k', '#', '#', 'c', 'f',
                   '#', '#', 'g', '#', '#'};
    BinaryTree<char> b1(test, 23, '#');

    b1.ThreeOrder(preOrder);

    char *a = nullptr;
    int aSize = 0;
    b1.ChangeToSeq(a, aSize);
//    for (int i = 0; i < aSize; i++)
//        cout << a[i] << endl;
}