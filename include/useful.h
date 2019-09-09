#ifndef USEFUL_H
#define USEFUL_H

#include <vector>

typedef void (*algorithms) ( long int * first, long int * last );

class DATA 
{
    private:
      std::vector< long int > time_data;
      std::vector< long int > samples_size;

    public:

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
