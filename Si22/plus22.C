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
Sty->SetPadLeftMargin(.1);
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
Sty->SetTitleOffset(.8,"y");
Sty->SetTitleOffset(1.3,"x");
Sty->SetTitleFillColor(10);
Sty->SetTitleTextColor(kBlack);
Sty->SetTickLength(.02,"xz");
Sty->SetTickLength(.015,"y");
Sty->SetNdivisions(5,"xyz");
Sty->SetEndErrorSize(0);
gROOT->SetStyle("MyStyle");
gROOT->ForceStyle();

 TCanvas canvas("plus22");

  double x[5]={10,12,14,16,18};
  double y[5]={1.982,1.673,3.199,4.79,1.277};

  TH2S framen("framen","",10,8,20,10,0,5.9);
  framen.GetXaxis()->SetTitle("N,Z");
  framen.GetYaxis()->SetTitle("E^{*}(2^{+}_{1}) (MeV)");
  framen.GetXaxis()->SetNdivisions(10);
  framen.GetYaxis()->SetNdivisions(10);
  framen.GetXaxis()->CenterTitle();
  framen.GetYaxis()->CenterTitle();

  framen.Draw();

  TGraph g(5,x,y);
  g.SetMarkerStyle(20);
  g.SetMarkerColor(2);
  g.SetLineColor(2);
  g.SetMarkerSize(1.5);
  g.Draw("PL");

  double yp[2]={1.887,1.598};
  TGraph gp(2,x,yp);
  gp.SetMarkerStyle(20);
  gp.SetMarkerColor(4);
  gp.SetLineColor(4);
  gp.SetMarkerSize(1.5);
  gp.Draw("PL");

  TLatex tt;
  tt.SetTextSize(.07);
  tt.SetTextAngle(-15);
  tt.SetTextColor(2);
  tt.DrawLatex(10.16,2.17,"Z=8");
  tt.SetTextColor(4);
  tt.DrawLatex(10.14,1.45,"N=8");


  TLine ll;
  ll.SetLineStyle(2);
  ll.SetLineColor(4);


  ll.DrawLine(x[1],yp[1],14,2.37);
  ll.DrawLine(x[1],yp[1],14,1.63);
  ll.DrawLine(x[1],yp[1],14,2.817);

  TMarker mark;
  mark.SetMarkerStyle(20);
  mark.SetMarkerSize(1.5);
  mark.SetMarkerColor(4);
  mark.DrawMarker(14,2.37);
  mark.DrawMarker(14,1.63);
  mark.DrawMarker(14,2.817);

  tt.SetTextSize(.06);
  tt.SetTextAngle(0);
  tt.SetTextColor(2);
  tt.DrawLatex(9.6,3.0,"^{18}O");
  tt.DrawLatex(11.6,2.5,"^{20}O");
  tt.DrawLatex(13.4,3.8,"^{22}O");
  tt.DrawLatex(15.5,5.,"^{24}O");
  tt.DrawLatex(17.7,2.5,"^{26}O");

  tt.SetTextColor(4);

  tt.DrawLatex(9.8,.86,"^{18}Ne");
  tt.DrawLatex(11.8,.86,"^{20}Mg");
  tt.DrawLatex(13.8,.86,"^{22}Si");

  tt.DrawLatex(14.3,2.7,"Holt et al");
  tt.DrawLatex(14.3,2.28,"Brown");
  tt.DrawLatex(14.3,1.6,"GSM");

}
