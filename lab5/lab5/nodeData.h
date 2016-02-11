/**----------------------------------------------------------------------------
@file nodeData.h
	Creates the data inside the nodes of the Threaded Binary Search Tree.
	Contains the NodeData class function declarations.

@author Blong Thao and Albert Tyshler
@course CSS 342 Shields
@date   02/26/14
-----------------------------------------------------------------------------*/

#ifndef L5NODEDATA_H
#define L5NODEDATA_H
#include <string>
using namespace std;

class NodeData {
	friend ostream& operator<<(ostream&, const NodeData&);

private:
	string token;
	int frequency;

public:
	//NodeData(string = " ");
	NodeData(string = " ", int = 1);
	NodeData(const NodeData&);
	//~NodeData();

	NodeData& operator=(const NodeData&);

	bool operator==(const NodeData&) const;
	bool operator<(const NodeData&) const;
	bool operator>(const NodeData&) const;

	void increaseCount();
	void decreaseCount();
	int getCount() const;
	string getToken() const;
	void setData(const NodeData&);
};

// #include "nodeData.cpp" 

#endif
