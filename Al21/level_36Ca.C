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
Sty->SetPadBottomMargin(.16);
Sty->SetPadLeftMargin(.18);
Sty->SetPadTopMargin(.05);
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
Sty->SetTitleOffset(1.4,"y");
Sty->SetTitleOffset(1.3,"x");
Sty->SetTitleFillColor(10);
Sty->SetTitleTextColor(kBlack);
Sty->SetTickLength(.02,"xz");
Sty->SetTickLength(.015,"y");
Sty->SetNdivisions(5,"xyz");
Sty->SetEndErrorSize(0);
gROOT->SetStyle("MyStyle");
gROOT->ForceStyle();

 TCanvas canvas("level_36Ca");
    double delta = .06;
  TH2S frame("frame","",10,0,1.,10,-1,5);
  frame.GetXaxis()->SetLabelSize(0.);
  frame.GetXaxis()->SetAxisColor(0.);
  //frame.GetXaxis()->SetTickWidth(0.);

  frame.GetYaxis()->SetTitle("Energy (MeV)");
  frame.GetYaxis()->CenterTitle();
  frame.SetStats(kFALSE);
  
  frame.Draw();

  TLine ll;
  ll.DrawLine(.1,0,.3,0);

  ll.DrawLine(.1,3.045,.3,3.045);


  ll.DrawLine(.1,4.192,.3,4.192);
  ll.DrawLine(.1,4.3,.3,4.3);

  ll.DrawLine(.4,2.57,.6,2.57);
  ll.DrawLine(.4,2.57+1.553,.6,2.57+1.553);
  ll.DrawLine(.7,2.57+.083,.9,2.57+.087);

  TLatex tt;
  tt.DrawLatex(.152,-.4,"^{36}Ca");
  tt.DrawLatex(.424,2.08,"#it{p}+^{35}K");
  tt.DrawLatex(.73,2.2,"2#it{p}+^{34}Ar");

  tt.DrawLatex( .05,-.135,"0^{+}");
  tt.DrawLatex(.05,2.82,"2^{+}");
  tt.DrawLatex(.05,4.01,"3^{-}");
  tt.DrawLatex(.05,4.39,"1^{+}");

  tt.DrawLatex(.62,2.33,"3/2^{+}");
  tt.DrawLatex(.62,3.88,"(1/2^{+})");


  TArrow arrow;
  arrow.SetAngle(30);
  arrow.SetFillColor(1);
  arrow.DrawArrow(.3,3.045,.4,2.57,.03);


}
