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
void processOne(TTree *QweakSimG4_Tree,double &LnPMThit,double &RnPMThit, int ndet);

int main(int argc, char** argv)
{
  if(argc != 3) {
    cout<<" run as: build/QweakGetPEs [detector number] [path to QweakSimG4 output file or to infile with list of output QweakSimG4 trees] "<<endl;
    return 1;
  }
  int ndet=atoi(argv[1]);
  string files(argv[2]);

  double lTotPE(0),rTotPE(0);
  double LnPMThit(0),RnPMThit(0),asymPMT(0);
  
  TFile *fout=new TFile("o_QweakSimTree_PEs.root","RECREATE");
  
  TH1D *lpe=new TH1D("lpe","left  nb of PEs per event",500,0,500); 
  TH1D *rpe=new TH1D("rpe","right nb of PEs per event",500,0,500); 

  if ( files.find(".root") < files.size() ){
    TFile *fin=new TFile(files.c_str(),"READ");
    if(!fin->IsOpen()){
      cout<<"Problem: can't find file: "<<files<<endl;
      fout->Close();
      return -3;
    }
    
    TTree *QweakSimG4_Tree=(TTree*)fin->Get("QweakSimG4_Tree");
    cout<<"processing only one file:QweakGetPEs 3 QwSim_0.root "<<files.c_str()<<" for detector "<<ndet<<endl;        
    cout<<" total nr ev: "<<QweakSimG4_Tree->GetEntries()<<endl;
    
    processOne(QweakSimG4_Tree,LnPMThit,RnPMThit,ndet);
    lpe->Fill(LnPMThit);
    rpe->Fill(RnPMThit);
    lTotPE+=LnPMThit;
    rTotPE+=RnPMThit;      
    fin->Close();
    delete fin;
  }else{  
    ifstream ifile(files.c_str());
    char _data[500];
    while(ifile>>_data){
      TFile *fin=TFile::Open(_data);
      TTree *QweakSimG4_Tree=(TTree*)fin->Get("QweakSimG4_Tree");
      cout<<"processing : "<<_data<<" for detector "<<ndet<<endl;

      processOne(QweakSimG4_Tree,LnPMThit,RnPMThit,ndet);
      lTotPE+=LnPMThit;
      rTotPE+=RnPMThit;          
    }
    cout<<"Done loop writting out!"<<endl;
    ifile.close();
  }


  fout->cd();
  lpe->Write();
  rpe->Write();
  fout->Close();
  cout<<"Total number of PEs: "<<setprecision(12)<<lTotPE<<" "<<rTotPE<<endl;
  
  return 0;
}


void processOne(TTree *QweakSimG4_Tree,double &LnPMThit,double &RnPMThit, int ndet){

  double Right, Left;
  int nhits = 0;

  QweakSimUserMainEvent* event = 0;
  QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);
      
  for (int i = 0; i < QweakSimG4_Tree->GetEntries(); i++) {

    QweakSimG4_Tree->GetEntry(i);
    if(i%1000==1) cout<<" at event: "<<i<<endl;
    
    if(event->Cerenkov.PMT.GetDetectorNbOfHits()>0){
      nhits++;
      //      LnPMThit=event->Cerenkov.PMT.GetPMTLeftNbOfHits()[ndet];//is the same as NbOfPEs
      //      RnPMThit=event->Cerenkov.PMT.GetPMTRightNbOfHits()[ndet];
      Left=event->Cerenkov.PMT.GetPMTLeftNbOfHits()[ndet];//is the same as NbOfPEs
      Right=event->Cerenkov.PMT.GetPMTRightNbOfHits()[ndet];
      RnPMThit = RnPMThit+Right;
      LnPMThit = LnPMThit+Left;
    }      
  }
  if (nhits>0){
    RnPMThit = RnPMThit/nhits;
    LnPMThit = LnPMThit/nhits;
    cout << "nhits = " << nhits << "   Avg left =  " << LnPMThit << " Avg right = " << RnPMThit << endl;
  }
}
