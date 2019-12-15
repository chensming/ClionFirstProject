//
// Created by Dell on 2019/12/15.
//

#include<iostream>
#include<stack>
using namespace std;

template<class T>
struct BSTNode {
    T data;
    BSTNode<T>* leftchild, * rightchild;
    BSTNode() : leftchild(0), rightchild(0) { data = T(); }
    BSTNode(T d) : data(d), leftchild(0), rightchild(0){}
    ~BSTNode(){}

    void setData(T d) { data = d; }
    T getData() { return data; }
};


template<class T>
class BST {
public:
    BST() :root(0) { Refvalue = T(); }
    BST(T value);
    ~BST() { makeEmpty(); }

    //置空（包括删除根节点）
    void makeEmpty();
    void makeEmpty(BSTNode<T>* ptr);

    //递归与非递归搜索
    bool Search(const T x) const;
    BSTNode<T>* Search(const T x, BSTNode<T>* ptr)const;
    BSTNode<T>* SearchNonRecursion(const T x) const;

    //递归与非递归插入
    bool Insert(const T x);
    bool Insert(const T x, BSTNode<T>*& ptr);
    bool InsertNonRecursion(const T x);

    //递归删除
    bool Remove(const T x);
    bool Remove(const T x, BSTNode<T>*& ptr);
    //bool RemoveNonRecursion(const T x);非递归比较麻烦,这里没写

    //广义表输出二叉树
    void PrintBinTree();
    void PrintBinTree(BSTNode<T>* BT);

    //中序递归与非递归遍历输出
    void InOrder();
    void InOrder(BSTNode<T>* subtree);
    void InOrderNonRecursion();

private:
    BSTNode<T>* root;
    T Refvalue; // 输入的终止标志值
};





template<class T>
BST<T>::BST(T value)
{
    T x;
    root = 0;
    Refvalue = value;
    cout << "请分别输入二叉搜索树的结点的值" << endl;
    cin >> x;
    while (x != Refvalue)
    {
        Insert(x, root);
        cin >> x;
    }
}






template<class T>
void BST<T>::makeEmpty()
{
    makeEmpty(root);
    root = 0;
}



template<class T>
void BST<T>::makeEmpty(BSTNode<T>* ptr)
{
    if (ptr != 0)
    {
        makeEmpty(ptr->leftchild);
        makeEmpty(ptr->rightchild);
        delete ptr;
    }
}




template<class T>
bool BST<T>::Search(const T x) const
{
    return (Search(x, root) != 0) ? true : false;
}



template<class T>
BSTNode<T>* BST<T>::Search(const T x, BSTNode<T>* ptr) const
{
    if (ptr == 0)
        return 0;
    else if (x < ptr->data)
        return Search(x, ptr->leftchild);
    else if (x > ptr->data)
        return Search(x, ptr->rightchild);
    else
        return ptr;
}




template<class T>
BSTNode<T>* BST<T>::SearchNonRecursion(const T x) const
{
    BSTNode<T>* p = root;
    while (p != 0)
    {
        if (p->data == x)
            return p;
        else if (x < p->data)
            p = p->leftchild;
        else
            p = p->rightchild;
    }
    return 0;
}








template<class T>
bool BST<T>::Insert(const T x)
{
    return Insert(x, root);
}





template<class T>
bool BST<T>::Insert(const T x, BSTNode<T>*& ptr)
{
    if (ptr == 0)
    {
        ptr = new BSTNode<T>(x);
        if (ptr == 0)
        {
            cerr << "内存分配错误" << endl;
            exit(1);
        }
        return true;
    }
    else if (x < ptr->data)
        Insert(x, ptr->leftchild);
    else if (x > ptr->data)
        Insert(x, ptr->rightchild);
    else return false; //已在树中，不需要插入
}




template<class T>
bool BST<T>::InsertNonRecursion(const T x)
{
    BSTNode<T>* BT, * f, * p;
    BT = root;
    f = 0;
    while (BT != 0)
    {
        if (x == BT->data)
            return -1;
        else if (x < BT->data)
        {
            f = BT;
            BT = BT->leftchild;
        }
        else
        {
            f = BT;
            BT = BT->rightchild;
        }
    }
    p = new BSTNode<T>;
    p->data = x;
    p->leftchild = p->rightchild = 0;
    if (f == 0)
        root = p;
    else if (x > p->data)
        f->rightchild = p;
    else
        f->rightchild = p;
    return true;
}


