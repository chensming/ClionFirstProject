//
// Created by Dell on 2019/12/22.
//

#include<iostream>

using namespace std;

const int DefaultSize = 100;

enum KindOfStatus {
    Active,
    Empty,
    Deleted
};

template<class T>
class HashTable {
public:
    explicit HashTable(int d, int sz = DefaultSize);

    ~HashTable() {
        delete[] ht;
        delete[] info;
    }

    HashTable<T> &operator=(const HashTable<T> &ht2);

    bool Search(T k1, T &el) const;

    bool Insert(const T &el);

    bool Remove(T k1);

    bool Remove(T k1, T &el);

    void makeEmpty();

    void Output();   //输出存储数组中的信息

private:
    int divitor;     //除数
    int CurrentSize; //当前大小
    int TableSize;   //容量
    T *ht;      //散列表存储数组
    KindOfStatus *info;   //状态数组
    int FindPos(T k1) const;
};


template<class T>
HashTable<T>::HashTable(int d, int sz) {
    divitor = d;
    TableSize = sz;
    CurrentSize = 0;
    ht = new T[TableSize];
    info = new KindOfStatus[TableSize];
    for (int i = 0; i < TableSize; i++)
        info[i] = Empty;
}


template<class T>
int HashTable<T>::FindPos(const T k1) const {
    //搜索在一个散列表中关键码与k1匹配的元素，搜索成功，则函数返回该元素的位置
    //范泽返回插入点(如果有足够的空间)
    //没找到返回-1，此时表已满
    int i = k1 % divitor;    //计算初始捅号
    int j = i;              // j是用来检测下一个空桶下标 或初始桶（如果初始桶为空为空）
    do {
        if (info[j] == Empty || (info[j] == Active && ht[j] == k1))
            return j;  //找到
        j = (j + 1) % TableSize; //线性探测，直接找下一个空的桶
    } while (j != i);
    return -1;     //没找到
}


template<class T>
bool HashTable<T>::Search(const T k1, T &el) const {
    int i = FindPos(k1);
    if (i == -1 || info[i] != Active || ht[i] != k1)
        return false;
    el = ht[i];
    return true;
}

//逻辑上删除而已
template<class T>
void HashTable<T>::makeEmpty() {
    for (int i = 0; i < TableSize; i++)
        info[i] = Empty;
    CurrentSize = 0;
}


template<class T>
HashTable<T> &HashTable<T>::operator=(const HashTable<T> &ht2) {
    //重载函数: 复制一个散列表
    if (this != &ht2) {
        delete[]ht;
        delete[]info;
        TableSize = ht2.TableSize;
        ht = new T[TableSize];
        info = new KindOfStatus[TableSize];
        for (int i = 0; i < TableSize; i++) {
            ht[i] = ht2.ht[i];
            info[i] = ht2.info[i];
        }
        CurrentSize = ht2.CurrentSize;
    }
    return *this;
}


template<class T>
bool HashTable<T>::Insert(const T &el) {
    //表中搜索e,若找到则不再插入，若未找到，但表已满，则不再插入，都返回false
    //若找到位置的标志是Empty或Deleted，不论表是否已满，x插入，返回true
    T k1 = el;
    int i = FindPos(k1);
    if (info[i] != Active) {
        ht[i] = el;
        info[i] = Active;
        CurrentSize++;
        return true;
    }
    if (info[i] == Active && ht[i] == el) {
        cout << "表中已有 " << el << " 元素,不能插入" << endl;
        return false;
    }
    cout << "表已满，不能插入" << el << " 元素" << endl;
    return false;
}


template<class T>
bool HashTable<T>::Remove(const T k1) {
    int i = FindPos(k1);
    if (info[i] == Active && ht[i] == k1) {
        info[i] = Deleted;  //逻辑上删除
        CurrentSize--;
        return true;
    }
    return false;
}


template<class T>
bool HashTable<T>::Remove(const T k1, T &el) {
    //在ht表中删除元素key，若表中找不到k1，或虽然找到k1,但它已经逻辑删除过
    //则返回false,否则在表中删除k1,并返回true,并在引用参数el中得到它
    int i = FindPos(k1);
    if (info[i] == Active && ht[i] == k1) {
        info[i] = Deleted;
        CurrentSize--;
        el = k1;
        return true;
    }
    return false;
}


template<class T>
void HashTable<T>::Output() {
    cout << endl;
    cout << "表中的元素:" << endl;
    for (int i = 0; i < TableSize; i++) {
        if (info[i] == Active) {
            cout << ht[i] << " ";
        } else {
            cout << "# ";
        }
    }
    cout << endl << endl;
}

template<class T>
void IsInsertSuccess(HashTable<T> &h, int x) {
    if (h.Insert(x)) {
        cout << "插入 " << x << "成功" << endl;
    } else {
        cout << "插入 " << x << "失败" << endl;
    }
}


template<class T>
void IsRemoveSuccess2(HashTable<T> &h, T x) {
    T backdata;
    if (h.Remove(x, backdata)) {
        cout << "删除 " << backdata << "成功" << endl;
    } else {
        cout << "删除 " << x << "失败" << endl;
    }
}


template<class T>
void IsRemoveSuccess(HashTable<T> &h, T x) {
    if (h.Remove(x)) {
        cout << "删除 " << x << "成功" << endl;
    } else {
        cout << "删除 " << x << "失败" << endl;
    }
}


template<class T>
void IsSearchSuccess(HashTable<T> &h, T x) {
    T backdata;
    if (h.Search(x, backdata)) {
        cout << "搜索 " << backdata << " 成功" << endl;
    } else {
        cout << "搜索 " << x << " 失败" << endl;
    }
}


int main() {
    HashTable<int> a(5, 12);
    IsInsertSuccess(a, 6);
    IsInsertSuccess(a, 1);
    IsInsertSuccess(a, 7);
    IsInsertSuccess(a, 5);
    IsInsertSuccess(a, 6);
    IsInsertSuccess(a, 25);
    IsInsertSuccess(a, -5);
    IsInsertSuccess(a, 7);
    IsInsertSuccess(a, 96);
    IsInsertSuccess(a, 73);
    IsInsertSuccess(a, 155);

    cout << endl;
    cout << "删除前..." << endl;
    a.Output();
    HashTable<int> b(2, 2);
    b = a;
    //复制a表到b表

    IsRemoveSuccess(a, 96);
    IsRemoveSuccess2(a, 155);
    IsRemoveSuccess(a, 6);

    IsSearchSuccess(a, 25);
    IsSearchSuccess(a, 1000);

    cout << endl;
    cout << "删除后..." << endl;
    a.Output();

    cout << "拷贝一份b表" << endl;
    b.Output();
}

