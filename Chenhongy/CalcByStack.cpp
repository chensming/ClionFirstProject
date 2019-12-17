#include<iostream>
using namespace std;

const int maxSize = 200;  //栈的最大容量

template<class T>
class Stack
{
public:
	Stack(); 
	~Stack();
	Stack(Stack<T>& s2);
	Stack<T>& operator=(const Stack<T>& s2);
	bool IsEmpty();
	bool IsFull();
	bool GetTop(T& x);
	bool Push(T x);
	bool Pop(T& x);
	bool Pop();
	void PrintFBottomToTop();

private:
	int CurrentSize;
	T data[maxSize];
};


template<class T>
Stack<T>::Stack()
{
	CurrentSize = 0;
}



template<class T>
Stack<T>::~Stack()
{
	CurrentSize = 0;
}



template<class T>
Stack<T>::Stack(Stack<T>& s2)
{
	CurrentSize = s2.CurrentSize;
	for (int i = 0; i < CurrentSize; i++)
	{
		data[i] = s2.data[i];
	}
}




template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s2)
{
	if (this != &s2)
	{
		CurrentSize = s2.CurrentSize;
		for (int i = 0; i < CurrentSize; i++)
		{
			data[i] = s2.data[i];
		}
	}
	return *this;
}








template<class T>
bool Stack<T>::IsEmpty()
{
	return (CurrentSize == 0) ? true : false;
}


template<class T>
bool Stack<T>::IsFull()
{
	return (CurrentSize == maxSize) ? true : false;
}


template<class T>
bool Stack<T>::GetTop(T& x)
{
	if (IsEmpty())
		return false;
	x = data[CurrentSize - 1];
	return true;
}


template<class T>
bool Stack<T>::Push(T x)
{
	if (IsFull())
		return false;
	data[CurrentSize++] = x;
	return true;
}



template<class T>
bool Stack<T>::Pop()
{
	if (IsEmpty())
		return false;
	CurrentSize--;
	return true;
}


template<class T>
bool Stack<T>::Pop(T& x)
{
	if (IsEmpty())
		return false;
	x = data[CurrentSize - 1];
	CurrentSize--;
	return true;
}


//从栈底到栈顶遍历
template<class T>
void Stack<T>::PrintFBottomToTop()
{
	if (IsEmpty())
	{
		cout << "栈为空" << endl;
		return;
	}
	cout << "栈中内容" << endl;
	for (int i = 0; i < CurrentSize; i++)
	{
		cout << data[i] << " ";
	}
}



template<class T>
void IsPushSucc(Stack<T>& a, T x)
{
	if (a.Push(x))
	{
		cout << "push " << x << " 成功" << endl;
	}
	else
	{
		cout << "push " << x << " 成功" << endl;
	}
}



template<class T>
void IsGetTop(Stack<T>& a, T& x)
{
	if (a.GetTop(x))
	{
		cout << "getTop " << x << " 成功" << endl;
	} 
	else
	{
		cout << "Stack is empty! So getTop failed!" << endl;
	}
}



template<class T>
void IsPopSucc(Stack<T>& a, T& x)
{
	if (a.Pop(x))
	{
		cout << "pop " << x << " 成功" << endl;
	}
	else
	{
		cout << "Stack is empty! So Pop failed!" << endl;
	}
}




template<class T>
void PrintIsEmpty(Stack<T>& a)
{
	if (a.IsEmpty())
	{
		cout << "Stack is empty" << endl;
	}
	else
	{
		cout << "Stack isn't empty" << endl;
	}
}


template<class T>
void PrintIsFull(Stack<T>& a)
{
	if (a.IsFull())
	{
		cout << "Stack is Full" << endl;
	}
	else
	{
		cout << "Stack isn't Full" << endl;
	}
}








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



/*
	#9*(9-3)/3+9*2+4#

*/