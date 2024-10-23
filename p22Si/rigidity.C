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
Sty->SetPadLeftMargin(.15);
Sty->SetPadTopMargin(.01);
Sty->SetPadRightMargin(.05);
Sty->SetHistLineWidth(3);
Sty->SetHistLineColor(kRed);
Sty->SetFuncWidth(3);
Sty->SetFuncColor(kGreen);
Sty->SetLineWidth(3);
Sty->SetLabelSize(0.06,"xyz");
Sty->SetLabelOffset(0.02,"y");
Sty->SetLabelOffset(0.02,"x");
Sty->SetLabelColor(kBlack,"xyz");
Sty->SetTitleSize(0.06,"xyz");
Sty->SetTitleOffset(1.2,"y");
Sty->SetTitleOffset(1.1,"x");
Sty->SetTitleFillColor(10);
Sty->SetTitleTextColor(kBlack);
Sty->SetTickLength(.02,"xz");
Sty->SetTickLength(.015,"y");
Sty->SetNdivisions(5,"xyz");
Sty->SetEndErrorSize(0);
gROOT->SetStyle("MyStyle");
gROOT->ForceStyle();

 TCanvas canvas("rigidity");

 TFile file("sim.root");
 TH1I* hist_beam = (TH1I*) file.Get("rigidity_23Si");
 TH1I* hist_22Si = (TH1I*) file.Get("rigidity_22Si_before");
 TH1I* hist_22Si_after = (TH1I*) file.Get("rigidity_22Si");

 TH2S frame("frame","",10,2.,2.3,10,0,140);
 frame.GetXaxis()->SetTitle("B#rho (Tm)");
 frame.GetYaxis()->SetTitle("Counts");
 frame.GetXaxis()->CenterTitle();
 frame.GetYaxis()->CenterTitle();
 frame.Draw();

 hist_22Si->SetLineColor(4); 
 hist_22Si->Draw("same");

 hist_beam->SetLineColor(2);
 hist_beam->Scale(.07);
 hist_beam->Draw("same");

 TLine ll;
 ll.SetLineStyle(2);
 ll.DrawLine(2.207,0,2.207,2500);
 ll.DrawLine(2.207+.0896,0,2.207+.0896,2500);

 hist_22Si_after->SetLineColor(3);
 hist_22Si_after->Draw("same");
}
