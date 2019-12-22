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
    ChainNode<T> **ht;   //ɢ�б�
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
    //��ɢ�б�ht�������ؼ���Ϊk1��Ԫ�أ���������һ��ֽ��ɢ�б�ĳλ�õ�ָ��
    //��Ԫ�ز��ڣ��򷵻�0(nullptr)
    int j = (k1 % TableSize + TableSize) % TableSize; // ���������ģΪ����������
    ChainNode<T> *p = ht[j];
    while (p != nullptr && p->data != k1)
        p = p->next;
    //����ֵΪnullptr�����ҵ�һ����λ�÷���
    //����ֵ�ǿ����ǹ�ϣ�������д�Ԫ�أ�Search������������
    return p;
}


template<class T>
bool HashTable<T>::Search(const T k1) {
    ChainNode<T> *p = FindPos(k1);
    return p != nullptr;
}


//ͷ����û������,��β������
template<class T>
bool HashTable<T>::InsertFront(const T el) {
//    ChainNode<T> *newPtr = new ChainNode<T>(el);
    auto *newPtr = new ChainNode<T>(el);
    assert(newPtr != nullptr);
    //FindPos(el) = newPtr;
    int j = (el % TableSize + TableSize) % TableSize;


    //ͷ����
    newPtr->next = ht[j];
    ht[j] = newPtr;
    return true;
}


//β����������,��ͷ����û��
template<class T>
bool HashTable<T>::InsertRear(const T el) {
//    ChainNode<T> *newPtr = new ChainNode<T>(el);
    auto *newPtr = new ChainNode<T>(el);
    assert(newPtr != nullptr);

    int j = (el % TableSize + TableSize) % TableSize;
    ChainNode<T> *p = ht[j], *pre = nullptr;
    while (p != nullptr) {
        if (p->data == el) {
            cout << "�������� " << el << " Ԫ��" << endl;
            return false;
        }
        pre = p;
        p = p->next;
    }
    if (pre == nullptr)   //��ͷ����
    {
        ht[j] = newPtr;
        return true;
    }
    //һ�����
    pre->next = newPtr;
    return true;
}
//�����ͷ����ѡ���˷�һ���ռ�ʹ�㷨���ͳһ����

template<class T>
bool HashTable<T>::Remove(const T k1, T &el) {
    int j = (k1 % TableSize + TableSize) % TableSize;
    ChainNode<T> *p = ht[j];
    ChainNode<T> *pre = nullptr;
    while (p != nullptr && p->data != k1) {
        pre = p;
        p = p->next;
    }
    if (p == nullptr)   //û�ҵ�Ŷ
        return false;
    if (pre != nullptr) {
        pre->next = p->next;
    }
    if (p == ht[j]) // �ڱ�ͷ
    {
        ht[j] = p->next;
    }
    el = p->data;  //ͨ�����ô���
    delete p;
    return true;
}


template<class T>
void IsRemoveSuccess(HashTable<T> &h, T x) {
    T backdata;
    if (h.Remove(x, backdata)) {
        cout << "ɾ�� " << backdata << "�ɹ�" << endl;
    } else {
        cout << "ɾ�� " << x << "ʧ��" << endl;
    }
}


template<class T>
void HashTable<T>::Output() const {
    ChainNode<T> *p;
    for (int i = 0; i < TableSize; i++) {
        cout << "�� " << i << "��Ͱ: ";
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
        cout << "���� " << x << " �ɹ�" << endl;
    } else {
        cout << "���� " << x << " ʧ��" << endl;
    }
}


template<class T>
void IsInsertFrontSuccess(HashTable<T> &h, int x) {
    if (h.InsertFront(x)) {
        cout << "ͷ���� " << x << "�ɹ�" << endl;
    } else {
        cout << "ͷ���� " << x << "ʧ��" << endl;
    }
}


template<class T>
void IsInsertRearSuccess(HashTable<T> &h, int x) {
    if (h.InsertRear(x)) {
        cout << "β���� " << x << "�ɹ�" << endl;
    } else {
        cout << "β���� " << x << "ʧ��" << endl;
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
    cout << "ɾ��ǰ..." << endl;
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