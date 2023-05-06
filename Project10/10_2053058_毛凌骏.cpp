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

//���ݱ�ڵ���
template <class Type>
class Element {
private:
	Type key;									//������	
	int link = -1;								//ָ����
public:
	Element():key(0){}							//�޲ι��캯��
	Element(Type x) :key(0) { key = x; }		//��һ���εĹ��캯��
	Type getKey() { return key; }				//��ȡ������
	void setKey(const Type x) { key = x; }		//�޸�������
	int getLink() { return link; }				//��ȡָ����
	void setLink(const int x) { link = x; }		//�޸�ָ����

	//���������
	void operator=(const Element<Type>& x) { key = x.key; }
	bool operator==(const Element<Type>& x) { return key == x.key; }
	bool operator<(const Element<Type>& x) { return key < x.key; }
	bool operator>(const Element<Type>& x) { return key > x.key; }
	bool operator<=(const Element<Type>& x) { return key <= x.key; }
	bool operator>=(const Element<Type>& x) { return key >= x.key; }
};

//���ݱ���
template <class Type>
class ElementList {
private:
	Element<Type>* list;					//������
	int length;								//������
public:
	ElementList();							//���캯��
	ElementList(ElementList &x);			//�������캯��
	void printList(Element<Type>* list);	//��ӡ����

	//��Ԫ��������
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

/*���ݱ����Ա����������ʵ��*/

//���캯��
template <class Type>
ElementList<Type>::ElementList() {
	int sum;
	cout << "������Ҫ������������ĸ�����";
	while (1) {
		cin >> sum;
		if (cin.fail()) {
			cout << "�������,���������룺";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else if (sum < 0 || sum>2147483647) {
			cout << "��ֵӦ����0-2147483647��Χ��,���������룺";
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

//�������캯��
template <class Type>
ElementList<Type>::ElementList(ElementList<Type> &x) {
	length = x.length;
	list = static_cast<Element<Type>*>(::operator new(sizeof(Element<Type>) * length));
	for (int i = 0; i < length; i++) {
		new(&list[i]) Type(x.list[i].getKey());
	}
}

//��ӡ���ݱ�
template <class Type>
void ElementList<Type>::printList(Element<Type>* list) {
	for (int i = 0; i < length; i++) {
		cout << list[i].getKey() << " ";
	}
	cout << endl;
}

/*���������㷨ʵ��*/

//ð������
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

//ѡ������
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

//ֱ�Ӳ�������
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

//ϣ������
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

//��������
template <class Type>
void quickSort(ElementList<Type>& list,long long& KCN) {
	quickSortR(list, 0, list.length, KCN);
}

//��������ݹ�ʵ��
template <class Type>
void quickSortR(ElementList<Type>& list, int left, int right, long long& KCN) {
	if (left < right) {
		int locate = partition(list, left, right, KCN);
		quickSortR(list, locate + 1, right, KCN);
		quickSortR(list, left, locate - 1, KCN);
	}
}

//������������л���
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

//������
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

//�ѵ����϶��µ����㷨
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

//�鲢����
template <class Type>
void mergeSort(ElementList<Type>& list, long long& KCN) {
	mergeSortR(list, 0, list.length - 1, KCN);
}

//�鲢����ݹ�ʵ��
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

//��·�鲢
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

//��ȡ��ֵ
int getDigit(int number, int d) {
	return (number / (int)pow(10, d)) % 10;
}

//��������
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

	cout << "**              �����㷨�Ƚ�                      **" << endl;
	cout << "====================================================" << endl;
	cout << "**              1 --- ð������                    **" << endl;
	cout << "**              2 --- ѡ������                    **" << endl;
	cout << "**              3 --- ֱ�Ӳ�������                **" << endl;
	cout << "**              4 --- ϣ������                    **" << endl;
	cout << "**              5 --- ��������                    **" << endl;
	cout << "**              6 --- ������                      **" << endl;
	cout << "**              7 --- �鲢����                    **" << endl;
	cout << "**              8 --- ��������                    **" << endl;
	cout << "**              9 --- �˳�����                    **" << endl;
	cout << "====================================================" << endl;
	cout << endl;

	ElementList<int> x;
	int mode;
	while (1) {
		ElementList<int> copy(x);
		long long int result = 0;
		cout << endl;
		cout << "��ѡ�������㷨��";
		while (1) {
			cin >> mode;
			if (cin.fail() || mode < 1 || mode > 9) {
				cout << "����������������룺";
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
			cout << "ð����������ʱ�䣺" << sortTime << "s" << endl;
			cout << "ð�����򽻻�������" << result << endl;
			break;
		case 2:
			selectSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "ѡ����������ʱ�䣺" << sortTime << "s" << endl;
			cout << "ѡ�����򽻻�������" << result << endl;
			break;
		case 3:
			insertSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "ֱ�Ӳ�����������ʱ�䣺" << sortTime << "s" << endl;
			cout << "ֱ�Ӳ������򽻻�������" << result << endl;
			break;
		case 4:
			shellSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "ϣ����������ʱ�䣺" << sortTime << "s" << endl;
			cout << "ϣ�����򽻻�������" << result << endl;
			break;
		case 5:
			quickSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "������������ʱ�䣺" << sortTime << "s" << endl;
			cout << "�������򽻻�������" << result << endl;
			break;
		case 6:
			heapSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "����������ʱ�䣺" << sortTime << "s" << endl;
			cout << "�����򽻻�������" << result << endl;
			break;
		case 7:
			mergeSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "�鲢��������ʱ�䣺" << sortTime << "s" << endl;
			cout << "�鲢���򽻻�������" << result << endl;
			break;
		case 8:
			redixSort(copy, result);
			end = clock();
			sortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
			cout << "������������ʱ�䣺" << sortTime << "s" << endl;
			cout << "�������򽻻�������" << result << endl;
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