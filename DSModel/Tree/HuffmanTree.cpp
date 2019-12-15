//
// Created by Dell on 2019/12/15.
//
#include<vector>
#include<iostream>
#include<algorithm>
#include<queue>
#include<iomanip>

using namespace std;



struct HuffmanNode {
    float data;
    //char ch;
    HuffmanNode* leftchild, * rightchild, * parent;
    HuffmanNode():data(-1),leftchild(0),rightchild(0),parent(0){}
    //HuffmanNode(const HuffmanNode& h);
    HuffmanNode(float elem,HuffmanNode *left = 0,HuffmanNode *right = 0,HuffmanNode* pr = 0):
            data(elem),leftchild(left),rightchild(right),parent(pr){}
    bool operator <=(HuffmanNode& R) { return data <= R.data; }
    bool operator >(HuffmanNode& R) { return data > R.data; }
};

/*
HuffmanNode::HuffmanNode(const HuffmanNode& h)
{
	data = h.data;
	leftchild = h.leftchild;
	rightchild = h.rightchild;
	//其实parent这个写不写无所谓，因为如果parent！=null，
	//就证明已经和其他节点合成一个父节点了,不会被放到堆里面
	parent = h.parent;
}
*/


bool cmp(const HuffmanNode& a, const HuffmanNode& b)
{
    return a.data < b.data;
}




class HuffmanTree {
public:
    HuffmanTree(float w[], int n);
    ~HuffmanTree() { deleteTree(root); }
    void LevelOrder();
    void PrintGeneralizedList();
    void PrintGeneralizedList(HuffmanNode* BT);


private:
    HuffmanNode* root;
    void deleteTree(HuffmanNode* t);
    void mergeTree(HuffmanNode* h1, HuffmanNode* h2, HuffmanNode*& parent);
};






void display(vector<HuffmanNode>& v);//使用vector迭代器遍历





HuffmanTree::HuffmanTree(float w[], int n)
{
    //为了消除警告，root = 0，其实没必要，最后root = parent
    //已经包括这个情况了
    root = 0;
    vector<HuffmanNode> hp;
    HuffmanNode* parent = 0, *first, *second, *work;
    HuffmanNode tempFirst, tempSecond;
    for (int i = 0; i < n; i++)
    {
        work = new HuffmanNode;
        work->data = w[i];
        work->leftchild = 0;
        work->rightchild = 0;
        work->parent = 0;
        hp.push_back(*work);
        //make_heap(hp.begin(), hp.end(), cmp);
        //sort_heap(hp.begin(), hp.end(), cmp);
    }
    make_heap(hp.begin(), hp.end(), cmp);
    sort_heap(hp.begin(), hp.end(), cmp);
    for (int i = 0; i < n - 1; i++) {
        if (hp.empty())
        {
            cout << "堆empty" << endl;
            return;
        }
        tempFirst = hp.front();
        first = new HuffmanNode();
        first->data = tempFirst.data;
        first->leftchild = tempFirst.leftchild;
        first->rightchild = tempFirst.rightchild;
        first->parent = tempFirst.parent;
        hp.erase(hp.begin());

        cout << "把first取出来并删除,其值为 "<< (*first).data ;
        cout << " ,删除后的堆中元素: " << endl;
        display(hp);

        tempSecond = hp.front();
        second = new HuffmanNode();
        second->data = tempSecond.data;
        second->leftchild = tempSecond.leftchild;
        second->rightchild = tempSecond.rightchild;
        second->parent = tempSecond.parent;
        hp.erase(hp.begin());

        cout << "把second取出来并删除,其值为 " << (*second).data;
        cout << " ,删除后的堆中元素: " << endl;
        display(hp);

        mergeTree(first, second, parent);
        hp.push_back(*parent);
        make_heap(hp.begin(), hp.end(), cmp);
        sort_heap(hp.begin(), hp.end(), cmp);

        cout << "把 " << (*first).data << " 与 " << (*second).data << " merge，然后得到值 ";
        cout << (*parent).data << " ,把它插入后堆中元素: " << endl;
        display(hp);
        cout << endl;
    }
    root = parent;
}






void HuffmanTree::deleteTree(HuffmanNode* t)
{
    if (t != nullptr)
    {
        deleteTree(t->leftchild);
        deleteTree(t->rightchild);
        delete t;
    }
    root = 0;
}




void HuffmanTree::mergeTree(HuffmanNode* h1, HuffmanNode* h2, HuffmanNode*& parent)
{
    parent = new HuffmanNode;
    parent->leftchild = h1;
    parent->rightchild = h2;
    parent->data = h1->data + h2->data;
    h1->parent = h2->parent = parent;
}









void display(vector<HuffmanNode>& v)//使用vector迭代器遍历
{
    vector<HuffmanNode>::iterator i;
    for (i = v.begin(); i < v.end(); i++)
    {
        cout << (*i).data << " ";
    }
    cout << endl << endl;
}







void HuffmanTree::LevelOrder()
{
    int IsEven = 1;
    queue<HuffmanNode *> Q;
    HuffmanNode* p;
    Q.push(root);
    while (!Q.empty())
    {
        IsEven = 1;
        int width = Q.size();
        for (int i = 0; i < width; i++)
        {
            p = Q.front();
            Q.pop();
            IsEven = (IsEven + 1) % 2;
            cout << setw(4) << p->data;
            if (IsEven && i != width - 1)
                cout << " , ";
            if (p->leftchild != 0)
                Q.push(p->leftchild);
            if (p->rightchild != 0)
                Q.push(p->rightchild);
        }
        cout << endl;
    }
    cout << endl << endl << endl;
}





void HuffmanTree::PrintGeneralizedList()
{
    PrintGeneralizedList(root);
    cout << endl;
}


void HuffmanTree::PrintGeneralizedList(HuffmanNode* BT)
{
    if (BT != 0)
    {
        cout << BT->data;
        if (BT->leftchild != 0 || BT->rightchild != 0)
        {
            cout << "(";
            PrintGeneralizedList(BT->leftchild);
            if (BT->rightchild != 0)
            {
                cout << ",";
                PrintGeneralizedList(BT->rightchild);
            }
            cout << ")";
        }
    }
}






int main()
{
    float test[10] = { 1,5,2,6,3,7,8,4,9,10 };
    HuffmanTree ht1(test,10);
    cout << "构建成功" << endl;
    ht1.LevelOrder();

    cout << endl;
    ht1.PrintGeneralizedList();

    cout << endl;
    system("pause");
}
