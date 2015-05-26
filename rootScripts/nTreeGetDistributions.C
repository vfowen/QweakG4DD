string onm;
string fnm;

void nTreeGetDistributions(){
  float Ecut=1;
  fnm="o_distributions_1Ecut_treeTst.root";
  TFile *fout=new TFile(fnm.c_str(),"RECREATE");
  fout->Close();

  onm="V";
  nTreeFirstIntOneSet("../fName_V.lst",Ecut);
  onm="L";
  nTreeFirstIntOneSet("../fName_L.lst",Ecut);
  //onm="mV";
  //nTreeFirstIntOneSet("../fName_mV.lst");
  //onm="mL";
  //nTreeFirstIntOneSet("../fName_mL.lst");
}

void nTreeFirstIntOneSet(string flist, float eneCut){

  ifstream fin(flist.c_str());
  string data;
  string gnm[5]={"Primary e-","Non primary e-","Non primary e+","All e#pm","Photons"};
  
  TFile *fout=new TFile(fnm.c_str(),"UPDATE");
  TH1F *distr[20];
  for(int i=0;i<5;i++){
    distr[i]  =new TH1F(Form("hX_%s_%d",onm.c_str(),i)   ,Form("%s ; Xpos[cm]",gnm[i].c_str())  ,200,-100,100);
    distr[i+5]=new TH1F(Form("hangX_%s_%d",onm.c_str(),i),Form("%s ; Ang X[deg]",gnm[i].c_str()),180,-90,90);
  }
  for(int i=10;i<15;i++){
    distr[i]  =new TH1F(Form("mX_%s_%d",onm.c_str(),i)   ,Form("Mean for %s ; Xpos[cm]",gnm[i-10].c_str())  ,200,-100,100);
    distr[i+5]=new TH1F(Form("mangX_%s_%d",onm.c_str(),i),Form("Mean for %s ; Ang X[deg]",gnm[i-10].c_str()),180,-90,90);
  }

  while(fin>>data){
    TString fl(data.c_str());
    fl.Remove(fl.Last('/')+1,fl.Length());
    fl+="o_anaTree.root";
    cout<<fl.Data()<<endl;
    doAnaTree(fl.Data(),distr,eneCut);    
  }

  for(int i=0;i<20;i++){
    fout->cd();
    distr[i]->Write();
  }

  fout->Close();
  
}


void doAnaTree(char *fn, TH1F *hA[20],float eneCut)
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
    if(e<=eneCut ) continue;
    if( fabs(angX)>90 ) continue;

    if(fabs(pType)==11){
      hA[3]->Fill(x);
      hA[8]->Fill(angX);
      updateMean(x,angX,hA[13],hA[18]);
    }
    
    if(pType==22){
      hA[4]->Fill(x);
      hA[9]->Fill(angX);
      updateMean(x,angX,hA[14],hA[19]);
    }else if(pType==11){
      if(sqrt(pow(poly,2)+pow(polz,2))>0.1){
	hA[0]->Fill(x);
	hA[5]->Fill(angX);
	updateMean(x,angX,hA[10],hA[15]);	
      }else{
	hA[1]->Fill(x);
	hA[6]->Fill(angX);
	updateMean(x,angX,hA[11],hA[16]);
      }
    }else if(pType==-11){
      hA[2]->Fill(x);
      hA[7]->Fill(angX);
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
 
