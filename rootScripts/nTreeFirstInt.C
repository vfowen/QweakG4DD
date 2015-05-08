TCanvas *c1=new TCanvas("c1","c1",1800,1200);
string onm;

void nTreeFirstInt(){
  onm="y_MD_firstInt_mV.pdf";
  nTreeFirstIntOneSet("../output/farm/fName_mV_0.in");
  onm="y_MD_firstInt_V.pdf";
  nTreeFirstIntOneSet("../output/farm/fName_V_0.in");
  onm="y_MD_firstInt_mL.pdf";
  nTreeFirstIntOneSet("../output/farm/fName_mL_0.in");
  onm="y_MD_firstInt_L.pdf";
  nTreeFirstIntOneSet("../output/farm/fName_L_0.in");
}
void nTreeFirstIntOneSet(string flist){
  c1->Clear();
  ifstream fin(flist.c_str());
  string data;
  string gnm[15]={"X position [cm] primary e","X position [cm] nonP e+","X position [cm] nonP e-","X position [cm] all e","X position [cm] g",
		 "Angle along x [deg] primary e","Angle along x [deg] nonP e+","Angle along x [deg] nonP e-","Angle along x [deg] all e","Angle along x [deg] g",
		 "Angle along y [deg] primary e","Angle along y [deg] nonP e+","Angle along y [deg] nonP e-","Angle along y [deg] all e","Angle along y [deg] g"};
  double val[500][15];
  double x[500];
  int ng=15;
  TGraph *mean[15];

  TH1F *Asym[15];
  for(int i=0;i<5;i++) Asym[i]=new TH1F(Form("Asym%d",i),Form("Asym %s",gnm[i].c_str()),50,0,30);
  for(int i=5;i<15;i++) Asym[i]=new TH1F(Form("Asym%d",i),Form("Asym %s",gnm[i].c_str()),180,0,90);

  c1->cd(0);
  c1->Divide(5,3);
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  int n=0;
  double min[15]={100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
  double max[15]={-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100};
  while(fin>>data){
    TString fl(data.c_str());
    fl.Remove(fl.Last('/')+1,fl.Length());
    fl+="o_anaTree.root";
    cout<<fl.Data()<<endl;
    doAna(fl.Data(),
	  val[n][0], val[n][1], val[n][2], val[n][3], val[n][4],//xpos
	  val[n][5], val[n][6], val[n][7], val[n][8], val[n][9],//angX
	  val[n][10],val[n][11],val[n][12],val[n][13],val[n][14],//angY
	  Asym);//asym

    if( bad(n,val,0) &&  bad(n,val,1) && bad(n,val,4) && bad(n,val,10)) continue;

    for(int i=0;i<ng;i++){
      if(val[n][i]<min[i]) min[i]=val[n][i];
      if(val[n][i]>max[i]) max[i]=val[n][i];
    }
    
    x[n]=n;
    n++;
  }

  gStyle->SetOptFit(1);
  for(int i=0;i<ng;i++){
    c1->cd(i+1);
    gPad->SetLogy(0);
    double dm[500];
    for(int j=0;j<n;j++) dm[j]=val[j][i];
    mean[i]=new TGraph(n,x,dm);
    mean[i]->GetXaxis()->SetTitle("simulation file number");
    mean[i]->SetTitle(gnm[i].c_str());
    mean[i]->Fit("pol0");
    mean[i]->SetMarkerStyle(20);
    mean[i]->SetMarkerColor(4);
    mean[i]->GetYaxis()->SetRangeUser(min[i]-0.01,max[i]+0.01);
    mean[i]->Draw("AP");
  }
  c1->Print(onm.c_str(),"pdf");

  c1->Print(Form("%s]",onm.c_str()),"pdf");
}


double doAna(char *fn, double &epx, double &epnx, double &emnx,double &ex, double &gx,
	     double &epax, double &epnax,double &emnax, double &eax, double &gax,
	     double &epay, double &epnay,double &emnay, double &eay, double &gay,
	     TH1F *hA[15])
{
  double pi=3.14159265;
  TString nb(fn);
  nb.Remove(nb.Last('/'),nb.Length());
  nb.Remove(0,nb.Last('_')+1);
  int n=nb.Atoi();
  
  TFile *fin=TFile::Open(fn,"READ");
  TTree *t=(TTree*)fin->Get("th");

  TH1F *ha[15];
  for(int i=0;i<5;i++)ha[i]=new TH1F(Form("ha%d_%d",i,n),Form("(+ - -)/(+ + -); Xpos[cm]"),50,0,30);
  for(int i=5;i<10;i++)ha[i]=new TH1F(Form("ha%d_%d",i,n),Form("(+ - -)/(+ + -); Ang X[deg]"),180,0,90);
  for(int i=10;i<15;i++)ha[i]=new TH1F(Form("ha%d_%d",i,n),Form("(+ - -)/(+ + -); Ang Y[deg]"),180,0,90);
  
  TH1F *hepx=new TH1F(Form("hepx%d",n),Form("First interaction primary e %d;Xpos [cm]",n) ,100,-30,30);
  TH1F *hepnx=new TH1F(Form("hepnx%d",n),Form("First interaction nonP e+ %d;Xpos [cm]",n) ,100,-30,30);
  TH1F *hemnx=new TH1F(Form("hemnx%d",n),Form("First interaction nonP e- %d;Xpos [cm]",n) ,100,-30,30);
  TH1F *hex =new TH1F(Form("hex%d" ,n),Form("First interaction all e %d;Xpos [cm]",n)     ,100,-30,30);
  TH1F *hgx =new TH1F(Form("hgx%d" ,n),Form("First interaction #gamma %d;Xpos [cm]"   ,n) ,100,-30,30);

  TH1F *hepax=new TH1F(Form("hepax%d",n),Form("first interaction primary e %d;ang along x",n)     ,360,-90,90);
  TH1F *hepnax=new TH1F(Form("hepnax%d",n),Form("first interaction nonP e+ %d;ang along x",n)     ,360,-90,90);
  TH1F *hemnax=new TH1F(Form("hemnax%d",n),Form("first interaction nonP e- %d;ang along x",n)     ,360,-90,90);
  TH1F *heax =new TH1F(Form("heax%d" ,n),Form("first interaction all e %d;ang along x",n)         ,360,-90,90);
  TH1F *hgax =new TH1F(Form("hgax%d" ,n),Form("first interaction #gamma %d;ang along x"   ,n)     ,360,-90,90);
  
  TH1F *hepay=new TH1F(Form("hepay%d",n),Form("first interaction primary e %d;ang along y",n)     ,360,-90,90);
  TH1F *hepnay=new TH1F(Form("hepnay%d",n),Form("first interaction nonP e+ %d;ang along y",n)     ,360,-90,90);
  TH1F *hemnay=new TH1F(Form("hemnay%d",n),Form("first interaction nonP e- %d;ang along y",n)     ,360,-90,90);
  TH1F *heay =new TH1F(Form("heay%d" ,n),Form("first interaction all e %d;ang along y",n)         ,360,-90,90);
  TH1F *hgay =new TH1F(Form("hgay%d" ,n),Form("first interaction #gamma %d;ang along y"   ,n)     ,360,-90,90);
    
  t->Project(Form("hepx%d",n),"x","hasParent==0 && nInt==1 &&  pType==11 && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angX)<=90");
  t->Project(Form("hepnx%d",n),"x","hasParent==0 && nInt==1 && pType==-11  && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("hemnx%d",n),"x","hasParent==0 && nInt==1 && pType==11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("hex%d" ,n),"x","hasParent==0 && nInt==1 && abs(pType)==11  && abs(angX)<=90");
  t->Project(Form("hgx%d" ,n),"x","hasParent==0 && nInt==1 && abs(pType)==22  && abs(angX)<=90");
  t->Project(Form("heax%d" ,n),"angX","hasParent==0 && nInt==1 && abs(pType)==11  && abs(angX)<=60");
  t->Project(Form("heay%d" ,n),"angY","hasParent==0 && nInt==1 && abs(pType)==11  && abs(angY)<=90");
  t->Project(Form("hgax%d" ,n),"angX","hasParent==0 && nInt==1 && abs(pType)==22  && abs(angX)<=60");
  t->Project(Form("hgay%d" ,n),"angY","hasParent==0 && nInt==1 && abs(pType)==22  && abs(angY)<=90");
  t->Project(Form("hepay%d",n),"angY","hasParent==0 && nInt==1 && abs(pType)==11 && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angY)<=90");
  t->Project(Form("hepax%d",n),"angX","hasParent==0 && nInt==1 && abs(pType)==11 && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angX)<=60");
  t->Project(Form("hepnay%d",n),"angY","hasParent==0 && nInt==1 && pType==-11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angY)<=90");
  t->Project(Form("hepnax%d",n),"angX","hasParent==0 && nInt==1 && pType==-11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=60");
  t->Project(Form("hemnay%d",n),"angY","hasParent==0 && nInt==1 && pType==11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angY)<=90");
  t->Project(Form("hemnax%d",n),"angX","hasParent==0 && nInt==1 && pType==11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=60");

  calcAsym(hepx,ha[0]);
  calcAsym(hepnx,ha[1]);
  calcAsym(hemnx,ha[2]);
  calcAsym(hex,ha[3]);
  calcAsym(hgx,ha[4]);

  calcAsym(hepax,ha[5]);
  calcAsym(hepnax,ha[6]);
  calcAsym(hemnax,ha[7]);
  calcAsym(heax,ha[8]);
  calcAsym(hgax,ha[9]);

  calcAsym(hepay,ha[10]);
  calcAsym(hepnay,ha[11]);
  calcAsym(hemnay,ha[12]);
  calcAsym(heay,ha[13]);
  calcAsym(hgay,ha[14]);

  
  c1->cd(1);
  hepx->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(2);
  hex->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(3);
  hepnx->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(4);
  hemnx->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(5);
  hgx->DrawCopy();
  gPad->SetLogy(1);

  c1->cd(6);
  hepax->DrawCopy();
  hepax->GetYaxis()->SetRangeUser(0.5,hepax->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(7);
  heax->DrawCopy();
  heax->GetYaxis()->SetRangeUser(0.5,heax->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(8);
  hepnax->DrawCopy();
  hepnax->GetYaxis()->SetRangeUser(0.5,hepnax->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(9);
  hemnax->DrawCopy();
  hemnax->GetYaxis()->SetRangeUser(0.5,hemnax->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(10);
  hgax->DrawCopy();
  hgax->GetYaxis()->SetRangeUser(0.5,hgax->GetMaximum()*1.1);
  gPad->SetLogy(1);

  c1->cd(11);
  hepay->DrawCopy();
  hepay->GetYaxis()->SetRangeUser(0.5,hepay->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(12);
  heay->DrawCopy();
  heay->GetYaxis()->SetRangeUser(0.5,heay->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(13);
  hepnay->DrawCopy();
  hepnay->GetYaxis()->SetRangeUser(0.5,hepnay->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(14);
  hemnay->DrawCopy();
  hemnay->GetYaxis()->SetRangeUser(0.5,hemnay->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(15);
  hgay->DrawCopy();
  hgay->GetYaxis()->SetRangeUser(0.5,hgay->GetMaximum()*1.1);
  gPad->SetLogy(1);  
  c1->Print(onm.c_str(),"pdf");


  for(int i=0;i<15;i++){
    c1->cd(i+1);
    ha[i]->GetYaxis()->SetRangeUser(-1.1,1.1);
    ha[i]->SetMarkerStyle(20);
    ha[i]->SetMarkerColor(2);
    ha[i]->SetLineColor(4);
    ha[i]->DrawCopy();
    gPad->SetLogy(0);
  }
  c1->Print(onm.c_str(),"pdf");

  for(int i=0;i<15;i++) addAsym(hA[i],ha[i]);
  
  epx=hepx->GetMean();
  epnx=hepnx->GetMean();
  emnx=hemnx->GetMean();
  ex=hex->GetMean();
  gx=hgx->GetMean();
  epax=hepax->GetMean();
  epnax=hepnax->GetMean();
  emnax=hemnax->GetMean();
  eax=heax->GetMean();
  gax=hgax->GetMean();
  epay=hepay->GetMean();
  epnay=hepnay->GetMean();
  emnay=hemnay->GetMean();
  eay=heay->GetMean();
  gay=hgay->GetMean();
  
  fin->Close();
}
 
void addAsym(TH1F *A,TH1F *a){
  int nb=A->GetXaxis()->GetNbins();
  for(int i=1;i<=nb;i++){
    double vA=A->GetBinContent(i);
    double vdA=A->GetBinError(i);
    double va=a->GetBinContent(i);
    double vda=a->GetBinError(i);
    double as,das;
    if(vdA==0){
      as=va;
      das=vda;
    }else if(vda==0){
      as=vA;
      das=vdA;
    }else{
      as=(vA/pow(vdA,2)+va/pow(vda,2))/(1./pow(vdA,2)+1./pow(vda,2));
      das=sqrt(1./(1./pow(vdA,2)+1./pow(vda,2)));
    }
    A->SetBinContent(i,as);
    A->SetBinError(i,das);
  }
}

void calcAsym(TH1F *a, TH1F *A){
  int nb=a->GetXaxis()->GetNbins();
  for(int i=0;i<nb/2;i++){
    double vm=a->GetBinContent(i+1);
    double vp=a->GetBinContent(nb-i);
    double as=(vp-vm)/(vp+vm);
    double das=2./pow(vp+vm,2)*sqrt(vp*vm*vm + vp*vp*vm);
    A->SetBinContent(i+1,as);
    A->SetBinError(i+1,das);
  }
}
 
 
int bad(int n, double a[500][15],int m){
  for(int i=0;i<n;i++)
    if(fabs(a[n][m]-a[i][m])<0.0001) return 1;
  return 0;
}
