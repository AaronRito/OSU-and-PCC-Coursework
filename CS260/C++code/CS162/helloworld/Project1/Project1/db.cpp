#define _CRT_SECURE_NO_WARNINGS
#include "db.h"
#include <fstream>

StudentList::StudentList()
{
	size = 0;
}
void StudentList::addToDB(const Student& s)
{
	list[size] = s;
	size++;
}

void StudentList::listDB() const
{
	int index;
	char name[MAX_CHAR];
	for (index = 0; index < size; index++)
	{
		list[index].getName(name);
		cout << name << '\t' << list[index].getGpa()<< endl;
	}
}

bool StudentList::searchDB(const char key[], Student & match) const
{
	bool	found = false;
	int		index;
	char	name[MAX_CHAR];
	for (index = 0; index < size; index++)
	{
		list[index].getName(name);
		if (strcmp(key, name) == 0)
		{
			match = list[index];
			found = true;
			break;
		}
	}
	return found;
}

void StudentList::saveDB(const char fileName[]) const
{
	ofstream	out;

	out.open(fileName);
	if (!out)
	{
		cerr << "Fail to open " << fileName << " for writing!" << endl;
		exit(1);
	}

	int index;
	char name[MAX_CHAR];
	for (index = 0; index < size; index++)
	{
		list[index].getName(name);
		out << name << ';' << list[index].getGpa() << endl;
	}

	out.close();
}
void StudentList::loadDB(const char fileName[])
{
	ifstream	in;
	char		name[MAX_CHAR];
	float		gpa;
	Student		student;

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
		in >> gpa;
		in.ignore(MAX_CHAR, '\n'); //remove the '\n'

		student.setGpa(gpa);
		student.setName(name);

		addToDB(student);
		in.get(name, MAX_CHAR, ';');
	}
	in.close();
}
