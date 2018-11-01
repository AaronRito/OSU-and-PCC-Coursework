#ifndef DATA_H
#define DATA_H


#include <iostream>
using namespace std;

class Data
{
public:
	Data();
	Data(const char * id, double gpa);
	Data(const Data& aData);
	~Data();

	const char* getID() const;
	void setID(const char * id);

	double getGpa() const;
	void setGpa(double gpa);

	const Data& operator= (const Data& aData);
	friend ostream& operator<< (ostream& out, const Data& aData);
private:
	char*	id;
	double	gpa;
};
bool operator< (const Data& s1, const Data& s2);
bool isLessThanByGpa(const Data& s1, const Data& s2);

#endif