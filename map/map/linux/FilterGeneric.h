#ifndef FILTERGENERIC_H
#define FILTERGENERIC_H
#include<vector>
#include<memory>

class FilterGeneric {
public:
	FilterGeneric();
	std::vector<int> filter(std::vector<int> list);
private:
	virtual bool g(int x) = 0;                            //����һ�����麯�����Ա㱻��������
	std::vector<int> _list;                               //_list���ڱ�����
};
#endif // !FILTERGENERIC_H

