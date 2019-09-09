#include "runner.h"

#include <random>
#include <chrono>
#include <iostream>

long int generate_numbers( long int range )
{
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator ( seed1 );

    return generator()%range;
}

long int * generate_array( size_t size )
{
    long int * array = new long int [size];

    for ( int i = 0; i < size; i++ )
    {
        array[i] = generate_numbers(size); 
    }

    return array;
}

void destroy_array( long int * array )
{
    delete[] array;
}

long int increase_array_control( long int max, long int samples, long int init_sample, int index )
{
    //linear method.
    //calculating the 'r' of aritmetic progressiom formula.
    long int reason = ( max - init_sample )/ samples;

    return init_sample + ( index - 1 ) * reason;

}

void execute_analysis( algorithms func, int algorithm_ID, long int max, 
                       long int samples, long int init_sample, DATA data )
{
    // alocating the limit of the machine!
    long int *vet = generate_array( max );

    std::cout << "===Vet 1==\n\n"  << "[ ";
    for ( int i = 0; i < init_sample; i++ )
    {
        std::cout << vet[i] << " ";
    }
    std::cout << std::endl;

    func( &vet[0], vet + increase_array_control( max, samples, init_sample, 1) );
    std::cout << "\n\nO retorno da func é " <<  increase_array_control( max, samples, init_sample, 1) << "\n\n"; 
    std::cout << "===sorted===\n\n" <<"[ ";
    for ( int i = 0; i < init_sample; i++ )
    {
        std::cout << vet[i] << " ";
    }
    std::cout << std::endl;

    destroy_array( vet );
}
