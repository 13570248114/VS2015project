#include"MapGeneric.h"

MapGeneric::MapGeneric(){
	_list.clear();
}

std::vector<int> MapGeneric::map(std::vector<int> list) {
	if (list.empty())
		return list;
	if (list.size() == 1) {                                               //�������Σ���listֻ��һ��Ԫ��ʱ����ӳ��֮��Ž��������
		_list.push_back(f(list.front()));
		return _list;
	}
	else {
		int backNumber = list.back();                                     //ÿ�εݹ�֮ǰ�ȳ�����һ��Ԫ��
		list.pop_back();
		_list = map(list);                                                //_list�����ģΪn-1ʱ�����صĽ��
		_list.push_back(f(backNumber));                                   //������������һ��ӳ������_list
		return _list;
	}
}