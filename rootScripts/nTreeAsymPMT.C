TCanvas *c1=new TCanvas("c1","c1",800,600);
string onm;

void nTreeAsymPMT(){
  //string flist="../output/farm/fName_mV_0.in";
  //onm="y_PMTasym_mV.pdf";
  //string flist="../output/farm/fName_mL_0.in";
  //onm="y_PMTasym_mL.pdf";
  //string flist="../output/farm/fName_L_0.in";
  //onm="y_PMTasym_L.pdf";
  string flist="../output/farm/fName_V_0.in";
  onm="y_PMTasym_V.pdf";

  ifstream fin(flist.c_str());
  string data;
  double val[500];
  double dv[500];
  double x[500];
  double dx[500];
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  int n=0;
  double min=100;
  double max=-100;
  c1->cd(0);
  c1->Divide(3);
  while(fin>>data){
    cout<<data.c_str()<<endl;
    nTupleAna(data,n,val[n],dv[n]);
    if(val[n]<min) min=val[n];
    if(val[n]>max) max=val[n];
    x[n]=n;
    dx[n]=0;
    if(bad(n,val)) continue;
    n++;
  }
  TGraphErrors *xMean=new TGraphErrors(n,x,val,dx,dv);
  xMean->GetXaxis()->SetTitle("simulation file number");
  xMean->GetYaxis()->SetTitle("PMT asymmetry");
  xMean->Fit("pol0");
  xMean->SetMarkerStyle(20);
  xMean->SetMarkerColor(4);
  c1->cd(0);
  gStyle->SetOptFit(1);
  xMean->GetYaxis()->SetRangeUser(min-0.01,max+0.01);
  xMean->Draw("AP");
  c1->Print(onm.c_str(),"pdf");

  c1->Print(Form("%s]",onm.c_str()),"pdf");
}


double nTupleAna(string fn, int n,double &a, double &da)
{    
  TFile *fin=TFile::Open(fn.c_str());
  TTree *t=(TTree*)fin->Get("QweakSimG4_Tree");
  TH1F *h=new TH1F(Form("h%d",n),Form("PMT asym for sim file %d",n),101,-1,1);
  t->Draw(Form("(Cerenkov.PMT.PMTLeftNbOfPEs[3] - Cerenkov.PMT.PMTRightNbOfPEs[3])/(Cerenkov.PMT.PMTLeftNbOfPEs[3] + Cerenkov.PMT.PMTRightNbOfPEs[3])>>h%d",n),"Cerenkov.PMT.PMTLeftNbOfPEs[3]!=0 && Cerenkov.PMT.PMTRightNbOfPEs[3]!=0");
  TF1 *fg=new TF1("fg","gaus(0)");
  fg->SetParameters(h->GetMaximum(),h->GetMean(),h->GetRMS());
  h->Fit("fg","Q");
  a=fg->GetParameter(1);
  da=fg->GetParError(1);
  gStyle->SetOptFit(1);
  c1->Print(onm.c_str(),"pdf");
  fin->Close();
}


int bad(int n, double a[500]){
  for(int i=0;i<n;i++)
    if(fabs(a[n]-a[i])<0.0001) return 1;
  return 0;
}
