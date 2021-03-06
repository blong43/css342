/**----------------------------------------------------------------------------
@file tbst.cpp
	Contains the ThreadedBST class function definitions.

@author Blong Thao and Albert Tyshler
@course CSS 342 Shields
@date   02/26/14
-----------------------------------------------------------------------------*/

#include "tbst.h"

/**--------------------- default ----------------------------------------------
	Initializes the root pointer and the right and left threads.
	@pre  Have declared root pointer and right and left threads.
	@post Root pointer is set to NULL and the left and right threads are
			set to false.
-----------------------------------------------------------------------------*/
ThreadedBST::ThreadedBST() 
{
	rootPtr = NULL;
}

/**--------------------- copy -------------------------------------------------
	Copies an entire ThreadedBST object over to the current TBST object.
	@pre  None.
	@post The current TBST object has a complete copy in reference of the
			other TBST object.
-----------------------------------------------------------------------------*/
ThreadedBST::ThreadedBST(const ThreadedBST& copy) 
{
	rootPtr =  copyTree(copy.rootPtr);
}

/**--------------------- destructor -------------------------------------------
	Starts freeing the left side of the tree first and then the right side.
	@pre  None.
	@post The TBST freed all memory allocations and has no memory leaks.
-----------------------------------------------------------------------------*/
ThreadedBST::~ThreadedBST() 
{
	destroyTree(rootPtr);
}

/**-------------------- destroyTree -------------------------------------------
	Traverses the tree recursively to delete the data and node.
	@param subtreePtr The tree node that is being free.
	@pre   All variables need to already be initialized.
	@post  Free all tree memory allocations and pointers are set to NULL,
			with both threads set to false.
-----------------------------------------------------------------------------*/
void ThreadedBST::destroyTree(Node* subtreePtr) 
{
	if (subtreePtr != NULL)
	{
		if (!subtreePtr->getisLeftThread())
			destroyTree(subtreePtr->getLeftChildPtr());
		if (!subtreePtr->getisRightThread())
			destroyTree(subtreePtr->getRightChildPtr());
		delete subtreePtr;
	}
}

/**-------------------- copyTree ----------------------------------------------
	Recursively copies a tree and returns the pointer to that tree.
	@param treePtr The rootPtr of the tree that is being copied.
	@pre   All variables in other tree should be initialized.
	@post  Everything from the other tree is copied into the current tree.
-----------------------------------------------------------------------------*/
Node* ThreadedBST::copyTree(const Node* treePtr) const
{
	Node* copyNode = NULL;
	if (treePtr != NULL) 
	{
		copyNode = new Node(treePtr->getItem(),treePtr->getLeftChildPtr(),
			treePtr->getRightChildPtr(), treePtr->getisLeftThread(), 
			treePtr->getisRightThread());
		if (!treePtr->getisLeftThread())
			copyNode->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
		if (!treePtr->getisRightThread())
			copyNode->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
	}
	return copyNode;
}

ThreadedBST& ThreadedBST::operator=(ThreadedBST& otherTree) {
	if (this != &otherTree) {
		destroyTree(this->rootPtr);
		copyTree(otherTree.rootPtr);
	}
	return *this;
}

/**-------------------- add ---------------------------------------------------
	Inserts a single node into the TBST iteratively.
	@param newData The new data that is being inserted into the TBST.
	@pre   The new data does not contain invalid data.
	@post  The new data is inserted into the correct position in the tree.
-----------------------------------------------------------------------------*/
bool ThreadedBST::add(const NodeData* newData)
{
	Node* ptr = new Node(newData);

	if (isEmpty()) {
		//cout << *ptr->getItem();
		rootPtr = ptr;
	}
	else {
		Node* current = rootPtr;
		Node* parent = NULL;
		bool found = false;

		while (current != NULL && !found ) {
			// put into already created node: add one to frequency
			if (*ptr->getItem() == *current->getItem()) {
				NodeData* currentData = current->getItem();
				currentData->increaseCount();
				delete ptr;
				return true;
			} 
			else {
				parent = current;
				// put in left side
				if (*ptr->getItem() < *current->getItem()) {
					if (current->getisLeftThread())
						found = true;
					else
						current = current->getLeftChildPtr();
				}
				// put in right side
				else {
					if (current->getisRightThread())
						found = true;
					else
						current = current->getRightChildPtr();
				}
			}
		}
		setThreads(ptr, current, parent);
	}
	return true;
}

