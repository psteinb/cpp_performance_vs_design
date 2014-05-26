#ifndef _CALIBRATE_H_
#define _CALIBRATE_H_
#include <cmath>

static  const  float  p0  =  0.0584334f    ;
static  const  float  p1  =  7.97765e-05   ;
static  const  float  p2  =  -2.43077e-06  ;
static  const  float  p3  =  8.28912e-09   ;
static  const  float  p4  =  -1.1121e-11   ;
static  const  float  p5  =  5.39762e-15   ;


float calibrate(const float& _old, const int& _x, const int& _y, const int& _z){

  float r = std::sqrt(_x*_x + _y*_y + _z*_z);

  float scale = p0 + p1*r + p2*r*r + p3*r*r*r + p4*r*r*r*r + p5r*r*r*r*r;

  float value = (1.f-scale)*_old;

  return value;

}

#endif /* _CALIBRATE_H_ */
