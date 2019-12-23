//
// Created by Dell on 2019/12/23.
//
#include <iostream>
#include <cassert>

using namespace std;

template<class T>
struct linkNode {
    T data;
    linkNode<T> *link;

    linkNode() : link(nullptr) { data = T(); }

    explicit linkNode(T x) : data(x), link(nullptr) {}
};

template<class T>
class CyclicList {
public:
    CyclicList();

    ~CyclicList();

    void MakeEmpty();

    bool Insert(int i, T x);

    bool Remove(int i);

    bool Remove(int i, T& x);

    void output(int num);//代表输多少个元素

    int GetSize();

    bool IsEmpty();


private:
    linkNode<T> *head;
};

template<class T>
CyclicList<T>::CyclicList() {
    head = new linkNode<T>(-1);
    assert(head != nullptr);
    head->link = head; // 循环链表
}

template<class T>
CyclicList<T>::~CyclicList() {
    MakeEmpty();
    delete head;
}

template<class T>
void CyclicList<T>::MakeEmpty() {
    linkNode<T> *del, *next = head->link;
    while (next != head) {
        del = next;
        next = next->link;
        delete del;
    }
    head->link = head;
}

//想插入到第几个位置（插入完成后的位置）
template<class T>
bool CyclicList<T>::Insert(int i, T x) {
    linkNode<T> *current = head;
    if (i < 1) {
        cout << "输入位置应该大于0" << endl;
        return false;
    }
    while (i > 1) {
        current = current->link;
        i--;
    }
    auto *p = new linkNode<T>(x);
    p->link = current->link;
    current->link = p;
    return true;
}

template<class T>
bool CyclicList<T>::Remove(int i) {
    linkNode<T> *current = head;
    if (i < 1) {
        cout << "输入位置应该大于0" << endl;
        return false;
    }
    while (i > 1) {
        current = current->link;
        i--;
    }
    if (current->link == head) {
        cout << "不能删除表头空节点" << endl;
        return false;
    }
    linkNode<T> *del = current->link;
    current->link = del->link;
    delete del;
    return true;
}

template<class T>
bool CyclicList<T>::Remove(int i, T& x) {
    linkNode<T> *current = head;
    if (i < 1) {
        cout << "输入位置应该大于0" << endl;
        return false;
    }
    while (i > 1) {
        current = current->link;
        i--;
    }
    if (current->link == head) {
        cout << "不能删除表头空节点" << endl;
        return false;
    }
    linkNode<T> *del = current->link;
    current->link = del->link;
    x = del->data;
    delete del;
    return true;
}

template<class T>
void CyclicList<T>::output(int num) {
    if (num < 1) {
        cout << "输入的值应该大于1" << endl;
        return;
    }
    linkNode<T> *p = head->link;
    while (num > 0) {
        if (head == p) {
            p = p->link;
            continue;
        }

        cout << p->data << " ";
        num--;
        p = p->link;
    }
    cout << endl;
}

template<class T>
int CyclicList<T>::GetSize() {
    linkNode<T> *p = head->link;
    int count = 0;
    while (p != head) {
        count++;
        p = p->link;
    }
    return count;
}

template<class T>
bool CyclicList<T>::IsEmpty() {
    return head->link == head;
}


int main() {
    CyclicList<int> c1;
    cout << "c1.IsEmpty(): " << c1.IsEmpty() << endl;
    cout << "c1.GetSize(): " << c1.GetSize() << endl;

    c1.Insert(1, 1);
    c1.output(10);
    cout << "c1.GetSize(): " << c1.GetSize() << endl;
    cout << "c1.IsEmpty(): " << c1.IsEmpty() << endl;

    c1.Insert(2, 2);
    c1.output(10);

    c1.Insert(3, 3);
    c1.output(10);

    c1.Insert(4, 4);
    c1.output(10);
    cout << "c1.GetSize(): " << c1.GetSize() << endl;

    int x;
    c1.Remove(3, x);
    c1.output(10);
    cout << "c1.GetSize(): " << c1.GetSize() << endl;
    cout << "x= " << x << endl;
}


