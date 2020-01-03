//
// Created by Dell on 2020/1/3.
//

#include <iostream>
#include <stack>

using namespace std;

template<class T>
struct test {
    T data1;
    T data2;
    test<T> *link;

    explicit test(test<T> *link1 = nullptr) :
            link(link1) { data1 = data2 = T(); }
};

int main() {
    stack<test<char>> st;
    test<char> t;
    for (int i = 0; i < 26; i++) {
        t.data1 = 'A' + i;
        t.data2 = 'a' + i;
        st.push(t);
    }
    while (!st.empty()) {
        t = st.top();
        st.pop();
        cout << "t.data1: " << t.data1;
        cout << " t.data2: " << t.data2 << endl;
    }
    cout << endl;
}
