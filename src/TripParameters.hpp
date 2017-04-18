//==============================================================================
// Assignment 4 - TripParameters Class
//==============================================================================
/*
    File: TripParameters.hpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/15/2017

******************************************************************************/

#ifndef PARAMETERS_HPP_
#define PARAMETERS_HPP_

#include <string>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

class TripParameters
{
public:
	TripParameters();
	TripParameters(int cityMPH, int highwayMPH, double fuelPrice, int restroomTimeMins,
			int napTimeMins, int awakeTimeHrs, double gasDistance);

	// Accessor Methods
	int 	getCityMph() const;
	int 	getHighwayMph() const;
	double 	getFuelPrice() const;
	int 	getRestroomTime() const;
	int 	getNapTime() const;
	int 	getAwakeTime() const;
	double 	getGasDistance() const;

	// Mutator Methods
	void 	setCityMph(int cityMph);
	void 	setHighwayMph(int highwayMph);
	void 	setFuelPrice(double fuelPrice);
	void 	setRestroomTime(int restroomTime);
	void 	setNapTime(int napTime);
	void 	setAwakeTime(int awakeTime);
	void 	setGasDistance(double gastDistance);

	// Retrieves the parameters from the entered file and updates the data as such
	//		Preconditions: The file must contain the labels listed as constants
	//			followed by the '=' and then the value. Extra white space is ignored
	//			and lines beginning with '#' are treated as comment lines and ignored.
	//		Postconditions: Values found in file are imported to member variables.
	//			If the parameter is not found, the default value will be used.
	void retrieveParms(const std::string &file) throw (std::invalid_argument);

private:
	int mCityMPH;
	int mHighwayMPH;
	double mFuelPrice;
	int mRestroomTimeMins;		// in minutes
	int mNapTimeMins;			// in minutes
	int mAwakeTimeMins;			// in minutes
	double mGasDistance;		// in miles
};

#endif /* PARAMETERS_HPP_ */
