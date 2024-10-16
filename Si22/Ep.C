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
Sty->SetPadLeftMargin(.12);
Sty->SetPadTopMargin(.05);
Sty->SetPadRightMargin(.05);
Sty->SetHistLineWidth(3);
Sty->SetHistLineColor(kRed);
Sty->SetFuncWidth(3);
Sty->SetFuncColor(kGreen);
Sty->SetLineWidth(3);
Sty->SetLabelSize(0.07,"xyz");
Sty->SetLabelOffset(0.02,"y");
Sty->SetLabelOffset(0.02,"x");
Sty->SetLabelColor(kBlack,"xyz");
Sty->SetTitleSize(0.07,"xyz");
Sty->SetTitleOffset(.8,"y");
Sty->SetTitleOffset(1.,"x");
Sty->SetTitleFillColor(10);
Sty->SetTitleTextColor(kBlack);
Sty->SetTickLength(.02,"xz");
Sty->SetTickLength(.015,"y");
Sty->SetNdivisions(5,"xyz");
Sty->SetEndErrorSize(0);
gROOT->SetStyle("MyStyle");
gROOT->ForceStyle();

 TCanvas canvas("decayEnergies","",600,800);


   canvas.Divide(1,2);
   canvas.cd(1);
   TH2S frame("frame","",10,23.5,27,10,-1,3);
   frame.GetXaxis()->SetTitle("A");
   frame.GetYaxis()->SetTitle("Q_{p} (MeV)");
   frame.GetXaxis()->CenterTitle();
   frame.GetYaxis()->CenterTitle();
   frame.Draw();

   TLine ll;
   ll.SetLineStyle(2);
   ll.DrawLine(23.5,0.,27,0.);

   const int n = 3;
   double x[n] = {26,25,24};
   double EpFRDM[n]={-.539, 1.66,2.361};
   double EpUSDC[n]={.217,1.274,1.806};
   double EpKG[n]={.639,1.904,1.980};
   double dx[3]={0.,0.,0.};
   double dEpKG[n]={.05,.106,.143};
   TGraph gpFRDM(n,x,EpFRDM);

   gpFRDM.SetMarkerStyle(20);
   gpFRDM.Draw("LP");

   double EpAME[1]={.0521};
   double dEpAME[1]={.718};
   double dxAME[1]={0.};

   TGraphErrors gpAME(1,x,EpAME,dxAME,dEpAME);
   gpAME.SetMarkerStyle(20);
   gpAME.SetMarkerColor(2);
   gpAME.SetMarkerSize(2);
   gpAME.SetLineColor(2);
   gpAME.Draw("LP");


   TGraph gpUSDC(n,x,EpUSDC);

   gpUSDC.SetMarkerStyle(21);
   gpUSDC.SetMarkerColor(8);
   gpUSDC.SetLineColor(8);
   gpUSDC.Draw("LP");


   TGraphErrors gpKG(n,x,EpKG,dx,dEpKG);

   gpKG.SetMarkerStyle(22);
   gpKG.SetMarkerColor(4);
   gpKG.SetLineColor(4);
   gpKG.Draw("LP");

   canvas.cd(2);
   TH2S frame2("frame2","",10,23.5,27,10,0,7);
   frame2.GetXaxis()->SetTitle("A");
   frame2.GetYaxis()->SetTitle("Q_{2p} (MeV)");
   frame2.GetXaxis()->CenterTitle();
   frame2.GetYaxis()->CenterTitle();
   frame2.Draw();


   double E2pFRDM[n]={1.66,3.19,6.67};
   TGraph g2pFRDM(n,x,E2pFRDM);
   g2pFRDM.SetMarkerStyle(20);
   g2pFRDM.Draw("LP");


   double E2pUSDC[n]={1.774,3.273,4.861};
   TGraph g2pUSDC(n,x,E2pUSDC);
   g2pUSDC.SetMarkerColor(8);
   g2pUSDC.SetLineColor(8);

   g2pUSDC.SetMarkerStyle(20);
   g2pUSDC.Draw("LP");


   double E2pKG[n]={2.146,3.769,4.861};
   double dE2pKG[n]={.021,.126,.125};
   TGraphErrors g2pKG(n,x,E2pKG,dx,dE2pKG);
   g2pKG.SetMarkerColor(4);
   g2pKG.SetLineColor(4);

   g2pKG.SetMarkerStyle(22);
   g2pKG.Draw("LP");


 E = 2.32;
 TBox box12(23.8,E-.33,24.2,E+.33);
  box12.SetFillColor(3);
  box12.SetFillStyle(3004);
  //box12.Draw("same");

  double yF[1]={E};
  double dyF[1]={.33};
  double xF[1]={24};
  TGraphErrors gF(1,xF,yF,dx,dyF);
  gF.SetMarkerStyle(20);
  gF.SetMarkerColor(3);
  gF.SetMarkerSize(2);
  gF.SetLineColor(3);
  gF.Draw("PE");

  E= .7;
  TBox box23(25.8,E-1.,26.2,E+1.);
  box23.SetFillColor(6);
  box23.SetFillStyle(3004);
  box23.SetLineWidth(2);
  box23.Draw("same");

 E= 3.15;
  TBox box22(24.8,E-1.45,25.2,E+1.45);
  box22.SetFillColor(6);
  box22.SetFillStyle(3004);
  box22.Draw("same");

   double E2pAME[1]={1.755};
   double dE2pAME[1]={.596};

   TGraphErrors g2pAME(1,x,E2pAME,dxAME,dE2pAME);
   g2pAME.SetMarkerStyle(20);
   g2pAME.SetMarkerColor(2);
   g2pAME.SetMarkerSize(2);
   g2pAME.SetLineColor(2);
   g2pAME.Draw("LP");

  TLatex tt;
  tt.SetTextSize(.06);
  double xt = 25.87;
  tt.DrawLatex(xt,6.,"FRLDM2012");
  tt.SetTextColor(2);
  tt.DrawLatex(xt,5.5,"AME2016");
  tt.SetTextColor(4);
  tt.DrawLatex(xt,5.,"ImKG");
  tt.SetTextColor(6);
  tt.DrawLatex(xt,4.55,"BMA");
  tt.SetTextColor(3);
  tt.DrawLatex(xt,4.,"Fortune");
  tt.SetTextColor(8);
  tt.DrawLatex(xt,3.5,"USDC");



}
