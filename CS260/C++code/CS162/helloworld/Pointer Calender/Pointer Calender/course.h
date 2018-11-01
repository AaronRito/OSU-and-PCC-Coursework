#ifndef COURSE_H
#define COURSE_H
#include "myutil.h"

class Course
{
public:
	Course();
	Course(const char initName[]);
	~Course();
	void getName(char outName[]) const;
	void setName(const char inName[]);
	void getTask(char outTask[]) const;
	void setTask(const char inTask[]);
	void getDate(char outDate[]) const;
	void setDate(const char inDate[]);
	void print() const;
	void print(char label[MAX_CHAR])const;
	void operator= (const Course& s1);
	
private:
	char*	name;
	char*	task;
	char*	date;	
};

#endif