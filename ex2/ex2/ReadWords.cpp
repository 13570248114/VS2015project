#include"ReadWords.h"
#include<iostream>
#include<cstdlib>
#include<cctype>
using namespace std;

ReadWords::ReadWords(const char *filename)
{
	wordfile.open(filename);
	if (wordfile.fail())
	{
		cout << filename << "open error !" << endl;
		exit(1);
	}
}

bool ReadWords::isNextWord()
{
	char c;
	wordfile >> c;
	if (c == EOF&&nextword.empty())
		return false;
	else
	{
		wordfile.seekg(-1, ios::cur);
		return true;
	}
}

string ReadWords::getNextWord()
{
	string word;
	if (isNextWord())
	{
		if (nextword.empty()) {
			getline(wordfile, nextword);
			nextword += ' ';
		}
		int i = 0;
		for (;i < nextword.length();i++)
		{
			if (nextword[i] != ' ')
			{
				word += tolower(nextword[i]);
			}
			else
			{
				nextword = nextword.substr(i+1, nextword.length() - i-1);
				int j;
				for (j = word.length() - 1;j >= 0;j--)
					if (isalpha(word[j]))
						break;
				word = word.substr(0, j + 1);
				//
				cout << word << "\n" << nextword;
				//
				break;
			}
		}

	}
	return word;
}

void  ReadWords::close()
{
	wordfile.close();
}