//==============================================================================
// Assignment 4 - Vehicle Class
//==============================================================================
/*
    File: Vehicle.cpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/18/2017

******************************************************************************/

#include "Vehicle.hpp"

using vehicleNS::DLMTR;
using std::string;
using std::stringstream;
using std::setprecision;
using std::fixed;

Vehicle::Vehicle()
{
	mMake = 		"Default";
	mModel = 		"Default";
	mEngine = 		0.0;
	mCylinderCnt = 	0;
	mTankSize = 	0;
	mCityMPG = 		0;
	mHighwayMPG = 	0;
	mCurrentFuel = 	0;
}

Vehicle::Vehicle(const string make, const string model, double engine, int cylinders,
			double tankSize, int cityMPG, int highwayMPG)
{
	mMake = 		make;
	mModel = 		model;
	mEngine = 		engine;
	mCylinderCnt = 	cylinders;
	mTankSize = 	tankSize;
	mCityMPG = 		cityMPG;
	mHighwayMPG = 	highwayMPG;
	mCurrentFuel = 	tankSize;
}

string 	Vehicle::getMake()  const			{ return mMake; }
string 	Vehicle::getModel()	 const			{ return mModel; }
double 	Vehicle::getEngine()  const			{ return mEngine; }
int 	Vehicle::getCylinderCount()	 const 	{ return mCylinderCnt; }
double 	Vehicle::getTankSize()  const		{ return mTankSize; }
int 	Vehicle::getCityMPG()  const		{ return mCityMPG; }
int 	Vehicle::getHighwayMPG()  const		{ return mHighwayMPG; }
double 	Vehicle::getCurrentFuel()  const	{ return mCurrentFuel; }

string Vehicle::toString() const
{
	stringstream ss;
	ss.clear();
	ss << std::left << std::setw(9) << mMake << DLMTR << std::setw(15) << mModel << DLMTR << fixed << setprecision(1) << mEngine << DLMTR << mCylinderCnt << DLMTR;
	ss << std::right << std::setfill('0') << std::setw(4) << mTankSize << DLMTR << mCityMPG << DLMTR << mHighwayMPG << DLMTR << setprecision(4) << mCurrentFuel;
	return ss.str();
}

double Vehicle::calcFuelConsumed(double miles, TripLeg::RoadType roadType)
{
	double mpg;
	if (roadType == TripLeg::CITY) {
		mpg = mCityMPG;
	} else if (roadType == TripLeg::HIGHWAY) {
		mpg = mHighwayMPG;
	}
	return miles / mpg;
}

void Vehicle::consumeFuel(double gallons)
{
	// Only reduce fuel if the tank wont be empty
	if (gallons <= mCurrentFuel) {
		mCurrentFuel -= gallons;
	}
}

int Vehicle::getMPG(TripLeg::RoadType type)
{
	int mpg = -1;
	if (type == TripLeg::CITY) {
		mpg = mCityMPG;
	} else if (type == TripLeg::HIGHWAY) {
		mpg = mHighwayMPG;
	}
	return mpg;
}

void Vehicle::fillTank()
{
	mCurrentFuel = mTankSize;
}

std::ostream & operator <<(std::ostream &lhs, const Vehicle &rhs)
{
	lhs << rhs.toString();
	return lhs;
}
