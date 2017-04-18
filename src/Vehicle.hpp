//==============================================================================
// Assignment 4 - Vehicle Class
//==============================================================================
/*
	File: Vehicle.hpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/18/2017

******************************************************************************/

#ifndef SRC_VEHICLE_HPP_
#define SRC_VEHICLE_HPP_

#include <string>
#include <sstream>
#include <iomanip>
#include "TripLeg.hpp"

namespace vehicleNS
{
	// Delimiter to be used within toString
	static const std::string DLMTR = "\n";
}

class Vehicle
{
public:
	Vehicle();
	Vehicle(const std::string make, const std::string model, double engine, int cylinders,
			double tankSize, int cityMPG, int highwayMPG);
	virtual ~Vehicle() {};

	// Accessors
	std::string getMake() const;
	std::string getModel() const;
	double 		getEngine() const;
	int 		getCylinderCount() const;
	double 		getTankSize() const;
	int 		getCityMPG() const;
	int 		getHighwayMPG() const;
	double 		getCurrentFuel() const;

	// To return a clone of the derived vehicle
	virtual Vehicle * clone() const = 0;

	// To return a type of the derived vehicle
	virtual std::string getType() const = 0;

	// To return the refuel time of the derived vehicle
	virtual double getRefuelTime() const = 0;

	//	Returns a string containing the member data of the current vehicle separated
	//		by the specified delimiter constant
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: String containing Vehicle info separated by DLMTR
	virtual std::string toString() const;

	//	Calculates the amount of fuel consumed after a number of miles
	//		Preconditions: Entered miles is greater than 0
	//		Postconditions: None
	//		Returns: Gallons of fuel consumed after the specified number of miles.
	double calcFuelConsumed(double miles, TripLeg::RoadType roadType);

	//	Reduces the current fuel in tank according to the gallons entered
	//		Preconditions: Gallons must be <= to fuel left in tank
	//		Postconditions: Current fuel is reduced by gallons entered
	void consumeFuel(double gallons);

	//	Returns the MPG based on the roadtype entered
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: MPG in gallons
	int getMPG(TripLeg::RoadType type) ;

	//	Fills the tank to full
	//		Preconditions: None
	//		Postconditions: None
	void fillTank();

	//	Overloaded << operater to stream out the following delineated:
	//		make << model << engineSize << engineCylinders << tanksize << cityMPG << highwayMPG << currentFuel
	friend std::ostream & operator <<(std::ostream &lhs, const Vehicle &rhs);

private:
	std::string mMake;
	std::string mModel;
	double 	mEngine;
	int 	mCylinderCnt;
	double 	mTankSize;
	int 	mCityMPG;
	int 	mHighwayMPG;
	double 	mCurrentFuel;
};

#endif /* SRC_VEHICLE_HPP_ */
