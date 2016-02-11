/**----------------------------------------------------------------------------
	@file SortSetList.cpp
	This file declares and defines each of the function calls of in 
	the class SortSetList.

	@authors Blong Thao & Albert Tyshler
	@course CSS 342 Shields
	@version 01/26/14
-----------------------------------------------------------------------------*/

#include "sortsetlist.h"

/**---------------------- Default ----------------------------------------------
	Constructor
	Sets the array
	@param  a, b, c, d, e  read them to determine size, then input into set.
	@pre  Need to have integers; otherwise,
	@post Set points to the newly created array; -1 means not in Set  
-----------------------------------------------------------------------------*/
SortSetList::SortSetList(int a, int b, int c, int d, int e)
{
	head = NULL;
	const int PARAM_SIZE = 5;
	int param[PARAM_SIZE] = {a, b, c, d, e};
	// puts values into set
	for (int i = 0; i < PARAM_SIZE; i++) {
		if (param[i] > -1)
			insert(param[i]);
	}
}

/**---------------------- Copy ------------------------------------------------
	@param copy  SortSetList, gets copied.
	@pre  Needs a SortSetList type parameter.
	@post Makes a SortSetList.
	@return SortSetList.
-----------------------------------------------------------------------------*/
SortSetList::SortSetList(const SortSetList& copy)
{
	// empty list
	if (copy.isEmpty()) 
	{
		head = NULL;
	}
	// copies every node from the other list
	else
	{
		// adds first node to list
		head = new Node;
		head->data = copy.head->data;
		Node* current = head;
		Node* currentCopy = copy.head->next;
		// adds more nodes to list is copylist has more to add
		while (currentCopy != NULL) {
			current->next = new Node;
			current->next->data = currentCopy->data;
			current = current->next;
			currentCopy = currentCopy->next;
		}
		// ends the list
		current->next = NULL;
	}
}

/**-------------------- Destructor --------------------------------------------
	@pre Needs to have a SortSetList to delete.
	@post Deletes the SortSetList and prevents memory leaks.
-----------------------------------------------------------------------------*/
SortSetList::~SortSetList()
{
	Node* current = head;
	// walks through list and deallocates every node
	while (current != NULL) {
		Node* next = current->next;
		delete current;
		current = next;
	}
	head = NULL;
}

/**-------------------------  operator+  --------------------------------------
   @param The right hand side, used to compare and unionize 
		  the left-hand side SortSetList.
   @pre Need to have a SortSet in the parameter
   @post Creates a new SortSetList that is the union of the previous 2
   @return Returns a SortSetList
-----------------------------------------------------------------------------*/
SortSetList SortSetList::operator+(const SortSetList& rightHandSide) {
	// makes sure there are no empty sets
	if ( isEmpty() && rightHandSide.isEmpty() ) return *this;
	if ( head == NULL ) 
	{
		return rightHandSide;
	}
	else if (rightHandSide.head == NULL)
	{
		return *this;
	}
	// otherwise, start the union phase
	else 
	{
		// copies the current set
		SortSetList theUnion(*this);
		Node* current = rightHandSide.head;
		Node* currentCheck = head;
		// adds the right hand side to the set
		while (current != NULL && currentCheck != NULL) 
		{
			while (current->data != currentCheck->data && 
				currentCheck->next != NULL) 
			{
				currentCheck = currentCheck->next;
			}
			// advance each pointer to avoid duplicates
			if (current->data == currentCheck->data) 
			{
				current = current->next;
				currentCheck = head;
			}
			// add to set
			else
			{
				theUnion.insert(current->data);
				current = current->next;
				currentCheck = head;
			}
		}
		return theUnion;
	}
}

