#include <iostream>
using namespace std;

template <class Type> class haffmanTree;
template <class Type> class haffmanTreeNode;

//最小堆的模板类
template <class Type>
class minHeap {
protected:
	int size;					//当前容量
	int maxSize = 100000;		//最大容量
	Type *heap;					//存放堆元素的数组
public:
	minHeap(int n, Type* elems);		//构造函数
	~minHeap();							//析构函数
	Type removeMin();					//最小元素出堆
	void insert(const Type& x);			//插入元素
	void siftDown(int start);			//自下而上调整最小堆
	void siftUp(int start);				//自上而下调整最小堆
	friend class haffmanTree<Type>;
	friend class haffmanTreeNode<Type>;
};

//哈夫曼树节点的模板类
template <class Type>
class haffmanTreeNode {
protected:
	Type value;										//数据域
	haffmanTreeNode* lChild, * rChild, * parent;    //指针域
public:
	haffmanTreeNode() :value(0), lChild(NULL), rChild(NULL), parent(NULL) {}	//无参构造函数
	haffmanTreeNode(Type v):value(v),lChild(NULL),rChild(NULL),parent(NULL){}	//带一个参数的构造函数
	friend class haffmanTree<Type>;
	friend class minHeap<haffmanTreeNode<Type>*>;
};

//哈夫曼树的模板类
template <class Type>
class haffmanTree {
protected:
	int size;						//哈夫曼树的节点个数
	haffmanTreeNode<Type>** elems;  //存放哈夫曼树节点元素
public:
	haffmanTree();									//构造函数
	~haffmanTree();									//析构函数
	int calculateWPL();								//计算哈夫曼树的WPL
	friend class haffmanTreeNode<Type>;
	friend class minHeap<haffmanTreeNode<Type>*>;
};

/*最小堆成员函数的体外实现*/

//最小堆构造函数
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

//最小堆析构函数
template <class Type>
minHeap<Type>::~minHeap() {
	delete heap;
}

//自上而下调整最小堆
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

//自下而上调整最小堆
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

//插入元素
template <class Type>
void minHeap<Type>::insert(const Type &x) {
	heap[size] = x;
	siftUp(size);
	size++;
}

//最小元素出堆
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

/*哈夫曼树成员函数的体外实现*/

//哈夫曼树构造函数
template <class Type>
haffmanTree<Type>::haffmanTree() {
	//输入及错误处理
	int n;
	cout << "请输入需要木头的个数：";
	while (1) {
		cin >> n;
		if (cin.fail()) {
			cout << "输入错误，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (n < 0 || n > 10000) {
			cout << "木头数量应在0到10000之间，请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	//创建森林
	size = 2 * n - 1;
	elems = new haffmanTreeNode<Type>*[2 * n - 1];
	for (int i = 0; i < 2 * n - 1; i++) {
		haffmanTreeNode<Type>* p = new haffmanTreeNode<Type>;
		elems[i] = p;
	}
	cout << "请输入每块木头的长度：";
	for (int i = 0; i < n; i++) {
		while (1) {
			cin >> elems[i]->value;
			if (cin.fail() || elems[i]->value < 0) {
				cout << "输入错误，请重新输入整段序列：";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
				i = 0;
			}
			else
				break;
		}
	}
	//利用最小堆创建哈夫曼树
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

//哈夫曼树构造函数
template <class Type>
haffmanTree<Type>::~haffmanTree() {
	delete elems;
}

//计算哈夫曼树的WPL
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
	cout << "最小花费为：";
	cout << haff.calculateWPL();
	return 0;
}