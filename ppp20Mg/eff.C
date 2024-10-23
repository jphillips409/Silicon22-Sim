{

 gROOT->Reset();
  TStyle * Sty = new TStyle("MyStyle","MyStyle");
  Sty->SetOptTitle(0);
  Sty->SetOptStat(0);
  Sty->SetLineWidth(5);
  Sty->SetPalette(55);
  Sty->SetCanvasColor(10);
  Sty->SetCanvasBorderMode(0);
  Sty->SetFrameLineWidth(3);
  Sty->SetFrameFillColor(10);
  Sty->SetPadColor(10);
  Sty->SetPadTickX(1);
  Sty->SetPadTickY(1);
  Sty->SetPadBottomMargin(.15);
  Sty->SetPadTopMargin(.01);
  Sty->SetPadLeftMargin(.15);
  Sty->SetPadRightMargin(.03);
  Sty->SetHistLineWidth(3);
  Sty->SetFuncWidth(3);
  Sty->SetFuncColor(kGreen);
  Sty->SetLineWidth(3);
  Sty->SetLabelSize(0.04,"xyz");
  Sty->SetLabelOffset(0.01,"y");
  Sty->SetLabelOffset(0.02,"x");
  Sty->SetLabelColor(kBlack,"xyz");
  Sty->SetTitleSize(0.04,"xyz");
  Sty->SetTitleOffset(1.4,"y");
  Sty->SetTitleOffset(1.6,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.05,"xz");
  Sty->SetTickLength(.025,"y");
  Sty->SetNdivisions(10,"xyz");
  Sty->SetEndErrorSize(0);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();
  TCanvas canvas("eff_EPA");

  TH2S frame("farme","",10,35,600,10,0,15);
  frame.GetXaxis()->SetTitle("Si-target distance (mm)");
  frame.GetYaxis()->SetTitle("Efficiency (%)");
  frame.GetXaxis()->CenterTitle();
  frame.GetYaxis()->CenterTitle();
  frame.Draw();

  const int n = 5;
  double x[n]={400,450,525,550,600};
  double y[n]={8.8,10.1,10.6,10.3,9.1};;
  TGraph g(n,x,y);
  g.Draw("*");
  g.Fit("pol2");

  TLatex tt;
  tt.SetTextSize(.06);
  tt.DrawLatex(160,32,"^{22}Si_{2^{+}}#rightarrow2#it{p}+^{20}Mg");
}
