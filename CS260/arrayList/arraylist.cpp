#include "arraylist.h"
#include "data.h"
#include <iostream>
#include <fstream>
using namespace std;

/************************
private:
	data * dArray;
	int capacity;
	int size;
	static const int DEFAULT_CAPACITY = 10;
************************/
list::list() : capacity(DEFAULT_CAPACITY), size(0)
{
	dArray = new data[capacity];
}

list::list(char * fileName) : capacity(DEFAULT_CAPACITY), size(0)
{
	ifstream in;
	data currData;
	char name[100];
	char pccId[10];
	float gpa;

	//alloate memory for the list
	dArray = new data[capacity];

	//initialize the list with the records in the file
	in.open(fileName);
	if(!in)
	{
		cerr << "fail to open " << fileName << " for input!" << endl;
		exit(1);
	}

	in.get(name, 100, ';');
	while(!in.eof())
	{
		//read in the attributes of current record
		in.ignore(100, ';');
		in.get(pccId, 10, ';');
		in.ignore(100, ';');
		in >> gpa;
		in.ignore(100, '\n');

		//populate current data 
		currData.setName (name);
		currData.setPccId (pccId);
		currData.setGpa (gpa);

		//add current data to the list
		insert(currData);

		//start reading in next record 
		in.get(name, 100, ';');
	}
	in.close ();
}

list::list(const list& aList)
{
	capacity = aList.capacity;
	dArray = new data[capacity];
	size = aList.size;

	int i;
	for(i=0; i<aList.size; i++)
		dArray[i] = aList.dArray[i]; //this is a deep copy because '=' was overloaded in data class
}

const list& list::operator= (const list& aList)
{
	if(this == &aList)
		return *this;
	else
	{
		//release dynamically allocated memory held by current object
		delete [] dArray; //the destructor of each data object in the array will be invoked

		//make a *this a deep copy of "aList"
		capacity = aList.capacity;
		dArray = new data[capacity];
		size = aList.size;

		int i;
		for(i=0; i<aList.size; i++)
			dArray[i] = aList.dArray[i]; //this is a deep copy because '=' was overloaded in data class
		return *this;
	}
}

list::~list()
{
	//the destructor of each data object in the array will be invoked before the array will be released
	delete [] dArray; 
}

bool list::insert (const data& aData)
{
	int i;

	//check if there is still space in the array
	if(size == capacity)
	{
		//create a bigger array and copy data over
		expandArray();
	}

	//we can use '<' to compare because we overloaded '<' in data class
	for(i=0; i<size && dArray[i]<aData; i++)	
		;

	//the data already exists
	if(i<size && dArray[i] == aData)
		return false;
	//insert the data here
	else
	{
		//shift array to make space for the data
		int j;
		for(j=size-1; j>=i; j--)
			dArray[j+1] = dArray[j];
		dArray[i] = aData; 
		size++;
		return true;
	}
}

void list::expandArray ()
{
	data * temp;
	int i;

	//create a bigger array and copy elements over
	capacity = capacity + 10;
	temp = new data[capacity];
	for(i=0; i<size; i++)
		temp[i] = dArray[i];

	//deallocate the existing array
	delete [] dArray;
	dArray = temp;
}

bool list::remove (char * key)
{
	int i;
	char id[100];

	//search for the data to be removed
	for(i=0; i<size; i++)
	{
		dArray[i].getPccId (id);
		if(strcmp(key, id) == 0)
		{
			//remove the data
			int j;
			for(j=i; j<size-1; j++)
			{
				dArray[j] = dArray[j+1];
			}
			size--;
			return true;
		}
	}
	//data is not in the list
	return false;
}

bool list::retrieve (char * key, data & aData)const
{
	//search for the data to be retrieved
	int i;
	char id[100];
	for(i=0; i<size; i++)
	{
		dArray[i].getPccId (id);
		if(strcmp(key, id) == 0)
		{
			aData = dArray[i];
			return true;
		}
	}

	//data is not in the list
	return false;
}

void list::display (void)const
{
	int i;

	cout << "Data in the list: " << endl << endl;
	for(i=0; i<size; i++)
	{
		//we can use << on data object because we overload << in the data class
		cout << '\t' << dArray[i] << endl;
	}
}

int list::getSize (void) const
{
	return size;
}

void list::writeOut(char * fileName)
{
	ofstream out;

	out.open(fileName);
	if(!out)
	{
		cerr << "fail to open " << fileName << " for output!" << endl;
		exit(1);
	}

	int i;
	char name[100];
	char pccId[100];
	for(i=0; i<size; i++)
	{
		//we can use << on data object because we overload << in the data class
		dArray[i] .getName (name);
		dArray[i] .getPccId (pccId);
		out << name << ';' << pccId << ';' << dArray[i].getGpa () << '\n';
	}

	out.close ();
}







	


