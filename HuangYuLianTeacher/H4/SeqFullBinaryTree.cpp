//
// Created by Dell on 2019/12/28.
//
#include <iostream>
#include <stack>
#include <queue>
#include <cassert>


using namespace std;

enum orderType {
    preOrder, inOrder, postOrder
};


template<class T>
class SeqFullBinaryTree {
public:
    SeqFullBinaryTree() : currentSize(0), elements(nullptr) {}

    SeqFullBinaryTree(T *a, int size);


    ~SeqFullBinaryTree() {
        delete[]elements;
    }

    void createTree(T *a, int size);


    void PreOrderRecs(void (*visit)(T x));

    void InOrderRecs(void (*visit)(T x));

    void PostOrderRecs(void (*visit)(T x));

    void PreOrderNonRecs(void (*visit)(T x));

    void InOrderNonRecs(void (*visit)(T x));

    void PostOrderNonRecs(void (*visit)(T x));

    void ThreeOrder(orderType order, void (*visit)(T x));

    //层次遍历
    void LevelOrder(void (*visit)(T x));

    //求树高
    int Height() const;

    int Height(int i) const;

    int HeightNoRecursion();

    //求节点个数
    int Size(void (*count)()) const;

    int SizeNonRecursionByLevelOrder();     //非递归方法,层次遍历顺序
    int SizeNonRecursionByPreOrder();       //非递归方法,前序遍历顺序

    //求叶子结点总数
    int LeavesSize() const;   //从根开始
    int LeavesSizeNonRecursionByLevelOrder();

    int LeavesSizeNonRecursionByPreOrder();

    //广义表输出二叉树
    void PrintBinTree();

    void PrintBinTree(int i);

private:
    int currentSize;
    T *elements;

    void PreOrderRecs(int i, void (*visit)(T x));

    void InOrderRecs(int i, void (*visit)(T x));

    void PostOrderRecs(int i, void (*visit)(T x));

};

template<class T>
SeqFullBinaryTree<T>::SeqFullBinaryTree(T *a, int size) {
    currentSize = size;
    elements = nullptr;
    createTree(a, size);
}

template<class T>
void SeqFullBinaryTree<T>::createTree(T *a, int size) {
    currentSize = size;
    delete[] elements;
    elements = new T[currentSize];
    assert(elements != nullptr);
    for (int i = 0; i < currentSize; i++)
        elements[i] = a[i];
}

template<class T>
void SeqFullBinaryTree<T>::PreOrderRecs(void (*visit)(T x)) {
    if (currentSize == 0)
        return;
    PreOrderRecs(0, visit);
}


template<class T>
void SeqFullBinaryTree<T>::InOrderRecs(void (*visit)(T)) {
    if (currentSize == 0)
        return;
    InOrderRecs(0, visit);
}

template<class T>
void SeqFullBinaryTree<T>::PostOrderRecs(void (*visit)(T)) {
    if (currentSize == 0)
        return;
    PostOrderRecs(0, visit);
}


template<class T>
void SeqFullBinaryTree<T>::PreOrderRecs(int i, void (*visit)(T x)) {
    if (i < currentSize) {
        visit(elements[i]);
        PreOrderRecs(2 * i + 1, visit);
        PreOrderRecs(2 * i + 2, visit);
    }
}

template<class T>
void SeqFullBinaryTree<T>::InOrderRecs(int i, void (*visit)(T x)) {
    if (i < currentSize) {
        InOrderRecs(2 * i + 1, visit);
        visit(elements[i]);
        InOrderRecs(2 * i + 2, visit);
    }
}

template<class T>
void SeqFullBinaryTree<T>::PostOrderRecs(int i, void (*visit)(T x)) {
    if (i < currentSize) {
        PostOrderRecs(2 * i + 1, visit);
        PostOrderRecs(2 * i + 2, visit);
        visit(elements[i]);
    }
}

