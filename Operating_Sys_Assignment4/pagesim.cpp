//Muzhou,Zhai(10106810) T02 assignment 4 question 9
//reference: http://campuscoke.blogspot.ca/2015/01/clock-page-replacement-algorithm-in-c.html
//tackoverflow.com/questions/24236822/how-to-implement-clock-page-replacement-algorithm-in-c-not-c
//http://www.thecrazyprogrammer.com/2016/11/optimal-page-replacement-algorithm-c.html
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
int pages[5000]; 		//store the integers in the input file
int numOfInput = 0;
int num,fr;
//===========Optimal algorithm
void OPT(){
	int frames[fr], temp[numOfInput];
	int status1, status2, status3;//these variables are for check the pages status
	int p;	//pointer
	int faults = 0;
    printf("Optimal:\n");
    for(int i = 0; i < fr; ++i){
        frames[i] = -1;//empty frames set as -1
    }
    for(int i = 0; i < numOfInput; ++i){
        status1 = 0;
        status2 = 0;//Initialize the status1 abd status2 as 0
        for(int j = 0; j < fr; ++j){
            if(frames[j] == pages[i]){//check if the current pages is in the frame
                   status1 = 1;//if yes status1 and status2  = 1
                   status2 = 1;
                   break;
               }
        }   
        if(status1 == 0){//if the current page is not int he frame
            for(int j = 0; j < fr; ++j){
                if(frames[j] == -1){//if there is no page in the frame
                   //with each page input into the frame, fault++
                    frames[j] = pages[i]; 
                    faults++;
                    status2 = 1;//status2 update to 1
                    break;
                }
            }    
        }
        if(status2 == 0){//if the current frame is not empty
            status3 = 0;           
            for(int j = 0; j < fr; ++j){ //the array temp[] is the status of the frame
                temp[j] = -1;//initialize it with -1    
                for(int k = i + 1; k < numOfInput; ++k){
                    if(frames[j] == pages[k]){//if the current page is in the frame
                        temp[j] = k;
                        break;
                    }
                }
            }
            for(int j = 0; j < fr; ++j){
                if(temp[j] == -1){//if temp[j] is empty
                    p = j;//update pointer
                    status3 = 1;//update status3
                    break;
                }
            }
            if(status3 ==0){//if temp[]is not empty
			    p = 0;
                int max = temp[0];
				// find the biggest number in the array temp[]
                for(int j = 1; j < fr; ++j){
                    if(temp[j] > max){
                        max = temp[j];
                        p = j;
                    }
                }                
            }
            frames[p] = pages[i];
            faults++;
        }  
    }
    //Print the last frame and the total fault
    printf("  -frames:");
     for(int j = 0; j < fr; ++j){
            printf(" %d", frames[j]);
        }
    printf("\n  -Page Faults: %d\n", faults);
}
//===========LRU algorithm
void LRU(){
	int frames[fr],t[fr];//time unit
	int status1, status2, status3;//these variables are for check the pages status
	int p; //pointer
	int counter;
	int faults = 0;
	printf("LRU:\n");
	for(int i = 0; i < fr; ++i){
        frames[i] = -1;//empty frames set as -1
    }
    for(int i = 0; i < numOfInput; ++i){
        status1 = 0;//Initialize the status1 abd status2 as 0
        status2 = 0;
        
        for(int j = 0; j < fr; ++j){
            if(frames[j] == pages[i]){//check if the current pages is in the frame
                counter++;
                t[j] = counter;
                   status1 = 1;//if yes status1 and status2  = 1
                   status2 = 1;
                   break;
               }
        }
        if(status1 == 0){//if the current page is not int he frame
            for(int j = 0; j < fr; ++j){
                if(frames[j] == -1){//if there is no page in the frame
                    counter++;  //with each page input into the frame, counter and fault++
                    faults++;
                    frames[j] = pages[i];
                    t[j] = counter;
                    status2 = 1;//status2 update to 1
                    break;
                }
            }    
        }
        if(status2 == 0){//if the current frame is not empty
            int minimum = t[0], p = 0;//find the minimum page among the array t[]
			for(int i = 1; i < fr; ++i){
				if(t[i] < minimum){
					minimum = t[i];
					p = i;
				}
			}
            counter++;
            faults++;
            frames[p] = pages[i];
            t[p] = counter;
        }
    }
    //Print the last frame and the total fault
    printf("  -frames:");
    for(int j = 0; j < fr; ++j){
        printf(" %d", frames[j]);
        }
    printf("\n  -Page Faults: %d\n", faults);
	}
//==============clock algorithm
void CLO(){
	int p = 0;	//a pointer
	int fault = 0;
	int memory[numOfInput][fr], buffer[fr][2];
	printf("Clock:\n");
	for(int j = 0; j < fr; j++){
		buffer[j][0] = -1;//frame
		buffer[j][1] = 0;//mark the used pages
	}
	for(int i = 0; i < numOfInput; i++){
        int search = -1;
        for(int j = 0; j < fr; j++){
			if(buffer[j][0] == pages[i]){
				search = j;
				buffer[j][1] = 1;
				break;
			} 
        }
        if(search == -1){   
			while(buffer[p][1] == 1){
				buffer[p][1] = 0;
				p++;
				if(p == fr)
					p = 0;
			}
			buffer[p][0] = pages[i];
			buffer[p][1] = 1;
			fault++;
			p++;
			if(p == fr)
				p = 0;
         }
         for(int j = 0; j < fr; j++){
			memory[i][j] = buffer[j][0];
		 }
    }
    //print he last frame and the total fault
	printf("  -frames:");       
    for(int i = 0; i < fr; i++){
        printf(" %d" ,memory[numOfInput-1][i]);
    }
    printf("\n  -Page Faults: %d\n", fault);
}

//========Main function	
int main( int argc, char ** argv)
{
	//get the number of frames
    sscanf(argv[1], "%d", &fr);
    int frameNum = 1;
    if( argc != 2 && argc != 3) {
        printf("Invalid arguements\n");
        exit(-1);
    }
    //get the input number of frame
    if( argc == 3) frameNum = atoi( argv[1]);
	//if the input is invaild, then print the warnning and exit
    if( frameNum < 1 || frameNum > 20) {
        printf("The frame number should between 1 to 20\n");
        exit(-1);
    }
	//Read and store the input file 
	while(1){
		int64_t num;
        if( 1 != scanf("%ld", & num)) break;
        pages[numOfInput] = num; 
        numOfInput++;
	}
	//execute through the algorithms
	OPT();
	LRU();
	CLO();
	
	return 0;
}
