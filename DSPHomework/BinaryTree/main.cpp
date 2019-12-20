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
                cout << "ǰ��ݹ�: " << endl;
                a.PreOrder(PrintData);
                break;
            case 3:
                cout << "ǰ��ǵݹ�: " << endl;
                a.PreOrderNonRecursion(PrintData);
                break;
            case 4:
                cout << "����ݹ�: " << endl;
                a.InOrder(PrintData);
                break;
            case 5:
                cout << "����ǵݹ�: " << endl;
                a.InOrderNonRecursion(PrintData);
                break;
            case 6:
                cout << "����ݹ�: " << endl;
                a.PostOrder(PrintData);
                break;
            case 7:
                cout << "����ǵݹ�: " << endl;
                a.PostOrderNonRecursion(PrintData);
                break;
            case 8:
                cout << "���ĸ߶�: " << a.Height() << endl;
                break;
            case 9:
                cout << "Ҷ�ӽ������: " << a.LeavesSize() << endl;
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
                cout << "��������" << endl;
                break;
        }
        cout << endl << endl;
        cout << " ����������Ҫ�Ĳ��� " << endl;
        cin >> choice;
    } while (choice != 11);
}

void showMainOperation()
{
    cout << "*************************************************" << endl;
    cout << "1------����һ�ö�����" << endl;
    cout << "2------ǰ������ݹ��㷨" << endl;
    cout << "3------ǰ������ǵݹ��㷨" << endl;
    cout << "4------��������ݹ��㷨" << endl;
    cout << "5------��������ǵݹ��㷨" << endl;
    cout << "6------��������ݹ��㷨" << endl;
    cout << "7------��������ǵݹ��㷨" << endl;
    cout << "8------������" << endl;
    cout << "9------��Ҷ������" << endl;
    cout << "10-----���������" << endl;
    cout << "11-----�˳�" << endl;
    cout << "12-----���˵�" << endl;
}


int main()
{
    BinaryTree<char> a;
    MainLoop(a);
    cout << endl;
    cout << "-------------------   ��лʹ��  -------------------";
    cout << endl
         << endl;
    system("pause");
}
