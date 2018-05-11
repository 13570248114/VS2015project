#include"ReduceGeneric.h"

ReduceGeneric::ReduceGeneric() {
	_list.clear();
}

std::vector<int> ReduceGeneric::reduce(std::vector<int> list) {
	if (list.size()<2)                                            //如果list中的元素少于2个，直接返回list
		return list;
	if (list.size() == 2) {                                       //递归的基本情形，两个元素直接做二元运算，将返回的结果放入vector的末尾
		_list.push_back(binaryOperator(list.front(), list.back()));
		return _list;
	}
	else {
		int backNumber = list.back();                             //先取出list中的最后一个元素
		list.pop_back();                                          //将list的规模减少1
		_list.push_back(binaryOperator(reduce(list).back(),backNumber));     //将最后一个元素与问题规模为n-1时的结果做二元运算，将结果放到vector的末尾
		return _list;
	}
}