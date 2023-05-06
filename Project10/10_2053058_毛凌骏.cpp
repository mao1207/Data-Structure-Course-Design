#include <iostream>
#include <random>
using namespace std;

template <class Type> class Element;
template <class Type> class ElementList;
template <class Type> void bubbleSort(ElementList<Type>& list, long long& KCN);
template <class Type> void selectSort(ElementList<Type>& list, long long& KCN);
template <class Type> void quickSort(ElementList<Type>& list, long long& KCN);
template <class Type> void quickSortR(ElementList<Type>& list, int left, int right, long long& KCN);
template <class Type> int partition(ElementList<Type>& list, int left, int right, long long& KCN);
template <class Type> void insertSort(ElementList<Type>& list, long long& KCN);
template <class Type> void shellSort(ElementList<Type>& list, long long& KCN);
template <class Type> void heapSort(ElementList<Type>& list, long long& KCN);
template <class Type> void siftDown(ElementList<Type>& list, int start, int end, long long& KCN);
template <class Type> void mergeSort(ElementList<Type>& list, long long& KCN);
template <class Type> void mergeSortR(ElementList<Type>& list, int left, int right, long long& KCN);
template <class Type> void merge(ElementList<Type>& list, ElementList<Type>& listTemp, int left, int right, long long& KCN);
template <class Type> void redixSort(ElementList<Type>& list, long long& KCN);

//数据表节点类
template <class Type>
class Element {
private:
	Type key;									//数据域	
	int link = -1;								//指针域
public:
	Element():key(0){}							//无参构造函数
	Element(Type x) :key(0) { key = x; }		//带一个参的构造函数
	Type getKey() { return key; }				//读取数据域
	void setKey(const Type x) { key = x; }		//修改数据域
	int getLink() { return link; }				//读取指针域
	void setLink(const int x) { link = x; }		//修改指针域

	//运算符重载
	void operator=(const Element<Type>& x) { key = x.key; }
	bool operator==(const Element<Type>& x) { return key == x.key; }
	bool operator<(const Element<Type>& x) { return key < x.key; }
	bool operator>(const Element<Type>& x) { return key > x.key; }
	bool operator<=(const Element<Type>& x) { return key <= x.key; }
	bool operator>=(const Element<Type>& x) { return key >= x.key; }
};

//数据表类
template <class Type>
class ElementList {
private:
	Element<Type>* list;					//数据域
	int length;								//链表长度
public:
	ElementList();							//构造函数
	ElementList(ElementList &x);			//拷贝构造函数
	void printList(Element<Type>* list);	//打印链表

	//友元函数声明
	friend void bubbleSort<Type>(ElementList<Type>& list, long long& KCN);
	friend void selectSort<Type>(ElementList<Type>& list, long long& KCN);
	friend void quickSort<Type>(ElementList<Type>& list, long long& KCN);
	friend void quickSortR<Type>(ElementList<Type>& list, int left, int right, long long& KCN);
	friend int partition<Type>(ElementList<Type>& list, int left, int right, long long& KCN);
	friend void insertSort<Type>(ElementList<Type>& list, long long& KCN);
	friend void shellSort<Type>(ElementList<Type>& list, long long& KCN);
	friend void heapSort<Type>(ElementList<Type>& list, long long& KCN);
	friend void siftDown<Type>(ElementList<Type>& list, int start, int end, long long& KCN);
	friend void mergeSort<Type>(ElementList<Type>& list, long long& KCN);
	friend void mergeSortR<Type>(ElementList<Type>& list, int left, int right, long long& KCN);
	friend void merge<Type>(ElementList<Type>& list, ElementList<Type>& listTemp, int left, int right, long long& KCN);
	friend void redixSort<Type>(ElementList<Type>& list, long long& KCN);
};

/*数据表类成员函数的类外实现*/

