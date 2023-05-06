#include <iostream>
#include <cstring>
#include <assert.h>
using namespace std;

//树的模板类声明
template <class Type> class Tree;

//树节点的模板类
template <class Type>
class treeNode {
protected:
	Type value;    //数据域
	treeNode<Type>* firstChild, * nextSibling;    //指针域
public:
	treeNode(Type v = 0, treeNode<Type>* f = NULL, treeNode<Type>* n = NULL) :
		value(v),firstChild(f),nextSibling(n) {}    //构造函数

	friend class Tree<Type>;
	friend class Family;
};

//树的模板类
template <class Type>
class Tree {
protected:
	treeNode<Type>* root, *current;                 //指针域
public:
	Tree();											//默认构造函数
	Tree(const Type& value);						//带一个参数的构造函数
	bool find(treeNode<Type>* root, Type key);		//查找节点
	void insertChild(const Type& value);			//插入节点
	void deleteChild(treeNode<Type>* p);            //递归删除树
	void deleteChild();                             //删除子树
	treeNode<Type>* findFirstChild();               //寻当前长子
	treeNode<Type>* findNextSibling();              //寻当前兄弟
	void changeNode(const Type& value);             //修改节点
	friend class treeNode<Type>;
	friend class Family;
};

//家谱管理系统类
class Family {
protected:
	Tree<string>* root;
public:
	Family();				  		  //构造函数
	void build();					  //完善家谱
	void add();                       //添加家庭成员
	void cancel();                    //解散局部家庭
	void change();					  //更改家庭成员姓名
	void printChild(string name);     //打印子女
	friend class treeNode<string>;    
	friend class Tree<string>;
};

/* 树类函数的体外实现 */

//默认构造函数
template <class Type>
Tree<Type>::Tree() {
	root = current = NULL;
}

//带一个参数的构造函数
template <class Type>
Tree<Type>::Tree(const Type& value) {
	root = new treeNode<Type>(value);
	current = root;
}

//查找节点
template <class Type>
bool Tree<Type>::find(treeNode<Type>* node, Type key) {
	if (node == NULL)
		return false;
	if (node->value == key) {
		current = node;
		return true;
	}
	else {
		if (find(node->nextSibling, key) == true)
			return true;
		if (node->firstChild != NULL && find(node->nextSibling, key) == false)
			return find(node->firstChild, key);
	}
	return false;
}

//插入节点
template <class Type>
void Tree<Type>::insertChild(const Type& value) {
	if (current->firstChild == NULL) {
		treeNode<Type>* p = new treeNode<Type>(value);
		current->firstChild = p;
	}
	else {
		treeNode<Type>* p = current->firstChild;
		while (p->nextSibling != NULL)
			p = p->nextSibling;
		treeNode<Type>* q = new treeNode<Type>(value);
		assert(q != NULL);
		p->nextSibling = q;
	}
}

//修改节点
template <class Type>
void Tree<Type>::changeNode(const Type& value) {
	current->value = value;
}

//寻当前长子
template <class Type>
treeNode<Type>* Tree<Type>::findFirstChild() {
	treeNode<Type>* temp = current->firstChild;
	current = temp;
	return temp;
}

//寻当前兄弟
template <class Type>
treeNode<Type>* Tree<Type>::findNextSibling() {
	treeNode<Type>* temp = current->nextSibling;
	current = temp;
	return temp;
}

//递归删除树
template <class Type>
void Tree<Type>::deleteChild(treeNode<Type>* p) {
	if (p != NULL) {
		deleteChild(p->firstChild);
		deleteChild(p->nextSibling);
		delete p;
	}
}

//删除子树
template <class Type>
void Tree<Type>::deleteChild() {
	if (current != NULL) {
		deleteChild(current->firstChild);
		current->firstChild = NULL;
	}
}

/* 家谱管理系统类函数的体外实现 */

//构造函数
Family::Family() {
	cout << "**            家谱管理系统            **" << endl;
	cout << "========================================" << endl;
	cout << "**         请选择要执行的操作:        **" << endl;
	cout << "**          A --- 完善家谱            **" << endl;
	cout << "**          B --- 添加家庭成员        **" << endl;
	cout << "**          C --- 解散局部家庭        **" << endl;
	cout << "**          D --- 更改家庭成员姓名    **" << endl;
	cout << "**          E --- 退出程序            **" << endl;
	cout << "========================================" << endl;
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	string name;
	cin >> name;
	const string p = name;
	root = new Tree<string>(name);
	cout << "此家谱的祖先是：" << name << endl;
}

