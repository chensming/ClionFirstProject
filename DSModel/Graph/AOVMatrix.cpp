//
// Created by Dell on 2019/12/22.
//

#include <iostream>
#include <iomanip>

using namespace std;
const int maxWeight = 9999;
const int DefaultMaxVertex = 50;


//有向图
template<class T, class E>
class AOVGraphM {
public:
    explicit AOVGraphM(int sz = DefaultMaxVertex);

    ~AOVGraphM();

    bool InsertVertex(const T &vertex);

    bool InsertEdge(int v1, int v2, E weight);

    void showMatrix();

    bool TopologicalSort();

    void printToPoList();

private:
    int numVertex;
    int maxVertex;
    int numEdge;

    T *vertexList;
    E **Edge;
    int *ToPoList;
};

template<class T, class E>
AOVGraphM<T, E>::AOVGraphM(int sz) {
    maxVertex = (sz > DefaultMaxVertex) ? sz : DefaultMaxVertex;
    vertexList = new T[maxVertex];
    numVertex = 0;
    numEdge = 0;
    ToPoList = nullptr;

    Edge = new E *[maxVertex];
    for (int i = 0; i < maxVertex; i++)
        Edge[i] = new E[maxVertex];
    for (int i = 0; i < maxVertex; i++)
        for (int j = 0; j < maxVertex; j++)
            Edge[i][j] = (i == j) ? 0 : maxWeight;
}

template<class T, class E>
AOVGraphM<T, E>::~AOVGraphM() {
    if (vertexList != nullptr)
        delete[] vertexList;
    if (Edge != nullptr)
        delete[] Edge;
    if (ToPoList != nullptr)
        delete[] ToPoList;
}

template<class T, class E>
bool AOVGraphM<T, E>::InsertVertex(const T &vertex) {
    if (numVertex == maxVertex)
        return false;
    vertexList[numVertex++] = vertex;
    return true;
}

template<class T, class E>
bool AOVGraphM<T, E>::InsertEdge(int v1, int v2, E weight) {
    if (v1 < 0 || v1 >= maxVertex || v2 < 0 || v2 >= maxVertex)
        return false;
    Edge[v1][v2] = weight;
    return true;
}

template<class T, class E>
void AOVGraphM<T, E>::showMatrix() {
    cout << "图的邻接矩阵: " << endl;
    cout << setw(8) << " ";
    for (int i = 0; i < numVertex; i++)
        cout << setw(8) << vertexList[i];
    cout << endl;
    for (int row = 0; row < numVertex; row++) {
        cout << setw(8) << vertexList[row];
        for (int col = 0; col < numVertex; col++) {
            cout << setw(8) << Edge[row][col];
        }
        cout << endl;
    }
    cout << endl << endl;
}

template<class T, class E>
bool AOVGraphM<T, E>::TopologicalSort() {
    if (ToPoList != nullptr)
        delete[] ToPoList;
    ToPoList = new int[numVertex];

    int top = -1, i, v, j;
//    这里用矩阵对角线的位置来代替
//    int count[numVertex];
//    for(int i = 0; i < numVertex; i++)
//        count[i] = 0;

//    初始化工作
    for (i = 0; i < numVertex; i++)
        for (j = 0; j < numVertex; j++)
            if (Edge[j][i] < maxWeight && i != j)
                Edge[i][i]++;

    //找到入度为0的点
    for (i = 0; i < numVertex; i++)
        if (Edge[i][i] == 0) { //进栈
            Edge[i][i] = top;
            top = i;
        }

    //进行numVertex - 1次，i 在这里是计数器的作用
    for (i = 0; i < numVertex; i++) {
        //找不到入度为0的点并且循环没退出，证明有回路
        if (top == -1) {
            delete[] ToPoList;
            cout << "网络中有回路" << endl;
            //恢复一下对角线矩阵
            for(i = 0; i < numVertex; i++)
                Edge[i][i] = 0;
            cout << endl;
            return false;
        } else {
            v = top;
            top = Edge[top][top];
            cout << vertexList[v] << " ";
            ToPoList[i] = v;
            for (j = 0; j < numVertex; j++)
                if (Edge[v][j] < maxWeight && v != j) {
                    Edge[j][j]--;
                    if (Edge[j][j] == 0) { //进栈
                        Edge[j][j] = top;
                        top = j;
                    }
                }
        }
    }

    //恢复一下对角线矩阵
    for(i = 0; i < numVertex; i++)
        Edge[i][i] = 0;
    cout << endl;
    return true;
}

template<class T, class E>
void AOVGraphM<T, E>::printToPoList() {
    if(ToPoList == nullptr)
        return;
    cout << "ToPoList: " << endl;
    for(int i = 0; i < numVertex; i++)
        cout << ToPoList[i] << "(" << vertexList[ToPoList[i]] << ") ";
    cout << endl;
}


int main() {
    AOVGraphM<char, double> a1;
    a1.InsertVertex('A');
    a1.InsertVertex('B');
    a1.InsertVertex('C');
    a1.InsertVertex('D');
    a1.InsertVertex('E');
    a1.InsertVertex('F');
    a1.InsertVertex('G');
    a1.InsertVertex('H');
    a1.InsertVertex('I');

    a1.InsertEdge(0, 2, 1);
    a1.InsertEdge(0, 7, 1);
    a1.InsertEdge(1, 2, 1);
    a1.InsertEdge(1, 3, 1);
    a1.InsertEdge(1, 4, 1);
    a1.InsertEdge(2, 3, 1);
    a1.InsertEdge(3, 5, 1);
    a1.InsertEdge(3, 6, 1);
    a1.InsertEdge(4, 5, 1);
    a1.InsertEdge(7, 8, 1);
    a1.InsertEdge(8, 6, 1);

    a1.TopologicalSort();
    a1.printToPoList();
    a1.showMatrix();

    cout << endl;
}