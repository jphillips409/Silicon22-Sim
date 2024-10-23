{
  TCanvas canvas("res","",600,800);
 const int n = 11;
 double x[n]={2,5,7,10,15,20,40,60,80,100,128};
 double y[n]={.3135,.2364,.22,.2128,.2085 ,.2074,.206,.2057,.2056,.2055,.2056};
 double yt[n]={.287,.1746,.1357 ,.1191,.1067, .1044,.09954,.09887,.09849,.09828,.09831};
 double ytt[n]={.2622,.1638,.1192 ,.1004,.08611,.08398,.07827,.07736,.07692,.07674,.07664};

TH2S frame("frame","",10,0,128,10,.06,.35);
frame.GetXaxis()->SetTitle("# of Rings");
frame.GetYaxis()->SetTitle("rms (MeV)");
frame.GetXaxis()->CenterTitle();
frame.GetYaxis()->CenterTitle();
frame.Draw();

TGraph g(n,x,y);
g.SetMarkerStyle(20);
g.Draw("Pl");

TGraph gt(n,x,yt);
gt.SetMarkerStyle(21);
gt.SetMarkerColor(4);
gt.SetLineColor(4);
gt.Draw("Pl");

TGraph gtt(n,x,ytt);
gtt.SetMarkerStyle(22);
gtt.SetMarkerColor(2);
gtt.SetLineColor(2);
gtt.Draw("Pl");

 TLine ll;
 ll.SetLineStyle(2);
 ll.DrawLine(0.,y[10],128,y[10]);
 ll.SetLineColor(4);
 ll.DrawLine(0.,yt[10],128,yt[10]);
 ll.SetLineColor(2);
 ll.DrawLine(0.,ytt[10],128,ytt[10]);


}
