#include <cmath>
#include "constants.h"
#include "decay.h"

CRandom CDecay::ran;
double const CDecay::pi = acos(-1.);
double const CDecay::EkTot8B = 2.842; // energy released in 8B IAS decay to 6LI IAS
double const CDecay::gamma8B = 0.00075;



/**
 * Constructor
\param part10 is a pointer to particle 1
\param part20 is a pointer to particle 2
\param part30 is a pointer to particle 3

 */
CDecay::CDecay(CFrag * part10, CFrag* part20, 
	       bool einstein0)
{



  einstein = einstein0;
  CFrame::einstein = einstein;

  frag[0] = part10;
  frag[1] = part20;




  real[0] = part10->real;
  real[1] = part20->real;




  recon[0] = part10->recon;
  recon[1] = part20->recon;



  sumA = 0.;
  for (int i=0;i<2;i++) sumA += real[i]->A;

  plfRecon = new CFrame(sumA);


  for (int i=0;i<2;i++) 
    {
     partCM[i] = new CFrame(real[i]->A);
    }
 



  /*
  double Er =  1.265+1.22+.15;
  int l = 0;
  int z1 = 1;
  int z2 = 12;
  double mu = 1.*20./21.;
  double ac = 1.4*(pow(21,.3333)+1.);
  double rwidth2 = .81*41.863/mu/pow(ac,2); //wigner
  double B23 = 999;
  double range = 10;
  Profile = new profile(Er,z1,z2,mu,ac,l,rwidth2,B23,range);
  */

    double Er =  2.066;
  int l = 0;
  int z1 = 1;
  int z2 = 12;
  double mu = 1.*20./21.;
  double ac = 1.4*(pow(21,.3333)+1.);
  double rwidth2 = .9*41.863/mu/pow(ac,2); //wigner
  double B23 = 999;
  double range = 10;
  Profile = new profile(Er,z1,z2,mu,ac,l,rwidth2,B23,range);


  Er =  1.074+.395;

  rwidth2 = .35*41.863/mu/pow(ac,2); //wigner
  Profile2 = new profile(Er,z1,z2,mu,ac,l,rwidth2,B23,range);
}




//*********************************************************
  /**
   * Destructor
   */
CDecay::~CDecay()
{
  for (int i=0;i<2;i++) delete partCM[i];
  delete plfRecon;
  delete Profile;
  delete Profile2;



}
//**********************************************************
  /**
   * returns the reconstructed kinetical energy of the fragmens in their
   * center-of-mass frame using the real fragment velocities.
   */
double CDecay::getErelReal()
{
  return getErel(real);
}
//********************************************************
//*********************************************************
  /**
   * returns the reconstructed kinetical energy of the fragmens in their
   * center-of-mass frame using the reconstructed or detected
   *  fragment velocities. 
   */
double CDecay::getErelRecon()
{
  return getErel(recon);
}
//*********************************************************
double CDecay::getErel(CFrame** part)
{
  if (einstein) return getErelRel(part);
  else return getErelNewton(part);
}
//**********************************************************
  /** 
   * find the relative kinetic energy of the fragments in their
   * center-of-mass frame. Non-relativistic version
   \param part is a pointer to the fragments velocity vectors (real or reconstructed)
   */

double CDecay::getErelNewton(CFrame** part)
{

  for (int i=0;i<3;i++) 
   {
     plfRecon->v[i] = 0.;
     for (int j=0;j<3;j++)
           plfRecon->v[i] += part[j]->v[i]*part[j]->A;
     plfRecon->v[i] /= sumA;  
   }

  plfRecon->getEnergy();

  ErelRecon = 0.;

   for (int j=0;j<3;j++)
     {
       partCM[j]->velocity = 0.;
       for (int i=0;i<3;i++)
         {
          partCM[j]->v[i] = part[j]->v[i] - plfRecon->v[i];
          partCM[j]->velocity += pow(partCM[j]->v[i],2);
         }
       partCM[j]->energy = real[j]->A/2.*partCM[j]->velocity/pow(.9784,2);
       partCM[j]->velocity = sqrt(partCM[j]->velocity);
       ErelRecon += partCM[j]->energy;
     }

   return ErelRecon;

}

