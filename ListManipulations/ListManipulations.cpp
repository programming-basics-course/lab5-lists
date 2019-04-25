// ListManipulations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#define GARAGE_TXT "garage.txt"
#define ROAD_TXT "road.txt"


int main()
{
	/*
		LOAD DATA FROM FILES
	*/


	// Pathes to the files with data about buses 
	std::string garage_file_address = "D://My projects//Labs//CPP//ListManipulations//Debug//garage.txt";
	std::string road_file_address = "D://My projects//Labs//CPP//ListManipulations//Debug//road.txt";


	// Retrive data about buses in the garage from the first file in memory
	dllnode* garage = retrive_from_file(garage_file_address);
	if (!garage)
	{
		std::cout << "Couldn't load data into memory!\n";
		return 1;
	}
	print_info(garage);

	// Retrive data about buses outside the garage from the second file in memory
	dllnode* road = retrive_from_file(road_file_address);
	if (!road)
	{
		std::cout << "Couldn't load data into memory!\n";
		return 2;
	}
	print_info(road);

	/*
		MANIPULATION WITH THE LISTS
	*/

	insert(&road, BUS(1789, "ivan", "rus", 7));
	

	/*
		SAVE DATA TO FILES
	*/

	save_to_file(garage, garage_file_address);
	save_to_file(road, road_file_address);


	delete_dllist(garage);
	delete_dllist(road);
	return 0;
}