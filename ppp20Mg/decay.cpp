#include <cmath>
#include "constants.h"
#include "decay.h"

CRandom CDecay::ran;
double const CDecay::pi = acos(-1.);
double const CDecay::EkTot8B = 2.842; // energy released in 8B IAS decay to 6LI IAS
double const CDecay::gamma8B = 0.00075;


//string decayType("2plus");
string decayType("0plus");
//string decayType("0plus_low");
//string decayType("0plus+2plus");
//************************************************************
//momentum correlation from 12O_gs experiment
void CDecay::Mode_12O()
{
  gamma_emitted = false;
  if (decayType == "0plus")
    {
     double EkTot = 1.7526;  //AME2016   
    EvtGen->getEvent(false,EkTot);
    }
  else if (decayType == "0plus_low")
    {
     double EkTot = .9; 
    EvtGen->getEvent(false,EkTot);
    }
  else if (decayType == "2plus")
    {
     double EkTot = 1.7526+2.018;  //AME2016   
    EvtGen_2p1->getEvent(false,EkTot);
    }
  else if (decayType == "0plus+2plus")
    {
      if (ran.Rndm() < 0.5)
	{
        double EkTot = 1.7526;  //AME2016   
        EvtGen->getEvent(false,EkTot);
	}
      else 
	{
          double EkTot = 1.7526+2.018;  //AME2016   
          EvtGen_2p1->getEvent(false,EkTot);

	}
    }
}

/**
 * Constructor
\param part10 is a pointer to particle 1
\param part20 is a pointer to particle 2
\param part30 is a pointer to particle 3

 */
CDecay::CDecay(CFrag * part10, CFrag *part20, CFrag* part30, CFrag* part40, 
	       bool einstein0)
{

  frag6Be = new CFrame (6);

  einstein = einstein0;
  CFrame::einstein = einstein;

  frag[0] = part10;
  frag[1] = part20;
  frag[2] = part30;
  frag[3] = part40;




  real[0] = part10->real;
  real[1] = part20->real;
  real[2] = part30->real;
  real[3] = part40->real;




  recon[0] = part10->recon;
  recon[1] = part20->recon;
  recon[2] = part30->recon;
  recon[3] = part40->recon;



  sumA = 0.;
  for (int i=0;i<4;i++) sumA += real[i]->A;

  plfRecon = new CFrame(sumA);


  for (int i=0;i<4;i++) 
    {
     partCM[i] = new CFrame(real[i]->A);
    }
 

  string name("6be_p2_new.dat");
  Moscow = new moscow(name);
  name = "/home/Argon30/simlib/T_0p1.dat";
  EvtGen = new evtGen(50,50,name,&ran,0.,real,Mass_p,Mass_24Si,0);
  name = "/home/Argon30/simlib/T_2p1.dat";
  EvtGen_2p1 = new evtGen(50,50,name,&ran,0.,real,Mass_p,Mass_24Si,0);


  /* original 
  double ET0 = 3.199   - 1.261;
  int l = 0;
  int z1 = 1;
  int z2 = 13;
  double mu = 1.*21./22.;
  double ac = 1.4*(pow(21,.3333)+1.);

  double rwidth2_23 = 28./mu/pow(ac,2); //wigner
  double B23 = 999;
  double range = 10;
  Profile = new profile(ET0,z1,z2,mu,ac,l,rwidth2_23,B23,range);
  */

 
  double ET0 = 1.137;
  int l = 0;
  int z1 = 1;
  int z2 = 13;
  double mu = 1.*21./22.;
  double ac = 1.4*(pow(21,.3333)+1.);

  double rwidth2_23 = .000000000000001/mu/pow(ac,2); //wigner
  double B23 = 999;
  double range = 10;
  Profile = new profile(ET0,z1,z2,mu,ac,l,rwidth2_23,B23,range);
  
}




//*********************************************************
  /**
   * Destructor
   */
