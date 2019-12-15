//
// Created by Dell on 2019/12/15.
//

#include <iostream>
using namespace std;

const int DefaultSize = 10;

class UFsets {
public:
    UFsets(int sz = DefaultSize);
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





int main()
{
    UFsets a;

    cout << endl;
    cout << "parent表: 结点编号(父节点的编号)" << endl;
    a.PrintParentList();

    a.Union(5, 6);
    cout << endl;
    cout << "parent表: 结点编号(父节点的编号)" << endl;
    a.PrintParentList();

    a.Union(6, 3);
    cout << endl;
    cout << "parent表: 结点编号(父节点的编号)" << endl;
    a.PrintParentList();

    a.Union(6, 4);
    cout << endl;
    cout << "parent表: 结点编号(父节点的编号)" << endl;
    a.PrintParentList();

    a.Union(7, 1);
    cout << endl;
    cout << "parent表: 结点编号(父节点的编号)" << endl;
    a.PrintParentList();

    a.Union(7, 2);
    cout << endl;
    cout << "parent表: 结点编号(父节点的编号)" << endl;
    a.PrintParentList();

    a.Union(9, 0);
    cout << endl;
    cout << "parent表: 结点编号(父节点的编号)" << endl;
    a.PrintParentList();

    a.Union(8, 5);
    cout << endl;
    cout << "parent表: 结点编号(父节点的编号)" << endl;
    a.PrintParentList();

    a.Union(8, 7);
    cout << endl;
    cout << "parent表: 结点编号(父节点的编号)" << endl;
    a.PrintParentList();

    a.Union(9, 8);
    cout << endl;
    cout << "parent表: 结点编号(父节点的编号)" << endl;
    a.PrintParentList();

    cout << endl;
    system("pause");
}




