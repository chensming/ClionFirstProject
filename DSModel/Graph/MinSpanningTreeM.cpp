//
// Created by Dell on 2019/12/14.
//

//
// Created by Dell on 2019/12/14.
//

#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;
const int maxWeight = 9999;
const int DefaultVertices = 30;
const int DefaultUFsetsSize = 30;


//最小生成树那用到了
template<class T, class E>
struct MSTEdgeNode {
    int tail, head;
    E cost;
};

template<class T, class E>
bool cmp(const MSTEdgeNode<T, E>& a, const MSTEdgeNode<T, E>& b) {
    return a.cost < b.cost;  //升序
}


class UFsets {
public:
    UFsets(int sz = DefaultUFsetsSize);

    ~UFsets() { delete[] parent; }

    //root2直接合并到root1
    void Union(int root1, int root2);

    int Find(int x);

    void WeightedUnion(int root1, int root2);

    void PrintParentList();

private:
    int* parent;
    int size;
};


template<class T, class E>
class Graphmtx {
public:
    Graphmtx(int sz = DefaultVertices);

    ~Graphmtx() {
        delete[] verticesList;
        delete[] Edge;
    }

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

    void showMatrix();

    void OuputGraphDest();

    void KruskalMinTree();

    void PrimMinTree(int v0);

    void Dijkstra();

    void printMinTree();


private:
    int maxVertices;
    int numVertices; // ??????
    int numEdges;
    T* verticesList;
    E** Edge;
    MSTEdgeNode<T, E>* mst;//最小生成树数组


    int getVertexPos(T Vertex) {
        for (int i = 0; i < numVertices; i++)
            if (verticesList[i] == Vertex)
                return i;
        return -1;
    }
};


////////////////////////////////////////////////////////////////////////////
//UFsets start

UFsets::UFsets(int sz) {
    size = sz;
    parent = new int[size];
    for (int i = 0; i < size; i++)
        parent[i] = -1;
}


void UFsets::Union(int root1, int root2) {
    int x = root1;
    while (parent[x] > 0)
        x = parent[x];
    parent[x] = parent[x] + parent[root2];
    parent[root2] = root1;
}


int UFsets::Find(int x) {
    if (parent[x] < 0)
        return x;
    else
        return Find(parent[x]);
}


void UFsets::WeightedUnion(int root1, int root2) {
    int r1 = Find(root1);
    int r2 = Find(root2);
    int temp = -1;
    if (r1 != r2)
        temp = parent[r1] + parent[r2];
    //r1的结点多
    if (parent[r1] < parent[r2]) {
        parent[r1] = temp;
        parent[r2] = r1;
    }
    else {
        parent[r2] = temp;
        parent[r1] = r2;
    }

}


void UFsets::PrintParentList() {
    for (int i = 0; i < size; i++)
        cout << i << "(" << parent[i] << ") ";
    cout << endl;
}



//UFsets end
///////////////////////////////////////////////////////////////////////////////


template<class T, class E>
Graphmtx<T, E>::Graphmtx(int sz) {
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    mst = 0;
    int i, j;
    verticesList = new T[maxVertices];
    Edge = (E * *) new E * [maxVertices];
    for (i = 0; i < maxVertices; i++) {
        Edge[i] = new E[maxVertices];
    }
    for (i = 0; i < maxVertices; i++)
        for (j = 0; j < maxVertices; j++)
            Edge[i][j] = (i == j) ? 0 : maxWeight;
}


template<class T, class E>
int Graphmtx<T, E>::getFirstNeightBor(int v) {
    if (v >= 0 && v < numVertices) {
        for (int col = 0; col < numVertices; col++) {
            if (Edge[v][col] && Edge[v][col] < maxWeight)
                return col;
        }
    }
    return -1;
}


template<class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w) {
    if (v >= 0 && v < numVertices && w >= 0 && w < numVertices) {
        for (int col = w + 1; col < numVertices; col++)
            if (Edge[v][col] && Edge[v][col] < maxWeight)
                return col;
    }
    return -1;
}


