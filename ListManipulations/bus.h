// Doubly-lisked List for BUS struct
#include "pch.h"

#ifndef BUS_H
#define BUS_H

struct BUS
{
	unsigned short license_plate;
	std::string drivers_name;
	std::string drivers_surname;
	unsigned short route;

	BUS();
	BUS(unsigned short, std::string, std::string, unsigned short);
	BUS(std::fstream &file);

	void print_info();
};


struct dllnode
{
	BUS bus = BUS();
	struct dllnode* prev;
	struct dllnode* next;
};


// Create a doubly-linked list
dllnode* create(BUS bus);

// Search throught a linked list to find an element
BUS find(dllnode*, unsigned short int);

// Insert a new node into the linked list
void insert(dllnode**, BUS);

// Delete a single element from the list
bool delete_element(dllnode**, unsigned short int);

// Delete an entire linked list
void delete_dllist(dllnode*);

// Print infomation about all elements of the list
void print_info(dllnode*);

// Retrives data from a file
dllnode* retrive_from_file(std::string address);

// Saves contents of the list to the file
void save_to_file(dllnode*, std::string);

#endif // BUS_H

