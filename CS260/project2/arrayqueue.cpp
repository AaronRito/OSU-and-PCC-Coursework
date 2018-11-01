#include "arrayqueue.h"
#include <fstream>


/*********************
private:
	data items[DEFAULT_CAPACITY];
	int front;
	int rear;
	int size;
*********************/

queue::queue():front(0), rear(0), size(0)
{
}

queue::queue(char * fileName):front(0), rear(0), size(0)
{
	ifstream in;
	Houses currHouses;
	char		address[MAX_CHAR], SqFoot[MAX_CHAR], Beds[MAX_CHAR], Bath[MAX_CHAR], Feature[MAX_CHAR];

	//initialize the queue with the records in the file
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

		//enter current data in the queue
		if(!enqueue(currHouses))
		{
			cerr << "Queue is full!" << endl;
			exit(1);
		}

		//start reading in next record 
		in.get(address, 100, ';');
	}
	in.close ();
}

bool queue::enqueue(const Houses& aData)
{
	//check if there is still space in the array
	if(size == DEFAULT_CAPACITY)
		return false;
	
	//add to the rear 	
	items[rear] = aData;
	rear = (rear + 1) % DEFAULT_CAPACITY;
	size++;
	return true;
}

bool queue::dequeue (Houses& aData)
{
	//empty stack, has nothing to pop
	if(isEmpty())
		return false;
	else
	{
		aData = items[front];
		front = (front + 1) % DEFAULT_CAPACITY;
		size--;
		return true;
	}
}

bool queue::isEmpty () const
{
	return size==0;
}

bool queue::peek (Houses& aData)const
{
	if(isEmpty())
		return false;
	else
	{
		aData = items[front];
		return true;
	}
}

void queue::display () const
{
	int i;

	cout << "Data in the queue: " << endl << endl;
	for(i=front; i<size; i=(i+1)%DEFAULT_CAPACITY)
	{
		//we can use << on data object because we overload << in the data class
		cout << '\t' << items[i] << endl;
	}
}

void queue::writeOut(char * fileName)
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
	for (i = front; i<size; i = (i + 1) % DEFAULT_CAPACITY)
	{
		//we can use << on data object because we overload << in the data class
		items[i].getAddress(Address);
		items[i].getSqfoot(SqFoot);
		items[i].getBeds(Beds);
		items[i].getBath(Bath);
		items[i].getFeature(Feature);
		out << Address << ';' << SqFoot << ';' << Beds << ';' << Bath << ';' << Feature << '\n';
	}

	out.close();
}
