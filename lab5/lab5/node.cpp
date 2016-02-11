/**----------------------------------------------------------------------------
@file node.cpp
		Definitions for the Node class functions.

@author Blong Thao and Albert Tyshler
@course CSS 342 Shields
@date   02/26/14
-----------------------------------------------------------------------------*/

#include "node.h"

/**---------------------- default1 --------------------------------------------
	Sets the NodeData item variable to the parameter anItem variable and sets
		both the leftChildPtr and rightChildPtr to NULL
	@param anItem The NodeData object used to initialize the item.
	@pre   The object must not have invalid values, no whitespace string value
				or negative frequency value.
	@post  Initialized the item variable, and set both left and right child
				pointers to NULL.
-----------------------------------------------------------------------------*/
Node::Node(const NodeData* anItem) {
	setItem(anItem);
	leftChildPtr = NULL;
	rightChildPtr = NULL;
	isLeftThread = false;
	isRightThread = false;
}

/**---------------------- default2 --------------------------------------------
	Sets the NodeData item variable to the parameter anItem variable and sets
		both the leftChildPtr and rightChildPtr to NULL
	@param anItem The NodeData object used to initialize the item.
	@pre   The object must not have invalid values, no whitespace string value
				or negative frequency value.
	@post  Initialized the item variable, and set both left and right child
				pointers to NULL.
-----------------------------------------------------------------------------*/
Node::Node(const NodeData* anItem, Node* left, Node* right,
		   bool threadL, bool threadR) {
	setItem(anItem);
	leftChildPtr = left;
	rightChildPtr = right;
	isLeftThread = threadL;
	isRightThread = threadR;
}

/**------------------------- copy ---------------------------------------------
	Copies every aspect of a Node object.
	@param copyNode The Node object that is copied over to the current Node.
	@pre   The Node object must not be a NULL pointer.
	@post  The current Node has the same values and pointers as the copyNode.
-----------------------------------------------------------------------------*/
Node::Node(const Node& copyNode) {
	setItem(copyNode.item);
	leftChildPtr = copyNode.leftChildPtr;
	rightChildPtr = copyNode.rightChildPtr;
}

/**--------------------- destructor -------------------------------------------
	Sets item to an invalid value that does not show up in the output and sets
		the leftChildPtr and rightChildPtr to NULL.
	@pre  The Node object needs to have a valid value.
	@post The Node object is now 'destructed'.
-----------------------------------------------------------------------------*/
Node::~Node() {
	delete item;
	item = NULL;

}

/**----------------------- setItem --------------------------------------------
	Sets the item.
	@pre  None.
	@post Item is initialized.
-----------------------------------------------------------------------------*/
void Node::setItem(const NodeData* anItem) {
	item = new NodeData(*anItem);
}

/**----------------------- getItem --------------------------------------------
	Gets the item.
	@pre  Item is set.
	@post Item is returned.
-----------------------------------------------------------------------------*/
NodeData* Node::getItem() const {
	return item;
}

/**------------------- getLeftChildPtr ----------------------------------------
	Gets the left child pointer.
	@pre  The left child pointer must be initalized.
	@post Return left child pointer.
-----------------------------------------------------------------------------*/
Node* Node::getLeftChildPtr() const
{
	return leftChildPtr;
}

/**------------------- getRightChildPtr ---------------------------------------
	Gets the right child pointer.
	@pre  The right child pointer must be initalized.
	@post Return right child pointer.
-----------------------------------------------------------------------------*/
Node* Node::getRightChildPtr() const
{
	return rightChildPtr;
}

/**------------------- setLeftChildPtr ----------------------------------------
	Sets the left child pointer.
	@pre  The left child pointer must be initialized.
	@post The left child pointer is assigned to ptr.
-----------------------------------------------------------------------------*/
void Node::setLeftChildPtr(Node* ptr)
{
	leftChildPtr = ptr;
}

/**------------------- setRightChildPtr ---------------------------------------
	Sets the right child pointer.
	@pre  The right child pointer must be initialized.
	@post The right child pointer is assigned to ptr.
-----------------------------------------------------------------------------*/
void Node::setRightChildPtr(Node* ptr)
{
	rightChildPtr = ptr;
}

/**------------------- setisLeftThread ----------------------------------------
	Sets the left thread boolean value.
	@pre  None.
	@post The left thread boolean value is equal to isThread boolean value.
-----------------------------------------------------------------------------*/
void Node::setisLeftThread(bool isThread)
{
	isLeftThread = isThread;
}

/**------------------- setisRightThread ---------------------------------------
	Sets the right thread boolean value.
	@pre  None.
	@post The right thread boolean value is equal to isThread boolean value.
-----------------------------------------------------------------------------*/
void Node::setisRightThread(bool isThread)
{
	isRightThread = isThread;
}

/**------------------- getisLeftThread ----------------------------------------
	Gets the left thread boolean value.
	@pre  The left thread needs to be initialized a true or false value.
	@post None.
-----------------------------------------------------------------------------*/
bool Node::getisLeftThread() const
{
	return isLeftThread;
}

/**------------------- getisRightThread ----------------------------------------
	Gets the right thread boolean value.
	@pre  The right thread needs to be initialized a true or false value.
	@post None.
-----------------------------------------------------------------------------*/
bool Node::getisRightThread() const
{
	return isRightThread;
}