/**------------------------- setThreads ---------------------------------------
-----------------------------------------------------------------------------*/
void ThreadedBST::setThreads(Node* ptr, Node* current, Node* parent) {
	// when the current walker pointer hits NULL
	if (current == NULL) {
		// insert left, thread right
		if (*ptr->getItem() < *parent->getItem()) {
			//cout << *ptr->getItem();
			parent->setLeftChildPtr(ptr);
			ptr->setRightChildPtr(parent);
			ptr->setisRightThread(true);
		}
		// insert right, thread left
		else {
			//cout << *ptr->getItem();
			parent->setRightChildPtr(ptr);
			ptr->setLeftChildPtr(parent);
			ptr->setisLeftThread(true);
		}
	}
	// when the current walker pointer points to a Node
	else {
		// insert left, thread left, unthread right 
		if (*ptr->getItem() < *current->getItem()) {
			//cout << *ptr->getItem();
			ptr->setLeftChildPtr(current->getLeftChildPtr());
			ptr->setisLeftThread(true);
			ptr->setRightChildPtr(current);
			ptr->setisRightThread(true);
			current->setLeftChildPtr(ptr);
			current->setisLeftThread(false);
		}
		// insert right, thread left, unthread right
		else {
			//cout << *ptr->getItem();
			ptr->setRightChildPtr(current->getRightChildPtr());
			ptr->setisRightThread(true);
			ptr->setLeftChildPtr(current);
			ptr->setisLeftThread(true);
			current->setRightChildPtr(ptr);
			current->setisRightThread(false);
		}
	}
}

/**------------------------- remove -------------------------------------------
	Removes a data target from the Threaded BST
	@param target The data that is being removed from the tree.
	@per   Target data should have valid values.
	@post  The target is removed = true; the target was not in tree = false.
-----------------------------------------------------------------------------*/
bool ThreadedBST::remove(const NodeData* target)
{
	bool success = false;
	rootPtr = removeValue(rootPtr, target, success);
	return success;
}

/**----------------------- removeValue ----------------------------------------
	Helper function for the remove function, checks the values.
	@param subtree The tree that is looked at.
	@param target  The data value that is going to be removed.
	@param success The boolean value to see if the remove was successful.
	@pre   The remove function calls it and inputs 3 valid parameters.
	@post  Returns a pointer to become the new tree if a value was removed.
-----------------------------------------------------------------------------*/
Node* ThreadedBST::removeValue(Node* subtree, const NodeData* target, 
							   bool& success) 
{
	if (!contains(target)) {
		success = false;
		cerr << "\nTarget was not found, returning original tree.\n";
		return subtree;
	}
	if (subtree == NULL) {
		success = false;
		return NULL;
	}
	else if (*subtree->getItem() == *target) {
		//base case: target is the root of the  subtree
		subtree = removeNode(subtree);
		success = true;
		return subtree;
	}
	else if (*subtree->getItem() > *target) {
		//search the left side of the tree
		if (!subtree->getisLeftThread()) {
			Node* temp = removeValue(subtree->getLeftChildPtr(), target, success);
			subtree->setLeftChildPtr(temp);
		}
		return subtree;
	}
	else {
		//search the right side of the tree
		if (!subtree->getisRightThread()) {
			Node* temp = removeValue(subtree->getRightChildPtr(), target, success);
			subtree->setRightChildPtr(temp);
		}
		return subtree;
	}
}

