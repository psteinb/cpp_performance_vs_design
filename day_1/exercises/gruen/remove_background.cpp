#define REMOVE_BACKGROUND_CPP
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

#include "utils.hpp"


void remove_background( unsigned short* _data, const size_t& _size, const unsigned short& _background){
  
  for(size_t index = 0;index< _size;++index){
    if(_data[index] < _background)
      _data[index] = 0;
  }
  
}



int main(int argc, char *argv[])
{
  if(argc!=2){
    std::cerr << "usage: remove_background <path/to/input/file>\n";
    return 1;
  }

  
  std::vector<unsigned short> all_stacks;
  
  exercises::get_file_contents(argv[1], all_stacks);

  size_t stacks_received = 0;
  if(all_stacks.size() % exercises::stack_size != 0)
    std::cout << "received mismatching number of elements, proceed with care\n";
  stacks_received = all_stacks.size() / exercises::stack_size;

  ///////////////////////////////////////////////////////////////////////////////
  // BOOTSTRAP DATA
  //we assume we have received 50 image stacks to make the app cpu-bound
  //that will require exercises::stack_size*2*50 Byte RAM
  static const size_t num_stacks_received = 50;
  std::vector<unsigned short*> stacks(num_stacks_received);
  unsigned short* begin = 0;
  unsigned short* end = 0;
  for(size_t stack_idx = 0;stack_idx<(num_stacks_received);++stack_idx){
    
    stacks[stack_idx] = new unsigned short[exercises::stack_size];

    begin = &all_stacks[(stack_idx % stacks_received)*exercises::stack_size];
    end = begin + exercises::stack_size;
    
    std::copy(begin, end, stacks[stack_idx]);

  }

  ///////////////////////////////////////////////////////////////////////////////
  //CPU-BOUND TASK
  const unsigned short threshold = 128;
  //insert timer start
  for(size_t stack_idx = 0;stack_idx<(num_stacks_received);++stack_idx){
    remove_background(stacks[stack_idx], exercises::stack_size, threshold);
  }
  //insert timer end

  ///////////////////////////////////////////////////////////////////////////////
  //CHECKSUM TEST GOES HERE
  size_t num_stacks_complying = 0;
  for(size_t stack_idx = 0;stack_idx<(num_stacks_received);++stack_idx){
    if(exercises::stack_is_background_free(stacks[stack_idx], exercises::stack_size))
      num_stacks_complying++;
  }
  std::cout << num_stacks_complying << "/" << num_stacks_received << " have no background\n";
  ///////////////////////////////////////////////////////////////////////////////
  //clean-up
  for(size_t stack_idx = 0;stack_idx<(num_stacks_received);++stack_idx){
    delete [] stacks[stack_idx];
  }
  return 0;
}
