#include "plf.h"
#include <iostream>
#include "TH1S.h"
#include "TH1I.h"
#include "TH2S.h"
#include "TFile.h"
#include "frag.h"
#include "decay.h"
#include "constants.h"
#include "loss.h"
#include "range.h"
//#include "CMomDist.h"


using namespace std;


int main()
{

  double Abeam = 23.;
  double EPAbeam = 100.;
  double Ebeam0 = Abeam*EPAbeam;
  double pc0 = sqrt(pow(Ebeam0+Abeam*m0,2) - pow(Abeam*m0,2));
  double P_acceptance = .02;


  //string detName("S11");
  string detName("gobbi");
  //string targetType("Si");
  string targetType("Be");

  bool bobhit = true;
  string range1("Hydrogen");
  range Range(range1);

  TFile f ("sim.root","RECREATE");
  int correct_ID = 0;
  int total_ID = 0;


  bool einstein = 1; //switch for newtonian(0) or relativistic(1) 

  string Loss1("Hydrogen.loss");
  string Loss3("Silicon.loss");


  string LossS("Silicon.loss");
 

  if (targetType == "Si")
    {
      Loss1 = "Hydrogen_Si.loss";
      Loss3 = "Silicon_Si.loss";
      LossS = "Sulfur_Si.loss";
       
    }

  string Loss_Si_in_BC400("Silicon_BC400.loss");
  CLoss loss_Si_in_BC400(Loss_Si_in_BC400,23.);

  string Loss_Si22_in_BC400("Silicon_BC400.loss");
  CLoss loss_Si22_in_BC400(Loss_Si_in_BC400,22.);

  CLoss loss_Si(LossS,23.);
  CLoss loss_S26(LossS,26.);





  string LossHinAl("Hydrogen_Al.loss");
  CLoss loss_HinAl(LossHinAl,1.);
  string LossHinSi("Hydrogen_Si.loss");
  CLoss loss_HinSi(LossHinSi,1.);

  double t_factor = 2.;
  int const Nevents =  100000*t_factor*.0172*.4*1.33*.6;

  double fiber_thickness = 103.2; //mg/cm2  for 1mm Bc400
  //double thickness = 188; //mg/cm2
  double thickness;
  thickness= 94*t_factor;
  if (targetType == "Si")
    {
      thickness = 69*t_factor;  //69 mg/cm2 is 300 microns
    }
  double const beamRadius = 10.;
  double CsiRes = .1275;
  double straggle = 1.01;
  double dist = 400.;
  double lifetime = 0.; //ns


  double de_protons_in_Al;
  double de_22Si_in_BC400 = 0; // sigma of energy loss in fiber scintillator from LISE, not very beam energy dependent
;
  double b_gobbi = 16;
  double thickAl0;  //  al absorber to stop beam in fro of Si.
  double thickSi0 = 348.18; // 1.5 mm of Si
  if (EPAbeam == 100) 
    {
      thickAl0 = 1351;
      de_protons_in_Al = .349;
      dist = 350.;
      b_gobbi = 17;
    }


  CPlf plf(thickness);
  CFrag frag1(1.,Mass_p/m0,Loss1,CsiRes,thickness,dist,b_gobbi,detName);
  CFrag frag2(14.,Mass_22Si/m0,Loss3,CsiRes,thickness,dist,b_gobbi,detName);

  CFrag frag4(14.,Mass_23Si/m0,LossS,CsiRes,thickness,dist,b_gobbi,detName);


  CDecay decay(&frag1,&frag2,einstein);

  double Qbreakup = decay.EkTot8B;

  TH1I hist_PPara_22Si("PPara_22Si","",400,5000,20000);

  TH1I hist_rigidity_22Si("rigidity_22Si","",860,1,3.3);
  TH1I hist_rigidity_22Si_before("rigidity_22Si_before","",860,1,3.3);
  TH1I hist_rigidity_23Si("rigidity_23Si","",860,1,3.3);
  TH1I hist_p_range("p_range","",200,0,140);
  TH1I hist_vel_23Si("vel_23Si","",100,8,14);
  TH1I hist_vel_22Si("vel_22Si","",100,8,14);
 
  
  TH1I hist_vel("vel","vel",100,0.,14.);
  TH1I hist_theta("theta","theta",200,0,20);
  TH1I hist_phi("phi","phi",125,0,360);

  TH1I hist_vel_R("velR","vel",100,0.,14.);
  TH1I hist_theta_R("thetaR","theta",200,0,10);
  TH1I hist_phi_R("phiR","phi",125,0,360);
  TH1I hist_theta_emission_R("thetaEmissionR","thetaEmission",100,0,180);

  TH1I alpha_mom("alpha_mom","",200,0,200);

  TH1I keAlpha("keAlpha","",1000,0,1000);
  TH1I keProton("keProton","",1000,0,200);

  TH1I hist_Ppara_P("Ppara_P","",1000,-400,400);
  TH1I hist_Pperp1_P("Pperp1_P","",1000,-400,400);
  TH1I hist_Pperp2_P("Pperp2_P","",1000,-400,400);


  TH1S hist_Erel("Erel","Erel",600,0.,10.);
  TH1S hist_Erel_withGamma("Erel_withGamma","Erel",600,0.,10.);
  TH1S hist_Erel_notarget("Erel_notarget","Erel",600,0.,10.);
  TH1S hist_Erel_alternate("Erel_alternate","Erel_alternate",600,0.,10.);
  TH1S hist_Erel_both("Erel_both","Erel_both",600,0.,10.);
  TH2S map_ErelErel("Erel_Erel","",100,3,6,100,3,6);

  TH1S hist_Erel_25P("Erel_25P","",600,0,10);


  TH1S hist_ppRel("ppRel","",500,-3,10);
  TH2S map_Erel_dthick("Erel_dthick","Erel_dthick",200,1.5,4.5,100,0,1000);
  TH2S map_Erel6Be_dthick("Erel6Be_dthick","Erel6Be_dthick",200,-1.,1.,100,0,1000);

  TH2S protonXY_s("protonXY_s","protonxy",250,-20,20,250,-13,13);
  TH2S protonXY_s_1("protonXY_s_1","protonxy",250,-20,20,250,-13,13);
  TH2S protonXY_s_2("protonXY_s_2","protonxy",250,-20,20,250,-13,13);
  TH2S protonXY_s_1o("protonXY_s_1o","protonxy",250,-20,20,250,-13,13);
  TH2S protonXY_s_2o("protonXY_s_2o","protonxy",250,-20,20,250,-13,13);
  TH2S protonXY_s_1i("protonXY_s_1i","protonxy",250,-20,20,250,-13,13);
  TH2S protonXY_s_2i("protonXY_s_2i","protonxy",250,-20,20,250,-13,13);
  TH2I protonCsI("protonCsI","protonCsI",16,-0.5,15.5,16,-0.5,15.5);

  TH2S coreXY_s("coreXY_s","alphaxy",250,-20,20,250,-13,13);
  TH2S coreXY_p("coreXY_p","alphaxy",250,-20,20,250,-13,13);

  TH1I hist_momDisttr("momDisttr","",100,-400,400);
  TH1I hist_momDistz("momDistz","",100,-400,400);
  CMomDist momDist;

  double mean =0.;
   double sig = 0.;


  int Ndet = 0;
  int NdetClean = 0;
  int NdetCleaner = 0;
  int NdetCleaner6 = 0;
  int NdetCleanerCen = 0;
  int Nmissingp = 0;
  int nguardring = 0;
  int highenergyprotons = 0;



  for (int i=0;i<Nevents;i++)
    {

      double pc = pc0*(1.-P_acceptance/2.) + plf.ran.Rndm()*P_acceptance*pc0;
      double Ebeam = sqrt(pow(pc,2) + pow(Abeam*m0,2)) - Abeam*m0;


      //unreacted beam



      frag4.real->energy = Ebeam;
      frag4.real->theta = 0.;
      frag4.real->phi  = 0.;

      frag4.targetInteraction(thickness,thickness);
      frag4.real->energy = loss_Si_in_BC400.getEout(frag4.real->energy,fiber_thickness);

      frag4.real->getVelocityRel();
      double rigidity = frag4.real->pcTot/1000.*3.3356/frag4.Z;
      hist_rigidity_23Si.Fill(rigidity);
      hist_vel_23Si.Fill(frag4.real->velocity);

      hist_momDisttr.Fill(momDist.getTransMom());
      hist_momDistz.Fill(momDist.getLongMom());
      if (i%3000 == 0) cout << '\xd' <<  i << flush;
      double dthick = thickness*plf.ran.Rndm();
      double dthick_beam = thickness - dthick;
      double Ebeam_at_reaction = loss_Si.getEout(Ebeam,dthick_beam);
      double pc_beam = sqrt(pow(Ebeam_at_reaction + Abeam*m0,2)-pow(Abeam*m0,2));
      double v_beam = pc_beam*c/(Ebeam_at_reaction + Abeam*m0);


      //cout << "v_beam = " << v_beam  << " " << Ebeam_at_reaction/Abeam << " " << dthick << endl;


      double rTarget = beamRadius*sqrt(plf.ran.Rndm());
      double thetaTarget = 2.*acos(-1.)*plf.ran.Rndm();
      double xTarget = rTarget*sin(thetaTarget);
      double yTarget = rTarget*cos(thetaTarget);

      plf.GetPlf(v_beam);
      hist_Ppara_P.Fill(plf.P_para);
      hist_Pperp1_P.Fill(plf.P_perp1);
      hist_Pperp2_P.Fill(plf.P_perp2);
      //multiple scattering of plf
      if (thickness > 0.)  plf.MultiScat(1.-dthick/thickness);


      double gamma_in = 1./sqrt(1.-pow(plf.frame->velocity/c,2));
      double mass26 = 26.*m0;
      double Ein26 = gamma_in*mass26 - mass26;
      double Eout26 = loss_S26.getEout(Ein26,dthick);
      double pout26 = sqrt(pow(Eout26+mass26,2) - pow(mass26,2));
      double vout26 = pout26/(Eout26+mass26)*c;
      double gamma_out = 1./sqrt(1.-pow(vout26/c,2));
      double gamma_average = (gamma_in+gamma_out)/2.;
      double time = -lifetime*gamma_average*log(plf.ran.Rndm()+DBL_MIN);
      double vel_average = (plf.frame->velocity+vout26)/2.;
      double dist_in_target = time*vel_average;
      double ddthick = dist_in_target/.1*thickness;   //in mg/cm2  .1 cm = 193 mg/cm2 for Be
      double dz = 0.;
      if (ddthick > dthick) //get out of target
	{
	  double dt = dthick/thickness*.1*vel_average;
          time = -lifetime*gamma_out*log(plf.ran.Rndm()+DBL_MIN);
	  dz = vout26*time;
	}



      dthick -= ddthick;

      hist_vel.Fill(plf.frame->velocity);
      hist_theta.Fill(plf.frame->theta*180./plf.pi);
      hist_phi.Fill(plf.frame->phi*180./plf.pi);


      //now beak up plf
      plf.isotropic();


      //decay.ModeMoscow(); //sequential micro+P26Be
      //decay.ModeMicroCanonical();

      /*
      if (decay.ran.Rndm() < .07)
	{	
	  decay.ModeOneHalf_Holt();
	}
      else if (decay.ran.Rndm() < .07 )
	{	
	  decay.ModeThreeHalves_Holt();
	}
      else 
	{
          decay.ModeFiveHalves_Holt();
	}
      */

      if (decay.ran.Rndm() < .25) decay.ModeFiveHalves_GSM();
      else decay.ModeOneHalf_GSM();
      //decay.ModeOneHalf_GSM();
      //decay.ModeFiveHalves_GSM();

      frag1.AddVelocity(plf.frame->v);
      frag2.AddVelocity(plf.frame->v);






      //interaction in target, continue if stopped
      if (dthick > 0)
	{
         if (frag1.targetInteraction(dthick,thickness)) continue;
         if (frag2.targetInteraction(dthick,thickness)) continue;
	}


      double thick_Al = thickAl0/cos(frag1.real->theta);
      double E11 = loss_HinAl.getEout(frag1.real->energy,thick_Al);
      E11 = decay.ran.Gaus(E11,de_protons_in_Al);
      double thick_Si = thickSi0/cos(frag1.real->theta);
      double E1 = loss_HinSi.getEout(E11,thick_Si);
      if (E1 != E1) continue;
      if (E1 <=0) continue;
      double p_range1 = Range.getRange(E1);
      double p_straggle1 = Range.getLateralStraggle();
      hist_p_range.Fill(p_range1*cos(frag1.real->theta));
      double p_longStraggle1 = Range.getLongitudinalStraggle();
      //probability of reaction is CsI
      double prob1 = 0.0354343*(p_range1/10.) - .0006678*pow(p_range1/10.,2);
      if (decay.ran.Rndm() < prob1) continue;
      p_range1 += decay.ran.Gaus(0,p_longStraggle1);
      hist_p_range.Fill(p_range1*cos(frag1.real->theta));





      double x = frag2.real->theta*180./plf.pi*cos(frag2.real->phi);
      double y = frag2.real->theta*180./plf.pi*sin(frag2.real->phi);
      coreXY_p.Fill(x,y);

      int nhit = 0;

      if (detName == "gobbi")
	{
          nhit = frag1.hitGobbi(xTarget,yTarget,p_range1*cos(frag1.real->theta),p_straggle1);
          nhit += frag2.hitGobbiFiber(xTarget,yTarget);
	}

      else if (detName == "S4" || detName == "S11")
        {

	  nhit = frag1.hit3(xTarget, yTarget, p_range1*cos(frag1.real->theta),p_straggle1);
        nhit += frag2.hit4(xTarget, yTarget);
        }
     





      if (nhit != 2) continue;



      Ndet++;











      double Elab3 = frag2.real->energy;
      Elab3 = loss_Si22_in_BC400.getEout(Elab3,fiber_thickness);
      double pc3 = sqrt(pow(Elab3+ frag2.mass*m0,2) -pow(frag2.mass*m0,2));
      hist_PPara_22Si.Fill(pc3);
      rigidity = pc3/1000.*3.3356/frag2.Z;
      
      hist_rigidity_22Si_before.Fill(rigidity);
      hist_vel_22Si.Fill(c*pc3/(Elab3+frag2.mass*m0));
      if (EPAbeam == 100)
	{
          if (t_factor == 1)
	    {
             if(rigidity < 2.165*.98) continue;
            if(rigidity > 2.165*1.02 ) continue;
	    }
          if (t_factor == 2)
	    {
             if(rigidity < 2.093*.98) continue;
            if(rigidity > 2.093*1.02 ) continue;
	    }
	}
      //if (fabs((rigidity-2.271)/2.271) > .02) continue;
      hist_rigidity_22Si.Fill(rigidity);





      NdetClean++;


      frag1.recon->getVelocity();
      frag2.recon->getVelocity();
      double ErelR_notarget = decay.getErelRecon();
      hist_Erel_notarget.Fill(ErelR_notarget);


      //correct for energy loss in half of target and get velocity
      frag1.Egain(thickness/2.);
      frag2.Egain(thickness/2.);

      double ErelR = decay.getErelRecon();


      keProton.Fill(E1);



      //double ErelR = decay.getEk5();
      hist_Erel.Fill(ErelR);
      if(decay.gamma_emitted)hist_Erel_withGamma.Fill(ErelR);
      hist_Erel_both.Fill(ErelR);
      hist_theta_R.Fill(decay.plfRecon->theta*180./3.1459);
      hist_vel_R.Fill(decay.plfRecon->velocity);




      for (int ii=0;ii<6;ii++)hist_ppRel.Fill(decay.ppRel[ii]);


      map_Erel_dthick.Fill(ErelR,dthick);
      hist_theta_R.Fill(180. - decay.plfRecon->theta*180./plf.pi);

       x = frag1.recon->theta*180./plf.pi*cos(frag1.recon->phi);
       y = frag1.recon->theta*180./plf.pi*sin(frag1.recon->phi);
      protonXY_s.Fill(x,y);

      x = frag2.recon->theta*180./plf.pi*cos(frag2.recon->phi);
      y = frag2.recon->theta*180./plf.pi*sin(frag2.recon->phi);
      coreXY_s.Fill(x,y);


      // if protons both in either inner ring or out ring
      // we might have ambiguity problems

      //cout << frag1.Ring->CsIring << " " << frag2.Ring->CsIring << endl;
      if((frag1.Ring->N_CsI < 4 &&  frag2.Ring->N_CsI < 4)
	 || (frag1.Ring->N_CsI >= 4 && frag2.Ring->N_CsI >= 4))
	{

	  //swap theta values
	  double theta1 = frag1.recon->theta; 
          double theta2 = frag2.recon->theta;

          frag1.recon->theta = theta2;
          frag2.recon->theta = theta1;

          frag1.recon->getVelocity();
          frag2.recon->getVelocity();

          double ErelR_alternate = decay.getErelRecon();
	  hist_Erel_alternate.Fill(ErelR_alternate);
	  hist_Erel_both.Fill(ErelR_alternate);
	  map_ErelErel.Fill(ErelR,ErelR_alternate);

	}

    }


  cout << "number with 1 lost proton " << (double)Nmissingp/(double)Nevents << endl;

  cout << "detection efficiency = " << (double)Ndet/(double)Nevents << endl;
  cout << "clean detection efficiency (separate stips and Csi) = " 
       << (double)NdetClean/(double)Nevents << endl;
//   cout << "final detection efficiency (protons stay in Csi) = " 
//        << (double)NdetCleaner/(double)Nevents << endl;
//   cout << "final detection efficiency (protons stat in Csi)6Li in det6 = " 
//        << (double)NdetCleaner6/(double)Nevents << endl;

//   cout << "final detection efficiency (protons stat in Csi)(3towers) = " 
//        << (double)NdetCleanerCen/(double)Nevents << endl;

  cout << "fraction of cores hitting guard ring = "  
       << (double)nguardring/(double)Nevents << endl;
  cout << "fraction of high energy protons being thrown out = "
       << (double)highenergyprotons/(double)Nevents << endl;

  mean = mean/(double)Ndet;
  sig = sig/(double)(Ndet-1) - (double)(Ndet)/(double)(Ndet-1)*pow(mean,2);
  sig = sqrt(sig);
  cout << "mean Erel= " << mean << " mean Ex " << mean+Qbreakup 
       << " sig= " << sig << " FWHM= " 
       << sig*2.35 << endl;
  

  cout << "correct identification of 6B3 p-p is " << 
    (double)correct_ID/(double)total_ID << " events= " <<  
    (double)total_ID/(double)NdetCleaner << endl;





  f.Write();

}
