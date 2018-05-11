#include "page2.h"

void page2::display()                                           //��ʾ����
{
	cout << "����\t�Ա�\t���֤\t�绰\t����\t�����\t���ƺ�\t���ͺ�" << endl;
	for (auto c : owner_message)
		c.owner_print_table();
}
void page2::add(page1 p1)                                   //��ӳ�����Ϣ������Ҫ�����복���ڵ�ĳһ������Ӧ
{
	cout << "�밴���¸�ʽ���복����Ϣ" << endl;
	cout << "���� �Ա� ���֤ �绰���� ����" << endl;
	string name, sex,id,tel,car_n,car_t;
	int year;
	cin >> name >> sex >> id >> tel >> year;
	cout << "���������г�������Ϣ���£�" << endl;
	p1.display();
	cout << "������ó����ĳ����ĳ���(���ƺ���Ҫ�ڳ�����)��" << endl;
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
	 		cout << "������ĳ������ڳ����ڣ����������복�ƺţ��������� no ����������Ϣ¼��" << endl;
	} while (flag&&car_n != "no");
	display();
}

bool page2::del(string name)                          //ɾ��������Ϣ�ĺ���
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

void page2::find(string name)                                    //���ҳ�����Ϣ�ĺ���
{
	bool flag = false;
	for (auto next = owner_message.begin();next != owner_message.end();next++)
	{
		if (next->get_owner_name() == name)
		{
			flag = true;
			cout << "���ҵ�������Ϊ" << name << "����Ϣ��" << endl;
			cout << "����\t�Ա�\t���֤\t�绰\t����\t�����\t���ƺ�\t���ͺ�" << endl;
			next->owner_print_table();
			break;
		}
	}
	if (!flag)
		cout << "�Ҳ�������Ϊ" << name << "����Ϣ" << endl;
}

vector<owner>::iterator page2::change(string name)             //�ı䳵����Ϣ�ĺ���
{
	bool flag = false;
	auto next = owner_message.begin();
	for (;next != owner_message.end();next++)
	{
		if (next->get_owner_name() == name)
		{
			flag = true;
			cout << "����Ϊ" << name << "����Ϣ��" << endl;
			next->owner_print();
			int i;
			cout << "�޸����֤�밴 0 ���޸ĵ绰�����밴 1 ���޸ĳ����밴2��";
			cin >> i;
			if (i == 0)
			{
				cout << "�����������֤:";
				string id;
				cin >> id;
				next->set_id(id);
			}
			else if (i == 1)
			{
				cout << "�������µ绰����:";
				string tel;
				cin >> tel;
				next->set_owner_tel(tel);
			}
			else if (i == 2)
			{
				cout << "�������µĳ���:";
				int year;
				cin >> year;
				next->set_year(year);
			}
			else
				cout << "�������" << endl;
			break;
		}
	}
	return next;
}

void page2::read_file()                               //���ļ��ж�������Ϣ
{
	ifstream in("owner_message.txt");
	if (!in)
		cout << "�ļ�������!" << endl;
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
		cout << "�Ѵӵ�ǰ����Ŀ¼�е�owner_message.txt�������ݣ�" << endl;
		in.close();
	}
}

void page2::write_file()                    //�ѳ�����Ϣд���ļ�
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
		cout << "\n\n\n\t\t\t\t        ������Ϣ����\t\n\n\n" << endl;
		cout << "\t\t\t****************************************************" << endl;
		cout << "\t\t\t*                     �˵�                         *" << endl;
		cout << "\t\t\t****************************************************\n\n" << endl;
		cout << "\t\t           0 ���ļ����복����Ϣ      1 ������Ϣ���浽�ļ� \n" << endl;
		cout << "\t\t           2 ������Ϣ����            3 ������Ϣɾ�� \n" << endl;
		cout << "\t\t           4 ������Ϣ�޸�            5 ������Ϣ��ʾ      \n" << endl;
		cout << "\t\t           6 ������Ϣ��ѯ            7 �����ϼ��˵�     \n" << endl;
		cout << "\t\t        ��ѡ��[0/1/2/3/4/5/6/7]:" << endl;

		int select;
		cin >> select;

		string name;
		vector<owner>::iterator it2;
		switch (select)
		{
		case 0:
			read_file();
			cout << "\n���������������" << endl;
			getch();
			break;
		case 1:
			write_file();
			cout << "�Ѱ����ݱ����ڵ�ǰ����Ŀ¼�е�owner_message.txt�У�" << endl;
			cout << "\n���������������" << endl;
			getch();
			break;
		case 2:
			system("cls");
			add(p1);
			cout << "\n���������������" << endl;
			getch();
			break;
		case 3:
			system("cls");
			display();
			cout << "\n������ϣ��ɾ���ĳ���������";	
			cin >> name;
			if (del(name))cout << "ɾ���ɹ���" << endl;
			else cout << "ɾ��ʧ�ܣ�" << endl;
			cout << "\n���������������" << endl;
			getch();
			break;
		case 4:
			system("cls");
			display();
			cout << "\n������ϣ��ɾ���ĳ���������";
			cin >> name;
			it2 = change(name);
			if (it2 != owner_message.end()) { cout << "�޸ĳɹ���" << endl; it2->owner_print(); }
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
			cout << "\n������ϣ�����ҵĳ������֣�";
			cin >> name;
			find(name);
			cout << "\n���������������" << endl;
			getch();
			break;
		case 7:
			k = 0;
			break;
		}
	}


}


