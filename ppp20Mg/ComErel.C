{
  gROOT->Reset();
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
Sty->SetPadBottomMargin(.15);
Sty->SetPadTopMargin(.05);
Sty->SetPadLeftMargin(.16);
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
Sty->SetTitleOffset(1.,"x");
Sty->SetTitleFillColor(10);
Sty->SetTitleTextColor(kBlack);
Sty->SetTickLength(.03,"xz");
Sty->SetTickLength(.02,"y");
Sty->SetNdivisions(5,"xyz");
Sty->SetEndErrorSize(0);
gROOT->SetStyle("MyStyle");
gROOT->ForceStyle();
  float pi = acos(-1.);


  TCanvas canvas("ComErel_8B");
  TH2S frame("frame","",10,6.4,10,10,0,700);
  frame.SetStats(kFALSE);
  frame.GetXaxis()->SetTitle("E*(^{8}B) [MeV]");
  frame.GetYaxis()->SetTitle("Counts");
  frame.GetXaxis()->CenterTitle();
  frame.GetYaxis()->CenterTitle();
  
  float const dif = .45;
  float const cen = 8.;
  float const mul = 690.2*.08;

  frame.Draw();

  TFile fdata("/home/Boron8/B8/sort.root");
  TH1I* vdata = (TH1I*) fdata.Get("corr/B8/Ex8B_2p6Li");
  vdata->SetLineWidth(3);
  vdata->SetLineColor(1);

  //vdata->Rebin(2);
  vdata->SetMarkerStyle(20);
  vdata->SetMarkerSize(1.5);
  for (int i=0;i<500;i++)
    {
      float y1 = vdata->GetBinContent(i);
      vdata->SetBinError(i,sqrt(y1));
    }  


  float Ndata = vdata->Integral();


  TFile fsim100("sim.root");
  TH1I* vsim100 = (TH1I*) fsim100.Get("Erel");
  vsim100->Scale(.128*1.2); //100 kev


  for (int i=0;i<500;i++)
    {
      float x = vsim100->GetBinCenter(i);
      float y2 = mul*exp(-pow((cen-x)/dif,2)/2.);
      float y1 = vsim100->GetBinContent(i);
      vsim100->SetBinContent(i,y1+y2);

    }



  vsim100->SetLineColor(2);
  vsim100->SetLineWidth(3);
  vsim100->Draw("same L");

  //TF1 * funct = new TF1("funct","2.*(3.2*x -17.2)",7.5,11.7);
  //TF1 * funct = new TF1("funct","(-258.9+40.*x)/1.5",6.4,8);
  TF1 * funct = new TF1("funct","[0]*exp(-pow((x-[1])/[2],2)/2.)",6.4,8);
  funct->SetParameter(0,mul);
  funct->SetParameter(1,cen);
  funct->SetParameter(2,dif); 
  funct->SetLineColor(1);
  funct->SetLineStyle(2);

  funct->Draw("same");

  vdata->Draw("same P");


}
