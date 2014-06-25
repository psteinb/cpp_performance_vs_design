#ifndef _CALIBRATE_H_
#define _CALIBRATE_H_
#include <vector>
#include <cmath>

static  const  float  p0  =  15832.6 ;
static  const  float  p1  =  3.1327 ;
static  const  float  p2  =  -0.164022 ;
static  const  float  p3  =  0.000220162 ;
static  const  float  p4  =  5.15833e-08 ;
static  const  float  p5  =  -1.53028e-10 ;


struct cell {
  float pos[3];
  float e;
};


float calibrate_energy(const cell& _data){

  float r = std::sqrt(_data.pos[0]*_data.pos[0] + _data.pos[1]*_data.pos[1] + _data.pos[2]*_data.pos[2]);

  float scale = p0 + p1*r + p2*r*r + p3*r*r*r + p4*r*r*r*r + p5*r*r*r*r*r // + p0*p0 + p1*p1*r + p2*p2*r*r + p3*p3*r*r*r
    ;
  scale /= (2./3.)*1e7;
  
  float value = (1.f-scale)*_data.e;

  return value;

}


struct instrument {

  std::vector<cell> active;
  
  instrument(unsigned _axis_len):
    active(_axis_len*_axis_len*_axis_len)
  {

    
    float radius = 0;
    
    unsigned long index = 0;
    for(unsigned z = 0;z<_axis_len;++z){
      for(unsigned y = 0;y<_axis_len;++y){
	for(unsigned x = 0;x<_axis_len;++x){

	  index = z*(_axis_len*_axis_len) + y*_axis_len + x ;
	  
	  float factor = - 2/(_axis_len*_axis_len);
	  active[index].pos[0] = x - _axis_len/2.f;
	  active[index].pos[1] = y - _axis_len/2.f;
	  active[index].pos[2] = z - _axis_len/2.f;
	  radius = std::sqrt(active[index].pos[0]*active[index].pos[0] + active[index].pos[1]*active[index].pos[1] + active[index].pos[2]*active[index].pos[2] );
	  active[index].e = factor*radius*radius + 2;
	  
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
