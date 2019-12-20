//
// Created by Dell on 2019/12/15.
//
#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>
#include <algorithm>


using namespace std;
const int maxWeight = 9999;
const int DefaultVertices = 30;

#include "UFsets.h"


template<class T, class E>
struct MSTEdgeNode {
    int tail, head;
    E cost;
};

template<class T, class E>
bool cmp(const MSTEdgeNode<T, E>& a, const MSTEdgeNode<T, E>& b) {
    return a.cost < b.cost;  //升序
}


template<class T, class E>
struct Edge {
    int dest;    //边的另一个顶点位置
    E cost;			//边上的权值
    Edge<T, E>* link;
    Edge():dest(-1),cost(-1),link(nullptr) {}
    Edge(int num, E weight) : dest(num),cost(weight),link(0){}
};

template<class T, class E>
struct Vertex {
    T data;
    Edge<T, E>* adj;
};

template<class T, class E>
class GraphLinked {
public:
    explicit GraphLinked(int sz = DefaultVertices);
    ~GraphLinked();

    T getValue(int i) {
        return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0;
    }

    E getWeight(int v1, int v2);
    bool insertVertex(const T& vertex);
    bool removeVertex(int v);
    bool insertEdge(int v1, int v2, E weight);
    bool removeEdge(int v1, int v2);

    int getFirstNeighbor(int v);
    int getNextNeighbor(int v, int w);

    void CreateNodeTable();
    void PrintDest(); //把邻接表的样子输出来
    void KruskalMinTree();
    void PrimMinTree();
    void Dikstra();

    //遍历
    void DFS();
    void BFS();


private:
    int numVertices;
    int maxVertices;
    int numEdges;
    bool* visited; //用于dfs和bfs

    Vertex<T, E>* NodeTable; //结点表
    MSTEdgeNode<T, E>* mst;//最小生成树数组

    int getVertexPos(const T vertex) {
        for (int i = 0; i < numVertices; i++)
        {
            if (NodeTable[i].data == vertex)
                return i;
        }
        return -1;
    }
    void DFS(int v);
};



template<class T, class E>
GraphLinked<T, E>::GraphLinked(int sz)
{
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;

    NodeTable = new Vertex<T, E>[maxVertices];
    if (NodeTable == 0)
    {
        cerr << "分存分配错误" << endl;
        exit(1);
    }
    for (int i = 0; i < maxVertices; i++)
    {
        NodeTable[i].adj = 0;
    }
}




template<class T, class E>
GraphLinked<T, E>::~GraphLinked()
{
    for (int i = 0; i < numVertices; i++)
    {
        Edge<T, E>* p = NodeTable[i].adj;
        while (p != nullptr)
        {
            NodeTable[i].adj = p->link;
            delete p;
            p = NodeTable[i].adj;
        }
    }
    delete[]NodeTable;
}


template<class T, class E>
E GraphLinked<T, E>::getWeight(int v1, int v2)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        Edge<T, E>* p = NodeTable[v1].adj;
        while (p != nullptr && p->dest != v2)
        {
            p = p->link;
        }
        if (p != nullptr)
            return p->cost;  //找到此边,返回权值
    }
    return 0;
}



template<class T, class E>
bool GraphLinked<T, E>::insertVertex(const T& vertex)
{
    if (numVertices == maxVertices)
        return false;
    NodeTable[numVertices].data = vertex;
    numVertices++;
    return true;
}



