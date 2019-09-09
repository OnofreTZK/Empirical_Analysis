#include "sorting.h"
#include <iterator>

void selection( long int *first, long int *last )
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
            }

            selector++;
        }

        std::iter_swap( first++, menor);

        selector = first;
    } 
}
