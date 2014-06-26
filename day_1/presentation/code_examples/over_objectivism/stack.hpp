#ifndef _STACK_H_
#define _STACK_H_
#include <vector>
#include <utility>
#include <cmath>


struct flat_stack {

  std::vector<float> intensities_;
  std::vector<std::pair<int,int> > dimensions_;
  
  flat_stack(const int& _max_dim0, 
	     const int& _max_dim1,
	     const int& _max_dim2):
    intensities_(_max_dim0*_max_dim1*_max_dim2),
    dimensions_(3)
  {
    dimensions_[0] = std::make_pair(0, _max_dim0);
    dimensions_[1] = std::make_pair(0, _max_dim1);
    dimensions_[2] = std::make_pair(0, _max_dim2);
  } 

  void fill(const float& _in){
    std::fill(intensities_.begin(), intensities_.end(), _in);
  }

  double l2norm(const flat_stack& _rhs){
    double value = 0.;
    for(size_t pixel = 0;pixel<std::min(_rhs.intensities_.size(), intensities_.size()); ++pixel){
      value += (_rhs.intensities_[pixel]-intensities_[pixel]) * (_rhs.intensities_[pixel]-intensities_[pixel]) ;
    }
    return value;
  }
  
  double l1norm(const flat_stack& _rhs){
    double value = 0.;
    for(size_t pixel = 0;pixel<std::min(_rhs.intensities_.size(), intensities_.size()); ++pixel){
      value += std::sqrt((_rhs.intensities_[pixel]-intensities_[pixel]) * (_rhs.intensities_[pixel]-intensities_[pixel])) ;
    }
    return value;
  }
};

struct pixel {

  int x_;
  int y_;
  int z_;
  
  float intensity_;

};

struct pixel_stack {

  std::vector<pixel> data_;
  std::vector<std::pair<int,int> > dimensions_;
  
  pixel_stack(const int& _max_dim0, 
	     const int& _max_dim1,
	     const int& _max_dim2):
    data_(_max_dim0*_max_dim1*_max_dim2),
    dimensions_(3)
  {
    dimensions_[0] = std::make_pair(0, _max_dim0);
    dimensions_[1] = std::make_pair(0, _max_dim1);
    dimensions_[2] = std::make_pair(0, _max_dim2);
  } 

  void fill(const float& _in){
    for(size_t pixel = 0;pixel<data_.size(); ++pixel){
      data_[pixel].intensity_ = _in;
    }
  }

  double l2norm(const pixel_stack& _rhs){
    double value = 0.;
    for(size_t pixel = 0;pixel<std::min(_rhs.data_.size(), data_.size()); ++pixel){
      value += (_rhs.data_[pixel].intensity_ - data_[pixel].intensity_) * (_rhs.data_[pixel].intensity_ - data_[pixel].intensity_);
    }
    return value;
  }

  double l1norm(const pixel_stack& _rhs){
    double value = 0.;
    for(size_t pixel = 0;pixel<std::min(_rhs.data_.size(), data_.size()); ++pixel){
      value += std::sqrt((_rhs.data_[pixel].intensity_ - data_[pixel].intensity_) * (_rhs.data_[pixel].intensity_ - data_[pixel].intensity_));
    }
    return value;
  }
};

#endif /* _STACK_H_ */
