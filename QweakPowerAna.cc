#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "QweakSimUserMainEvent.hh"
#include "QweakSimSystemOfUnits.hh"
#include "TFile.h"
#include "TTree.h"

using namespace std;

int main(int argc, char** argv)
{

  if( argc < 3 ) {
    cout<<" usage: build/QweakPowerAna [anaPower file] [QweakSimG4 output file]"<<endl;
    return 1;
  }

  string finANdata(argv[1]);
  string finQweak(argv[2]);

  cout<<finANdata<<" "<<finQweak<<endl;
  TFile *finQw=new TFile(finQweak.c_str(),"READ");
  if(!finQw->IsOpen()){
    cout<<"Problem: can't find file: "<<finQweak<<endl;
    return -3;
  }

  TFile *fout=new TFile("o_ANdata.root","RECREATE");
  TTree *t=new TTree("t","AN data from MSc");
  int nev,mscGen,flip;
  float pol,cost,an,ene;
  float finalPosX,finalAngX,finalEne;
  float transPol;
  t->Branch("nev",&nev,"nev/I");
  t->Branch("flip",&flip,"flip/I");
  t->Branch("mscGen",&mscGen,"mscGen/I");
  t->Branch("pol",&pol,"pol/F");
  t->Branch("transPol",&transPol,"transPol/F");
  t->Branch("cost",&cost,"cost/F");
  t->Branch("an",&an,"an/F");
  t->Branch("ene",&ene,"ene/F");
  t->Branch("finalPosX",&finalPosX,"finalPosX/F");
  t->Branch("finalAngX",&finalAngX,"finalAngX/F");
  t->Branch("finalEne",&finalEne,"finalEne/F");

  TTree *QweakSimG4_Tree=(TTree*)finQw->Get("QweakSimG4_Tree");    
  QweakSimUserMainEvent* event = 0;
  QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);    

  ifstream finAN(finANdata.c_str());
  int nAN=-1;
  string line;
  float polRef=-1;
  std::getline(finAN,line);//header line
  int foundPrimary(0);
  for (int i = 0; i < QweakSimG4_Tree->GetEntries(); i++) {
    QweakSimG4_Tree->GetEntry(i);
    nev=event->Primary.GetPrimaryEventNumber();//FIXME
    //if(i%10000==1) cout<<"   at event: "<<i<<endl;
    cout<<"   at event: "<<i<<" ev# "<<nev<<endl;

    while(nAN<nev && std::getline(finAN,line)){
      //cout<<" skipping "<<nev<<endl<<line<<endl;
      std::istringstream iss(line);
      string word;
      iss>>word;
      if(word=="step")
	iss>>polRef>>nAN;
    }
    //cin.ignore();
    foundPrimary=0;
    
    for (int hit = 0;
	 hit < event->Cerenkov.Detector.GetDetectorNbOfHits() && !foundPrimary;
	 hit++) {	
      if(event->Cerenkov.Detector.GetDetectorID()[hit]!=3) continue;
      
      int pTypeHit=event->Cerenkov.Detector.GetParticleType()[hit];
      if(abs(pTypeHit)!=11) continue;
      
      int parentID=event->Cerenkov.Detector.GetParentID()[hit];
      int tID     =event->Cerenkov.Detector.GetParticleID()[hit];
      if(parentID!=0 || tID!=1) continue;
      //cout<<" ~~~~ "<<parentID<<" "<<tID<<" "<<pTypeHit<<" "<<i<<" "<<nev<<endl;
      //cin.ignore();
      foundPrimary=1;
      
      finalEne=event->Cerenkov.Detector.GetTotalEnergy()[hit];
      finalPosX=event->Cerenkov.Detector.GetDetectorGlobalPositionX()[hit];      
      double Gphi   = event->Cerenkov.Detector.GetGlobalPhiAngle()[hit];
      double Gtheta = event->Cerenkov.Detector.GetGlobalThetaAngle()[hit];	
      double _Gtheta=Gtheta/180.*pi;
      double _Gphi=(Gphi+90)/180.*pi; //+90 to account for the offset in the output
      finalAngX = atan2(sin(_Gtheta)*cos(_Gphi),cos(_Gtheta)) * 180.0 / pi;
      
      //cout<<"start reading !!!! "<<nev<<" "<<i<<endl;
      //cin.ignore();
      while(nAN<=nev && std::getline(finAN,line)){
	//cout<<nAN<<endl<<" "<<line<<endl<<polRef<<endl;
	//cin.ignore();
	std::istringstream iss(line);
	string word;
	iss>>word;
	if(word=="step"){
	  iss>>polRef>>nAN;
	}else{
	  if(word=="U") mscGen=3;
	  else if(word=="Ws") mscGen=1;
	  else if(word=="Wm") mscGen=2;
	  iss>>ene>>cost>>an>>pol>>transPol>>flip;

	  if(pol!=polRef){
	    cout<<pol<<" <> "<<polRef<<endl;
	    return -5;
	  }

	  // cout<<"  "<<nev<<" "<<mscGen<<" "<<pol<<" "<<cost<<" "<<an<<" "<<ene
	  //     <<" "<<finalPosX<<" "<<finalAngX<<" "<<finalEne<<endl;
	  //cin.ignore();
	  t->Fill();
	}
      }//while ANdata loop
    }//nhit
  }//tree entries

  fout->cd();
  t->Write();
  fout->Close();
  finAN.close();
  finQw->Close();
  return 0;
}
