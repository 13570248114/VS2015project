#include<iostream>
#include<string>
#include<sstream>
using namespace std;

/*

int main() {
	string last, cur;
	string in;
	cin >> in;
	for (auto ch : in) {
		if(ch >= '0'&&ch <= '9')
			cur += ch;
		else {
			if (cur.size() >= last.size())
				last = cur;
			cur.clear();
		}
	}
	if (cur.size() >= last.size())
		last = cur;
	cout << last << "," << last.size() << endl;
}

*/

typedef struct
{
	unsigned int uiElementLength;    //表示uiElementValue占用BIT数，范围1~32
	unsigned int uiElementValue;     //从字节流中按顺序解析的数值，用于输出

}ELEMENT_STRU;



void Decode(unsigned int uiInputLen, unsigned char aInputByte[], unsigned int uiElementNum, ELEMENT_STRU astElement[]) {
	int head, tail;
	for(int i)
}

int main() {
	string six;
	unsigned int uiInputLen;
	cin >> uiInputLen;
	unsigned char* aInputByte = new unsigned char[uiInputLen];
	for (int i = 0;i < uiInputLen;i++) {
		cin >> six;
		aInputByte[i] = (six[3] - '0') + (six[2] - '0') * 16;
	}
	int uiElementNum;
	cin >> uiElementNum;
	ELEMENT_STRU* astElement = new ELEMENT_STRU[uiElementNum];
	for (int i = 0;i < uiElementNum;i++)
		cin >> astElement[i].uiElementLength;
	Decode(uiInputLen, aInputByte, uiElementNum, astElement);
	return 0;
}