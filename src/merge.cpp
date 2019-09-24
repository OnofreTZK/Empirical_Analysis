#include "sorting.h"

#include <iostream>
#include <iterator>
#include <cstdlib>
#include <math.h>

void printV(std::string desc, long int *first, long int *last) {
    std::cout << desc << " [ ";
    for( long int *it = first; it < last; it++ ) {
        std::cout << *it << " ";
    }
    std::cout << "]\n";
}

void merge(long int *first, long int *half, long int *last, long int &count) {
    long int tamTotal = std::distance(first, last);
    long int *newThing = new long int[tamTotal];

    long int *slow = first;
    long int *fast = half;

    for(int i = 0; i < tamTotal; i++) {
        if(slow >= half && fast >= last) {
            break;
        } else if(slow == half || fast == last) {
            if(slow == half) {
                for( int j = i; j < tamTotal; j++ ) {
                    newThing[j] = *fast++;
                }
                break;
            } else if(fast == last) {
                for( int j = i; j < tamTotal; j++ ) {
                    newThing[j] = *slow++;
                }
                break;
            }
        } else {
            if( *slow < *fast ) {
                newThing[i] = *slow++;
            } else {
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

    if( first == last || tamanho <= 1 ) { return; } // vetor vazio
    printf("------------------------------------------------------------------------------\n");
    printV("> [mergesort] entire:", first, last);

    // printf("TAMANHO: %li\n", tamanho);

    // divisao elemento central:
    long int *half = first + int(floor(tamanho/2));
    // printf("HALF: %li\n\n", *half);

    printV("\t>> [mergesort] 1º half:", first, half);
    printV("\t>> [mergesort] 2º half:", half, last);
    // recurssão
    mergesort(first, half, count);
    mergesort(half, last, count);

    merge(first, half, last, count);
}



