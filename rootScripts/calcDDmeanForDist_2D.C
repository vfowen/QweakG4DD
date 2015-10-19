TCanvas *c1=new TCanvas("c1","c1",1400,600);
string onm;

TGraphErrors *posAsym;
TGraph       *angAsym;

void calcDDmeanForDist_2D(){
  onm="../output/models/y_DD2D_2photon.pdf";
  gStyle->SetOptStat(1211);

  TFile *fpos=TFile::Open("o_PEasyms.root","READ");
  posAsym=(TGraphErrors*)fpos->Get("asym_9");
  angAsym=(TGraph*)      fpos->Get("angle");

  c1->Print(Form("%s[",onm.c_str()),"pdf");

  doOneConfig("../output/models/o_dist_asym_depol_V_2phX1e2_1M.root","2phot_1e2x_1e6_V");
  doOneConfig("../output/models/o_dist_asym_depol_V_2phX1e4_1M.root","2phot_1e4x_1e6_V");
  
  c1->Print(Form("%s]",onm.c_str()),"pdf");
  fpos->Close();
  //fang->Close();
}

void doOneConfig(string fnm, string sufix){
  TFile *fin=TFile::Open(fnm.c_str(),"READ");

  string energyCut[3]={"0MeV","1MeV","2MeV"};
  string cases[2]={"Pe","Ae"};

  for(int i=1;i<3;i++)
    for(int j=0;j<2;j++){      
      TH2D *h=(TH2D*)fin->Get(Form("dist%s_%d",cases[j].c_str(),i));

      if(!h) {
	cout<<"cannot find histo "<<Form("dist%s_%d",cases[j],i)<<endl;
	exit(2);
      }

      h->SetTitle(Form("%s %s",h->GetTitle(),sufix.c_str()));
      calcMean(h);
  }
  
  fin->Close();
}

void calcMean(TH2D *a){

  int binx=a->GetXaxis()->GetNbins();
  int biny=a->GetYaxis()->GetNbins();

  TH1D *dd=new TH1D(Form("dd_%s",a->GetName()),Form("DD %s",a->GetTitle()),201,-1.2,1.2);

  double mn(0),dmn(0),n(0);

  int ss=0;
  
  for(int i=1;i<=binx;i++)
    for(int j=1;j<=biny;j++){
      double nentries=a->GetBinContent(i,j);
      double xpos=a->GetXaxis()->GetBinCenter(i);
      double xang=a->GetYaxis()->GetBinCenter(j);

      if(fabs(xpos)>=20 || fabs(xang)>=20) continue;

      if(fabs(xpos)<=0 || fabs(xang)<=0) continue;
      
      if(nentries>0){      
	double asym=getAsym(xpos,xang);
	//dd->Fill(asym,nentries);
	for(int kk=0;kk<nentries;kk++) dd->Fill(asym);
	//cout<<ss<<" "<<n<<" "<<mn<<" "<<xpos<<" "<<xang<<" "<<asym<<endl;
	mn=(n*mn+nentries*asym)/(nentries+n);
	//cout<<" "<<nentries<<" "<<mn<<endl;
	ss++;
	n+=nentries;
      }
    }
  
  c1->Clear();
  c1->cd(0);
  c1->Divide(2);
  c1->cd(1);  
  a->GetXaxis()->SetRangeUser(-20,20);
  a->GetYaxis()->SetRangeUser(-35,35);
  a->SetStats(0);
  a->DrawCopy("colz");
  gPad->SetLogz(1);
  gPad->SetGridx(1);
  gPad->SetGridy(1);
  c1->cd(2);
  dd->SetTitle(Form("%s Mean:%.2e",dd->GetTitle(),mn));
  dd->DrawCopy();
  gPad->SetLogy(1);

  c1->Print(onm.c_str(),"pdf");
  
}

double getAsym(double pos,double ang){
  //double posA=(posAsym->Eval(pos,0,"S") - posAsym->Eval(-pos,0,"S"))/2;
  //double angA=(angAsym->Eval(ang,0,"S") - angAsym->Eval(-ang,0,"S"))/2;
  
  double posA=0.006351*pos;
  double angA(0);
  if(fabs(ang)<10)
    angA=ang*0.065;
  else if(fabs(ang)<20)
    angA=ang*0.016+0.49*ang/fabs(ang);
  else
    angA=0.81;
  //cout<<pos<<" ==> "<<posA<<" ~~~ "<<ang<<" ==> "<<angA<<endl;
  return posA+angA;
}
