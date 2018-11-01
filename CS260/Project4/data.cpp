#define _CRT_SECURE_NO_WARNINGS
#include "data.h"

//class constructor, declare the defaults here
aData::aData() 
{
	char defaultName[] = "no Name";
	Name = new char[strlen(defaultName) + 1];
	strcpy(Name, defaultName);

	char defaultPhone[] = "no Phone";
	Phone = new char[strlen(defaultPhone) + 1];
	strcpy(Phone, defaultPhone);

	char defaultProd[] = "no Product";
	Prod = new char[strlen(defaultProd) + 1];
	strcpy(Prod, defaultProd);

	char defaultEvt[] = "no Event";
	Evt = new char[strlen(defaultEvt) + 1];
	strcpy(Evt, defaultEvt);
}
//copy construtor
aData::aData(const char inName[]) 
{
	Name = new char[strlen(inName) + 1];
	strcpy(Name, inName);
}
//pointer constructor for copy
aData::aData(const aData& s)
{
	this->Name = nullptr;
	*this = s;
}
//destructor
aData::~aData()
{
	if (Name)
		delete[](Name);
	if (Phone)
		delete[](Phone);
	if (Prod)
		delete[](Prod);
	if (Evt)
		delete[](Evt);
}
//member functions
void aData::getName(char outName[]) const
{
	strcpy(outName, Name);
}
void aData::setName(const char inName[])
{
	if (Name != nullptr)
		delete[] Name;
	Name = new char[strlen(inName) + 1];
	strcpy(Name, inName);
}
void aData::getPhone(char outAss[]) const
{
	strcpy(outAss, Phone);
}
void aData::setPhone(const char inAss[])
{
	if (Phone != nullptr)
		delete[] Phone;
	Phone = new char[strlen(inAss) + 1];
	strcpy(Phone, inAss);
}
void aData::getProd(char outDate[]) const
{
	strcpy(outDate, Prod);
}
void aData::setProd(const char inDate[])
{
	if (Prod != nullptr)
		delete[] Prod;
	Prod = new char[strlen(inDate) + 1];
	strcpy(Prod, inDate);
}
void aData::getEvt(char outDiv[]) const
{
	strcpy(outDiv, Evt);
}
void aData::setEvt(const char inDiv[])
{
	if (Evt != nullptr)
		delete[] Evt;
	Evt = new char[strlen(inDiv) + 1];
	strcpy(Evt, inDiv);
}
void aData::print()const
{
	cout << Name << '\t' << Phone << '\t' << Prod << '\t' << Evt << endl;
}
void aData::print(char label[MAX_CHAR])const
{
	cout << label << Name << '\t' << Phone << '\t' << Prod << '\t' << Evt << endl;
}
//overload operator, makes shadow copy??
void aData::operator=(const aData& s)
{
	if (this == &s)
		return;
	if (Name != nullptr)
	{
		delete[] Name;
	}
	Name = new char[strlen(s.Name) + 1];
	strcpy(Name, s.Name);

	if (Phone != nullptr)
	{
		delete[] Phone;
	}
	Phone = new char[strlen(s.Phone) + 1];
	strcpy(Phone, s.Phone);

	if (Prod != nullptr)
	{
		delete[] Prod;
	}
	Prod = new char[strlen(s.Prod) + 1];
	strcpy(Prod, s.Prod);

	if (Evt != nullptr)
	{
		delete[] Evt;
	}
	Evt = new char[strlen(s.Evt) + 1];
	strcpy(Evt, s.Evt);
}

ostream& operator<< (ostream& out, const aData& Adata)
{
	out << "  Name: " << Adata.Name << "  Phone: " << Adata.Phone << "  Product: " << Adata.Prod << "  Events: " << Adata.Evt;
	return out;
}
