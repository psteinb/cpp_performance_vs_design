#include <iostream>
#include <vector>
#include "x86intrin.h"

typedef std::vector<float> Matrix;
#ifdef __SSE__
void MatrixSum(float const * _lhs, 
	       float const* _rhs, 
	       float* _result, size_t size){

  std::cout << "using intrinsic version\n";
  for(size_t i = 0;i<size;i+=4){
    __m128 lhs=_mm_load_ps(&_lhs[i]);
    __m128 rhs=_mm_load_ps(&_rhs[i]);
    __m128 res=_mm_add_ps(lhs,rhs);
    _mm_store_ps(&_result[i],res);
  }
  
}
#else
void MatrixSum(float const * _lhs, 
	       float const* _rhs, 
	       float* _result, size_t size){
  
  std::cout << "using standard version\n";
  for(size_t i = 0;i<size;++i){
    _result[i] = _lhs[i] + _rhs[i];
  }
  
}

#endif



int main(int argc, char* argv[])
{

  
  static const size_t size = (1<<20);
  
  Matrix first(size);
  Matrix second(size);
  Matrix result(size);
  
  std::fill(first.begin(), first.end(),42);
  std::fill(second.begin(), second.end(),24);
  
  MatrixSum(&first[0], &second[0], &result[0], size);
  
  
  if(result[0]!=result[size/2] && result[size/2] != result[size-1]){
     std::cout << "Failed.\n";
    return 1;
  }
  else{
    std::cout << "OK.\n";
    return 0;
  }
}