template<class T, class E>
bool Graphmtx<T, E>::insertVertex(const T vertex) {
    if (numVertices == maxVertices)
        return false;
    verticesList[numVertices++] = vertex;
    return true;
}


template<class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost) {
    if (v1 >= 0 && v1 < maxWeight && v2 >= 0 && v2 <= maxWeight) {
        Edge[v1][v2] = Edge[v2][v1] = cost;
        numEdges++;
        return true;
    }
    return false;
}


template<class T, class E>
bool Graphmtx<T, E>::removeVertex(int v) {
    if (v < 0 || v >= numVertices)
        return false;
    if (numVertices == 1)
        return false;
    int i, j;
    verticesList[v] = verticesList[numVertices - 1];
    for (i = 0; i < numVertices; i++) {
        if (Edge[i][v] > 0 && Edge[i][v] < maxWeight)
            numEdges--;
    }
    for (i = 0; i < numVertices; i++) {
        Edge[i][v] = Edge[i][numVertices - 1];
    }
    for (j = 0; j < numVertices; j++)
        Edge[v][j] = Edge[numVertices - 1][j];
    numVertices--;
}


template<class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2) {
    if (v1 >= 0 && v1 < maxVertices && v2 >= 0 && v2 < maxWeight) {
        Edge[v1][v2] = Edge[v2][v1] = maxWeight;
        numEdges--;
        return true;
    }
    return false;
}


template<class T, class E>
void Graphmtx<T, E>::showMatrix() {
    cout << "图的邻接矩阵: " << endl;
    cout << setw(8) << " ";
    for (int i = 0; i < numVertices; i++)
        cout << setw(8) << verticesList[i];
    cout << endl;
    for (int row = 0; row < numVertices; row++) {
        cout << setw(8) << verticesList[row];
        for (int col = 0; col < numVertices; col++) {
            cout << setw(8) << Edge[row][col];
        }
        cout << endl;
    }
    cout << endl << endl;
}


template<class T, class E>
void Graphmtx<T, E>::OuputGraphDest() {
    for (int row = 0; row < numVertices; row++) {
        cout << "与编号为 " << row << ",其值为 " << verticesList[row] << " 的顶点相连的顶点: ";
        cout << "顶点值(编号, 权值)" << endl;
        for (int col = 0; col < numVertices; col++) {
            if (Edge[row][col] > 0 && Edge[row][col] < maxWeight) {
                cout << verticesList[col] << "(" << col << ", " << Edge[row][col] << ") ";
            }
        }
        cout << endl << endl;
    }
}


//int numVertices 顶点数
//int numEdges 边数
template<class T, class E>
void Graphmtx<T, E>::KruskalMinTree() {
    if (mst != 0)
        delete[] mst;
    mst = new MSTEdgeNode<T, E>[numVertices];


    MSTEdgeNode<T, E> p, leastNode;
    vector<MSTEdgeNode<T, E>> hp;
    UFsets ufset(numVertices);



    //初始化工作
    for (int u = 0; u < numVertices; u++)
        for (int v = u + 1; v < numVertices; v++)  //无向图邻接矩阵对称
            if (Edge[u][v] < maxWeight) {
                p.tail = u;
                p.head = v;
                p.cost = Edge[u][v];
                hp.push_back(p);
            }
    make_heap(hp.begin(), hp.end(), cmp<T, E>);
    sort_heap(hp.begin(), hp.end(), cmp<T, E>);

    int count = 1;//最小生成树边数计数
    while (count < numVertices) {
        leastNode = hp.front();
        hp.erase(hp.begin());

        int u = ufset.Find(leastNode.tail);
        int v = ufset.Find(leastNode.head);
        if (u != v) //判断有无构成环路
        {
            ufset.Union(u, v);
            mst[count - 1] = leastNode;
            cout << leastNode.tail << "->" << leastNode.head << "(" << leastNode.cost << ") ";
            count++;
        }
    }
    if (count == numVertices) {
        cout << endl << "最小生成树生成" << endl;
    }
}


