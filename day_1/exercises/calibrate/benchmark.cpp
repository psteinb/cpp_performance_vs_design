#include <cstdlib>
#include <iostream>
#include "calibrate.hpp"

int main(int argc, char *argv[])
{
  unsigned exponent = 9;
  if(argc>1)
    exponent = atoi(argv[1]);

  unsigned num_cells = 1 << exponent;
  std::cout << "using " << num_cells << "x" << num_cells << "x" << num_cells << " cells\n";
  instrument my_calo(num_cells);
  my_calo.calibrate();
  
  return 0;
}
