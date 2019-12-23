//
// Created by Dell on 2019/12/24.
//
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct cmp{
    bool operator ()(int &a,int &b){
        return a>b;//最小值优先
    }
};


template<class T>
class MinHeap {
public :
    MinHeap() = default;

    MinHeap(T a[], int n);

    ~MinHeap() = default;

    void Insert(T x);

    bool RemoveMin(T& x);

    bool IsEmpty();

    int GetSize();

private:
    priority_queue<T, vector<T>, cmp> pQueue;
};



template<class T>
MinHeap<T>::MinHeap(T *a, int n) {
    for(int i = 0; i < n; i++){
        pQueue.push(a[i]);
    }
}


template<class T>
void MinHeap<T>::Insert(T x) {
    pQueue.push(x);
}

template<class T>
bool MinHeap<T>::RemoveMin(T &x) {
    if(pQueue.empty())
        return false;
    x = pQueue.top();
    pQueue.pop();
    return true;
}

template<class T>
bool MinHeap<T>::IsEmpty() {
    return pQueue.empty();
}

template<class T>
int MinHeap<T>::GetSize() {
    return pQueue.size();
}


int main(){
    int test[10] = {9, 8, 3, 7, 1, 6, 0, 5, 2, 4};
    MinHeap<int> m1(test,10);
    m1.Insert(11);
    int x;
    cout << "m1.IsEmpty(): " << m1.IsEmpty() << endl;
    cout << "m1.GetSize(): " << m1.GetSize() << endl;
    while(!m1.IsEmpty()){
        m1.RemoveMin(x);
        cout << x << " ";
    }
    cout << endl;
    cout << "m1.GetSize(): " << m1.GetSize() << endl;
    cout << "m1.IsEmpty(): " << m1.IsEmpty() << endl;
}