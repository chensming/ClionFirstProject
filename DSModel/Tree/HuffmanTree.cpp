//
// Created by Dell on 2019/12/15.
//
//
// Created by Dell on 2019/12/15.
//
#include <utility>
#include<vector>
#include<iostream>
#include<algorithm>
#include<queue>
#include<iomanip>
#include <stack>
#include <fstream>

using namespace std;


struct HuffmanNode {
    float data;
    char ch;
    string code;
    HuffmanNode *leftChild, *rightChild, *parent;

    HuffmanNode() : data(-1), ch('$'), code(""), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}

    //HuffmanNode(const HuffmanNode& h);
    HuffmanNode(float elem, HuffmanNode *left = nullptr, HuffmanNode *right = nullptr, HuffmanNode *pr = nullptr) :
            data(elem), leftChild(left), rightChild(right), parent(pr) {}

    bool operator<=(HuffmanNode &R) { return data <= R.data; }

    bool operator>(HuffmanNode &R) { return data > R.data; }
};

/*
HuffmanNode::HuffmanNode(const HuffmanNode& h)
{
	data = h.data;
	leftChild = h.leftChild;
	rightChild = h.rightChild;
	//其实parent这个写不写无所谓，因为如果parent！=null，
	//就证明已经和其他节点合成一个父节点了,不会被放到堆里面
	parent = h.parent;
}
*/


bool cmp(const HuffmanNode &a, const HuffmanNode &b) {
    return a.data < b.data;
}


class HuffmanTree {
public:
    HuffmanTree();

    HuffmanTree(const float w[], const char ch[], int n);

    ~HuffmanTree() {
        deleteTree(root);
        charactorSize = 0;
        if(charactor != nullptr)
        {
            delete [] charactor;
            charactor = nullptr;
        }
    }

    void LevelOrder();

    void PrintGeneralizedList();

    void PrintGeneralizedList(HuffmanNode *BT);

    void setCode();

    void getCode();

    void enCoding(string originalFile, string encodingFile);

    void BuildDeCodingTree();

    void deCoding(string encodingFile, string outputFile);

private:
    HuffmanNode *root;

    string map[256];//存字符对应的编码

    char *charactor;//判断存了哪些字符

    int charactorSize;//存的字符个数

    void buildHuffmanTree(const float w[], const char ch[], int n);

    void deleteTree(HuffmanNode *t);

    void mergeTree(HuffmanNode *h1, HuffmanNode *h2, HuffmanNode *&parent);

    static void setCode(string s, HuffmanNode *ptr);
};


void display(vector<HuffmanNode> &v);//使用vector迭代器遍历

HuffmanTree::HuffmanTree() {
    charactor = nullptr;
    root = nullptr;
    int n;
    char ch[256];
    float weight[256];
    cout << "请输入要编码的字符个数(1<n<256)" << endl;
    cin >> n;
    cout << "请分别输入要编码的字符" << endl;
    for (int i = 0; i < n; i++)
        cin >> ch[i];
    cout << "请分别输入对应字符的权重" << endl;
    for (int i = 0; i < n; i++)
        cin >> weight[i];
    buildHuffmanTree(weight, ch, n);
}


