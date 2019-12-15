#include <iostream>
#include<stack>
#include<queue>
using namespace std;


//二叉树结点
template<class T>
struct BinTreeNode
{
    T data;
    BinTreeNode* leftchild, * rightchild;
    BinTreeNode() : leftchild(0), rightchild(0) {}
    BinTreeNode(T x, BinTreeNode* l = 0, BinTreeNode * r = 0) : data(x), leftchild(l), rightchild(r) {}
};

//后序非递归遍历用到的结构
template<class T>
struct stkNode {
    BinTreeNode<T>* ptr;
    int tag; //0代表左，1代表右
    stkNode(BinTreeNode<T>* N = 0) : ptr(N), tag(0) {}
};

template<class T>
class BinaryTree {
public:
    BinaryTree() : root(0) {}
    ~BinaryTree() {}

    //建树
    void Create();
    void Create(BinTreeNode<T>*& BT, T endValue);
    //删除树
    void destroy();
    void destroy(BinTreeNode<T>* subTree);

    //前序,中序,后序递归遍历算法
    void PreOrder(void(*visti)(BinTreeNode<T>* p)) const;
    void InOrder(void(*visit)(BinTreeNode<T>* p)) const;
    void PostOrder(void (*visit)(BinTreeNode<T>* p)) const;
    //重载前序，中序，后序递归排序算法
    void PreOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>* p)) const;
    void InOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>* p)) const;
    void PostOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>* p)) const;
    //前序,中序，后序非递归算法
    void PreOrderNonRecursion(void(*visit)(BinTreeNode<T>* p));
    void InOrderNonRecursion(void(*visit)(BinTreeNode<T>* p));
    void PostOrderNonRecursion(void(*visit)(BinTreeNode<T>* p));

    //层次遍历
    void LevelOrder(void (*visit)(BinTreeNode<T>* p));

    //求树高
    int Height() const;
    int Height(BinTreeNode<T>* subTree) const;
    int HeightNoRecursion();

    //求节点个数
    int Size() const;                       //从根开始
    int Size(BinTreeNode<T>* subTree) const;      //前序遍历顺序
    int SizeNonRecursionByLevelOrder();     //非递归方法,层次遍历顺序
    int SizeNonRecursionByPreOrder();       //非递归方法,前序遍历顺序

    //求叶子结点总数
    int LeavesSize() const;   //从根开始
    int LeavesSize(BinTreeNode<T>* t) const;   //前序遍历顺序
    int LeavesSizeNonRecursionByLevelOrder();
    int LeavesSizeNonRecursionByPreOrder();

    //广义表输出二叉树
    void PrintBinTree();
    void PrintBinTree(BinTreeNode<T>* BT);

private:
    BinTreeNode<T>* root;
};










//////////////////////////////////////////////////////////////////////////////

//从根开始建立树
template<class T>
void BinaryTree<T>::Create()
{
    cout << "请输入结束的标志" << endl;
    T endValue;
    cin >> endValue;
    cout << "请输入二叉树结点的值 (0结束)" << endl;
    Create(root, endValue);
}


//前序顺序建立二叉树
template<class T>
void BinaryTree<T>::Create(BinTreeNode<T>*& BT, T endValue)
{

    T x;
    cin >> x;
    if (x == endValue)
    {
        BT = 0;
    }
    else
    {
        BT = new BinTreeNode<T>(x);
        Create(BT->leftchild, endValue);
        Create(BT->rightchild, endValue);
    }
}


//从根开始删除
template<class T>
void BinaryTree<T>::destroy()
{
    destroy(root);
}

//删除以subtree为根的树
template<class T>
void BinaryTree<T>::destroy(BinTreeNode<T>* subTree)
{
    if (subTree != 0)
    {
        destroy(subTree->leftchild);
        destroy(subTree->rightchild);
        delete subTree;
    }
    root = 0;  //不然删完遍历会报错
}






//////////////////////////////////////////////////////////////////////////////////

//前序,中序,后序递归遍历算法
template<class T>
void BinaryTree<T>::PreOrder(void (*visit)(BinTreeNode<T>* p)) const
{
    if (root == 0)
    {
        cout << "该树为空" << endl;
        return;
    }
    PreOrder(root, visit);
}



