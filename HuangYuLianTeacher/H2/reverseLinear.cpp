//
// Created by Dell on 2019/12/26.
//

#include <iostream>
using namespace std;

template<class T>
void swap(T *a, int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}


template<class T>
void reverseSeqList(T *a, int arraySize) {
    for (int i = 0; i <= (arraySize - 1) / 2; i++) {
        swap(a, i, arraySize - 1 - i);
    }
}

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
void reverseLinkedListNonRecursion(linkNode<T> *head) {
    linkNode<T> *p = head->link, *pre = nullptr, *temp;
    while (p != nullptr) {
        temp = p->link;
        p->link = pre;
        pre = p;
        p = temp;
    }
    head->link = pre;
}

template<class T>
linkNode<T> *reverseLinkedListRecursion(linkNode<T> *head, linkNode<T> *pre) {
    //初始时head为头结点，pre为nullptr
    //之后head继续往后移动,
    if (head == nullptr)
        return pre;
    linkNode<T> *p = head;
    head = head->link;
    p->link = pre;
    pre = p;
    return reverseLinkedListRecursion(head, pre);
}


int main() {
    int test[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//    reverseSeqList(test, 10);
//    for (int i = 0; i < 10; i++)
//        cout << *(test + i) << " ";
    cout << endl;
    linkNode<int> *link1 = buildLinkedList(test, 10);
    display(link1);
    cout << "reverse..." << endl;
    reverseLinkedListNonRecursion(link1);
    display(link1);
    linkNode<int> *pre = nullptr;
    link1->link = reverseLinkedListRecursion(link1->link, pre);
    display(link1);
}