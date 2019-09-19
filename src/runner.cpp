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
    unsigned seed1 = 20000000;

    std::mt19937 generator ( seed1 );

    return generator()%range;
}


long int * generate_array( long int max )
{
    long int * array = new long int [max];

    for ( int i = 0; i < max; i++ )
    {
        array[i] = generate_numbers(max); 
    }

    return array;
}



void random_array( long int * first, long int * last, long int max)
{
    while( first != last )
    {
        *first = generate_numbers( max );

        first++;
    }
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

    return init_sample + (( index - 1 ) * reason);

}
//=================================================================================================



//=================================================================================================
//Function to select the type of array.
//=================================================================================================
void type_array( long int * array ,int type, DATA data, long int max )
{

        switch( type )
        {
            case 0 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                random_array( array, array + max, max );
                break;
            case 1 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                random_array( array, array + max, max );
                std::sort( array, array + max );
                break;
            case 2 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                random_array( array, array + max, max );
                std::sort( array, array + max );
                std::reverse( array, array + max );
                break;
            case 3 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                random_array( array, array + max, max );
                std::partial_sort( array, array + (long int)( 0.75*max ), array + max );
                break;
            case 4 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                random_array( array, array + max, max );
                std::partial_sort( array, array + (long int)( 0.50*max ), array + max );
                break;
            case 5 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                random_array( array, array + max, max );
                std::partial_sort( array, array + (long int)( 0.25*max ), array + max );
                break;
            default:
                std::cout << "\nHow?\n";
                break;
        }
}
//================================================================================================



void create_data_file( DATA data, int algorithm_ID, int type )
{
    std::ofstream file ("../data/"+data.sort_ID[algorithm_ID]+"_"+data.typesample[type]+".txt");

    data.get_data( &file );

    file.close();
}



void execute_analysis( algorithms func, int algorithm_ID, long int max, 
                       long int samples, long int init_sample, DATA data )
{
    //generate a full random array
    long int * array = generate_array( max );

    // Time Manipulation
    //=========================================================
    double arithmetic_mean;// necessary to progressive mean
    //=========================================================

    data.alocate_vectors( samples );

    for( int type = 0; type < 6; type++ )
    {

        for( int iter_samples = 0; iter_samples < samples; iter_samples++)
        {
            //type_array( array, type, data, max );

            arithmetic_mean = 0.0;

            for( int time_control = 0; time_control < 10; time_control++ )
            {
                type_array( array, type, data, max );

                // -- TIMER STARTS HERE --
                std::chrono::steady_clock::time_point START = std::chrono::steady_clock::now();
                func( array, array + increase_array_control( max, samples, init_sample, iter_samples + 1 ) );
                std::chrono::steady_clock::time_point STOP = std::chrono::steady_clock::now();
                // -- TIMER STOPS HERE --

                auto timer = (STOP - START);

                //calculating progressive mean.
                arithmetic_mean = arithmetic_mean + ( ( std::chrono::duration< double, std::milli > (timer).count() - arithmetic_mean )/(time_control+1) );

            }
            //get the sample size to put in data.
            long int sample = increase_array_control( max, samples, init_sample, iter_samples + 1 );

            //setting values in data.
            data.set_values( sample, arithmetic_mean, iter_samples );
        }

        //create file.
        create_data_file( data, algorithm_ID, type );

    }

    delete[] array;
}
