#include "sorting.h"

#include <iterator>
#include <iostream>

void bubble( long int * first, long int * last, long int &count )
{

    long int * bubble = first;

    while( first != last )
    {
        while( bubble != last )
        {
            if( *first> *bubble )
            {   count++;
                std::iter_swap( first, bubble );
                count++;
            }
            bubble++;
            count += 2; //loop and pointer increment.
        }
        first++;
        bubble = first;
        count += 2; //loop and pointer increment.
    }

}
