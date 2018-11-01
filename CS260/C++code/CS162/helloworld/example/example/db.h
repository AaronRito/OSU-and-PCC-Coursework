#ifndef DB_H
#define DB_H

#include "myutil.h"

const int MAX_CAP = 10;
struct Student
{
	char	name[MAX_CHAR];
	float	gpa;
};

void addToDB(const Student& s, Student list[], int& size);
void listDB(const Student list[], int size);
bool searchDB(const char key[], const Student list[], int size, Student& match);
void saveDB(const char fileName[], const Student list[], int size);
void loadDB(const char fileName[], Student list[], int& size);

#endif