HuffmanTree::HuffmanTree(const float w[], const char ch[], int n) {
    //为了消除警告，root = 0，其实没必要，最后root = parent
    //已经包括这个情况了
    root = nullptr;
    vector<HuffmanNode> hp;
    HuffmanNode *parent = nullptr, *first, *second, *work;
    HuffmanNode tempFirst, tempSecond;
    charactor = new char[n];
    //存可编码的字符
    for (int i = 0; i < n; i++) {
        charactor[i] = ch[i];
    }
    charactorSize = 0;


    for (int i = 0; i < n; i++) {
        work = new HuffmanNode;
        work->data = w[i];
        work->ch = ch[i];
        work->leftChild = nullptr;
        work->rightChild = nullptr;
        work->parent = nullptr;
        hp.push_back(*work);
        //make_heap(hp.begin(), hp.end(), cmp);
        //sort_heap(hp.begin(), hp.end(), cmp);
    }
    make_heap(hp.begin(), hp.end(), cmp);
    sort_heap(hp.begin(), hp.end(), cmp);
    for (int i = 0; i < n - 1; i++) {
        if (hp.empty()) {
            cout << "堆empty" << endl;
            return;
        }
        tempFirst = hp.front();
        first = new HuffmanNode();
        first->data = tempFirst.data;
        first->ch = tempFirst.ch;
        first->leftChild = tempFirst.leftChild;
        first->rightChild = tempFirst.rightChild;
        first->parent = tempFirst.parent;
        hp.erase(hp.begin());

//        cout << "把first取出来并删除,其值为 " << (*first).data;
//        cout << " ,对应的字符为 " << (*first).ch << " ,删除后的堆中元素: " << endl;
//        display(hp);

        tempSecond = hp.front();
        second = new HuffmanNode();
        second->data = tempSecond.data;
        second->ch = tempSecond.ch;
        second->leftChild = tempSecond.leftChild;
        second->rightChild = tempSecond.rightChild;
        second->parent = tempSecond.parent;
        hp.erase(hp.begin());

//        cout << "把second取出来并删除,其值为 " << (*second).data;
//        cout << " ,对应的字符为 " << (*second).ch << " ,删除后的堆中元素: " << endl;
//        display(hp);

        mergeTree(first, second, parent);
        hp.push_back(*parent);
        make_heap(hp.begin(), hp.end(), cmp);
        sort_heap(hp.begin(), hp.end(), cmp);

//        cout << "把 " << (*first).data << " 与 " << (*second).data << " merge，然后得到值 ";
//        cout << (*parent).data << " ,对应字符为 " << (*parent).ch;
//        cout << " ,把它插入后堆中元素: " << endl;
//        display(hp);
//        cout << endl;
    }
    root = parent;
}


void HuffmanTree::buildHuffmanTree(const float w[], const char ch[], int n) {
//    cout << endl;
//    for(int i = 0; i < n; i++)
//        cout << w[i] << " ";
//    cout << endl;
//    for(int i = 0; i < n; i++)
//        cout << ch[i] << " ";
//    cout << endl;
//    为了消除警告，root = 0，其实没必要，最后root = parent
//    已经包括这个情况了
    vector<HuffmanNode> hp;
    HuffmanNode *parent = 0, *first, *second,work;
    HuffmanNode tempFirst, tempSecond;
    charactor = new char[n];
    //存可编码的字符
    for (int i = 0; i < n; i++) {
        charactor[i] = ch[i];
    }
    charactorSize = 0;


    for (int i = 0; i < n; i++) {
        work.data = w[i];
        work.ch = ch[i];
        work.leftChild = nullptr;
        work.rightChild = nullptr;
        work.parent = nullptr;
        hp.push_back(work);
        //make_heap(hp.begin(), hp.end(), cmp);
        //sort_heap(hp.begin(), hp.end(), cmp);
    }
    make_heap(hp.begin(), hp.end(), cmp);
    sort_heap(hp.begin(), hp.end(), cmp);
    for (int i = 0; i < n - 1; i++) {
        if (hp.empty()) {
            cout << "堆empty" << endl;
            return;
        }
        tempFirst = hp.front();
        first = new HuffmanNode();
        first->data = tempFirst.data;
        first->ch = tempFirst.ch;
        first->leftChild = tempFirst.leftChild;
        first->rightChild = tempFirst.rightChild;
        first->parent = tempFirst.parent;
        hp.erase(hp.begin());

//        cout << "把first取出来并删除,其值为 " << (*first).data;
//        cout << " ,对应的字符为 " << (*first).ch << " ,删除后的堆中元素: " << endl;
//        display(hp);

        tempSecond = hp.front();
        second = new HuffmanNode();
        second->data = tempSecond.data;
        second->ch = tempSecond.ch;
        second->leftChild = tempSecond.leftChild;
        second->rightChild = tempSecond.rightChild;
        second->parent = tempSecond.parent;
        hp.erase(hp.begin());

//        cout << "把second取出来并删除,其值为 " << (*second).data;
//        cout << " ,对应的字符为 " << (*second).ch << " ,删除后的堆中元素: " << endl;
//        display(hp);

        mergeTree(first, second, parent);
        hp.push_back(*parent);
        make_heap(hp.begin(), hp.end(), cmp);
        sort_heap(hp.begin(), hp.end(), cmp);

//        cout << "把 " << (*first).data << " 与 " << (*second).data << " merge，然后得到值 ";
//        cout << (*parent).data << " ,对应字符为 " << (*parent).ch;
//        cout << " ,把它插入后堆中元素: " << endl;
//        display(hp);
//        cout << endl;
    }
    root = parent;
}

