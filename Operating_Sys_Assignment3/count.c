/// counts number of primes from standard input
///
/// compile with:
///   $ gcc findPrimes.c -O3 -o count -lm
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int N,N1,d; //The first parameter the user input to indicatet the number of the threads
int numOfInput = 0;
int data[1000000]; 		//store the integers
int counter,num, pid;
int sum,temp,i,tmp,index = 0;	//initialize variables
		
//int i = 0;
pthread_mutex_t sum_mutex;
/// primality test, if n is prime, return 1, else return 0
int isPrime(int64_t n)
{
     if( n <= 1) return 0; // small numbers are not primes
     if( n <= 3) return 1; // 2 and 3 are prime
     if( n % 2 == 0 || n % 3 == 0) return 0; // multiples of 2 and 3 are not primes
     int64_t i = 5;
     int64_t max = sqrt(n);
     while( i <= max) {
         if (n % i == 0 || n % (i+2) == 0) return 0;
         i += 6;
     }
     return 1;
}



//===============Function that deal with the multi-threads 
void *worker_thread(void *tid){
	 int total = numOfInput;   //the number of integers in the file
    int div; //The variable that how many integers in each groups
    //==========The logical loop that calculate the number of integers that should be in each group
    if(total % N != 0){	//if the integer cannot be devided
		if((((total/N)+1) * (N-1) +total%((total/N)+1) == total) && (total%((total/N)+1) != 0)){
		div = (total - (total % N) + N)/N; //if total/num +1 is possible
		}
		else{
			div = (total - (total % N))/N;   //if total/num +1 is not possible
		}
	}
	else{
		div = total/N;	//if the integer can be devided
	}
	
    int result=0;		//store the sum result
    int *mytid = (int *) tid;	//index of the current thread
    pthread_mutex_lock (&sum_mutex);	//lock the thread
    //printf("Thread %d", *mytid);	
	//if there are more than 1 thread, do the calculation
    if (pid != 1){
        for(tmp = tmp + div; index < tmp; index++){
            if(isPrime(data[index])){
				temp+=1;
			}
        }
        pid--;  //decrease by 1
    }
	//store the sum result into the data[]
    else{
        for(int dump = 0; index <= total; index++){
            if(isPrime(data[index])){
				temp+=1;
			}
        }
    }
	//print the result
    sum += temp;
    pthread_mutex_unlock (&sum_mutex);	//unlock
    pthread_exit(NULL);			//end
    //printf("The number of primes in this thread = %d\n", count1);
   
}
//===============================Main function
int main( int argc, char ** argv)
{
    /// parse command line arguments
    sscanf(argv[1], "%d", &N);
    N1 = N;
      int nThreads = 1;
    if( argc != 2 && argc != 3) {
        printf("Uasge: countPrimes [nThreads]\n");
        exit(-1);
    }
    if( argc == 3) nThreads = atoi( argv[1]);

    /// handle invalid arguments
    if( nThreads < 1 || nThreads > 256) {
        printf("Bad arguments. 1 <= nThreads <= 256!\n");
    }
  
    /// count the primes
    if(N == 1){
		printf("Counting primes using %d thread\n", N);
	}
	else{
		printf("Counting primes using %d threads\n", N);
	}
	
	while(1){
		int64_t num;
		//printf("%d\n", num);
        if( 1 != scanf("%ld", & num)) break;
        data[numOfInput] = num; 
        numOfInput++;
	}
	
	pthread_t my_thread[N];
    pthread_attr_t attr;
    pthread_mutex_init(&sum_mutex, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	//create threads and can be worked in the work_thread
	int tids[N];
    for(int c = 1; c <=N; c++){
        tids[c] = c;
        pthread_create(&my_thread[N], &attr, worker_thread, (void*) &tids[c]);
    }

	//make sure the print of the final sum result appears in the correct location
    for (int q=0; q<N; q++) { pthread_join(my_thread[N], NULL);}
     // report results
    printf("The total prime numbers is: %d\n", sum);
	//destory the lock
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&sum_mutex);
    pthread_exit (NULL);

    return 0;
}

