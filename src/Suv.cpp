//==============================================================================
// Assignment 4 - Suv Class
//==============================================================================
/*
	File: Suv.cpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/8/2017

******************************************************************************/

#include "Suv.hpp"

using std::string;
using std::ostream;

namespace
{
	static const std::string VEHICLE_TYPE = "Suv";
	static const double REFUEL_TIME = 10.0;
}

Suv::Suv() : Vehicle()
{
	// Intentionally left blank
}

Suv::Suv(std::string make, std::string model, double engine, int cylinders,
		double tankSize, int cityMPG, int highwayMPG) :
		Vehicle(make, model, engine, cylinders, tankSize, cityMPG, highwayMPG)
{
	// Intentionally left blank
}

Vehicle * Suv::clone() const
{
	Suv *temp = new Suv(*this);
	return temp;
}

string Suv::getType() const
{
	return VEHICLE_TYPE;
}

double Suv::getRefuelTime() const
{
	return REFUEL_TIME;
}

string Suv::toString() const
{
	return getType() + vehicleNS::DLMTR + Vehicle::toString();
}
