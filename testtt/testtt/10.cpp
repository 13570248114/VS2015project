#include<iostream>
#include<string>
using namespace std;

template<typename s1, typename s2, typename s3, typename s4, typename s5, typename s6> class Student {
public:
	Student() {};
	Student(s1 ss1, s2 ss2, s3 ss3, s4 ss4, s5 ss5) :xuehao(ss1), xingming(ss2), gaoshu(ss3), yingyu(ss4), chengxu(ss5), zongfen(ss3+ss4+ss5) {};
	friend ostream& operator<<(ostream& os, const Student& s)
	{
		os << "学号：" << s.xuehao << endl;
		os << "姓名：" << s.xingming << endl;
		os << "数学：" << s.gaoshu << endl;
		os << "英语：" << s.yingyu << endl;
		os << "程学设计：" << s.chengxu << endl;
		os << "总分：" << s.zongfen << endl;
		os << endl;
		return os;
	}
private:
	s1 xuehao;
	s2 xingming;
	s3 gaoshu;
	s4 yingyu;
	s5 chengxu;
	s6 zongfen;
};

int main()
{
	int xuehao = 2017342;
	Student<int, string, int, int, int, int> s1(xuehao, string("李晓华"),78, 82, 74);
	Student<string, string, double, double, double, double> s2(string("0214546"), string("张雨生"), 82.5, 77.5, 84.5);
	cout << s1 << endl;
	cout << s2 << endl;
}