/**------------------------- removeNode ---------------------------------------
	Helper function for the remove, does the delete and removing part.
	@param pointer The pointer that is to be freed and reset somewhere else.
	@pre   Called by the remove function.
	@post  The node is returned and connected.
-----------------------------------------------------------------------------*/
Node* ThreadedBST::removeNode(Node* ptr, Node* parent)
{
	// the node is a leaf, just delete it and return a null pointer
	if (isLeaf(ptr))
	{
		if (parent != NULL) {
			if (*ptr->getLeftChildPtr()->getItem() == *parent->getItem()) {
				Node* rightT = ptr->getRightChildPtr();
				ptr->~Node();
				delete ptr;
				ptr = NULL;
				return rightT;
			}
		}
		ptr->~Node();
		delete ptr;
		ptr = NULL;
		return ptr;
	}	
	// if tree contains one child, assign the next node to take 
	//its place and delete it
	else if (hasChild(ptr))
		return containsOneChild(ptr);
	// there are children
	else
		return containsTwoChildren(ptr);
}

/**------------------- containsOneChild ---------------------------------------
	Removes the node with one child.
	@param ptr   The parent node that is being checked.
	@pre   Used only when a Node pointer has one children.
	@post  Found the replacement node and replaced it with the parent.
-----------------------------------------------------------------------------*/
Node* ThreadedBST::containsOneChild(Node* ptr) {
	// the new Node that gets connected to the tree in place of the target
	Node* newN = NULL;

	// set the left child to be the new node
	if (ptr->getLeftChildPtr() != NULL && !ptr->getisLeftThread())
	{
		newN = ptr->getLeftChildPtr();

		// resetting the new node's right child's thread to
		// the ptr's thread since its being deleted
		Node* newNRight = newN->getRightChildPtr();
		bool threaded = false;
		while (newNRight != NULL && !threaded)
		{
			// found thread, now reset the thread
			if (newNRight->getisRightThread()) 
			{
				newNRight->setRightChildPtr(ptr->getRightChildPtr());
				threaded = true;
			}
			// else, descend right
			newNRight = newNRight->getRightChildPtr();
		}
	} 
	else { // set the right child to be the new node
		newN = ptr->getRightChildPtr();

		// resetting the new node's left child's thread to
		// the ptr's thread since its being deleted
		Node* newNLeft = newN->getLeftChildPtr();
		bool threaded = false;
		while (newNLeft != NULL && !threaded)
		{
			// found thread, now reset the thread
			if (newNLeft->getisLeftThread()) {
				newNLeft->setLeftChildPtr(ptr->getLeftChildPtr());
				threaded = true;
			}
			// else, descend left
			newNLeft = newNLeft->getLeftChildPtr();
		}
	}
	delete ptr;
	ptr = NULL;
	return newN;
}

/**------------------- containsTwoChildren ------------------------------------
	Removes the node values with two children.
	@param ptr   The parent node that is being checked.
	@pre   Used only when a Node pointer has two children.
	@post  Found the successor and replaced it with the parent.
-----------------------------------------------------------------------------*/
Node* ThreadedBST::containsTwoChildren(Node* ptr) {
	// replacement value for the node, using the successor
	NodeData newValue;
	Node* temp = removeLeftmostNode(ptr->getRightChildPtr(), newValue, ptr);
		
	// used to find the left most node in the right tree
	Node* leftMostNode = ptr->getRightChildPtr()->getLeftChildPtr();
	bool foundLeftMostNode = false;

	// when 
	if (/*leftMostNode != NULL*/false) {
		while (leftMostNode == NULL && !foundLeftMostNode) {
			if (leftMostNode->getisLeftThread()) {
				ptr->getRightChildPtr()->setLeftChildPtr(temp);
				foundLeftMostNode = true;
			}
			leftMostNode = leftMostNode->getLeftChildPtr();
		}
	} else
		ptr->setRightChildPtr(temp);
	//	ptr->setRightChildPtr(temp);
	ptr->setItem(&newValue);
	return ptr;
}

