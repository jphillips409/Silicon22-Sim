#include "frag.h"
#include <cmath>


float const CFrag::pi=acos(-1.);
CRandom CFrag::ran;

/**
 * Constructor
 \param Z0 is the atomic number of fragment
 \param mass0 is mass of fragment in amu
 \param filename specifies the name of the file with energy loss information
 \param CsI_res0 fractional energy resolution of this fragment in CsI
 \param thickness is target thickness in mg/cm2 
 \param scaleSmallAngle - scale the predicted width for small angle scattering
 \param  
*/

CFrag::CFrag(float Z0,float mass0, string filename, float CsI_res0,
	     float thickness, float scaleSmallAngle0, bool useRealP0):fragment(Z0,mass0)
{
  loss = new CLoss(filename,mass);
  CsI_res = CsI_res0;
  //be9 target  
  float thick = thickness/1000./9.*6.02e23; // atoms/ cem2
  multScat = new CMultScat((int)Z,4,thick);

  float fromCenter = 27.2;//35.;
  float radius = 63.; //50.;
  Array = new CArray(radius,fromCenter,6.42,7.6);
  shadowArray = new CArray(radius+2.,fromCenter,7.4,8.2);
  real = new CFrame(mass);
  recon = new CFrame(mass);
  scaleSmallAngle = scaleSmallAngle0;
  useRealP = useRealP0;

  //const double dz = -10.44;
  const double dz = -1.;
  Pixels = new pixels (dz);
  Pixels->prepareSim();

  //proton thresholds
  ifstream pfile("/home/Boron8/simlib/pthres.dat");
  int one;
  float two;
  for (int i=0;i<56;i++)
    {
      pfile >> one >> two;
      p_thres[i] = two;
      if (one != i) cout << " bad " << endl;
    }

  pfile.close();


}


//*********************************************************
/**
*Destructor
*/
CFrag::~CFrag()
{
  delete Array;
  delete real;
  delete recon;
  delete Pixels;
}

//**********************************************************
  /**
   * logical function determines if a particle is detected
   */
int CFrag::hit()
{
  is_hit = Array->hit(real->theta,real->phi,(float)0.,(float)0.) ;

  if (is_hit) 
    {

      recon->theta = Array->thetaRecon;
      recon->phi = Array->phiRecon;

      recon->energy = real->energy + sqrt(real->energy)*CsI_res*
       ran.Gaus(0.,1.);




     recon->getVelocity();

    }

  return is_hit;
}
//*******************************************************
int CFrag::hitShadow(float xtarget , float ytarget)
{
  is_hit = shadowArray->hit(real->theta,real->phi,xtarget,ytarget) ;

  return is_hit;
}


//**********************************************************
  /**
   * logical function determines if a particle is detected
\param xTarget is in-plane location of interection in target form nomimal center
\param yTarget is out-of-plane location (cm)
  */
int CFrag::hit(float xTarget, float yTarget)
{
  is_hit = Array->hit(real->theta,real->phi,xTarget, yTarget) ;

  if (is_hit)
    {
      
      recon->theta = Array->thetaRecon;
      recon->phi = Array->phiRecon;
     recon->energy = real->energy + sqrt(real->energy)*CsI_res*
       ran.Gaus(0.,1.);
     
     /*
      recon->theta = real->theta;
      recon->phi = real->phi;
      
      recon->energy = real->energy;
     */
     recon->getVelocity();

    }

  return is_hit;
}
//******************************************************************
  /**
   * Add a velocity vector to the fragments velocity vector.
   * Used to transform between reference frames
   */
void CFrag::AddVelocity(double *Vplf)
{
  real->transformVelocity(Vplf);
}
//****************************************************************
  /** 
   * returns the energy after the fragment has exited the target
\param thick is the thickness of target that the particle has to traverse (mg/cm2)
  */
