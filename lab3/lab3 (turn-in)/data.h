/**----------------------------------------------------------------------------
 @file data.h
	The file that contains the declarations for the Data class.

 @authors Blong Thao and Alber Tyshler
 @course CSS 342 Shields
 @version 1.0
 @date 02/09/14
-----------------------------------------------------------------------------*/

#ifndef DATA_H
#define DATA_H
#include <iostream>
using namespace std;

/**----------------------------------------------------------------------------
	Assumptions:
	-- The int byte holds the Bytes and the char theData will hold the data
	   values in the Data class.
	-- The constructor holds default values if there are no inputs to the
	   parameters; which then becomes the values unless changed.
	-- The data and byte values that is considered invalid is -1.
	-- clear() function is included into the remove and destructor, throws
	   invalid values into those spots to remove or destruct the data.
-----------------------------------------------------------------------------*/

class Data
{
	friend ostream& operator<<(ostream& output, const Data&);

public:
	// Constructors: Default, Destructor
	Data(int = -1, char = -1);
	~Data();

	// Operators: smaller than, equality, inequality
	bool operator<(const Data &);
	bool operator==(const Data &);
	bool operator!=(const Data &);

	// Insert, Remove
	bool insert(const int, const char);
	bool remove(const int, const char);

private:
	int theByte;
	char theData;
	void clear();
};

#endif
