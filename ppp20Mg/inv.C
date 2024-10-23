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
  Sty->SetPadBottomMargin(.17);
  Sty->SetPadTopMargin(.01);
  Sty->SetPadLeftMargin(.15);
  Sty->SetPadRightMargin(.03);
  Sty->SetHistLineWidth(3);
  Sty->SetFuncWidth(3);
  Sty->SetFuncColor(kGreen);
  Sty->SetLineWidth(3);
  Sty->SetLabelSize(0.06,"xyz");
  Sty->SetLabelOffset(0.01,"y");
  Sty->SetLabelOffset(0.02,"x");
  Sty->SetLabelColor(kBlack,"xyz");
  Sty->SetTitleSize(0.06,"xyz");
  Sty->SetTitleOffset(1.,"y");
  Sty->SetTitleOffset(1.2,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.05,"xz");
  Sty->SetTickLength(.025,"y");
  Sty->SetNdivisions(10,"xyz");
  Sty->SetEndErrorSize(0);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();
  TCanvas cancas("inv_22Si");



  TFile file("sim.root");
  TH1I * hist = (TH1I*) file.Get("Erel");

  TH2S frame("frame","",10,0,10,10,0,120);
  frame.GetXaxis()->SetTitle("Q_{2p} (MeV)");
  frame.GetYaxis()->SetTitle("Counts");
  frame.GetXaxis()->CenterTitle();
  frame.GetYaxis()->CenterTitle();
  frame.Draw();
  hist->Rebin(2);
  hist->Draw("same");



  TLatex tt;
  tt.SetTextSize(.05);
  tt.DrawLatex(5,50*2,"^{22}Si#rightarrow2#it{p}+^{20}Mg");

 
  TArrow arrow;
  arrow.SetAngle(30);
  arrow.SetLineColor(2);
  arrow.SetFillColor(2);
  arrow.DrawArrow(3.203,2*60,3.203,2*50);
  arrow.DrawArrow(4.588,2*20,4.588,2*10);
  arrow.DrawArrow(4.913,2*20,4.913,2*10);
  
  tt.SetTextColor(2);
  tt.DrawLatex(3.61,2*54,"2^{+}");
  tt.DrawLatex(4.3,2*21,"(3^{+})");
  tt.DrawLatex(4.9,2*21,"(0^{+})");
  
}
