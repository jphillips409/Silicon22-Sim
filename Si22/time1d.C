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
Sty->SetPadBottomMargin(.2);
Sty->SetPadLeftMargin(.12);
Sty->SetPadTopMargin(.01);
Sty->SetPadRightMargin(.05);
Sty->SetHistLineWidth(3);
Sty->SetHistLineColor(kRed);
Sty->SetFuncWidth(3);
Sty->SetFuncColor(kGreen);
Sty->SetLineWidth(3);
Sty->SetLabelSize(0.08,"xyz");
Sty->SetLabelOffset(0.02,"y");
Sty->SetLabelOffset(0.02,"x");
Sty->SetLabelColor(kBlack,"xyz");
Sty->SetTitleSize(0.08,"xyz");
Sty->SetTitleOffset(.7,"y");
Sty->SetTitleOffset(1.1,"x");
Sty->SetTitleFillColor(10);
Sty->SetTitleTextColor(kBlack);
Sty->SetTickLength(.02,"xz");
Sty->SetTickLength(.015,"y");
Sty->SetNdivisions(5,"xyz");
Sty->SetEndErrorSize(0);
gROOT->SetStyle("MyStyle");
gROOT->ForceStyle();

 TCanvas canvas("time36_2d","",600,800);
  canvas.Divide(1,3);

  canvas.cd(1);

  TH2S frame0("frame0","",10,0,1.2,10,0,120);
  frame0.GetXaxis()->SetTitle("Q_{p} (MeV)");
  frame0.GetYaxis()->SetTitle("Counts");
  frame0.GetXaxis()->CenterTitle();
  frame0.GetYaxis()->CenterTitle();

  frame0.Draw();

  TFile file0("sim0_2d.root");
  TH1I* hist0 = (TH1I*) file0.Get("Erel");
  TH1I* hist0_notarget = (TH1I*) file0.Get("Erel_notarget");

  hist0->Rebin(4);
  hist0->SetLineColor(4);
  hist0_notarget->Rebin(4);
  hist0_notarget->SetLineColor(2);


  hist0->Draw("same");
  hist0_notarget->Draw("same");

  TLatex tt;
  tt.SetTextSize(.08);
  tt.SetNDC();
  tt.DrawLatex(.2,.7,"#tau=0");



  TLegend leg(.6,.5,.95,.95);
  leg.AddEntry(hist0,"target-#DeltaE correction","L");
  leg.AddEntry(hist0_notarget," no target-#DeltaE correction","L");
  leg.Draw();

  canvas.cd(2);
  TH2S frame20("frame20","",10,0,1.2,10,0,120);
  frame20.GetXaxis()->SetTitle("Q_{p} (MeV)");
  frame20.GetYaxis()->SetTitle("Counts");
  frame20.GetXaxis()->CenterTitle();
  frame20.GetYaxis()->CenterTitle();
  frame20.Draw();
  TFile file20("sim3_2d.root");
  TH1I* hist20 = (TH1I*) file20.Get("Erel");
  TH1I* hist20_notarget = (TH1I*) file20.Get("Erel_notarget");

  hist20->Rebin(4);
  hist20->SetLineColor(4);
  hist20_notarget->Rebin(4);
  hist20_notarget->SetLineColor(2);


  hist20->Draw("same");
  hist20_notarget->Draw("same");
  tt.DrawLatex(.6,.7,"#Gamma=3 meV, #tau=0.2 ps");
  tt.DrawLatex(.15,.7,"^{36}Ca_{2^{+}}#rightarrow#it{p}+^{35}K");


  canvas.cd(3);
  TH2S frame40("frame40","",10,0,1.2,10,0,140);
  frame40.GetXaxis()->SetTitle("Q_{2p} (MeV)");
  frame40.GetYaxis()->SetTitle("Counts");
  frame40.GetXaxis()->CenterTitle();
  frame40.GetYaxis()->CenterTitle();
  frame40.Draw();
  TFile file40("simp3_2d.root");
  TH1I* hist40 = (TH1I*) file40.Get("Erel");
  TH1I* hist40_notarget = (TH1I*) file40.Get("Erel_notarget");

  hist40->Rebin(4);
  hist40->SetLineColor(4);
  hist40_notarget->Rebin(4);
  hist40_notarget->SetLineColor(2);


  hist40->Draw("same");
  hist40_notarget->Draw("same");

  tt.DrawLatex(.6,.7,"#Gamma=.3 meV, #tau=2 ps");

}
