//==============================================================================
// Assignment 4 - Van Class
//==============================================================================
/*
	File: Van.hpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/8/2017

******************************************************************************/

#ifndef SRC_VAN_HPP_
#define SRC_VAN_HPP_

#include <string>
#include <iostream>
#include "Vehicle.hpp"

class Van : public Vehicle
{
public:
	Van();
	Van(std::string make, std::string model, double engine, int cylinders,
			double tankSize, int cityMPG, int highwayMPG);

	//	Copies the Van and returns a dynamic pointer to the clone
	//		Preconditions: None
	//		Postconditions: A cloned Van is now on the heap
	//		Returns: Pointer to cloned Van
	virtual Vehicle * clone() const;

	// Returns the string "Van" as identified by the vehicle type constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: string "Van"
	virtual std::string getType() const;

	// Returns the double refuel time as identified by the refuel time constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: double refuel time
	virtual double getRefuelTime() const;

	//	Returns a string containing the member data of the current Van separated
	//		by the specified delimiter constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: String containing Van info separated by DLMTR
	virtual std::string toString() const;
};

#endif /* SRC_VAN_HPP_ */
