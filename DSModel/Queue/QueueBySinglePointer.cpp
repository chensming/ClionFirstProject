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
        data = T(), link[0] = nullptr;
        link[1] = nullptr;
    }

    explicit linkNode(T x) {
        data = x, link[0] = nullptr;
        link[1] = nullptr;
    }
};

template<class T>
class QueueBySPointer {
public:
    QueueBySPointer();

    ~QueueBySPointer();

    void makeEmpty();

    void EnQueue(T x);

    bool DeQueue();

    bool DeQueue(T &x);

    bool getFront(T &x) const;

    int getSize() const;

    bool IsEmpty() { return rear->link[1] == rear; }

    void output() const;

private:
    linkNode<T> *rear;
};


template<class T>
QueueBySPointer<T>::QueueBySPointer() {
    rear = new linkNode<T>(-1);
    assert(rear != nullptr);
    rear->link[0] = rear->link[1] = rear;
}

template<class T>
QueueBySPointer<T>::~QueueBySPointer() {
    makeEmpty();
    delete rear;
}

template<class T>
void QueueBySPointer<T>::makeEmpty() {
    linkNode<T> *p = rear->link[1];
    linkNode<T> *del = nullptr;
    while (p != rear) {
        del = p;
        p = p->link[1];
        delete del;
    }
}

template<class T>
void QueueBySPointer<T>::EnQueue(T x) {
    auto *p = new linkNode<T>(x);
    p->link[1] = rear;
    p->link[0] = rear->link[0];
    rear->link[0] = p;
    p->link[0]->link[1] = p;
}

template<class T>
bool QueueBySPointer<T>::DeQueue() {
    if (IsEmpty())
        return false;
    linkNode<T>* del = rear->link[1];
    rear->link[1] = del->link[1];
    del->link[1]->link[0] = rear;
    delete del;
    return true;
}

template<class T>
bool QueueBySPointer<T>::DeQueue(T &x) {
    if (IsEmpty())
        return false;
    linkNode<T>* del = rear->link[1];
    rear->link[1] = del->link[1];
    del->link[1]->link[0] = rear;
    x = del->data;
    delete del;
    return true;
}

template<class T>
bool QueueBySPointer<T>::getFront(T &x) const {
    if (IsEmpty())
        return false;
    x = rear->link[1]->data;
    return true;
}

template<class T>
int QueueBySPointer<T>::getSize() const {
    int count = 0;
    linkNode<T>* p = rear->link[1];
    while(p != rear){
        count++;
        p = p->link[1];
    }
    return count;
}

template<class T>
void QueueBySPointer<T>::output() const {
    linkNode<T>* p = rear->link[1];
    while(p != rear){
        cout << p->data << " ";
        p = p->link[1];
    }
    cout << endl;
}


int main(){
    QueueBySPointer<int> q1;
    cout << "q1.IsEmpty(): " << q1.IsEmpty() << endl;
    cout << "q1.getSize(): " << q1.getSize() << endl;
    q1.EnQueue(1);
    q1.EnQueue(2);
    cout << "q1.IsEmpty(): " << q1.IsEmpty() << endl;
    q1.EnQueue(3);
    q1.EnQueue(4);
    q1.EnQueue(5);
    q1.EnQueue(6);
    q1.EnQueue(7);
    cout << "q1.getSize(): " << q1.getSize() << endl;
    q1.output();
    int x;
    q1.DeQueue();
    q1.DeQueue(x);
    cout << "x= " << x << endl;
    cout << "q1.IsEmpty(): " << q1.IsEmpty() << endl;
    cout << "q1.getSize(): " << q1.getSize() << endl;
    q1.output();

    cout << endl << "end of main" << endl;
}