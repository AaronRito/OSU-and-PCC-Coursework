#define _CRT_SECURE_NO_WARNINGS
#include "student.h"

Student::Student()
{
	strcpy(name, "no name");
	gpa = 0;
}

Student::Student(const char inName[])
{
	strcpy(name, inName);
	gpa = 0;
}

void Student::getName(char outName[]) const
{
	strcpy(outName, name);
}

void Student::setName(const char inName[])
{
	strcpy(name, inName);
}

float Student::getGpa() const
{
	return gpa;
}

void Student::setGpa(float inGpa)
{
	gpa = inGpa;
}

void Student::print()const
{
	cout << name << '\t' << gpa << endl;
}