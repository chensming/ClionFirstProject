//
// Created by Dell on 2019/12/15.
//

#include<iostream>
#include<stack>
#include <cassert>

using namespace std;

template<class T>
struct BSTNode {
    T data;
    BSTNode<T> *leftChild, *rightChild;

    BSTNode() : leftChild(nullptr), rightChild(nullptr) { data = T(); }

    explicit BSTNode(T d) : data(d), leftChild(nullptr), rightChild(nullptr) {}

    ~BSTNode() = default;

    void setData(T d) { data = d; }

    T getData() { return data; }
};


template<class T>
class BST {
public:
    BST() : root(nullptr) { RefValue = T(); }

    explicit BST(T value);

    ~BST() { makeEmpty(); }

    //置空（包括删除根节点）
    void makeEmpty();

    void makeEmpty(BSTNode<T> *ptr);

    //递归与非递归搜索
    bool Search(T x) const;

    BSTNode<T> *Search(T x, BSTNode<T> *ptr) const;

    BSTNode<T> *SearchNonRecursion(T x) const;

    //递归与非递归插入
    bool Insert(T x);


    bool InsertNonRecursion(T x);

    //递归删除
    bool Remove(T x);

    bool Remove(T x, BSTNode<T> *&ptr);
    //bool RemoveNonRecursion(const T x);非递归比较麻烦,这里没写

    //广义表输出二叉树
    void PrintBinTree();

    void PrintBinTree(BSTNode<T> *BT);

    //中序递归与非递归遍历输出
    void InOrder();

    void InOrder(BSTNode<T> *subtree);

    void InOrderNonRecursion();

    //递归算法，找到返回true，找不到返回false并插入
    bool BuildIfNotFound(T x);

    bool BuildIfNotFoundNonRecursion(T x);

private:
    BSTNode<T> *root;
    T RefValue; // 输入的终止标志值

    bool Insert(T x, BSTNode<T> *&ptr);

    bool BuildIfNotFound(T x, BSTNode<T> *&ptr);
};


template<class T>
BST<T>::BST(T value) {
    T x;
    root = nullptr;
    RefValue = value;
    cout << "请分别输入二叉搜索树的结点的值" << endl;
    cin >> x;
    while (x != RefValue) {
        Insert(x, root);
        cin >> x;
    }
}


template<class T>
void BST<T>::makeEmpty() {
    makeEmpty(root);
    root = nullptr;
}


template<class T>
void BST<T>::makeEmpty(BSTNode<T> *ptr) {
    if (ptr != nullptr) {
        makeEmpty(ptr->leftChild);
        makeEmpty(ptr->rightChild);
        delete ptr;
    }
}


template<class T>
bool BST<T>::Search(const T x) const {
    return Search(x, root) != nullptr;
}


template<class T>
BSTNode<T> *BST<T>::Search(const T x, BSTNode<T> *ptr) const {
    if (ptr == nullptr)
        return nullptr;
    else if (x < ptr->data)
        return Search(x, ptr->leftChild);
    else if (x > ptr->data)
        return Search(x, ptr->rightChild);
    else
        return ptr;
}


