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
    if( argc < 4 )
    {
      std::cout << "create a helper.cpp !!!";
    }


    //array of sorting algorithms.
    algorithms array[8]{ quicksort,
                         selection
                       };
    DATA data;

    execute_analysis( array[0], 0, 10, 50, atoi(argv[1]), data );

    return 0;
}
