/*-----------------------------------------------------------------------------
@file    recursivemergesort.cpp
			The definitions of the recursive merge sort functions.
			Credits to Frank M. Carrano, in his book:
			Data Abstraction & Problem Solving with C++ On page 317.
@authors Blong Thao and Albert Tyshler
@course  CSS 342 Shields
@date    02/23/14
-----------------------------------------------------------------------------*/

#include "recursivemergesort.h"
#define MAX_SIZE 100000

/**-------------------------- recurMergeSort --------------------------------------------
	Sorts the items in an array into ascending order
	@param theArray The given array being passed in
	@param first The index of the first element to consider in theArray
	@param last The index of the last element to consider in theArray
	@pre theArray[first..last] is an array
	@post theArray[first..last] is sorted in ascending order
-----------------------------------------------------------------------------*/
void recurMergeSort(int* theArray, int first, int last) 
{
	if(first < last)
	{
		int mid = first + (last - first)/2;

		recurMergeSort(theArray, first, mid);

		recurMergeSort(theArray, mid + 1, last);

		recurMerge(theArray, first, mid, last);
	}
}

/**-------------------------- recurMerge -------------------------------------------
	Merges 2 sorted array segments into one sorted array
	@param theArray The given array being passed in
	@param first The index of the beginning of the first segment in theArray
	@param mid The index of the end of the first segment in  theArray
	@param last The index of the last element in the second segment in theArray
	@pre first <= mid <= last. The subarrays theArray[first..mid] and 
		theArray[mid+1..last] are each sorted in increasing order.
	@post theArray[first..last] is sorted
-----------------------------------------------------------------------------*/ 
void recurMerge(int* theArray, int first, int mid, int last)
{
	int temp[MAX_SIZE];

	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;

	int index = first1;
	while ((first1 <= last1) && (first2 <= last2))
	{
		if (theArray[first1] <= theArray[first2])
		{
			temp[index] = theArray[first1];
			first1++;
		}
		else
		{
			temp[index] = theArray[first2];
			first2++;
		}
		index++;
	}

	while (first1 <= last1)
	{
		temp[index] = theArray[first1];
		first1++;
		index++;
	}

	while (first2 <= last2)
	{
		temp[index] = theArray[first2];
		first2++;
		index++;
	}

	for (index = first; index <= last; index++)
		theArray[index] = temp[index];
}
