string fnm;

void nStripAngVSe(){
  fnm="o_PEangle_distributions.root";
  TFile *fout=new TFile(fnm.c_str(),"RECREATE");
  fout->Close();
  
  const int ne=5;
  const int energy[5]={5,10,30,50,100};
  for(int i=0;i<ne;i++)
    doOneEnergy(energy[i]);
}

void doOneEnergy(int energy){

  gSystem->Exec(Form("ls /lustre/expphy/volatile/hallc/qweak/ciprian/farmoutput/angVSe/jobs/L_%04d_*/o_anaTree.root > z_tst.in",energy));
  ifstream fin("z_tst.in");
  string data;

  TFile *fout=TFile::Open(fnm.c_str(),"UPDATE");
  TH2D *LX=new TH2D(Form("LX_%04d",energy),"; angX [deg] ; left number of PEs",180,-90,90,150,-0.5,149.5);
  TH2D *LY=new TH2D(Form("LY_%04d",energy),"; angY [deg] ; left number of PEs",180,-90,90,150,-0.5,149.5);
  TH2D *RX=new TH2D(Form("RX_%04d",energy),"; angX [deg] ; left number of PEs",180,-90,90,150,-0.5,149.5);
  TH2D *RY=new TH2D(Form("RY_%04d",energy),"; angY [deg] ; left number of PEs",180,-90,90,150,-0.5,149.5);

  while(fin>>data)
    doOneFile(data,LX,LY,RX,RY);    
  fin.close();

  fout->cd();
  LX->Write();
  LY->Write();
  RX->Write();
  RY->Write();
  fout->Close();
}

void doOneFile(string fname,TH2D *LangX, TH2D *LangY,TH2D *RangX, TH2D *RangY){

  cout<<"Processing: "<<fname.c_str()<<endl;
      
  TFile *rf=TFile::Open(fname.c_str(),"READ");
  TTree *te=(TTree*)rf->Get("te");
  TTree *th=(TTree*)rf->Get("th");

  float lpe(0),rpe(0),aX(0),aY(0);
  int nEvTH(0),nEvTE(0);
  int tID(0),nInt(0),pType(0),hasParent(0);

  te->SetBranchAddress("LnPMThit",&lpe);
  te->SetBranchAddress("RnPMThit",&rpe);
  te->SetBranchAddress("evNr",&nEvTE);

  th->SetBranchAddress("evNr",&nEvTH);
  th->SetBranchAddress("angX",&aX);
  th->SetBranchAddress("angY",&aY);
  th->SetBranchAddress("tID",&tID);
  th->SetBranchAddress("hasParent",&hasParent);
  th->SetBranchAddress("nInt",&nInt);
  th->SetBranchAddress("pType",&pType);
  
  int nev=th->GetEntries();
  int currentEv=-1;
  int evTE=0;

  int statL(0),statR(0),statAx(0),statAy(0),statN(0);
  
  for(int i=0;i<nev;i++){
    th->GetEntry(i);

    if(pType!=11) continue;// electron
    if(hasParent!=0) continue;
    if(tID!=1) continue;
    if(nInt!=1) continue;

    do{
      te->GetEntry(evTE);
      evTE++;
    }while(nEvTH!=nEvTE);

    if(fabs(aX)>90 || fabs(aY)>90 || lpe<0 || rpe<0) {
      if(fabs(aX)>90) statAx++;
      if(fabs(aY)>90) statAy++;
      if(lpe<0) statL++;
      if(rpe<0) statR++;
      statN++;
      //cout<<"~~ "<<nEvTH<<" "<<nEvTE<<" "<<aX<<" "<<aY<<" "<<lpe<<" "<<rpe<<endl;
      continue;
    }
    LangX->Fill(aX,lpe);
    LangY->Fill(aY,lpe);
    RangX->Fill(aX,rpe);
    RangY->Fill(aY,rpe);
  }

  cout<<"~~ skipped "<<statN<<" "<<statL<<" "<<statR<<" "<<statAx<<" "<<statAy<<endl;
  rf->Close();
}
