#include "runner.h"
#include <random>
#include <chrono>
long int generate_numbers()
{
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator ( seed1 );

    return generator()%100; // 100 is temporary.
}

long int * generate_array( size_t size )
{
    long int * array = new long int [size];

    for ( int i = 0; i < size; i++ )
    {
        array[i] = generate_numbers(); 
    }

    return array;
}
