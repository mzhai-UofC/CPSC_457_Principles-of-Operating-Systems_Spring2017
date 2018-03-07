#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <vector>
#include <sstream>



using namespace std;

int main(int argc, char *argv[]){
    if(argc < 4 ){
    	cout << "Less argument!" <<endl;
    }
    
    string filename;
    int time_quantum;

    filename = argv[1];
    sscanf(argv[3], "%d", &time_quantum);
    cout << "filename: " << filename << endl;
    cout << "time quantum: " << time_quantum << endl;

    ifstream infile(filename);   
    int at[30], bt[30], rt[30];
//    int counter = 0;
    int a, b, c;
    bzero(at, sizeof(at));
    bzero(bt, sizeof(bt));
    bzero(rt, sizeof(rt));

    /*
    while(infile >> a){
        if(counter %2 ==0){
	    at[counter/2] = a;
	}else{
	    bt[counter/2] = a;
	    rt[counter/2] = a;
	}
    }
*/  
    int counter =0;
    while (infile >> c >> a >> b)
    {

	//cout << "a: " << a<<endl;
	//cout << "b: " << b<<endl;
        
	at[counter] = a;
	bt[counter] = b;

	rt[counter] = b;

	counter++;
    }

    


    int length;
    length = sizeof(at) /sizeof(int);
    for(int i=0; i < length; i++){
        cout << "at " << i <<": " << at[i] << endl; 
    }

    length = sizeof(bt) /sizeof(int);
    for(int i=0; i < length ; i++){
        cout << "bt " << i <<": " << bt[i] << endl;
    }

    length = sizeof(rt) /sizeof(int);
    for(int i=0; i< length ; i++){
        cout << "rt " << i <<": "<<rt[i] <<endl;
    }



    return 0;
}
