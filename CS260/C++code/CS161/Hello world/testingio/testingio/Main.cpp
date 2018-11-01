//*****************************************************************
//This is Aaron Rito's assignment #4, test averager
//Author: Aaron Rito
//Date: 7/21/2013
//Source: CS161

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    // Declare the input and output file objects
    ifstream inFile;
    ofstream outFile;

    // Declare variables to store information from
    // the input file and other data.
    char reply;
	double score, age;
    string firstName;
	string gender;
	string filename;

	double allscores =0, allcount =0;
	double allavg =0;
	
	double fover7total =0, fover7count =0;
	double fover7avg = 0;

	double mover7total =0, mover7count =0;
	double mover7avg = 0;

	double munder7total =0, munder7count =0;
	double munder7avg = 0;

	double funder7total =0, funder7count =0;
	double funder7avg = 0;

	cout << "Please specify file path for your data (ex.c:\\Users\\aaron\\Desktop\\CS161\\input files\\results.txt)" << endl;
	getline(cin, filename);


	// Store the input and output file paths
    string inFileName = filename;
    string outFileName = "c:\\results.txt";
	
	// Open the input and output files but must extract
    // the char arrar from the string object.
    inFile.open(inFileName.c_str());
    outFile.open(outFileName.c_str());

    // Set up formatting of output file to show two
    // decimal places.
    outFile << fixed << showpoint;
    outFile << setprecision(2);

	
    cout << "Processing data..." << endl;

    while (!inFile.eof())
    {
        firstName  = "";

        // Read the first two entries from the file and
        // store in string variables.
        inFile >> firstName >> age >> gender >> score;
		if (firstName.length() == 0) {
            break;
        }

        // Now read the three scores from the file and store
        // in doubles.


		if (age > 7 && gender == "M") {
			mover7total+= score;
			mover7count++;
		}
	
		if (age > 7 && gender == "F") {
		funder7total+= score;
		funder7count++;
		}

		if (age <= 7 && gender == "F") {
		fover7total+= score;
		fover7count++;

		}
		
		if (age <= 7 && gender == "M") {
			munder7total+= score;
			munder7count++;
		}
		if (age >= 0) {
			allscores+= score;
			allcount++;
		}
	}

	if (mover7count > 0) {
		mover7avg = mover7total / mover7count; 
	}
	if (munder7count > 0) {
		munder7avg = munder7total / munder7count; 
	}
	
	
	if (funder7count > 0) {
		funder7avg = funder7total/ funder7count;
	}
	if (fover7count > 0) {
		fover7avg = fover7total/ fover7count;
	}
		if (allcount > 0) {
		allavg = allscores/ allcount; 
	}

		if (allavg == 0) {
		cout << "invalid file path, please restart" << endl;
        cout << "Press q to quit: ";
        cin >> reply;
        exit(1);         
    }

		

	// output mover7 

	cout << "The average score for male subjects over 7 is: " << mover7avg << endl;
	cout << "The average score for male subjects 7 and under is: " << munder7avg << endl;
	cout << "The average score for female subjects over 7 is: " << fover7avg  << endl;
	cout << "The average score for female subjects 7 and under is: " << funder7avg << endl;
	cout << "The average score for all subjects is: " << allavg << endl;
		
		
    // Close the two files
	inFile.close();
    outFile.close();

    // This next line seems to be required to put the file
    // in a state where it can be opened again. May also
    // have to do for outFile.
    inFile.clear(std::ios_base::goodbit);
	
	 

		cout << "press q to quit";
		cin >> reply;
return 0;
} 