/**------------------------  operator-  --------------------------------------- 
   @param The right hand side, used to compare and compute 
		  the "difference" to the left-hand side SortSetList.
   @pre Need to have a SortSet in the parameter
   @post Creates a new SortSetList that is the difference of the previous 2
   @return Returns a SortSetList
-----------------------------------------------------------------------------*/
SortSetList SortSetList::operator-(const SortSetList& rightHandSide) {
	// makes sure there are no empty sets
	if ( isEmpty() && rightHandSide.isEmpty() ) return *this;
	if ( head == NULL ) 
	{
		return rightHandSide;
	}
	else if (rightHandSide.head == NULL)
	{
		return *this;
	}
	// otherwise, start finding the differences
	else 
	{
		// copies the current set
		// pointers are set to each head for comparison
		SortSetList theDifference(*this);
		Node* rightCur = rightHandSide.head;
		Node* leftCur = head;
		// adds the rhs to the set
		while (leftCur != NULL && rightCur != NULL) 
		{
			// looks through list to make sure there are no duplicates
			while (rightCur->data > leftCur->data 
				&& leftCur->next != NULL) 
			{
				leftCur = leftCur->next;
			}
			// takeout the duplicates, reset leftCur pointer
			if (rightCur->data == leftCur->data) 
			{
				theDifference.remove(leftCur->data);
				rightCur = rightCur->next;
				leftCur = head;
			}
			// add the value to set, reset leftCur pointer
			else
			{
				theDifference.insert(rightCur->data);
				rightCur = rightCur->next;
				leftCur = head;
			}
		}
	return theDifference;
	}
}

/**------------------------  operator*  ---------------------------------------
   @param The right hand side, used to compare and find the intersection 
		  points to the left-hand side SortSetList.
   @pre Need to have a SortSet in the parameter
   @post Creates a new SortSetList that is the intersection of the previous 2
   @return Returns a SortSetList
-----------------------------------------------------------------------------*/
SortSetList SortSetList::operator*(const SortSetList& rightHandSide) {
	// makes sure there are no empty sets
	if ( isEmpty() && rightHandSide.isEmpty() ) return *this;
	if ( head == NULL ) 
	{
		return rightHandSide;
	}
	else if (rightHandSide.head == NULL)
	{
		return *this;
	}
	// otherwise, start finding the differences
	else 
	{
		// empty set; will be filled if there are any values that are equal
		// between the two sets being compared
		SortSetList theIntersect;
		Node* rightCur = rightHandSide.head;
		Node* leftCur = head;
		while (rightCur != NULL && leftCur != NULL) 
		{
			// looks through each data value to check for equal values
			while (rightCur->data > leftCur->data && leftCur->next != NULL) 
			{
				leftCur = leftCur->next;
			}
			// add them to theIntersect
			if (rightCur->data == leftCur->data) 
			{
				theIntersect.insert(rightCur->data);
				rightCur = rightCur->next;
			}
			// advance through set
			else
			{
				rightCur = rightCur->next;
			}
		}
		return theIntersect;
	}
}

/**------------------------  operator+=  --------------------------------------
   @param The right hand side, used to compare and compute 
	  the "union" to the left-hand side SortSetList and
	  replace "this" with the new List
   @pre Need to have a SortSet in the parameter
   @post Replaces the current "this" SortSetList with the union 
   of "this" and RightHandSide
   @return Returns *this; the new List.
-----------------------------------------------------------------------------*/
SortSetList& SortSetList::operator+=(const SortSetList &rightHandSide) {
	// assign the current set to be the union of the other set and itself
	*this = *this + rightHandSide;
	return *this;
}

/**------------------------  operator-=  --------------------------------------
   @param The right hand side, used to compare and compute 
	  the "difference" to the left-hand side SortSetList and
	  replace "this" with the new List
   @pre Need to have a SortSet in the parameter
   @post Replaces the current "this" SortSetList with the difference 
   of "this" and RightHandSide
   @return Returns *this; the new List.
-----------------------------------------------------------------------------*/
SortSetList& SortSetList::operator-=(const SortSetList &rightHandSide) {
	// assign the current set to be the difference of the other set and itself
	*this = *this - rightHandSide;
	return *this;
}

/**------------------------  operator*=  -------------------------------------- 
   @param The right hand side, used to compare and compute 
	  the "intersection" with the left-hand side SortSetList and
	  replace "this" with the new List
   @pre Need to have a SortSet in the parameter
   @post Replaces the current "this" SortSetList with the intersect 
   of "this" and RightHandSide; i.e. where the node values match up between 
   the 2 sets
   @return Returns *this; the new List.
-----------------------------------------------------------------------------*/
SortSetList& SortSetList::operator*=(const SortSetList &rightHandSide) {
	// assign the current set to be the intersect of the other set and itself
	*this = *this * rightHandSide;
	return *this;
}