void HuffmanTree::deleteTree(HuffmanNode *t) {
    if (t != nullptr) {
        deleteTree(t->leftChild);
        deleteTree(t->rightChild);
        delete t;
    }
    root = nullptr;
}


void HuffmanTree::mergeTree(HuffmanNode *h1, HuffmanNode *h2, HuffmanNode *&parent) {
    parent = new HuffmanNode;
    parent->leftChild = h2;//让数据靠右边
    parent->rightChild = h1;
    parent->data = h1->data + h2->data;
    h1->parent = h2->parent = parent;
}


void display(vector<HuffmanNode> &v)//使用vector迭代器遍历
{
    vector<HuffmanNode>::iterator i;
    for (i = v.begin(); i < v.end(); i++) {
        cout << (*i).data << " ";
    }
    cout << endl;
    for (i = v.begin(); i < v.end(); i++) {
        cout << (*i).ch << " ";
    }
    cout << endl << endl;
}


void HuffmanTree::LevelOrder() {
    int IsEven = 1;
    queue<HuffmanNode *> Q;
    HuffmanNode *p;
    Q.push(root);
    while (!Q.empty()) {
        IsEven = 1;
        int width = Q.size();
        for (int i = 0; i < width; i++) {
            p = Q.front();
            Q.pop();
            IsEven = (IsEven + 1) % 2;
            cout << setw(4) << p->data << "__" << setw(3) << p->ch;
            if (IsEven && i != width - 1)
                cout << " , ";
            if (p->leftChild != 0)
                Q.push(p->leftChild);
            if (p->rightChild != 0)
                Q.push(p->rightChild);
        }
        cout << endl;
    }
    cout << endl << endl << endl;
}


void HuffmanTree::PrintGeneralizedList() {
    PrintGeneralizedList(root);
    cout << endl;
}


void HuffmanTree::PrintGeneralizedList(HuffmanNode *BT) {
    if (BT != nullptr) {
        cout << BT->data << "  " << BT->ch;
        if (BT->leftChild != 0 || BT->rightChild != 0) {
            cout << "(";
            PrintGeneralizedList(BT->leftChild);
            if (BT->rightChild != 0) {
                cout << ",";
                PrintGeneralizedList(BT->rightChild);
            }
            cout << ")";
        }
    }
}

void HuffmanTree::setCode() {
    if (root == nullptr) {
        cout << "该树为空，无法设置编码" << endl;
        return;
    }
    setCode("", root);
}


void HuffmanTree::setCode(string s, HuffmanNode *ptr) {
    if (ptr != nullptr) {
        ptr->code = s;
        setCode(s + "0", ptr->leftChild);
        setCode(s + "1", ptr->rightChild);
    }
}

void HuffmanTree::getCode() {
    if (root == nullptr) {
        cout << "该树为空，无法进行编码" << endl;
        return;
    }
    stack<HuffmanNode *> S;
    HuffmanNode *p = root;
    do {
        while (p != nullptr) {
            S.push(p);
            if (p->leftChild == nullptr && p->rightChild == nullptr) {
                map[p->ch] = p->code;
                charactor[charactorSize] = p->ch;
                charactorSize++;
                cout << p->ch << ":" << p->code << " ";
            }
            p = p->leftChild;
        }
        if (!S.empty()) {
            p = S.top();
            S.pop();
            p = p->rightChild;
        }
    } while (p != nullptr || !S.empty());
    cout << endl << "编码成功";
    cout << endl;
}

