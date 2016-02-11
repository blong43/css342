/**----------------------------------------------------------------------------
@file   tbst.h 
	    Contains the ThreadedBST class function declarations.

@author Blong Thao and Albert Tyshler
@course CSS 342 Shields
@date   02/26/14
-----------------------------------------------------------------------------*/

#ifndef THREADED_BST
#define THREADED_BST
#include <iostream>
#include <string>
#include <assert.h>
#include "nodeData.h"
#include "node.h"
using namespace std;

class ThreadedBST {

private:
	Node* rootPtr;

	bool hasChild(const Node*);
	bool isLeaf(const Node*);
	void destroyTree(Node*);
	void setThreads(Node*, Node*, Node*);
	void recurInorder(void visit(NodeData*), Node*);
	void iterInorder(void visit(NodeData*), Node*);
	void preorder(void visit(NodeData*), Node*);
	void postorder(void visit(NodeData*), Node*);

	Node* copyTree(const Node*) const;
	Node* removeValue(Node*, const NodeData*, bool&);
	Node* removeNode(Node*, Node* = NULL); /**/
	Node* removeLeftmostNode(Node*, NodeData&, Node*); /**/
	Node* containsOneChild(Node*);
	Node* containsTwoChildren(Node*);
	
public:
	ThreadedBST();
	ThreadedBST(const ThreadedBST&);
	~ThreadedBST();

	bool add(const NodeData*);
	bool remove(const NodeData*);
	bool contains(const NodeData*) const;
	bool isEmpty();

	void preorderTraversal(void visit(NodeData*));
	void postorderTraversal(void visit(NodeData*));
	void recurInorderTraversal(void visit(NodeData*));
	void iterInorderTraversal(void visit(NodeData*));
	void TreeToArray(NodeData*, int);

	ThreadedBST& operator=(ThreadedBST&);
};

// #include "tbst.cpp"

#endif
