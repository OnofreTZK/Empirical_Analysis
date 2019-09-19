#include "runner.h"

#include <iterator>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>

#define MAX 100000

int main(int argc, char *argv[])
{
    long int init_sample, samples;

    int algo1, algo2, algo3; // keep the code to sorting algorithms selected.

    DATA data; // class type to save time analyse.

    //array of sorting algorithms.
    algorithms array[8]{ quicksort,
                         selection
                       };

    //identify the name of algorithm.
    //std::vector< std::string > sort_ID{ "quick sort", "selection sort" };


    if( argc < 4 ) //verify minimal
    {
        std::cout << "\nToo few arguments!\n";
        printHelp();
        return EXIT_FAILURE;
    }
    else if( argc > 6 ) //verify max
    {
        std::cout << "\nToo many arguments! Please, choose only <3> sorting algorithms to analyse!\n";
        printHelp();
        return EXIT_FAILURE;
    }
    else if( atoi(argv[2]) < 25 or atoi(argv[2]) > 100 ) //verify samples range.
    {
        std::cout << "\nNumber of samples is out of range!\n";
        printHelp();
        return EXIT_FAILURE;
    }
    else if( argc == 4 )
    {
        init_sample = atoi(argv[1]);
        samples = atoi(argv[2]);
        algo1 = atoi(argv[3]);

        std::cout << "\n>>>Starting " << data.sort_ID[algo1] << " analysis\n";

        execute_analysis( array[algo1], algo1, MAX, samples, init_sample, data );

        return EXIT_SUCCESS;
    }
    else if( argc == 5 )
    {
        init_sample = atoi(argv[1]);
        samples = atoi(argv[2]);
        algo1 = atoi(argv[3]);
        algo2 = atoi(argv[4]);

        std::cout << "\n>>>Starting " << data.sort_ID[algo1] << " analysis\n";

        execute_analysis( array[algo1], algo1, MAX, samples, init_sample, data );

        std::cout << "\n>>>Starting " << data.sort_ID[algo2] << " analysis\n";

        execute_analysis( array[algo2], algo2, MAX, samples, init_sample, data );

        return EXIT_SUCCESS;
    }
    else if( argc == 6 )
    {
        init_sample = atoi(argv[1]);
        samples = atoi(argv[2]);
        algo1 = atoi(argv[3]);
        algo2 = atoi(argv[4]);
        algo3 = atoi(argv[5]);

        std::cout << "\n>>>Starting " << data.sort_ID[algo1] << " analysis\n";

        execute_analysis( array[algo1], algo1, MAX, samples, init_sample, data );

        std::cout << "\n>>>Starting " << data.sort_ID[algo2] << " analysis\n";

        execute_analysis( array[algo2], algo2, MAX, samples, init_sample, data );

        std::cout << "\n>>>Starting " << data.sort_ID[algo3] << " analysis\n";

        execute_analysis( array[algo3], algo3, MAX, samples, init_sample, data );

        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
