{
  gROOT->Reset();
  TFile fdata("/home/Boron8/B8/sort.root");
  TH1I* vdata = (TH1I*) fdata.Get("corr/B8/VelocityCM_IAS");
  vdata->SetLineWidth(2);
  vdata->Draw();

  float Ndata = vdata->Integral(67,82);


  TFile fsim("sim.root");
  TH1I* vsim = (TH1I*) fsim.Get("vel");

  float Nsim = vsim->Integral();
  vsim->Scale(Ndata/Nsim);
  vsim->SetLineColor(2);
  vsim->Draw("same");
}
