#ifndef STUDENT_H
#define STUDENT_H
#include "myutil.h"

class Student
{
public:
	Student();
	Student(const char initName[]);
	void getName(char outName[]) const;
	void setName(const char inName[]);
	float getGpa() const;
	void setGpa(float gpa);
	void print() const;

private:
	char	name[MAX_CHAR];
	float	gpa;
};

#endif