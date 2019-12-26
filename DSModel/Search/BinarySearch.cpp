//
// Created by Dell on 2019/12/24.
//

#include <iostream>
using  namespace std;

int BinarySearch(const int a[], int n, int x){
    int low = 0, high = n - 1, mid;
    while(low <= high){
        mid = (low + high) / 2;
        if(a[mid] == x)
            return mid;
        else if(a[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; //没找到
}


int main(){
 int test[10] = {10, 22, 35, 48, 67, 81, 94, 105, 107, 150};
 int x = 70;
 cout << "exit? " << BinarySearch(test, 10, x) << endl;
}