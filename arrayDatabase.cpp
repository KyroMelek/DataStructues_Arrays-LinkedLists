//Native Libraries
#include <fstream>
#include <iostream>
#include<iomanip>
#include<cmath>

//Local files to include
#include "arrayDatabase.h"

//Common std
using std::ifstream;
using std::cout;
using std::endl;
using std::acos;
using std::sin;
using std::cos;

long double dec_to_rad(long double);

// Constructs Database from file
arrayDatabase::arrayDatabase(string pathToFile)
{   
    ifstream cityDatabaseFile;
    string cities;
    //Start numOfCities at -1 to ignore first line, which is just the heading
    int numOfCitiesInFile = -1;

    //Count number of cities in file
    cityDatabaseFile.open(pathToFile, std::ios::in);
    if (cityDatabaseFile.is_open())
    {
        while (!cityDatabaseFile.eof())
        {
            getline(cityDatabaseFile, cities);
            //ignore empty lines
            if (cities == "")
                continue;
            numOfCitiesInFile++;
        } 
        cityDatabaseFile.close();
    }

    //Allocate array on heap
    size = numOfCitiesInFile;    
    database = new cityRecord[size];
    freeSpots = 0;

    //Copy file contents into array    
    cityDatabaseFile.open(pathToFile, std::ios::in);
    if (cityDatabaseFile.is_open())
    {
        int i = 0;
        bool isFirstLine = true;
        while (!cityDatabaseFile.eof())
        {
            getline(cityDatabaseFile, cities);
            if (cities == "" || isFirstLine)
            {                
                isFirstLine = false;
                continue;
            }                
            else
            {
                string cityName = "";
                string cityXCoord = "";
                string cityYCoord = "";

                bool cityNameRetrieved = false;
                bool cityXCoordRetrieved = false;
                bool cityYCoordRetrieved = false;

                for (unsigned int i = 0; i < cities.size(); i++)
                {
                    if (!cityNameRetrieved && cities[i] != ':')
                    {
                        cityName += cities[i];
                    }
                    else if (cities[i] == ':' )
                    {
                        cityNameRetrieved = true;    
                        continue;
                    }
                    else if (!cityXCoordRetrieved && cities[i] != ',')
                    {
                        cityXCoord += cities[i];
                    }
                    else if (cities[i] == ',')
                    {
                        cityXCoordRetrieved = true;
                        continue;
                    }
                    else if (!cityYCoordRetrieved && cities[i] != '\n')
                    {
                        cityYCoord += cities[i];
                    }
                    else if (cities[i] == '\n')
                    {
                        cityYCoordRetrieved = true;
                        continue;
                    }
                }

                (database + i)->cityName = cityName;
                (database + i)->cityXCoordinate = std::stod(cityXCoord);
                (database + i)->cityYCoordinate = std::stod(cityYCoord);
                i++;
            }            
        }
        cityDatabaseFile.close();
    }
}

//Inserts City into array
//If array is full, allocate new larger array and copy contents of old array into it
//If array is NOT full, insert element in the first available slot
void arrayDatabase::insertCity(string name, double lattitude, double longitude)
{
    //Search array to see if element already exists    
    for (int i = 0; i < size; i++)
    {
        if ((database + i)->cityName == name && (database + i)->cityXCoordinate == lattitude && (database + i)->cityYCoordinate == longitude)
        {
            cout << "\n No need to insert again, as this record exists in the existing data set.\n";
            return;
        }
    }
    cityRecord newRecord{ name, lattitude, longitude };
    //If the array has an available spot, insert in the first available slot
    //Else allocate new array with 5 empty spots and copy
    if (freeSpots > 0)
    {       
        *(database + size - freeSpots) = newRecord;
        --freeSpots;
        cout << "Record inserted successfully.\n";
    }
    else
    {
        cityRecord* databaseTemp = new cityRecord[size + 5];
        for (int i = 0; i < size; i++)
        {
            *(databaseTemp + i) = *(database + i);
        }
        *(databaseTemp + size - freeSpots) = newRecord;
        delete[] database;
        database = databaseTemp;
        size = size + 5;
        freeSpots = 4;
        cout << "Record inserted successfully.\n";
    }
}

//Searches array database for city by name
int arrayDatabase::searchCity(string name, bool shouldLog)
{
    for (int i = 0; i < size - freeSpots; i++)
    {
        if ((database + i)->cityName == name)
        {
            cout << "Output:\n";
            if(shouldLog)
                logRecord(i);
            return i;
        }
    }
    cout << "No such record exists in the existing data set.\n";
    return -1;
}

//Searches array database for city by Coord
int arrayDatabase::searchCity(double xCoord, double yCoord)
{   
    for (int i = 0; i < size - freeSpots; i++)
    {
        if ((database + i)->cityXCoordinate == xCoord && (database + i)->cityYCoordinate)
        {
            cout << "Output:\n";
            logRecord(i);
            return i;
        }
    }
    cout << "No such record exists in the existing data set.\n";
    return -1;
}

//Delete City by name 
void arrayDatabase::deleteCity(string name)
{
    int indexOfCityToDelete = searchCity(name, true);

    if (indexOfCityToDelete == -1)         
        return;    

    //Delete city and shift array to fill the empty spot and place it at the end
    for (int i = indexOfCityToDelete; i < size - 1; i++)
    {
        (database + i)->cityName = (database + i + 1)->cityName;
        (database + i)->cityXCoordinate = (database + i + 1)->cityXCoordinate;
        (database + i)->cityYCoordinate= (database + i + 1)->cityYCoordinate;
    }
    *(database + size - 1) = {};
    ++freeSpots;
    cout << "\nDeleted\n";
}

//Delete City by coord
void arrayDatabase::deleteCity(double lattitude, double longitude)
{
    int indexOfCityToDelete = searchCity(lattitude, longitude);    

    if (indexOfCityToDelete == -1)          
        return;    

    //Delete city and shift array to fill the empty spot and place it at the end
    for (int i = indexOfCityToDelete; i < size - 1; i++)
    {
        *(database + i) = *(database + i + 1);
    }
    *(database + size - 1) = {};
    ++freeSpots;
    cout << "\nDeleted\n";
}

void arrayDatabase::citiesWithinDistance(string name, double distance)
{
    long double R = 3963.191;
    int indexOfSpecifiedLocation = searchCity(name, false);
    long double Lat1 = dec_to_rad((database + indexOfSpecifiedLocation)->cityXCoordinate);;
    long double Long1 = dec_to_rad((database + indexOfSpecifiedLocation)->cityYCoordinate);;   

    for (int i = 0; i < size; i++)
    {
        if (i == indexOfSpecifiedLocation)
            continue;
        long double Lat2 = dec_to_rad((database + i)->cityXCoordinate);
        long double Long2 = dec_to_rad((database + i)->cityYCoordinate);
        long double Distance = R * acos( sin(Lat1) * sin(Lat2) + cos(Lat1) * cos(Lat2) * cos(Long2 - Long1) );
        if (Distance <= distance)
            logRecord(i);
    }
}

//converts latitude or longitude decimal data to radians
long double dec_to_rad(long double degree)
{
    long double M_PI = 3.1415926535;
    return degree * (M_PI / 180.0);
}

////Helper functions
void arrayDatabase::printAllRecords()
{
    for (int i = 0; i < size - freeSpots; i++)
    {
        logRecord(i);
    }
}

void arrayDatabase::logRecord(int index)
{
    cout << std::setprecision(7) << std::fixed 
        << (database + index)->cityName << ": " 
        << (database + index)->cityXCoordinate << ", " 
        << (database + index)->cityYCoordinate << std::endl;
}