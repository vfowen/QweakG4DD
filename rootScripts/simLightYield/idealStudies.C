void idealStudies(){
  const int nStudies=6;
  string fnms[nStudies]={
    "Bevel_R0.5mm.root",
    "Bevel_R1.0mm.root",
    "Bevel_R1.5mm.root",
    "Polish_R0.999.root",
    "Polish_R0.95.root",
    "Polish_R0.90.root"
  };

  TCanvas *c1[nStudies];
  for(int i=0;i<nStudies;i++){
    c1[i]=new TCanvas(Form("c%d",i),fnms[i].c_str());
    double slopeL(0),slopeR(0);
    doOne(fnms[i],slopeL,slopeR);
    cout<<fnms[i]<<"\t"<<slopeL<<"\t"<<slopeR<<endl;
  }
}

void doOne(string fnm, double &sl, double &sr){
  TFile *fin=TFile::Open(fnm.c_str(),"READ");
  TProfile *r=(TProfile*)fin->Get("RightPMT");
  int rbl=r->GetXaxis()->FindBin(-99);
  int rbh=r->GetXaxis()->FindBin( 99);
  double scale = r->Integral(rbl,rbh,"width");
  r->Scale(1/scale);

  TF1 *fr=new TF1("fr","pol1");
  r->SetTitle(fnm.c_str());
  r->Fit("fr","Q","",-90,-5);
  sr=fr->GetParameter(1);

  TProfile *l=(TProfile*)fin->Get("LeftPMT");
  int lbl=l->GetXaxis()->FindBin(-99);
  int lbh=l->GetXaxis()->FindBin( 99);
  scale = l->Integral(lbl,lbh,"width");
  l->Scale(1/scale);

  TF1 *fl=new TF1("fl","pol1");
  l->Fit("fl","Q","",5,90);
  sl=fl->GetParameter(1);

  r->SetLineColor(2);
  l->SetLineColor(4);
  r->DrawCopy();
  l->DrawCopy("same");
  fr->Draw("same");
  fl->Draw("same");
  fin->Close();
}
