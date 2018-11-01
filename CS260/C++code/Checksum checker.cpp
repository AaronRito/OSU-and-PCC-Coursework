

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

     string filename;
	 string outFileName = "c:\\data.txt";
	 ifstream inputFile;
	 ofstream outputfile;
	 int fileNamesSize = 0;
     int checkSumsSize = 0;

const int SUM_ARR_SZ = 100;
unsigned int checkSums[SUM_ARR_SZ];
string fileNames[SUM_ARR_SZ];
char chararray[100000];
char reply;

void abortProgram();
int runcheck(string filename);
bool runitegrity(string filename);

int main ()
{
	int returnedchecksum; 

	reply = ' ';
	  		   
         while (reply != 'q' && reply != 'Q'){
			cout << "Please select:" << endl;
			cout << "A) Compute checksum of specified file" << endl;
			cout << "B) Verify integrity of specified file" << endl;
			cout << "Q) Quit" << endl;
			cin  >> reply ;
			cin.ignore();

			  if (reply == 'a' || reply == 'A') { 
				  cout << "Input file name: " << endl; 
				  getline(cin, filename) ;			  
				  returnedchecksum = runcheck(filename) ;
				  if (returnedchecksum > 0) {
					  // save the filename and checksum
					  fileNames[fileNamesSize++] = filename;
					  checkSums[checkSumsSize++] = returnedchecksum;
				  }
			  }
			  else if (reply == 'b' || reply == 'B') {
				   cout << "Input file name: " << endl; 
			       getline(cin, filename) ;
				   runitegrity(filename);
			  }
			  else if  (reply == 'q' || reply == 'Q') { 
				abortProgram();}			  	
			  }	

		return 0;
		 
}
			 

	
	// Open the input file.
 int runcheck(string filename) 
 
 {
	 
	 int fileLen = 0;
	 int end, beg, index;
	 int checksum = 0;
	           
		  inputFile.open(filename.c_str(), ios::binary);  
		  if ( ! inputFile.is_open()) { 
			  cout << "invalid file path" << endl;
				 return 0;}
		  else{
			  inputFile.seekg(0, ios_base::end);
			  fileLen = inputFile.tellg();
			  inputFile.seekg(0, ios_base::beg);
			  inputFile.read(chararray, fileLen);
			  inputFile.close();
			  inputFile.clear(std::ios_base::goodbit);
			// compute checksum 
			for (index=0; index <= fileLen; index++){
				checksum+= int(chararray[index]); 
			}
			cout << "File checksum = " << checksum << endl;
			return checksum; 
		  }
		  
		
 }   
 

 bool runitegrity(string filename)
 {
	 int arrayindex, newchecksum;
	 char string1[255], string2[255];
	 bool checkcompares;
strcpy_s(string1,filename.c_str());

 for (arrayindex = 0; arrayindex <= fileNamesSize; arrayindex++){
	strcpy_s(string2,fileNames[arrayindex].c_str()); 
  if (strcmp(string1,string2) == 0) {
     // compare the recomputed checksum to the stored checksum
	  newchecksum= runcheck(filename);
	 checkcompares = newchecksum == checkSums[arrayindex];
	  if (!checkcompares) {
		  cout << "The file integrity check has failed (previous checksum = " << checkSums[arrayindex] << ", new checksum = " << newchecksum << endl;
	  }	
	 else {
	   cout << "The file integrity check has passed successfully." << endl;
	 return checkcompares;
  }
 }
  else { 
	  cout << "The checksum has not been computed on the file:" << filename << endl;
   }
  return false;
}
 }


	//abort the program 
 
void abortProgram()

{
    string line;
    cout << "Please press <Enter> to quit:";
    getline(cin, line);
    exit(1);
}
 