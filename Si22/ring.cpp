#include "ring.h"


CRandom ring::ran;  //random number generator

//constructor
ring::ring(double dist0, double rmin0, double rmax0, int Nring0, int Npie0, double r_middle0, double rminCsI0, double rmaxCsI0)
{
  dist = dist0;  // distance of ring counter to target
  rmin = rmin0;  // minimum active radius of ring counter
  rmax = rmax0;  // maximum active radius of ring counter
  Nring = Nring0; // number of annular ring sectors
  Npie  = Npie0;  //number of pie sectors
  rminCsI = rminCsI0;
  rmaxCsI = rmaxCsI0;
  r_middle = r_middle0;

  theta_min = atan2(rmin,dist);
  theta_max = atan2(rmax,dist);
  dr = rmax - rmin;
}

// returns 1 if particle hits detector, else returns zero
// inputs  theta = emission zenith angle in radians of scattered particle
//         phi =   emission azimuth angle in radians of scattered particle
//         phi goes from -pi to pi
bool ring::hit(double theta, double phi, double xtarget, double ytarget, double range, double straggle)
{


  double x = dist*sin(theta)*cos(phi)+xtarget;
  double y = dist*sin(theta)*sin(phi)+ytarget;

  double rad = sqrt(pow(x,2)+pow(y,2));
  if (rad < rmin) return false;
  if (rad > rmax) return false;

  hitRing = int((rad-rmin)/dr*double(Nring));
  double rr = ran.Rndm();
 
  double radAssigned = ((double)hitRing+rr)*dr/double(Nring) + rmin;
  thetaHit = atan(radAssigned/dist);



  double phi2 = atan2(y,x);
  if (phi2 < 0.) phi2 += 2.*acos(-1.);
  hitPie = int(phi2/2./acos(-1.)*Npie);

  //missing wedge in Si
  if (hitPie < 8) return false;

  bool inner = false;
  if (rad < r_middle) inner = true;

  if (inner) N_CsI = int(phi2/2./acos(-1.)*4.);
  else N_CsI = int(phi2/2./acos(-1.)*16.) + 4;


  phiHit = ((double)hitPie+ran.Rndm())*2.*acos(-1.)/double(Npie);
  

  // proton must stop in same CsI, calculate x and y where proton stops

  double xrange = (dist+range)*sin(theta)*cos(phi)+xtarget+ ran.Gaus(0.,straggle/sqrt(2.));
  double yrange = (dist+range)*sin(theta)*sin(phi)+ytarget+ ran.Gaus(0.,straggle/sqrt(2.));
  double phi2_range = atan2(yrange,xrange);
  if (phi2_range < 0.) phi2_range += 2.*acos(-1.);
  double rad_range = sqrt(pow(xrange,2)+pow(yrange,2));

  if (rad_range < rminCsI) return false;
  if (rad_range > rmaxCsI) return false;
  


  bool inner_range = false;
  if (rad_range < r_middle) inner_range = true; 

  int N_CsI_range;
  if (inner_range) N_CsI_range = int(phi2_range/2./acos(-1.)*4.);
  else N_CsI_range = int(phi2_range/2./acos(-1.)*16.) + 4;

  if (N_CsI != N_CsI_range) return false;

  return true;
}
