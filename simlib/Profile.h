#ifndef SEQ_PROFILE_H
#define SEQ_PROFILE_H
#include <complex>
#include "cwfcomp.H"
#include <iostream>

using namespace std;

class profile
{
 public:
  double Et;
  profile(double Et, double Er, int z1, int z2, int z3, double mu123, 
double ac123, int l1, double mu23, double ac23, int l2, double rwidth2_23, 
double B23);
  profile(double Er, int z1,int z2,double mu, double ac, int l, double rwidth2,
	  double B, double range =0);


  profile(double Er, double DE0, int z1, int z2, double mu,double ac, int l1, int l2, double rwidth2_1, double rwidth2_2, double B1, double B2); 

  profile(){};

  ~profile();

  double rand(double xran);
  double rand_2branches(double xran1,double xran2);

  double Gamma(double E, double Et, double r, double l, double mu, int z1, int z2, double rwidth2);
  double Shift(double E, double r, double l, double mu, int z1, int z2);


  int N;
  double gamma;
  double Er;
  int l;
  double *Profile;
  double *Earray;
  double *yarray;
  double *Parray;
  double dE;
  double P_l(double E, double r, double l, double mu, int z1, int z2);

  double* y1array;
  double* y2array;

  double B;  
  double DE;

  double getWigner(double, double);
 private:
  double Sommerfeld(double E, double mu, int z1, int z2);


  static const double hbarc;
  static const double amu;
  static const double pi;


  complex<double>F;
  complex<double>G;
  complex<double>FD;
  complex<double>GD;



};



#endif //SEQ_PROFILE_BE9_H
