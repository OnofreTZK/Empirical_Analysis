#include "sorting.h"

#include <iostream>
#include <iterator>

void variable( long int * first, long int * last )
{

    if( first == last )
    {
        return;
    }

    if( std::distance( first, last ) < 9 )
    {
        insertion( first, last );
    }

    long int * pivot = partition( first, last, last - 1 );
    variable( first, pivot);
    variable( pivot + 1, last );

}
