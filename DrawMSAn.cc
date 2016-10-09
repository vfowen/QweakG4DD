#include <iostream>

#include "TGraph.h"
#include "TFile.h"

#include "globals.hh"
#include "QweakSimMScAnalyzingPower.hh"

int main(int argc, char** argv){
  if(argc !=3){
    std::cout<<" usage: build/DrawMSAn [theta in deg] [energy in MeV]"<<std::endl;
    return 1;
  }

  double theta=atof(argv[1]);
  double energy=atof(argv[2]);

  TFile *fout=TFile::Open("z_MScAN.root","update");

  const double maxE=1160;
  const double maxT=180;
  const int maxPts=5000;
  
  TGraph *ge=new TGraph();
  ge->SetName(Form("anE_%04.0f",theta));
  ge->SetTitle(Form("AN for theta=%4.0f;energy [MeV]",theta));
  for(int i=0;i<maxPts;i++){
    double e=i*maxE/maxPts;
    ge->SetPoint(i,e,AnalyzingPower(e,cos(theta*pi/180.),50));
  }
  
  TGraph *gt=new TGraph();
  gt->SetName(Form("anT_%04.0f",energy));
  gt->SetTitle(Form("AN for energy=%4.0f;theta [deg]",energy));
  for(int i=0;i<maxPts;i++){
    double t=i*maxT/maxPts;
    double cth=cos(t*pi/180.);
    gt->SetPoint(i,t,AnalyzingPower(energy,cth,50));
  }

  fout->cd();
  ge->Write();
  gt->Write();  
  fout->Close();
}
