#include <iostream>
#include <chrono>
#include "virtual_inheritance.hpp"

int main(int argc, char* argv[])
{
  Direct *pdir, dir;
  pdir = &dir;

  const int start_count = 1<<30;
  int ia=start_count;
  auto t_start = std::chrono::high_resolution_clock::now();
  while( pdir->Perform(ia) );
  auto t_end = std::chrono::high_resolution_clock::now();
  double delta_direct = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()/1e3;
  std::cout << "Direct		" << delta_direct  <<" ms from " << start_count << " iterations\n";

  Derived drv;
  AbstrBase *ab = &drv;
  t_start = std::chrono::high_resolution_clock::now();
  while( ab->Perform(ia) );
  t_end = std::chrono::high_resolution_clock::now();
  delta_direct = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()/1e3;
  std::cout << "Virtual		" << delta_direct  <<" ms from " << start_count << " iterations\n";

  return 0;
}
