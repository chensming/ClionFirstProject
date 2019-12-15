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
    return a.cost < b.cost;  //����
}


template<class T, class E>
struct Edge {
    int dest;    //�ߵ���һ������λ��
    E cost;			//���ϵ�Ȩֵ
    Edge<T, E>* link;
    Edge() {}
    Edge(int num, E weight) : dest(num),cost(weight),link(0){}
    bool operator!= (Edge<T, E>& R)const {
        return (dest != R.dest) ? true : false;
    }
};

template<class T, class E>
struct Vertex {
    T data;
    Edge<T, E>* adj;
};

template<class T, class E>
class Graphlnk {
public:
    Graphlnk(int sz = DefaultVertices);
    ~Graphlnk();

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
    void PrintDest(); //���ڽӱ�����������
    void KruskalMinTree();
    void PrimMinTree();
    void Dikstra();

    //����
    void DFS();
    void BFS();


private:
    int numVertices;
    int maxVertices;
    int numEdges;
    bool* visited; //����dfs��bfs

    Vertex<T, E>* NodeTable; //����
    MSTEdgeNode<T, E>* mst;//��С����������


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
Graphlnk<T, E>::Graphlnk(int sz)
{
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;

    NodeTable = new Vertex<T, E>[maxVertices];
    if (NodeTable == 0)
    {
        cerr << "�ִ�������" << endl;
        exit(1);
    }
    for (int i = 0; i < maxVertices; i++)
    {
        NodeTable[i].adj = 0;
    }
}




template<class T, class E>
Graphlnk<T, E>::~Graphlnk()
{
    for (int i = 0; i < numVertices; i++)
    {
        Edge<T, E>* p = NodeTable[i].adj;
        while (p != 0)
        {
            NodeTable[i].adj = p->link;
            delete p;
            p = NodeTable[i].adj;
        }
    }
    delete[]NodeTable;
}


template<class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        Edge<T, E>* p = NodeTable[v1].adj;
        while (p != 0 && p->dest != v2)
        {
            p = p->link;
        }
        if (p != 0)
            return p->cost;  //�ҵ��˱�,����Ȩֵ
    }
    return 0;
}



template<class T, class E>
bool Graphlnk<T, E>::insertVertex(const T& vertex)
{
    if (numVertices == maxVertices)
        return false;
    NodeTable[numVertices].data = vertex;
    numVertices++;
    return true;
}



template<class T, class E>
bool Graphlnk<T, E>::removeVertex(int v)
{
    if (numVertices == 1 || v < 0 || v >= numVertices)
        return false;
    Edge<T, E>* p, * s, * t;
    int i, k;
    while (NodeTable[v].adj != 0) {
        p = NodeTable[v].adj;
        k = p->dest;
        s = NodeTable[k].adj;  //�ҶԳƴ�ŵı߽��
        t = 0;                 //t �� s��ǰһ��ָ�룬����s�ߣ��������ɾ�����
        while (s != 0 && s->dest != v)
        {
            t = s;
            s = s->link;
        }
        if (s != 0) {
            if (t == 0)
                NodeTable[k].adj = s->link;
            else
                t->link = s->link;
            delete s;
        }

        NodeTable[v].adj = p->link;
        delete p;
        numEdges--;
    }

    numVertices--;   //ͼ�Ķ�������1
    NodeTable[v].data = NodeTable[numVertices].data;  //�����һ��������
    p = NodeTable[v].adj = NodeTable[numVertices].adj;
    while (p != 0) {
        s = NodeTable[p->dest].adj;
        while (s != 0)
        {
            if (s->dest == numVertices)
            {
                s->dest = v;
                break;
            }
            else
                s = s->link;
        }
        ///////////////////////////////////////////////
        //����û��������
        p = p->link;
        //////////////////////////////////////////////
    }

    //���⣺�����һ��������������ô�������������ӵ�numVertices����ô��
    return true;
}





template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight)
{
    if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
    {
        Edge<T, E>* q, * p = NodeTable[v1].adj;
        while (p != 0 && p->dest != v2)
            p = p->link;
        if (p != 0)
            return false; //���д˱�,����p��ʱ��Ϊ0
        p = new Edge<T, E>;
        q = new Edge<T, E>;

        p->dest = v2;
        p->cost = weight;
        q->dest = v1;
        q->cost = weight;

        //ͷ����v1�ı�����
        p->link = NodeTable[v1].adj;
        NodeTable[v1].adj = p;

        //ͷ����v2�ı�����
        q->link = NodeTable[v2].adj;
        NodeTable[v2].adj = q;


        numEdges++;
        return true;
    }
    return false;
}




