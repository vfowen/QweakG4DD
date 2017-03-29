#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <ctime>

#include "interpolatePEs.hh"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h" 

using namespace std;
clock_t tStart;

int main(int argc, char** argv)
{
  tStart=clock();

  // Print help
  if( argc == 1 || (0 == strcmp("--help", argv[1]))) {
    cout << " usage: build/posModel [options]" << endl
         << " --rootfile <path to rootfile>" << endl
         << " --barmodel ideal0, ideal23, ideal23_polish, ideal23_bevel, "
         << "ideal23_glue, ideal23_thickdiff, "
         << "ideal23_RBevelEndcapCentralGlueSideOnly, "
         << "ideal23_RBevelEndcapPMTSideOnly, ideal23_RBevelLongAxisOnly, "
         << "ideal23_RLG2mmThinner, "
         << "ideal23_RNoBevel, ideal23_GlueFilmR040, ideal23_PolishR005Decrease, ideal23_PolishR010Decrease, "
         << "md1config10_23, md1config16_model2_23, md1_model2_lightGuideMod, md1config5_model2_23, md2config5_23, "
         << "md2config5_model2_23, md2config3run1par_model2_23, md2config11_model2_23, md3config4_23, md4config4_23," 
         << "md5config4_23,md6config3_23, md7config2_23, md8config16_0, md8config16_23, md8configMG_23, "
	 << "tracking_md1,tracking_md2,tracking_md3,tracking_md4,tracking_md5,tracking_md6,tracking_md7,tracking_md8"
         << endl
         << " --distmodel mirror (omit for as is)"
         << endl
      	 << " --suffix <name to append to outFile> (omit for default)" << endl;
    return 1;
  }
  
  // Read in command line paramaters
  string barModel = "ideal23";
  string distModel = "asIs";
  string rootfile = "";
  string suffix = "";
  
  for(Int_t i = 1; i < argc; i++) {    
    if(0 == strcmp("--barmodel", argv[i])) {
      barModel = argv[i+1];
    } else if(0 == strcmp("--distmodel", argv[i])) {
      distModel = argv[i+1];
    } else if(0 == strcmp("--rootfile", argv[i])) {
      rootfile = argv[i+1];
    }else if(0 == strcmp("--suffix", argv[i])) {
      suffix = argv[i+1];
    }    
  }

  if(rootfile==""){
    cout<<" no rootfile provided! Exiting!"<<endl;
    return 1;
  }
  
  TFile *fin=TFile::Open(rootfile.c_str(),"READ");
  TTree *t=(TTree*)fin->Get("t");
  int evNr;
  int primary;//0 secondary, 1 primary
  float x,y,z,E;
  float angX,angY;
  float angXi,angYi;
  float polT;
  double asymPpM(0),asymPmM(0);
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
  if(t->GetListOfBranches()->FindObject("asymPpM")){
    t->SetBranchAddress("asymPpM",&asymPpM);
    t->SetBranchAddress("asymPmM",&asymPmM);
  }

  string outNm="";
  if(suffix=="")
    outNm=Form("o_posModel_%s_%s.root", barModel.c_str(),distModel.c_str());
  else
    outNm=Form("o_posModel_%s_%s_%s.root", barModel.c_str(),distModel.c_str(), suffix.c_str()); 

  TFile *fout=new TFile(outNm.c_str(),"RECREATE");

  string lr[2]={"R","L"};
  string pm[2]={"posPol","negPol"};
  TH1D *hpe[2][2],*posPE[2][2],*angPE[2][2];//[R/L][P/M]
  TH1D *as[2],*posAs[2],*angAs[2],*avgAs[2];//[R/L]

  int nBins=200;
  TH1D *totPEs = new TH1D("totPEs","rPos, rNeg, lPos, lNeg",4,0,4);
  TH1D *avgDD  = new TH1D("avgDD","Avg DD distribution",100,-1e-5,1e-5);
  TH1D *avgAb  = new TH1D("avgAb","Avg Ab distribution",100,-1e-5,1e-5);
  
  for(int i=0;i<2;i++){
    as[i] = new TH1D(Form("as_%s",lr[i].c_str()),
		     Form("Asymmetry distribution %s",lr[i].c_str()),
		     100,-1e-5,1e-5);
    avgAs[i] = new TH1D(Form("avgAs_%s",lr[i].c_str()),
			Form("Avg Asymmetry distribution %s",lr[i].c_str()),
			100,-1e-5,1e-5);
    posAs[i] = new TH1D(Form("posAs_%s",lr[i].c_str()),
			Form("%s PMT;position[cm];asymmetry[ppm]",lr[i].c_str()),
			nBins,-100,100);
    angAs[i] = new TH1D(Form("angAs_%s",lr[i].c_str()),
			Form("%s PMT;relative angle [deg];asymmetry[ppm]",lr[i].c_str()),
			nBins,-100,100);

    for(int j=0;j<2;j++){
      hpe[i][j] = new TH1D(Form("pe_%s_%s",lr[i].c_str(),pm[j].c_str()),
			   Form("PE distribution for %s PMT and %s",lr[i].c_str(),pm[j].c_str()),
			   100,0,500);
      posPE[i][j] = new TH1D(Form("posPE_%s_%s",lr[i].c_str(),pm[j].c_str()),
			     Form("%s PMT| %s;position[cm];PEs",lr[i].c_str(),pm[j].c_str()),
			     nBins,-100,100);
      angPE[i][j] = new TH1D(Form("angPE_%s_%s",lr[i].c_str(),pm[j].c_str()),
			     Form("%s PMT| %s;relative angle [deg];PEs",lr[i].c_str(),pm[j].c_str()),
			     nBins,-100,100);      
    }
  }

  double stepSize=0.2;
  double currentStep=stepSize;
  
  double flip(1.);
  if(distModel == "mirror")
    flip=-1.;

  double rTotPE[2]={0,0},lTotPE[2]={0,0};
  double rAvgPE[2]={0,0},lAvgPE[2]={0,0};

  int nev=t->GetEntries();
  float currentProc=0,procStep=10;
  interpolatePEs interpolator(barModel);
  for(int i=0;i<nev;i++){
    t->GetEntry(i);
    if( float(i+1)/nev*100 > currentProc ){
      cout<<" at event: "<<i<<"\t"
	  <<float(i+1)/nev*100<<"% | time passed: "
	  << (double) ((clock() - tStart)/CLOCKS_PER_SEC)<<" s"<<endl;
      currentProc+=procStep;
    }

    if(float(i+1)/nev*100>currentStep){
      if(rAvgPE[0]+rAvgPE[1]>0 && lAvgPE[0]+lAvgPE[1]>0){
	double avgR =  (rAvgPE[0] - rAvgPE[1])/(rAvgPE[0] + rAvgPE[1]);
	double avgL =  (lAvgPE[0] - lAvgPE[1])/(lAvgPE[0] + lAvgPE[1]);
	
	avgAs[0]->Fill(avgR);
	avgAs[1]->Fill(avgL);
	avgDD -> Fill( avgR - avgL );
	avgAb -> Fill( (avgR + avgL)/2 );
	rAvgPE[0]=0;
	rAvgPE[1]=0;
	lAvgPE[0]=0;
	lAvgPE[1]=0;
      }
      currentStep+=stepSize;
    }
    
    
    //if( float(i+1)/nev*100 > 20 ) break;

    double yt     = -1.0*flip*x;
    double angYt  = -1.0*flip*angX;
    double angYti = -1.0*flip*angXi;
    double angYt_rel = angYt - angYti;

    double lpe[2]={-1,-1},rpe[2]={-1,-1};
    double shift=1.5e-5;//cm
    if(barModel=="md8configMG_23"){
      if(!interpolator.getPEs(E,-1*(yt+shift),-1*(angYt),lpe[0],rpe[0]))
	continue;
      if(!interpolator.getPEs(E,-1*(yt-shift),-1*(angYt),lpe[1],rpe[1]))
	continue;      
    }else{
      if(!interpolator.getPEs(E,yt+shift,angYt,rpe[0],lpe[0]))
	continue;
      if(!interpolator.getPEs(E,yt-shift,angYt,rpe[1],lpe[1]))
	continue;
    }

    if(lpe[0]<=0 || lpe[1]<=0 || rpe[0]<=0 || rpe[1]<=0 ){
      cout<<"Problem with interpolator! Fed it:\n\tposition: "
	  <<yt<<"\tshitft: "<<shift<<"\tangle: "<<angYt<<"\tEnergy: "<<E<<endl
	  <<"\t Obtained: "<<lpe[0]<<"\t"<<lpe[1]<<"\t"<<rpe[0]<<"\t"<<rpe[1]<<"\n";
      return 2;
    }
    // cout<<setprecision(12)<<yt<<"\tshitft: "<<shift<<"\tangle: "<<angYt<<"\tEnergy: "<<E<<endl
    // 	<<"\t Obtained: "<<lpe[0]<<"\t"<<lpe[1]<<"\t"<<rpe[0]<<"\t"<<rpe[1]<<"\n";
    // cin.ignore();

    as[0] -> Fill( (rpe[0] - rpe[1])/(rpe[0] + rpe[1]) );
    as[1] -> Fill( (lpe[0] - lpe[1])/(lpe[0] + lpe[1]) );
    for(int j=0;j<2;j++){
      rTotPE[j]+=rpe[j];
      lTotPE[j]+=lpe[j];
      rAvgPE[j]+=rpe[j];
      lAvgPE[j]+=lpe[j];
      
      hpe[0][j]->Fill(rpe[j]);
      hpe[1][j]->Fill(lpe[j]);

      posPE[0][j]->Fill(yt,rpe[j]);
      posPE[1][j]->Fill(yt,lpe[j]);

      angPE[0][j]->Fill(angYt_rel,rpe[j]);
      angPE[1][j]->Fill(angYt_rel,lpe[j]);
    }
  }
  
  cout<<"Finished processing!"<<endl;
  fin->Close();

  for(int i=0;i<2;i++)
    for(int j=1;j<=nBins;j++){
      double vP = posPE[i][0]->GetBinContent(j);
      double vM = posPE[i][1]->GetBinContent(j);
      if(vP+vM>0)
	posAs[i]->SetBinContent(j,(vP-vM)/(vP+vM));

      vP = angPE[i][0]->GetBinContent(j);
      vM = angPE[i][1]->GetBinContent(j);
      if(vP+vM>0)
	angAs[i]->SetBinContent(j,(vP-vM)/(vP+vM));      
    }

  totPEs->SetBinContent(1,rTotPE[0]);
  totPEs->SetBinContent(2,rTotPE[1]);
  totPEs->SetBinContent(3,lTotPE[0]);
  totPEs->SetBinContent(4,lTotPE[1]);
  fout->cd();
  totPEs->Write();
  avgDD->Write();
  avgAb->Write();
  for(int i=0;i<2;i++){
    as[i]->Write();
    avgAs[i]->Write();
    angAs[i]->Write();
    posAs[i]->Write();
    for(int j=0;j<2;j++){
      hpe[i][j]->Write();
      posPE[i][j]->Write();
      angPE[i][j]->Write();
    }
  }

  double rAs  = (rTotPE[0] - rTotPE[1])/(rTotPE[0] + rTotPE[1]);
  double lAs  = (lTotPE[0] - lTotPE[1])/(lTotPE[0] + lTotPE[1]);
  double dd   = (rAs - lAs);
  double ab   = (rAs + lAs)/2;
  cout<<"L\tR\tDD\tAb\n";
  cout<<lAs<<"\t"<<rAs<<"\t"<<dd<<"\t"<<ab<<endl;

  fout->Close();

  cout<<" Running time[s]: "<< (double) ((clock() - tStart)/CLOCKS_PER_SEC)<<endl;
  return 0;
}
