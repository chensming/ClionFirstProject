//
// Created by Dell on 2019/12/18.
//

#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

void showMainOperation();

//���������
template <class T>
struct BinTreeNode
{
    T data;
    BinTreeNode *leftchild, *rightchild;
    BinTreeNode() : leftchild(0), rightchild(0) {}
    BinTreeNode(T x, BinTreeNode *l = 0, BinTreeNode *r = 0) : data(x), leftchild(l), rightchild(r) {}
};

//����ǵݹ�����õ��Ľṹ
template <class T>
struct stkNode
{
    BinTreeNode<T> *ptr;
    int tag; //0������1������
    stkNode(BinTreeNode<T> *N = 0) : ptr(N), tag(0) {}
};

template <class T>
class BinaryTree
{
public:
    BinaryTree() : root(0) {}
    ~BinaryTree() {}

    //����
    void Create();
    void Create(BinTreeNode<T> *&BT, T endValue);
    //ɾ����
    void destroy();
    void destroy(BinTreeNode<T> *subTree);

    //ǰ��,����,����ݹ�����㷨
    void PreOrder(void (*visti)(BinTreeNode<T> *p)) const;
    void InOrder(void (*visit)(BinTreeNode<T> *p)) const;
    void PostOrder(void (*visit)(BinTreeNode<T> *p)) const;
    //����ǰ�����򣬺���ݹ������㷨
    void PreOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p)) const;
    void InOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p)) const;
    void PostOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p)) const;
    //ǰ��,���򣬺���ǵݹ��㷨
    void PreOrderNonRecursion(void (*visit)(BinTreeNode<T> *p));
    void InOrderNonRecursion(void (*visit)(BinTreeNode<T> *p));
    void PostOrderNonRecursion(void (*visit)(BinTreeNode<T> *p));

    //��α���
    void LevelOrder(void (*visit)(BinTreeNode<T> *p));

    //������
    int Height() const;
    int Height(BinTreeNode<T> *subTree) const;
    int HeightNoRecursion();

    //�������
    int Size() const;                        //�Ӹ���ʼ
    int Size(BinTreeNode<T> *subTree) const; //ǰ�����˳��
    int SizeNonRecursionByLevelOrder();      //�ǵݹ鷽��,��α���˳��
    int SizeNonRecursionByPreOrder();        //�ǵݹ鷽��,ǰ�����˳��

    //��Ҷ�ӽ������
    int LeavesSize() const;                  //�Ӹ���ʼ
    int LeavesSize(BinTreeNode<T> *t) const; //ǰ�����˳��
    int LeavesSizeNonRecursionByLevelOrder();
    int LeavesSizeNonRecursionByPreOrder();

    //��������������
    void PrintBinTree();
    void PrintBinTree(BinTreeNode<T> *BT);

private:
    BinTreeNode<T> *root;
};

//////////////////////////////////////////////////////////////////////////////

//�Ӹ���ʼ������
template <class T>
void BinaryTree<T>::Create()
{
    cout << "����������ı�־" << endl;
    T endValue;
    cin >> endValue;
    cout << "���������������ֵ (0����)" << endl;
    Create(root, endValue);
}

//ǰ��˳����������
template <class T>
void BinaryTree<T>::Create(BinTreeNode<T> *&BT, T endValue)
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

//�Ӹ���ʼɾ��
template <class T>
void BinaryTree<T>::destroy()
{
    destroy(root);
}

//ɾ����subtreeΪ������
template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T> *subTree)
{
    if (subTree != 0)
    {
        destroy(subTree->leftchild);
        destroy(subTree->rightchild);
        delete subTree;
    }
    root = 0; //��Ȼɾ������ᱨ��
}

//////////////////////////////////////////////////////////////////////////////////

//ǰ��,����,����ݹ�����㷨
template <class T>
void BinaryTree<T>::PreOrder(void (*visit)(BinTreeNode<T> *p)) const
{
    if (root == 0)
    {
        cout << "����Ϊ��" << endl;
        return;
    }
    PreOrder(root, visit);
}

template <class T>
void BinaryTree<T>::InOrder(void (*visit)(BinTreeNode<T> *p)) const
{
    if (root == 0)
    {
        cout << "����Ϊ��" << endl;
        return;
    }
    InOrder(root, visit);
}

template <class T>
void BinaryTree<T>::PostOrder(void (*visit)(BinTreeNode<T> *p)) const
{
    if (root == 0)
    {
        cout << "����Ϊ��" << endl;
        return;
    }
    PostOrder(root, visit);
}

//ǰ�����򣬺����������

template <class T>
void BinaryTree<T>::PreOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p)) const
{
    if (subTree != 0)
    {
        visit(subTree);
        PreOrder(subTree->leftchild, visit);
        PreOrder(subTree->rightchild, visit);
    }
}

template <class T>
void BinaryTree<T>::InOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p)) const
{
    if (subTree != 0)
    {
        InOrder(subTree->leftchild, visit);
        visit(subTree);
        InOrder(subTree->rightchild, visit);
    }
}
template <class T>
void BinaryTree<T>::PostOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p)) const
{
    if (subTree != 0)
    {
        PostOrder(subTree->leftchild, visit);
        PostOrder(subTree->rightchild, visit);
        visit(subTree);
    }
}

