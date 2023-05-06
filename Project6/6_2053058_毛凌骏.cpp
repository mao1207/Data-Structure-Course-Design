#include <iostream>
#include <cstring>
#include <assert.h>
using namespace std;

//����ģ��������
template <class Type> class Tree;

//���ڵ��ģ����
template <class Type>
class treeNode {
protected:
	Type value;    //������
	treeNode<Type>* firstChild, * nextSibling;    //ָ����
public:
	treeNode(Type v = 0, treeNode<Type>* f = NULL, treeNode<Type>* n = NULL) :
		value(v),firstChild(f),nextSibling(n) {}    //���캯��

	friend class Tree<Type>;
	friend class Family;
};

//����ģ����
template <class Type>
class Tree {
protected:
	treeNode<Type>* root, *current;                 //ָ����
public:
	Tree();											//Ĭ�Ϲ��캯��
	Tree(const Type& value);						//��һ�������Ĺ��캯��
	bool find(treeNode<Type>* root, Type key);		//���ҽڵ�
	void insertChild(const Type& value);			//����ڵ�
	void deleteChild(treeNode<Type>* p);            //�ݹ�ɾ����
	void deleteChild();                             //ɾ������
	treeNode<Type>* findFirstChild();               //Ѱ��ǰ����
	treeNode<Type>* findNextSibling();              //Ѱ��ǰ�ֵ�
	void changeNode(const Type& value);             //�޸Ľڵ�
	friend class treeNode<Type>;
	friend class Family;
};

//���׹���ϵͳ��
class Family {
protected:
	Tree<string>* root;
public:
	Family();				  		  //���캯��
	void build();					  //���Ƽ���
	void add();                       //��Ӽ�ͥ��Ա
	void cancel();                    //��ɢ�ֲ���ͥ
	void change();					  //���ļ�ͥ��Ա����
	void printChild(string name);     //��ӡ��Ů
	friend class treeNode<string>;    
	friend class Tree<string>;
};

/* ���ຯ��������ʵ�� */

//Ĭ�Ϲ��캯��
template <class Type>
Tree<Type>::Tree() {
	root = current = NULL;
}

//��һ�������Ĺ��캯��
template <class Type>
Tree<Type>::Tree(const Type& value) {
	root = new treeNode<Type>(value);
	current = root;
}

//���ҽڵ�
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

//����ڵ�
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

//�޸Ľڵ�
template <class Type>
void Tree<Type>::changeNode(const Type& value) {
	current->value = value;
}

//Ѱ��ǰ����
template <class Type>
treeNode<Type>* Tree<Type>::findFirstChild() {
	treeNode<Type>* temp = current->firstChild;
	current = temp;
	return temp;
}

//Ѱ��ǰ�ֵ�
template <class Type>
treeNode<Type>* Tree<Type>::findNextSibling() {
	treeNode<Type>* temp = current->nextSibling;
	current = temp;
	return temp;
}

//�ݹ�ɾ����
template <class Type>
void Tree<Type>::deleteChild(treeNode<Type>* p) {
	if (p != NULL) {
		deleteChild(p->firstChild);
		deleteChild(p->nextSibling);
		delete p;
	}
}

//ɾ������
template <class Type>
void Tree<Type>::deleteChild() {
	if (current != NULL) {
		deleteChild(current->firstChild);
		current->firstChild = NULL;
	}
}

/* ���׹���ϵͳ�ຯ��������ʵ�� */

//���캯��
Family::Family() {
	cout << "**            ���׹���ϵͳ            **" << endl;
	cout << "========================================" << endl;
	cout << "**         ��ѡ��Ҫִ�еĲ���:        **" << endl;
	cout << "**          A --- ���Ƽ���            **" << endl;
	cout << "**          B --- ��Ӽ�ͥ��Ա        **" << endl;
	cout << "**          C --- ��ɢ�ֲ���ͥ        **" << endl;
	cout << "**          D --- ���ļ�ͥ��Ա����    **" << endl;
	cout << "**          E --- �˳�����            **" << endl;
	cout << "========================================" << endl;
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�������";
	string name;
	cin >> name;
	const string p = name;
	root = new Tree<string>(name);
	cout << "�˼��׵������ǣ�" << name << endl;
}

//��ӡ��Ů
void Family::printChild(string name) {
	if (root->find(root->root, name) == false) {
		cout << name << "������" ;
		return;
	}
	else {
		treeNode<string>* firstChild = root->findFirstChild();
		if (firstChild == NULL) {
			cout << name << "����Ů";
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

//���Ƽ���
void Family::build() {
	cout << "������Ҫ������ͥ���˵�������";
	string name;
	cin >> name;
	char t;
	while ((t = cin.get()) != '\n');
	if (root->find(root->root,name) == NULL) {
		cout << "δ�ҵ�����" << endl;
		return;
	}
	else if(root->findFirstChild()!=NULL) {
		cout << "�������м�ͥ��������B�����Ů" << endl;
		return;
	}
	else {
		root->find(root->root, name);
		int number;
		cout << "������" << name << "�Ķ�Ů������";
		while (1) {
			cin >> number;
			if (cin.fail()) {
				cout << "����������������룺";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
			}
			else if (number < 0) {
				cout << "��Ů����Ӧ����0�����������룺";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
			}
			else
				break;
		}
		cout << "����������" << name << "�Ķ�Ů��������";
		for (int i = 0; i < number; i++) {
			string childName;
			cin >> childName;
			root->insertChild(childName);
		}
		cout << name << "�ĵ�һ�������ǣ�";
		printChild(name);
		cout << endl;
	}
}

//��Ӽ�ͥ��Ա
void Family::add() {
	string name;
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	cin >> name;
	char t;
	while ((t = cin.get()) != '\n');
	if (root->find(root->root, name) == NULL) {
		cout << "δ�ҵ�����" << endl;
		return;
	}
	else {
		cout << "������" << name << "����ӵĶ��ӣ���Ů�������˵�������";
		string childName;
		cin >> childName;
		root->find(root->root, name);
		root->insertChild(childName);
		cout << name << "�ĵ�һ�������ǣ�";
		printChild(name);
		cout << endl;
	}
}

//��ɢ�ֲ���ͥ
void Family::cancel() {
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	string name;
	cin >> name;
	char t;
	while ((t = cin.get()) != '\n');
	if (root->find(root->root, name) == NULL) {
		cout << "δ�ҵ�����" << endl;
		return;
	}
	else {
		cout << "Ҫ��ɢ��ͥ�����ǣ�" << name << endl;
		cout << name << "�ĵ�һ�������ǣ�";
		printChild(name);
		root->find(root->root, name);
		root->deleteChild();
		cout << endl;
	}
}

//���ļ�ͥ��Ա����
void Family::change() {
	cout << "������Ҫ�����������˵�Ŀǰ������";
	string name;
	cin >> name;
	char t;
	while ((t = cin.get()) != '\n');
	if (root->find(root->root, name) == NULL) {
		cout << "δ�ҵ�����" << endl;
		return;
	}
	else {
		cout << "��������ĺ��������";
		string nameChange;
		cin >> nameChange;
		char t;
		while ((t = cin.get()) != '\n');
		root->changeNode(nameChange);
		cout << name << "�Ѹ���Ϊ" << nameChange << endl;
	}
}

int main()
{
	Family genealogy;
	while (1) {
		cout << "========================================" << endl;
		char type;
		cout << "��ѡ��Ҫִ�еĲ�����";
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
			cout << "�����������������" << endl;
		}
	}
}