/*
7 stu1 �� 19 ǰ�˹���ʦ
2 stu2 Ů 21 ��Ա����
4 stu3 �� 21 �ŶӼ�������
6 stu4 Ů 18 ��Ա����
8 stu5 Ů 32 ��ʦ
3 stu6 �� 19 ��ʦ
*/
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

//student�ṹ��������
struct student {
	int number = 0;
	string name = "";
	string sex = "";
	int age = 0;
	string type="";
};

template <class Type> class linkList;

//����ڵ���
template <class Type> class linkNode {
protected:
	Type value;    //������
	linkNode<Type>* next;    //ָ����
public:
	linkNode();    //���캯��
	void copyNode(const linkNode<Type>* link);    //���ƽڵ���Ϣ
	void inputNode();    //����ڵ���Ϣ
	friend class linkList<Type>;
};

//������
template <class Type> class linkList {
protected:
	linkNode<Type>* head;    //����ͷָ��
	int length = 0;    //������
public:
	linkList(linkNode<Type>* link);    //��һ�������Ĺ��캯��
	linkList(linkNode<Type>* link, int number);    //�����������Ĺ��캯��
	~linkList();    //��������
	void print();    //��ӡ����ڵ���Ϣ
	linkNode<Type>* search(int locate);    //��λ�ò��ҽڵ���Ϣ
	linkNode<Type>* searchNumber(int number);    //�����Ų��ҽڵ���Ϣ
	void searchInput();    //���Ҳ���
	void insert();    //�������
	void cancel();    //ɾ������
	void alter();    //�޸Ĳ���
	void statistics();    //ͳ�Ʋ���
	void operate();    //ѭ��ѡ�����
};

//����ڵ�Ĺ��캯��
template <class Type>
linkNode<Type>::linkNode() {
	value = new student;
	next = NULL;
}

//���ƽڵ���Ϣ
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

