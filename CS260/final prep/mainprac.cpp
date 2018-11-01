#include "table.h"

#include <iostream>

using namespace std;

int main()
{
    node * root = NULL;
    build(root);
    display(root);

/* STARTING VALUES */

	cout  << "The number of nodes is: " << numberOfNodes(root) << endl;
	cout << "The height is: " << height(root) << endl;
	cout << "The other height is: " << treeHeight(root) << endl;
	cout << "The sum of the data is: " << sumR(root) << endl;
	cout << "VALUE FUNCTIONS COMPLETE" << endl << endl;
	cout << "ADDING 44 TO THE LIST" << endl<< endl;
	int key = 44;
        addNode(&root, key);
	cout << "FIND 44" << endl;
	retrieve(root, key);
	cout << "REMOVE LARGEST" << endl;
	removeLargest(root);
	display(root);
        cout  << "The number of nodes is: " << numberOfNodes(root) << endl;
        cout << "The height is: " << height(root) << endl;
        cout << "The sum of the data is: " << sumR(root) << endl<<endl;
	int max = getMax(root);
	cout << "The largest value in the list is: " << max << endl << endl;
	int min = getMin(root);
	cout << "The smallest value in the list is: " << min << endl<< endl; 

/*MODIFICATIONS*/ 
	cout << "REMOVING SMALLEST" << endl;
	removeSmallest(root);
	display(root);
	cout  << "The number of nodes is: " << numberOfNodes(root) << endl;
        cout << "The height is: " << height(root) << endl;
        cout << "The sum of the data is: " << sumR(root) << endl<<endl;
	cout << "REMOVING EVENS" << endl;
	remove(root);
	display(root);
	cout  << "The number of nodes is: " << numberOfNodes(root) << endl;
        cout << "The height is: " << height(root) << endl;
        cout << "The sum of the data is: " << sumR(root) << endl << endl;;
	

/* POST LIST DESTROY */
	destroy(root);
	cout << "POST LIST DESTROY" << endl;
	cout << "The number of nodes is: " << numberOfNodes(root) << endl;
	cout << "The height is: " << height(root) << endl;
        
    return 0;
}
