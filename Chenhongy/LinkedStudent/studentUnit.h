//
// Created by Dell on 2019/12/17.
//

#ifndef LINKEDSTUDENT_STUDENTUNIT_H
#define LINKEDSTUDENT_STUDENTUNIT_H


struct dateType
{
    int year;
    int month;
    int day;
};

struct student
{
    char number[10];   //学号
    char name[20];     //名字
    dateType dateTime; //出生日期
    char sex;          //性别
    char health[200];  //身体状况
};

struct LinkNode
{
    student data;
    LinkNode *next;

    LinkNode(LinkNode *ptr = 0) { next = ptr; }
};

class studentUnit
{
public:
    studentUnit();
    ~studentUnit();
    //置空
    void makeEmpty();
    //1.向学生健康表插入学生信息
    bool addStudent();
    //2.在健康表修改学生信息
    bool editStudent();
    //3.在健康表删除学生信息
    bool deleteStudent();
    //4.从文件中读取健康表信息
    bool readFile();
    //5.向文件写入学生健康表信息
    bool writeFile();
    //6.在健康表中查询学生信息(按学生学号来进行查找)
    bool searchStudent();
    //7.在屏幕中输出全部学生信息
    void output();
    //返回表中第 i 个的地址
    LinkNode *Locate(int i);

private:
    LinkNode *first;
};



#endif //LINKEDSTUDENT_STUDENTUNIT_H
