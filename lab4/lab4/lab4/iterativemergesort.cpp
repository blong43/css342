/*-----------------------------------------------------------------------------
@file    iterativemergesort.cpp
			The definition for the merge sort and includes the helper functions
			that help it achieve its sort.
@authors Blong Thao and Albert Tyshler
@course  CSS 342 Shields
@date    02/23/14
-----------------------------------------------------------------------------*/

#include "iterativemergesort.h"

/**-------------------------- iterMergeSort -----------------------------------
	@param theSize The size of the array that is being sorted.
	@param sort The array that is to be sorted.
	@param theTemp The array that is being used to store temporary data in.
	@pre The sort array has to have elements in it to be sorted.
	@post None.
-----------------------------------------------------------------------------*/
void iterMergeSort(int theSize, int* sort) 
{
	int* theTemp = new int[theSize];

	// sets the number for how large each section should be:
	// 2, 4, 8, . . ., until the array is sorted
	for (int section = 1; section < theSize; section *= 2) 
	{
		// keeps counts of each section until it hits the end of unsorted array
		for (int count = 0; count < theSize; count += 2 * section)
		{
			// merge the sections from the toSort array to the temp array 
			iterMerge(sort, theTemp, count, min( count + section, theSize ),
				min( count + 2*section, theSize ) );
		}
		// alternates the source and destination of the merge
		swapArrays(sort, theTemp, theSize);
	}
	delete [] theTemp;
}

/**-------------------------- iterMerge ---------------------------------------
	@param sort The array that needs to be sorted.
	@param theTemp The array that holds temporary values.
	@param left The beginning of the left section.
	@param right The beginning of the right section.
	@param end The end of the array.
	@pre Each of the int parameters cannot be a negative value, or larger than
			the size of the array.
	@post None.
-----------------------------------------------------------------------------*/ 
void iterMerge(int* sort, int* theTemp, int left, int right, int end)
{
	//walker for the left and right array sections
	int curLeft = left;
	int curRight = right;
	
	//while there are values in the left or right sections
	for (int index = left; index < end; index++)
	{
		//when the left index is less than the right index and curRight has not 
		//yet gone past the "end," OR the curRight index value is greater than
		//curLeft index value the comparison of left and right sections begin
		if (curLeft < right && (curRight >= end || 
			sort[curLeft] <= sort[curRight]) )
		{
			theTemp[index] = sort[curLeft];
			curLeft++;
		}
		//otherwise, the curRight index value gets inserted into the temp array
		else
		{
			theTemp[index] = sort[curRight];
			curRight++;
		}
	}
}

/**-------------------------- copyArray ---------------------------------------
	@param sort The array that is copying over the temporary data.
	@param theTemp The array that has the sorted data.
	@param theSize The size of the sort array.
	@pre None.
	@post None.
-----------------------------------------------------------------------------*/
void swapArrays(int* sort, int* theTemp, int theSize)
{
	for (int index = 0; index < theSize; index++) {
		int swapIdx = theTemp[index];
		theTemp[index] = sort[index];
		sort[index] = swapIdx;
	}
}
