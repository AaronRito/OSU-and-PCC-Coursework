#include "dlist.h"
using namespace std;

int main()
{
    node * head = NULL;
    build(head);
    display(head);
	int num = 555;
	int num2 = 777;
	int num3 = 999;
//	int pos = MySize(head) -2;
//	cout << "pos  " << pos << endl;
	cout << "add at BEG" << endl;
	addNode(head, 0, num);
	display(head);
	cout << "add at END" << endl;
	int pos = (MySize(head) -1);
	addNode(head, pos, num2);
	display(head);
	cout << "add at MID" << endl;
	int pos2 =(MySize(head) -3);
	addNode(head, pos2 , num3);
	display(head);
	int evenNum = countEven(head);
	cout << evenNum << endl;
    //PLEASE PUT YOUR CODE HERE to call the function assigned
	cout << removeEven(head) << endl;

    display(head);
    destroy(head);    
    return 0;
}
