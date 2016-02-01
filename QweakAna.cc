#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "QweakSimUserMainEvent.hh"
#include "QweakSimSystemOfUnits.hh"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

using namespace std;

TH3D *distPe,*distAe,*distPh;
TH2D *distLongPolLogE,*distTranPolLogE;
TH1D *distElog[3];
TH1D *distE[3];

void findInt(std::vector<int> &inter,std::vector<int> &val, int trackID,int parent, int &hasPar, int &nInt);
void processOne(TTree *QweakSimG4_Tree);
int nDet(-2);

int main(int argc, char** argv)
{

  if( argc < 3 ) {
    cout<<" usage: build/QweakAna [detector number] [path to infile with list of output QweakSimG4 trees] [optional - number of events]"<<endl;
    return 1;
  }

  nDet=atoi(argv[1]);
  string files(argv[2]);
  int defEvts=-1;

  if(argc == 4)
    defEvts=atoi(argv[3]);

  TFile *fout=new TFile("o_dist.root","RECREATE");  

  TH1I *hNev=new TH1I("hNev","total number of events processed",1,0,1);

  distPe=new TH3D("distPe","Primary distribution;position [cm]; angle [deg]; E [MeV]",
  		201,-100.5,100.5,
  		180,-90,90,
  		301,0,301);

  distAe=new TH3D("distAe","All e distribution;position [cm]; angle [deg]; E [MeV]",
  		201,-100.5,100.5,
  		180,-90,90,
  		301,0,301);
  
  distPh=new TH3D("distPh","Photon distribution;position [cm]; angle [deg]; E [MeV]",
			201,-100.5,100.5,
			180,-90,90,
			301,0,301);
  
  distLongPolLogE=new TH2D("distLongPolLogE",";longitudinal Polarization[%]; log10(E) [MeV]",
			   100,0,100,200,-1.3,3.5);
  distTranPolLogE=new TH2D("distTranPolLogE",";transverse   Polarization[%]; log10(E) [MeV]",
			   100,0,100,200,-1.3,3.5);

  string part[3]={"Pe","Ae","Ph"};
  string partTit[3]={"Primary e-","All e","Photons"};
  for(int i=0;i<3;i++){
    distElog[i]=new TH1D(Form("distElog_%s",part[i].c_str()),Form("%s;log10(E) [MeV]",partTit[i].c_str()),200,-1,3.5);
    distE[i]=new TH1D(Form("distE_%s",part[i].c_str()),Form("%s;E [MeV]",partTit[i].c_str()),200,0,1200);
  }

  int totEv=0;
  if ( files.find(".root") < files.size() ){
    TFile *fin=new TFile(files.c_str(),"READ");
    if(!fin->IsOpen()){
      cout<<"Problem: can't find file: "<<files<<endl;
      fout->Close();
      return -3;
    }

    TTree *QweakSimG4_Tree=(TTree*)fin->Get("QweakSimG4_Tree");
    cout<<"processing only one file: "<<files.c_str()<<" for detector "<<nDet<<endl;    
    
    int evts=QweakSimG4_Tree->GetEntries();
    totEv+=evts;
    cout<<" total nr ev: "<<evts<<" "<<totEv<<endl;
    
    processOne(QweakSimG4_Tree);
    
    cout<<"Done looping!"<<endl;
    fin->Close();
    delete fin;
  }else{
    ifstream ifile(files.c_str());
    string data;
    while(ifile>>data){
      TFile *fin=new TFile(files.c_str(),"READ");
      if(!fin->IsOpen()){
	cout<<"Problem: can't find file: "<<data<<endl;
	continue;
      }
      TTree *QweakSimG4_Tree=(TTree*)fin->Get("QweakSimG4_Tree");
      cout<<"processing : "<<data.c_str()<<" for detector "<<nDet<<endl;          
      int evts=QweakSimG4_Tree->GetEntries();
      if( evts != defEvts && defEvts != -1){
	cout<<"  skipping this file #ev is "<<evts<<" should be "<<defEvts<<endl;
	fin->Close();
	continue;
      }
      totEv+=evts;
      cout<<" total nr ev: "<<evts<<" "<<totEv<<endl;      
      processOne(QweakSimG4_Tree);      
      cout<<"Done looping!"<<endl;
      fin->Close();
      delete fin;
    }
    ifile.close();
  }
  
  cout<<"Processed "<<totEv<<" events"<<endl;
  
  fout->cd();
  hNev->SetBinContent(1,totEv);
  hNev->Write();

  distPe->Write();
  distAe->Write();
  distPh->Write();

  distLongPolLogE->Write();
  distTranPolLogE->Write();

  for(int i=0;i<3;i++){
    distE[i]->Write();
    distElog[i]->Write();    
  }
  fout->Close();
  return 0;
}

