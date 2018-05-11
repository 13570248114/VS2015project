#include"ReduceGeneric.h"

ReduceGeneric::ReduceGeneric() {
	_list.clear();
}

std::vector<int> ReduceGeneric::reduce(std::vector<int> list) {
	if (list.size()<2)                                            //���list�е�Ԫ������2����ֱ�ӷ���list
		return list;
	if (list.size() == 2) {                                       //�ݹ�Ļ������Σ�����Ԫ��ֱ������Ԫ���㣬�����صĽ������vector��ĩβ
		_list.push_back(binaryOperator(list.front(), list.back()));
		return _list;
	}
	else {
		int backNumber = list.back();                             //��ȡ��list�е����һ��Ԫ��
		list.pop_back();                                          //��list�Ĺ�ģ����1
		_list.push_back(binaryOperator(reduce(list).back(),backNumber));     //�����һ��Ԫ���������ģΪn-1ʱ�Ľ������Ԫ���㣬������ŵ�vector��ĩβ
		return _list;
	}
}