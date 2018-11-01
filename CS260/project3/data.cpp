#define _CRT_SECURE_NO_WARNINGS
#include "data.h"

//class constructor, declare the defaults here
aData::aData()
{
	char defaultSymbol[] = "no Symbol";
	Symbol = new char[strlen(defaultSymbol) + 1];
	strcpy(Symbol, defaultSymbol);

	char defaultName[] = "no Name";
	Name = new char[strlen(defaultName) + 1];
	strcpy(Name, defaultName);

	char defaultAss[] = "no Assest";
	Ass = new char[strlen(defaultAss) + 1];
	strcpy(Ass, defaultAss);

	char defaultDate[] = "no Date";
	Date = new char[strlen(defaultDate) + 1];
	strcpy(Date, defaultDate);

	char defaultDiv[] = "no Dividend";
	Div = new char[strlen(defaultDiv) + 1];
	strcpy(Div, defaultDiv);
}
//copy construtor
aData::aData(const char inSymbol[])
{
	Symbol = new char[strlen(inSymbol) + 1];
	strcpy(Symbol, inSymbol);
}
//pointer constructor for copy
aData::aData(const aData& s)
{
	this->Symbol = nullptr;
	*this = s;
}
//destructor
aData::~aData()
{
	if (Symbol)
		delete[](Symbol);
	if (Name)
		delete[](Name);
	if (Ass)
		delete[](Ass);
	if (Date)
		delete[](Date);
	if (Div)
		delete[](Div);
}
//member functions
void aData::getSymbol(char outSymbol[]) const
{
	strcpy(outSymbol, Symbol);
}
void aData::setSymbol(const char inSymbol[])
{
	if (Symbol != nullptr)
		delete[] Symbol;
	Symbol = new char[strlen(inSymbol) + 1];
	strcpy(Symbol, inSymbol);
}
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
void aData::getAss(char outAss[]) const
{
	strcpy(outAss, Ass);
}
void aData::setAss(const char inAss[])
{
	if (Ass != nullptr)
		delete[] Ass;
	Ass = new char[strlen(inAss) + 1];
	strcpy(Ass, inAss);
}
void aData::getDate(char outDate[]) const
{
	strcpy(outDate, Date);
}
void aData::setDate(const char inDate[])
{
	if (Date != nullptr)
		delete[] Date;
	Date = new char[strlen(inDate) + 1];
	strcpy(Date, inDate);
}
void aData::getDiv(char outDiv[]) const
{
	strcpy(outDiv, Div);
}
void aData::setDiv(const char inDiv[])
{
	if (Div != nullptr)
		delete[] Div;
	Div = new char[strlen(inDiv) + 1];
	strcpy(Div, inDiv);
}
void aData::print()const
{
	cout << Symbol << '\t' << Name << '\t' << Ass << '\t' << Date << '\t' << Div << endl;
}
void aData::print(char label[MAX_CHAR])const
{
	cout << label << Symbol << '\t' << Name << '\t' << Ass << '\t' << Date << '\t' << Div << endl;
}
//overload operator, makes shadow copy??
void aData::operator=(const aData& s)
{
	if (this == &s)
		return;
	if (Symbol != nullptr)
	{
		delete[] Symbol;
	}
	Symbol = new char[strlen(s.Symbol) + 1];
	strcpy(Symbol, s.Symbol);

	if (Name != nullptr)
	{
		delete[] Name;
	}
	Name = new char[strlen(s.Name) + 1];
	strcpy(Name, s.Name);

	if (Ass != nullptr)
	{
		delete[] Ass;
	}
	Ass = new char[strlen(s.Ass) + 1];
	strcpy(Ass, s.Ass);

	if (Date != nullptr)
	{
		delete[] Date;
	}
	Date = new char[strlen(s.Date) + 1];
	strcpy(Date, s.Date);

	if (Div != nullptr)
	{
		delete[] Div;
	}
	Div = new char[strlen(s.Div) + 1];
	strcpy(Div, s.Div);
}

ostream& operator<< (ostream& out, const aData& Adata)
{
	out << "Ticker: " << Adata.Symbol << "  Name: " << Adata.Name << "  Asset: " << Adata.Ass << "  Date: " << Adata.Date << "  Dividend: " << Adata.Div;
	return out;
}