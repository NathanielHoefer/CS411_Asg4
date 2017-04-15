//==============================================================================
// Assignment 4 - Van Class
//==============================================================================
/*
	File: Van.cpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/8/2017

******************************************************************************/

#include "Van.hpp"

using std::string;
using std::ostream;

namespace
{
	static const std::string VEHICLE_TYPE = "Van";
	static const double REFUEL_TIME = 12.0;
}

Van::Van() : Vehicle()
{
	// Intentionally left blank
}

Van::Van(std::string make, std::string model, double engine, int cylinders,
		double tankSize, int cityMPG, int highwayMPG) :
		Vehicle(make, model, engine, cylinders, tankSize, cityMPG, highwayMPG)
{
	// Intentionally left blank
}

Vehicle * Van::clone() const
{
	Van *temp = new Van(*this);
	return temp;
}

string Van::getType() const
{
	return VEHICLE_TYPE;
}

double Van::getRefuelTime() const
{
	return REFUEL_TIME;
}

string Van::toString() const
{
	return getType() + vehicleNS::DLMTR + Vehicle::toString();
}
