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

    //array of sorting algorithms.
    algorithms array[8]{ quicksort,
                         selection
                       };
    DATA data;

    execute_analysis( array[0], 0, 1000, 50, atoi(argv[1]), data );

    return 0;
}
