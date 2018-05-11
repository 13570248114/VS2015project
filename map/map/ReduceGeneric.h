#ifndef REDUCEGENERIC_H
#define REDUCEGENERIC_H
#include<vector>

class ReduceGeneric {
public:
	ReduceGeneric();
	std::vector<int> reduce(std::vector<int> list);
private:
	virtual int binaryOperator(int x,int y) = 0;                  //����һ�����麯�����Ա㱻��������
	std::vector<int> _list;                                       //_list���ڱ�����
};
#endif // !REDUCEGENERIC_H

