#include"Minesweeper.h"                                                             //类声明头文件
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<conio.h>
#include <fstream>
using namespace std;

//以下是状态位
#define BOMB 9                                                                     //BOMB表示该位置有炸弹
#define MARKED -2                                                                  //MARKED表示该位置被标记
#define UNOPEN -1                                                                  //表示该位置没被打开
#define WIN 1                                                                      //赢
#define ON 2                                                                       //游戏正在进行
#define LOSE 0                                                                     //输

Minesweeper::Minesweeper(int X, int Y, int bombs)                                  //构造函数
{
	gridNumOfX = X;                                                                //赋值
	gridNumOfY = Y;
	bombNum = bombs;
	markNum = 0;
	gameON = true;
	Win_or_Lose = false;

	map = new int *[gridNumOfX+2];                                                  //申请空间，为了避免边界值特殊处理，在矩阵的边界扩大了一圈
	for (int i = 0;i < gridNumOfX+2;i++)
	{
		map[i] = new int[gridNumOfY+2];
	}

	for (int i = 0;i < gridNumOfX + 2;i++)                                           //给矩阵内各点赋初值
		for (int j = 0;j < gridNumOfY + 2;j++)
			map[i][j] = UNOPEN;

	srand(time(0));                                                                   //生成随机数的种子
	for (int i = 0;i < bombNum;)                                                      //随机分布炸弹位置
	{
		int x = rand() % gridNumOfX + 1;
		int y = rand() % gridNumOfY + 1;
		if (map[x][y] != BOMB)                                                         //该位置没炸弹的话就给炸弹
		{
			map[x][y] = BOMB;
			i++;
		}
	}
}

Minesweeper::Minesweeper(ifstream& in)                                                     //构造函数
{
	in >> gridNumOfX >> gridNumOfY >> bombNum >> markNum >> gameON >> Win_or_Lose;         //从文件中读

	map = new int *[gridNumOfX + 2];                                                        //申请空间，为了避免边界值特殊处理，在矩阵的边界扩大了一圈
	for (int i = 0;i < gridNumOfX + 2;i++)
	{
		map[i] = new int[gridNumOfY + 2];
	}

	for (int j = 0;j < gridNumOfY + 2;j++)                                                   //给矩阵额外增加的边界赋初值
	{
		map[0][j] = UNOPEN;
		map[gridNumOfX + 1][j] = UNOPEN;
	}
	for (int i = 0;i < gridNumOfX + 2;i++)
	{
		map[i][0] = UNOPEN;
		map[i][gridNumOfY + 1] = UNOPEN;
	}

	for (int i = 1;i <= gridNumOfX;i++)                                                      //从文件中读矩阵
		for (int j = 1;j <= gridNumOfY;j++)
			in >> map[i][j];
	in.close();
}


Minesweeper::~Minesweeper()
{
	for (int i = 0;i < gridNumOfX+2;i++)                                                
		delete[] map[i];
	delete map;
}

int Minesweeper::calculate(int x, int y)                                        //计算一个点周围有多少个炸弹
{
	int count = 0;
	for (int i = 0;i < 3;i++)                                                  //两个循环可以走遍一个点周围的8个点
		for (int j = 0;j < 3;j++)
			if (!(derection[i] == 0 && derection[j] == 0))
				if (map[x + derection[i]][y + derection[j]] == BOMB|| map[x + derection[i]][y + derection[j]] == MARKED)  //被标记的也是炸弹
					count++;
	return count;
}

void Minesweeper::setMap(int x, int y)                        //计算矩阵内各点的值
{
	int num = calculate(x, y); 
	if (num == 0)                                             //如果该店周围8各点没有炸弹，那么对该8各点分别递归本函数
	{
		map[x][y] = 0;
		for (int i = 0;i < 3;i++)                              //两个循环可以走遍一个点周围的8个点
		{
			for (int j = 0;j < 3;j++)
			{
				if (!(derection[i] == 0 && derection[j] == 0))  //除了自己以外的其他8各点才递归
				{
					int neighborX = x + derection[i];           //邻接点
					int neighborY = y + derection[j];
					if (neighborX <= gridNumOfX && neighborY <= gridNumOfY && neighborX >= 1 && neighborY >= 1)
						if (map[neighborX][neighborY] == UNOPEN)
							setMap(neighborX, neighborY);        //递归相邻的点
				}
			}
		}
	}
	else
		map[x][y] = num;                                         //如果周围有炸弹，直接是炸弹数
}

