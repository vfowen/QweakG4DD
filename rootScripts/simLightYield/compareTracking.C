void compareTracking(){
  const int nfl=8;
  int mdV[nfl]={1,2,3,4,5,6,7,8};
  int nhist[nfl]={2,2,1,1,1,1,2,2};
  string tRNs[nfl]={
    "Run13681",//md1
    "Run13671",//md2
    //"Run8662",//md2
    "Run13676",//md3
    "Run13674",//md4
    "Run13681",//md5
    "Run13671",//md6
    "Run13676",//md7
    "Run13674"//md8
  };

  string sfns[nfl]={
    "md1Config5_model2.root",
    "md2Config11_model2.root",
    "md3Config4.root",
    "md4Config4.root",
    "md5Config4.root",
    "md6Config3.root",
    "md7Config2.root",
    "md8configMG.root"
  };
  TCanvas *c1[nfl];
  gStyle->SetOptStat(0);
  for(int i=0;i<nfl;i++){
    //for(int i=0;i<1;i++){
    c1[i]=new TCanvas(Form("c%d",i),Form("c%d",i),1200,600);
    c1[i]->Divide(2);

    c1[i]->cd(2);
    TFile *tpf=TFile::Open(Form("../trackingData/PE%dp_y_%s.root",mdV[i],tRNs[i].c_str()),"READ");
    TProfile *tpr=(TProfile*)tpf->Get(Form("light_vs_y%dp",nhist[i]));

    TFile *smf=TFile::Open(sfns[i].c_str(),"READ");
    string profNm="LeftPMT";
    if(i==7) profNm="RightPMT";
    TProfile *spr=(TProfile*)smf->Get(profNm.c_str());

    double slp(0),integral(0);
    doOne(tpr,spr,integral,slp,1);
    cout<<i<<"\t+\t"<<slp<<"\t"<<integral;
    tpf->Close();

    c1[i]->cd(1);
    TFile *tmf=TFile::Open(Form("../trackingData/PE%dm_y_%s.root",mdV[i],tRNs[i].c_str()),"READ");
    TProfile *tmr=(TProfile*)tmf->Get(Form("light_vs_y%dm",nhist[i]));
    profNm="RightPMT";
    if(i==7) profNm="LeftPMT";    
    TProfile *smr=(TProfile*)smf->Get(profNm.c_str());    
    
    doOne(tmr,smr,integral,slp,0);
    cout<<"\t-\t"<<slp<<"\t"<<integral<<endl;
    tmf->Close();

    smf->Close();
  }
  
}

void doOne(TProfile *trk, TProfile *sim, double &integ, double &slopeDiff, int lr){

  int tl=trk->GetXaxis()->FindBin(-99);
  int th=trk->GetXaxis()->FindBin( 99);
  double intT=trk->Integral(tl,th);
  trk->Scale(1/intT);

  int sl=sim->GetXaxis()->FindBin(-99);
  int sh=sim->GetXaxis()->FindBin( 99);
  double intS=sim->Integral(sl,sh);
  sim->Scale(1/intS);
  
  float lv[2]={-90,5};
  float hv[2]={-5,90};

  int tbl = trk->GetXaxis()->FindBin(lv[lr]);
  int tbh = trk->GetXaxis()->FindBin(hv[lr]);
  int sbl = sim->GetXaxis()->FindBin(lv[lr]);
  int sbh = sim->GetXaxis()->FindBin(hv[lr]);

  integ = ( trk->Integral(tbl,tbh,"width") - sim->Integral(sbl,sbh,"width") )
    /sim->Integral(sbl,sbh,"width") *100;

  TF1 *tf1=new TF1("tf1","pol1");
  tf1->SetLineColor(2);
  
  TF1 *sf1=new TF1("sf1","pol1");
  sf1->SetLineColor(4);

  // trk->Fit("tf1","Q","",lv[lr],hv[lr]);
  // sim->Fit("sf1","Q","",lv[lr],hv[lr]);
  slopeDiff = (tf1->GetParameter(1) - sf1->GetParameter(1))/sf1->GetParameter(1) *100;
  trk->SetLineColor(2);
  trk->GetXaxis()->SetRangeUser(-95,95);
  trk->DrawCopy("");
  sim->SetLineColor(4);
  sim->DrawCopy("same");
  // sf1->Draw("same");
  // tf1->Draw("same");  
}
