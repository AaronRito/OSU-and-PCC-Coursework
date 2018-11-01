#include "data.h"
//#define _CRT_SECURE_NO_WARNINGS

Data::Data() : id(nullptr), gpa(0)
{
}

Data::Data(const char * id, double gpa) : id(nullptr), gpa(gpa)
{
	this->id = new char[strlen(id) + 1];
	strcpy(this->id, id);
}

Data::Data(const Data& aData) : id(nullptr), gpa(aData.gpa)
{
	
	*this = aData;
}

Data::~Data()
{
	if (this->id)
		delete[] this->id;
}


const char * Data::getID() const
{
	return id;
}

void Data::setID(const char * id)
{
	if (this->id)
	{
		delete[] this->id;
	}
	this->id = new char[strlen(id) + 1];
	strcpy(this->id, id);
}

double Data::getGpa() const
{
	return gpa;
}

void Data::setGpa(double gpa)
{
	this->gpa = gpa;
}

const Data& Data::operator=(const Data& aData)
{
	if (this != &aData)
	{
		if (!aData.id)
			this->id = nullptr;
		else
		{
			if (this->id)
			{
				delete[] this->id;
			}
			this->id = new char[strlen(aData.id) + 1];
			strcpy(this->id, aData.id);
		}
		this->gpa = aData.gpa;		
	}
	
	return *this;
}

ostream& operator<< (ostream& out, const Data& aData)
{
	out << aData.id << '\t' << aData.gpa;
	return out;
}

bool operator< (const Data& s1, const Data& s2)
{
	return strcmp(s1.getID(), s2.getID()) < 0;
}

bool isLessThanByGpa(const Data& s1, const Data& s2)
{
	return s1.getGpa() < s2.getGpa();
}

