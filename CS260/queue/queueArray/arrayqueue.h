#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include "data.h"
class queue 
{
public:
	queue(); 
	queue(char * fileName);
	/* not needed because there is no dynamically allocated memory
	queue(const queue& aQueue);
	~queue();

	const queue& operator= (const queue& aQueue);
	*/

	bool enqueue(const data&);
	bool dequeue(data&);

	bool peek(data&)const;
	bool isEmpty(void)const;

	void display() const; //for testing
	void writeOut(char * fileName);

private:
	static const int DEFAULT_CAPACITY = 100;
	data items[DEFAULT_CAPACITY];
	int front;
	int rear;
	int size;	
};
#endif