#include<iostream>
#include"ReadWords.h"
using namespace std;

int main()
{
	ReadWords read("hamlet.txt");
	while (read.isNextWord())
	{
		read.getNextWord();
		cout << endl;
	}
}