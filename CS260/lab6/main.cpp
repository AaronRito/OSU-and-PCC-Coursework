#include "table.h"

#include <iostream>

using namespace std;

int main()
{
    node * root = NULL;
    build(root);
    display(root);

    /*  PLACE YOUR FUNCTION CALL HERE */

	cout<< "My node count is: " << size(root)<< endl;
	cout << "My height calculation 1 is: " << height(root) <<  endl;
	cout << "My height calculation 2 is: " << treeHeight(root) <<  
endl;
	cout << "My sum of the data is: " << sumR(root) << endl;
    display(root);
    destroy(root);
    return 0;
}
