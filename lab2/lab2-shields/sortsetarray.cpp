/**----------------------------------------------------------------------------
	@file sortsetarray.cpp
	This file declares and defines each of the function calls of in 
	the class SortSetArray.

	@authors Blong Thao & Albert Tyshler
	@course CSS 342 Shields
	@version 01/26/14
-----------------------------------------------------------------------------*/

#include "sortsetarray.h"

/**---------------------- Default ----------------------------------------------
	Constructor
	Sets the array
	@param  a, b, c, d, e  read them to determine size, then input into set.
	@pre  Need to have integers; otherwise,
	@post Set points to the newly created array; -1 means not in Set  
-----------------------------------------------------------------------------*/
SortSetArray::SortSetArray(int a, int b, int c, int d, int e) : size(0)
{
	// holds the parameters
	const int PARAM_SIZE = 5;
	int param[PARAM_SIZE] = {a, b, c, d, e};
	// finds the largest size
	for (int i = 0; i < PARAM_SIZE; i++) {
		if (param[i] > -1 && size < param[i])
			size = param[i];
	} 
	// builds the set
	if (size > -1) {
		//size++;
		set = new bool[size+1];
		// initializes the array to -1
		for (int i = 0; i <= size; i++) 
			set[i] = false;
		// puts values into set
		insert(a);
		insert(b);
		insert(c);
		insert(d);
		insert(e);
	} // if
	// zeros out the set
	else {
		set = new bool[size+1];
		set[size] = false;
	}
}

/**---------------------- Copy ------------------------------------------------
	@param copy  SortSetArray, gets copied.
	@pre  Needs a SortSetArray type parameter.
	@post Makes a SortSetArray.
	@return SortSetArray.
-----------------------------------------------------------------------------*/
SortSetArray::SortSetArray(const SortSetArray& copy)
{
	// sets everything to the be same as the param
	size = copy.size;
	set = new bool[copy.size+1];

	for(int i = 0; i <= size; i++)
		set[i] = copy.set[i];
}

/**-------------------- Destructor --------------------------------------------
	@pre Needs to have a SortSetArray to delete.
	@post Deletes the SortSetArray and prevents memory leaks.
-----------------------------------------------------------------------------*/
SortSetArray::~SortSetArray()
{
	// frees mem allocs and zeros out size
	delete [] set;
	set = NULL;
	size = 0;
}

/**-------------------------  operator+  --------------------------------------
   @param The right hand side, used to compare and unionize 
		  the left-hand side SortSetArray.
   @pre Need to have a SortSet in the parameter
   @post Creates a new SortSetArray that is the union of the previous 2
   @return Returns a SortSetArray
-----------------------------------------------------------------------------*/
SortSetArray SortSetArray::operator+(const SortSetArray& rightHandSide) {
	// make sure we have the bigger set and unionize the two sets
	if (rightHandSide.size >= size) {
		SortSetArray temp(rightHandSide);
		for (int i = 0; i <= size; i++) {
			if (set[i])
				temp.set[i] = set[i];
		}
		return temp;
	}
	//if the main set is larger continue with *this to unionize the sets
	else {
		SortSetArray temp(*this);
		for (int i = 0; i <= rightHandSide.size; i++) {
			if (rightHandSide.set[i])
				temp.set[i] = rightHandSide.set[i];
		}
		return temp;
	}
}

/**------------------------  operator-  --------------------------------------- 
   @param The right hand side, used to compare and compute 
		  the "difference" to the left-hand side SortSetArray.
   @pre Need to have a SortSet in the parameter
   @post Creates a new SortSetArray that is the difference of the previous 2
   @return Returns a SortSetArray
-----------------------------------------------------------------------------*/
SortSetArray SortSetArray::operator-(const SortSetArray& rightHandSide) {
	// makes sure we have the larger set and find the difference
	// between the two sets, after comparing the both sets, then
	// last part of the larger set is checked for differences.
	if (rightHandSide.size >= size) {
		SortSetArray temp(rightHandSide);
		int i;
		for (i = 0; i <= size; i++) {
			if (set[i] == rightHandSide.set[i])
				temp.set[i] = false;
			else
				temp.set[i] = true;
		}
		for (; i <= rightHandSide.size; i++) {
			if (rightHandSide.set[i])
				temp.set[i] = true;
		}
		return temp;
	}
	else {
		SortSetArray temp(*this);
		int i;
		for (i = 0; i <= rightHandSide.size; i++) {
			if (set[i] == rightHandSide.set[i])
				temp.set[i] = false;
			else
				temp.set[i] = true;
		}
		for (; i <= size; i++) {
			if (set[i])
				temp.set[i] = true;
		}
		return temp;
	}
}

