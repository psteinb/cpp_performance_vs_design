#define REMOVE_BACKGROUND_CPP
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
// file to serve as a starting point

void get_file_contents(const char *_filename, std::vector<unsigned short>& _payload)
{
  std::ifstream in(_filename, std::ios::in | std::ios::binary);
  std::string contents("");
  // print file:
  if(in.is_open()){
    
    while (in.good()) {
      contents.push_back(in.get());
    }
  }
  else
    {
      std::cerr << ">> problem opening file at: " << _filename << "\n";
    }

  size_t received_elements = contents.size()/2;
  if(received_elements!=_payload.size())
    _payload.resize(received_elements);
  
  unsigned short* received = reinterpret_cast<unsigned short*>(&contents[0]);
  std::copy(received, received + received_elements, _payload.begin());
  
  
}


void remove_background( unsigned short* _data, const size_t& _size, const unsigned short& _background){
  
  for(size_t index = 0;index< _size;++index){
    if(_data[index] < _background)
      _data[index] = 0;
  }
  
}

bool stack_is_background_free( unsigned short* _data, const size_t& _size){
  
  size_t num_pixels_above_128 = 0;
  for(size_t index = 0;index< _size;++index){
    if(_data[index] > 128)
      num_pixels_above_128++;
  }
  
  return num_pixels_above_128 == _size;
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