//�ǵݹ�ǰ�����򣬺�������㷨
template <class T>
void BinaryTree<T>::PreOrderNonRecursion(void (*visit)(BinTreeNode<T> *p))
{
    if (root == 0)
    {
        cout << "����Ϊ��" << endl;
        return;
    }
    stack<BinTreeNode<T> *> S;
    BinTreeNode<T> *p = root;
    do
    {
        //һֱ����,���ʲ���¼����Ա㷵��
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

template <class T>
void BinaryTree<T>::InOrderNonRecursion(void (*visit)(BinTreeNode<T> *p))
{
    if (root == 0)
    {
        cout << "����Ϊ��" << endl;
        return;
    }
    stack<BinTreeNode<T> *> S;
    BinTreeNode<T> *p = root;
    do
    {
        //һֱ����,���ʲ���¼����Ա㷵��
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

template <class T>
void BinaryTree<T>::PostOrderNonRecursion(void (*visit)(BinTreeNode<T> *p))
{
    if (root == 0)
    {
        cout << "����Ϊ��" << endl;
        return;
    }
    stack<stkNode<T>> S;
    stkNode<T> w;
    BinTreeNode<T> *p = root;
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
                    continuing = false; //ֹͣ���whileѭ��,����ȥ�������������0
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

//��α���
template <class T>
void BinaryTree<T>::LevelOrder(void (*visit)(BinTreeNode<T> *p))
{
    queue<BinTreeNode<T> *> Q;
    BinTreeNode<T> *p = root;
    Q.push(p); //ָ����ڵ��ָ�����
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

//������
template <class T>
int BinaryTree<T>::Height() const
{
    return Height(root);
}

template <class T>
int BinaryTree<T>::Height(BinTreeNode<T> *subTree) const
{
    if (subTree == 0)
    {
        return 0;
    }
    int leftchildHeight = Height(subTree->leftchild);
    int rightchildHeight = Height(subTree->rightchild);
    return (leftchildHeight > rightchildHeight) ? leftchildHeight + 1 : rightchildHeight + 1;
}

//�ǵݹ�������,��α���˳��
template <class T>
int BinaryTree<T>::HeightNoRecursion()
{
    int depth = 0;
    BinTreeNode<T> *p = root;
    queue<BinTreeNode<T> *> q;
    q.push(p); //��ָ�����
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

//�������
template <class T>
int BinaryTree<T>::Size() const
{
    return Size(root);
}

template <class T>
int BinaryTree<T>::Size(BinTreeNode<T> *subTree) const
{
    if (subTree == 0)
        return 0;
    return 1 + Size(subTree->leftchild) + Size(subTree->rightchild);
}

//�ǵݹ���ڵ����,��α���˳��
template <class T>
int BinaryTree<T>::SizeNonRecursionByLevelOrder()
{
    //�������Ϊ�գ���ڵ���Ϊ0
    if (root == 0)
        return 0;
    //������գ������ִ������Ĳ���
    int size = 1; //�����и��ڵ�
    BinTreeNode<T> *p = root;
    queue<BinTreeNode<T> *> Q;
    Q.push(p); ////��ָ�����
    while (!Q.empty())
    {
        int width = Q.size(); //��ȡ��ǰ��ο��,Ҳ����֪����һ��ε����нڵ����
        for (int i = 0; i < width; i++)
        {
            p = Q.front(); //��ȡ�Ӷ�Ԫ��
            Q.pop();       //�����Ӷ�Ԫ��
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

template <class T>
int BinaryTree<T>::SizeNonRecursionByPreOrder()
{
    if (root == 0)
        return 0;
    stack<BinTreeNode<T> *> S;
    BinTreeNode<T> *p = root;
    int size = 0; //��������
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

//��Ҷ�ӽ����Ŀ
template <class T>
int BinaryTree<T>::LeavesSize() const
{
    return LeavesSize(root);
}

template <class T>
int BinaryTree<T>::LeavesSize(BinTreeNode<T> *t) const
{
    if (t == 0)
        return 0;
    if (t->leftchild == 0 && t->rightchild == 0)
        return 1;
    return LeavesSize(t->leftchild) + LeavesSize(t->rightchild);
}

template <class T>
int BinaryTree<T>::LeavesSizeNonRecursionByLevelOrder()
{
    //�������Ϊ�գ���ڵ���Ϊ0
    if (root == 0)
        return 0;
    //��ʼʱҶ�ӽ���������0
    int size = 0;
    BinTreeNode<T> *p = root;
    queue<BinTreeNode<T> *> Q;
    Q.push(p); //��ָ�����
    while (!Q.empty())
    {
        int width = Q.size(); //��ȡ��ǰ��ο��,Ҳ����֪����һ��ε����нڵ����
        for (int i = 0; i < width; i++)
        {
            p = Q.front(); //��ȡ�Ӷ�Ԫ��
            Q.pop();       //�����Ӷ�Ԫ��
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

template <class T>
int BinaryTree<T>::LeavesSizeNonRecursionByPreOrder()
{
    if (root == 0)
        return 0;
    stack<BinTreeNode<T> *> S;
    BinTreeNode<T> *p = root;
    int size = 0;
    do
    {
        while (p != 0)
        {
            S.push(p);
            //Ҷ�ӽ����
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

//��������������
template <class T>
void BinaryTree<T>::PrintBinTree()
{
    PrintBinTree(root);
}

template <class T>
void BinaryTree<T>::PrintBinTree(BinTreeNode<T> *BT)
{
    if (BT != 0)
    {
        cout << BT->data;
        if (BT->leftchild != 0 || BT->rightchild != 0)
        {
            cout << "(";
            PrintBinTree(BT->leftchild); // �ݹ����������
            if (BT->rightchild != 0)
            {
                cout << ",";
                PrintBinTree(BT->rightchild); // �ݹ����������
            }
            cout << ")";
        }
    }
}

//������dataֵ�ĺ���
template <class T>
void PrintData(BinTreeNode<T> *p)
{
    cout << p->data << " ";
}

#endif //BINARYTREE_BINARYTREE_H
