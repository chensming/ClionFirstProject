//
// Created by Dell on 2019/12/22.
//


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;
const int maxWeight = 9999;

template<class T, class E>
class GraphBuildByMatrix {
public:
    GraphBuildByMatrix(const T *v, const E *m, int num);

    ~GraphBuildByMatrix();

    void showDest();

    void showMatrix();

private:
    T *vertexList;
    E **matrix;
    int numVertex;
};

template<class T, class E>
GraphBuildByMatrix<T, E>::GraphBuildByMatrix(const T *v, const E *m, int num) {
    numVertex = num;
    vertexList = new T[numVertex];
    matrix = new E *[numVertex];
    assert(vertexList != nullptr);
    assert(matrix != nullptr);

    //拷贝参数传来的数组过程
    int i, j;
    for (i = 0; i < numVertex; i++)
        matrix[i] = new E[numVertex];

    for (i = 0; i < numVertex; i++)
        vertexList[i] = v[i];
    for (i = 0; i < numVertex; i++)
        for (j = 0; j < numVertex; j++)
            matrix[i][j] = *(m + i * numVertex + j);
}

template<class T, class E>
GraphBuildByMatrix<T, E>::~GraphBuildByMatrix() {
    delete[] vertexList;
    delete[] matrix;
}

template<class T, class E>
void GraphBuildByMatrix<T, E>::showDest() {
    if (vertexList == nullptr || matrix == nullptr)
        return;
    for (int row = 0; row < numVertex; row++) {
        cout << "与编号为 " << row << ",其值为 " << vertexList[row] << " 的顶点相连的顶点: ";
        cout << "顶点值(编号, 权值)" << endl;
        for (int col = 0; col < numVertex; col++) {
            if (matrix[row][col] > 0 && matrix[row][col] < maxWeight) {
                cout << vertexList[col] << "(" << col << ", " << matrix[row][col] << ") ";
            }
        }
        cout << endl << endl;
    }
}

template<class T, class E>
void GraphBuildByMatrix<T, E>::showMatrix() {
    cout << "图的邻接矩阵: " << endl;
    cout << setw(8) << " ";
    for (int i = 0; i < numVertex; i++)
        cout << setw(8) << vertexList[i];
    cout << endl;
    for (int row = 0; row < numVertex; row++)
    {
        cout << setw(8) << vertexList[row];
        for (int col = 0; col < numVertex; col++)
        {
            cout << setw(8) << matrix[row][col];
        }
        cout << endl;
    }
    cout << endl << endl;
}


int main() {
    char ch[5] = {'A', 'B', 'C', 'D', 'E'};
    double m[5][5] = {
            0, 9999, 2, 3, 4,
            6, 0, 9999, 5, 4,
            7, 9999, 0, 3, 4,
            4, 5, 6, 0, 1,
            9999, 6, 9999, 4, 0
    };
    GraphBuildByMatrix<char, double> g1(ch, reinterpret_cast<const double *>(m), 5);
    g1.showDest();
    g1.showMatrix();
}