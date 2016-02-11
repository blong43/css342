/**----------------------------------------------------------------------------
 @file lab3maintest.cpp
	Tests a few files with the sub-methods that are used in the lab3main.cpp.

 @authors Blong Thao and Alber Tyshler
 @course CSS 342 Shields
 @version 1.0
 @date 02/09/14
-----------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <ctime>
#include "comparelist.h"
using namespace std;

/**----------------------------------------------------------------------------
	Assumptions:
	-- Empty files are tests and have sizes of zero and outputs nothing.
	-- There are multiple sub-methods that are in the CompareList class that
	   should have been included in the main instead of the class:
	       compareListPF, buildListPF and compareConsec;
	   they just seemed to work better this way.
	-- Tested numbers being read into the list and they do work.
-----------------------------------------------------------------------------*/


int findSize(ifstream&);
void resetFile(ifstream&);
void clockElapsed(clock_t, clock_t);

int main() {
	clock_t timeStartPF, timeEndPF, timeStartCon, timeEndCon;
	const char s0_FILE [] = "target1.txt", t0_FILE [] = "target2.txt", 
		       p0_FILE [] = "prospect0.txt", p1_FILE [] = "prospect1.txt",
			   emptyFile[] = "testempty.txt";
	ifstream s0File(s0_FILE), t0File(t0_FILE),
		     p0File(p0_FILE), p1File(p1_FILE),
			 eFile(emptyFile);

	CompareList A, B, C, D, E;
	int t1Size = findSize(s0File), t2Size = findSize(t0File),
		p0Size = findSize(p0File), p1Size = findSize(p1File),
		eSize = findSize(eFile);

	A.buildListPF(s0File), B.buildListPF(t0File), 
	C.buildListPF(p0File), D.buildListPF(p1File),
	E.buildListPF(eFile);

	cout << "Target1: " << s0_FILE << " File size: " << t1Size << endl;
	cout << "Target2: " << t0_FILE << " File size: " << t2Size << endl;
	cout << "Prospect0: " << p0_FILE << " File size: " << p0Size << endl;
	cout << "Prospect1: " << p1_FILE << " File size: " << p1Size << endl;
	cout << "Prospect2: " << emptyFile << " File size: " << eSize << endl;

	cout << "Target1:   " << A << endl;
	cout << "Target2:   " << B << endl;
	cout << "Prospect0:  " << C << endl;
	cout << "Prospect1:  " << D << endl;
	cout << "Prospect2:  " << E << endl << endl;

	timeStartPF = clock();
	cout << "Comparing Target1 and Prospect0: " << endl;
	A.compareListPF(C);
	cout << "Comparing Target2 and Prospect0: " << endl;
	B.compareListPF(C);
	cout << "Comparing Target1 and Prospect1: " << endl;
	A.compareListPF(D);
	cout << "Comparing Target2 and Prospect1: " << endl;
	B.compareListPF(D);
	cout << "Comparing Target1 and Prospect2: " << endl;
	A.compareListPF(E);
	cout << "Comparing Target2 and Prospect2: " << endl;
	B.compareListPF(E);

	timeEndPF = clock();
	cout << "PrimeFib List Comparisons: ";
	clockElapsed(timeStartPF, timeEndPF);

	timeStartCon = clock();
	resetFile(s0File);
	resetFile(p0File);
	cout << "Comparing each byte for target1 and prospect0: " << endl;
	A.compareConsec(s0File, p0File, t1Size, p0Size);
	
	resetFile(t0File);
	resetFile(p0File);
	cout << "Comparing each byte for target2 and prospect0: " << endl;
	B.compareConsec(t0File, p0File, t2Size, p0Size);

	resetFile(s0File);
	resetFile(p1File);
	cout << "Comparing each byte for target1 and prospect1: " << endl;
	A.compareConsec(s0File, p1File, t1Size, p1Size);
	
	resetFile(t0File);
	resetFile(p1File);
	cout << "Comparing each byte for target2 and prospect1: " << endl;
	B.compareConsec(t0File, p1File, t2Size, p1Size);

	resetFile(s0File);
	resetFile(eFile);
	cout << "Comparing each byte for target1 and prospect2: " << endl;
	A.compareConsec(s0File, eFile, t1Size, eSize);
	
	resetFile(t0File);
	resetFile(eFile);
	cout << "Comparing each byte for target2 and prospect2: " << endl;
	B.compareConsec(t0File, eFile, t2Size, eSize);

	timeEndCon = clock();
	cout << "Consecutive List Comparisons: ";
	clockElapsed(timeStartCon, timeEndCon);

	return 0;
}

/**-------------- resetFile ---------------------------------------------------
@param file The file that has its cursor reset.
-----------------------------------------------------------------------------*/
void resetFile(ifstream& file) {
	file.clear();
	file.seekg(0, ios::beg);
}

/**--------------- findSize ---------------------------------------------------
@param file The file that is looked into to find the size.
@return streamoff, similar to an integer.
-----------------------------------------------------------------------------*/
int findSize(ifstream& file) {
	file.seekg(0, file.end);
	int length = (int)file.tellg();
	file.seekg(0, file.beg);
	resetFile(file);
	return length;
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
   cout << "Time Elapsed: " << ticks << " clock ticks ~= " 
        << (float)ticks / (float)CLOCKS_PER_SEC << " seconds\n\n"; 
}
