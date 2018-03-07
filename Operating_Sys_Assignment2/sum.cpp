#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
//=========global variables
int data[1000000]; 		//store the integers
int counter,num, pid;	//variables
int sum,index = 0;		//initialize variables
int tmp = 0;			//loop counter
pthread_mutex_t sum_mutex;	//mutex lock
//==========The function that deal with each thread's elements. Calculation & print
void *worker_thread(void *tid){
    int total = counter;   //the number of integers in the file
    int div; //The variable that how many integers in each groups
    //==========The logical loop that calculate the number of integers that should be in each group
    if(total % num != 0){	//if the integer cannot be devided
		if((((total/num)+1) * (num-1) +total%((total/num)+1) == total) && (total%((total/num)+1) != 0)){
		div = (total - (total % num) + num)/num; //if total/num +1 is possible
		}
		else{
			div = (total - (total % num))/num;   //if total/num +1 is not possible
		}
	}
	else{
		div = total/num;	//if the integer can be devided
	}
	
    int result=0;		//store the sum result
    int *mytid = (int *) tid;	//index of the current thread
    pthread_mutex_lock (&sum_mutex);	//lock the thread
    printf("Thread %d", *mytid);	
	//if there are more than 1 thread, do the calculation
    if (pid != 1){
        for(tmp = tmp + div; index < tmp; index++){
            result += data[index];
        }
        pid--;  //decrease by 1
    }
	//store the sum result into the data[]
    else{
        for(int dump = 0; index <= total; index++){
            result += data[index];
        }
    }
	//print the result
    sum += result;
    cout <<": " << result << endl;
    pthread_mutex_unlock (&sum_mutex);	//unlock
    pthread_exit(NULL);			//end
}

int main(int argc, char* argv[])
{
	//check the paramaters
    if( argc != 3) {
        fprintf(stderr, "invalid parameters.\n");
        exit(-1);
    }
    string filename;	//get the filename from the user
    filename = argv[1];
   
    int a;	//initialize variables
    int id;
    sscanf(argv[2], "%d", &id);	//get user's input thread's number
    num = id;
    pid = num;
    int tids[id];
    std::ifstream infile(filename); //open the file
    counter = 0;
    //read the integers can store them into data[]
    while(infile >> a){
        cout << "Integers: " << a << endl;
        data[counter] = a;
        counter++;
    }
    pthread_t my_thread[id];
    pthread_attr_t attr;
    pthread_mutex_init(&sum_mutex, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	//create threads and can be worked in the work_thread
    for(int c = 1; c <=id; c++){
        tids[c] = c;
        pthread_create(&my_thread[id], &attr, worker_thread, (void*) &tids[c]);
    }

	//make sure the print of the final sum result appears in the correct location
    for (int q=0; q<id; q++) { pthread_join(my_thread[id], NULL);}
        printf("Sum: %d\n", sum);
	//destory the lock
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&sum_mutex);
    pthread_exit (NULL);

    return 0;
}

