#include "plf.h"
#include "constants.h"
using namespace std;

CRandom CPlf::ran;
double const CPlf::pi = acos(-1.);

/**
 * Constructor
 \param thickness is target thickness in mg/cm2
*/

CPlf::CPlf(double thickness)
{
  temp1 = .5*pi/180.; 
  temp2 = 1.4*pi/180.;
  frame = new CFrame(Mass_22Si/m0);
  double thick = thickness/1000./9.*6.02e23; // atoms/ cem2
  multScat =  new CMultScat(6,4,thick);


  ifstream filez0("MOMDIS/sigz0.dat");
  ifstream filez1("MOMDIS/sigz1.dat");
  ifstream filez2("MOMDIS/sigz2.dat");

  npara = 0;
  double sum = 0;
  double xx0,yy0,xx1,yy1,xx2,yy2;
  for (;;)
    {
      filez0 >> xx0 >> yy0;
      filez1 >> xx1 >> yy1;
      filez2 >> xx2 >> yy2;
      if (filez0.bad())break;
      if (filez0.eof())break;
      Ppara[npara] = xx0;
      ypara[npara] = yy0+yy1+yy2;
      sum += ypara[npara];
      if (npara > 0) ypara[npara] += ypara[npara-1];
      npara++;
    }

  for (int i=0;i<npara;i++) ypara[i] /= sum;

  filez0.close(); 
  filez0.clear();

  filez1.close(); 
  filez1.clear();

  filez2.close(); 
  filez2.clear();


  ifstream filex0("MOMDIS/sigx0.dat");
  ifstream filex1("MOMDIS/sigx1.dat");
  ifstream filex2("MOMDIS/sigx2.dat");

  nperp = 0;
  sum = 0;
  for (;;)
    {
      filex0 >> xx0 >> yy0;
      filex1 >> xx1 >> yy1;
      filex2 >> xx2 >> yy2;
      if (filex0.bad())break;
      if (filex0.eof())break;
      Pperp[nperp] = xx0;
      yperp[nperp] = (yy0+yy1+yy2)*fabs(xx0);
      sum += yperp[nperp];
      if (nperp > 0) yperp[nperp] += yperp[nperp-1];
      nperp++;
    }

  for (int i=0;i<nperp;i++) yperp[i] /= sum;

  filex0.close(); 
  filex0.clear();

  filex1.close(); 
  filex1.clear();

  filex2.close(); 
  filex2.clear();



}
//********************************************
  /**
   * Destructor
   */
CPlf::~CPlf()
{
  delete frame;
  delete multScat;
}
//********************************************
  /**
   * Monte Carlo selection of the angle and velocity of the parent fragment
   */
void CPlf::GetPlf(double v_beam)
{


  float x = ran.Rndm();
  int i = 0;
  for (;;)
    {
      if (ypara[i] > x) break;
      i++;
    }
 P_para = Ppara[i] + 2.*(1.-2.*ran.Rndm());
 //P_para *= 1.4;
  //PparaTos = 0.;

  x  = ran.Rndm();
  i = 0;
  for (;;)
    {
      if (yperp[i] > x) break;
      i++;
    }
double P_perp = Pperp[i] + 2.*(1.-2.*ran.Rndm());
//P_perp *= 1.4;
 double theta = 2.*acos(-1.)*ran.Rndm();
 P_perp1 = P_perp*cos(theta);
 P_perp2 = P_perp*sin(theta);

 double P = sqrt(pow(P_para,2)+pow(P_perp1,2)+pow(P_perp2,2));
 double Etot = sqrt(pow(P,2)+pow(frame->mass,2));
 double gammaR = 1./(sqrt(1.-pow(v_beam/c,2)));
       
 frame->pc[2] = gammaR*(P_para + v_beam*Etot/c);
 frame->pc[0] = P_perp1;
 frame->pc[1] = P_perp2;

 frame->pcTot = sqrt(pow(frame->pc[0],2)+ pow(frame->pc[1],2) + pow(frame->pc[2],2));

 frame->totEnergy = sqrt(pow(frame->pcTot,2) + pow(frame->mass,2));
 frame->gamma = frame->totEnergy/frame->mass;
 frame->velocity = 30.*sqrt(1.-pow(1./frame->gamma,2));

 frame->v[0] = frame->pc[0]/frame->pcTot*frame->velocity;
 frame->v[1] = frame->pc[1]/frame->pcTot*frame->velocity;
 frame->v[2] = frame->pc[2]/frame->pcTot*frame->velocity;
 
 frame->theta = acos(frame->pc[2]/frame->pcTot);
 frame->phi = atan2(frame->pc[1],frame->pc[0]);

}
//*************************************************
  /**
   * selects breakup angle of parent fragments (isotropic distribution)
   */
