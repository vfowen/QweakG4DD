#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "QweakSimUserMainEvent.hh"
#include "QweakSimSystemOfUnits.hh"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TGraph.h"
#include "TGraphErrors.h"

using namespace std;
float calcAsym(int posAng,float val);
TGraph *singleAsym;
TGraphErrors *posAsym;
TGraph       *angAsym;

int main(int argc, char** argv)
{
  if(argc < 3 || argc > 4 ) {
    cout<<" usage: build/QweakAna [detector number] [path to infile with list of output QweakSimG4 trees] [optional: E cut]"<<endl;
    return 1;
  }
  float nDet=atoi(argv[1]);
  string files(argv[2]);
  float Ecut=0;
  if(argc == 4) Ecut=atof(argv[3]);

  TFile *finAsym=TFile::Open("output/o_PEasyms.root","READ");
  posAsym=(TGraphErrors*)finAsym->Get("asym_9");
  angAsym=(TGraph*)      finAsym->Get("angle");
  
  
  TFile *fout=new TFile(Form("o_dist_asym_%04.2Ecut.root",Ecut),"RECREATE");
  
  TH1F *distXposPe =new TH1F("distXposPe" ,"X position distribution primary e-;x pos [cm]",200,-100,100);
  TH1F *distXposNPe=new TH1F("distXposNPe","X position distribution All e;x pos [cm]"     ,200,-100,100);
  TH1F *distXposPh =new TH1F("distXposPh" ,"X position distribution photons;x pos [cm]"   ,200,-100,100);

  TH1F *distXangPe =new TH1F("distXangPe" ,"Angle along X distribution primary e-;ang X [deg]",180,-90,90);
  TH1F *distXangNPe=new TH1F("distXangNPe","Angle along X distribution All e;ang X [deg]"     ,180,-90,90);
  TH1F *distXangPh =new TH1F("distXangPh" ,"Angle along X distribution photons;ang X [deg]"   ,180,-90,90);

  TH1F *asymXposPe =new TH1F("asymXposPe" ,"DD Asymmetry for X position deviation primary e-",200,-1,1);
  TH1F *asymXposNPe=new TH1F("asymXposNPe","DD Asymmetry for X position deviation all e"     ,200,-1,1);

  TH1F *asymXangPe =new TH1F("asymXangPe" ,"DD Asymmetry for angle deviation primary e-",200,-1,1);
  TH1F *asymXangNPe=new TH1F("asymXangNPe","DD Asymmetry for angle deviation all e"     ,200,-1,1);
  
  ifstream ifile(files.c_str());
  string data;

  while(ifile>>data){
    TFile *fin=TFile::Open(data.c_str());
    TTree *QweakSimG4_Tree=(TTree*)fin->Get("QweakSimG4_Tree");
    cout<<"processing : "<<data.c_str()<<" for detector "<<nDet<<" with E cut "<<Ecut<<endl;    
    
    //set addresses of leafs
    QweakSimUserMainEvent* event = 0;
    QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);
    cout<<" total nr ev: "<<QweakSimG4_Tree->GetEntries()<<endl;
    
    for (int i = 0; i < QweakSimG4_Tree->GetEntries(); i++) {
      QweakSimG4_Tree->GetEntry(i);
      if(i%10000==1) cout<<"   at event: "<<i<<endl;
      
      for (int hit = 0; hit < event->Cerenkov.Detector.GetDetectorNbOfHits(); hit++) {	
	if(event->Cerenkov.Detector.GetDetectorID()[hit]!=nDet) continue;
	int pTypeHit=event->Cerenkov.Detector.GetParticleType()[hit];
	if(abs(pTypeHit)!=11  && abs(pTypeHit)!=22 ) continue;
	float E=event->Cerenkov.Detector.GetTotalEnergy()[hit];
	if(E<Ecut) continue;
	
	float x=event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit];
	
	double Gphi   = event->Cerenkov.Detector.GetGlobalPhiAngle()[hit];
	double Gtheta = event->Cerenkov.Detector.GetGlobalThetaAngle()[hit];	

	double _Gtheta=Gtheta/180.*pi;
	double _Gphi=(Gphi+90)/180.*pi; //+90 to account for the offset in the output

	float angX = atan2(sin(_Gtheta)*cos(_Gphi),cos(_Gtheta)) * 180.0 / pi;

	int parentID=event->Cerenkov.Detector.GetParentID()[hit];
	int tID     =event->Cerenkov.Detector.GetParticleID()[hit];
	
	if(abs(pTypeHit)==22){ //
	  distXposPh->Fill(x);
	  distXangPh->Fill(angX);
	}else if(abs(pTypeHit)==11){
	  double posAsymV=calcAsym(0,x);
	  double angAsymV=calcAsym(1,angX);
	  
	  if(tID==1 && parentID==0){ //primary
	    distXposPe->Fill(x);
	    distXangPe->Fill(angX);
	    asymXposPe->Fill(posAsymV);
	    asymXangPe->Fill(angAsymV);
	  }
	  distXposNPe->Fill(x);
	  distXangNPe->Fill(angX);
	  asymXposNPe->Fill(posAsymV);
	  asymXangNPe->Fill(angAsymV);	    
	}
      }
    }
    
    cout<<"Done looping!"<<endl;
    fin->Close();
  }

  fout->cd();
  distXposPe ->Write();
  distXposPh ->Write();
  distXposNPe->Write();
  distXangPe ->Write();
  distXangPh ->Write();
  distXangNPe->Write();
  
  asymXposPe ->Write();
  asymXposNPe->Write();
  asymXangPe ->Write();
  asymXangNPe->Write();
  fout->Close();
  finAsym->Close();  
  ifile.close();
  return 0;
}

float calcAsym(int posAng,float val){
  if(posAng==0)      singleAsym=posAsym;
  else if(posAng==1) singleAsym=angAsym;

  double asym=-2;
  if( (posAng==0 && fabs(val)<20) || (posAng==1 && fabs(val)<45) )
    asym=singleAsym->Eval(val,0,"S");
  else if(posAng==1 && fabs(val)>=45)
    asym=0.90;
  
  return asym;
}

