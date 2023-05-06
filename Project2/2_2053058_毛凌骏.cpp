#include <iostream>
using namespace std;
template <class Type> class linkList;

//����ڵ���
template <class Type> class linkNode {
protected:
	Type value;    //������
	linkNode<Type>* next;    //ָ����
public:	
	friend class linkList<Type>;
	template<class T>
	friend void jointLink(linkList<T>& s1, linkList<T>& s2);
};

//������
template <class Type> class linkList {
protected:
	linkNode<Type>* head;    //����ͷָ��
public:
	linkList();    //���캯��
	~linkList();    //��������
	linkList(linkNode<Type>* node);    //��һ�������Ĺ��캯��
	void print();    //��ӡ����ڵ���Ϣ
	bool search(int n);    //�����Ƿ�Ϊ����ڵ㣬�����򷵻�true

	template<class T>
	friend void jointLink(linkList<T> &s1, linkList<T> &s2);
};

//�����๹�캯��
template<class Type>
linkList<Type>::linkList() {
	head = new linkNode<Type>;
	if (head == NULL) {
		cout << "��ʼ��ʧ��" << endl;
		exit(-1);
	}
	linkNode<Type>* temp = head;
	int last = 0;
	while (1) {
		linkNode<Type>* node = new linkNode<Type>;
		if (node == NULL) {
			cout << "��ʼ��ʧ��" << endl;
			exit(-1);
		}
		int m;
		cin >> m;
		if (m == -1)
			break;
		if (cin.fail() || m < 0 || m < last) {
			cout << "������������������������У�";
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

//��������������
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

//�������һ�������Ĺ��캯��
template<class Type>
linkList<Type>::linkList(linkNode<Type>* node) {
	head = node;
}

//��ӡ����ڵ���Ϣ
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

//�����Ƿ�Ϊ����ڵ㣬�����򷵻�true
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

//�����󽻼��ĺ���
template<class Type>
void jointLink(linkList<Type>& s1, linkList<Type>& s2) {
	linkNode<Type>* resultNode = new linkNode<Type>;
	linkNode<Type>* end = resultNode;
	if (end == NULL) {
		cout << "��ʼ��ʧ��" << endl;
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
	cout << "�������һ�������ɸ����������ɵķǽ�������s1����-1��ʾ���еĽ�β:";
	linkList<int> s1;
	cout << "������ڶ��������ɸ����������ɵķǽ�������s2����-1��ʾ���еĽ�β:";
	linkList<int> s2;
	cout << "��������s1Ϊ��";
	s1.print();
	cout << endl;
	cout << "��������s2Ϊ��";
	s2.print();
	cout << endl;
	cout << "�����������еĽ�������Ϊ��";
	jointLink<int>(s1, s2);
}