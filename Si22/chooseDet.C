{
  TFile fileGobbi("sim_gobbi.root");
  TFile fileHira("sim_hira.root");
  TFile fileGobbi_Hira("sim_Gobbi_Hira.root");


  TH2I* map_p_gobbi = (TH2I*) fileGobbi.Get("protonXY_s");
  TH2I* map_p_hira = (TH2I*) fileHira.Get("protonXY_s");
  TH2I* map_p_gobbi_hira = (TH2I*) fileGobbi_Hira.Get("protonXY_s");


  TH2I* map_c_gobbi = (TH2I*) fileGobbi.Get("coreXY_s");
  TH2I* map_c_hira = (TH2I*) fileHira.Get("coreXY_s");
  TH2I* map_c_gobbi_hira = (TH2I*) fileGobbi_Hira.Get("coreXY_s");


  TCanvas canvas("chooseDet","",600,800);
  canvas.Divide(1,3);
  canvas.cd(1);
  map_p_gobbi->Draw("COL");
  map_c_gobbi->Draw("COL same");

  TLatex tt;
  tt.DrawLatex(-15,7,"18%");


  canvas.cd(2);
  map_p_hira->Draw("COL");
  map_c_hira->Draw("COL same");
  
  tt.DrawLatex(-15,7,"9%");
  canvas.cd(3);
  map_p_gobbi_hira->Draw("col");
  map_c_gobbi_hira->Draw("col same");

  tt.DrawLatex(-15,7,"10%");
}
