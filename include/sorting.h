#ifndef SRTG_H
#define SRTG_H

long int * partition( long int *first, long int *last, long int * pivot );

void quicksort( long int * first, long int * last );

void selection( long int * first , long int * last );

void insertion( long int * first, long int * last );

void bubble( long int * first, long int * last );

long int getMax( long int * first, long int * last );

void countingSort( long int * first, long int * last );

void radix( long int * first, long int * last );

void merge( long int * l_first, long int * l_last,
            long int * r_first, long int * r_last,
            long int * a_first );

void copyiterator( long int * newfirst, long int * newlast,
                   long int * first );

void mergesort( long int * first, long int * last );

void shell( long int * first, long int * last );

#endif