/**------------------------  operator=  --------------------------------------- 
   @param rightHandSide  The SortSetList on the right hand side; gets copied
						 into the current list.
   @pre  Needs a SortSetList.
   @post Current list copies the rhs.
   @return SortSetList.
-----------------------------------------------------------------------------*/
SortSetList& SortSetList::operator=(const SortSetList & rightHandSide) {
	if (this != &rightHandSide) 
	{
		// pointers walking each set
		Node* leftCurr = head;
		Node* rightCurr = rightHandSide.head;

		// deletes what was in the current list
		while (leftCurr != NULL) {
			Node* temp = leftCurr->next;
			delete leftCurr;
			leftCurr = temp;
		}

		// after set is emptied, head is initialized again
		head = NULL;

		// starts head off with the first node from rhs
		if (rightCurr != NULL) {
			head = new Node;
			head->data = rightCurr->data;
			leftCurr = head;
			rightCurr = rightCurr->next;

			// inputs the values from the rhs into the current list
			while (rightCurr != NULL) {
				leftCurr->next = new Node;
				leftCurr->next->data = rightCurr->data;
				leftCurr = leftCurr->next;
				rightCurr = rightCurr->next;
			}
			// ends of the list
			leftCurr->next = NULL;
		}
	}
	return *this;
}

/**---------------------- == ----------------------------------------------
   @param rightHandSide The list that is being compared.
   @pre Needs a SortSetList.
   @post Tells if the two list are equal or not.
   @return Boolean.
-----------------------------------------------------------------------------*/
bool SortSetList::operator== (const SortSetList& rightHandSide) const {
	// cases: both empty, one empty, and one or more in the list
	if(isEmpty() && rightHandSide.isEmpty())
	{
		return true;
	}
	else if(isEmpty() || rightHandSide.isEmpty())
	{
		return false;
	}
	else
	{
		// pointers to walk each list
		Node* leftCurr = head;
		Node* rightCurr = rightHandSide.head;
		// walk each list until a value comparison is not equal, then the lists
		// are not equal; otherwise, both lists are equal
		while(leftCurr->next != NULL && rightCurr->next != NULL)
		{
			if(leftCurr->data == rightCurr->data)
			{
				leftCurr = leftCurr->next;
				rightCurr = rightCurr->next;
			}
			else
			{
				return false;
			}	
		}
		return true;
	}
}

/**---------------------- != ----------------------------------------------
   @param The right hand side, used to check for inequality with the 
	 left hand side.
   @pre Need to have a SortSet in the parameter
   @post Checks to see if the two Lists are not equal 
   @return Returns either true for inequality or false for equality.
-----------------------------------------------------------------------------*/
bool SortSetList::operator!= (const SortSetList& rightHandSide) const {
	// cases: both empty, one empty, and one or more in the list
	if(isEmpty() && rightHandSide.isEmpty())
	{
		return false;
	}
	else if(isEmpty() || rightHandSide.isEmpty())
	{
		return true;
	}
	else
	{
		// pointers to walk each list
		Node* leftCurr = head;
		Node* rightCurr = rightHandSide.head;
		// walk each list until a value comparison is not equal, then the lists
		// are not equal; otherwise, both lists are equal
		while(leftCurr->next != NULL && rightCurr->next != NULL)
		{
			if(leftCurr->data == rightCurr->data)
			{
				leftCurr = leftCurr->next;
				rightCurr = rightCurr->next;
			}
			else
			{
				return true;
			}	
		}
		return false;
	}
}

