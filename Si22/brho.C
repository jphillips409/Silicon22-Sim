{

  TFile file("sim.root");
  TH1I* hist35 = (TH1I*) file.Get("rigidity_35K");
  TH1I* hist36 = (TH1I*) file.Get("rigidity_36Ca");
  TH1I* hist37 = (TH1I*) file.Get("rigidity_37Ca");

  double ymax = 10000.;
  //E.A = 75
  double xmin = 1.85;
  double xmax = 2.35;


  //100 MeV/A
  //double xmin = 2.5;
  //double xmax = 3.0;

  TH2S frame("frame","",10,xmin,xmax,10,10,ymax);
  frame.SetStats(kFALSE);
  frame.GetXaxis()->SetTitle("B#rho (Tm)");
  frame.GetYaxis()->SetTitle("Counts");
  frame.GetXaxis()->CenterTitle();
  frame.GetYaxis()->CenterTitle();
frame.Draw();

  hist35->SetLineColor(2);
  hist35->Draw("same");

  hist36->SetLineColor(4);
  hist36->Scale(.6);
  hist36->Draw("same");


  hist37->SetLineColor(3);
  hist37->Scale(.14);
  hist37->Draw("Same");

  
  //double center = 2.21;
  double center = 2.064;
  double brho_min = center - center*.03;
  double brho_max = center + center*.03;
  cout << brho_min << " " << brho_max << endl;
  
  TLine line;
  line.SetLineStyle(2);
  line.DrawLine(brho_min,0,brho_min,ymax);
  line.DrawLine(brho_max,0,brho_max,ymax);
  
  TLegend leg(.63,.32,.89,.85);
  leg.AddEntry(hist35,"^{37}Ca#rightarrow^{36}Ca#rightarrow#it{p}+^{35}K","l");
  leg.AddEntry(hist36,"^{37}Ca#rightarrow#gamma+^{36}Ca ","l");
  leg.AddEntry(hist37," unreacted ^{37}Ca beam","l");
  leg.Draw();


}
