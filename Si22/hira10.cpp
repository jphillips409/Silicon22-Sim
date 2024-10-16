#include "hira10.h"

hira10::hira10(double dist0, double b0)

{
  dist = dist0;
  b = b0;

  length = 79.;// length of SI frame in mm
  Dactive = 64.2+20;  //active dimension of Si

  double alpha = 8.23*acos(-1.)/180.;  //angle


  float r1[3];
  //center of first telescope
  r1[0] = length*cos(alpha) - b/2.;
  r1[1] = -length*sin(alpha) + length*cos(alpha);
  r1[2] = dist - length*sin(alpha);

  float dr1_1[3];
  //unit vestor 1
  dr1_1[0] = cos(alpha);
  dr1_1[1] = -sin(alpha);
  dr1_1[2] = 0.;


  float dr1_2[3];
  dr1_2[0] = 0.;
  dr1_2[1] = cos(alpha);
  dr1_2[2] = - sin(alpha);
  

  tele[0] = new CTele(r1,dr1_1,dr1_2,Dactive,Dactive);

  //rotate by 90 degrees

  float r2[3];
  r2[0] = r1[1];
  r2[1] = -r1[0];
  r2[2] = r1[2];


  float dr2_1[3];
  dr2_1[0] = dr1_1[1];
  dr2_1[1] = -dr1_1[0];
  dr2_1[2] = dr1_1[2];

  float dr2_2[3];
  dr2_2[0] = dr1_2[1];
  dr2_2[1] = -dr1_2[0];
  dr2_2[2] = dr1_2[2];

  tele[1] = new CTele(r2,dr2_1,dr2_2,Dactive,Dactive);

  //rotate by 90 degrees

  float r3[3];
  r3[0] = r2[1];
  r3[1] = -r2[0];
  r3[2] = r2[2];


  float dr3_1[3];
  dr3_1[0] = dr2_1[1];
  dr3_1[1] = -dr2_1[0];
  dr3_1[2] = dr2_1[2];

  float dr3_2[3];
  dr3_2[0] = dr2_2[1];
  dr3_2[1] = -dr2_2[0];
  dr3_2[2] = dr2_2[2];

  tele[2] = new CTele(r3,dr3_1,dr3_2,Dactive,Dactive);


  //rotate by 90 degrees

  float r4[3];
  r4[0] = r3[1];
  r4[1] = -r3[0];
  r4[2] = r3[2];


  float dr4_1[3];
  dr4_1[0] = dr3_1[1];
  dr4_1[1] = -dr3_1[0];
  dr4_1[2] = dr3_1[2];

  float dr4_2[3];
  dr4_2[0] = dr3_2[1];
  dr4_2[1] = -dr3_2[0];
  dr4_2[2] = dr3_2[2];

  tele[3] = new CTele(r4,dr4_1,dr4_2,Dactive,Dactive);

  dist_hole = dist + 177.8;
}


hira10::~hira10()
{
  delete tele[0];
  delete tele[1];
  delete tele[2];
  delete tele[3];
}
//*************************************************************************
bool hira10::hit(double theta, double phi, double xtarget, double ytarget)
{

  hitTele = -1;
  for (int itele=0;itele<4;itele++)
    {
      if (tele[itele]->hit(theta,phi,xtarget,ytarget))
	{
	  hitTele = itele;
          break;
	}
    }
      if (hitTele == -1) return false;
      hitCsI = tele[hitTele]->ICsI;
      hitxStrip = tele[hitTele]->ixStrip;
      hityStrip = tele[hitTele]->iyStrip;
      thetaRecon = tele[hitTele]->thetaRecon;
      phiRecon = tele[hitTele]->phiRecon;
      return true;

}

  //********************************************************************
  bool hira10::thruHole(double theta, double phi, double xtarget, double ytarget)
      {
        double x = dist_hole*sin(theta)*cos(phi) + xtarget;
        if (fabs(x) > b/2.) return false;
        double y = dist_hole*sin(theta)*sin(phi) + ytarget;
        if (fabs(y) > b/2.) return false;

        return true;
      }
