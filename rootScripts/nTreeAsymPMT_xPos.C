TCanvas *c1=new TCanvas("c1","c1",1600,1200);
string onm;

void nTreeAsymPMT_xPos(){
  onm="y_MD_asymPMT_xVar_V.pdf";
  gSystem->Exec("ls /Users/ciprian/qweak/QweakG4DD/output/farm/diffPos/V_1160_*/o_anaTree.root > z_list.in");
  // onm="y_MD_asymPMT_xVar_L.pdf";
  // gSystem->Exec("ls /Users/ciprian/qweak/QweakG4DD/output/farm/diffPos/L_1160_*/o_anaTree.root > z_list.in");
  asymPMT("z_list.in");
  gSystem->Exec("rm -rf z_list.in");
}
void asymPMT(string flist){
  c1->Clear();
  ifstream fin(flist.c_str());
  string data;
  //string gnm[8]={"L x=-5 cm","L x=-3 cm","L x=-2 cm","L x=-1 cm","L x=1 cm","L x=2 cm","L x=3 cm","L x=5 cm"};
  string gnm[8]={"V x=-5 cm","V x=-3 cm","V x=-2 cm","V x=-1 cm","V x=1 cm","V x=2 cm","V x=3 cm","V x=5 cm"};
  double val[500][16];
  double x[500][8],dx[500];
  int ng=8;
  int iter[8]={-5,-3,-2,-1,1,2,3,5};
  
  TGraphErrors *mean[12];
  gStyle->SetOptFit(1);
  c1->cd(0);
  c1->Divide(3);
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  int n[8]={0,0,0,0,0,0,0,0};
  double min[16]={100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
  double max[16]={-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100};
  while(fin>>data){
    TString fl(data.c_str());
    fl.Remove(fl.Last('/')+1,fl.Length());
    fl+="o_anaTree.root";
    TString _xp(data.c_str());
    _xp.Remove(0,_xp.First('1'));
    _xp.Remove(0,_xp.First('_')+1);
    _xp.Remove(_xp.First('_'),_xp.Length());
    float xpos=_xp.Atof();
    cout<<data<<" > "<<_xp<<" is "<<xpos<<endl;
    if(fabs(xpos)>6) continue;
    int l=-1;
    for(int j=0;j<ng;j++)
      if(fabs((float)iter[j]-xpos)<0.1) l=j;
    if(l==-1) {cout<<"problem: "<<l<<endl; exit(1);}
    cout<<l<<" "<<n[l]<<endl;
    doAna(fl.Data(),val[n[l]][l],val[n[l]][l+8]);
    if(bad(val,n[l],l) && bad(val,n[l],l+8)) continue;
    if(val[n[l]][l]<min[l]) min[l]=val[n[l]][l];
    if(val[n[l]][l]>max[l]) max[l]=val[n[l]][l];
    
    x[n[l]][l]=n[l];
    dx[n[l]]=0;
    n[l]++;
  }

  double _mn[8],_dmn[8];
  double _xpos[8]={-5,-3,-2,-1,1,2,3,5};
  TF1 *fp=new TF1("fp","pol0");
  c1->cd(0);
  c1->Clear();
  c1->Divide(4,2);  
  for(int i=0;i<ng;i++){
    c1->cd(i+1);
    gPad->SetLogy(0);
    double dm[500],ddm[500],dmx[500];
    for(int j=0;j<n[i];j++) {
      dm[j]=val[j][i];
      dmx[j]=x[j][i];
      ddm[j]=val[j][i+8];
    }
    
    mean[i]=new TGraphErrors(n[i],dmx,dm,dx,ddm);
    mean[i]->GetXaxis()->SetTitle("simulation file number");
    mean[i]->SetTitle(gnm[i].c_str());
    mean[i]->Fit("fp");
    mean[i]->SetMarkerStyle(20);
    mean[i]->SetMarkerColor(4);
    mean[i]->GetYaxis()->SetRangeUser(min[i]-0.01,max[i]+0.01);
    mean[i]->Draw("AP");
    _mn[i]=fp->GetParameter(0);
    _dmn[i]=fp->GetParError(0);
  }
  c1->Print(onm.c_str(),"pdf");

  c1->cd(0);
  c1->Clear();
  TGraphErrors *asym=new TGraphErrors(8,_xpos,_mn,dx,_dmn);
  asym->GetXaxis()->SetTitle("Beam start x position [cm]");
  asym->GetYaxis()->SetTitle("Mean PMT asym");
  asym->SetMarkerStyle(20);
  asym->SetMarkerColor(4);
  asym->Fit("pol1");
  asym->Draw("AP");
  gPad->Update();
  TPaveStats *ps = (TPaveStats *)asym->GetListOfFunctions()->FindObject("stats");
  ps->SetX1NDC(0.35);
  ps->SetX2NDC(0.75);
  gPad->SetGridy(1);
  gPad->SetGridx(1);
  gPad->Modified();
  gPad->Update();
  c1->Print(onm.c_str(),"pdf");
  
  c1->Print(Form("%s]",onm.c_str()),"pdf");
}


double doAna(char *fn, double &a, double &da)
{
  double pi=3.14159265;
  TString nb(fn);
  nb.Remove(nb.Last('/'),nb.Length());
  nb.Remove(0,nb.Last('_')+1);
  int n=nb.Atoi();
  
  TFile *fin=TFile::Open(fn,"READ");
  TTree *t=(TTree*)fin->Get("te");

  TH1F *ha=new TH1F(Form("ha%d",n),Form("PMT asym %d",n) ,101,-1.01,1.01);
  TH1F *hl=new TH1F(Form("hl%d",n),Form("L PMT hit %d",n) ,300,-0.5,299.5);
  TH1F *hr=new TH1F(Form("hr%d",n),Form("R PMT hit %d",n) ,300,-0.5,299.5);
  
  
  t->Project(Form("ha%d",n),"(LnPMThit-RnPMThit)/(LnPMThit+RnPMThit)","LnPMThit>0 && RnPMThit>0");
  t->Project(Form("hl%d",n),"LnPMThit","LnPMThit>0 && RnPMThit>0");
  t->Project(Form("hr%d",n),"RnPMThit","LnPMThit>0 && RnPMThit>0");

  TF1 *gs=new TF1("gs","gaus(0)");
  c1->cd(1);
  hl->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(2);
  hr->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(3);
  gs->SetParameters(ha->GetMaximum(),ha->GetMean(),ha->GetRMS());
  ha->Fit("gs","Q");
  ha->DrawCopy();
  c1->Print(onm.c_str(),"pdf");

  a =gs->GetParameter(1);
  da=gs->GetParError(1);
  fin->Close();
}


int bad(double a[500][16],int n,int m){
  for(int i=0;i<n;i++)
    if(fabs(a[n][m]-a[i][m])<0.0001) return 1;
  return 0;
}
