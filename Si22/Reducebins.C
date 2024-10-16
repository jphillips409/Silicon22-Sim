void Reducebins()
{

  ifstream ifile("zn12_allM.out");
  if(!ifile.is_open())
    {
      cout << "No data" << endl;
      return;
    }

  const int N = 221;
  float yarrayTr[N] = {0.};
  float xarrayTr[N] = {0.};

  for(int i = 0;i<N;i++)
    {
      ifile >> xarrayTr[i] >> yarrayTr[i];
    }


  TH1F *Trans = new TH1F("name","name",221,-400,400);

  for(int i=0;i<N;i++)
    {
      int j= Trans->FindBin(xarrayTr[i]);
      Trans->SetBinContent(j,yarrayTr[i]);
    }

  Trans->Rebin(4);

  ofstream ofile("zn12_allM_reduce.out");
  for(int i = 1;i<Trans->GetNbinsX();i++)
    {
      ofile << Trans->GetBinCenter(i) << " " << Trans->GetBinContent(i) << endl;

    
    }

  Trans->Draw();

  ifile.close();
  ofile.close();

  return;
}