/**------------------- removeLeftmostNode -------------------------------------
	Removes the left most node in the tree.
	@param nodePtr   The parent node that is being checked.
	@param successor The value that is replacing the parent node.
	@pre   Used only when a Node pointer has two children.
	@post  Found the left most node and deleted it.
-----------------------------------------------------------------------------*/
Node* ThreadedBST::removeLeftmostNode(Node* nodePtr, NodeData& successor,
									  Node* parent)
{
	// left child will never be NULL, so check for thread
	if (nodePtr->getisLeftThread())
	{
		
		successor = *nodePtr->getItem();
		// takes the value of the left node and removes the node from tree
		if (nodePtr->getLeftChildPtr() == parent) 
			return removeNode(nodePtr, parent);
		return removeNode(nodePtr);
	}
	// did not find left most node yet, try again
	else
		return removeLeftmostNode(nodePtr->getLeftChildPtr(),
									successor, parent);
}

/**-------------------- contains ----------------------------------------------
	Check a TBST for a data value.
	@param target The data that is being looked for.
	@pre   None.
	@post  Target is found = true; target is not found = false.
-----------------------------------------------------------------------------*/
bool ThreadedBST::contains(const NodeData* target) const
{
	Node* temp = rootPtr;
	while (temp != NULL) 
	{
		if (*temp->getItem() == *target)
			return true;
		else if (*target > *temp->getItem()) {
			if (!temp->getisRightThread())
				temp = temp->getRightChildPtr();
			else 
				return false;
		}
		else if (*target < *temp->getItem()) {
			if (!temp->getisLeftThread())
				temp = temp->getLeftChildPtr();
			else
				return false;
		}
	}
	return false;
}

/**-------------------- isEmpty -----------------------------------------------
	Checks to see if the TBST is empty
	@pre  Must be called will a TBST object, TBST A; A.isEmpty().
	@post True if empty, or false if not empty.
-----------------------------------------------------------------------------*/
bool ThreadedBST::isEmpty()
{
	return rootPtr == NULL;
}

/**-------------------- isLeaf ------------------------------------------------
	Checks a node to see if its a leaf.
	@param check The node that is being checked.
	@pre   Needs to be in the tree.
	@post  Return true if it?s a leaf, otherwise returns false.
-----------------------------------------------------------------------------*/
bool ThreadedBST::isLeaf(const Node* check)
{
	if ((check->getLeftChildPtr() == NULL && check->getRightChildPtr() == NULL) 
	|| (check->getLeftChildPtr() == NULL && check->getisRightThread()) ||
	(check->getisLeftThread() && check->getisRightThread()) ||
	(check->getisLeftThread() && check->getRightChildPtr() == NULL))
		return true;
	return false;
}

/**-------------------- hasChild ------------------------------------------------
	Checks a node to see if its has only one child.
	@param check The node that is being checked.
	@pre   Needs to be in the tree.
	@post  Return true if it?s a leaf, otherwise returns false.
-----------------------------------------------------------------------------*/
bool ThreadedBST::hasChild(const Node* ptr)
{
	if ((ptr->getLeftChildPtr() != NULL &&	ptr->getisRightThread())
	|| (ptr->getisLeftThread() && ptr->getRightChildPtr() != NULL)
	|| (ptr->getLeftChildPtr() == NULL && ptr->getRightChildPtr() != NULL)
	|| (ptr->getLeftChildPtr() != NULL && ptr->getRightChildPtr() == NULL))
		return true;
	return false;
}

/**-------------------- preorderTraverse --------------------------------------
	Recursive pre-order traversal of the Threaded BST
	@param theRoot The starting point of the TBST.
	@pre   All variables need to be defined.
	@post  Print the tree in pre-order format.
-----------------------------------------------------------------------------*/
void ThreadedBST::preorderTraversal(void visit(NodeData*)) 
{
	preorder(visit, rootPtr);
}

void ThreadedBST::preorder(void visit(NodeData*), Node* subtree) {
	if (subtree != NULL) 
	{
		NodeData theItem = *subtree->getItem();
		visit(&theItem);
		if (!subtree->getisLeftThread())
			preorder(visit, subtree->getLeftChildPtr());
		if (!subtree->getisRightThread())
			preorder(visit, subtree->getRightChildPtr());
	}
}

