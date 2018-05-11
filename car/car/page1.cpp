#include "page1.h"

void page1::display()
{
	cout << "���\t���ƺ�\t�ͺ�" << endl;
	for (auto c : car_message)
		c.car_print_table();
}
void page1::add()
{
	cout << "�밴���¸�ʽ���복����Ϣ" << endl;
	cout << "���� �����ͺ�" << endl;
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
			cout << "���ƺ�Ϊ" << car_number << "�ĳ�����Ϣ��" << endl;
			next->car_print();
			int i;
			cout << "�޸ĳ��ƺ��밴 0 ���޸ĳ����ͺ��밴 1 ��";
			cin >> i;
			if (i == 0)
			{
				cout << "�������µĳ��ƺ�:";
				string car_n;
				cin >> car_n;
				next->set_car_num(car_n);
			}
			if (i == 1)
			{
				cout << "�������µĳ�������:";
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
		cout << "�ļ�������!" << endl;
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
		cout << "�Ѵӵ�ǰ����Ŀ¼�е�car_message.txt�������ݣ�" << endl;
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
		cout << "\n\n\n\t\t\t\t          ������Ϣ����\t\n\n\n" << endl;
		cout << "\t\t\t****************************************************" << endl;
		cout << "\t\t\t*                     �˵�                       *" << endl;
		cout << "\t\t\t****************************************************\n\n" << endl;
		cout << "\t\t           0 ���ļ����복����Ϣ      1 ������Ϣ���浽�ļ� \n" << endl;
		cout << "\t\t           2 ������Ϣ����            3 ������Ϣɾ�� \n" << endl;
		cout << "\t\t           4 ������Ϣ�޸�            5 ������Ϣ��ʾ      \n" << endl;
		cout << "\t\t           6 ������Ϣ��ѯ            7 �����ϼ��˵�    \n" << endl;
		cout << "\t\t        ��ѡ��[0/1/2/3/4/5/6/7]:" << endl;

		int select;
		cin >> select;

		string car_n;
		vector<car>::iterator it2, next;
		switch (select)
		{
		case 0:
			read_file();
			cout << "\n���������������" << endl;
			getch();
			break;
		case 1:
			write_file();
			cout << "�Ѱ����ݱ����ڵ�ǰ����Ŀ¼�е�car_message.txt�У�" << endl;
			cout << "\n���������������" << endl;
			getch();
			break;
		case 2:
			system("cls");
			add();
			cout << "\n���������������" << endl;
			getch();
			break;
		case 3:
			system("cls");
			display();
			cout << "\n������ϣ��ɾ���ĳ����ı�ţ�";
			int n;
			cin >> n;
			if (del(n))cout << "ɾ���ɹ���" << endl;
			else cout << "ɾ��ʧ�ܣ�" << endl;
			cout << "\n���������������" << endl;
			getch();
			break;
		case 4:
			system("cls");
			display();
			cout << "\n�����복�ƺ�" << endl;
			cin >> car_n;
			it2 = change(car_n);
			if (it2 != car_message.end()) { cout << "�޸ĳɹ���" << endl; it2->car_print(); }
			else cout << "�޸�ʧ�ܣ�" << endl;	
			cout << "\n���������������" << endl;
			getch();
			break;
		case 5:
			system("cls");
			display();
			cout << "\n���������������" << endl;
			getch();
			break;
		case 6:
			system("cls");
			cout << "\n������ϣ�����ҵĳ����ĳ��ƺţ�";
			cin >> car_n;
			next = find(car_n);
			if (next != car_message.end())
			{
				cout << "���ҵ������ƺ�Ϊ" << car_n << "�ĳ�����Ϣ��" << endl;
				cout << "���\t�ͺ�\t�ͺ�" << endl;
				next->car_print_table();
			}
			else
				cout << "�Ҳ���" << endl;
			cout << "\n���������������" << endl;
			getch();
			break;
		case 7:
			k = 0;
			break;
		}
	}
	

}


