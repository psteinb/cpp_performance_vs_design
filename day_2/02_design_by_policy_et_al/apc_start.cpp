#define ACP_DESIGN_BY_POLICY_CPP
#include <iostream>
#include <cmath>

template<typename T>
struct EuclideanNorm {

  T calculate( T* _begin, T* _end){
    
    T value = 0;
    T* temp = _begin;
    for(;temp!=_end;++temp){
      value += (*temp)*(*temp);
    }

    return std::sqrt(value);
  }


};

template <typename T, 
	  unsigned Length, 
	  typename NormPolicy = EuclideanNorm<T> >
struct static_array : public NormPolicy {

  T* data_;
  
  static_array():
    data_(new T[Length]){
    
  }

  static_array(const static_array& _rhs):
    data_(0){
    
    data_ = new T[Length];
    
    const T* begin = &_rhs.data_[0];
    const T* end = begin + Length;
    
    std::copy(begin, end, data_);
    
  }

  static_array& operator=(const static_array& _rhs){
    
    if(this!=&_rhs){
        const T* begin = &_rhs.data_[0];
	const T* end = begin + Length;
	std::copy(begin, end, data_);
    }
    
    return *this;
  }

  size_t size() const {
    return Length;
  }

  T* begin() {
    return data_;
  }
  
  T* end() {
    return data_ + Length;
  }

  T norm() {
    return NormPolicy::calculate(begin(),end());
  }
};

typedef static_array<int, 1024> EuclideanArray;
typedef static_array<int, 1024, NonEuclideanNorm<int> > NonEuclideanArray;

typedef double my_double;

int main(int argc, char *argv[])
{
  std::cout << "An Introduction to Design by Policy and Friends!\n\n";
  
  static_array<int,1024> my_array;
  
  std::fill(my_array.begin(), my_array.end(),1);
  
  std::cout << "created a " << my_array.size() << " elements static array\n";

  std::cout << "norm of my_array " << my_array.norm() << "\n";
  return 0;
}
