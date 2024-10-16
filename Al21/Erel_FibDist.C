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
  Sty->SetPadBottomMargin(.1);
  Sty->SetPadTopMargin(.03);
  Sty->SetPadLeftMargin(.13);
  Sty->SetPadRightMargin(.03);
  Sty->SetHistLineWidth(3);
  Sty->SetFuncWidth(3);
  Sty->SetFuncColor(kGreen);
  Sty->SetLineWidth(3);
  Sty->SetLabelSize(0.06,"xyz");
  Sty->SetLabelOffset(0.01,"y");
  Sty->SetLabelOffset(0.02,"x");
  Sty->SetLabelColor(kBlack,"xyz");
  Sty->SetTitleSize(0.09,"xyz");
  Sty->SetTitleOffset(0.7,"y");
  Sty->SetTitleOffset(1.1,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.05,"xz");
  Sty->SetTickLength(.025,"y");
  Sty->SetNdivisions(10,"xyz");
  Sty->SetEndErrorSize(0);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();
  TCanvas canvas("Erel_23P_1p_Width","",300,1000);

  canvas.Divide(1,5);
  canvas.cd(1);

  TFile file("sim_85MeVA_fibdist87.root");
  //TFile file("sim.root");
  TH1I* hist = (TH1I*) file.Get("Erel_trans");
  TH2S frame("frame","",10,0,2.8,10,4,6000);
  frame.GetXaxis()->SetTitle("Q_{p} (MeV)");

  frame.GetYaxis()->SetTitle("Counts/32 keV");
  frame.GetYaxis()->CenterTitle();
  frame.GetXaxis()->CenterTitle();
  frame.Draw();
  hist->Rebin(2);
  hist->Draw("same");
  gPad->SetLogy();

  TArrow arrow;
  arrow.SetAngle(30);
  arrow.SetFillColor(1);
  arrow.SetArrowSize(0.03);

  //arrow.DrawArrow(2.32,80,2.327,30);
  //arrow.DrawArrow(.694,40,.694,30);

  TLatex tt;
  tt.SetTextSize(.08);

  // tt.DrawLatex(2.258,91,"3/2^{+}");
  //tt.DrawLatex(.629,177,"3/2^{+}");
  tt.DrawLatex(1.3,1000,"#splitline{(a) ^{21}Al#rightarrow#it{p}+^{20}Mg}{     85 MeV/A}");
  tt.DrawLatex(1.3,300,"     87 mm");

  canvas.cd(2);
  TH2S frame2("frame2","",10,0,2.8,10,4,6000);
  frame2.GetXaxis()->SetTitle("Q_{p} (MeV)");

  frame2.GetYaxis()->SetTitle("Counts/32 keV");
  frame2.GetYaxis()->CenterTitle();
  frame2.GetXaxis()->CenterTitle();
  frame2.Draw();

  TFile file3("sim_85MeVA_fibdist100.root");
  TH1I* hist3 = (TH1I*) file3.Get("Erel_trans");

  hist3->Rebin(2);
  hist3->Draw("same"); 
  gPad->SetLogy();

  tt.DrawLatex(1.3,1000,"(b) 100 mm");

  canvas.cd(3);
  TH2S frame3("frame3","",10,0,2.8,10,4,6000);
  frame3.GetXaxis()->SetTitle("Q_{p} (MeV)");

  frame3.GetYaxis()->SetTitle("Counts/32 keV");
  frame3.GetYaxis()->CenterTitle();
  frame3.GetXaxis()->CenterTitle();
  frame3.Draw();

  TFile file4("sim_85MeVA_fibdist110.root");
  TH1I* hist4 = (TH1I*) file4.Get("Erel_trans");

  hist4->Rebin(2);
  hist4->Draw("same"); 
  gPad->SetLogy();

  tt.DrawLatex(1.3,1000,"(c) 110 mm");

  canvas.cd(4);
  TH2S frame4("frame4","",10,0,2.8,10,4,6000);
  frame4.GetXaxis()->SetTitle("Q_{p} (MeV)");

  frame4.GetYaxis()->SetTitle("Counts/32 keV");
  frame4.GetYaxis()->CenterTitle();
  frame4.GetXaxis()->CenterTitle();
  frame4.Draw();

  TFile file5("sim_85MeVA_fibdist120.root");
  TH1I* hist5 = (TH1I*) file5.Get("Erel_trans");

  hist5->Rebin(2);
  hist5->Draw("same"); 
  gPad->SetLogy();

  tt.DrawLatex(1.3,1000,"(d) 120 mm");

  canvas.cd(5);
  TH2S frame5("frame5","",10,0,2.8,10,4,6000);
  frame5.GetXaxis()->SetTitle("Q_{p} (MeV)");

  frame5.GetYaxis()->SetTitle("Counts/32 keV");
  frame5.GetYaxis()->CenterTitle();
  frame5.GetXaxis()->CenterTitle();
  frame5.Draw();

  TFile file6("sim_85MeVA_fibdist160.root");
  TH1I* hist6 = (TH1I*) file6.Get("Erel_trans");

  hist6->Rebin(2);
  hist6->Draw("same");
  gPad->SetLogy();
 
  tt.DrawLatex(1.3,1000,"(e) 160 mm");

}
