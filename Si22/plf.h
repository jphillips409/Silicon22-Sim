#include "random.h"
#include <iostream>
#include "frame.h"
#include "CMomDist.h"
#include "mScat.h"

using namespace std;

/**
 * !\brief parent fragment stuff
 *
 * deals with the velocity and angular distribution of the parent
 * fragment before its decays
 */

class CPlf
{
 public:
  double vel;  //!< velocity of parent fragment in cm/ns
  double theta; //!< theta angle of parent fragment in radians
  double phi; //!< phi angle
  double v[3]; //!< velcoity vector of parent fragment in cm/ns

  double theta_breakup;
  double phi_breakup;
  double unit_breakup[3];

  CPlf(double);
  ~CPlf();
  void GetPlf(double pc_beam);
  void isotropic();
  void inplane();
  double temp1,temp2;
  static double const pi;
  static CRandom ran;
  CFrame *frame;
  CMomDist momDist;
  CMultScat *multScat;
  void MultiScat(double);

  double Ppara[210];
  double Pperp[210];
  double ypara[210];
  double yperp[210];
  int npara;
  int nperp;
  double P_perp1,P_perp2, P_para;

};
