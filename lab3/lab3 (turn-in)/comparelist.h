/**----------------------------------------------------------------------------
 @file comparelist.h
	The file that contains most of the function declaration the CompareList 
	class uses to run the application and the test cases.

 @authors Blong Thao and Alber Tyshler
 @course CSS 342 Shields
 @version 1.0
 @date 02/09/14
-----------------------------------------------------------------------------*/

#ifndef COMPARELIST_H
#define COMPARELIST_H
#include <iostream>
#include <fstream>
#include "data.h"
using namespace std;

/**----------------------------------------------------------------------------
	Assumptions:
	-- struct Node holds a Data pointer and a Node pointer; these can only be
	   used within the CompareList class.
	-- Throughout the application head is assumed to first be initialized to 
	   NULL to make sure there are no errors/memory leaks.
	-- Data class has these functions that can be used with it: ==, !=, <,
	   insert, remove, and cout.
	-- clear function in CompareList frees memory allocations in a list.
	-- makeData function in CompareList creates a Data pointer to be inserted
	   into any lists.
	-- readFile function in CompareList reads the file and spits out an array
	   of chars that are in that file, -1 means that the file ended.
	-- Each primeFib list displays: 2 A	   3 B   5 C   514299 Z   ; for all 9
	   primeFib numbers.
	-- buildListPF inserts all the valid bytes into the list
	-- The list compare functions compares only the PFLists and find the matches;
	   prints out the percentage of matches. While the other compare all the
	   bytes consecutively until there is not a match.

-----------------------------------------------------------------------------*/

class CompareList
{
	private:
	struct Node {
		Data* data;
		Node* next;
	};
	Node* head;
	void clear(Node*);
	void makeData(const int, const char);
	bool readFile(ifstream&, char*, const int);

	// prints the list in a particular type format shown in assumptions
	friend ostream& operator<<(ostream& output, const CompareList& theList) {
		Node* current = theList.head;
		while (current != NULL) {
			output << *current->data;
			current = current->next;
		}
		return output;
	}
public:
	// Constructors: Default, Copy, Destructors
	CompareList();
	~CompareList();

	// Operators: equality, inequality
	bool operator==(const CompareList &);
	bool operator!=(const CompareList &);

	// insert, remove, isEmpty
	bool insert(Data*);
	bool remove(Data*);
	bool isEmpty() const;

	// Assignment operator and the buildList
	CompareList& operator=(const CompareList&);
	CompareList& buildListPF(ifstream&);

	// compares the consecutive bytes and PF list
	void compareListPF(const CompareList&);
	void compareConsec(ifstream&, ifstream&, const int, const int);
};
#endif
