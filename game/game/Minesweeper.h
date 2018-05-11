#include<fstream>
using std::ifstream;
class Minesweeper                           //扫雷游戏的类
{

private:
	int** map;                             //用二维矩阵存图
	int gridNumOfX;                        //行数
	int gridNumOfY;                        //列数
	int bombNum;                           //炸弹数
	int markNum;                           //标记数
	int derection[3] = { 0,1,-1 };         //用于处理临近点
	bool gameON;                           //游戏正在进行的标志
	bool Win_or_Lose;                      //赢输的标志，赢为1，输为0

public:
	Minesweeper() {};                      //三个构造函数
	Minesweeper(int X, int Y, int bombs) ;
	Minesweeper(ifstream& in);
	~Minesweeper();                        //析构函数
	int calculate(int x, int y);           //计算点（x,y）的周围有多少个炸弹
	void setMap(int x, int y);             //计算图上各点的值
	void print(bool gameON);               //打印函数
	bool win();                            //判断是否打开了除了诈弹之外所有格子的函数，只是胜利的一个条件
	void marked(int x, int y);             //用于标记某点是否为炸弹的函数
	void revealed(int x, int y);           //打开某一个格子的函数
	bool getGameON() { return gameON; }    //获取游戏是否还在进行的状态
	void saveGame();                       //保存游戏
	void playing();                        //玩游戏
};

