// g++ -Wall -Wextra equifile.cpp -o equifile.exe

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <stdio.h>
#include <string.h>
using namespace std;

#include <fstream>
using std::ios;
using std::ifstream;

#include <exception>
using std::exception;

#include <cstring>
#include <cstdlib>
using std::exit;
using std::memcmp;

bool equalFiles(ifstream& in1, ifstream& in2);

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cerr << "Usage: equifile.exe <file1> <file2>" << endl;
        exit(-1);
    }

    try {
        ifstream in1(argv[1], ios::binary);
        ifstream in2(argv[2], ios::binary);

        if(equalFiles(in1, in2)) {
            cout << "Files are equal" << endl;
            exit(0);
        }
        else
        {
            cout << "Files are not equal" << endl;
            exit(1);
        }

    } catch (const exception& ex) {
        cerr << ex.what() << endl;
        exit(-2);
    }

    return -3;
}

bool equalFiles(ifstream& file1, ifstream& file2)
{	
  	bool rc = true;
	int c1,c2;
	c1 = 0; c2 = 0;
	string str;
	while(!file1.eof())
	{
		getline(file1,str);
		c1++;
	}
	file1.clear();   //  sets a new value for the error control state
	file1.seekg(0,ios::beg);
	while(!file2.eof())
	{
		getline(file2,str);
		c2++;
	}
	file2.clear();
	file2.seekg(0,ios::beg);
	
 	if(c1 != c2) 
	{
		cout << "Different number of lines in files!" << "\n";
		cout << "file1 has " << c1 << " lines and file2 has " 
				     << c2 << " lines" << "\n";  
	}
//---------- compare two files line by line ------------------
	char string1[256], string2[256];
	int j = 0;
	while(!file1.eof())
	{
		file1.getline(string1,256);
		file2.getline(string2,256);
		j++;
		if(strcmp(string1,string2) != 0)
		{
			cout << j << "-th strings are not equal" << "\n";
			cout << "   " << string1 << "\n";
			cout << "   " << string2 << "\n";
			rc = false;
		}
	}

    return rc;
}