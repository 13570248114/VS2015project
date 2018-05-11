#ifndef  MAP_H
#define MAP_H
#include<vector>
#include<memory>

class  MapGeneric {
public:
	MapGeneric();
	std::vector<int> map(std::vector<int> list);
private:
	virtual int f(int x) = 0;                        //定义一个纯虚函数，以便被子类重载
	std::vector<int> _list;                           //_list用于保存结果
};
#endif // ! MAP_H

