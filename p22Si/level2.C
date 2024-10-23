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

 TCanvas canvas("level_23P_Brown");
    double delta = .06;
  TH2S frame("frame","",10,-.3,1.,10,-1,4);
  frame.GetXaxis()->SetLabelSize(0.);
  frame.GetXaxis()->SetAxisColor(0.);
  //frame.GetXaxis()->SetTickWidth(0.);

  frame.GetYaxis()->SetTitle("Energy (MeV)");
  frame.GetYaxis()->CenterTitle();
  frame.SetStats(kFALSE);
  
  frame.Draw();
  double shift = 0.;
  double xmin23P = -.2;
  double xmax23P = 0.;
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
  double E = 2.37;
  ll.DrawLine(xmin22Si,E,xmax22Si,E);
  TBox box23(xmin22Si,E-.004/2,xmax22Si,E+.004/2);
  box23.SetFillColor(1);
  box23.SetFillStyle(3004);
  box23.Draw("same");


  E = 2.08;
  ll.DrawLine(xmin23P,E,xmax23P,E);
  TBox box133(xmin23P,E-.27/2,xmax23P,E+.27/2);
  box133.SetFillColor(1);
  box133.SetFillStyle(3004);
  box133.Draw("same");

  E = 3.57;
  ll.DrawLine(xmin23P,E,xmax23P,E);
  TBox box143(xmin23P,E-.039/2,xmax23P,E+.039/2);
  box143.SetFillColor(1);
  box143.SetFillStyle(3004);
  box143.Draw("same");

  E = 1.6;
  ll.DrawLine(xmin21Al,E,xmax21Al,E);
  E = 1.6+.2;
  ll.DrawLine(xmin21Al,E,xmax21Al,E);
  TBox box13(xmin21Al,E-.13/2,xmax21Al,E+.13/2);
  box13.SetFillColor(1);
  box13.SetFillStyle(3004);
  box13.Draw("same");

  E = .3;
  ll.DrawLine(xmin20Mg,E,xmax20Mg,E);




  TLatex tt;
  tt.DrawLatex(.123,-.37,"#it{p}+^{22}Si");
  tt.DrawLatex(-.16,1.6,"^{23}P");
  tt.DrawLatex(.288,.186,"0^{+}");
  tt.DrawLatex(.288,2.57,"2^{+}");

  tt.DrawLatex(.34,1.31,"5/2^{+}");
  tt.DrawLatex(.50,1.96,"1/2^{+}");

  tt.DrawLatex(.88,.45,"0^{+}");
  tt.DrawLatex(-.25,2.2,"1/2^{+}");
  tt.DrawLatex(-.25,3.68,"5/2^{+}");
  tt.DrawLatex(.41,.95,"2#it{p}+^{21}Al");
  tt.DrawLatex(.71,-.16,"3#it{p}+^{20}Mg");
  //tt.DrawLatex(1.01,2.26,"3#it{p}+^{19}Na");

  TArrow arrow;
  arrow.SetFillColor(2);
  arrow.SetLineColor(2);
  arrow.SetAngle(30);
  arrow.DrawArrow(xmax23P,2.08,xmin22Si,0);
  arrow.DrawArrow(xmax23P,3.57,xmin22Si+.05,0);
  arrow.DrawArrow(xmax23P,3.57,xmin22Si,2.37);
  arrow.DrawArrow(xmax22Si,2.37,xmin21Al+.1,1.6);
  arrow.DrawArrow(xmax21Al,1.6,xmin20Mg+.1,.3);
  // arrow.DrawArrow(xmax21Al,1.261+1.22,xmin20Mg+.15,-.004);

}
