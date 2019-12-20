//
// Created by Dell on 2019/12/20.
//
#include <iostream>
#include <cassert>

using namespace std;
const int DefaultMaxSize = 50;

template<class T>
class SeqList {
public:
    explicit SeqList(int sz = DefaultMaxSize);

    SeqList(SeqList<T> &L);

    ~SeqList();

    int GetLength();

    void ReSize(int sz);

    int GetMaxSize();

    int Search(T x);

    int Locate(int i) const;

    bool GetData(int i, T &x) const;

    bool SetData(int i, T x);

    bool Insert(int i, T x);

    bool Remove(int i);

    bool Remove(int i, T &x);

    bool IsEmpty();

    bool IsFull();

    void input();

    void output();

private:
    T *data;
    int maxSize;
    int last;
};

template<class T>
SeqList<T>::SeqList(int sz) {
    maxSize = (sz < 10) ? DefaultMaxSize : sz;
    data = new T[maxSize];
    assert(data != nullptr);
    last = -1;
}

template<class T>
SeqList<T>::SeqList(SeqList<T> &L) {
    maxSize = L.GetMaxSize();
    last = L.GetLength() - 1;
    T value;
    data = new T[maxSize];
    assert(data != nullptr);
    for(int i = 0; i <= last; i++){
        data[i] = L.data[i];
    }
}

template<class T>
SeqList<T>::~SeqList() {
    if (data != nullptr)
        delete[] data;
}

template<class T>
int SeqList<T>::GetLength() {
    //last 指向最后一个元素下标，
    //当没有元素时，last 为-1
    return last + 1;
}

template<class T>
void SeqList<T>::ReSize(int sz) {
    if (sz == maxSize)
        return;
    T *oldData = data;
    int oldMaxSize = maxSize;
    maxSize = sz;
    data = new T[maxSize];
    for (int i = 0; i <= last; i++) {
        data[i] = oldData[i];
    }
    delete[] oldData;
}

template<class T>
int SeqList<T>::GetMaxSize() {
    return maxSize;
}

template<class T>
int SeqList<T>::Search(T x) {
    for (int i = 0; i <= last; i++)
        if (data[i] == x)
            return i;
    return false;
}

//定位第 i 个元素
template<class T>
int SeqList<T>::Locate(int i) const {
    if (i < 0 || i > last + 1)
        return -1;
    return i;
}

//取第 i 个元素的值
template<class T>
bool SeqList<T>::GetData(int i, T &x) const {
    if (i <= 0 || i > last + 1)
        return false;
    x = data[i - 1];
    return true;
}

//设置第 i 个元素的值
template<class T>
bool SeqList<T>::SetData(int i, T x) {
    if (i <= 0 || i > last + 1)
        return false;
    data[i - 1] = x;
    return true;
}

//插入到第 i 个元素之后(i = 0,表示插到最前)
template<class T>
bool SeqList<T>::Insert(int i, T x) {
    if (i < 0 || i > last + 1 || IsFull())
        return false;
    for (int j = last; j >= i; j--)
        data[j + 1] = data[j];
    data[i] = x;
    last++;
    return true;
}

//删除第 i 个元素
template<class T>
bool SeqList<T>::Remove(int i) {
    if (i <= 0 || i > last + 1 || IsEmpty())
        return false;
    for (int j = i; j < last; j++)
        data[j] = data[j + 1];
    last--;
}

//删除第 i 个元素,并通过引用变量 x 返回
template<class T>
bool SeqList<T>::Remove(int i, T &x) {
    if (i <= 0 || i > last + 1 || IsEmpty())
        return false;
    x = data[i];
    for (int j = i; j < last; j++)
        data[j] = data[j + 1];
    last--;
    return true;
}

template<class T>
bool SeqList<T>::IsEmpty() {
    return last == -1;
}

template<class T>
bool SeqList<T>::IsFull() {
    return last + 1 == maxSize;
}

template<class T>
void SeqList<T>::input() {
    int n;
    while (true) {
        cout << "请输入要建立的顺序表的个数" << endl;
        cin >> n;
        if (n > 0 && n <= maxSize)
            break;
    }
    cout << "请分别输入它们的元素:" << endl;
    last = -1;
    for (int i = 0; i < n; i++) {
        cin >> data[i];
        last++;
    }
}

template<class T>
void SeqList<T>::output() {
    for (int i = 0; i <= last; i++)
        cout << data[i] << " ";
    cout << endl;
}


int main() {
    SeqList<int> a;
    //    a.input();
    cout << "a.IsEmpty(): " << a.IsEmpty() << endl;
    cout << "a.Insert()..." << endl;
    a.Insert(0, 1);
    a.Insert(1, 3);
    a.Insert(1, 2);
    a.Insert(3, 4);
    a.Insert(0, 0);
    a.Insert(5, 5);

    SeqList<int> b(a);

    cout << "a.output()..." << endl;
    a.output();

    cout << endl;
    cout << "a.Remove(1): " << endl;
    a.Remove(1);
    cout << "a.output()..." << endl;
    a.output();

    int x;
    cout << "a.Remove(2, x): " << endl;
    a.Remove(2, x);
    cout << "x= " << x << endl;

    cout << "a.output()..." << endl;
    a.output();
    cout << endl;

    cout << "a.GetLength(): " << a.GetLength() << endl;
    cout << "b.getLength(): " << b.GetLength() << endl;

    cout << "b.output()..." << endl;
    b.output();

    cout << endl;
    cout << "b.GetMaxSize: " << b.GetMaxSize() << endl;
    cout << "b.GetData(3, x): " << b.GetData(3, x) << endl;
    cout << "x= " << x << endl;

    cout << "b.SetData(3, 100)" << endl;
    b.SetData(3, 100);

    cout << "b.Search(100): " << b.Search(100) << endl;

    cout << endl;
    cout << "b.GetMaxSize(): " << b.GetMaxSize() << endl;
    cout << "b.reSize(12)" << endl;
    b.ReSize(12);
    cout << "b.GetMaxSize(): " << b.GetMaxSize() << endl;
    cout << "b.output()..." << endl;
    b.output();

    cout << endl;
}
