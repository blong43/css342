/**----------------------------------------------------------------------------
@file lab5test.cpp

@author Blong Thao and Albert Tyshler
@course CSS 342 Shields
@date   03/06/14
-----------------------------------------------------------------------------*/

#include "tbst.h"
#include <cstdlib>
#include <string.h>
#define MAX_SIZE 52
#define DEFAULT_SIZE 13
#define printAmt 7
int counter = 0;
int size = 0;
bool debug = false;
const char DEBUG_ARG[] = "DEBUG";
const char FILE_ARG[] = "FILE";
const string debugSet = "Debug is set to: ";
const string arguments = "Needed more arguements, will now use default size.";
const string negativeArg = "Size must be positive, size is: ";
const string reSize = "Size is going to resize to default size";
const string introduction = " ///////////////////////////"
							"////////////////////////////////\n"
		  " //////////////////  lab5test.cpp  /////////////////////////\n" 
		  " ///////////////////////////////////////////////////////////\n\n";
NodeData items[] = {NodeData("A",1),NodeData("B",2),NodeData("C",3),
	NodeData("D",4),NodeData("E",5),NodeData("F",6),NodeData("G",7),
	NodeData("H",8),NodeData("I",9),NodeData("J",10),NodeData("K",11),
	NodeData("L",12),NodeData("M",13),NodeData("N",14),NodeData("O",15),
	NodeData("P",16),NodeData("Q",17),NodeData("R",18),NodeData("S",19),
	NodeData("T",20),NodeData("U",21),NodeData("V",22),NodeData("W",23),
	NodeData("X",24),NodeData("Y",25),NodeData("Z",26),NodeData("a",27),
	NodeData("b",28),NodeData("c",29),NodeData("d",30),NodeData("e",31),
	NodeData("f",32),NodeData("g",33),NodeData("h",34),NodeData("i",35),
	NodeData("j",36),NodeData("k",37),NodeData("l",38),NodeData("m",39),
	NodeData("n",40),NodeData("o",41),NodeData("p",42),NodeData("q",43),
	NodeData("r",44),NodeData("s",45),NodeData("t",46),NodeData("u",47),
	NodeData("w",48),NodeData("v",49),NodeData("x",50),NodeData("y",51),
	NodeData("z",52)};
void buildTree(ThreadedBST&, int);
void swapND(NodeData&, NodeData&);
void buildRandTree(ThreadedBST&, int);
void evensDeleter(ThreadedBST&);
void display(NodeData*);
void displaySevenPerLine(NodeData*);
void randomTreeAndDeleteEvens(int);
void traversals(int);
void testCases();

/**
Executes the test code for the TBST
@param argc  The amount of arguments in the array.
@param argv  Holds the number of arguments that is being passed into the program.
*/
int main(int argc, char* argv[]) {
	
	if ( strcmp(argv[argc-1], "DEBUG") == 0) {
		debug = true;
		cout << debugSet << debug << endl;
	}
	if (argc < 2) {
		size = DEFAULT_SIZE;
		cerr << arguments << argv[0] << endl;
	} else {
		size = atoi( argv[1] );
		if ( size <= 0 ) {
			cerr << negativeArg << size << endl << reSize;
			size = DEFAULT_SIZE;
		}
	}

	srand(size);


	cout << introduction << endl;
	traversals(size);
	randomTreeAndDeleteEvens(size);
	testCases();

	return 0;
}



/**
Builds the tree by adding in items to the tree.
*/
void buildTree(ThreadedBST &tree, int size)  {
	for (int pos = 0; pos < size; pos++)
		tree.add(&items[pos]);
}

/**
Used to swap NodeData objects to isolate numbers that have been used
in the random number generator, creates unique numbers.
*/
void swapND(NodeData& back, NodeData& front) {
	NodeData temp = front;
	front = back;
	back = temp;
}

/**
Builds the tree that adds random NodeData items.
*/
void buildRandTree(ThreadedBST &tree, int theSize) {
	if (theSize == 0)
		cerr << "Size is zero, no tree to be built\n";
	
	int maxRand = MAX_SIZE-1;
	// builds the tree in random order
	for (int nodes = 0; nodes < theSize; nodes++) {
		// random number generator
		int temp = (maxRand < -1) ? rand() : rand() % (maxRand-nodes);

		if (debug) 
			cout << "Random entry: " << items[temp] << ", ";
		tree.add(&items[temp]);
		swapND(items[temp], items[maxRand-nodes]);
	}
	cout << endl;
}

/**
Deletes all the evens in the second tree, the one that copied
the random tree.
*/
void evensDeleter(ThreadedBST &tree) {
	const int EVENS = 2;

	// checks the entire tree and removes evens
	for (int nodes = 0; nodes < MAX_SIZE; nodes++)
	{
		if (tree.contains(&items[nodes])) {
			if (items[nodes].getCount() % EVENS == 0) {
				cout << "Remove: " << items[nodes] << "\n";
				//tree.remove(&items[nodes]);
			}
		}
	}
}


