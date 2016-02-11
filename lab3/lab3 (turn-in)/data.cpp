/**----------------------------------------------------------------------------
 @file data.cpp
	The file that contains the functions for the Data class.

 @authors Blong Thao and Alber Tyshler
 @course CSS 342 Shields
 @version 1.0
 @date 02/09/14
-----------------------------------------------------------------------------*/

#include <iostream>
#include "data.h"
using namespace std;

/** ----------- Default -------------------------------------------------------
@pre  Index and data must have values >= 0 to count as valid data.
-----------------------------------------------------------------------------*/
Data::Data(int byte, char data) {
	theData = data;
	theByte = byte;
}

/** ----------- Destructor ----------------------------------------------------
@post  Sets index and data to '-1' to show its destructed.
-----------------------------------------------------------------------------*/
Data::~Data() {
	clear();
}

/**--------------- < ----------------------------------------------------------
@pre  Needs a Data object.
@post Finds out which Data object is smaller.
-----------------------------------------------------------------------------*/
bool Data::operator<(const Data &compareTo) {
	return theData < compareTo.theData;
}

/** ----------- Equality ------------------------------------------------------
@pre  Needs a Data object.
@post Finds out if the Data objects are equal to each other.
-----------------------------------------------------------------------------*/
bool Data::operator==(const Data &compareTo) {	
	return theByte == compareTo.theByte;
}

/** ----------- Inequality ----------------------------------------------------
@pre  Needs a Data object.
@post Finds out if the Data objects are not equal to each other.
-----------------------------------------------------------------------------*/
bool Data::operator!=(const Data &compareTo) {
	return !(theByte == compareTo.theByte);
}

/** ----------- Insert -------------------------------------------------------
@pre Needs an int value > 0 and char value that is not negative.
@post Inserts to Data object.
-----------------------------------------------------------------------------*/
bool Data::insert(const int intInput, const char charInput) {
	if (intInput > -1 && charInput > -1) {
		theByte = intInput;
		theData = charInput;
		return true;
	}
	return false;
}

/** ----------- Remove -------------------------------------------------------
@pre Needs valid parameters to remove from Data object.
@post Clears out the Data object.
-----------------------------------------------------------------------------*/
bool Data::remove(const int intInput, const char charInput) {
	if (intInput == theByte && charInput == theData) {
 		clear();
		return true;
	}
	return false;
}

/**------------- clear --------------------------------------------------------
@post Turns variables into values invalid to the compareList tool.
-----------------------------------------------------------------------------*/
void Data::clear() {
	theByte = -1;
	theData = -1;
}

/** ---------------- << -------------------------------------------------------
@pre  Needs a Data object to output from.
@post Outputs the Data object in this form.
-----------------------------------------------------------------------------*/
ostream& operator<<(ostream& output, const Data& input) {
	if (input.theData == '\n')
		output << input.theByte << " " << "NL" << "  ";
	else if (input.theData == '\t' || input.theData == '\r')
		output << input.theByte << " " << "Tab" << "  ";
	else if (input.theData == ' ')
		output << input.theByte << " " << "WS" << "  ";
	else
		output << input.theByte << " " << input.theData << "  ";
	return output;
}
