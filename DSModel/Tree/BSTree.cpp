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

    //�ÿգ�����ɾ�����ڵ㣩
    void makeEmpty();

    void makeEmpty(BSTNode<T> *ptr);

    //�ݹ���ǵݹ�����
    bool Search(T x) const;

    BSTNode<T> *Search(T x, BSTNode<T> *ptr) const;

    BSTNode<T> *SearchNonRecursion(T x) const;

    //�ݹ���ǵݹ����
    bool Insert(T x);


    bool InsertNonRecursion(T x);

    //�ݹ�ɾ��
    bool Remove(T x);

    bool Remove(T x, BSTNode<T> *&ptr);
    //bool RemoveNonRecursion(const T x);�ǵݹ�Ƚ��鷳,����ûд

    //��������������
    void PrintBinTree();

    void PrintBinTree(BSTNode<T> *BT);

    //����ݹ���ǵݹ�������
    void InOrder();

    void InOrder(BSTNode<T> *subtree);

    void InOrderNonRecursion();

    //�ݹ��㷨���ҵ�����true���Ҳ�������false������
    bool BuildIfNotFound(T x);

    bool BuildIfNotFoundNonRecursion(T x);

private:
    BSTNode<T> *root;
    T RefValue; // �������ֹ��־ֵ

    bool Insert(T x, BSTNode<T> *&ptr);

    bool BuildIfNotFound(T x, BSTNode<T> *&ptr);
};


template<class T>
BST<T>::BST(T value) {
    T x;
    root = nullptr;
    RefValue = value;
    cout << "��ֱ���������������Ľ���ֵ" << endl;
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
        return false; //�������У�����Ҫ����
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
            //���ڵ����
        else if (ptr->leftChild != nullptr && ptr->rightChild != nullptr) {
            temp = ptr->rightChild;
            while (temp->leftChild != nullptr)
                temp = temp->leftChild;
            ptr->data = temp->data;
            Remove(ptr->data, ptr->rightChild);
            return true;
        } else {
            //���õ�����������if��else�����������
            temp = ptr;
            //���������������ÿ�
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
        cout << "����Ϊ��" << endl;
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
        cout << "�Ҳ��� " << x << ", Ȼ���ѽ�����뵽������..." << endl;
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
            return true; //�ҵ���
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
    cout << "û�ҵ� " << x << " ,���Ѿ�������뵽������������" << endl;
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
    cout << "�Թ�������������ֵ" << endl;
    a.PrintBinTree();


    a.InsertNonRecursion(100);
    cout << endl;
    cout << "�Թ�������������ֵ" << endl;
    a.PrintBinTree();
    a.InsertNonRecursion(30);
    cout << endl;
    cout << "�Թ�������������ֵ" << endl;
    a.PrintBinTree();
    a.InsertNonRecursion(20);
    cout << endl;
    cout << "�Թ�������������ֵ" << endl;
    a.PrintBinTree();

    a.InsertNonRecursion(19);
    cout << endl;
    cout << "�Թ�������������ֵ" << endl;
    a.PrintBinTree();

    a.InsertNonRecursion(9);
    cout << endl;
    cout << "�Թ�������������ֵ" << endl;
    a.PrintBinTree();

    cout << endl;
    int x = 37;
    if (a.BuildIfNotFoundNonRecursion(x))
        cout << "�ҵ� " << x << " ��" << endl;
    cout << endl;
    cout << "�Թ�������������ֵ" << endl;
    a.PrintBinTree();

    x = 21;
    if (a.BuildIfNotFoundNonRecursion(x))
        cout << "�ҵ� " << x << " ��" << endl;
    cout << endl;
    cout << "�Թ�������������ֵ" << endl;
    a.PrintBinTree();

    cout << "�������" << endl;
    a.InOrder();

    cout << "�ǵݹ��������" << endl;
    a.InOrderNonRecursion();

    cout << endl;
//    system("pause");
}