/*-------------------- postorderTraverse --------------------------------------
	Recursive post-order traversal of the Threaded BST
	@param theRoot The starting point of the TBST.
	@pre   All variables need to be defined.
	@post  Print the tree in post-order format.
-----------------------------------------------------------------------------*/
void ThreadedBST::postorderTraversal(void visit(NodeData*)) 
{
	postorder(visit, rootPtr);
}

void ThreadedBST::postorder(void visit(NodeData*), Node* subtree) {
	if (subtree != NULL) 
	{
		if (!subtree->getisLeftThread())
			postorder(visit, subtree->getLeftChildPtr());
		if (!subtree->getisRightThread())
			postorder(visit, subtree->getRightChildPtr());
		NodeData theItem = *subtree->getItem();
		visit(&theItem);
	}
}
/**-------------------- recurInorderTraverse ----------------------------------
	Recursive in-order traversal of the Threaded BST
	@param theRoot The starting point of the TBST.
	@pre   All variables need to be defined.
	@post  Print the tree in in-order format.
-----------------------------------------------------------------------------*/
void ThreadedBST::recurInorderTraversal(void visit(NodeData*)) 
{
	recurInorder(visit, rootPtr);
}

/**------------------------ inorder -------------------------------------------
	Helper function for the recursive Inorder Traversal.
	@param subtree The starting point of the traversal.
	@pre   None.
	@post  Outputs data in order OR no data if NULL.
-----------------------------------------------------------------------------*/
void ThreadedBST::recurInorder(void visit(NodeData*),Node* subtree) {
	if (subtree != NULL) 
	{
		if (!subtree->getisLeftThread())
			recurInorder(visit, subtree->getLeftChildPtr());
		NodeData theItem = *subtree->getItem();
		visit(&theItem);
		if (!subtree->getisRightThread())
			recurInorder(visit, subtree->getRightChildPtr());
	}
}

///**-------------------- iterInorderTraversal -----------------------------------
//	Iterative in-order traversal of the Threaded BST
//	@param theRoot The starting point of the TBST.
//	@pre   All variables need to be defined.
//	@post  Print the tree in in-order format.
//-----------------------------------------------------------------------------*/
void ThreadedBST::iterInorderTraversal(void visit(NodeData*)) 
{
	iterInorder(visit, rootPtr);
}
///**-------------------- iterInorderTraverse2 -----------------------------------
//	Iterative in-order traversal of the Threaded BST
//	@param theRoot The starting point of the TBST.
//	@pre   All variables need to be defined.
//	@post  Print the tree in in-order format.
//-----------------------------------------------------------------------------*/
void ThreadedBST::iterInorder(void visit(NodeData*), Node* theRoot) 
{
	if(isEmpty())
		return;
	Node* curr = theRoot;
	Node* prev = NULL;

	while (curr->getLeftChildPtr() != NULL )
		curr = curr->getLeftChildPtr();

	while (curr != NULL)
	{
		visit(curr->getItem());
		prev = curr;
		curr = curr->getRightChildPtr();
	
		if(prev->getRightChildPtr() != NULL && !prev->getisRightThread())
		{
			while(curr->getLeftChildPtr() != NULL && !curr->getisLeftThread())
				curr = curr->getLeftChildPtr();

		}
	}
}

void ThreadedBST::TreeToArray(NodeData* theArray, int arrSize) {
	if (isEmpty())
		return;

	Node* curr = rootPtr;
	Node* prev = NULL;

	while (curr->getLeftChildPtr() != NULL )
		curr = curr->getLeftChildPtr();

	int position = 0;
	while (curr != NULL)
	{
		theArray[position] = *curr->getItem();
		//cout << "In array: " << theArray[position] << endl;
		prev = curr;
		curr = curr->getRightChildPtr();
	
		if(prev->getRightChildPtr() != NULL && !prev->getisRightThread())
		{
			while(curr->getLeftChildPtr() != NULL && !curr->getisLeftThread())
				curr = curr->getLeftChildPtr();

		}
		position++;
	}

}