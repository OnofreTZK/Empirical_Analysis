#ifndef USEFUL_H
#define USEFUL_H

#include <vector>
#include <string>

typedef void (*algorithms) ( long int * first, long int * last );

class DATA 
{
    private:
      std::vector< long int > time_data;
      std::vector< long int > samples_size;

    public:

      std::vector< std::string > typesample{ "Full random array",
                                             "Array in non-descending order",
                                             "Array in non-ascending order",
                                             "75/100 sorted array",
                                             "50/100 sorted array",
                                             "25/100 sorted array" };



      void alocate_vectors( long int samples )
      {
          time_data.resize( samples );
          samples_size.resize( samples );
      };

      void set_values( long int sample, long int time, int index )
      {
          time_data[index] = time;
          samples_size[index] = sample;
      }


};


#endif
