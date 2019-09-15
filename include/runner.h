#ifndef RUNNER_H
#define RUNNER_H

#include "sorting.h"
#include "useful.h"

#include <cstdlib> 

// using mt199337 to generate random numbers.
long int generate_numbers( long int range );

// initial form for tests.
long int * generate_array( size_t size );

// free alocated memory.
void destroy_array( long int * array );

// linear increment to array size.
long int increase_array_control( long int max, long int samples, long int init_sample, int index );

void simple_shuffle( long int * first, long int * last );

void type_array( long int * array, int type, DATA data, long int max );

// main function to execute everything.
void execute_analysis( algorithms func, int algorithm_ID, long int max, long int samples, long int init_sample, DATA data );
#endif
