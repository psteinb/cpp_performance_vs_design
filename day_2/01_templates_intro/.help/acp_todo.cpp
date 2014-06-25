#define ACP_TEMPLATE_INTRO_CPP
#include <iostream>
#include <cmath>

template<typename T>
double normal(const T& _x, const double& _mean, const double& _sigma){

  static const double pre_factor = std::sqrt(2.*M_PI);
  return 1./(pre_factor*_sigma)*std::exp((_x-_mean)*(_x-_mean)/(-2*_sigma*_sigma));

}

int faculty(int _start){

  int value = 1;

  while(_start>0){
    value*=_start--;
  }
  
  return value;
}

template<typename T>
struct poisson{

  double lambda;

  poisson(const double& _lambda = 1.):
    lambda(_lambda){}

  
};

template<>
struct poisson<int>{

  double lambda;

  poisson(const double& _lambda = 1.):
    lambda(_lambda){}

  double operator()(const int& _k) const {
    double value = std::pow(lambda, _k)*std::exp(-1*lambda);
    value /= faculty(_k);
    return value;
  }

};


int main(int argc, char *argv[])
{
  std::cout << "Introduction to templates in C++!\n";
  
  std::cout << "The normal distribution with mean=0 and sigma=1 has the following values:\n";
  for(int i = -5;i<5;++i)
    std::cout << i << ":" << normal(i,0,1) << " ";
  std::cout << "\n\n";
  
  //the following does not compile
  poisson<float> my_pdf(2.5);
  //std::cout << "Poisson(k=1.5, lambda = 2.5) " << my_pdf(1.5) << std::endl;
  
  std::cout << "The poisson distribution with mean=2 has the following values:\n";
  poisson<int> int_poisson(2);
  for(int i = -5;i<5;++i)
    std::cout << i << ":" << int_poisson(i) << " ";
  std::cout << "\n";
  
  return 0;
}