//**********************************************************
  /** 
   * find the relative kinetic energy of the fragments in their
   * center-of-mass frame. Relativistic version
   \param part is a pointer to the fragments velocity vectors (real or reconstructed)
   */
double CDecay::getErelRel(CFrame **part)
{


  //for simulations where heavy residue theta = 0;

  part[3]->pc[3] = part[3]->pc[1] + part[3]->pc[2] + part[3]->pc[3];
  part[3]->pc[1] = 0.;
  part[3]->pc[2] = 0.;

  //KYLE LOOK HERE THIS IS WHAT I CHANGED

  for (int i=0;i<3;i++) 
   {
     plfRecon->pc[i] = 0.;
     for (int j=0;j<2;j++)plfRecon->pc[i] += part[j]->pc[i];
   }
  plfRecon->totEnergy = 0;
  for (int j=0;j<2;j++) plfRecon->totEnergy += part[j]->totEnergy;
  plfRecon->getVelocityFromMom();


  plfRecon->velocity = sqrt(pow(plfRecon->v[0],2)+pow(plfRecon->v[1],2)
		    +pow(plfRecon->v[2],2));
  plfRecon->theta = acos(plfRecon->v[2]/plfRecon->velocity);



  for (int j=0;j<2;j++)
    for (int i=0;i<3;i++) partCM[j]->v[i] = part[j]->v[i];

  ErelRecon = 0.;
   for (int j=0;j<2;j++)
     {
       partCM[j]->transformVelocity(plfRecon->v);
       ErelRecon += partCM[j]->getEnergy();
     }


   float vv =0.;
   float vvH =0.;
   for(int i =0;i<3;i++)
     {
       vv += pow(partCM[0]->v[i],2);
       vvH += pow(partCM[1]->v[i],2);
     }
   vv = sqrt(vv);
   vvH = sqrt(vvH);
   cos_ptheta1 = partCM[0]->v[2]/vv;
   cos_thetaH = partCM[1]->v[2]/vvH;



   return ErelRecon;



}
//*************************************************************
  /**
   * The momentum of the five fragments are chosen randomly from the 
   * allowable phase space.
   */
void CDecay::ModeMicroCanonical()
{

  double EkTot;
//   for(;;)
//     {
//       EkTot = ran.BreitWigner(EkTot8B,gamma8B);
//          if( fabs(EkTot- EkTot8B) <  2.*gamma8B && EkTot > 0.) break;
//     }

  //EkTot = 2.12;  //Aaron
    EkTot = 1.7526;  //AME2016   
  micro(3,real,EkTot,sumA);
}



  //*****************************
    void CDecay::micro(int N,CFrame **Frag,double Ektot,double massTot)
{
  valarray <double> vcm(3);
  for (int i=0;i<N;i++)
    {

      Frag[i]->v[0] = ran.Gaus(0.,1.)/Frag[i]->A;
      Frag[i]->v[1] = ran.Gaus(0.,1.)/Frag[i]->A;
      Frag[i]->v[2] = ran.Gaus(0.,1.)/Frag[i]->A;
      
      for (int j=0;j<3;j++) vcm[j] += Frag[i]->v[j]*Frag[i]->A;
    }

  vcm /= massTot;

  double testTotal= 0.;
  for (int i=0;i<N;i++)
    {
      Frag[i]->velocity = 0.;
      for (int j=0;j<3;j++)
	{
	  Frag[i]->v[j] -= vcm[j];
          Frag[i]->velocity += pow(Frag[i]->v[j],2);
         }
      Frag[i]->energy = Frag[i]->A/2.*Frag[i]->velocity/pow(.9784,2);
      Frag[i]->velocity = sqrt(Frag[i]->velocity);
      testTotal += Frag[i]->energy;
    }
  double ratio = sqrt(Ektot/testTotal);
  for (int i=0;i<N;i++)
    {
      Frag[i]->velocity *= ratio;
      for (int j=0;j<3;j++) Frag[i]->v[j] *= ratio;
    }

}

