
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include <iterator>  
using namespace std;

template<typename I>
int a(I f, I l)
{
	int r = 0;
	for (;f != l; ++f)
		r += *f;
	return r;
}

template<typename I>
int* a_d(I f, I l)
{
	int *r = new int[l - f];
	*r = *f;
	int va = *f;
	while (++f != l)
	{
		int t = *f;
		*++r = t - va;
		va = t;
	}
	return ++r;
}

template<typename I>
int ip(I f, I l)
{
	int r =0;
	for (;f != l;++f)
	{
		r += (*f**f);
	}
	return r;
}

template<typename I>
int* ps(I f, I l)
{
	int *r = new int[l - f];
	*r = *f;
	int va = *f;
	while (++f != l)
	{
		va = va + *f;
		*++r = va;
	}
	return ++r;
}

template<typename I>
void p(I f, I l)
{
	for (;f != l;++f)
		cout << *f << "\t";
	cout << endl;
	
}

template<typename I>
int power(I x, int n)
{
	while ((n & 1) == 0) {
		n >>= 1;
		x = x*x;
	}

	int r = x;
	n >>= 1;
	while (n != 0) {
		x = x*x;
		if ((n & 1) != 0)
			r = r*x;
		n >>= 1;
	}
	return r;
}

template<typename I>
bool e(I f1, I e, I f2) {
	for (;f1 != e;f1++, f2++)
		if (*f1 != *f2)
			return false;
	return true;
}

inline char* copy(char *f, char *l, char *r)
{
	memmove(r, f, l - f);
	return r + (l - f);
}

template<typename I, typename O>
O u(I f1, I e1, I f2, I e2, O r) {
	while (f1 != e1&&f2 != e2)
	{
		if (*f1 < *f2) {
			*r = *f1;
			++f1;
		}
		else if (*f2 < *f1) {
			*r = *f2;
			++f2;
		}
		else {
			*r = *f1;
			++f1, ++f2;
		}
		++r;
	}
	return copy(f1, e1, copy(f2, e2, r));
}

template<typename I, typename O>
O i(I f1, I e1, I f2, I e2, O r) {
	while (f1 != e1&&f2 != e2)
	{
		if (*f1 < *f2) {
			++f1;
		}
		else if (*f2 < *f1) {
			++f2;
		}
		else {
			*r = *f1;
			++f1, ++f2;
			++r;
		}
		
	}
	return r;
}

template<typename I, typename O>
O d(I f1, I e1, I f2, I e2, O r) {
	while (f1 != e1&&f2 != e2)
	{
		if (*f1 < *f2) {
			*r = *f1;
			++f1;
			++r;
		}
		else if (*f2 < *f1) {
			++f2;
		}
		else {
			++f1, ++f2;
		}
	}
	return copy(f1, e1,r);
}

template<typename I>
I af(I f, I e) {
	I n = f;
	while (++n != e)
	{
		if (*f == *n)
			return f;
		f = n;
	}
	return e;
}

template<typename I>
I f(I f, I e, int v) {
	while (f != e&&*f != v)
		++f;
	return f;
}

template<typename I>
I fe1(I f, I e, I f1,I e1) {
	I r =e;
	while (1) {
		I nr = search(f, e, f1, e1);
		if (nr == e)
			return r;
		else
		{
			r = nr;
			f = nf;
			++f;
		}
	}
}

template<typename I>
bool in(I f, I e, I f1, I e1) {
	while (f1 != e1&&f != e)
	{
		if (*f1 < *f)
			return false;
		else if (*f < *f1)
			++f;
		else
			++f, ++f1;
	}
	return f1 == e1;
}

template<typename I, typename O>
O in(I f, I e, I f1, I e1,O o) {
	while (f1 != e1&&f != e)
	{
		if (*f1 < *f)
			*o = *f1, ++f1;
		else
			*o=*f, ++f;
		++o;
	}
	return copy(f1,e1,copy(f,e,o));
}

