#define ACP_TEST_CPP
#include <iostream>
// file to serve as a starting point
template <int start>
struct fac {

  static const int value = start*fac<start - 1>::value;

};

template <>
struct fac <0> {

  static const int value = 1;

};

struct shout {

  void operator()() const {
    std::cout << "shout!\n";
  }
};

template <typename T, int start>
struct unroll {

  static void apply(){
    T t;t();
    unroll<T,start - 1>::apply();
  }

};

template <typename T>
struct unroll<T,0> {

  static void apply(){
    return;
  }

};


int main(int argc, char *argv[])
{
  std::cout << "Compile Time Calculations!\n";
  
  std::cout << "6! = " << fac<6>::value << "\n";

  unroll<shout, 10>::apply();
  

  return 0;
}
