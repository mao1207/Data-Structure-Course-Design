//( ( 2 + 3 ) * 4 – ( 8 + 2 ) ) / 5
#include <iostream>
#include <sstream>
#include <stdio.h>
using namespace std;

#define SIZE 1000

//运算符数组
char ope[6] = { '+','-','*','/','(',')'};

//顺序栈的模板类
template <class T>
class Stack {
protected:
	T elems[SIZE] = {};    //存储数组
	int head = 0;    //栈顶指针
public:
	void push(T elem);    //元素入栈
	T pop();    //元素出栈
	bool isEmpty();    //判断栈是否为空
	T getTop();    //读取栈顶元素
	int getLength();    //获取栈元素个数
};

//计算器类
class calculator {
protected:
	string sign[SIZE];    //输入字符
	string result[SIZE];    //后缀表达式字符
	string ans;    //表达式计算结果
	bool state = true;    //判断是否输入错误
	int length = 0;    //输入字符个数
	int step = 0;    //后缀表达式字符个数
public:
	calculator(char sentense[]);    //构造函数
	int judge(string x);    //查找字符优先级
	void print();    //转换为后缀表达式并打印结果
	int answer();    //求出表达式的计算结果
};

//元素入栈
template <class T>
void Stack<T>::push(T elem) {
	if (!isEmpty() && elem == ")" && elems[head - 1] == "(") {
		head -= 1;
		return;
	}
	elems[head] = elem;
	head++;
}

//元素出栈
template <class T>
T Stack<T>::pop() {
	head--;
	return elems[head];
}

//判断栈是否为空
template <class T>
bool Stack<T>::isEmpty() {
	if (head == 0)
		return true;
	else
		return false;
}

//读取栈顶元素
template <class T>
T Stack<T>::getTop() {
	return elems[head - 1];
}

//获取栈元素个数
template <class T>
int Stack<T>::getLength() {
	return head;
}

//构造函数
calculator::calculator(char sentense[]) {
	length = 0;
	string num = "";
	for (int i = 0; sentense[i] != '\0'; i++) {
		if (sentense[i] == ' ' && sentense[i + 1] != ' ' || sentense[i + 1] == '\0') {
			sign[length] = num;
			num = "";
			length += 1;
		}
		else {
			if (sentense[i] == '+' && sentense[i + 1] >= '0' && sentense[i + 1] <= '9')
				continue;
			num += sentense[i];
		}
	}
	for (int i = 0; i < length; i++) {
		if (judge(sign[i]) < 0) {
			cout << "输入错误" << endl;
			state = false;
			return;
		}
	}
}

//判断字符优先级
int calculator::judge(string x) {
	int num = 0;
	for (int i = 0; i < x.length(); i++) {
		if (i == 0 && x[i] == '-')
			continue;
		if ((x[i] < '0' || x[i] > '9') && x[i] != '.')
			break;
		if (x[i] == '.') {
			num += 1;
			if (num > 1)
				break;
		}
		if (i == x.length() - 1)
			return 0;    //字符为数字
	}
	if (x.length() == 1) {
		for (int i = 0; i < 6; i++) {
			if (x[0] == ope[i]) {
				if (x[0] == '(')
					return 4;    //字符为'('
				if (x[0] == '*' || x[0] == '/')
					return 3;    //字符为'*'或'/'
				if (x[0] == '+' || x[0] == '-')
					return 2;    //字符为'+'或'-'
				if (x[0] == ')')
					return 1;    //字符为')'
			}
		}
	}
	return -1;    //报错返回-1
}

//求出后缀表达式并打印结果
void calculator::print() {
	Stack<string> temp;
	for (int i = 0; i < length; i++) {
		if (judge(sign[i]) == 0) {
			result[step] = sign[i];
			step += 1;
		}
		else {
			if (temp.isEmpty() || judge(sign[i]) > judge(temp.getTop()))
				temp.push(sign[i]);
			else {
				while (!temp.isEmpty() && judge(sign[i]) <= judge(temp.getTop())) {
					if (judge(temp.getTop()) != 4) {
						result[step] = temp.pop();
						step += 1;
					}
					else
						break;
				}
				temp.push(sign[i]);
			}
		}
	}
	while (!temp.isEmpty()) {
		result[step] = temp.pop();
		step += 1;
	}
	if (answer() == -1 && state == true) {
		cout << "缺少运算数" << endl;
		state = false;
	}
	if (answer() == -2 && state == true) {
		cout << "缺少运算符" << endl;
		state = false;
	}
	if (answer() == -3 && state == true) {
		cout << "除数不能为0" << endl;
		state = false;
	}
	if (answer() == -4 && state == true) {
		cout << "括号不匹配" << endl;
		state = false;
	}
	if (state) {
		cout << "转换为后缀表达式是：";
		for (int i = 0; i < step; i++) {
			cout << result[i];
			if (i != step - 1)
				cout << " ";
		}
		cout << endl;
		cout << "计算结果是：" << ans << endl;
	}
}

//求出表达式的计算结果
int calculator::answer() {
	Stack<string> stack;
	for (int i = 0; i < step; i++) {
		if (judge(result[i]) > 0) {
			if (judge(result[i]) == 4 || judge(result[i]) == 1)
				return -4;
			if (stack.getLength() < 2)
				return -1;
			stringstream s1(stack.pop());
			stringstream s2(stack.pop());
			double x1, x2, newNumber = 0;
			s1 >> x1;
			s2 >> x2;
			if (result[i] == "+")
				newNumber = x2 + x1;
			else if (result[i] == "-")
				newNumber = x2 - x1;
			else if (result[i] == "*")
				newNumber = x2 * x1;
			else if (result[i] == "/") {
				if (x1 == 0)
					return -3;
				newNumber = x2 / x1;
			}
			ostringstream os;
			os.precision(16);
			os << newNumber;
			stack.push(os.str());
		}
		else if (judge(result[i]) == 0)
			stack.push(result[i]);
	}
	if (stack.getLength() != 1)
		return -2;
	ans= stack.getTop();
	return true;
}

int main()
{
	cout << "========================================" << endl;
	cout << "**            智能计算系统            **" << endl;
	cout << "========================================" << endl;
	
	while (1) {
		char sentense[SIZE];
		string sign[SIZE];
		cout << "请输入运算表达式，注意不同符号间用空格分隔：";
		fgets(sentense, SIZE, stdin);
		calculator transform(sentense);
		transform.print();
		char tag;
		cout << "是否继续(y/n):";
		while (1) {
			cin >> tag;
			if (cin.fail() || (tag != 'n' && tag != 'N' && tag != 'y' && tag != 'Y')) {
				cout << "输入错误，请重新输入：";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
			}
			else
				break;
		}
		char t;
		while ((t = cin.get()) != '\n');
		if (tag == 'n' || tag == 'N')
			break;
	}
}