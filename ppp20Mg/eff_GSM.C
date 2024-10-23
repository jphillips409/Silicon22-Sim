{
  //100 MeV/A
  double x[5]={450,500,550,600,650};
  double y[5]={.3488,.3779,.387,.3792,.356};

  TH2S frame("frame","",10,400,900,10,0,.4);
  frame.Draw();

  TGraph g(5,x,y);
  g.Draw("*C");

  //150 MeV/A
  double xx[5]={550,600,650,700,750};
  double yy[5]={.302,.325,.335,.336,.329};

  TGraph gg(5,xx,yy);
  gg.SetLineColor(2);
  gg.Draw("*C");


  //170 MeV/A
  double xxx[5]={650,700,750,800,850};
  double yyy[5]={.306,.3095,.3142,.3071,.295};

  TGraph ggg(5,xxx,yyy);
  ggg.SetLineColor(4);
  ggg.Draw("*C");

}
