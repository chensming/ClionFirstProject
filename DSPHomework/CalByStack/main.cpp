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

//运算的函数
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
        }//将字符数字转换成整形数字
        if (!IsNumber(s[i])) {
            if (operate.IsEmpty()) {
                operate.Push(s[i]);
            }//入栈第一个符号'#'
            else {
                operate.GetTop(top);

                if (Priority(s[i]) > Priority(top) || s[i] == '(') {
                    operate.Push(s[i]);
                }//入栈高优先级的运算符
                else {
                    while (Priority(s[i]) <= Priority(top)) {
                        if (top == '#' && s[i] == '#') {
                            int answer;

                            operate.Pop();
                            number.GetTop(answer);
                            cout << "\n答案是：" << answer << endl;
                            number.Pop();
                            return true;
                        }//当运算符实现完全后，只剩下'#'
                        else if (top == '(' && s[i] == ')') {
                            ++i;
                        }//当左右括号相遇时，跳过右括号，删除左括号
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
                        operate.GetTop(top);//取前一个运算符，用于与现在扫描的运算符进行比较
                    }//将优先级高的运算符实现计算
                    operate.Push(s[i]);//用于当top=='#'时，将最后一个运算符入栈
                }
            }
        }//扫描运算符，并判断优先级，以及运算
    }//主循环
}//对运算符的扫描，和数字字符的转化，以及计算




int main()
{
    string expression;
    cout << "请输入一个以 \'# \' 开始和以它为结束的计算表达式" << endl;
    cin >> expression;
    Calculate(expression);
    cout << endl;
    return 0;
}