template<class T>
void BinaryTree<T>::InOrder(void (*visit)(BinTreeNode<T>* p)) const
{
    if (root == 0)
    {
        cout << "该树为空" << endl;
        return;
    }
    InOrder(root, visit);
}



template<class T>
void BinaryTree<T>::PostOrder(void (*visit)(BinTreeNode<T>* p)) const
{
    if (root == 0)
    {
        cout << "该树为空" << endl;
        return;
    }
    PostOrder(root, visit);
}




//前序，中序，后序遍历重载

template<class T>
void BinaryTree<T>::PreOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>* p)) const
{
    if (subTree != 0)
    {
        visit(subTree);
        PreOrder(subTree->leftchild, visit);
        PreOrder(subTree->rightchild, visit);
    }
}


template<class T>
void BinaryTree<T>::InOrder(BinTreeNode<T>* subTree, void (*visit)(BinTreeNode<T>* p)) const
{
    if (subTree != 0)
    {
        InOrder(subTree->leftchild, visit);
        visit(subTree);
        InOrder(subTree->rightchild, visit);
    }
}
template<class T>
void BinaryTree<T>::PostOrder(BinTreeNode<T>* subTree, void(*visit)(BinTreeNode<T>* p)) const
{
    if (subTree != 0)
    {
        PostOrder(subTree->leftchild, visit);
        PostOrder(subTree->rightchild, visit);
        visit(subTree);
    }
}






//非递归前序，中序，后序遍历算法
template<class T>
void BinaryTree<T>::PreOrderNonRecursion(void(*visit)(BinTreeNode<T>* p))
{
    if (root == 0)
    {
        cout << "该树为空" << endl;
        return;
    }
    stack<BinTreeNode<T>*> S;
    BinTreeNode<T>* p = root;
    do
    {
        //一直往左,访问并记录结点以便返回
        while (p != 0)
        {
            S.push(p);
            visit(p);
            p = p->leftchild;
        }
        if (!S.empty())
        {
            p = S.top();
            S.pop();
            p = p->rightchild;
        }
    } while (p != 0 || !S.empty());
    cout << endl;
}


template<class T>
void BinaryTree<T>::InOrderNonRecursion(void(*visit)(BinTreeNode<T>* p))
{
    if (root == 0)
    {
        cout << "该树为空" << endl;
        return;
    }
    stack<BinTreeNode<T>*> S;
    BinTreeNode<T>* p = root;
    do {
        //一直往左,访问并记录结点以便返回
        while (p != 0)
        {
            S.push(p);
            p = p->leftchild;
        }
        if (!S.empty())
        {
            p = S.top();
            S.pop();
            visit(p);
            p = p->rightchild;
        }
    } while (p != 0 || !S.empty());
    cout << endl;
}


template<class T>
void BinaryTree<T>::PostOrderNonRecursion(void(*visit)(BinTreeNode<T>* p))
{
    if (root == 0)
    {
        cout << "该树为空" << endl;
        return;
    }
    stack<stkNode<T>> S;
    stkNode<T> w;
    BinTreeNode<T>* p = root;
    do
    {
        while (p != 0)
        {
            w.ptr = p;
            w.tag = 0;
            S.push(w);
            p = p->leftchild;
        }
        bool continuing = true;
        while (continuing && !S.empty())
        {
            w = S.top();
            S.pop();
            p = w.ptr;
            switch (w.tag)
            {
                case 0:
                    w.tag = 1;
                    S.push(w);
                    continuing = false; //停止这个while循环,让它去找最左的左子树0
                    p = p->rightchild;
                    break;
                case 1:
                    visit(p);
                    break;
            }
        }
    } while (!S.empty());
    cout << endl;
}



//层次遍历
template<class T>
void BinaryTree<T>::LevelOrder(void(*visit)(BinTreeNode<T>* p))
{
    queue<BinTreeNode<T>*> Q;
    BinTreeNode<T>* p = root;
    Q.push(p);//指向根节点的指针入队
    while (!Q.empty())
    {
        p = Q.front();
        Q.pop();
        visit(p);
        if (p->leftchild != 0)
        {
            Q.push(p->leftchild);
        }

        if (p->rightchild != 0)
        {
            Q.push(p->rightchild);
        }
    }
}






