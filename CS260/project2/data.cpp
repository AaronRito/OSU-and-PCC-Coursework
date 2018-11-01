#define _CRT_SECURE_NO_WARNINGS
#include "data.h"

//class constructor, declare the defaults here
Houses::Houses()
{
	char defaultAddress[] = "no Address";
	Address = new char[strlen(defaultAddress) + 1];
	strcpy(Address, defaultAddress);

	char defaultSqFoot[] = "no SqFoot";
	SqFoot = new char[strlen(defaultSqFoot) + 1];
	strcpy(SqFoot, defaultSqFoot);

	char defaultBeds[] = "no Beds";
	Beds = new char[strlen(defaultBeds) + 1];
	strcpy(Beds, defaultBeds);

	char defaultBath[] = "no Bath";
	Bath = new char[strlen(defaultBath) + 1];
	strcpy(Bath, defaultBath);

	char defaultFeature[] = "no Feature";
	Feature = new char[strlen(defaultFeature) + 1];
	strcpy(Feature, defaultFeature);
}
//copy construtor
Houses::Houses(const char inAddress[])
{
	Address = new char[strlen(inAddress) + 1];
	strcpy(Address, inAddress);
}
//pointer constructor for copy
Houses::Houses(const Houses& s)
{
	this->Address = nullptr;
	this->Bath = nullptr; //not sure I need this
	*this = s;
}
//destructor
Houses::~Houses()
{

	if (Address)
		delete[] Address;
	if (SqFoot)
		delete[] SqFoot;
	if (Beds)
		delete[] Beds;
	if (Bath)
		delete[](Bath);
	if (Feature)
		delete[](Feature);
}
//member functions
void Houses::getAddress(char outAddress[]) const
{
	strcpy(outAddress, Address);
}
void Houses::setAddress(const char inAddress[])
{
	if (Address != nullptr)
		delete[] Address;
	Address = new char[strlen(inAddress) + 1];
	strcpy(Address, inAddress);
}
void Houses::getSqfoot(char outSqFoot[]) const
{
	strcpy(outSqFoot, SqFoot);
}
void Houses::setSqfoot(const char inSqFoot[])
{
	if (SqFoot != nullptr)
		delete[] SqFoot;
	SqFoot = new char[strlen(inSqFoot) + 1];
	strcpy(SqFoot, inSqFoot);
}
void Houses::getBeds(char outBeds[]) const
{
	strcpy(outBeds, Beds);
}
void Houses::setBeds(const char inBeds[])
{
	if (Beds != nullptr)
		delete[] Beds;
	Beds = new char[strlen(inBeds) + 1];
	strcpy(Beds, inBeds);
}
void Houses::getBath(char outBath[]) const
{
	strcpy(outBath, Bath);
}
void Houses::setBath(const char inBath[])
{
	if (Bath != nullptr)
		delete[] Bath;
	Bath = new char[strlen(inBath) + 1];
	strcpy(Bath, inBath);
}
void Houses::getFeature(char outFeature[]) const
{
	strcpy(outFeature, Feature);
}
void Houses::setFeature(const char inFeature[])
{
	if (Feature != nullptr)
		delete[] Feature;
	Feature = new char[strlen(inFeature) + 1];
	strcpy(Feature, inFeature);
}
void Houses::print()const
{
	cout << Address << '\t' << SqFoot << '\t' << Beds << '\t' << Bath << '\t' << Feature << endl;
}
void Houses::print(char label[MAX_CHAR])const
{
	cout << label << Address << '\t' << SqFoot << '\t' << Beds << '\t' << Bath << '\t' << Feature << endl;
}
//overload operator, makes shadow copy??
void Houses::operator=(const Houses& s)
{
	if (this == &s)
		return;
	if (Address != nullptr)
	{
		delete[] Address;
	}
	Address = new char[strlen(s.Address) + 1];
	strcpy(Address, s.Address);

	if (SqFoot != nullptr)
	{
		delete[] SqFoot;
	}
	SqFoot = new char[strlen(s.SqFoot) + 1];
	strcpy(SqFoot, s.SqFoot);

	if (Beds != nullptr)
	{
		delete[] Beds;
	}
	Beds = new char[strlen(s.Beds) + 1];
	strcpy(Beds, s.Beds);

	if (Bath != nullptr)
	{
		delete[] Bath;
	}
	Bath = new char[strlen(s.Bath) + 1];
	strcpy(Bath, s.Bath);

	if (Feature != nullptr)
	{
		delete[] Feature;
	}
	Feature = new char[strlen(s.Feature) + 1];
	strcpy(Feature, s.Feature);
}

ostream& operator<< (ostream& out, const Houses& Adata)
{
	out << "Address: " << Adata.Address << "  Sq Foot: " << Adata.SqFoot << "  # of beds: " << Adata.Beds << "  # of baths: " << Adata.Bath << "  Special Feature: " << Adata.Feature;
	return out;
}