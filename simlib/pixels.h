#if !defined(MYLIB_PIXELS_H)
#define MYLIB_PIXELS_H 1


#include <fstream>
#include <iostream>
#include <cmath>
#include "sle.h"

using namespace std;

struct location
{
  double x,y,z;
  double theta,phi;
};


struct teles
{
  float r_front[3];
  float r_back[3];
  float r_center[3];
};


struct teleP
{
  location Location[32][32];
};

class pixels
{
 public:
  pixels(double dz = 0.);
  teleP TeleP[14];
  location getCenter(int itele);
  float getCsiCenter(int itele, int iCsi);
  float phi;
  float getAngle(int itele,int ifront, int iback);
  float getAngle(int itele, int ifront, int iback, float dz); 
  void prepareSim();
  teles Tele[14];
  bool sim(float,float,float,float, float,float, float dz = 0.);
  
  int ixStrip;
  int iyStrip;
  int ICsI;
  float thetaRecon;
  float phiRecon;
  int hitTele;
};

#endif
