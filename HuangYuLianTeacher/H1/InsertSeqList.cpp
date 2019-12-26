//
// Created by Dell on 2019/12/26.
//
#include <iostream>
using namespace std;

template<class T>
void InsertSeqList(T *a, int arraySize, T x) {
    int i = arraySize - 1;
    while(a[i] > x) {//方向很有意思
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = x;
}

int main() {
    int size = 12;
    int temp[20] = {11, 22, 53, 65, 78, 95, 153, 245, 358, 468, 759, 846};
    InsertSeqList(temp, size, 300);
    for(int i = 0; i < size + 1; i++){
        cout << temp[i] << " ";
    }
}