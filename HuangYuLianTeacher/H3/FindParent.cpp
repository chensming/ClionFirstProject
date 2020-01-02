//
// Created by Dell on 2019/12/28.
//
#include <iostream>
#include <stack>
#include <cassert>

using namespace std;

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

    void destroyTree(BinTreeNode<T> *ptr);

    void Orders(int d);

    void Orders(int d, void (*visit)(BinTreeNode<T> *p));

    void PostOrderNonRecs(void (*visit)(BinTreeNode<T> *p));

    void FindParentRecs(T x);

    void FindParentNonRecs(T x);

private:
    BinTreeNode<T> *root;
    T RefValue;

    void FindParentRecs(BinTreeNode<T> *ptr, T x, bool &flag);
};

template<class T>
BinaryTree<T>::BinaryTree(T *a, int arraySize, T endValue) {
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
BinaryTree<T>::~BinaryTree() {
    destroyTree(root);
}

template<class T>
void BinaryTree<T>::destroyTree(BinTreeNode<T> *ptr) {
    if (ptr != nullptr) {
        destroyTree(ptr->child[0]);
        destroyTree(ptr->child[1]);
        delete ptr;
    }
}


//d == 0：前序，1：中序，2：后序
template<class T>
void BinaryTree<T>::Orders(int d) {
    stack<BinTreeNode<T> *> st;
    stack<int> stFlag; //放标志
    BinTreeNode<T> *t = root;
    int flag = 0;
    while (t != nullptr || !st.empty()) {
        while (t != nullptr) {
            ///////////前序遍历////////////
            if (d == 0)
                cout << t->data << " ";
            //////////////////////////////
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
                ///////////后序遍历////////////////
                if (d == 2)
                    cout << t->data << " ";
                /////////////////////////////////
                t = nullptr;
            } else {
                ///////////中序遍历//////////////
                if (d == 1)
                    cout << t->data << " ";
                ///////////////////////////////
                st.push(t);
                stFlag.push(1);
                t = t->child[1];
            } //else
        } //if
    } //while
} //Orders



template<class T>
void BinaryTree<T>::Orders(int d, void (*visit)(BinTreeNode<T> *p)) {
    stack<BinTreeNode<T> *> st;
    stack<int> stFlag; //放标志
    BinTreeNode<T> *t = root;
    int flag = 0;
    while (t != nullptr || !st.empty()) {
        while (t != nullptr) {
            ///////////前序遍历////////////
            if (d == 0)
                visit(t);
            //////////////////////////////
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
                ///////////后序遍历////////////////
                if (d == 2)
                    visit(t);
                /////////////////////////////////
                t = nullptr; //没有这个则后序排序不会停止
            } else {
                ///////////中序遍历//////////////
                if (d == 1)
                    visit(t);
                ///////////////////////////////
                st.push(t);
                stFlag.push(1);
                t = t->child[1];
            } //else
        } //if
    } //while
}

template<class T>
struct stNode {
    BinTreeNode<T> *ptr;
    int tag;
};


template<class T>
void BinaryTree<T>::PostOrderNonRecs(void (*visit)(BinTreeNode<T> *)) {
    stack<stNode<T>> st;
    stNode<T> w;
    BinTreeNode<T> *p = root;
    do {
        while (p != nullptr) {
            w.ptr = p;
            w.tag = 0;
            st.push(w);
            p = p->child[0];
        }
        bool continueFlag = true;
        while (continueFlag && !st.empty()) {
            w = st.top();
            st.pop();
            p = w.ptr;
            switch (w.tag) {
                case 0:
                    w.tag = 1;
                    st.push(w);
                    //停止这个while循环,让它去找最左的左子树0
                    continueFlag = false;
                    p = p->child[1];
                    break;
                case 1:
                    visit(p);
                    break;
            }
        }
    } while (!st.empty());
}

template<class T>
void BinaryTree<T>::FindParentRecs(T x) {
    if (root->data == x) {
        cout << x << " is the root value " << endl;
        return;
    }
    bool flag = false;
    FindParentRecs(root, x, flag);
    if (!flag)
        cout << x << " is not found!" << endl;
}

//逆序输出
template<class T>
void BinaryTree<T>::FindParentRecs(BinTreeNode<T> *ptr, T x, bool &flag) {
    if (ptr != nullptr) {
        ////////////////前序遍历修改部分/////////////////////
        if (ptr->data == x) {
            flag = true;
            return;
        }
        /////////////////////////////////////////
        FindParentRecs(ptr->child[0], x, flag);
        if (!flag)
            FindParentRecs(ptr->child[1], x, flag);
        if (flag) {
            //不能和上面的化简,如果要找的值在右子树,化简了会少输出了根节点
            cout << ptr->data << " ";
        }
    }
}

template<class T>
void BinaryTree<T>::FindParentNonRecs(T x) {
    //如果是根节点的话.直接告诉用户是根结点
    if(root->data == x) {
        cout << x << " is the root value" << endl;
        return ;
    }



    stack<BinTreeNode<T> *> st;
    BinTreeNode<T> *p = root;
    do {
        while (p != nullptr) {
            ///////////前序非递归遍历修改部分//////////////////
            if (p->data == x) {
                //此时输出栈里面的内容就好了
                while (!st.empty()){
                    p = st.top();
                    st.pop();
                    cout << p->data << " ";
                }
                return;
            }
            ////////////////////////////////////////////////
            st.push(p);
            p = p->child[0];
        }
        if (!st.empty()) {
            p = st.top();
            st.pop();
            p = p->child[1];
        }
    } while (p != nullptr || !st.empty());
    cout << x << " is not found!" << endl;
}


template<class T>
void printData(BinTreeNode<T> *p) {
    cout << p->data << " ";
}


int main() {
    char test[11] = {'a', 'b', 'd', '#', '#', '#', 'c', 'e', '#', '#', '#'};
    BinaryTree<char> b1(test, 11, '#');

    b1.FindParentNonRecs('e');


    cout << endl;
}
