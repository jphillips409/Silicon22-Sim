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
Sty->SetPadLeftMargin(.12);
Sty->SetPadTopMargin(.05);
Sty->SetPadRightMargin(.05);
Sty->SetHistLineWidth(3);
Sty->SetHistLineColor(kRed);
Sty->SetFuncWidth(3);
Sty->SetFuncColor(kGreen);
Sty->SetLineWidth(3);
Sty->SetLabelSize(0.07,"xyz");
Sty->SetLabelOffset(0.02,"y");
Sty->SetLabelOffset(0.02,"x");
Sty->SetLabelColor(kBlack,"xyz");
Sty->SetTitleSize(0.07,"xyz");
Sty->SetTitleOffset(.8,"y");
Sty->SetTitleOffset(1.,"x");
Sty->SetTitleFillColor(10);
Sty->SetTitleTextColor(kBlack);
Sty->SetTickLength(.02,"xz");
Sty->SetTickLength(.015,"y");
Sty->SetNdivisions(5,"xyz");
Sty->SetEndErrorSize(0);
gROOT->SetStyle("MyStyle");
gROOT->ForceStyle();
 TCanvas canvas("Q2p");

 TH2S frame("frame","",10,0,1.35,10,0,3);
   frame.GetXaxis()->SetLabelSize(0.);
   frame.GetXaxis()->SetAxisColor(0);
   frame.GetYaxis()->SetTitle("Q_{2p} (MeV)");
   frame.GetXaxis()->CenterTitle();
   frame.GetYaxis()->CenterTitle();
   frame.Draw();

   //GSM
  TLine ll;
 ll.DrawLine(.1,1.752,.2,1.750);
 ll.DrawLine(.2,1.074,.3,1.074);
 ll.DrawLine(.3,0,.4,0);

 TArrow arrow;
 arrow.SetFillColor(2);
 arrow.SetLineColor(2);
 arrow.SetAngle(30);
 arrow.DrawArrow(.2,1.750,.25,1.074);
 arrow.DrawArrow(.3,1.074,.35,0);

 //Brown
 ll.DrawLine(.5,2.07,.6,2.07);
 ll.DrawLine(.6,1.3,.7,1.3);
 ll.DrawLine(.7,0,.8,0);

 arrow.DrawArrow(.6,2.07,.65,1.3);
 arrow.DrawArrow(.7,1.3,.75,0);

 //HOLT
 ll.DrawLine(.9,2.833,1.,2.833);
 ll.DrawLine(1.0,1.696,1.1,1.696);
 ll.DrawLine(1.1,0,1.2,0);

 arrow.DrawArrow(1.,2.833,1.05,1.696);
 arrow.DrawArrow(1.1,1.69,1.15,0);

 TLatex tt;
 tt.DrawLatex(.16,-.27,"GSM");
 tt.DrawLatex(.52,-.27,"Alex Brown");
 tt.DrawLatex(.94,-.27,"Holt et al.");

 tt.DrawLatex(.73,2.77,"^{22}Si(2^{+})");
 tt.DrawLatex(1.12,1.67,"^{21}Al(1/2^{+})");
 tt.DrawLatex(.92,.036,"^{20}Mg(0^{+})");
 
}
