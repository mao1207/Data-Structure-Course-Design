#include <iostream>
using namespace std;
#define SIZE 1000

//循环队列实现
template <typename T>
class Queue {
protected:
	T elems[SIZE] = {};    //存储数组
	int front = 0, rear = 0;    //队首指针与队尾指针
public:
	//元素入队列
	void push(T elem) {
		elems[rear] = elem;
		rear = (rear + 1) % SIZE;
	}
	//元素出队列
	T pop() {
		int temp = front;
		front = (front + 1) % SIZE;
		return elems[temp];
	}
	//判断队列是否为空
	bool isEmpty() {
		if (rear == front)
			return true;
		return false;
	}
};

//输入顾客总数及顾客编号
void input(Queue<int> windowA, Queue<int> windowB,int &step,int result[]) {
	int sum;
	cout << "请输入到达银行的人数及顾客序列：" << endl;
	//输入与错误处理
	while (1) {
		cin >> sum;
		if (cin.fail()) {
			cout << "输入错误，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (sum > 1000 || sum < 0) {
			cout << "顾客总数应在0-1000范围内，请重新输入：";
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
				cout << "输入错误，请重新输入整段序列：";
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
	//按顺序输出队列元素
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
	//如果队列有剩余直接输出
	while (!windowA.isEmpty()) {
		result[step] = windowA.pop();
		step += 1;
	}
	while (!windowB.isEmpty()) {
		result[step] = windowB.pop();
		step += 1;
	}
}

//输出业务完成顺序
void output(int step,int result[]) {
	cout << "按业务完成顺序的顾客序列：" << endl;
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