template<class T>
void SeqFullBinaryTree<T>::PreOrderNonRecs(void (*visit)(T x)) {
    stack<int> st;
    int v = 0;
    do {
        while (v < currentSize) {
            visit(elements[v]);
            st.push(v);
            v = v * 2 + 1;
        }
        if (!st.empty()) {
            v = st.top();
            st.pop();
            v = v * 2 + 2;
        }
    } while (v < currentSize || !st.empty());
}

template<class T>
void SeqFullBinaryTree<T>::InOrderNonRecs(void (*visit)(T x)) {
    stack<int> st;
    int v = 0;
    do {
        while (v < currentSize) {
            st.push(v);
            v = v * 2 + 1;
        }
        if (!st.empty()) {
            v = st.top();
            st.pop();
            visit(elements[v]);
            v = v * 2 + 2;
        }
    } while (v < currentSize || !st.empty());

}

template<class T>
void SeqFullBinaryTree<T>::PostOrderNonRecs(void (*visit)(T x)) {
    stack<int> st;
    stack<bool> isRightSt;
    int v = 0;
    bool rightFlag;
    do {
        while (v < currentSize) {
            st.push(v);
            isRightSt.push(false);
            v = v * 2 + 1;
        }
        while (!isRightSt.empty()) {
            v = st.top();
            rightFlag = isRightSt.top();
            st.pop();
            isRightSt.pop();
            if (!rightFlag) {//左子树回来
                st.push(v);
                isRightSt.push(true);
                v = v * 2 + 2;
                break;
            } else {//右子树回来
                visit(elements[v]);
            }
        }

    } while (!st.empty());

}


template<class T>
void SeqFullBinaryTree<T>::ThreeOrder(orderType order, void (*visit)(T)) {
    stack<int> st;
    stack<bool> stFlag;
    int v = 0;
    bool flag;
    while (v < currentSize || !st.empty()) {
        while (v < currentSize) {
            if (order == preOrder) {
                visit(elements[v]);
            }
            st.push(v);
            stFlag.push(false);
            v = v * 2 + 1;
        }
        if (!st.empty()) {
            v = st.top();
            st.pop();
            flag = stFlag.top();
            stFlag.pop();
            if (flag) {   //该结点是第二次进栈出来的
                if (order == postOrder) {
                    visit(elements[v]);
                }
                //没有这个则后序排序不会停止,
                // 这个会停止上面那个往左走的while循环
                v = currentSize;
            } else {     //该结点是第一次进栈出来的
                if (order == inOrder) {
                    visit(elements[v]);
                }
                st.push(v);
                stFlag.push(true);
                v = v * 2 + 2;
            }
        }
    }
}

template<class T>
void SeqFullBinaryTree<T>::LevelOrder(void (*visit)(T x)) {
    queue<int> qu;
    int v = 0;
    qu.push(v);
    while (!qu.empty()) {
        v = qu.front();
        qu.pop();
        visit(elements[v]);
        if (2 * v + 1 < currentSize)
            qu.push(2 * v + 1);
        if (2 * v + 2 < currentSize)
            qu.push(2 * v + 2);
    }
}

template<class T>
int SeqFullBinaryTree<T>::Height() const {
    return Height(0);
}

template<class T>
int SeqFullBinaryTree<T>::Height(int i) const {
    if (i >= currentSize)
        return 0;
    int h1 = Height(2 * i + 1);
    int h2 = Height(2 * i + 2);
    return (h1 > h2) ? h1 + 1 : h2 + 1;
}

template<class T>
int SeqFullBinaryTree<T>::HeightNoRecursion() {
    return 0;
}


template<class T>
void PrintData(T x) {
    cout << x << " ";
}


int main() {
    char tree[11] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
    SeqFullBinaryTree<char> s1(tree, 11);
    cout << "levelOrder" << endl;
    s1.LevelOrder(PrintData);

    cout << endl;
    cout << "height: " << s1.Height();


}





