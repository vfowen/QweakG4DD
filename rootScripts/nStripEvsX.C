TCanvas *c1=new TCanvas("c1","c1",1200,800);
string onm;

void nStripEvsX(){
  onm="y_eVSx.pdf";

  double lpe[10][25],rpe[10][25];
  double dlpe[10][25],drpe[10][25];

  c1->cd(0);
  c1->Divide(2);
  c1->Print(Form("%s[",onm.c_str()),"pdf");

  TH2F *h2l=new TH2F("h2l","Left number of PEs;x position[cm];E [MeV]" ,21,-0.105,0.105,10,2.5,52.5);
  TH2F *h2r=new TH2F("h2r","Right number of PEs;x position[cm];E [MeV]",21,-0.105,0.105,10,2.5,52.5);

  double eVal[10]={5,10,15,20,25,30,35,40,45,50};
  double xVal[25]={-20,-15,-10,-5,-3,-1,-0.1,-0.05,-0.04,-0.03,-0.02,-0.01,0,0.01,0.02,0.03,0.04,0.05,0.1,1,3,5,10,15,20};

  for(int i=0;i<10;i++)
    for(int j=0;j<25;j++){
      doAna(eVal[i],xVal[j],lpe[i][j],rpe[i][j],dlpe[i][j],drpe[i][j]);
      h2l->Fill(xVal[j],eVal[i],lpe[i][j]);
      h2r->Fill(xVal[j],eVal[i],rpe[i][j]);
    }

  c1->cd(1);
  h2l->Draw("colz");
  c1->cd(2);
  h2r->Draw("colz");  
  c1->Print(onm.c_str(),"pdf");

  double lp1[25],dlp1[25];
  double rp1[25],drp1[25];
  double lp0[25],dlp0[25];
  double rp0[25],drp0[25];
  double dx[25]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  double _xval[25];

  for(int i=0;i<10;i++){
    double ly[25],ldy[25],ry[25],rdy[25];
    int npts=0;
    for(int j=0;j<25;j++){      
      ly[npts] = lpe[i][j];
      ldy[npts]=dlpe[i][j];
      ry[npts] = rpe[i][j];
      rdy[npts]=drpe[i][j];
      _xval[npts]=xVal[j];
      if(lpe[i][j]!=-999) npts++;
    }

    TF1 *p1=new TF1("p1","pol1");    
    c1->cd(1);
    TGraphErrors *gl=new TGraphErrors(npts,_xval,ly,dx,ldy);
    gl->SetMarkerStyle(20);
    gl->SetTitle(Form("E %f",eVal[i]));
    gl->GetXaxis()->SetTitle("x position [cm]");
    gl->GetYaxis()->SetTitle("left number of PEs");
    gl->Fit("p1","Q","",-5,5);
    gl->Draw("AP");
    lp1[i]=p1->GetParameter(1);
    dlp1[i]=p1->GetParError(1);
    lp0[i]=p1->GetParameter(0);
    dlp0[i]=p1->GetParError(0);
    c1->cd(2);
    TGraphErrors *gr=new TGraphErrors(npts,_xval,ry,dx,rdy);
    gr->SetMarkerStyle(20);
    gr->GetXaxis()->SetTitle("x position [cm]");
    gr->GetYaxis()->SetTitle("right number of PEs");
    gr->Fit("p1","Q","",-5,5);
    gr->Draw("AP");
    rp1[i]=fabs(p1->GetParameter(1));
    drp1[i]=p1->GetParError(1);
    rp0[i]=p1->GetParameter(0);
    drp0[i]=p1->GetParError(0);
    c1->Print(onm.c_str(),"pdf");
  }

  c1->cd(1);
  TGraphErrors *glp=new TGraphErrors(10,eVal,lp1,dx,dlp1);
  glp->SetMarkerStyle(20);
  glp->GetXaxis()->SetTitle("e [MeV]");
  glp->GetYaxis()->SetTitle("p1 left");
  glp->Fit("p1","Q");
  glp->Draw("AP");

  c1->cd(2);
  TGraphErrors *grp=new TGraphErrors(10,eVal,rp1,dx,drp1);
  grp->SetMarkerStyle(20);
  grp->GetXaxis()->SetTitle("e [MeV]");
  grp->GetYaxis()->SetTitle("p1 right");
  grp->Fit("p1","Q");
  grp->Draw("AP");
  c1->Print(onm.c_str(),"pdf");

  c1->cd(1);
  TGraphErrors *gl0p=new TGraphErrors(10,eVal,lp0,dx,dlp0);
  gl0p->SetMarkerStyle(20);
  gl0p->GetXaxis()->SetTitle("e [MeV]");
  gl0p->GetYaxis()->SetTitle("p0 left");
  //gl0p->Fit("p1","Q");
  gl0p->Draw("AP");

  c1->cd(2);
  TGraphErrors *gr0p=new TGraphErrors(10,eVal,rp0,dx,drp0);
  gr0p->SetMarkerStyle(20);
  gr0p->GetXaxis()->SetTitle("e [MeV]");
  gr0p->GetYaxis()->SetTitle("p0 right");
  //gr0p->Fit("p1","Q");
  gr0p->Draw("AP");
  c1->Print(onm.c_str(),"pdf");

  double _rat[10],_drat[10];
  for(int i=0;i<10;i++){
    // _rat[i] =(lp0[i]/pow(dlp0[i],2)+rp0[i]/pow(drp0[i],2))/(1./pow(dlp0[i],2)+1./pow(drp0[i],2));
    // _drat[i]=sqrt((1.)/(1./pow(dlp0[i],2)+1./pow(drp0[i],2)));
    _rat[i] =(lp0[i]/rp0[i]);
    _drat[i]=sqrt(pow(dlp0[i]/lp0[i],2)+pow(drp0[i]/rp0[i],2));
  }
  c1->cd(0);
  c1->Clear();
  TGraphErrors *rat=new TGraphErrors(10,eVal,_rat,dx,_drat);
  rat->SetMarkerStyle(20);
  rat->GetXaxis()->SetTitle("e [MeV]");
  rat->GetYaxis()->SetTitle("p0 ratio (l/r)");
  rat->Fit("pol0","Q");
  rat->Draw("AP");
  c1->Print(onm.c_str(),"pdf");
  
  c1->Print(Form("%s]",onm.c_str()),"pdf");

}

