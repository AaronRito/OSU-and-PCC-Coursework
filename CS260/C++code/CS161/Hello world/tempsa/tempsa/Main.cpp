// This is Assingment #7a, Tempatures.
// August 16, 2013
// Author: Aaron Rito
// Sources: CS161, Stackoverflow.com, https://github.com/ztaylor, parkratpr
 
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctype.h>
#include <algorithm>
 
using namespace std;
 
    string filename;
	const char FIELD_DELIM_CHAR = ',';
	const char LINE_DELIM_CHAR  = '\n';
	const int ARRAY_SIZE = 1000;
	ifstream inFile;
	string city[ARRAY_SIZE];
	double lowTemp[ARRAY_SIZE];
    double highTemp[ARRAY_SIZE];
	int counter = 0;
	char reply;
	int numofcities = 0;
	string cityname;
	

int myLoadData ();
void ShowAll ();
void abortProgram();
void findcity(string searchitem);

int main()
{
    string searchitem;
    int num;
    
    reply = ' ';
    
    while (reply != 'q' && reply != 'Q') {
        cout << "Welcome to Aaron's Library Database." << endl;
        cout << "(L)oad File, (S)how All, (F)ind City, (Q)uit:" << endl;
        cin  >> reply ;
        cin.ignore();
        
        if (reply == 'l' || reply == 'L') {
            counter = 0;
            cout <<"Please enter the name of the temperatures file" << endl;
            getline(cin, filename);
            num = myLoadData();  
            
        } 

        else if (reply == 's' || reply == 'S') {
            
            ShowAll();
            
        }
        
        else if (reply == 'f' || reply == 'F') {
            cout << "What city would you like to search for?" << endl;
            getline(cin, searchitem);
            findcity(searchitem);
			
        }
        
        else if  (reply == 'q' || reply == 'Q') {
        abortProgram();}
    }   
    
    return 0;
    
}


//read file into 3 different arrays

int myLoadData ()

{
    
    const int LINE_BUFF_SZ = 1024;
    char buff[LINE_BUFF_SZ];
    ifstream inFile;
    
    
    inFile.open(filename.c_str());
    
    if ( ! inFile.is_open()) {
		cout << endl;
        cout << "Invalid file path, please press <L> to try again or <Q> to quit" << endl;
		cout << endl;
        return -1;
    }
    counter = 0;
    while (!inFile.eof()) {
        buff[0] = 0;
        inFile.getline(buff, LINE_BUFF_SZ, FIELD_DELIM_CHAR);
        
        if (buff[0] == 0)
        {
            continue;
        }
        city[counter] = string(buff);
        inFile.getline(buff, LINE_BUFF_SZ, FIELD_DELIM_CHAR);
        lowTemp[counter] = atoi(buff);
        inFile.getline(buff, LINE_BUFF_SZ, LINE_DELIM_CHAR);
        highTemp[counter] = atoi(buff);
        counter++;
    }
    cout << counter << " record(s) found" << endl;
    inFile.close();
    inFile.clear(std::ios_base::goodbit);
    
    return counter;
    
}

// print the data

void ShowAll()

{
    int index;
    
    for (index=0; index < counter; index++){
        cout << city[index] << " (" << int(lowTemp[index]) << "," << int(highTemp[index]) << ")" << endl;
        
    }
    
    
    return ;
    
}


// Search for a city

void findcity(string cityName)

{

    transform(cityName.begin(), cityName.end(), cityName.begin(), ::tolower);
	int searchcount =0;
    string currentCity;
    int index;
    for (index=0; index < counter; index++) {
        currentCity = city[index];
        transform(currentCity.begin(), currentCity.end(), currentCity.begin(), ::tolower);
        if (currentCity.find(cityName) != string::npos) {
			searchcount ++;
            cout << city[index] <<" (" << int(lowTemp[index]) << "," << int(highTemp[index]) << ")" << endl;
	
		}

	}
	    
	cout << searchcount << " record(s) found" <<endl;
            
	
}
        
//abort the program

void abortProgram()

{
	string line;
    cout << "Please press <Enter> to quit:";
    getline(cin, line);
    exit(1);
}
 