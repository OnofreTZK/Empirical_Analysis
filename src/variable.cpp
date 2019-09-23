#include "sorting.h"

#include <iostream>
#include <iterator>

void variable( long int * first, long int * last, long int &count )
{

    if( first == last )
    {
        count++; // if.
        return;
    }

    if( std::distance( first, last ) < 9 )
    {
        count++; // if
        insertion( first, last, count );
    }

    long int * pivot = partition( first, last, last - 1, count );
    variable( first, pivot, count);
    variable( pivot + 1, last, count );

}
