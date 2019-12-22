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

    void Output();   //����洢�����е���Ϣ

private:
    int divitor;     //����
    int CurrentSize; //��ǰ��С
    int TableSize;   //����
    T *ht;      //ɢ�б�洢����
    KindOfStatus *info;   //״̬����
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
    //������һ��ɢ�б��йؼ�����k1ƥ���Ԫ�أ������ɹ����������ظ�Ԫ�ص�λ��
    //���󷵻ز����(������㹻�Ŀռ�)
    //û�ҵ�����-1����ʱ������
    int i = k1 % divitor;    //�����ʼͱ��
    int j = i;              // j�����������һ����Ͱ�±� ���ʼͰ�������ʼͰΪ��Ϊ�գ�
    do {
        if (info[j] == Empty || (info[j] == Active && ht[j] == k1))
            return j;  //�ҵ�
        j = (j + 1) % TableSize; //����̽�⣬ֱ������һ���յ�Ͱ
    } while (j != i);
    return -1;     //û�ҵ�
}


template<class T>
bool HashTable<T>::Search(const T k1, T &el) const {
    int i = FindPos(k1);
    if (i == -1 || info[i] != Active || ht[i] != k1)
        return false;
    el = ht[i];
    return true;
}

//�߼���ɾ������
template<class T>
void HashTable<T>::makeEmpty() {
    for (int i = 0; i < TableSize; i++)
        info[i] = Empty;
    CurrentSize = 0;
}


template<class T>
HashTable<T> &HashTable<T>::operator=(const HashTable<T> &ht2) {
    //���غ���: ����һ��ɢ�б�
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
    //��������e,���ҵ����ٲ��룬��δ�ҵ����������������ٲ��룬������false
    //���ҵ�λ�õı�־��Empty��Deleted�����۱��Ƿ�������x���룬����true
    T k1 = el;
    int i = FindPos(k1);
    if (info[i] != Active) {
        ht[i] = el;
        info[i] = Active;
        CurrentSize++;
        return true;
    }
    if (info[i] == Active && ht[i] == el) {
        cout << "�������� " << el << " Ԫ��,���ܲ���" << endl;
        return false;
    }
    cout << "�����������ܲ���" << el << " Ԫ��" << endl;
    return false;
}


template<class T>
bool HashTable<T>::Remove(const T k1) {
    int i = FindPos(k1);
    if (info[i] == Active && ht[i] == k1) {
        info[i] = Deleted;  //�߼���ɾ��
        CurrentSize--;
        return true;
    }
    return false;
}


template<class T>
bool HashTable<T>::Remove(const T k1, T &el) {
    //��ht����ɾ��Ԫ��key���������Ҳ���k1������Ȼ�ҵ�k1,�����Ѿ��߼�ɾ����
    //�򷵻�false,�����ڱ���ɾ��k1,������true,�������ò���el�еõ���
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
    cout << "���е�Ԫ��:" << endl;
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
        cout << "���� " << x << "�ɹ�" << endl;
    } else {
        cout << "���� " << x << "ʧ��" << endl;
    }
}


template<class T>
void IsRemoveSuccess2(HashTable<T> &h, T x) {
    T backdata;
    if (h.Remove(x, backdata)) {
        cout << "ɾ�� " << backdata << "�ɹ�" << endl;
    } else {
        cout << "ɾ�� " << x << "ʧ��" << endl;
    }
}


template<class T>
void IsRemoveSuccess(HashTable<T> &h, T x) {
    if (h.Remove(x)) {
        cout << "ɾ�� " << x << "�ɹ�" << endl;
    } else {
        cout << "ɾ�� " << x << "ʧ��" << endl;
    }
}


template<class T>
void IsSearchSuccess(HashTable<T> &h, T x) {
    T backdata;
    if (h.Search(x, backdata)) {
        cout << "���� " << backdata << " �ɹ�" << endl;
    } else {
        cout << "���� " << x << " ʧ��" << endl;
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
    cout << "ɾ��ǰ..." << endl;
    a.Output();
    HashTable<int> b(2, 2);
    b = a;
    //����a��b��

    IsRemoveSuccess(a, 96);
    IsRemoveSuccess2(a, 155);
    IsRemoveSuccess(a, 6);

    IsSearchSuccess(a, 25);
    IsSearchSuccess(a, 1000);

    cout << endl;
    cout << "ɾ����..." << endl;
    a.Output();

    cout << "����һ��b��" << endl;
    b.Output();
}

