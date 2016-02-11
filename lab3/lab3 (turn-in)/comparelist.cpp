/**----------------------------------------------------------------------------
 @file comparelist.cpp
	The file that contains most of the functions the CompareList class uses to
	run the application and the test cases.

 @authors Blong Thao and Alber Tyshler
 @course CSS 342 Shields
 @version 1.0
 @date 02/09/14
-----------------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include "comparelist.h"
#define MAX_SIZE 514229
using namespace std;

/**----------------------- Default --------------------------------------------
@post Initializes the head to NULL.
-----------------------------------------------------------------------------*/
CompareList::CompareList() : head(NULL) {}

/**----------------------Destructor--------------------------------------------
@post Frees all memory allocations
-----------------------------------------------------------------------------*/
CompareList::~CompareList() {
	// traverses the list and frees data and node mem allocs, sets head to NULL
	clear(head);
}

/**----------------------- readFile -------------------------------------------
@param file  The file being read.
@param ascii The char array that reads in the file characters
@pre  None.
@post The file got read, or not if its empty.
-----------------------------------------------------------------------------*/
bool CompareList::readFile(ifstream& file, char* ascii, int size) {
	int byte = 0;
	char theChar;
	char* charArray = ascii;
	
	// intialize array to a non-ascii value
	for (; byte <= size; byte++)
		charArray[byte] = -1;

	// avoid white space reads into array
	do {
		file >> skipws;
		if (file.eof()) return false;
	} while (!(file >> theChar));

	byte = 0;
	// reads in first character, then the rest of file (via loop)
	charArray[byte] = theChar;
	for (byte = 1; byte <= size; byte++) 
	{
		// read in characters and turn them to ASCII characters
		file >> noskipws >> theChar;
		
		// read end of file, now break out of loop
		if (file.eof()) break;

		// stores values into array
		charArray[byte] = theChar;
	}
	return true;
}

/**----------------------------------------------------------------------------
@param file  The file that is being read to make the PF list.
@pre None.
@post Returns the CompareList with the prime Fib bytes in the list.
-----------------------------------------------------------------------------*/
CompareList& CompareList::buildListPF(ifstream& file) {
	// empty out list before making a new list
	if (!isEmpty()) clear(head);
	char theChar;
	int startPos = 0, byte = 0;
	const int pFNums = 9;
	int primeFib[pFNums] = { 2, 3, 5, 13, 89, 233, 1597, 28657, 514229};

	// skips all front white spaces, but reads in first char
	do {
		file >> skipws;
		if (file.eof()) break;
	} while (!(file >> theChar));

	// reads in all whitespaces and chars, inserts only the PF bytes
	for (byte = 1; byte <= MAX_SIZE; byte++) {
		file >> noskipws >> theChar;

		if (file.eof()) break;

		// when there is a PF byte put the char into the list
		if (byte == primeFib[startPos]) {
			makeData(byte, theChar);
			startPos++;
		}
	}
	return *this;
}

/**---------------------- Insert ----------------------------------------------
@param input  The Data that is to be inserted into the list.
@pre  Valid Data, cannot be < 0 values for byte and data.
@post  The list now contains this input.
@return  A boolean.
-----------------------------------------------------------------------------*/
bool CompareList::insert(Data* input) {
	Data* error = new Data;
	if ( *input == *error ) {
		delete error;
		return false;
	}
	delete error;
	// the data value is inserted into a Data pointer
	Node* ptr = new Node;
    if (ptr == NULL) return false;         // out of memory
    ptr->data = new Data;                  // link the node to data
	*ptr->data = *input;
	ptr->next = NULL;

    // inserts the data into the head of list
	if (isEmpty()) {
        ptr->next = head;                        
        head = ptr;
    }
	// runs through list until it reaches the end and inserts data there
	else {
		Node* current = head->next;
		Node* previous = head;
		while (current != NULL)
		{
			if (*previous->data == *ptr->data) break;
			previous = current;
			current = current->next;
		}
		// insert new node, link it in
		if (*previous->data != *ptr->data) {
			ptr->next = current;
			previous->next = ptr;
		} else {
			delete ptr->data;
			delete ptr;
			ptr = NULL;
		}

	}
	return true;
}

/**---------------------- Remove ----------------------------------------------
@param input  The Data that is to be removed from the list.
@pre  Valid Data, cannot be -1 values for byte and data.
@post  The list does not have the input anymore.
@return  A boolean.
-----------------------------------------------------------------------------*/
bool CompareList::remove(Data* input) {
	// walker for current list and the next node
	Node* current = head;

	// compares first data in the list, removes from beginning of list
	if (*current->data == *input)
	{
		Node* nextNode = head->next;
		delete current->data;
		delete current;
		head = nextNode;
		return true;
	}
	// compares data in the list, removes from anywhere the
	// data is found in the list

	while (current->next != NULL)
	{
		if (*current->next->data == *input)
		{
			Node* nextNode = current->next->next;
			delete current->next->data;
			delete current->next;
			current->next = nextNode;
			return true;
		}
		current = current->next;
	}
	return false;
}

/**---------------------- isEmpty ----------------------------------------------
@post The list is either empty or not.
@return A boolean.
-----------------------------------------------------------------------------*/
bool CompareList::isEmpty() const {
	return head == NULL;
}

