#include <iostream>
#include <chrono>
#include "stack.hpp"

int main(int argc, char* argv[])
{
  
  const int pixel_count_x = 256*argc; 
  const int pixel_count_y = 256*argc; 
  const int pixel_count_z = 256; 

  size_t memory_consumption_mbyte = pixel_count_x*pixel_count_y*pixel_count_z*4/(1<<20);

  flat_stack flat_first(pixel_count_x, pixel_count_y, pixel_count_z);
  flat_stack flat_second(pixel_count_x, pixel_count_y, pixel_count_z);
  flat_first.fill(42);
  flat_second.fill(41);
  
  double flat_l2norm = 0;
  auto t_start = std::chrono::high_resolution_clock::now();
  for(int i = 0;i<50;++i)
    flat_l2norm = flat_first.l2norm(flat_second);
  auto t_end = std::chrono::high_resolution_clock::now();
  double delta_flat = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()/1e3;
  std::cout << "flat		" << delta_flat  <<" s (l2norm: " << flat_l2norm << ", "<< memory_consumption_mbyte << " MB)\n";

  pixel_stack pixel_first(pixel_count_x, pixel_count_y, pixel_count_z);
  pixel_stack pixel_second(pixel_count_x, pixel_count_y, pixel_count_z);
  pixel_first.fill(44);
  pixel_second.fill(43);

  double pixel_l2norm = 0;
  t_start = std::chrono::high_resolution_clock::now();
  for(int i = 0;i<50;++i)
    pixel_l2norm = pixel_first.l2norm(pixel_second);
  t_end = std::chrono::high_resolution_clock::now();
  double delta_pixel = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count()/1e3;
  std::cout << "pixel		" << delta_pixel  <<" ms (l2norm: " << pixel_l2norm << ", "<< memory_consumption_mbyte << " MB)\n";

  return 0;
}
