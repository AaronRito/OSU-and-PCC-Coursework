//*****************************************************************
//
// Example of multi-line input file with code that detects
// the end of the file even if there is a blank line at the
// end of the file.
//
// Create an input file with these five fields, on each
// line with space delimiters:
//
//    FirstName LastName score1 score2 score3
//
// The file name and location should be "c:\\test.txt"
// as shown in the the inFileName variable in the code.
//
// The program computes the average of the three scores and
// prints the name and average to the output file.
//
//*****************************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

void main()
{
    // Declare the input and output file objects
    ifstream inFile;
    ofstream outFile;

    // Declare variables to store information from
    // the input file and other data.
    double mU7,MO7,FU7,FO7, score, avg;
    string filename;
    char gender;

    // Store the input and output file paths
    string inFileName = "c:\\Users\\Desktop\\CS161\\input files\\toyStudyResults.txt";
    string outFileName = "c:\\Users\\Desktop\\CS161\\input files\\results.txt";

    // Open the input and output files but must extract
    // the char arrar from the string object.
    inFile.open(inFileName.c_str());
    outFile.open(outFileName.c_str());

    // Set up formatting of output file to show two
    // decimal places.
    outFile << fixed << showpoint;
    outFile << setprecision(2);

    if (inFileName.length == 0) 
		{cout << "Please enter the file path for your data" << endl;
		getline(cin, inFileName);
	}
    cout << "Processing data..." << endl;



    while (!inFile.eof())
    {
        firstName  = "";

        // Read the first two entries from the file and
        // store in string variables.
        inFile >> firstName >> lastName;

        if (firstName.length() == 0)
        {
            break;
        }

        // Print the first and last name to the output file
        outFile << "Name: " << firstName << " "
                << lastName << endl;

        // Now read the three scores from the file and store
        // in doubles.
        inFile >> t1 >> t2 >> t3;

        // Compute the average of the three scores
        average = (t1 + t2 + t3) / 3;

        // Print out the average to the output file
        outFile << "Average score: " << setw(6)
                << average << endl << endl;
    }

    // Close the two files
    inFile.close();
    outFile.close();

    // This next line seems to be required to put the file
    // in a state where it can be opened again. May also
    // have to do for outFile.
    inFile.clear(std::ios_base::goodbit);
}

