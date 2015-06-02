TCanvas *c1=new TCanvas("c1","c1",1400,500);
string onm;

void plotDistr(){
  TFile *fin=TFile::Open("o_distributions_1Ecut_treeTest.root","READ");
  onm="y_distrAna_LV_1Ecut.pdf";

  c1->Print(Form("%s[",onm.c_str()),"pdf");
  TH1F *hL1=(TH1F*)fin->Get("hX_L_0");
  TH1F *hV1=(TH1F*)fin->Get("hX_V_0");
  mkPlots(hV1,hL1,"xPos Primary: Red V, Blue L",0); 
  mkDistrAsym(hV1,hL1,"xPos Primary: Red V, Blue L",0);
  
  TH1F *hL2=(TH1F*)fin->Get("hX_L_3");
  TH1F *hV2=(TH1F*)fin->Get("hX_V_3");
  mkPlots(hV2,hL2,"xPos All e: Red V, Blue L",1);
  mkDistrAsym(hV2,hL2,"xPos All e: Red V, Blue L",1);

  TH1F *hL3=(TH1F*)fin->Get("hX_L_4");
  TH1F *hV3=(TH1F*)fin->Get("hX_V_4");
  mkPlots(hV3,hL3,"xPos Photons: Red V, Blue L",2);
  mkDistrAsym(hV3,hL3,"xPos Photons: Red V, Blue L",2);


  TH1F *hL4=(TH1F*)fin->Get("hangX_L_0");
  TH1F *hV4=(TH1F*)fin->Get("hangX_V_0");
  mkPlots(hV4,hL4,"xAng Primary: Red V, Blue L",3);
  mkDistrAsym(hV4,hL4,"xAng Primary: Red V, Blue L",3);

  TH1F *hL5=(TH1F*)fin->Get("hangX_L_3");
  TH1F *hV5=(TH1F*)fin->Get("hangX_V_3");
  mkPlots(hV5,hL5,"xAng All e#pm: Red V, Blue L",4);
  mkDistrAsym(hV5,hL5,"xAng All e#pm: Red V, Blue L",4);

  TH1F *hL6=(TH1F*)fin->Get("hangX_L_4");
  TH1F *hV6=(TH1F*)fin->Get("hangX_V_4");
  mkPlots(hV6,hL6,"xAng Photons: Red V, Blue L",5);
  mkDistrAsym(hV6,hL6,"xAng Photons: Red V, Blue L",5);

  c1->Print(Form("%s]",onm.c_str()),"pdf");
  fin->Close();
}

void mkDistrAsym(TH1F *a, TH1F *b,string tit, int n){
  int nb=a->GetXaxis()->GetNbins();
  float b1=a->GetBinCenter(1)-a->GetBinWidth(1)/2;
  float b2=a->GetBinCenter(nb)+a->GetBinWidth(nb)/2;

  double yl[6]={0.2,0.05,0.02,0.1,0.01,0.01};

  c1->cd(0);
  c1->Clear();
  c1->Divide(3);
  c1->cd(1);
  a->SetLineColor(2);
  a->SetTitle(tit.c_str());
  a->DrawCopy("hist");
  b->DrawCopy("same&&hist");
  if(n<3)
    gPad->SetLogy(1);

  c1->cd(2);
  TH1F *A=new TH1F(Form("A%d",n),"L-R/L+R (Vertical)",nb/2,0,b2);
  calcAsym(a,A);
  A->SetMarkerStyle(22);
  A->SetMarkerColor(2);
  if(n<3) A->GetXaxis()->SetRangeUser(0,40);   
  A->GetYaxis()->SetRangeUser(-yl[n],yl[n]);  
  A->DrawCopy();
  gPad->SetGridy(1);

  c1->cd(3);
  TH1F *B=new TH1F(Form("B%d",n),"L-R/L+R (Longitudinal)",nb/2,0,b2);
  calcAsym(b,B);
  B->SetMarkerStyle(22);
  B->SetMarkerColor(4);
  if(n<3) B->GetXaxis()->SetRangeUser(0,40);
  B->GetYaxis()->SetRangeUser(-yl[n],yl[n]);
  B->Fit("pol0");
  B->DrawCopy();
  gPad->SetGridy(1);

  c1->Print(onm.c_str(),"pdf");  
}

void mkPlots(TH1F *a, TH1F *b,string tit, int n){
  int nb=a->GetXaxis()->GetNbins();
  float b1=a->GetBinCenter(1)-a->GetBinWidth(1)/2;
  float b2=a->GetBinCenter(nb)+a->GetBinWidth(nb)/2;

  c1->cd(0);
  c1->Clear();
  c1->Divide(3);
  c1->cd(1);

  a->SetLineColor(2);
  a->SetTitle(tit.c_str());
  a->DrawCopy();
  b->DrawCopy("same");
  if(n<3)
    gPad->SetLogy(1);

  c1->cd(2);
  TH1F *d=new TH1F(Form("d_%d",n),"Ratio V/L",nb,b1,b2);
  a->Sumw2();
  b->Sumw2();
  d->Divide(a,b);
  d->Rebin(4);
  d->GetXaxis()->SetRangeUser(-70,70);
  d->GetYaxis()->SetRangeUser(2,6);
  d->DrawCopy();  
  gPad->SetGridy(1);  

  c1->cd(3);
  gStyle->SetOptFit(1);
  TH1F *has=new TH1F(Form("has_%d",n),"Asym L-V/L+V",nb,b1,b2);
  int skip=3;
  for(int i=2;i<=nb;i+=skip){
    float _a=0;
    float _b=0;
    for(int j=-1;j<skip-1;j++){
      _a+=a->GetBinContent(i+j);
      _b+=b->GetBinContent(i+j);
    }
    if(_a+_b==0) continue;
    float as=(_a-_b)/(_a+_b);
    float das=2/pow(_a+_b,2)*sqrt(pow(_b,2)*_a+pow(_a,2)*_b);
    has->SetBinContent(i,as);
    has->SetBinError(i,das);
  }
  has->GetXaxis()->SetRangeUser(-70,70);
  has->GetYaxis()->SetRangeUser(-0.5,0.5);
  has->Fit("pol1","Q","",-30,30);
  has->DrawCopy();
  gPad->SetGridy(1);

  c1->Print(onm.c_str(),"pdf");
}

void calcAsym(TH1F *a, TH1F *A){
  int nb=a->GetXaxis()->GetNbins();
  for(int i=0;i<nb/2;i++){
    double mx=a->GetBinCenter(i+1);
    int bp=a->GetXaxis()->FindBin(fabs(mx));
    double vm=a->GetBinContent(i+1);
    double vp=a->GetBinContent(bp);
    double as,das;
    if(vp+vm==0){
      as=0;
      das=0;
    }else{
      as=(vp-vm)/(vp+vm);
      das=2./pow(vp+vm,2)*sqrt(vp*vm*vm + vp*vp*vm);
    }
    int bA=A->GetXaxis()->FindBin(fabs(mx));
    A->SetBinContent(bA,as);
    A->SetBinError(bA,das);
  }
}
