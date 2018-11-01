#define _CRT_SECURE_NO_WARNINGS
#include "course.h"


Course::Course()
{
	strcpy(name, "no name");
	strcpy(task, "no task");
	strcpy(date, "no date");
	
}

Course::Course(const char inName[])
{
	strcpy(name, inName);
	
}

void Course::getName(char outName[]) const
{
	strcpy(outName, name);
}

void Course::setName(const char inName[])
{
	strcpy(name, inName);
}
void Course::getTask(char outTask[]) const
{
	strcpy(outTask, task);
}

void Course::setTask(const char inTask[])
{
	strcpy(task, inTask);
}

void Course::getDate(char outDate[]) const
{
	strcpy(outDate, date);
}

void Course::setDate(const char inDate[])
{
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
