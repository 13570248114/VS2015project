#include<stdio.h>
#include"listIteratorInt.h"

int main() {
	int check;
	IteratorInt it;
	it = IteratorIntNew();
	check = add(it, 7);

	check = add(it, 10);

	check = add(it, 12);

	reset(it);
	check = set(it, 100);
	printf("return : %d\n", check);
	int *n;
	n = findNext(it, 7);
	printf("return : %d\n", *n);


	n = findPrevious(it, 7);
	if (n == NULL) {
		printf("return nULL");
	}
	else {
		printf("return : %d\n", *n);
	}

	n = next(it);
	if (n == NULL) {
		printf("reutrn NULL");
	}
	else {
		printf("return : %d\n", *n);
	}
	freeIt(it);
}