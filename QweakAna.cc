#include <string>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "QweakSimUserMainEvent.hh"
#include "QweakSimSystemOfUnits.hh"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TGraph.h"
#include "TGraphErrors.h"

using namespace std;
void findInt(std::vector<int> &inter,std::vector<int> &val, int trackID,int parent, int &hasPar, int &nInt);
double updateMean(double vOld, double vNew, int nOld);
void updateMean(int i,double val, std::vector<double> &average, std::vector<int> &n);
double getAsym(int posAng,double val);
void calcAsym(TH1D *dist,TH1D *mean, TH1D *asym,int posAng);

TGraph *singleAsym;
TGraphErrors *posAsym;
TGraph       *angAsym;

int main(int argc, char** argv)
{
  if( argc !=3 ) {
    cout<<" usage: build/QweakAna [detector number] [path to infile with list of output QweakSimG4 trees]"<<endl;
    return 1;
  }
  double nDet=atoi(argv[1]);
  string files(argv[2]);

  TFile *finAsym=TFile::Open("output/o_PEasyms.root","READ");
  posAsym=(TGraphErrors*)finAsym->Get("asym_9");
  angAsym=(TGraph*)      finAsym->Get("angle");

  double eCut[3]={0.,1.,2.};
  TFile *fout=new TFile("o_dist_asym.root","RECREATE");
  TH1D *averages=new TH1D("averages","averages",20,0,20);
  TH1D *distXposPe[3],*distXposAe[3],*distXposPh[3];
  TH1D *distXangPe[3],*distXangAe[3],*distXangPh[3];
  TH1D *meanXposPe[3],*meanXposAe[3];
  TH1D *meanXangPe[3],*meanXangAe[3];
  TH1D *asymXposPe[3],*asymXangPe[3],*asymXposAe[3],*asymXangAe[3];
  TH1D *ddAsXposPe[3],*ddAsXangPe[3],*ddAsXposAe[3],*ddAsXangAe[3];
  TH2D *distAsymXposPe[3],*distAsymXposAe[3];
  TH2D *distAsymXangPe[3],*distAsymXangAe[3];
  
  for(int i=0;i<3;i++){
    distXposPe[i]=new TH1D(Form("distXposPe_%d",i),"X position distribution primary e-;x pos [cm]",200,-100,100);
    distXposAe[i]=new TH1D(Form("distXposAe_%d",i),"X position distribution All e;x pos [cm]"     ,200,-100,100);
    distXposPh[i]=new TH1D(Form("distXposPh_%d",i),"X position distribution photons;x pos [cm]"   ,200,-100,100);
    distXangPe[i]=new TH1D(Form("distXangPe_%d",i),"Angle along X distribution primary e-;ang X [deg]",180,-90,90);
    distXangAe[i]=new TH1D(Form("distXangAe_%d",i),"Angle along X distribution All e;ang X [deg]"     ,180,-90,90);
    distXangPh[i]=new TH1D(Form("distXangPh_%d",i),"Angle along X distribution photons;ang X [deg]"   ,180,-90,90);

    meanXposPe[i]=new TH1D(Form("meanXposPe_%d",i),"X position mean primary e-;x pos [cm]",200,-100,100);
    meanXposAe[i]=new TH1D(Form("meanXposAe_%d",i),"X position mean All e;x pos [cm]"     ,200,-100,100);
    meanXangPe[i]=new TH1D(Form("meanXangPe_%d",i),"Angle along X mean primary e-;ang X [deg]",180,-90,90);
    meanXangAe[i]=new TH1D(Form("meanXangAe_%d",i),"Angle along X mean All e;ang X [deg]"     ,180,-90,90);

    asymXposPe[i]=new TH1D(Form("asymXposPe_%d",i),"Asymmetry for X position deviation primary e-",200,-1,1);
    asymXposAe[i]=new TH1D(Form("asymXposAe_%d",i),"Asymmetry for X position deviation all e"     ,200,-1,1);
    asymXangPe[i]=new TH1D(Form("asymXangPe_%d",i),"Asymmetry for angle deviation primary e-",200,-1,1);
    asymXangAe[i]=new TH1D(Form("asymXangAe_%d",i),"Asymmetry for angle deviation all e"     ,200,-1,1);

    ddAsXposPe[i]=new TH1D(Form("ddAsXposPe_%d",i),"DD Asym Primary e-; xPos [cm]",100,0,100);
    ddAsXposAe[i]=new TH1D(Form("ddAsXposAe_%d",i),"DD Asym All e; xPos [cm]"     ,100,0,100);
    ddAsXangPe[i]=new TH1D(Form("ddAsXangPe_%d",i),"DD Asym Primary e-; X angle [deg]",100,0,90);
    ddAsXangAe[i]=new TH1D(Form("ddAsXangAe_%d",i),"DD Asym All e; X angle [deg]"     ,100,0,90);

    distAsymXposPe[i]=new TH2D(Form("distAsymXposPe_%d",i),";xPos [cm];Asym ",200,-100,100,200,-1,1);
    distAsymXposAe[i]=new TH2D(Form("distAsymXposAe_%d",i),";xPos [cm];Asym ",200,-100,100,200,-1,1);
    distAsymXangPe[i]=new TH2D(Form("distAsymXangPe_%d",i),";xAng [deg];Asym ",180,-90, 90,200,-1,1);
    distAsymXangAe[i]=new TH2D(Form("distAsymXangAe_%d",i),";xAng [deg];Asym ",180,-90, 90,200,-1,1);
  }

  std::vector<double> runningAverages(12,0);
  std::vector<int> nAverages(12,0);
  string aveName[4]={"asymXposPe","asymXangPe","asymXposAe","asymXangAe"};
  
  ifstream ifile(files.c_str());
  string data;
  std::vector<int> interaction;
  std::vector<int> trackID;

  while(ifile>>data){
    TFile *fin=TFile::Open(data.c_str());
    TTree *QweakSimG4_Tree=(TTree*)fin->Get("QweakSimG4_Tree");
    cout<<"processing : "<<data.c_str()<<" for detector "<<nDet<<endl;    
    
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

	double posAsymV=getAsym(0,x);
	double angAsymV=getAsym(1,angX);

	for(int j=0;j<3;j++){
	  if(E<eCut[j]) continue;
	  if(abs(pTypeHit)==22){ //photons
	    distXposPh[j]->Fill(x);
	    distXangPh[j]->Fill(angX);
	  }else if(abs(pTypeHit)==11){ //electrons
	    if(tID==1 && parentID==0){ //primary
	      distXposPe[j]->Fill(x);
	      distXangPe[j]->Fill(angX);
	      if( posAsymV > -1 ) {
		asymXposPe[j]->Fill(posAsymV);
		updateMean(j,posAsymV,runningAverages,nAverages);
		distAsymXposPe[j]->Fill(x,posAsymV);
	      }
	      if( angAsymV > -1 ) {
		asymXangPe[j]->Fill(angAsymV);
		updateMean(j+3,angAsymV,runningAverages,nAverages);
		distAsymXangPe[j]->Fill(angX,angAsymV);
	      }

	      double mean=0;
	      int nb=-1;
	      nb=distXposPe[j]->GetXaxis()->FindBin(x);
	      mean=updateMean(meanXposPe[j]->GetBinContent(nb), x, distXposPe[j]->GetBinContent(nb)-1);
	      meanXposPe[j]->SetBinContent(nb,mean);
	      nb=distXangPe[j]->GetXaxis()->FindBin(angX);
	      mean=updateMean(meanXangPe[j]->GetBinContent(nb), angX, distXangPe[j]->GetBinContent(nb)-1);
	      meanXangPe[j]->SetBinContent(nb,mean);
	    }
	    distXposAe[j]->Fill(x);
	    distXangAe[j]->Fill(angX);
	    if( posAsymV > -1 ) {
	      asymXposAe[j]->Fill(posAsymV);
	      updateMean(j+6,posAsymV,runningAverages,nAverages);
	      distAsymXposAe[j]->Fill(x,posAsymV);
	    }
	    if( angAsymV > -1 ){
	      asymXangAe[j]->Fill(angAsymV);	    
	      updateMean(j+9,angAsymV,runningAverages,nAverages);
	      distAsymXangAe[j]->Fill(angX,angAsymV);
	    }

	    double mean=0;
	    int nb=-1;
	    nb=distXposAe[j]->GetXaxis()->FindBin(x);
	    mean=updateMean(meanXposAe[j]->GetBinContent(nb), x, distXposAe[j]->GetBinContent(nb)-1);
	    meanXposAe[j]->SetBinContent(nb,mean);
	    nb=distXangAe[j]->GetXaxis()->FindBin(angX);
	    mean=updateMean(meanXangAe[j]->GetBinContent(nb), angX, distXangAe[j]->GetBinContent(nb)-1);
	    meanXangAe[j]->SetBinContent(nb,mean);
	  }
	  
	}//eCut
      }//nhit
    }//tree entries
    
    cout<<"Done looping!"<<endl;
    fin->Close();
  }

  for(int i=0;i<4;i++)
    for(int j=0;j<3;j++){
      averages->GetXaxis()->SetBinLabel(i*3+j+1,Form("%s_%d",aveName[i].c_str(),j));
      averages->SetBinContent(i*3+j+1,runningAverages[i*3+j]);
    }

  
  for(int j=0;j<3;j++){
    calcAsym(distXposPe[j],meanXposPe[j],ddAsXposPe[j],0);
    calcAsym(distXangPe[j],meanXangPe[j],ddAsXangPe[j],1);
    calcAsym(distXposAe[j],meanXposAe[j],ddAsXposAe[j],0);
    calcAsym(distXangAe[j],meanXangAe[j],ddAsXangAe[j],1);
  }
  
  fout->cd();
  averages->Write();
  for(int j=0;j<3;j++){
    
    distXposPe[j]->Write();
    distXposPh[j]->Write();
    distXposAe[j]->Write();
    distXangPe[j]->Write();
    distXangPh[j]->Write();
    distXangAe[j]->Write();  
    
    meanXposPe[j]->Write();
    meanXposAe[j]->Write();
    meanXangPe[j]->Write();
    meanXangAe[j]->Write();  

    asymXposPe[j]->Write();
    asymXposAe[j]->Write();
    asymXangPe[j]->Write();
    asymXangAe[j]->Write();
    
    ddAsXposPe[j]->Write();
    ddAsXposAe[j]->Write();
    ddAsXangPe[j]->Write();
    ddAsXangAe[j]->Write();

    distAsymXposPe[j]->Write();
    distAsymXposAe[j]->Write();
    distAsymXangPe[j]->Write();
    distAsymXangAe[j]->Write();
  }
  fout->Close();
  finAsym->Close();  
  ifile.close();
  return 0;
}