/**---------------------- Insert ----------------------------------------------
   @param The input number that is being inserted into the Data Node
   @pre Need to have an integer in the parameter
   @post inserts the value into the List or creates a new Node for insertion
   @return Returns either true if it is inserted or false if something is wrong.
-----------------------------------------------------------------------------*/
bool SortSetList::insert(const int input) {
	// the input number is inserted into its correct position
	Node* ptr = new Node;
    if (ptr == NULL) return false;                 // out of memory, bail
    ptr->data = input;                           // link the node to data
	ptr->next = NULL;

    // if the list is empty or if the node should be inserted before 
    // the first node of the list
	if (isEmpty() || ptr->data < head->data && ptr->data != head->data) {
        ptr->next = head;                        
        head = ptr;
    }
	// then check the rest of the list until we find where it belongs 
	else {
		Node* current = head->next;          // to walk list
		Node* previous = head;               // to walk list, lags behind

		// walk until end of the list or found position to insert
		// accounts for duplicates, walks past them
		while (current != NULL && current->data <= ptr->data) {
			previous = current;                  // walk to next node
            current = current->next;
		}
		// insert new node, link it in only if each value is not equal
		if (ptr->data != previous->data)
		{
			ptr->next = current;
			previous->next = ptr;
		}
		else
		{
			Node* ptrNext = ptr->next;
			delete ptr;
			ptr = ptrNext;
		}
	}
	return true;
}

/**---------------------- Remove ----------------------------------------------
   @param The input number that is being removed from the List
   @pre Need to have an integer in the parameter
   @post removes the value from the List if it is valid otherwise returns false
	if not found
   @return Returns either true if it is removed or false if not found.
-----------------------------------------------------------------------------*/
bool SortSetList::remove(int input) {
	// walker for current set
	Node* current = head;
	
	// compares first data in current set
	if(input == head->data)
	{
		Node* next = current->next;
		delete current;
		head = next;
		return true;
	}

	// compares data in current set
	while(current->next != NULL)
	{
		if(input == current->next->data)
		{
			Node* next = current->next->next;
			delete current->next;
			current->next = next;
			return true;
		}
		current = current->next;
	}
	return false;
}

/**---------------------- isInSet ----------------------------------------------
   @param The input number that is being checked for within the List
   @pre Need to have an integer in the parameter
   @post Checks if the value in the parameter is located within the Linked List
   @return Returns either true if it is there or false if not.
-----------------------------------------------------------------------------*/
bool SortSetList::isInSet(const int input) const {
	// checks to see if the value is in the linked list
	Node* current = head;

	// loop to run through the entire list
	while(current != NULL)
	{
		// is the value is found return true
		if(current->data == input)
		{
			return true;
		}
		current = current-> next;
	}
	// if not found return false
	return false;
}

/**---------------------- isEmpty ----------------------------------------------
   @param No Parameters
   @pre Calls the function to check for an empty Linked List without params
   @post Checks if head is null
   @return Returns either true if it is empty or false if not.
-----------------------------------------------------------------------------*/
bool SortSetList::isEmpty() const {
	// checks if head is empty or not
	return head == NULL;
}

/**----------------------- eratosthenesSieve ----------------------------------
	Checks if the input is a prime number or not
	@param input  The number to check.
	@pre Needs an input to start the check.
	@post The input is either (prime : not ? true : false).
	@return A boolean, true or false.
-----------------------------------------------------------------------------*/
SortSetList SortSetList::eratosthenesSieve(const int setSize) {
	// set for primes; boolean array will hold the primes to insert into set
	SortSetList primes;
	bool* thePrimes = new bool[setSize+1];

	// turns all values in bool array true; then will be 
	// marked false if not a prime number, 0 and 1 are not prime
	for (int i = 2; i <= setSize; i++)
		thePrimes[i] = true;

	// takes out all multiples of the primes and
	// inserts the primes into the prime set
	if (setSize >= 2) {
		for (int i = 2; i <= setSize; i++) {
			if (thePrimes[i] == true) {
				primes.insert(i);
				takeOutMultiples(thePrimes, i, setSize);
			}
		}
	}
	// free memory
	delete [] thePrimes;
	return primes;
}

/**----------------- takeOutMultiples -----------------------------------------
	Takes out all multiples to continue with removing anything but primes
	@param The sortSetList, the number it is taking out in multiples, and the size
	@pre Needs these values to remove the non prime values
	@post The values that are multiples of the input value are set to false
	@return No return, the loop contines in "eratosthenesSieve"
-----------------------------------------------------------------------------*/
void SortSetList::takeOutMultiples(bool*& theSet, 
									int num, const int setSize) {
	// counter and marker to take out the multiples
	int count = 2;
	int mark;

	// marks out all multiples of the primes
	while ( (mark = num*count) <= setSize) {
		if (theSet[mark] == true)
			theSet[mark] = false;
		count++;
	}
}
