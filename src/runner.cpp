#include "runner.h"

#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <array>

//=================================================================================================
//Generating array
//=================================================================================================
long int generate_numbers( long int range )
{ 
      //auto seed = 12345678;

      std::random_device seed;

      std::mt19937_64 gen( seed() );

      std::uniform_int_distribution<long int> distr(0, range);

      return distr( gen );
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
//================================================================================================



//================================================================================================
// Fake shuffle
//================================================================================================
void random_array( long int * first, long int * last, long int max)
{
    while( first != last )
    {
        *first = generate_numbers( max );

        first++;
    }
}
//================================================================================================



//================================================================================================
// "Special" sorts
//================================================================================================
void descending_sorting( long int * first, long int * last )
{
    long int iterator = std::distance( first, last );

    while ( last != first )
    {
        *first = iterator;

        iterator--;
        first++;
    }
}



void ascending_sorting( long int * first, long int * last )
{
    long int iterator = 0;

    while( first != last )
    {
        *first = iterator + 1;

        iterator++;
        first++;
    }
}



void partial_sorting( long int * first, long int * last, int partial )
{ 

    double percent = (double) partial/100;

    double distance = (double) std::distance( first, last ) * percent;

    long int * unsort = first + (int) distance;

    int count = 0;
    while( count < distance )
    {

        std::iter_swap( first, unsort );

        first++;
        unsort--;

        count++;
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
                ascending_sorting( array, array + max );
                break;
            case 2 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                descending_sorting( array, array + max );
                break;
            case 3 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                ascending_sorting( array, array + max );
                partial_sorting( array, array + max, 25 );
                break;
            case 4 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                ascending_sorting( array, array + max );
                partial_sorting( array, array + max, 50);
                break;
            case 5 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                ascending_sorting( array, array + max );
                partial_sorting( array, array + max, 75 );
                break;
            default:
                std::cout << "\nHow?\n";
                break;
        }
}
//================================================================================================


//================================================================================================
// Create file with samples size and time measures.
//================================================================================================
void create_data_file( DATA data, int algorithm_ID, int type )
{
    std::ofstream file ("../data/"+data.sort_ID[algorithm_ID]+"_"+data.typesample[type]+".txt");

    data.get_data( &file );

    file.close();
}
//================================================================================================



void print4test( long int * first, long int * last )
{

    std::cout << "\n[ ";
    while( first != last )
    {
        std::cout << *first << ", ";

        first++;
    }
    std::cout << "]\n";
}



void printer( long int max )
{
    long int * arraytest = generate_array( max );

    print4test( arraytest, arraytest + max );

    variable( arraytest, arraytest + max );

    print4test( arraytest, arraytest + max );

    delete[] arraytest;
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