void doAna(double _e, double _x,double &l, double &r,double &dl, double &dr){

  gSystem->Exec(Form("ls /Users/ciprian/qweak/QweakG4DD/output/farm/eVSx/V_%04d_%06.2f_*/o_anaTree.root > z_tst.in",(int)_e,_x));
  ifstream fin("z_tst.in");
  string data;

  double al[100],adl[100];
  double ar[100],adr[100];
  double x[100],dx[100];
  int n=0;  
  while(fin>>data){  
    cout<<data.c_str()<<" E "<<_e<<" X "<<_x;
    doAna1(data,n,al[n],ar[n],adl[n],adr[n]);
    cout<<" "<<n<<" "<<al[n]<<" "<<ar[n]<<endl;
    x[n]=n;
    dx[n]=0;
    if(al[n]<100 && al[n]>1 && ar[n]<100 && ar[n]>1) n++;
  }
  fin.close();
  if(n==0) {
    l=-999;
    cout<<" no files for "<<_e<<" "<<_x<<endl;
    gSystem->Exec("rm -rf z_tst.in");
    return;
  }
  TF1 *fp0=new TF1("fp0","pol0");
  
  c1->cd(1);
  TGraphErrors *gl=new TGraphErrors(n,x,al,dx,adl);
  gl->SetMarkerStyle(20);
  gl->SetTitle(Form("E %d x %f",(int)_e,_x));
  gl->GetXaxis()->SetTitle("sim number");
  gl->GetYaxis()->SetTitle("left PMT nr PEs");
  gl->Fit("fp0","Q");
  gl->Draw("AP");
  l=fp0->GetParameter(0);
  dl=fp0->GetParError(0);

  c1->cd(2);
  gr=new TGraphErrors(n,x,ar,dx,adr);
  gr->SetMarkerStyle(20);
  gr->GetXaxis()->SetTitle("sim number");
  gr->GetYaxis()->SetTitle("right PMT nr PEs");
  gr->Fit("fp0","Q");
  gr->Draw("AP");
  r=fp0->GetParameter(0);
  dr=fp0->GetParError(0);
  c1->Print(onm.c_str(),"pdf");
  
  gSystem->Exec("rm -rf z_tst.in");
  
}

void doAna1(string fnm,int n,double &l, double &r,double &dl, double &dr){

  TString pre(fnm.c_str());
  pre.Remove(0,pre.First('0'));
  pre.Remove(pre.First('.')+3,pre.Length());
  TFile *rf=TFile::Open(fnm.c_str(),"READ");
  TTree *t=(TTree*)rf->Get("te");

  TH1F *hl=new TH1F(Form("hl%d",n),Form("left NPE %s",pre.Data())  ,101,-0.5,100.5);
  TH1F *hr=new TH1F(Form("hr%d",n),Form("right NPE %s",pre.Data()),101,-0.5,100.5);

  t->Project(Form("hl%d",n),"LnPMThit");
  t->Project(Form("hr%d",n),"RnPMThit");

  hl->Sumw2();
  hr->Sumw2();
  hl->SetMarkerStyle(20);
  hr->SetMarkerStyle(20);
  
  TF1 *gs=new TF1("gs","gaus(0)");
  gStyle->SetOptFit(1);

  c1->cd(1);  
  gs->SetParameters(hl->GetMaximum(),hl->GetMean(),hl->GetRMS());
  hl->Fit("gs","Q","",hl->GetMean()-2*hl->GetRMS(),hl->GetMean()+2*hl->GetRMS());
  hl->DrawCopy();
  l=gs->GetParameter(1);
  dl=gs->GetParError(1);

  c1->cd(2);
  gs->SetParameters(hr->GetMaximum(),hr->GetMean(),hr->GetRMS());
  hr->Fit("gs","Q","",hr->GetMean()-2*hr->GetRMS(),hr->GetMean()+2*hr->GetRMS());
  hr->DrawCopy();
  r=gs->GetParameter(1);
  dr=gs->GetParError(1);

  c1->Print(onm.c_str(),"pdf");

  rf->Close();
}
