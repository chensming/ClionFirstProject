#include <iostream>
#include "Stack.h"
using namespace std;


bool IsNumber(char x)
{
    if (x >= '0' && x <= '9')
        return true;
    return false;
}



int Priority(char x)
{
    if (x == '+' || x == '-')
        return 0;
    else if (x == '*' || x == '/')
        return 1;
    else if (x == '(' || x == ')')
        return -1;
    else if (x == '#')
        return -2;
}

//����ĺ���
bool Calculate(string s) {
    Stack<int> number;
    Stack<char> operate;
    char top;
    int a, b;

    for (unsigned int i = 0; i < s.size(); ++i) {
        if (IsNumber(s[i])) {
            int numTemp = 0;
            string strTemp;

            strTemp += s[i];
            while (IsNumber(s[++i]))
                strTemp += s[i];
            for (unsigned int j = 0; j < strTemp.size(); ++j) {
                numTemp = numTemp * 10 + strTemp[j] - 48;
            }
            number.Push(numTemp);
            strTemp.clear();
        }//���ַ�����ת������������
        if (!IsNumber(s[i])) {
            if (operate.IsEmpty()) {
                operate.Push(s[i]);
            }//��ջ��һ������'#'
            else {
                operate.GetTop(top);

                if (Priority(s[i]) > Priority(top) || s[i] == '(') {
                    operate.Push(s[i]);
                }//��ջ�����ȼ��������
                else {
                    while (Priority(s[i]) <= Priority(top)) {
                        if (top == '#' && s[i] == '#') {
                            int answer;

                            operate.Pop();
                            number.GetTop(answer);
                            cout << "\n���ǣ�" << answer << endl;
                            number.Pop();
                            return true;
                        }//�������ʵ����ȫ��ֻʣ��'#'
                        else if (top == '(' && s[i] == ')') {
                            ++i;
                        }//��������������ʱ�����������ţ�ɾ��������
                        else {
                            number.GetTop(b);
                            number.Pop();
                            number.GetTop(a);
                            number.Pop();
                        }
                        if (top == '+') {
                            a += b;
                            number.Push(a);
                        }
                        else if (top == '-') {
                            a -= b;
                            number.Push(a);
                        }
                        else if (top == '*') {
                            a *= b;
                            number.Push(a);
                        }
                        else if (top == '/') {
                            if (b == 0)
                            {
                                cout << "divisor is not allowed to zero" << endl;
                                return false;
                            }
                            a /= b;
                            number.Push(a);
                        }
                        operate.Pop();
                        operate.GetTop(top);//ȡǰһ�������������������ɨ�����������бȽ�
                    }//�����ȼ��ߵ������ʵ�ּ���
                    operate.Push(s[i]);//���ڵ�top=='#'ʱ�������һ���������ջ
                }
            }
        }//ɨ������������ж����ȼ����Լ�����
    }//��ѭ��
}//���������ɨ�裬�������ַ���ת�����Լ�����




int main()
{
    string expression;
    cout << "������һ���� \'# \' ��ʼ������Ϊ�����ļ�����ʽ" << endl;
    cin >> expression;
    Calculate(expression);
    cout << endl;
    return 0;
}
