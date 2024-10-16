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
  Sty->SetPadLeftMargin(.1);
  Sty->SetPadRightMargin(.03);
  Sty->SetHistLineWidth(3);
  Sty->SetFuncWidth(3);
  Sty->SetFuncColor(kGreen);
  Sty->SetLineWidth(3);
  Sty->SetLabelSize(0.06,"xyz");
  Sty->SetLabelOffset(0.01,"y");
  Sty->SetLabelOffset(0.02,"x");
  Sty->SetLabelColor(kBlack,"xyz");
  Sty->SetTitleSize(0.04,"xyz");
  Sty->SetTitleOffset(1.4,"y");
  Sty->SetTitleOffset(1.6,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.05,"xz");
  Sty->SetTickLength(.025,"y");
  Sty->SetNdivisions(10,"xyz");
  Sty->SetEndErrorSize(0);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();
  TCanvas cancas("36Ca_inv_1mm");



  TFile file("sim_36Ca_1mm.root");
  TH1I * hist = (TH1I*) file.Get("Erel");
  TH1I * hist_t = (TH1I*) file.Get("Erel_trans");
  TH1I * hist_n = (TH1I*) file.Get("Erel_trans_narrow");

  TH2S frame("frame","",10,0,2.4,10,0,330);
  frame.GetXaxis()->SetTitle("E_{T} (MeV)");
  frame.GetYaxis()->SetTitle("Counts");
  frame.GetXaxis()->CenterTitle();
  frame.GetYaxis()->CenterTitle();
  frame.Draw();
  hist->Draw("same");

  hist_t->SetLineColor(2);
  hist_n->SetLineColor(4);

  hist_t->Draw("same");
  hist_n->Draw("same");


  TLatex tt;
  tt.SetTextSize(.05);
  tt.DrawLatex(.1,480/2,"^{36}Ca#rightarrow#it{p}+^{35}K");
  tt.DrawLatex(.1,420/2,"1mm target");
  tt.DrawLatex(.1,360/2,"10% branch");

  tt.DrawLatex(1.,260/2,"all");
  tt.SetTextColor(2);
  tt.DrawLatex(.8,190/2,"|cos#theta_{H}|<0.5");
  tt.SetTextColor(4);
  tt.DrawLatex(.8,120/2,"|cos#theta_{H}|<0.2");
 
  TArrow arrow;
  arrow.SetAngle(30);
  arrow.SetLineColor(6);
  arrow.SetFillColor(6);
  arrow.DrawArrow(.475,350/2,.475,300/2,.03);
  arrow.DrawArrow(.475+4.3-3.045,640/2,.475+4.3-3.045,600/2,.03);
  
  tt.SetTextColor(6);
  tt.DrawLatex(.54,310/2,"2^{+}");
  tt.DrawLatex(1.85,605/2,"1^{+}");
}
