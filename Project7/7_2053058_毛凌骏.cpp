#include <iostream>
using namespace std;

template <class Type> class haffmanTree;
template <class Type> class haffmanTreeNode;

//��С�ѵ�ģ����
template <class Type>
class minHeap {
protected:
	int size;					//��ǰ����
	int maxSize = 100000;		//�������
	Type *heap;					//��Ŷ�Ԫ�ص�����
public:
	minHeap(int n, Type* elems);		//���캯��
	~minHeap();							//��������
	Type removeMin();					//��СԪ�س���
	void insert(const Type& x);			//����Ԫ��
	void siftDown(int start);			//���¶��ϵ�����С��
	void siftUp(int start);				//���϶��µ�����С��
	friend class haffmanTree<Type>;
	friend class haffmanTreeNode<Type>;
};

//���������ڵ��ģ����
template <class Type>
class haffmanTreeNode {
protected:
	Type value;										//������
	haffmanTreeNode* lChild, * rChild, * parent;    //ָ����
public:
	haffmanTreeNode() :value(0), lChild(NULL), rChild(NULL), parent(NULL) {}	//�޲ι��캯��
	haffmanTreeNode(Type v):value(v),lChild(NULL),rChild(NULL),parent(NULL){}	//��һ�������Ĺ��캯��
	friend class haffmanTree<Type>;
	friend class minHeap<haffmanTreeNode<Type>*>;
};

//����������ģ����
template <class Type>
class haffmanTree {
protected:
	int size;						//���������Ľڵ����
	haffmanTreeNode<Type>** elems;  //��Ź��������ڵ�Ԫ��
public:
	haffmanTree();									//���캯��
	~haffmanTree();									//��������
	int calculateWPL();								//�������������WPL
	friend class haffmanTreeNode<Type>;
	friend class minHeap<haffmanTreeNode<Type>*>;
};

/*��С�ѳ�Ա����������ʵ��*/

//��С�ѹ��캯��
template <class Type>
minHeap<Type>::minHeap(int n, Type* elems) {
	size = n;
	heap = new Type[maxSize];
	for (int i = 0; i < n; i++) {
		heap[i] = elems[i];
	}
	int start = (n - 2) / 2;
	while (start >= 0) {
		siftDown(start);
		start--;
	}
}

//��С����������
template <class Type>
minHeap<Type>::~minHeap() {
	delete heap;
}

//���϶��µ�����С��
template<class Type>
void minHeap<Type>::siftDown(int start) {
	int i = start, j = 2 * i + 1;
	Type temp = heap[i];
	while (j < size) {
		if (j < size - 1 && heap[j]->value > heap[j + 1]->value)
			j++;
		if (heap[j]->value < temp->value) {
			heap[i] = heap[j];
			i = j;
			j = 2 * i + 1;
		}
		else
			break;
	}
	heap[i] = temp;
}

//���¶��ϵ�����С��
template <class Type>
void minHeap<Type>::siftUp(int start) {
	int i = start, j = (i - 1) / 2;
	Type temp = heap[i];
	while (i > 0) {
		if (heap[j]->value > temp->value) {
			heap[i] = heap[j];
			i = j;
			j = (j - 1) / 2;
		}
		else
			break;
	}
	heap[i] = temp;
}

//����Ԫ��
template <class Type>
void minHeap<Type>::insert(const Type &x) {
	heap[size] = x;
	siftUp(size);
	size++;
}

//��СԪ�س���
template <class Type>
Type minHeap<Type>::removeMin() {
	Type result;
	if (!size)
		return 0;
	else {
		result = heap[0];
		heap[0] = heap[size - 1];
		size--;
		siftDown(0);
	}
	return result;
}

/*����������Ա����������ʵ��*/

//�����������캯��
template <class Type>
haffmanTree<Type>::haffmanTree() {
	//���뼰������
	int n;
	cout << "��������Ҫľͷ�ĸ�����";
	while (1) {
		cin >> n;
		if (cin.fail()) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (n < 0 || n > 10000) {
			cout << "ľͷ����Ӧ��0��10000֮�䣬���������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	//����ɭ��
	size = 2 * n - 1;
	elems = new haffmanTreeNode<Type>*[2 * n - 1];
	for (int i = 0; i < 2 * n - 1; i++) {
		haffmanTreeNode<Type>* p = new haffmanTreeNode<Type>;
		elems[i] = p;
	}
	cout << "������ÿ��ľͷ�ĳ��ȣ�";
	for (int i = 0; i < n; i++) {
		while (1) {
			cin >> elems[i]->value;
			if (cin.fail() || elems[i]->value < 0) {
				cout << "������������������������У�";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
				i = 0;
			}
			else
				break;
		}
	}
	//������С�Ѵ�����������
	minHeap<haffmanTreeNode<Type>*> minh(n, elems);
	for (int i = n; i < 2 * n - 1; i++) {
		haffmanTreeNode<Type>* s1 = minh.removeMin();
		haffmanTreeNode<Type>* s2 = minh.removeMin();
		elems[i]->lChild = s1;
		elems[i]->rChild = s2;
		elems[i]->value = s1->value + s2->value;
		s1->parent = elems[i];
		s2->parent = elems[i];
		minh.insert(elems[i]);
	}	
}

//�����������캯��
template <class Type>
haffmanTree<Type>::~haffmanTree() {
	delete elems;
}

//�������������WPL
template <class Type>
int haffmanTree<Type>::calculateWPL() {
	int result = 0;
	for (int i = 0; i < size; i++) {
		if (elems[i]->lChild != NULL && elems[i]->rChild != NULL)
			result += elems[i]->value;
	}
	return result;
}
int main()
{
	haffmanTree<int> haff;
	cout << "��С����Ϊ��";
	cout << haff.calculateWPL();
	return 0;
}