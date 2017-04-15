//==============================================================================
// Assignment 4 - Vehicle Records Class
//==============================================================================
/*
    File: VehicleRecords.cpp
    Project: Assignment 4
    Author: Nathaniel Hoefer
    Student ID: X529U639
    Class: CS411 - Spring 2017
	Date: 4/15/2017

******************************************************************************/

#include "VehicleRecords.hpp"

using vehicleNS::DLMTR;

namespace
{
	// Vehicle Type Constants
	static const std::string CAR_TYPE = "Car";
	static const std::string SUV_TYPE = "Suv";
	static const std::string VAN_TYPE = "Van";
	static const std::string MINIVAN_TYPE = "Minivan";
	static const std::string TRUCK_TYPE = "Truck";

	// Parses the input string based on the delimiter given and the element requested.
	//	Preconditions: Elements begin with zero and if exceeds the number of elements within
	//		the string, it will loop around.
	//	Postconditions: None
	//	Returns: String of the parsed element
	std::string parseLine(const std::string str, const int element, const char delimeter)
	{
		int index, len;
		index = len = 0;
		len = str.find(delimeter);
		for (int i = 0; i < element; i++) {
			index += len + 1;
			len = str.find(delimeter, index) - index;
		}
		return str.substr(index, len);
	}

	// Trims both the right and left side of all white spaces
	// 		Preconditions: String contains chars other than white space
	//		Postconditions: None
	// 		Returns: Reference to trimmed string
	std::string& trimString(std::string &str)
	{
		str.erase(0, str.find_first_not_of(" \t\r\n"));
		str.erase(str.find_last_not_of(" \t\r\n") + 1);
		return str;
	}

	// Determines if the entered string contains only digits
	// 		Preconditions: None
	//		Postconditions: None
	//		Returns: True if string contains only digits
	bool isDigits(std::string str)
	{
		bool isDigits = false;
		str = trimString(str);
		for (int i = 0; i < (int) str.length(); i++ ) {
			if (std::isdigit(str[i]) || str[i] == '.') {
				isDigits = true;
			} else {
				isDigits = false;
				i = str.length();
			}
		}
		return isDigits;
	}

	// Converts an integer to a string
	//		Preconditions: None
	//		Postconditions: None
	//		Returns: String containing the int value
	std::string toString(const int val)
	{
		char buffer[10000];
		std::sprintf(buffer, "%d", val);
		std::string str = buffer;
		return str;
	}
}

std::vector<Vehicle *> VehicleRecords::importVehicles(std::string file) throw (std::invalid_argument)
{
	std::ifstream stream;
	stream.open(file.c_str());

	// Validates that the stream is open
	if (stream.fail()) {
		std::string exc = "ERROR - Vehicle Import: Unable to open vehicles file: " + file;
		throw std::invalid_argument(exc);
	}

	std::string line = "";
	std::string type, make, model, temp;
	double engine, tankSize;
	int cylinders, cityMPG, highwayMPG;
	std::vector<Vehicle *> vehicles;
	int lineNum = 1;

	// Stream in each line and trim
	while (!stream.eof()) {
		getline(stream, line);

		// Trim line of extra whitespace
		line.erase(0, line.find_first_not_of(" \t\r\n"));

		// Check to see if it is a comment line
		if (line[0] != '#' && !line.empty()) {

			// Element within vehicle records line
			int element = 0;

			// Parse vehicle type
			type = parseLine(line, element++, DLMTR[0]);
			type = trimString(type);

			// Parse vehicle make
			make = parseLine(line, element++, DLMTR[0]);
			make = trimString(make);

			// Parse vehicle model
			model = parseLine(line, element++, DLMTR[0]);
			model = trimString(model);

			// Parse vehicle engine
			temp = parseLine(line, element++, DLMTR[0]);
			temp = trimString(temp);
			if (!isDigits(temp)) {
				std::string exc = "ERROR - Vehicle Import: Invalid Engine Type [" + toString(lineNum) + "]: \"" + temp + "\"";
				throw std::invalid_argument(exc);
			}
			engine = std::atof(temp.c_str());

			// Parse vehicle cylinder count
			temp = parseLine(line, element++, DLMTR[0]);
			temp = trimString(temp);
			if (!isDigits(temp)) {
				std::string exc = "ERROR - Vehicle Import: Invalid Cylinder Count [" + toString(lineNum) + "]: \"" + temp + "\"";
				throw std::invalid_argument(exc);
			}
			cylinders = std::atoi(temp.c_str());

			// Parse vehicle tank size
			temp = parseLine(line, element++, DLMTR[0]);
			temp = trimString(temp);
			if (!isDigits(temp)) {
				std::string exc = "ERROR - Vehicle Import: Invalid Tank Size [" + toString(lineNum) + "]: \"" + temp + "\"";
				throw std::invalid_argument(exc);
			}
			tankSize = std::atof(temp.c_str());

			// Parse vehicle city MPG
			temp = parseLine(line, element++, DLMTR[0]);
			temp = trimString(temp);
			if (!isDigits(temp)) {
				std::string exc = "ERROR - Vehicle Import: Invalid City MPG [" + toString(lineNum) + "]: \"" + temp + "\"";
				throw std::invalid_argument(exc);
			}
			cityMPG = std::atoi(temp.c_str());

			// Parse vehicle highway MPG
			temp = parseLine(line, element++, DLMTR[0]);
			temp = trimString(temp);
			if (!isDigits(temp)) {
				std::string exc = "ERROR - Vehicle Import: Invalid Highway MPG [" + toString(lineNum) + "]: \"" + temp + "\"";
				throw std::invalid_argument(exc);
			}
			highwayMPG = std::atoi(temp.c_str());

			// Creates the vehicles based on type
			if (type == CAR_TYPE) {
				vehicles.push_back(new Car(make, model, engine, cylinders, tankSize, cityMPG, highwayMPG));
			} else if (type == SUV_TYPE) {
				vehicles.push_back(new Suv(make, model, engine, cylinders, tankSize, cityMPG, highwayMPG));
			} else if (type == VAN_TYPE) {
				vehicles.push_back(new Van(make, model, engine, cylinders, tankSize, cityMPG, highwayMPG));
			} else if (type == MINIVAN_TYPE) {
				vehicles.push_back(new Minivan(make, model, engine, cylinders, tankSize, cityMPG, highwayMPG));
			} else if (type == TRUCK_TYPE) {
				vehicles.push_back(new Truck(make, model, engine, cylinders, tankSize, cityMPG, highwayMPG));
			}
		}
		lineNum++;
	}
	if (vehicles.empty()) {
		std::string exc = "ERROR - Vehicle Import: File \"" + file + "\" does not contain any vehicle records";
		throw std::invalid_argument(exc);
	}
	return vehicles;
}
