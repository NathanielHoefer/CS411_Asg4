//==============================================================================
// Assignment 4 - VehicleTrip Class
//==============================================================================
/*
    File: VehicleTrip.cpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/7/2017

******************************************************************************/

#include "VehicleTrip.hpp"

using std::string;
using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::setfill;
using vehicleNS::DLMTR;

static const std::string ODLMTR = "|";

VehicleTrip::VehicleTrip(const Vehicle *vehicle, const TripParameters &parms)
{
	mParms = 		parms;
	mVehicle = 		vehicle->clone();
	mFuelPurchased = 0.0;
	mFuelConsumed = 0.0;
	mCityMiles = 	0;
	mHighwayMiles = 0;
	mDriveTime = 	0.0;
	mGStationCnt = 	0;
	mTripTime = 	0;
}

VehicleTrip::VehicleTrip(const VehicleTrip &trip)
{
	mParms = trip.mParms;

	if (trip.mVehicle) {
		mVehicle = trip.mVehicle->clone();
	} else {
		mVehicle = NULL;
	}
	mFuelPurchased = trip.mFuelPurchased;
	mFuelConsumed = trip.mFuelConsumed;
	mCityMiles = 	trip.mCityMiles;
	mHighwayMiles = trip.mHighwayMiles;
	mDriveTime = 	trip.mDriveTime;
	mGStationCnt = 	trip.mGStationCnt;
	mTripTime = 	trip.mTripTime;
}

VehicleTrip::~VehicleTrip()
{
	if (mVehicle) {
		delete mVehicle;
	}
}

TripParameters VehicleTrip::getParms() const	{ return mParms; }
Vehicle * VehicleTrip::getVehicle() const
{
	if (mVehicle) {
		return mVehicle->clone();
	} else {
		return NULL;
	}
}
double 	VehicleTrip::getFuelPurchased() const 	{ return mFuelPurchased; }
double 	VehicleTrip::getFuelConsumed() const 	{ return mFuelConsumed; }
double 	VehicleTrip::getCityMiles() const 		{ return mCityMiles; }
double 	VehicleTrip::getHighwayMiles() const	{ return mHighwayMiles; }
int 	VehicleTrip::getDriveTime() const 		{ return mDriveTime; }
int 	VehicleTrip::getTripTime() const		{ return mTripTime; }
int 	VehicleTrip::getGStationCount() const 	{ return mGStationCnt; }

void VehicleTrip::runTrip(std::vector<TripLeg> &legs)
{

	double milesUntilStation = 0;
	double gasDistance = mParms.getGasDistance();	// Distance between each station

	// Process each trip leg
	for (int i = 0; i < (int)legs.size(); i++) {

		// Sets MPG for the trip leg
		int mpg = mVehicle->getMPG(legs.at(i).getRoadType());
		double legDistance = legs.at(i).getDistance();
		TripLeg::RoadType roadType = legs.at(i).getRoadType();

		// Sets to remaining miles until gas station
		double legTravelled;		// The miles travelled in the current leg
		bool isStationInLeg;

		// Is station in next leg?
		if (milesUntilStation > legDistance) {
			legTravelled = legDistance;
			milesUntilStation -= legDistance;
			isStationInLeg = false;
		} else {
			legTravelled = milesUntilStation;
			isStationInLeg = true;
		}

		mVehicle->consumeFuel(legTravelled / mpg);

		// Travel until end of leg
		while (legTravelled < legDistance) {

			// Station in next leg?
			if ((legTravelled + gasDistance) > legDistance) {
				isStationInLeg = false;
			}

			// Will it make it to the next gas station?
			double fueltoStation;
			if (isStationInLeg) {
				fueltoStation = mVehicle->calcFuelConsumed(gasDistance, roadType);
			} else {
				fueltoStation = calcFuelUntilStation(legs, i, legTravelled);
			}

			// Stopping at gas station if needed
			if (fueltoStation > mVehicle->getCurrentFuel()) {
				increaseFuelPurchased();
				mVehicle->fillTank();
				mGStationCnt++;
			}

			// Update current local travel and getVehicle tank
			if (isStationInLeg) {
				legTravelled += gasDistance;
				mVehicle->consumeFuel(gasDistance / mpg);
			} else {
				double remainder = legDistance - legTravelled;
				legTravelled += remainder;
				milesUntilStation = gasDistance - remainder;
				mVehicle->consumeFuel(remainder / mpg);
			}
		}

		// End of tripleg calculations
		mFuelConsumed += mVehicle->calcFuelConsumed(legDistance, roadType);
		if (roadType == TripLeg::CITY) {
			mCityMiles += legDistance;
		} else if (roadType == TripLeg::HIGHWAY) {
			mHighwayMiles += legDistance;
		}
	}

	// Calculate Total Time
	int refuelTime, restroomTime, sleepTime;
	mDriveTime += calcDriveTime(mCityMiles, TripLeg::CITY);
	mDriveTime += calcDriveTime(mHighwayMiles, TripLeg::HIGHWAY);
	refuelTime = round(calcRefuelTime());
	restroomTime = round(calcRestroomTime());
	sleepTime = round(calcSleepTime());
	mTripTime = round(mDriveTime) + refuelTime + restroomTime + sleepTime;
}

