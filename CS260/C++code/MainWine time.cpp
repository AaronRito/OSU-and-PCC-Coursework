


#include <iostream>
#include <iomanip>        
#include <string>

using namespace std;

const double GALLONS_PER_ACRE = 945.5;
const double BOTTLES_PER_GALLON = 0.198


;int main ()
{
    double itemAcres;
    int    itemBottles;
    double itemGallons;
    

    //outputs
    cout << fixed;            
                             
    cout << setprecision(2);  
                              
	
    //dialog
    cout << "Welcome to Aaron's Viticulture Program" << endl;
    cout << "How many acres of grape vines are you growing? ";
    cin >> itemAcres;
  


    // Calculate the results
    itemGallons = itemAcres * GALLONS_PER_ACRE;
    itemBottles = itemGallons / BOTTLES_PER_GALLON;
    

    // Output the results
    cout << "The number of bottles of wine you can expect is: " << itemBottles << endl;
    cout << "This is equivalent to " << itemGallons << " Gallons." << endl;

    // "Pause" so the user can see the results
    char reply;
    cout << "Enter q to quit... ";
    cin >> reply;
    return 0;
}