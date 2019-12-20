//
// Created by Dell on 2019/12/17.
//

#include "studUnit.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

studUnit::studUnit(int sz)
{
    if (sz > 0)
    {
        maxSize = sz;
        last = -1;
        data = new studType[maxSize];
        if (data == 0)
        {
            maxSize = 0;
            last = -1;
            return;
        }
    }
}

studUnit::~studUnit()
{
    maxSize = 0;
    last = -1;
    delete[] data;
}

//第last+1个学生为data[last]的数据
void studUnit::addStudent()
{
    //last的指向是每增加一个是last会指向最后一个
    last++;
    cout << "插入第 " << (last + 1) << " 个学生" << endl;
    cout << "请输入学号" << endl;
    cin >> data[last].number;
    // cout << data[last].number << "!!!" << endl;
    cout << "请输入姓名" << endl;
    while (getchar() != '\n')
        ;
    cin.getline(data[last].name, 20);
    // cout << data[last].name << "???" << endl;
    cout << "请输入出生日期(年 月 日)" << endl;
    cin >> data[last].dateTime.year >> data[last].dateTime.month;
    cin >> data[last].dateTime.day;
    cout << "请输入性别(男m,女f)" << endl;
    cin >> data[last].sex;
    cout << "请输入健康信息" << endl;
    while (getchar() != '\n')
        ;
    cin.getline(data[last].health, 200);
    cout << "输入完毕! " << endl;
    cout << endl;
}

void studUnit::editStudent()
{
    int studnum;
    cout << "目前有 " << last + 1 <<"个学生" <<endl;
    cout << "请输入要修改第几个学生的信息 " << endl;
    cin >> studnum;
    if(1 > studnum || last+1 < studnum)
        exit(1);
    studnum -= 1;
    cout << "请输入学号" << endl;
    cin >> data[studnum].number;
    // cout << data[last].number << "!!!" << endl;
    cout << "请输入姓名" << endl;
    while (getchar() != '\n')
        ;
    cin.getline(data[studnum].name, 20);
    // cout << data[last].name << "???" << endl;
    cout << "请输入出生日期(年 月 日)" << endl;
    cin >> data[studnum].dateTime.year >> data[studnum].dateTime.month;
    cin >> data[studnum].dateTime.day;
    cout << "请输入性别(男m,女f)" << endl;
    cin >> data[studnum].sex;
    cout << "请输入健康信息" << endl;
    while (getchar() != '\n')
        ;
    cin.getline(data[studnum].health, 200);
    cout << "更改完毕! " << endl;
    cout << endl;
}


void studUnit::deleteStudent()
{
    int num;
    cout << "请输入要删除第几个学生" << endl;
    cin >> num;
    if (num == 0)
    {
        cout << "输入的数字不能为0" << endl
             << endl;
        return;
    }
    if (num > last + 1)
    {
        cerr << "输入的数字序错误" << endl;
        return;
    }
    for (int i = num; i <= last; i++)
    {
        data[i - 1] = data[i];
    }
    last--;
    cout << "删除后还有 " << (last + 1) << "个学生" << endl;
    cout << endl;
}

void studUnit::searchStudent()
{
    int i = 0;
    char number[10];
    cout << "请输入要查找的学生学号" << endl;
    cin >> number;
    for (; i <= last; i++)
    {
        if (strcmp(number, data[i].number) == 0)
        {
            cout << "学号: " << data[i].number << endl;
            cout << "姓名: " << data[i].name << endl;
            cout << "生日: " << data[i].dateTime.year << " "
                 << data[i].dateTime.month << " "
                 << data[i].dateTime.day << endl;
            cout << "性别:(男m,女f)" << data[i].sex << endl;
            cout << "健康情况: " << data[i].health << endl;
            cout << endl;
            cout << endl;
            return;
        }
    }
    cout << "您要查找的学号不存在!" << endl
         << endl;
}

void studUnit::output()
{
    if (last == -1)
    {
        cout << "没有学生了！" << endl;
    }
    for (int i = 0; i <= last; i++)
    {
        cout << "学号: " << data[i].number << endl;
        cout << "姓名: " << data[i].name << endl;
        cout << "生日: " << data[i].dateTime.year << " "
             << data[i].dateTime.month << " "
             << data[i].dateTime.day << endl;
        cout << "性别: f:男 m:女 " << data[i].sex << endl;
        cout << "健康情况: " << data[i].health << endl;
        cout << endl;
    }
    cout << "输出完毕! " << endl
         << endl
         << endl;
}

void studUnit::readFile()
{
    ifstream infile("Chenhongy/LinearStudent/f1.dat", ios::in | ios::out | ios::binary);
    if (!infile)
    {
        cerr << "open error!" << endl;
        exit(1);
    }
    int i = 0;
    while (infile.read((char *)&data[i], sizeof(data[i])))
    {
        i++;
        last++;
    }
    cout << "读取" << last + 1 << "条信息成功" << endl;
    cout << endl;
    cout << endl;
}

void studUnit::writeFile()
{
    if(-1 == last)
    {
        int choose = 0;
        cout << "!!!继续将会导致数据被清空，是否继续?" << endl;
        cout << "1.继续 0.返回" <<endl;
        cin >> choose;
        if(0 == choose)
            return;
    }
    ofstream outfile("Chenhongy/LinearStudent/f1.dat", ios::binary);
    if (!outfile)
    {
        cerr << "open error!" << endl;
        abort();
    }
    for (int i = 0; i <= last; i++)
    {
        outfile.write((char *)&data[i], sizeof(data[i]));
    }
    outfile.close();
    cout << endl;
    if(-1 == last)
        cout << "清空成功 " << endl;
    else
        cout << " write " << last + 1 << " information successfully!" << endl;
    cout << endl;
}