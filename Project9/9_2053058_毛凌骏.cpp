#include <iostream>
using namespace std;

template <class NameType, class DistType> class Graph;

//边的模板类
template <class NameType, class DistType>
class Edge {
protected:
	int dest;													//边的终点
	DistType cost;												//边的权重
	Edge<NameType, DistType>* link;								//指向下一条边的指针
public:
	Edge() :dest(0), cost(0), link(NULL) {};					//无参构造函数
	Edge(int D, DistType C) :dest(D), cost(C), link(NULL) {}	//带两个参的构造函数
	friend Graph<NameType, DistType>;
};

//顶点的模板类
template <class NameType, class DistType>
class Vertex {
protected:
	NameType data;												//顶点名称
	Edge <NameType, DistType>* adj;								//指向与该边相邻第一条边的指针
public:
	Vertex() :data(0), adj(NULL) {};							//构造函数
	friend Graph<NameType, DistType>;
};

//图的模板类
template <class NameType, class DistType>
class Graph {
protected:
	Vertex<NameType, DistType>* nodeList;						//顶点表
	int vertexNumber;											//顶点数量
	int edgeNumber;												//边数量
	int* count;													//顶点度数数组
	int* topo;													//拓扑排序数组
public:
	Graph();													//构造函数
	~Graph();													//析构函数
	int findVertex(NameType v);									//查找顶点在vertexList中的位置
	bool TopologicalSort();										//对顶点拓扑排序
	void criticalPath();										//查找关键活动
	void printPath(DistType* ve, DistType* vl);					//打印关键活动
	void printLength(DistType* ve, DistType* vl);				//打印关键路径长度
	void printGraph();											//打印图
};

/*图的模板类函数类外实现*/

//构造函数
template <class NameType, class DistType>
Graph<NameType, DistType>::Graph() {
	//输入顶点
	while (1) {
		cin >> vertexNumber >> edgeNumber;
		if (cin.fail()) {
			cout << "输入错误请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (vertexNumber < 0)
			cout << "任务交界点数量不能为负，请重新输入：";
		else if (edgeNumber < 0)
			cout << "任务数量不能为负，请重新输入：";
		else
			break;
	}
	nodeList = new Vertex<NameType, DistType>[vertexNumber];
	count = new int[vertexNumber];
	topo = new int[vertexNumber];
	for (int i = 0; i < vertexNumber; i++) {
		nodeList[i].data = i + 1;
		count[i] = 0;
		topo[i] = -1;
	}
	//输入边
	for (int i = 0; i < edgeNumber; i++) {
		while (1) {
			//输入及错误处理
			NameType begin, end;
			int weight;
			cin >> begin >> end >> weight;
			//输入类型错误
			if (cin.fail()) {
				cout << "输入错误请重新输入" << endl;
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
				continue;
			}
			//输入边权为负数
			if (weight < 0) {
				cout << "任务需要的时间不能为负数，请重新输入" << endl;;
				continue;
			}
			//输入顶点不存在
			int flag1 = findVertex(begin);
			int flag2 = findVertex(end);
			if (flag1 == -1 || flag2 == -1) {
				cout << "交界点不存在，请重新输入" << endl;;
				continue;
			}
			if (flag1 == flag2) {
				cout << "不能存在环，请重新输入" << endl;
				continue;
			}

			//创建边
			Edge<NameType, DistType>* newEdge = new Edge<NameType, DistType>;
			newEdge->dest = flag2;
			newEdge->cost = weight;
			newEdge->link = nodeList[flag1].adj;
			nodeList[flag1].adj = newEdge;
			count[flag2] += 1;

			//清空缓冲区
			char t;
			while ((t = cin.get()) != '\n');
			break;
		}
	}
}

//析构函数
template <class NameType, class DistType>
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
template <class NameType, class DistType>
int Graph<NameType, DistType>::findVertex(NameType v) {
	for (int i = 0; i < vertexNumber; i++) {
		if (nodeList[i].data == v)
			return i;
	}
	return -1;
}

//对顶点拓扑排序
template <class NameType,class DistType>
bool Graph<NameType, DistType>::TopologicalSort() {
	int top = -1;
	for (int i = 0; i < vertexNumber; i++) {
		if (count[i] == 0) {
			count[i] = top;
			top = i;
		}
	}
	for (int i = 0; i < vertexNumber; i++) {
		if (top == -1) 
			return false;
		else {
			topo[i] = top;
			top = count[top];
			Edge<NameType, DistType>* p = nodeList[topo[i]].adj;
			while (p != NULL) {
				count[p->dest] -= 1;
				if (count[p->dest] == 0) {
					count[p->dest] = top;
					top = p->dest;
				}
				p = p->link;
			}
		}
	}
	return true;
}

//查找关键活动
template <class NameType,class DistType>
void Graph<NameType, DistType>::criticalPath() {
	if (!TopologicalSort()) {
		cout << 0 << endl;
		return;
	}
	DistType* ve = new DistType[vertexNumber];
	DistType* vl = new DistType[vertexNumber];
	for (int i = 0; i < vertexNumber; i++) {
		ve[i] = 0;
		vl[i] = 0;
	}
	for (int i = 0; i < vertexNumber; i++) {
		Edge<NameType, DistType>* p = nodeList[topo[i]].adj;
		while (p != NULL) {
			if (ve[topo[i]] + p->cost > ve[p->dest])
				ve[p->dest] = ve[topo[i]] + p->cost;
			p = p->link;
		}
	}
	for (int i = 0; i < vertexNumber; i++)
		vl[i] = ve[vertexNumber - 1];
	for (int i = vertexNumber - 1; i >= 0; i--) {
		Edge<NameType, DistType>* p = nodeList[topo[i]].adj;
		while (p != NULL) {
			if (vl[p->dest] - p->cost < vl[topo[i]])
				vl[topo[i]] = vl[p->dest] - p->cost;
			p = p->link;
		}
	}
	printLength(ve, vl);
	printPath(ve, vl);
}

//打印关键活动
template <class NameType,class DistType>
void Graph<NameType, DistType>::printPath(DistType* ve, DistType* vl) {
	for (int i = 0; i < vertexNumber; i++) {
		Edge<NameType, DistType>* p = nodeList[i].adj;
		while (p != NULL) {
			if (ve[i] == vl[p->dest] - p->cost)
				cout << i + 1 << "->" << p->dest + 1 << endl;
			p = p->link;
		}
	}
}

//打印关键路径长度
template <class NameType, class DistType>
void Graph<NameType, DistType>::printLength(DistType* ve, DistType* vl) {
	int result = 0;
	int temp = topo[0], end = topo[vertexNumber - 1];
	while (temp != end) {
		Edge<NameType, DistType>* p = nodeList[temp].adj;
		while (p != NULL) {
			if (ve[temp] == vl[p->dest] - p->cost) {
				result += p->cost;
				temp = p->dest;
				continue;
			}
			p = p->link;
		}
	}
	cout << result << endl;
}

//打印图
template <class NameType, class DistType>
void Graph<NameType, DistType>::printGraph() {

	for (int i = 0; i < vertexNumber; i++) {
		Edge<NameType, DistType>* p = nodeList[i].adj;
		while (p != NULL) {
			cout << nodeList[i].data << "-<" << p->cost << ">-" << nodeList[p->dest].data << "  ";
			p = p->link;
		}
	}
	cout << endl;
}

int main()
{
	Graph<int, int> task;
	task.criticalPath();
}