#ifndef _STATIC_ARRAY_HPP_
#define _STATIC_ARRAY_HPP_
#include <cmath>

template <typename T,typename U>
struct SumNorm{

  T apply_norm(const T* _payload, const U& _size) const {
    
    T value = 0;

    for(U i = 0;i<_size;++i)
      value += _payload[i];

    return value;

  }
  
};

template <typename T,typename U>
struct EuclidNorm{

  T apply_norm(const T* _payload, const U& _size) const {
    
    T value = 0;
    
    for(U i = 0;i<_size;++i)
      value += _payload[i]*_payload[i];
    
    return std::sqrt(value);

  }
  
};

template<typename T, unsigned int Length, typename NormT = SumNorm<T, unsigned int> >
struct static_array : public NormT {
  
  static const unsigned int size_ = Length;
  typedef T value_type;
  typedef unsigned int size_type;
  typedef NormT norm_type;
  
  value_type* data_;

  static_array():
    data_(new T[Length]){
    
  }
  
  static_array(const T& _default):
    data_(new T[Length])
  {

    T* begin = &data_[0];
    std::fill(begin,begin + Length,_default);
    
  }

  template<typename OtherT>
  static_array(const OtherT& _rhs):
    data_(new T[Length])
  {

    OtherT* src_begin = &_rhs.data_[0];
    T* begin = &data_[0];
    
    std::copy(src_begin,src_begin + (Length<OtherT::size_ ? Length : OtherT::size_),begin);
    
  }

  ~static_array(){
    delete [] data_;
    data_ = 0;
  }

  template<typename OtherT>
  static_array& operator=(const OtherT& _rhs){

    if(this!=&_rhs){

      delete [] data_;
      data_ = new T[Length];
      
      OtherT* src_begin = &_rhs.data_[0];
      T* begin = &data_[0];
      std::copy(src_begin,src_begin + (Length<OtherT::size_ ? Length : OtherT::size_),begin);
      
    }
    
    return *this;
  }
  
  static size_type size()  {
    return size_;
  }
  
  value_type* begin() {
    return &data_[0];
  }

  value_type* end() {
    return &data_[size_] + 1;
  }

  const value_type* begin() const {
    return &data_[0];
  }

  const value_type* end() const {
    return &data_[size_] + 1;
  }  

  value_type norm() const {

    return NormT::apply_norm(begin(),size());

  }
  
};

#endif /* _STATIC_ARRAY_H_ */
