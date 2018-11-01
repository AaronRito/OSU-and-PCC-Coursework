#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "data.h"

class stack 
{
public:
	stack(); 
	stack(char * fileName);
	stack(const stack& aStack);
	~stack();

	const stack& operator= (const stack& aStack);

	bool push(const Houses&);
	bool pop(Houses&);

	bool peek(Houses&)const;
	bool isEmpty(void)const;

	void display() const; //for testing
	void writeOut(char * fileName);
private:
	Houses * items;
	int capacity;
	int top;
	static const int DEFAULT_CAPACITY = 100;
	void expandArray();
};
#endif