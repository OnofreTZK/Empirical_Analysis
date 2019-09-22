#include "sorting.h"

#include <iostream>
#include <iterator>
#include <cstdlib>

void copyiterator( long int * newfirst, long int * newlast, long int * first, long int * last )
{

    while( first != last  )
    {
        *newfirst = *first;
        //std::cout << *newfirst << ", ";

        newfirst++;

        first++;
    }

}



void merge( long int * first, long int * last, long int * half )
{
    int size1 = std::distance( first, half );
    int size2 = std::distance( half, last );

    long int subArray1[size1];
    long int subArray2[size2];
    long int mergedArray[std::distance(first, last)];


    copyiterator( subArray1, subArray1 + size1, first, half);
    copyiterator( subArray2, subArray2 + size2, half, last);

    int index1 = 0; // subArray1 index.
    int index2 = 0; // subArray2 index.
    int mergedindex = 0; // final array index

    while( mergedindex < std::distance( first, last ) )
    {
        if( size1 == 0 and size2 == 0 )
        {
            return;
        }
        else if( size1 == 0 )
        {
            while( index2 < size2 )
            {
                mergedArray[mergedindex] = subArray2[index2];
                mergedindex++;
                index2++;
            }
        }
        else if( size2 == 0 )
        {
            while( index1 < size1 )
            {
                mergedArray[mergedindex] = subArray1[index1];
                mergedindex++;
                index1++;
            }
        }
        else if( subArray1[index1] < subArray2[index2] )
        {
            mergedArray[mergedindex] = subArray1[index1];
            index1++;
            mergedindex++;
        }
        else if( subArray1[index1] > subArray2[index2] )
        {
            mergedArray[mergedindex] = subArray2[index2];
            index2++;
            mergedindex++;
        }
        else if( subArray1[index1] == subArray2[index2] )
        {
            mergedArray[mergedindex] = subArray1[index1];
            index1++;
            mergedindex++; 
            mergedArray[mergedindex] = subArray2[index2];
            index2++;
            mergedindex++;
        }
        else if( index1 == size1 )
        {
            while( index2 < size2 )
            {
                mergedArray[mergedindex] = subArray2[index2];
                mergedindex++;
                index2++;
            }
        }
        else if( index2 == size2 )
        {
            while( index1 < size1 )
            {
                mergedArray[mergedindex] = subArray1[index1];
                mergedindex++;
                index1++;
            }
        }
    }

    copyiterator( first, last, mergedArray, mergedArray + std::distance( first, last ) );
}


void mergesort( long int * first, long int * last )
{
    if( first == last )
    {
        return;
    }

    long int * half = first + std::distance( first, last )/2;

    mergesort( first, half );
    mergesort( half + 1, last );

    merge( first, last, half );
}
