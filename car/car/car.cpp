#include"car.h"

void car::setcar(int number, string s1, string s2)
{
	num = number;
	car_mum = s1;
	car_type = s2;
}

void car::car_print()
{
	cout << "\n�������Ϊ" << num << "�ĳ�����Ϣ���£�" << endl;
	cout << "���ƣ�" << car_mum << endl;
	cout << "�������ͣ�" << car_type << endl;
}

void car::set_num(int number)
{
	num = number;
}

void car::set_car_num(string s1)
{
	car_mum = s1;
}

void car::set_car_type(string s2)
{
	car_type = s2;
}

void car::car_print_table()
{
	cout << num << '\t' << car_mum << '\t' << car_type << endl;
}