//**********************************************************
  /**
   * Simulates the decay of 8C as two sequential prompt two-proton decays
   * passing through the 6Be ground state. The prompt decays are each 
   * treated as sampling available phase space.
   */
void CDecay::ModeMoscow()
{

  //avergae total kinetic energy for 6Be decay
  double const EkTot6Be = 1.3711;
  // width 
  double const gamma6Be = .092;

  //choose total kinetic 
  double EkTot;
  if (gamma6Be == 0.)EkTot= EkTot6Be;
  else
    {
     for (;;)
       {
         EkTot = ran.BreitWigner(EkTot6Be,gamma6Be);
         if( fabs(EkTot- EkTot6Be) <  2.*gamma6Be) break;
        }
    }


  CFrame ** Frag;
  Frag = new CFrame* [3];
  Frag[0] = new CFrame(1.);
  Frag[1] = new CFrame(1.);
  Frag[2] = new CFrame(4.);

  
  Moscow->getEvent(EkTot,Frag[2],Frag[1],Frag[0]);

  //look at correlations in Jacobi coordinates


  for (int i=0;i<3;i++)
    {
      real[0]->v[i] = Frag[0]->v[i];
      real[1]->v[i] = Frag[1]->v[i];
      real[2]->v[i] = Frag[2]->v[i];
    } 
  getJacobiPrimary();
}



//********************************************************************
double CDecay::getEk3body(CFrame* frag1, CFrame* frag2, CFrame* frag3)
{
  if (einstein) return getEk3bodyRel(frag1,frag2,frag3);
  else return getEk3bodyNewton(frag1,frag2,frag3);
}

//*********************************************************************
  /**
   * returns the relative kinetic energy of three fragments in their
   * center-of-mass frame. Non-relativistic version
   \param frag1 is a pointer to fragment 1 
   \param frag2 is a pointer to fragment 2 
   \param frag3 is a pointer to fragment 3 
   */
double CDecay::getEk3bodyNewton(CFrame* frag1, CFrame* frag2, CFrame* frag3)
{
  double totMass = frag1->A + frag2->A + frag3->A;
  
  CFrame frag1CM(frag1->A);
  CFrame frag2CM(frag2->A);
  CFrame frag3CM(frag3->A);

  double vcm[3] = {0.};
  double ek = 0;
  for (int i=0;i<3;i++)
    {
      vcm[i] += frag1->v[i]*frag1->A;
      vcm[i] += frag2->v[i]*frag2->A;
      vcm[i] += frag3->v[i]*frag3->A;
      vcm[i] /= totMass;

      frag1CM.v[i] = frag1->v[i] - vcm[i];
      frag2CM.v[i] = frag2->v[i] - vcm[i];
      frag3CM.v[i] = frag3->v[i] - vcm[i];
      
    }
      ek += frag1CM.getEnergy();
      ek += frag2CM.getEnergy();
      ek += frag3CM.getEnergy();

  return ek;
}
//*********************************************************
  /**
   * returns the relative kinetic energy of three fragments in their
   * center-of-mass frame. Relativistic version
   \param frag1 is a pointer to fragment 1 
   \param frag2 is a pointer to fragment 2 
   \param frag3 is a pointer to fragment 3 
   */
double CDecay::getEk3bodyRel(CFrame* frag1, CFrame* frag2, CFrame* frag3)
{
    double totMass = frag1->A + frag2->A + frag3->A;
    CFrame frame(totMass);

  for (int i=0;i<3;i++) 
   {
     frame.pc[i] = frag1->pc[i] + frag2->pc[i] + frag3->pc[i];
   }
  frame.totEnergy = frag1->totEnergy + frag2->totEnergy + frag3->totEnergy;
  frame.getVelocityFromMom();

  for (int i=0;i<3;i++)
    {
    frag6Be->pc[i] = frame.pc[i];
    frag6Be->v[i] = frame.pc[i]/frame.pcTot*frame.velocity;
    }
  frag6Be->totEnergy = frame.totEnergy;

  CFrame p1(frag1->A);
  CFrame p2(frag2->A);
  CFrame p3(frag3->A);
  for (int i=0;i<3;i++)
    {
      p1.v[i] = frag1->v[i];
      p2.v[i] = frag2->v[i];
      p3.v[i] = frag3->v[i];
   
    }

  p1.transformVelocity(frame.v);
  p2.transformVelocity(frame.v);
  p3.transformVelocity(frame.v);
  

  ErelRecon = p1.getEnergy() + p2.getEnergy() + p3.getEnergy();

  return ErelRecon;

}