void processOne(TTree *QweakSimG4_Tree){

  std::vector<int> interaction;
  std::vector<int> trackID;

  //set addresses of leafs
  QweakSimUserMainEvent* event = 0;
  QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);    

  for (int i = 0; i < QweakSimG4_Tree->GetEntries(); i++) {
    QweakSimG4_Tree->GetEntry(i);
    if(i%10000==1) cout<<"   at event: "<<i<<endl;
    
    interaction.clear();
    trackID.clear();
    
    for (int hit = 0; hit < event->Cerenkov.Detector.GetDetectorNbOfHits(); hit++) {	
      if(event->Cerenkov.Detector.GetDetectorID()[hit]!=nDet) continue;
      int pTypeHit=event->Cerenkov.Detector.GetParticleType()[hit];
      if(abs(pTypeHit)!=11  && abs(pTypeHit)!=22 ) continue;
      double E=event->Cerenkov.Detector.GetTotalEnergy()[hit];
      
      int parentID=event->Cerenkov.Detector.GetParentID()[hit];
      int tID     =event->Cerenkov.Detector.GetParticleID()[hit];
      
      int hasParent(-1),nInt(-1);
      findInt(interaction,trackID,tID,parentID,hasParent,nInt);
      if(nInt!=1 || hasParent==1) continue;
      
      if(abs(pTypeHit)==22){ //photons
	distElog[2]->Fill(log10(E));
	distE[2]->Fill(E);
      }else{//electrons
	distElog[1]->Fill(log10(E));
	distE[1]->Fill(E);
	if(tID==1 && parentID==0){ //primary
	  distElog[0]->Fill(log10(E));
	  distE[0]->Fill(E);
	  double polX=event->Cerenkov.Detector.GetPolarizationX()[hit];
	  double polY=event->Cerenkov.Detector.GetPolarizationY()[hit];
	  double polZ=event->Cerenkov.Detector.GetPolarizationZ()[hit];
	  distTranPolLogE->Fill(sqrt(polX*polX+polY*polY)*100.,log10(E));
	  distLongPolLogE->Fill(polZ*100.,log10(E));
	}
      }
      
      double x=event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit];
      
      double Gphi   = event->Cerenkov.Detector.GetGlobalPhiAngle()[hit];
      double Gtheta = event->Cerenkov.Detector.GetGlobalThetaAngle()[hit];	
      double _Gtheta=Gtheta/180.*pi;
      double _Gphi=(Gphi+90)/180.*pi; //+90 to account for the offset in the output
      double angX = atan2(sin(_Gtheta)*cos(_Gphi),cos(_Gtheta)) * 180.0 / pi;
      
      if(fabs(angX)>90) continue;
      
      double histE= ( E>300 ) ? 300.5 : E;
      if(abs(pTypeHit)==22){ //photons
	distPh->Fill(x,angX,histE);
      }else if(abs(pTypeHit)==11){ //electrons
	distAe->Fill(x,angX,histE);
	
	if(tID==1 && parentID==0) //primary
	  distPe->Fill(x,angX,histE);
      }
      
    }//nhit
  }//tree entries
}


void findInt(std::vector<int> &inter,std::vector<int> &val, int trackID,int parent, int &hasPar, int &nInt){
  int found=0;
  nInt=-2;
  int findParent=0;
  for(unsigned int i=0;i<val.size();i++){
    if(trackID==val[i]){
      inter[i]++;
      nInt=inter[i];
      found++;
    }
    if(parent==val[i])
      findParent++;
  }
  
  if(findParent) hasPar=1;
  else hasPar=0;
  
  if(!found){
    val.push_back(trackID);
    inter.push_back(1);
    nInt=1;
  }
  if(found>1){
    cout<<"multiple entries for track "<<trackID<<endl;
  }
}
