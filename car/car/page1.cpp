#include "page1.h"

void page1::display()
{
	cout << "编号\t车牌号\t型号" << endl;
	for (auto c : car_message)
		c.car_print_table();
}
void page1::add()
{
	cout << "请按以下格式输入车辆信息" << endl;
	cout << "车牌 车辆型号" << endl;
	string car_num, car_type;
	cin >> car_num >> car_type;
	car c;
	c.setcar(car_message.size(), car_num, car_type);
	car_message.push_back(c);
	display();
}

bool page1::del(int i)
{
	bool flag = false;
	for (auto next = car_message.begin();next != car_message.end();)
	{
		if (next->get_num() == i&&!flag)
		{
			next = car_message.erase(next);
			flag = true;
		}
		else
			next++;

		if (flag&&next!=car_message.end())
		{
			int new_num= next->get_num();
			new_num--;
			next->set_num(new_num);
		}
	}
	display();
	return flag;
}

vector<car>::iterator page1::find(string car_number)
{
	vector<car>::iterator next;
	for (next = car_message.begin();next != car_message.end();next++)
	{
		if (next->get_car_num()== car_number)
		{
			break;
		}
	}
	return next;
}

vector<car>::iterator page1::change(string car_number)
{
	bool flag = false;
	auto next = car_message.begin();
	for (;next != car_message.end();next++)
	{
		if (next->get_car_num() == car_number)
		{
			flag = true;
			cout << "车牌号为" << car_number << "的车辆信息是" << endl;
			next->car_print();
			int i;
			cout << "修改车牌号请按 0 ，修改车辆型号请按 1 ：";
			cin >> i;
			if (i == 0)
			{
				cout << "请输入新的车牌号:";
				string car_n;
				cin >> car_n;
				next->set_car_num(car_n);
			}
			if (i == 1)
			{
				cout << "请输入新的车辆类型:";
				string car_type;
				cin >> car_type;
				next->set_car_type(car_type);
			}
			break;
		}
	}
	return next;
}

void page1::read_file()
{
	ifstream in("car_message.txt");
	if(!in)
		cout << "文件不存在!" << endl;
	else
	{
		int num;
		string car_n;
		string car_t;
		car_message.clear();
		while (!in.eof())
		{
			in >> num >> car_n >> car_t;
			if (in.eof())break;
			car c(car_message.size(), car_n, car_t);
			car_message.push_back(c);
		}
		in.close();
		cout << "已从当前工作目录中的car_message.txt读入数据！" << endl;
	}
}

void page1::write_file()
{
	ofstream out("car_message.txt");
	for (auto c : car_message)
		out << c.get_num() <<'\t'<< c.get_car_num() << '\t'<< c.get_car_type() << '\n';
	out.close();
}

void page1::menu(int k)
{
	while (k)
	{
		system("cls");
		cout << "\n\n\n\t\t\t\t          车辆信息管理\t\n\n\n" << endl;
		cout << "\t\t\t****************************************************" << endl;
		cout << "\t\t\t*                     菜单                       *" << endl;
		cout << "\t\t\t****************************************************\n\n" << endl;
		cout << "\t\t           0 从文件读入车辆信息      1 车辆信息保存到文件 \n" << endl;
		cout << "\t\t           2 车辆信息输入            3 车辆信息删除 \n" << endl;
		cout << "\t\t           4 车辆信息修改            5 车辆信息显示      \n" << endl;
		cout << "\t\t           6 车辆信息查询            7 返回上级菜单    \n" << endl;
		cout << "\t\t        请选择[0/1/2/3/4/5/6/7]:" << endl;

		int select;
		cin >> select;

		string car_n;
		vector<car>::iterator it2, next;
		switch (select)
		{
		case 0:
			read_file();
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 1:
			write_file();
			cout << "已把数据保存在当前工作目录中的car_message.txt中！" << endl;
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 2:
			system("cls");
			add();
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 3:
			system("cls");
			display();
			cout << "\n请输入希望删除的车辆的编号：";
			int n;
			cin >> n;
			if (del(n))cout << "删除成功！" << endl;
			else cout << "删除失败！" << endl;
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 4:
			system("cls");
			display();
			cout << "\n请输入车牌号" << endl;
			cin >> car_n;
			it2 = change(car_n);
			if (it2 != car_message.end()) { cout << "修改成功！" << endl; it2->car_print(); }
			else cout << "修改失败！" << endl;	
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 5:
			system("cls");
			display();
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 6:
			system("cls");
			cout << "\n请输入希望查找的车辆的车牌号：";
			cin >> car_n;
			next = find(car_n);
			if (next != car_message.end())
			{
				cout << "已找到，车牌号为" << car_n << "的车辆信息是" << endl;
				cout << "编号\t型号\t型号" << endl;
				next->car_print_table();
			}
			else
				cout << "找不到" << endl;
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 7:
			k = 0;
			break;
		}
	}
	

}


