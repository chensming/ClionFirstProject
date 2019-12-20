#include <iostream>
#include "HuffmanTree.h"
using namespace std;

int main() {

//    float test[10] = {1, 5, 2, 6, 3, 7, 8, 4, 9, 10};
//    char testch[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
//    HuffmanTree ht1(test, testch, 10);

    HuffmanTree ht1;

    cout << "������������Ĺ��������ɹ�,���ļ�Ҫ��Ϣ����($��HuffmanNode�ַ���Ա��Ĭ��ֵ): " << endl;
    ht1.LevelOrder();
    cout << endl;
    ht1.PrintGeneralizedList();

    ht1.setCode();
    ht1.getCode();
    ht1.enCoding("a.txt", "encodedFile.txt");
    ht1.BuildDeCodingTree();

    cout << "�ؽ���������Ĺ��������ɹ�,���ļ�Ҫ��Ϣ����($��HuffmanNode�ַ���Ա��Ĭ��ֵ): " << endl;
    ht1.LevelOrder();
    ht1.PrintGeneralizedList();
    ht1.deCoding("encodedFile.txt", "b.txt");

    cout << endl;
    system("pause");
}

