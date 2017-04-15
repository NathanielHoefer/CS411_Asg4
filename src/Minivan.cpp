//==============================================================================
// Assignment 4 - Minivan Class
//==============================================================================
/*
	File: Minivan.cpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/8/2017

******************************************************************************/

#include "Minivan.hpp"

using std::string;
using std::ostream;

namespace
{
	static const std::string VEHICLE_TYPE = "Minivan";
	static const double REFUEL_TIME = 14.0;
}

Minivan::Minivan() : Vehicle()
{
	// Intentionally left blank
}

Minivan::Minivan(std::string make, std::string model, double engine, int cylinders,
		double tankSize, int cityMPG, int highwayMPG) :
		Vehicle(make, model, engine, cylinders, tankSize, cityMPG, highwayMPG)
{
	// Intentionally left blank
}

Vehicle * Minivan::clone() const
{
	Minivan *temp = new Minivan(*this);
	return temp;
}

string Minivan::getType() const
{
	return VEHICLE_TYPE;
}

double Minivan::getRefuelTime() const
{
	return REFUEL_TIME;
}

string Minivan::toString() const
{
	return getType() + vehicleNS::DLMTR + Vehicle::toString();
}
