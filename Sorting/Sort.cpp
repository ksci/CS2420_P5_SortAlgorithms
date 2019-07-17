#include <random>
#include <algorithm>
#include "Sort.h"
#include <iostream>

using namespace std;

//create the Sort object
Sort::Sort(int size) {
	this->size = size;
	myArray = new int[size];
	InitArray();
}

//delete the array
Sort::~Sort() {
	delete[] myArray;
	myArray = nullptr;
}

//create the array
void Sort::InitArray() {
	if (size > 0) {
		srand(0);											//constant seed for random number generator gives repeatable results
		int i;
		myArray[0] = rand() % 100000;							//start the array

		for (i = 1;  i < size; i++) {								//fill the array with random integers
			myArray[i] = (rand() % 100000);
		}
	}
}

//Print the array
void Sort::Print() {
	int i;
	int max = this->size;
	for (i = 0; i < max; i++) {
		cout << myArray[i];
		if (max - i > 1) {
			cout << ", ";
		}
	}
	cout << endl;
}

//selection sort works by scanning the array for the largest number
//then swapping that into the last array position.  Repeat until the array
//is sorted.  This runs in time O(n^2)
void Sort::SelectionSort() {
	int i;
	int j;
	int temp;
	for (i = size - 1; i >= 0; i--) {
		int max = 0;
		for (j = 0; j <= i; j++) {
			if (myArray[j] > max) {
				max = myArray[j];
				temp = j;
				
			}
		}
		myArray[temp] = myArray[i];
		myArray[i] = max;
	}

}

//insertion sort works by scannning the next element in an array and seeing if
//it is bigger than the previous element.  If it isn't then we store that to temp
//memory and move the list down (to the right) until we find the correct place to insert it.
void Sort::InsertionSort() {
	int temp = 0;
	int i;
	for (i = 1; i < this->size; i++) {
		int j = i;
		temp = myArray[i];
		while (temp < myArray[j - 1]) {
			myArray[j] = myArray[j - 1];
			j--;
		}
		myArray[j] = temp;
	}
}

//uses the built in sort function from algorithm
void Sort::AlgorithmSort() {
	sort(myArray, myArray+size);
}


///<summary>
///For Merge Sort I combined ideas I found in both the book and some online resources
///The challenge was writing an algorithm that, well, worked.  While the books version
///was functional at producing the divide and conquer numbers, it seemed to be unable to
///produce accurate Merging.  I incorporated the 'mid' variable to more easily keep track of
///where I was at in the algorithm
///</summary>

//Merge sort splits the list in half recursively until it is basically just swapping
//smaller groups.  It should have performance of O(n log n).  Uses the recursive helper
//and MergeSort to help with it
void Sort::MergeSort() {

	MergeSortRecursionHelper(0, size-1);
}

//divide and conquer the array and find the low to high points over
//which we are going to merge
void Sort::MergeSortRecursionHelper(int low, int high)
{
	RecursionCounter rcTmp;	// used for Unit Testing. DO NOT REMOVE

	int mid;

	if (high > low) {
		mid = (low + high) / 2;

		MergeSortRecursionHelper(low, mid);
		MergeSortRecursionHelper(mid+1, high);

		Merge(low, mid, high);
	}
}

//Takes the subarrays and merges them into a new temporary array which is then copied to the
//original array.  Compares the subarrays element by element and places the smaller one
//into the temp array first.
void Sort::Merge(int low, int mid, int high) {
	//cout << "Merge called with " << low << " " << high << endl;  //for testing purposes

	int* temp;						//pointer to the temporary array
	int copied = 0;					//total elements copied, should never be more than teh size of temp array
	int copied1 = low;				//number of elements copied from array1, should never be more than mid-low (left half of array)
	int copied2 = mid + 1;			//number of elements copied from array2, should never be more than high - mid+1 (right half of array)
	int i;							//iterator
	int length = high - low + 1;	//length of temp array

	temp = new int[length];			//Allocate the temporary array

	//Merge the elements from subarray1 and subarray2 into a temporary array
	while ((copied1 <= mid) && (copied2 <= high)) {			//Merge the arrays as long as there are still elements in one of the arrays
		if (myArray[copied1] < myArray[copied2]) {
			temp[copied++] = myArray[copied1++];			//place the value of myArray[copied1] into temp[copied], simultaneously increment both
		}
		else {
			temp[copied++] = myArray[copied2++];
		}
	}

	//add the remaining elements left from either of the subarrays
	while (copied1 <= mid) {
		temp[copied++] = myArray[copied1++];
	}
	while (copied2 <= high) {
		temp[copied++] = myArray[copied2++];
	}

	//copy temp array to the original array
	for (i = 0; i < length; i++) {
		*(myArray + low + i) = temp[i];
	}

	delete[] temp;						//Free up heap memory from temp array
	temp = nullptr;

	//this->Print();					//for testing purposes
}



