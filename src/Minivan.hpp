//==============================================================================
// Assignment 4 - Minivan Class
//==============================================================================
/*
	File: Minivan.hpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/8/2017

******************************************************************************/

#ifndef SRC_MINIVAN_HPP_
#define SRC_MINIVAN_HPP_

#include <string>
#include <iostream>
#include "Vehicle.hpp"

class Minivan : public Vehicle
{
public:
	Minivan();
	Minivan(std::string make, std::string model, double engine, int cylinders,
			double tankSize, int cityMPG, int highwayMPG);

	//	Copies the Minivan and returns a dynamic pointer to the clone
	//		Preconditions: None
	//		Postconditions: A cloned Minivan is now on the heap
	//		Returns: Pointer to cloned Minivan
	virtual Vehicle * clone() const;

	// Returns the string "Minivan" as identified by the vehicle type constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: string "Minivan"
	virtual std::string getType() const;

	// Returns the double refuel time as identified by the refuel time constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: double refuel time
	virtual double getRefuelTime() const;

	//	Returns a string containing the member data of the current Minivan separated
	//		by the specified delimiter constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: String containing Minivan info separated by DLMTR
	virtual std::string toString() const;
};

#endif /* SRC_MINIVAN_HPP_ */
