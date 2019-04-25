// ListManipulations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#define GARAGE_TXT "D:\\My projects\\Labs\\CPP\\ListManipulations\\Debug\\data\\garage.txt"
#define ROAD_TXT "D:\\My projects\\Labs\\CPP\\ListManipulations\\Debug\\data\\road.txt"


int main()
{
	/*
		LOAD DATA FROM FILES
	*/

	// Retrive data about buses in the garage from the first file in memory
	dllnode* garage = retrive_from_file(GARAGE_TXT);
	if (!garage)
	{
		std::cout << "Couldn't load data into memory!\n";
		return 1;
	}


	// Retrive data about buses outside the garage from the second file in memory
	dllnode* road = retrive_from_file(ROAD_TXT);
	if (!road)
	{
		std::cout << "Couldn't load data into memory!\n";
		return 2;
	}


	/*
		MANIPULATION WITH THE LISTS
	*/


	BUS bus;
	unsigned short lisence_plate;
	std::string name = " ";
	std::string surname = " ";
	unsigned short route;
	
	char command;
	bool exit = false;

	while (!exit)
	{
		std::cout << "BusTracking:>";
		std::cin >> command;

		switch (command)
		{
			case 'i':	// a bus enters the garage
				
				std::cin >> lisence_plate;

				bus = find(road, lisence_plate);

				if (bus.drivers_name == "")
				{
					std::cout << "There is no bus with such plates!\n";
				}
				else
				{
					insert(&garage, bus);
				}

				delete_element(&road, lisence_plate);

				break;

			case 'o':	// a bus leaves the garave
				
				std::cin >> lisence_plate;
					
				bus = find(garage, lisence_plate);
				
				if (bus.drivers_name == "")
				{
					std::cout << "There is no bus with such plates!\n";
				}
				else
				{
					insert(&road, bus);
				}

				delete_element(&garage, lisence_plate);
				break;

			case 'n':

				std::cin >> lisence_plate;
				std::cin >> name;
				std::cin >> surname;
				std::cin >> route;

				bus = BUS(lisence_plate, name, surname, route);
				insert(&garage, bus);

				break;


			case 's':	// show info about buses locations

				std::cout << "GARAGE:\n";
				print_info(garage);

				std::cout << "ROAD:\n";
				print_info(road);
				break;

			case 'd':	// delete all data
				
				std::cin >> lisence_plate;
				if (delete_element(&road, lisence_plate))
				{
				}
				else if (delete_element(&garage, lisence_plate))
				{
				}
				else
				{
					std::cout << "There is no bus with such plates!\n";
				}

;
				break;

			case 'h':	// help -- information about all of the commands
				std::cout	<< "i LICENCE_PLATE\n"
							<< "----a bus has entered the garage\n";
				std::cout	<< "o LICENCE_PLATE\n"
							<< "----a bus has left the garage\n";
				std::cout	<< "n LICENCE_PLATE DRIVER_NAME DRIVER_SURNAME ROUTE\n"
							<< "----add a new bus to the garage\n";
				std::cout	<< "d LICENCE_PLATE DRIVER_NAME DRIVER_SURNAME ROUTE\n"
							<< "----add a new bus to the garage\n";
				std::cout	<< "s\n"
							<< "----to show information about buses in garage and on the road\n";
				std::cout	<< "e\n"
							<< "----exit the program\n";
				break;

			case 'e':	// exit
				exit = true;
				break;

			default:
				std::cout << "Invalid command! Type 'h' for help." << std::endl;
				break;
		}
	}


	/*
		SAVE DATA TO FILES
	*/

	save_to_file(garage, GARAGE_TXT);
	save_to_file(road, ROAD_TXT);


	delete_dllist(garage);
	delete_dllist(road);
	return 0;
}