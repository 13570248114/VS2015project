#include<iostream>
#include<string>
using namespace std;

struct S
{
	int i;
	int *p;
};

int main() {
	struct S s;
	int *p = &s.i;
	p[0] = 4;
	p[1] = 3;
	s.p = p;
	s.p[1] = 1;
	s.p[0] = 2;
}

//˼·����ch = getchar()ѭ�����뵥���ַ����������ֵ��ַ������ַ���num���棬��stoi��������ת��