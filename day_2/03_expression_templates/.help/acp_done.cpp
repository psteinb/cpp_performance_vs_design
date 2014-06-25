#define ACP_TEST_CPP
#include <iostream>
#include <cassert>
#include "static_array.hpp"
// file to serve as a starting point

int main(int argc, char *argv[])
{
  std::cout << "Expression Templates!\n";

  static_array<int,1024> first(1);
  static_array<int,1024> second(2);
  static_array<int,1024> result = first + second;

  std::cout << "norm of first is " << first.norm() << "\n";
  std::cout << "norm of second is " << second.norm() << "\n";
  std::cout << "norm of first + second is " << result.norm() << "\n";

  assert(result.norm() > first.norm());
 
  return 0;
}
