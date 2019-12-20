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
    char number[10];   //ѧ��
    char name[20];     //����
    dateType dateTime; //��������
    char sex;          //�Ա�
    char health[200];  //����״��
};

class studUnit
{
public:
    studUnit(int sz);
    ~studUnit();
    //1.��ѧ�����������ѧ����Ϣ
    void addStudent();
    //2.�ڽ������޸�ѧ����Ϣ
    void editStudent();
    //3.�ڽ�����ɾ��ѧ����Ϣ
    void deleteStudent();
    //4.���ļ��ж�ȡ��������Ϣ
    void readFile();
    //5.���ļ�д��ѧ����������Ϣ
    void writeFile();
    //6.�ڽ������в�ѯѧ����Ϣ(��ѧ��ѧ�������в���)
    void searchStudent();
    //7.����Ļ�����ȫ��ѧ����Ϣ
    void output();

private:
    studType *data;
    int maxSize;
    int last;
};



#endif //LINEARSTUDENT_STUDUNIT_H
