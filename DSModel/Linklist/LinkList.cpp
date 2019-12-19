//
// Created by Dell on 2019/12/15.
//

#include <iostream>
using namespace std;


template<class T>
struct LinkNode
{
    T data;
    LinkNode* next;

    LinkNode()
    {
        data = T();
        next = nullptr;
    }
    LinkNode(T d)
    {
        data = d;
        next = nullptr;
    }
};


template<class T>
class LinkList
{
public:
    LinkList() { head = new LinkNode<T>; }
    LinkList(const T& x) { head = new LinkNode<T>(x); }
    LinkList(LinkList<T>& L);
    ~LinkList() { makeEmpty(); }
    void InputFront();
    void InputRear();

    void makeEmpty();
    int Length() const;
    LinkNode<T>* getHead() const { return head; }
    LinkNode<T>* Search(T x);
    LinkNode<T>* Locate(int i);

    bool getData(int i, T& x);
    bool setData(int i, T& x);
    bool Insert(int i, T& x);
    bool Remove(int i, T& x);
    bool IsEmpty() const;
    bool IsFull() const { return false; }

    //void Sort();
    void output();
    LinkList<T>& operator=(LinkList<T>& L);

private:
    LinkNode<T>* head;
};


template<class T>
LinkList<T>::LinkList(LinkList<T>& L)
{
    T value;
    LinkNode<T>* srcptr = L.getHead();
    LinkNode<T>* destptr = head = new LinkNode<T>;

    while (srcptr->next != 0)
    {
        value = srcptr->next->data;// 表头结点无数据，直接跳过
        destptr->next = new LinkNode<T>(value);
        destptr = destptr->next;
        srcptr = srcptr->next;
    }
    destptr->next = 0; //其实初始化是已经置为零了,这里再确保一下
}









template<class T>
void LinkList<T>::InputFront()
{
    LinkNode<T>* newNode;
    T value, endValue;
    makeEmpty();

    cout << "请输入结束标志" << endl;
    cin >> endValue;
    cout << "请分别输入结点的值" << endl;
    cin >> value;
    while (value != endValue)
    {
        newNode = new LinkNode<T>(value);
        if (newNode == 0)
        {
            cerr << "存储分配错误(from LinkList<T>::InputFront()" << endl;
            exit(1);
        }
        newNode->next = head->next;
        head->next = newNode;
        cin >> value;
    }

    cout << "头插法建链成功" << endl;
}


template<class T>
void LinkList<T>::InputRear()
{
    LinkNode<T>* newNode, * last = head;
    T value, endValue;
    makeEmpty();

    cout << "请输入结束标志" << endl;
    cin >> endValue;
    cout << "请分别输入结点的值" << endl;
    cin >> value;
    while (value != endValue)
    {
        newNode = new LinkNode<T>(value);
        if (newNode == 0)
        {
            cerr << "存储分配错误(from LinkList<T>::InputRear()" << endl;
            exit(1);
        }
        last->next = newNode;
        last = newNode;
        cin >> value;
    }
    last->next = 0;

    cout << "尾插入建链成功" << endl;
}



//不过不删除表头结点
template<class T>
void LinkList<T>::makeEmpty()
{
    LinkNode<T>* q;
    while (head->next != 0)
    {
        q = head->next;
        head->next = q->next;
        delete q;
    }
}




template<class T>
int LinkList<T>::Length() const
{
    LinkNode<T>* p = head->next;
    int count = 0;
    while (p != 0)
    {
        p = p->next;
        count++;
    }
    return count;
}






template<class T>
LinkNode<T>* LinkList<T>::Search(T x)
{
    LinkNode<T>* current = head->next;
    while (current != 0)
    {
        if (current->data == x)
            break;
        else
            current = current->next;
    }
    return current;
}




//返回第 i 个元素的地址
template<class T>
LinkNode<T>* LinkList<T>::Locate(int i)
{
    if (i < 0)
        return 0;
    LinkNode<T>* current = head;
    int k = 0;
    while (current != 0 && k < i)
    {
        current = current->next;
        k++;
    }
    return current;
}





//取出第 i 个元素的值
template<class T>
bool LinkList<T>::getData(int i, T& x)
{
    if (i < 0)
        return false;
    LinkNode<T>* current = Locate(i);
    if (current == 0)
        return false;
    x = current->data;
    return true;
}



