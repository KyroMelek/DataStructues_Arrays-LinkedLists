#pragma once
#include<string>
using std::string;

class arrayDatabase
{
public:
	struct cityRecord {
		string cityName = "";
		double cityXCoordinate = 0;
		double cityYCoordinate = 0;
	};
	cityRecord* database = nullptr;
	int size = 0;
	int freeSpots = 0 ;

	//Constructors
	arrayDatabase(string pathToFile);
	arrayDatabase() {};

	//Public Methods
	//Inserts City into databse 
	void insertCity(string name, double lattitude, double longitude);
	//Deletes city from DB by name
	void deleteCity(string name);
	//Deletes city from DB by coords
	void deleteCity(double lattitude, double longitude);
	//Searches for city by name
	int searchCity(string name, bool shouldLog);
	//Searches for city by coords
	int searchCity(double lattitude, double longitude);
	//Returns all citeis within a given distance of a given point 
	void citiesWithinDistance(string name, double distance);
	//Prints all cities in DB
	void printAllRecords();

	//HelperFunctions	
	void logRecord(int index);

	//Destructor
	~arrayDatabase() { delete[] database; }

};