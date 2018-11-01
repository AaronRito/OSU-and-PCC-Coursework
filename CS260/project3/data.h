#ifndef data_H
#define data_H
#include "myutil.h"
#include <cstring>


class aData
{
public:
	aData();
	aData(const char initSymbol[]);
	aData(const aData& s);
	~aData();
	void getSymbol(char outSymbol[]) const;
	void setSymbol(const char inSymbol[]);
	void getName(char outName[]) const;
	void setName(const char outName[]);
	void getAss(char outAss[]) const;
	void setAss(const char inAss[]);
	void getDate(char outDate[]) const;
	void setDate(const char inDate[]);
	void getDiv(char outDiv[]) const;
	void setDiv(const char inDiv[]);
	void print() const;
	void print(char label[MAX_CHAR])const;
	void operator= (const aData& s1);
	friend ostream& operator<< (ostream& out, const aData& Adata);

private:
	char*	Symbol;
	char*	Name;
	char*	Ass;
	char*   Date;
	char*   Div;
};

#endif