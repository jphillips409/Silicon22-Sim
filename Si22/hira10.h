#ifndef _hira10
#define _hira10

#include "random.h"
#include "tele.h"
using namespace std;


class hira10
{
 public:
  //  static CRandom ran;
  hira10(double,double);
  ~hira10();


  bool hit(double,double,double,double);
  bool thruHole(double, double,double,double);

  double dist;
  double dist_hole;
  double length;
  double b;
  double Dactive;

  int hitTele;
  int hitCsI;
  int hitxStrip;
  int hityStrip;

  double thetaRecon;
  double phiRecon;
  CTele * tele[4];


};


#endif
