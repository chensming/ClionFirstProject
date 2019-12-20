//
// Created by Dell on 2019/12/19.
//
#include <iostream>

using namespace std;
const int DefaultMaxSize = 50;

template<class T>
class SeqQueue {
public:
    explicit SeqQueue(int sz = DefaultMaxSize);

    ~SeqQueue();

    bool EnQueue(T x);

    bool DeQueue();

    bool DeQueue(T &x);

    bool getFront(T &x);

    void makeEmpty();

    bool IsEmpty() const;

    bool IsFull() const;

    int getSize() const;

    void output() const;

private:
    int rear, front;
    T *elements;
    int maxSize;
};

template<class T>
SeqQueue<T>::SeqQueue(int sz) {
    front = rear = 0;
    maxSize = sz;
    elements = new T[maxSize];
    if (elements == nullptr) {
        cerr << "分配内存错误" << endl;
        exit(1);
    }
}

template<class T>
SeqQueue<T>::~SeqQueue() {
    if (elements != nullptr)
        delete[] elements;
}

template<class T>
bool SeqQueue<T>::EnQueue(T x) {
    if (IsFull())
        return false;
    elements[rear] = x;
    rear = (rear + 1) % maxSize;
    return true;
}

template<class T>
bool SeqQueue<T>::DeQueue() {
    if (IsEmpty())
        return false;
    front = (front + 1) % maxSize;//出队靠对头移动
    return true;
}

template<class T>
bool SeqQueue<T>::DeQueue(T &x) {
    if (IsEmpty())
        return false;
    x = elements[front];
    front = (front + 1) % maxSize;
    return true;
}

template<class T>
bool SeqQueue<T>::getFront(T &x) {
    if (IsEmpty())
        return false;
    x = elements[front];
    return true;
}

//只是让栈逻辑为空而已，没有破话空间结构
template<class T>
void SeqQueue<T>::makeEmpty() {
    front = rear = 0;
}

template<class T>
bool SeqQueue<T>::IsEmpty() const {
    return front == rear;
}

template<class T>
bool SeqQueue<T>::IsFull() const {
    return (rear + 1) % maxSize == front;
}


template<class T>
int SeqQueue<T>::getSize() const {
    return (rear - front + maxSize) % maxSize;
}


template<class T>
void SeqQueue<T>::output() const {
    cout << "from front to rear(先进靠右边)" << endl;
    for(int i = front; i != rear; i = (i + 1) % maxSize)
        cout << elements[i] << " ";
    cout << endl;
}


int main() {
    SeqQueue<int> s1;
    cout << "s1.IsEmpty(): " << s1.IsEmpty() << endl;
    cout << "s1.IsFull(): " << s1.IsFull() << endl;
    cout << "EnQueue 1 to 10 ..." << endl;
    s1.EnQueue(1);
    s1.EnQueue(2);
    s1.EnQueue(3);
    s1.EnQueue(4);
    s1.EnQueue(5);
    s1.EnQueue(6);
    s1.EnQueue(7);
    s1.EnQueue(8);
    s1.EnQueue(9);
    s1.EnQueue(10);
    cout << "s1.getSize(): " << s1.getSize() << endl;
    s1.output();

    cout << "s1.DeQueue()..." << endl;
    s1.DeQueue();
    int x;
    s1.DeQueue(x);
    cout << "DeQueue one more element, it is " << x << "."<< endl;
    s1.output();
}