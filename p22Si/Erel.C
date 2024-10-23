{
  int compression = 15;
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

  TFile file("sim.root");
  TH1I* hist = (TH1I*) file.Get("Erel");
  TH2S frame("frame","",10,0,6.5,10,0,140);
  frame.GetXaxis()->SetTitle("Q_{p} (MeV)");

  frame.GetYaxis()->SetTitle("Counts");
  frame.GetYaxis()->CenterTitle();
  frame.GetXaxis()->CenterTitle();
  frame.Draw();
  hist->Rebin(compression);
  hist->Draw("same");

  TArrow arrow;
  arrow.SetAngle(30);
  arrow.SetFillColor(1);
  arrow.DrawArrow(2.08,69*2.,2.08,56*2.);
  arrow.DrawArrow(3.57,72*.46*2.,3.57,50*.46*2.);
  arrow.SetFillColor(0);
  arrow.DrawArrow(3.57+1.22,72*.36*2,3.57+1.22,50*.3*2);
  //arrow.DrawArrow(2.32,80,2.327,30);
  //arrow.DrawArrow(.694,40,.694,30);

  TLatex tt;
  tt.SetTextSize(.07);
  tt.DrawLatex(2.38,60*2,"1/2^{+}");
  tt.DrawLatex(3.37,64*.55*2,"5/2^{+}");
  // tt.DrawLatex(2.258,91,"3/2^{+}");
  //tt.DrawLatex(.629,177,"3/2^{+}");
  tt.DrawLatex(3.5,59*2,"(a) ^{23}P#rightarrow#it{p}+^{22}Si");

  canvas.cd(2);
  TH2S frame2("frame2","",10,0,6.5,10,0,64);
  frame2.GetXaxis()->SetTitle("Q_{3p} (MeV)");

  frame2.GetYaxis()->SetTitle("Counts");
  frame2.GetYaxis()->CenterTitle();
  frame2.GetXaxis()->CenterTitle();
  frame2.Draw();

  TFile file3("../ppp20Mg/sim.root");
  TH1I* hist3 = (TH1I*) file3.Get("Erel");

  hist3->Rebin(compression);
  hist3->Draw("same"); 
  tt.DrawLatex(.2,25*2,"(b) ^{23}P#rightarrow3#it{p}+^{20}Mg");
  arrow.SetFillColor(1);
  arrow.DrawArrow(3.28,31*2,3.28,26*2);
  arrow.SetFillColor(0);
  arrow.DrawArrow(3.28+1.22,10*2,3.28+1.22,5*2);
  tt.DrawLatex(3.63,26*2,"5/2^{+}");


  cout << " 1p total = " <<hist->Integral() << endl;
  cout << " 3p total = " <<hist3->Integral() << endl; 
}
