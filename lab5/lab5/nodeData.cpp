/*-----------------------------------------------------------------------------
@file    nodeData.cpp
		 This file contains the definitions for the NodeData class 
			functions.

@authors Blong Thao and Albert Tyshler
@course  CSS 342 Shields
@date    02/28/14
-----------------------------------------------------------------------------*/

#include "nodeData.h"

///**--------------------------- default ----------------------------------------
//	Sets token and frequency to theToken and theFreq respectively 
//	@param theToken The token string value being passed in
//	@param theFreq The frequency int value being passed in
//	@pre  Must not have invalid values, no whitespace string value
//				or negative frequency value.
//	@post The frequency and token will both have its proper values
//-----------------------------------------------------------------------------*/
//NodeData::NodeData(string theToken)
//{
//	token = theToken;
//	frequency = 1;
//}

/**--------------------------- default ----------------------------------------
	Sets token and frequency to theToken and theFreq respectively 
	@param theToken The token string value being passed in
	@param theFreq The frequency int value being passed in
	@pre  Must not have invalid values, no whitespace string value
				or negative frequency value.
	@post The frequency and token will both have its proper values
-----------------------------------------------------------------------------*/
NodeData::NodeData(string theToken, int freq)
{
	token = theToken;
	frequency = freq;
}

/**------------------------------- Copy ---------------------------------------
	Copies every aspect of a NodeData object.
	@param copy The NodeData object that is copied over to the current NodeData
	@pre   The NodeData object must not be a NULL pointer.
	@post The current NodeData has the same values and pointers as the copy
-----------------------------------------------------------------------------*/
NodeData::NodeData(const NodeData& copy)
{
	token = copy.token;
	frequency = copy.frequency;
}

//NodeData::~NodeData() {
//	token = " ";
//	frequency = 0;
//}

/**--------------------------- operator= --------------------------------------
	Assigns the left hand side NodeData to the right hand side 
	@param RHS. The right hand side of the operator
	@pre A valid left hand side
	@post The current NodeData is assigned the same values as the RHS.
-----------------------------------------------------------------------------*/
NodeData& NodeData::operator=(const NodeData& RHS)
{
	if (this != &RHS) {
		this->token = RHS.getToken();
		this->frequency = RHS.getCount();
	}
	return *this;
}
/**-------------------------- operator== --------------------------------------
	Checks if the left hand side token is equal to the right hand side 
	@param RHS. The right hand side of the operator
	@pre A valid left hand side
	@post None.
-----------------------------------------------------------------------------*/
bool NodeData::operator==(const NodeData& RHS) const
{
	return this->token == RHS.token;
}

/**-------------------------- operator< ---------------------------------------
	Checks if the left hand side token is less than the right hand side 
	@param RHS. The right hand side of the operator
	@pre A valid left hand side
	@post None.
-----------------------------------------------------------------------------*/
bool NodeData::operator<(const NodeData& RHS) const
{
	if (this->getToken() < RHS.getToken())
		return true;
	return false;
}

/**---------------------------- operator> -------------------------------------
	Checks if the left hand side token is greater than the right hand side 
	@param RHS. The right hand side of the operator
	@pre A valid left hand side
	@post None.
-----------------------------------------------------------------------------*/
bool NodeData::operator>(const NodeData& RHS) const
{
	if(this->getToken() > RHS.getToken())
		return true;
	return false;
}

/**---------------------------- increaseCount ---------------------------------
	increases the frequency by 1
	@pre frequency needs to be higher than or equal 0
	@post None.
-----------------------------------------------------------------------------*/
void NodeData::increaseCount()
{
	frequency++;
}

/**---------------------------- decreaseCount ---------------------------------
	decreases the frequency by 1
	@pre frequency needs to be higher than 0
	@post None.
-----------------------------------------------------------------------------*/
void NodeData::decreaseCount()
{
	frequency--;
}

/**------------------------------- getCount -----------------------------------
	returns the token int frequency
	@pre the frequency needs to be initialized 
	@post None.
-----------------------------------------------------------------------------*/
int NodeData::getCount() const
{
	return frequency;
}

/**------------------------------- getToken -----------------------------------
	returns the token string
	@pre the token needs to be initialized 
	@post None.
-----------------------------------------------------------------------------*/
string NodeData::getToken() const
{
	return token;
}

/**------------------------------- setData ------------------------------------
	sets the frequency and token data
	@param data. The token and frequency data
	@pre contains valid values
	@post sets the current data to the data 
-----------------------------------------------------------------------------*/
void NodeData::setData(const NodeData& data) 
{
	//assign the token and the frequency to the data's token and frequency 
	token = data.token;
	frequency = data.frequency;
}

/**------------------------------ operator << ---------------------------------
	Prints out the nodeData token and frequency 
	@param output ostream cout, within c++; for the nodeData class
	@param data the NodeData object that is being read
	@pre NodeData cannot be empty
	@post Prints out the token and frequency 
-----------------------------------------------------------------------------*/
ostream& operator<<(ostream& output, const NodeData& data)
{
	//prints out the nodeData with token first then the frequency
	output << data.getToken() << " " << data.getCount();
	return output;
}
