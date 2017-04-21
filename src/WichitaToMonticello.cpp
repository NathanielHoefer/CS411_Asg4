//==============================================================================
// Assignment 4 - WichitaToMonticello
//==============================================================================
/*
    File: WichitaToMonticello.cpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/7/2017

    Simulates a trip from Wichita to Monticello with a number of vehicles to
    determine which vehicles take the least/most time, require the least/most
    fuel purchased, and require the least/most consumed. This program imports both
    the vehicles and the parameters from the string constants provided at the
    beginning of this file. The results are printed to the console as well as to
    the file specified by the string constant OUTPUT_FILE. Helper functions and
    Test drivers were moved to separate files in order to clean this file. The
    vehicles are now stored as dynamic pointers in a vector.

    Notes: Input values have not been fully checked for values ranging far beyond
    reasonable values since it was not explicitly mentioned in the rubric.


******************************************************************************/

#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "VehicleTrip.hpp"
#include "TripLeg.hpp"
#include "Car.hpp"
#include "Suv.hpp"
#include "Van.hpp"
#include "Minivan.hpp"
#include "Truck.hpp"
#include "VehicleRecords.hpp"

using namespace std;

// Helper Function Prototypes
vector<TripLeg> initializeTripLegs();
void printResults(VehicleTrip shortestTime, VehicleTrip longestTime, VehicleTrip leastFuelAdded,
				VehicleTrip mostFuelAdded, VehicleTrip leastFuelUsed, VehicleTrip mostFuelUsed,
				ofstream &output);
void printVehicleStats(VehicleTrip trip);
void printToFile(VehicleTrip &trip, ofstream &output);
bool compareVehicleTrips(const VehicleTrip *vt1, const VehicleTrip *vt2);

// File name constants
static const string VEHICLE_FILE = "WichitaToMonticello-Vehicles2.txt";
static const string PARMS_FILE = "WichitaToMonticello-Input.ini";
static const string OUTPUT_FILE = "WichitaToMonticello-Results2.txt";
static const string MAIN_DLMTR = "|";

int main()
{
	cout << "========================================================" << endl;
	cout << "           Wichita to Monticello - Assignment 4         " << endl;
	cout << "========================================================" << endl;

	vector<Vehicle *> vehicles;
	vector<TripLeg> tripLegs = initializeTripLegs();
	TripParameters parms;
	vector<VehicleTrip *> vehicleTrips;

	// Exits the program if vehicles or parameters are not properly imported
	try {
		vehicles = VehicleRecords::importVehicles(VEHICLE_FILE);
		parms.retrieveParms(PARMS_FILE);
	} catch (invalid_argument &e) {
		cout << e.what() << endl;
		cout << "ENDING PROGRAM" << endl;
		exit(1);
	} catch (exception &e) {
		cout << e.what() << endl;
		cout << "ENDING PROGRAM" << endl;
		exit(1);
	}

	// Run initial trip and initialize output stream
	vehicleTrips.push_back(new VehicleTrip (vehicles.at(0), parms));
	vehicleTrips[0]->runTrip(tripLegs);

	// Initializes records
	VehicleTrip shortestTime = 	*vehicleTrips[0];
	VehicleTrip longestTime = 	*vehicleTrips[0];
	VehicleTrip leastFuelAdded = *vehicleTrips[0];
	VehicleTrip mostFuelAdded = *vehicleTrips[0];
	VehicleTrip leastFuelUsed = *vehicleTrips[0];
	VehicleTrip mostFuelUsed = 	*vehicleTrips[0];

	// Process each vehicle trip and determine the results
	for (int i = 1; i < (int)vehicles.size(); i++) {
		vehicleTrips.push_back(new VehicleTrip(vehicles.at(i), parms));
		vehicleTrips[i]->runTrip(tripLegs);

		// Updates results
		if (vehicleTrips[i]->getTripTime() < shortestTime.getTripTime())
			shortestTime = *vehicleTrips[i];
		if (vehicleTrips[i]->getTripTime() > longestTime.getTripTime())
			longestTime = *vehicleTrips[i];
		if (vehicleTrips[i]->getFuelPurchased() < leastFuelAdded.getFuelPurchased())
			leastFuelAdded = *vehicleTrips[i];
		if (vehicleTrips[i]->getFuelPurchased() > mostFuelAdded.getFuelPurchased())
			mostFuelAdded = *vehicleTrips[i];
		if (vehicleTrips[i]->getFuelConsumed() < leastFuelUsed.getFuelConsumed())
			leastFuelUsed = *vehicleTrips[i];
		if (vehicleTrips[i]->getFuelConsumed() > mostFuelUsed.getFuelConsumed())
			mostFuelUsed = *vehicleTrips[i];
	}

	// Open output file and print the header
	ofstream outputStream(OUTPUT_FILE.c_str());
	outputStream << "Type|Make|Model|EngineSize|EngineCylinders|TankSize|MpgCity|MpgHighway|Time(minutes)|Time(d.hh:mm)";
	outputStream << "|CostFueldAdded|CostFuelUsed|FuelAdded|FuelUsed|FuelRemaining|FuelStops" << endl << endl;

	// Sort and print each vehicle trip
	std::sort(vehicleTrips.begin(), vehicleTrips.end(), compareVehicleTrips);
	for (int i = 0; i < (int) vehicleTrips.size(); i++) {
		printToFile(*vehicleTrips[i], outputStream);
		outputStream << endl;
	}

	// Print the formatted results
	printResults(shortestTime, longestTime, leastFuelAdded, mostFuelAdded,
			leastFuelUsed, mostFuelUsed, outputStream);
}