//打印子女
void Family::printChild(string name) {
	if (root->find(root->root, name) == false) {
		cout << name << "不存在" ;
		return;
	}
	else {
		treeNode<string>* firstChild = root->findFirstChild();
		if (firstChild == NULL) {
			cout << name << "无子女";
			return;
		}
		else {
			cout << firstChild->value << " ";
			while (1) {
				treeNode<string>* nextSibling = root->findNextSibling();
				if (nextSibling == NULL)
					break;
				cout<< nextSibling->value << " ";
			}

		}
	}
}

//完善家谱
void Family::build() {
	cout << "请输入要建立家庭的人的姓名：";
	string name;
	cin >> name;
	char t;
	while ((t = cin.get()) != '\n');
	if (root->find(root->root,name) == NULL) {
		cout << "未找到此人" << endl;
		return;
	}
	else if(root->findFirstChild()!=NULL) {
		cout << "此人已有家庭，可输入B添加子女" << endl;
		return;
	}
	else {
		root->find(root->root, name);
		int number;
		cout << "请输入" << name << "的儿女个数：";
		while (1) {
			cin >> number;
			if (cin.fail()) {
				cout << "输入错误，请重新输入：";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
			}
			else if (number < 0) {
				cout << "儿女个数应大于0，请重新输入：";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
			}
			else
				break;
		}
		cout << "请依次输入" << name << "的儿女的姓名：";
		for (int i = 0; i < number; i++) {
			string childName;
			cin >> childName;
			root->insertChild(childName);
		}
		cout << name << "的第一代子孙是：";
		printChild(name);
		cout << endl;
	}
}

//添加家庭成员
void Family::add() {
	string name;
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	cin >> name;
	char t;
	while ((t = cin.get()) != '\n');
	if (root->find(root->root, name) == NULL) {
		cout << "未找到此人" << endl;
		return;
	}
	else {
		cout << "请输入" << name << "新添加的儿子（或女儿）的人的姓名：";
		string childName;
		cin >> childName;
		root->find(root->root, name);
		root->insertChild(childName);
		cout << name << "的第一代子孙是：";
		printChild(name);
		cout << endl;
	}
}

//解散局部家庭
void Family::cancel() {
	cout << "请输入要解散家庭的人的姓名：";
	string name;
	cin >> name;
	char t;
	while ((t = cin.get()) != '\n');
	if (root->find(root->root, name) == NULL) {
		cout << "未找到此人" << endl;
		return;
	}
	else {
		cout << "要解散家庭的人是：" << name << endl;
		cout << name << "的第一代子孙是：";
		printChild(name);
		root->find(root->root, name);
		root->deleteChild();
		cout << endl;
	}
}

//更改家庭成员姓名
void Family::change() {
	cout << "请输入要更改姓名的人的目前姓名：";
	string name;
	cin >> name;
	char t;
	while ((t = cin.get()) != '\n');
	if (root->find(root->root, name) == NULL) {
		cout << "未找到此人" << endl;
		return;
	}
	else {
		cout << "请输入更改后的姓名：";
		string nameChange;
		cin >> nameChange;
		char t;
		while ((t = cin.get()) != '\n');
		root->changeNode(nameChange);
		cout << name << "已更名为" << nameChange << endl;
	}
}

int main()
{
	Family genealogy;
	while (1) {
		cout << "========================================" << endl;
		char type;
		cout << "请选择要执行的操作：";
		cin >> type;
		char t;
		while ((t = cin.get()) != '\n');
		if (type == 'A' || type == 'a')
			genealogy.build();
		else if (type == 'B' || type == 'b')
			genealogy.add();
		else if (type == 'C' || type == 'c')
			genealogy.cancel();
		else if (type == 'D' || type == 'd')
			genealogy.change();
		else if (type == 'E' || type == 'e')
			return 0;
		else {
			cout << "输入错误，请重新输入" << endl;
		}
	}
}