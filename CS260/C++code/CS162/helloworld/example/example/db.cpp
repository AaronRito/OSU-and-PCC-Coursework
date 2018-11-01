#define _CRT_SECURE_NO_WARNINGS
#include "db.h"
#include <fstream>
void addToDB(const Student& s, Student list[], int& size)
{
	list[size] = s;
	size++;
}

void listDB(const Student list[], int size)
{
	int index;
	for (index = 0; index < size; index++)
	{
		cout << list[index].name << '\t' << list[index].gpa << endl;
	}
}

bool searchDB(const char key[], const Student list[], int size, Student & match)
{
	bool	found = false;
	int		index ;
	for (index = 0; index < size; index++)
	{
		if (strcmp(key, list[index].name) ==0 )
		{
			
			match = list[index];
			
			found = true;
			
		}
	}
	return found;
}

void saveDB(const char fileName[], const Student list[], int size)
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
		out << list[index].name << ';' << list[index].gpa << endl;
	}

	out.close();
}
void loadDB(const char fileName[], Student list[], int& size)
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

		student.gpa = gpa;
		strcpy(student.name, name);

		addToDB(student, list, size);
		in.get(name, MAX_CHAR, ';');
	}
	in.close();
}
