#ifndef CAR_H
#define CAR_H

#include"head.h"
class car {
private:
	int num;                                  //车辆编号
	string car_mum;                           //车牌
	string car_type;                          //车辆型号

public:
	car() {};
	car(int n , string s1 , string s2 ) :num(n), car_mum(s1), car_type(s2) {};  //构造函数
	void setcar(int number, string s1, string s2);    //设置具体的信息
	void set_num(int number);
	void set_car_num(string s1);
	void set_car_type(string s2);
	int get_num() { return num; }
	string& get_car_num() { return car_mum; }
	string& get_car_type() { return car_type; }
	void car_print();    //打印车辆信息的函数
	void car_print_table();
};

#endif

