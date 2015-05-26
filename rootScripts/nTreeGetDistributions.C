string onm;
void nTreeGetDistributions(){
  TFile *fout=new TFile("o_distributions.root","RECREATE");
  fout->Close();
  onm="V";
  nTreeFirstIntOneSet("../fName_V.lst");
  // onm="L";
  // nTreeFirstIntOneSet("../fName_L.lst");
  // onm="mV";
  // nTreeFirstIntOneSet("../fName_mV.lst");
  // onm="mL";
  // nTreeFirstIntOneSet("../fName_mL.lst");
}

void nTreeFirstIntOneSet(string flist){

  ifstream fin(flist.c_str());
  string data;
  string gnm[5]={"Primary e-","Non primary e-","Non primary e+","All e#pm","Photons"};
  
  TFile *fout=new TFile("o_distributions.root","UPDATE");
  TH1F *distr[20];
  for(int i=0;i<5;i++){
    distr[i]  =new TH1F(Form("hX_%s_%d",onm.c_str(),i)   ,Form("%s ; Xpos[cm]",gnm[i].c_str())  ,200,-100,100);
    distr[i+5]=new TH1F(Form("hangX_%s_%d",onm.c_str(),i),Form("%s ; Ang X[deg]",gnm[i].c_str()),180,-90,90);
  }
  for(int i=10;i<15;i++){
    distr[i]  =new TH1F(Form("mX_%s_%d",onm.c_str(),i)   ,Form("Mean for %s ; Xpos[cm]",gnm[i].c_str())  ,200,-100,100);
    distr[i+5]=new TH1F(Form("mangX_%s_%d",onm.c_str(),i),Form("Mean for %s ; Ang X[deg]",gnm[i].c_str()),180,-90,90);
  }

  while(fin>>data){
    TString fl(data.c_str());
    fl.Remove(fl.Last('/')+1,fl.Length());
    fl+="o_anaTree.root";
    cout<<fl.Data()<<endl;
    doAnaTree(fl.Data(),distr);    
  }

  for(int i=0;i<20;i++){
    fout->cd();
    distr[i]->Write();
  }

  fout->Close();
  
}


void doAna(char *fn, TH1F *hA[10])
{
  TString nb(fn);
  nb.Remove(nb.Last('/'),nb.Length());
  nb.Remove(0,nb.Last('_')+1);
  int n=nb.Atoi();
  
  TFile *fin=TFile::Open(fn,"READ");
  TTree *t=(TTree*)fin->Get("th");

  TH1F *ha[10];
  for(int i=0;i<5;i++){
    ha[i]  =new TH1F(Form("ha%d_%d",i,n)  ,Form(" Particle %d; Xpos[cm]"  ,i),200,-100,100);
    ha[i+5]=new TH1F(Form("ha%d_%d",i+5,n),Form(" Particle %d; Ang X[deg]",i),180,-90,90);
  }

  t->Project(Form("ha0_%d",n),"x"   ,"E>1 && hasParent==0 && nInt==1 && pType==11  && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angX)<=90");
  t->Project(Form("ha1_%d",n),"x"   ,"E>1 && hasParent==0 && nInt==1 && pType==11  && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("ha2_%d",n),"x"   ,"E>1 && hasParent==0 && nInt==1 && pType==-11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("ha3_%d",n),"x"   ,"E>1 && hasParent==0 && nInt==1 && abs(pType)==11  && abs(angX)<=90");
  t->Project(Form("ha4_%d",n),"x"   ,"E>1 && hasParent==0 && nInt==1 && abs(pType)==22  && abs(angX)<=90");
  t->Project(Form("ha5_%d",n),"angX","E>1 && hasParent==0 && nInt==1 && pType==11  && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angX)<=90");
  t->Project(Form("ha6_%d",n),"angX","E>1 && hasParent==0 && nInt==1 && pType==11  && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("ha7_%d",n),"angX","E>1 && hasParent==0 && nInt==1 && pType==-11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("ha8_%d",n),"angX","E>1 && hasParent==0 && nInt==1 && abs(pType)==11  && abs(angX)<=90");
  t->Project(Form("ha9_%d",n),"angX","E>1 && hasParent==0 && nInt==1 && abs(pType)==22  && abs(angX)<=90");

  for(int i=0;i<10;i++)
    hA[i]->Add(ha[i]);

  fin->Close();
}
 
void doAnaTree(char *fn, TH1F *hA[20])
{
  TString nb(fn);
  nb.Remove(nb.Last('/'),nb.Length());
  nb.Remove(0,nb.Last('_')+1);
  int n=nb.Atoi();
  
  TFile *fin=TFile::Open(fn,"READ");
  TTree *t=(TTree*)fin->Get("th");

  float x,e;
  int hasPar,nInt, pType;
  float poly,polz,angX;

  t->SetBranchAddress("x",&x);
  t->SetBranchAddress("angX",&angX);
  t->SetBranchAddress("E",&e);
  t->SetBranchAddress("nInt",&nInt);
  t->SetBranchAddress("hasParent",&hasPar);
  t->SetBranchAddress("pType",&pType);
  t->SetBranchAddress("poly",&poly);
  t->SetBranchAddress("polz",&polz);

  int nv=t->GetEntries();

  for(int i=0;i<nv;i++){
    t->GetEvent(i);
    if(hasPar!=0) continue;
    if(nInt!=1) continue;
    if(e<=1 ) continue;
    if( fabs(angX)>90 ) continue;

    if(fabs(pType)==11){
      ha[3]->Fill(x);
      ha[8]->Fill(angX);
      updateMean(x,angX,hA[13],hA[18]);
    }
    
    if(pType==22){
      hA[4]->Fill(x);
      hA[9]->Fill(angX);
      updateMean(x,angX,hA[14],hA[19]);
    }else if(pType==11){
      if(sqrt(pow(poly,2)+pow(polz,2))>0.1){
	ha[0]->Fill(x);
	ha[5]->Fill(angX);
	updateMean(x,angX,hA[10],hA[15]);	
      }else{
	ha[1]->Fill(x);
	ha[6]->Fill(angX);
	updateMean(x,angX,hA[11],hA[16]);
      }
    }else if(pType==-11){
      ha[2]->Fill(x);
      ha[7]->Fill(angX);
      updateMean(x,angX,hA[12],hA[17]);
    }
  }
  
  fin->Close();
}

void updateMean(float x, float ax, TH1F *a, TH1F *b){
  int bx=a->GetXaxis()->FindBin(x);
  int bax=b->GetXaxis()->FindBin(ax);

  if(a->GetBinError(bx)==0){
    a->SetBinContent(bx,x);
    a->SetBinError(bx,1);
  }else{
    float dval=a->GetBinError(bx)+1;
    float val=(x+(dval-1)*a->GetBinContent(bx))/dval;
    a->SetBinContent(bx,val);
    a->SetBinError(bx,dval);    
  }

  if(b->GetBinError(bax)==0){
    b->SetBinContent(bax,x);
    b->SetBinError(bax,1);
  }else{
    float dval=b->GetBinError(bax)+1;
    float val=(ax+(dval-1)*b->GetBinContent(bax))/dval;
    b->SetBinContent(bax,val);
    b->SetBinError(bax,dval);    
  }
}
 
