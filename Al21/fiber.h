#ifndef _fiber
#define _fiber
#include "random.h"
class fiber{
 public:

  static CRandom ran;
  double distAb;   // distance from target to absorber in front to Si in mm
  double radAb; // radius of hole in Absorber in mm
  double distFibers; // distance from target to fibers  in mm
  double fiberWidth;  // fiber width in mm
  fiber(double distAb, double radAb, double distFibers, double fiberWidth);

  bool hit(double theta, double phi, double xtarget, double ytarget);


  double thetaHit;
  double phiHit;

  int Ix,Iy; /// hit x and y fibers
};

#endif
