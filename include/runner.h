#ifndef RUNNER_H
#define RUNNER_H

#include "sorting.h"
#include "useful.h"

#include <cstdlib>

// using mt199337 to generate random numbers.
long int generate_numbers( long int range );

// initial form for tests.
long int * generate_array( long int max );

// "shuffling"
void random_array( long int *first, long int *last, long int max );

// descending sort
void descending_sorting( long int * first, long int * last );

// ascending sort
void ascending_sorting( long int * first, long int * last );

// partial sorting
void partial_sorting( long int * first, long int * last, int partial );

// linear increment to array size(PA).
long int increase_array_control( long int max, long int samples, long int init_sample, int index );

void print4test( long int * first, long int * last, long int count );

void printer( long int max );

// random array
void simple_shuffle( long int * first, long int * last, long int max );

// type sample selection
void type_array( long int * array, int type, DATA data, long int max );

// create file for plotting script
void create_data_file( DATA data, int algorithm_ID, int type );

// main function to execute everything.
void execute_analysis( algorithms func, int algorithm_ID, long int max, long int samples, long int init_sample, DATA data );
#endif
