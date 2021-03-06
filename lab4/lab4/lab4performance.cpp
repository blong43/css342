/*-----------------------------------------------------------------------------
@file    lab4performance.cpp
			Test the functions in each class and make sure that they work
			with any random number amount that they are given.
@authors Blong Thao and Albert Tyshler
@course  CSS 342 Shields
@date    02/23/14
-----------------------------------------------------------------------------*/

#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include "recursivemergesort.h"
#include "iterativemergesort.h"
#include "recursivequicksort.h"
#include "heapsort.h"
#define TEST1_SIZE 100
#define TEST2_SIZE 1000
#define TEST3_SIZE 10000
#define TEST4_SIZE 100000
#define TEST5_SIZE 34
#define RAND_NUMS 500000
#define FIRST_NINE 9
#define REG_SIZE 18
using namespace std;

void run1();
void run2();
void run3();
void run4();
void run5();
void testIterMergeSort(const int);
void testRecurMergeSort(const int);
void testRecurQuickSort(const int);
void testHeapSort(const int);
void initArray(int*, int, int);
void elapsed( timeval&, timeval&);

int main() 
{
	run1();
	run2();
	run3();
	run4();
	run5();
	return 0;
}

/**----------------------- run1 -----------------------------------------------
	Runs the perfomance for each sort, the input values are random numbers;
	with the output of each sort for a size of 100.
-----------------------------------------------------------------------------*/
void run1() {
	cout << "------------------------- RUN1 ----------------------------\n\n";
	testIterMergeSort(TEST1_SIZE);
	testRecurMergeSort(TEST1_SIZE);
	testRecurQuickSort(TEST1_SIZE);
	testHeapSort(TEST1_SIZE);
}

/**----------------------- run2 -----------------------------------------------
	Runs the perfomance for each sort, the input values are random numbers;
	with the output of each sort for a size of 1,000.
-----------------------------------------------------------------------------*/
void run2() {
	cout << "------------------------- RUN2 ----------------------------\n\n";
	testIterMergeSort(TEST2_SIZE);
	testRecurMergeSort(TEST2_SIZE);
	testRecurQuickSort(TEST2_SIZE);
	testHeapSort(TEST2_SIZE);
}

/**----------------------- run3 -----------------------------------------------
	Runs the perfomance for each sort, the input values are random numbers;
	with the output of each sort for a size of 10,000.
-----------------------------------------------------------------------------*/
void run3() {
	cout << "------------------------- RUN3 ----------------------------\n\n";
	testIterMergeSort(TEST3_SIZE);
	testRecurMergeSort(TEST3_SIZE);
	testRecurQuickSort(TEST3_SIZE);
	testHeapSort(TEST3_SIZE);
}

/**----------------------- run4 -----------------------------------------------
	Runs the perfomance for each sort, the input values are random numbers;
	with the output of each sort for a size of 100,000.
-----------------------------------------------------------------------------*/
void run4() {
	cout << "------------------------- RUN4 ----------------------------\n\n";
	testIterMergeSort(TEST4_SIZE);
	testRecurMergeSort(TEST4_SIZE);
	testRecurQuickSort(TEST4_SIZE);
	testHeapSort(TEST4_SIZE);
}

/**----------------------- run5 -----------------------------------------------
	Runs the perfomance for each sort, the input values are random numbers;
	with the output of each sort for a size of 34.
-----------------------------------------------------------------------------*/
void run5() {
	cout << "------------------------- RUN5 -------------------------\n\n";
	testIterMergeSort(TEST5_SIZE);
	testRecurMergeSort(TEST5_SIZE);
	testRecurQuickSort(TEST5_SIZE);
	testHeapSort(TEST5_SIZE);
}

