#define GENERATE_DATA_CPP
#include <iostream>
#include <sstream>
#include "utils.hpp"
#include <typeinfo>

template<typename T>
bool charPtr_as(char * _optarg, T& _result){

  std::istringstream instream;
  instream.str(_optarg);
  T meta;
  if( !(instream >> meta) ){
    std::cerr << __FILE__ << "\t unable to convert "<< _optarg << " to type " << typeid(_result).name() << std::endl;
    return false;
  }
  _result = meta;
  return true;
  
}


int main(int argc, char *argv[])
{
  if(argc<2 || argc>4){
    std::cerr << "usage: generate_data <num files> <path/to/output/file(s)|default:$PWD> \n";
    return 1;
  }
  
  int num_stacks = 0;
  charPtr_as<int>(argv[1], num_stacks);
  std::vector<unsigned short*> stacks(num_stacks);
  
  for(int i = 0;i<num_stacks;++i){
    stacks[i] = new unsigned short[exercises::stack_size];
    std::fill(stacks[i], stacks[i] + exercises::stack_size, 0);
  }
  
  std::vector<size_t> dims = {256, 256, 256};
  std::vector<size_t> center = {0, 0, 0};
  exercises::sphere central_sphere(64);
  exercises::square central_square(128);
  size_t sphere_num_pixels = 0;
  size_t square_num_pixels = 0;

  for(int i = 0;i < num_stacks;i+=2){
    
    exercises::add_noise(stacks[i], exercises::stack_size);

    center = {(i % 2)*32u, (i % 3)*16u, 0};
    central_sphere.center_ = center;
    sphere_num_pixels = central_sphere.draw(stacks[i], exercises::stack_size, dims);
    
    
    if(i+1 < num_stacks){
      exercises::add_noise(stacks[i+1], exercises::stack_size);

      center = {(i % 3)*32u, 0, (i % 3)*16u};
      central_square.center_ = center;
      square_num_pixels = central_square.draw(stacks[i+1], exercises::stack_size, dims);
      
    }
  }

  
  for(int i = 0;i<num_stacks;++i){
    std::string path(argc>2 ? argv[2] : "./generated.data");
    exercises::write_file_contents(path.c_str(), stacks[i], exercises::stack_size);
    delete [] stacks[i];
  }

}
