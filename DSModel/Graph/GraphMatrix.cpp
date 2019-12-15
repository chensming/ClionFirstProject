//
// Created by Dell on 2019/12/15.
//
#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;
const int maxWeight = 9999;
const int DefaultVertices = 30;


template <class T, class E>
class Graphmtx
{
public:
    Graphmtx(int sz = DefaultVertices);
    ~Graphmtx()
    {
        delete[] verticesList;
        delete[] Edge;
    }
    //去顶点 i 的值，i不合理返回0
    T getValue(int i) {
        return i >= 0 && i <= numVertices ? verticesList[i] : 0;
    }
    E getWeight(int v1, int v2) {
        return v1 >= 0 && v1 <= numVertices && v2 >= 0 && v2 <= numVertices ? Edge[v1][v2] : 0;
    }
    int getFirstNeightBor(int v);
    int getNextNeighbor(int v, int w);
    bool insertVertex(const T vertex);
    bool insertEdge(int v1, int v2, E cost);
    bool removeVertex(int v);
    bool removeEdge(int v1, int v2);
    void DFS();
    void BFS();
    void showMatrix();
    void OuputGraphDest();


private:
    int maxVertices;
    int numVertices;
    int numEdges;
    T* verticesList;
    E** Edge;
    bool* visited;


    int getVertexPos(T Vertex)
    {
        for (int i = 0; i < numVertices; i++)
            if (verticesList[i] == Vertex)
                return i;
        return -1;
    }
    void DFS(int v);
};



template<class T, class E>
Graphmtx<T, E>::Graphmtx(int sz)
{
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    visited = 0;
    int i, j;
    verticesList = new T[maxVertices];
    Edge = (E * *) new E * [maxVertices];
    for (i = 0; i < maxVertices; i++)
    {
        Edge[i] = new E[maxVertices];
    }
    for (i = 0; i < maxVertices; i++)
        for (int j = 0; j < maxVertices; j++)
            Edge[i][j] = (i == j) ? 0 : maxWeight;
}


template<class T, class E>
int Graphmtx<T, E>::getFirstNeightBor(int v)
{
    if (v >= 0 &&v < numVertices) {
        for (int col = 0; col < numVertices; col++)
        {
            if (Edge[v][col] && Edge[v][col] < maxWeight)
                return col;
        }
    }
    return -1;
}









template<class T,class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w)
{
    if (v >= 0 && v < numVertices && w >=0 && w < numVertices)
    {
        for (int col = w + 1; col < numVertices; col++)
            if (Edge[v][col] && Edge[v][col] < maxWeight)
                return col;
    }
    return -1;
}




template<class T, class E>
bool Graphmtx<T, E>::insertVertex(const T vertex)
{
    if (numVertices == maxVertices)
        return false;
    verticesList[numVertices++] = vertex;
    return true;
}




template<class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost)
{
    if (v1 >= 0 && v1 < maxWeight && v2 >= 0 && v2 <= maxWeight)
    {
        Edge[v1][v2] = Edge[v2][v1] = cost;
        numEdges++;
        return true;
    }
    return false;
}




template<class T, class E>
bool Graphmtx<T, E>::removeVertex(int v)
{
    if (v < 0 || v >= numVertices)
        return false;
    if (numVertices == 1)
        return false;
    int i, j;
    verticesList[v] = verticesList[numVertices - 1];
    for (i = 0; i < numVertices; i++)
    {
        if (Edge[i][v] > 0 && Edge[i][v] < maxWeight)
            numEdges--;
    }
    for (i = 0; i < numVertices; i++)
    {
        Edge[i][v] = Edge[i][numVertices - 1];
    }
    for (j = 0; j < numVertices; j++)
        Edge[v][j] = Edge[numVertices - 1][j];
    numVertices--;
}



template<class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2)
{
    if (v1 >= 0 && v1 < maxVertices && v2 >= 0 && v2 < maxWeight)
    {
        Edge[v1][v2] = Edge[v2][v1] = maxWeight;
        numEdges--;
        return true;
    }
    return false;
}





template<class T, class E>
void Graphmtx<T, E>::DFS()
{
    int v0;
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;

    cout << "请输入深度优先遍历的出发点编号(从0到" << numVertices - 1 << "): ";
    cin >> v0;
    DFS(v0);
}



template<class T, class E>
void Graphmtx<T, E>::DFS(int v)
{
    visited[v] = true;
    cout << verticesList[v] << " ";
    for (int col = 0; col < numVertices; col++)
    {
        if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
        {
            if (!visited[col])
                DFS(col);
        }
    }
}


template<class T, class E>
void Graphmtx<T, E>::BFS()
{
    int v;
    queue<int> Q;
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;
    cout << "请输入广度优先遍历的出发点编号(从0到" << numVertices - 1 << "): ";
    cin >> v;
    if (v < 0 || v > numVertices - 1)
    {
        cout << "输入的编号有误" << endl;
        return;
    }
    Q.push(v);
    while (!Q.empty())
    {
        v = Q.front();
        Q.pop();
        if (!visited[v])
        {
            visited[v] = true;
            cout << verticesList[v] << " ";
            for (int col = 0; col < numVertices; col++)
            {
                if (Edge[v][col] > 0 && Edge[v][col] < maxWeight && !visited[col])
                {
                    Q.push(col);
                }
            }
        }
    }
}



template<class T, class E>
void Graphmtx<T, E>::showMatrix()
{
    cout << "图的邻接矩阵: " << endl;
    cout << setw(8) << " ";
    for (int i = 0; i < numVertices; i++)
        cout << setw(8) << verticesList[i];
    cout << endl;
    for (int row = 0; row < numVertices; row++)
    {
        cout << setw(8) << verticesList[row];
        for (int col = 0; col < numVertices; col++)
        {
            cout << setw(8) << Edge[row][col];
        }
        cout << endl;
    }
    cout << endl << endl;
}



template<class T, class E>
void Graphmtx<T, E>::OuputGraphDest()
{
    for (int row = 0; row < numVertices; row++)
    {
        cout << "与编号为 " << row << ",其值为 " << verticesList[row] << " 的顶点相连的顶点: ";
        cout << "顶点值(编号, 权值)" << endl;
        for (int col = 0; col < numVertices; col++)
        {
            if (Edge[row][col] > 0 && Edge[row][col] < maxWeight)
            {
                cout << verticesList[col] << "(" << col << ", " << Edge[row][col] << ") ";
            }
        }
        cout << endl << endl;
    }
}





int main()
{
    Graphmtx<char, double> a;
    a.insertVertex('a');
    a.insertVertex('b');
    a.insertVertex('c');
    a.insertVertex('d');
    a.insertVertex('e');

    a.insertEdge(0, 1, 2.7);
    a.insertEdge(0, 2, 4.1);
    a.insertEdge(0, 4, 8.8);
    a.insertEdge(1, 3, 3.2);
    a.insertEdge(1, 4, 8.0);
    a.insertEdge(2, 3, 6.7);
    a.insertEdge(3, 4, 5.4);


    a.showMatrix();
    a.OuputGraphDest();
/*
	cout << "删除边ae后" << endl << endl;
	a.removeEdge(0, 4);
	a.showMatrix();
	a.OuputGraphDest();
*/
/*
	cout << "删除点c后" << endl << endl;
	a.removeVertex(2);
	a.showMatrix();
	a.OuputGraphDest();
*/

    cout << "深度优先遍历..." << endl;
    a.DFS();
    cout << endl;

    cout << "广度优先遍历..." << endl;
    a.BFS();
    cout << endl;










    cout << endl;
}
