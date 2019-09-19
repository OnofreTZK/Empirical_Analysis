#ifndef USEFUL_H
#define USEFUL_H

#include <vector>
#include <string>
#include <fstream>

//pointer to function
typedef void (*algorithms) ( long int * first, long int * last );

//Help to guide user.
void printHelp();

class DATA 
{
    private:
      std::vector< double > time_data;
      std::vector< long int > samples_size;

    public:

      std::vector< std::string > sort_ID{ "quick sort",
                                          "selection sort" };

      std::vector< std::string > typesample{ "Full random",
                                             "non-descending order",
                                             "non-ascending order",
                                             "sorted: 75%",
                                             "sorted: 50%",
                                             "sorted: 25%" };



      void alocate_vectors( long int samples )
      {
          time_data.resize( samples );
          samples_size.resize( samples );
      };

      void set_values( long int sample, double timer, int index )
      {
          time_data[index] = timer;
          samples_size[index] = sample;
      }

      void get_data( std::ofstream * file )
      {
          for( size_t i = 0; i < time_data.size(); i++ )
          {
              *file << samples_size[i] << " " << time_data[i] << "\n";
          }
      }


};


#endif
