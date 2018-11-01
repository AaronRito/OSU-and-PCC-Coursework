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
	data currData;
	char name[100];
	char pccId[10];
	float gpa;

	//initialize the queue with the records in the file
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

		//enter current data in the queue
		if(!enqueue(currData))
		{
			cerr << "Queue is full!" << endl;
			exit(1);
		}

		//start reading in next record 
		in.get(name, 100, ';');
	}
	in.close ();
}

bool queue::enqueue(const data& aData)
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

bool queue::dequeue (data& aData)
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

bool queue::peek (data& aData)const
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
	if(!out)
	{
		cerr << "fail to open " << fileName << " for output!" << endl;
		exit(1);
	}

	int i;
	char name[100];
	char pccId[100];
	for(i=front; i<size; i=(i+1)%DEFAULT_CAPACITY)
	{
		//we can use << on data object because we overload << in the data class
		items[i] .getName (name);
		items[i] .getPccId (pccId);
		out << name << ';' << pccId << ';' << items[i].getGpa () << '\n';
	}

	out.close ();
}