template<class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{
    if (v1 >= 0 || v1 < numVertices || v2 >= 0 && v2 < numVertices)
    {
        Edge<T, E>* p = NodeTable[v1].adj;
        Edge<T, E>* q = 0, *s = p; //q��p��һ��ָ��,����ɾ������

        while (p != 0 && p->dest != v2)
        {
            q = p;
            p = p->link;
        }
        if (p != 0)
        {
            if (p == s)    //Ҫɾ�Ľ�㱻ͷָ��ָ��
                NodeTable[v1].adj = p->link;
            else
                q->link = p->link;
            delete p;
        }
        else
            return false; // p == 0��û�ҵ�������

        p = NodeTable[v2].adj;  //v2��Ӧ��������ɾ��
        q = 0;
        s = p;
        while (p->dest != v1)
        {
            q = p;
            p = p->link;
        }
        if (p == s)   //Ҫɾ�Ľ�㱻ͷָ��ָ��
            NodeTable[v2].adj = p->link;
        else
            q->link = p->link;
        delete p;
        return true;
    }
    return false;
}







template<class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v)
{
    if (v >= 0 && v < numVertices)
    {
        Edge<T, E>* p = NodeTable[v].adj;
        if (p != 0)
            return p->dest;//���ڣ����ص�һ���ٽ��
    }
    return -1;
}







template<class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w)
{
    if (v >= 0 && v < numVertices)
    {
        Edge<T, E>* p = NodeTable[v].adj;
        while (p != 0 && p->dest != w)
            p = p->link;
        if (p != 0 && p->link != 0)
            return p->link->dest;
    }
    return -1;  //-1��������
}





//�����ڽӱ�ṹ
template<class T, class E>
void Graphlnk<T, E>::CreateNodeTable()
{
    int n, i, j, m;
    Edge<T, E>* p;

    cout << "������Ҫ�����Ľ�����" << endl;
    cin >> n; //������
    if (n > maxVertices)
    {
        cout << "�����������" << endl;
        return;
    }
    numVertices = n;
    for (i = 0; i < n; i++)
    {
        NodeTable[i].adj = 0;  //Ԥ��Ϊ����
        cout << "��������Ϊ " << i << "�Ľ���ֵ: ";
        cin >> NodeTable[i].data;

        cout << "������" << NodeTable[i].data << "���ڽӵ������";
        cin >> m;
        cout << "���������� " << m << "���ڽӵ�(���ڶ����� Ȩ��)" << endl;
        for (j = 0; j < m; j++)
        {
            p = new Edge<T, E>;
            cin >> p->dest;
            cin >> p->cost;
            //ͷ���뽨��
            p->link = NodeTable[i].adj;
            NodeTable[i].adj = p;
        }
    }
}






template<class T, class E>
void Graphlnk<T, E>::DFS(int v)
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
void Graphlnk<T, E>::DFS()
{
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;
    int v0;
    cout << "������������ȱ����ĳ������ţ�0�� " << numVertices - 1 << endl;
    cin >> v0;
    DFS(v0);
    cout << endl << endl;
}




template<class T, class E>
void Graphlnk<T, E>::BFS()
{
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;
    int v;
    Edge<T, E>* p;
    queue<int>Q;
    cout << "�����������ȱ����ĳ������ţ�0�� " << numVertices - 1 << endl;
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
void Graphlnk<T, E>::PrintDest()
{
    Edge<T, E>* p;
    for (int i = 0; i < numVertices; i++)
    {
        cout << "-----��" << "���Ϊ " << i << " ,ֵΪ ";
        cout << NodeTable[i].data << " �����ĵ� : ����ֵ(���,Ȩֵ)" << endl;
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
void Graphlnk<T, E>::KruskalMinTree() {
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

    //��ʼ������
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
    Graphlnk<char, double> a;
    //a.CreateNodeTable();

    //��ͼ�Ƚ�������

    //�Ȳ��붥��
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





    cout << endl;
}






