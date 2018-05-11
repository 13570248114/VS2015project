#ifndef PAGE1_H
#define PAGE1_H

#include "head.h"
#include "car.h"
class page1 {
private:
	vector<car> car_message;
public:
	page1() {};
	void display();
	void add();
	bool del(int i);
	vector<car>::iterator find(string car_number);
	vector<car>::iterator change(string car_number);
	void menu(int k);
	void read_file();
	void write_file();
	vector<car>& get_car_message() {
		return car_message;
	}
};

#endif
