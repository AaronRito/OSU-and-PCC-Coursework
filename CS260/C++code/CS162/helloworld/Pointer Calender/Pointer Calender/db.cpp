#define _CRT_SECURE_NO_WARNINGS
#include "db.h"
#include "course.h"
#include "myutil.h"
#include <fstream>

TaskList::TaskList()
{
	currCapacity = MAX_CAP;
	list = new Course[currCapacity];
	size = 0;
}
TaskList::~TaskList()
{
	delete[] list;
}
// add an item to the database
void TaskList::addToDB(const Course& s)
{
	if (size == currCapacity)
	{
		grow();
	}
	list[size] = s;
	size++;
}
void TaskList::grow()
{
	currCapacity *= 2;
	Course * temp;
	temp = new Course[currCapacity];
	int index;
	for (index = 0; index < size; index++)
	{
		temp[index] = list[index];
	}
	delete[] list;
	list = temp;
}
// list the contents in memory
void TaskList::listDB() const
{
	if (size < 1){
		cout << "No tasks in memory, press (a) to add a task." << endl; 
	}
	else{
	char name[MAX_CHAR];
	char task[MAX_CHAR];
	char date[MAX_CHAR];
	int index;
	int listPos = 0;
	for (index = 0; index < size; index++){

		listPos = index +1;
		list[index].getName(name);
		list[index].getTask(task);
		list[index].getDate(date);
		cout << listPos << ". " << name << '\t' << task << '\t' << date << endl;
		
	}
  }
}
// This function searches for a class name.
bool TaskList::searchDB(const char key[]) 
{
	bool found = false;
	char name[MAX_CHAR];

	for (int i = 0; i < size; i++){

		list[i].getName(name);
		if (strcmp(key, name) == 0){
	
			list[i].print("Match found: ");
			found = true;
		}
	}
return found;
}
//save the data when the program closes.
void TaskList::saveDB(const char fileName[]) const
{
	ofstream	out;
	char	name[MAX_CHAR];
	char	task[MAX_CHAR];
	char	date[MAX_CHAR];
	out.open(fileName);
	if (!out){

		cerr << "Fail to open " << fileName << " for writing!" << endl;
		exit(1);
	}

	int index;
	for (index = 0; index < size; index++){

		list[index].getName(name);
		list[index].getTask(task);
		list[index].getDate(date);
		out << name << ';' << task << ';' << date << endl;
		
	}
	out.close();
}
//load the data when the program opens
void TaskList::loadDB(const char fileName[])
{
	ifstream	in;
	char		name[MAX_CHAR], task[MAX_CHAR], date[MAX_CHAR];
	Course		course;

	in.open(fileName);
	if (!in){
		cerr << "Fail to open " << fileName << " for reading!" << endl;
		exit(1);
	}
	in.get(name, MAX_CHAR, ';'); 
	while (!in.eof()){

		in.get(); //remove the ';'
		in.get(task, MAX_CHAR, ';');
		in.get();
		in.get(date, MAX_CHAR);
		in.ignore(MAX_CHAR, '\n');
		
		course.setName(name);
		course.setTask(task);
		course.setDate(date);
		addToDB(course);
		in.get(name, MAX_CHAR, ';'); 
	}
	in.close();
}

bool TaskList::delIt(const int pos)
{
	bool  found = false;
	int	index;
	int		j;
    index = pos - 1;

	for (j=index;j < size; j++){
		
		list[j] = list[j+1];
		found = true;
	}
	if (pos <= size){
		size --;}
	else{
		cout << "Invalid entry." << endl;
	}
	return found;
}