//The main benefit of this version of Quick Sort over the one I made
//originally is that this one does not require you to make and delete
//temporary arrays
void Sort::QuickSort() {
	QuickSortRecursionHelper(0, size - 1);
}

//Because the recursion occurs AFTER the partition is calculated, this 
//leads to a stack overflow MUCH sooner than Merge Sort.  Additionally, since the pivot starts on 
//right most element, if the list is nearly sorted then it has to recurse through
//the entire list, not cutting it in half.  This means the recursion depth ends up being 
//nearly the length of the whole list!
void Sort::QuickSortRecursionHelper(int initialLow, int initialHigh) {
	//RecursionCounter rcTmp;	// used for Unit Testing. DO NOT REMOVE
	//cout << endl << "QuickSort called on elements " << initialLow << " " << initialHigh << endl;
	//this->Print();
	int pi;
	if (initialLow < initialHigh) {
		pi = QuickSortPartition(initialLow, initialHigh);
		//this->Print();
		QuickSortRecursionHelper(initialLow, pi - 1);
		QuickSortRecursionHelper(pi + 1, initialHigh);
	}

}

//There is a lot of overhead here which can lead to stack overflow.  Have a wide range of numbers
//compared to length of array, or consider changing the pivot to the middle value of the dataset
int Sort::QuickSortPartition(int initialLow, int initialHigh) {
	int pivot = myArray[initialHigh];			//the pivot is created from the right most element of the array
	int tempNum;
	int tooHighIndex = initialLow;
	int tooLowIndex = initialHigh-1;
	bool stillRoom = true;
	
	while (stillRoom) {
		//this->Print();
		//These while loops go through the array and look for values that are above and below the pivot
		while ((tooHighIndex < initialHigh) && (myArray[tooHighIndex] <= pivot)) {
			tooHighIndex++;
		}
		while ((tooLowIndex > initialLow) && (myArray[tooLowIndex] > pivot)) {
			tooLowIndex--;
		}
		if (tooHighIndex < tooLowIndex) {					//The L/R pointers have not crossed, swap the values
			tempNum = myArray[tooHighIndex];
			myArray[tooHighIndex] = myArray[tooLowIndex];
			myArray[tooLowIndex] = tempNum;
		}
		else {												//The pointers ahve crossed
			stillRoom = false;
			myArray[initialHigh] = myArray[tooHighIndex];
			myArray[tooHighIndex] = pivot;
		}
	}
	return tooHighIndex;
}


/* MILLER QUICK SORT (10x slower)
//Quick Sort is another divide and conquer technique.  We create a pivot
//point and sort the array left and right around that pivot point.
//The pivot point is taken from the last element in the array
//This Miller version involves temp arrays and is about 10x slower than it should be
void Sort::MillerQuickSort() {
	QuickSortRecursionHelper(0, size - 1);
}

//This is the recursive part of Quick Sort
void Sort::MillerQuickSortRecursionHelper(int initialLow, int initialHigh)
{
	RecursionCounter rcTmp;	// used for Unit Testing. DO NOT REMOVE
	//cout << endl << "QuickSort called on elements " << initialLow << " " << initialHigh << endl;
	//this->Print();

	if (initialLow < initialHigh){
		int pi = QuickSortPartition(initialLow, initialHigh);
		//this->Print();
		QuickSortRecursionHelper(initialLow, pi-1);
		QuickSortRecursionHelper(pi + 1, initialHigh);
	}

}

//this is the meat of the Quick Sort algorithm and it partitions the 
//array around the pivot point
int Sort::MillerQuickSortPartition(int initialLow, int initialHigh) {
	//This one took me quite awhile to figure out and eventually I had to use cards on a table
	//to work through the logic.  What makes it tricky is that the temp array we make needs
	//to be copied to the correct indices of the original array and it was difficult to
	//put it in the right spot at first.
	
	int length = initialHigh - initialLow + 1;
	int lowPtr = 0;
	int highPtr = length - 1;

	int pivot = myArray[initialHigh];
	int* tempArr = new int[length];
	int temp = pivot;

	for (int i = initialLow; i < initialHigh; i++) {
		if (myArray[i] <= pivot) {
			tempArr[lowPtr++] = myArray[i];
		}
		if (myArray[i] > pivot) {
			tempArr[highPtr--] = myArray[i];
		}
	}
	tempArr[lowPtr] = temp;

	//copy the temp array to the correct location in the original array
	for (int i = initialLow; i < length + initialLow; i++) {
		myArray[i] = tempArr[i - initialLow];
	}
	//garbage collection
	delete[] tempArr;
	tempArr = nullptr;
	//return the correct location of the pivot relative to the original array
	return lowPtr + initialLow;
}
*/