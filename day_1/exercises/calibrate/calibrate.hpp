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


struct cell {
  float pos[3];
  float e;
};


float calibrate_energy(const cell& _data){

  float r = std::sqrt(_data.pos[0]*_data.pos[0] + _data.pos[1]*_data.pos[1] + _data.pos[2]*_data.pos[2]);

  float scale = p0 + p1*r + p2*r*r + p3*r*r*r + p4*r*r*r*r + p5*r*r*r*r*r;

  float value = (1.f-scale)*_data.e;

  return value;

}


struct instrument {

  std::vector<cell> active;
  
  instrument(unsigned _axis_len):
    active(_axis_len*_axis_len*_axis_len)
  {

    active.resize(_axis_len*_axis_len*_axis_len);
    float radius = 0;
    
    unsigned long index = 0;
    for(unsigned z = 0;z<_axis_len;++z){
      for(unsigned y = 0;y<_axis_len;++y){
	for(unsigned x = 0;x<_axis_len;++x){

	  index = z*(_axis_len*_axis_len) + y*_axis_len + x ;
	  active[index].pos[0] = x - _axis_len/2.f;
	  active[index].pos[1] = y - _axis_len/2.f;
	  active[index].pos[2] = z - _axis_len/2.f;
	  radius = std::sqrt(active[index].pos[0]*active[index].pos[0] + active[index].pos[1]*active[index].pos[1] + active[index].pos[2]*active[index].pos[2] );
	  active[index].e = std::abs(std::cos(radius*_axis_len*2/M_PI));
	  
	}
      }
    }
  }

  void calibrate(){
    for(unsigned i = 0;i<active.size();++i){
      active[i].e = calibrate_energy(active[i]);
    }
  }


  float sum() const {
    float value = 0.f;

    for(unsigned i = 0;i<active.size();++i){
      value += active[i].e;
    }

    return value;
  }
    
};

#endif /* _CALIBRATE_H_ */
