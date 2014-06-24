#include <iostream>
#include <vector>

typedef std::vector<float> Matrix;

void MatrixSum(float const * _lhs, 
	       float const* _rhs, 
	       float* _result, size_t size){
  
  for(size_t i = 0;i<size;++i){
    _result[i] = _lhs[i] + _rhs[i];
  }
  
}

int main(int argc, char* argv[])
{

  
  static const size_t size = (1<<20);
  
  Matrix first(size);
  Matrix second(size);
  Matrix result(size);
  
  std::fill(first.begin(), first.end(),42);
  std::fill(second.begin(), second.end(),24);
  
  MatrixSum(&first[0], &second[0], &result[0], size);
  
  
  if(result[0]!=result[size/2] && result[size/2] != result[size-1])
    return 1;
  else
    return 0;
}