template<class T>
bool BST<T>::Remove(const T x)
{
    return Remove(x, root);
}






template<class T>
bool BST<T>::Remove(const T x, BSTNode<T>*& ptr)
{
    BSTNode<T>* temp;
    if (ptr != 0)
    {
        if (x < ptr->data)
            return Remove(x, ptr->leftchild);
        else if (x > ptr->data)
            return Remove(x, ptr->rightchild);
            //等于的情况
        else if (ptr->leftchild != 0 && ptr->rightchild != 0)
        {
            temp = ptr->rightchild;
            while (temp->leftchild != 0)
                temp = temp->leftchild;
            ptr->data = temp->data;
            Remove(ptr->data, ptr->rightchild);
            return true;
        }
        else {
            //引用的作用在下面if和else语句中体现了
            temp = ptr;
            //连接右子树或将其置空
            if (ptr->leftchild == 0)
                ptr = ptr->rightchild;
            else
                ptr = ptr->leftchild;
            delete temp;
            return true;
        }
    }
}







template<class T>
void BST<T>::PrintBinTree()
{
    PrintBinTree(root);
}




template<class T>
void BST<T>::PrintBinTree(BSTNode<T> * BT)
{
    if (BT != 0)
    {
        cout << BT->data;
        if (BT->leftchild != 0 || BT->rightchild != 0)
        {
            cout << "(";
            if (BT->leftchild != 0)
                PrintBinTree(BT->leftchild);
            if (BT->rightchild != 0)
            {
                cout << ",";
                PrintBinTree(BT->rightchild);
            }
            cout << ")";
        }

    }
}





template<class T>
void BST<T>::InOrder()
{
    InOrder(root);
    cout << endl;
}




template<class T>
void BST<T>::InOrder(BSTNode<T>* subtree)
{
    if (subtree != 0)
    {
        InOrder(subtree->leftchild);
        cout << subtree->data << " ";
        InOrder(subtree->rightchild);
    }
}






template<class T>
void BST<T>::InOrderNonRecursion()
{
    if (root == 0)
    {
        cout << "该树为空" << endl;
        return;
    }
    stack<BSTNode<T>*>S;
    BSTNode<T>* p = root;
    while (p != 0 || !S.empty())
    {
        while (p != 0)
        {
            S.push(p);
            p = p->leftchild;
        }
        if (!S.empty())
        {
            p = S.top();
            S.pop();
            cout << p->data << " ";
            p = p->rightchild;
        }
    }
    cout << endl;
}


















int main()
{
    BST<int> a;

    a.Insert(16);
    a.Insert(8);
    a.Insert(3);
    a.Insert(22);
    a.Insert(18);
    a.Insert(3);
    a.Insert(36);
    a.Insert(24);
    a.Insert(-6);
    a.Insert(-7);



    cout << endl;
    cout << "以广义表输出树结点的值" << endl;
    a.PrintBinTree();

    cout << endl << endl;
    if (a.Search(24))
        cout << "搜索 24 成功" << endl;
    else
        cout << "搜索 24 失败" << endl;
    cout << endl;

    if (a.SearchNonRecursion(36) != 0)
        cout << "搜索 36 成功" << endl;
    else
        cout << "搜索 36 失败" << endl;
    cout << endl;

    if (a.Remove(-6))
        cout << "删除 -6 成功" << endl;
    else
        cout << "删除 -6 失败" << endl;
    cout << endl;

    if (a.Search(-6))
        cout << "搜索 -6 成功" << endl;
    else
        cout << "搜索 -6 失败" << endl;
    cout << endl;


    cout << endl;
    cout << "以广义表输出树结点的值" << endl;
    a.PrintBinTree();


    a.InsertNonRecursion(100);
    a.InsertNonRecursion(30);
    a.InsertNonRecursion(20);
    cout << endl;
    cout << "以广义表输出树结点的值" << endl;
    a.PrintBinTree();

    cout << "中序遍历" << endl;
    a.InOrder();

    cout << "非递归中序遍历" << endl;
    a.InOrderNonRecursion();

    cout << endl;
    system("pause");
}








