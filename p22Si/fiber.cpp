#include "fiber.h"

CRandom fiber::ran;  //random number generator

fiber::fiber(double distAb0, double radAb0, double distFibers0, double fiberWidth0)
{
  distAb = distAb0;
  radAb = radAb0;
  distFibers  = distFibers0;
  fiberWidth = fiberWidth0;
}

bool fiber::hit(double theta, double phi, double xtarget, double ytarget)
{
  double x = distAb*sin(theta)*cos(phi)+xtarget;
  double y = distAb*sin(theta)*sin(phi)+ytarget;

  double rad = sqrt(pow(x,2)+pow(y,2));
  if (rad > radAb) return false;

  double x2 = distFibers*sin(theta)*cos(phi)+xtarget;
  double y2 = distFibers*sin(theta)*sin(phi)+ytarget;

  Ix = floor (x2/fiberWidth);
  Iy = floor (y2/fiberWidth);

  //64 fibers to a ribbon - in sim code
  //if (abs(Ix) > 32) return false;
  //if (abs(Iy) > 32) return false;

  double xAssigned = (double(Ix)+ran.Rndm())*fiberWidth;
  double yAssigned = (double(Iy)+ran.Rndm())*fiberWidth;

  double radAssigned = sqrt(pow(xAssigned,2)+pow(yAssigned,2));
  thetaHit = atan(radAssigned/distFibers);
  phiHit = atan2(yAssigned,xAssigned);

  return true;
}
