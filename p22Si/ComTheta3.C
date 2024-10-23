{
  gROOT->Reset();

  TH2S frame("frame","",10,-1,1,10,0,16500);
  frame.GetXaxis()->SetTitle("cos(#theta_{pc})");
  frame.SetStats(kFALSE);
  frame.Draw();

  TFile file("/home/Carbon8/daq/corr_7Be.root");
  TH1I* histX = (TH1I*) file.Get("Be6/theta3_6Be_he3he3");
  histX->SetMarkerStyle(20);
  histX->Draw("same P");
  float Nx = histX->Integral();

  TFile fileS("sim.root");
  TH1I* sr = (TH1I*) fileS.Get("theta3");
  sr->SetLineColor(2);
  float Nr = sr->Integral();

  sr->Scale(Nx/Nr); 
  sr->Draw("L same");

  return;

  TH1I* sp = (TH1I*) fileS.Get("theta");
  sp->SetLineColor(4);
  float Np = sp->Integral();

  sp->Scale(Nx/Np); 
  sp->Draw("L same");

  return;

  double xx[100];
  double yy[100];
  int N = 0;;
  for (int i=1;i<200;i++)
    {
      float x = sr->GetBinCenter(i);


      if (x < 7.7) continue;
      if (x > 11.1) break;


      float y = sr->GetBinContent(i);

      float y1 = histX->GetBinContent(i);
      cout << x << " " << y / y1 << endl;

      xx[N] = x;
      yy[N] = y/y1;
      N++;
    }

  TGraph g(N,xx,yy);
  g.Draw("A*");
  g.Fit("pol1");


}
