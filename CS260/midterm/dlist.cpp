#include "dlist.h"

int count(node * head)
{
	if (head == null)
	{
		return 0;
	}
	return count(head->next) +1;
}
void insert(node * head, int newInt, int position)
{
	if (pos ==0)
	{
		head.data= newInt;
		return;
	}
	return (insert(head->next, newInt, (position -1)));
}
 int remove(node * head, int position)
 {
	if (postion = 0)
	{
		return head.data;
	}
	return (remove(head->next, (position-1)));
 }

 
//put the implmenetation of the required functions here
