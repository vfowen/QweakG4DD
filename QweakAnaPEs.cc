#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <algorithm>

#include "interpolatePEs.hh"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

using namespace std;

int main(int argc, char** argv){

  if( argc == 1 || (0 == strcmp("--help", argv[1]))) {
    cout << " usage: build/anaPEs [options]" << endl
         << " --rootfile <path to rootfile>" << endl
         << " --barmodel tracks, ideal0, ideal23, ideal23_polish, ideal23_bevel, "
         << "md6config3_23, md7config2_23, md8config16_0 or md8config16_23"<<endl
         << "\t <tracks> is default and does not calculate PEs" << endl
         << " --distmodel mirror (omit for as is)" << endl
	 << " --suffix <name to append to outFile> (omit for default)" << endl;
    return 1;
  }
  
  // Read in command line paramaters
  string barModel = "tracks";
  string distModel = "asIs";
  string rootfile = "";
  string suffix="";
  int offset = 0;
  for(Int_t i = 1; i < argc; i++) {
    if(0 == strcmp("--barmodel", argv[i])) {
      barModel = argv[i+1];
    }else if(0 == strcmp("--distmodel", argv[i])) {
      distModel = argv[i+1];
    }else if(0 == strcmp("--rootfile", argv[i])) {
      rootfile = argv[i+1];
    }else if(0 == strcmp("--offset", argv[i])) {
      offset = atoi(argv[i+1]);
    }else if(0 == strcmp("--suffix", argv[i])) {
      suffix = argv[i+1];
    }
  }
  cout<<"Bar Model: "<<barModel<<endl;
  interpolatePEs interpolator;
  int maxAvg=2;
  if(barModel!="tracks"){
    interpolator.setLightMap(barModel);
    maxAvg=20;
  }

  TFile *fin=TFile::Open(rootfile.c_str(),"READ");
  TTree *t=(TTree*)fin->Get("t");
  int evNr;
  int primary;//0 secondary, 1 primary
  float x,y,z,E,angX,angY,angXi,angYi,polT;
  float phi,theta;
  double asymPpM(0),asymPmM(0);
  int fillPhi=0;
  t->SetBranchAddress("evNr",&evNr);
  t->SetBranchAddress("primary",&primary);
  t->SetBranchAddress("x",&x);
  t->SetBranchAddress("y",&y);
  t->SetBranchAddress("z",&z);
  t->SetBranchAddress("E",&E);
  t->SetBranchAddress("angX",&angX);
  t->SetBranchAddress("angY",&angY);
  t->SetBranchAddress("angXi",&angXi);
  t->SetBranchAddress("angYi",&angYi);
  t->SetBranchAddress("polT",&polT);
  if(t->GetListOfBranches()->FindObject("phi")){
    t->SetBranchAddress("phi",&phi);
    t->SetBranchAddress("th",&theta);
    fillPhi=1;
  }
  if(t->GetListOfBranches()->FindObject("asymPpM")){
    t->SetBranchAddress("asymPpM",&asymPpM);
    t->SetBranchAddress("asymPmM",&asymPmM);
  }

  string outNm;
  if(suffix=="")
    outNm = Form("o_anaPE_%s_%s.root",barModel.c_str(),distModel.c_str());
  else
    outNm = Form("o_anaPE_%s_%s_%s.root",barModel.c_str(),distModel.c_str(),suffix.c_str());
  TFile *fout=new TFile(outNm.c_str(),"RECREATE");
  string lr[2]={"R","L"};
  string species[3]={"N","P","A"};

  TH1D *hTotPE=new TH1D("hTotPE","",4,0,4);
  hTotPE->GetXaxis()->SetBinLabel(1,"N left  Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(2,"N right Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(3,"P left  Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(4,"P right Total number of PEs");
  //[L/R][Primary/NonPrimary/All]
  TH1D *hpe[2][3],*posPE[2][3],*angPE[2][3],*phiPE[2][3],*hpeAvg[2][3];
  for(int i=0;i<2;i++)
    for(int j=0;j<3;j++){
      hpe[i][j]=new TH1D(Form("hpe_%s_%s",lr[i].c_str(),species[j].c_str()),
			 Form("%s %s;number of PEs",lr[i].c_str(),species[j].c_str()),
			 300,0,300);
      double showerFactor(1);
      if(j!=1) showerFactor=20;
      hpeAvg[i][j]=new TH1D(Form("hpeAvg_%s_%s",lr[i].c_str(),species[j].c_str()),
			    Form("1k ev Avg %s %s;number of PEs",lr[i].c_str(),species[j].c_str()),
			    600,0,maxAvg*showerFactor);

      posPE[i][j]=new TH1D(Form("posPE_%s_%s",lr[i].c_str(),species[j].c_str()),
			   Form("%s %s;position along bar[cm]",lr[i].c_str(),species[j].c_str()),
			   400,-100,100);
      
      angPE[i][j]=new TH1D(Form("angPE_%s_%s",lr[i].c_str(),species[j].c_str()),
			   Form("%s %s;angle in shower [deg]",lr[i].c_str(),species[j].c_str()),
			   400,-100,100);      

      phiPE[i][j]=new TH1D(Form("phiPE_%s_%s",lr[i].c_str(),species[j].c_str()),
			   Form("%s %s;global phi [deg]",lr[i].c_str(),species[j].c_str()),
			   400,0,400);      
    }

  double TotPE[2][2]={{0,0},{0,0}};
  double AvgPE[2][2]={{0,0},{0,0}};

  int stepEvNr(0),prevEvNr(0),currEvNr(0),realEvNr(0),nrFiles(0),recordNr(1000);
  float startProc=0,stopProc=15,currentProc=0,procStep=10;
  int nev=t->GetEntries();
  for(int i=0;i<nev;i++){
    if( float(i+1)/nev*100 > currentProc ){
      cout<<" at event: "<<i<<"\t"<<float(i+1)/nev*100<<"%"<<endl;
      currentProc+=procStep;
    }
    //if( i>500000) break;
    //if( float(i+1)/nev*100<startProc || float(i+1)/nev*100>stopProc ) continue;

    t->GetEntry(i);
    
    if( i>0 )
      prevEvNr=currEvNr;
    currEvNr=evNr;
    if( evNr<prevEvNr )
      stepEvNr += std::ceil(prevEvNr/100.)*100;
    realEvNr=evNr+stepEvNr;

    if(realEvNr>recordNr){
      recordNr+=1000;
      for(int j=0;j<2;j++){
	for(int k=0;k<2;k++){
	  hpeAvg[j][k]->Fill(AvgPE[k][j]/1000.);	  
	}
	hpeAvg[j][2]->Fill((AvgPE[0][j]+AvgPE[1][j])/1000.);
      }

      for(int j=0;j<2;j++)
	for(int k=0;k<2;k++)
	  AvgPE[j][k]=0;
    }
    
    float flip(1.);
    if(distModel == "mirror")
      flip=-1.;

    double pes[2]={0,0};
    if(barModel == "tracks"){
      if(x>0) pes[0]=1;
      else if(x<0) pes[1]=1;
    }else{
      if(!interpolator.getPEs(E,flip*x,flip*angX,pes[0],pes[1])) continue;
    }
    
    for(int j=0;j<2;j++){
      TotPE[primary][j]+=pes[j];
      AvgPE[primary][j]+=pes[j];
      
      hpe[j][primary]->Fill(pes[j]);
      posPE[j][primary]->Fill(x,pes[j]);
      angPE[j][primary]->Fill(angX-angXi,pes[j]);
      
      hpe[j][2]->Fill(pes[j]);
      posPE[j][2]->Fill(x,pes[j]);
      angPE[j][2]->Fill(angX-angXi,pes[j]);

      if(fillPhi){
	double tmpPhi= phi < 0 ? 360 + phi : phi;
	phiPE[j][primary]->Fill(tmpPhi,pes[j]);
	phiPE[j][2]->Fill(tmpPhi,pes[j]);
      }      
    }
    
    
  }

  for(int j=0;j<2;j++)
    for(int k=0;k<2;k++){
      hTotPE->SetBinContent(j*2+k+1,TotPE[j][k]);
    }

  fout->cd();
  hTotPE->Write();
  for(int i=0;i<2;i++)
    for(int j=0;j<3;j++){
      hpe[i][j]->Write();
      hpeAvg[i][j]->Write();
      posPE[i][j]->Write();
      angPE[i][j]->Write();
      phiPE[i][j]->Write();
    }
  
  fout->Close();

}
