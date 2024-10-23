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
  Sty->SetTitleSize(0.07,"xyz");
  Sty->SetTitleOffset(1.,"y");
  Sty->SetTitleOffset(1.,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.05,"xz");
  Sty->SetTickLength(.025,"y");
  Sty->SetNdivisions(10,"xyz");
  Sty->SetEndErrorSize(0);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();
  TCanvas canvas("sep",""); 

 TFile filep25 ("sim_p25mm.root");
  TH1I * hist25 = (TH1I*) filep25.Get("Erel");
  hist25->Scale(2.);

  TFile filep5 ("sim_p5mm.root");
  TH1I * hist5 = (TH1I*) filep5.Get("Erel");

   TFile file1 ("sim_1mm.root");
 
  TH1I * hist1 = (TH1I*) file1.Get("Erel");
  hist1->Scale(.5);

   TFile fileS ("sim_si_300.root");
  TH1I * histS = (TH1I*) fileS.Get("Erel");


  TH2S frame("frame","",10,0,6,10,0,1800);
  frame.GetXaxis()->SetTitle("E_{2p} (MeV)");
  frame.GetYaxis()->SetTitle("Counts");
  frame.GetXaxis()->CenterTitle();
  frame.GetYaxis()->CenterTitle();
  frame.Draw();
  hist1->Draw("same");
  hist5->SetLineColor(2);
  hist5->Draw("same");
  hist25->SetLineColor(4);
  hist25->Draw("same");

  TLatex tt;
  tt.SetTextSize(.06);
  tt.DrawLatex(1.99,1400,"0^{+}");
  tt.DrawLatex(3.73,759,"2^{+}");
  tt.DrawLatex(2.5,1000,"^{26}S#rightarrow2#it{p}+^{24}Si");

  tt.DrawLatex(4,1600,"1-mm Be");
  tt.SetTextColor(2);
  tt.DrawLatex(4,1400,"0.5-mm Be");

  tt.SetTextColor(4);
  tt.DrawLatex(4,1200,"0.25-mm Be");

  histS->SetLineColor(3);
  histS->Draw("same");
}