//求树高
template<class T>
int BinaryTree<T>::Height() const
{
    return Height(root);
}


template<class T>
int BinaryTree<T>::Height(BinTreeNode<T>* subTree) const
{
    if (subTree == 0)
    {
        return 0;
    }
    int leftchildHeight = Height(subTree->leftchild);
    int rightchildHeight = Height(subTree->rightchild);
    return (leftchildHeight > rightchildHeight) ? leftchildHeight + 1 : rightchildHeight + 1;
}


//非递归求树高,层次遍历顺序
template<class T>
int BinaryTree<T>::HeightNoRecursion()
{
    int depth = 0;
    BinTreeNode<T>* p = root;
    queue<BinTreeNode<T>*> q;
    q.push(p);  //根指针入队
    while (!q.empty())
    {
        depth++;
        int width = q.size();
        for (int i = 0; i < width; i++)
        {
            p = q.front();
            q.pop();
            if (p->leftchild != 0)
                q.push(p->leftchild);
            if (p->rightchild != 0)
                q.push(p->rightchild);
        }
    }
    return depth;
}






//求结点个数
template<class T>
int BinaryTree<T>::Size() const
{
    return Size(root);
}


template<class T>
int BinaryTree<T>::Size(BinTreeNode<T>* subTree) const
{
    if (subTree == 0)
        return 0;
    return 1 + Size(subTree->leftchild) + Size(subTree->rightchild);
}




//非递归求节点个数,层次遍历顺序
template<class T>
int BinaryTree<T>::SizeNonRecursionByLevelOrder()
{
    //如果树根为空，则节点数为0
    if (root == 0)
        return 0;
    //如果不空，则可以执行下面的操作
    int size = 1;  //至少有根节点
    BinTreeNode<T>* p = root;
    queue<BinTreeNode<T>*> Q;
    Q.push(p);  ////根指针入队
    while (!Q.empty())
    {
        int width = Q.size();  //获取当前层次宽度,也就是知道下一层次的所有节点个数
        for (int i = 0; i < width; i++)
        {
            p = Q.front();     //获取队顶元素
            Q.pop();          //弹出队顶元素
            if (p->leftchild != 0)
            {
                size++;
                Q.push(p->leftchild);
            }
            if (p->rightchild != 0)
            {
                size++;
                Q.push(p->rightchild);
            }
        }
    }
    return size;
}



template<class T>
int BinaryTree<T>::SizeNonRecursionByPreOrder()
{
    if (root == 0)
        return 0;
    stack<BinTreeNode<T>*> S;
    BinTreeNode<T>* p = root;
    int size = 0;  //结点计数器
    do
    {
        while (p != 0)
        {
            S.push(p);
            size++;
            p = p->leftchild;
        }
        if (!S.empty())
        {
            p = S.top();
            S.pop();
            p = p->rightchild;
        }
    } while (p != 0 || !S.empty());
    return size;
}



//求叶子结点数目
template<class T>
int BinaryTree<T>::LeavesSize() const
{
    return LeavesSize(root);
}



template<class T>
int BinaryTree<T>::LeavesSize(BinTreeNode<T>* t) const
{
    if (t == 0)
        return 0;
    if (t->leftchild == 0 && t->rightchild == 0)
        return 1;
    return LeavesSize(t->leftchild) + LeavesSize(t->rightchild);
}





template<class T>
int BinaryTree<T>::LeavesSizeNonRecursionByLevelOrder()
{
    //如果树根为空，则节点数为0
    if (root == 0)
        return 0;
    //初始时叶子结点计数器置0
    int size = 0;
    BinTreeNode<T>* p = root;
    queue<BinTreeNode<T>*> Q;
    Q.push(p);   //根指针入队
    while (!Q.empty())
    {
        int width = Q.size();       //获取当前层次宽度,也就是知道下一层次的所有节点个数
        for (int i = 0; i < width; i++)
        {
            p = Q.front();       //获取队顶元素
            Q.pop();			//弹出队顶元素
            if (p->leftchild == 0 && p->rightchild == 0)
            {
                size++;
            }
            else
            {
                if (p->leftchild != 0)
                    Q.push(p->leftchild);
                if (p->rightchild != 0)
                    Q.push(p->rightchild);
            }
        }
    }
    return size;
}



