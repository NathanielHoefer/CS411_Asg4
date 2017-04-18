//==============================================================================
// Assignment 4 - Car Class
//==============================================================================
/*
	File: Car.cpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/8/2017

******************************************************************************/

#include "Car.hpp"

using std::string;
using std::ostream;

namespace
{
	static const std::string VEHICLE_TYPE = "Car";
	static const double REFUEL_TIME = 8.0;
}

Car::Car() : Vehicle()
{
	// Intentionally left blank
}

Car::Car(const std::string make, const std::string model, double engine, int cylinders,
		double tankSize, int cityMPG, int highwayMPG) :
		Vehicle(make, model, engine, cylinders, tankSize, cityMPG, highwayMPG)
{
	// Intentionally left blank
}

Vehicle * Car::clone() const
{
	Car *temp = new Car(*this);
	return temp;
}

string Car::getType() const
{
	return VEHICLE_TYPE;
}

double Car::getRefuelTime() const
{
	return REFUEL_TIME;
}

string Car::toString() const
{
	std::stringstream ss;
	ss.clear();
	ss.str("");
	ss << std::left << std::setw(7) << getType() << vehicleNS::DLMTR << Vehicle::toString();
	return ss.str();
}
