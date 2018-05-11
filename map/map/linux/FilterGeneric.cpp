#include"FilterGeneric.h"

FilterGeneric::FilterGeneric() {
	_list.clear();
}

std::vector<int> FilterGeneric::filter(std::vector<int> list) {
	if (list.empty())                                         //如果输入为空，则直接返回空
		return list;
	if (list.size() == 1) {                                   //递归的基本情形
		if(g(list.front()))                                   //满足过滤条件，则加入容器内
			_list.push_back(list.front());
		return _list;
	}
	else {
		int backNumber = list.back();                          //先读取输入容器内最后一个元素的值
		list.pop_back();                                       //再丢弃数组最后一个元素，使容器的规模变为n-1
		_list = filter(list);                                  //用_list保存前n-1元素过滤的结果
		if (g(backNumber))                                     //每次递归都看最后一个元素是否满足过滤条件
			_list.push_back(backNumber);                       //满足过滤条件，则加入容器内
		return _list;
	}
}