//
// Created by Dell on 2019/12/26.
//
#include <iostream>
#include <cassert>
#include <stack>

using namespace std;

template<class T>
struct linkNode {
    T data;
    linkNode<T> *link;

    explicit linkNode(T x) : data(x), link(nullptr) {}
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
    explicit BinaryTree(T endValue) : root(nullptr), RefValue(endValue) {}

    BinaryTree(T a[], int size, T endValue);

    ~BinaryTree();

    void CreateTree();

    void makeEmpty(BinTreeNode<T> *subTree);

    void InOrderNonRecursion();

    void PreOrderRecs();

    linkNode<T> *SpanLeavesLinkedList();

private:
    BinTreeNode<T> *root;
    T RefValue;

    void PreOrderRecs(BinTreeNode<T> *subTree);

    void CreateTree(BinTreeNode<T> *parent, int d);
};

//非递归建树
template<class T>
BinaryTree<T>::BinaryTree(T *a, int size, T endValue) {
    stack<BinTreeNode<T> *> st;
    BinTreeNode<T> *p = nullptr, *q = nullptr;
    root = new BinTreeNode<T>(a[0]);
    assert(root != nullptr);
    RefValue = endValue;
    st.push(root);
    int d = 0; //0向左
    for (int i = 1; i < size; i++) {
        if (a[i] != RefValue) {
            p = new BinTreeNode<T>(a[i]);
            q = st.top();
            st.pop();
            q->child[d] = p;
            st.push(q);
            st.push(p);
            d = 0;
        } else {
            if (d == 1) {
                //回去后只需考虑右子树情况
                //如果此时d还为1证明该结点没用了
                st.pop();
            } else
                d = 1;
        }
    }
}

template<class T>
BinaryTree<T>::~BinaryTree() {
    makeEmpty(root);
}

template<class T>
void BinaryTree<T>::CreateTree() {
    cout << "input the element of nodes,end a branch use";
    cout << RefValue << " as a symbol" << endl;
    T x;
    cin >> x;
    if (x != RefValue) {
        root = new BinTreeNode<T>(x);
    }
    CreateTree(root, 0);
    CreateTree(root, 1);
}

template<class T>
void BinaryTree<T>::makeEmpty(BinTreeNode<T> *subTree) {
    if (subTree != nullptr) {
        makeEmpty(subTree->child[0]);
        makeEmpty(subTree->child[1]);
        delete subTree;
    }
}

template<class T>
void BinaryTree<T>::InOrderNonRecursion() {
    stack<BinTreeNode<T> *> st;
    BinTreeNode<T> *p = root;
    do {
        while (p != nullptr) {
            st.push(p);
            p = p->child[0];
        }
        if (!st.empty()) {
            p = st.top();
            st.pop();
            cout << p->data << " ";
            p = p->child[1];
        }
    } while (p != nullptr || !st.empty());
}

template<class T>
void BinaryTree<T>::PreOrderRecs() {
    PreOrderRecs(root);
}

template<class T>
void BinaryTree<T>::PreOrderRecs(BinTreeNode<T> *subTree) {
    if (subTree != nullptr) {
        cout << subTree->data << " ";
        PreOrderRecs(subTree->child[0]);
        PreOrderRecs(subTree->child[1]);
    }
}

template<class T>
void BinaryTree<T>::CreateTree(BinTreeNode<T> *parent, int d) {
    T x;
    cin >> x;
    if (x != RefValue) {
        auto *p = new BinTreeNode<T>(x);
        parent->child[d] = p;
        CreateTree(p, 0);//左孩子
        CreateTree(p, 1);//右边孩子
    }
}

template<class T>
linkNode<T> *BinaryTree<T>::SpanLeavesLinkedList() {
    if (root == nullptr)
        return nullptr;
    stack<BinTreeNode<T> *> st;
    BinTreeNode<T> *p = root;
    linkNode<T> *head = nullptr, *q = nullptr, *newNode;
    //该链表浪费一个表头空间让算法变得统一
    head = new linkNode<T>(RefValue);
    q = head;
    do {
        while (p != nullptr) {
            st.push(p);
            //////////////////////////////////////
            if (p->child[0] == nullptr && p->child[1] == nullptr) {
                newNode = new linkNode<T>(p->data);
                q->link = newNode;
                q = q->link;
            }
            //////////////////////////////////////
            p = p->child[0];
        }
        if (!st.empty()) {
            p = st.top();
            st.pop();
            p = p->child[1];
        }
    } while (p != nullptr || !st.empty());
    return head;
}


template<class T>
void display(linkNode<T>* head) {
    if(head == nullptr){
        cout << "the linkedList is null " << endl;
        return;
    }
    linkNode<T>* p = head->link;
    while(p != nullptr){
        cout << p->data << " ";
        p = p->link;
    }
}


int main() {
    char test[11] = {'a', 'b', 'd', '#', '#', '#', 'c', 'e', '#', '#', '#'};
    BinaryTree<char> b1(test, 11, '#');
//    BinaryTree<char> b1('#');
//    b1.CreateTree();

    cout << "PreOrder " << endl;
    b1.PreOrderRecs();
    cout << endl;
    cout << "InOrder: " << endl;
    b1.InOrderNonRecursion();
    cout << endl;
    auto *link1 = b1.SpanLeavesLinkedList();
    display(link1);
}