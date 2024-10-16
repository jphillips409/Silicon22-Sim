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

 TCanvas canvas("level_23P_ImKG");
    double delta = .06;
  TH2S frame("frame","",10,-.3,1.3,10,-1,6);
  frame.GetXaxis()->SetLabelSize(0.);
  frame.GetXaxis()->SetAxisColor(0.);
  //frame.GetXaxis()->SetTickWidth(0.);

  frame.GetYaxis()->SetTitle("Energy (MeV)");
  frame.GetYaxis()->CenterTitle();
  frame.SetStats(kFALSE);
  
  frame.Draw();
  double shift = 0.;

  double xmin23P = -.2+shift;
  double xmax23P = 0.+shift;
  double xmin22Si = .1+ shift;
  double xmax22Si = .3 + shift;
  double xmin21Al = .4+ shift;
  double xmax21Al = .6+ shift;
  double xmin20Mg = .7+shift;
  double xmax20Mg = .9+shift;
  double xmin19Na = 1+shift;
  double xmax19Na = 1.2+shift;







  TLine ll;
  double E= 2.955;
  ll.DrawLine(xmin23P,E,xmax23P,E);
  TBox box43(xmin23P,E-1.21/2,xmax23P,E+1.21/2);
  box43.SetFillColor(1);
  box43.SetFillStyle(3004);
  box43.Draw("same");

  
  E+= 2.81;
  ll.DrawLine(xmin23P,E,xmax23P,E);
  TBox box44(xmin23P,E-.735/2,xmax23P,E+.735/2);
  box44.SetFillColor(1);
  box44.SetFillStyle(3004);
  box44.Draw("same");
  
  E = 0.;
  ll.DrawLine(xmin22Si,0.,xmax22Si,0.);
  E = 3.199;
  ll.DrawLine(xmin22Si,E,xmax22Si,E);
  TBox box23(xmin22Si,E-.388/2,xmax22Si,E+.388/2);
  box23.SetFillColor(1);
  box23.SetFillStyle(3004);
  box23.Draw("same");


  E = 1.261;
  ll.DrawLine(xmin21Al,E,xmax21Al,E);
  E = 1.261 + 1.22;
  ll.DrawLine(xmin21Al,E,xmax21Al,E);
  TBox box13(xmin21Al,E-1.1/2,xmax21Al,E+1.1/2);
  box13.SetFillColor(1);
  box13.SetFillStyle(3004);
  box13.Draw("same");

  E = -.004;
  ll.DrawLine(xmin20Mg,E,xmax20Mg,E);

  E = -.004+1.598;
  ll.DrawLine(xmin20Mg,E,xmax20Mg,E);

  E = -.004+2.740;
  ll.DrawLine(xmin19Na,E,xmax19Na,E);


  TLatex tt;
  tt.DrawLatex(.09,-.37,"#it{p}+^{22}Si");
  tt.DrawLatex(.153-.3,2.5,"^{23}P");
  tt.DrawLatex(.059,.186,"0^{+}");
  tt.DrawLatex(.079,3.33,"2^{+}");
  tt.DrawLatex(-.226,3.17,"1/2^{+}");
  tt.DrawLatex(-.226,5.22,"5/2^{+}");

  tt.DrawLatex(.32,1.35,"5/2^{+}");
  tt.DrawLatex(.32,2.63,"1/2^{+}");

  tt.DrawLatex(.89,.173,"0^{+}");
  tt.DrawLatex(.89,1.72,"2^{+}");
  tt.DrawLatex(.42,.77,"2#it{p}+^{21}Al");
  tt.DrawLatex(.72,-.41,"3#it{p}+^{20}Mg");
  tt.DrawLatex(1.01,2.26,"4#it{p}+^{19}Na");

  TArrow arrow;
  arrow.SetFillColor(2);
  arrow.SetLineColor(2);
  arrow.SetAngle(30);
  arrow.DrawArrow(xmax22Si-.05,3.199,xmin21Al+.1,1.261);
  arrow.DrawArrow(xmax21Al,1.261,xmin20Mg+.1,-.004);
  arrow.DrawArrow(xmax21Al,1.261+1.22,xmin20Mg+.15,-.004);
  arrow.DrawArrow(xmax23P,2.955,xmin22Si+.06,-.004);

  arrow.DrawArrow(xmax23P,5.795,xmin22Si+.1,3.199);
  arrow.SetLineStyle(2);
  arrow.DrawArrow(xmax23P,5.795,xmin22Si+.1,-.004);

}