template<class T>
bool LinkList<T>::setData(int i, T& x)
{
    if (i < 0)
        return false;
    LinkNode<T>* current = Locate(i);
    if (current == 0)
        return false;
    current->data = x;
    return true;
}


//将新结点插入到第 i 个结点之后
template<class T>
bool LinkList<T>::Insert(int i, T& x)
{
    LinkNode<T>* current = Locate(i);
    if (current == 0)
        return false;
    auto* newNode = new LinkNode<T>(x);
    if (newNode == nullptr)
    {
        cerr << "存储分配错误(from LinkList<T>::Insert)" << endl;
        exit(1);
    }

    newNode->next = current->next;
    current->next = newNode;
    return true;
}




//删除第 i 个结点
template<class T>
bool LinkList<T>::Remove(int i, T& x)
{
    //找到要删除的结点的前一个结点
    LinkNode<T>* current = Locate(i - 1);
    if (current == 0 || current->next == 0)
        return false;

    //指向要删除的结点
    LinkNode<T>* del = current->next;
    current->next = del->next;
    x = del->data;
    delete del;
    return true;
}


template<class T>
bool LinkList<T>::IsEmpty() const
{
    return head->next == 0;
}





template<class T>
void LinkList<T>::output()
{
    LinkNode<T>* current = head->next;
    while (current != 0)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}







template<class T>
LinkList<T>& LinkList<T>::operator=(LinkList<T>& L)
{
    T value;
    LinkNode<T>* srcptr = L.getHead();
    LinkNode<T>* destptr = head = new LinkList<T>;
    while (srcptr->next != 0)
    {
        value = srcptr->next->data; //直接跳过表头结点
        destptr->next = new LinkNode<T>(value);
        destptr = destptr->next;
        srcptr = srcptr->next;
    }
    destptr->next = 0;
    return *this;
}







template<class T>
void IsInsertSucc(LinkList<T>& a, int i, T& x)
{
    if (a.Insert(i, x))
    {
        cout << "在第 " << i << " 个结点之后插入新结点成功" << endl;
        cout << "它的值为 " << x << endl;
    }
    else
    {
        cout << "在第 " << i << " 个结点之后插入新结点成功" << endl;
    }
    cout << endl;

}


template<class T>
void IsRemoveSucc(LinkList<T>& a, int i, T& x)
{
    if (a.Remove(i, x))
    {
        cout << "删除第 " << i << " 个结点成功" << endl;
        cout << "它的值为 " << x << endl;
    }
    else
    {
        cout << "删除第 " << i << " 个结点失败" << endl;
    }
    cout << endl;
}







int main()
{
    LinkList<int> a;
    int x = 56 ,i = 0;
    IsInsertSucc(a, 0, x);
    x = 48;
    IsInsertSucc(a, 0, x);
    x = 82;
    IsInsertSucc(a, 0, x);

    cout << "LinkList<int> b(a)" << endl;
    LinkList<int> b(a);

    x = 34;
    IsInsertSucc(a, 0, x);
    x = 459;
    IsInsertSucc(a, 0, x);
    x = -85;
    IsInsertSucc(a, 0, x);
    x = 648;
    IsInsertSucc(a, 0, x);

    cout << endl;
    cout << "a中的元素" << endl;
    a.output();

    cout << endl;
    cout << "c = a" << endl;
    LinkList <int> c = a;


    cout << endl;
    cout << "remove..." << endl;
    IsRemoveSucc(a, 2, x);

    cout << endl;
    cout << "a中的元素" << endl;
    a.output();

    cout << endl;
    cout << "b中的元素" << endl;
    b.output();

    cout << endl;
    cout << "c中的元素" << endl;
    c.output();
/*
	cout << endl << endl;
	cout << "重新建立 a 链,头插" << endl;
	a.InputFront();


	cout << endl << endl;
	cout << "重新建立 b 链,尾插" << endl;
	b.InputRear();

	cout << endl;
	cout << "a中的元素" << endl;
	a.output();

	cout << endl;
	cout << "b中的元素" << endl;
	b.output();
*/

    cout << endl << endl;
    a.getData(2, x);
    i = 2;
    cout << "a链第 " << i << " 个元素的值: " << x << endl;
    cout << endl;


    cout << endl;
    cout << "a中的元素" << endl;
    a.output();


    cout << endl;
    x = 1000;
    i = 3;
    cout << "a链第 "<< i << " 个元素的值变为 " << x << endl;
    a.setData(i, x);
    cout << "a中的元素" << endl;
    a.output();



    cout << endl;
}










