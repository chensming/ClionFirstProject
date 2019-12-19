//
// Created by Dell on 2019/12/17.
//
#include <iostream>
#include <queue>
#include <fstream>

using namespace std;


struct EdgesTypeChar {
    char tail;
    char head;
};

struct EdgeType {
    int dest;
    EdgeType *link;

    EdgeType() : dest(-1), link(nullptr) {}
};

struct VertexType {
    char data;
    EdgeType *adj;

    VertexType() : data(-1), adj(nullptr) {}
};

class GraphDest {
public:
    GraphDest(int numv, int nume, int isDG, char *vlist, EdgesTypeChar *elist);

    ~GraphDest();

    void PrintDest();

    void DFS();

    void BFS();

private:
    int numVertex;
    int numEdge;
    bool *visited;
    //����
    VertexType *NodeTable;

    void DFS(int v);

    int change(char ch);
};

GraphDest::GraphDest(int numv, int nume, int isDG, char *vlist, EdgesTypeChar *elist) {
    numVertex = numv;
    numEdge = nume;
    visited = nullptr;
    EdgeType *p;

    NodeTable = new VertexType[numVertex];
//    �޲ι��캯���Ѹ�linkĬ��ֵnullptr
//    for(int i = 0; i < numVertex; i++)
//    {
//        NodeTable[i].adj = nullptr;
//    }
    //�����㼯
    for (int i = 0; i < numVertex; i++)
        NodeTable[i].data = vlist[i];
    //�����߼�
    for (int i = 0; i < numEdge; i++) {
        p = new EdgeType;
        p->dest = change(elist[i].head);
        //ͷ����
        p->link = NodeTable[change(elist[i].tail)].adj;
        NodeTable[change(elist[i].tail)].adj = p;
        //����ͼ��Ҫ�������ٽ���һ����
        if (!isDG) { //isDG == 0��Ϊ����ͼ
            p = new EdgeType;
            p->dest = change(elist[i].tail);
            //ͷ����
            p->link = NodeTable[change(elist[i].head)].adj;
            NodeTable[change(elist[i].head)].adj = p;
        }
    }

}

int GraphDest::change(char ch) {
    for (int i = 0; i < numVertex; i++)
        if (ch == NodeTable[i].data)
            return i;
}

GraphDest::~GraphDest() {
    delete[] NodeTable;
}

void GraphDest::PrintDest() {
    EdgeType *p;
    for (int i = 0; i < numVertex; i++) {
        cout << "-----��" << "���Ϊ " << i << " ,ֵΪ ";
        cout << NodeTable[i].data << " �����ĵ� : ����ֵ(���)" << endl;
        p = NodeTable[i].adj;
        while (p != nullptr) {
            cout << NodeTable[p->dest].data << "(" << p->dest << ") ";
            p = p->link;
        }
        cout << endl << endl;
    }
}

void GraphDest::DFS() {
    if(visited != nullptr)
        delete[] visited;
    visited = new bool[numVertex];
    for(int i = 0; i < numVertex; i++)
        visited[i] = false;
    int v0;
    cout << "������������ȱ����ĳ�������(��0��" << numVertex - 1 << "): ";
    cin >> v0;
    if (v0 < 0 || v0 > numVertex - 1) {
        cout << "����ı������" << endl;
        return;
    }
    DFS(v0);
}


void GraphDest::DFS(int v) {
    visited[v] = true;
    cout << NodeTable[v].data << " ";
    EdgeType* p = NodeTable[v].adj;
    while(p != nullptr){
        if(!visited[p->dest])
            DFS(p->dest);
        p = p->link;
    }
}

void GraphDest::BFS() {
    if(visited != nullptr)
        delete[] visited;
    visited = new bool[numVertex];
    for(int i = 0; i < numVertex; i++)
        visited[i] = false;
    int v;
    EdgeType* p;
    queue<int> Q;

    cout << "�����������ȱ����ĳ�������(��0��" << numVertex - 1 << "): ";
    cin >> v;
    if (v < 0 || v > numVertex - 1) {
        cout << "����ı������" << endl;
        return;
    }

    Q.push(v);
    while(!Q.empty()){
        v = Q.front();
        Q.pop();
        if(!visited[v]){
            visited[v] = true;
            cout << NodeTable[v].data << " ";
            p = NodeTable[v].adj;
            while(p != nullptr){
                if(!visited[p->dest])
                    Q.push(p->dest);
                p = p->link;
            }
        }
    }
}

int main() {
    int numVertex, numEdge, isDirectGraph;
    char *vertexes;
    EdgesTypeChar *edges;
    ifstream infile("FirstProject/Chenhongy/Graph/a.txt", ios::in);
    if (!infile) {
        cerr << "open a.txt error" << endl;
        exit(1);
    }
    infile >> numVertex >> numEdge >> isDirectGraph;
    vertexes = new char[numVertex];
    edges = new EdgesTypeChar[numEdge];
    //��ȡ��
    for (int i = 0; i < numVertex; i++)
        infile >> vertexes[i];
    //��ȡ��
    for (int i = 0; i < numEdge; i++) {
        infile >> edges[i].tail >> edges[i].head;
    }

    GraphDest g1(numVertex, numEdge, isDirectGraph, vertexes, edges);
    g1.PrintDest();

    cout << "������ȱ���: " << endl;
    g1.DFS();

    cout << endl << "������ȱ���: " << endl;
    g1.BFS();


    delete[] vertexes;
    delete[] edges;
    cout << endl;
}