void HuffmanTree::enCoding(string originalFile, string encodingFile) {
    string str[100];
    char ch;
    string temp1 = originalFile;
    string temp2 = encodingFile;
    originalFile = "./Chenhongy/HuffmanTree/Files/" + originalFile;
    ifstream infile(originalFile, ios::in);
    encodingFile = "./Chenhongy/HuffmanTree/Files/" + encodingFile;
    ofstream outfile(encodingFile, ios::out);
    if (!infile) {
        cerr << "open error when read file" << endl;
        exit(1);
    }
    if (!outfile) {
        cerr << "open error when write file" << endl;
        exit(1);
    }
    while (infile.get(ch)) {
        if (ch == ' ') {
            outfile << ' ';
        } else if (ch == '\n') {
            outfile << '\n';
        } else {
            outfile << map[ch % 256];
        }
    }
    infile.close();
    outfile.close();
    cout << endl << "从 ";
    cout << temp1 << " 编码到 " << temp2 << " 中" << endl;
    cout << endl;
}

void HuffmanTree::BuildDeCodingTree() {
    if (root == nullptr) {
        cout << "该树为空,不能进行译码" << endl;
        return;
    }
    deleteTree(root);
    char ch;
    string code;
    HuffmanNode *p, *q;
    root = new HuffmanNode;
    for (int i = 0; i < charactorSize; i++) {
        ch = charactor[i];
        code = map[ch];
        p = root;
        //到倒数第二个编码，留下最后一个编码单独处理
        for (int j = 0; j < code.length() - 1; j++) {
            if (code[j] == '0') {
                if (p->leftChild == nullptr) {
                    q = new HuffmanNode;
                    p->leftChild = q;
                }
                p = p->leftChild;
            } else { //code[j] == '1'
                if (p->rightChild == nullptr) {
                    q = new HuffmanNode;
                    p->rightChild = q;
                }
                p = p->rightChild;
            }
        }
        //最为编码的一定是叶子结点，肯定要new
        q = new HuffmanNode;
        //只有ch要用到，其他默认即可
        q->ch = ch;
        if (code[code.length() - 1] == '0') {
            p->leftChild = q;
        } else {
            p->rightChild = q;
        }
    }
    cout << "建立译码树完毕." << endl << endl;
}

void HuffmanTree::deCoding(string encodingFile, string outputFile) {
    char ch;
    HuffmanNode *p = root;
    string temp1 = encodingFile;
    string temp2 = outputFile;
    encodingFile = "./Chenhongy/HuffmanTree/Files/" + encodingFile;
    outputFile = "./Chenhongy/HuffmanTree/Files/" + outputFile;
    ifstream infile(encodingFile, ios::in);
    ofstream outfile(outputFile, ios::out);
    if (!infile) {
        cerr << "open error when read file" << endl;
        exit(1);
    }
    if (!outfile) {
        cerr << "open error when write file" << endl;
        exit(1);
    }
    while (infile.get(ch)) {
        if (ch == ' ')
            outfile << ' ';
        else if (ch == '\n')
            outfile << '\n';
        else {
            if (ch == '0' && p->leftChild != nullptr) {
                //不是叶子结点，没有数据，向左
                p = p->leftChild;
            } else if (ch == '1' && p->rightChild != nullptr) {
                //不是叶子结点，没有数据，向左
                p = p->rightChild;
            }
            if (p->leftChild == nullptr && p->rightChild == nullptr) {
                //是叶子结点，有数据，开始下一次查找
                outfile << p->ch;
                p = root;
            }
        }
    }
    infile.close();
    outfile.close();
    cout << "从已编码文件 " << temp1 << " 译码到 " << temp2 << " 已完成" << endl;
    cout << endl << endl;
}


int main() {

//    char ch[31] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
//                   'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ',', '.', 'I', 'M', '?'};
//    float weight[31] = {1, 5, 2, 6, 3, 7, 8, 4, 9, 10, 1, 5, 2, 6, 3, 7, 8, 4,
//                        9, 10, 5, 8, 6, 9, 2, 5, 2, 3, 5, 4, 1};
//    HuffmanTree ht1(weight, ch, 31);
    HuffmanTree ht1;
    cout << "构建成功" << endl;

    cout << "树的结构" << endl;
    ht1.LevelOrder();
    ht1.PrintGeneralizedList();

    ht1.setCode();
    cout << endl << "字符对应的编码" << endl;
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

