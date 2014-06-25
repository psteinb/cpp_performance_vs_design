#include <iostream>
#include <iomanip>
#include <chrono>

struct pure_virtual_interface {

  virtual void update() = 0;

};

struct pure_virtual_implementation : public pure_virtual_interface {

  unsigned long counter;
  
  pure_virtual_implementation():
    counter(0){}
  
  virtual void update(){
    counter+=1;
  };

};

template <typename DaughterT>
struct crtp_interface {

  void update(){
#ifdef __GNUG__
    return static_cast<DaughterT*>(this)->update_impl(); 
#else
    return DaughterT::DoPerform(ia); 
#endif
  }
  
};


struct crtp_implementation : public crtp_interface<crtp_implementation> {

  unsigned long counter;
  
  crtp_implementation():
    counter(0){}

  void update_impl(){
    counter+=1;
  }
  
};


int main(int argc, char *argv[])
{
  const unsigned int num = 1 << 30;
  pure_virtual_implementation* demo1 = new pure_virtual_implementation;
  
  std::cout << num << " updates\n";

  auto t_start = std::chrono::high_resolution_clock::now();
  for(unsigned int i = 0;i<num;++i)
    demo1->update();
  auto t_end = std::chrono::high_resolution_clock::now();
  double delta_common = std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();
  std::cout << std::setw(30) << "virtual inheritance: " << delta_common << " ms\n";
  
  delete demo1;

  crtp_implementation demo2;
  t_start = std::chrono::high_resolution_clock::now();
  for(unsigned int i = 0;i<num;++i)
    demo2.update();
  t_end = std::chrono::high_resolution_clock::now();
  double delta_crtp = std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();
  std::cout << std::setw(30) << "crtp inheritance: " << delta_crtp << " ms\n";
  return 0;
}
