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
  Sty->SetPadTopMargin(.05);
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
  Sty->SetTitleSize(0.06,"xyz");
  Sty->SetTitleOffset(1.,"y");
  Sty->SetTitleOffset(1.1,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.05,"xz");
  Sty->SetTickLength(.025,"y");
  Sty->SetNdivisions(10,"xyz");
  Sty->SetEndErrorSize(0);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();
  TCanvas canvas("Erel_23P_1p_Width","",600,800);

  canvas.Divide(1,2);
  canvas.cd(1);

  TFile file("sim_85MeVA_expt.root");
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
  arrow.DrawArrow(1.469,124*1.2,1.469,42*1.2);
  arrow.DrawArrow(1.074,2500*1.2,1.074,1000*1.2);
  arrow.DrawArrow(2.327,80*1.2,2.327,30*1.2);
  arrow.DrawArrow(.694,150*1.2,.694,60*1.2);
  //arrow.DrawArrow(2.32,80,2.327,30);
  //arrow.DrawArrow(.694,40,.694,30);

  TLatex tt;
  tt.SetTextSize(.05);
  tt.DrawLatex(1.15,1642*1.2,"5/2^{+}");
  tt.DrawLatex(1.396,146*1.2,"1/2^{+}");
    tt.DrawLatex(2.258,91*1.2,"3/2^{+}");
  tt.DrawLatex(.629,177*1.2,"3/2^{+}");
  // tt.DrawLatex(2.258,91,"3/2^{+}");
  //tt.DrawLatex(.629,177,"3/2^{+}");
  tt.SetTextSize(.05);
  tt.DrawLatex(1.8,1000*1.2,"#splitline{(a) ^{21}Al#rightarrow#it{p}+^{20}Mg}{     |cos#theta_{Core}| < .5}");
  tt.DrawLatex(1.8, 400*1.2,"     85 MeV/A");
  tt.SetTextSize(.05);

  canvas.cd(2);
  TH2S frame2("frame2","",10,0,2.8,10,4,6000);
  frame2.GetXaxis()->SetTitle("Q_{p} (MeV)");

  frame2.GetYaxis()->SetTitle("Counts/32 keV");
  frame2.GetYaxis()->CenterTitle();
  frame2.GetXaxis()->CenterTitle();
  frame2.Draw();

  TFile file3("sim_100MeVA_expt.root");
  TH1I* hist3 = (TH1I*) file3.Get("Erel_trans");

  hist3->Rebin(2);
  hist3->Draw("same"); 
  gPad->SetLogy();

  tt.SetTextSize(.05);
  tt.DrawLatex(1.8,1000*1.2,"#splitline{(b) ^{21}Al#rightarrow#it{p}+^{20}Mg}{     |cos#theta_{Core}| < .5}");
  tt.DrawLatex(1.8, 400*1.2,"     100 MeV/A");
  tt.SetTextSize(.05);
  arrow.DrawArrow(1.469,124*1.2,1.469,42*1.2);
  arrow.DrawArrow(1.074,2500*1.2,1.074,1000*1.2);
  arrow.DrawArrow(2.327,80*1.2,2.327,30*1.2);
  arrow.DrawArrow(.694,150*1.2,.694,60*1.2);
  tt.DrawLatex(1.15,1642*1.2,"5/2^{+}");
  tt.DrawLatex(1.396,146*1.2,"1/2^{+}");
    tt.DrawLatex(2.258,91*1.2,"3/2^{+}");
  tt.DrawLatex(.629,177*1.2,"3/2^{+}");
}