// Creates trip leg objects for the trip from Wichita to Monticello
//		Preconditions: None
//		Postconditions: None
//		Returns: a vector containing all of the instantiated trip legs in the
//			correct order
vector<TripLeg> initializeTripLegs()
{
	vector<TripLeg> tripLegs;
	tripLegs.push_back(TripLeg(3.3, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(23.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(0.05, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(0.2, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(56.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(50.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(6.8, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(53.5, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(21.3, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(229, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(2.8, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(74.7, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(47.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(69.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(0.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(24.3, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(21.2, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(79.2, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(208, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(181.3, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(86.6, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(106.7, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(8.0, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(45.6, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(0.1, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(0.5, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(22.7, 	TripLeg::HIGHWAY));
	tripLegs.push_back(TripLeg(0.6, 	TripLeg::CITY));
	tripLegs.push_back(TripLeg(1.7, 	TripLeg::CITY));
	return tripLegs;
}

// Prints the results of the trip to the console and the ofstream provided.
//		Preconditions: The entered vehicle trips have already been run with the
//			stats calculated
//		Postconditions: The formatted results printed to the console and ofstream
void printResults(VehicleTrip shortestTime, VehicleTrip longestTime,
					VehicleTrip leastFuelAdded, VehicleTrip mostFuelAdded,
					VehicleTrip leastFuelUsed, VehicleTrip mostFuelUsed,
					ofstream &output)
{
	cout << "========================================================" << endl;
	cout << "                      Trip Results                      " << endl;
	cout << "========================================================" << endl;

	cout << setw(14) << "" << "Total miles driven = " << fixed << setprecision(2)
			<< shortestTime.getCityMiles() + shortestTime.getHighwayMiles()
			<< endl;
	cout << setw(10) << "" << fixed << setprecision(2) << left
			<< "City = " << setw(12) << shortestTime.getCityMiles();
	cout << fixed << setprecision(2) << "Highway = "
			<< shortestTime.getHighwayMiles() << endl << endl << endl;

	cout << "========================================================" << endl;
	cout << "   1. Vehicle ariving first at Jefferson's Monticello:  " << endl;
	cout << "========================================================" << endl;
	shortestTime.formattedTrip(cout);
	output << endl;
	printToFile(shortestTime, output);
	output << "  # Vehicle arriving first" << endl;

	cout << "========================================================" << endl;
	cout << "   2. Vehicle arriving last at Jefferson's Monticello:  " << endl;
	cout << "========================================================" << endl;
	longestTime.formattedTrip(cout);
	printToFile(longestTime, output);
	output << "  # Vehicle arriving last" << endl;

	cout << "========================================================" << endl;
	cout << "   3. Vehicle costing the least to reach Jefferson's    " << endl;
	cout << "        Monticello based on fuel added to tank:         " << endl;
	cout << "========================================================" << endl;
	leastFuelAdded.formattedTrip(cout);
	printToFile(leastFuelAdded, output);
	output << "  # Vehicle costing least (fuel added)" << endl;

	cout << "========================================================" << endl;
	cout << "   4. Vehicle costing the most to reach Jefferson's     " << endl;
	cout << "        Monticello based on fuel added to tank:         " << endl;
	cout << "========================================================" << endl;
	mostFuelAdded.formattedTrip(cout);
	printToFile(mostFuelAdded, output);
	output << "  # Vehicle costing most (fuel added)" << endl;

	cout << "========================================================" << endl;
	cout << "   5. Vehicle costing the least to reach Jefferson's    " << endl;
	cout << "         Monticello based on actual fuel used:          " << endl;
	cout << "========================================================" << endl;
	leastFuelUsed.formattedTrip(cout);
	printToFile(leastFuelUsed, output);
	output << "  # Vehicle costing least (fuel used)" << endl;

	cout << "========================================================" << endl;
	cout << "   6. Vehicle costing the most to reach Jefferson's     " << endl;
	cout << "         Monticello based on actual fuel used:          " << endl;
	cout << "========================================================" << endl;
	mostFuelUsed.formattedTrip(cout);
	printToFile(mostFuelUsed, output);
	output << "  # Vehicle costing most (fuel used)" << endl;
}

// Prints the formatted vehicle stats from the trip entered to the console
//		Preconditions: The trip entered has already be run
//		Postconditions: Formatted stats are printed
void printVehicleStats(VehicleTrip trip)
{
	stringstream results;
	results << trip;
	string temp;
	string make, model;
	int cityMPG, highwayMPG, tripTime, gStationCnt;
	double tankSize, currentFuel, fuelPurchased, fuelConsumed;

	// Parses the results from stream
	getline(results, temp, MAIN_DLMTR[0]);
	make = temp;
	getline(results, temp, MAIN_DLMTR[0]);
	model = temp;
	getline(results, temp, MAIN_DLMTR[0]);
	getline(results, temp, MAIN_DLMTR[0]);
	getline(results, temp, MAIN_DLMTR[0]);
	tankSize = atof(temp.c_str());
	getline(results, temp, MAIN_DLMTR[0]);
	cityMPG = atoi(temp.c_str());
	getline(results, temp, MAIN_DLMTR[0]);
	highwayMPG = atoi(temp.c_str());
	getline(results, temp, MAIN_DLMTR[0]);
	currentFuel = atof(temp.c_str());
	getline(results, temp, MAIN_DLMTR[0]);
	tripTime = atoi(temp.c_str());
	getline(results, temp, MAIN_DLMTR[0]);
	fuelPurchased = atof(temp.c_str());
	getline(results, temp, MAIN_DLMTR[0]);
	fuelConsumed = atof(temp.c_str());
	getline(results, temp, MAIN_DLMTR[0]);
	gStationCnt = atoi(temp.c_str());

	// Calculations for centering title
	int titleLen = make.size() + model.size() + 1;
	int leftTitleSpace = (56 - titleLen) / 2;

	// Calculations for formatted time
	int days, hours, minutes, remainingTime;
	remainingTime = tripTime;
	days = tripTime / (24 * 60);
	remainingTime = tripTime % (24 * 60);
	hours = remainingTime / 60;
	minutes = remainingTime % 60;

	double fuelAddedCost = fuelPurchased * trip.getParms().getFuelPrice();
	double fuelConsumedCost = fuelConsumed * trip.getParms().getFuelPrice();

	// Formats output
	cout << setw(leftTitleSpace) << "";
	cout << make << " " << model		   << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << left << fixed << setprecision(2);
	cout << "Tank Size = " << setw(6) << tankSize;
	cout << "gal   City MPG = " << setw(5) << cityMPG;
	cout << "Highway MPG = " << highwayMPG << endl;;
	cout << "--------------------------------------------------------" << endl;
	cout << "Trip time(minutes) = " << setw(7) << tripTime;
	cout << "Trip time(d.hh:mm) = " << days << "." << setfill('0') << right
			<< setw(2) << hours << ":" << setw(2) << minutes << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << left << setfill(' ');
	cout << "Trip cost based on fuel added = $" << fuelAddedCost << endl;
	cout << "Trip cost based on fuel used  = $" << fuelConsumedCost << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Fuel added = " << setw(8) << setprecision(4) << fuelPurchased
			<< "gal    Fuel remaining = " << currentFuel << " gal" << endl;
	cout << "Fuel used  = " << setw(8) << fuelConsumed;
	cout << "gal    Fuel stops     = " << gStationCnt << endl << endl << endl;
}

// Appends the vehicle stats from the trip entered to the stream entered
//		Preconditions: Trip entered has already been ran
//		Postcontitions: Trip printed in the following format:
//			Make|Model|EngineSize|EngineCylinders|TankSize|MpgCity|MpgHighway|Time(minutes)|Time(d.hh:mm)|
//			CostFueldAdded|CostFuelUsed|FuelAdded|FuelUsed|FuelRemaining|FuelStops
void printToFile(VehicleTrip &trip, ofstream &output)
{
	stringstream results;
	results << trip;
	string temp;

	output << trip;
}

// Compares the current fuel of two vehicle trips
bool compareVehicleTrips(const VehicleTrip *vt1, const VehicleTrip *vt2)
{
	return vt1->getVehicle()->getCurrentFuel() < vt2->getVehicle()->getCurrentFuel();
}
