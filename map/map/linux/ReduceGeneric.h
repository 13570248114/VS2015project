#ifndef REDUCEGENERIC_H
#define REDUCEGENERIC_H
#include<vector>

class ReduceGeneric {
public:
	ReduceGeneric();
	std::vector<int> reduce(std::vector<int> list);
private:
	virtual int binaryOperator(int x,int y) = 0;                  //定义一个纯虚函数，以便被子类重载
	std::vector<int> _list;                                       //_list用于保存结果
};
#endif // !REDUCEGENERIC_H

