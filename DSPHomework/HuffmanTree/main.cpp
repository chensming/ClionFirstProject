#include <iostream>
#include "HuffmanTree.h"
using namespace std;

int main() {

//    float test[10] = {1, 5, 2, 6, 3, 7, 8, 4, 9, 10};
//    char testch[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
//    HuffmanTree ht1(test, testch, 10);

    HuffmanTree ht1;

    cout << "构建用来编码的哈夫曼树成功,树的简要信息如下($是HuffmanNode字符成员的默认值): " << endl;
    ht1.LevelOrder();
    cout << endl;
    ht1.PrintGeneralizedList();

    ht1.setCode();
    ht1.getCode();
    ht1.enCoding("a.txt", "encodedFile.txt");
    ht1.BuildDeCodingTree();

    cout << "重建用来译码的哈夫曼树成功,树的简要信息如下($是HuffmanNode字符成员的默认值): " << endl;
    ht1.LevelOrder();
    ht1.PrintGeneralizedList();
    ht1.deCoding("encodedFile.txt", "b.txt");

    cout << endl;
    system("pause");
}

