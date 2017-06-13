void drawAngles(){
  const int nbars=20;
  string fnms[nbars]={
    "o_avgModel_md1config16_model2_23_asIs_offset_0.00_Nmodels_7_symMustMD3.root",
    "o_avgModel_md1config5_model2_23_asIs_offset_0.00_Nmodels_7_symMustMD3.root",
    "o_avgModel_md2config3run1par_model2_23_asIs_offset_0.00_Nmodels_7_symMustMD3.root",
    "o_avgModel_md2config11_model2_23_asIs_offset_0.00_Nmodels_7_symMustMD3.root",
    "o_avgModel_md3config4_23_asIs_offset_0.00_Nmodels_7_symMustMD3.root",
    "o_avgModel_md4config4_23_asIs_offset_0.00_Nmodels_7_symMustMD3.root",
    "o_avgModel_md5config4_23_asIs_offset_0.00_Nmodels_7_symMustMD3.root",
    "o_avgModel_md6config3_23_asIs_offset_0.00_Nmodels_7_symMustMD3.root",
    "o_avgModel_md7config2_23_asIs_offset_0.00_Nmodels_7_symMustMD3.root",
    "o_avgModel_md8config16_23_asIs_offset_0.00_Nmodels_7_symMustMD3.root",
    "o_avgModel_md8configMG_23_asIs_offset_0.00_Nmodels_7_symMustMD3.root",
    "o_avgModel_ideal23_asIs_offset_0.00_Nmodels_7_symMustMD3_symPEs_asymPEs000.root",
    "o_avgModel_ideal23_asIs_offset_0.00_Nmodels_7_symMustMD3_symPEs_asymPEs001.root",
    "o_avgModel_ideal23_asIs_offset_0.00_Nmodels_7_symMustMD3_symPEs_asymPEs005.root",
    "o_avgModel_ideal23_asIs_offset_0.00_Nmodels_7_symMustMD3_symPEs_asymPEs010.root",
    "o_avgModel_md1config16_model2_23_asIs_offset_0.00_Nmodels_7_SymMustMD1.root",
    "o_avgModel_md1config16_model2_23_asIs_offset_0.00_Nmodels_7_SymMustMD3.root",
    "o_avgModel_ideal23_asIs_offset_0.00_Nmodels_7_symMustMD3_symPEs_asymPEs001pos.root",
    "o_avgModel_ideal23_asIs_offset_0.00_Nmodels_7_symMustMD3_symPEs_asymPEs005pos.root",
    "o_avgModel_ideal23_asIs_offset_0.00_Nmodels_7_symMustMD3_symPEs_asymPEs010pos.root"
  };

  double x,y;
  TGraph *gr=new TGraph();
  int ivar=0;
  for(int i=0;i<nbars;i++){
  //for(int i=0;i<1;i++){
    doOne(fnms[i],i,x,y,ivar);
    gr->SetPoint(i,x,y);
    cout<<i<<"\t"<<x<<"\t"<<y<<endl;
  }
  TCanvas *c1=new TCanvas("c1","c1");
  gr->SetTitle(";light imbalance integral; abias [ppb]");
  gr->SetMarkerStyle(20);
  gr->Draw("AP");
  gPad->SetGridx(1);
  gPad->SetGridy(1);

}

