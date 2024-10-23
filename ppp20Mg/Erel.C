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
  TCanvas canvas("Erel_21Si","");


  TFile file("sim.root");
  TH1I* hist = (TH1I*) file.Get("Erel");
  TH2S frame("frame","",10,0,6.8,10,0,35);
  frame.GetXaxis()->SetTitle("Q_{4p} (MeV)");

  frame.GetYaxis()->SetTitle("Counts");
  frame.GetYaxis()->CenterTitle();
  frame.GetXaxis()->CenterTitle();
  frame.Draw();

  hist->Rebin(3);
  hist->Draw("same");

  TArrow arrow;
  arrow.SetAngle(30);
  arrow.DrawArrow(4.645,32,4.645,27);
  arrow.DrawArrow(4.645+1.116,10,4.645+1.116,4);
  //arrow.DrawArrow(2.327,80,2.327,30);
  //arrow.DrawArrow(.694,150,.694,60);

  TLatex tt;
  tt.DrawLatex(4.9,29,"1/2^{-}");
  tt.DrawLatex(5.6,11.5,"3/2^{-}");
  // tt.DrawLatex(2.258,91,"3/2^{+}");
  //tt.DrawLatex(.629,177,"3/2^{+}");
  tt.DrawLatex(.39,30,"^{21}Si#rightarrow4#it{p}+^{17}Ne");
}
