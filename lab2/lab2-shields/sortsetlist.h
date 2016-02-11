/**----------------------------------------------------------------------------
   @file sortsetlist.h
	This file declares only the function calls of the class SortSetList.

   @authors Blong Thao & Albert Tyshler
   @course CSS 342 Shields
   @version 01/26/14
-----------------------------------------------------------------------------*/

#ifndef LLSET_H
#define LLSET_H
#include <iostream>
using namespace std;

/**----------------------------------------------------------------------------
   SortSetList: A linked list implementation of the SortSet ADT. 
   
   Assumptions:
   -- Accounts for negatives and empty lists.
   -- The prime finder function (eratosthenesSieves) produces a big-O
      of (n^2) due to the multiple loops it goes through while inserting
	  the values into the list.
   -- The fibonacci finder is in the main and we store the fib numbers by
      inserting them into the list.
   -- Test cases are in the lab2test.cpp file and tests each operator and
      function, there seems to be no memory leaks in those cases.
   -- Outputting a Linked List Sort Set should always appear like this:
				{ 1 2 3 4 5 6 7 8 9 10}
	  Meaning there are no duplicates and no negatives.
   -- Operators can be concatenated amongst one another.
-----------------------------------------------------------------------------*/

class SortSetList
{
	/**------------------------ << --------------------------------------------
	@param output The output.
	@param theList The list that is being outputed
	@pre None.
	@post Prints out: { numbers }
	-------------------------------------------------------------------------*/
	friend ostream& operator<<(ostream& output, const SortSetList& theList) {
		// walks through the list to print out each value like: { 1 2 3} 
		Node* current = theList.head;
		output << "{";
		while (current != NULL) {
			output << " " << current->data;
			current = current->next;
		}
		output << "}";
		return output;
	}

	/**------------------------ << --------------------------------------------
	@param input The input.
	@param theList The list that is being input.
	@pre None.
	@post Inserted the value inputs.
	-------------------------------------------------------------------------*/
	friend istream& operator>>(istream& input, SortSetList& theList) {
		// holds the numbers that are inputed and used to insert in the list
		int number = 0;
		while ( input >> number && number != -1) 
		{
			// does not take in negatives
			if (number > -1)
			{
				// checks list for duplicates
				Node* current = theList.head;
				while (current != NULL)
				{
					if (current->data != number)
					{
						current = current->next;
					}
					else
					{
						break;
					}
				}
				if (current == NULL || current->data != number) 
				{
					theList.insert(number);
				}
			}
		}
		return input;
	}

public:
	// Constructors: Default, Copy, Destructors
	SortSetList(int = -1, int = -1, int = -1, int = -1, int = -1);
	SortSetList(const SortSetList&);
	~SortSetList();

	// Operators: union, difference, intersect
	SortSetList operator+(const SortSetList &);
	SortSetList operator-(const SortSetList &);
	SortSetList operator*(const SortSetList &);


	// Assignment Operators
	SortSetList& operator+=(const SortSetList &);
	SortSetList& operator*=(const SortSetList &);
	SortSetList& operator-=(const SortSetList &);
	SortSetList& operator=(const SortSetList &);	

	// Equality Operators
	bool operator==(const SortSetList &) const;
	bool operator!=(const SortSetList &) const;

	// Insert, Remove, Empty, IsInSet
	bool insert(const int);
	bool duplicate(const int);
	bool remove( int );
	bool isEmpty() const;
	bool isInSet(const int) const;

	// Primes
	SortSetList eratosthenesSieve(const int);	
	
private:
	struct Node {
		int data;
		Node* next;
	};
	Node* head;
	void takeOutMultiples(bool*&, int, const int);
};

#endif
