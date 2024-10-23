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
  Sty->SetTitleSize(0.07,"xyz");
  Sty->SetTitleOffset(.6,"y");
  Sty->SetTitleOffset(1.,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.05,"xz");
  Sty->SetTickLength(.025,"y");
  Sty->SetNdivisions(10,"xyz");
  Sty->SetEndErrorSize(0);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();
  TCanvas canvas("hits","",600,800);

  canvas.Divide(1,2);

  canvas.cd(1);

  TFile fileS("sim_0plus_S11_450.root");
  TFile fileG("sim_0plus_gobbi_550.root");

  TH2I * proton_S = (TH2I*) fileS.Get("protonXY_s");

  TH2I * core_S = (TH2I*) fileS.Get("coreXY_s");

  TH2S frame("frame","",10,-13,13,10,-9,9);
  frame.GetXaxis()->SetTitle("#theta cos(#phi) (deg)");
  frame.GetYaxis()->SetTitle("#theta sin(#phi) (deg)");
  frame.GetXaxis()->CenterTitle();
  frame.GetYaxis()->CenterTitle();
  frame.Draw();

  proton_S->Draw("COL same");
  core_S->Draw("Zcol same");

  TLatex tt;
  tt.SetTextSize(.08);
  tt.DrawLatex(-11,6,"S11");
  
  canvas.cd(2);
  frame.Draw();

  TH2I * proton_G = (TH2I*) fileG.Get("protonXY_s");

  TH2I * core_G = (TH2I*) fileG.Get("coreXY_s");

  proton_G->Draw("COL same");
  core_G->Draw("Zcol same");
  tt.DrawLatex(-11,6,"Gobbi");

}