template<class T>
int BinaryTree<T>::LeavesSizeNonRecursionByPreOrder()
{
    if (root == 0)
        return 0;
    stack<BinTreeNode<T>*>S;
    BinTreeNode<T>* p = root;
    int size = 0;
    do {
        while (p != 0)
        {
            S.push(p);
            //叶子结点呢
            if (p->leftchild == 0 && p->rightchild == 0)
            {
                size++;
                break;
            }
            p = p->leftchild;
        }
        if (!S.empty())
        {
            p = S.top();
            S.pop();
            p = p->rightchild;
        }
    } while (p != 0 || !S.empty());
    return size;
}




//广义表输出二叉树
template<class T>
void BinaryTree<T>::PrintBinTree()
{
    PrintBinTree(root);
}



template<class T>
void BinaryTree<T>::PrintBinTree(BinTreeNode<T>* BT)
{
    if (BT != 0)
    {
        cout << BT->data;
        if (BT->leftchild != 0 || BT->rightchild != 0)
        {
            cout << "(";
            PrintBinTree(BT->leftchild);  // 递归输出左子树
            if (BT->rightchild != 0)
            {
                cout << ",";
                PrintBinTree(BT->rightchild); // 递归输出右子树
            }
            cout << ")";
        }
    }
}




















//输出结点data值的函数
template<class T>
void PrintData(BinTreeNode<T>* p)
{
    cout << p->data << " ";
}





int main()
{
    BinaryTree<char> a;
    a.Create();

    cout << endl << endl;
    cout << "前序递归遍历" << endl;
    a.PreOrder(PrintData);

    cout << endl << endl;
    cout << "中序递归遍历" << endl;
    a.InOrder(PrintData);

    cout << endl << endl;
    cout << "后序递归遍历" << endl;
    a.PostOrder(PrintData);

    cout << endl << endl << endl;
    cout << "前序非递归遍历" << endl;
    a.PreOrderNonRecursion(PrintData);

    cout << endl;
    cout << "中序非递归遍历" << endl;
    a.InOrderNonRecursion(PrintData);

    cout << endl;
    cout << "后序非递归遍历" << endl;
    a.PostOrderNonRecursion(PrintData);

    cout << endl;
    cout << "层次遍历" << endl;
    a.LevelOrder(PrintData);

    cout << endl;
    cout << "递归求树的高度" << endl;
    cout << "height: " << a.Height();

    cout << endl << endl;
    cout << "非递归求树的高度" << endl;
    cout << "height: " << a.HeightNoRecursion();

    cout << endl << endl << endl << endl;
    cout << "递归求结点个数" << endl;
    cout << "size: " << a.Size();

    cout << endl << endl;
    cout << "层次顺序非递归求结点个数" << endl;
    cout << "size: " << a.SizeNonRecursionByLevelOrder();

    cout << endl << endl;
    cout << "前序顺序非递归求结点个数" << endl;
    cout << "size: " << a.SizeNonRecursionByPreOrder();


    cout << endl << endl;
    cout << "***************************************************" << endl;
    cout << endl << endl;
    cout << "递归求叶子结点总数" << endl;
    cout << "leavesSize: " << a.LeavesSize() << endl;

    cout << endl << endl;
    cout << "层次顺序非递归方法求叶子结点总数" << endl;
    cout << "leavesSize: " << a.LeavesSizeNonRecursionByLevelOrder() << endl;

    cout << endl << endl;
    cout << "前序顺序非递归方法求叶子结点总数" << endl;
    cout << "leavesSize: " << a.LeavesSizeNonRecursionByPreOrder() << endl;


    cout << endl << endl;
    cout << "广义表输出" << endl;
    a.PrintBinTree();

    cout << endl;
}
