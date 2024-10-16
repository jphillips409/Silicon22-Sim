#include <string>
#include <fstream>
#include <iostream>
#include "fragment.h"

using namespace std;


class moscow
{
  private:
  int ntot;
  float A1;
  float A2;
  float A3;
  static const float constant;
  ifstream  ifFile;
 public:
  moscow(string);
  bool getEvent(float,fragment*);
};
