/*
7 stu1 男 19 前端工程师
2 stu2 女 21 人员管理
4 stu3 男 21 团队技术担当
6 stu4 女 18 人员管理
8 stu5 女 32 老师
3 stu6 男 19 老师
*/
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

//student结构体存放数据
struct student {
	int number = 0;
	string name = "";
	string sex = "";
	int age = 0;
	string type="";
};

template <class Type> class linkList;

//链表节点类
template <class Type> class linkNode {
protected:
	Type value;    //数据域
	linkNode<Type>* next;    //指针域
public:
	linkNode();    //构造函数
	void copyNode(const linkNode<Type>* link);    //复制节点信息
	void inputNode();    //输入节点信息
	friend class linkList<Type>;
};

//链表类
template <class Type> class linkList {
protected:
	linkNode<Type>* head;    //链表头指针
	int length = 0;    //链表长度
public:
	linkList(linkNode<Type>* link);    //带一个参数的构造函数
	linkList(linkNode<Type>* link, int number);    //带两个参数的构造函数
	~linkList();    //析构函数
	void print();    //打印链表节点信息
	linkNode<Type>* search(int locate);    //按位置查找节点信息
	linkNode<Type>* searchNumber(int number);    //按考号查找节点信息
	void searchInput();    //查找操作
	void insert();    //插入操作
	void cancel();    //删除操作
	void alter();    //修改操作
	void statistics();    //统计操作
	void operate();    //循环选择操作
};

//链表节点的构造函数
template <class Type>
linkNode<Type>::linkNode() {
	value = new student;
	next = NULL;
}

//复制节点信息
template <class Type>
void linkNode<Type>::copyNode(const linkNode<Type>* link) {
	value = new student;
	value->number = (link->value)->number;
	value->name = (link->value)->name;
	value->sex = (link->value)->sex;
	value->age = (link->value)->age;
	value->type = (link->value)->type;
	if (link->next != NULL)
		next = link->next;
	else
		next = NULL;
}

