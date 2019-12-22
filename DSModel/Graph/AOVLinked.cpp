//
// Created by Dell on 2019/12/21.
//
//
#include <cassert>
#include <iostream>

using namespace std;
const int MaxWeight = 9999;
const int DefaultMaxVertexNum = 30;

template<class T, class E>
struct Edge {
    int dest;
    E cost;
    Edge<T, E> *link;

    Edge() : dest(-1), link(nullptr) { cost = E(); }
};

template<class T, class E>
struct Vertex {
    T data;
    Edge<T, E> *adj;

    Vertex() : adj(nullptr) { data = T(); }
};

//有向图
template<class T, class E>
class AOVGragh {
public:
    AOVGragh(int sz = DefaultMaxVertexNum);

    ~AOVGragh();

    bool InsertVertex(const T &vertex);

    bool InsertEdge(int v1, int v2, E weight);

    void printDest();

    bool TopologicalSort();

    void printToPoList();


private:
    int numVertex;
    int maxVertex;
    int numEdges;

    Vertex<T, E> *NodeTable;
    int* ToPoList;
};

template<class T, class E>
AOVGragh<T, E>::AOVGragh(int sz) {
    ToPoList = nullptr;
    maxVertex = (sz > DefaultMaxVertexNum) ? sz : DefaultMaxVertexNum;
    NodeTable = new Vertex<T, E>[maxVertex];
    assert(NodeTable != nullptr);
    numVertex = 0;
    numEdges = 0;
}

template<class T, class E>
AOVGragh<T, E>::~AOVGragh() {
    if (NodeTable != nullptr)
        delete[] NodeTable;
    if(ToPoList != nullptr)
        delete [] ToPoList;
}

template<class T, class E>
bool AOVGragh<T, E>::InsertVertex(const T &vertex) {
    if (numVertex == maxVertex)
        return false;
    NodeTable[numVertex].data = vertex;
    numVertex++;
    return true;
}

template<class T, class E>
bool AOVGragh<T, E>::InsertEdge(int v1, int v2, E weight) {
    if (v1 < 0 || v1 >= numVertex || v2 < 0 || v2 >= numVertex)
        return false;
    Edge<T, E> *p = NodeTable[v1].adj;
    //要判断一下改变是否已经存在
    while (p != nullptr && p->dest != v2)
        p = p->link;
    //已有此边,否则p此时必为nullptr
    if (p != nullptr)
        return false;

    p = new Edge<T, E>;
    p->dest = v2;
    p->cost = weight;
    p->link = NodeTable[v1].adj;
    NodeTable[v1].adj = p; //头插法

    //该图为有向图，故不用插入两条边
    numEdges++;
    return true;
}

template<class T, class E>
void AOVGragh<T, E>::printDest() {
    Edge<T, E> *p;
    for (int i = 0; i < numVertex; i++) {
        cout << "-----与" << "编号为 " << i << " ,值为 ";
        cout << NodeTable[i].data << " 相连的点 : 顶点值(编号,权值)" << endl;
        p = NodeTable[i].adj;
        while (p != nullptr) {
            cout << NodeTable[p->dest].data;
            cout << "( " << p->dest << ", " << p->cost << ")" << " ";
            p = p->link;
        }
        cout << endl << endl;
    }
    cout << endl << endl;
}

template<class T, class E>
bool AOVGragh<T, E>::TopologicalSort() {
    if(ToPoList != nullptr)
        delete [] ToPoList;
    ToPoList = new int[numVertex];

    int top = -1, i, v;
    int count[numVertex];
    for (int i = 0; i < numVertex; i++)
        count[i] = 0;

    //初始化工作
    Edge<T, E> *p;
    for (i = 0; i < numVertex; i++) {
        p = NodeTable[i].adj;
        while (p != nullptr) {
            count[p->dest]++;
            p = p->link;
        }
    }

    //寻找入度为零，即count[i]为0的点
    for(i = 0; i < numVertex; i++){
        if(count[i] == 0){
            count[i] = top;
            top = i;
        }
    }

    for(i = 0; i < numVertex; i++){
        if(top == -1){
            delete [] ToPoList;
            cout << "网络中有回路" << endl;
            return false;
        } else {
            v = top;
            top = count[top]; //退栈
            cout << NodeTable[v].data << " ";
            ToPoList[i] = v;
            p = NodeTable[v].adj;
            while(p != nullptr){
                count[p->dest]--;
                if(count[p->dest] == 0){ //进栈
                    count[p->dest] = top;
                    top = p->dest;
                }
                p = p->link;
            }
        }
    }
    cout << endl;
    return true;
}

template<class T, class E>
void AOVGragh<T, E>::printToPoList() {
    if(ToPoList == nullptr)
        return;
    cout << "ToPoList: " << endl;
    for(int i = 0; i < numVertex; i++)
        cout << ToPoList[i] << "(" << NodeTable[ToPoList[i]].data << ") ";
    cout << endl;
}


int main() {
    AOVGragh<char, double> a1;
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

    a1.printDest();
    a1.TopologicalSort();
    a1.printToPoList();
}