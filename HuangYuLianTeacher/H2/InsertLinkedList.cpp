//
// Created by Dell on 2019/12/26.
//
#include <iostream>

using namespace std;

template<class T>
struct linkNode {
    T data;
    linkNode<T> *link;

    explicit linkNode(T d) : data(d), link(nullptr) {}
};

template<class T>
linkNode<T> *buildLinkedList(T *a, int arraySize) {
    int i = 0;
    linkNode<T> *head = nullptr, *last = nullptr, *p = nullptr;
    head = new linkNode<T>(-1);
    last = head;
    while (i < arraySize) {
        p = new linkNode<T>(a[i]);
        last->link = p;
        last = last->link;
        i++;
    }
    return head;
}

template<class T>
void display(linkNode<T> *head) {
    linkNode<T> *p = head->link;
    cout << "the element of linkedList is :" << endl;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->link;
    }
    cout << endl;
}


template<class T>
void InsertLinkedList(linkNode<T> *ptr, T x) {
    linkNode<T> *p = ptr->link, *pre = ptr, *newNode = nullptr;
    while (p != nullptr && x > p->data) {
        pre = p;
        p = p->link;
    }
    newNode = new linkNode<T>(x);
    newNode->link = p;
    pre->link = newNode;
}




int main() {
    int size = 12;
    int temp[20] = {11, 22, 53, 65, 78, 95, 153, 245, 358, 468, 759, 846};
    linkNode<int> *link1 = buildLinkedList(temp, size);
    display(link1);
    cout << "insert..." << endl;
    InsertLinkedList(link1, 200);
    display(link1);
}