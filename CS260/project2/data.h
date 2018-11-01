#ifndef data_H
#define data_H
#include "myutil.h"
#include <cstring>


class Houses
{
public:
	Houses();
	Houses(const char initAddress[]);
	Houses(const Houses& s);
	~Houses();
	void getAddress(char outAddress[]) const;
	void setAddress(const char inAddress[]);
	void getSqfoot(char outSqFoot[]) const;
	void setSqfoot(const char inSqFoot[]);
	void getBeds(char outBeds[]) const;
	void setBeds(const char inBeds[]);
	void getBath(char outBath[]) const;
	void setBath(const char inBath[]);
	void getFeature(char outBeds[]) const;
	void setFeature(const char inBeds[]);
	void print() const;
	void print(char label[MAX_CHAR])const;
	void operator= (const Houses& s1);
	friend ostream& operator<< (ostream& out, const Houses& Adata);

private:
	char*	Address;
	char*	SqFoot;
	char*	Beds;
	char*   Bath;
	char*   Feature;
};

#endif