//����ڵ���Ϣ��������
template <class Type>
void linkNode<Type>::inputNode() {
	while (1) {
		cin >> value->number;
		cin >> value->name;
		cin >> value->sex;
		cin >> value->age;
		cin >> value->type;
		if (cin.fail()) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (value->name.length() >= 8) {
			cout << "�������������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (value->type.length() >= 20) {
			cout << "�������͹��������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (value->age < 0 || value->age >= 120) {
			cout << "�����������Ӧ����0-120֮�䣬���������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (value->sex != "��" && value->sex != "Ů") {
			cout << "�Ա�����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
}

//��һ�������������캯��
template <class Type>
linkList<Type>::linkList(linkNode<Type>* link) {
	head = link;
	length = 0;
}

//�����������������캯��
template <class Type>
linkList<Type>::linkList(linkNode<Type>* link, int number) {
	head = link;
	length = number;
	linkNode<Type>* temp;
	temp = head;
	if (head == NULL) {
		cout << "��ʼ��ʧ��" << endl;
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

//���������������
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

//��ӡ����ڵ���Ϣ
template <class Type>
void linkList<Type>::print() {
	cout << endl;
	cout << "����    ����    �Ա�    ����    �������" << endl;
	linkNode<Type>* node = head->next;
	while (node != NULL) {
		Type value = node->value;
		cout << setw(8) << setiosflags(ios::left) << setw(8) << value->number << setw(8) << value->name << setw(8) << value->sex << setw(8) << value->age << setw(8) << value->type << endl;
		node = node->next;
	}
}

//��λ�ò��ҽڵ���Ϣ
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

//�����Ų��ҽڵ���Ϣ
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

//���Ҳ���
template <class Type>
void linkList<Type>::searchInput() {
	int locate;
	cout << "������Ҫ���ҵĿ������ţ�";
	while (1) {
		cin >> locate;
		if (cin.fail()) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (!searchNumber(locate) && locate != (head->value)->number) {
			cout << "���������ÿ����ţ����������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	if (locate == (head->value)->number) {
		cout << "����    ����    �Ա�    ����    �������" << endl;
		cout << (head->value)->number << " " << (head->value)->name << " " << (head->value)->sex << " " << (head->value)->age << " " << (head->value)->type << endl;
	}
	else {
		cout << "����    ����    �Ա�    ����    �������" << endl;
		linkNode<Type>* node = searchNumber(locate)->next;
		cout << (node->value)->number << " " << (node->value)->name << " " << (node->value)->sex << " " << (node->value)->age << " " << (node->value)->type << endl;
	}
}

//�������
template <class Type>
void linkList<Type>::insert() {
	int locate;
	cout << "��������Ҫ����Ŀ���λ�ã�";
	while (1) {
		cin >> locate;
		if (cin.fail() || locate <= 0 || locate > length + 1) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	cout << "����������Ҫ����Ŀ����Ŀ��š��������Ա����估�������" << endl;
	linkNode<Type>* temp = new linkNode<Type>;
	if (temp == NULL) {
		cout << "��ʼ��ʧ��" << endl;
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

//ɾ������
template <class Type>
void linkList<Type>::cancel() {
	if (length == 0) {
		cout << "���κο�ɾ������" << endl;
		return;
	}
	int locate;
	cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
	while (1) {
		cin >> locate;
		if (cin.fail()) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (!searchNumber(locate) && locate != (head->value)->number) {
			cout << "���������ÿ����ţ����������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	linkNode<Type>* node = searchNumber(locate)->next;
	cout << "��ɾ���Ŀ�����Ϣ�ǣ�" << locate << " " << (node->value)->name << " " << (node->value)->sex << " " << (node->value)->age << " " << (node->value)->type << endl;
	if (((searchNumber(locate)->next)->next))
		searchNumber(locate)->next = (searchNumber(locate)->next)->next;
	else
		searchNumber(locate)->next = NULL;
	delete node;
	length -= 1;
	print();
}

//�޸Ĳ���
template <class Type>
void linkList<Type>::alter() {
	int locate;
	cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�";
	while (1) {
		cin >> locate;
		if (cin.fail()) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (!searchNumber(locate) && locate != (head->value)->number) {
			cout << "���������ÿ����ţ����������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	cout << "�����������޸ĺ�ÿ����Ŀ��š��������Ա����估�������" << endl;
	if (locate == (head->value)->number) {
		head->inputNode();
	}
	else {
		linkNode<Type>* temp = searchNumber(locate)->next;
		temp->inputNode();
	}
	print();
}

//ͳ�Ʋ���
template <class Type>
void linkList<Type>::statistics() {
	int type;
	cout << "��������Ҫͳ�Ƶ����ݣ�0Ϊ�Ա�1Ϊ���䣬2Ϊ������𣩣�";
	while (1) {
		cin >> type;
		if (cin.fail() || type < 0 || type > 2) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	if (type == 0) {    //������Ů�Էֱ𴴽�����洢��Ϣ
		int step = 0;
		int male = 0, female = 0;
		linkNode<Type>* man = new linkNode<Type>;
		linkNode<Type>* woman = new linkNode<Type>;
		if (man == NULL || woman == NULL) {
			cout << "��ʼ��ʧ��" << endl;
			exit(-1);
		}
		linkNode<Type>* temp = head->next;
		linkNode<Type>* temp1 = man;
		linkNode<Type>* temp2 = woman;
		while (step < length) {
			linkNode<Type>* node = new linkNode<Type>;
			node->copyNode(temp);
			if (node == NULL) {
				cout << "��ʼ��ʧ��" << endl;
				exit(-1);
			}
			if ((temp->value)->sex== "��") {
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
		cout << "�Ա�Ϊ�У���" << male << "�����ݣ�" << endl;
		linkList<Type> linkMan(man);
		linkMan.print();
		cout << "�Ա�ΪŮ����" << female << "�����ݣ�" << endl;
		linkList<Type> linkWoman(woman);
		linkWoman.print();
	}
	if (type == 1) {    //������ϣ������Ϊi�Ŀ�����Ϣ�洢�������i��Ԫ����
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
					cout << "��ʼ��ʧ��" << endl;
					exit(-1);
				}
				ageTemp[(temp->value)->age] = age[(temp->value)->age];
			}
			linkNode<Type>* node = new linkNode<Type>;
			node->copyNode(temp);
			if (node == NULL) {
				cout << "��ʼ��ʧ��" << endl;
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
				cout << "����Ϊ" << i << "����" << ageSum[i] << "�����ݣ�" << endl;
				linkList<Type> link(age[i]);
				link.print();
			}
		}
	}
	if (type == 2) {    //�������������ſ������������Ϣ
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
					cout << "��ʼ��ʧ��" << endl;
					exit(-1);
				}
				workTemp[key] = work[key];
				keyNow = key;
				key += 1;
			}
			linkNode<Type>* node = new linkNode<Type>;
			node->copyNode(temp);
			if (node == NULL) {
				cout << "��ʼ��ʧ��" << endl;
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
				cout << "��������Ϊ" << workType[i] << "����" << workSum[i] << "�����ݣ�" << endl;
				linkList<Type> link(work[i]);
				link.print();
			}
		}
	}
}

//ѭ��ѡ�����
template <class Type>
void linkList<Type>::operate() {
	print();
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
	cout << endl;
	while (1) {
		cout << "��ѡ����Ҫ���еĲ�����";
		int type;
		while (1) {
			cin >> type;
			if (cin.fail() || type < 0 || type>5) {
				cout << "����������������룺";
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

//������Ϣ��ʾ
void input() {
	int n = 0;
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼����������";
	while (1) {
		cin >> n;
		if (cin.fail() || n < 0) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	cout << "���������뿼���Ŀ��š��������Ա����䡢�������!" << endl;
	linkNode<student*>* head = new linkNode<student*>;
	linkList<student*> studentList(head, n);
	studentList.operate();
}

//������
int main() {
	input();
	return 0;
}