float CFrag::Eloss(float thick)
{
  if (real->energy <=0. || real->energy != real->energy) return 0.;
  if (thick > 1000) return 0.;
  real->energy = loss->getEout(real->energy,thick);
  return real->energy;
}
//*******************************************************************
  /**
   * corrects energy of a detected particle for the energy loss
   * in the target.
\param thick is the thickness of target material though which the particle passed (mg/cm2)
  */
float CFrag::Egain(float thick)
{
  if (thick > 0.)
    recon->energy = loss->getEin(recon->energy,thick/cos(recon->theta));


  recon->getVelocity();

   return recon->energy;
}
//***********************************************
//include multiple scattering
  /**
   * Monte Carlo choice of small angle scattering due to passage through the target
\param fractionalThick is the fractional thick of the target through which the particle passed
  */
void CFrag::MultiScat(float fractionalThick)
{

  float thetaRMS = multScat->thetaRMS(real->energy,fractionalThick);
  float sigma = thetaRMS/sqrt(2.)*scaleSmallAngle;
  //cout << "thetaRMS= " << thetaRMS << endl;
  float deltaTheta = sqrt(2.)*sigma*sqrt(-log(ran.Rndm()));
  //cout << "deltaTheta= " << deltaTheta << endl;
  float deltaPhi = 2.*pi*ran.Rndm();
  //cout << "delta Phi= " << deltaPhi << endl;

  float x = sin(deltaTheta)*cos(deltaPhi);
  float y = sin(deltaTheta)*sin(deltaPhi);
  float z = cos(deltaTheta);



  //rotate in z-x plane by theta
  float xx = x*cos(real->theta) + z*sin(real->theta);
  float yy = y;
  float zz = z*cos(real->theta) - x*sin(real->theta);


  //rotate in x-y plane
  float xxx = xx*cos(real->phi) - yy*sin(real->phi);
  float yyy = yy*cos(real->phi) + xx*sin(real->phi);
  float zzz = zz;


  float thetaNew = acos(zzz);
  float phiNew = atan2(yyy,xxx);


  real->theta = thetaNew;
  real->phi = phiNew;
}
//*********************
  /**
   * accounts for multiscattering and energy loss in the target
   \param dthick is thickness of target though the particle must pass (mg/cm2)
\param thickness is total target thickness (mg/cm2)
   */
bool CFrag::targetInteraction(float dthick, float thickness)
{
  bool stopped = 0;
  if (dthick == 0.) return stopped;
  float thick = dthick/cos(real->theta);
  Eloss(thick);
  if (real->energy <= 0. || real->energy != real->energy) 
    {
      stopped = 1;
      return stopped;
    }
  MultiScat(thick/thickness);
  return stopped;
}
//**********************************************************
  /**
   * logical function determines if a particle is detected
\param xTarget is in-plane location of interection in target form nomimal center
\param yTarget is out-of-plane location (cm)
  */
