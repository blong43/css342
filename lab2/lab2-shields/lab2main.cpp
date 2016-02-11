/**----------------------------------------------------------------------------
	@file lab2main.cpp
		  Test the constructors, operators, and functions of the SortSet
		  (Array and Linked List) implementations.
	@author Blong Thao and Albert Tyshler
	@course CSS 342 Shields
	@version 01/26/14
-----------------------------------------------------------------------------*/

#include <iostream>
#include <ctime>
#include "sortsetarray.h"
#include "sortsetlist.h"
using namespace std;

/**----------------------------------------------------------------------------
	Time and Space Comparison:
	-- The array based implementation of the SortSet ADT finds primes quicker
	   and doesn't create too much pointers to do it all. 
	   (2.1 seconds to run all its functions via typescript)
	-- The linked list based implemenation of the SortSet ADT finds primes in
	   an O(n^2) time due to lots of method calls that occur in the function.
	   In addition, the list version needs to add nodes instead of already
	   creating a list that has boolean values.
	   (263.95 seconds to run all its functions via typescript)
	-- The array implmentation overall is quicker in find primes, but takes
	   up a bit more space than the linked list implementation because the array
	   implemenation creates the array of n size and fills it up with false values
	   until proven true, meaning in the set.
	   (Around 16 allocs per run via previous runs with only array)
	-- The linked list implementation seems to allocate more pointers, but takes
	   up less space because it does not make unneccessary spot holders like the
	   array implementation does.
	   (Over 9000+ allocs per run via previous runs with only LL)
-----------------------------------------------------------------------------*/

int fibonacciIter(const int);
void clockElapsed(clock_t, clock_t);

// these variables control the Fib and Primes that the SortSets go up to;
// change these to fit your computer capabilities
const int DEFAULT_SIZE = 30;
const int MAX_SIZE = fibonacciIter(30);

int main() {
	// sets the timer for both implementations
	clock_t clockTimeStartArray, clockTimeEndArray,
		clockTimeStartLL, clockTimeEndLL;
	clockTimeStartArray = clock();
	
	// comment out linked list implementations to test
	SortSetArray sFibonaccisA( MAX_SIZE );
	SortSetArray sPrimesA;
	SortSetArray sPFdifferenceA;
	SortSetArray sPFunionA;
	SortSetArray sPFintersectionA;

	// builds the sFibonaccis, stores the fibs, used in this sense to
	// avoid making two functions per implementation
	for (int i = 0; i < DEFAULT_SIZE; ++i)
		sFibonaccisA.insert(fibonacciIter(i));
	// removes the MAX SIZE from the set if its not a Fibonacci
	if (MAX_SIZE > fibonacciIter(DEFAULT_SIZE))
		sFibonaccisA.remove(MAX_SIZE);
	
	// stores the primes, differences, union, intersection
	// eratosthenesSieve param can be changed to fit the needed size
	sPrimesA = sPrimesA.eratosthenesSieve(MAX_SIZE);
	sPFdifferenceA = sPrimesA - sFibonaccisA;
	sPFunionA = sPrimesA + sFibonaccisA;
	sPFintersectionA = sPrimesA * sFibonaccisA;

	// comment out to avoid waiting for large output amounts
	cout << "Fibonaccis: " << sFibonaccisA;
	cout << "Primes: " << sPrimesA;
	cout << "Differences: " << sPFdifferenceA;
	cout << "Union: " << sPFunionA;
	cout << "Intersection: " << sPFintersectionA;
 
	// end of array based operation time
	clockTimeEndArray = clock();
	cout << "Array-based implentation: "; 
	clockElapsed (clockTimeStartArray, clockTimeEndArray);    
	
	clockTimeStartLL = clock();
	// comment out the Array-based implementation to test
	SortSetList sPrimesLL;
	SortSetList sFibonaccisLL;
	SortSetList sPFUnionLL;
	SortSetList sPFDifferenceLL;
	SortSetList sPFIntersectLL;

	// stores each fib number
	for (int i = 0; i <= DEFAULT_SIZE; i++)
		sFibonaccisLL.insert(fibonacciIter(i));
	// stores the primes, differences, union, intersection
	// eratosthenesSieve param can be changed to fit the needed size
	sPrimesLL = sPrimesLL.eratosthenesSieve(MAX_SIZE);
	sPFUnionLL = sPrimesLL + sFibonaccisLL;
	sPFDifferenceLL = sPrimesLL - sFibonaccisLL;
	sPFIntersectLL = sPrimesLL * sFibonaccisLL;

	// comment out when testing large numbers (exceeding 100000)
	cout << "Fibs: " << sFibonaccisLL << endl;
	cout << "Primes: " << sPrimesLL << endl;
	cout << "Union: " << sPFUnionLL << endl;
	cout << "Differences: " << sPFDifferenceLL << endl;
	cout << "Intersects: " << sPFIntersectLL << endl;

	// end of linked list operation time
	clockTimeEndLL = clock();
	cout << "LinkedList-based implentation: "; 
	clockElapsed (clockTimeStartLL, clockTimeEndLL);   

	return 0;
}

/**------------------------- fibonacciIter ------------------------------------
	@param input The amount we are going to calculate to.
	@pre  Needs an input.
	@post Produces all the fibs up to the input number.
	@return Integers.
-----------------------------------------------------------------------------*/
int fibonacciIter(const int input) {
	// check for zero and negtives
	if (input <= 0) {
        return 0;
    }
	// finds the fibs
	int temp;
	int fib0 = 0;
    int fib1 = 1;
    for (int i = 2; i <= input; ++i) {
		temp = fib1;
        fib1 += fib0;
        fib0 = temp;
    }
    return fib1;
}

/**-------------------- clockElapsed ------------------------------------------
	@param clockTimeStart  The starts of the time.
	@param clockTimeEnd  The end of the time.
	@pre  Needs to have two inputs of clock_t.
	@post Outputs the time elapse between the clock function calls.
	@return Void. 
-----------------------------------------------------------------------------*/
void clockElapsed( clock_t clockTimeStart, clock_t clockTimeEnd ) {
   clock_t ticks;
   ticks = clockTimeEnd - clockTimeStart;
   cout << "Clock Time Elapsed: " << ticks << " clock ticks ~= " 
        << (float)ticks / (float)CLOCKS_PER_SEC << " seconds\n"; 
}
