#include <iostream>
using namespace std;
template <class Type> class linkList;

//链表节点类
template <class Type> class linkNode {
protected:
	Type value;    //数据域
	linkNode<Type>* next;    //指针域
public:	
	friend class linkList<Type>;
	template<class T>
	friend void jointLink(linkList<T>& s1, linkList<T>& s2);
};

//链表类
template <class Type> class linkList {
protected:
	linkNode<Type>* head;    //链表头指针
public:
	linkList();    //构造函数
	~linkList();    //析构函数
	linkList(linkNode<Type>* node);    //带一个参数的构造函数
	void print();    //打印链表节点信息
	bool search(int n);    //查找是否为链表节点，若是则返回true

	template<class T>
	friend void jointLink(linkList<T> &s1, linkList<T> &s2);
};

//链表类构造函数
template<class Type>
linkList<Type>::linkList() {
	head = new linkNode<Type>;
	if (head == NULL) {
		cout << "初始化失败" << endl;
		exit(-1);
	}
	linkNode<Type>* temp = head;
	int last = 0;
	while (1) {
		linkNode<Type>* node = new linkNode<Type>;
		if (node == NULL) {
			cout << "初始化失败" << endl;
			exit(-1);
		}
		int m;
		cin >> m;
		if (m == -1)
			break;
		if (cin.fail() || m < 0 || m < last) {
			cout << "输入错误，请重新输入整个序列：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
			temp = head;
			last = 0;
			continue;
		}
		node->value = m;
		temp->next = node;
		temp = node;
		last = m;
	}
	temp->next = NULL;
}

//链表类析构函数
template<class Type>
linkList<Type>::~linkList() {
	linkNode<Type>* temp = head;
	while (temp!=NULL) {
		linkNode<Type>* node = temp->next;
		delete temp;
		temp = node;
	}
	delete temp;
	head = NULL;
}

//链表类带一个参数的构造函数
template<class Type>
linkList<Type>::linkList(linkNode<Type>* node) {
	head = node;
}

//打印链表节点信息
template<class Type>
void linkList<Type>::print() {
	linkNode<Type>* temp = head->next;
	int flag = 0;
	while (temp != NULL) {
		cout << temp->value;
		if (temp->next != NULL)
			cout << " ";
		temp = temp->next;
		flag = 1;
	}
	if (!flag)
		cout << "NULL";
}

//查找是否为链表节点，若是则返回true
template<class Type>
bool linkList<Type>::search(int n) {
	linkNode<Type>* temp = head->next;
	while (temp != NULL) {
		if (temp->value == n)
			return true;
		temp = temp->next;
	}
	return false;
}

//用于求交集的函数
template<class Type>
void jointLink(linkList<Type>& s1, linkList<Type>& s2) {
	linkNode<Type>* resultNode = new linkNode<Type>;
	linkNode<Type>* end = resultNode;
	if (end == NULL) {
		cout << "初始化失败" << endl;
		exit(-1);
	}
	linkNode<Type>* ps1 = (s1.head)->next;
	linkNode<Type>* ps2 = (s2.head)->next;
	while (ps1 != NULL && ps2 != NULL) {
		if (ps1->value == ps2->value) {
			linkNode<Type>* node = new linkNode<Type>;
			node->value = ps1->value;
			end->next = node;
			end = node;
			ps1 = ps1->next;
			ps2 = ps2->next;
		}
		else if (ps1->value > ps2->value)
			ps2 = ps2->next;
		else
			ps1 = ps1->next;
	}
	end->next = NULL;
	linkList<int> result(resultNode);
	result.print();
}

int main()
{
	cout << "请输入第一个由若干个正整数构成的非降序序列s1，用-1表示序列的结尾:";
	linkList<int> s1;
	cout << "请输入第二个由若干个正整数构成的非降序序列s2，用-1表示序列的结尾:";
	linkList<int> s2;
	cout << "输入序列s1为：";
	s1.print();
	cout << endl;
	cout << "输入序列s2为：";
	s2.print();
	cout << endl;
	cout << "两个输入序列的交集序列为：";
	jointLink<int>(s1, s2);
}