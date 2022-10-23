#pragma once
#include<string>
using std::string;

class linkedListDatabase
{
public:
	struct cityRecordNode {
		string cityName = "";
		double cityXCoordinate = 0;
		double cityYCoordinate = 0;
		cityRecordNode* next = nullptr;
	};
	
	cityRecordNode* head = nullptr;

	//Constructors
	linkedListDatabase(string pathToFile);	
	~linkedListDatabase();

	//Public Methods
	//Inserts City into databse 
	void insertCity(string name, double lattitude, double longitude, bool shouldLog);
	//Deletes city from DB by name
	void deleteCity(string name);
	//Deletes city from DB by coords
	void deleteCity(double lattitude, double longitude);
	//Searches for city by name
	cityRecordNode** searchCity(string name, bool shouldLog);
	//Searches for city by coords
	cityRecordNode** searchCity(double lattitude, double longitude, bool shouldLog);
	//Returns all citeis within a given distance of a given point 
	void citiesWithinDistance(string name, double distance);
	//Prints all cities in DB
	void printAllRecords();

	//HelperFunctions	
	void logRecord(cityRecordNode* record);
	long double dec_to_rad(long double degree);

	//Destructor
	
};