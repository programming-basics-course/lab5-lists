#include "pch.h"


BUS::BUS()
{
	license_plate = 0;
	drivers_name = "";
	drivers_surname = "";
	route = 0;
}

BUS::BUS(unsigned short plate, std::string name, std::string surname, unsigned short route)
{
	license_plate = plate;
	drivers_name = name;
	drivers_surname = surname;
	this->route = route;
}

BUS::BUS(std::fstream &file)
{
	file >> license_plate;
	file >> drivers_name;
	file >> drivers_surname;
	file >> route;
}

void BUS::print_info()
{
	std::cout << "License plate: " << license_plate << std::endl;
	std::cout << "Driver       : " << drivers_name << " " << drivers_surname << std::endl;
	std::cout << "Route number : " << route << std::endl;
}






// Create a doubly-linked list
dllnode* create()
{
	dllnode* dllist = new dllnode;

	dllist->bus = BUS();
	dllist->prev = NULL;
	dllist->next = NULL;

	return dllist;
}


// Search throught a linked list to find an element
BUS find(dllnode* head, unsigned short int license_plate)
{
	dllnode* trav = new dllnode;
	trav = head;

	bool there_is = false;

	while (trav)
	{
		if (trav->bus.license_plate == license_plate)
			return trav->bus;

		trav = trav->next;
	}

	std::cout << "Sorry, there is no bus with this number is this list.\n";
	return BUS();
}


// Insert a new node into the linked list
void insert(dllnode** head, BUS bus)
{
	// Check on both NULLs ??

	// Empty list case
	if ((*head)->bus.drivers_name == "")
	{
		(*head)->bus = bus;
		return;
	}

	dllnode* new_bus = new dllnode;
	new_bus->bus = bus;
	new_bus->prev = NULL;
	new_bus->next = (*head);

	(*head)->prev = new_bus;

	(*head) = new_bus;
}


// Delete a single element from the list
void delele_element(dllnode* head, unsigned short int licence_plate)
{
	dllnode* trav = new dllnode;
	trav = head;

	while (trav)
	{
		if (trav->bus.license_plate == licence_plate)
		{

			trav->prev->next = trav->next;
			trav->next->prev = trav->prev;

			//delete trav->bus;
			delete trav;
			return;
		}

		trav = trav->next;
	}

	std::cout << "Couldn't find the bus to delete from the list" << std::endl;

}


// Delete an entire linked list
void delete_dllist(dllnode* head)
{
	// "Delete the rest of the list and return"
	if (head->next)
		delete_dllist(head->next);

	//delete head->bus;
	delete head;
}


// Print infomation about all elements of the list
void print_info(dllnode* head)
{
	std::cout << "INFORMARION ABOUT THE LIST" << std::endl << std::endl;

	while (head)
	{
		head->bus.print_info();
		std::cout << std::endl;
		head = head->next;
	}

}


// Retrives data from a file
dllnode* retrive_from_file(std::string address)
{

	std::fstream file(address);
	if (!file.is_open())
	{
		std::cout << "Could not open file.";
		file.close();
		return NULL;
	}

	// Create an empty list
	dllnode* head = create();

	while (file.peek() != EOF)
	{
		insert(&head, BUS(file));
	}
	file.close();


	return head;
}

// Saves contents of the list to the file
void save_to_file(dllnode* head, std::string address)
{
	// Open the file and delete its contents
	std::fstream file(address);
	if (!file.is_open())
	{
		std::cout << "Couldn't open the file for saving data\n";
		file.close();
		return;
	}

	dllnode* trav = new dllnode;
	trav = head;

	while (trav)
	{
		file << trav->bus.license_plate << "\t\t";
		file << trav->bus.drivers_name << " ";
		file << trav->bus.drivers_surname << "\t\t";
		if (trav->next)
			file << trav->bus.route << "\n";

		trav = trav->next;
	}

	file.close();
}
