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

int main(int argc, char *argv[])
{
    long int MAX, init_sample, samples;

    int algo1, algo2, algo3; // keep the code to sorting algorithms selected.

    DATA data; // class type to save time analyse.

    //array of sorting algorithms.
    algorithms array[8]{ quicksort,
                         selection
                       };

    if( argc < 5 ) //verify minimal
    {
        std::cout << "\nToo few arguments!\n";
        printHelp();
        return EXIT_FAILURE;
    }
    else if( argc > 7 ) //verify max
    {
        std::cout << "\nToo many arguments! Please, choose only <3> sorting algorithms to analyse!\n";
        printHelp();
        return EXIT_FAILURE;
    }
    else if( atoi(argv[3]) < 25 or atoi(argv[3]) > 100 ) //verify samples range.
    {
        std::cout << "\nNumber of samples is out of range!\n";
        printHelp();
        return EXIT_FAILURE;
    }
    else if( argc == 5 )
    {
        MAX = atoi(argv[1]);
        init_sample = atoi(argv[2]);
        samples = atoi(argv[3]);
        algo1 = atoi(argv[4]);

        std::cout << "\n>>>Starting " << data.sort_ID[algo1] << " analysis\n";

        execute_analysis( array[algo1], algo1, MAX, samples, init_sample, data );

        //printer( MAX );

        return EXIT_SUCCESS;
    }
    else if( argc == 6 )
    {
        MAX = atoi(argv[1]);
        init_sample = atoi(argv[2]);
        samples = atoi(argv[3]);
        algo1 = atoi(argv[4]);
        algo2 = atoi(argv[5]);

        std::cout << "\n>>>Starting " << data.sort_ID[algo1] << " analysis\n";

        execute_analysis( array[algo1], algo1, MAX, samples, init_sample, data );

        std::cout << "\n>>>Starting " << data.sort_ID[algo2] << " analysis\n";

        execute_analysis( array[algo2], algo2, MAX, samples, init_sample, data );

        return EXIT_SUCCESS;
    }
    else if( argc == 7 )
    {
        MAX = atoi(argv[1]);
        init_sample = atoi(argv[2]);
        samples = atoi(argv[3]);
        algo1 = atoi(argv[4]);
        algo2 = atoi(argv[5]);
        algo3 = atoi(argv[6]);

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