//*******************
double CDecay::getEk3()
{
  return getEk3bodyRel(recon[0],recon[1],recon[2]);
}
//************************************************************


void CDecay::getJacobi(CFrame**part,bool com)
{
    double totMass = part[0]->A + part[1]->A + part[2]->A;

  CFrame p1(part[0]->A);
  CFrame p2(part[1]->A);
  CFrame p3(part[2]->A);
  double Etot;
  for (int i=0;i<3;i++)
    {
      p1.v[i] = part[0]->v[i];
      p2.v[i] = part[1]->v[i];
      p3.v[i] = part[2]->v[i];
   
    }

    if (com)
      {
       CFrame frame(totMass);


      for (int i=0;i<3;i++) 
       {
         frame.pc[i] = part[0]->pc[i] + part[1]->pc[i] + part[2]->pc[i];
       }
      frame.totEnergy = part[0]->totEnergy + part[1]->totEnergy + 
      part[2]->totEnergy;
      frame.getVelocityFromMom();



      p1.transformVelocity(frame.v);
      p2.transformVelocity(frame.v);
      p3.transformVelocity(frame.v);

      Etot = p1.getEnergy() + p2.getEnergy() + p3.getEnergy();
      }
    else
      {
	Etot = 0.;
	for (int i=0;i<3;i++) Etot += 0.5*p1.A*pow(p1.v[i]/.9784,2)
	  + 0.5*p2.A*pow(p2.v[i]/.9784,2) + 0.5*p3.A*pow(p3.v[i]/.9784,2);
      }
  
  //p-p relative velocity can use newton
  double vrel[3];
  double vrelative = 0.;
  double dot = 0.;
  double v3 = 0.;
  for (int i=0;i<3;i++)
    {
      vrel[i] = p1.v[i] - p2.v[i];
      vrelative += pow(vrel[i],2);
      dot += vrel[i]*p3.v[i];
      v3 += pow(p3.v[i],2);
    }
  vrelative = sqrt(vrelative);
  v3 = sqrt(v3);

  double Epp = 0.5*0.5*pow(vrelative/.9784,2);
  x_T = Epp/Etot;

  CosTheta_T = dot/v3/vrelative;


  //6Be-p1
  vrelative = 0.;
  dot = 0.;
  double v2 = 0.;
  for (int i=0;i<3;i++)
    {
      vrel[i] = p1.v[i] - p3.v[i];
      vrelative += pow(vrel[i],2);
      dot += vrel[i]*p2.v[i];
      v2 += pow(p2.v[i],2);
    }
  vrelative = sqrt(vrelative);
  v2 = sqrt(v2);

  double Epa = 0.5*28./29.*pow(vrelative/.9784,2);
  x_Y[0] = Epa/Etot;

  CosTheta_Y[0] = dot/v2/vrelative;


  //6Be-p2
  vrelative = 0.;
  dot = 0.;
  double v1 = 0.;
  for (int i=0;i<3;i++)
    {
      vrel[i] = p2.v[i] - p3.v[i];
      vrelative += pow(vrel[i],2);
      dot += vrel[i]*p1.v[i];
      v1 += pow(p1.v[i],2);
    }
  vrelative = sqrt(vrelative);
  v1 = sqrt(v1);

  Epa = 0.5*28./29.*pow(vrelative/.9784,2);
  x_Y[1] = Epa/Etot;

  CosTheta_Y[1] = dot/v1/vrelative;
}


void CDecay::getJacobiSecondary()
{
  getJacobi(recon,(bool)1);
}

void CDecay::getJacobiPrimary()
{
  getJacobi(real,(bool)0);
} 








