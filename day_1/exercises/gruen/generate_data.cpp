#define GENERATE_DATA_CPP
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

void write_file_contents(const char *_filename, const std::vector<unsigned short>& _payload)
{
  std::ofstream out(_filename, std::ios::out | std::ios::binary | std::ios::app);


  if(out.is_open()){
    
    for(size_t index = 0;index < _payload.size();++index)
      out << _payload[index];

  }
  else
    {
      std::cerr << ">> problem opening file at: " << _filename << "\n";
    }
  
}



int main(int argc, char *argv[])
{
  if(argc!=2){
    std::cerr << "usage: remove_background <path/to/input/file>\n";
    return 1;
  }

  static const size_t stack_size = 256*256*256;//32MB
  std::vector<unsigned short> all_stacks;
  
  get_file_contents(argv[1], all_stacks);

  size_t stacks_received = 0;
  if(all_stacks.size() % stack_size != 0)
    std::cout << "received mismatching number of elements, proceed with care\n";
  stacks_received = all_stacks.size() / stack_size;
  
  //we assume we have received 50 image stacks to make the app cpu-bound
  //that will require stack_size*2*50 Byte RAM
  static const size_t num_stacks_received = 50;
  std::vector<unsigned short*> stacks(num_stacks_received);
  unsigned short* begin = 0;
  unsigned short* end = 0;
  for(size_t stack_idx = 0;stack_idx<(num_stacks_received);++stack_idx){
    
    stacks[stack_idx] = new unsigned short[stack_size];

    begin = &all_stacks[(stack_idx % stacks_received)*stack_size];
    end = begin + stack_size;
    
    std::copy(begin, end, stacks[stack_idx]);

  }

  ///////////////////////////////////////////////////////////////////////////////
  //CPU-BOUND TASK
  const unsigned short threshold = 128;
  //insert timer start
  for(size_t stack_idx = 0;stack_idx<(num_stacks_received);++stack_idx){
    remove_background(stacks[stack_idx], stack_size, threshold);
  }
  //insert timer end

  ///////////////////////////////////////////////////////////////////////////////
  //CHECKSUM TEST GOES HERE
  size_t num_stacks_complying = 0;
  for(size_t stack_idx = 0;stack_idx<(num_stacks_received);++stack_idx){
    if(stack_is_background_free(stacks[stack_idx], stack_size))
      num_stacks_complying++;
  }
  
  ///////////////////////////////////////////////////////////////////////////////
  //clean-up
  for(size_t stack_idx = 0;stack_idx<(num_stacks_received);++stack_idx){
    delete [] stacks[stack_idx];
  }
  return 0;
}
