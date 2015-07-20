TCanvas *c1=new TCanvas("c1","c1",600,600);
string onm;

void calcDDmeanForDist(){
  onm="y_DDasym_depol.pdf";
  gStyle->SetOptStat(1211);

  c1->Print(Form("%s[",onm.c_str()),"pdf");

  doOneConfig("../output/depol/o_dist_asym_depol_L_299.root" ,"L");
  doOneConfig("../output/depol/o_dist_asym_depol_V_699.root" ,"V");
  doOneConfig("../output/depol/o_dist_asym_depol_mV_299.root","mV");
  doOneConfig("../output/depol/o_dist_asym_depol_mL_299.root","mL");
  
  c1->Print(Form("%s]",onm.c_str()),"pdf");
}

void doOneConfig(string fnm, string sufix){
  TFile *fin=TFile::Open(fnm.c_str(),"READ");

  string energyCut[3]={"0MeV","1MeV","2MeV"};
  string cases[4]={"posPe","posAe","angPe","angAe"};

  TH1D *ave=(TH1D*)fin->Get("averages");
  
  for(int i=0;i<3;i++)
    for(int j=0;j<4;j++){      
      TH1D *h=(TH1D*)fin->Get(Form("ddAsX%s_%d",cases[j].c_str(),i));
      TH1D *d=(TH1D*)fin->Get(Form("distX%s_%d",cases[j].c_str(),i));
      if(!h) {
	cout<<"cannot find histo "<<Form("ddAsX%s_%d",cases[j],i)<<endl;
	exit(2);
      }
      h->SetTitle(Form("%s %s",h->GetTitle(),sufix.c_str()));
      calcMean(h,d);
      TH1D *m=(TH1D*)fin->Get(Form("asymX%s_%d",cases[j].c_str(),i));
      m->SetTitle(Form("%s %s",m->GetTitle(),sufix.c_str()));
      plotMarkDAsym(m,ave->GetBinContent(j*3+i+1),ave->GetBinContent(12+j*3+i+1),j);		    
  }
  
  fin->Close();
}

void calcMean(TH1D *a, TH1D *d){

  int maxBin=-1;
  for(int i=1;i<=a->GetXaxis()->GetNbins() && maxBin==-1;i++)
    if(a->GetBinError(i)==0) maxBin=i-1;
  //cout<<maxBin<<" "<<endl;

  int b1=d->GetXaxis()->FindBin(-a->GetBinCenter(maxBin));
  int b2=d->GetXaxis()->FindBin( a->GetBinCenter(maxBin));
  double ntot=d->Integral(b1,b2);
  
  double x(0),y(0),dy(0),w(0);
  double sumV=0;
  double sumW=0;
  double sumD=0;
  double sumN=0;
    
  for(int i=1;i<=maxBin;i++){
    x=a->GetBinCenter(i);
    y=a->GetBinContent(i);
    dy=a->GetBinError(i);

    w=d->GetBinContent(d->GetXaxis()->FindBin(x)) + d->GetBinContent(d->GetXaxis()->FindBin(-x)); 

    if(y!=y || dy!=dy) continue;
    
    sumN+=w;
    w/=ntot;
    sumW+=w;
    sumV+=y[i]*w;
    sumD+=pow(w*dy,2);
  }

  m=sumV;
  dm=sqrt(sumD);

  c1->cd(0);
  a->GetXaxis()->SetRangeUser(0,a->GetBinCenter(maxBin+1));
  a->DrawCopy();
  TLegend *leg=new TLegend(0.15,0.8,0.75,0.95);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->AddEntry(a,Form("mean:  %4.0f #pm %4.0f ppm",sumV*1e6,sqrt(sumD)*1e6,"lep"));
  leg->Draw();
  c1->Print(onm.c_str(),"pdf");
  
}

void plotMarkDAsym(TH1D *a, double mean, double dmean, int log){

  int maxBin=-1;
  for(int i=1;i<=a->GetXaxis()->GetNbins() && maxBin==-1;i++)
    if(a->GetBinError(i)==0) maxBin=i-1;

  c1->cd(0);
  a->GetXaxis()->SetRangeUser(0,a->GetBinCenter(maxBin+1));
  a->DrawCopy();
  if(log==0 || log==1) gPad->SetLogy(1);
  double entries=a->GetEntries();
  TLegend *leg=new TLegend(0.15,0.8,0.75,0.95);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->AddEntry(a,Form("mean:  %4.0f ppm",mean*1e6,"lep"));
  //leg->Draw();
  c1->Print(onm.c_str(),"pdf");
  
  if(log==0 || log==1) gPad->SetLogy(0);
}
