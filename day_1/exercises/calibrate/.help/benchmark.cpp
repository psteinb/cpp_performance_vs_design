#include <cstdlib>
#include <iostream>
#include "calibrate.hpp"

int main(int argc, char *argv[])
{
  unsigned exponent = 9;
  if(argc>1)
    exponent = atoi(argv[1]);

  unsigned num_cells = 1 << exponent;
  unsigned long total = num_cells*num_cells*num_cells;
  std::cout << "using " << num_cells << "x" << num_cells << "x" << num_cells << " = "<< total <<" ("<< (float)total << ") cells\n";
  instrument my_calo(num_cells);
  
  float sum_raw = my_calo.sum();
  
  my_calo.calibrate();

  float sum_calibrate = my_calo.sum();
  
  std::cout << "raw       : " << sum_raw << "\n"
	    << "calibrated: " << sum_calibrate << "\n";
  
  return 0;
}