template<class T>
BSTNode<T> *BST<T>::SearchNonRecursion(const T x) const {
    BSTNode<T> *p = root;
    while (p != nullptr) {
        if (p->data == x)
            return p;
        else if (x < p->data)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    return nullptr;
}


template<class T>
bool BST<T>::Insert(const T x) {
    return Insert(x, root);
}


template<class T>
bool BST<T>::Insert(const T x, BSTNode<T> *&ptr) {
    if (ptr == nullptr) {
        ptr = new BSTNode<T>(x);
        assert(ptr != nullptr);
        return true;
    } else if (x < ptr->data)
        return Insert(x, ptr->leftChild);
    else if (x > ptr->data)
        return Insert(x, ptr->rightChild);
    else
        return false; //已在树中，不需要插入
}


template<class T>
bool BST<T>::InsertNonRecursion(const T x) {
    BSTNode<T> *BT, *f, *p;
    BT = root;
    f = nullptr;
    while (BT != nullptr) {
        if (x == BT->data)
            return -1;
        else if (x < BT->data) {
            f = BT;
            BT = BT->leftChild;
        } else {
            f = BT;
            BT = BT->rightChild;
        }
    }
    p = new BSTNode<T>(x);
    p->leftChild = p->rightChild = nullptr;
    if (f == nullptr)
        root = p;
    else if (x > f->data)
        f->rightChild = p;
    else
        f->leftChild = p;
    return true;
}


template<class T>
bool BST<T>::Remove(const T x) {
    return Remove(x, root);
}


template<class T>
bool BST<T>::Remove(const T x, BSTNode<T> *&ptr) {
    BSTNode<T> *temp;
    if (ptr != nullptr) {
        if (x < ptr->data)
            return Remove(x, ptr->leftChild);
        else if (x > ptr->data)
            return Remove(x, ptr->rightChild);
            //等于的情况
        else if (ptr->leftChild != nullptr && ptr->rightChild != nullptr) {
            temp = ptr->rightChild;
            while (temp->leftChild != nullptr)
                temp = temp->leftChild;
            ptr->data = temp->data;
            Remove(ptr->data, ptr->rightChild);
            return true;
        } else {
            //引用的作用在下面if和else语句中体现了
            temp = ptr;
            //连接右子树或将其置空
            if (ptr->leftChild == nullptr)
                ptr = ptr->rightChild;
            else
                ptr = ptr->leftChild;
            delete temp;
            return true;
        }
    }
    return false;
}


template<class T>
void BST<T>::PrintBinTree() {
    PrintBinTree(root);
    cout << endl;
}


template<class T>
void BST<T>::PrintBinTree(BSTNode<T> *BT) {
    if (BT != nullptr) {
        cout << BT->data;
        if (BT->leftChild != nullptr || BT->rightChild != nullptr) {
            cout << "(";
            if (BT->leftChild != nullptr)
                PrintBinTree(BT->leftChild);
            if (BT->rightChild != nullptr) {
                cout << ",";
                PrintBinTree(BT->rightChild);
            }
            cout << ")";
        }

    }
}


template<class T>
void BST<T>::InOrder() {
    InOrder(root);
    cout << endl;
}


template<class T>
void BST<T>::InOrder(BSTNode<T> *subtree) {
    if (subtree != nullptr) {
        InOrder(subtree->leftChild);
        cout << subtree->data << " ";
        InOrder(subtree->rightChild);
    }
}


template<class T>
void BST<T>::InOrderNonRecursion() {
    if (root == nullptr) {
        cout << "该树为空" << endl;
        return;
    }
    stack<BSTNode<T> *> S;
    BSTNode<T> *p = root;
    while (p != nullptr || !S.empty()) {
        while (p != nullptr) {
            S.push(p);
            p = p->leftChild;
        }
        if (!S.empty()) {
            p = S.top();
            S.pop();
            cout << p->data << " ";
            p = p->rightChild;
        }
    }
    cout << endl;
}

template<class T>
bool BST<T>::BuildIfNotFound(T x) {
    return BuildIfNotFound(x, root);
}

template<class T>
bool BST<T>::BuildIfNotFound(T x, BSTNode<T> *&ptr) {
    if (ptr == nullptr) {
        ptr = new BSTNode<T>(x);
        assert(ptr != nullptr);
        cout << "找不到 " << x << ", 然后已将其插入到二叉树..." << endl;
        return false;
    } else if (x == ptr->data) {
        return true;
    } else if (x < ptr->data) {
        return BuildIfNotFound(x, ptr->leftChild);
    } else {
        return BuildIfNotFound(x, ptr->rightChild);
    }
}

template<class T>
bool BST<T>::BuildIfNotFoundNonRecursion(T x) {
    BSTNode<T> *pre = nullptr, *ptr = root;
    while (ptr != nullptr) {
        if (x == ptr->data)
            return true; //找到了
        else if (x < ptr->data) {
            pre = ptr;
            ptr = ptr->leftChild;
        } else {
            pre = ptr;
            ptr = ptr->rightChild;
        }
    }
    ptr = new BSTNode<T>(x);
    if(pre == nullptr)
        root = ptr;
    else if(x < pre->data){
        pre->leftChild = ptr;
    } else {
        pre->rightChild = ptr;
    }
    cout << "没找到 " << x << " ,现已经将其插入到二叉搜索树中" << endl;
    return false;
}


int main() {
    BST<int> a;

    a.Insert(16);
    a.Insert(8);
    a.Insert(3);
    a.Insert(22);
    a.Insert(18);
    a.Insert(3);
    a.Insert(36);
    a.Insert(24);
    a.Insert(-6);
    a.Insert(-7);


    cout << endl;
    cout << "以广义表输出树结点的值" << endl;
    a.PrintBinTree();


    a.InsertNonRecursion(100);
    cout << endl;
    cout << "以广义表输出树结点的值" << endl;
    a.PrintBinTree();
    a.InsertNonRecursion(30);
    cout << endl;
    cout << "以广义表输出树结点的值" << endl;
    a.PrintBinTree();
    a.InsertNonRecursion(20);
    cout << endl;
    cout << "以广义表输出树结点的值" << endl;
    a.PrintBinTree();

    a.InsertNonRecursion(19);
    cout << endl;
    cout << "以广义表输出树结点的值" << endl;
    a.PrintBinTree();

    a.InsertNonRecursion(9);
    cout << endl;
    cout << "以广义表输出树结点的值" << endl;
    a.PrintBinTree();

    cout << endl;
    int x = 37;
    if (a.BuildIfNotFoundNonRecursion(x))
        cout << "找到 " << x << " 了" << endl;
    cout << endl;
    cout << "以广义表输出树结点的值" << endl;
    a.PrintBinTree();

    x = 21;
    if (a.BuildIfNotFoundNonRecursion(x))
        cout << "找到 " << x << " 了" << endl;
    cout << endl;
    cout << "以广义表输出树结点的值" << endl;
    a.PrintBinTree();

    cout << "中序遍历" << endl;
    a.InOrder();

    cout << "非递归中序遍历" << endl;
    a.InOrderNonRecursion();

    cout << endl;
//    system("pause");
}








