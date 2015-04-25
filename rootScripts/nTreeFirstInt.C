TCanvas *c1=new TCanvas("c1","c1",1600,1200);
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
  string gnm[12]={"X position [cm] primary e","X position [cm] e non Primary","X position [cm] all e","X position [cm] g",
		 "Angle along x [deg] primary e","Angle along x [deg] e non Primary","Angle along x [deg] all e","Angle along x [deg] g",
		 "Angle along y [deg] primary e","Angle along y [deg] e non Primary","Angle along y [deg] all e","Angle along y [deg] g"};
  double val[500][12];
  double x[500];
  int ng=12;
  TGraph *mean[12];

  c1->cd(0);
  c1->Divide(4,3);
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  int n=0;
  double min[12]={100,100,100,100,100,100,100,100,100,100,100,100};
  double max[12]={-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100,-100};
  while(fin>>data){
    TString fl(data.c_str());
    fl.Remove(fl.Last('/')+1,fl.Length());
    fl+="o_anaTree.root";
    cout<<fl.Data()<<endl;
    doAna(fl.Data(),
	  val[n][0],val[n][1],val[n][2],val[n][3],//xpos
	  val[n][4],val[n][5],val[n][6],val[n][7],//angX
	  val[n][8],val[n][9],val[n][10],val[n][11]);//angY

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


double doAna(char *fn, double &epx, double &enx,double &ex, double &gx,
	     double &epax, double &enax, double &eax, double &gax,
	     double &epay, double &enay, double &eay, double &gay)
{
  double pi=3.14159265;
  TString nb(fn);
  nb.Remove(nb.Last('/'),nb.Length());
  nb.Remove(0,nb.Last('_')+1);
  int n=nb.Atoi();
  
  TFile *fin=TFile::Open(fn,"READ");
  TTree *t=(TTree*)fin->Get("th");

  TH1F *hepx=new TH1F(Form("hepx%d",n),Form("First interaction primary e %d;Xpos [cm]",n) ,101,-30,30);
  TH1F *henx=new TH1F(Form("henx%d",n),Form("First interaction non prim e %d;Xpos [cm]",n),101,-30,30);
  TH1F *hex =new TH1F(Form("hex%d" ,n),Form("First interaction all e %d;Xpos [cm]",n)     ,101,-30,30);
  TH1F *hgx =new TH1F(Form("hgx%d" ,n),Form("First interaction #gamma %d;Xpos [cm]"   ,n) ,101,-30,30);

  TH1F *hepax=new TH1F(Form("hepax%d",n),Form("first interaction primary e %d;ang along x",n)     ,361,-90,90);
  TH1F *henax=new TH1F(Form("henax%d",n),Form("first interaction non primary e %d;ang along x",n) ,361,-90,90);
  TH1F *heax =new TH1F(Form("heax%d" ,n),Form("first interaction all e %d;ang along x",n)         ,361,-90,90);
  TH1F *hgax =new TH1F(Form("hgax%d" ,n),Form("first interaction #gamma %d;ang along x"   ,n)     ,361,-90,90);
  TH1F *hepay=new TH1F(Form("hepay%d",n),Form("first interaction primary e %d;ang along y",n)     ,361,-90,90);
  TH1F *henay=new TH1F(Form("henay%d",n),Form("first interaction non primary e %d;ang along y",n) ,361,-90,90);
  TH1F *heay =new TH1F(Form("heay%d" ,n),Form("first interaction non prim e %d;ang along y",n)    ,361,-90,90);
  TH1F *hgay =new TH1F(Form("hgay%d" ,n),Form("first interaction #gamma %d;ang along y"   ,n)     ,361,-90,90);
  
  
  t->Project(Form("hepx%d",n),"x","hasParent==0 && nInt==1 && abs(pType)==11 && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angX)<=90");
  t->Project(Form("henx%d",n),"x","hasParent==0 && nInt==1 && abs(pType)==11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("hex%d" ,n),"x","hasParent==0 && nInt==1 && abs(pType)==11  && abs(angX)<=90");
  t->Project(Form("hgx%d" ,n),"x","hasParent==0 && nInt==1 && abs(pType)==22  && abs(angX)<=90");
  t->Project(Form("heax%d" ,n),"angX","hasParent==0 && nInt==1 && abs(pType)==11  && abs(angX)<=60");
  t->Project(Form("heay%d" ,n),"angY","hasParent==0 && nInt==1 && abs(pType)==11  && abs(angY)<=90");
  t->Project(Form("hgax%d" ,n),"angX","hasParent==0 && nInt==1 && abs(pType)==22  && abs(angX)<=60");
  t->Project(Form("hgay%d" ,n),"angY","hasParent==0 && nInt==1 && abs(pType)==22  && abs(angY)<=90");
  t->Project(Form("hepay%d",n),"angY","hasParent==0 && nInt==1 && abs(pType)==11 && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angY)<=90");
  t->Project(Form("hepax%d",n),"angX","hasParent==0 && nInt==1 && abs(pType)==11 && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angX)<=60");
  t->Project(Form("henay%d",n),"angY","hasParent==0 && nInt==1 && abs(pType)==11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angY)<=90");
  t->Project(Form("henax%d",n),"angX","hasParent==0 && nInt==1 && abs(pType)==11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=60");

  c1->cd(1);
  hepx->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(2);
  hex->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(3);
  henx->DrawCopy();
  gPad->SetLogy(1);
  c1->cd(4);
  hgx->DrawCopy();
  gPad->SetLogy(1);

  c1->cd(5);
  hepax->DrawCopy();
  hepax->GetYaxis()->SetRangeUser(0.5,hepax->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(6);
  heax->DrawCopy();
  heax->GetYaxis()->SetRangeUser(0.5,heax->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(7);
  henax->DrawCopy();
  henax->GetYaxis()->SetRangeUser(0.5,henax->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(8);
  hgax->DrawCopy();
  hgax->GetYaxis()->SetRangeUser(0.5,hgax->GetMaximum()*1.1);
  gPad->SetLogy(1);

  c1->cd(9);
  hepay->DrawCopy();
  hepay->GetYaxis()->SetRangeUser(0.5,hepay->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(10);
  heay->DrawCopy();
  heay->GetYaxis()->SetRangeUser(0.5,heay->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(11);
  henay->DrawCopy();
  henay->GetYaxis()->SetRangeUser(0.5,henay->GetMaximum()*1.1);
  gPad->SetLogy(1);
  c1->cd(12);
  hgay->DrawCopy();
  hgay->GetYaxis()->SetRangeUser(0.5,hgay->GetMaximum()*1.1);
  gPad->SetLogy(1);  
  c1->Print(onm.c_str(),"pdf");

  epx=hepx->GetMean();
  enx=henx->GetMean();
  ex=hex->GetMean();
  gx=hgx->GetMean();
  epax=hepax->GetMean();
  enax=henax->GetMean();
  eax=heax->GetMean();
  gax=hgax->GetMean();
  epay=hepay->GetMean();
  enay=henay->GetMean();
  eay=heay->GetMean();
  gay=hgay->GetMean();
  
  fin->Close();
}


int bad(int n, double a[500][12],int m){
  for(int i=0;i<n;i++)
    if(fabs(a[n][m]-a[i][m])<0.0001) return 1;
  return 0;
}
