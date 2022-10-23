//Native Libraries
#include <fstream>
#include <iostream>
#include<iomanip>
#include<cmath>

#include"linkedListDatabase.h"

//Common std
using std::ifstream;
using std::cout;
using std::endl;
using std::acos;
using std::sin;
using std::cos;

linkedListDatabase::linkedListDatabase(string pathToFile) : head(nullptr)
{
	ifstream cityDatabaseFile;
	string cities;

	//Copy file contents into array    
	cityDatabaseFile.open(pathToFile, std::ios::in);
	if (cityDatabaseFile.is_open())
	{		
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
					else if (cities[i] == ':')
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
				insertCity(cityName, std::stod(cityXCoord), std::stod(cityYCoord), false);								
			}
		}
		cityDatabaseFile.close();
	}
}

//Linked List operations 
void linkedListDatabase::insertCity(string name, double lattitude, double longitude, bool shouldLog=true)
{	
	cityRecordNode* iteratorNode;			
	cityRecordNode* newCity;
	//Allocate a new node and store its data
	newCity = new cityRecordNode;
	newCity->cityName = name;
	newCity->cityXCoordinate = lattitude;
	newCity->cityYCoordinate = longitude;
	newCity->next = nullptr;

	//If there are no nodes in the list 
	//make this new node the first node
	if (!head) //if head is null 
	{
		head = newCity;
		if(shouldLog)
			cout << "Record inserted successfully.\n";
	}
	else //Otherwise insert new Node at the end
	{
		//Initialize iteratorNode to the head of the list 
		iteratorNode = head;

		//Find the last node in the list
		//Search array to see if element already exists    
		while (iteratorNode->next)
		{
			if (iteratorNode->cityName == name && iteratorNode->cityXCoordinate == lattitude && iteratorNode->cityYCoordinate == longitude)
			{
				cout << "\n No need to insert again, as this record exists in the existing data set.\n";
				return;
			}
			else
				iteratorNode = iteratorNode->next;
		}
		//Insert newNode as the last node
		iteratorNode->next = newCity;
		if (shouldLog)
			cout << "Record inserted successfully.\n";
	}
}

linkedListDatabase::cityRecordNode** linkedListDatabase::searchCity(string name, bool shouldLog=true)
{
	//What we will return: An array where the first element is the node prior to the node being searched for 
	// and the second element is the node being searched for
	//Since an array can not be returned directly from a method, a pointer to the array will be returned
	static cityRecordNode* resultNodes[2] = {nullptr, nullptr};
	cityRecordNode** Result = resultNodes;

	cityRecordNode* iteratorNode = nullptr; //To traverse the array
	cityRecordNode* previousNode = nullptr; //To point to the previous node

	//If the list is empty, return the pointer to the empty array
	if (!head)
	{
		if(shouldLog)
			cout << "No such record exists in the existing data set.\n";
		return Result;
	}

	//Determine if the first node is the one 
	if (head->cityName == name)
	{
		resultNodes[1] = head;		
		if (shouldLog)
			logRecord(head);
		return Result;
	}
	else
	{
		//Initialize iteratorNode to the head
		iteratorNode = head;

		//Skip all nodes whose value member is not what was passed
		//Adds a gaurd for Node not being in the list at all
		while (iteratorNode != nullptr && iteratorNode->cityName != name)
		{
			previousNode = iteratorNode;
			iteratorNode = iteratorNode->next;
		}

		if (!iteratorNode)
		{
			if (shouldLog)
				cout << "No such record exists in the existing data set.\n";
			return Result;
		}
		else
		{
			if(shouldLog)
				logRecord(iteratorNode);
		}		
		//If node is found and is not head, return previos node. This allows us to rewire the nodes when deleting without having to traverse again
		resultNodes[0] = previousNode;
		resultNodes[1] = iteratorNode;		
		return Result;
	}
}

linkedListDatabase::cityRecordNode** linkedListDatabase::searchCity(double xCoord, double yCoord, bool shouldLog=true)
{
	//What we will return: An array where the first element is the node prior to the node being searched for 
// and the second element is the node being searched for
//Since an array can not be returned directly from a method, a pointer to the array will be returned
	static cityRecordNode* resultNodes[2] = { nullptr, nullptr };
	cityRecordNode** Result = resultNodes;

	cityRecordNode* iteratorNode = nullptr; //To traverse the array
	cityRecordNode* previousNode = nullptr; //To point to the previous node

	//If the list is empty, return the pointer to the empty array
	if (!head)
	{
		if (shouldLog)
			cout << "No such record exists in the existing data set.\n";
		return Result;
	}

	//Determine if the first node is the one 
	if (head->cityXCoordinate == xCoord && head->cityYCoordinate == yCoord)
	{
		resultNodes[1] = head;
		if (shouldLog)
			logRecord(head);
		return Result;
	}
	else
	{
		//Initialize iteratorNode to the head
		iteratorNode = head;

		//Skip all nodes whose value member is not what was passed
		//Adds a gaurd for Node not being in the list at all
		while (iteratorNode != nullptr)
		{
			if ((iteratorNode->cityXCoordinate == xCoord) && (iteratorNode->cityYCoordinate == yCoord))
				break;
			previousNode = iteratorNode;
			iteratorNode = iteratorNode->next;
		}

		if (!iteratorNode)
		{
			if (shouldLog)
				cout << "No such record exists in the existing data set.\n";
			return Result;
		}
		else
		{
			if (shouldLog)
				logRecord(iteratorNode);
		}
		//If node is found and is not head, return previos node. This allows us to rewire the nodes when deleting without having to traverse again
		resultNodes[0] = previousNode;
		resultNodes[1] = iteratorNode;
		return Result;
	}
}

