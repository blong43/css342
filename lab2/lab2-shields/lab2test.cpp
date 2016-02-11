/**----------------------------------------------------------------------------
	@file lab2test.cpp
		  Test the constructors, operators, and functions of the SortSet
		  (Array and Linked List) implementations.
	@author Blong Thao and Albert Tyshler
	@course CSS 342 Shields
	@version 01/26/14
-----------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include "sortsetarray.h"
#include "sortsetlist.h"
using namespace std;

int main() {
	// tests for SortSet Array
	cout << "Testing SortSetArray:" << endl;
	SortSetArray A(4, 2, 10, 45, 20);
	SortSetArray B(3, 4, 5, 45, -1000);
	SortSetArray C;
	SortSetArray D(B);
	SortSetArray E(10, 7, 6, 8, 100);
	SortSetArray F(10, 4, 6, 8, 7);
	cout << "A: " << A << endl; // { 2 4 10 20 45}
	cout << "B: " << B << endl; // { 3 4 5 45}
	cout << "C: " << C << endl; // {}
	cout << "D: " << D << endl; // { 3 4 5 45}
	cout << "E: " << E << endl; // { 6 7 8 10 100}
	cout << "F: " << F << endl; // { 4 6 7 8 10}
	cout << "Inserting 3 to C " << C.insert(3) << endl;
	cout << "C: " << C << endl;
	cout << "Removing 3 from C" << C.remove(3) << endl;
	cout << "C: " << C << endl;
	cout << "Is set A empty? " << A.isEmpty() << endl;
	cout << "Is set C empty? " << C.isEmpty() << endl;
	cout << "Is 4 in set A? " << (A.isInSet(4) ? "Yes" : "No") << endl;
	cout << "Is 8 in set A? " << (A.isInSet(8) ? "Yes" : "No") << endl;
	cout << "A + B: " << A + B << endl; // { 2 3 4 5 10 20 45}
	cout << "A - B: " << A - B << endl; // { 2 3 5 10 20}
	cout << "A * B: " << A * B << endl; // { 4 45} 
	cout << "A == C: " << ((A == C) ? "Yes" : "No") << endl;
	cout << "A != C: " << ((A != C) ? "Yes" : "No") << endl;
	cout << "A = E * F + B: " << (A = E * F + B) << endl; // { 3 4 5 6 7 8 10 45}
	cout << "Write to C: (Type -1 to stop)" << endl;
	cin >> C;
	cout << "New C: " << C << endl;
	cout << "E + D - C: " << (E + D - C) << endl; // { depends on cin}
	cout << "C += B " << (C += B) << endl; // { 3 4 5 45} 
	cout << "D -= A " << (D -= B) << endl; // {}
	cout << "A *= B " << (A *= B) << endl; // { 3 4 5 45}
	cout << endl;

	// tests the SortSetList
	cout << "Testing SortSetList:" << endl;
	SortSetList AA(10, 20, 21);
	SortSetList BB(67, 20, 20, 10, 0);
	SortSetList CC(9, 10);
	SortSetList DD(CC);
	SortSetList EE;
	cout << "AA: " << AA << endl; // output: { 10 20 21}
	cout << "BB: " << BB << endl; // output: { 0 10 20 67}
	cout << "CC: " << CC << endl; // output: { 9 10}
	cout << "Is 10 in set AA? " << (AA.isInSet(10) ? "Yes" : "No") << endl;
	cout << "Is 15 in set AA? " << (AA.isInSet(15) ? "Yes" : "No") << endl;
	cout << "Is set AA empty? " << (AA.isEmpty() ? "Yes" : "No") << endl;
	cout << "Is set EE empty? " << (EE.isEmpty() ? "Yes" : "No") << endl;
	cout << "AA + BB " << AA + BB << endl; // output: { 0 10 20 21 67}
	cout << "AA - BB " << AA - BB << endl; // output: { 0 21 67}
	cout << "AA * BB " << AA * BB << endl; // output: { 10 20}
	AA = BB;
	cout << "AA = BB: " << AA << endl; // output: { 0 10 20 67}
	cout << "Is AA == BB? " << ((AA == BB) ? "Yes" : "No") << endl;
	cout << "Is AA != BB? " << ((AA != BB) ? "Yes" : "No") << endl;
	cout << "CC += BB: " << (CC += BB) << endl; // output: { 0 9 10 20 67}
	cout << "BB -= BB: " << (BB -= BB) << endl; // output: {}
	cout << "DD *= BB: " << (DD *= BB) << endl; // output: { 9 10}
	cout << "Write to CC: (To stop writing, type in -1) " << endl;
	cin >> CC;
	cout << "CC: " << CC << endl << endl; // output { something} 
	
	// write from file
	cout << "Testing I/O:" << endl;
	SortSetArray fileA;
	SortSetList fileLL;
	ifstream inputFile;
	inputFile.open ("inputtest.txt");
	inputFile >> fileA;
	inputFile >> fileLL;
	cout << "fileA: " << fileA << endl; // reads 1 3 4 7 8 9 22 55 56 66
	cout << "fileLL: " << fileLL << endl; // reads 9 22 99, end of file
	inputFile.close();

	// write to file
	cout << "Open outputtest.txt to see inputtest file printed over" << endl;
	ofstream file;
	file.open ("outputtest.txt");
	file << fileA << endl; // outputs { 1 3 4 7 8 9 22 55 56 66}
	file << fileLL << endl; // outputs { 9 22 99}
	file.close();

	return 0;
}