void VehicleTrip::formattedTrip(std::ostream & stream) const
{
	std::vector<std::string> elements = VehicleRecords::deserialize(toString(), 16, ODLMTR[0]);

	// Assigns the elements to the following strings
	string type = elements[0] + ": ";
	string make = elements[1];
	string model = elements[2];
	string tankSize = elements[5];
	string cityMPG = elements[6];
	string highwayMPG = elements[7];
	string timeMin = elements[8];
	string timeDetail = elements[9];
	string fuelAddedCost = elements[10];
	string fuelConsumedCost = elements[11];
	string currentFuel = elements[14];

	// Calculations for centering title
	int titleLen = type.size() + 2 + make.size() + model.size() + 1;
	int leftTitleSpace = (56 - titleLen) / 2;

	// Formats output
	stream << setw(leftTitleSpace) << "";
	stream << type << make << " " << model << endl;
	stream << "--------------------------------------------------------" << endl;
	stream << left << fixed << setprecision(2);
	stream << "Tank Size = " << setw(6) << tankSize;
	stream << "gal   City MPG = " << setw(5) << cityMPG;
	stream << "Highway MPG = " << highwayMPG << endl;
	stream << "--------------------------------------------------------" << endl;
	stream << "Trip time(minutes) = " << setw(7) << timeMin;
	stream << "Trip time(d.hh:mm) = " << timeDetail << endl;
	stream << "--------------------------------------------------------" << endl;
	stream << left << setfill(' ');
	stream << "Trip cost based on fuel added = $" << fuelAddedCost << endl;
	stream << "Trip cost based on fuel used  = $" << fuelConsumedCost << endl;
	stream << "--------------------------------------------------------" << endl;
	stream << "Fuel added = " << setw(8) << setprecision(4) << mFuelPurchased
			<< "gal    Fuel remaining = " << mVehicle->getCurrentFuel() << " gal" << endl;
	stream << "Fuel used  = " << setw(8) << mFuelConsumed;
	stream << "gal    Fuel stops     = " << mGStationCnt << endl << endl << endl;
}

std::string VehicleTrip::toString() const
{
	std::stringstream ss;
	ss.str("");
	ss.clear();
	string output, type, make, model, time, engineSize, cylCount, tankSize, cityMPG, highwayMPG, currentFuel;

	// Separates elements of vehicle (Because of the difference in order of the vehicle output vs the required
	// vehicle trip output, the vehicle elements must be taken apart
	ss << mVehicle->toString();
	getline(ss, type);
	getline(ss, make);
	getline(ss, model);
	ss >> engineSize >> cylCount >> tankSize >> cityMPG >> highwayMPG >> currentFuel;

	ss.clear();
	ss.str("");

	// Calculations for formatted time
	int days, hours, minutes, remainingTime;
	remainingTime = mTripTime;
	days = mTripTime / (24 * 60);
	remainingTime = mTripTime % (24 * 60);
	hours = remainingTime / 60;
	minutes = remainingTime % 60;

	double fuelAddedCost = mFuelPurchased * mParms.getFuelPrice();
	double fuelConsumedCost = mFuelConsumed * mParms.getFuelPrice();

	// Formats the time and the remaining values
	ss << mTripTime << ODLMTR;
	ss << days << "." << setfill('0') << setw(2) << hours << ":" << setw(2) << minutes << ODLMTR;
	ss << fixed << right << setfill('0') << setw(7) << setprecision(2) << fuelAddedCost << ODLMTR;
	ss << setprecision(2) << setw(7) << fuelConsumedCost << ODLMTR;
	ss << setprecision(4) << setw(9)<< mFuelPurchased << ODLMTR;
	ss << setprecision(4) << setw(9)<< mFuelConsumed << ODLMTR;
	ss << setprecision(4) << setw(9)<< currentFuel << ODLMTR;
	ss << mGStationCnt;

	// Form the string with all of the elements using a delimeter in between
	output = type + ODLMTR + make + ODLMTR + model + ODLMTR + engineSize + ODLMTR + cylCount + ODLMTR +
			tankSize + ODLMTR +	cityMPG + ODLMTR + highwayMPG + ODLMTR + ss.str();

	return output;
}

