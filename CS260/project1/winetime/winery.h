#ifndef winery_H
#define winery_H
#include "myutil.h"

class winery
{
public:
	winery();
	winery(const char initName[]);
	winery(const winery& s);
	~winery();
	void getName(char outName[]) const;
	void setName(const char inName[]);
	void getlocation(char outlocation[]) const;
	void setlocation(const char inlocation[]);
	void getDate(char outDate[]) const;
	void setDate(const char inDate[]);
	void getRank(char outRank[]) const;
	void setRank(const char inRank[]);
	void getAcre(char outDate[]) const;
	void setAcre(const char inDate[]);
	void print() const;
	void print(char label[MAX_CHAR])const;
	void operator= (const winery& s1);
	
private:
	char*	name;
	char*	location;
	char*	date;
	char*   rank;
	char*   acre;
};

#endif