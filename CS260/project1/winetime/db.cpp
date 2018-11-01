#define _CRT_SECURE_NO_WARNINGS
#include "db.h"
#include "winery.h"
#include "myutil.h"
#include <fstream>
#include <iostream>
#include <iomanip>

//constructor
list::list()
{
	head_name = nullptr;
	head_rank = nullptr;
	size = 0;
}
//destructor
list::~list()
{
	Node * curr = head_name;
	while (curr)							//loop through deleteing each node until curr = null
	{
		head_name = curr->next_by_name;		//assign the head to the next item in the list	
		delete curr;
		curr = head_name;					//update the pointer
	}
}
// add an item to the linked list
void list::addToDB(const winery& s)
{
	Node * dataNode = new Node; //create a new node to host the list
	dataNode->list = s; // assign the node to the first item in the list
	dataNode->next_by_name = nullptr;
	dataNode->next_by_rank = nullptr;

	// Add the pointers to teh node in the correct order
	Node * prev = nullptr;
	Node * curr = head_name;
	Node * prev2 = nullptr;
	Node * curr2 = head_rank;
	char currName[MAX_CHAR];
	char name[MAX_CHAR];
	char currRank[MAX_CHAR];
	char rank[MAX_CHAR];

	s.getName(name);
	s.getRank(rank);
	while (curr)		//while curr is not null, insert the item in the correct spot using the name
	{		
			 curr->list.getName(currName);
			 if (strcmp(name, currName) > 0)
			 {
				 prev=curr;
				 curr=curr->next_by_name;
			 }			
			 else
				 break;
	}
	dataNode->next_by_name = curr; // update the next pointer

	if(!prev) 
	{			
		dataNode->next_by_name = head_name; // if first item in list, update the head.
		head_name = dataNode;
	}
	else
	{
		prev->next_by_name = dataNode;	//otherwise update the prev pointer
	}

	while (curr2)		//Do the same thing with the rank pointer
	{
		curr2->list.getRank(currRank);
		if (strcmp(rank, currRank) < 0)
		{
			prev2 = curr2;
			curr2 = curr2->next_by_rank;
		}
		else
			break;
	}
	dataNode->next_by_rank = curr2;
	if (!prev2)
	{
		dataNode->next_by_rank = head_rank;
		head_rank = dataNode;
	}
	else
	{
		prev2->next_by_rank = dataNode;
	}
	size++; //increase the list size for logic
}
// get from copy
void list::get(int index, winery& s)
{
	Node * curr = head_name;
	int counter = 0;
	while (counter < index)
	{
		curr = curr->next_by_name;
		counter++;
	}
	s = curr->list;
}
// list the contents in memory by name
void list::listName() const
{
	char	name[MAX_CHAR], location[MAX_CHAR], date[MAX_CHAR], rank[MAX_CHAR], acre[MAX_CHAR];
	int listPos = 0;
	Node * curr;
	if (size < 1)
	{
		cout << "No wineries in memory, press (a) in the main menu to add a location." << endl; 
	}
	else
	{	
		cout << std::left << setw(15) << "Winery" << setw(15) << "Location" << setw(12) << "Founded" << setw(8) << "Rank" << setw(8) << "Acreage" << endl;
		cout << "______________________________________________________________________________" << endl;
		for (curr = head_name; curr!=nullptr; curr=curr->next_by_name)
		{
			listPos++;
			curr->list.getName(name);
			curr->list.getlocation(location);
			curr->list.getDate(date);
			curr->list.getRank(rank);
			curr->list.getAcre(acre);
			cout << std::left << listPos << "." << setw(15) << name << setw(15) << location << setw(12) << date << setw(8) << rank << setw(8) << acre << endl;
		}
	}
}
//list by rank
void list::listRank() const
{
	char	name[MAX_CHAR], location[MAX_CHAR], date[MAX_CHAR], rank[MAX_CHAR], acre[MAX_CHAR];
	int listPos = 0;
	Node * curr;
	if (size < 1)
	{
		cout << "No wineries in memory, press (a) to add a location." << endl;
	}
	else
	{
		cout << setw(8) << "Rank" << setw(15) << "Winery" << setw(15) << "Location" << setw(12) << "Founded" << setw(8) << "Acreage" << endl;	
		cout << "______________________________________________________________________________" << endl;
		for (curr = head_rank; curr != nullptr; curr = curr->next_by_rank)
		{
			listPos++;
			curr->list.getName(name);
			curr->list.getlocation(location);
			curr->list.getDate(date);
			curr->list.getRank(rank);
			curr->list.getAcre(acre);
			cout << setw(8) << rank << setw(15) << name <<  setw(15)<< location << setw(12) << date << setw(8) << acre << endl;
		}
	}
}
// This function searches for a class name.
bool list::searchDB(const char key[]) 
{
	bool	found = false;
	Node *	curr;
	char	name[MAX_CHAR];
	for (curr=head_name; curr; curr= curr->next_by_name)
	{
		curr->list.getName(name);
		if (strcmp(key, name) == 0)
		{
			curr->list.print("Match found: ");
			found = true;		
		}
	}
	return found;
}
//save the list when the program closes.
void list::saveDB(const char fileName[]) const
{
	ofstream	out;
	char		name[MAX_CHAR], location[MAX_CHAR], date[MAX_CHAR], rank[MAX_CHAR], acre[MAX_CHAR];
	out.open(fileName);
	if (!out)
	{
		cerr << "Fail to open " << fileName << " for writing!" << endl;
		exit(1);
	}

	Node * curr;
	for (curr=head_name; curr; curr=curr->next_by_name)
	{
		curr->list.getName(name);
		curr->list.getlocation(location);
		curr->list.getDate(date);
		curr->list.getRank(rank);
		curr->list.getAcre(acre);
		out << name << ';' << location << ';' << date << ';' << rank << ';' << acre << endl;
	}
	out.close();	
}
//load the list when the program opens
void list::loadDB(const char fileName[])
{
	ifstream	in;
	char		name[MAX_CHAR], location[MAX_CHAR], date[MAX_CHAR], rank[MAX_CHAR], acre[MAX_CHAR];
	winery		winery;

	in.open(fileName);
	if (!in)
	{
		cerr << "Fail to open " << fileName << " for reading!" << endl;
		exit(1);
	}
	in.get(name, MAX_CHAR, ';');
	while (!in.eof())
	{		
		in.get(); //remove the ';'
		in.get(location, MAX_CHAR, ';');
		in.get();
		in.get(date, MAX_CHAR, ';');
		in.get();
		in.get(rank, MAX_CHAR, ';');
		in.get();
		in.get(acre, MAX_CHAR);
		in.ignore(MAX_CHAR, '\n');
		//copy the data
		winery.setName(name);
		winery.setlocation(location);
		winery.setDate(date);
		winery.setRank(rank);
		winery.setAcre(acre);
		addToDB(winery);
		in.get(name, MAX_CHAR, ';'); 
	}
	in.close();
}
//remove node
bool list::remove(const char key[])
{
	// just like in add, 2 sets of pointers to manage the list 
	bool	found = false; //return true if a match was found
	Node *	curr;
	Node * prev = nullptr;
	Node *	curr2;
	Node * prev2 = nullptr;
	char	name[MAX_CHAR];

	for (curr = head_name; curr != nullptr; curr = curr->next_by_name) //iterate through the list
	{
		curr->list.getName(name);
		if (strcmp(key, name) == 0)
		{
			if (!prev) //if the item being deleted it the first item in the list, update the head.
			{
				head_name = curr->next_by_name;	
			}
			else	//otherwise update the next pointer to skip the deleted enrty
			{
				prev->next_by_name = curr->next_by_name;
			}
			found = true; //confirm the strcmp match to delete, otherwise leave the function
			break;
		}
		prev = curr;
	}
	if (found)		//if the match is confirmed, update the rank pointers the same way
	{	
		prev2 = nullptr;
		for (curr2 = head_rank; curr2 != nullptr; curr2 = curr2->next_by_rank)
		{
			curr2->list.getName(name);
			if (strcmp(key, name) == 0)
			{
				if (!prev2)
				{
					head_rank = curr2->next_by_rank;
				}
				else
				{
					prev2->next_by_rank = curr2->next_by_rank;
				}
			}
			prev2 = curr2;
		}
		delete(curr); //remove the item now that the pointers are updated
		size--;
	}
	return found;
}

  
    