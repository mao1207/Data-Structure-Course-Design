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

//边的模板类
template <class NameType, class DistType>
class Edge {
protected:
	int dest;												//边的终点
	DistType cost;											//边的权重
	Edge<NameType, DistType>* link;							//指向下一条边的指针
public:
	Edge():dest(0), cost(0), link(NULL){};					//无参构造函数
	Edge(int D,DistType C):dest(D),cost(C),link(NULL){}		//带两个参的构造函数
	friend Graph<NameType, DistType>;
};

//顶点的模板类
template <class NameType, class DistType>
class Vertex {
protected:
	NameType data;											//顶点名称
	Edge <NameType,DistType> * adj;							//指向与该边相邻第一条边的指针
public:
	Vertex() :data("0"), adj(NULL) {};						//构造函数
	friend Graph<NameType, DistType>;
};

//图的模板类
template <class NameType, class DistType>
class Graph {
protected:
	Vertex<NameType, DistType>* nodeList;							//顶点表		
	int vertexNumber;												//顶点数量
	int edgeNumber;													//边数量
public:
	Graph() :nodeList(NULL), vertexNumber(0), edgeNumber(0) {};		//构造函数
	~Graph();														//析构函数
	void createVertex();											//创建顶点表
	void createEdge();												//创建边
	int findVertex(NameType v);										//查找顶点在vertexList中的位置
	void update(int vertex, DistType* &lowcost, int* &nearvex);		//更新lowcost与nearvex数组
	void printGraph();												//打印图
	void kruskal(Graph<NameType, DistType>* &result, bool& state);	//构建最小生成树Kruskal
	void prim(Graph<NameType, DistType>*& result, bool& state);		//构建最小生成树Prim
};

//最小堆的模板类
template <class Type>
class minHeap {
protected:
	int size;					//当前容量
	int maxSize = 100000;		//最大容量
	Type* heap;					//存放堆元素的数组
public:
	minHeap() :size(0), heap(NULL) { heap = new Type[maxSize]; }
	minHeap(int n, Type* elems);		//构造函数
	~minHeap();							//析构函数
	Type removeMin();					//最小元素出堆
	void insert(const Type& x);			//插入元素
	void siftDown(int start);			//自下而上调整最小堆
	void siftUp(int start);				//自上而下调整最小堆
};

//并查集类
class UFsets {
protected:
	int size;							//并查集大小
	int* parents;						//前驱数组
public:
	UFsets(int n);						//构造函数
	~UFsets();                          //析构函数
	int find(int x);					//查找节点前驱
	bool compare(int x, int y);			//比较两个节点前驱是否一致
	void combine(int root1,int root2);  //合并两个节点
};

//电网造价模拟系统类
template <class NameType,class DistType>
class PowerCost {
protected:
	Graph<NameType, DistType>* power;    //图信息
public:
	PowerCost();				   		 //构造函数
	void operation();					 //循环操作
};

/*图的模板类函数类外实现*/

//析构函数
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

//查找顶点在vertexList中的位置
template <class NameType,class DistType>
int Graph<NameType, DistType>::findVertex(NameType v) {
	for (int i = 0; i < vertexNumber; i++) {
		if (nodeList[i].data == v)
			return i;
	}
	return -1;
}

