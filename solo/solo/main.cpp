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

//思路：用ch = getchar()循环读入单个字符，把是数字的字符加入字符串num后面，用stoi函数进行转换