void doOne(string fnm, int nr, double &integ, double &abias,int iVar){
  //cout<<"Processing "<<fnm<<endl;
  string xVar[2]={"ang","pos"};
  string xVr[2]={"Qang","pos"};
  float xMax=89;
  if(iVar==1)
    xMax=100;
  
  TFile *fin=TFile::Open(fnm.c_str(),"READ");
  TH1D *xvar=(TH1D*)fin->Get(Form("x_%s",xVar[iVar].c_str()));  
  TH1D *peLvar=(TH1D*)fin->Get(Form("peL_%s_0",xVr[iVar].c_str()));
  TH1D *peRvar=(TH1D*)fin->Get(Form("peR_%s_0",xVr[iVar].c_str()));

  //cout<<xvar->GetTitle()<<endl;
  // double rebin=10;
  // xvar->Rebin(rebin);
  // peLvar->Rebin(rebin);
  // peRvar->Rebin(rebin);
  int nbin=xvar->GetXaxis()->GetNbins();
  TH1D* xvarSym=(TH1D*)xvar->Clone(Form("xvarSym_%d",nr));
  //cout<<"xvar int: "<<xvarSym->Integral()<<endl;
  for(int i=1;i<=nbin;i++)
    xvarSym->SetBinContent(i,xvar->GetBinContent(i)+xvar->GetBinContent(nbin-i+1));
  //cout<<"xvarSym int: "<<xvarSym->Integral()<<endl;

  //cout<<nr<<"int \t"<<peLvar->Integral()<<"\t"<<peRvar->Integral()<<endl;
  peLvar->Scale(1/peLvar->Integral());
  peRvar->Scale(1/peRvar->Integral());
  //cout<<nr<<"int \t"<<peLvar->Integral()<<"\t"<<peRvar->Integral()<<endl;

  TH1D *peL=(TH1D*)peLvar->Clone(Form("peL_%d",nr));
  peL->Divide(peLvar,xvarSym);
  TH1D *peR=(TH1D*)peRvar->Clone(Form("peR_%d",nr));
  peR->Divide(peRvar,xvarSym);
  //cout<<nr<<"Int \t"<<peL->Integral()<<"\t"<<peR->Integral()<<endl;
  
  TH1D *asPE=(TH1D*)peL->Clone(Form("asPE_%d",nr));
  nbin=peL->GetXaxis()->GetNbins();
  TH1D *mirPer=(TH1D*)peR->Clone("mirPer");
  for(int i=1;i<=nbin;i++){
    double vl=peL->GetBinContent(i);
    //double vr=peR->GetBinContent(nbin-i-1);
    double vr=peR->GetBinContent(i);
    mirPer->SetBinContent(nbin-i+1,vr);
    if(vr+vl==0) continue;
    double va=(vr-vl)/(vr+vl);
    asPE->SetBinContent(i,va);
  }
  gStyle->SetOptStat(0);
  TCanvas *c1=new TCanvas(Form("c1_%d",nr),fnm.c_str(),1000,1200);
  c1->Divide(3,3);
  c1->cd(1);
  peL->SetTitle("PEs: Red/Blue == +/-");
  peL->DrawCopy();
  peR->SetLineColor(2);
  peR->DrawCopy("same");
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  c1->cd(2);
  gStyle->SetOptStat("neMRiou");
  TH1D *d1=(TH1D*)peR->Clone(Form("d1_%d",nr));
  TH1D *d2=(TH1D*)peR->Clone(Form("d2_%d",nr));
  TH1D *d3=(TH1D*)peR->Clone(Form("d3_%d",nr));
  d1->Add(peR,peL);
  d2->Multiply(d1,xvarSym);
  d3->Multiply(d2,asPE);
  d3->SetTitle("(PE+ + PE-)*tracks*A");
  d3->DrawCopy();
  // peL->DrawCopy();
  // mirPer->SetLineColor(2);
  // mirPer->DrawCopy("same");
  // cout<<"\t"<<peL->Integral()<<"\t"<<mirPer->Integral()<<endl;

  c1->cd(3);
  d1->SetTitle("PE+ + PE-");
  d1->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  
  c1->cd(4);
  TH1D *d1foldm=fold(d1,-1);
  d1foldm->SetTitle("PE+ + PE- folded and diff");
  d1foldm->GetXaxis()->SetRangeUser(0,xMax);
  d1foldm->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  c1->cd(5);
  TH1D *d1foldp=fold(d1,1);
  d1foldp->SetTitle("PE+ + PE- folded and sum");
  d1foldp->GetXaxis()->SetRangeUser(0,xMax);
  d1foldp->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  
  
  c1->cd(6);
  TH1D *d4=(TH1D*)asPE->Clone("d4");
  for(int i=1;i<=nbin/2;i++){
    double vasL = asPE->GetBinContent(i);
    double vasR = asPE->GetBinContent(nbin-i+1);

    double vtrL = xvarSym->GetBinContent(i);
    double vtrR = xvarSym->GetBinContent(nbin-i+1);

    double vplL = peL->GetBinContent(i);
    double vplR = peL->GetBinContent(nbin-i+1);

    double vprL = peR->GetBinContent(i);
    double vprR = peR->GetBinContent(nbin-i+1);

    if(((vprL/vtrL+vplL/vtrL) + (vprR/vtrR+vplR/vtrR)) <= 0)
      d4->SetBinContent(nbin-i+1,0);
    else
      d4->SetBinContent(nbin-i+1,
			(vasL*(vprL/vtrL+vplL/vtrL) + vasR*(vprR/vtrR+vplR/vtrR) )/
			((vprL/vtrL+vplL/vtrL) + (vprR/vtrR+vplR/vtrR) ));
    d4->SetBinContent(i,0);
  }
  d4->SetTitle("(A_{i}*(P+_{i}/t_{i} + P-_{i}/t_{i}) + A_{nv-i+1}*(P+_{nv-i+1}/t_{nv-i+1} + P-_{nv-i+1}/t_{nv-i+1}))/(weight)");
  d4->GetXaxis()->SetRangeUser(0,xMax);
  d4->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  c1->cd(7);
  TH1D *xvarSymFold=fold(xvarSym,1);
  xvarSymFold->SetTitle("folded tracks and summed");
  xvarSymFold->GetXaxis()->SetRangeUser(0,xMax);
  xvarSymFold->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  //gStyle->SetOptStat(0);
  c1->cd(8);
  asPE->SetTitle("(PE+ - PE-)/(PE+ + PE-)");
  asPE->GetXaxis()->SetRangeUser(-xMax,xMax);
  //asPE->DrawCopy();
  TH1D *peTrksFold = (TH1D*)d1foldp->Clone("peTrksFold");
  peTrksFold->Multiply(d1foldp,xvarSymFold);
  peTrksFold->SetTitle("(folded PE+ + PE-)*(folded tracks)");
  //peTrksFold->DrawCopy();

  TH1D *d5=(TH1D*)d4->Clone(Form("d5_%d",nr));
  d5->Multiply(d4,peTrksFold);
  d5->SetTitle("pad5*pad6*pad7 == (PE sum)*Asym*(tracks)");
  d5->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  c1->cd(9);
  TH1D *asPEfold=fold(asPE,1);
  asPEfold->SetTitle("(PE+ - PE-)/(PE+ + PE-) folded and summed");
  asPEfold->GetXaxis()->SetRangeUser(0,xMax);
  asPEfold->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  gStyle->SetOptStat(0);
  TCanvas *c2=new TCanvas(Form("c2_%d",nr),fnm.c_str(),1000,800);
  c2->Divide(2,2);
  c2->cd(1);
  //peL->SetTitle("PEs: Red/Blue == +/-");
  peL->SetTitle("PEs/tracks: Red/Blue == PE+_{i}/tr_{i} / PE-_{i}/tr_{i}");
  peL->DrawCopy();
  peR->SetLineColor(2);
  peR->DrawCopy("same");
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  c2->cd(2);
  asPE->SetTitle("(P+_{i}/tr_{i} - P-_{i}/tr_{i}) /(P+_{i}/tr_{i} + P-_{i}/tr_{i})");
  asPE->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);

  c2->cd(3);
  d4->DrawCopy();
  gPad->SetGridx(1);
  gPad->SetGridy(1);


  int binMax=d4->GetXaxis()->FindBin(xMax)-1;
  int binZero=d4->GetXaxis()->FindBin(0);
  //d5 produces 0; d4 seems ok
  integ = d4->Integral(binZero,binMax)/(peTrksFold->Integral(binZero,binMax));
  
  //integ = asPEfold->Integral();
  TH1D *asl=(TH1D*)fin->Get("asL_6");
  TH1D *asr=(TH1D*)fin->Get("asR_6");
  double al=asl->GetMean();
  double ar=asr->GetMean();
  double factor = 295./(ar-al);
  abias = (al+ar)/2*factor;
  
  fin->Close();
}

TH1D *fold(TH1D *h, float flip){
  string flipnm="m";
  if(flip>0) flipnm="p";
  
  TH1D *fold=(TH1D*)h->Clone(Form("%s_fold_%s",h->GetName(),flipnm.c_str()));
  int nb=h->GetXaxis()->GetNbins();
  if(nb%2!=0) {
    cout<<"Nbins "<<nb<<" this may not work"<<endl;
    std::cin.ignore();
  }

  for(int i=1;i<=nb/2;i++){
    //cout<<"\t"<<h->GetBinCenter(i)<<" <> "<<h->GetBinCenter(nb-i+1)<<endl;    
    // std::cin.ignore();
    double vl = h->GetBinContent(i);
    double vr = h->GetBinContent(nb-i+1);

    fold->SetBinContent(i,0);
    fold->SetBinContent(nb-i+1, vr + flip* vl);
    //cout<<i<<" "<<nb-i-1<<" "<<endl;
  }
  return fold;
}
