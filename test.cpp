#include <iostream> 
#include <cstdlib>

int main(int argc, char *argv[])
{

    long int *pointer = new long int [atoi(argv[1])];

    std::cout << "\n>>> Alocado com sucesso usando " << argv[1] << std::endl; 

    return 0;
}
