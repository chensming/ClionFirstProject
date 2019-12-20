//
// Created by Dell on 2019/12/17.
//

#include "studentUnit.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

studentUnit::studentUnit()
{
    first = new LinkNode();
}

studentUnit::~studentUnit()
{
    makeEmpty();
}

void studentUnit::makeEmpty()
{
    LinkNode *q;
    while (first->next != 0)
    {
        q = first->next;
        first->next = q->next;
        delete q;
    }
}

bool studentUnit::addStudent()
{
    int i;
    cout << "请输入要插入到第几个学生之后(0代表插入到最前面)" << endl;
    cin >> i;
    LinkNode *current = Locate(i);
    if (current == 0)
    {
        cerr << "输入有误" << endl;
        return false;
    }
    // char number[10];   //学号
    // char name[20];     //名字
    // dateType dateTime; //出生日期
    // char sex;          //性别
    // char health[200];  //身体状况
    LinkNode *p = new LinkNode();
    if (p == nullptr)
    {
        cerr << "内存分配错误" << endl;
        exit(1);
    }

    cout << "请输入该学生的学号" << endl;
    cin >> p->data.number;
    cout << "请输入该学生的名字" << endl;
    while (getchar() != '\n')
    {
        //null
    }
    cin.getline(p->data.name, 20);
    cout << "请输入该学生的出生日期" << endl;
    cin >> p->data.dateTime.year >> p->data.dateTime.month >> p->data.dateTime.day;
    cout << "请输入该学生的性别(男m,女f)" << endl;
    cin >> p->data.sex;
    cout << "请输入该学生的身体健康情况" << endl;
    while (getchar() != '\n')
    {
    }
    cin.getline(p->data.health, 200);

    //插入接点后相连
    p->next = current->next;
    current->next = p;
    cout << "输入完毕" << endl;
    cout << endl;
    return true;
}

bool studentUnit::editStudent()
{
    int i;
    cout << "请输入您要修改第几个学生的信息" << endl;
    cin >> i;
    if (i <= 0)
    {
        cout << "输入有误" << endl;
        return false;
    }
    LinkNode *current = Locate(i);
    if (current == 0)
    {
        cout << "输入有误" << endl;
        return false;
    }

    cout << "请输入要修改的学生的学号" << endl;
    cin >> current->data.number;
    cout << "请输入要修改的学生的名字" << endl;
    while (getchar() != '\n')
    {
        //null
    }
    cin.getline(current->data.name, 20);
    cout << "请输入要修改的学生的出生日期" << endl;
    cin >> current->data.dateTime.year >> current->data.dateTime.month >> current->data.dateTime.day;
    cout << "请输入要修改的学生的性别(男m,女f)" << endl;
    cin >> current->data.sex;
    cout << "请输入要修改的学生的身体健康情况" << endl;
    while (getchar() != '\n')
    {
    }
    cin.getline(current->data.health, 200);

    cout << "修改成功" << endl;
    cout << endl;
    return true;
}

bool studentUnit::deleteStudent()
{
    int i;
    cout << "请输入您要删除第几个学生的信息" << endl;
    cin >> i;
    if (i <= 0)
    {
        cout << "输入有误" << endl;
        return false;
    }
    LinkNode *current = Locate(i-1);
    if (current == 0 || current->next == 0)
    {
        cout << "输入有误" << endl;
        return false;
    }
    LinkNode *del = current->next;
    current->next = del->next;
    cout << "删除成功" << endl;
    return true;
}

bool studentUnit::readFile()
{
    ifstream infile("student.dat", ios::in | ios::binary);
    if (!infile)
    {
        cerr << "infile打开student.dat失败" << endl;
        abort();
    }
    int i = 0;
    LinkNode *p = new LinkNode();
    if (p == 0)
    {
        cerr << "分配内存错误" << endl;
        exit(1);
    }
    first->next = p;
    LinkNode *q = p;
    while (infile.read((char *)(&(p->data)), sizeof(p->data)))
    {
        i++;
        q = p;
        p = new LinkNode();
        if (p == 0)
        {
            cerr << "分配内存错误" << endl;
            exit(1);
        }
        q->next = p;
    }
    q->next = 0;
    delete p;
    infile.close();
    cout << "成功读入 " << i << " 条信息" << endl;
    cout << endl;
    return true;
}

bool studentUnit::writeFile()
{
    ofstream outfile("student.dat", ios::out|ios::binary);
    if (!outfile)
    {
        cerr << "outfile打开student.dat失败" << endl;
        exit(1);
    }
    LinkNode *p = first->next;
    int i = 0;
    while (p != 0)
    {
        outfile.write((char *)(&(p->data)), sizeof(p->data));
        i++;
        p = p->next;
    }
    cout << "成功写入 " << i << " 条信息" << endl;
    cout << endl;
    return true;
}

bool studentUnit::searchStudent()
{
    char num[10];
    cout << "请输入要查找的学生的学号" << endl;
    cin >> num;
    LinkNode *p = first->next;
    while (p != 0 && (strcmp(p->data.number, num) != 0))
    {
        p = p->next;
    }
    if (p == 0)
    {
        cout << "没找到该学生" << endl;
        return false;
    }
    cout << "该学生信息如下: " << endl;
    cout << "学号: " << p->data.number << endl;
    cout << "姓名: " << p->data.name << endl;
    cout << "生日: " << p->data.dateTime.year << " "
         << p->data.dateTime.month << " "
         << p->data.dateTime.day << endl;
    cout << "性别:(男m,女f) " << p->data.sex << endl;
    cout << "健康情况: " << p->data.health << endl;
    cout << endl;
    return true;
}

void studentUnit::output()
{
    LinkNode *p = first->next;
    cout << "-------------学生信息表--------------" << endl;
    while (p != 0)
    {
        cout << "学号: " << p->data.number << endl;
        cout << "姓名: " << p->data.name << endl;
        cout << "生日: " << p->data.dateTime.year << " "
             << p->data.dateTime.month << " "
             << p->data.dateTime.day << endl;
        cout << "性别:(f:男 m:女)" << p->data.sex << endl;
        cout << "健康情况: " << p->data.health << endl;
        cout << endl;
        p = p->next;
    }
    cout << "--------------------------------------" << endl;
    cout << "输出完毕" << endl;
    cout << endl;
}

LinkNode *studentUnit::Locate(int i)
{
    if (i < 0)
        return 0;
    LinkNode *current = first;
    int k = 0;
    while (current != 0 && k < i)
    {
        current = current->next;
        k++;
    }
    return current;
}
