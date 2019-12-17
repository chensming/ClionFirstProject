//
// Created by Dell on 2019/12/17.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>

using namespace std;
struct EdgesTypeChar {
    char tail;
    char head;
};


class GraphMatrix {
public:

    GraphMatrix(int numv, int nume, int isDG, char *vlist, EdgesTypeChar *elist);

    ~GraphMatrix();

    void showMatrix();

    void DFS();

    void BFS();

private:
    int numVertices;
    int numEdges;
    char *VerticesList;
    int **EdgeMatrix;
    bool *visited;

    int change(char ch);

    void DFS(int v);
};

GraphMatrix::GraphMatrix(int numv, int nume, int isDG, char *vlist, EdgesTypeChar *elist) {
    numVertices = numv;
    numEdges = nume;
    visited = nullptr;
    VerticesList = new char[numVertices];
    EdgeMatrix = (int **) new int *[numEdges];
    for (int i = 0; i < numVertices; i++)
        EdgeMatrix[i] = new int[numEdges];

    for (int i = 0; i < numVertices; i++)
        VerticesList[i] = vlist[i];

    for (int row = 0; row < numVertices; row++)
        for (int col = 0; col < numVertices; col++)
            EdgeMatrix[row][col] = 0;
    if (isDG == 1) //����ͼ
        for (int i = 0; i < numEdges; i++) {
            EdgeMatrix[change(elist[i].tail)][change(elist[i].head)] = 1;
        }
    else //����ͼ
        for (int i = 0; i < numEdges; i++) {
            EdgeMatrix[change(elist[i].tail)][change(elist[i].head)] = 1;
            EdgeMatrix[change(elist[i].head)][change(elist[i].tail)] = 1;
        }
    cout << "ͼ�Ĺ������" << endl;
}


GraphMatrix::~GraphMatrix() {
    numVertices = 0;
    numEdges = 0;
    delete[] VerticesList;
    delete[] EdgeMatrix;
}

void GraphMatrix::showMatrix() {
    cout << "ͼ���ڽӾ���: " << endl;
    cout << setw(8) << " ";
    for (int i = 0; i < numVertices; i++)
        cout << setw(8) << VerticesList[i];
    cout << endl;
    for (int row = 0; row < numVertices; row++) {
        cout << setw(8) << VerticesList[row];
        for (int col = 0; col < numVertices; col++)
            cout << setw(8) << EdgeMatrix[row][col];
        cout << endl;
    }
    cout << endl << endl;
}

int GraphMatrix::change(char ch) {
    for (int i = 0; i < numVertices; i++)
        if (ch == VerticesList[i])
            return i;
}

void GraphMatrix::DFS() {
    if (visited != nullptr)
        delete[] visited;
    visited = new bool[numVertices];
    int v0;
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }
    cout << "������������ȱ����ĳ�������(��0��" << numVertices - 1 << "): ";
    cin >> v0;
    if (v0 < 0 || v0 > numVertices - 1) {
        cout << "����ı������" << endl;
        return;
    }
    DFS(v0);
}

void GraphMatrix::DFS(int v) {
    visited[v] = true;
    cout << VerticesList[v] << " ";
    for (int col = 0; col < numVertices; col++) {
        if (EdgeMatrix[v][col] && !visited[col])
            DFS(col); //�ɴ���δ�����ʹ�
    }
}

void GraphMatrix::BFS() {
    if (visited != nullptr)
        delete[] visited;
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;
    int v;
    queue<int> Q;
    cout << "�����������ȱ����ĳ�������(��0��" << numVertices - 1 << "): ";
    cin >> v;
    if (v < 0 || v > numVertices - 1) {
        cout << "����ı������" << endl;
        return;
    }
    Q.push(v);
    while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        if (!visited[v]) {
            visited[v] = true;
            cout << VerticesList[v] << " ";
            for (int i = 0; i < numVertices; i++) {
                if (EdgeMatrix[v][i] && !visited[i]) {
                    Q.push(i);
                }
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

    GraphMatrix g1(numVertex, numEdge, isDirectGraph, vertexes, edges);
    g1.showMatrix();

    cout << "������ȱ���: " << endl;
    g1.DFS();

    cout << endl << "������ȱ���: " << endl;
    g1.BFS();


    delete[] vertexes;
    delete[] edges;
    cout << endl;
}


//�ж϶�ȡ�Ƿ���ȷ�Ĵ���
//    cout << ((isDirectGraph == 1) ? "����ͼ" : "����ͼ");
//    cout << "��" << numVertex << "���� : "<< endl;
//    for(int i = 0; i < numVertex; i++)
//        cout << vertexes[i] << " ";
//    cout << endl;
//    cout <<"��" << numEdge << "����: " << endl;
//    for(int i = 0; i < numEdge; i++)
//        cout << edges[i].tail << " --> " << edges[i].head << endl;