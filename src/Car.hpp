//==============================================================================
// Assignment 4 - Car Class
//==============================================================================
/*
	File: Car.hpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/8/2017
S
******************************************************************************/

#ifndef SRC_CAR_HPP_
#define SRC_CAR_HPP_

#include <string>
#include <iostream>
#include "Vehicle.hpp"

class Car : public Vehicle
{
public:
	Car();
	Car(const std::string make, const std::string model, double engine, int cylinders,
			double tankSize, int cityMPG, int highwayMPG);

	//	Copies the Car and returns a dynamic pointer to the clone
	//		Preconditions: None
	//		Postconditions: A cloned car is now on the heap
	//		Returns: Pointer to cloned car
	virtual Vehicle * clone() const;

	// Returns the string "Car" as identified by the vehicle type constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: string "Car"
	virtual std::string getType() const;

	// Returns the double refuel time as identified by the refuel time constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: double refuel time
	virtual double getRefuelTime() const;

	//	Returns a string containing the member data of the current car separated
	//		by the specified delimiter constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: String containing car info separated by DLMTR
	virtual std::string toString() const;
};

#endif /* SRC_CAR_HPP_ */
