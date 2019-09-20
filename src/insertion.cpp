#include "sorting.h"

#include <iterator>
#include <iostream>

void insertion( long int * first, long int * last )
{
    long int * fast = first;
    long int * slow = fast;

    while( fast != last - 1 )
    {

        if( *fast > *(fast + 1) )
        {
            std::iter_swap( fast, fast + 1 );
            slow = fast;
            fast++;

            while( slow != first )
            {
                if( *slow < *(slow - 1) )
                {
                    std::iter_swap( slow, slow - 1 );
                    slow--;
                }
                else if( *slow == *(slow - 1) )
                {
                    slow--;
                }
                else if( *slow > *(slow - 1) )
                {
                    break;
                }
            }

        }
        else if( *fast < *(fast + 1) )
        {
            fast++;
        }
        else if( *fast == *(fast + 1) )
        {
            fast++;
        }
    }
}
