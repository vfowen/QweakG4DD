void getPlots(){
  TFile *fa=TFile::Open("oavgmodelideal23mirroroffset000nmodels8.root","READ");
  //TFile *fa=TFile::Open("oavgmodelideal23asisoffset000nmodels8.root","READ");
  TH1D *pel=(TH1D*)fa->Get("peL_pos_7");//posDiff light*asym
  TH1D *per=(TH1D*)fa->Get("peR_pos_7");
  gStyle->SetOptStat(0);
  
  TCanvas *c1=new TCanvas("c1","c1");
  c1->Divide(3,2);
  c1->cd(1);
  pel->SetTitle("Red Left PE *asym | Blue Right PE*asym");
  pel->SetLineColor(2);
  pel->GetYaxis()->SetRangeUser(-0.02,0.02);
  pel->DrawCopy();
  per->DrawCopy("same");
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  c1->cd(4);
  TH1D *pelScaled=(TH1D*)pel->Clone("pelScaled");
  TH1D *perScaled=(TH1D*)per->Clone("perScaled");
  TH1D *lnorm=(TH1D*)fa->Get("peL_pos_0");//light*1
  TH1D *rnorm=(TH1D*)fa->Get("peR_pos_0");
  pelScaled->Divide(lnorm);
  perScaled->Divide(rnorm);
  
  TH1D *ab=(TH1D*)pelScaled->Clone("ab");
  ab->Add(perScaled);
  ab->Scale(0.5);
  ab->SetTitle("bin by bin (#sum{PEL*A}/#sum{PEL} + #sum{PER*A}/#sum{PER})/2");
  ab->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  c1->cd(2);
  lnorm->SetTitle("Red Left PE | Blue Right PE");
  lnorm->SetLineColor(2);
  lnorm->DrawCopy();
  rnorm->DrawCopy("same");
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  c1->cd(3);
  pelScaled->SetTitle("Red #sum{PEL*A}/#sum{PEL} | Blue: #sum{PER*A}/#sum{PER}");
  pelScaled->SetLineColor(2);
  pelScaled->GetYaxis()->SetRangeUser(-1e-6,1e-6);
  pelScaled->DrawCopy();
  perScaled->DrawCopy("same");
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  
  c1->cd(5);
  TH1D *fold=foldHist(ab);
  fold->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  c1->cd(6);
  TH1D *cdfAB=cdf(fold);
  cdfAB->SetTitle("cdf");
  cdfAB->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  
  fa->Close();
}

TH1D *foldHist(TH1D *a){
  int nbin=a->GetXaxis()->GetNbins();
  TH1D *h=new TH1D(Form("fold_%s",a->GetName()),Form("fold_%s",a->GetName()),nbin/2,0,a->GetBinCenter(nbin)+a->GetBinWidth(nbin)/2);

  for(int i=1;i<=nbin/2;i++){
    double vl = a->GetBinContent(i);
    double vr = a->GetBinContent(nbin-i+1);
    //if(vr+vl>0)
    h->SetBinContent(nbin/2-i+1,(vr+vl));
  }
  return h;
}

TH1D *cdf(TH1D *b){
  TH1D *h=(TH1D*)b->Clone(Form("%s_cdf",b->GetName()));
  int nbin=h->GetXaxis()->GetNbins();
  for(int i=2;i<=nbin;i++)
    h->SetBinContent(i,h->GetBinContent(i-1)+h->GetBinContent(i));
  return h;
}
