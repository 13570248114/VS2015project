#include<iostream>
#include<fstream>
#include"Minesweeper.h"           
using namespace std;
void menu();
int main()
{
	while(1)                     //ѭ��ִ�����˵�
		menu();	
}

void menu()
{
	system("cls");                                              //��������
	cout << "\tMinesweeper\t\t\t\n\n" << endl;
	cout << "\t   menu\t\t\n\n" << endl;
	cout << "1. continue playing the saved game" << endl;      //1.���ѱ������Ϸ�лָ�
	cout << "2. start new game" << endl;                       //2.��ʼһ���µ���Ϸ��10��10��,25��ը��
	cout << "3. difficulty levels setting" << endl;            //3.ѡ�����ѳ̶�
	cout << "4. choose the size of the board" << endl;         //4.�Զ���ͼ�Ĵ�С��ը������
	cout << "\nPlease input [1/2/3/4] to play the game " << endl;

	int select;
	cin >> select;

	switch (select)
	{
	case 1:
	{
		ifstream in("gameDate.txt");                //�򿪱�����Ϸ���ļ�
		Minesweeper game(in);                       //���ļ������һ����Ϸ����
		game.print(game.getGameON());               //��ӡ
		game.playing();                             //����Ϸ
		break;
	}
	case 2:
	{
		Minesweeper game(10, 10, 20);               //����һ���µ���Ϸ��10��10��,25��ը��
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
			Minesweeper game(5, 5, 5);                  //�򵥣�����һ���µ���Ϸ��5��5��, 5��ը��
			game.print(game.getGameON());
			game.playing();
			break;
		}
		case 2:
		{
			Minesweeper game(10, 10, 20);               //��ͨ������һ���µ���Ϸ��10��10��, 25��ը��
			game.print(game.getGameON());
			game.playing();
			break;
		}
		case 3:
		{
			Minesweeper game(15, 15, 45);               //���ѣ�����һ���µ���Ϸ��15��15��, 45��ը��
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
		Minesweeper game(row, col, bombs);          //�Զ��壺����һ���µ���Ϸ��row��col��, bombs��ը��
		game.print(game.getGameON());
		game.playing();
		break;
	}
	}



}