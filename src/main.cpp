#include "runner.h"
#include "sorting.h"
#include "useful.h"

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

    //array of sorting algorithms.
    algorithms array{ quicksort,
                      selection
                    };

    long int *vet1 = generate_array(atoi(argv[1]));

    std::cout << "===Vet 1==\n\n"  << "[ ";
    for ( int i = 0; i < atoi(argv[1]); i++ )
    {
        std::cout << vet1[i] << " ";
    }
    std::cout << std::endl;

    array[1]( vet1, vet1 + atoi(argv[1]) );

    std::cout << "===selection===\n\n" <<"[ ";
    for ( int i = 0; i < atoi(argv[1]); i++ )
    {
        std::cout << vet1[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
