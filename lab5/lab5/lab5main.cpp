/**----------------------------------------------------------------------------
@file lab5main.cpp

@author Blong Thao and Albert Tyshler
@course CSS 342 Shields
@date   03/06/14
-----------------------------------------------------------------------------*/

#include "tbst.h"
#include <cstdlib>
#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cctype>
//#include <sys/time.h>  // for gettimeofday() and timeval
#include <ctime>       // for  clock()and clock_t and CLOCKS_PER_SEC
#define DEFAULT_SIZE 1000000
#define printAmt 21
int counter = 0;
int size = 0;
bool debug = false;
const string intro = "//////////////////////////////////////////////////////\n"
		  "////////////////  lab5test.cpp  //////////////////////\n" 
		  "//////////////////////////////////////////////////////\n"
		  "/////// Authors: Albert Tyshler and Blong Thao ///////\n"
		  "//////// Purpose: To print tokens from a tree/////////\n"
		  "/////////// in most/least frequency order ////////////\n"
		  "//////////////////////////////////////////////////////\n\n";
const char DEBUG_ARG[] = "DEBUG";
const char FILE_ARG[] = "FILE";
const char HAMLET_FILE[] = "hamlet.txt";
const char B0_FILE[] = "b0.txt";
const char TO_BE_FILE[] = "tobeShort.txt";
const string debugSet = "Debug is set to: ";
const string arguments = "Needed more arguements, will now use default size.";
const string negativeArg = "Size must be positive, size is: ";
const string reSize = "Size is going to resize to default size";
void introduction();
//void elapsed(timeval&, timeval&);
void clockElapsed(clock_t, clock_t);
void displaySevenPerLine(NodeData*);
void buildTree(ThreadedBST&, int);
void tokenize(const char*, ThreadedBST&);
void showResults(ThreadedBST&);
int partition(NodeData*, int, int);
void quickSort(NodeData*, int, int);
void displayLargest21(NodeData*, int, bool, int);
void displaySmallest21(NodeData*, int, bool, int);

/**
The main routine: outputs the 21 least and most frequencies.
	Will display the time it takes to display all frequencies
	and print out the output into a file called lab5out.txt.
*/
int main(int argc, char* argv[]) {
	
	if ( strcmp(argv[argc-1], DEBUG_ARG) == 0) {
		debug = true;
		cout << debugSet << debug << endl;
	}

	//if (argc < 2) {
	//	size = DEFAULT_SIZE;
	//	cerr << arguments << argv[0] << endl;
	//} else {
	//	size = atoi( argv[1] );
	//	if ( size <= 0 ) {
	//		cerr << negativeArg << size << endl << reSize;
	//		size = DEFAULT_SIZE;
	//	}
	//}
	cout << intro;
	clock_t startTime, endTime;

	startTime = clock();
	for (int cmdLineArgs = 1; cmdLineArgs < argc; cmdLineArgs++) {
		ThreadedBST freqTree;
		tokenize(argv[cmdLineArgs], freqTree);
		showResults(freqTree);
		cout << argv[cmdLineArgs] << endl;
	}
	endTime = clock();
	clockElapsed(startTime, endTime);
	//cout << argv[0] << endl;
	
	return 0;
}

void clockElapsed( clock_t clockTimeStart, 
                   clock_t clockTimeEnd ) {  // uses less precise ctime
   clock_t ticks;
   ticks = clockTimeEnd - clockTimeStart;
   cout << "clockElapsed:clock time elapsed: " << ticks << " clock ticks ~= " 
        << (float)ticks / (float)CLOCKS_PER_SEC << " seconds\n"; 
} // clockElapsed

void tokenize(const char* theFile, ThreadedBST& freqTree) 
{	
	ifstream inputFile (theFile);
	if (inputFile.is_open())
	{
		while ( inputFile.good() )
		{
		string wordOrPunc;
		inputFile >> wordOrPunc;
			if (inputFile.eof())
				break;
			if (wordOrPunc.length() > 2 
			   && (ispunct(wordOrPunc.at(wordOrPunc.length() - 2)) 
			   || (ispunct(wordOrPunc.at(wordOrPunc.length() - 1)) ))) {
				NodeData word(wordOrPunc.substr((wordOrPunc.length() - 1), 2));
				NodeData punc(wordOrPunc.substr(0, wordOrPunc.length()-2 ));
				freqTree.add(&word);
				freqTree.add(&punc);
			}
			else {
				NodeData word(wordOrPunc);
				freqTree.add(&word);
			}
			counter++;
		}
		inputFile.close();  
	}
	else 
		cout << "Unable to open file";
	
	freqTree.~ThreadedBST();

	//void (*Display)(NodeData*) = &displaySevenPerLine;
	//freqTree.iterInorderTraversal(Display);
	//cout << endl;
}