template<typename I>
I pa(I f, I e) {
	while (true)
	{
		while (true)
		{
			if (f == e)
				return f;
			else if ((*f) % 2 == 1)
				++f;
			else
				break;
		}

		--e;
		while (true)
		{
			if (f == e)
				return f;
			else if (*e % 2 == 0)?
				--e;
			else
				break;
		}

		iter_swap(f, e);
		++f;
	}
}

template<typename I>
I low(I f, I e, int v)
{
	int len = e - f;
	int h;
	I m;

	while (len > 0) {
		h = len >> 1;
		m = f;
		advance(m, h);
		if (*m < v)
		{
			f = m;
			++f;
			len = len - h - 1;
		}
		else
			len = h;
	}
	return f;
}

template<typename I>
I up(I f, I e, int v)
{
	int len = e - f;
	int h;
	I m;

	while (len > 0) {
		h = len >> 1;
		m = f;
		advance(m, h);
		if (*m > v)
		{
			len = h;
		}
		else
		{
			f = m;
			++f;
			len = len - h - 1;
		}
	}
	return f;
}

template<typename I>
bool np(I f, I e)
{
	if (f == e)
		return false;
	I i = f;
	++i;
	if (i == e)
		return false;
	i = e;
	--i;

	while (true)
	{
		I ii = i;
		--i;
		if (*i < *ii)
		{
			I j = e;
			while (!(*i < *--j));
			iter_swap(i, j);
			reverse(ii, e);
			return true;
		}

		if (i == f)
		{
			reverse(f, e);
			return false;
		}
	}
}

template<typename I>
bool pp(I f, I e)
{
	if (f == e)
		return false;
	I i = f;
	++i;
	if (i == e)
		return false;
	i = e;
	--i;

	while (true)
	{
		I ii = i;
		--i;
		if (*i > *ii)
		{
			I j = e;
			while (!(*--j >*i));
			iter_swap(i, j);
			reverse(ii, e);
			return true;
		}

		if (i == f)
		{
			reverse(f, e);
			return false;
		}
	}
}

template<typename I>
void pas(I f, I m, I e)
{
	make_heap(f, m);
	for(I i=m;i<e;i++)
		if()
}

int main()
{
	int ai[6] = { 1,2,3,4,5,6 };
	int aj[3] = { 6,7,8 };
	vector<int> v(ai, ai + 6);
	vector<int> v1(aj, aj + 3);
	//cout << a(v.begin(), v.end()) << endl;
	//int *r = a_d(v.begin(), v.end());
	//cout << *(r - (v.end() - v.begin())) << endl;
	//cout << ip(v.begin(), v.end()) << endl;
	//int *r = ps(v.begin(), v.end());
	//int len = v.end() - v.begin();
	//p(r - len, r);
	//cout << power(2, 5) << endl;
	//cout << e(v.begin()+1, v.end(), v.begin()) << endl;
	//char c1[5] = { '1','2','3','4','5' };
	//char c2[5] = { '2','2','3','4','5' };
	//copy(c2, c2 + 5, c1);
	//p(c1, c1 + 5);
	//vector<int> r(10);
	//auto it = u(v.begin(), v.end(), v1.begin(), v1.end(), r.begin());
	//p(r.begin(), r.end());
	//r.erase(it, r.end());
	//p(r.begin(), r.end());
	//i(v.begin(), v.end(), v1.begin(), v1.end(), r.begin());
	//p(r.begin(), r.end());
	//d(v.begin(), v.end(), v1.begin(), v1.end(), r.begin());
	//p(r.begin(), r.end());
	//cout << *af(v.begin(), v.end()) << endl;
	//pa(v.begin(), v.end());
	//p(v.begin(), v.end());
	//auto i = up(v.begin(), v.end(), 3);
	//cout << *i<< endl;
	while(np(v1.begin(), v1.end()))
		p(v1.begin(), v1.end());
}
