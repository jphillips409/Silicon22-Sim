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
  TCanvas canvas("eff","",600,800);

  canvas.Divide(1,2);

  canvas.cd(1);
  const int n = 5;
  //26S, 0+_1, 1.7 MeV
  double x[n]={300,400,500,600,700};
  double y[n]={.1974,.299,.367,.380,.347};

  double y11[n]={.279,.324,.318,.240,.115};


  TH2S frame("frame","",10,200,800,10,0,.5);
  frame.GetXaxis()->SetTitle("dist (mm)");
  frame.GetYaxis()->SetTitle("Efficiency");
  frame.GetXaxis()->CenterTitle();
  frame.GetYaxis()->CenterTitle();
  frame.Draw();


  TGraph g11(n,x,y11);
  g11.SetLineColor(2);
  g11.SetLineStyle(2);
  g11.Draw("C");


  //26S 2+_1  1.7+2.0 MeV
  double y2_11[n]={.3705,.3029,.12203,.0472,.01945};
  double y2[n]={.289,.3114,.296,.221,.233};

  TGraph g2_11(n,x,y2_11);
  g2_11.SetLineColor(4);
  g2_11.SetLineStyle(2);
  g2_11.Draw("C");



  //26S 0+ 0.9 MeV
  double y3_11[n]={.176,.244,.2615,.2559,.228};
  double y3[n]={.0098,.07418,.1826,.2773,.322};


  TGraph g3_11(n,x,y3_11);
  g3_11.SetLineColor(3);
  g3_11.SetLineStyle(2);
  g3_11.Draw("C");

  TLatex tt;
  tt.SetTextColor(3);
  tt.DrawLatex(650,.45,"E_{T}=0.9 MeV");
  tt.SetTextColor(2);
  tt.DrawLatex(650,.37,"E_{T}=1.75 MeV");
  tt.SetTextColor(4);
  tt.DrawLatex(650,.29,"E_{T}=3.9 MeV");
  tt.SetTextColor(1);
  tt.DrawLatex (230,.43,"S11");

  canvas.cd(2);
  frame.Draw();


  TGraph g(n,x,y);
  g.SetLineColor(2);
  g.Draw("C");


  TGraph g2(n,x,y2);
  g2.SetLineColor(4);
  g2.Draw("C");


  TGraph g3(n,x,y3);
  g3.SetLineColor(3);
  g3.Draw("C");

tt.DrawLatex (230,.43,"Gobbi");
}
