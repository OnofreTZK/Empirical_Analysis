#include "sorting.h"
#include <iterator>

void selection( long int *first, long int *last, long int &count )
{
    long int *selector{first}; // ponteiro para percorrer o vector.

    long int *menor{first}; // variavel temporária para armazenar o menor valor.

    while( first < last )
    {
        menor = first;
 
        while( selector != last )
        {
            if( *selector < *menor )
            {
                menor = selector;
                count++; // if
            }

            selector++;
            count += 2; // while and increment.
        }

        std::iter_swap( first++, menor);
        count += 3; // while, swap and increment.

        selector = first;
    } 
}
