/*
a b 8
b c 7
c d 5
d a 11
a c 18
b d 12
-1 -1 -1
*/
#include <iostream>
using namespace std;

template <class NameType, class DistType> class Graph;

//�ߵ�ģ����
template <class NameType, class DistType>
class Edge {
protected:
	int dest;												//�ߵ��յ�
	DistType cost;											//�ߵ�Ȩ��
	Edge<NameType, DistType>* link;							//ָ����һ���ߵ�ָ��
public:
	Edge():dest(0), cost(0), link(NULL){};					//�޲ι��캯��
	Edge(int D,DistType C):dest(D),cost(C),link(NULL){}		//�������εĹ��캯��
	friend Graph<NameType, DistType>;
};

//�����ģ����
template <class NameType, class DistType>
class Vertex {
protected:
	NameType data;											//��������
	Edge <NameType,DistType> * adj;							//ָ����ñ����ڵ�һ���ߵ�ָ��
public:
	Vertex() :data("0"), adj(NULL) {};						//���캯��
	friend Graph<NameType, DistType>;
};

//ͼ��ģ����
template <class NameType, class DistType>
class Graph {
protected:
	Vertex<NameType, DistType>* nodeList;							//�����		
	int vertexNumber;												//��������
	int edgeNumber;													//������
public:
	Graph() :nodeList(NULL), vertexNumber(0), edgeNumber(0) {};		//���캯��
	~Graph();														//��������
	void createVertex();											//���������
	void createEdge();												//������
	int findVertex(NameType v);										//���Ҷ�����vertexList�е�λ��
	void update(int vertex, DistType* &lowcost, int* &nearvex);		//����lowcost��nearvex����
	void printGraph();												//��ӡͼ
	void kruskal(Graph<NameType, DistType>* &result, bool& state);	//������С������Kruskal
	void prim(Graph<NameType, DistType>*& result, bool& state);		//������С������Prim
};

//��С�ѵ�ģ����
template <class Type>
class minHeap {
protected:
	int size;					//��ǰ����
	int maxSize = 100000;		//�������
	Type* heap;					//��Ŷ�Ԫ�ص�����
public:
	minHeap() :size(0), heap(NULL) { heap = new Type[maxSize]; }
	minHeap(int n, Type* elems);		//���캯��
	~minHeap();							//��������
	Type removeMin();					//��СԪ�س���
	void insert(const Type& x);			//����Ԫ��
	void siftDown(int start);			//���¶��ϵ�����С��
	void siftUp(int start);				//���϶��µ�����С��
};

//���鼯��
class UFsets {
protected:
	int size;							//���鼯��С
	int* parents;						//ǰ������
public:
	UFsets(int n);						//���캯��
	~UFsets();                          //��������
	int find(int x);					//���ҽڵ�ǰ��
	bool compare(int x, int y);			//�Ƚ������ڵ�ǰ���Ƿ�һ��
	void combine(int root1,int root2);  //�ϲ������ڵ�
};

//�������ģ��ϵͳ��
template <class NameType,class DistType>
class PowerCost {
protected:
	Graph<NameType, DistType>* power;    //ͼ��Ϣ
public:
	PowerCost();				   		 //���캯��
	void operation();					 //ѭ������
};

/*ͼ��ģ���ຯ������ʵ��*/

//��������
template <class NameType,class DistType>
Graph<NameType, DistType>::~Graph() {
	for (int i = 0; i < vertexNumber; i++) {
		Edge<NameType, DistType>* p = nodeList[i].adj;
		while (p != NULL) {
			Edge<NameType, DistType>* q = p->link;
			delete p;
			p = q;
		}
	}
	delete nodeList;
}

//���Ҷ�����vertexList�е�λ��
template <class NameType,class DistType>
int Graph<NameType, DistType>::findVertex(NameType v) {
	for (int i = 0; i < vertexNumber; i++) {
		if (nodeList[i].data == v)
			return i;
	}
	return -1;
}

//���������
template <class NameType,class DistType>
void Graph <NameType, DistType> ::createVertex() {
	//���뼰������
	cout << "�����붥��ĸ�����";
	while (1) {
		cin >> vertexNumber;
		if (cin.fail()) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (vertexNumber < 0)
			cout << "�������Ӧ����0�����������룺";
		else
			break;
	}
	nodeList = new Vertex<NameType, DistType>[vertexNumber];
	cout << "�������������������ƣ�";
	for (int i = 0; i < vertexNumber; i++) {
		while (1) {
			if (i >= 0 && i < vertexNumber)
				cin >> nodeList[i].data;
			if (cin.fail()) {
				cout << "�������,�������������ζ������У�";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
				i = -1;
				break;
			}
			for (int j = 0; j < i; j++) {
				if (nodeList[j].data == nodeList[i].data) {
					cout << "�����ظ�,�������������ζ������У�";
					cin.clear();
					char t;
					while ((t = cin.get()) != '\n');
					i = -1;
					break;
				}
			}
			break;
		}
	}
	char t;
	while ((t = cin.get()) != '\n');
}

