/**********************************************
Last Name:  Zhai
First Name:  Muzhou
Student ID: 10106810
Course: CPSC 457
Tutorial Section: T02
Assignment: 1
Question: 5

File name: readFile.cpp
**********************************************/
/*
*This file has been modified very few lines from the original readFile.cpp
*instead of using getLine() method, I modified the file to print the text file to string, so that this program will run faster.
*/
#include <iostream>
#include <fstream>
using namespace std;

int main (int argc, char * const argv[])
{
    // Get the file name
    string filename; 		//initialize the string filename
    if (argc != 2)
    {
        cout << "Usage: readFile <input file> " << endl;
        return -1;
    }
    else
    {
        filename = argv[1];	//file name will be stored in argv[1]
    }
    // Open the file
    ifstream infile;		//initialize the ifstream object infile
    infile.open(filename.c_str());		//open the file according to the file name.
    string content; 		//initialize a string content, content is the string stand for the strings(words) in the sample.txt 
    while(infile >> content) { 		//if there are still more strings(words) in side the file
			cout << content <<  ' '; 	//output the string(word) end with a space.
		}
    infile.close(); 		//close the file 
    return 0;		//return 0
}