VehicleTrip & VehicleTrip::operator =(const VehicleTrip &rhs)
{
	// Checks whether the rhs is the same as this
	if (this == &rhs) {
		return *this;
	}

	// Deletes the vehicle if it exists
	if (mVehicle) {
		delete mVehicle;
	}

	// Checks to see if rhs vehicle exists
	if (rhs.mVehicle) {
		mVehicle = rhs.mVehicle->clone();
	} else {
		mVehicle = rhs.mVehicle;
	}

	// Assigns the remaining trip elements
	mFuelPurchased = rhs.mFuelPurchased;
	mFuelConsumed = rhs.mFuelConsumed;
	mCityMiles = rhs.mCityMiles;
	mHighwayMiles = rhs.mHighwayMiles;
	mDriveTime = rhs.mDriveTime;
	mTripTime = rhs.mTripTime;
	mGStationCnt = rhs.mGStationCnt;
	return *this;
}

std::ostream & operator <<(std::ostream &lhs, VehicleTrip &rhs)
{
	lhs << rhs.toString();
	return lhs;
}

double VehicleTrip::calcDriveTime(double miles, TripLeg::RoadType roadType)
{
	int mph;
	if (roadType == TripLeg::CITY) {
		mph = mParms.getCityMph();
	} else if (roadType == TripLeg::HIGHWAY) {
		mph = mParms.getHighwayMph();
	}

	double temp = (miles / mph) * 60;
	return temp;
}

double VehicleTrip::calcRefuelTime()
{
	return mGStationCnt * mVehicle->getRefuelTime();
}

double VehicleTrip::calcRestroomTime()
{
	return (mGStationCnt / 2) * mParms.getRestroomTime();
}

double VehicleTrip::calcSleepTime()
{
	int numOfNaps = mDriveTime / mParms.getAwakeTime();

	// Checks to see if arrival is exactly at nap time
	if (numOfNaps != 0 && numOfNaps % mParms.getNapTime() == 0)
		numOfNaps--;

	return numOfNaps * mParms.getNapTime();
}

void VehicleTrip::increaseFuelConsumed(double miles, TripLeg::RoadType roadType)
{
	double gallons = mVehicle->calcFuelConsumed(miles, roadType);
	mFuelConsumed += gallons;
}

void VehicleTrip::increaseFuelPurchased()
{
	mFuelPurchased += mVehicle->getTankSize() - mVehicle->getCurrentFuel();
}

double VehicleTrip::calcFuelUntilStation(std::vector<TripLeg> &tripLegs, int currLeg, double legTravelled)
{
	double cityMiles, highwayMiles;
	double gasDist = mParms.getGasDistance();
	TripLeg::RoadType type = tripLegs.at(currLeg).getRoadType();
	cityMiles = highwayMiles = 0;

	// Add remaining miles in current trip
	if (type == TripLeg::CITY) {
		cityMiles += tripLegs.at(currLeg).getDistance() - legTravelled;
	} else if (type == TripLeg::HIGHWAY) {
		highwayMiles += tripLegs.at(currLeg).getDistance() - legTravelled;
	}

	// Loop until next gas station is found
	for (int i = currLeg + 1; i < (int)tripLegs.size(); i++) {
		double tripDist = tripLegs.at(i).getDistance();
		TripLeg::RoadType type = tripLegs.at(i).getRoadType();
		double distance = cityMiles + highwayMiles;

		// Is gas station not reached in current leg?
		if (distance < gasDist) {
			// Gas station is in current trip leg
			if ((distance + tripDist) > gasDist) {
				// Add the remainder of the distance
				if (type == TripLeg::CITY) {
					cityMiles += gasDist - distance;
				} else if (type == TripLeg::HIGHWAY) {
					highwayMiles += gasDist - distance;
				}
			} else {
				// Trip leg doesn't contain gas station
				if (type == TripLeg::CITY) {
					cityMiles += tripDist;
				} else if (type == TripLeg::HIGHWAY) {
					highwayMiles += tripDist;
				}
			}
		} else {
			// To exit loop
			i = tripLegs.size();
		}
	}

	double gallons = mVehicle->calcFuelConsumed(cityMiles, TripLeg::CITY) +
					 mVehicle->calcFuelConsumed(highwayMiles, TripLeg::HIGHWAY);
	return gallons;
}


