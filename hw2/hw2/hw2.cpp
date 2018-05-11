#include<fstream>
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
void readFile(string fileName, string words[], int numberOfWords);
void replaceWord(string &word, char toReplaceInWord);
void writeFile(string fileName, string words[], int numberOfWords);

int main(int argc, char* argv[]) {
	//Check correct number of arguments
	if (argc != 5) {
		cout << "Error" << endl;
		return 0;
	}
	//Handling cmd line args
	//YOU MUST INITIALIZE THEIR VALUES!
	string inputFileName = argv[1];
	string outputFileName = argv[2];
	int numberOfWords = atoi(argv[3]);
	char* lettersToReplace = argv[5];
	/*
	* Initialize your variables here
	*/
	//Checking valid input
	if (numberOfWords <= 0) {
		cout << "Error" << endl;
		return 0;
	}
	string* words = new string[numberOfWords];
	//Reading input from file
	readFile(inputFileName, words, numberOfWords);
	int len = strlen(lettersToReplace);
	for(int i=0;i<numberOfWords;i++)
		for (int j = 0;j < len;j++) {
			replaceWord(words[i], lettersToReplace[j]);
		}
	writeFile(outputFileName, words, numberOfWords);
	return 0;
}

void readFile(string fileName, string words[], int numberOfWords)
{
	ifstream in(fileName);
	for (int i = 0;i < numberOfWords;i++)
		in >> words[i];
}

void replaceWord(string &word, char toReplaceInWord)
{
	if (word[0] == toReplaceInWord)
		word = "----";
}

void writeFile(string fileName, string words[], int numberOfWords)
{
	ofstream out(fileName);
	for (int i = 0;i < numberOfWords;i++)
	{
		out << words[i] << "\n";
	}
}


