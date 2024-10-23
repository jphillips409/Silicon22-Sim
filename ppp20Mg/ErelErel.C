{
  TFile file("sim.root");
  TH2S frame("frame","",10,3,6,10,3,6);
  frame.GetXaxis()->SetTitle("E_{T}(correct) [MeV]");
  frame.GetYaxis()->SetTitle("E_{T}(wrong) [MeV]");
  frame.GetXaxis()->CenterTitle();
  frame.GetYaxis()->CenterTitle();
  frame.SetStats(kFALSE);
  frame.Draw();
  TH2S* mapp = (TH2S*) file.Get("Erel_Erel");

  mapp->Draw("ZCOL same");
}
