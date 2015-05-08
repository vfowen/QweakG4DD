TCanvas *c1=new TCanvas("c1","c1",1800,1200);
string onm;

void nTreeEnergyAsym(){
  onm="y_MD_firstInt_energyAsym_V.pdf";
  nTreeFirstIntOneSet("../fName_V.lst");
}
void nTreeFirstIntOneSet(string flist){
  c1->Clear();
  ifstream fin(flist.c_str());
  string data;
  string gnm[4]={"primary e+","non primary e+","non primary e-","gamma"};

  TH1F *Asym[4];
  for(int i=0;i<4;i++) Asym[i]=new TH1F(Form("Asym%d",i),Form("log10(E) asym %s",gnm[i].c_str()),400,-2,3.5);

  c1->cd(0);
  c1->Divide(2,2);
  c1->Print(Form("%s[",onm.c_str()),"pdf");
  int n=0;
  while(fin>>data){
    TString fl(data.c_str());
    fl.Remove(fl.Last('/')+1,fl.Length());
    fl+="o_anaTree.root";
    cout<<fl.Data()<<endl;
    doAna(fl.Data(),Asym,n);
    n++;
  }

  for(int i=0;i<4;i++){
    c1->cd(i+1);
    gPad->SetLogy(0);
    Asym[i]->GetYaxis()->SetRangeUser(-1.1,1.1);
    Asym[i]->DrawCopy();    
  }
  c1->Print(onm.c_str(),"pdf");

  for(int i=0;i<4;i++){
    c1->cd(i+1);
    gPad->SetLogy(0);
    Asym[i]->GetYaxis()->SetRangeUser(-0.1,0.1);
    //Asym[i]->GetXaxis()->SetRangeUser(0,_xh[i]);
    Asym[i]->DrawCopy();    
  }
  c1->Print(onm.c_str(),"pdf");

  c1->Print(Form("%s]",onm.c_str()),"pdf");
}


double doAna(char *fn,TH1F *hA[15], int n)
{
  TFile *fin=TFile::Open(fn,"READ");
  TTree *t=(TTree*)fin->Get("th");

  TH1F *ha[4];
  TH1F *he[8];
  for(int i=0;i<4;i++){
    ha[i]=new TH1F(Form("ha%d_%d",i,n),Form("(+ - -)/(+ + -); log10(E)[MeV]"),400,-2,3.5);
    he[i]=new TH1F(Form("hel%d_%d",i,n),Form("(+ - -)/(+ + -); log10(E)[MeV]"),400,-2,3.5);
    he[i+4]=new TH1F(Form("her%d_%d",i,n),Form("(+ - -)/(+ + -); log10(E)[MeV]"),400,-2,3.5);
  }
    
  t->Project(Form("hel0_%d",n), "log10(E)","x>0.00001 && hasParent==0 && nInt==1 && pType==11 && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angX)<=90");
  t->Project(Form("hel1_%d",n), "log10(E)","x>0.00001 && hasParent==0 && nInt==1 && pType==-11&& sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("hel2_%d",n), "log10(E)","x>0.00001 && hasParent==0 && nInt==1 && pType==11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("hel3_%d",n), "log10(E)","x>0.00001 && hasParent==0 && nInt==1 && abs(pType)==22  && abs(angX)<=90");
						
  t->Project(Form("her0_%d",n), "log10(E)","x<0.00001 && hasParent==0 && nInt==1 && pType==11 && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angX)<=90");
  t->Project(Form("her1_%d",n), "log10(E)","x<0.00001 && hasParent==0 && nInt==1 && pType==-11&& sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("her2_%d",n), "log10(E)","x<0.00001 && hasParent==0 && nInt==1 && pType==11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("her3_%d",n), "log10(E)","x<0.00001 && hasParent==0 && nInt==1 && abs(pType)==22  && abs(angX)<=90");

  for(int i=0;i<4;i++)
    calcAsym(he[i],he[i+4],ha[i]);

  for(int i=0;i<4;i++) addAsym(hA[i],ha[i]);
  
  

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

void calcAsym(TH1F *a, TH1F *b,TH1F *A){
  int nb=a->GetXaxis()->GetNbins();
  for(int i=0;i<nb;i++){
    double vm=a->GetBinContent(i+1);
    double vp=b->GetBinContent(i+1);
    double as,das;
    if(vp+vm==0){
      as=0;
      das=0;
    }else{
      as=(vp-vm)/(vp+vm);
      das=2./pow(vp+vm,2)*sqrt(vp*vm*vm + vp*vp*vm);
    }
    A->SetBinContent(i+1,as);
    A->SetBinError(i+1,das);
  }
}
 
 
