#ifndef  MAP_H
#define MAP_H
#include<vector>
#include<memory>

class  MapGeneric {
public:
	MapGeneric();
	std::vector<int> map(std::vector<int> list);
private:
	virtual int f(int x) = 0;                        //����һ�����麯�����Ա㱻��������
	std::vector<int> _list;                           //_list���ڱ�����
};
#endif // ! MAP_H