//******************************************************
void CDecay::sequential(CFrame *frag1, CFrame * frag2,double ET)
{

  double mass1  = frag1->A;
  double mass2  = frag2->A;
  double mu = mass1*mass2/(mass1+mass2);
  double Vrel = sqrt(2.*ET/mu)*vfact;
  double v1  = mass2/(mass1+mass2)*Vrel;
  double v2  = Vrel - v1;


   double gamma1 = 1./sqrt(1.-pow(v1/c,2));
   float pc = gamma1*v1*mass1*m0/c;

   for (;;)
     {
       double E1 = sqrt(pow(pc,2)+pow(mass1*m0,2))- mass1*m0;
       double E2 = sqrt(pow(pc,2)+pow(mass2*m0,2))- mass2*m0;
       double y = E1 + E2  - ET;
       double dE1 = pc/sqrt(pow(pc,2)+pow(mass1*m0,2));
       double dE2 = pc/sqrt(pow(pc,2)+pow(mass2*m0,2));
       double dy = dE1 + dE2;
       double dpc = - y/dy;
       if (fabs(dpc) < .0001) break;
       pc += dpc;
     }
   v1 = pc/sqrt(pow(pc,2)+pow(mass1*m0,2))*c;
   v2 = pc/sqrt(pow(pc,2)+pow(mass2*m0,2))*c;


   double theta = acos(2.*ran.Rndm()-1.);
   double phi = 2.*acos(-1.)*ran.Rndm();


   frag1->v[0] = v1*sin(theta)*cos(phi);
   frag1->v[1] = v1*sin(theta)*sin(phi);
   frag1->v[2] = v1*cos(theta);

   frag2->v[0] = -v2*sin(theta)*cos(phi);
   frag2->v[1] = -v2*sin(theta)*sin(phi);
   frag2->v[2] = -v2*cos(theta);

}

void CDecay::ModeFiveHalves_Holt()

{
  double Er = 1.68;
  double gamma = .001;
  gamma_emitted = false;
  for (;;)
    {
     Ek = ran.BreitWigner(Er,gamma);
     if (Ek > 0. && Ek < 7) break;
    }
  sequential(frag[0]->real,frag[1]->real,Ek);

}

void CDecay::ModeThreeHalves_Holt()

{
  double Er = 1.68 + 1.405- 1.633;
  double gamma = .001;
  gamma_emitted = true;
  for (;;)
    {
     Ek = ran.BreitWigner(Er,gamma);
     if (Ek > 0. && Ek < 7) break;
    }
  sequential(frag[0]->real,frag[1]->real,Ek);

}

void CDecay::ModeOneHalf_Holt()

{
  /*
  double Er = 1.265+1.22;
  double gamma = 1.1;
  gamma_emitted = false;
  for (;;)
    {
     Ek = ran.BreitWigner(Er,gamma);
     if (Ek > 0. && Ek < 7) break;
    }
  */
  double Ek = Profile->rand(ran.Rndm());
  sequential(frag[0]->real,frag[1]->real,Ek);

}

void CDecay::ModeThreeHalves_GSM()

{
  double Er = 1.074+1.253;
  double gamma = .001;
  gamma_emitted = false;
  if (ran.Rndm() > .44)
    {
      gamma_emitted = true;
      Er -= 1.633;
    }
  for (;;)
    {
     Ek = ran.BreitWigner(Er,gamma);
     if (Ek > 0. && Ek < 7) break;
    }
  sequential(frag[0]->real,frag[1]->real,Ek);

}

void CDecay::ModeFiveHalves_GSM()

{
  double Er = 1.074;
  double gamma = .001;
  gamma_emitted = false;
  for (;;)
    {
     Ek = ran.BreitWigner(Er,gamma);
     if (Ek > 0. && Ek < 7) break;
    }
  sequential(frag[0]->real,frag[1]->real,Ek);

}




void CDecay::ModeOneHalf_GSM()

{
  
  double Er = 1.074+.395;
  double gamma = .160;
  gamma_emitted = false;
  for (;;)
    {
     Ek = ran.BreitWigner(Er,gamma);
     if (Ek > 0. && Ek < 7) break;
    }
  sequential(frag[0]->real,frag[1]->real,Ek);

}