//������
template <class NameType,class DistType>
void Graph<NameType, DistType>::createEdge() {
	while (1) {
		//���뼰������
		NameType begin, end;
		int weight;
		cout << "�������������㼰�ߣ�";
		cin >> begin >> end >> weight;
		//�������ʹ���
		if (cin.fail()) {
			cout << "�����������������" << endl;
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
			continue;
		}
		//��ֹ����
		if (begin == "-1" && end == "-1" && weight == -1)
			break;
		//�����ȨΪ����
		if (weight < 0) {
			cout << "�߲���Ϊ����������������" << endl;;
			continue;
		}
		//���붥�㲻����
		int flag1 = findVertex(begin);
		int flag2 = findVertex(end);
		if (flag1 == -1 || flag2 == -1) {
			cout << "���㲻���ڣ�����������" << endl;;
			continue;
		}
		if (flag1 == flag2) {
			cout << "���ܴ��ڻ�������������" << endl;
			continue;
		}

		//������
		edgeNumber += 1;
		Edge<NameType, DistType>* newEdge = new Edge<NameType, DistType>;
		newEdge->dest = flag2;
		newEdge->cost = weight;
		newEdge->link = nodeList[flag1].adj;
		nodeList[flag1].adj = newEdge;

		//��ջ�����
		char t;
		while ((t = cin.get()) != '\n');
	}
}

//��ӡͼ
template <class NameType,class DistType>
void Graph<NameType, DistType>::printGraph() {
	for (int i = 0; i < vertexNumber; i++) {
		Edge<NameType, DistType>* p = nodeList[i].adj;
		while (p!=NULL) {
			cout << nodeList[i].data << "-<" << p->cost << ">-" << nodeList[p->dest].data << "  ";
			p = p->link;
		}
	}
	cout << endl;
}

//����lowcost��nearvex����
template <class NameType, class DistType>
void Graph<NameType, DistType>::update(int vertex, DistType* &lowcost, int* &nearvex) {
	nearvex[vertex] = -1;
	for (int i = 0; i < vertexNumber; i++) {
		Edge<NameType, DistType>* p = nodeList[i].adj;
		while (p != NULL) {
			if (i == vertex || p->dest == vertex) {
				if (i == vertex) {
					if (lowcost[p->dest] > p->cost && nearvex[p->dest] != -1) {
						lowcost[p->dest] = p->cost;
						nearvex[p->dest] = vertex;
					}
				}
				else {
					if (lowcost[i] > p->cost && nearvex[i] != -1) {
						lowcost[i] = p->cost;
						nearvex[i] = vertex;
					}
				}
			}
			p = p->link;
		}
	}
}

//������С������Kruskal
template <class NameType,class DistType>
void Graph<NameType, DistType>::kruskal(Graph<NameType, DistType>*& result, bool& state) {
	//��С�������߽ṹ��
	struct MSTEdge {
		int value = 0;
		Vertex<NameType, DistType> head;
		Edge<NameType, DistType>* tail=new Edge<NameType, DistType>;
	};
	//��С���벢�鼯��ʼ��
	minHeap<MSTEdge*> heap;
	UFsets sets(vertexNumber);
	result->vertexNumber = vertexNumber;
	result->edgeNumber = edgeNumber;
	result->nodeList = new Vertex<NameType,DistType>[vertexNumber];
	for (int i = 0; i < vertexNumber; i++) {
		result->nodeList[i] = nodeList[i];
		result->nodeList[i].adj = NULL;
		Edge<NameType, DistType>* p = nodeList[i].adj;
		while (p != NULL) {
			Edge<NameType, DistType>* q = new Edge<NameType, DistType>;
			q->cost = p->cost;
			q->dest = p->dest;
			q->link = p->link;
			MSTEdge* m = new MSTEdge;
			m->value = p->cost;
			m->head = nodeList[i];
			m->tail = q;
			heap.insert(m);
			p = p->link;
		}
	}
	//Kruskal�㷨ʵ��
	int sum1 = 0;
	int sum2 = 0;
	while (sum1 < vertexNumber - 1) {
		sum2 += 1;
		MSTEdge* edge = heap.removeMin();
		int flag1 = findVertex(edge->head.data);
		int flag2 = edge->tail->dest;
		if (sets.compare(flag1,flag2))
			continue;
		else {
			Edge<NameType, DistType>* p = edge->tail;
			p->link = result->nodeList[flag1].adj;
			result->nodeList[flag1].adj = p;
			sets.combine(flag1, flag2);
			sum1 += 1;
		}
		if (sum1 < vertexNumber - 1 && sum2 == edgeNumber) {
			cout << "����ͨͼ��������С��������" << endl;
			state = false;
			return;
		}
	}
	cout << "����Kruskal��С��������" << endl;
	state = true;
}

