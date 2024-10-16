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

 TCanvas canvas("level_22Si_Holt");
    double delta = .06;
  TH2S frame("frame","",10,0,1.3,10,-1,4);
  frame.GetXaxis()->SetLabelSize(0.);
  frame.GetXaxis()->SetAxisColor(0.);
  //frame.GetXaxis()->SetTickWidth(0.);

  frame.GetYaxis()->SetTitle("Energy (MeV)");
  frame.GetYaxis()->CenterTitle();
  frame.SetStats(kFALSE);
  
  frame.Draw();
  double shift = 0.;
  double xmin22Si = .1+ shift;
  double xmax22Si = .3 + shift;
  double xmin21Al = .4+ shift;
  double xmax21Al = .6+ shift;
  double xmin20Mg = .7+shift;
  double xmax20Mg = .9+shift;
  double xmin19Na = 1+shift;
  double xmax19Na = 1.2+shift;







  TLine ll;
  ll.DrawLine(xmin22Si,0.,xmax22Si,0.);
  double E = 2.817;
  ll.DrawLine(xmin22Si,E,xmax22Si,E);
  TBox box23(xmin22Si,E-.388/2,xmax22Si,E+.388/2);
  box23.SetFillColor(1);
  box23.SetFillStyle(3004);
  //box23.Draw("same");


  E = 1.68;
  ll.DrawLine(xmin21Al,E,xmax21Al,E);
  E = 1.68 + .386;
  ll.DrawLine(xmin21Al,E,xmax21Al,E);
  TBox box13(xmin21Al,E-1.1/2,xmax21Al,E+1.1/2);
  box13.SetFillColor(1);
  box13.SetFillStyle(3004);
  //box13.Draw("same");

  E = 1.68 + 1.405;
  ll.DrawLine(xmin21Al,E,xmax21Al,E);


  E = -.016;
  ll.DrawLine(xmin20Mg,E,xmax20Mg,E);

  E = -.016+1.633;
  ll.DrawLine(xmin20Mg,E,xmax20Mg,E);

  E = -.016+2.740;
  ll.DrawLine(xmin19Na,E,xmax19Na,E);


  TLatex tt;
  tt.DrawLatex(.153,-.37,"^{22}Si");
  tt.DrawLatex(.079,.186,"0^{+}");
  tt.DrawLatex(.079,2.97,"2^{+}");

  tt.DrawLatex(.33,1.68,"5/2^{+}");
  tt.DrawLatex(.41,2.22,"1/2^{+}");
  tt.DrawLatex(.36,3.2,"3/2^{+}");

  tt.DrawLatex(.89,.173,"0^{+}");
  tt.DrawLatex(.89,1.72,"2^{+}");
  tt.DrawLatex(.42,.77,"#it{p}+^{21}Al");
  tt.DrawLatex(.72,-.41,"2#it{p}+^{20}Mg");
  tt.DrawLatex(1.01,2.26,"3#it{p}+^{19}Na");
  tt.SetTextSize(.08);
  tt.DrawLatex(.5,3.6,"SM");

  TArrow arrow;
  arrow.SetFillColor(2);
  arrow.SetLineColor(2);
  arrow.SetAngle(30);
  arrow.DrawArrow(xmax22Si-.05,2.817,xmin21Al+.1,1.68);
  arrow.DrawArrow(xmax21Al,1.68,xmin20Mg+.1,-.016);
  arrow.DrawArrow(xmax21Al,1.68+.395,xmin20Mg+.15,-.016);
  arrow.DrawArrow(xmax21Al,1.68+1.405,xmin20Mg+.15,-.016+1.633);

}