CDecay::~CDecay()
{
  for (int i=0;i<5;i++) delete partCM[i];
  delete plfRecon;
  delete Moscow;
  delete EvtGen;
  delete EvtGen_2p1;
  delete Profile;





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



  for (int i=0;i<3;i++) 
   {
     plfRecon->pc[i] = 0.;
     for (int j=0;j<4;j++)plfRecon->pc[i] += part[j]->pc[i];
   }
  plfRecon->totEnergy = 0;
  for (int j=0;j<4;j++) plfRecon->totEnergy += part[j]->totEnergy;
  plfRecon->getVelocityFromMom();


  plfRecon->velocity = sqrt(pow(plfRecon->v[0],2)+pow(plfRecon->v[1],2)
		    +pow(plfRecon->v[2],2));
  plfRecon->theta = acos(plfRecon->v[2]/plfRecon->velocity);



  for (int j=0;j<4;j++)
    for (int i=0;i<3;i++) partCM[j]->v[i] = part[j]->v[i];

  ErelRecon = 0.;
   for (int j=0;j<4;j++)
     {
       partCM[j]->transformVelocity(plfRecon->v);
       ErelRecon += partCM[j]->getEnergy();
     }


   return ErelRecon;


   //p-p relative
   int ii = 0;
   for (int i=0;i<1;i++)
     {
       for (int j=i+1;j<2;j++)
	 {
           for (int k=0;k<3;k++) 
             {
               plfRecon->pc[k] = part[i]->pc[k]+part[j]->pc[k];
	     }
          plfRecon->totEnergy = part[i]->totEnergy
                                + part[j]->totEnergy;
          plfRecon->getVelocityFromMom();
          for (int k=0;k<3;k++) 
	    {
             partCM[i]->v[k] = part[i]->v[k];   
             partCM[j]->v[k] = part[j]->v[k];   
	    }
             ppRel[ii] = 0.;

             partCM[i]->transformVelocity(plfRecon->v);
             ppRel[ii] += partCM[i]->getEnergy();

             partCM[j]->transformVelocity(plfRecon->v);
             ppRel[ii] += partCM[j]->getEnergy();
	     ii++;
	 }
     }


  for (int i=0;i<3;i++) 
   {
     plfRecon->pc[i] = 0.;
     for (int j=0;j<4;j++)plfRecon->pc[i] += part[j]->pc[i];
   }
  plfRecon->totEnergy = 0;
  for (int j=0;j<2;j++) plfRecon->totEnergy += part[j]->totEnergy;
  plfRecon->getVelocityFromMom();


  for (int j=0;j<2;j++)
    for (int i=0;i<3;i++) partCM[j]->v[i] = part[j]->v[i];

  double ErelReconA = 0.;
   for (int j=0;j<2;j++)
     {
       partCM[j]->transformVelocity(plfRecon->v);
       ErelReconA += partCM[j]->getEnergy();
     }

   aRatio = ErelReconA/ErelRecon;


}
//*************************************************************
  /**
   * The momentum of the five fragments are chosen randomly from the 
   * allowable phase space.
   */
