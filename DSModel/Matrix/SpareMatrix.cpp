//
// Created by Dell on 2019/12/18.
//
#include <iostream>
#include <iomanip>

using namespace std;

template<class T>
struct MatrixUnit {
    int row;
    int col;
    T value;
    MatrixUnit *link;

    MatrixUnit() : row(-1), col(-1), value(0), link(nullptr) {}
};

template<class T>
struct Unit {
    int row;
    int col;
    T value;
};


template<class T>
class SpareMatrix {
public:

    SpareMatrix(const T *m, int r, int c);

    ~SpareMatrix();

    void print();

    void printMatrix();

    void printLinearMatrix();

    void printLinear();

    void tranLinearMatrix();

private:
    MatrixUnit<T> *matrixList; //存放存进来的矩阵链表
    Unit<T> *tranMatrixList; //存放转置的矩阵
    int currentSize;
    int row;
    int col;
};


template<class T>
SpareMatrix<T>::SpareMatrix(const T *m, int r, int c) {
    matrixList = nullptr;
    currentSize = 0;
    tranMatrixList = nullptr;
    MatrixUnit<T> *p;
    row = r;
    col = c;

    MatrixUnit<T> *last = nullptr;
    p = new MatrixUnit<T>;
    //                头插法,浪费一个空间使得循环的算法统一起来
    p->link = matrixList;
    matrixList = p;
    last = matrixList;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            if (*((m + i * c) + j) != 0) {
                p = new MatrixUnit<T>;
                p->row = i;
                p->col = j;
                p->value = *((m + i * c) + j);
                last->link = p;
                last = p;
                currentSize++;
            }
        }
}

template<class T>
SpareMatrix<T>::~SpareMatrix() {
    if (matrixList != nullptr)
        delete[] matrixList;
    if (tranMatrixList != nullptr)
        delete[] tranMatrixList;
}

template<class T>
void SpareMatrix<T>::print() {
    if (matrixList == nullptr) {
        cout << "矩阵为空" << endl;
        return;
    }
    MatrixUnit<T> *p = matrixList->link;
    //跳过浪费空间的表头结点
    cout << "矩阵元素表(row, col, value)" << endl;
    while (p != nullptr) {
        cout << "(" << p->row << ", " << p->col << ", " << p->value << ") ";
        p = p->link;
    }
    cout << endl;
}

template<class T>
void SpareMatrix<T>::printMatrix() {
    if (matrixList == nullptr || matrixList->link == nullptr) {
        cout << "矩阵为空" << endl;
        return;
    }
    MatrixUnit<T> *p = matrixList->link;
    double showMatrix[row][col];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            showMatrix[i][j] = 0.0;
    while (p != nullptr) {
        showMatrix[p->row][p->col] = p->value;
        p = p->link;
    }
    cout << "稀疏矩阵元素如下" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            cout << setw(4) << showMatrix[i][j];
        cout << endl;
    }
}


template<class T>
void SpareMatrix<T>::printLinearMatrix() {
    if (tranMatrixList == nullptr) {
        cout << "转置矩阵矩阵为空" << endl;
        return;
    }
    int i, j;
    double showMatrix[row][col];
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            showMatrix[i][j] = 0.0;
    for (i = 0; i < currentSize; i++) {
        showMatrix[tranMatrixList[i].row][tranMatrixList[i].col] = tranMatrixList[i].value;
    }
    cout << "转置矩阵元素如下" << endl;
    for (i = 0; i < row; i++){
        for (j = 0; j < col; j++)
            cout << setw(4) << showMatrix[i][j];
        cout << endl;
    }


    cout << endl;
}


template<class T>
void SpareMatrix<T>::printLinear() {
    if (tranMatrixList == nullptr) {
        cout << "转置矩阵矩阵为空" << endl;
        return;
    }
    cout << "转置矩阵元素表(row, col, value)" << endl;
    for (int i = 0; i < currentSize; i++) {
        cout << "(" << tranMatrixList[i].row << "," << tranMatrixList[i].col << ",";
        cout << tranMatrixList[i].value << ") ";
    }
    cout << endl;
}


template<class T>
void SpareMatrix<T>::tranLinearMatrix() {
    if (tranMatrixList != nullptr)
        delete[] tranMatrixList;
    if (matrixList == nullptr || matrixList->link == nullptr) {
        cout << "矩阵为空" << endl;
        return;
    }
    MatrixUnit<T> *p = matrixList->link;
    tranMatrixList = new Unit<T>[currentSize];
    int rNum[row], rStart[row];
    for (int i = 0; i < row; i++)
        rNum[i] = 0;
    while (p != nullptr) {
        rNum[p->col]++;
        p = p->link;
    }

    rStart[0] = 0;
    for (int i = 1; i < row; i++) {
        rStart[i] = rStart[i - 1] + rNum[i - 1];
    }
    int j;
    p = matrixList->link;
    while (p != nullptr) {
        j = p->col;
        tranMatrixList[rStart[j]].row = j;
        tranMatrixList[rStart[j]].col = p->row;
        tranMatrixList[rStart[j]].value = p->value;
        rStart[j]++;
        p = p->link;
    }
}


int main() {
    int *p;
    int test[5][5] = {1, 0, 0, 2, 0,
                      0, 7, 0, 0, 0,
                      6, 0, 0, 8, 0,
                      0, 0, 0, 0, 5,
                      0, 2, 0, 0, 0};
    SpareMatrix<int> a((int *) test, 5, 5);
    a.print();
    a.printMatrix();
    a.tranLinearMatrix();
//    a.printLinear();
    a.printLinearMatrix();
    cout << endl;
}