template<class T, class E>
bool GraphLinked<T, E>::removeVertex(int v)
{
    if (numVertices == 1 || v < 0 || v >= numVertices)
        return false;
    Edge<T, E>* p, * s, * t;
    int k;
    while (NodeTable[v].adj != nullptr) {
        p = NodeTable[v].adj;
        k = p->dest;
        s = NodeTable[k].adj;  //找对称存放的边结点
        t = nullptr;                 //t 是 s的前一个指针，跟着s走，方便后续删除结点
        while (s != nullptr && s->dest != v)
        {
            t = s;
            s = s->link;
        }
        if (s != nullptr) {
            if (t == nullptr)
                NodeTable[k].adj = s->link;
            else
                t->link = s->link;
            delete s;
        }

        NodeTable[v].adj = p->link;
        delete p;
        numEdges--;
    }

    numVertices--;   //图的顶点数减1
    NodeTable[v].data = NodeTable[numVertices].data;  //用最后一个结点来填补
    p = NodeTable[v].adj = NodeTable[numVertices].adj;
    while (p != nullptr) {
        s = NodeTable[p->dest].adj;
        while (s != nullptr)
        {
            if (s->dest == numVertices)
            {
                //将原本与编号为numVertices的该为v,因为它已经搬到v了
                s->dest = v;
                break;
            }
            else
                s = s->link;
        }
        ///////////////////////////////////////////////
        //书中没有这句代码
        p = p->link;
        //////////////////////////////////////////////
    }

    return true;
}





template<class T, class E>
bool GraphLinked<T, E>::insertEdge(int v1, int v2, E weight)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        Edge<T, E>* q, * p = NodeTable[v1].adj;
        while (p != nullptr && p->dest != v2)
            p = p->link;
        if (p != nullptr)
            return false; //已有此边,否则p此时必为0
        p = new Edge<T, E>;
        q = new Edge<T, E>;

        p->dest = v2;
        p->cost = weight;
        q->dest = v1;
        q->cost = weight;

        //头插入v1的边链表
        p->link = NodeTable[v1].adj;
        NodeTable[v1].adj = p;

        //头插入v2的边链表
        q->link = NodeTable[v2].adj;
        NodeTable[v2].adj = q;


        numEdges++;
        return true;
    }
    return false;
}




template<class T, class E>
bool GraphLinked<T, E>::removeEdge(int v1, int v2)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        Edge<T, E>* p = NodeTable[v1].adj;
        Edge<T, E>* q = 0, *s = p; //q是p上一个指针,方便删除操作

        while (p != 0 && p->dest != v2)
        {
            q = p;
            p = p->link;
        }
        if (p != 0)
        {
            if (p == s)    //要删的结点被头指针指着
                NodeTable[v1].adj = p->link;
            else
                q->link = p->link;
            delete p;
        }
        else
            return false; // p == 0，没找到这条边

        p = NodeTable[v2].adj;  //v2对应边链表中删除
        q = 0;
        s = p;
        while (p->dest != v1)
        {
            q = p;
            p = p->link;
        }
        if (p == s)   //要删的结点被头指针指着
            NodeTable[v2].adj = p->link;
        else
            q->link = p->link;
        delete p;
        return true;
    }
    return false;
}







template<class T, class E>
int GraphLinked<T, E>::getFirstNeighbor(int v)
{
    if (v >= 0 && v < numVertices)
    {
        Edge<T, E>* p = NodeTable[v].adj;
        if (p != nullptr)
            return p->dest;//存在，返回第一个临界点
    }
    return -1;
}







template<class T, class E>
int GraphLinked<T, E>::getNextNeighbor(int v, int w)
{
    if (v >= 0 && v < numVertices)
    {
        Edge<T, E>* p = NodeTable[v].adj;
        while (p != nullptr && p->dest != nullptr)
            p = p->link;
        if (p != nullptr && p->link != nullptr)
            return p->link->dest;
    }
    return -1;  //-1代表不存在
}





