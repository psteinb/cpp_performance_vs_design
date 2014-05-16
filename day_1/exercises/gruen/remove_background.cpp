#define ACP_TEST_CPP
#include <iostream>
#include <fstream>
// file to serve as a starting point

void get_file_contents(const char *_filename, std::vector<unsigned short>& _payload)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  std::string contents("");
  // print file:
  if(in.is_open()){
    
    while (in.good()) {
      contents.push_back(in.get());
    }
  }
  else
    {
      std::cerr << ">> problem opening file at: " << filename << "\n";
    }

  size_t received_elements = contents.size()/2;
  if(received_elements!=_payload.size())
    _payload.resize(received_elements);
  
  unsigned short* received = reinterpret_cast<unsigned short*>(&contents[0]);
  std::copy(received, received + received_elements, _payload.begin());
  
  
}

int main(int argc, char *argv[])
{
  if(argc!=2){
    std::cerr << "usage: remove_background <path/to/input/file>\n";
    return 1;
  }

  static const size_t stack_size = 256*256*128;//16MB
  std::vector<unsigned short> all_stacks;
  
  get_file_contents(argv[1], all_stacks);

  size_t stacks_received = 0;
  if(all_stacks.size() % stack_size != 0)
    std::cout << "received mismatching number of elements, proceed with care\n";
  stacks_received = all_stacks.size() / stack_size;
  
  
  return 0;
}
