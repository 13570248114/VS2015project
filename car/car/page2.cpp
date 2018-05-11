#include "page2.h"

void page2::display()                                           //显示函数
{
	cout << "姓名\t性别\t身份证\t电话\t车龄\t车编号\t车牌号\t车型号" << endl;
	for (auto c : owner_message)
		c.owner_print_table();
}
void page2::add(page1 p1)                                   //添加车主信息函数，要求车主与车库内的某一部车对应
{
	cout << "请按以下格式输入车主信息" << endl;
	cout << "姓名 性别 身份证 电话号码 车龄" << endl;
	string name, sex,id,tel,car_n,car_t;
	int year;
	cin >> name >> sex >> id >> tel >> year;
	cout << "车库内所有车辆的信息如下：" << endl;
	p1.display();
	cout << "请输入该车主的车辆的车牌(车牌号码要在车库内)：" << endl;
	bool flag = true;
	do {
		cin >> car_n;
		auto next = p1.find(car_n);
		if (next != p1.get_car_message().end())
		{
			flag = false;
			owner o(name, sex, id, tel, year, next->get_num(), next->get_car_num(), next->get_car_type());
			owner_message.push_back(o);
		}
		else
	 		cout << "所输入的车辆不在车库内，请重新输入车牌号，或者输入 no 结束车主信息录入" << endl;
	} while (flag&&car_n != "no");
	display();
}

bool page2::del(string name)                          //删除车主信息的函数
{
	bool flag = false;
	for (auto next = owner_message.begin();next != owner_message.end();)
	{
		if (next->get_owner_name() == name && !flag)
		{
			next = owner_message.erase(next);
			flag = true;
		}
		else
			next++;

		if (flag&&next != owner_message.end())
		{
			int new_num = next->get_num();
			new_num--;
			next->set_num(new_num);
		}
	}
	display();
	return flag;
}

void page2::find(string name)                                    //查找车主信息的函数
{
	bool flag = false;
	for (auto next = owner_message.begin();next != owner_message.end();next++)
	{
		if (next->get_owner_name() == name)
		{
			flag = true;
			cout << "已找到，车主为" << name << "的信息是" << endl;
			cout << "姓名\t性别\t身份证\t电话\t车龄\t车编号\t车牌号\t车型号" << endl;
			next->owner_print_table();
			break;
		}
	}
	if (!flag)
		cout << "找不到车主为" << name << "的信息" << endl;
}

vector<owner>::iterator page2::change(string name)             //改变车主信息的函数
{
	bool flag = false;
	auto next = owner_message.begin();
	for (;next != owner_message.end();next++)
	{
		if (next->get_owner_name() == name)
		{
			flag = true;
			cout << "车主为" << name << "的信息是" << endl;
			next->owner_print();
			int i;
			cout << "修改身份证请按 0 ，修改电话号码请按 1 ，修改车龄请按2：";
			cin >> i;
			if (i == 0)
			{
				cout << "请输入新身份证:";
				string id;
				cin >> id;
				next->set_id(id);
			}
			else if (i == 1)
			{
				cout << "请输入新电话号码:";
				string tel;
				cin >> tel;
				next->set_owner_tel(tel);
			}
			else if (i == 2)
			{
				cout << "请输入新的车龄:";
				int year;
				cin >> year;
				next->set_year(year);
			}
			else
				cout << "输入错误！" << endl;
			break;
		}
	}
	return next;
}

void page2::read_file()                               //从文件中读车主信息
{
	ifstream in("owner_message.txt");
	if (!in)
		cout << "文件不存在!" << endl;
	else
	{
		string name, sex, id, tel, car_n, car_t;
		int year, nn;
		owner_message.clear();
		while (!in.eof())
		{
			in >> name >> sex >> id >> tel >> year >> nn >> car_n >> car_t;
			if (in.eof())break;
			owner o(name, sex, id, tel, year, nn, car_n, car_t);
			owner_message.push_back(o);
		}
		cout << "已从当前工作目录中的owner_message.txt读入数据！" << endl;
		in.close();
	}
}

void page2::write_file()                    //把车主信息写入文件
{
	ofstream out("owner_message.txt");
	for (auto c : owner_message)
		out << c.get_owner_name() << '\t' << c.get_owner_sex()<< '\t' <<c.get_id()<<'\t'<<c.get_owner_tel() << '\t'<<c.get_year()<<'\t'<<c.get_num()<<'\t'<<c.get_car_num()<<'\t'<<c.get_car_type()<<'\n';
	out.close();
}

void page2::menu(int k, page1 p1)
{
	while (k)
	{
		system("cls");
		cout << "\n\n\n\t\t\t\t        车主信息管理\t\n\n\n" << endl;
		cout << "\t\t\t****************************************************" << endl;
		cout << "\t\t\t*                     菜单                         *" << endl;
		cout << "\t\t\t****************************************************\n\n" << endl;
		cout << "\t\t           0 从文件读入车主信息      1 车主信息保存到文件 \n" << endl;
		cout << "\t\t           2 车主信息输入            3 车主信息删除 \n" << endl;
		cout << "\t\t           4 车主信息修改            5 车主信息显示      \n" << endl;
		cout << "\t\t           6 车主信息查询            7 返回上级菜单     \n" << endl;
		cout << "\t\t        请选择[0/1/2/3/4/5/6/7]:" << endl;

		int select;
		cin >> select;

		string name;
		vector<owner>::iterator it2;
		switch (select)
		{
		case 0:
			read_file();
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 1:
			write_file();
			cout << "已把数据保存在当前工作目录中的owner_message.txt中！" << endl;
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 2:
			system("cls");
			add(p1);
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 3:
			system("cls");
			display();
			cout << "\n请输入希望删除的车主姓名：";	
			cin >> name;
			if (del(name))cout << "删除成功！" << endl;
			else cout << "删除失败！" << endl;
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 4:
			system("cls");
			display();
			cout << "\n请输入希望删除的车主姓名：";
			cin >> name;
			it2 = change(name);
			if (it2 != owner_message.end()) { cout << "修改成功！" << endl; it2->owner_print(); }
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
			cout << "\n请输入希望查找的车主名字：";
			cin >> name;
			find(name);
			cout << "\n请输入任意键返回" << endl;
			getch();
			break;
		case 7:
			k = 0;
			break;
		}
	}


}


