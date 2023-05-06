//( ( 2 + 3 ) * 4 �C ( 8 + 2 ) ) / 5
#include <iostream>
#include <sstream>
#include <stdio.h>
using namespace std;

#define SIZE 1000

//���������
char ope[6] = { '+','-','*','/','(',')'};

//˳��ջ��ģ����
template <class T>
class Stack {
protected:
	T elems[SIZE] = {};    //�洢����
	int head = 0;    //ջ��ָ��
public:
	void push(T elem);    //Ԫ����ջ
	T pop();    //Ԫ�س�ջ
	bool isEmpty();    //�ж�ջ�Ƿ�Ϊ��
	T getTop();    //��ȡջ��Ԫ��
	int getLength();    //��ȡջԪ�ظ���
};

//��������
class calculator {
protected:
	string sign[SIZE];    //�����ַ�
	string result[SIZE];    //��׺���ʽ�ַ�
	string ans;    //���ʽ������
	bool state = true;    //�ж��Ƿ��������
	int length = 0;    //�����ַ�����
	int step = 0;    //��׺���ʽ�ַ�����
public:
	calculator(char sentense[]);    //���캯��
	int judge(string x);    //�����ַ����ȼ�
	void print();    //ת��Ϊ��׺���ʽ����ӡ���
	int answer();    //������ʽ�ļ�����
};

//Ԫ����ջ
template <class T>
void Stack<T>::push(T elem) {
	if (!isEmpty() && elem == ")" && elems[head - 1] == "(") {
		head -= 1;
		return;
	}
	elems[head] = elem;
	head++;
}

//Ԫ�س�ջ
template <class T>
T Stack<T>::pop() {
	head--;
	return elems[head];
}

//�ж�ջ�Ƿ�Ϊ��
template <class T>
bool Stack<T>::isEmpty() {
	if (head == 0)
		return true;
	else
		return false;
}

//��ȡջ��Ԫ��
template <class T>
T Stack<T>::getTop() {
	return elems[head - 1];
}

//��ȡջԪ�ظ���
template <class T>
int Stack<T>::getLength() {
	return head;
}

//���캯��
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
			cout << "�������" << endl;
			state = false;
			return;
		}
	}
}

//�ж��ַ����ȼ�
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
			return 0;    //�ַ�Ϊ����
	}
	if (x.length() == 1) {
		for (int i = 0; i < 6; i++) {
			if (x[0] == ope[i]) {
				if (x[0] == '(')
					return 4;    //�ַ�Ϊ'('
				if (x[0] == '*' || x[0] == '/')
					return 3;    //�ַ�Ϊ'*'��'/'
				if (x[0] == '+' || x[0] == '-')
					return 2;    //�ַ�Ϊ'+'��'-'
				if (x[0] == ')')
					return 1;    //�ַ�Ϊ')'
			}
		}
	}
	return -1;    //������-1
}

//�����׺���ʽ����ӡ���
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
		cout << "ȱ��������" << endl;
		state = false;
	}
	if (answer() == -2 && state == true) {
		cout << "ȱ�������" << endl;
		state = false;
	}
	if (answer() == -3 && state == true) {
		cout << "��������Ϊ0" << endl;
		state = false;
	}
	if (answer() == -4 && state == true) {
		cout << "���Ų�ƥ��" << endl;
		state = false;
	}
	if (state) {
		cout << "ת��Ϊ��׺���ʽ�ǣ�";
		for (int i = 0; i < step; i++) {
			cout << result[i];
			if (i != step - 1)
				cout << " ";
		}
		cout << endl;
		cout << "�������ǣ�" << ans << endl;
	}
}

//������ʽ�ļ�����
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
	cout << "**            ���ܼ���ϵͳ            **" << endl;
	cout << "========================================" << endl;
	
	while (1) {
		char sentense[SIZE];
		string sign[SIZE];
		cout << "������������ʽ��ע�ⲻͬ���ż��ÿո�ָ���";
		fgets(sentense, SIZE, stdin);
		calculator transform(sentense);
		transform.print();
		char tag;
		cout << "�Ƿ����(y/n):";
		while (1) {
			cin >> tag;
			if (cin.fail() || (tag != 'n' && tag != 'N' && tag != 'y' && tag != 'Y')) {
				cout << "����������������룺";
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