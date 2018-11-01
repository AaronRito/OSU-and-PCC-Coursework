#ifndef DB_H
#define DB_H

#include "myutil.h"
#include "winery.h"

const int MAX_CAP = 1;
const int GROWTH_FACTOR = 4;

class list{

public:
	list();
	~list();
	void addToDB(const winery& s);
	void listName() const	;
	void listRank() const;
	void saveDB(const char fileName[]) const;
	void loadDB(const char fileName[]);
	bool searchDB(const char key[]);
	bool remove(const char key[]);
	void get(int index, winery& s);

private: 
	struct Node
	{
		winery list;
		Node * next_by_name;
		Node * next_by_rank;
	};
	Node * head_name;
	Node * head_rank;
	int size;
};
#endif