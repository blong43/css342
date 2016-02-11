/**----------------------------------------------------------------------------
 @file lab3testlist.cpp
	Tests functions in Data and CompareList classes.

 @authors Blong Thao and Alber Tyshler
 @course CSS 342 Shields
 @version 1.0
 @date 02/09/14
-----------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include "comparelist.h"
using namespace std;

int main() {
	CompareList A, B, C, D;
	Data* data1 = new Data(0, 'B');
	Data* data2 = new Data(1, 'L');
	Data* data3 = new Data(2, 'O');
	Data* data4 = new Data(3, 'N');
	Data* data5 = new Data(4, 'G');
	Data* data6 = new Data(5, 'A');
	Data* data7 = new Data(6, 'L');
	Data* data8 = new Data(7, 'B');
	Data* data9 = new Data(8, 'E');
	Data* data10 = new Data(9, 'R');
	Data* data11 = new Data(10, 'T');
	Data* data12 = new Data;

	data1->insert(1, 'C');
	data2->insert(2, 'O');
	data3->insert(3, 'D');
	data4->insert(4, 'E');
	data5->remove(10, 'T');
	data11->remove(10, 'T');
	data12->remove(-1, 'T');

	A.insert(data1); // A: 1 C
	A.insert(data2); // A: 1 C  2 O
	A.insert(data3); // A: 1 C  2 O  3 D
	A.insert(data4); // A: 1 C  2 O  3 D  4 E
	A.insert(data5); // A: 1 C  2 O  3 D  4 E ; does not take dupe bytes
	A.insert(data12); // A: 1 C  2 O  3 D  4 E ; does not take -1 bytes

	B.insert(data6); // B: 5 A
	B.insert(data7); // B: 5 A  6 L
	B.insert(data8); // B: 5 A  6 L  7 B
	B.insert(data9); // B: 5 A  6 L  7 B  8 E  
	B.insert(data10); // B: 5 A  6 L  7 B  8 E  9 R
	B.insert(data11); // B: 5 A  6 L  7 B  8 E  9 R  10 T 

	C = A; // A: 1 C  2 O  3 D  4 E
	D = B; // B: 5 A  6 L  7 B  8 E  9 R  10 T 

	C.remove(data1); // A: 2 O  3 D  4 E
	C.remove(data3); // A: 2 O  4 E
	C.remove(data7); // A: 2 O  4 E
	
	D.remove(data6); // B: 6 L  7 B  8 E  9 R  10 T 
	D.remove(data1); // B: 6 L  7 B  8 E  9 R  10 T 

	cout << "List A:  " << A << endl;
	cout << "List B:  " << B << endl;
	cout << "List C:  " << C << endl;
	cout << "List D:  " << D << endl;
	cout << "\nIs list A equal to list B: " << (A == B ? "Yes" : "No") << endl;
	cout << "Is list A equal to list C: " << (A == B ? "Yes" : "No") << endl;
	cout << "Is list A equal to list D: " << (A == B ? "Yes" : "No") << endl;
	cout << "Is list B equal to list C: " << (A == B ? "Yes" : "No") << endl;
	
	cout << "\nAssign A = B = D" << endl;	
	A = B = D;

	cout << "List A: " << A << endl;
	cout << "\nIs list A equal to list B: " << (A == B ? "Yes" : "No") << endl;
	
	cout << "\nAssign B = C " << endl;
	B = C;

	cout << "List B: " << B << endl;
	cout << "\nIs list B equal to list C: " << (B == C ? "Yes" : "No") << endl;

	delete data1, delete data2,	delete data3, delete data4, delete data5,
	delete data6, delete data7,	delete data8, delete data9,	delete data10,
	delete data11, delete data12;

	return 0;
}