void CPlf::isotropic()
{
  theta_breakup = acos(1.-2.*ran.Rndm());
  phi_breakup = 2.*pi*ran.Rndm();

  unit_breakup[0] = sin(theta_breakup)*cos(phi_breakup);
  unit_breakup[1] = sin(theta_breakup)*sin(phi_breakup);
  unit_breakup[2] = cos(theta_breakup);

}
//*************************************************
  /**
   * Selects break angle of parent fragment.
   * the distribution is assumed to be isotropic in-plane i.e. 1/sin(theta)
   */
void CPlf::inplane()
{
  theta_breakup =pi*ran.Rndm();
  phi_breakup = 2.*pi*ran.Rndm();

  unit_breakup[0] = sin(theta_breakup)*cos(phi_breakup);
  unit_breakup[1] = sin(theta_breakup)*sin(phi_breakup);
  unit_breakup[2] = cos(theta_breakup);


  //rotate along axis of plf
  //first the x-z plane
  double xd = unit_breakup[0]*cos(theta) + unit_breakup[2]*sin(theta);
  double yd = unit_breakup[1];
  double zd = unit_breakup[2]*cos(theta) - unit_breakup[0]*sin(theta);

  //then in x-y plane
  double xdd = xd*cos(phi) + yd*sin(phi);
  double ydd = yd*cos(phi) - xd*sin(phi);
  double zdd = zd;

  unit_breakup[0] = xdd;
  unit_breakup[1] = ydd;
  unit_breakup[2] = zdd;


}
//***********************************************
//include multiple scattering
  /**
   * multiple scattering of parent fragment
   \param fractionalThick fractional thickness of the target through which
    the parent passes before it decays (mg.cm2)
   */
void CPlf::MultiScat(double fractionalThick)
{
  if (fractionalThick == 0.) return;
  frame->getEnergy();
  double thetaRMS = multScat->thetaRMS(frame->energy,fractionalThick);
  double sigma = thetaRMS/sqrt(2.);
  //cout << "thetaRMS= " << thetaRMS << endl;
  double deltaTheta = sqrt(2.)*sigma*sqrt(-log(ran.Rndm()));
  //cout << "deltaTheta= " << deltaTheta << endl;
  double deltaPhi = 2.*pi*ran.Rndm();
  //cout << "delta Phi= " << deltaPhi << endl;

  double x = sin(deltaTheta)*cos(deltaPhi);
  double y = sin(deltaTheta)*sin(deltaPhi);
  double z = cos(deltaTheta);



  //rotate in z-x plane by theta
  double xx = x*cos(frame->theta) + z*sin(frame->theta);
  double yy = y;
  double zz = z*cos(frame->theta) - x*sin(frame->theta);


  //rotate in x-y plane
  double xxx = xx*cos(frame->phi) - yy*sin(frame->phi);
  double yyy = yy*cos(frame->phi) + xx*sin(frame->phi);
  double zzz = zz;


  double thetaNew = acos(zzz);
  double phiNew = atan2(yyy,xxx);
  if (phiNew < 0.) phiNew += 2.*pi;

  frame->theta = thetaNew;
  frame->phi = phiNew;
  frame->v[0] = frame->velocity*cos(phiNew)*sin(thetaNew);
  frame->v[1] = frame->velocity*sin(phiNew)*sin(thetaNew);
  frame->v[2] = frame->velocity*cos(thetaNew);
  
}
