{
  gROOT->Reset();
TStyle * Sty = new TStyle("MyStyle","MyStyle");
Sty->SetOptTitle(0);
Sty->SetOptStat(0);
Sty->SetPalette(8,0);
Sty->SetCanvasColor(10);
Sty->SetCanvasBorderMode(0);
Sty->SetFrameLineWidth(0);
Sty->SetFrameFillColor(10);
Sty->SetPadColor(10);
Sty->SetPadTickX(1);
Sty->SetPadTickY(1);
Sty->SetPadBottomMargin(.15);
Sty->SetPadTopMargin(.15);
Sty->SetPadLeftMargin(.115);
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
Sty->SetTitleOffset(1.3,"x");
Sty->SetTitleFillColor(10);
Sty->SetTitleTextColor(kBlack);
Sty->SetTickLength(.05,"xz");
Sty->SetTickLength(.025,"y");
Sty->SetNdivisions(5,"xyz");
Sty->SetEndErrorSize(0);
gROOT->SetStyle("MyStyle");
gROOT->ForceStyle();
 TCanvas canvas("chart","",500,600);

 TH2S frame("frame","",10,6.,12.5,10,10.,17.8);
frame.SetStats(kFALSE);
frame.GetXaxis()->SetLabelSize(0.);
frame.GetXaxis()->SetTickLength(0.);
frame.GetXaxis()->SetAxisColor(0.);
frame.GetYaxis()->SetLabelSize(0.);
frame.GetYaxis()->SetTickLength(0.);
frame.GetYaxis()->SetAxisColor(0.);
frame.Draw();







 TWbox   mg18(5.5,11.5,6.5,12.5);
 mg18.Draw();
 TWbox   mg19(6.5,11.5,7.5,12.5);
 mg19.Draw();
 TWbox   mg20(7.5,11.5,8.5,12.5,2);
 mg20.Draw();

 TWbox   mg21(8.5,11.5,9.5,12.5,2);
 mg21.Draw();
 TWbox   mg22(9.5,11.5,10.5,12.5,2);
 mg22.Draw();
 TWbox   mg23(10.5,11.5,11.5,12.5,2);
 mg23.Draw();
 TWbox   mg24(11.5,11.5,12.5,12.5,1);
 mg24.Draw();





 TWbox   al21(7.5,12.5,8.5,13.5,3);
 al21.Draw();

 TWbox   al22(8.5,12.5,9.5,13.5,2);
 al22.Draw();

 TWbox   al23(9.5,12.5,10.5,13.5,2);
 al23.Draw();

 TWbox   al24(10.5,12.5,11.5,13.5,2);
 al24.Draw();
 TWbox   al25(11.5,12.5,12.5,13.5,2);
 al25.Draw();


 TWbox   si22(7.5,13.5,8.5,14.5,3);
 si22.Draw();
 TWbox   si23(8.5,13.5,9.5,14.5,2);
 si23.Draw();
 TWbox   si24(9.5,13.5,10.5,14.5,2);
 si24.Draw();
 TWbox   si25(10.5,13.5,11.5,14.5,2);
 si25.Draw();
 TWbox   si26(11.5,13.5,12.5,14.5,2);
 si26.Draw();




 TWbox   p23(7.5,14.5,8.5,15.5,3);
 p23.Draw();
 TWbox   p26(10.5,14.5,11.5,15.5,2);
 p26.Draw();
 TWbox   p27(11.5,14.5,12.5,15.5,2);
 p27.Draw();


 TWbox   s27(10.5,15.5,11.5,16.5,2);
 s27.Draw();
 TWbox   s28(11.5,15.5,12.5,16.5,2);
 s28.Draw();


 TWbox   na17(5.5,10.5,6.5,11.5);
 na17.Draw();
 TWbox   na18(6.5,10.5,7.5,11.5);
 na18.Draw();
 TWbox   na19(7.5,10.5,8.5,11.5);
 na19.Draw();
 TWbox   na20(8.5,10.5,9.5,11.5,2);
 na20.Draw();
 TWbox   na21(9.5,10.5,10.5,11.5,2);
 na21.Draw();
 TWbox   na22(10.5,10.5,11.5,11.5,2);
 na22.Draw();
 TWbox   na23(11.5,10.5,12.5,11.5,1);
 na23.Draw();


 TWbox   stable(5.5,18,6.5,19,1);
 stable.Draw();
 TWbox   beta(6.8,18,7.8,19,2);
 beta.Draw();

 TWbox   proton(8.1,18,9.1,19);
 proton.Draw();


 TLine ll;
 ll.SetLineWidth(4);
 ll.DrawLine(7.5,10.,7.5,16.5);
 ll.DrawLine(8.5,10.,8.5,16.5);

 
 TLatex text;
 text.DrawLatex(8.7,13.8,"^{23}Si");
 text.DrawLatex(7.6,13.8,"^{22}Si");
 text.DrawLatex(7.6,12.8,"^{21}Al");
 text.DrawLatex(7.6,11.8,"^{20}Mg");
 text.DrawLatex(5.6,11.8,"^{18}Mg");
 text.DrawLatex(7.6,14.8,"^{23}P");
 text.DrawLatex(7.6,15.8,"^{24}S");
 text.DrawLatex(10.7,15.8,"^{27}S");
 text.DrawLatex(7.6,8.9,"N=8");
 text.DrawLatex(5.7,13.4,"Z=14");
 text.DrawLatex(5.7,15.4,"Z=16");
 text.SetTextSize(.03);
 text.SetTextColor(0);
 text.DrawLatex(5.6,18.4,"stable");
 text.SetTextColor(1);
 text.DrawLatex(6.9,18.4,"#beta-decay");
 text.DrawLatex(8.2,18.4,"#it{p}-decay");
 

 TArrow arrow;
 arrow.SetFillColor(1);
 arrow.SetAngle(30);
 arrow.DrawArrow(8,9.4,8,10);
 arrow.DrawArrow(5.7,14,6.4,14);
 arrow.DrawArrow(5.7,16,6.4,16);

 TArrow arrow2;
arrow2.SetFillColor(4);

 arrow2.SetLineColor(4);
 arrow2.SetLineWidth(4);
 arrow2.DrawArrow(8.7,14,8.4,14,.03);
 arrow2.DrawArrow(8.65,14.3,8.24,14.8,.03);
 arrow2.DrawArrow(8.65,13.7,8.24,13.2,.03);

 /*
 text.DrawLatex(2.9,5.9,"^{9}C");
 text.DrawLatex(3.9,5.9,"^{10}C");
 text.DrawLatex(2.9,4.9,"^{8}B");
 text.DrawLatex(3.9,4.9,"^{9}B");
 text.DrawLatex(1.9,4.9,"^{7}B");
 text.DrawLatex(1.8,3.9,"^{6}Be");
 text.DrawLatex(2.8,3.9,"^{7}Be");
 text.DrawLatex(3.8,3.9,"^{8}Be");
 text.DrawLatex(.8,2.9,"^{4}Li");
 text.DrawLatex(1.8,2.9,"^{5}Li");
 text.DrawLatex(2.8,2.9,"^{6}Li");
 text.DrawLatex(3.8,2.9,"^{7}Li");
 text.DrawLatex(.8,1.9,"^{3}He");
 text.DrawLatex(1.8,1.9,"^{4}He");
 text.DrawLatex(2.8,1.9,"^{5}He");
 text.DrawLatex(3.8,1.9,"^{6}He");


 TArrow arrow;
 arrow.SetLineColor(2);
 arrow.SetFillColor(2);
 arrow.SetAngle(40.);
 arrow.SetLineWidth(5);
 arrow.DrawArrow(2.8,6.,2.3,6.,.02,"|>");
 arrow.DrawArrow(3.3,6.,3.8,6.,.02,"|>");
 arrow.DrawArrow(3.,5.8,3.,5.3,.02,"|>");
 arrow.DrawArrow(2.7,5.8,2.2,5.3,.02,"|>");
 arrow.DrawArrow(2.8,4.,2.3,4.,.02,"|>");
 */
}
