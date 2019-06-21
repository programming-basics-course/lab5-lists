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
dllnode* create(BUS bus)
{
	dllnode* dllist = new dllnode;

	dllist->bus = bus;
	dllist->prev = NULL;
	dllist->next = NULL;

	return dllist;
}


// Search throught a linked list to find an element
BUS find(dllnode* head, unsigned short int license_plate)
{
	dllnode* trav = head;

	while (trav)
	{
		if (trav->bus.license_plate == license_plate)
			return trav->bus;

		trav = trav->next;
	}

	return BUS();
}


// Insert a new node into the linked list
void insert(dllnode** head, BUS bus)
{
	// Check on both NULLs ??

	if (*head == NULL)
	{
		*head = create(bus);
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
bool delete_element(dllnode** head, unsigned short int licence_plate)
{
	dllnode* trav = new dllnode;
	trav = *head;

	while (trav)
	{

		if (trav->bus.license_plate == licence_plate)
		{
			// The element to delete is the first one
			if (trav == *head)
			{
				if (trav->next == NULL)
				{
					delete trav;
					*head = NULL;
					return true;
				}

				trav->next->prev = NULL;
				*head = trav->next;
				delete trav;
				return true;
			}

			// The element to delte it the last one
			if (trav->next == NULL)
			{
				trav->prev->next = NULL;
				delete trav;
				return true;
			}


			trav->prev->next = trav->next;
			trav->next->prev = trav->prev;

			//delete trav->bus;
			delete trav;
			return true;
		}

		trav = trav->next;
	}

	return false;

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

	if (!head)
	{
		std::cout << "The list is empty.\n";
	}

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
	dllnode* head = NULL;

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

	dllnode* trav = head;

	while (trav)
	{
		file << trav->bus.license_plate << "\t\t";
		file << trav->bus.drivers_name << " ";
		file << trav->bus.drivers_surname << "\t\t";
		file << trav->bus.route;

		if (trav->next != NULL)
			file << "\n";

		trav = trav->next;

	}

	file.close();
}
