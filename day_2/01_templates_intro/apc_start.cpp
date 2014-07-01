#define ACP_TEST_CPP
#include <iostream>
// file to serve as a starting point

template <class T, typename U>
T sum(const T& _lhs, const U& _rhs){
  return _lhs + _rhs;
}

template <typename T, typename U>
struct adder {

  T operator()(const T& _lhs, const U& _rhs){
    return _lhs + _rhs;
  }

};

template <typename T>
struct adder<T,double> {

  T operator()(const T& _lhs, const double& _rhs){
    
    std::cout << "this is your special implementation running!\n";
    return _lhs + _rhs;
  }

};



int main(int argc, char *argv[])
{
  std::cout << "Introduction to templates in C++!\n";

  double one = 1.;
  int two = 42;
  double alt_two = 42.;
  
  std::cout << "result of one+two = " << sum<double, int>(one,two) << "\n";

  adder<double,int> sum_by_object;
  std::cout << "result of one+two = " << sum_by_object(one,two) << "\n";
  
  adder<int,double> special_sum_by_object;
  std::cout << "result of one+two : " << special_sum_by_object(one,two) << "\n";

  return 0;
}
