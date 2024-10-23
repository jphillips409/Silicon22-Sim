{
  const int n = 6;
  double x[n]={0,2,4,6,8,10};
  double y[n]={1.,.933,.867,.8141,.758,.713};

  TGraph g(n,x,y);
  g.Draw("*A");
  g.Fit("pol2");
}
