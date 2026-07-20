#include <iostream>
#include <vector>
#include <stdlib.h>    // atoi
#include <pthread.h>
#include <stdio.h>     // printf

using namespace std;

pthread_once_t once_control = PTHREAD_ONCE_INIT;

struct Bounds{
    int tid;
    int from;
    int to;
    int result;
};

void Info(){
    printf("Threads start to compute\n");
}

void* Sum(void* arg)
{
    Bounds* data = (Bounds*)(arg);		// unpack arguments
    int tid  = data->tid;
    int from = data->from;
    int to   = data->to;

    pthread_once(&once_control, Info);          // info message

    int thread_sum = 0;                         // partial result
    for(int i = from; i <= to; ++i)
        thread_sum += i;

    printf("Partial sum thread %i is: %i\n", tid, thread_sum);

    data->result = thread_sum;
    pthread_exit((void*)&(data->result)); 		// return partial result
}


int main(int argc, char **argv){

    // read number of threads from commandline
    int NUM_THREADS = 0;
    if(argc > 1) NUM_THREADS = atoi(argv[1]);  // get specification
    if(NUM_THREADS <= 0) NUM_THREADS = 5;      // some default

    vector<pthread_t> threadID(NUM_THREADS);   // thread IDs
    vector<Bounds> args(NUM_THREADS);          // thread arguments

    for(int t = 0; t < NUM_THREADS; ++t) {     // spawn threads
        args[t].tid  = t; 
        args[t].from = 100*t + 1; 
        args[t].to   = 100*(t+1);

        pthread_create(&threadID[t], NULL, Sum, (void*)&args[t]);
    }

    void* res;
    int result = 0;
    for(int t = 0; t < NUM_THREADS; ++t) {     
        pthread_join(threadID[t], &res);       // wait for results

        int thread_result = *(int*)(res);
        result += thread_result;               // sum up partial results
    }

    printf("Final result is: %i\n", result);
    pthread_exit(NULL);  // terminate main thread and all other threads
}

