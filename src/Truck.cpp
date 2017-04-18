//==============================================================================
// Assignment 4 - Truck Class
//==============================================================================
/*
	File: Truck.cpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/8/2017

******************************************************************************/

#include "Truck.hpp"

using std::string;
using std::ostream;

namespace
{
	static const std::string VEHICLE_TYPE = "Truck";
	static const double REFUEL_TIME = 16.0;
}

Truck::Truck() : Vehicle()
{
	// Intentionally left blank
}

Truck::Truck(const std::string make, const std::string model, double engine, int cylinders,
		double tankSize, int cityMPG, int highwayMPG) :
		Vehicle(make, model, engine, cylinders, tankSize, cityMPG, highwayMPG)
{
	// Intentionally left blank
}

Vehicle * Truck::clone() const
{
	Truck *temp = new Truck(*this);
	return temp;
}

string Truck::getType() const
{
	return VEHICLE_TYPE;
}

double Truck::getRefuelTime() const
{
	return REFUEL_TIME;
}

string Truck::toString() const
{
	std::stringstream ss;
	ss.clear();
	ss.str("");
	ss << std::left << std::setw(7) << getType() << vehicleNS::DLMTR << Vehicle::toString();
	return ss.str();
}
