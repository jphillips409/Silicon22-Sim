#include "gtele.h"
#include <cmath>

CRandom gtele::ran;  //random number generator

gtele::gtele( double x0, double y0, double Dactive0, double Dphysical0)
{
  xCenter = x0;
  yCenter = y0;
  Dactive = Dactive0;
  Dphysical = Dphysical0;

}

//************************************************
int gtele::hit(double x, double y)
{
  int ihit =0;
  if (fabs(x - xCenter) > Dactive/2.) return ihit;
  if (fabs(y - yCenter) > Dactive/2.) return ihit;

  ihit = 1;

  ix = (int)((x - xCenter + Dactive/2.)/Dactive*32.);
  iy = (int)((y - yCenter + Dactive/2.)/Dactive*32.);


  if (ix < 16)
    {
      if (iy < 16) nCsI = 0;
      else nCsI = 1;
    }
  else 
    {
      if (iy < 16) nCsI = 2;
      else nCsI = 3;
    }



  xRecon = ((double)ix+ran.Rndm())/32.*Dactive - Dactive/2. + xCenter;
  yRecon = ((double)iy+ran.Rndm())/32.*Dactive - Dactive/2. + yCenter;

  

  return ihit;
 
}
//************************************************
bool gtele::hitAbsorber(double x, double y)
{

  if (fabs(x - xCenter) > Dphysical/2.) return false;
  if (fabs(y - yCenter) > Dphysical/2.) return false;

  return true;
 
}
