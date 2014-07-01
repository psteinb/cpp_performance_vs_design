#define ACP_TEST_CPP
#include <iostream>
// file to serve as a starting point

template <unsigned int start>
struct fac{

  static const unsigned int value = start*fac<start - 1>::value;
  
};

template<>
struct fac<1>{
  static const unsigned int value = 1;
};

template<typename T, unsigned int index>
struct loop_for {
  
  static const void now(){
    T temp;temp();
    return loop_for<T,index - 1>::now();
  }

};

template <typename T>
struct loop_for<T,0>{
  static const void now(){
    T temp;temp();
    return;
  }
};

struct shout {
    
  void operator()(){
    std::cout << "YALLA!\n";
  }
    
};

int main(int argc, char *argv[])
{
  std::cout << "Compile Time Calculations!\n";
  
  std::cout << "6! = " << fac<fac<4>::value>::value << "\n";

  loop_for<shout,10>::now();

  shout shouter;
  for(int i = 0;i<10;++i){
    shouter();
  }
  return 0;
}