template<class T, class E>
void Graphmtx<T, E>::PrimMinTree(int v0) {
    delete mst;
    mst = new MSTEdgeNode<T, E>[numVertices];


    int v = v0;
    vector<MSTEdgeNode<T, E>> hp;
    MSTEdgeNode<T, E> temp;
    temp.tail = v;

    Edge[v][v] = -1;
    for(int col = 0; col < numVertices; col++) {
        temp.head = col;
        temp.cost = Edge[v][col];
        hp.push_back(temp);
    }
    make_heap(hp.begin(), hp.end(), cmp<T, E>);
    sort_heap(hp.begin(), hp.end(), cmp<T, E>);


    int count = 1;
    while (count < numVertices) {
        temp = hp.front();
        hp.erase(hp.begin());
        if (Edge[temp.head][temp.head] != -1) {
            Edge[temp.head][temp.head] = -1;
            mst[count - 1] = temp;
            temp.tail = temp.head;
            for(int col = 0; col < numVertices; col++) {
                temp.head = col;
                temp.cost = Edge[temp.tail][col];
                hp.push_back(temp);
            }
            make_heap(hp.begin(), hp.end(), cmp<T, E>);
            sort_heap(hp.begin(), hp.end(), cmp<T, E>);
            count++;
        }
    }
    if (count == numVertices)
        cout << "最小生成树生成" << endl;
    for(int row = 0; row < numVertices; row++)
        for(int col = 0; col < numVertices; col++)
            if(row == col)
                Edge[col][col] = 0;
}


template<class T, class E>
void Graphmtx<T, E>::Dijkstra() {
    int v0;
    E* dist = new E[numVertices];
    bool* visited = new bool[numVertices];
    int pos;


    cout << "请输入出发点编号 0至" << numVertices - 1 << endl;
    cin >> v0;

    for (int i = 0; i < numVertices; i++)
        dist[i] = Edge[v0][i];
    visited[v0] = true;
    for (int i = 0; i < numVertices - 1; i++) {
//        int min = maxWeight;
//        for (int k = 0; k < numVertices; k++) {
//            if (visited = false && dist[k] < min) {
//                pos = k;
//                min = dist[k];
//            }
            E min = maxWeight;
            for(int k = 0; k < numVertices; k++){
                if(!visited[k] && dist[k] < min){
                    pos = k;
                    min = dist[k];
                }
            visited[pos] = 1;
            for (int j = 0; j < numVertices; j++) {
                if (!visited[j] && Edge[pos][j] + min < dist[j])
                    dist[j] = Edge[pos][j] + min;
            }

        }
    }

    cout << verticesList[v0] << "到其他点的最短距离分别为" << endl;
    for(int i = 0; i < numVertices; i++)
        cout << "To--"<< verticesList[i] << ":"<<dist[i] << "  ";


    delete[] dist;
    delete[] visited;
}


template<class T, class E>
void display(vector<MSTEdgeNode<T, E>>& v)//使用vector迭代器遍历
{
    //vector<MSTEdgeNode<T, E> >::iterator iter;
    for (auto iter = v.begin(); iter < v.end(); iter++) {
        cout << (*iter).tail << "->" << (*iter).head << (*iter).cost << endl;
    }
    cout << endl << endl;
}


template<class T, class E>
void Graphmtx<T, E>::printMinTree() {
    if (mst == 0) {
        cout << "最小生成树为空" << endl;
        return;
    }
    for (int i = 0; i < numVertices - 1; i++)
        cout << mst[i].tail << "->" << mst[i].head << "(" << mst[i].cost << ")" << endl;
}



int main() {
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


    //    cout << endl;
    //    a.KruskalMinTree();
    //    a.printMinTree();
    //
    //    cout << endl;
    //    a.PrimMinTree();
    //    a.printMinTree();
    cout << endl << "KruskalMinTree: " << endl;
    a.KruskalMinTree();

    cout << endl << "Prim: " << endl;
    a.PrimMinTree(0);
    a.printMinTree();
//    a.showMatrix();

    cout << endl << "Dijkstra: " << endl;
    a.Dijkstra();
//    a.showMatrix();

    cout << endl;
}