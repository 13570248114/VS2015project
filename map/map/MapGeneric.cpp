#include"MapGeneric.h"

MapGeneric::MapGeneric(){
	_list.clear();
}

std::vector<int> MapGeneric::map(std::vector<int> list) {
	if (list.empty())
		return list;
	if (list.size() == 1) {                                               //基本情形，当list只有一个元素时，作映射之后放进结果数组
		_list.push_back(f(list.front()));
		return _list;
	}
	else {
		int backNumber = list.back();                                     //每次递归之前先抽出最后一个元素
		list.pop_back();
		_list = map(list);                                                //_list保存规模为n-1时所返回的结果
		_list.push_back(f(backNumber));                                   //把所抽出来最后一个映射后放入_list
		return _list;
	}
}