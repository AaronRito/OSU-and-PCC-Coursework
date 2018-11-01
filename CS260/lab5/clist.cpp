#include "clist.h"
int sumi(node * head)
{
	node * first = head;
	int total = 0;
	while (head->next != first)
	{
		total = total + head->data;
		head = head->next;
	}
	total = total + first->data;
	return total;
}
int sum(node * head)
{
	node * first = head;
        int total = 0;
        total  = sumR(head, first);
        return total;
}
int sumR(node * head, node * first)
{
        if (head->next == first)
                return first->data;
        else
                return(head->next->data + sumR(head->next, first));
}
int counti(node * head)
{
	node * first = head;
        int total = 1;
        while (head->next != first)
        {
                total = total + 1;
                head = head->next;
        }
        return total;
}
int count(node * head)
{
	node * first = head;
        int total = 0;
        total  = countR(head, first);
        return total;	
}
int countR(node * head, node * first)
{
	if (head->next == first)
                return 1;
        else
                return(1 + countR(head->next, first));	
}
