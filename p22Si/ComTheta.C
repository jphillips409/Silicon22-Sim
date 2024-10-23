{
  gROOT->Reset();
  TFile fdata("/home/Boron8/B8/sort.root");
  TH1I* vdata = (TH1I*) fdata.Get("corr/B8/ThetaCM_IAS");
  vdata->SetMarkerStyle(20);
  vdata->Draw("P");
  float Ndata = vdata->Integral();
  vdata->GetXaxis()->SetRangeUser(0,14);


  TFile fsim("sim.root");
  TH1I* vsim = (TH1I*) fsim.Get("thetaR");
  float Nsim = vsim->Integral();
  vsim->SetLineColor(2);
  vsim->Scale(Ndata/Nsim);
  vsim->Draw("same");

}
