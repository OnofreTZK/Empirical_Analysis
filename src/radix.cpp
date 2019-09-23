#include "sorting.h"

#include <iostream>
#include <iterator>

long int getMax( long int * first, long int * last, long int &count )
{
    long int maximum = *first;

    while( first < last )
    {
        if( maximum < *first )
        {
            maximum = *first;
            count++; // if
        }
        first++;
        count += 2; // while and increment.
    }

    return maximum;
}

void countingSort( long int * first, long int * last, long int digit, long int &count )
{
    long int size = std::distance( first, last );

    long int * output = new long int [size];

    long int cnt[10] = { 0 };

    long int * left = first;

    cnt[0] = 0;

    for( int i = 0; i < size; i++ )
    {
        cnt[ (*left/digit)%10 ]++;
        left++;
        count += 3; // increments and loop.

    }

    for( int i = 1; i < 10; i++ )
    {
        cnt[i] += cnt[i -1];
        count++;
    }

    left = last;

    for( int i = size - 1; i >= 0; i-- )
    {
        left--;
        output[ cnt[ (*left/digit)%10 ] - 1 ] = *left;
        cnt[ (*left/digit)%10 ]--;
        count += 3;

    }

    left = first;

    for( int i = 0; i < size; i++ )
    {
        *left = output[i];
        left++;
        count += 2;
    }

    delete[] output;

}

void radix( long int * first, long int * last, long int &count )
{
    long int maximum = getMax( first, last, count );

    for( long int digit = 1; maximum/digit > 0; digit *= 10 )
    {
        countingSort( first, last, digit, count );
        count++;
    }

}

