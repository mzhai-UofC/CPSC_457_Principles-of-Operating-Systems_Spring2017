#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;
struct file
{
	std::string fName;
	int fSize;
};

bool acompare(file lhs, file rhs) { return lhs.fSize > rhs.fSize; }

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}
int main(int argc, char * const argv[])
{
    int PATH_MAX = 512;
    char path[PATH_MAX];
    char filename[PATH_MAX];
    struct stat buf;
    file * f = new file[1000]; 
    int i = 0;
    int num2;
    int total;	//store the total size
    char command[100];	//a char command
    //Checking if the input parameters are in the correct number. Only two parameters allowed
    if( argc != 3) {
    fprintf(stderr, "Warnning: Incorrect input format. Two parameters should be input.The first should be a string, and the second shoud be can integer. ");
    exit(-1);
	}
	//Find all the files in the current location using the system call popen
    sprintf(command, "find . -type f ");
    std::string num1 = argv[1];			//Get the first parameter, it should be a string
    sscanf(argv[2], "%d", &num2);		//Get the second parameter, it should be an integer
    FILE * fp = popen(command, "r");	//Using system call to find all the files in the current location
   
    //If the current location is still not empty, read the file name
    while (fgets(path, PATH_MAX, fp) != NULL){
        strncpy(filename, &path[2], 510);
		int index = strlen(filename) - 1;
		filename[index] = '\0';
		//Checking invalid size
        if(stat(filename, &buf) <0 ){
            printf("Mesg: %s\n", strerror(errno));
            exit(-1); 
        }
        //Since the filename is char type, we have to usethe stringstream to covert char to string, so that we can compare it to the user input string.
        stringstream ss;
        string FM;
        ss << filename;
		ss >> FM;
		//Checking if the filename contains the inpur string as suffix.
        if(hasEnding(FM, num1))
        {
        f[i].fName = filename;	//if yes, store the file name to the structure as well as its size
        f[i].fSize = buf.st_size; 
        i++;
		}
    }
    std::sort(f, f+i, acompare);  //Sorting the structures based on the file size
    //output the the largest files by the limitation of the user input number 
    for(int j=0; j<num2; j++){
		if(f[j].fName != ""){  //filter the empty files
		total += f[j].fSize;   //sum the total size of the files
		cout  << "./"<< f[j].fName <<"  " << f[j].fSize << endl;  //print the filenames as well as their sizes
	}
}
	cout <<"Toal Size: " << total << endl;  //print the total size
    return 0;
}


