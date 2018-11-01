#define _CRT_SECURE_NO_WARNINGS
#include "course.h"


Course::Course()
{
	char defaultName[] = "no name";
	name = new char[strlen(defaultName) + 1];
	strcpy(name, defaultName);
	
	char defaultTask[] = "no task";
	task = new char[strlen(defaultTask) + 1];
	strcpy(task, defaultTask);
	
	char defaultDate[] = "no date";
	date = new char[strlen(defaultDate) + 1];
	strcpy(date, defaultDate);
	
}

Course::Course(const char inName[])
{
	name = new char[strlen(inName) + 1];
	strcpy(name, inName);

	
}
Course::~Course()
{
		if (name)
		delete[] name;
		if (task)
		delete[] task;
		if( date)
		delete[] date;
}


void Course::getName(char outName[]) const
{
	strcpy(outName, name);
}

void Course::setName(const char inName[])
{
		if (name!=nullptr)
			delete[] name;
		name = new char[strlen(inName) + 1];
		strcpy(name, inName);
}
void Course::getTask(char outTask[]) const
{
	strcpy(outTask, task);
}

void Course::setTask(const char inTask[])
{
		if (task!=nullptr)
			delete[] task;
		task = new char[strlen(inTask) + 1];
		strcpy(task, inTask);
}

void Course::getDate(char outDate[]) const
{
	strcpy(outDate, date);
}

void Course::setDate(const char inDate[])
{
		if (date!=nullptr)
			delete[] date;
		date = new char[strlen(inDate) + 1];
		strcpy(date, inDate);
}

void Course::print()const
{
	cout << name << '\t' << task << '\t' << date << endl;
}
void Course::print(char label[MAX_CHAR])const
{
	cout << label <<  name << '\t' << task << '\t' << date << endl;
}
void Course::operator=(const Course& s)
{
	if (this == &s)
		return;
	//setName(s.name);
	if (name != nullptr)
	{
		delete[] name;
	}
	name = new char[strlen(s.name) + 1];
	strcpy(name, s.name);

	if (task != nullptr)
	{
		delete[] task;
	}
	task= new char[strlen(s.task) + 1];
	strcpy(task, s.task);

	if (date != nullptr)
	{
		delete[] date;
	}
	date = new char[strlen(s.date) + 1];
	strcpy(date, s.date);
}