/**------------------ operator== -----------------------------------------------
@param rightHandSide  The list to compare with the current list.
@pre  None.
@post Returns a boolean value.
-----------------------------------------------------------------------------*/
bool CompareList::operator==(const CompareList& rightHandSide) {
	// checks for empty lists
	if (rightHandSide.isEmpty() && this->isEmpty()) 
		return true;
	// checks for if one is empty and the other one is not.
	else if (rightHandSide.isEmpty() || this->isEmpty()) 
		return false;
	else {
		// pointers to walk each list
		Node* leftCurr = head;
		Node* rightCurr = rightHandSide.head;
		// walk each list until a value comparison is not equal, then the lists
		// are not equal; otherwise, both lists are equal
		while(leftCurr != NULL && rightCurr != NULL)
		{
			if(*leftCurr->data == *rightCurr->data)
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

/**------------------ operator!= -----------------------------------------------
@param rightHandSide  The list to compare with the current list.
@pre  None.
@post Returns a boolean value.
-----------------------------------------------------------------------------*/
bool CompareList::operator!=(const CompareList& rightHandSide) {
	if (rightHandSide.isEmpty() && this->isEmpty()) 
		return false;
	else if (rightHandSide.isEmpty() || this->isEmpty()) 
		return true;
	else {
		// pointers to walk each list
		Node* leftCurr = head;
		Node* rightCurr = rightHandSide.head;
		// walk each list until a value comparison is not equal, then the lists
		// are not equal; otherwise, both lists are equal
		while(leftCurr != NULL && rightCurr != NULL)
		{
			if(*leftCurr->data == *rightCurr->data)
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

/**------------------ operator= -----------------------------------------------
@param rightHandSide The object that the current list is copying.
@pre Parameter must take in a CompareList object.
@post Current list is now the same as the rightHandSide.
-----------------------------------------------------------------------------*/
CompareList& CompareList::operator=(const CompareList& rightHandSide) {
	if (this != &rightHandSide) 
	{
		// pointers walking each set
		Node* leftCurr = head;
		Node* rightCurr = rightHandSide.head;

		// deletes what was in the current list
		clear(leftCurr);

		// after set is emptied, head is initialized again

		// inputs the values from the rhs into the current list
		while (rightCurr != NULL) {
			insert(rightCurr->data);
			rightCurr = rightCurr->next;
		}
	}
	return *this;
}

/**---------------- clear -----------------------------------------------------
@pre Needs a Node pointer, likely a head pointer.
@post None.
-----------------------------------------------------------------------------*/

void CompareList::clear(Node* current) {
	// traverses through the list and frees all memory allocations
	while (current != NULL) {
		Node* next = current->next;
		delete current->data;
		delete current;
		current = next;
	}
	head = NULL;
}

/**------------------- makeData -----------------------------------------------
@pre Valid input values > -1.
@post Inserts the Data into the list.
-----------------------------------------------------------------------------*/
void CompareList::makeData(const int byte, const char theChar) {
	// creates a data object and stores it into the list
	Data* listData = new Data(byte, theChar);
	insert(listData);
	delete listData;
}

/**------------------ compareLists --------------------------------------------
@param rightHandSide  The other list to compare with the current list.
@pre  Just needs a list to compare with.
@post Shows the matches and percent match; bytes and values 
	  are aligned over the top of each other to view matches.
-----------------------------------------------------------------------------*/
void CompareList::compareListPF(const CompareList& rightHandSide) {
	// variables that track the matches, total, and percent matches 
	int matches = 0, total = 0;
	double percent = 0.0;
	 
	// checks for empty lists and outputs the matches 
	if (rightHandSide.isEmpty() || this->isEmpty()) {
		cout << "  Matches: " << matches << endl;
		cout << "  Percent Match: " <<  percent << "%" << endl << endl;
	} else {
		// pointers to walk each list
		Node* leftCurr = head;
		Node* rightCurr = rightHandSide.head;
		// walk each list until the end of list(s), comparing each byte
		while(leftCurr != NULL && rightCurr != NULL)
		{
			// when they match, increment match and total, advance walkers
			if (*leftCurr->data == *rightCurr->data)
			{
				// this indicates a match
				cout << "~" << *leftCurr->data;
				matches++;
				total++;
				leftCurr = leftCurr->next;
				rightCurr = rightCurr->next;
			}
			// otherwise, increment total, advance walkers
			else
			{
				total++;
				leftCurr = leftCurr->next;
				rightCurr = rightCurr->next;
			}	
		}
		percent = ( (double) matches / (double)total ) * 100;
		cout << "\n  Matches: " << matches << endl;
		cout << "  Percent Match: " << setprecision(2) << fixed 
			  << percent << "%" << endl << endl;
	}
}

/**--------------------- compareConsec ----------------------------------------
@param file1, file2  The files that need to be compared.
@pre None.
@post Outputs the byte that concludes that the files did not match OR
	  that the files do match.
-----------------------------------------------------------------------------*/
void CompareList::compareConsec(ifstream& file1, ifstream& file2,
								const int size1, const int size2) {
	int smallerSize = size1;
	if (size1 > size2)
		smallerSize = size2;
									
	int byte = 0;
	bool match = true;
	char* file1Array = new char[size1+1];
	char* file2Array = new char[size2+1];
	bool readFile1 = readFile(file1, file1Array, size1);
	bool readFile2 = readFile(file2, file2Array, size2);

	if (readFile1 || readFile2) {
		for (; byte <= smallerSize; byte++) {
			if (file1Array[byte] != file2Array[byte]) {
				cout << "  At byte " << byte << " concludes the prospect "
					 << "did not match the target." << endl << endl;
				match = false;
				break;
			}
		}
		if (match)
			cout << "  Target and Prospect files are a match" << endl << endl;
	}
	delete [] file1Array;
	delete [] file2Array;
}
