#ifndef data_H
#define data_H
#include "myutil.h"
#include <cstring>


class aData
{
public:
	aData();
	aData(const char initName[]);
	aData(const aData& s);
	~aData();
	void getName(char outName[]) const;
	void setName(const char outName[]);
	void getPhone(char outAss[]) const;
	void setPhone(const char inAss[]);
	void getProd(char outDate[]) const;
	void setProd(const char inDate[]);
	void getEvt(char outDiv[]) const;
	void setEvt(const char inDiv[]);
	void print() const;
	void print(char label[MAX_CHAR])const;
	void operator= (const aData& s1);
	friend ostream& operator<< (ostream& out, const aData& Adata);

private:
	char*	Name;
	char*	Phone;
	char*   Prod;
	char*   Evt;
};

#endif