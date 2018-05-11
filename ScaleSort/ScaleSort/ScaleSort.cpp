#include<vector>
#include<iostream>
using namespace std;

class ScaleSort {
public:
	vector<int> sortElement(vector<int> A, int n, int k) {
		// write code here
		if (A.size() < k)
			return A;
		vector<int> heap = getKHeap(A, k);
		for (int i = k; i < n; i++)
		{
			A[i - k] = heap[0];
			heap[0] = A[i];
			adjustHeap(heap, 0, k - 1);
		}
		for (int i = n - k; i < n; i++)
		{
			A[i] = heap[0];
			swap(heap, 0, k - 1);
			k--;
			adjustHeap(heap, 0, k - 1);
		}
		return A;
	}
private:
	void swap(vector<int>& A, int i, int j)
	{
		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}

	void adjustHeap(vector<int>& A, int left, int right)
	{
		int parent = left;
		int minChild = 2 * parent + 1;
		int value = A[parent];

		while (minChild <= right)
		{
			minChild =  minChild < right&& A[minChild + 1] < A[minChild] ? minChild + 1 : minChild;
			if (value > A[minChild])
			{
				A[parent] = A[minChild];
				parent = minChild;
				minChild = 2 * parent + 1;
			}
			else
				break;
		}
		A[parent] = value;
	}

	vector<int> getKHeap(vector<int> A, int k)
	{
		vector<int> heap;
		for (int i = 0; i < k; i++) {
			heapInsert(heap, A[i]);
		}
		return heap;
	}

	void heapInsert(vector<int>& heap, int value)
	{
		heap.push_back(value);
		int index = heap.size() - 1;
		while (index != 0) {
			int parent = (index-1) / 2;
			if (heap[parent] > heap[index]) {
				swap(heap, index, parent);
				index = parent;
			}
			else
				break;
		}
	}

};

int main()
{
	ScaleSort sort;
	vector<int> a{ 1,3,2,4 };
	a = sort.sortElement(a, a.size(), 2);
	for (auto i : a)
		cout << i << endl;
}