void linkedListDatabase::deleteCity(string name)
{
	cityRecordNode** searchResult = searchCity(name);
	cityRecordNode* previousNode = searchResult[0];
	cityRecordNode* recordToDelete = searchResult[1];

	//If the city was not found, return
	if (recordToDelete == nullptr)
		return;	
	//If we are trying to delete the head
	if (recordToDelete == head)
	{
		head = head->next;
		delete recordToDelete;
		cout << "\nDeleted\n";
	}
	else
	{
		previousNode->next = recordToDelete->next;
		delete recordToDelete;
		cout << "\nDeleted\n";
	}			
}

void linkedListDatabase::deleteCity(double xCoord, double yCoord)
{
	cityRecordNode** searchResult = searchCity(xCoord, yCoord);
	cityRecordNode* previousNode = searchResult[0];
	cityRecordNode* recordToDelete = searchResult[1];

	//If the city was not found, return
	if (recordToDelete == nullptr)
		return;
	//If we are trying to delete the head
	if (recordToDelete == head)
	{
		head = head->next;
		delete recordToDelete;
		cout << "\nDeleted\n";
	}
	else
	{
		previousNode->next = recordToDelete->next;
		delete recordToDelete;
		cout << "\nDeleted\n";
	}
}

void linkedListDatabase::citiesWithinDistance(string name, double distance)
{	
	cityRecordNode* SpecifiedLocation = searchCity(name, false)[1];	
	
	//If location not in DB
	if(!SpecifiedLocation)
	{
		cout << "No such record exists in the existing data set.\n";
		return;
	}

	long double R = 3963.191;
	long double Lat1 = dec_to_rad(SpecifiedLocation->cityXCoordinate);;
	long double Long1 = dec_to_rad(SpecifiedLocation->cityYCoordinate);;

	cityRecordNode* iteratorNode; //To traverse the array		
	//Initialize iteratorNode to the head
	iteratorNode = head;

	//Skip all nodes whose value member is not what was passed
	//Adds a check for Node not being in the list at all
	while (iteratorNode != nullptr)
	{
		if (iteratorNode == SpecifiedLocation)
		{				
			iteratorNode = iteratorNode->next;
			continue;
		}
		long double Lat2 = dec_to_rad(iteratorNode->cityXCoordinate);
		long double Long2 = dec_to_rad(iteratorNode->cityYCoordinate);
		long double Distance = R * acos(sin(Lat1) * sin(Lat2) + cos(Lat1) * cos(Lat2) * cos(Long2 - Long1));
		if (Distance <= distance)
			logRecord(iteratorNode);			
		iteratorNode = iteratorNode->next;
	}
	
}

//converts latitude or longitude decimal data to radians
long double linkedListDatabase::dec_to_rad(long double degree)
{
	long double M_PI = 3.1415926535;
	return degree * (M_PI / 180.0);
}

void linkedListDatabase::printAllRecords()
{
	cityRecordNode* iteratorNode;
	iteratorNode = head;
	while (iteratorNode != nullptr)
	{
		logRecord(iteratorNode);
		iteratorNode = iteratorNode->next;
	}
}

void linkedListDatabase::logRecord(cityRecordNode* record)
{
	cout << std::setprecision(7) << std::fixed
		<< record->cityName << ": "
		<< record->cityXCoordinate << ", "
		<< record->cityYCoordinate << std::endl;
}

//Destructor 
linkedListDatabase::~linkedListDatabase()
{
	cityRecordNode* iteratorNode; //To traverse the list
	cityRecordNode* nextNode;		// To point to the next node

	//Position iteratorNode at head
	iteratorNode = head;

	//While iteratorNode is not at the end of the list
	while (iteratorNode != nullptr)
	{
		//Save the next node
		nextNode = iteratorNode->next;
		//Delete the current Node
		delete iteratorNode;
		//Assign the next node to be deleted
		iteratorNode = nextNode;
	}
}