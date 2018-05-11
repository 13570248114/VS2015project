#include<iostream>
using namespace std;

class A {
public:
	A(int a) :_a(a) {}
	virtual int arithmetic() const{
		return _a;
	}
protected:
	int _a;
};

class B :public A {
public:
	B(int b) :A(b) {}
	int arithmetic() const override {
		return _a*_a;
	}
};

class C :public B {
public:
	C(int c) :B(c) {}
	int arithmetic() const override {
		return _a*_a*_a;
	}
};

class test {
public:
	test() = default;
	void staticallyCall(A* a) {
		cout << a->A::arithmetic() << endl;
	}
	void dynamicallyCall(A *a) {
		cout << a->arithmetic() << endl;
	}
	void threeCall() {
		A *a = new A(3);
		B *b = new B(3);
		C* c = new C(3);
		cout << "A,B,C all have a member variables _a and a virtual member function arithmetic(), \nwhile arithmetic() of A return _a, arithmetic() of B return _a*_a,arithmetic() of C return _a*_a*_a" << endl;
		cout << "In this case , _a = 3 : " << endl;
		cout << "This call is statically bound to A's method:" << endl;
		staticallyCall(a);
		cout << "This call is dynamically bound to B's method:" << endl;
		dynamicallyCall(b);
		cout << "This call is dynamically bound to C's method:" << endl;
		dynamicallyCall(c);
	}
};

int main()
{
	test t;
	t.threeCall();
}