//建立邻接表结构
template<class T, class E>
void GraphLinked<T, E>::CreateNodeTable()
{
    int n, i, j, m;
    Edge<T, E>* p;

    cout << "请输入要创建的结点个数" << endl;
    cin >> n; //结点个数
    if (n > maxVertices)
    {
        cout << "超过最大结点数" << endl;
        return;
    }
    numVertices = n;
    for (i = 0; i < n; i++)
    {
        NodeTable[i].adj = 0;  //预设为空链
        cout << "请输入编号为 " << i << "的结点的值: ";
        cin >> NodeTable[i].data;

        cout << "请输入" << NodeTable[i].data << "的邻接点个数：";
        cin >> m;
        cout << "请输入它的 " << m << "个邻接点(相邻顶点编号 权重)" << endl;
        for (j = 0; j < m; j++)
        {
            p = new Edge<T, E>;
            cin >> p->dest;
            cin >> p->cost;
            //头插入建链
            p->link = NodeTable[i].adj;
            NodeTable[i].adj = p;
        }
    }
}






template<class T, class E>
void GraphLinked<T, E>::DFS(int v)
{
    visited[v] = true;
    cout << NodeTable[v].data << " ";
    Edge<T, E>* p = NodeTable[v].adj;
    while (p != 0)
    {
        if (!visited[p->dest])
            DFS(p->dest);
        p = p->link;
    }
}




template<class T, class E>
void GraphLinked<T, E>::DFS()
{
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;
    int v0;
    cout << "请输入深度优先遍历的出发点编号：0至 " << numVertices - 1 << endl;
    cin >> v0;
    DFS(v0);
    cout << endl << endl;
}




template<class T, class E>
void GraphLinked<T, E>::BFS()
{
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;
    int v;
    Edge<T, E>* p;
    queue<int>Q;
    cout << "请输入广度优先遍历的出发点编号：0至 " << numVertices - 1 << endl;
    cin >> v;
    Q.push(v);

    while (!Q.empty())
    {
        v = Q.front();
        Q.pop();
        if (!visited[v])
        {
            visited[v] = true;
            cout << NodeTable[v].data << " ";
            p = NodeTable[v].adj;
            while (p != 0)
            {
                if (!visited[p->dest])
                    Q.push(p->dest);
                p = p->link;
            }
        }
    }
    cout << endl << endl;
}






template<class T, class E>
void GraphLinked<T, E>::PrintDest()
{
    Edge<T, E>* p;
    for (int i = 0; i < numVertices; i++)
    {
        cout << "-----与" << "编号为 " << i << " ,值为 ";
        cout << NodeTable[i].data << " 相连的点 : 顶点值(编号,权值)" << endl;
        p = NodeTable[i].adj;
        while (p != 0)
        {
            cout << NodeTable[p->dest].data;
            cout << "( " << p->dest << ", " << p->cost << ")" << " ";
            p = p->link;
        }
        cout << endl << endl;
    }
    cout << endl << endl;
}

template<class T, class E>
void GraphLinked<T, E>::KruskalMinTree() {
    if(mst != 0)
        delete [] mst;
    mst = new MSTEdgeNode<T,E> [numVertices];

    if(visited != nullptr)
        delete[] visited;
    visited = new bool[numVertices];
    for(int i = 0; i < numVertices; i++){
        visited[i] = false;
    }

    MSTEdgeNode<T,E>* p, leastNode;
    vector<MSTEdgeNode<T,E>>hp;
    UFsets fsets(numVertices);

    //初始化工作
    Edge<T,E> *edgePtr;
    for(int i = 0; i < numVertices; i++){
        edgePtr = NodeTable[i].adj;
        while(edgePtr != 0){
            if(!visited[edgePtr->dest]){

            }
            p = new MSTEdgeNode<T,E>;
            p->tail = i;
            p->head = edgePtr->dest;
            p->cost = edgePtr->cost;
            hp.push_back(*p);
            make_heap(hp.begin(),hp.end(),cmp<T,E>);
            sort_heap(hp.begin(),hp.end(),cmp<T,E>);
            edgePtr = edgePtr->link;
        }
    }
}


int main()
{
    GraphLinked<char, double> a;
    //a.CreateNodeTable();

    //把图先建立起来

    //先插入顶点
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

    a.PrintDest();

    a.KruskalMinTree();



    cout << endl;
}






