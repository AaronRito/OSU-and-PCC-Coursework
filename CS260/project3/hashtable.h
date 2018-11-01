#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "data.h"
#include <cstring>
class hashTable
{
public:
	hashTable();
	hashTable(char * fileName);
	hashTable(const hashTable& aTable);
	~hashTable();

	const hashTable& operator= (const hashTable& aTable);

	void insert(const aData& MyData);
	bool remove(char * key);
	bool retrieve(char * key, aData& MyData)const;
	bool modify(char * tickerSymbol, char * newNetAssetVal, char * newDate, char * newDateReturn);
	void display(void)const;
	void monitor(void)const;
	int getSize(void)const;
	void writeOut(char * fileName);

private:
	struct node
	{
		aData item;
		node * next;
		node(const aData& MyData)
		{
			item = MyData;
			next = NULL;
		}
	};
	node ** table;
	int capacity;
	int size;
	const static int DEFAULT_CAPACITY = 7;

	void destroyTable();
	void initializeTable();
	int calculateIndex(char * key)const;
};
#endif