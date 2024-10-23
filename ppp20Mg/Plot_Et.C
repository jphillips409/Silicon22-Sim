void Plot_Et()
{

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  TStyle * Sty = (TStyle*)gROOT->FindObject("MyStyle");
  if(!Sty)
    {
      Sty = new TStyle("MyStyle","MyStyle");
    }
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
  Sty->SetPadBottomMargin(.17);
  Sty->SetPadTopMargin(.03);
  Sty->SetPadLeftMargin(.17);
  Sty->SetPadRightMargin(.01);
  Sty->SetHistLineWidth(3);
  Sty->SetHistLineColor(kBlack);
  Sty->SetFuncWidth(3);
  Sty->SetFuncColor(kRed);

  Sty->SetLineWidth(3);
  Sty->SetLabelSize(0.06,"xyz");
  Sty->SetLabelOffset(0.02,"y");
  Sty->SetLabelOffset(0.02,"x");
  Sty->SetLabelColor(kBlack,"xyz");
  Sty->SetTitleSize(0.06,"xyz");
  Sty->SetTitleOffset(1.3,"y");
  Sty->SetTitleOffset(1.1,"x");
  Sty->SetTitleFillColor(10);
  Sty->SetTitleTextColor(kBlack);
  Sty->SetTickLength(.03,"xz");
  Sty->SetTickLength(.02,"y");
  Sty->SetNdivisions(5,"x");
  Sty->SetNdivisions(10,"yz");
  Sty->SetEndErrorSize(0);
  gROOT->SetStyle("MyStyle");
  gROOT->ForceStyle();



  TFile *ings = new TFile("GSI_Gs.root");
  if(!ings)
    {
      cout <<"No data" << endl;
      return;
    }


  TH1S *Sum = (TH1S*)gROOT->FindObject("Sum");
  if(Sum)
    {
      Sum->Reset();
    }
  Sum = new TH1S("Sum","Sum",600,0,10);

  TH1S *ground = (TH1S*)gROOT->FindObject("ground");
  if(!ground)
    {
      ground = (TH1S*)ings->Get("Erel")->Clone("ground");
    }


  float Ngs = 0.25;
  float Nex = 1.;

  Sum->Add(ground,Ngs);

  cout << "Done" << endl;

  TFile *inex = new TFile("GSI_Ex.root");
  if(!inex)
    {
      cout << "no data2" << endl;
      return;
    }

  TH1S *excite = (TH1S*)gROOT->FindObject("Excite");
  if(!excite)
    {
      excite = (TH1S*)inex->Get("Erel")->Clone("Excite");
    }

  Sum->Add(excite,Nex);



  TCanvas *mycan = new TCanvas("mycan","mycan",800,600);



  // Sum->Draw();
  
  TFile *ings1 = new TFile("SYS_Gs.root");
  if(!ings)
    {
      cout <<"No data" << endl;
      return;
    }


  TH1S *Sum1 = (TH1S*)gROOT->FindObject("Sum1");
  if(Sum1)
    {
      Sum1->Reset();
    }
  Sum1 = new TH1S("Sum1","Sum1",600,0,10);

  TH1S *ground1 = (TH1S*)gROOT->FindObject("ground1");
  if(!ground1)
    {
      ground1 = (TH1S*)ings1->Get("Erel")->Clone("ground1");
    }


  Sum1->Add(ground1,Ngs);

  cout << "Done" << endl;

  TFile *inex1 = new TFile("SYS_Ex.root");
  if(!inex1)
    {
      cout << "no data2" << endl;
      return;
    }

  TH1S *excite1 = (TH1S*)gROOT->FindObject("Excite1");
  if(!excite1)
    {
      excite1 = (TH1S*)inex1->Get("Erel")->Clone("Excite1");
    }

  Sum1->Add(excite1,Nex);

  
  Sum->SetTitle("Reconstructed Breakup Energy");
  Sum->GetXaxis()->SetTitle("Energy (MeV)");
  Sum->GetXaxis()->CenterTitle();
  Sum->GetYaxis()->SetTitle("Counts");
  Sum->GetYaxis()->CenterTitle();
  Sum->Rebin(4);
  Sum1->Rebin(4);
  Sum->Draw();
  Sum->GetXaxis()->SetRangeUser(1,6);
  Sum1->Draw("same");
  Sum1->SetLineColor(kRed);
  Sum1->SetLineStyle(9);

  return;
}