/**------------------------  operator*  ---------------------------------------
   @param The right hand side, used to compare and find the intersection 
		  points to the left-hand side SortSetArray.
   @pre Need to have a SortSet in the parameter
   @post Creates a new SortSetArray that is the intersection of the previous 2
   @return Returns a SortSetArray
-----------------------------------------------------------------------------*/
SortSetArray SortSetArray::operator*(const SortSetArray& rightHandSide) {
	// makes sure we have larger set and finds the intersections
	// after comparing the two sets, then the last part of the 
	// larger set is not intersects
	if (rightHandSide.size >= size) {
		SortSetArray temp(rightHandSide);
		int i;
		for (i = 0; i <= size; i++) {
			if ( (set[i] && rightHandSide.set[i]) )
				temp.set[i] = true;
			else
				temp.set[i] = false;
		}
		for (; i <= rightHandSide.size; i++)
			temp.set[i] = false;
		return temp;
	}
	else {
		SortSetArray temp(*this);
		int i;
		for (i = 0; i <= rightHandSide.size; i++) {
			if ( (set[i] && rightHandSide.set[i]) )
				temp.set[i] = true;
			else
				temp.set[i] = false;
		}
		for (; i <= size; i++)
			temp.set[i] = false;
		return temp;
	}
}

/**------------------------  operator+=  --------------------------------------
   @param The right hand side, used to compare and compute 
	  the "union" to the left-hand side SortSetArray and
	  replace "this" with the new array
   @pre Need to have a SortSet in the parameter
   @post Replaces the current "this" SortSetArray with the union 
   of "this" and RightHandSide
   @return Returns *this; the new array.
-----------------------------------------------------------------------------*/
SortSetArray& SortSetArray::operator+=(const SortSetArray &rightHandSide) {
	// assign the current set to be the union of the other set and itself
	*this = *this + rightHandSide;
	return *this;
}

/**------------------------  operator-=  --------------------------------------
   @param The right hand side, used to compare and compute 
	  the "difference" to the left-hand side SortSetArray and
	  replace "this" with the new array
   @pre Need to have a SortSet in the parameter
   @post Replaces the current "this" SortSetArray with the difference 
   of "this" and RightHandSide
   @return Returns *this; the new array.
-----------------------------------------------------------------------------*/
SortSetArray& SortSetArray::operator-=(const SortSetArray &rightHandSide) {
	// assign the current set to be the differnce of the other set and itself
	*this = *this - rightHandSide;
	return *this;
}

/**------------------------  operator*=  -------------------------------------- 
   @param The right hand side, used to compare and compute 
	  the "intersection" with the left-hand side SortSetArray and
	  replace "this" with the new array
   @pre Need to have a SortSet in the parameter
   @post Replaces the current "this" SortSetArray with the intersect 
   of "this" and RightHandSide; i.e. where the numbers match up between 
   the 2 sets
   @return Returns *this; the new array.
-----------------------------------------------------------------------------*/
SortSetArray& SortSetArray::operator*=(const SortSetArray &rightHandSide) {
	// assign the current set to be the intersect of the other set and itself
	*this = *this * rightHandSide;
	return *this;
}

