/**----------------------------------------------------------------------------
   @file sortsetarray.h
	This file declares only the function calls of the class SortSetArray.

   @authors Blong Thao & Albert Tyshler
   @course CSS 342 Shields
   @version 01/26/14
-----------------------------------------------------------------------------*/

#ifndef ARRAYSET_H
#define ARRAYSET_H
#include <iostream>
using namespace std;

/**----------------------------------------------------------------------------
   SortSetArray: Is a sorted set implemented by an array.
   
   Assumptions: 
   -- Accounts for the negative values that are inputted into this application
     as well as for empty inputs/parameters.
   -- Operators are allowed to concatenate without any memory leaks or errors.
   -- Copy constructors copies every detail and makes the set a replica of the
     other set, and used throughout the operators to reduce duplicate code.
   -- Prints out a set in this sequence: { 2 5 6 10}
-----------------------------------------------------------------------------*/

class SortSetArray
{
	// the cin and cout operators
	friend ostream& operator<<(ostream&, const SortSetArray&);
	friend istream& operator>>(istream&, SortSetArray&);

public: 
	// Constructors: Default, Copy, Destructors
	SortSetArray(int = -1, int = -1, int = -1, int = -1, int = -1);
	SortSetArray(const SortSetArray&);
	~SortSetArray();

	// Operators: union, difference, intersect
	SortSetArray operator+(const SortSetArray &);
	SortSetArray operator-(const SortSetArray &);
	SortSetArray operator*(const SortSetArray &);

	// Assignment Operators
	SortSetArray& operator+=(const SortSetArray &);
	SortSetArray& operator*=(const SortSetArray &);
	SortSetArray& operator-=(const SortSetArray &);
	SortSetArray& operator=(const SortSetArray &);	

	// Equality Operators
	bool operator==(const SortSetArray &) const;
	bool operator!=(const SortSetArray &) const;

	// Insert, Remove, Empty?, IsInSet?
	bool insert(const int);
	bool remove(const int);
	bool isEmpty() const;
	bool isInSet(const int) const;

	// Primes
	SortSetArray eratosthenesSieve(const int);

private:
	int size;
	bool *set;
	void takeOutMultiples(SortSetArray&, const int, const int);
};

#endif
