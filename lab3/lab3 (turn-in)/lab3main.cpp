/**----------------------------------------------------------------------------
 @file lab3main.cpp
	The file that runs the applicaton using all need functions
	to complete all instructions for lab3 in the lab3main.cpp.

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
	Time Comparisons with Consecutive and PF byte comparisons:
	-- As a right now the consecutive byte comparison is taking more time
	   to compare since there are more bytes to compare.
	-- The PF byte comparisons only compare nine nodes or less so that makes
	   the PF byte comparisons seem faster at this time.
	-- The PF byte comparisons would take longer if there were more data for
	   it to compare, which we conclude takes a Big-O(n^2) because it runs
	   through a look checking for indices from the file that match the PF
	   byte numbers and then runs another loop to insert it into the list.
	-- The consecutive byte comparisons take a Big-O(n) only because it grows
	   linearly to how many comparisons are needed, as well as to the amount
	   of comparisons needs = to the smaller file size.

	-- Did not use all prospect files that were given, but uses half of them.
-----------------------------------------------------------------------------*/

int findSize(ifstream&);
void resetFile(ifstream&);
void clockElapsed(clock_t, clock_t);

int main() {
	// timers
	clock_t timeStartPF, timeEndPF, timeStartCon, timeEndCon;

	// All files, targets and prospects
	const char s0_FILE[] = "s0.txt", t0_FILE[] = "t0.txt", 
		p0_FILE[] = "c1.txt", p1_FILE[] = "c2.txt", p2_FILE[] = "c3.txt",
		p3_FILE[] = "c4.txt", p4_FILE[] = "c5.txt", p5_FILE[] = "c6.txt",
		p6_FILE[] = "c7.txt", p7_FILE[] = "c8.txt", p8_FILE[] = "h1.txt", 
		p9_FILE[] = "h2.txt", p10_FILE[] = "license.txt", 
		p11_FILE[] = "s1.txt", p12_FILE[] = "s10.txt", 
		p13_FILE[] = "s11.txt", p14_FILE[] = "s12.txt", 
		p15_FILE[] = "t1.txt";
	
	// files stored into an ifstream
	ifstream s0File(s0_FILE), t0File(t0_FILE), p0File(p0_FILE), 
		p1File(p1_FILE), p2File(p2_FILE), p3File(p3_FILE), p4File(p4_FILE),
		p5File(p5_FILE), p6File(p6_FILE), p7File(p7_FILE), p8File(p8_FILE), 
		p9File(p9_FILE), p10File(p10_FILE), p11File(p11_FILE), 
		p12File(p12_FILE), p13File(p13_FILE), p14File(p14_FILE), 
		p15File(p15_FILE);

	CompareList A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R;

	// the file sizes
	int t1Size = findSize(s0File), t2Size = findSize(t0File), 
		p0Size = findSize(p0File), p1Size = findSize(p1File),
		p2Size = findSize(p2File), p3Size = findSize(p1File),
		p4Size = findSize(p4File), p5Size = findSize(p1File),
		p6Size = findSize(p6File), p7Size = findSize(p1File),
		p8Size = findSize(p8File), p9Size = findSize(p1File),
		p10Size = findSize(p10File), p11Size = findSize(p11File),
		p12Size = findSize(p12File), p13Size = findSize(p13File),
		p14Size = findSize(p14File), p15Size = findSize(p15File);
	
	A.buildListPF(s0File), B.buildListPF(t0File), C.buildListPF(p0File), 
	D.buildListPF(p1File), E.buildListPF(p2File), F.buildListPF(p3File),
	G.buildListPF(p4File), H.buildListPF(p5File); I.buildListPF(p6File),
	J.buildListPF(p7File), K.buildListPF(p8File), L.buildListPF(p9File),
	M.buildListPF(p10File), N.buildListPF(p11File), O.buildListPF(p12File),
	P.buildListPF(p13File), Q.buildListPF(p14File); R.buildListPF(p15File),

	cout << "Target1:   " << s0_FILE << " File size: " << t1Size << endl;
	cout << "Target2:   " << t0_FILE << " File size: " << t2Size << endl;
	cout << "Prospect0: " << p0_FILE << " File size: " << p0Size << endl;
	cout << "Prospect1: " << p1_FILE << " File size: " << p1Size << endl;
	cout << "Prospect2: " << p2_FILE << " File size: " << p2Size << endl;
	cout << "Prospect3: " << p3_FILE << " File size: " << p3Size << endl;
	cout << "Prospect4: " << p4_FILE << " File size: " << p4Size << endl;
	cout << "Prospect5: " << p5_FILE << " File size: " << p5Size << endl;
	cout << "Prospect6: " << p6_FILE << " File size: " << p6Size << endl;
	cout << "Prospect7: " << p7_FILE << " File size: " << p7Size << endl;
	cout << "Prospect8: " << p8_FILE << " File size: " << p8Size << endl;
	cout << "Prospect9: " << p9_FILE << " File size: " << p9Size << endl;
	cout << "Prospect10: " << p10_FILE << " File size: " << p10Size << endl;
	cout << "Prospect11: " << p11_FILE << " File size: " << p11Size << endl;
	cout << "Prospect12: " << p12_FILE << " File size: " << p12Size << endl;
	cout << "Prospect13: " << p13_FILE << " File size: " << p13Size << endl;
	cout << "Prospect14: " << p14_FILE << " File size: " << p14Size << endl;
	cout << "Prospect15: " << p15_FILE << " File size: " << p15Size << endl;

	cout << "\nTarget1:    " << A << endl;
	cout << "Target2:    " << B << endl;
	cout << "Prospect0:  " << C << endl;
	cout << "Prospect1:  " << D << endl;
	cout << "Prospect2:  " << E << endl;
	cout << "Prospect3:  " << F << endl;
	cout << "Prospect4:  " << G << endl;
	cout << "Prospect5:  " << H << endl;
	cout << "Prospect6:  " << I << endl;
	cout << "Prospect7:  " << J << endl;
	cout << "Prospect8:  " << K << endl;
	cout << "Prospect9:  " << L << endl;
	cout << "Prospect10: " << M << endl;
	cout << "Prospect11: " << N << endl;
	cout << "Prospect12: " << O << endl;
	cout << "Prospect13: " << P << endl;
	cout << "Prospect14: " << Q << endl;
	cout << "Prospect15: " << R << endl;

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
	cout << "Comparing Target1 and Prospect3: " << endl;
	A.compareListPF(F);
	cout << "Comparing Target2 and Prospect3: " << endl;
	B.compareListPF(F);
	cout << "Comparing Target1 and Prospect4: " << endl;
	A.compareListPF(G);
	cout << "Comparing Target2 and Prospect4: " << endl;
	B.compareListPF(G);
	cout << "Comparing Target1 and Prospect5: " << endl;
	A.compareListPF(H);
	cout << "Comparing Target2 and Prospect5: " << endl;
	B.compareListPF(H);
	cout << "Comparing Target1 and Prospect6: " << endl;
	A.compareListPF(I);
	cout << "Comparing Target2 and Prospect6: " << endl;
	B.compareListPF(I);
	cout << "Comparing Target1 and Prospect7: " << endl;
	A.compareListPF(J);
	cout << "Comparing Target2 and Prospect7: " << endl;
	B.compareListPF(J);
	cout << "Comparing Target1 and Prospect8: " << endl;
	A.compareListPF(K);
	cout << "Comparing Target2 and Prospect8: " << endl;
	B.compareListPF(K);
	cout << "Comparing Target1 and Prospect9: " << endl;
	A.compareListPF(L);
	cout << "Comparing Target2 and Prospect9: " << endl;
	B.compareListPF(L);
	cout << "Comparing Target1 and Prospect10: " << endl;
	A.compareListPF(M);
	cout << "Comparing Target2 and Prospect10: " << endl;
	B.compareListPF(M);
	cout << "Comparing Target1 and Prospect11: " << endl;
	A.compareListPF(N);
	cout << "Comparing Target2 and Prospect11: " << endl;
	B.compareListPF(N);
	cout << "Comparing Target1 and Prospect12: " << endl;
	A.compareListPF(O);
	cout << "Comparing Target2 and Prospect12: " << endl;
	B.compareListPF(O);
	cout << "Comparing Target1 and Prospect13: " << endl;
	A.compareListPF(P);
	cout << "Comparing Target2 and Prospect13: " << endl;
	B.compareListPF(P);
	cout << "Comparing Target1 and Prospect14: " << endl;
	A.compareListPF(Q);
	cout << "Comparing Target2 and Prospect14: " << endl;
	B.compareListPF(Q);
	cout << "Comparing Target1 and Prospect15: " << endl;
	A.compareListPF(R);
	cout << "Comparing Target2 and Prospect15: " << endl;
	B.compareListPF(R);
	timeEndPF = clock();
	cout << "PrimeFib List Comparisons: ";
	clockElapsed(timeStartPF, timeEndPF);

	timeStartCon = clock();
	resetFile(s0File);
	resetFile(p0File);
	cout << "Comparing each byte for target1 and prospect1: " << endl;
	A.compareConsec(s0File, p0File, t1Size, p0Size);
	resetFile(t0File);
	resetFile(p0File);
	cout << "Comparing each byte for target2 and prospect1: " << endl;
	B.compareConsec(t0File, p0File, t2Size, p0Size);
	resetFile(s0File);
	resetFile(p1File);
	cout << "Comparing each byte for target1 and prospect2: " << endl;
	A.compareConsec(s0File, p1File, t1Size, p1Size);
	resetFile(t0File);
	resetFile(p1File);
	cout << "Comparing each byte for target2 and prospect2: " << endl;
	B.compareConsec(t0File, p1File, t2Size, p1Size);
	resetFile(s0File);
	resetFile(p2File);
	cout << "Comparing each byte for target1 and prospect3: " << endl;
	A.compareConsec(s0File, p2File, t1Size, p2Size);
	resetFile(t0File);
	resetFile(p2File);
	cout << "Comparing each byte for target2 and prospect3: " << endl;
	B.compareConsec(t0File, p2File, t2Size, p2Size);
	resetFile(s0File);
	resetFile(p3File);
	cout << "Comparing each byte for target1 and prospect4: " << endl;
	A.compareConsec(s0File, p3File, t1Size, p3Size);
	resetFile(t0File);
	resetFile(p3File);
	cout << "Comparing each byte for target2 and prospect4: " << endl;
	B.compareConsec(t0File, p3File, t2Size, p3Size);
	resetFile(s0File);
	resetFile(p4File);
	cout << "Comparing each byte for target1 and prospect5: " << endl;
	A.compareConsec(s0File, p4File, t1Size, p4Size);
	resetFile(t0File);
	resetFile(p4File);
	cout << "Comparing each byte for target2 and prospect5: " << endl;
	B.compareConsec(t0File, p4File, t2Size, p4Size);
	resetFile(s0File);
	resetFile(p5File);
	cout << "Comparing each byte for target1 and prospect6: " << endl;
	A.compareConsec(s0File, p5File, t1Size, p5Size);
	resetFile(t0File);
	resetFile(p5File);
	cout << "Comparing each byte for target2 and prospect6: " << endl;
	B.compareConsec(t0File, p5File, t2Size, p5Size);
	resetFile(s0File);
	resetFile(p6File);
	cout << "Comparing each byte for target1 and prospect7: " << endl;
	A.compareConsec(s0File, p6File, t1Size, p6Size);
	resetFile(t0File);
	resetFile(p6File);
	cout << "Comparing each byte for target2 and prospect7: " << endl;
	B.compareConsec(t0File, p6File, t2Size, p6Size);
	resetFile(s0File);
	resetFile(p7File);
	cout << "Comparing each byte for target1 and prospect8: " << endl;
	A.compareConsec(s0File, p7File, t1Size, p7Size);
	resetFile(t0File);
	resetFile(p7File);
	cout << "Comparing each byte for target2 and prospect8: " << endl;
	B.compareConsec(t0File, p7File, t2Size, p7Size);
	resetFile(s0File);
	resetFile(p8File);
	cout << "Comparing each byte for target1 and prospect9: " << endl;
	A.compareConsec(s0File, p8File, t1Size, p8Size);
	resetFile(t0File);
	resetFile(p8File);
	cout << "Comparing each byte for target2 and prospect9: " << endl;
	B.compareConsec(t0File, p8File, t2Size, p8Size);
	resetFile(s0File);
	resetFile(p9File);
	cout << "Comparing each byte for target1 and prospect10: " << endl;
	A.compareConsec(s0File, p9File, t1Size, p9Size);
	resetFile(t0File);
	resetFile(p9File);
	cout << "Comparing each byte for target2 and prospect10: " << endl;
	B.compareConsec(t0File, p9File, t2Size, p9Size);
	resetFile(s0File);
	resetFile(p10File);
	cout << "Comparing each byte for target1 and prospect11: " << endl;
	A.compareConsec(s0File, p10File, t1Size, p10Size);
	resetFile(t0File);
	resetFile(p10File);
	cout << "Comparing each byte for target2 and prospect11: " << endl;
	B.compareConsec(t0File, p10File, t2Size, p10Size);
	resetFile(s0File);
	resetFile(p11File);
	cout << "Comparing each byte for target1 and prospect12: " << endl;
	A.compareConsec(s0File, p11File, t1Size, p11Size);
	resetFile(t0File);
	resetFile(p11File);
	cout << "Comparing each byte for target2 and prospect12: " << endl;
	B.compareConsec(t0File, p11File, t2Size, p11Size);
	resetFile(s0File);
	resetFile(p12File);
	cout << "Comparing each byte for target1 and prospect13: " << endl;
	A.compareConsec(s0File, p12File, t1Size, p12Size);
	resetFile(t0File);
	resetFile(p12File);
	cout << "Comparing each byte for target2 and prospect13: " << endl;
	B.compareConsec(t0File, p12File, t2Size, p12Size);
	resetFile(s0File);
	resetFile(p13File);
	cout << "Comparing each byte for target1 and prospect14: " << endl;
	A.compareConsec(s0File, p13File, t1Size, p13Size);
	resetFile(t0File);
	resetFile(p13File);
	cout << "Comparing each byte for target2 and prospect14: " << endl;
	B.compareConsec(t0File, p13File, t2Size, p13Size);
	resetFile(s0File);
	resetFile(p14File);
	cout << "Comparing each byte for target1 and prospect15: " << endl;
	A.compareConsec(s0File, p14File, t1Size, p14Size);
	resetFile(t0File);
	resetFile(p14File);
	cout << "Comparing each byte for target2 and prospect15: " << endl;
	B.compareConsec(t0File, p14File, t2Size, p14Size);

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
