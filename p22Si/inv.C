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
  Sty->SetLabelSize(0.06,"xyz");
  Sty->SetLabelOffset(0.01,"y");
  Sty->SetLabelOffset(0.02,"x");
  Sty->SetLabelColor(kBlack,"xyz");
  Sty->SetTitleSize(0.06,"xyz");
  Sty->SetTitleOffset(1.2,"y");
  Sty->SetTitleOffset(1.4,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.05,"xz");
  Sty->SetTickLength(.025,"y");
  Sty->SetNdivisions(10,"xyz");
  Sty->SetEndErrorSize(0);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();
  TCanvas cancas("inv_21Al");



  TFile file("sim.root");
  TH1I * hist = (TH1I*) file.Get("Erel");

  TH2S frame("frame","",10,0,5,10,0,1200);
  frame.GetXaxis()->SetTitle("Q_{p} (MeV)");
  frame.GetYaxis()->SetTitle("Counts");
  frame.GetXaxis()->CenterTitle();
  frame.GetYaxis()->CenterTitle();
  frame.Draw();
  hist->Draw("same");

  TH1I* hists = (TH1I*) hist->Clone();
  hists->Rebin(4);
  hists->SetLineColor(4);
  hists->Scale(4);
  hists->Draw("same");

  TLatex tt;
  tt.SetTextSize(.05);
  tt.DrawLatex(3,1000,"^{21}Al#rightarrow#it{p}+^{20}Mg");
 
  TArrow arrow;
  arrow.SetAngle(30);
  arrow.SetLineColor(2);
  arrow.SetFillColor(2);
  arrow.DrawArrow(1.265,1200,1.265,1000);
  arrow.DrawArrow(1.265+1.22,330,1.265+1.22,180);
  
  tt.SetTextColor(2);
  tt.DrawLatex(1.45,1084,"5/2^{+}");
  tt.DrawLatex(2.37,327,"1/2^{+}");
}
