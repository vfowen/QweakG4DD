void mkPEasymGraphs(){
  TFile *fout=new TFile("o_PEasyms.root","RECREATE");
  fout->Close();
  mkAngleGraphs();
  mkPositionGraphs();
}

void mkAngleGraphs(){
  int n=21;
  double ang[21]={-40,-35,-30,-25,-20,-15,-10,-7.5,-5,-2.5,0,2.5,5,7.5,10,15,20,25,30,35,40};
  double asym50[21]={-0.86,-0.79,-0.76,-0.77,-0.8,-0.8,-0.64,-0.51,-0.33,-0.15,0,0.16,0.34,0.5,0.64,0.76,0.8,0.77,0.76,0.79,0.86};
  double asym200[21]={-0.85,-0.8,-0.78,-0.76,-0.82,-0.82,-0.74,-0.62,-0.38,-0.15,0.01,0.16,0.38,0.62,0.74,0.83,0.82,0.77,0.78,0.81,0.85};
  double asym400[21]={-0.85,-0.8,-0.78,-0.75,-0.82,-0.83,-0.74,-0.78,-0.37,-0.15,0.01,0.16,0.37,0.64,0.75,0.83,0.83,0.76,0.78,0.81,0.85};

  TFile *fout=TFile::Open("o_PEasyms.root","UPDATE");
  TGraph *angle=new TGraph();
  angle->SetName("angle");
  for(int i=0;i<n;i++)
    angle->SetPoint(i,ang[i],asym50[i]);
  angle->Write();
  fout->Close();
}

void mkPositionGraphs(){
  /// look in nStripEvsX 
}
