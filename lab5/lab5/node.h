/**----------------------------------------------------------------------------
@file node.h 
		Declarations for the Node class functions.

@author Blong Thao and Albert Tyshler
@course CSS 342 Shields
@date   02/26/14
-----------------------------------------------------------------------------*/

#ifndef L5NODE_H
#define L5NODE_H
#include "nodeData.h"

class Node {

private:
	NodeData* item;
	Node* leftChildPtr;
	Node* rightChildPtr;
	bool isLeftThread, isRightThread;

public:
	// Constructors
	Node(const NodeData*);
	Node(const NodeData*, Node*, Node*, bool, bool);
	Node(const Node&);
	~Node();

	// Getters and Setters
	void setItem(const NodeData*);
	NodeData* getItem() const;
	
	Node* getLeftChildPtr() const;
	Node* getRightChildPtr() const;
	void setLeftChildPtr(Node*);
	void setRightChildPtr(Node*);

	void setisLeftThread(bool);
	void setisRightThread(bool);
	bool getisLeftThread() const;
	bool getisRightThread() const;
};

// #include "node.cpp"

#endif
