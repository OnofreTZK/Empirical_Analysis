#include "sorting.h"
#include <iterator> 


long int * partition( long int *first, long int *last, long int * pivot, long int &count )
{
    long int *slow = first;
    long int *fast = first;

    std::iter_swap( pivot, last - 1 );
    count++;

    while( fast < last )
    {
        if(  *fast < *(last-1)  )
        {
            std::iter_swap( slow, fast );
            slow++;
            count += 3; // if, swap e incremento
        }

        fast++;
        count += 2; // while and pointer
    }

    std::iter_swap( slow, last - 1 );
    count++;

    return slow;
}


void quicksort( long int * first, long int * last, long int &count )
{
    count++;

    if( first == last )
    {
        count++;
        return;
    }

    long int * pivot = partition( first, last, last - 1, count );
    quicksort( first, pivot, count);
    quicksort( pivot + 1, last, count );

}
