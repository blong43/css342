/*-----------------------------------------------------------------------------
@file    heapsort.cpp
			Definitions of heap sort's functions.
@authors Blong Thao and Albert Tyshler
@course  CSS 342 Shields
@date    02/23/14
-----------------------------------------------------------------------------*/

#include "heapsort.h"
#include <cassert>

/**----------------------- shiftRight -----------------------------------------
	Keeps shifting right and ensure that swapIdx satisfies the left and
		right child of it is smaller than itself
	@param arr The given array being passed in
	@param low, high The lowest and highest values
	@pre arr is an unsorted portion for the array
	@post returns back to heapify to continue the operation
-----------------------------------------------------------------------------*/
void shiftRight(int* arr, int low, int high)
{
    int root = low;
	bool stop = false;
    while ( ((root*2)+1 <= high) && !stop )
    {
        int leftChild = (root * 2) + 1;
        int rightChild = leftChild + 1;
        int swapIdx = root;
        /*Check if root is less than left child*/
        if (arr[swapIdx] < arr[leftChild])
        {
            swapIdx = leftChild;
        }
        /*If right child exists check if it is less than current root*/
        if ((rightChild <= high) && (arr[swapIdx] < arr[rightChild]))
        {
            swapIdx = rightChild;
        }
        /*Make the biggest element of root, left and right child the root*/
        if (swapIdx != root)
        {
            int tmp = arr[root];
            arr[root] = arr[swapIdx];
            arr[swapIdx] = tmp;
            /*Keep shifting right and ensure that swapIdx satisfies
            heap property aka left and right child of it is smaller than
            itself*/
            root = swapIdx;
        }
        else
        {
            stop = true;
        }
    }
    return;
}

/**----------------------- heapify --------------------------------------------
	works with the shitRight method to move the values within the tree
	@param arr The given array being passed in
	@param low, high The lowest and highest values are used to calulate
		the middle element which is then passed to shiftRight
	@pre arr is an unsorted portion for the array
	@post arr is a sorted portion of the array
-----------------------------------------------------------------------------*/
void heapify(int* arr, int low, int high)
{
    /*Start with middle element. Middle element is chosen in
    such a way that the last element of array is either its
    left child or right child*/
    int midIdx = (high - low -1)/2;
    while (midIdx >= 0)
    {
        shiftRight(arr, midIdx, high);
        --midIdx;
    }
    return;
}

/**----------------------- heapsort -------------------------------------------
	Sorts the items in an array into ascending order
	@param arr The given array being passed in
	@param size The size of the passed in array
	@pre arr is an unsorted array
	@post arr is sorted in ascending order
-----------------------------------------------------------------------------*/
void heapSort(int* arr, int size)
{
    assert(arr);
    assert(size > 0);
    /*This will put max element in the index 0*/
    heapify(arr, 0, size-1);
    int high = size - 1;
    while (high > 0)
    {
        /*Swap max element with high index in the array*/
        int tmp = arr[high];
        arr[high] = arr[0];
        arr[0] = tmp;
        --high;
        /*Ensure heap property on remaining elements*/
        shiftRight(arr, 0, high);
    }
    return;
}
