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

template<typename T>
struct static_array_el_sum{

  const T* lhs;
  const T* rhs;
  
  explicit static_array_el_sum(const T* _lhs, const T* _rhs):
    lhs(_lhs),
    rhs(_rhs){
  }

  typename T::value_type operator[](const size_t& _at) const {
    return lhs->data_[_at] + rhs->data_[_at];
  }

  typename T::size_type size() const {
    return lhs->size();
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

  static_array(const static_array_el_sum<static_array>& _sum):
    data_(new T[Length])
  {

    for(size_t i = 0;i<(size() > _sum.size() ? _sum.size() : size());++i)
      data_[i] = _sum[i];

  }


  ~static_array(){
    delete [] data_;
    data_ = 0;
  }

  static_array& operator=(const static_array& _rhs){

    if(this!=&_rhs){

      delete [] data_;
      data_ = new T[Length];
      
      const value_type* src_begin = &_rhs.data_[0];
      value_type* begin = &data_[0];
      
      std::copy(src_begin,src_begin + size(),begin);
      
    }
    
    return *this;
  }
  
  static size_type size()  {
    return size_;
  }

  value_type operator[](const size_t& _index){
    if(_index < size())
      return data_[_index];
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

  

  friend static_array_el_sum<static_array> operator+(const static_array& _lhs, const static_array& _rhs){
    static_array_el_sum<static_array> value(&_lhs, &_rhs);
    return value;
  }

  
  static_array& operator=(const static_array_el_sum<static_array>& _sum){

    for(size_t i = 0;i<(size() > _sum.size() ? _sum.size() : size());++i)
      data_[i] = _sum[i];
    
    return *this;
  }

};

#endif /* _STATIC_ARRAY_H_ */
