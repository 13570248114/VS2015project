#include"Minesweeper.h"                                                             //������ͷ�ļ�
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<conio.h>
#include <fstream>
using namespace std;

//������״̬λ
#define BOMB 9                                                                     //BOMB��ʾ��λ����ը��
#define MARKED -2                                                                  //MARKED��ʾ��λ�ñ����
#define UNOPEN -1                                                                  //��ʾ��λ��û����
#define WIN 1                                                                      //Ӯ
#define ON 2                                                                       //��Ϸ���ڽ���
#define LOSE 0                                                                     //��

Minesweeper::Minesweeper(int X, int Y, int bombs)                                  //���캯��
{
	gridNumOfX = X;                                                                //��ֵ
	gridNumOfY = Y;
	bombNum = bombs;
	markNum = 0;
	gameON = true;
	Win_or_Lose = false;

	map = new int *[gridNumOfX+2];                                                  //����ռ䣬Ϊ�˱���߽�ֵ���⴦���ھ���ı߽�������һȦ
	for (int i = 0;i < gridNumOfX+2;i++)
	{
		map[i] = new int[gridNumOfY+2];
	}

	for (int i = 0;i < gridNumOfX + 2;i++)                                           //�������ڸ��㸳��ֵ
		for (int j = 0;j < gridNumOfY + 2;j++)
			map[i][j] = UNOPEN;

	srand(time(0));                                                                   //���������������
	for (int i = 0;i < bombNum;)                                                      //����ֲ�ը��λ��
	{
		int x = rand() % gridNumOfX + 1;
		int y = rand() % gridNumOfY + 1;
		if (map[x][y] != BOMB)                                                         //��λ��ûը���Ļ��͸�ը��
		{
			map[x][y] = BOMB;
			i++;
		}
	}
}

