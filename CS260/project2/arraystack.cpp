#include "arraystack.h"
#include "data.h"
#include "myutil.h"
#include <fstream>

/*********************
private:
	data * items;
	int capacity;
	int top;
*********************/

stack::stack():capacity(DEFAULT_CAPACITY), top(-1)
{
	items = new Houses[capacity];
}

stack::stack(char * fileName):capacity(DEFAULT_CAPACITY), top(-1)
{
	ifstream in;
	Houses currHouses;
	char		address[MAX_CHAR], SqFoot[MAX_CHAR], Beds[MAX_CHAR], Bath[MAX_CHAR], Feature[MAX_CHAR];

	//alloate memory for the stack
	items = new Houses[capacity];

	//initialize the stack with the records in the file
	in.open(fileName);
	if(!in)
	{
		cerr << "fail to open " << fileName << " for input!" << endl;
		exit(1);
	}

	in.get(address, 100, ';');
	while (!in.eof())
	{
		in.get(); //remove the ';'
		in.get(SqFoot, MAX_CHAR, ';');
		in.get();
		in.get(Beds, MAX_CHAR, ';');
		in.get();
		in.get(Bath, MAX_CHAR, ';');
		in.get();
		in.get(Feature, MAX_CHAR);
		in.ignore(MAX_CHAR, '\n');
		//copy the Houses
		currHouses.setAddress(address);
		currHouses.setSqfoot(SqFoot);
		currHouses.setBeds(Beds);
		currHouses.setBath(Bath);
		currHouses.setFeature(Feature);
		push(currHouses);
		in.get(address, MAX_CHAR, ';');
	}
	in.close();
}

stack::stack(const stack& aStack)
{
	capacity = aStack.capacity;
	items = new Houses[capacity];
	top = aStack.top;

	int i;
	for(i=0; i<=aStack.top; i++)
		items[i] = aStack.items[i]; //this is a deep copy because '=' was overloaded in Houses class
}

const stack& stack::operator=(const stack& aStack)
{
	if(this == &aStack)
		return *this;
	else
	{
		//release dynamically allocated memory held by current object
		delete [] items; //the destructor of each Houses object in the array will be invoked

		//make a *this a deep copy of "aStack"
		capacity = aStack.capacity;
		items = new Houses[capacity];
		top = aStack.top;

		int i;
		for(i=0; i<=aStack.top; i++)
			items[i] = aStack.items[i]; //this is a deep copy because '=' was overloaded in Houses class
		return *this;
	}
}

stack::~stack()
{
	delete [] items;
}

bool stack::push(const Houses& aHouses)
{
	//check if there is still space in the array
	if(top+1 == capacity)
	{
		//create a bigger array and copy data over
		expandArray();
	}
	
	//add on top 
	top++;
	items[top] = aHouses;
	return true;
}

void stack::expandArray ()
{
	Houses * temp;
	int i;

	//create a bigger array and copy elements over
	capacity = capacity + 10;
	temp = new Houses[capacity];
	for(i=0; i<=top; i++)
		temp[i] = items[i];

	//deallocate the existing array
	delete [] items;
	items = temp;
}

bool stack::pop (Houses& aHouses)
{
	//empty stack, has nothing to pop
	if(isEmpty())
		return false;
	else
	{
		aHouses = items[top];
		top--;
		return true;
	}
}

bool stack::isEmpty () const
{
	return top<0;
}

bool stack::peek (Houses& aHouses)const
{
	if(isEmpty())
		return false;
	else
	{
		aHouses = items[top];
		return true;
	}
}

void stack::display () const
{
	int i;

	cout << "Data in the stack: " << endl << endl;
	for(i=0; i<=top; i++)
	{
		//we can use << on data object because we overload << in the data class
		cout << '\t' << items[i] << endl;
	}
}

void stack::writeOut(char * fileName)
{
	ofstream out;

	out.open(fileName);
	if (!out)
	{
		cerr << "fail to open " << fileName << " for output!" << endl;
		exit(1);
	}

	int i;
	char Address[MAX_CHAR];
	char SqFoot[MAX_CHAR];
	char Beds[MAX_CHAR];
	char Bath[MAX_CHAR];
	char Feature[MAX_CHAR];
	for(i=0; i<=top; i++)
	{
		//we can use << on data object because we overload << in the data class
		items[i] .getAddress (Address);
		items[i] .getSqfoot (SqFoot);
		items[i] .getBeds(Beds);
		items[i] .getBath(Bath);
		items[i] .getFeature(Feature);
		out << Address << ';' << SqFoot << ';' << Beds << ';' << Bath << ';' << Feature <<'\n';
	}

	out.close ();
}