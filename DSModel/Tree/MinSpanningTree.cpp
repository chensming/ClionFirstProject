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


//点的值类型为T，边的权值类型为E
template<class T, class E>
struct MSTEdgeNode
{
    int tail, head;  //点的编号
    E cost; //权值
};

template<class T,class E>
bool cmp(const MSTEdgeNode<T, E>& a, const MSTEdgeNode<T, E>& b)
{
    return a.cost < b.cost;  //升序
}


class UFsets {
public:
    UFsets(int sz = DefaultUFsetsSize);
    ~UFsets() { delete[] parent; }
    //不管结点多少，就是把root1作为新树的根
    void Union(int root1, int root2);
    int Find(int x);
    void WeightedUnion(int root1, int root2);
    void PrintParentList();

private:
    int* parent;
    int size;
};



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
    void showMatrix();
    void OuputGraphDest();
    void KruskalMinTree();
    void PrimMinTree();
    void Dijkstra();
    void printMinTree();


private:
    int maxVertices;
    int numVertices; // 顶点数
    int numEdges;
    T* verticesList;
    E** Edge;
    MSTEdgeNode<T, E>* mst;//最小生成树数组


    int getVertexPos(T Vertex)
    {
        for (int i = 0; i < numVertices; i++)
            if (verticesList[i] == Vertex)
                return i;
        return -1;
    }
};


////////////////////////////////////////////////////////////////////////////
//并查集函数实现部分start

UFsets::UFsets(int sz)
{
    size = sz;
    parent = new int[size];
    for (int i = 0; i < size; i++)
        parent[i] = -1;
}


void UFsets::Union(int root1, int root2)
{
    //根节点parent值要变小,
    //因为weightUnion函数式根据根节点parent[root]的相反数大小
    //从而来得知哪个树节点多的
    int x = root1;
    while (parent[x] > 0)
        x = parent[x];
    parent[x] = parent[x] + parent[root2];
    parent[root2] = root1;
}




int UFsets::Find(int x)
{
    if (parent[x] < 0)
        return x;
    else
        return Find(parent[x]);
}



void UFsets::WeightedUnion(int root1, int root2)
{
    int r1 = Find(root1);
    int r2 = Find(root2);
    int temp = -1;
    if (r1 != r2)
        temp = parent[r1] + parent[r2];
    //r1树结点多
    if (parent[r1] < parent[r2])
    {
        parent[r1] = temp;
        parent[r2] = r1;
    }
    else
    {
        parent[r2] = temp;
        parent[r1] = r2;
    }

}



void UFsets::PrintParentList()
{
    for (int i = 0; i < size; i++)
        cout << i << "(" << parent[i] << ") ";
    cout << endl;
}



//并查集函数实现部分end
///////////////////////////////////////////////////////////////////////////////


template<class T, class E>
Graphmtx<T, E>::Graphmtx(int sz)
{
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    mst = 0;
    int i, j;
    verticesList = new T[maxVertices];
    Edge = (E * *) new E * [maxVertices];
    for (i = 0; i < maxVertices; i++)
    {
        Edge[i] = new E[maxVertices];
    }
    for (i = 0; i < maxVertices; i++)
        for (j = 0; j < maxVertices; j++)
            Edge[i][j] = (i == j) ? 0 : maxWeight;
}


template<class T, class E>
int Graphmtx<T, E>::getFirstNeightBor(int v)
{
    if (v >= 0 && v < numVertices) {
        for (int col = 0; col < numVertices; col++)
        {
            if (Edge[v][col] && Edge[v][col] < maxWeight)
                return col;
        }
    }
    return -1;
}









