//
// Created by Dell on 2019/12/20.
//

#include <iostream>

using namespace std;

template<class T>
struct linkNode {
    T data;
    linkNode *link;
};


template<class T>
class LinkedStack {
public:
    LinkedStack();

    ~LinkedStack();

    void makeEmpty();

    void Push(const T x);

    bool Pop();

    bool Pop(T &x);

    bool getTop(T &x);

    bool IsEmpty() const;

    int getSize() const;

    void output();

private:
    linkNode<T> *top;
};

template<class T>
LinkedStack<T>::LinkedStack() {
    top = nullptr;
}


template<class T>
LinkedStack<T>::~LinkedStack() {
    makeEmpty();
}

template<class T>
void LinkedStack<T>::makeEmpty() {
    linkNode<T> *p;
    while (top != nullptr) {
        p = top;
        top = top->link;
        delete p;
    }
}

template<class T>
void LinkedStack<T>::Push(const T x) {
//    linkNode<T>* p = new linkNode<T>;
    auto *p = new linkNode<T>;
//    if(p == nullptr)
//    {
//        cerr<<"·ÖÅäÈÕÄÚ´æ´íÎó" << endl;
//        exit(1);
//    }
    p->data = x;
    p->link = top;
    top = p;
}

template<class T>
bool LinkedStack<T>::Pop() {
    if (IsEmpty())
        return false;
    linkNode<T> *p = top;
    top = top->link;
    delete p;
    return true;
}

template<class T>
bool LinkedStack<T>::Pop(T &x) {
    if (IsEmpty())
        return false;
    linkNode<T> *p = top;
    top = top->link;
    x = p->data;
    delete p;
    return true;
}

template<class T>
bool LinkedStack<T>::getTop(T &x) {
    if (IsEmpty())
        return false;
    x = top->data;
    return true;
}

template<class T>
bool LinkedStack<T>::IsEmpty() const {
    return top == nullptr;
}

template<class T>
int LinkedStack<T>::getSize() const {
    linkNode<T> *p = top;
    int count = 0;
    while (p != nullptr) {
        count++;
        p = p->link;
    }
    return count;
}

template<class T>
void LinkedStack<T>::output() {
    linkNode<T> *p = top;
    cout << "from top to bottom..." << endl;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->link;
    }
    cout << endl;
}


int main() {
    LinkedStack<int> s1;
    cout << "s1.IsEmpty(): " << s1.IsEmpty() << endl;
    cout << "push 1 to 10..." << endl;
    s1.Push(1);
    s1.Push(2);
    s1.Push(3);
    s1.Push(4);
    s1.Push(5);
    s1.Push(6);
    s1.Push(7);
    s1.Push(8);
    s1.Push(9);
    s1.Push(10);
    s1.output();
    cout << "s1.getSize: " << s1.getSize() << endl;
    cout << "pop 10..." << endl;
    s1.Pop();
    int x;
    s1.Pop(x);
    cout <<"pop one more elements, it is " << x << endl;
    cout << endl;
    s1.output();
}