void calcAsym(TH1D *dist,TH1D *mean, TH1D *asym,int posAng){

  int middleBin=dist->GetXaxis()->GetNbins()/2;
  for(int i=0;i<asym->GetXaxis()->GetNbins();i++){
    double nL=dist->GetBinContent(middleBin-i);
    double nR=dist->GetBinContent(middleBin+i+1);

    double aL=getAsym(posAng,mean->GetBinContent(middleBin-i));
    double aR=getAsym(posAng,mean->GetBinContent(middleBin+i+1));

    if( aL < -1 || aR < -1 || (nR+nL == 0) ) continue;
    
    asym->SetBinContent( i+1, (nR*aR+nL*aL)/(nR+nL) );
    asym->SetBinError( i+1, sqrt(pow(nR*(aL-aR),2)*nL+pow(nL*(aR-aL),2)*nR)/pow(nL+nR,2) );
  }
  
}

double getAsym(int posAng,double val){
  if(posAng==0)      singleAsym=posAsym;
  else if(posAng==1) singleAsym=angAsym;

  double asym=-2;
  if( (posAng==0 && fabs(val)<20) || (posAng==1 && fabs(val)<35) )
    asym=( singleAsym->Eval(val,0,"S") - singleAsym->Eval(-val,0,"S") )/2;
  // else if(posAng==1 && fabs(val)>=40)
  //   asym=0.85*val/fabs(val);

  return asym;
}

void updateMean(int i,double val, std::vector<double> &average, std::vector<int> &n){
  average[i]=(average[i]*(double)n[i]+val)/((double)n[i]+1);
  n[i]++;    
}

double updateMean(double vOld, double vNew, int nOld){
  if(nOld==0) return vNew;
  else return (vOld*(double)nOld+vNew)/((double)nOld+1.);
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
