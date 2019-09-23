#include "sorting.h"

#include <iterator>
#include <iostream>

void insertion( long int * first, long int * last, long int &count )
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

            count += 3; // if, swap and pointer increment.

            while( slow != first )
            {
                if( *slow < *(slow - 1) )
                {
                    std::iter_swap( slow, slow - 1 );
                    slow--;
                    count += 3; // if, swap and pointer decrement.
                }
                else if( *slow == *(slow - 1) )
                {
                    slow--;
                    count += 2; // if and pointer decrement
                }
                else if( *slow > *(slow - 1) )
                {
                    count++; // if.
                    break;
                }

                count++; // while.
            }

        }
        else if( *fast < *(fast + 1) )
        {
            fast++;
            count += 2; // if and pointer increment.
        }
        else if( *fast == *(fast + 1) )
        {
            fast++;
            count += 2; // if and pointer increment.
        }

        count++; // while
    }
}
