#include <iostream>
//#include "GraphMatrix.h"
#include "GraphDest.h"
using namespace std;


int main() {
    int numVertex, numEdge, isDirectGraph;
    char *vertexes;
    EdgesTypeChar *edges;
    ifstream infile("a.txt", ios::in);
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

//    GraphMatrix g1(numVertex, numEdge, isDirectGraph, vertexes, edges);
//    g1.showMatrix();
//
//    cout << "������ȱ���: " << endl;
//    g1.DFS();
//
//    cout << endl << "������ȱ���: " << endl;
//    g1.BFS();
//
//
//    delete[] vertexes;
//    delete[] edges;
//    cout << endl;
//    system("pause");

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


//�ж϶�ȡ�Ƿ���ȷ�Ĵ���
//    cout << ((isDirectGraph == 1) ? "����ͼ" : "����ͼ");
//    cout << "��" << numVertex << "���� : "<< endl;
//    for(int i = 0; i < numVertex; i++)
//        cout << vertexes[i] << " ";
//    cout << endl;
//    cout <<"��" << numEdge << "����: " << endl;
//    for(int i = 0; i < numEdge; i++)
//        cout << edges[i].tail << " --> " << edges[i].head << endl;