template<class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w)
{
    if (v >= 0 && v < numVertices && w >= 0 && w < numVertices)
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









//int numVertices 顶点数
//int numEdges 边数
template<class T, class E>
void Graphmtx<T, E>::KruskalMinTree()
{
    if (mst != 0)
        delete[] mst;
    mst = new MSTEdgeNode<T, E> [numVertices];



    MSTEdgeNode<T, E>* p, leastNode;
    vector<MSTEdgeNode<T, E>> hp;
    make_heap(hp.begin(), hp.end());
    UFsets ufset(numVertices);



    //初始化工作
    for(int u = 0; u < numVertices; u++)
        for(int v = u + 1; v < numVertices; v++) //无向图邻接矩阵对称
            if (Edge[u][v] < maxWeight)
            {
                p = new MSTEdgeNode<T,E>;
                p->tail = u;
                p->head = v;
                p->cost = Edge[u][v];
                hp.push_back(*p);
                push_heap(hp.begin(), hp.end(), cmp);
            }
    int count = 1;//最小生成树边数计数
    while (count < numVertices)
    {
        leastNode = hp.front();
        hp.erase(hp.begin());

        int u = ufset.Find(leastNode.tail);
        int v = ufset.Find(leastNode.head);
        if (u != v) //判断有无构成环路
        {
            ufset.Union(u, v);
            mst[count - 1] = leastNode;
            cout << leastNode.tail << "->" << leastNode.head << "(" << leastNode.cost << ")";
            count++;
        }
    }
    if (count == numVertices)
    {
        cout << "最小生成树生成" << endl;
    }
}





template<class T, class E>
void Graphmtx<T, E>::PrimMinTree()
{
    if (mst != 0)
        delete mst;
    mst = new MSTEdgeNode<T, E>[numVertices];

    MSTEdgeNode<T, E>* p, leastNode;
    vector<MSTEdgeNode<T, E>> hp;
    UFsets ufset(numVertices);
    bool visited[numVertices];

    for (int i = 0; i < numVertices; i++)
        visited[i] = false;

    cout << "请输入出发点编号 0至" << numVertices - 1 << endl;
    int u;
    cin >> u;
    if (u < 0 || u > numVertices - 1)
    {
        cout << "输入有误" << endl;
        return;
    }

    visited[u] = true;
    int count = 1;

    while (count < numVertices)
    {
        for (int v = 0; v < numVertices; v++)
        {
            if ((visited[v] == false) && Edge[u][v] < maxWeight)
            {
                p = new MSTEdgeNode<T, E>;
                p->tail = u;
                p->head = v;
                p->cost = Edge[u][v];

                hp.push_back(*p);
                make_heap(hp.begin(), hp.end(), cmp);
                sort_heap(hp.begin(), hp.end(), cmp);
            }
        }
        while (!hp.empty() && count < numVertices)
        {
            leastNode = hp.front();
            hp.erase(hp.begin());
            if (!visited[leastNode.head])
            {
                mst[count - 1] = leastNode;
                cout << leastNode.tail << "->" << leastNode.head << "(" << leastNode.cost << ")";
                u = leastNode.head;
                visited[u] = true;
                count++;
                break;
            }
        }
    }

}





template<class T, class E>
void Graphmtx<T, E>::Dijkstra()
{
    int v0;
    E dist[numVertices];
    bool visited[numVertices];
    int pos;


    cout << "请输入出发点编号 0至" << numVertices - 1 << endl;
    cin >> v0;

    for (int i = 0; i < numVertices; i++)
        dist[i] = Edge[v0][i];
    visited[v0] = true;
    for (int i = 0; i < numVertices - 1; i++)
    {
        int min = maxWeight;
        for (int k = 0; k < numVertices; k++)
        {
            if (visited = false && dist[k] < min)
            {
                pos = k;
                min = dist[k];
            }
            visited[pos] = 1;
            for (int j = 0; j < numVertices; j++)
            {
                if (visited[j] == false && Edge[pos][j] + min < dist[j])
                    dist[j] = Edge[pos][j] + min;
            }

        }
    }




}













template<class T,class E>
void display(vector<MSTEdgeNode<T,E>>& v)//使用vector迭代器遍历
{
    //vector<MSTEdgeNode<T, E> >::iterator iter;
    for (auto iter = v.begin(); iter < v.end(); iter++)
    {
        cout << (*iter).tail << "->" << (*iter).head << (*iter).cost << endl;
    }
    cout << endl << endl;
}




template<class T, class E>
void Graphmtx<T, E>::printMinTree()
{
    if (mst == 0)
    {
        cout << "最小生成树为空" << endl;
        return;
    }
    for(int i = 0; i < numVertices; i++)
        cout << mst[i].tail << "->" << mst[i].head << mst[i].cost << endl;

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



    cout << endl;
    a.KruskalMinTree();
    a.printMinTree();








    cout << endl;
}