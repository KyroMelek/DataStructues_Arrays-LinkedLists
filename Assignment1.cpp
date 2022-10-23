//Kyrolos Melek
//
// Purpose: This program runs a database of cities and supports common operations
//such as insertion, deletion, and searching of cities using both linked list and array 
//implementations. The program also supports returning all cities within a given distance
//of a specified point. 


//Built in Libraries
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

//Local files
#include"arrayDatabase.h"
#include"linkedListDatabase.h"

//Common std 
using std::cout;
using std::cin;
using std::endl;
using std::string;

//Funtion Declarations 
void mainMenu();
int operationMenu();
void arrayImplementation(arrayDatabase&);
void linkedListImplementation(linkedListDatabase&);
long double dec_to_rad(long double);

int main()
{   
    mainMenu();
}

void mainMenu()
{
    bool isValidInput = false;
    while (!isValidInput)
    {
        char implementationOption;

        cout << "Implementation Options :\n";
        cout << "A. Use an array - based list implementation\n";
        cout << "B. Use a linked - list implementation\n\n";

        cout << "Enter your implementation option :";
        cin >> implementationOption;
        if (implementationOption != 'A' && implementationOption != 'a' && implementationOption != 'B' && implementationOption != 'b')
        {
            cout << "Invalid Implementation Option. Please try again. \n \n";
            cin.clear();
            cin.ignore(123, '\n');                        
        }
        else if (implementationOption == 'A' || implementationOption == 'a')
        {
            arrayDatabase cityDatabase("Assignment 1_Test Data_For Windows Users.txt");
            arrayImplementation(cityDatabase);
            isValidInput = true;
        }
        else if (implementationOption == 'B' || implementationOption == 'b')
        {
            linkedListDatabase cityDatabase("Assignment 1_Test Data_For Windows Users.txt");
            linkedListImplementation(cityDatabase);
            isValidInput = true;
        }
    }
}

void arrayImplementation(arrayDatabase& cityDatabase)
{
    bool shouldExit = false;
    while (!shouldExit)
    {
        int OperationOption = operationMenu();
        if (OperationOption == 8)
            return;
        switch (OperationOption)
        {
        case 1:
        {
            string cityName;
            double xCoord;
            double yCoord;
            cout << "\n Enter name of the city: ";
            cin >> cityName;
            cout << "\n Enter x coordinate of the city:";
            cin >> xCoord;
            cout << "\n Enter y coordinate of the city:";
            cin >> yCoord;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.insertCity(cityName, xCoord, yCoord);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
            
            break;
        }
        case 2:
        {
            string cityName;
            cout << "\nEnter name of the city to be searched: ";
            cin >> cityName;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.searchCity(cityName, true);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

            
        }
            break;
        case 3:
        {
            double xCoord;
            double yCoord;                       
            cout << "\n Enter x coordinate of the city:";
            cin >> xCoord;
            cout << "\n Enter y coordinate of the city:";
            cin >> yCoord;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.searchCity(xCoord, yCoord);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";            
        }
            break;
        case 4:
        {
            string cityName;
            cout << "\nEnter name of the city to be deleted: ";
            cin >> cityName;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.deleteCity(cityName);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";            
        }
            break;
        case 5:
        {
            double xCoord;
            double yCoord;
            cout << "\n Enter x coordinate of the city to be deleted:";
            cin >> xCoord;
            cout << "\n Enter y coordinate of the city to be deleted:";
            cin >> yCoord;
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.deleteCity(xCoord, yCoord);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";            
        }
            break;
        case 6:
        {
            string cityName;
            cout << "\nEnter name of the city: ";
            cin >> cityName;
            double distance;
            cout << "\nEnter distance: ";
            cin >> distance;
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.citiesWithinDistance(cityName, distance);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";            
        }
            break;
        case 7:
            cityDatabase.printAllRecords();
            break;
        }
        cin.clear();
        cin.ignore(123, '\n');
    }        
}

void linkedListImplementation(linkedListDatabase& cityDatabase)
{
    bool shouldExit = false;
    while (!shouldExit)
    {
        int OperationOption = operationMenu();
        if (OperationOption == 8)
            return;
        switch (OperationOption)
        {
        case 1:
        {
            string cityName;
            double xCoord;
            double yCoord;
            cout << "\n Enter name of the city: ";
            cin >> cityName;
            cout << "\n Enter x coordinate of the city:";
            cin >> xCoord;
            cout << "\n Enter y coordinate of the city:";
            cin >> yCoord;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.insertCity(cityName, xCoord, yCoord, true);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";            
            break;
        }
        case 2:
        {
            string cityName;
            cout << "\nEnter name of the city to be searched: ";
            cin >> cityName;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.searchCity(cityName, true);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";            
        }
        break;
        case 3:
        {
            double xCoord;
            double yCoord;
            cout << "\n Enter x coordinate of the city:";
            cin >> xCoord;
            cout << "\n Enter y coordinate of the city:";
            cin >> yCoord;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.searchCity(xCoord, yCoord, true);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";            
        }
        break;
        case 4:
        {
            string cityName;
            cout << "\nEnter name of the city to be deleted: ";
            cin >> cityName;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.deleteCity(cityName);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";            
        }
        break;
        case 5:
        {
            double xCoord;
            double yCoord;
            cout << "\n Enter x coordinate of the city to be deleted:";
            cin >> xCoord;
            cout << "\n Enter y coordinate of the city to be deleted:";
            cin >> yCoord;
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.deleteCity(xCoord, yCoord);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";            
        }
        break;
        case 6:
        {
            string cityName;
            cout << "\nEnter name of the city: ";
            cin >> cityName;
            double distance;
            cout << "\nEnter distance: ";
            cin >> distance;

            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();

            cityDatabase.citiesWithinDistance(cityName, distance);

            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = (end - start);
            std::time_t end_time = std::chrono::system_clock::to_time_t(end);
            std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";            
        }
        break;
        case 7:
            cityDatabase.printAllRecords();
            break;
        }
        cin.clear();
        cin.ignore(123, '\n');
    }
}

int operationMenu()
{
    bool operationValid = false;
    while (!operationValid)
    {
        int OperationOption;
        cout << "\nOperation Options :\n";
        cout << "1. Insert a record\n";
        cout << "2. Search for a record by name\n";
        cout << "3. Search for a record by coordinate\n";
        cout << "4. Delete a record by name\n";
        cout << "5. Delete a record by coordinate\n";
        cout << "6. Print records within a given distance of a specified location\n";
        cout << "7. Print all records\n";
        cout << "8. Exit\n";

        cout << "Enter your operation option :";
        cin >> OperationOption;
        if (OperationOption < 1 || OperationOption > 8)
        {
            cout << "\n Invalid Operation Option. Please try again. \n \n";
            cin.clear();
            cin.ignore(123, '\n');
        }        
        else
            return OperationOption;
    }    
}



