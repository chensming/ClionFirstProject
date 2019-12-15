//
// Created by Dell on 2019/12/14.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct W{
    int data;
    char c;
};

template <class T>
bool cmp(const T&a, const T& b){
    return a.data < b.data;
}

template<class T>
void display(vector<T>& v){
    for(auto iter = v.begin(); iter < v.end(); iter++){
        cout << (*iter).data << "(" << (*iter).c << ") ";
    }
    cout << endl;
}

int main()
{
    vector<W> a = {{9,'j'},{6,'g'},{2,'c'},{4,'e'},{7,'h'},{0,'a'},{1,'b'},{8,'i'},{3,'d'},{5,'f'}};
    make_heap(a.begin(), a.end(), cmp<W>);
    sort_heap(a.begin(), a.end(), cmp<W>);

    display(a);

//    system("pause");
}