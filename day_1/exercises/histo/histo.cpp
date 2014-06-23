#include <vector>
#include <iostream>
#include <random>
#include <cstdlib>

struct hist
{

  float start;
  float stop;
  size_t len;
  unsigned long entries;
  

  std::vector<float> data;
  std::vector<float> lo_bin_borders;
  std::vector<float> hi_bin_borders;

  hist(float _start, float _stop, size_t _len = 50):
    start(_start),
    stop(_stop),
    len(_len),
    entries(0),
    data(_len,0),
    lo_bin_borders(_len),
    hi_bin_borders(_len)
  {
    float bin_width = (stop - start)/_len;
    for(size_t i = 0;i<_len;++i){
      lo_bin_borders[i] = start + i*bin_width;
      hi_bin_borders[i] = start + (i+1)*bin_width;
    }
  }

  void fill(const float& _value){
    if(_value<stop && _value>start){
      size_t found_bin = len+1;
      for(size_t i = 0;i<len;++i){
	if(_value >= lo_bin_borders[i] && _value < hi_bin_borders[i]){
	  found_bin = i;
	  break;
	}
      }
      
      if(found_bin<len){
	data[found_bin]+=1;
	entries++;
      }
    }
  }

  void print(const size_t& _modulus=0){
        
    if(_modulus){
      float sum = 0.f;
      size_t last_bin_index = 0;
      for(size_t i = 0;i<len;++i){
	if(i % _modulus == 0 || i == len-1){
	  std::cout << last_bin_index << " - " << i << ":\t" << sum << "\n";
	  sum = 0.f;
	  last_bin_index = i +1;
	}
	else
	  sum += data[i];
      }

    }else{
      for(size_t i = 0;i<len;++i){

	std::cout << i << ":\t" << data[i] << "\n";
	
      }
    }
    
    
  }

  size_t integral(){
    float sum = 0;
    for(size_t i = 0;i<len;++i){
      sum+=data[i];
    }
    return sum;
  }
  

};

int main(int argc, char *argv[])
{

  const size_t upper_limit = 1 << 14;
  size_t exponent = 16;
  if(argc>1)
    exponent = atoi(argv[1]);
  const size_t num_iterations = 1 << exponent;
  const size_t binning = 1024*32;

  
  hist benchmark_me(0, upper_limit , binning);
  float poisson_lamda = upper_limit/4;
  std::cout << num_iterations <<" iterations of Poisson PDF (lambda = "<< poisson_lamda 
	    <<") recorded by histo (start="<< 0
	    <<",stop="<< upper_limit 
	    <<",n_bins="<< binning <<")\n";
  
  std::random_device rd;
  std::mt19937 gen(rd());
  std::poisson_distribution<> pdf(poisson_lamda);

  float bootstrap_pdf[1024];
  for(size_t i = 0;i<1024;++i){
    bootstrap_pdf[i] = pdf(gen);
  }

  for(size_t i = 0;i<num_iterations;++i){
    benchmark_me.fill(bootstrap_pdf[i % 1024]);
  }
  
  benchmark_me.print(binning/32);
  std::cout << "histogram recorded " << benchmark_me.entries << " entries\n";
  return 0;
}
