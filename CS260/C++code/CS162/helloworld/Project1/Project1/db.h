#ifndef DB_H
#define DB_H

#include "myutil.h"
#include "student.h"

const int MAX_CAP = 10;


class StudentList
{
public:
	StudentList();
	void addToDB(const Student& s);
	void listDB() const;
	bool searchDB(const char key[], Student& match) const;
	void saveDB(const char fileName[]) const;
	void loadDB(const char fileName[]);

private: 
	Student list[MAX_CAP];
	int size;
};

#endif