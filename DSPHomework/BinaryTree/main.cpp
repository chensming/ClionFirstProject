#include <iostream>
#include "BinaryTree.h"
using namespace std;


template <class T>
void MainLoop(BinaryTree<T> &a)
{
    int choice = 12;
    do
    {
        switch (choice)
        {
            case 1:
                a.Create();
                break;
            case 2:
                cout << "前序递归: " << endl;
                a.PreOrder(PrintData);
                break;
            case 3:
                cout << "前序非递归: " << endl;
                a.PreOrderNonRecursion(PrintData);
                break;
            case 4:
                cout << "中序递归: " << endl;
                a.InOrder(PrintData);
                break;
            case 5:
                cout << "中序非递归: " << endl;
                a.InOrderNonRecursion(PrintData);
                break;
            case 6:
                cout << "后序递归: " << endl;
                a.PostOrder(PrintData);
                break;
            case 7:
                cout << "后序非递归: " << endl;
                a.PostOrderNonRecursion(PrintData);
                break;
            case 8:
                cout << "树的高度: " << a.Height() << endl;
                break;
            case 9:
                cout << "叶子结点数量: " << a.LeavesSize() << endl;
                break;
            case 10:
                a.PrintBinTree();
                break;
            case 11:
                cout << "left..." << endl;
                break;
            case 12:
                showMainOperation();
                break;
            default:
                cout << "输入有误" << endl;
                break;
        }
        cout << endl << endl;
        cout << " 请输入您想要的操作 " << endl;
        cin >> choice;
    } while (choice != 11);
}

void showMainOperation()
{
    cout << "*************************************************" << endl;
    cout << "1------建立一棵二叉树" << endl;
    cout << "2------前序遍历递归算法" << endl;
    cout << "3------前序遍历非递归算法" << endl;
    cout << "4------中序遍历递归算法" << endl;
    cout << "5------中序遍历非递归算法" << endl;
    cout << "6------后序遍历递归算法" << endl;
    cout << "7------后序遍历非递归算法" << endl;
    cout << "8------求树高" << endl;
    cout << "9------求叶子总数" << endl;
    cout << "10-----输出二叉树" << endl;
    cout << "11-----退出" << endl;
    cout << "12-----主菜单" << endl;
}


int main()
{
    BinaryTree<char> a;
    MainLoop(a);
    cout << endl;
    cout << "-------------------   感谢使用  -------------------";
    cout << endl
         << endl;
    system("pause");
}
