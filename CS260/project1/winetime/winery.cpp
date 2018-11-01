#define _CRT_SECURE_NO_WARNINGS
#include "winery.h"

//class constructor, declare the defaults here
winery::winery()
{
	char defaultName[] = "no name";
	name = new char[strlen(defaultName) + 1];
	strcpy(name, defaultName);
	
	char defaultlocation[] = "no location";
	location = new char[strlen(defaultlocation) + 1];
	strcpy(location, defaultlocation);
	
	char defaultDate[] = "no date";
	date = new char[strlen(defaultDate) + 1];
	strcpy(date, defaultDate);	

	char defaultRank[] = "no rank";
	rank = new char[strlen(defaultRank) + 1];
	strcpy(rank, defaultRank);

	char defaultAcre[] = "no acre";
	acre= new char[strlen(defaultAcre) + 1];
	strcpy(acre, defaultAcre);
}
//copy construtor
winery::winery(const char inName[])
{
	name = new char[strlen(inName) + 1];
	strcpy(name, inName);	
}
//pointer constructor for copy
winery::winery(const winery& s)
{
	this->name = nullptr;
	this->rank = nullptr; //not sure I need this
	*this = s;
}
//destructor
winery::~winery()
{
	
	if (name)
		delete[] name;
	if (location)
		delete[] location;
	if (date)
		delete[] date;
	if (rank)
		delete(rank);
	if (acre)
		delete(acre);
}
//member functions
void winery::getName(char outName[]) const
{
	strcpy(outName, name);
}
void winery::setName(const char inName[])
{
		if (name!=nullptr)
			delete[] name;
		name = new char[strlen(inName) + 1];
		strcpy(name, inName);
}
void winery::getlocation(char outlocation[]) const
{
	strcpy(outlocation, location);
}
void winery::setlocation(const char inlocation[])
{
		if (location!=nullptr)
			delete[] location;
		location = new char[strlen(inlocation) + 1];
		strcpy(location, inlocation);
}
void winery::getDate(char outDate[]) const
{
	strcpy(outDate, date);
}
void winery::setDate(const char inDate[])
{
		if (date!=nullptr)
			delete[] date;
		date = new char[strlen(inDate) + 1];
		strcpy(date, inDate);
}
void winery::getRank(char outRank[]) const
{
	strcpy(outRank, rank);
}
void winery::setRank(const char inRank[])
{
	if (rank != nullptr)
		delete[] rank;
	rank = new char[strlen(inRank) + 1];
	strcpy(rank, inRank);
}
void winery::getAcre(char outAcre[]) const
{
	strcpy(outAcre, acre);
}
void winery::setAcre(const char inAcre[])
{
	if (acre != nullptr)
		delete[] acre;
	acre = new char[strlen(inAcre) + 1];
	strcpy(acre, inAcre);
}
void winery::print()const
{
	cout << name << '\t' << location << '\t' << date << '\t' << rank << '\t' << acre << endl;
}
void winery::print(char label[MAX_CHAR])const
{
	cout << label << name << '\t' << location << '\t' << date << '\t' << rank << '\t' << acre << endl;
}
//overload operator, makes shadow copy??
void winery::operator=(const winery& s)
{
	if (this == &s)
		return;
	if (name != nullptr)
	{
		delete[] name;
	}
	name = new char[strlen(s.name) + 1];
	strcpy(name, s.name);

	if (location != nullptr)
	{
		delete[] location;
	}
	location= new char[strlen(s.location) + 1];
	strcpy(location, s.location);

	if (date != nullptr)
	{
		delete[] date;
	}
	date = new char[strlen(s.date) + 1];
	strcpy(date, s.date);

	if (rank != nullptr)
	{
		delete[] rank;
	}
	rank = new char[strlen(s.rank) + 1];
	strcpy(rank, s.rank);

	if (acre != nullptr)
	{
		delete[] acre;
	}
	acre = new char[strlen(s.acre) + 1];
	strcpy(acre, s.acre);
}