#include "sorting.h"

#include <iostream>
#include <iterator>
#include <cstdlib>
#include <math.h>

void merge(long int *first, long int *half, long int *last, long int &count) {
    long int tamTotal = std::distance(first, last);
    long int *newThing = new long int[tamTotal];

    long int *slow = first;
    long int *fast = half;

    for(int i = 0; i < tamTotal; i++) {
        if(slow >= half && fast >= last) {
           count++; 
           break;
        } else if(slow == half || fast == last) {
            count++;
            if(slow == half) {
                count++;
                for( int j = i; j < tamTotal; j++ ) {
                    newThing[j] = *fast++;
                }
                break;
            } else if(fast == last) {
                count++;
                for( int j = i; j < tamTotal; j++ ) {
                    newThing[j] = *slow++;
                }
                break;
            }
        } else {
            count++;
            if( *slow < *fast ) {
                count++;
                newThing[i] = *slow++;
            } else {
                count++;
                newThing[i] = *fast++;
            }
        }
    }

    // passa resultados
    for(int i = 0; i < tamTotal; i++) {
        *(first+i) = newThing[i];
    }

    delete[] newThing;
}

void mergesort( long int * first, long int * last, long int &count ) {
    auto tamanho = std::distance(first, last);

    if( first == last || tamanho <= 1 ) 
    {
        count++; 
        return; 
    } // empty array

    // half size
    long int *half = first + int(floor(tamanho/2));


    mergesort(first, half, count);
    mergesort(half, last, count);

    merge(first, half, last, count);
}



