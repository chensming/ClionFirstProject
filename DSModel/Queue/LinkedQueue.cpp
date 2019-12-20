//
// Created by Dell on 2019/12/20.
//
#include <iostream>
#include <cassert>

using namespace std;

template<class T>
struct linkNode {
    T data;
    linkNode<T> *link;

    linkNode() : link(nullptr) {}
};

template<class T>
class LinkedQueue {
public:
    LinkedQueue();

    ~LinkedQueue();

    void makeEmpty();

    bool EnQueue(T x);

    bool DeQueue();

    bool DeQueue(T &x);

    bool getFront(T &x) const;

    int getSize() const;

    bool IsEmpty() { return front->link == nullptr; }

    void output() const;

private:
    linkNode<T> *front, *rear;
};

template<class T>
LinkedQueue<T>::LinkedQueue() {
    //浪费一个空间使入队算法统一
    front = new linkNode<T>;
    rear = front;
    assert(front != nullptr);
}

template<class T>
LinkedQueue<T>::~LinkedQueue() {
    makeEmpty();
    delete front;
}

template<class T>
void LinkedQueue<T>::makeEmpty() {
    linkNode<T> *p, *head = front;
    front = front->link;//不删除多出的空表头结点
    while (front != nullptr) {
        p = front;
        front = front->link;
        delete p;
    }
    head->link = nullptr;
    front = rear = head;
}

template<class T>
bool LinkedQueue<T>::EnQueue(T x) {
//    linkNode<T>* p = new linkNode<T>;
    auto *p = new linkNode<T>;
    assert(p != nullptr);
    p->data = x;
    rear->link = p;
    rear = p;
    return true;
}

template<class T>
bool LinkedQueue<T>::DeQueue() {
    if (IsEmpty())
        return false;
    linkNode<T> *p = front->link;//跳过表头空结点
    front->link = p->link;
    delete p;
    return true;
}

template<class T>
bool LinkedQueue<T>::DeQueue(T &x) {
    if (IsEmpty())
        return false;
    linkNode<T> *p = front->link;//跳过表头空结点
    front->link = p->link;
    x = p->data;
    delete p;
    return true;
}

template<class T>
bool LinkedQueue<T>::getFront(T &x) const {
    if (IsEmpty())
        return false;
    x = front->link->data;
    return true;
}

template<class T>
int LinkedQueue<T>::getSize() const {
    linkNode<T> *p = front->link;
    int count = 0;
    while (p != nullptr) {
        count++;
        p = p->link;
    }
    return count;
}

template<class T>
void LinkedQueue<T>::output() const {
    linkNode<T>* p = front->link;
    while(p != nullptr){
        cout << p->data << " ";
        p = p->link;
    }
    cout << endl;
}


int main(){
    LinkedQueue<int> q1;
    cout << "q1.IsEmpty(): " << q1.IsEmpty() << endl;
    cout << "enQueue from 1 to 10..." << endl;
    q1.EnQueue(1);
    q1.EnQueue(2);
    q1.EnQueue(3);
    q1.EnQueue(4);
    q1.EnQueue(5);
    q1.EnQueue(6);
    q1.EnQueue(7);
    q1.EnQueue(8);
    q1.EnQueue(9);
    q1.EnQueue(10);
    cout << "q1.getSize(): " << q1.getSize() << endl;
    cout << "q1.output..." << endl;
    q1.output();

    cout << endl;
    cout << "q1.DeQueue() " << endl;
    q1.DeQueue();
    int x;
    q1.DeQueue(x);
    cout << "deQueue one more element,it is " << x << "." << endl;
    cout << "q1.output..." << endl;
    q1.output();

    cout << endl;
    cout << "q1.makeEmpty()... " << endl;
    q1.makeEmpty();
    cout << "q1.getSize(): " << q1.getSize() << endl;
    cout << "q1.output..." << endl;
    q1.output();

    cout << "enQueue 10 to 15" << endl;
    q1.EnQueue(10);
    q1.EnQueue(11);
    q1.EnQueue(12);
    q1.EnQueue(13);
    q1.EnQueue(14);
    q1.EnQueue(15);
    cout << "q1.output..." << endl;
    q1.output();
}