//输入节点信息及错误处理
template <class Type>
void linkNode<Type>::inputNode() {
	while (1) {
		cin >> value->number;
		cin >> value->name;
		cin >> value->sex;
		cin >> value->age;
		cin >> value->type;
		if (cin.fail()) {
			cout << "输入错误，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (value->name.length() >= 8) {
			cout << "姓名过长，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (value->type.length() >= 20) {
			cout << "报考类型过长，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (value->age < 0 || value->age >= 120) {
			cout << "年龄输入错误，应该在0-120之间，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (value->sex != "男" && value->sex != "女") {
			cout << "性别输入错误，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
}

//带一个参数的链表构造函数
template <class Type>
linkList<Type>::linkList(linkNode<Type>* link) {
	head = link;
	length = 0;
}

//带两个参数的链表构造函数
template <class Type>
linkList<Type>::linkList(linkNode<Type>* link, int number) {
	head = link;
	length = number;
	linkNode<Type>* temp;
	temp = head;
	if (head == NULL) {
		cout << "初始化失败" << endl;
		exit(-1);
	}
	for (int i = 0; i < length; i++) {
		linkNode<Type>* node = new linkNode<Type>;
		node->inputNode();
		temp->next = node;
		temp = node;
	}
	temp->next = NULL;
}

//链表类的析构函数
template <class Type>
linkList<Type>::~linkList() {
	linkNode<Type>* temp;
	temp = head;
	for (int i = 0; i < length + 1; i++) {
		linkNode<Type>* node = temp->next;
		delete temp;
		temp = node;
	}
	head = NULL;
}

//打印链表节点信息
template <class Type>
void linkList<Type>::print() {
	cout << endl;
	cout << "考号    姓名    性别    年龄    报考类别" << endl;
	linkNode<Type>* node = head->next;
	while (node != NULL) {
		Type value = node->value;
		cout << setw(8) << setiosflags(ios::left) << setw(8) << value->number << setw(8) << value->name << setw(8) << value->sex << setw(8) << value->age << setw(8) << value->type << endl;
		node = node->next;
	}
}

//按位置查找节点信息
template <class Type>
linkNode<Type>* linkList<Type>::search(int locate) {
	int step = 0;
	linkNode<Type>* temp = head->next;
	while (step < locate - 2) {
		temp = temp->next;
		step += 1;
	}
	return temp;
}

//按考号查找节点信息
template <class Type>
linkNode<Type>* linkList<Type>::searchNumber(int number) {
	int step = 0;
	linkNode<Type>* temp = head;
	while (step < length && ((temp->next)->value)->number != number) {
		temp = temp->next;
		step += 1;
	}
	if (step == length && (temp->value)->number != number) {
		return NULL;
	}
	else
		return temp;
}

//查找操作
template <class Type>
void linkList<Type>::searchInput() {
	int locate;
	cout << "请输入要查找的考生考号：";
	while (1) {
		cin >> locate;
		if (cin.fail()) {
			cout << "输入错误，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (!searchNumber(locate) && locate != (head->value)->number) {
			cout << "搜索不到该考生号，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	if (locate == (head->value)->number) {
		cout << "考号    姓名    性别    年龄    报考类别" << endl;
		cout << (head->value)->number << " " << (head->value)->name << " " << (head->value)->sex << " " << (head->value)->age << " " << (head->value)->type << endl;
	}
	else {
		cout << "考号    姓名    性别    年龄    报考类别" << endl;
		linkNode<Type>* node = searchNumber(locate)->next;
		cout << (node->value)->number << " " << (node->value)->name << " " << (node->value)->sex << " " << (node->value)->age << " " << (node->value)->type << endl;
	}
}

//插入操作
template <class Type>
void linkList<Type>::insert() {
	int locate;
	cout << "请输入您要插入的考生位置：";
	while (1) {
		cin >> locate;
		if (cin.fail() || locate <= 0 || locate > length + 1) {
			cout << "输入错误，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	cout << "请依次输入要插入的考生的考号、姓名、性别、年龄及报考类别！" << endl;
	linkNode<Type>* temp = new linkNode<Type>;
	if (temp == NULL) {
		cout << "初始化失败" << endl;
		exit(-1);
	}
	temp->inputNode();
	if (locate == 1) {
		length += 1;
		temp->next = head->next;
		head->next = temp;
	}
	else {
		linkNode<Type>* node = search(locate);
		temp->next = node->next;
		node->next = temp;
		length += 1;
	}
	print();
}

//删除操作
template <class Type>
void linkList<Type>::cancel() {
	if (length == 0) {
		cout << "无任何可删除数据" << endl;
		return;
	}
	int locate;
	cout << "请输入要删除的考生的考号：";
	while (1) {
		cin >> locate;
		if (cin.fail()) {
			cout << "输入错误，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (!searchNumber(locate) && locate != (head->value)->number) {
			cout << "搜索不到该考生号，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	linkNode<Type>* node = searchNumber(locate)->next;
	cout << "你删除的考生信息是：" << locate << " " << (node->value)->name << " " << (node->value)->sex << " " << (node->value)->age << " " << (node->value)->type << endl;
	if (((searchNumber(locate)->next)->next))
		searchNumber(locate)->next = (searchNumber(locate)->next)->next;
	else
		searchNumber(locate)->next = NULL;
	delete node;
	length -= 1;
	print();
}

//修改操作
template <class Type>
void linkList<Type>::alter() {
	int locate;
	cout << "请输入要修改的考生的考号：";
	while (1) {
		cin >> locate;
		if (cin.fail()) {
			cout << "输入错误，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (!searchNumber(locate) && locate != (head->value)->number) {
			cout << "搜索不到该考生号，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	cout << "请依次输入修改后该考生的考号、姓名、性别、年龄及报考类别！" << endl;
	if (locate == (head->value)->number) {
		head->inputNode();
	}
	else {
		linkNode<Type>* temp = searchNumber(locate)->next;
		temp->inputNode();
	}
	print();
}

//统计操作
template <class Type>
void linkList<Type>::statistics() {
	int type;
	cout << "请输入需要统计的数据（0为性别，1为年龄，2为报考类别）：";
	while (1) {
		cin >> type;
		if (cin.fail() || type < 0 || type > 2) {
			cout << "输入错误，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	if (type == 0) {    //对男性女性分别创建链表存储信息
		int step = 0;
		int male = 0, female = 0;
		linkNode<Type>* man = new linkNode<Type>;
		linkNode<Type>* woman = new linkNode<Type>;
		if (man == NULL || woman == NULL) {
			cout << "初始化失败" << endl;
			exit(-1);
		}
		linkNode<Type>* temp = head->next;
		linkNode<Type>* temp1 = man;
		linkNode<Type>* temp2 = woman;
		while (step < length) {
			linkNode<Type>* node = new linkNode<Type>;
			node->copyNode(temp);
			if (node == NULL) {
				cout << "初始化失败" << endl;
				exit(-1);
			}
			if ((temp->value)->sex== "男") {
				temp1->next = node;
				temp1 = node;
				male += 1;
			}
			else {
				temp2->next = node;
				temp2 = node;
				female += 1;
			}
			temp = temp->next;
			step += 1;
		}
		temp1->next = NULL;
		temp2->next = NULL;
		cout << "性别为男：共" << male << "条数据：" << endl;
		linkList<Type> linkMan(man);
		linkMan.print();
		cout << "性别为女：共" << female << "条数据：" << endl;
		linkList<Type> linkWoman(woman);
		linkWoman.print();
	}
	if (type == 1) {    //建立哈希表将年龄为i的考生信息存储在数组第i个元素上
		int step = 0;
		linkNode<Type>* temp = head->next;
		linkNode<Type>* age[120];
		linkNode<Type>* ageTemp[120];
		int ageSum[120] = { 0 };
		for (int i = 0; i < 120; i++) {
			age[i] = NULL;
			ageTemp[i] = NULL;
		}
		while (step < length) {
			if (age[(temp->value)->age] == NULL) {
				age[(temp->value)->age] = new linkNode<Type>;
				if (age[(temp->value)->age] == NULL) {
					cout << "初始化失败" << endl;
					exit(-1);
				}
				ageTemp[(temp->value)->age] = age[(temp->value)->age];
			}
			linkNode<Type>* node = new linkNode<Type>;
			node->copyNode(temp);
			if (node == NULL) {
				cout << "初始化失败" << endl;
				exit(-1);
			}
			ageTemp[(temp->value)->age]->next = node;
			ageTemp[(temp->value)->age] = node;
			ageSum[(temp->value)->age] += 1;
			temp = temp->next;
			step += 1;
		}
		for (int i = 0; i < 120; i++) {
			if (ageSum[i] != 0) {
				if (ageTemp[i] != NULL)
					ageTemp[i]->next = NULL;
				cout << "年龄为" << i << "：共" << ageSum[i] << "条数据：" << endl;
				linkList<Type> link(age[i]);
				link.print();
			}
		}
	}
	if (type == 2) {    //建立链表数组存放考生报考类别信息
		int step = 0, key = 0;
		linkNode<Type>* temp = head->next;
		linkNode<Type>* work[100];
		linkNode<Type>* workTemp[100];
		int workSum[100] = { 0 };
		string workType[100];
		for (int i = 0; i < 100; i++) {
			work[i] = NULL;
			workTemp[i] = NULL;
		}
		while (step < length) {
			int flag = 0;
			int keyNow = 0;
			for (int i = 0; i < key; i++) {
				if ((temp->value)->type == workType[i]) {
					keyNow = i;
					flag = 1;
				}
			}
			if (flag == 0) {
				workType[key] = (temp->value)->type;
				work[key] = new linkNode<Type>;
				if (work[key] == NULL) {
					cout << "初始化失败" << endl;
					exit(-1);
				}
				workTemp[key] = work[key];
				keyNow = key;
				key += 1;
			}
			linkNode<Type>* node = new linkNode<Type>;
			node->copyNode(temp);
			if (node == NULL) {
				cout << "初始化失败" << endl;
				exit(-1);
			}
			workTemp[keyNow]->next = node;
			workTemp[keyNow] = node;
			workSum[keyNow] += 1;
			temp = temp->next;
			step += 1;
		}
		for (int i = 0; i < 100; i++) {
			if (workSum[i] != 0) {
				if (workTemp[i] != NULL)
					workTemp[i]->next = NULL;
				cout << "报考类型为" << workType[i] << "：共" << workSum[i] << "条数据：" << endl;
				linkList<Type> link(work[i]);
				link.print();
			}
		}
	}
}

//循环选择操作
template <class Type>
void linkList<Type>::operate() {
	print();
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
	cout << endl;
	while (1) {
		cout << "请选择您要进行的操作：";
		int type;
		while (1) {
			cin >> type;
			if (cin.fail() || type < 0 || type>5) {
				cout << "输入错误，请重新输入：";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
			}
			else
				break;
		}
		if (type != 0)
			cout << "==================================================" << endl;
		if (type == 1)
			insert();
		if (type == 2)
			cancel();
		if (type == 3)
			searchInput();
		if (type == 4)
			alter();
		if (type == 5)
			statistics();
		if (type != 0)
			cout << "==================================================" << endl;
		if (type == 0)
			exit(0);

	}
}

//输入信息提示
void input() {
	int n = 0;
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生的人数：";
	while (1) {
		cin >> n;
		if (cin.fail() || n < 0) {
			cout << "输入错误，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	cout << "请依次输入考生的考号、姓名、性别、年龄、报考类别!" << endl;
	linkNode<student*>* head = new linkNode<student*>;
	linkList<student*> studentList(head, n);
	studentList.operate();
}

//主函数
int main() {
	input();
	return 0;
}