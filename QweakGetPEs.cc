#include <string.h>
#include "stdio.h"
#include "iostream"
#include <iomanip>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "QweakSimUserMainEvent.hh"
#include "math.h"
#include "stdlib.h"
#include "TString.h"
#include "TH1D.h"

using namespace std;

int main(int argc, char** argv)
{
  if(argc != 3) {
    cout<<" run as: build/QweakGetPEs [detector number] [path to infile with list of output QweakSimG4 trees] "<<endl;
    return 1;
  }
  int ndet=atoi(argv[1]);
  string files(argv[2]);

  ifstream ifile(files.c_str());
  char _data[500];

  double lTotPE(0),rTotPE(0);
  double LnPMThit(0),RnPMThit(0),asymPMT(0);
  
  TFile *fout=new TFile("o_QweakSimTree_PEs.root","RECREATE");
  
  TH1D *lpe=new TH1D("lpe","left  nb of PEs per event",500,0,500); 
  TH1D *rpe=new TH1D("rpe","right nb of PEs per event",500,0,500); 
  TH1D *asymPE=new TH1D("asymPE","PE asym",201,-1.,1.01);
  
  while(ifile>>_data){
    TFile *fin=TFile::Open(_data);
    TTree *QweakSimG4_Tree=(TTree*)fin->Get("QweakSimG4_Tree");
    cout<<"processing : "<<_data<<" for detector "<<ndet<<endl;
        
    //set addresses of leafs
    QweakSimUserMainEvent* event = 0;
    QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);
    
    for (int i = 0; i < QweakSimG4_Tree->GetEntries(); i++) {
      QweakSimG4_Tree->GetEntry(i);
      if(i%10000==1) cout<<" at event: "<<i<<endl;
      //loop over hits
      LnPMThit=-2;
      RnPMThit=-2;
      asymPMT=-2;
      
      if(event->Cerenkov.PMT.GetDetectorNbOfHits()>0){
	LnPMThit=event->Cerenkov.PMT.GetPMTLeftNbOfHits()[ndet];//is the same as NbOfPEs
	RnPMThit=event->Cerenkov.PMT.GetPMTRightNbOfHits()[ndet];
	lpe->Fill(LnPMThit);
	rpe->Fill(RnPMThit);
	lTotPE+=LnPMThit;
	rTotPE+=RnPMThit;      
      }      
      
      if( LnPMThit!=-2 && RnPMThit!=-2 && (LnPMThit+RnPMThit)>0 ){
	asymPMT=(LnPMThit-RnPMThit)/(LnPMThit+RnPMThit);
	asymPE->Fill(asymPMT);
      }
    }
    
    cout<<"Done loop writting out!"<<endl;
  }

  fout->cd();
  lpe->Write();
  rpe->Write();
  asymPE->Write();
  fout->Close();
  cout<<"Total number of PEs: "<<setprecision(12)<<lTotPE<<" "<<rTotPE<<endl;
  
  ifile.close();
  return 0;
}
