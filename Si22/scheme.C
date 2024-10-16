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

 TCanvas canvas("level_22Si_HoltMichel");

 TH2S frame("frame","",10,0,3.0,10,-1,4.);
   frame.GetXaxis()->SetLabelSize(0.);
  frame.GetXaxis()->SetAxisColor(0.);

  frame.GetYaxis()->SetTitle("Energy (MeV)");
  frame.GetYaxis()->CenterTitle();
  frame.SetStats(kFALSE);
  frame.Draw();

  double shift = .3;


  TLine ll;
  ll.SetLineColor(2);
  //20Mg Holt
  ll.DrawLine(.1,0,.3,0);
  ll.DrawLine(.1,1.76,.3,1.76);
  //20Mg Michel
  ll.SetLineColor(4);
  ll.DrawLine(.4,0,.6,0);
  ll.DrawLine(.4,1.61,.6,1.61);
  //exp
  ll.SetLineColor(1);
  ll.DrawLine(.7,0,.9,0);
  ll.DrawLine(.7,1.598,.9,1.598);

  ll.SetLineColor(1);
  ll.SetLineStyle(2);
  ll.DrawLine(.3,1.76,.4,1.61);
  ll.DrawLine(.6,1.61,.7,1.598);

  ll.DrawLine(.3,0.,.4,0.);
  ll.DrawLine(.6,0.,.7,0.);

  ll.SetLineStyle(1);
  //21Al
  ll.SetLineColor(2);
  ll.DrawLine(.8+shift,0,1.+shift,0);
  ll.DrawLine(.8+shift,.52,1.+shift,.52);
  ll.DrawLine(.8+shift,1.276,1.+shift,1.276);
  ll.SetLineColor(4);
  ll.DrawLine(1.1+shift,0.,1.3+shift,0.);
  ll.DrawLine(1.1+shift,.382,1.3+shift,.382);
  ll.DrawLine(1.1+shift,1.24,1.3+shift,1.24);
  //21O
  ll.SetLineColor(1);
  ll.DrawLine(1.4+shift,0,1.6+shift,0.);
  ll.DrawLine(1.4+shift,1.22,1.6+shift,1.22);
  ll.SetLineStyle(2);
  ll.SetLineColor(1);
  ll.DrawLine(1.+shift,0.,1.1+shift,0.);
  ll.DrawLine(1.+shift,0.52,1.1+shift,.382);
  ll.DrawLine(1.+shift,1.276,1.1+shift,1.24);
  ll.DrawLine(1.3+shift,0.,1.4+shift,0.);
  ll.SetLineStyle(1);

  shift += .3;
  //22Si
  ll.SetLineColor(2);
  ll.DrawLine(1.5+shift,0,1.7+shift,0);
  ll.DrawLine(1.5+shift,2.791,1.7+shift,2.791);
  ll.SetLineColor(4);
  ll.DrawLine(1.8+shift,0.,2.0+shift,0.);
  ll.DrawLine(1.8+shift,1.74,2.+shift,1.74);

  //22O
  ll.SetLineColor(1);
  ll.DrawLine(2.1+shift,0.,2.3+shift,0.);
  ll.DrawLine(2.1+shift,3.199,2.3+shift,3.199);
  ll.SetLineColor(1);
  ll.SetLineStyle(2);
  ll.DrawLine(1.7+shift,0.,1.8+shift,0.);
  ll.DrawLine(2.+shift,0.,2.1+shift,0.);
  ll.DrawLine(1.7+shift,2.791,1.8+shift,1.74);
  ll.DrawLine(2.+shift,1.74,2.1+shift,3.199);

  TLatex tt;
  tt.SetTextSize(.07);
  tt.DrawLatex(.30,3.47,"^{20}Mg");
  tt.DrawLatex(1.2,3.47,"^{21}Al");
  tt.DrawLatex(1.67,3.47,"^{21}O");
  tt.DrawLatex(1.62+shift,3.47,"^{22}Si");
  tt.DrawLatex(2.11+shift,3.47,"^{22}O");

  tt.SetTextSize(.06);
  tt.DrawLatex(.034,-.007,"0^{+}");
  tt.DrawLatex(.034,1.68,"2^{+}");
  tt.DrawLatex(1,.031,"5/2^{+}");
  tt.DrawLatex(1,.58,"1/2^{+}");
  tt.DrawLatex(1,1.42,"3/2^{+}");

  double ss = .3;

  tt.DrawLatex(1.74+ss,.031,"0^{+}");
  tt.DrawLatex(1.74+ss,2.85,"2^{+}");

  tt.SetTextSize(.05);
  tt.DrawLatex(.72,-.49,"Exp");
  tt.DrawLatex(1.67,-.49,"Exp");
  tt.DrawLatex(2.4+ss,-.49,"Exp");


  tt.SetTextColor(2);
  tt.DrawLatex(.11,-.49,"SM");
  tt.DrawLatex(1.09,-.49,"SM");
  tt.DrawLatex(1.8+ss,-.49,"SM");
  tt.SetTextColor(4);
  tt.DrawLatex(.38,-.49,"GSM");
  tt.DrawLatex(1.34,-.49,"GSM");
  tt.DrawLatex(2.09+ss,-.49,"GSM");
  tt.SetTextColor(1);
  tt.DrawLatex(1.76,1.29,"(1/2^{+})");  


}
