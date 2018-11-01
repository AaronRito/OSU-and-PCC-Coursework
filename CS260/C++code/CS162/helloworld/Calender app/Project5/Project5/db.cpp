#define _CRT_SECURE_NO_WARNINGS
#include "db.h"
#include <fstream>
// add an item to the database
void addToDB(const Course& s, Course list[], int& size)
{

	list[size] = s;
	size++;
}
// list the contents in memory
void listDB(const Course list[], int size)
{
	if (size < 1){
		cout << "No tasks in memory, press (a) to add a task." << endl; 
	}
	else{
	
	int index;
	for (index = 0; index < size; index++)
	{
		cout << list[index].name << '\t' << list[index].task << '\t' << list[index].date << endl;
		}
	}
}
// This function searches for a class name.
bool searchDB(const char key[], const Course list[], int size, int (matches)[MAX_CAP], int& matchesSize)
{
	bool	found = false;
	int		index = 0;
	
	matchesSize= 0;
	for (index = 0; index < size; index++)
	{
		if (strcmp(key, list[index].name) == 0)
		{
			matches[matchesSize] = index;
			matchesSize++;	
			found = true;
		}			
	}
	return found;
}
// This function is called if multiple search results are returned during the delete process. It lets the user choose which specific task to remove.
bool searchTask(const char key[], const Course list[], int size, const char className[], int (matches)[MAX_CAP], int& matchesSize)
{
	bool	found = false;
	int		index;
	
	matchesSize= 0;
	for (index = 0; index < size; index++)
	{
		if ((strcmp(key, list[index].task) == 0) && (strcmp(className, list[index].name) == 0))
		{
			matches[matchesSize] = index;
			matchesSize++;
			found = true;
		}			
	}
	return found;
}
//save the data when the program closes.
void saveDB(const char fileName[], const Course list[], int size)
{
	ofstream	out;

	out.open(fileName);
	if (!out)
	{
		cerr << "Fail to open " << fileName << " for writing!" << endl;
		exit(1);
	}

	int index;
	for (index = 0; index < size; index++)
	{
		out << list[index].name << ';' << list[index].task << ';' << list[index].date << endl;
	}

	out.close();
}
//load the data when the program opens
void loadDB(const char fileName[], Course list[], int& size)
{
	ifstream	in;
	char		name[MAX_CHAR], task[MAX_CHAR], date[MAX_CHAR];
	Course		course;

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
		in.get(task, MAX_CHAR, ';');
		in.get();
		in.get(date, MAX_CHAR);
		in.ignore(MAX_CHAR, '\n');
		
		strcpy(course.name, name);
		strcpy(course.task, task);
		strcpy(course.date, date);
		addToDB(course, list, size);
		in.get(name, MAX_CHAR, ';'); 
		
	}
	in.close();
}