void CDecay::ModeMicroCanonical()
{
  gamma_emitted = false;
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



//************************************************************
  /**
   * checks to see if each of the five fragments go into separate Si strips
   * (both front and back) and separate CsI crystals 
   */
bool CDecay::OnTopOf()
{


  
  //for inner two detectors consider 3x3 array of CsI
  for (int i=0;i<3;i++)
    {
      if (frag[i]->Array->hitTower != 2) continue;
      if (frag[i]->Array->Tower[2]->hitTele == 1)
        frag[i]->Array->Tower[2]->Tele[1]->ICsI = 
	  frag[i]->Array->Tower[2]->Tele[1]->ICsI3; 
      if (frag[i]->Array->Tower[2]->hitTele == 2)
        frag[i]->Array->Tower[2]->Tele[2]->ICsI = 
	  frag[i]->Array->Tower[2]->Tele[2]->ICsI3; 

      if (frag[i]->shadowArray->hitTower != 2) continue;
      if (frag[i]->shadowArray->Tower[2]->hitTele == 1)
        frag[i]->shadowArray->Tower[2]->Tele[1]->ICsI = 
	  frag[i]->shadowArray->Tower[2]->Tele[1]->ICsI3; 
      if (frag[i]->shadowArray->Tower[2]->hitTele == 2)
        frag[i]->shadowArray->Tower[2]->Tele[2]->ICsI = 
	  frag[i]->shadowArray->Tower[2]->Tele[2]->ICsI3; 
    }
  

  for (int i=0;i<2;i++)
    for (int j=i+1;j<3;j++)
      {
	if (frag[i]->Array->hitTower == frag[j]->Array->hitTower)
	  {
	    int itower = frag[i]->Array->hitTower;
            if (frag[i]->Array->Tower[itower]->hitTele 
                 == frag[j]->Array->Tower[itower]->hitTele) 
	      {
		int itele = frag[i]->Array->Tower[itower]->hitTele;
                int icsi1 = frag[i]->Array->Tower[itower]->Tele[itele]->ICsI;
                int icsi2 = frag[j]->Array->Tower[itower]->Tele[itele]->ICsI;
		if (icsi1 == icsi2) return 1;
                int ix1 = frag[i]->Array->Tower[itower]->Tele[itele]->ixStrip;
                int ix2 = frag[j]->Array->Tower[itower]->Tele[itele]->ixStrip;
		if (ix1 == ix2) return 1;
                int iy1 = frag[i]->Array->Tower[itower]->Tele[itele]->iyStrip;
                int iy2 = frag[j]->Array->Tower[itower]->Tele[itele]->iyStrip;
		if (iy1 == iy2) return 1;
	      }

	  }
      }

  return 0;
}






//**********************************************************************
  /**
   * checks to see if each of the four protons leaves its CsI
   */
bool CDecay::leaveCsI()
{
  for (int i=0;i<2;i++) //only protons
    {
      if (frag[i]->Array->hitTower != frag[i]->shadowArray->hitTower)
	{
	  cout << "shadow hit tower does not match" << endl;
          abort();
	}
      int itower = frag[i]->Array->hitTower;
      if (frag[i]->Array->Tower[itower]->hitTele 
                 != frag[i]->shadowArray->Tower[itower]->hitTele) 
	{
	  cout << "shadow hit detector does not match" << endl;
          abort();

	}
      int itele = frag[i]->Array->Tower[itower]->hitTele;
      if (frag[i]->Array->Tower[itower]->Tele[itele]->ICsI !=  
	  frag[i]->shadowArray->Tower[itower]->Tele[itele]->ICsI) return 1;     
    }
  return 0;
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
  gamma_emitted = false;
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

void CDecay::ModeSequential()

{
  double Ek2 = 0.;
  double Ek1 = 0.;
  gamma_emitted = false;
  for(;;)
    {
      Ek2= Profile->rand(ran.Rndm());
      Ek1 = Profile->Et - Ek2;
      if (Ek1 < 7. && Ek2 < 7.)break;
    }

  CFrame *  inter = new CFrame(frag[1]->mass/m0+frag[2]->mass/m0+Ek2);
  sequential(frag[0]->real,inter,Ek1);
  sequential(frag[1]->real,frag[2]->real,Ek2);

  for (int k=0;k<3;k++)
    {
      frag[1]->v[k] += inter->v[k];
      frag[2]->v[k] += inter->v[k];
    }
  delete inter;
}

void CDecay::ModeSequential_2plus_GSM()

{



  double Ek1 = .678;
  double Ek2 = 1.074;

  CFrame *  inter = new CFrame(frag[1]->real->mass/m0+frag[2]->real->mass/m0+Ek2/m0);
  sequential(frag[0]->real,inter,Ek1);
  sequential(frag[1]->real,frag[2]->real,Ek2);

  frag[1]->real->transformVelocity(inter->v);
  frag[2]->real->transformVelocity(inter->v);



  delete inter;
}

void CDecay::ModeSequential_2plus_Holt()

{



  double Ek1;
  for (;;)
    {
    Ek1 = ran.BreitWigner(1.137,.038);
    if (Ek1 > 0. && Ek1 < 7.) break;
    }
  double Ek2 = 1.696;

  CFrame *  inter = new CFrame(frag[1]->real->mass/m0+frag[2]->real->mass/m0+Ek2/m0);
  sequential(frag[0]->real,inter,Ek1);
  sequential(frag[1]->real,frag[2]->real,Ek2);

  frag[1]->real->transformVelocity(inter->v);
  frag[2]->real->transformVelocity(inter->v);



  delete inter;
}

void CDecay::Mode3Proton()

{

  double Ek1;
  for (;;)
    {
    Ek1 = ran.BreitWigner(1.2,.039);
    if (Ek1 > 0 && Ek1 < 5) break;
    }
  double Ek2 = .77;
  double Ek3 = 1.3;

  ET = Ek1 + Ek2 + Ek2;

  CFrame *  inter1 = new CFrame(frag[1]->real->mass/m0+frag[2]->real->mass/m0+frag[3]->real->mass/m0
				+ (Ek2+Ek3)/m0 );
  sequential(frag[0]->real,inter1,Ek1);

  CFrame *  inter2 = new CFrame(frag[2]->real->mass/m0+frag[3]->real->mass/m0
				+ Ek3/m0 );

  sequential(frag[1]->real,inter2,Ek2);
  frag[1]->real->transformVelocity(inter1->v);
  inter2->transformVelocity(inter1->v);
  delete inter1;

  sequential(frag[2]->real,frag[3]->real,Ek3);

  frag[2]->real->transformVelocity(inter2->v);
  frag[3]->real->transformVelocity(inter2->v);
  delete inter2;






}
