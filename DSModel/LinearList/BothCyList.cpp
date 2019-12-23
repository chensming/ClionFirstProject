//
// Created by Dell on 2019/12/23.
//

#include <iostream>
#include <cassert>

using namespace std;

template<class T>
struct linkNode {
    T data;
    linkNode<T> *link[2];

    linkNode() {
        link[0] = link[1] = nullptr;
        data = T();
    }

    explicit linkNode(T x) {
        link[0] = link[1] = nullptr;
        data = x;
    }
};


template<class T>
class BothCyList {
public:
    BothCyList();

    ~BothCyList();

    void MakeEmpty();

    bool Insert(int i, int d, T x);

    bool Remove(int i, int d);

    bool Remove(int i, int d, T &x);

    void output(int d, int num);//代表输多少个元素

    int GetSize();

    bool IsEmpty();


private:
    linkNode<T> *head;
};

template<class T>
BothCyList<T>::BothCyList() {
    head = new linkNode<T>(-1);
    assert(head != nullptr);
    head->link[0] = head;
    head->link[1] = head;
}

template<class T>
BothCyList<T>::~BothCyList() {
    MakeEmpty();
    delete head;
}

template<class T>
void BothCyList<T>::MakeEmpty() {
    linkNode<T> *p = head->link[1];
    linkNode<T> *del = nullptr;
    while (p != head) {
        del = p;
        p = p->link[1];
        delete del;
    }
}


//d方向，i为第i个，x为要插入的值
template<class T>
bool BothCyList<T>::Insert(int i, int d, T x) {
    if (i < 1) {
        cout << "输入的i要大于0" << endl;
        return false;
    }
    linkNode<T> *p = head;
    linkNode<T> *q = nullptr;
    while (i > 1) {
        p = p->link[d];
        i--;
    }
    q = new linkNode<T>(x);
    int nd = (d + 1) % 2;
    q->link[d] = p->link[d];
    q->link[d]->link[nd] = q;
    p->link[d] = q;
    q->link[nd] = p;
    return true;
}

template<class T>
bool BothCyList<T>::Remove(int i, int d) {
    if (i < 1) {
        cout << "输入的i要大于0" << endl;
        return false;
    }
    linkNode<T> *p = head;
    while (i > 0) {
        p = p->link[d];
        i--;
    }
    p->link[d]->link[!d] = p->link[!d];
    p->link[!d]->link[d] = p->link[d];
    delete p;
    return true;
}


template<class T>
bool BothCyList<T>::Remove(int i, int d, T &x) {
    if (i < 1) {
        cout << "输入的i要大于0" << endl;
        return false;
    }
    linkNode<T> *p = head;
    while (i > 0) {
        p = p->link[d];
        i--;
    }
    p->link[d]->link[!d] = p->link[!d];
    p->link[!d]->link[d] = p->link[d];
    x = p->data;
    delete p;
    return true;
}


template<class T>
void BothCyList<T>::output(int d, int num) {
    linkNode<T> *p = head->link[d];
    while (num > 0) {
        if(p == head){
            p = p->link[d];
            continue;
        }
        cout << p->data << " ";
        p = p->link[d];
        num--;
    }
    cout << endl;
}

template<class T>
int BothCyList<T>::GetSize() {
    linkNode<T> *p = head->link[1];
    int count = 0;
    while (p != head) {
        count++;
        p = p->link[1];
    }
    return count;
}

template<class T>
bool BothCyList<T>::IsEmpty() {
    return head->link[0] == head;
}


int main() {
    BothCyList<int> a;
    a.Insert(1,1,10);
    a.Insert(2,1,20);
    a.Insert(3,1,30);
    a.Insert(4,1,40);
    a.Insert(5,1,50);
    a.Insert(1,0,90);
    a.Insert(2,0,80);
    a.Insert(3,0,70);
    a.Insert(4,0,60);
    a.output(1,a.GetSize());
    a.output(0,a.GetSize());
}