/**----------------- elapsed --------------------------------------------------
	@param startTime The start time.
	@param endTime The end time.
	@pre Start time cannot happen after endtime.
-----------------------------------------------------------------------------*/
void elapsed( timeval &startTime, timeval &endTime ) { // uses <sys/time.h>
   long seconds, microseconds; // milliSecTime,
   seconds  = endTime.tv_sec  - startTime.tv_sec;
   microseconds = endTime.tv_usec - startTime.tv_usec;
   if ( microseconds < 0 ){ 
       microseconds += 1000000 ;  // correct for roll over
   }
   cout << "elapsed time: " << seconds << " sec, " << microseconds
	<< " microsec.\n\n";
}

/**----------------- initArray ------------------------------------------------
	Fills the array with random numbers
	@param array The array the is being filled with random numbers.
	@param randMax The size of the array.
	@pre   Needs a non-negative randMax.
	@post  Array is filled with random numbers.
-----------------------------------------------------------------------------*/
void initArray(int* array, int arraySize, int randMax ) {
	int size = arraySize;

	// stores random numbers into the array
	for ( int index = 0; index < size; index++ )
	{
		// temp makes a random number(non-negative) and stores it
		// hit is a flag that signals if the random number is a duplicate
		int temp = ( randMax == -1 ) ? rand( ) : rand( ) % randMax;

		// stores the random number into the array
		array[index] = temp;
	  }
}

/**---------------- testIterMergeSort -----------------------------------------
	Prints out the test results of the iterative merge sort
	@param size The size of the array being tested.
	@pre Size should not be negative, array contains only integers.
	@post None.
-----------------------------------------------------------------------------*/
void testIterMergeSort(const int size)
{
	srand (size);
	int* test = new int[size];
	initArray(test, size, RAND_NUMS);
	
	cout << "Testing Iterative Merge Sort: \n\n";
	cout << "Test size is: " << size << endl << endl;

	struct timeval startTime, endTime;
	gettimeofday( &startTime, 0 );

	iterMergeSort(size, test);
	
	gettimeofday( &endTime, 0 );
	elapsed( startTime, endTime );

	delete [] test;
}

/**---------------- testRecurMergeSort ----------------------------------------
	Prints out the test results of the recursive merge sort
	@param size The size of the array being tested.
	@pre Size should not be negative, array contains only integers.
	@post None.
-----------------------------------------------------------------------------*/
void testRecurMergeSort(const int size) {
	srand (size);
	int* test = new int[size];
	initArray(test, size, RAND_NUMS);
	
	cout << "Testing Recursive Merge Sort: \n\n";
	cout << "Test size is: " << size << endl << endl;
	
	struct timeval startTime, endTime;
	gettimeofday( &startTime, 0 );

	recurMergeSort(test, 0, size-1);
	
	gettimeofday( &endTime, 0 );
	elapsed( startTime, endTime );

	delete [] test;
}

/**---------------- testRecurQuickSort ----------------------------------------
	Prints out the test results of the recursive quick sort
	@param size The size of the array being tested.
	@pre Size should not be negative, array contains only integers.
	@post None.
-----------------------------------------------------------------------------*/
void testRecurQuickSort(const int size) {
	srand (size);
	int* test = new int[size];
	initArray(test, size, RAND_NUMS);
	
	cout << "Testing Recursive Quick Sort: \n\n";
	cout << "Test size is: " << size << endl << endl;

	struct timeval startTime, endTime;
	gettimeofday( &startTime, 0 );

	quickSort(test, 0, size-1);
	
	gettimeofday( &endTime, 0 );
	elapsed( startTime, endTime );

	delete [] test;
}

/**---------------- testHeapSort ----------------------------------------------
	Prints out the test results of the heap sort.
	@param size The size of the array being tested.
	@pre Size should not be negative, array contains only integers.
	@post None.
-----------------------------------------------------------------------------*/
void testHeapSort(const int size) {
	srand (size);
	int* test = new int[size];
	initArray(test, size, RAND_NUMS);
	
	cout << "Testing Heap Sort: \n\n";
	cout << "Test size is: " << size << endl << endl;

	struct timeval startTime, endTime;
	gettimeofday( &startTime, 0 );

	heapSort(test, size);
	
	gettimeofday( &endTime, 0 );
	elapsed( startTime, endTime );
	
	delete [] test;
}
