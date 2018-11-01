#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <cstring>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

/************************
private:
	node ** table;
	int capacity;
	int size;
	const static int DEFAULT_CAPACITY = 11;
************************/
void hashTable::initializeTable()
{
	capacity = DEFAULT_CAPACITY;
	size = 0;
	table = new node*[capacity];

	//initialize each head of the individual linked list
	int i;
	for(i=0; i<capacity; i++)
		table[i] = NULL;
}

hashTable::hashTable() : capacity(DEFAULT_CAPACITY), size(0)
{
	initializeTable();
}

hashTable::hashTable(char * fileName) 
{
	ifstream in;
	aData currData;
	char symbol[MAX_CHAR], name[MAX_CHAR], ass[MAX_CHAR], date[MAX_CHAR], div[MAX_CHAR];

	initializeTable();

	//initialize the table with the records in the file
	in.open(fileName);
	if(!in)
	{
		cerr << "fail to open " << fileName << " for input!" << endl;
		exit(1);
	}

	in.get(symbol, MAX_CHAR, ';');
	while(!in.eof())
	{
		//read in the attributes of current record
		in.ignore(MAX_CHAR, ';');
		in.get(name, MAX_CHAR, ';');
		in.ignore(MAX_CHAR, ';');
		in.get(ass, MAX_CHAR, ';');
		in.ignore(MAX_CHAR, ';');
		in.get(date, MAX_CHAR, ';');
		in.ignore(MAX_CHAR, ';');
		in >> div;
		in.ignore(MAX_CHAR, '\n');

		//populate current data 
		currData.setSymbol (symbol);
		currData.setName (name);
		currData.setAss (ass);
		currData.setDate(date);
		currData.setDiv(div);

		//add current data to the table
		insert(currData);

		//start reading in next record 
		in.get(symbol, MAX_CHAR, ';');
	}
	in.close ();
}

hashTable::hashTable(const hashTable& aTable):capacity(aTable.capacity), size(aTable.size)
{
	table = new node*[capacity];

	//copy the array of linked list
	int i;	
	for(i=0; i<capacity; i++)
	{
		//copy each linked list in the array
		if (aTable.table[i] == NULL)
			table[i] = NULL;
		else
		{
			//copy the first node in current chain
			table[i] = new node(aTable.table[i]->item);

			//copy the rest of the chain
			node * srcNode = aTable.table[i]->next;
			node * destNode = table[i];
			while(srcNode)
			{
				destNode->next = new node(srcNode->item);
				destNode = destNode->next;
				srcNode = srcNode->next;
			}
			destNode->next = NULL;
		}
	}
}

const hashTable& hashTable::operator= (const hashTable& aTable)
{
	if(this == &aTable)
		return *this;
	else
	{
		//release dynamically allocated memory held by current object
		destroyTable(); 

		//make *this a deep copy of "aTable"
		table = new node*[capacity];
		capacity = aTable.capacity;
		size = aTable.size;

		//copy the array of linked list
		int i;	
		for(i=0; i<capacity; i++)
		{
			//copy each linked list in the array
			if (aTable.table[i] == NULL)
				table[i] = NULL;
			else
			{
				//copy the first node in current chain
				table[i] = new node(aTable.table[i]->item);

				//copy the rest of the chain
				node * srcNode = aTable.table[i]->next;
				node * destNode = table[i];
				while(srcNode)
				{
					destNode->next = new node(srcNode->item);
					destNode = destNode->next;
					srcNode = srcNode->next;
				}
				destNode->next = NULL;
			}
		}		
		return *this;
	}
}

void hashTable::destroyTable ()
{
	//delete each chain
	int i;
	for(i=0; i<capacity; i++)
	{
		node * head = table[i];
		node * curr;
		
			while (head)							//loop through deleteing each node until curr = null
			{
				curr = head->next;	
				delete head;
				head = curr;					//update the pointer
			}
	}

	//delete the array
	delete[] table;

}
hashTable::~hashTable()
{
	destroyTable(); 
}

void hashTable::insert (const aData& MyData)
{
	//calculate the insertion position (the index of the array)
	char key[100];
	char name[MAX_CHAR];
	MyData.getSymbol(key);
	int index = calculateIndex(key);
	node * curr = table[index];
	node * prev = nullptr;
	//create a new node to hold data
	node * newNode = new node(MyData);

	if (table[index])
	{
		while (curr != NULL)		//while curr is not null, insert the item in the correct spot using the name
		{
			curr->item.getSymbol(name);
			if (strcmp(name, key) < 0)
			{
				prev = curr;
				curr = curr->next;
			}
			else
				break;
		}
		newNode->next = curr; // update the next pointer

		if (!prev)
		{
			newNode->next = table[index]; // if first item in list, update the head.
			table[index] = newNode;
		}
		else
		{
			prev->next = newNode;	//otherwise update the prev pointer
		}
	}
	else
	{
		newNode->next = table[index];
		table[index] = newNode;
	}
	size++;
}