void Minesweeper::print(bool gameON)                             //打印函数
{
	system("cls");
	cout << "\t\tMinesweeper\t\t\t\n\n\n" << endl;               //下面几行是打印样式的控制，不用仔细看
	cout << "\tYou have " << bombNum - markNum << " bombs still to find\n\n" << endl;
	cout << "   ";
	for (int i = 1;i <= gridNumOfY;i++)
		if(i<10) cout << "  " << i << " ";
		else cout << "  " << i << "";
	cout << endl;
	cout << "   ";
	for (int i = 1;i <= gridNumOfY;i++)
		cout << "  " << '-' << " ";
	cout << endl;

	if (gameON == 0)                                                           //如果游戏已经结束，则会打印出炸弹的所有位置
	{
		for (int i = 1;i <= gridNumOfX;i++)
		{
			if(i<10) cout << i << "  |";
			else cout << i << " |";
			for (int j = 1;j <= gridNumOfY;j++)
			{	
				if (map[i][j] == BOMB||map[i][j]==MARKED)
					cout << " B |";
				else if (map[i][j] == UNOPEN || map[i][j] == BOMB)
					cout << "   |";
				else
					cout << " " << map[i][j] << " |";
			}
			cout << endl;
			cout << "   ";
			for (int i = 1;i <= gridNumOfY;i++)
				cout << "  " << '-' << " ";
			cout << endl;
		}
		if (Win_or_Lose)
			cout << "You Win!" << endl;
		else
			cout << "YOU LOSE!\nYou have revealed a bomb" << endl;
	}
	else                                                                  //如果游戏还没结束，则根据矩阵的状态更新打印
	{
		for (int i = 1;i <= gridNumOfX;i++)
		{
			if (i<10) cout << i << "  |";
			else cout << i << " |";
			for (int j = 1;j <= gridNumOfY;j++)
			{
				if (map[i][j] == MARKED)
					cout << " x |";
				else if (map[i][j] == UNOPEN || map[i][j] == BOMB)
					cout << "   |";
				else
					cout << " " << map[i][j] << " |";
			}
			cout << endl;
			cout << "   ";
			for (int i = 1;i <= gridNumOfY;i++)
				cout << "  " << '-' << " ";
			cout << endl;
		}
		
	}
}

bool Minesweeper::win()                               //判断是否打开了除了诈弹之外所有格子的函数，只是胜利的一个条件
{
	int unOpenNum = 0;                                //用于记录除了炸弹之外其他的未打开的格子的数量
	for (int i = 1;i <= gridNumOfX;i++)               //统计矩阵上除了炸弹之外其他的未打开的格子的数量
		for (int j = 1;j <= gridNumOfY;j++)
			if (map[i][j] == UNOPEN)
				unOpenNum++;

	if (unOpenNum == 0)                               //如果除了炸弹之外其他的未打开的格子的数量为零，说明排雷成功
		return true;
	else
		return false;
}

void Minesweeper::marked(int x, int y)                //标记函数，只有该格子中有炸弹才会成功标记，否则不能标记
{
	if (map[x][y] == BOMB)                            //该点事炸弹，可以标记
	{
		map[x][y] = MARKED;                           //从炸弹状态切换到标记状态
		markNum++;                                    //标记数加一
		print(ON);                                    //游戏正在进行，打印
		if (markNum == bombNum)                       //如果正确标记的数量等于炸弹数，则排雷成功
		{
			cout << "You Win\nYou have mark all of the bombs!" << endl;
			gameON = false;                            //该游戏已结束的状态位
			Win_or_Lose = true;                        //该游戏赢了的状态
			cout << "Input any key to return menu" << endl;
			getch();                                    //用于保住屏幕输出
		}
		else
			gameON = true;                              //游戏继续进行
	}
	else                                                //该点不是炸弹，不能标记
	{
		cout << "(" << x << "," << y << ")" << "Can't mark : there isn't a bomb!" << endl;
		gameON = true;
	}
}

void Minesweeper::revealed(int x, int y)                 //打开格子的函数
{
	if (map[x][y] == BOMB || map[x][y] == MARKED)        //所打开的格子是一个炸弹或者该格子已标记有炸弹
	{
		print(LOSE);                                     //游戏结束打印
		gameON = false;                                  //游戏结束标志
		cout << "Input any key to return menu"<<endl;     
		getch();
	}
	else                                                  //打开格子中没有炸弹
	{
		setMap(x, y);                                     //设置该点及周围其他点的值
		print(ON);

		if (win())                                        //如果出了炸弹以外的所有格子已经被打开，则排雷成功
		{
			cout << "You Win\nYou have revealed all of the grid beside the bombs!" << endl;
			gameON=false;          
			Win_or_Lose = true;
			cout << "Input any key to return menu" << endl;
			getch();
		}
		else
			gameON = true;
	}
}



void Minesweeper::saveGame()                          //保存游戏到文件 gameDate.txt
{
	ofstream of("gameDate.txt");
	if (of.is_open())
	{
		of << gridNumOfX <<"\t"<< gridNumOfY << "\t" << bombNum << "\t" << markNum << "\t" << gameON << "\t" << Win_or_Lose<<endl;
		for (int i = 1;i <= gridNumOfX;i++)
		{
			for (int j = 1;j <= gridNumOfY;j++)
				of << map[i][j] << "\t";
			of << "\n";
		}
		of.close();
	}
	
}

void Minesweeper::playing()                                 //正在玩游戏
{
	while (gameON)                                          //游戏状态是真时才循环
	{
		int select,x,y;
		cout << "1. Revealed a grid.\t\t2. Mark a grid" << endl;     //1.打开格子    2.标记格子
		cout << "3. save the game.\t\t4. return to menu\n" << endl;  //3.保存游戏    4.返回到主菜单
		cout << "Please inpit [1/2/3/4] : ";
		cin >> select;
		if (select < 3)
		{
			cout << "Please input the row and column of the grid:" << endl;   //输入行，列
			cin >> x >> y;
			if (select == 1)
				revealed(x, y);
			else
				marked(x, y);
		}
		else if (select == 3)
		{
			saveGame();                                                      //保存游戏
			print(ON);
			cout << "The game have saved!\n" << endl;
		}			
		else
		{
			break;                                                           //从正在游戏的循环中出去
		}
		
	}
}