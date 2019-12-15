//
// Created by Dell on 2019/12/15.
//

#ifndef FIRSTPROJECT_UFSETS_H
#define FIRSTPROJECT_UFSETS_H
const int DefaultUFsetsSize = 30;


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









#endif //FIRSTPROJECT_UFSETS_H
