#ifndef _ring
#define _ring
#include "random.h"
#include <iostream>
using namespace std;

class ring
{
 public:
  static CRandom ran;
  ring(double dist,double rmin, double rmax, int Nring, int Npi, double r_middle, double rminCsI, double rmaxCsI);
  bool hit(double theta, double phi, double xtarget, double ytarget,double range=0., double straggle=0.);

  int hitRing; // ring which was hit
  int hitPie;  // pie sector which was hit

  double thetaHit; //zenith angle in radians assigned to hit
  double phiHit; // azimuth angle in radians assigned to hit

  double rmin;  //minium radius of ring counter
  double rmax;  //maximum radius of ring counter
  double dist;  //distance of ring counter from target
  int Nring;   // number of annullar ring sectors
  int Npie;    //number of pie sectors
  double dr;
  double rminCsI;
  double rmaxCsI;
  double r_middle;

  double theta_min;
  double theta_max;

  int N_CsI;
};
#endif
