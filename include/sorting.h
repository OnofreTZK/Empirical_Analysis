#ifndef SRTG_H
#define SRTG_H

long int * partition( long int *first, long int *last, long int * pivot, long int &count );

void quicksort( long int * first, long int * last, long int &count );

void selection( long int * first , long int * last, long int &count );

void insertion( long int * first, long int * last, long int &count );

void bubble( long int * first, long int * last, long int &count );

long int getMax( long int * first, long int * last, long int &count );

void countingSort( long int * first, long int * last, long int &count );

void radix( long int * first, long int * last, long int &count );

void merge( long int * first, long int * last, long int * half, long int &count );

void copyiterator( long int * newfirst, long int * newlast,
                   long int * first, long int * last );

void mergesort( long int * first, long int * last, long int &count );

void shell( long int * first, long int * last, long int &count );

void variable( long int * first, long int * last, long int &count );

#endif