Minesweeper::Minesweeper(ifstream& in)                                                     //���캯��
{
	in >> gridNumOfX >> gridNumOfY >> bombNum >> markNum >> gameON >> Win_or_Lose;         //���ļ��ж�

	map = new int *[gridNumOfX + 2];                                                        //����ռ䣬Ϊ�˱���߽�ֵ���⴦���ھ���ı߽�������һȦ
	for (int i = 0;i < gridNumOfX + 2;i++)
	{
		map[i] = new int[gridNumOfY + 2];
	}

	for (int j = 0;j < gridNumOfY + 2;j++)                                                   //������������ӵı߽縳��ֵ
	{
		map[0][j] = UNOPEN;
		map[gridNumOfX + 1][j] = UNOPEN;
	}
	for (int i = 0;i < gridNumOfX + 2;i++)
	{
		map[i][0] = UNOPEN;
		map[i][gridNumOfY + 1] = UNOPEN;
	}

	for (int i = 1;i <= gridNumOfX;i++)                                                      //���ļ��ж�����
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

int Minesweeper::calculate(int x, int y)                                        //����һ������Χ�ж��ٸ�ը��
{
	int count = 0;
	for (int i = 0;i < 3;i++)                                                  //����ѭ�������߱�һ������Χ��8����
		for (int j = 0;j < 3;j++)
			if (!(derection[i] == 0 && derection[j] == 0))
				if (map[x + derection[i]][y + derection[j]] == BOMB|| map[x + derection[i]][y + derection[j]] == MARKED)  //����ǵ�Ҳ��ը��
					count++;
	return count;
}

void Minesweeper::setMap(int x, int y)                        //��������ڸ����ֵ
{
	int num = calculate(x, y); 
	if (num == 0)                                             //����õ���Χ8����û��ը������ô�Ը�8����ֱ�ݹ鱾����
	{
		map[x][y] = 0;
		for (int i = 0;i < 3;i++)                              //����ѭ�������߱�һ������Χ��8����
		{
			for (int j = 0;j < 3;j++)
			{
				if (!(derection[i] == 0 && derection[j] == 0))  //�����Լ����������8����ŵݹ�
				{
					int neighborX = x + derection[i];           //�ڽӵ�
					int neighborY = y + derection[j];
					if (neighborX <= gridNumOfX && neighborY <= gridNumOfY && neighborX >= 1 && neighborY >= 1)
						if (map[neighborX][neighborY] == UNOPEN)
							setMap(neighborX, neighborY);        //�ݹ����ڵĵ�
				}
			}
		}
	}
	else
		map[x][y] = num;                                         //�����Χ��ը����ֱ����ը����
}

void Minesweeper::print(bool gameON)                             //��ӡ����
{
	system("cls");
	cout << "\t\tMinesweeper\t\t\t\n\n\n" << endl;               //���漸���Ǵ�ӡ��ʽ�Ŀ��ƣ�������ϸ��
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

	if (gameON == 0)                                                           //�����Ϸ�Ѿ�����������ӡ��ը��������λ��
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
	else                                                                  //�����Ϸ��û����������ݾ����״̬���´�ӡ
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

bool Minesweeper::win()                               //�ж��Ƿ���˳���թ��֮�����и��ӵĺ�����ֻ��ʤ����һ������
{
	int unOpenNum = 0;                                //���ڼ�¼����ը��֮��������δ�򿪵ĸ��ӵ�����
	for (int i = 1;i <= gridNumOfX;i++)               //ͳ�ƾ����ϳ���ը��֮��������δ�򿪵ĸ��ӵ�����
		for (int j = 1;j <= gridNumOfY;j++)
			if (map[i][j] == UNOPEN)
				unOpenNum++;

	if (unOpenNum == 0)                               //�������ը��֮��������δ�򿪵ĸ��ӵ�����Ϊ�㣬˵�����׳ɹ�
		return true;
	else
		return false;
}

void Minesweeper::marked(int x, int y)                //��Ǻ�����ֻ�иø�������ը���Ż�ɹ���ǣ������ܱ��
{
	if (map[x][y] == BOMB)                            //�õ���ը�������Ա��
	{
		map[x][y] = MARKED;                           //��ը��״̬�л������״̬
		markNum++;                                    //�������һ
		print(ON);                                    //��Ϸ���ڽ��У���ӡ
		if (markNum == bombNum)                       //�����ȷ��ǵ���������ը�����������׳ɹ�
		{
			cout << "You Win\nYou have mark all of the bombs!" << endl;
			gameON = false;                            //����Ϸ�ѽ�����״̬λ
			Win_or_Lose = true;                        //����ϷӮ�˵�״̬
			cout << "Input any key to return menu" << endl;
			getch();                                    //���ڱ�ס��Ļ���
		}
		else
			gameON = true;                              //��Ϸ��������
	}
	else                                                //�õ㲻��ը�������ܱ��
	{
		cout << "(" << x << "," << y << ")" << "Can't mark : there isn't a bomb!" << endl;
		gameON = true;
	}
}

void Minesweeper::revealed(int x, int y)                 //�򿪸��ӵĺ���
{
	if (map[x][y] == BOMB || map[x][y] == MARKED)        //���򿪵ĸ�����һ��ը�����߸ø����ѱ����ը��
	{
		print(LOSE);                                     //��Ϸ������ӡ
		gameON = false;                                  //��Ϸ������־
		cout << "Input any key to return menu"<<endl;     
		getch();
	}
	else                                                  //�򿪸�����û��ը��
	{
		setMap(x, y);                                     //���øõ㼰��Χ�������ֵ
		print(ON);

		if (win())                                        //�������ը����������и����Ѿ����򿪣������׳ɹ�
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



void Minesweeper::saveGame()                          //������Ϸ���ļ� gameDate.txt
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

void Minesweeper::playing()                                 //��������Ϸ
{
	while (gameON)                                          //��Ϸ״̬����ʱ��ѭ��
	{
		int select,x,y;
		cout << "1. Revealed a grid.\t\t2. Mark a grid" << endl;     //1.�򿪸���    2.��Ǹ���
		cout << "3. save the game.\t\t4. return to menu\n" << endl;  //3.������Ϸ    4.���ص����˵�
		cout << "Please inpit [1/2/3/4] : ";
		cin >> select;
		if (select < 3)
		{
			cout << "Please input the row and column of the grid:" << endl;   //�����У���
			cin >> x >> y;
			if (select == 1)
				revealed(x, y);
			else
				marked(x, y);
		}
		else if (select == 3)
		{
			saveGame();                                                      //������Ϸ
			print(ON);
			cout << "The game have saved!\n" << endl;
		}			
		else
		{
			break;                                                           //��������Ϸ��ѭ���г�ȥ
		}
		
	}
}