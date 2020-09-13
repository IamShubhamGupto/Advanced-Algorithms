#include "splay_tree_imp.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BENCHMARK_COUNT 100


// function to start a nanosecond-resolution timer
struct timespec timer_start(){
	struct timespec start_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	return start_time;
}

// function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
	struct timespec end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
	return diffInNanos;
}


int main() {

    void* dictionary = make_new_dictionary();
    for(int i=1; i<=BENCHMARK_COUNT; ++i) {
        struct timespec vartime = timer_start();
        if(rand()%2) {
            insert(dictionary, random()%BENCHMARK_COUNT, random()%BENCHMARK_COUNT);
        }
        else {
            printf("%d ", find(dictionary, random()%BENCHMARK_COUNT));
            // find(dictionary, random()%BENCHMARK_COUNT);
        }
        long time_elapsed_nanos = timer_end(vartime);
        printf("%ld\n", time_elapsed_nanos);
    }
}
