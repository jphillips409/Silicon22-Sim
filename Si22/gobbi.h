#ifndef _gobbi
#define _gobbi

#include "gtele.h"
#include "random.h"
using namespace std;


class gobbi
{
 public:
  static CRandom ran;
  gtele *Tele[5];
  gtele *TeleCsI[5];
  gobbi(double,double,bool extra=false);
  ~gobbi();


  int hit(double,double,double,double,double,double);
  bool thruHole(double,double,double,double);

  double thetaHit;
  double phiHit;
  int nTele;
  bool extra;
  int itele;
  int itele_CsI;
  double dist;
  double length;
  double b;
  double Dactive;
  double thetaCollimator;

};


#endif
