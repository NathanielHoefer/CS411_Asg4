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

Car::Car() : Vehicle()
{
	// Intentionally left blank
}

Car::Car(std::string make, std::string model, double engine, int cylinders,
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
	return CAR_REFUEL_TIME;
}

string Car::toString() const
{
	return getType() + vehicleNS::DLMTR + Vehicle::toString();
}
