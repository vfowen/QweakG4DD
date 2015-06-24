// Author Ciprian
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

using namespace std;
int findInt(std::vector<int> &inter,std::vector<int> &val, int check, int parent, int &hasPar);

int main(int argc, char** argv)
{
  if(argc != 3) {
    cout<<" run as: build/QweakTreeStrip [detector number] [path to infile with list of output QweakSimG4 trees] "<<endl;
    return 1;
  }
  int ndet=atoi(argv[1]);
  string files(argv[2]);

  ifstream ifile(files.c_str());
  char _data[500];

  while(ifile>>_data){
    TFile *fin=TFile::Open(_data);
    TTree *QweakSimG4_Tree=(TTree*)fin->Get("QweakSimG4_Tree");
    cout<<"processing : "<<_data<<" for detector "<<ndet<<endl;
    
    
    //set addresses of leafs
    QweakSimUserMainEvent* event = 0;
    QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);
    
    //hit
    int evNr;
    int hitNr;
    int pTypeHit;
    float x,y,z;
    float px,py,pz;
    float Gphi,Gtheta;
    float Lphi,Ltheta;
    float vRel;
    float E;
    float angX, angY;
    int nInt;
    int hasParent;
    int tID;
    int _parentID;
    
    //event
    float LnPMThit,RnPMThit;
    float LEtot,REtot;
    float gLEtot,gREtot;
    float gasymE;
    float asymE,asymPMT;
    float polx,poly,polz;
    
    TString onm(_data);
    onm.Remove(onm.Last('/'),onm.Length());
    TFile *fout=new TFile(Form("%s/o_anaTree.root",onm.Data()),"RECREATE");
    TTree *th=new TTree("th","Stripped QweakSimG4 tree for hits");
    th->Branch("evNr",&evNr,"evNr/I");
    th->Branch("hitNr",&hitNr,"hitNr/I");
    th->Branch("pType",&pTypeHit,"pType/I");
    th->Branch("tID",&tID,"tID/I");
    th->Branch("parentID",&_parentID,"parentID/I");
    th->Branch("nInt",&nInt,"nInt/I");
    th->Branch("hasParent",&hasParent,"hasParent/I");
    th->Branch("x",&x,"x/F");
    th->Branch("y",&y,"y/F");
    th->Branch("z",&z,"z/F");
    th->Branch("px",&x,"px/F");
    th->Branch("py",&y,"py/F");
    th->Branch("pz",&z,"pz/F");
    th->Branch("angY",&angY,"angY/F");
    th->Branch("angX",&angX,"angX/F");
    th->Branch("Gph",&Gphi,"Gph/F");
    th->Branch("Lph",&Lphi,"Lph/F");
    th->Branch("Gth",&Gtheta,"Gth/F");
    th->Branch("Lth",&Ltheta,"Lth/F");
    th->Branch("vRel",&vRel,"vRel/F");
    th->Branch("E",&E,"E/F");
    th->Branch("polx",&polx,"polx/F");
    th->Branch("poly",&poly,"poly/F");
    th->Branch("polz",&polz,"polz/F");
    
    TTree *te=new TTree("te","Event level info for e#pm");
    te->Branch("evNr",&evNr,"evNr/I");
    te->Branch("LnPMThit",&LnPMThit,"LnPMThit/F");
    te->Branch("RnPMThit",&RnPMThit,"RnPMThit/F");
    te->Branch("LEtot",&LEtot,"LEtot/F");
    te->Branch("REtot",&REtot,"REtot/F");
    te->Branch("gLEtot",&gLEtot,"gLEtot/F");
    te->Branch("gREtot",&gREtot,"gREtot/F");
    te->Branch("gasymE",&gasymE,"gasymE/F");
    te->Branch("asymE",&asymE,"asymE/F");
    te->Branch("asymPMT",&asymPMT,"asymPMT/F");
    
    double cutoff=1./1.458;
    double emass=0.510998910;//MeV
    
    cout<<" total nr ev: "<<QweakSimG4_Tree->GetEntries()<<endl;
    std::vector<int> interaction;
    std::vector<int> trackID;
    double pi=3.14159265358979323846;
    
    for (int i = 0; i < QweakSimG4_Tree->GetEntries(); i++) {
      QweakSimG4_Tree->GetEntry(i);
      if(i%10000==1) cout<<" at event: "<<i<<endl;
      //loop over hits
      LnPMThit=-2;
      RnPMThit=-2;
      asymE=-2;
      asymPMT=-2;
      gasymE=-2;
      gLEtot=0;
      gREtot=0;
      LEtot=0;
      REtot=0;
      evNr  = event->Primary.GetPrimaryEventNumber();
      //cout<<" interaction trackid "<<interaction.size()<<" "<<trackID.size()<<endl;
      interaction.clear();
      trackID.clear();
      
      for (int hit = 0; hit < event->Cerenkov.Detector.GetDetectorNbOfHits(); hit++) {
	if(event->Cerenkov.Detector.GetDetectorID()[hit]!=ndet) continue;
	pTypeHit=event->Cerenkov.Detector.GetParticleType()[hit];
	if(abs(pTypeHit)!=11  && abs(pTypeHit)!=22 ) continue;
	
	tID=event->Cerenkov.Detector.GetParticleID()[hit];
	nInt=findInt(interaction,trackID,tID,event->Cerenkov.Detector.GetParentID()[hit],hasParent);
	hitNr = hit;
	_parentID=event->Cerenkov.Detector.GetParentID()[hit];
	
	x=event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit];
	y=event->Cerenkov.Detector.GetDetectorGlobalPositionY()[hit];
	z=event->Cerenkov.Detector.GetDetectorGlobalPositionZ()[hit];
	
	px=event->Cerenkov.Detector.GetGlobalMomentumX()[hit];
	py=event->Cerenkov.Detector.GetGlobalMomentumY()[hit];
	pz=event->Cerenkov.Detector.GetGlobalMomentumZ()[hit];
	
	polx=event->Cerenkov.Detector.GetPolarizationX()[hit];
	poly=event->Cerenkov.Detector.GetPolarizationY()[hit];
	polz=event->Cerenkov.Detector.GetPolarizationZ()[hit];
      
	E=event->Cerenkov.Detector.GetTotalEnergy()[hit];
	
	float _p=sqrt(pow(px,2)+pow(py,2)+pow(pz,2));
	vRel=sqrt(pow(_p,2)/(pow(emass,2)+pow(_p,2)));// relativistic velocity /c which should be compared to 1/refractive index
	
	Gphi   = event->Cerenkov.Detector.GetGlobalPhiAngle()[hit];
	Gtheta = event->Cerenkov.Detector.GetGlobalThetaAngle()[hit];
	
	double _Gtheta=Gtheta/180.*pi;
	double _Gphi=(Gphi+90)/180.*pi; //+90 to account for the offset in the output
	angY = atan2(sin(_Gtheta)*sin(_Gphi),cos(_Gtheta)) * 180.0 / pi;
	angX = atan2(sin(_Gtheta)*cos(_Gphi),cos(_Gtheta)) * 180.0 / pi;
	
	Lphi   = event->Cerenkov.Detector.GetLocalPhiAngle()[hit];
	Ltheta = event->Cerenkov.Detector.GetLocalThetaAngle()[hit];
	
	if(vRel>cutoff && abs(pTypeHit)==11 && z>577.6){ //over cerenkov th, electrons, in the qurtz
	  if(x>0) REtot+=E;
	  else LEtot+=E;
	}
	
	if(z>577.6 && pTypeHit==22){
	  if(x>0) gREtot+=E;
	  else gLEtot+=E;
	}
	th->Fill();
      }
      
      if(event->Cerenkov.PMT.GetDetectorNbOfHits()>0){
	LnPMThit=event->Cerenkov.PMT.GetPMTLeftNbOfHits()[ndet];//is the same as NbOfPEs
	RnPMThit=event->Cerenkov.PMT.GetPMTRightNbOfHits()[ndet];
      }
      
      if( LnPMThit!=-2 && RnPMThit!=-2 && (LnPMThit+RnPMThit)>0 ) asymPMT=(LnPMThit-RnPMThit)/(LnPMThit+RnPMThit);
      if( LEtot!=0 && REtot!=0 && (LEtot + REtot)>0 ) asymE=(LEtot - REtot)/(LEtot + REtot);
      if( gLEtot!=0 && gREtot!=0 && (gLEtot + gREtot)>0 ) gasymE=(gLEtot - gREtot)/(gLEtot + gREtot);
      //if( asymE>1 || asymE < -1 ) cout<<LEtot<<" "<<REtot<<" "<<(LEtot - REtot)<<" "<<(LEtot + REtot)<<" "<<asymE<<endl;
      te->Fill();
    }
    
    cout<<"Done loop writting out!"<<endl;
    th->Write();
    te->Write();
    fout->Close();
  }

  ifile.close();
  return 0;
}

int findInt(std::vector<int> &inter,std::vector<int> &val, int check,int parent, int &hasPar){
  int found=0;
  int ret=-1;
  int findParent=0;
  for(unsigned int i=0;i<val.size();i++){
    if(check==val[i]){
      inter[i]++;
      ret=inter[i];
      found++;
    }
    if(parent==val[i])
      findParent++;
  }
  
  if(findParent) hasPar=1;
  else hasPar=0;
  
  if(!found){
    val.push_back(check);
    inter.push_back(1);
    ret=1;
  }
  if(found>1){
    cout<<"multiple entries for track "<<check<<endl;
  }
  return ret;
}

