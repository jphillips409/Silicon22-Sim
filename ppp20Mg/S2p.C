{
TStyle * Sty = new TStyle("MyStyle","MyStyle");
Sty->SetOptTitle(0);
Sty->SetOptStat(0);
//Sty->SetPalette(8,0);
Sty->SetCanvasColor(10);
Sty->SetCanvasBorderMode(0);
Sty->SetFrameLineWidth(3);
Sty->SetFrameFillColor(10);
Sty->SetPadColor(10);
Sty->SetPadTickX(1);
Sty->SetPadTickY(1);
Sty->SetPadBottomMargin(.2);
Sty->SetPadLeftMargin(.2);
Sty->SetPadTopMargin(.05);
Sty->SetPadRightMargin(.05);
Sty->SetHistLineWidth(3);
Sty->SetHistLineColor(kRed);
Sty->SetFuncWidth(3);
Sty->SetFuncColor(kGreen);
Sty->SetLineWidth(3);
Sty->SetLabelSize(0.06,"xyz");
Sty->SetLabelOffset(0.02,"y");
Sty->SetLabelOffset(0.02,"x");
Sty->SetLabelColor(kBlack,"xyz");
Sty->SetTitleSize(0.06,"xyz");
Sty->SetTitleOffset(1.4,"y");
Sty->SetTitleOffset(1.3,"x");
Sty->SetTitleFillColor(10);
Sty->SetTitleTextColor(kBlack);
Sty->SetTickLength(.02,"xz");
Sty->SetTickLength(.015,"y");
Sty->SetNdivisions(5,"xyz");
Sty->SetEndErrorSize(0);
gROOT->SetStyle("MyStyle");
gROOT->ForceStyle();


 TCanvas canvas("S2p","",600,800);
 canvas.Divide(1,2);
 canvas.cd(1);
  //N=12
  double x[9]={10,11,12,13,14,15,16,17,18};
  double y[9]={26.398,24.060,20.486,13.964,7.785,6.384,3.363,.693,-2.280};

  TGraph g(9,x,y);

  TH2S frame("frame","",10,8,23,10,-3,27);
  frame.GetXaxis()->SetTitle("Z");
  frame.GetYaxis()->SetTitle("S_{2p} (MeV)");
  frame.GetXaxis()->CenterTitle();
  frame.GetYaxis()->CenterTitle();

  frame.Draw();

  g.SetMarkerStyle(20);
  g.Draw("PL");

  //N=10
  double xx[5]={10,11,12,13,14};
  double yy[5]={20.837,15.275,7.936,5.645,3.433};
  
  TGraph gg(5,xx,yy);
  gg.SetMarkerStyle(20);
  gg.SetMarkerColor(2);
  gg.SetLineColor(2);

  gg.Draw("PL");


  double xxx[3]={14,15,16};
  double yyy[3]={3.433,1.588,-1.755};
  TGraph ggg(3,xxx,yyy);
  ggg.SetLineColor(2);
  ggg.SetLineStyle(2);
  ggg.Draw("PL");
  


  //N=11
  double x4[5]={10,11,12,13,14};
  double y4[5]={23.642,19.741,14.319,9.445,5.277};
  TGraph g4(5,x4,y4);
  g4.SetMarkerStyle(20);
  g4.SetMarkerColor(4);
  g4.SetLineColor(4);
  g4.Draw("PL");

  double x5[4]={14,15,16,17};
  double y5[4]={5.277,3.556,1.278,-1.965};

  TGraph g5(4,x5,y5);
  g5.SetMarkerColor(4);
  g5.SetLineColor(4);
  g5.SetLineStyle(2);
  g5.Draw("PL");

  TLatex tt;
  tt.DrawLatex(15,22,"N=12");
  tt.SetTextColor(4);
  tt.DrawLatex(15,18,"N=11");
  tt.SetTextColor(2);
  tt.DrawLatex(15,14,"N=10");

  canvas.cd(2);

  double xt1[13]={10,11,12,13,14,15,16,17,18,19,20,21,22};
  double yt1[13]={34.020,32.520,29.676,23.861,18.423,17.536,14.946,12.158,10.007,8.661,8.087,8.058,6.990};


TH2S frame2("frame2","",10,8,23,10,-1,35);
  frame2.GetXaxis()->SetTitle("N");
  frame2.GetYaxis()->SetTitle("S_{2n} (MeV)");
  frame2.GetXaxis()->CenterTitle();
  frame2.GetYaxis()->CenterTitle();

  frame2.Draw();
  
  TGraph gt1(13,xt1,yt1);
  gt1.SetMarkerStyle(20);
  gt1.Draw("PL");

  double xt2[12]={10,11,12,13,14,15,16,17,18,19,20,21};
  double yt2[12]={28.50,23.626,17.125,15.564,14.069,13.024,9.709,7.056,5.324,4.793,4.162,3.360};


  TGraph gt2(12,xt2,yt2);
  gt2.SetMarkerStyle(20);
  gt2.SetMarkerColor(2);
  gt2.SetLineColor(2);
  gt2.Draw("PL");


  double xt3[11]={8,9,10,11,12,13,14,15,16,17,18};
  double yt3[11]={28.887,19.807,12.188,12.001,11.563,11.413,10.655,9.583,6.925,3.434,-.018};


  TGraph gt3(11,xt3,yt3);
  gt3.SetMarkerStyle(20);
  gt3.SetMarkerColor(6);
  gt3.SetLineColor(6);
  gt3.Draw("PL");


  tt.SetTextColor(1);
  tt.DrawLatex(16,30,"Z=12");
  tt.SetTextColor(2);
  tt.DrawLatex(16,26,"Z=10");
  tt.SetTextColor(6);
  tt.DrawLatex(16,22,"Z=8");
}
