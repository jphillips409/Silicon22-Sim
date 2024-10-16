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
Sty->SetPadBottomMargin(.16);
Sty->SetPadLeftMargin(.18);
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

 TCanvas canvas("plus2","",600,800);
 canvas.Divide(1,2);
 canvas.cd(1);

  double x[5]={10,12,14,16,18};
  double y[5]={1.982,1.673,3.199,4.79,1.277};

  TH2S framen("framen","",10,8,20,10,0,5);
  framen.GetXaxis()->SetTitle("N,Z");
  framen.GetYaxis()->SetTitle("E^{*}(2^{+}_{1}) (MeV)");

  framen.GetXaxis()->CenterTitle();
  framen.GetYaxis()->CenterTitle();

  framen.Draw();

  TGraph g(5,x,y);
  g.SetMarkerStyle(20);
  g.SetMarkerColor(2);
  g.SetLineColor(2);
  g.Draw("PL");

  double yp[2]={1.887,1.598};
  TGraph gp(2,x,yp);
  gp.SetMarkerStyle(20);
  gp.SetMarkerColor(4);
  gp.SetLineColor(4);
  gp.Draw("PL");

  TLatex tt;
  tt.SetTextSize(.08);
  tt.SetTextColor(2);
  tt.DrawLatex(10,4.2,"Z=8");
  tt.SetTextColor(4);
  tt.DrawLatex(10,3.8,"N=8");


  TLine ll;
  ll.SetLineStyle(2);
  ll.DrawLine(16,0,16,5);


  canvas.cd(2);
  //O24,Ne26,28Mg,30Si,32S,34Ar,36Ca
  double xx[7]={8,10,12,14,16,18,20};
  double yy[7]={4.79,2.018,1.473,2.235,2.230,2.091,3.045};

  TH2S framez("framez","",10,6,22,10,0,5);
  framez.GetXaxis()->SetTitle("N,Z");
  framez.GetYaxis()->SetTitle("E^{*}(2^{+}_{1}) (MeV)");

  framez.GetXaxis()->CenterTitle();
  framez.GetYaxis()->CenterTitle();

  framez.Draw();
  
  TGraph gg(7,xx,yy);
  gg.SetMarkerStyle(20);
  gg.SetMarkerColor(2);
  gg.SetLineColor(2);
  gg.Draw("PL");

  //28S,30S,32S,34S,36S,38S
  double xxz[6]={12,14,16,18,20,22};
  double yyz[6]={1.507,2.211,2.230,2.127,3.290,1.292};

  TGraph ggp(6,xxz,yyz);
  ggp.SetMarkerStyle(20);
  ggp.SetMarkerColor(4);
  ggp.SetLineColor(4);
  ggp.Draw("PL"); 

  ll.DrawLine(8,0,8,5);
  ll.DrawLine(20,0,20,5);

  tt.SetTextColor(2);
  tt.DrawLatex(10,4.2,"N=16");
  tt.SetTextColor(4);
  tt.DrawLatex(10,3.8,"Z=16");

}
