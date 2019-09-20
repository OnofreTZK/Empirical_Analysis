#include "sorting.h"

#include <iterator>
#include <iostream>

void bubble( long int * first, long int * last )
{
    long int * bubble = first;

    while( first != last )
    {
        while( bubble != last )
        {
            if( *first> *bubble )
            {
                std::iter_swap( first, bubble );
            }
            bubble++;
        }
        first++;
        bubble = first;
    }
}
