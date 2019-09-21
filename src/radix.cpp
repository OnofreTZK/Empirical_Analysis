#include "sorting.h"

#include <iostream>
#include <iterator>

long int getMax( long int * first, long int * last )
{
    long int maximum = *first;

    while( first < last )
    {
        if( maximum < *first )
        {
            maximum = *first;
        }
        first++;
    }

    return maximum;
}

void countingSort( long int * first, long int * last, long int digit )
{
    long int size = std::distance( first, last );

    long int * output = new long int [size];

    long int count[10] = { 0 };

    long int * left = first;

    count[0] = 0;

    for( int i = 0; i < size; i++ )
    {
        count[ (*left/digit)%10 ]++;
        left++;
    }

    for( int i = 1; i < 10; i++ )
    {
        count[i] += count[i -1];
    }

    left = last;

    for( int i = size - 1; i >= 0; i-- )
    {
        left--;
        output[ count[ (*left/digit)%10 ] - 1 ] = *left;
        count[ (*left/digit)%10 ]--;
    }

    left = first;

    for( int i = 0; i < size; i++ )
    {
        *left = output[i];
        left++;
    }

    delete[] output;

}

void radix( long int * first, long int * last )
{
    long int maximum = getMax( first, last );

    for( long int digit = 1; maximum/digit > 0; digit *= 10 )
    {
        countingSort( first, last, digit );
    }

}

