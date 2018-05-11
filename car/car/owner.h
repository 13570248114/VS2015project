#ifndef OWNER_H
#define OWNER_H

#include"car.h"
class owner :public car {
private:
	string owner_name;                //姓名
	string owner_sex;                 //性别
	string id;                       //身份证
	string owner_tel;                //电话号码
	int years;                       //车龄

public:
	owner(){};
	owner(string o_name , string sex, string i, string tel,int y,int n, string s1, string s2): owner_name(o_name),owner_sex(sex),id(i),owner_tel(tel),years(y),car(n,s1,s2){};
	string& get_owner_name() { return owner_name; }
	string& get_owner_sex() { return owner_sex; }
	string& get_id() { return id; }
	string& get_owner_tel() { return owner_tel; }
	int get_year() { return years; }

	void set_owner_name(string s1);
	void set_owner_sex(string s2);
	void set_id(string s3);
	void set_owner_tel(string s4);
	void set_owner(string s1, string s2, string s3, string s4);
	void set_year(int y);

	void owner_print();
	void owner_print_table();
};

#endif // !OWNER_H

