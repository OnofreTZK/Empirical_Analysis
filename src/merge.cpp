#include "sorting.h"

#include <iostream>
#include <iterator>
#include <cstdlib>

void merge( long int *l_first, long int * l_last, // [l_first; l_last)
            long int *r_first, long int * r_last, // [r_first; r_last)
            long int *a_first )
{

   long int * a_last = a_first + ( std::distance( l_first, l_last ) ) + ( std::distance( r_first, r_last ) );

    if( ( l_first == l_last ) and ( r_first == r_last ) )
    {
        return;
    }
    else if( l_first == l_last )
    {
        while( r_first != r_last )
        {
            *a_first = *r_first;
            a_first++;
            r_first++;
        }
    }
    else if( r_first == r_last )
    { 
        while( l_first != l_last )
        {
            *a_first = *l_first;
            a_first++;
            l_first++;
        }
    }

    while( a_first != a_last )
    {
        if( r_first == r_last )
        { 
             *a_first = *l_first;
             a_first++;
             l_first++;
        }
        else if( l_first == l_last )
        {
            *a_first = *r_first;
            a_first++;
            r_first++;
        }
        else if(  *l_first < *r_first  )
        {
            *a_first = *l_first;
            l_first++;
            a_first++;
        }
        else if(  *r_first < *l_first  )
        {
            *a_first = *r_first;
            r_first++;
            a_first++;
        }
        else if( *l_first == *r_first )
        {
            *a_first = *l_first;
            a_first++;
            l_first++;
            *a_first = *r_first;
            a_first++;
            r_first++;
        }
     }
}



void copyiterator( long int * newfirst, long int * newlast, long int * first )
{

    while( newfirst < newlast )
    {
        //std::cout << "\n first = "<< *first << "\n"; 
        *newfirst = *first;
        std::cout << *newfirst << ", ";

        newfirst++;

        first++;
    }

    std::cout << std::endl;

}



void mergesort( long int * first, long int * last )
{

    if( first < last )
    {

        int half_size = std::distance( first, last)/2;
        //std::cout << "\n half size = " << half_size << "\n";
        long int * half = first + half_size;
        long int * newfirst = new long int [half_size];
        long int * newfirst2 = new long int[half_size];

        copyiterator( newfirst, newfirst + half_size, first );
        copyiterator( newfirst2, newfirst2 + half_size, half );

        mergesort( first, half );
        mergesort( half + 1, last );

        merge( newfirst, newfirst + half_size,
               newfirst2 , newfirst2 + half_size,
               first );

        delete[] newfirst;
        delete[] newfirst2;
    }

}