/**------------------------- displaySevenPerLine ------------------------------
	Prints out the data per visit and only seven per line.
	@param anItem The item that is being displayed.
	@pre   The object cannot have zero frequency and be printed.
	@post  The object is printed.
-----------------------------------------------------------------------------*/
void displaySevenPerLine(NodeData* anItem) {

	counter++;
	display(anItem);
	if (counter % printAmt == 0)
		cout << endl;
}

/**------------------------- display ------------------------------------------
	Prints out the data per visit.
	@param anItem The item that is being displayed.
	@pre   The object cannot have zero frequency and be printed.
	@post  The object is printed.
-----------------------------------------------------------------------------*/
void display(NodeData* anItem) {
	cout << "[" << *anItem << "] ";
}


/**
Uses the iterative inorder traversal to print out the tree with seven
items per line.
*/
void printTree(ThreadedBST &tree) {
	void (*Display)(NodeData*) = &displaySevenPerLine;
	tree.iterInorderTraversal(Display);
	cout << endl;
}

/**
Generates a tree with random elements, but will sort them correctly,
will not be a degenerate tree.
*/
void randomTreeAndDeleteEvens(int size) {
	// makes a tree that take in random input
	ThreadedBST randTree;
	buildRandTree(randTree, size);
	cout << "Random Tree: \n";
	printTree(randTree);

	ThreadedBST deleteEvens(randTree);
	cout << "\nRemove function does not account for all cases.\n"
		 << "Thus, it cannot be used to delete the evens.\n"
		 << "Here is what should be removed from the tree.\n\n"; 
	evensDeleter(randTree);

	cout << "\nCopied Tree: \n";
	counter = 0;
	printTree(deleteEvens);
}

/**
Displays the traversals and that they do work, the tree itself
is a degenerate tree, which shows why the preorder and inorder
traversals are the same.
*/
void traversals(int size) {
	ThreadedBST testTraverals;
	buildTree(testTraverals, size);
	void (*Display)(NodeData*) = &display;

	cout << "Testing Recursive Traversals: \n\n"
		 << "Preorder: " << endl;
	testTraverals.preorderTraversal(*Display);

	cout << "\n\nInorder: \n";
	testTraverals.recurInorderTraversal(*Display);

	cout << "\n\nPostorder: " << endl;
	testTraverals.postorderTraversal(*Display);
	cout << endl << endl;
}

/**
  Test to add Nodes into a tree.
*/
void testCases()
{


	ThreadedBST A;
	ThreadedBST B;
	ThreadedBST C;
	

	NodeData t1("H");
	NodeData t2("A");
	NodeData t3("C");
	NodeData t4("B");
	NodeData t5("D");
	NodeData t8("E");
	NodeData t6("G");
	NodeData t7("F");
	NodeData t9("I");
	NodeData t10("GH");
	NodeData t11("!");
	NodeData t12("#");
	NodeData t13("5");
	NodeData t122("we");
	NodeData t100("ew");

	A.add(&t7); // F
	A.add(&t4); // B
	A.add(&t2); // A
	A.add(&t5); // D
	A.add(&t3); // C
	A.add(&t8); // E
	A.add(&t6); // G
	A.add(&t9); // I
	A.add(&t1); // H
	A.add(&t10);// GH
	A.add(&t11); // !
	A.add(&t12); // #

	counter = 0;
	cout << endl << "Here are the added nodes for tree 1" << endl;
	printTree(A);

	//Testing tree 2
	NodeData t20("H");
	NodeData t21("A");
	NodeData t22("C");
	NodeData t23("B");
	NodeData t24("D");
	NodeData t25("E");
	NodeData t26("G");
	NodeData t27("F");
	NodeData t29("I");
	NodeData t30("GH");

	B.add(&t30); // F
	B.add(&t30); // B
	B.add(&t29); // A
	B.add(&t27); // D
	B.add(&t26); // C
	B.add(&t25); // E
	B.add(&t24); // G
	B.add(&t23); // I
	B.add(&t22); // H
	B.add(&t22);// GH
	B.add(&t21); // !
	B.add(&t20); // #

	counter = 0;
	cout << endl << "Here are the added nodes for tree 2" << endl;
	printTree(B);

	cout<< "All should be true" << endl;
	cout << A.contains(&t25) << endl;
	cout << A.contains(&t26) << endl;
	cout << A.contains(&t27) << endl;

	cout<< "All should be false" << endl;
	cout << A.contains(&t13) << endl;
	cout << A.contains(&t122) << endl;
	cout << A.contains(&t100) << endl;

	cout<< "Testing remove" << endl;
	A.remove(&t25);
	A.remove(&t27);
	cout<< "removing E, F" << endl;
	printTree(A);

	cout<< endl <<  "Testing isEmpty, tree C should be empty" << endl;
	if(C.isEmpty())
		cout<< "C is empty" << endl;
	else
	{
		cout<< "C is not empty!" << endl;
	}

		cout<< endl <<  "Testing isEmpty, tree A should not be empty" << endl;
	if(A.isEmpty())
		cout<< "A is empty" << endl;
	else
	{
		cout<< "A is not empty!" << endl;
	}

}