/**------------------------  operator=  --------------------------------------- 
   @param The right hand side, used to assign the 
	 right hand side to the left.
   @pre Need to have a SortSet in the parameter
   @post Replaces the current "this" SortSetArray with a copy 
   of the RightHandSide
   @return Returns *this; the new array.
-----------------------------------------------------------------------------*/
SortSetArray& SortSetArray::operator=(const SortSetArray & rightHandSide) {
	// make sure both sets are not already equal to each other
	if (this != &rightHandSide)
	{
		// copies the size of the other set
		delete [] set;
		set = new bool[rightHandSide.size+1];
		size = rightHandSide.size;

		// copies the other set to the current set
		for(int i = 0; i <= size; i++)
			set[i] = rightHandSide.set[i];
	}
	return *this;
}

/**---------------------- == ----------------------------------------------
   @param The right hand side, used to check equality with the 
	 left hand side.
   @pre Need to have a SortSet in the parameter
   @post Checks to see if the two arrays are equal
   of the RightHandSide
   @return Returns either true for equality or false for inequality.
-----------------------------------------------------------------------------*/
bool SortSetArray::operator==(const SortSetArray& rightHandSide)const {
	//if the sets size is greater than right hand size
	if(size >= rightHandSide.size) {
		int i;
		//loops to check for equality in values
		for(i = 0; i <= rightHandSide.size; i++)
		{
			if(set[i] != rightHandSide.set[i])
				return false;
		}
		for(; i <= size; i++)
		{
			if(set[i])
				return false;
		}
		return true;
	}
	else
		//if the right hand side is larger than the main size
	{
		int i;
		for(i = 0; i <= size; i++)
		{
			if(set[i] != rightHandSide.set[i])
				return false;
		}
		for(; i <= rightHandSide.size; i++)
		{
			if(rightHandSide.set[i])
				return false;
		}
		return true;
	}
}

/**---------------------- != ----------------------------------------------
   @param The right hand side, used to check for inequality with the 
	 left hand side.
   @pre Need to have a SortSet in the parameter
   @post Checks to see if the two arrays are not equal 
   of the RightHandSide
   @return Returns either true for inequality or false for equality.
-----------------------------------------------------------------------------*/
bool SortSetArray::operator != (const SortSetArray& rightHandSide)const {
	//checking for inequality
	if (size >= rightHandSide.size) {
		//if the main size is larger than right hand size
		int i;
		//loops to check for any inconsistencies and returns 
		//false if any values are equal
		for (i = 0; i <= rightHandSide.size; i++)
		{
			if(set[i] != rightHandSide.set[i])
				return true;
		}
		for (; i <= size; i++)
		{
			if(set[i])
				return true;
		}
		return false;
	}
	else
		//vice versa from above
	{
		int i;
		for (i = 0; i <= size; i++)
		{
			if(set[i] != rightHandSide.set[i])
				return true;
		}
		for (; i <= rightHandSide.size; i++)
		{
			if(rightHandSide.set[i])
				return true;
		}
		return false;
	}
}

/**---------------------- Insert ----------------------------------------------
   @param The input number that is being inserted into the array
   @pre Need to have an integer in the parameter
   @post inserts the value into the array or creates a new array for insertion
   @return Returns either true if it is inserted or false.
-----------------------------------------------------------------------------*/
bool SortSetArray::insert(const int input) {
	// the input number is inserted into its correct position
	if (input > -1) {
		// makes a new boolean array if the set is empty, then inserts
		if (isEmpty()) {
			delete [] set;
			set = new bool[input+1];
			size = input;
			for (int i = 0; i <= input; i++)
				set[i] = false;
			set[input] = true;
			return true;
		} 
		else 
		{
			set[input] = true; //find the index and set it to true
			return true;
		}
	}
	else
		return false;
}

/**---------------------- Remove ----------------------------------------------
   @param The input number that is being removed from the array
   @pre Need to have an integer in the parameter
   @post removes the value from the array if it is valid otherwise returns false
   @return Returns either true if it is removed or false.
-----------------------------------------------------------------------------*/
bool SortSetArray::remove(const int input) {
	// if the value is a valid integer then it is sent to false in the array slot
	if (input > -1) {
		set[input] = false;
		//returns true after removal
		return true;
	}
	// otherwise returns false if the value is less than 0
	return false;
}

