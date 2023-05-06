#include <iostream>
#include <iomanip>
#include <random>
#include <time.h>
using namespace std;

//字符数组
char sign[2] = { '0','#' };

//计算格式化所需的空格
int locate(int n) {
	int result = 1;
	while (n / 10 != 0) {
		n /= 10;
		result += 1;
	}
	return result;
}

//迷宫类
class maze {
protected:
	int length = 0;    //迷宫长度
	int width = 0;     //迷宫宽度
	int** road;        //初始地图
	int** result;      //结果地图
public:
	maze();    //构造函数
	bool BFS(int x1, int y1, int x2, int y2);    //广度优先搜索函数
	void printMaze();    //打印迷宫地图
	void printResult(int x1, int y1, int x2, int y2, int n);    //打印路径文字解
	void drawResult();    //打印路径图形解
};

//构造函数
maze::maze() {
	//输入迷宫长和宽
	cout << "请输入构建迷宫的长和宽：" << endl;
	while (1) {
		cin >> length >> width;
		if (cin.fail() || length > 20 || width > 20) {
			if (length > 20 || width > 20)
				cout << "长和宽应该在0-20范围内，请重新输入:";
			else
				cout << "输入错误，请重新输入:";
			cin.clear();
			char t;
			while ((t = cin.get()) != '\n');
		}
		else
			break;
	}

	//分配初始地图空间
	road = new int*[width];
	for (int i = 0; i < width; i++)
		road[i] = new int[length+1];

	//分配结果地图空间
	result = new int* [width];
	for (int i = 0; i < width; i++)
		result[i] = new int[length+1];

	while (1) {
		//地图初始化
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

		//若创建的地图不存在可达路径，则重置
		if (BFS(width - 1, length - 1, 0, 0))
			break;
	}

	printMaze();
	printResult(0, 0, width - 1, length - 1, result[0][0]);
	drawResult();
}

//广度优先搜索函数
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

//打印迷宫地图
void maze::printMaze() {
	cout << "迷宫地图（S为起点，E为终点）：" << endl;
	cout << endl;
	cout << "  ";
	for (int i = 0; i < length; i++) {
		cout << setw(5) << i << "列";
	}
	cout << endl;
	for (int i = 0; i < width; i++) {
		cout << i << "行";
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

//打印路径文字解
void maze::printResult(int x1, int y1, int x2, int y2, int n) {
	if (n == result[0][0])
		cout << "最短路径（文字解）：" << endl << endl;
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

//打印路径图形解
void maze::drawResult() {
	cout << endl;
	cout << "最短路径（图形解）：" << endl << endl;
	cout << "  ";
	for (int i = 0; i < length; i++) {
		cout << setw(5) << i << "列";
	}
	cout << endl;
	for (int i = 0; i < width; i++) {
		cout << i << "行";
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