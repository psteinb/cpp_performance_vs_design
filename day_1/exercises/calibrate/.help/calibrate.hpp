#ifndef _CALIBRATE_H_
#define _CALIBRATE_H_
#include <vector>
#include <cmath>

static  const  float  p0  =  0.0584334f    ;
static  const  float  p1  =  7.97765e-05   ;
static  const  float  p2  =  -2.43077e-06  ;
static  const  float  p3  =  8.28912e-09   ;
static  const  float  p4  =  -1.1121e-11   ;
static  const  float  p5  =  5.39762e-15   ;


void calibrate_energy(float* _x, float* _y, float* _z, float* _e, const size_t& _size){

#if GCC_VERSION > 40701
  float *x = (float*)__builtin_assume_aligned(_x, 16);
  float *y = (float*)__builtin_assume_aligned(_y, 16);
  float *z = (float*)__builtin_assume_aligned(_z, 16);
  float *e = (float*)__builtin_assume_aligned(_e, 16);
#else
  float *x = _x;
  float *y = _y;
  float *z = _z;
  float *e = _e;
#endif

  for(size_t i = 0;i<_size;++i){
    float r = std::sqrt(x[i]*x[i] + y[i]*y[i] + z[i]*z[i]);
    float scale = p0 + p1*r + p2*r*r + p3*r*r*r + p4*r*r*r*r + p5*r*r*r*r*r;
    e[i] = (1.f-scale)*e[i];
  }
  
}


struct instrument {

  std::vector<float> x_pos;
  std::vector<float> y_pos;
  std::vector<float> z_pos;
  std::vector<float> e;
  
  instrument(unsigned _axis_len):
    x_pos(_axis_len*_axis_len*_axis_len,0.f),
    y_pos(_axis_len*_axis_len*_axis_len,0.f),
    z_pos(_axis_len*_axis_len*_axis_len,0.f),
    e(_axis_len*_axis_len*_axis_len,0.f)
  {

    float radius = 0;
    unsigned long index = 0;

    for(unsigned z = 0;z<_axis_len;++z){
      for(unsigned y = 0;y<_axis_len;++y){
	for(unsigned x = 0;x<_axis_len;++x){

	  index = z*(_axis_len*_axis_len) + y*_axis_len + x ;
	  x_pos[index] = x - _axis_len/2.f;
	  y_pos[index] = y - _axis_len/2.f;
	  z_pos[index] = z - _axis_len/2.f;
	  radius = std::sqrt(x_pos[index]*x_pos[index] + y_pos[index]*y_pos[index]+ z_pos[index]*z_pos[index]);
	  e[index] = std::abs(std::cos(radius*_axis_len*2/M_PI));
	  
	}
      }
    }
  }

  void calibrate(){

    float* energy = &e[0];
    float* x = &x_pos[0];
    float* y = &y_pos[0];
    float* z = &z_pos[0];
    
    calibrate_energy(x,y,z,energy,x_pos.size());
    
    
  }


  float sum() const {
    float value = 0.f;

    for(unsigned i = 0;i<e.size();++i){
      value += e[i];
    }

    return value;
  }
    
};

#endif /* _CALIBRATE_H_ */
