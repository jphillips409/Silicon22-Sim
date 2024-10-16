#include "random.h"

class gtele
{
 public:
  static CRandom ran;
  double xCenter;
  double yCenter;
  double Dactive;
  double Dphysical;


  gtele(double,double,double,double);
  bool hitAbsorber(double,double);
  int hit(double,double);
  double xRecon;
  double yRecon;

  int ix;
  int iy;
  int nCsI;
};
