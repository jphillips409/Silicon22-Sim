#include "frag.h"
#include "fragment.h"
#include <valarray>
#include "random.h"
#include "moscow.h"
#include "evtGen.h"
#include "profile.h"

struct prop
{
  double Erel;
  double Dvelocity;
  double plfTheta;
  double plfPhi;
  double plfVel;
  double thetaEmission;
};


/**
 *!\brief selects the veloity vectors of the secondary fragments
 */

class CDecay
{
 public:
  CFrame* frag6Be;
  double CosTheta_T;
  double x_T;
  double x_Y[2];
  double CosTheta_Y[2];

  void getJacobi(CFrame**,bool);
  void getJacobiPrimary();
  void getJacobiSecondary();
  


  bool einstein;
  static CRandom ran;
  CFrame *real[5]; 
  CFrame *recon[5];
  CFrame *plfRecon;
  CFrame *partCM[5];
  CFrag *frag[5];  //!< information about the decay fragments
  static double const pi; //!< 3.14159....

  CDecay(CFrag*,CFrag*,CFrag*,CFrag*,bool einstein0);
  ~CDecay();
  double getErelReal();
  double getErelRecon();
  double getErel(CFrame**);
  double getErelNewton(CFrame**);
  double getErelRel(CFrame**);

  void Mode_12O();
  void ModeMoscow();
  void ModeMicroCanonical();
  void ModeMicroCanonicalBe();
  void micro(int,CFrame**,double,double);
  void getEk6Be(CFrame**);
  double getEk3body(CFrame*,CFrame*,CFrame*);
  double getEk3bodyNewton(CFrame*,CFrame*,CFrame*);
  double getEk3bodyRel(CFrame*,CFrame*,CFrame*);
  double getEk3();
  void getEk6BeRecon();
  void getEk6BeReal();
  bool OnTopOf();
  bool OnTopOf3();
  bool leaveCsI();
  prop Recon;

  double  sumA;
  double ErelRecon; //!<reconstructed relative kinetic energy


  double aaRel;
  double ppRel[6];
  double aapRelMin;
  double aapRelMax;
  double pEnergyMin;
  double pEnergyMax;
  double ppThetaRel;
  static double const EkTot8B;
  static double const gamma8B;
  double Ek6Be[6];
  double aRatio;

  int Nsolution; //!< number of p-p pairs with correct 6Be energy
  int Isolution; //!< solution #

  moscow * Moscow;
  evtGen * EvtGen;
  evtGen * EvtGen_2p1;


  profile * Profile;
  void sequential(CFrame *frag1, CFrame * frag2,double ET);
  void ModeSequential();
  void ModeSequential_2plus_GSM();
  void ModeSequential_2plus_Holt();
  void ModeSequential_0plus();
  bool gamma_emitted;
  void Mode3Proton();
  double ET;
};
