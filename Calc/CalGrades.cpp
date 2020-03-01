//
// Created by Dell on 2020/1/16.
//

#include<iostream>
#include<fstream>

using namespace std;

int main() {
    ifstream infile("./Calc/GradesFiles/chenSM.txt", ios::in);
    if (!infile) {
        cerr << "open file error" << endl;
        exit(1);
    }
    int gradeNum;
    infile >> gradeNum;
    float point;
    float grade;
    float totalPoint = 0;
    float totalGrade = 0;
    int count = 0;
    for(int i = 0; i < gradeNum; i++){
        infile >> point >> grade;
//        if(point < 0 && grade < 0)
//            break;
        count++;
        totalPoint = totalPoint + point;
        totalGrade = totalGrade + point * (grade - 50) / 10;
    }
    float averageGrades = totalGrade / totalPoint;
    cout << "  the number of subject: " << count << endl;
    cout << "  the total point: " << totalPoint << endl;
    cout << "  your GPA: " << averageGrades << endl;
    infile.close();
}