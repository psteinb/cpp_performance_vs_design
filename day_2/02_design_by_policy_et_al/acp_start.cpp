#define ACP_DESIGN_BY_POLICY_CPP
#include <iostream>

int main(int argc, char *argv[])
{
  std::cout << "An Introduction to Design by Policy and Friends!\n\n";
  
  static_array<int,1024> my_array;
  
  std::fill(my_array.begin(), my_array.end(),1);
  
  std::cout << "created a " << my_array.size() << " elements static array\n";
  
  return 0;
}