bool hashTable::remove (char * key)
{
	//calculate the removal position (the index of the array)
	int index = calculateIndex(key);	

	//search for the data to be removed in the chain (linked list)
	node * curr = table[index];
	node * prev = NULL;
	char name[MAX_CHAR];
	while (curr)
	{
		curr->item.getSymbol (name);
		if(strcmp(key, name) == 0)
		{
			//find match and remove the node
			if(!prev)
				table[index] = curr->next;
			else
				prev->next = curr->next;

			curr->next = NULL;
			delete curr;
			size--;
			return true;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return false;
}
bool hashTable::modify(char * tickerSymbol, char * newNetAssetVal, char * newDate, char * newDateReturn)
{
	aData currData;
	//calculate the retrieval position (the index of the array)
	int index = calculateIndex(tickerSymbol);

	//search for the data in the chain (linked list)
	node * curr = table[index];
	char currenti[MAX_CHAR];
	char name[MAX_CHAR];
	curr->item.getName(name);
	while (curr)
	{
		curr->item.getSymbol(currenti);
		if (strcmp(tickerSymbol, currenti) == 0)
		{
			remove(currenti);
		
			//find match and return the data
			//populate current data 
			currData.setSymbol(tickerSymbol);
			currData.setName(name);
			currData.setAss(newNetAssetVal);
			currData.setDate(newDate);
			currData.setDiv(newDateReturn);

			//add current data to the table
			insert(currData);
			return true;
		}
		else
			curr = curr->next;
	}

	//data is not in the table
	return false;


}
bool hashTable::retrieve (char * key, aData & MyData)const
{
	//calculate the retrieval position (the index of the array)
	int index = calculateIndex(key);

	//search for the data in the chain (linked list)
	node * curr = table[index];
	char name[MAX_CHAR];
	while (curr)
	{
		curr->item.getSymbol (name);
		if(strcmp(key, name) == 0)
		{
			//find match and return the data
			MyData = curr->item;
			return true;
		}
		else
			curr = curr->next;
	}

	//data is not in the table
	return false;
}

void hashTable::display (void)const
{
	int i;
	node * curr;

	cout << "Data in the table: " << endl << endl;
	for(i=0; i<capacity; i++)
	{
		for(curr = table[i]; curr; curr = curr->next)		
			//we can use << on data object because we overload << in the data class
			cout << '\t' << curr->item << endl;
	}
}

int hashTable::getSize (void) const
{
	return size;
}

void hashTable::writeOut(char * fileName)
{
	ofstream out;

	out.open(fileName);
	if(!out)
	{
		cerr << "fail to open " << fileName << " for output!" << endl;
		exit(1);
	}

	int i;
	char symbol[MAX_CHAR], name[MAX_CHAR], ass[MAX_CHAR], date[MAX_CHAR], div[MAX_CHAR];
	node * curr;
	for(i=0; i<capacity; i++)
	{
		for(curr = table[i]; curr; curr = curr->next)		
		{	
			curr->item.getSymbol (symbol);
			curr->item.getName (name);
			curr->item.getAss(ass);
			curr->item.getDate(date);
			curr->item.getDiv(div);
			out << symbol << ';' << name << ';' << ass << ";" << date << ";" <<  div << '\n';
		}
	}
	out.close ();
}

int hashTable::calculateIndex (char * key)const
{
	char * c = key;
	int total = 0;
	while(*c)
	{
		total += *c;
		c++;
	}
	return (total)%capacity;
}
void hashTable::monitor(void)const
{
	int i;
	int collision = 0;
	int entries = 0;
	node * curr;
	cout << "Collision monitor report:" << endl;
	for (i = 0; i < capacity; i++)
	{
		if (table[i] != NULL)
			entries = entries + 1;
		for (curr = table[i]; curr; curr = curr->next)
		{
			collision = collision + 1;
			
		}
		if (collision > 1)
		{
			cout << "Collisions found in chain " << i << ", # of entries in chain = " << collision << endl;
			for (curr = table[i]; curr; curr = curr->next)
				cout << '\t' << curr->item << endl;
			
		}
		collision = 0;
	}
	cout << "Total entries in table = " << getSize() << endl;
	cout << "Total head nodes in array =" << entries << endl;
	cout << "Total unused storage spaces = " << (capacity - entries) << endl;
 }







	


