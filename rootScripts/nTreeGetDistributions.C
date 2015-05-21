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
  TH1F *distr[10];
  for(int i=0;i<5;i++){
    distr[i]  =new TH1F(Form("hX_%s_%d",onm.c_str(),i)   ,Form("%s ; Xpos[cm]",gnm[i].c_str())  ,200,-100,100);
    distr[i+5]=new TH1F(Form("hangX_%s_%d",onm.c_str(),i),Form("%s ; Ang X[deg]",gnm[i].c_str()),180,-90,90);
  }

  while(fin>>data){
    TString fl(data.c_str());
    fl.Remove(fl.Last('/')+1,fl.Length());
    fl+="o_anaTree.root";
    cout<<fl.Data()<<endl;
    doAna(fl.Data(),distr);    
  }

  for(int i=0;i<10;i++){
    fout->cd();
    distr[i]->Write();
  }

  fout->Close();
  
}


double doAna(char *fn, TH1F *hA[10])
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

  t->Project(Form("ha_0_%d",n),"x"   ,"E>1 && hasParent==0 && nInt==1 && pType==11  && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angX)<=90");
  t->Project(Form("ha_1_%d",n),"x"   ,"E>1 && hasParent==0 && nInt==1 && pType==11  && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("ha_2_%d",n),"x"   ,"E>1 && hasParent==0 && nInt==1 && pType==-11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("ha_3_%d",n),"x"   ,"E>1 && hasParent==0 && nInt==1 && abs(pType)==11  && abs(angX)<=90");
  t->Project(Form("ha_4_%d",n),"x"   ,"E>1 && hasParent==0 && nInt==1 && abs(pType)==22  && abs(angX)<=90");
  t->Project(Form("ha_5_%d",n),"angX","E>1 && hasParent==0 && nInt==1 && pType==11  && sqrt(pow(poly,2)+pow(polz,2))>0.1 && abs(angX)<=90");
  t->Project(Form("ha_6_%d",n),"angX","E>1 && hasParent==0 && nInt==1 && pType==11  && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("ha_7_%d",n),"angX","E>1 && hasParent==0 && nInt==1 && pType==-11 && sqrt(pow(poly,2)+pow(polz,2))<0.1 && abs(angX)<=90");
  t->Project(Form("ha_8_%d",n),"angX","E>1 && hasParent==0 && nInt==1 && abs(pType)==11  && abs(angX)<=90");
  t->Project(Form("ha_9_%d",n),"angX","E>1 && hasParent==0 && nInt==1 && abs(pType)==22  && abs(angX)<=90");

  for(int i=0;i<10;i++)
    hA[i]->Add(ha[i]);
  
  fin->Close();
}
 
