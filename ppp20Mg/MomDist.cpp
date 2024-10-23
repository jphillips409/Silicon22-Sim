


#include "CMomDist.h"


CRandom CMomDist::random;
int const CMomDist::n=221;
int const CMomDist::nn=111;
/**
 * Constructor
 */
CMomDist::CMomDist()
{
  xArrayz = new float [n];
  yArrayz = new float [n];
  xArraytr = new float [nn];
  yArraytr = new float [nn];
  ifstream ifFilez("zn02_allM.out");
  if (ifFilez.fail()) 
    {
      cout << " could not open zn02_allM.out " << endl;
      abort();
    }

  for (int i=0;i<n;i++)
    {
      ifFilez >> xArrayz[i] >> yArrayz[i];
      if (ifFilez.eof()) abort();
      if (ifFilez.bad()) abort();
      if ( i > 0) yArrayz[i] += yArrayz[i-1];
    }

  for (int i=0;i<n;i++) yArrayz[i] /= yArrayz[n-1];
  ifFilez.close();

  if (false)
    {
  ifstream ifFiletr("2plus_trans.out");
  if (ifFiletr.fail())
    {
      cout << " could not open 2plus_trans.out " << endl;
      abort();
    }

  for (int j=0;j<nn;j++)
    {
      ifFiletr >> xArraytr[j] >> yArraytr[j];
      if (ifFiletr.eof()) abort();
      if (ifFiletr.bad()) abort();
      if ( j > 0) yArraytr[j] += yArraytr[j-1];
    }
  ifFiletr.close();
    }
  else
    {
  ifstream ifFiletr2("0plus_trans2.out");
  ifstream ifFiletr1("0plus_trans1.out");
  ifstream ifFiletr0("0plus_trans0.out");
  if (ifFiletr2.fail())
    {
      cout << " could not open 2plus_trans.out " << endl;
      abort();
    }

  double a, b;
  for (int j=0;j<nn;j++)
    {
      ifFiletr2 >> xArraytr[j] >> yArraytr[j];
      ifFiletr1 >> a >> b;
      yArraytr[j] += b;
      ifFiletr0 >> a >> b;
      yArraytr[j] += b;

      if (ifFiletr2.eof()) abort();
      if (ifFiletr2.bad()) abort();
      if ( j > 0) yArraytr[j] += yArraytr[j-1];
    }

    }
  for (int j=0;j<nn;j++) yArraytr[j] /= yArraytr[nn-1];



}
//******************************************************
  /**
   * Destructor
   */
CMomDist::~CMomDist()
{
  delete [] xArrayz;
  delete [] yArrayz;
  delete [] xArraytr;
  delete [] yArraytr;
}
//*******************************************
  /**
   * Select Momentum components of the parent in a Monte Carlo fashion
   */
float CMomDist::getTransMom()
{
  float probtr = random.Rndm();
  int i = 0;
  for (;;)
    {
      if (yArraytr[i] > probtr) break;
      i++;
      if (i == nn) break;
    }
  float xtr;
  if ( i==0) xtr = xArraytr[i];
  else xtr = xArraytr[i-1] + (xArraytr[i]-xArraytr[i-1])*random.Rndm();
  return xtr;
}

float CMomDist::getLongMom()
{
  float probz = random.Rndm();
  int i = 0;
  for (;;)
    {
      if (yArrayz[i] > probz) break;
      i++;
      if (i == n) break;
    }
  float xz;
  if ( i==0) xz = xArrayz[i];
  else xz = xArrayz[i-1] + (xArrayz[i]-xArrayz[i-1])*random.Rndm();
  return xz;
}
