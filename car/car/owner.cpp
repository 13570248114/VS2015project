#include"owner.h"

void owner::set_owner_name(string s1)
{
	owner_name = s1;
}

void owner::set_owner_sex(string s2)
{
	owner_sex = s2;
}

void owner::set_id(string s3)
{
	id = s3;
}

void owner::set_owner_tel(string s4)
{
	owner_tel = s4;
}

void owner::set_owner(string s1, string s2, string s3, string s4)
{
	owner_name = s1;
	owner_sex = s2;
	id = s3;
	owner_tel = s4;
}

void owner::owner_print()
{
	cout << "车主的个人信息如下：" << endl;
	cout << "姓名：" << owner_name << '\t' << "性别：" << owner_sex << endl;
	cout << "电话：" << owner_tel << '\t' << "身份证：" << id << endl;
	cout << "其车辆信息如下：" << endl;
	car_print();
}

void owner::owner_print_table()
{
	cout << owner_name << '\t' << owner_sex << '\t' << id << '\t' << owner_tel<<'\t'<<years;
	cout << '\t';
	car_print_table();
}

void owner::set_year(int y)
{
	years = y;
}