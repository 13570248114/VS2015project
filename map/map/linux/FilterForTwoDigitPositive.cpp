#include"FilterForTwoDigitPositive.h"

bool  FilterForTwoDigitPositive::g(int x) {
	return x > 9 && x < 100;                                            //返回一个布尔表达式的结果
}