#include "sorting.h"
#include <iterator> 


long int * partition( long int *first, long int *last, long int * pivot )
{
    long int *slow = first;
    long int *fast = first;

    std::iter_swap( pivot, last - 1 );

    while( fast < last )
    {
        if(  *fast < *pivot  )
        {
            std::iter_swap( slow, fast );
            slow++;
        }

        fast++; // fast always will increase.
    }

    if( slow != last ) //pivot stands in last and need to swap with slow.
    {
        std::iter_swap( slow , last - 1);
    }
    return slow; //returns pivot final position.
 }


void quicksort( long int * first, long int * last )
{
    long int *pivot = partition( first, last, last - 1 ); 

     if( first == last )
     {
         return;
     }

     quicksort( first, partition( first, last, pivot ) );
     quicksort( partition( pivot + 1, last, last - 1 ), last );

}
