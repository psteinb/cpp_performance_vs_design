//compile: g++ -fopenmp omp_hello.cpp -o omp_hello
#include <iostream>
 
int main(void)
{
#pragma omp parallel
  std::cout << "Hello, world.\n";
  return 0;
}
