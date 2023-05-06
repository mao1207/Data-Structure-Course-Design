#include <iostream>
using namespace std;
#define SIZE 1000

//ѭ������ʵ��
template <typename T>
class Queue {
protected:
	T elems[SIZE] = {};    //�洢����
	int front = 0, rear = 0;    //����ָ�����βָ��
public:
	//Ԫ�������
	void push(T elem) {
		elems[rear] = elem;
		rear = (rear + 1) % SIZE;
	}
	//Ԫ�س�����
	T pop() {
		int temp = front;
		front = (front + 1) % SIZE;
		return elems[temp];
	}
	//�ж϶����Ƿ�Ϊ��
	bool isEmpty() {
		if (rear == front)
			return true;
		return false;
	}
};

//����˿��������˿ͱ��
void input(Queue<int> windowA, Queue<int> windowB,int &step,int result[]) {
	int sum;
	cout << "�����뵽�����е��������˿����У�" << endl;
	//�����������
	while (1) {
		cin >> sum;
		if (cin.fail()) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (sum > 1000 || sum < 0) {
			cout << "�˿�����Ӧ��0-1000��Χ�ڣ����������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	for (int i = 0; i < sum; i++) {
		int number;
		while (1) {
			cin >> number;
			if (cin.fail()) {
				cout << "������������������������У�";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
				i = 0;
				while (!windowA.isEmpty())
					windowA.pop();
				while (!windowB.isEmpty())
					windowB.pop();
				cin >> sum;
			}
			else
				break;
		}
		if (number % 2 == 1)
			windowA.push(number);
		else
			windowB.push(number);
	}
	int p = 0;
	//��˳���������Ԫ��
	while (!windowA.isEmpty() && !windowB.isEmpty()) {
		if (p % 3 != 2 && !windowA.isEmpty()) {
			result[step] = windowA.pop();
			step += 1;
			p += 1;
		}
		if (p % 3 == 2 && !windowB.isEmpty()) {
			result[step] = windowB.pop();
			step += 1;
			p += 1;
		}
	}
	//���������ʣ��ֱ�����
	while (!windowA.isEmpty()) {
		result[step] = windowA.pop();
		step += 1;
	}
	while (!windowB.isEmpty()) {
		result[step] = windowB.pop();
		step += 1;
	}
}

//���ҵ�����˳��
void output(int step,int result[]) {
	cout << "��ҵ�����˳��Ĺ˿����У�" << endl;
	for (int i = 0; i < step; i++) {
		cout << result[i];
		if (i != step - 1)
			cout << " ";
	}
}

int main()
{
	Queue<int> windowA, windowB;
	int result[SIZE] = {};
	int step = 0;
	input(windowA, windowB, step, result);
	output(step, result);
}