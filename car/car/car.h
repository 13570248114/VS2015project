#ifndef CAR_H
#define CAR_H

#include"head.h"
class car {
private:
	int num;                                  //�������
	string car_mum;                           //����
	string car_type;                          //�����ͺ�

public:
	car() {};
	car(int n , string s1 , string s2 ) :num(n), car_mum(s1), car_type(s2) {};  //���캯��
	void setcar(int number, string s1, string s2);    //���þ������Ϣ
	void set_num(int number);
	void set_car_num(string s1);
	void set_car_type(string s2);
	int get_num() { return num; }
	string& get_car_num() { return car_mum; }
	string& get_car_type() { return car_type; }
	void car_print();    //��ӡ������Ϣ�ĺ���
	void car_print_table();
};

#endif

