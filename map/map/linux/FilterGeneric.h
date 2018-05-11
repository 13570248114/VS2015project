#ifndef FILTERGENERIC_H
#define FILTERGENERIC_H
#include<vector>
#include<memory>

class FilterGeneric {
public:
	FilterGeneric();
	std::vector<int> filter(std::vector<int> list);
private:
	virtual bool g(int x) = 0;                            //定义一个纯虚函数，以便被子类重载
	std::vector<int> _list;                               //_list用于保存结果
};
#endif // !FILTERGENERIC_H

