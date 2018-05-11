#include<iostream>
using namespace std;
/*
void merge(int* A, int left, int mid, int right)
{
	int* temp = new int[right - left + 1];
	int l = left;
	int r = mid + 1;
	int k = 0;
	while (l <= mid&&r <= right)
	{
		if (A[l] <= A[r])
		{
			temp[k++] = A[l++];
		}
		else
			temp[k++] = A[r++];
	}
	while (l <= mid)
		temp[k++] = A[l++];
	while (r <= right)
		temp[k++] = A[r++];
	for (int i = 0;i<k;i++)
		A[left + i] = temp[i];
}

void mergeSort(int* A, int left, int right)
{
	if (left == right)
		return;
	int mid = (left + right) / 2;
	mergeSort(A, left, mid);
	mergeSort(A, mid + 1, right);
	merge(A, left, mid, right);
	return;
}

int* mergeSort(int* A, int n) {
	// write code here
	mergeSort(A, 0, n - 1);
	return A;
}
*/

void max_min(int* A, int n, int& max, int& min)
{
	max = min = A[0];
	for (int i = 1; i < n; i++)
	{
		if (A[i]<min)
			min = A[i];
		else if (A[i]>max)
			max = A[i];
	}
}

int* countingSort(int* A, int n) {
	// write code here
	if (A == nullptr || n < 2)
		return A;
	int max, min;
	max_min(A, n, max, min);
	int* tong = new int[max - min + 1];
	for (int i = 0;i < max - min + 1;i++)
		tong[i] = 0;
	for (int i = 0; i < n; i++)
		tong[A[i] - min]++;
	int index = 0;
	for (int i = 0; i< max - min + 1; i++)
		while (tong[i] > 0)
		{
			A[index++] = i + min;
			tong[i]--;
		}
	return A;
}

int main()
{
	int a[5] = { 2,3,1,5,4 };
	countingSort(a, 5);
	int i = 0;
	while (i < 5)
		cout << a[i++] << endl;
}
