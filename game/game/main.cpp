#include<iostream>
#include<fstream>
#include"Minesweeper.h"           
using namespace std;
void menu();
int main()
{
	while(1)                     //循环执行主菜单
		menu();	
}

void menu()
{
	system("cls");                                              //清屏函数
	cout << "\tMinesweeper\t\t\t\n\n" << endl;
	cout << "\t   menu\t\t\n\n" << endl;
	cout << "1. continue playing the saved game" << endl;      //1.从已保存的游戏中恢复
	cout << "2. start new game" << endl;                       //2.开始一个新的游戏，10×10，,25个炸弹
	cout << "3. difficulty levels setting" << endl;            //3.选择困难程度
	cout << "4. choose the size of the board" << endl;         //4.自定义图的大小和炸弹个数
	cout << "\nPlease input [1/2/3/4] to play the game " << endl;

	int select;
	cin >> select;

	switch (select)
	{
	case 1:
	{
		ifstream in("gameDate.txt");                //打开保存游戏的文件
		Minesweeper game(in);                       //从文件构造出一个游戏对象
		game.print(game.getGameON());               //打印
		game.playing();                             //玩游戏
		break;
	}
	case 2:
	{
		Minesweeper game(10, 10, 20);               //构造一个新的游戏，10×10，,25个炸弹
		game.print(game.getGameON());
		game.playing();
		break;
	}
	case 3:
	{
		system("cls");
		int se;
		cout << "\t difficulty levels\n\n" << endl;
		cout << "  1. easy" << endl;
		cout << "  2. normal" << endl;
		cout << "  3. hard" << endl;
		cout << "\nPlease select 1/2/3: ";
		cin >> se;
		switch (se)
		{
		case 1:
		{
			Minesweeper game(5, 5, 5);                  //简单：构造一个新的游戏，5×5，, 5个炸弹
			game.print(game.getGameON());
			game.playing();
			break;
		}
		case 2:
		{
			Minesweeper game(10, 10, 20);               //普通：构造一个新的游戏，10×10，, 25个炸弹
			game.print(game.getGameON());
			game.playing();
			break;
		}
		case 3:
		{
			Minesweeper game(15, 15, 45);               //困难：构造一个新的游戏，15×15，, 45个炸弹
			game.print(game.getGameON());
			game.playing();
			break;
		}

		}
		break;
	}
	case 4:
	{
		system("cls");
		int row, col, bombs;
		cout << "\t\tchoose the size of the board" << endl;
		cout << "Please input the size of the board" << endl;
		cout << "the number of the rows   the number of the columns  the number of the bombs:" << endl;
		cin >> row >> col >> bombs;
		Minesweeper game(row, col, bombs);          //自定义：构造一个新的游戏，row×col，, bombs个炸弹
		game.print(game.getGameON());
		game.playing();
		break;
	}
	}



}