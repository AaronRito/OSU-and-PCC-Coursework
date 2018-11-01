

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctype.h>
#include <algorithm>
#include <stdlib.h> 
#include <stdio.h>

using namespace std;

typedef int (*compfn)(const void*, const void*);
	
struct HiLoTemp
 {
   string city;
   double lowTemp;
   double highTemp;
 };

const int ARRAY_SIZE = 1000;
HiLoTemp cities [ARRAY_SIZE];
int numofcities = 0;
string cityname;
string filename;
const char FIELD_DELIM_CHAR = ',';
const char LINE_DELIM_CHAR  = '\n';
ifstream inFile;

	
int LoadData ();
void ShowAll (int count, bool sortdesc);
void ShowCities(int count, string name);
void abortProgram();
void sortcity (int count);
int compare(struct HiLoTemp *elem1, struct HiLoTemp *elem2);
 

int main(){

	string name;
	int count;
	char reply;

	reply = ' ';
	cout << "Welcome to Aaron's Library Database." << endl; 

	while (reply != 'q' && reply != 'Q') {
		
		cout << endl << "(L)oad File, Sort (A)scending, Sort (D)scending, (F)ind City, (Q)uit:" << endl; 
		cin  >> reply ;
		cin.ignore();

		if (reply == 'l' || reply == 'L') { 
			cout << "Input file name: " << endl;
			getline(cin, filename) ;
			count = 0;
			count = LoadData(); 
		}
		else if (reply == 'a' || reply == 'A') {
				cout << endl;
				ShowAll(count, false);
		}
		else if (reply == 'd' || reply == 'D') {
				cout << endl;
				ShowAll(count, true);
		}
		else if (reply == 'f' || reply == 'F') {
				cout << endl;
				cout << "What city would you like to search for?" << endl;
				getline(cin, name);
				cout << endl;
				ShowCities(count,name);    
		}
		else if  (reply == 'q' || reply == 'Q') { 
			abortProgram();}			  	
	}	

	return 0; 
}

 //read file into the array

int LoadData (){

	const int LINE_BUFF_SZ = 1024;
	char buff[LINE_BUFF_SZ];
	ifstream inFile;
	int count;

	inFile.open(filename.c_str());  
		
	if ( ! inFile.is_open()) { 
		cout << endl;
		cout << "Invalid file path, please press <L> to try again or <Q> to quit....." << endl;
		cout << endl;
		return -1;
	}
	count = 0;
	while (!inFile.eof()) {
		buff[0] = 0; 
		inFile.getline(buff, LINE_BUFF_SZ, FIELD_DELIM_CHAR);
		if (buff[0] == 0){
			continue;  
		}
		cities[count].city = string(buff);
		inFile.getline(buff, LINE_BUFF_SZ, FIELD_DELIM_CHAR);
		cities[count].lowTemp = atoi(buff); 
		inFile.getline(buff, LINE_BUFF_SZ, LINE_DELIM_CHAR);
		cities[count].highTemp = atoi(buff); 
		count++;				
	} 

	sortcity(count); 
	cout << count << " record(s) found" << endl;
	inFile.close();
	inFile.clear(std::ios_base::goodbit);
	return count;
		
}

		
// show cities in A or D order
void ShowAll(int count,bool sortdesc)  {

	int index;


		if (sortdesc){
			for (index=count-1; index >= 0; index--) {
				cout << cities[index].city << " (" << int(cities[index].lowTemp) << "," << int(cities[index].highTemp) << ")" << endl;
		
			}
		}
		else {
			for (index=0; index < count; index++){
				cout << cities[index].city << " (" << int(cities[index].lowTemp) << "," << int(cities[index].highTemp) << ")" << endl;
		
			}
		}
		return ;
}


// Search for a city	
void ShowCities(int count, string cityName){
	
	int searchcount =0;
	string currentCity;
	int index;

    transform(cityName.begin(), cityName.end(), cityName.begin(), ::tolower);   
	  
	for (index=0; index < count; index++) {
		currentCity = cities[index].city;
		transform(currentCity.begin(), currentCity.end(), currentCity.begin(), ::tolower);
		if (currentCity.find(cityName) != string::npos) {
			searchcount ++;
			cout << cities[index].city << " (" << int(cities[index].lowTemp) << "," << int(cities[index].highTemp) << ")" << endl;
		}
	}
	cout << searchcount << " record(s) found" <<endl;
}

// sort the city list
void sortcity (int count){

	qsort((void *) &cities,              
	count,                                
	sizeof(struct HiLoTemp),              
	(compfn)compare );                 
}

// compare the lists
int compare(struct HiLoTemp *elem1, struct HiLoTemp *elem2)
{
		if ( elem1->city < elem2->city)
				return -1;
		else if (elem1->city > elem2->city)
			
				return 1;

		else
      
				return 0;
}

//abort the program 
 void abortProgram(){

	string line;
	cout << "Please press <Enter> to quit:";
	getline(cin, line);
	exit(1);
}