//构造函数
template <class Type>
ElementList<Type>::ElementList() {
	int sum;
	cout << "请输入要产生的随机数的个数：";
	while (1) {
		cin >> sum;
		if (cin.fail()) {
			cout << "输入错误,请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (sum < 0 || sum>2147483647) {
			cout << "数值应当在0-2147483647范围内,请重新输入：";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}
	length = sum;
	list = static_cast<Element<Type>*>(::operator new(sizeof(Element<Type>) * sum));
	for (int i = 0; i < sum; i++) {
		new(&list[i]) Type(rand());
	}
}

//拷贝构造函数
template <class Type>
ElementList<Type>::ElementList(ElementList<Type> &x) {
	length = x.length;
	list = static_cast<Element<Type>*>(::operator new(sizeof(Element<Type>) * length));
	for (int i = 0; i < length; i++) {
		new(&list[i]) Type(x.list[i].getKey());
	}
}

//打印数据表
template <class Type>
void ElementList<Type>::printList(Element<Type>* list) {
	for (int i = 0; i < length; i++) {
		cout << list[i].getKey() << " ";
	}
	cout << endl;
}

/*八种排序算法实现*/

//冒泡排序
template <class Type>
void bubbleSort(ElementList<Type>& list, long long& KCN) {
	int exchange = 0;
	for (int i = 0; i < list.length; i++) {
		for (int j = list.length - 1; j > i; j--) {
			KCN++;
			if (list.list[j - 1] > list.list[j]) {
				Element<Type> temp = list.list[j];
				list.list[j] = list.list[j - 1];
				list.list[j - 1] = temp;
				exchange = 1;
			}
			if (!exchange)
				break;
		}
	}
}

//选择排序
template <class Type>
void selectSort(ElementList<Type>& list, long long& KCN) {
	for (int i = 0; i < list.length; i++) {
		for (int j = i + 1; j < list.length; j++) {
			KCN++;
			if (list.list[i] > list.list[j]) {
				Element<Type> temp = list.list[i];
				list.list[i] = list.list[j];
				list.list[j] = temp;
			}
		}
	}
}

//直接插入排序
template <class Type>
void insertSort(ElementList<Type>& list, long long& KCN) {
	for (int i = 0; i < list.length; i++) {
		int j = i - 1;
		Element<Type> temp = list.list[i];
		while (j >= 0 && temp < list.list[j]) {
			list.list[j + 1] = list.list[j];
			j--;
			KCN++;
		}
		list.list[j + 1] = temp;
	}
}

//希尔排序
template <class Type>
void shellSort(ElementList<Type>& list, long long& KCN) {
	int gap = list.length / 2;
	while (gap) {
		for (int i = 0; i < list.length; i++) {
			int j = i - gap;
			Element<Type> temp = list.list[i];
			while (j >= 0 && temp < list.list[j]) {
				list.list[j + gap] = list.list[j];
				j -= gap;
				KCN++;
			}
			list.list[j + gap] = temp;
		}
		gap = gap == 2 ? 1 : (int)gap / 2.2;
	}
}

//快速排序
template <class Type>
void quickSort(ElementList<Type>& list,long long& KCN) {
	quickSortR(list, 0, list.length, KCN);
}

//快速排序递归实现
template <class Type>
void quickSortR(ElementList<Type>& list, int left, int right, long long& KCN) {
	if (left < right) {
		int locate = partition(list, left, right, KCN);
		quickSortR(list, locate + 1, right, KCN);
		quickSortR(list, left, locate - 1, KCN);
	}
}

//快速排序的序列划分
template <class Type>
int partition(ElementList<Type>& list, int left, int right, long long& KCN) {
	int pivotpos = left;
	for (int i = pivotpos + 1; i < right; i++) {
		KCN++;
		if (list.list[i] < list.list[left]) {
			pivotpos++;
			Element<Type> temp = list.list[i];
			list.list[i] = list.list[pivotpos];
			list.list[pivotpos] = temp;
		}
	}
	Element<Type> temp = list.list[left];
	list.list[left] = list.list[pivotpos];
	list.list[pivotpos] = temp;
	return pivotpos;
}

//堆排序
template <class Type>
void heapSort(ElementList<Type>& list, long long& KCN) {
	for (int i = (list.length - 2) / 2; i >= 0; i--) {
		siftDown(list, i, list.length - 1, KCN);
	}
	for (int i = list.length - 1; i >= 0; i--) {
		Element<Type> temp = list.list[0];
		list.list[0] = list.list[i];
		list.list[i] = temp;
		siftDown(list, 0, i - 1, KCN);
	}
}

//堆的自上而下调整算法
template <class Type>
void siftDown(ElementList<Type>& list, int start, int end, long long& KCN) {
	int i = start, j = 2 * i + 1;
	Element<Type> temp = list.list[i];
	while (j <= end) {
		if (j < end && list.list[j + 1] > list.list[j])
			j++;
		if (temp > list.list[j])
			break;
		else {
			list.list[i] = list.list[j];
			KCN++;
			i = j;
			j = 2 * i + 1;
		}
	}
	list.list[i] = temp;
}

//归并排序
template <class Type>
void mergeSort(ElementList<Type>& list, long long& KCN) {
	mergeSortR(list, 0, list.length - 1, KCN);
}

//归并排序递归实现
template <class Type>
void mergeSortR(ElementList<Type>& list, int left, int right, long long& KCN) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergeSortR(list, left, mid, KCN);
		mergeSortR(list, mid + 1, right, KCN);
		ElementList<Type> listTemp(list);
		merge(list, listTemp, left, right, KCN);
	}
}

