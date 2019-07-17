/********************************************************************************************
**	Project: Sort
**  Programmer: Kyle Miller
**  Course:		cs2420
**	Section:	002
**	Assignment: 5
**	Data:		June 29 2019
**
**	I certify that I wrote all code in this project except that which was
**	provided by the instructor.
**
***********************************************************************************************/

#include <iostream>
#include "Sort.h"
#include "Timer.h"

using namespace std;

// used for Unit Testing. DO NOT REMOVE
int RecursionCounter::currentDepth = 0;
int RecursionCounter::maxDepth = 0;


void TestSelectionSort(Sort& sort) {
	Timer ti;
	sort.Print();
	ti.Start();
	sort.SelectionSort();
	ti.End();
	sort.Print();
	cout << "Selection Sort of " << sort.GetSize() << " items "
		<< "took " << ti.DurationInNanoSeconds() << "ns" << endl;
	cout << endl;
}

void TestInsertionSort(Sort& sort) {
	Timer ti;
	sort.Print();
	ti.Start();
	sort.InsertionSort();
	ti.End();
	sort.Print();
	cout << "Insertion Sort of " << sort.GetSize() << " items "
		<< "took " << ti.DurationInNanoSeconds() << "ns" << endl;
	cout << endl;
}

void TestAlgorithmSort(Sort& sort) {
	Timer ti;
	sort.Print();
	ti.Start();
	sort.AlgorithmSort();
	ti.End();
	sort.Print();
	cout << "std::sort() Sort of " << sort.GetSize() << " items "
		<< "took " << ti.DurationInNanoSeconds() << "ns" << endl;
	cout << endl;
}

void TestMergeSort(Sort& sort) {
	Timer ti;
	sort.Print();
	ti.Start();
	sort.MergeSort();
	ti.End();
	sort.Print();
	cout << "Merge Sort of " << sort.GetSize() << " items "
		<< "took " << ti.DurationInNanoSeconds() << "ns" << endl;
	cout << endl;
}

void TestQuickSort(Sort& sort) {
	Timer ti;
	sort.Print();
	ti.Start();
	sort.QuickSort();
	ti.End();
	sort.Print();
	cout << "Quick Sort of " << sort.GetSize() << " items "
		<< "took " << ti.DurationInNanoSeconds() << "ns" << endl;
	cout << endl;
}

int main() {
	Timer ti;

	//Sort sort(10);
	//sort.Print();
	//Sort sort1(10);
	//Sort sort2(100000);
	//Sort sort3(1000000);
	//Sort sort4(100000);


	//These will print the before and after arrays w/ time values
	//TestMergeSort(sort);
	//TestAlgorithmSort(sort1);
	//TestSelectionSort(sort2);
	//TestInsertionSort(sort3);
	//TestQuickSort(sort4);

	//test for stack overflow with large input arrays
	for (int i = 500; i < 100'000'000; i += i) {
		Sort sort3(i);
		cout << "starting Quick Sort() of " << i << "elements" << endl << "Quick Sort duration: ";
		ti.Start();
		sort3.QuickSort();
		ti.End();
		cout << ti.DurationInMilliSeconds() << "ms." << endl << endl;
	}

	// comment out any part of this output as necessary, it is for the ouput
	//portion of the zylabs assignment
	/*
	cout << "starting SelectionSort" << endl << "Selection Sort duration: ";
	ti.Start();
	sort.SelectionSort();
	ti.End();
	cout << ti.DurationInMilliSeconds() << "ms." << endl << endl;
	
	cout << "starting InsertionSort" << endl << "Insertion Sort duration: ";
	ti.Start();
	sort1.InsertionSort();
	ti.End();
	cout << ti.DurationInMilliSeconds() << "ms." << endl << endl;
	

	cout << "starting Merge Sort()" << endl << "Merge Sort duration: ";
	ti.Start();
	sort2.MergeSort();
	ti.End();
	cout << ti.DurationInMilliSeconds() << "ms." << endl << endl;


	cout << "starting Quick Sort()" << endl << "Quick Sort duration: ";
	ti.Start();
	sort3.QuickSort();
	ti.End();
	cout << ti.DurationInMilliSeconds() << "ms." << endl << endl;


	cout << "starting std::sort()" << endl << "std::sort() duration: ";
	ti.Start();
	sort4.AlgorithmSort();
	ti.End();
	cout << ti.DurationInMilliSeconds() << "ms." << endl << endl;
	*/
	return 0;
}