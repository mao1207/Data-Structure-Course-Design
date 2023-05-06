#include <iostream>
#include <iomanip>
#include <random>
#include <time.h>
using namespace std;

//�ַ�����
char sign[2] = { '0','#' };

//�����ʽ������Ŀո�
int locate(int n) {
	int result = 1;
	while (n / 10 != 0) {
		n /= 10;
		result += 1;
	}
	return result;
}

//�Թ���
class maze {
protected:
	int length = 0;    //�Թ�����
	int width = 0;     //�Թ����
	int** road;        //��ʼ��ͼ
	int** result;      //�����ͼ
public:
	maze();    //���캯��
	bool BFS(int x1, int y1, int x2, int y2);    //���������������
	void printMaze();    //��ӡ�Թ���ͼ
	void printResult(int x1, int y1, int x2, int y2, int n);    //��ӡ·�����ֽ�
	void drawResult();    //��ӡ·��ͼ�ν�
};

//���캯��
maze::maze() {
	//�����Թ����Ϳ�
	cout << "�����빹���Թ��ĳ��Ϳ�" << endl;
	while (1) {
		cin >> length >> width;
		if (cin.fail() || length > 20 || width > 20) {
			if (length > 20 || width > 20)
				cout << "���Ϳ�Ӧ����0-20��Χ�ڣ�����������:";
			else
				cout << "�����������������:";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}

	//�����ʼ��ͼ�ռ�
	road = new int*[width];
	for (int i = 0; i < width; i++)
		road[i] = new int[length+1];

	//��������ͼ�ռ�
	result = new int* [width];
	for (int i = 0; i < width; i++)
		result[i] = new int[length+1];

	while (1) {
		//��ͼ��ʼ��
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < length; j++) {
				road[i][j] = rand() % 2;
				if (road[i][j] == 1)
					result[i][j] = -1;
				else
					result[i][j] = 0;
			}
		}
		result[width - 1][length - 1] = 1;

		//�������ĵ�ͼ�����ڿɴ�·����������
		if (BFS(width - 1, length - 1, 0, 0))
			break;
	}

	printMaze();
	printResult(0, 0, width - 1, length - 1, result[0][0]);
	drawResult();
}

//���������������
bool maze::BFS(int x1, int y1, int x2, int y2) {
	if (road[x1][y1] != 0 || road[x2][y2] != 0)
		return false;
	while (1) {
		int flag = 1;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < length; j++) {
				if (result[i][j] > 0) {
					int n = result[i][j];
					if (j - 1 >= 0 && result[i][j - 1] == 0) {
						result[i][j - 1] = n + 1;
						flag = 0;
					}
					if (j + 1 < length && result[i][j + 1] == 0) {
						result[i][j + 1] = n + 1;
						flag = 0;
					}
					if (i - 1 >= 0 && result[i - 1][j] == 0) {
						result[i - 1][j] = n + 1;
						flag = 0;
					}
					if (i + 1 < width && result[i + 1][j] == 0) {
						result[i + 1][j] = n + 1;
						flag = 0;
					}
				}
			}
		}
		if (flag)
			break;
	}
	if (result[x2][y2] == 0)
		return false;
	return true;
}

//��ӡ�Թ���ͼ
void maze::printMaze() {
	cout << "�Թ���ͼ��SΪ��㣬EΪ�յ㣩��" << endl;
	cout << endl;
	cout << "  ";
	for (int i = 0; i < length; i++) {
		cout << setw(5) << i << "��";
	}
	cout << endl;
	for (int i = 0; i < width; i++) {
		cout << i << "��";
		for (int j = 0; j < (4 - locate(i)); j++)
			cout << " ";
		for (int j = 0; j < length; j++) {
			if (i == 0 && j == 0)
				cout << "S" << "      ";
			else if (i == width - 1 && j == length - 1)
				cout << "E" << "      ";
			else
				cout << sign[road[i][j]] << "      ";
		}
		cout << endl;
		cout << endl;
	}
}

//��ӡ·�����ֽ�
void maze::printResult(int x1, int y1, int x2, int y2, int n) {
	if (n == result[0][0])
		cout << "���·�������ֽ⣩��" << endl << endl;
	cout << "<" << x1 << "," << y1 << ">";
	if (x1 != x2 || y1 != y2)
		cout << " ---> ";
	else
		cout << endl;
	result[x1][y1] = -2;
	if (x1 == x2 && y1 == y2) {
		return;
	}
	if (y1 - 1 >= 0 && result[x1][y1 - 1] == n - 1) {
		result[x1][y1 - 1] = n + 1;
		printResult(x1, y1 - 1, x2, y2, n - 1);
	}
	else if (x1 - 1 >= 0 && result[x1 - 1][y1] == n - 1) {
		result[x1 - 1][y1] = n + 1;
		printResult(x1 - 1, y1, x2, y2, n - 1);
	}
	else if (y1 + 1 < length && result[x1][y1 + 1] == n - 1) {
		result[x1][y1 + 1] = n + 1;
		printResult(x1, y1 + 1, x2, y2, n - 1);
	}
	else if (x1 + 1 < width && result[x1 + 1][y1] == n - 1) {
		result[x1 + 1][y1] = n + 1;
		printResult(x1 + 1, y1, x2, y2, n - 1);
	}
}

//��ӡ·��ͼ�ν�
void maze::drawResult() {
	cout << endl;
	cout << "���·����ͼ�ν⣩��" << endl << endl;
	cout << "  ";
	for (int i = 0; i < length; i++) {
		cout << setw(5) << i << "��";
	}
	cout << endl;
	for (int i = 0; i < width; i++) {
		cout << i << "��";
		for (int j = 0; j < (4 - locate(i)); j++)
			cout << " ";
		for (int j = 0; j < length; j++) {
			if (i == 0 && j == 0)
				cout << "S" << "      ";
			else if (i == width - 1 && j == length - 1)
				cout << "E" << "      ";
			else if (result[i][j] == -2)
				cout << "*" << "      ";
			else
				cout << sign[road[i][j]] << "      ";
		}
		cout << endl;
		cout << endl;
	}
}

int main()
{
	srand((int)time(NULL));
	maze();
	return 0;
}