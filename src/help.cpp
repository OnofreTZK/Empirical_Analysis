#include "useful.h"

#include <iostream>

void printHelp()
{
    std::cout << "\nUse the following format: " 
              << "\n\n\t\x1b[92m<executable>\x1b[0m <array_max_size> <initial_sample_size> <number_of_samples> <algorithms>\n\n"
              << "\x1b[96m<number_of_samples>\x1b[0m must be in range: [25, 100).\n\n";
}
