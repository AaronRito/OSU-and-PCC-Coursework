#include "dlist.h"
#include <cstring>
using namespace std;

//put the implmenetation of the required functions here
int addNode(node *& head, int pos, int newInt)
{
	if (!head)
	return 0;
	if (pos == 0)
	{
		node * temp = new node;
                temp->data = newInt;
		if (head->previous == NULL)
                {
                        temp->next = head;
			head->previous = temp;
			temp->previous = NULL;
			head = temp;
               }
               else if(head->next == NULL )
               {
                        head->next = temp;
			temp->previous = head;
			temp->next = NULL;
	       }
               else
               {			
                        temp->previous = head;
			temp->next = head->next;
			head->next->previous = temp;
			head->next = temp;
               }
		return 1;
	}
	else
	return (addNode(head->next, pos-1, newInt));	
}
int MySize(node * head)
{
	if (head == NULL)
        return 0;
	else
	return (MySize(head->next) +1);
}
int countEven(node * head)
{
	if (head == NULL)
	return 0;
	else if (head->data % 2 == 0) 
	{
		return(countEven(head->next) +1);
	}
	return(countEven(head->next));

}
int removeEven(node *& head)
{
	if (head == NULL)
	return 0;
	else if (head->data % 2 == 0)
	{
		node * temp = head;
		if (head->previous == NULL)
		{
			head = head->next;
			if (head)
			head->previous = NULL;
			
		}
		else if(head->next == NULL )
		{	
			head = head->previous;
			head->next = NULL;
		}
		else 
		{
			temp->previous->next = temp->next;
			temp->next->previous = temp->previous;
		}
		delete temp;
		return(removeEven(head));
	}
	else
	return(removeEven(head->next));
}
