#ifndef DB_H
#define DB_H

#include "myutil.h"

const int MAX_CAP = 10;
struct Course
{
	char	name[MAX_CHAR];
	char	task[MAX_CHAR];
	char	date[MAX_CHAR];
};

void addToDB(const Course& s, Course list[], int& size);
void listDB(const Course list[], int size);
bool searchDB(const char key[], const Course list[], int size, int (matches)[MAX_CAP], int& matchesSize);
bool searchTask(const char key[], const Course list[], int size, const char className[], int (matches)[MAX_CAP], int& matchesSize);
void saveDB(const char fileName[], const Course list[], int size);
void loadDB(const char fileName[], Course list[], int& size);
void del(const char key[], const Course list[], int size, Course& match);

#endif