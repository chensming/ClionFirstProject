//
// Created by Dell on 2019/12/17.
//

#include <iostream>
using namespace std;
#include "studUnit.h"

void mainLoop(studUnit& student);
void showTitle();

int main()
{
    studUnit a(10);
    showTitle();
    mainLoop(a);
    cout << "exit successfully!" << endl;
}

void showTitle()
{
    /*
        输出操作指南
    */
    cout << endl
         << endl;
    cout << "***************************************************" << endl;
    cout << " 1.向学生健康表插入学生信息" << endl;
    cout << " 2.在健康表修改学生信息" <<endl;
    cout << " 3.在健康表删除学生信息" << endl;
    cout << endl;
    cout << " 4.从文件中读取健康表信息" << endl;
    cout << " 5.向文件写入学生健康表信息" << endl;
    cout << endl;
    cout << " 6.在健康表中查询学生信息(按学生学号来进行查找)" << endl;
    cout << " 7.在屏幕中输出全部学生信息" << endl;
    cout << endl;
    cout << " 8.显示操作的指南" << endl;
    cout << " 0.退出" << endl;
    cout << "***************************************************" << endl;
    cout << endl
         << endl;
}

void mainLoop(studUnit& student)
{
    int userChoose = 1;
    while(userChoose)
    {
        cout << "请输入你要进行的操作: "<<endl;
        cin >> userChoose;
        switch (userChoose)
        {
            case 1:
                student.addStudent();
                break;
            case 2:
                student.editStudent();
                break;
            case 3:
                student.deleteStudent();
                break;
            case 4:
                student.readFile();
                break;
            case 5:
                student.writeFile();
                break;
            case 6:
                student.searchStudent();
                break;
            case 7:
                student.output();
                break;
            case 8:
                showTitle();
                break;
            case 0:
                cout << "preparing to exit!" << endl;
                break;
            default:
                cout << "invalid operation!" << endl;
                break;
        }
    };
}
