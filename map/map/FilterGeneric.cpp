#include"FilterGeneric.h"

FilterGeneric::FilterGeneric() {
	_list.clear();
}

std::vector<int> FilterGeneric::filter(std::vector<int> list) {
	if (list.empty())                                         //�������Ϊ�գ���ֱ�ӷ��ؿ�
		return list;
	if (list.size() == 1) {                                   //�ݹ�Ļ�������
		if(g(list.front()))                                   //������������������������
			_list.push_back(list.front());
		return _list;
	}
	else {
		int backNumber = list.back();                          //�ȶ�ȡ�������������һ��Ԫ�ص�ֵ
		list.pop_back();                                       //�ٶ����������һ��Ԫ�أ�ʹ�����Ĺ�ģ��Ϊn-1
		_list = filter(list);                                  //��_list����ǰn-1Ԫ�ع��˵Ľ��
		if (g(backNumber))                                     //ÿ�εݹ鶼�����һ��Ԫ���Ƿ������������
			_list.push_back(backNumber);                       //������������������������
		return _list;
	}
}