//二路归并
template <class Type>
void merge(ElementList<Type>& list, ElementList<Type>& listTemp, int left, int right, long long& KCN) {
	int mid = (left + right) / 2;
	int s1 = left, s2 = mid + 1, t = left;
	while (s1 <= mid && s2 <= right) {
		if (listTemp.list[s1] <= listTemp.list[s2])
			list.list[t++] = listTemp.list[s1++];
		else
			list.list[t++] = listTemp.list[s2++];
		KCN++;
	}
	while (s1 <= mid) {
		list.list[t++] = listTemp.list[s1++];
	}
	while (s2 <= right)
		list.list[t++] = listTemp.list[s2++];
}

//获取数值
int getDigit(int number, int d) {
	return (number / (int)pow(10, d)) % 10;
}

//基数排序
template <class Type>
void redixSort(ElementList<Type>& list, long long& KCN) {
	int front[10], rear[10], begin = 0, start = 0;
	for (int i = 0; i < list.length - 1; i++) {
		list.list[i].setLink(i + 1);
	}
	for (int i = 0; i < 10; i++) {
		int j = start;
		for (int i = 0; i < 10; i++) {
			front[i] = rear[i] = -1;
		}
		for (int k = 0; k < list.length; k++) {
			int digit = getDigit(list.list[j].getKey(), i);
			if (front[digit] == -1) {
				front[digit] = rear[digit] = j;
			}
			else {
				list.list[rear[digit]].setLink(j);
				rear[digit] = j;
			}
			j = list.list[j].getLink();
		}
		int before = 0, after = 0;
		begin = 0;
		while (before < 10) {
			if (front[before] != -1) {
				after = before + 1;
				while (front[after] == -1) {
					after++;
				}
				list.list[rear[before]].setLink(front[after]);
				before = after;
			}
			else if (after == 0) {
				before++;
				begin++;
			}
		}
		start = front[begin];
	}
}


int main()
{
	srand((unsigned int)(time(0)));

	cout << "**              排序算法比较                      **" << endl;
	cout << "====================================================" << endl;
	cout << "**              1 --- 冒泡排序                    **" << endl;
	cout << "**              2 --- 选择排序                    **" << endl;
	cout << "**              3 --- 直接插入排序                **" << endl;
	cout << "**              4 --- 希尔排序                    **" << endl;
	cout << "**              5 --- 快速排序                    **" << endl;
	cout << "**              6 --- 堆排序                      **" << endl;
	cout << "**              7 --- 归并排序                    **" << endl;
	cout << "**              8 --- 基数排序                    **" << endl;
	cout << "**              9 --- 退出程序                    **" << endl;
	cout << "====================================================" << endl;
	cout << endl;

	ElementList<int> x;
	int mode;
	while (1) {
		ElementList<int> copy(x);
		long long int result = 0;
		cout << endl;
		cout << "请选择排序算法：";
		while (1) {
			cin >> mode;
			if (cin.fail() || mode < 1 || mode > 9) {
				cout << "输入错误请重新输入：";
				cin.clear();
				char t;
				while ((t = cin.get()) != '\n');
			}
			else
				break;
		}
		clock_t start = clock(), end;
		double sortTime;
		switch (mode) {
		case 1:
			bubbleSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "冒泡排序所用时间：" << sortTime << "s" << endl;
			cout << "冒泡排序交换次数：" << result << endl;
			break;
		case 2:
			selectSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "选择排序所用时间：" << sortTime << "s" << endl;
			cout << "选择排序交换次数：" << result << endl;
			break;
		case 3:
			insertSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "直接插入排序所用时间：" << sortTime << "s" << endl;
			cout << "直接插入排序交换次数：" << result << endl;
			break;
		case 4:
			shellSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "希尔排序所用时间：" << sortTime << "s" << endl;
			cout << "希尔排序交换次数：" << result << endl;
			break;
		case 5:
			quickSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "快速排序所用时间：" << sortTime << "s" << endl;
			cout << "快速排序交换次数：" << result << endl;
			break;
		case 6:
			heapSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "堆排序所用时间：" << sortTime << "s" << endl;
			cout << "堆排序交换次数：" << result << endl;
			break;
		case 7:
			mergeSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "归并排序所用时间：" << sortTime << "s" << endl;
			cout << "归并排序交换次数：" << result << endl;
			break;
		case 8:
			redixSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "基数排序所用时间：" << sortTime << "s" << endl;
			cout << "基数排序交换次数：" << result << endl;
			break;
		case 9:
			exit(0);
			break;
		default:
			break;
		}
	}
	return 0;
}