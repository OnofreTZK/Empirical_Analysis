#include "sorting.h"

#include <iostream>
#include <iterator>

void shell( long int * first, long int * last )
{
    long int size = std::distance( first, last );

    long int * array_aux = new long int[size];

    copyiterator( array_aux, array_aux + size, first );

    for( int gap = size/2; gap > 0; gap /= 2 )
    {
        for( int i = gap; i < size; i++ )
        {
            long int aux = array_aux[i];

            int j;

            for( j = i; j >= gap && array_aux[j - gap] > aux; j -= gap )
            {
                array_aux[j] = array_aux[j - gap];
            }

            array_aux[j] = aux;

        }

    }

    copyiterator( first, last, array_aux );
}
