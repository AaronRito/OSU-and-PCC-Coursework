#ifndef DB_H
#define DB_H

#include "myutil.h"
#include "course.h"

const int MAX_CAP = 1;
const int GROWTH_FACTOR = 2;

class TaskList{

public:
	TaskList();
	~TaskList();
	void addToDB(const Course& s);
	void listDB() const	;
	void saveDB(const char fileName[]) const;
	void loadDB(const char fileName[]);
	bool searchDB(const char key[]);
	bool delIt(const int pos);


private: 
	   	 Course * list;
		 int currCapacity;
		 int size;

		 void grow();
};


#endif