/**---------------------- isInSet ----------------------------------------------
   @param The input number that is being checked within the array
   @pre Need to have an integer in the parameter
   @post Checks if the value in the parameter is set to true within the array
   @return Returns either true if it is there or false if not.
-----------------------------------------------------------------------------*/
bool SortSetArray::isInSet(const int input) const {
	// if the value being input is valid then check if that array index is true
	if (input > -1) {
		if (set[input])
			return true;
	}
	// if it is not found false is ultimately returned
	return false;
}

/**---------------------- isEmpty ----------------------------------------------
   @param No Parameters
   @pre Calls the function to check for an empty array without params
   @post Checks if all of the values in the array are set to false or the array
	is empty
   @return Returns either true if it is empty or false if not.
-----------------------------------------------------------------------------*/
bool SortSetArray::isEmpty() const {
	// if the size of the array is 0 then it is empty
	if (size == 0)
		return true;
	for (int i = 0; i <= size; i++) {
		// runs through the array to see if any values are true
		if (set[i])
			return false;
	}
	return true;
}

/**------------------------ << ------------------------------------------------
   @param The output and the SortSet Array
   @pre Need to have output and a valid array
   @post The array, along with brackets are output to the console as long as 
	the index is true
   @return Returns the output array to the console
-----------------------------------------------------------------------------*/
ostream& operator<<(ostream &output, const SortSetArray &setArray)
{
	// prints out the output of the sets like: { 1 2 3}
	output << "{";
	for (int i = 0; i <= setArray.size; i++) {
		if (setArray.set[i] == true)
			output << " " << i;
	}
	output << "}";
	return output;
}

/**------------------------- >> -----------------------------------------------
   @param The input file and the SortSet Array
   @pre Need to have input and a valid array
   @post The array is created with the values that are input from the text
   @return Returns the "input" values back in array form
-----------------------------------------------------------------------------*/
istream& operator>>(istream &input, SortSetArray& setArray) 
{
	// this variable holds the input
	int num = 0;

	// takes in any amount of numbers and inserts it into the set;
	// type in -1 to stop the input of numbers
	while ( input >> num && num != -1 ) {
		// makes a new array when the input is higher than the current size
		// and puts in all the same values plus the input value
		if (num > setArray.size) {
			SortSetArray temp(num);
			for (int i = 0; i <= setArray.size; i++) {
				if (setArray.set[i])
					temp.set[i] = true;
			}
			delete [] setArray.set;
			setArray.set = temp.set;
			temp.set = NULL;
			setArray.size = temp.size;
		}
		setArray.insert(num);
	}
	return input;
}

/**------------------- eratosthenesSieve --------------------------------------
	Checks if the input is a prime number or not
	@param input  The number to check.
	@pre Needs an input to start the check.
	@post The input is either (prime : not ? true : false).
	@return A boolean, true or false.
-----------------------------------------------------------------------------*/
SortSetArray SortSetArray::eratosthenesSieve(const int setSize) {
	// holds all the primes
	SortSetArray primes(setSize);
	
	// turns all values other than 0 and 1 to true; 
	// will be used to mark off the multiples
	for (int i = 2; i < setSize; i++)
		primes.set[i] = true;
	
	// used to take out all the multiples and finds the primes
	if (setSize >= 2) {
		for (int i = 2; i < setSize; i++) {
			if (primes.set[i] == true) {
				takeOutMultiples(primes, i, setSize);
			}
		}
	}
	return primes;
}

/**----------------- takeOutMultiples -----------------------------------------
	Takes out all multiples to continue with removing anything but primes
	@param The sortSetArray, the number it is taking out in multiples, and the size
	@pre Needs these values to remove the non prime values
	@post The values that are multiples of the input value are set to false
	@return No return, the loop contines in "eratosthenesSieve"
-----------------------------------------------------------------------------*/
void SortSetArray::takeOutMultiples(SortSetArray& theSet, 
									const int num, const int setSize) {
	// the counter and marker for each multiple
	int count = 2;
	int mark;

	// runs through the set and marks all the multiples
	while ( (mark = num*count) <= setSize) {
		if (theSet.set[mark] == true)
			theSet.set[mark] = false;
		count++;
	}
}

