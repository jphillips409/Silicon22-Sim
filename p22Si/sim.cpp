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
#include "TTree.h"
#include "TGraph.h"
//#include "CMomDist.h"


using namespace std;


int main()
{

  TFile f ("sim.root","RECREATE");
  int correct_ID = 0;
  int total_ID = 0;

  TH1I hist_PPara_22Si("PPara_22Si","",400,5000,20000);
  TH1I hist_fiber_x("Fiber_x","",76,-6.5,69.5);
  TH1I hist_fiber_y("Fiber_y","",76,-6.5,69.5);
  TH2S hist_theta_fiberx("theta_fiberx","",200,0,20,76,-6.5,69.5);

  TH1I hist_rigidity_22Si("rigidity_22Si","",860,1,3.3);
  TH1I hist_rigidity_22Si_before("rigidity_22Si_before","",860,1,3.3);
  TH1I hist_rigidity_23Si("rigidity_23Si","",860,1,3.3);
  TH1I hist_p_range("p_range","",200,0,140);
  TH1I hist_vel_23Si("vel_23Si","",100,8,14);
  TH1I hist_vel_22Si("vel_22Si","",100,8,14);
   TH1I hist_rigidity_22Al("rigidity_22Al","",860,1,4.);
  
  TH1I hist_vel("vel","vel",100,0.,14.);
  TH1I hist_theta("theta","theta",200,0,20);
  TH1I hist_phi("phi","phi",125,0,360);

  TH1I hist_vel_R("velR","vel",100,0.,14.);
  TH1I hist_theta_R("thetaR","theta",200,0,10);
  TH1I hist_phi_R("phiR","phi",125,0,360);
  TH1I hist_theta_emission_R("thetaEmissionR","thetaEmission",100,0,180);

  TH1I Li9_Mass("Li9_Mass","Li9_Mass",1000,8300.,8600.);

  TH1I alpha_mom("alpha_mom","",200,0,200);

  TH1I keAlpha("keAlpha","",1000,0,200);
  TH1I keProton("keProton","",1000,0,200);
  TH1I keProton_RCsI("keProton_RCsI","",1000,0,200);

  TH1I ke22Si("ke22Si","",1000,0,200);
  TH1I ke22Si_R("ke22Si_R","",1000,0,200);

  TH1I hist_Ppara_P("Ppara_P","",1000,-400,400);
  TH1I hist_Pperp1_P("Pperp1_P","",1000,-400,400);
  TH1I hist_Pperp2_P("Pperp2_P","",1000,-400,400);

  //10 keV bins
  TH1S hist_Erel("Erel","Erel",1000,0.,10.);
  TH1S hist_Erel_withGamma("Erel_withGamma","Erel",1000,0.,10.);
  TH1S hist_Erel_notarget("Erel_notarget","Erel",1000,0.,10.);
  TH1S hist_Erel_alternate("Erel_alternate","Erel_alternate",1000,0.,10.);
  TH1S hist_Erel_both("Erel_both","Erel_both",1000,0.,10.);
  TH2S map_ErelErel("Erel_Erel","",100,3,6,100,3,6);

  TH1S hist_Erel_25P("Erel_25P","",600,0,10);

  TH2I hist_Erel_thetaH("hist_Erel_thetaH","",200,0,20,25,-1,1);

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

  //Use this to iterate over different distances
  //To not iterate, program in the same distance for start and end
  double dist_start = 300; //mm from target
  double dist_end = 300; //mm from target
  double dist_incr = 10; //mm increment
  int dist_numb = (((int)dist_end - (int)dist_start)/((int)dist_incr)) + 1; //Number of distances 
  double dist_arr[dist_numb];

  double dist = dist_start;

  TTree *tree = new TTree("T","Efficiency Values");
  double eff_tot = 0;
  double distances[dist_numb];
  double eff_dist_tot[dist_numb];
  tree->Branch("eff_tot",&eff_tot,"eff_tot/D");
  tree->Branch("dist",&dist,"dist/D");

  for (int d=0;d < dist_numb; d++)
  {
    eff_tot = 0;
    dist = dist_start + dist_incr*d;

    distances[d] = dist;
    eff_dist_tot[d] = eff_tot;


  double Abeam = 23.;
  double EPAbeam = 100.;
  double Ebeam0 = Abeam*EPAbeam;
  double pc0 = sqrt(pow(Ebeam0+Abeam*m0,2) - pow(Abeam*m0,2));
  double P_acceptance = .02;
  double mass_target = Mass_9Be;

  //string detName("S11");
  string detName("gobbi");
  //string targetType("Si");
  string targetType("Be");

  bool bobhit = true;
  string range1("Hydrogen");
  range Range(range1);



  bool einstein = 1; //switch for newtonian(0) or relativistic(1) 

  string Loss1("Hydrogen.loss");
  string Loss3("Silicon.loss");


  string LossS("Silicon.loss");
  string LossAl("Aluminum_Be.loss");

  if (targetType == "Si")
    {
      Loss1 = "Hydrogen_Si.loss";
      Loss3 = "Silicon_Si.loss";
      LossS = "Sulfur_Si.loss";
       
    }

  string Loss_Si_in_BC400("Silicon_BC400.loss");
  CLoss loss_Si_in_BC400(Loss_Si_in_BC400,23.);

  string Loss_Al_in_BC400("Aluminum_BC400.loss");
  CLoss loss_Al_in_BC400(Loss_Al_in_BC400,22.);

  string Loss_Si22_in_BC400("Silicon_BC400.loss");
  CLoss loss_Si22_in_BC400(Loss_Si_in_BC400,22.);

  CLoss loss_Si(LossS,23.);
  CLoss loss_S26(LossS,26.);
  CLoss loss_Al(LossAl,22.);


  string LossHinAl("Hydrogen_Al.loss");
  CLoss loss_HinAl(LossHinAl,1.);
  string LossHinSi("Hydrogen_Si.loss");
  CLoss loss_HinSi(LossHinSi,1.);

  double t_factor = 2.;
  //int const Nevents =  100000*t_factor*.0172*.4*1.33*.6*.55*2.;
  //int const Nevents =  160000;
  int Nevents =  1000000;
  //if (EPAbeam == 100) Nevents = 1311;
  //if (EPAbeam == 85) Nevents = 1287; //Num events required to match proposal 

  double fiber_thickness = 103.2; //mg/cm2  for 1mm Bc400
  //double thickness = 188; //mg/cm2
  double thickness;
  thickness = 92.4*t_factor;
  //thickness= 94*t_factor;
  if (targetType == "Si")
    {
      thickness = 69*t_factor;  //69 mg/cm2 is 300 microns
    }
  double const beamRadius = 10.;
  double CsiRes = .1275;
  double straggle = 1.01;
  //double dist = 400.;
  double lifetime = 0.; //ns

  double de_protons_in_Al;
  double de_23Si_in_BC400 = 1.2972; // sigma of energy loss in fiber scintillator from LISE, not very beam energy dependent
  double de_22Al_in_BC400 = 1.2012; // sigma of energy loss in fiber scintillator from LISE, not very beam energy dependent
  double de_22Si_in_BC400 = 0; // sigma of energy loss in fiber scintillator from LISE, not very beam energy dependent
;
  double b_gobbi = 16;
  double thickAl0;  //  al absorber to stop beam in fro of Si.
  double thickSi0 = 348.18; // 1.5 mm of Si

  double Al_EPAbeam = 100;

  if (EPAbeam == 100) 
   {
     thickAl0 = 1351;
     de_protons_in_Al = .349;
     //dist = 300.;
     b_gobbi = 17.5;

     Al_EPAbeam = 94.52;

     de_22Si_in_BC400 = 1.2914; //roughly constant

   }
  else if (EPAbeam == 120) 
    {
      thickAl0 = 1351;
      de_protons_in_Al = .349;
      //dist = 504.;
      b_gobbi = 17.5;

      Al_EPAbeam = 113.484;

    }
  else if (EPAbeam == 85)
  {
     thickAl0 = 1351;
     de_protons_in_Al = .351;
     //dist = 300.;
     b_gobbi = 17.5;

     Al_EPAbeam = 80.31;

     de_22Si_in_BC400 = 1.2914; //roughly constant

  }
  else abort();

  //Al22 beam contaminant
  double Al_Ebeam0 = 22*Al_EPAbeam;
  double Al_pc0 = sqrt(pow(Al_Ebeam0+22*m0,2) - pow(22*m0,2));

  CPlf plf(thickness);
  CFrag frag1(1.,Mass_p/m0,Loss1,CsiRes,thickness,dist,b_gobbi,detName);
  CFrag frag2(14.,Mass_22Si/m0,Loss3,CsiRes,thickness,dist,b_gobbi,detName);

  CFrag frag4(14.,Mass_23Si/m0,LossS,CsiRes,thickness,dist,b_gobbi,detName);
  CFrag frag5(13.,Mass_22Al/m0,LossAl,CsiRes,thickness,dist,b_gobbi,detName); //Al22 beam contaminant

  CDecay decay(&frag1,&frag2,einstein);

  double Qbreakup = decay.EkTot8B;

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

  int NdetCleaner_1Half = 0;
  int Nevents_1Half = 0;
  int NdetCleaner_5Halves = 0;
  int Nevents_5Halves = 0;


  for (int i=0;i<Nevents;i++)
    {

      double pc = pc0 + pc0*(P_acceptance*frag4.ran.Rndm() - 0.01); //Applies + or - 2% p dispersion
      double Ebeam = sqrt(pow(pc,2) + pow(Abeam*m0,2)) - Abeam*m0;

      double Al_pc = Al_pc0 + Al_pc0*(P_acceptance*frag5.ran.Rndm() - 0.01); //Applies + or - 2% p dispersion
      double Al_Ebeam = sqrt(pow(Al_pc,2) + pow(22*m0,2)) - 22*m0;

      //unreacted Al beam

      frag5.real->energy = Al_Ebeam;
      frag5.real->theta = 0.;
      frag5.real->phi  = 0.;

      frag5.targetInteraction(thickness,thickness);
      frag5.real->energy = loss_Al_in_BC400.getEout(frag5.real->energy,fiber_thickness);

      frag5.real->getVelocityRel();
      double Al_rigidity = frag5.real->pcTot/1000.*3.3356/frag5.Z;
      hist_rigidity_22Al.Fill(Al_rigidity);

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
      double Etot = Ebeam_at_reaction  + Mass_23Si;

      //cout << "v_beam = " << v_beam  << " " << Ebeam_at_reaction/Abeam << " " << dthick << endl;


      double rTarget = beamRadius*sqrt(plf.ran.Rndm());
      double thetaTarget = 2.*acos(-1.)*plf.ran.Rndm();
      double xTarget = rTarget*sin(thetaTarget);
      double yTarget = rTarget*cos(thetaTarget);

      /*
      plf.GetPlf(v_beam);
      hist_Ppara_P.Fill(plf.P_para);
      hist_Pperp1_P.Fill(plf.P_perp1);
      hist_Pperp2_P.Fill(plf.P_perp2);
      //multiple scattering of plf
      if (thickness > 0.)  plf.MultiScat(1.-dthick/thickness);
      */
      /*
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
      */

      //find center of mass of target and projectile
      double p_cm = pc_beam;  //projectile momentum in Lab

      double E_cm = Etot + mass_target; //projectile energy in Lab

      double Vcm = p_cm/E_cm*c; //projectile velocity in Lab
      double gamma_cm = 1./sqrt(1.-pow(Vcm/c,2));
      //transform projectile to CM
      double pbeam_cm = (pc_beam - Etot*Vcm/c)*gamma_cm;   //projectile mom in com
      double Etot_cm = (Etot - Vcm/c*pc_beam)*gamma_cm;   //projectile energy in com 
      //transform target to CM
      double Etot_target_cm = sqrt(pow(pbeam_cm,2)+pow(mass_target,2));  //target energy in com

      double Esum_cm = Etot_cm + Etot_target_cm;







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
      int evttype;
      if (decay.ran.Rndm() < .25) 
      {
        decay.ModeFiveHalves_GSM();
        Nevents_5Halves++;
        evttype = 5;
      }
      else
      {
        decay.ModeOneHalf_GSM();
        Nevents_1Half++;
        evttype = 1;
      }
      //decay.ModeOneHalf_GSM();
      //decay.ModeFiveHalves_GSM();

     double mass_proj_star = 23.*m0 + mass_p + mass_22Si + decay.ET;
       double mass_target_star = Mass_9Li+ 27.;//22.;
       
       if (decay.ran.Rndm() < .182) 
	 {
           mass_target_star += decay.ran.Gaus(120.,35.);
	 }
       else if (decay.ran.Rndm() < .24)
	 {
           mass_target_star += decay.ran.Gaus(55.,20.);
	 }

       else if (decay.ran.Rndm() < .433) 
	 {
           mass_target_star += decay.ran.Gaus(25.,20.);
	 }
      double Ek_cm = Esum_cm - mass_target_star - mass_proj_star;

      Li9_Mass.Fill(mass_target_star);
     
      //find  momentum of target_star and projectile_star
      double mu = mass_proj_star*mass_target_star/(mass_proj_star+mass_target_star)/m0;
      double Vrel = sqrt(2.*Ek_cm/mu)*vfact;
      double v1  = mass_target_star/(mass_target_star+mass_proj_star)*Vrel;
      double v2  = Vrel - v1;


      double gamma1 = 1./sqrt(1.-pow(v1/c,2));
      pc = gamma1*v1*mass_proj_star/c;

      for (;;)
        {
          double E1 = sqrt(pow(pc,2)+pow(mass_proj_star,2))- mass_proj_star;
          double E2 = sqrt(pow(pc,2)+pow(mass_target_star,2))- mass_target_star;
          double y = E1 + E2  - Ek_cm;
          double dE1 = pc/sqrt(pow(pc,2)+pow(mass_proj_star,2));
          double dE2 = pc/sqrt(pow(pc,2)+pow(mass_target_star,2));
          double dy = dE1 + dE2;
          double dpc = - y/dy;
          if (fabs(dpc) < .0001) break;
          pc += dpc;
        }
      //Drop beam momentum by -3.5% due to charge exchange
      pc = pc - pc*0.035;
      v1 = pc/sqrt(pow(pc,2)+pow(mass_proj_star,2))*c;
      v2 = pc/sqrt(pow(pc,2)+pow(mass_target_star,2))*c;

      Etot_cm = sqrt(pow(pc,2)+pow(mass_proj_star,2));




      //select theta randomly from out theta_max
      double theta_max = 10.; //degrees
      theta_max *= acos(-1.)/180.;// radians

      double temp1 = 6.08;
      double temp2 = 11.83;
      double temp;

      if (decay.ran.Rndm() > 0.47) temp = temp1;
      else temp = temp2;

      double theta = temp/180.*pi*sqrt(-log(decay.ran.Rndm()+1.e-32));
      //if (decay.ran.Rndm() < .05) theta = decay.ran.Gaus(4./180.*pi,.7/180.*pi);

      //theta = acos(1.-(1.-cos(theta_max))*decay.ran.Rndm());

      double ppara = pc*cos(theta);
      double pperp = pc*sin(theta);

      //transform back to lab
      double ppara_lab = (ppara + Vcm/c*Etot_cm)*gamma_cm;
      double pperp_lab = pperp;
      Etot = (Etot_cm + Vcm/c*ppara)*gamma_cm;


      pc_beam = sqrt(pow(ppara_lab,2)+pow(pperp_lab,2));

      v_beam = pc_beam/Etot*c;

      double phi = 2.*pi*decay.ran.Rndm();
      double theta_lab = acos(ppara_lab/pc_beam);

	      plf.frame->v[0] = v_beam*sin(theta_lab)*cos(phi);
	      plf.frame->v[1] = v_beam*sin(theta_lab)*sin(phi);
	      plf.frame->v[2] = v_beam*cos(theta_lab);
        plf.frame->velocity = v_beam;
        plf.frame->theta = theta_lab;
        plf.frame->phi = phi;



      if (thickness > 0.)  plf.MultiScat(1.-dthick/thickness);



      hist_vel.Fill(plf.frame->velocity);
      hist_theta.Fill(plf.frame->theta*180./plf.pi);
      hist_phi.Fill(plf.frame->phi*180./plf.pi);





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


      ke22Si.Fill(frag2.real->energy/frag2.real->A);


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


      keProton_RCsI.Fill(E1);

      //cout << "fiber x: " << frag2.Fiber->Ix << " angle: " << frag2.real->theta*180./acos(-1.)<< " phi: " << frag2.real->phi*180./acos(-1.) << endl;


      double Elab3 = frag2.real->energy;
      Elab3 = loss_Si22_in_BC400.getEout(Elab3,fiber_thickness);
      Elab3 = decay.ran.Gaus(Elab3,de_22Si_in_BC400);
      double pc3 = sqrt(pow(Elab3+ frag2.mass*m0,2) -pow(frag2.mass*m0,2));
      hist_PPara_22Si.Fill(pc3);
      rigidity = pc3/1000.*3.3356/frag2.Z;
      
      ke22Si_R.Fill(frag2.real->energy/frag2.real->A);

      hist_rigidity_22Si_before.Fill(rigidity);
      hist_vel_22Si.Fill(c*pc3/(Elab3+frag2.mass*m0));
      if (EPAbeam == 100)
	{
          if (t_factor == 1)
	    {
             if(rigidity < 2.165*.975) continue;
            if(rigidity > 2.165*1.025 ) continue;
	    }
          if (t_factor == 2)
	    {
             if(rigidity < 2.04*.975) continue;
            if(rigidity > 2.04*1.025 ) continue;
	    }
	}

      if (EPAbeam == 85)
      {
        if (rigidity < 1.721 || rigidity > 1.81) continue;
      }  
      if (EPAbeam == 120)
      {
        if (rigidity < 2.252 || rigidity > 2.368) continue; 
      }
      //if (fabs((rigidity-2.271)/2.271) > .02) continue;
      hist_rigidity_22Si.Fill(rigidity);

      //Checks that the fiber index is realistic
      //64, 0.5 mm fibers
      int fiber_x = floor(frag2.Fiber->Ix+32);
      hist_fiber_x.Fill(fiber_x);
      hist_theta_fiberx.Fill(frag2.real->theta*180./acos(-1.),fiber_x);

      int fiber_y = floor(frag2.Fiber->Iy+32);
      hist_fiber_y.Fill(fiber_y);
      
      if (fiber_x < 0 || fiber_x > 63) continue;
      if (fiber_y < 0 || fiber_y > 63) continue;



      NdetClean++;
      if (evttype == 5) NdetCleaner_5Halves++;
      if (evttype == 1) NdetCleaner_1Half++;


      frag1.recon->getVelocity();
      frag2.recon->getVelocity();
      double ErelR_notarget = decay.getErelRecon();
      hist_Erel_notarget.Fill(ErelR_notarget);


      //correct for energy loss in half of target and get velocity
      frag1.Egain(thickness/2.);
      frag2.Egain(thickness/2.);

      double ErelR = decay.getErelRecon();

      hist_Erel_thetaH.Fill(ErelR,decay.cos_thetaH);

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
  eff_tot = (double)NdetClean/(double)Nevents;
  tree->Fill();
  cout << "Clean counts for 1/2+ = " << NdetCleaner_1Half << endl;
  cout << "Clean counts for 5/2+ = " << NdetCleaner_5Halves << endl;
  cout << "clean detection efficiency (separate stips and Csi) = " 
       << (double)NdetClean/(double)Nevents << endl;
  cout << "clean detection efficiency (separate stips and Csi) for 1/2+ = " << (double)NdetCleaner_1Half/(double)Nevents_1Half << endl;
  cout << "clean detection efficiency (separate stips and Csi) for 5/2+ = " << (double)NdetCleaner_5Halves/(double)Nevents_5Halves << endl;

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


    eff_dist_tot[d] = eff_tot;

  }

  auto gDistEff = new TGraph(dist_numb,distances,eff_dist_tot);
  
  tree->Write();
  gDistEff->Draw("AC");
  gDistEff->Write();


  f.Write();

}
