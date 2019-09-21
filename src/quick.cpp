#include "sorting.h"
#include <iterator> 


long int * partition( long int *first, long int *last, long int * pivot )
{
    long int *slow = first;
    long int *fast = first;

    std::iter_swap( pivot, last - 1 );

    while( fast < last )
    {
        if(  *fast < *(last-1)  )
        {
            std::iter_swap( slow, fast );
            slow++;
        }

        fast++;
    }

    std::iter_swap( slow, last - 1 );

    return slow;
}


void quicksort( long int * first, long int * last )
{

    if( first == last )
    {
        return;
    }

    long int * pivot = partition( first, last, last - 1 );
    quicksort( first, pivot/* partition( first, pivot, pivot - 1 ) */);
    quicksort( /*partition( pivot + 1, last, last - 1 )*/pivot + 1, last );

}
