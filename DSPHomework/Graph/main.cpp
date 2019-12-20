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
    //读取点
    for (int i = 0; i < numVertex; i++)
        infile >> vertexes[i];
    //读取边
    for (int i = 0; i < numEdge; i++) {
        infile >> edges[i].tail >> edges[i].head;
    }

//    GraphMatrix g1(numVertex, numEdge, isDirectGraph, vertexes, edges);
//    g1.showMatrix();
//
//    cout << "深度优先遍历: " << endl;
//    g1.DFS();
//
//    cout << endl << "广度优先遍历: " << endl;
//    g1.BFS();
//
//
//    delete[] vertexes;
//    delete[] edges;
//    cout << endl;
//    system("pause");

    GraphDest g1(numVertex, numEdge, isDirectGraph, vertexes, edges);
    g1.PrintDest();

    cout << "深度优先遍历: " << endl;
    g1.DFS();

    cout << endl << "广度优先遍历: " << endl;
    g1.BFS();


    delete[] vertexes;
    delete[] edges;
    cout << endl;
}


//判断读取是否正确的代码
//    cout << ((isDirectGraph == 1) ? "有向图" : "无向图");
//    cout << "有" << numVertex << "个点 : "<< endl;
//    for(int i = 0; i < numVertex; i++)
//        cout << vertexes[i] << " ";
//    cout << endl;
//    cout <<"有" << numEdge << "条边: " << endl;
//    for(int i = 0; i < numEdge; i++)
//        cout << edges[i].tail << " --> " << edges[i].head << endl;