//创建顶点表
template <class NameType,class DistType>
void Graph <NameType, DistType> ::createVertex() {
	//输入及错误处理
	cout << "请输入顶点的个数：";
	while (1) {
		cin >> vertexNumber;
		if (cin.fail()) {
			cout << "输入错误请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (vertexNumber < 0)
			cout << "顶点个数应大于0，请重新输入：";
		else
			break;
	}
	nodeList = new Vertex<NameType, DistType>[vertexNumber];
	cout << "请依次输入各顶点的名称：";
	for (int i = 0; i < vertexNumber; i++) {
		while (1) {
			if (i >= 0 && i < vertexNumber)
				cin >> nodeList[i].data;
			if (cin.fail()) {
				cout << "输入错误,请重新输入整段顶点序列：";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
				i = -1;
				break;
			}
			for (int j = 0; j < i; j++) {
				if (nodeList[j].data == nodeList[i].data) {
					cout << "顶点重复,请重新输入整段顶点序列：";
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

//创建边
template <class NameType,class DistType>
void Graph<NameType, DistType>::createEdge() {
	while (1) {
		//输入及错误处理
		NameType begin, end;
		int weight;
		cout << "请输入两个顶点及边：";
		cin >> begin >> end >> weight;
		//输入类型错误
		if (cin.fail()) {
			cout << "输入错误请重新输入" << endl;
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
			continue;
		}
		//终止条件
		if (begin == "-1" && end == "-1" && weight == -1)
			break;
		//输入边权为负数
		if (weight < 0) {
			cout << "边不能为负数，请重新输入" << endl;;
			continue;
		}
		//输入顶点不存在
		int flag1 = findVertex(begin);
		int flag2 = findVertex(end);
		if (flag1 == -1 || flag2 == -1) {
			cout << "顶点不存在，请重新输入" << endl;;
			continue;
		}
		if (flag1 == flag2) {
			cout << "不能存在环，请重新输入" << endl;
			continue;
		}

		//创建边
		edgeNumber += 1;
		Edge<NameType, DistType>* newEdge = new Edge<NameType, DistType>;
		newEdge->dest = flag2;
		newEdge->cost = weight;
		newEdge->link = nodeList[flag1].adj;
		nodeList[flag1].adj = newEdge;

		//清空缓冲区
		char t;
		while ((t = cin.get()) != '\n');
	}
}

//打印图
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

//更新lowcost与nearvex数组
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

//构建最小生成树Kruskal
template <class NameType,class DistType>
void Graph<NameType, DistType>::kruskal(Graph<NameType, DistType>*& result, bool& state) {
	//最小生成树边结构体
	struct MSTEdge {
		int value = 0;
		Vertex<NameType, DistType> head;
		Edge<NameType, DistType>* tail=new Edge<NameType, DistType>;
	};
	//最小堆与并查集初始化
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
	//Kruskal算法实现
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
			cout << "非连通图不存在最小生成树！" << endl;
			state = false;
			return;
		}
	}
	cout << "生成Kruskal最小生成树！" << endl;
	state = true;
}

//构建最小生成树Prim
template <class NameType, class DistType>
void Graph<NameType, DistType>::prim(Graph<NameType, DistType>*& result, bool& state) {
	NameType start;
	int temp = 0;
	int dest = 0;
	//输入起始顶点
	cout << "请输入起始顶点：";
	while (1) {
		cin >> start;
		if (cin.fail()) {
			cout << "输入错误请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
			continue;
		}
		else if ((temp = findVertex(start)) == -1) {
			cout << "该节点不存在，请重新输入：";
			continue;
		}
		else
			break;
	}
	//初始化lowcost数组与nearvex数组
	DistType* lowcost = new DistType[vertexNumber];
	int* nearvex = new int[vertexNumber];
	for (int i = 0; i < vertexNumber; i++) {
		lowcost[i] = 214783647;
		nearvex[i] = 0;
	}
	//prim算法实现
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
			cout << "非连通图不存在最小生成树！" << endl;
			state = false;
			return;
		}
	}
	cout << "生成Prim最小生成树！" << endl;
	state = true;
}

/*最小堆模板类函数的类外实现*/

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
void minHeap<Type>::insert(const Type& x) {
	heap[size] = x;
	siftUp(size);
	size++;
}

//最小元素出堆
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

/*并查集模板类的类外实现*/

//构造函数
UFsets::UFsets(int n) {
	size = n;
	parents = new int[n];
	for (int i = 0; i < n; i++) {
		parents[i] = -1;
	}
}

//析构函数
UFsets::~UFsets() {
	delete parents;
}

//比较操作
bool UFsets::compare(int x, int y) {
	return (find(x) == find(y));
}

//搜索操作
int UFsets::find(int x) {
	while (parents[x] != -1) {
		x = parents[x];
	}
	return x;
}

//合并操作
void UFsets::combine(int root1, int root2) {
	parents[find(root2)] = root1;
}

/*电网造价模拟系统类函数类外实现*/

//构造函数
template <class NameType,class DistType>
PowerCost<NameType, DistType>::PowerCost() {
	cout << "**           电网造价模拟系统           **" << endl;
	cout << "==========================================" << endl;
	cout << "**          请选择要执行的操作:         **" << endl;
	cout << "**          A --- 创建电网顶点          **" << endl;
	cout << "**          B --- 添加电网的边          **" << endl;
	cout << "**          C --- 构造最小生成树        **" << endl;
	cout << "**          D --- 显示最小生成树        **" << endl;
	cout << "**          E --- 退出程序              **" << endl;
	cout << "==========================================" << endl;
	power= new Graph<NameType, DistType>;
}

//操作主体
template <class NameType, class DistType>
void PowerCost<NameType, DistType>::operation() {
	Graph<string, int>* result = new Graph<NameType, DistType>;
	bool state = 0;
	while (1) {
		cout << "==========================================" << endl;
		char type;
		cout << "请选择要执行的操作：";
		cin >> type;
		char t;
		while ((t = cin.get()) != '\n');
		if (type == 'A' || type == 'a')
			power->createVertex();
		else if (type == 'B' || type == 'b')
			power->createEdge();
		else if (type == 'C' || type == 'c') {
			int type = 1;
			cout << "请选择构造最小生成树的方法（1:kruskal 2:prim）:";
			while (1) {
				cin >> type;
				if (cin.fail() || type < 1 || type>2) {
					cout << "输入错误请重新输入：";
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
				cout << "最小生成树的顶点及边为：" << endl;
				result->printGraph();
			}
			else
				cout << "非连通图不存在最小生成树！" << endl;
		}
		else if (type == 'E' || type == 'e')
			exit(0);
		else {
			cout << "输入错误，请重新输入" << endl;
		}
	}
}

int main()
{
	PowerCost<string, int> power;
	power.operation();
	return 0;
}