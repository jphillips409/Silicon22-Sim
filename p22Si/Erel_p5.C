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
  TCanvas canvas("Erel_23P","",600,800);

  canvas.Divide(1,2);
  canvas.cd(1);

  TFile file("sim_p5.root");
  TH1I* hist = (TH1I*) file.Get("Erel");
  TH2S frame("frame","",10,0,6.5,10,0,80);
  frame.GetXaxis()->SetTitle("Q_{p} (MeV)");

  frame.GetYaxis()->SetTitle("Counts");
  frame.GetYaxis()->CenterTitle();
  frame.GetXaxis()->CenterTitle();
  frame.Draw();
  hist->Rebin(8);
  hist->Draw("same");

  TArrow arrow;
  arrow.SetAngle(30);
  arrow.SetFillColor(1);
  arrow.DrawArrow(2.08,79,2.08,66);
  arrow.DrawArrow(3.57,72*.46,3.57,50*.46);
  //arrow.DrawArrow(2.32,80,2.327,30);
  //arrow.DrawArrow(.694,40,.694,30);

  TLatex tt;
  tt.SetTextSize(.07);
  tt.DrawLatex(2.38,70,"1/2^{+}");
  tt.DrawLatex(3.37,64*.55,"5/2^{+}");
  // tt.DrawLatex(2.258,91,"3/2^{+}");
  //tt.DrawLatex(.629,177,"3/2^{+}");
  tt.DrawLatex(3.5,69,"(a) ^{23}P#rightarrow#it{p}+^{22}Si");

  canvas.cd(2);
  TH2S frame2("frame2","",10,0,6.5,10,0,15);
  frame2.GetXaxis()->SetTitle("Q_{3p} (MeV)");

  frame2.GetYaxis()->SetTitle("Counts");
  frame2.GetYaxis()->CenterTitle();
  frame2.GetXaxis()->CenterTitle();
  frame2.Draw();

  TFile file3("../ppp20Mg/sim.root");
  TH1I* hist3 = (TH1I*) file3.Get("Erel");

  hist3->Rebin(4);
  hist3->Draw("same"); 
  tt.DrawLatex(.2,12,"(b) ^{23}P#rightarrow3#it{p}+^{20}Mg");
  arrow.DrawArrow(3.27,14,3.27,11);
  tt.DrawLatex(3.63,11.8,"5/2^{+}");
}