//������С������Prim
template <class NameType, class DistType>
void Graph<NameType, DistType>::prim(Graph<NameType, DistType>*& result, bool& state) {
	NameType start;
	int temp = 0;
	int dest = 0;
	//������ʼ����
	cout << "��������ʼ���㣺";
	while (1) {
		cin >> start;
		if (cin.fail()) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
			continue;
		}
		else if ((temp = findVertex(start)) == -1) {
			cout << "�ýڵ㲻���ڣ����������룺";
			continue;
		}
		else
			break;
	}
	//��ʼ��lowcost������nearvex����
	DistType* lowcost = new DistType[vertexNumber];
	int* nearvex = new int[vertexNumber];
	for (int i = 0; i < vertexNumber; i++) {
		lowcost[i] = 214783647;
		nearvex[i] = 0;
	}
	//prim�㷨ʵ��
	result->vertexNumber = vertexNumber;
	result->edgeNumber = edgeNumber;
	result->nodeList = new Vertex<NameType, DistType>[vertexNumber];
	for (int i = 0; i < vertexNumber; i++) {
		result->nodeList[i] = nodeList[i];
		result->nodeList[i].adj = NULL;
	}
	lowcost[temp] = 0;
	for (int i = 0; i < vertexNumber; i++) {
		update(temp, lowcost, nearvex);
		int min = 2147483647;
		for (int j = 0; j < vertexNumber; j++) {
			if (lowcost[j] < min && nearvex[j] != -1) {
				min = lowcost[j];
				dest = j;
			}
		}
		Edge<NameType, DistType>* minEdge = new Edge<NameType, DistType>(dest, lowcost[dest]);
		if (i != vertexNumber - 1) {
			minEdge->link = result->nodeList[nearvex[dest]].adj;
			result->nodeList[nearvex[dest]].adj = minEdge;
		}
		temp = dest;
	}
	for (int i = 0; i < vertexNumber; i++) {
		if (nearvex[i] != -1) {
			cout << "����ͨͼ��������С��������" << endl;
			state = false;
			return;
		}
	}
	cout << "����Prim��С��������" << endl;
	state = true;
}

/*��С��ģ���ຯ��������ʵ��*/

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
void minHeap<Type>::insert(const Type& x) {
	heap[size] = x;
	siftUp(size);
	size++;
}

//��СԪ�س���
template <class Type>
Type minHeap<Type>::removeMin() {
	Type result;
	if (!size)
		return heap[0];
	else {
		result = heap[0];
		heap[0] = heap[size - 1];
		size--;
		siftDown(0);
	}
	return result;
}

/*���鼯ģ���������ʵ��*/

//���캯��
UFsets::UFsets(int n) {
	size = n;
	parents = new int[n];
	for (int i = 0; i < n; i++) {
		parents[i] = -1;
	}
}

//��������
UFsets::~UFsets() {
	delete parents;
}

//�Ƚϲ���
bool UFsets::compare(int x, int y) {
	return (find(x) == find(y));
}

//��������
int UFsets::find(int x) {
	while (parents[x] != -1) {
		x = parents[x];
	}
	return x;
}

//�ϲ�����
void UFsets::combine(int root1, int root2) {
	parents[find(root2)] = root1;
}

/*�������ģ��ϵͳ�ຯ������ʵ��*/

//���캯��
template <class NameType,class DistType>
PowerCost<NameType, DistType>::PowerCost() {
	cout << "**           �������ģ��ϵͳ           **" << endl;
	cout << "==========================================" << endl;
	cout << "**          ��ѡ��Ҫִ�еĲ���:         **" << endl;
	cout << "**          A --- ������������          **" << endl;
	cout << "**          B --- ��ӵ����ı�          **" << endl;
	cout << "**          C --- ������С������        **" << endl;
	cout << "**          D --- ��ʾ��С������        **" << endl;
	cout << "**          E --- �˳�����              **" << endl;
	cout << "==========================================" << endl;
	power= new Graph<NameType, DistType>;
}

//��������
template <class NameType, class DistType>
void PowerCost<NameType, DistType>::operation() {
	Graph<string, int>* result = new Graph<NameType, DistType>;
	bool state = 0;
	while (1) {
		cout << "==========================================" << endl;
		char type;
		cout << "��ѡ��Ҫִ�еĲ�����";
		cin >> type;
		char t;
		while ((t = cin.get()) != '\n');
		if (type == 'A' || type == 'a')
			power->createVertex();
		else if (type == 'B' || type == 'b')
			power->createEdge();
		else if (type == 'C' || type == 'c') {
			int type = 1;
			cout << "��ѡ������С�������ķ�����1:kruskal 2:prim��:";
			while (1) {
				cin >> type;
				if (cin.fail() || type < 1 || type>2) {
					cout << "����������������룺";
					cin.clear();
					char t;
					while ((t = cin.get()) != '\n');
					continue;
				}
				else
					break;
			}
			if (type == 1)
				power->kruskal(result, state);
			else
				power->prim(result, state);
		}
		else if (type == 'D' || type == 'd') {
			if (state) {
				cout << "��С�������Ķ��㼰��Ϊ��" << endl;
				result->printGraph();
			}
			else
				cout << "����ͨͼ��������С��������" << endl;
		}
		else if (type == 'E' || type == 'e')
			exit(0);
		else {
			cout << "�����������������" << endl;
		}
	}
}

int main()
{
	PowerCost<string, int> power;
	power.operation();
	return 0;
}