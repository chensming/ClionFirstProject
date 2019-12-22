//
// Created by Dell on 2019/12/22.
//

#ifndef FIRSTPROJECT_MYCLOCK_H
#define FIRSTPROJECT_MYCLOCK_H

#include <ctime>
#include <iostream>
using namespace std;

class myClock {
public:
    void start() {
        cout << "开始计时" << endl;
        t1 = clock();
    }

    void end() {
        t2 = clock();
        cout << "经过时间 " << (double) (t2 - t1) / 1000 << "s" << endl;
        cout << endl;
    }

private:
    long t1;
    long t2;
};

#endif //FIRSTPROJECT_MYCLOCK_H
