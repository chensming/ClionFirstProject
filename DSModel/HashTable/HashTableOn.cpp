#include<iostream>

using namespace std;

#include<cassert>

const int DefaultSize = 100;

template<class T>
struct ChainNode {
    T data;
    ChainNode<T> *next;

    ChainNode() { next = nullptr; }

    explicit ChainNode(T d, ChainNode<T> *n = nullptr) {
        data = d;
        next = n;
    }
};

template<class T>
class HashTable {
public:
    explicit HashTable(int sz = DefaultSize);

    ~HashTable() { delete[] ht; }

    bool Search(T k1);

    bool InsertFront(T el);

    bool InsertRear(T el);

    bool Remove(T k1, T &el);

    void Output() const;

private:
    int TableSize;
    ChainNode<T> **ht;   //散列表
    ChainNode<T> *FindPos(T k1);

};


template<class T>
HashTable<T>::HashTable(int sz) {
    TableSize = sz;
    ht = new ChainNode<T> *[sz];
    assert(ht != nullptr);
    for (int i = 0; i < TableSize; i++)
        ht[i] = nullptr;
}


template<class T>
ChainNode<T> *HashTable<T>::FindPos(const T k1) {
    //在散列表ht中搜索关键码为k1的元素，函数返回一个纸箱散列表某位置的指针
    //若元素不在，则返回0(nullptr)
    int j = (k1 % TableSize + TableSize) % TableSize; // 解决负数求模为负数的问题
    ChainNode<T> *p = ht[j];
    while (p != nullptr && p->data != k1)
        p = p->next;
    //返回值为nullptr则是找到一个空位置返回
    //返回值非空则是哈希表中已有此元素，Search函数调用了它
    return p;
}


template<class T>
bool HashTable<T>::Search(const T k1) {
    ChainNode<T> *p = FindPos(k1);
    return p != nullptr;
}


//头插入没有判重,而尾插入有
template<class T>
bool HashTable<T>::InsertFront(const T el) {
//    ChainNode<T> *newPtr = new ChainNode<T>(el);
    auto *newPtr = new ChainNode<T>(el);
    assert(newPtr != nullptr);
    //FindPos(el) = newPtr;
    int j = (el % TableSize + TableSize) % TableSize;


    //头插入
    newPtr->next = ht[j];
    ht[j] = newPtr;
    return true;
}


//尾插入有判重,而头插入没有
template<class T>
bool HashTable<T>::InsertRear(const T el) {
//    ChainNode<T> *newPtr = new ChainNode<T>(el);
    auto *newPtr = new ChainNode<T>(el);
    assert(newPtr != nullptr);

    int j = (el % TableSize + TableSize) % TableSize;
    ChainNode<T> *p = ht[j], *pre = nullptr;
    while (p != nullptr) {
        if (p->data == el) {
            cout << "表中已有 " << el << " 元素" << endl;
            return false;
        }
        pre = p;
        p = p->next;
    }
    if (pre == nullptr)   //表头插入
    {
        ht[j] = newPtr;
        return true;
    }
    //一般插入
    pre->next = newPtr;
    return true;
}
//这里表头可以选择浪费一个空间使算法变得统一起来

template<class T>
bool HashTable<T>::Remove(const T k1, T &el) {
    int j = (k1 % TableSize + TableSize) % TableSize;
    ChainNode<T> *p = ht[j];
    ChainNode<T> *pre = nullptr;
    while (p != nullptr && p->data != k1) {
        pre = p;
        p = p->next;
    }
    if (p == nullptr)   //没找到哦
        return false;
    if (pre != nullptr) {
        pre->next = p->next;
    }
    if (p == ht[j]) // 在表头
    {
        ht[j] = p->next;
    }
    el = p->data;  //通过引用传回
    delete p;
    return true;
}


template<class T>
void IsRemoveSuccess(HashTable<T> &h, T x) {
    T backdata;
    if (h.Remove(x, backdata)) {
        cout << "删除 " << backdata << "成功" << endl;
    } else {
        cout << "删除 " << x << "失败" << endl;
    }
}


template<class T>
void HashTable<T>::Output() const {
    ChainNode<T> *p;
    for (int i = 0; i < TableSize; i++) {
        cout << "第 " << i << "个桶: ";
        p = ht[i];
        while (p != nullptr) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    cout << endl;
}


template<class T>
void IsSearchSuccess(HashTable<T> &h, T x) {
    if (h.Search(x)) {
        cout << "搜索 " << x << " 成功" << endl;
    } else {
        cout << "搜索 " << x << " 失败" << endl;
    }
}


template<class T>
void IsInsertFrontSuccess(HashTable<T> &h, int x) {
    if (h.InsertFront(x)) {
        cout << "头插入 " << x << "成功" << endl;
    } else {
        cout << "头插入 " << x << "失败" << endl;
    }
}


template<class T>
void IsInsertRearSuccess(HashTable<T> &h, int x) {
    if (h.InsertRear(x)) {
        cout << "尾插入 " << x << "成功" << endl;
    } else {
        cout << "尾插入 " << x << "失败" << endl;
    }
}


int main() {
    HashTable<int> a(12);
    IsInsertFrontSuccess(a, 6);
    IsInsertFrontSuccess(a, 1);
    IsInsertFrontSuccess(a, 7);
    IsInsertFrontSuccess(a, 5);
    IsInsertFrontSuccess(a, 6);
    IsInsertFrontSuccess(a, 25);
    IsInsertFrontSuccess(a, -5);
    IsInsertFrontSuccess(a, 7);
    IsInsertFrontSuccess(a, 96);
    IsInsertFrontSuccess(a, 73);
    IsInsertFrontSuccess(a, 155);

    cout << endl;
    cout << "删除前..." << endl;
    a.Output();

    cout << endl;
    IsSearchSuccess(a, 73);
    IsRemoveSuccess(a, 155);
    IsSearchSuccess(a, -5);

    cout << endl << endl;
    a.Output();


    IsRemoveSuccess(a, 6);
    IsRemoveSuccess(a, 7);


    cout << endl << endl;
    a.Output();


    cout << endl << endl;
    IsInsertRearSuccess(a, 88);
    a.Output();

    IsInsertRearSuccess(a, 721);

    cout << endl << endl;
    a.Output();

    IsInsertRearSuccess(a, 88);

    cout << endl << endl;
    a.Output();

}