void showResults(ThreadedBST& freqTree)
{
	cout << "\n\nFewest 21 Frequencies:\n\n";
	NodeData* freqArray = new NodeData[DEFAULT_SIZE];
	freqTree.TreeToArray(freqArray, DEFAULT_SIZE);

	bool donePrinting = false;
	int index = 0;
	int itemDisplayCount = 0;
	displaySmallest21(freqArray, index, donePrinting, itemDisplayCount);

	cout << "\n\nLargest 21 Frequencies:\n\n";
	displayLargest21(freqArray, index, donePrinting, itemDisplayCount);
	cout << endl;
	delete [] freqArray;
	counter = 0;
}

/**------------------------- displayLargest21 ---------------------------------
	Prints out the data and only seven per line.
-----------------------------------------------------------------------------*/
void displayLargest21(NodeData* freqArray, int index, bool allPrinted,
						 int itemDisplayCount) {
	quickSort(freqArray, counter, 0);
	index = counter-1;
	allPrinted = false;
	itemDisplayCount = 0;
	while (!allPrinted && index > 0) {
		if (freqArray[index].getToken() == " ");
		else {
			cout << "[" << freqArray[index] << "] ";
			itemDisplayCount++;
			if (itemDisplayCount % 7 == 0)
				cout << endl;
			if (itemDisplayCount == printAmt)
				allPrinted = true;
		}
		index--;
	}
}

/**------------------------- displaySmallest21 ---------------------------------
	Prints out the data and only seven per line.
-----------------------------------------------------------------------------*/
void displaySmallest21(NodeData* freqArray, int index, bool allPrinted,
						 int itemDisplayCount) {
	quickSort(freqArray, 0, counter);
	index = 0;
	allPrinted = false;
	itemDisplayCount = 0;
	while (!allPrinted && index < counter) {
		if (freqArray[index].getToken() == " ");
		else {
			cout << "[" << freqArray[index] << "] ";
			itemDisplayCount++;
			if (itemDisplayCount % 7 == 0)
				cout << endl;
			if (itemDisplayCount == printAmt)
				allPrinted = true;
		}
		index++;
	}
}

	//// write from file
	//cout << "Testing I/O:" << endl;
	//SortSetArray fileA;
	//SortSetList fileLL;
	//ifstream inputFile;
	//inputFile.open ("inputtest.txt");
	//inputFile >> fileA;
	//inputFile >> fileLL;
	//cout << "fileA: " << fileA << endl; // reads 1 3 4 7 8 9 22 55 56 66
	//cout << "fileLL: " << fileLL << endl; // reads 9 22 99, end of file
	//inputFile.close();

	//// write to file
	//cout << "Open outputtest.txt to see inputtest file printed over" << endl;
	//ofstream file;
	//file.open ("outputtest.txt");
	//file << fileA << endl; // outputs { 1 3 4 7 8 9 22 55 56 66}
	//file << fileLL << endl; // outputs { 9 22 99}
	//file.close();

//const string negativeArg = "Size must be positive, size is: ";
//const string reSize = "Size is going to resize to default size";
/**------------------------------ partition -----------------------------------
	Partitions the array[first..last]
	@param input The given array
	@param left The left most element to consider in the array
	@param right The right most element to consider in the array
	@pre unchanged, unsorted array, input.
	@post finds the final position for the pivot element, which it returns.
-----------------------------------------------------------------------------*/
int partition(NodeData* input, int left, int right)
{
	int pivot = input[right].getCount();
	while ( left < right )
	{
		while ( input[left].getCount() < pivot )
			left++;

		while ( input[right].getCount() > pivot )
			right--;

		if ( input[left].getCount() == input[right].getCount() )
			left++;
		else if ( left < right )
		{
			NodeData tmp = input[left];
			input[left] = input[right];
			input[right] = tmp;
		}
	}
	return right;
}

/**------------------------------ quickSort -----------------------------------
	Sorts an array into ascending order. 
	@param input The given array
	@param first The first element to consider in the array
	@param last The last element to consider in the array
	@pre theArray[first..last] is an array.
	@post theArray[first..last] is sorted.
-----------------------------------------------------------------------------*/
void quickSort(NodeData* input, int first, int last)
{
    if ( first < last )
    {
        int pivotIndex = partition(input, first, last);        
        quickSort(input, first, pivotIndex-1);
        quickSort(input, pivotIndex+1, last);
    }
}
