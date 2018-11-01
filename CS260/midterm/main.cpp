#include "dlist.h"
using namespace std;

int main()
{
	int number = 5;
    node * head = NULL;
    build(head);
    display(head);

    int size = count(head);
	insert(head, number, size -1); 
	int thing = remove(head, size -1);

    display(head);
    destroy(head);    
    return 0;
}