int CFrag::hit2(float xTarget, float yTarget, float dz)
{



  //input offsets are in units of cm, go to mm
  xTarget *= 10.;
  yTarget *= 10.;
  //dz is already in units of mm

  is_hit = Pixels->sim(real->theta,real->phi,xTarget, yTarget,ran.Rndm(),ran.Rndm(),dz) ;





  if (!is_hit) return is_hit;


  int itele = Pixels->hitTele;
  int id = Pixels->hitTele*4 + Pixels->ICsI;
  recon->theta = Pixels->thetaRecon;
  recon->phi = Pixels->phiRecon;


  //test to see if we get out what we put in, only work approximately
  /*  
  int save_x = Pixels->ixStrip;
  int save_y = Pixels->iyStrip;
  bool js_hit = Pixels->sim(recon->theta,recon->phi,0.,0.,.5,.5,0.);
  if (save_x != Pixels->ixStrip && save_y != Pixels->iyStrip)
    {
      cout << itele << endl;
      cout << real->theta << " " << real->phi << endl;
  cout << recon->theta << " " << Pixels->thetaRecon << endl;
  cout << recon->phi << " " << Pixels->phiRecon << endl;
  cout << save_x << " " << Pixels->ixStrip << endl;
cout << save_y << " " << Pixels->iyStrip << endl;
  cout << endl;

  abort();
    }
  */



  
  if (fabs(real->A- 1.) < 0.5)
    {
      if (!protonHoleNe16(itele,Pixels->ixStrip,31-Pixels->iyStrip)) is_hit = 0;
    }

 

  if (fabs(real->A-4.) < 0.5)
    {
      if (!alphaHoleNe16(itele,Pixels->ixStrip,31-Pixels->iyStrip)) is_hit = 0;
    }




  if(real->A >10.)
    {
      if (itele !=6  && itele !=7) 
	is_hit =0;
      else if (itele == 6)
	{
          double x = 1.;
	  if (31-Pixels->iyStrip == 15) x*= .89;
	  if (31-Pixels->iyStrip == 31) x*= .92;
	  if (Pixels->ixStrip == 0) x*= .86;
	  if (Pixels->ixStrip == 15) x*= .95;
	  if (Pixels->ixStrip == 16) x*= .83;
	  if (Pixels->ixStrip == 31) x*= .83;
	  if (ran.Rndm() > x) is_hit = 0;
 	}
      else if (itele == 7)
	{
          double x = 1.;
	  if (31-Pixels->iyStrip == 16) x*= .85;
	  if (Pixels->ixStrip == 15) x*= .91;
	  if (Pixels->ixStrip == 16) x*= .86;
	  if (Pixels->ixStrip == 31) x*= .80;
	  if (ran.Rndm() > x) is_hit = 0;
 	}


      //only have else if using inner 4 CsI not inner 8
//       else
// 	{
// 	  if(itele ==6)
// 	    {
// 	      if(Pixels->ICsI == 0 || Pixels->ICsI ==3) is_hit=0;
// 	    }
// 	  else
// 	    {
// 	      if(Pixels->ICsI == 1 || Pixels->ICsI ==2) is_hit=0;
// 	    }
// 	}

    }
  if (is_hit)
    {
      
      recon->theta = Pixels->thetaRecon;
      recon->phi = Pixels->phiRecon;

      recon->energy = real->energy + sqrt(real->energy)*CsI_res*
	ran.Gaus(0.,1.);
      
      if (useRealP)
	{
         recon->theta = real->theta;
         recon->phi = real->phi;
         recon->energy = real->energy;
	}

      recon->getVelocity();

    }

  if(fabs(real->A-1.)< 0.5 && recon->energy < p_thres[id]) is_hit = 0;

  return is_hit;




}
//**************************************************
bool CFrag::alphaHoleNe16(int itele, int ifront, int iback)
{


  if (itele == 0) //det0 done
    {
      float x = 1.;

      if (iback == 15) x *= .90;
      if (iback == 16) x *= .76;
      if (ifront == 14) x *= .96;
      if (ifront == 15) x *= .66;
      if (ifront == 31) x *= .98;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 1)//det1 done
    {
      float x = 1.;
      if (iback == 15) x *= .95;
      if (iback == 16) x *= .71;
      if (ifront == 15) x *= .68;
      if (ifront == 31) x *= .94;
      if (ran.Rndm() > x) return false;
    }    

  else if (itele == 2)//det2 done
    {
      float x = 1.;
      if (iback == 15) x *= .73;
      if (iback == 16) x *= .91;
      if (ifront == 15) x*= .68;
      if (ifront == 16) x*= .92;
      if (ifront == 31) x*=.96;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 3) //det3 done
    {
      float x = 1.;
      if (iback == 15) x*= .88;
      if (iback == 16) x*= .71;
      if (ifront == 15) x*= .68;
      if (ifront == 16) x*= .89;
      if (ifront == 31) x*= .97;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 4) //det4  done
    {
      float x = 1.;
      if (iback == 0) x *= .98;
      if (iback == 15) x*= .94;
      if (iback == 16) x*= .78;
      if (ifront == 15) x*=.70;
      if (ifront == 16) x*=.92;
      if (ifront == 31) x*= .95;
      if (ran.Rndm() > x) return false;

    }
  else if (itele == 5) //det5 done
    {
      float x = 1.;
      if (iback == 15) x*=.67;
      if (ifront == 0) x*=.97;
      if (ifront == 15) x*=.78;
      if (ifront == 16) x*=.83;
      if (ifront == 31) x*=.93;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 6) //det 6 done 
    {
      float x = 1.;
      if (iback == 15) x*=.84;
      if (iback == 16) x*=.89;
      if (iback == 31) x*=.97;
      if (ifront == 15) x*=.82;
      if (ifront == 16) x*=.72;

      if (ran.Rndm() > x) return false;
    }
  else if (itele == 7) //det 7 done
    {
      float x = 1.;
      if (iback == 15) x*=.93;
      if (iback == 16) x*=.66;
      if (ifront == 15) x*=.81;
      if (ifront == 16) x*=.77;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 8) //det 8 done
    {
      float x = 1.;
      if (iback == 15) x*=.72;
      if (ifront == 0) x*= .95;
      if (ifront == 15) x*= .72;
      if (ifront == 16) x*= .9;
      if (ifront == 31) x*= .91;

      if (ran.Rndm() > x) return false;
    }
  else if (itele == 9) //det 9 done
    {

      float x = 1.;
      if (iback == 15) x *= .77;
      if (iback == 16) x*= .89;
      if (iback == 31) x*=.99;
      if (ifront == 15)x*=.81;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 10) //det 10 done 
    {
      float x = 1.;
      if (iback == 15) x*= .90;
      if (iback == 16) x*= .71;
      if (ifront == 15) x*=.66;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 11) //det 11 done
    {
      float x = 1.;
      if (iback == 17) x*= .47;
      if (ifront == 0) x*=.95;
      if (ifront == 15) x*=.96;
      if (ifront == 16) x*= .69;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 12) //det 12  done
    {
      if (ifront == 4) return false;
      if (ifront == 31) return false;
          
      float x = 1.;
      if (iback == 15) x*= .84;
      if (iback == 16) x*=.82;
      if (iback == 31) x*=.93;
      if (ifront == 16) x*=.70;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 13) //det 13 
    {
      float x = 1.;
      if (iback == 15) x*= .96;
      if (iback == 16) x*=.70;
      if (iback == 31) x*=.96;

      if (ifront == 16) x*=.62;
      if (ran.Rndm() > x) return false;
    }

  return true;
}
//**************************************************
bool CFrag::protonHoleNe16(int itele, int ifront, int iback)
{


  if (itele == 0) //det0 done
    {
      float x = 1.;

      if (iback == 0) x *= .92;
      if (iback == 14) x *= .89;
      if (iback == 15) x *= .74;
      if (iback == 31) x *= .90;
      if (ifront == 14) x *= .91;
      if (ifront == 15) x *= .74;
      if (ifront == 16) x *= .96;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 1)//det1 done
    {
      float x = 1.;
      if (iback == 0) x *= .93;
      if (iback == 15) x *= .91;
      if (iback == 16) x *= .73;
      if (iback == 18) x *= .98;
      if (iback == 31) x *= .89;
      if (ifront == 14) x *= .89;
      if (ifront == 15) x *= .77;
      if (ifront == 16) x *= .97;
      if (ifront == 31) x *= .93;
      if (ran.Rndm() > x) return false;
    }    

  else if (itele == 2)//det2 done
    {
      float x = 1.;
      if (iback == 0) x *= .98;
      if (iback == 15) x *= .77;
      if (iback == 16) x *= .87;
      if (iback == 31) x*= .95;
      if (ifront == 0) x*= .91;
      if (ifront == 13) x*= .94;
      if (ifront == 15) x*= .69;
      if (ifront == 16) x*= .92;
      if (ifront == 31) x*=.93;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 3) //det3 done
    {
      float x = 1.;
      if (iback == 0) x *= .93;
      if (iback == 15) x*= .90;
      if (iback == 16) x*= .717;
      if (iback == 31) x*= .94;
      if (ifront == 0) x*= .92;
      if (ifront == 15) x*= .72;
      if (ifront == 16) x*= .87;
      if (ifront == 31) x*= .92;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 4) //det4 done
    {
      float x = 1.;
      if (iback == 0) x *= .96;
      if (iback == 15) x*= .95;
      if (iback == 16) x*= .73;
      if (iback == 31) x*= .95;
      if (ifront == 0) x*=.91;
      if (ifront == 15) x*=.74;
      if (ifront == 16) x*=.91;
      if (ifront == 31) x*= .93;
      if (ran.Rndm() > x) return false;

    }
  else if (itele == 5) //det5 done
    {
      float x = 1.;
      if (iback == 0) x*= .91;
      if (iback == 10) x*= .96;
      if (iback == 15) x*=.70;
      if (iback == 16) x*=.95;
      if (iback == 31) x*=.94;
      if (ifront == 0) x*=.91;
      if (ifront == 15) x*=.77;
      if (ifront == 16) x*=.80;
      if (ifront == 31) x*=.88;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 6) //det 6 done
    {
      float x = 1.;
      if (iback == 0) x*= .92;
      if (iback == 15) x*=.79;
      if (iback == 16) x*=.85;
      if (iback == 31) x*=.90;
      if (ifront == 0) x*=.88;
      if (ifront == 15) x*=.85;
      if (ifront == 16) x*=.72;
      if (ifront == 30) x*=.82;
      if (ifront == 31) x*=.87;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 7) //det 7
    {
      if (iback == 13) return false;
      float x = 1.;
      if (iback == 15) x*=.87;
      if (iback == 16) x*=.70;
      if (ifront == 2) x*=.93;
      if (ifront == 15) x*=.84;
      if (ifront == 16) x*=.80;
      if (ifront == 25) x*=.90;
      if (ifront == 26) x*=.95;
      if (ifront == 31) x*=.56;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 8) //det 8 done
    {
      float x = 1.;
      if (iback == 0) x *= .98;
      if (iback == 15) x*=.97;
      if (iback == 16) x*=.75;
      if (iback == 17) x*=.98;
      if (ifront == 0) x*= .97;
      if (ifront == 15) x*= .75;
      if (ifront == 16) x*= .86;
      if (ifront == 31) x*= .95;

      if (ran.Rndm() > x) return false;
    }
  else if (itele == 9) //det 9 done
    {

      float x = 1.;
      if (iback == 15) x *= .8;
      if (iback == 16) x*= .89;
      if (iback == 31) x*=.99;
      if (ifront == 15)x*=.96;
      if (ifront == 16)x*=.77;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 10) //det 10 done
    {
      float x = 1.;
      if (iback == 0) x *= .98;
      if (iback == 15) x*= .85;
      if (iback == 16) x*= .75;
      if (iback == 31) x*= .98;
      if (ifront == 0) x*=.97;
      if (ifront == 15) x*=.95;
      if (ifront == 16) x*=.71;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 11) //det 11 done
    {
      float x = 1.;
      if (iback == 0) x*= .97;
      if (iback == 31) x*=.96;
      if (ifront == 0) x*=.95;
      if (ifront == 15) x*=.90;
      if (ifront == 16) x*= .75;
      if (ifront == 31) x*=.95;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 12) //det 12  done
    {
      if (ifront == 4) return false;
          
      float x = 1.;
      if (iback == 0) x*= .94;
      if (iback == 15) x*= .84;
      if (iback == 16) x*=.81;
      if (iback == 31) x*=.93;
      if (ifront == 0) x*=.93;
      if (ifront == 5) x*=.91;
      if (ifront == 16) x*=.77;
      if (ran.Rndm() > x) return false;
    }
  else if (itele == 13) //det 13 done
    {
      float x = 1.;
      if (iback == 0) x*=.98;
      if (iback == 15) x*= .95;
      if (iback == 16) x*=.73;
      if (iback == 31) x*=.96;
      if (ifront == 0) x*=.94;
      if (ifront == 16) x*=.78;
      if (ran.Rndm() > x) return false;
    }

  return true;
}
