#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "data.h"
class list
{
public:
	list();
	list(char * fileName);
	list(const list& aList);
	~list();

	const list& operator= (const list& aList);

	bool insert(const data& aData);
	bool remove(char * key);
	bool retrieve(char * key, data& aData)const;
	void display(void)const;
	int getSize(void)const;
	void writeOut(char * fileName);

private:
	data * dArray;
	int capacity;
	int size;
	const static int DEFAULT_CAPACITY = 10;
	void expandArray(void);

};
#endif