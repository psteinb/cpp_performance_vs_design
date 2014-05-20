#define GENERATE_DATA_CPP
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <random>

namespace exercises {

static const size_t stack_size = 256*256*256;//32MB

void get_file_contents(const char *_filename, std::vector<unsigned short>& _payload)
{
  std::ifstream in(_filename, std::ios::in | std::ios::binary);
  std::string contents("");contents.reserve(stack_size*2);

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
  
  //the following line assumes that the image was written to disk 
  //using the same memory endianess than the architecture this is running on
  unsigned short* received = reinterpret_cast<unsigned short*>(&contents[0]);
  std::copy(received, received + received_elements, _payload.begin());
  
  
}

  void write_file_contents(const char *_filename, unsigned short* _payload, const size_t & _size)
{
  std::ofstream out(_filename, std::ios::out | std::ios::binary | std::ios::app);


  if(out.is_open()){
    char* buffer = reinterpret_cast<char*>(_payload);
    out.write(buffer, _size*2);
  }
  else
    {
      std::cerr << ">> problem opening file at: " << _filename << "\n";
    }
  
}


  bool stack_is_background_free( unsigned short* _data, const size_t& _size, const unsigned short& _threshold = 128){
  
  size_t num_pixels_above_threshold = 0;
  for(size_t index = 0;index< _size;++index){
    if(_data[index] > _threshold)
      num_pixels_above_threshold++;
  }
  
  return num_pixels_above_threshold == _size;
  }



  
  void add_noise(unsigned short* _data, const size_t& _size, const unsigned short& _mean = 64){

     std::random_device rd;
     std::mt19937 gen(rd());
     std::poisson_distribution<> d(_mean);
     unsigned short sample = 0;
     std::cout << "poisson mean: " << _mean << "\t";
     for(size_t i=0; i<_size; ++i) {
       sample = d(gen);
       if(i<32)
	 std::cout << " ["<< i <<"] :" << sample << "\t";
       _data[i] += sample;
     }
     std::cout<< "\n";
  }

  
  struct sphere {
  
    unsigned short intensity_;
    std::vector<size_t> center_;
    size_t radius_;
    size_t thickness_;

    explicit sphere(const size_t& _radius):
      intensity_(1<<15),
      center_(3,0),
      radius_(_radius),
      thickness_(3){}
    
    //we assume row-major format
    size_t draw(unsigned short* _data, const size_t& _size, const std::vector<size_t>& _dims){

      float distance_to_center = 0.f;
      int z_eff = 0;
      int y_eff = 0;
      int x_eff = 0;
      size_t index = 0;
      
      size_t pixels_touched = 0;
      
      for(int z = 0;z<_dims[2];++z){
	z_eff = z - _dims[2]/2 - center_[2]/2;
	
	for(int y = 0;y<_dims[1];++y){
	  y_eff = y - _dims[1]/2 - center_[1]/2;
	  
	  for(int x = 0;x<_dims[0];++x){
	    
	    x_eff = x - _dims[0]/2 - center_[0]/2;
	    
	    index = z*(_dims[2]*_dims[1]) + y*_dims[1] + x;
	    distance_to_center = std::sqrt(z_eff*z_eff + y_eff*y_eff + x_eff*x_eff);
	    if(distance_to_center > (radius_ - thickness_/2) && distance_to_center < (radius_ + thickness_/2)){
	      _data[index] += intensity_;
	      pixels_touched++;
	    }
	  }
	}
      }
 
      return pixels_touched;
    }

  };
  
  struct square {
  
    unsigned short intensity_;
    std::vector<size_t> center_;
    size_t base_length_;
    size_t thickness_;

    explicit square(const size_t& _length):
      intensity_(1<<15),
      center_(3,0),
      base_length_(_length),
      thickness_(3){}
    
    //we assume row-major format
    size_t draw(unsigned short* _data, const size_t& _size, const std::vector<size_t>& _dims){

      float distance_to_center = 0.f;
      int z_eff = 0;
      int y_eff = 0;
      int x_eff = 0;
      bool z_on_border = false;
      bool y_on_border = false;
      bool x_on_border = false;
      size_t index = 0;
      
      size_t pixels_touched = 0;
      
      for(int z = 0;z<_dims[2];++z){
	z_eff = std::abs(z - _dims[2]/2 - center_[2]/2);
	z_on_border = z_eff > (base_length_ - thickness_)/2 && z_eff < (base_length_ + thickness_)/2;
	
	for(int y = 0;y<_dims[1];++y){
	  y_eff = y - _dims[1]/2 - center_[1]/2;
	  y_on_border = y_eff > (base_length_ - thickness_)/2 && y_eff < (base_length_ + thickness_)/2;
	  
	  for(int x = 0;x<_dims[0];++x){
	    
	    x_eff = x - _dims[0]/2 - center_[0]/2;
	    x_on_border = x_eff > (base_length_ - thickness_)/2 && x_eff < (base_length_ + thickness_)/2;
	    
	    index = z*(_dims[1]*_dims[0]) + y*_dims[0] + x;

	    if(z_on_border || y_on_border || x_on_border){
	      _data[index] += intensity_;
	      pixels_touched++;
	    }
	  }
	}
      }
 
      return pixels_touched;
    }

  };
}

