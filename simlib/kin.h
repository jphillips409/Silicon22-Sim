#include <cmath>

struct vel
{
  double vv;
  double v[3];
};




class kin
{
 public:
  kin(){};
  vel findCM(float[3],float[3],float,float);
  vel findCM(double[3],double[3],double,double);
  vel findCM(float[3],float[3],float[3],float,float,float);
  vel findCM(float[3],float[3],float[3],float[3],float);
  vel trans(vel,float[3],float);
  vel trans(vel,double[3],double);
  vel transV(vel,vel);


};
