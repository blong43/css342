/*-----------------------------------------------------------------------------
@file    recursivequicksort.cpp
			The definitions of the the recursive quicksort functions.
@authors Blong Thao and Albert Tyshler
@course  CSS 342 Shields
@date    02/23/14
-----------------------------------------------------------------------------*/

#include "recursivequicksort.h"

/**------------------------------ partition -----------------------------------
	Partitions the array[first..last]
	@param input The given array
	@param left The left most element to consider in the array
	@param right The right most element to consider in the array
	@pre unchanged, unsorted array, input.
	@post finds the final position for the pivot element, which it returns.
-----------------------------------------------------------------------------*/
 int partition(int* input, int left, int right)
 {
	int pivot = input[right];
	while ( left < right )
    {
       while ( input[left] < pivot )
           left++;

       while ( input[right] > pivot )
           right--;

       if ( input[left] == input[right] )
           left++;
       else if ( left < right )
       {
           int tmp = input[left];
           input[left] = input[right];
           input[right] = tmp;
       }
    }
    return right;
}

/**------------------------------ quickSort -----------------------------------
	Sorts an array into ascending order. 
	@param input The given array
	@param first The first element to consider in the array
	@param last The last element to consider in the array
	@pre theArray[first..last] is an array.
	@post theArray[first..last] is sorted.
-----------------------------------------------------------------------------*/
void quickSort(int* input, int first, int last)
{
    if ( first < last )
    {
        int pivotIndex = partition(input, first, last);        
        quickSort(input, first, pivotIndex-1);
        quickSort(input, pivotIndex+1, last);
    }
}
