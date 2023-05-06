#include <iostream>
using namespace std;

template <class NameType, class DistType> class Graph;

//�ߵ�ģ����
template <class NameType, class DistType>
class Edge {
protected:
	int dest;													//�ߵ��յ�
	DistType cost;												//�ߵ�Ȩ��
	Edge<NameType, DistType>* link;								//ָ����һ���ߵ�ָ��
public:
	Edge() :dest(0), cost(0), link(NULL) {};					//�޲ι��캯��
	Edge(int D, DistType C) :dest(D), cost(C), link(NULL) {}	//�������εĹ��캯��
	friend Graph<NameType, DistType>;
};

//�����ģ����
template <class NameType, class DistType>
class Vertex {
protected:
	NameType data;												//��������
	Edge <NameType, DistType>* adj;								//ָ����ñ����ڵ�һ���ߵ�ָ��
public:
	Vertex() :data(0), adj(NULL) {};							//���캯��
	friend Graph<NameType, DistType>;
};

//ͼ��ģ����
template <class NameType, class DistType>
class Graph {
protected:
	Vertex<NameType, DistType>* nodeList;						//�����
	int vertexNumber;											//��������
	int edgeNumber;												//������
	int* count;													//�����������
	int* topo;													//������������
public:
	Graph();													//���캯��
	~Graph();													//��������
	int findVertex(NameType v);									//���Ҷ�����vertexList�е�λ��
	bool TopologicalSort();										//�Զ�����������
	void criticalPath();										//���ҹؼ��
	void printPath(DistType* ve, DistType* vl);					//��ӡ�ؼ��
	void printLength(DistType* ve, DistType* vl);				//��ӡ�ؼ�·������
	void printGraph();											//��ӡͼ
};

/*ͼ��ģ���ຯ������ʵ��*/

//���캯��
template <class NameType, class DistType>
Graph<NameType, DistType>::Graph() {
	//���붥��
	while (1) {
		cin >> vertexNumber >> edgeNumber;
		if (cin.fail()) {
			cout << "����������������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (vertexNumber < 0)
			cout << "���񽻽����������Ϊ�������������룺";
		else if (edgeNumber < 0)
			cout << "������������Ϊ�������������룺";
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
	//�����
	for (int i = 0; i < edgeNumber; i++) {
		while (1) {
			//���뼰������
			NameType begin, end;
			int weight;
			cin >> begin >> end >> weight;
			//�������ʹ���
			if (cin.fail()) {
				cout << "�����������������" << endl;
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
				continue;
			}
			//�����ȨΪ����
			if (weight < 0) {
				cout << "������Ҫ��ʱ�䲻��Ϊ����������������" << endl;;
				continue;
			}
			//���붥�㲻����
			int flag1 = findVertex(begin);
			int flag2 = findVertex(end);
			if (flag1 == -1 || flag2 == -1) {
				cout << "����㲻���ڣ�����������" << endl;;
				continue;
			}
			if (flag1 == flag2) {
				cout << "���ܴ��ڻ�������������" << endl;
				continue;
			}

			//������
			Edge<NameType, DistType>* newEdge = new Edge<NameType, DistType>;
			newEdge->dest = flag2;
			newEdge->cost = weight;
			newEdge->link = nodeList[flag1].adj;
			nodeList[flag1].adj = newEdge;
			count[flag2] += 1;

			//��ջ�����
			char t;
			while ((t = cin.get()) != '\n');
			break;
		}
	}
}

//��������
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

//���Ҷ�����vertexList�е�λ��
template <class NameType, class DistType>
int Graph<NameType, DistType>::findVertex(NameType v) {
	for (int i = 0; i < vertexNumber; i++) {
		if (nodeList[i].data == v)
			return i;
	}
	return -1;
}

//�Զ�����������
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

//���ҹؼ��
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

//��ӡ�ؼ��
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

//��ӡ�ؼ�·������
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

//��ӡͼ
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