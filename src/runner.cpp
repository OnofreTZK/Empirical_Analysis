#include "runner.h"

#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <array>

//=================================================================================================
//Generating a array with full random numbers
//================================================================================================
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
//=================================================================================================



//=================================================================================================
// Free memory
//=================================================================================================
void destroy_array( long int * array )
{
    delete[] array;
}
//=================================================================================================



//=================================================================================================
// Function to control the size increase in the range ( init_sample, max]
//=================================================================================================
long int increase_array_control( long int max, long int samples, long int init_sample, int index )
{
    //linear method.
    //calculating the 'r' of aritmetic progressiom formula.
    long int reason = ( max - init_sample )/ samples;

    return init_sample + ( index - 1 ) * reason;

}
//=================================================================================================



//=================================================================================================
//Function to shuffle
//=================================================================================================
void simple_shuffle( long int * first, long int * last )
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle( first, last, std::default_random_engine(seed) );
}
//=================================================================================================

void execute_analysis( algorithms func, int algorithm_ID, long int max, 
                       long int samples, long int init_sample, DATA data )
{

    long int * array = generate_array( max );

    for( int type = 0; type < 6; type++ )
    {
        switch( type )
        {
            case 0 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                break;
            case 1 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                simple_shuffle( array, array + max );
                //simple function to sort in non descending
                break;
            case 2 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                simple_shuffle( array, array + max );
                //simple function to sort in non ascending
                break;
            case 3 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                simple_shuffle( array, array + max );
                //simple function to sort 75%
                break;
            case 4 : 
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                simple_shuffle( array, array + max );
                //simple function to sort 50%.
                break;
            case 5 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                simple_shuffle( array, array + max );
                //simple function to sort 25%.
                break;
            default:
                std::cout << "\nThis code break the universe!\n";
        }
    } 
}
