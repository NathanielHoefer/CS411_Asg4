//==============================================================================
// Assignment 4 - Suv Class
//==============================================================================
/*
	File: Suv.hpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/8/2017

******************************************************************************/

#ifndef SRC_SUV_HPP_
#define SRC_SUV_HPP_

#include <string>
#include <iostream>
#include "Vehicle.hpp"

class Suv : public Vehicle
{
public:
	Suv();
	Suv(std::string make, std::string model, double engine, int cylinders,
			double tankSize, int cityMPG, int highwayMPG);

	//	Copies the Suv and returns a dynamic pointer to the clone
	//		Preconditions: None
	//		Postconditions: A cloned suv is now on the heap
	//		Returns: Pointer to cloned suv
	virtual Vehicle * clone() const;

	// Returns the string "Suv" as identified by the vehicle type constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: string "Suv"
	virtual std::string getType() const;

	// Returns the double refuel time as identified by the refuel time constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: double refuel time
	virtual double getRefuelTime() const;

	//	Returns a string containing the member data of the current suv separated
	//		by the specified delimiter constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: String containing suv info separated by DLMTR
	virtual std::string toString() const;
};

#endif /* SRC_SUV_HPP_ */
