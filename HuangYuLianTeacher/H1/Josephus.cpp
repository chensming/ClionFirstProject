//
// Created by Dell on 2019/12/26.
//
#include <iostream>

using namespace std;

//personNum为一圈中的人数，startNum为从第几个人开始，stepNum为每次数多少人
void Josephus(int personNum, int startNum, int stepNum) {
    int people[personNum];
    for (int i = 0; i < personNum; i++)
        people[i] = i + 1;
    int i = 0, j = startNum - 1;
    while (i < personNum - 1) {
        while (people[(j + stepNum) % personNum] == 0)
            j++;
        j = (j + stepNum) % personNum;
        people[j] = 0;

        i++;
    }
    for (i = 0; i < personNum; i++) {
        if (people[i] != 0) {
            cout << "the winner is the " << i + 1 << " person." << endl;
            break;
        }
    }
}


int main() {
    Josephus(10, 5, 3);
}