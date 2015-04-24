TCanvas *c1=new TCanvas("c1","c1",1200,600);
string onm;
void nTupleAngleAlongBar(){
  onm="y_PbExitAngles_mV.pdf";
  nTupleAngleAlongBarOneSet("../output/farm/fTuple_mV_0.in");
  onm="y_PbExitAngles_mL.pdf";
  nTupleAngleAlongBarOneSet("../output/farm/fTuple_mL_0.in");
  onm="y_PbExitAngles_L.pdf";
  nTupleAngleAlongBarOneSet("../output/farm/fTuple_L_0.in");
  onm="y_PbExitAngles_V.pdf";
  nTupleAngleAlongBarOneSet("../output/farm/fTuple_V_0.in");

}

void nTupleAngleAlongBarOneSet(string flist){
  ifstream fin(flist.c_str());

  c1->Clear();
  string data;
  double x[500];
  double z[500];
  double y[500];
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  int n=0;
  double xmin=100;
  double xmax=-100;
  double ymin=100;
  double ymax=-100;
  c1->cd(0);
  c1->Divide(3);
  while(fin>>data){
    cout<<data.c_str()<<endl;
    doAna(x[n],y[n],data);
    if(fabs(x[n])>90 || fabs(y[n])>90) continue;
    if(x[n]<xmin) xmin=x[n];
    if(x[n]>xmax) xmax=x[n];
    if(y[n]<ymin) ymin=y[n];
    if(y[n]>ymax) ymax=y[n];
    z[n]=n;
    if(bad(n,x) && bad(n,y)) continue;
    n++;
  }
  TGraph *xMean=new TGraph(n,z,x);
  xMean->GetXaxis()->SetTitle("simulation file number");
  xMean->GetYaxis()->SetTitle("Angle along X [deg]");
  xMean->Fit("pol0");
  xMean->SetMarkerStyle(20);
  xMean->SetMarkerColor(4);
  TGraph *yMean=new TGraph(n,z,y);
  yMean->GetXaxis()->SetTitle("simulation file number");
  yMean->GetYaxis()->SetTitle("Angle along Y [deg]");
  yMean->Fit("pol0");
  yMean->SetMarkerStyle(20);
  yMean->SetMarkerColor(4);
  c1->cd(0);
  c1->Clear();
  c1->Divide(2);
  c1->cd(1);
  gStyle->SetOptFit(1);
  xMean->GetYaxis()->SetRangeUser(xmin-0.1,xmax+0.1);
  xMean->Draw("AP");
  c1->cd(2);
  gStyle->SetOptFit(1);
  yMean->GetYaxis()->SetRangeUser(ymin-0.1,ymax+0.1);
  yMean->Draw("AP");
  c1->Print(onm.c_str(),"pdf");

  c1->Print(Form("%s]",onm.c_str()),"pdf");
}

void doAna(double &meanx,double &meany, string fnm){
  double pi=3.14159265;
  TString nb(fnm);
  nb.Remove(nb.Last('/'),nb.Length());
  nb.Remove(0,nb.Last('_')+1);
  int n=nb.Atoi();

  TFile *fin=TFile::Open(fnm.c_str());

  TNtuple *t=(TNtuple*)fin->Get("t");
  float be,bdpx,bdpy,bdpz;
  float ae,adpx,adpy,adpz;
  float apx,apy,apz;
  float bpx,bpy,bpz;
  float ax,ay,az;
  float bx,by,bz;
  float proc;
  float evN;
  
  t->SetBranchAddress("be",  &be);
  t->SetBranchAddress("bx",&bx);
  t->SetBranchAddress("by",&by);
  t->SetBranchAddress("bz",&bz);
  t->SetBranchAddress("ae",  &ae);
  t->SetBranchAddress("apx",&apx);
  t->SetBranchAddress("apy",&apy);
  t->SetBranchAddress("apz",&apz);
  t->SetBranchAddress("bpx",&bpx);
  t->SetBranchAddress("bpy",&bpy);
  t->SetBranchAddress("bpz",&bpz);
  t->SetBranchAddress("bdpx",&bdpx);
  t->SetBranchAddress("bdpy",&bdpy);
  t->SetBranchAddress("bdpz",&bdpz);
  t->SetBranchAddress("adpx",&adpx);
  t->SetBranchAddress("adpy",&adpy);
  t->SetBranchAddress("adpz",&adpz);
  t->SetBranchAddress("ax",&ax);
  t->SetBranchAddress("ay",&ay);
  t->SetBranchAddress("az",&az);
  t->SetBranchAddress("process",&proc);//1:msc; 2:CoulombSc; 3:eBrem;..
  if(!t->GetBranch("evN")){
    cout<<fnm.c_str()<<" does not have evN branch .. quitting!"<<endl;
    meanx=-999;
    return;
  }
  t->SetBranchAddress("evN",&evN);

  double angX,angY;
  TH2F *ang=new TH2F(Form("ang%d",n),"last Pb primary interaction;ang along x; ang along y",361,-180,180,361,-180,180);
  TH1F *aX=new TH1F(Form("aX%d",n),"last Pb primary e inter;angle along X",181,-90,90);
  TH1F *aY=new TH1F(Form("aY%d",n),"last Pb primary e inter;angle along Y",181,-90,90);
  
  int currentEv=-1;
  double n1=0,n2=0,n3=0,n4=0,scat;
  
  int nentries=t->GetEntries();
  for(int i=0;i<nentries;i++){
    t->GetEntry(i);

    if(currentEv!=(int)evN){      
      if(currentEv!=-1){
	if(angX!=-999){
	  ang->Fill(angY,angX);
	  aX->Fill(angY);
	  aY->Fill(angX);
	}
      }
      currentEv=(int)evN;
    }
    
    TVector3 bp(bpx,bpy,bpz);
    TVector3 ap(apx,apy,apz);
    if(bp.Mag()==0 || ap.Mag()==0) {
      angX=-999;
      continue;
    }
    
    TVector3 bdp(bdpx,bdpy,bdpz);
    TVector3 adp(adpx,adpy,adpz);
    float _bphi,_aphi;
    if(bdp.Phi()<0) _bphi=bdp.Phi()+2*pi;
    else _bphi=bdp.Phi();
    if(adp.Phi()<0) _aphi=adp.Phi()+2*pi;
    else _aphi=adp.Phi();
    float _bth,_ath;
    if(bdp.Theta()<0) _bth=bdp.Theta()+2*pi;
    else _bth=bdp.Theta();
    if(adp.Theta()<0) _ath=adp.Theta()+2*pi;
    else _ath=adp.Theta();

    angY=atan2(sin(_ath)*sin(_aphi),cos(_ath))*180./pi;
    angX=atan2(sin(_ath)*cos(_aphi),cos(_ath))*180./pi;            
  }

  c1->cd(1);
  ang->Draw("colz");
  c1->cd(2);
  aX->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(3);
  aY->DrawCopy();
  c1->Print(onm.c_str(),"pdf");

  meanx=aX->GetMean();
  meany=aY->GetMean();
  fin->Close();
}

int bad(int n, double a[500]){
  for(int i=0;i<n;i++)
    if(fabs(a[n]-a[i])<0.0001) return 1;
  return 0;
}
