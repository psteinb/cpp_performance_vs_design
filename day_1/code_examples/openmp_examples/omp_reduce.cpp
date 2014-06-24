
#include <iostream>
#include <omp.h>

int main(int argc, char *argv[])
{

  static const int size = 1 << 15;
  float a[size], b[size], result;
  static const int chunk = 10;
  result = 0.f;

  for (int i=0; i < size; i++)
    {
      a[i] = i * 1.0;
      b[i] = i * 2.0;
    }

#pragma omp parallel for default(shared) schedule(static,chunk) reduction(+:result)  
  for (int i=0; i < size; i++)
    result = result + (a[i] * b[i]);

  std::cout << "sum of " << size << " elements: " << result << "\n";

}
