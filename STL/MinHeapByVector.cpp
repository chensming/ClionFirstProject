//
// Created by Dell on 2019/12/12.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<class T>
bool cmp(const int &a, const int &b) {
    return a < b;
}



template<class T>
void display(vector<T> &v) {
    for(auto iter = v.begin(); iter < v.end(); iter++)
    {
        cout << *iter << " ";
    }
    cout << endl;
}


int main() {
    vector<int> num = {9, 6, 2, 4, 7, 0, 1, 8};
    make_heap(num.begin(), num.end(), cmp<int>);
    cout << "make_heap(num.begin(), num.end(), cmp<int>);" << endl;
    display(num);

    sort_heap(num.begin(), num.end(), cmp<int>);
    cout << endl << "sort_heap(num.begin(), num.end(), cmp<int>);" << endl;
    display(num);

    num.push_back(3);
    num.push_back(5);
    cout << endl << "num.push_back(3);num.push_back(5);" << endl;
    display(num);

    make_heap(num.begin(), num.end(), cmp<int>);
    sort_heap(num.begin(), num.end(), cmp<int>);
    cout << endl << " sort_heap(num.begin(), num.end(), cmp<int>);" << endl;
    display(num);


    num.erase(num.begin());
    cout << endl << "num.erase(num.begin());" << endl;
    display(num);


//    system("pause");
}