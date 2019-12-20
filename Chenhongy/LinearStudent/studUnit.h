//
// Created by Dell on 2019/12/17.
//

#ifndef LINEARSTUDENT_STUDUNIT_H
#define LINEARSTUDENT_STUDUNIT_H


struct dateType
{
    int year;
    int month;
    int day;
};

struct studType
{
    char number[10];   //学号
    char name[20];     //名字
    dateType dateTime; //出生日期
    char sex;          //性别
    char health[200];  //身体状况
};

class studUnit
{
public:
    studUnit(int sz);
    ~studUnit();
    //1.向学生健康表插入学生信息
    void addStudent();
    //2.在健康表修改学生信息
    void editStudent();
    //3.在健康表删除学生信息
    void deleteStudent();
    //4.从文件中读取健康表信息
    void readFile();
    //5.向文件写入学生健康表信息
    void writeFile();
    //6.在健康表中查询学生信息(按学生学号来进行查找)
    void searchStudent();
    //7.在屏幕中输出全部学生信息
    void output();

private:
    studType *data;
    int maxSize;
    int last;
};



#endif //LINEARSTUDENT_STUDUNIT_H
