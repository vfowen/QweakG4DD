#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "QweakSimUserMainEvent.hh"
#include "QweakSimSystemOfUnits.hh"
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TGraph.h"
#include "TGraphErrors.h"

using namespace std;
void findInt(std::vector<int> &inter,std::vector<int> &val, int trackID,int parent, int &hasPar, int &nInt);
double calcAsym(int posAng,double val);
TGraph *singleAsym;
TGraphErrors *posAsym;
TGraph       *angAsym;

int main(int argc, char** argv)
{
  if(argc < 3 || argc > 4 ) {
    cout<<" usage: build/QweakAna [detector number] [path to infile with list of output QweakSimG4 trees] [optional: E cut]"<<endl;
    return 1;
  }
  double nDet=atoi(argv[1]);
  string files(argv[2]);
  double Ecut=0;
  if(argc == 4) Ecut=atof(argv[3]);

  TFile *finAsym=TFile::Open("output/o_PEasyms.root","READ");
  posAsym=(TGraphErrors*)finAsym->Get("asym_9");
  angAsym=(TGraph*)      finAsym->Get("angle");
  
  
  TFile *fout=new TFile(Form("o_dist_asym_%04.2fEcut.root",Ecut),"RECREATE");
  
  TH1D *distXposPe =new TH1D("distXposPe" ,"X position distribution primary e-;x pos [cm]",200,-100,100);
  TH1D *distXposNPe=new TH1D("distXposNPe","X position distribution All e;x pos [cm]"     ,200,-100,100);
  TH1D *distXposPh =new TH1D("distXposPh" ,"X position distribution photons;x pos [cm]"   ,200,-100,100);

  TH1D *distXangPe =new TH1D("distXangPe" ,"Angle along X distribution primary e-;ang X [deg]",180,-90,90);
  TH1D *distXangNPe=new TH1D("distXangNPe","Angle along X distribution All e;ang X [deg]"     ,180,-90,90);
  TH1D *distXangPh =new TH1D("distXangPh" ,"Angle along X distribution photons;ang X [deg]"   ,180,-90,90);

  TH1D *asymXposPe =new TH1D("asymXposPe" ,"DD Asymmetry for X position deviation primary e-",200,-1,1);
  TH1D *asymXposNPe=new TH1D("asymXposNPe","DD Asymmetry for X position deviation all e"     ,200,-1,1);

  TH1D *asymXangPe =new TH1D("asymXangPe" ,"DD Asymmetry for angle deviation primary e-",200,-1,1);
  TH1D *asymXangNPe=new TH1D("asymXangNPe","DD Asymmetry for angle deviation all e"     ,200,-1,1);
  
  ifstream ifile(files.c_str());
  string data;
  std::vector<int> interaction;
  std::vector<int> trackID;
    
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

      interaction.clear();
      trackID.clear();
      
      for (int hit = 0; hit < event->Cerenkov.Detector.GetDetectorNbOfHits(); hit++) {	
	if(event->Cerenkov.Detector.GetDetectorID()[hit]!=nDet) continue;
	int pTypeHit=event->Cerenkov.Detector.GetParticleType()[hit];
	if(abs(pTypeHit)!=11  && abs(pTypeHit)!=22 ) continue;
	double E=event->Cerenkov.Detector.GetTotalEnergy()[hit];
	if(E<Ecut) continue;

	int parentID=event->Cerenkov.Detector.GetParentID()[hit];
	int tID     =event->Cerenkov.Detector.GetParticleID()[hit];

	int hasParent(-1),nInt(-1);
	findInt(interaction,trackID,tID,parentID,hasParent,nInt);
	if(nInt!=1 || hasParent==1) continue;
	
	double x=event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit];
	
	double Gphi   = event->Cerenkov.Detector.GetGlobalPhiAngle()[hit];
	double Gtheta = event->Cerenkov.Detector.GetGlobalThetaAngle()[hit];	

	double _Gtheta=Gtheta/180.*pi;
	double _Gphi=(Gphi+90)/180.*pi; //+90 to account for the offset in the output

	double angX = atan2(sin(_Gtheta)*cos(_Gphi),cos(_Gtheta)) * 180.0 / pi;

	if(fabs(angX)>90) continue;
	
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

double calcAsym(int posAng,double val){
  if(posAng==0)      singleAsym=posAsym;
  else if(posAng==1) singleAsym=angAsym;

  double asym=-2;
  if( (posAng==0 && fabs(val)<20) || (posAng==1 && fabs(val)<45) )
    asym=singleAsym->Eval(val,0,"S");
  else if(posAng==1 && fabs(val)>=45)
    asym=0.90*val/fabs(val);

  if(asym>0.9) cout<<"calcAsym: " <<posAng<<" "<<val<<" "<<asym<<endl;
  return asym;
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
