#ifndef __SORT__
#define __SORT__

#include "RecursionCounter.h"

class Sort
{
public:
	Sort(int size);
	~Sort();

	void InitArray();

	void SelectionSort();
	void InsertionSort();
	void AlgorithmSort();
	void MergeSort();
	void QuickSort();

	void Print();

	int GetSize() const { return size; }
	int* GetDataArray() const { return myArray; }

private:
	int* myArray;
	int size;

	
	void MergeSortRecursionHelper(int low, int high);
	void QuickSortRecursionHelper(int initialLowIndex, int initialHighIndex);
	int QuickSortPartition(int Low, int High);
	void Merge(int low, int mid, int high);
};

#endif
