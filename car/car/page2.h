#ifndef PAGE2_H
#define PAGE2_H

#include "head.h"
#include "owner.h"
#include "page1.h"

class page2 {
private:
	vector<owner> owner_message;
public:
	page2() {};
	void display();
	void add(page1 p1);
	bool del(string name);
	void find(string name);
	vector<owner>::iterator change(string name);
	void menu(int k,page1 p1);
	void read_file();
	void write_file();
};

#endif
