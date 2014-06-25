#define ACP_DESIGN_BY_POLICY_CPP
#include <iostream>
#include "static_array.hpp"

int main(int argc, char *argv[])
{
  std::cout << "An Introduction to Design by Policy and Friends!\n\n";
  
  static_array<int,1024> my_array;
  std::cout << "created a " << my_array.size() << " elements array\n";
  std::fill(my_array.begin(), my_array.end(),1);
  
  std::cout << "norm of the array: " << my_array.norm() << "\n";

  static_array<int,1024,EuclidNorm<int,size_t> > my_vector(3);
  std::cout << "norm of the euclidean array: " << my_vector.norm() << "\n";

  // std::cout << "norm of the euclidean vector: " << my_vector.norm() << "\n";

  
  return 0;
}
