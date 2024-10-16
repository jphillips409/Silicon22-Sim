#ifndef frame_
#define frame_
#include <cmath>


/**
 *!\brief Relativistic and Non-Relativistic stuff
 *
 * give velocity, energies, transforms to new reference frame
 * using either non-relativistic or Relativistics equations
 */

class CFrame
{
 public:
  double energy;  //!< fragments energy in MeV
  double velocity; //!< fragments velocity in cm/ns 
  double pcTot;  //!< total momentum*c of fragment
  double v[3];  //!< velocity vector of fragment
  double pc[3]; //!< momentum*c vector of fragment MeV
  double mass;  //!< rest mass of fragment in MeV
  double A;
  double gamma; //!< relativistic gamma factor 
  double theta; //!< theta nagle of fragment in radians
  double phi;  //!< phi angle
  double totEnergy; //!< rest mass plas kinetic energy


 
  double getVelocity();
  double getVelocityNewton();
  double getVelocityRel();
  double getEnergy();
  double getEnergyNewton();
  double getEnergyRel();
  void getAngle();
  void transformVelocity(double*);
  void transformVelocityNewton(double*);
  void transformVelocityRel(double*);
  void getVelocityFromMom();
  void getVelocityFromMomNewton();
  void getVelocityFromMomRel();

  CFrame(double);
  static bool  einstein;
};


#endif
