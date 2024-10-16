{


  TH2S frame("frame","",10,0,3,10,.1,.2);
  frame.Draw();
  int const N = 9;
  double x[N]={0.,.131,.164,.291,.329,.658,.940,1.31,2.91};
  double y[N]={.1093,.1096,.1098,.1101,.1111,.1152,.1189,.1234,.1313};
  double y_notarget[N]={.1931,.1847,.1829,.1797,.174,.1592,.1496,.1395,.1236};

  TGraph g(N,x,y);
  g.Draw("*l");

  TGraph g_notarget(N,x,y_notarget);
  g_notarget.SetLineColor(2);
  g_notarget.SetMarkerColor(2);
  g_notarget.SetMarkerStyle(20);
  g_notarget.Draw("LP");

  TF1 * funct = new TF1("funct","[0] + [1]*x + [2]*x*x +[3]*x*x*x",0,3);
  g_notarget.Fit(funct);
   
  double data[10];
  funct->GetParameters(data);
  funct->SetParameter(0,data[0]*(1.+1./sqrt(2000.)));
  funct->SetParameter(1,data[1]*(1.+1./sqrt(2000.)));
  funct->SetParameter(2,data[2]*(1.+1./sqrt(2000.)));
  funct->SetParameter(3,data[3]*(1.+1./sqrt(2000.)));

   funct->DrawCopy("same");

  funct->SetParameter(0,data[0]*(1.-1./sqrt(2000.)));
  funct->SetParameter(1,data[1]*(1.-1./sqrt(2000.)));
  funct->SetParameter(2,data[2]*(1.-1./sqrt(2000.)));
  funct->SetParameter(3,data[3]*(1.-1./sqrt(2000.)));

   funct->DrawCopy("same");

}
