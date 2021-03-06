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
#include "TH2D.h"

using namespace std;

void getCorrectedInitialConditions(float angX, float x, float z, float zi, TH1D *h, float &angXi, float &xi, int posAng);
void getCorrectedInitialConditions(float angX, float x, float &angXi, float &xi, int pol);

const double pi=acos(-1);

int main(int argc, char** argv){

  clock_t tStart=clock();
  
  if( argc == 1 || (0 == strcmp("--help", argv[1]))) {
    cout << " usage: build/anaPEs [options]" << endl
         << " --rootfile <path to rootfile>" << endl
         << " --barmodel ideal0, ideal23, ideal23_polish, ideal23_bevel, "
         << "ideal23_glue, ideal23_thickdiff, "
         << "ideal23_RBevelEndcapCentralGlueSideOnly, "
         << "ideal23_RBevelEndcapPMTSideOnly, ideal23_RBevelLongAxisOnly, "
         << "ideal23_RLG2mmThinner, "
         << "ideal23_RNoBevel, ideal23_GlueFilmR040, ideal23_PolishR005Decrease, ideal23_PolishR010Decrease, "
         << "md1config10_23, md1config16_model2_23, md1_model2_lightGuideMod, md1config5_model2_23, md2config5_23, "
         << "md2config5_model2_23, md2config3run1par_model2_23, md2config11_model2_23, md3config4_23, md4config4_23," 
         << "md5config4_23,md6config3_23, md7config2_23, md8config16_0, md8config16_23, md8configMG_23"
         << endl
         << "\t <tracks> is default and does not calculate PEs" << endl
         << " --distmodel mirror (omit for as is)" << endl
         << " --Ecut <Lval> <Hval> (optional: make energy cuts on electrons in MeV)" << endl
         << " --correctInitialAng <distFile> <polV> (optional: calculates initial angle offset from a distribution according to polarization (+1 for V and -1 for mV). works for MD3 moustaches for now)" << endl
         << " --correctInitialPos <distFile> <polV> (optional: calculates initial position offset from a distribution according to polarization (+1 for V and -1 for mV). works for MD3 moustaches for now)" << endl
	 << " --correctInitialCor <polV> (optional: calculates initial position offset from a correlation between initial angle and final position for different polarization (+1 for V and -1 for mV). works for MD3 moustaches for now)" << endl
	 << " --suffix <name to append to outFile> (omit for default)" << endl;
    return 1;
  }
  
  // Read in command line paramaters
  string barModel = "tracks";
  string distModel = "asIs";
  string rootfile = "";
  string suffix="";
  int offset = 0;
  int correctInitial(0);
  TFile *corrFl;
  TH1D *hcorrection;
  double eCutLow(-1),eCutHigh(-1);
  for(Int_t i = 1; i < argc; i++) {
    if(0 == strcmp("--Ecut", argv[i])) {
      eCutLow  = atof(argv[i+1]);
      eCutHigh = atof(argv[i+2]);
      cout<<"Will make cuts "<<eCutLow<<" <E< "<<eCutHigh<<endl;
    }else if(0 == strcmp("--barmodel", argv[i])) {
      barModel = argv[i+1];
    }else if(0 == strcmp("--correctInitialAng", argv[i])) {
      corrFl=TFile::Open(argv[i+1],"READ");
      correctInitial = atoi(argv[i+2]);
      cout<<"Will correct initial angle for polarizaiton: "<<correctInitial<<endl;
      if(correctInitial==1)
	hcorrection = (TH1D*)corrFl->Get("hAng_V");
      else if(correctInitial==-1)
	hcorrection = (TH1D*)corrFl->Get("hAng_M");
      else{
	cout<<"Correction polarization value was inputted badly! Quitting!:" <<correctInitial<<endl;
	return -2;
      }
    }else if(0 == strcmp("--correctInitialPos", argv[i])) {
      corrFl=TFile::Open(argv[i+1],"READ");
      correctInitial = atoi(argv[i+2])*2;
      cout<<"Will correct initial position for polarizaiton: "<<correctInitial<<endl;
      if(correctInitial==2)
	hcorrection = (TH1D*)corrFl->Get("hPos_V");
      else if(correctInitial==-2)
	hcorrection = (TH1D*)corrFl->Get("hPos_M");
      else{
	cout<<"Correction polarization value was inputted badly! Quitting!:" <<correctInitial<<endl;
	return -2;
      }
    }else if(0 == strcmp("--correctInitialCor", argv[i])) {
      correctInitial = atoi(argv[i+1])*3;
      cout<<"Will correct initial position/angle with correlation "<<correctInitial<<endl;
    }else if(0 == strcmp("--distmodel", argv[i])) {
      distModel = argv[i+1];
    }else if(0 == strcmp("--rootfile", argv[i])) {
      rootfile = argv[i+1];
    }else if(0 == strcmp("--offset", argv[i])) {
      offset = atoi(argv[i+1]);
    }else if(0 == strcmp("--suffix", argv[i])) {
      suffix = argv[i+1];
    }
  }
  cout<<"Bar Model: "<<barModel<<endl;
  interpolatePEs interpolator;
  int maxAvg=2;
  if(barModel!="tracks"){
    interpolator.setLightMap(barModel);
    maxAvg=20;
  }

  TFile *fin=TFile::Open(rootfile.c_str(),"READ");
  TTree *t=(TTree*)fin->Get("t");
  int evNr;
  int primary;//0 secondary, 1 primary
  float x,xi,y,z,zi,E,angX,angY,angXi,angYi,polT;
  float phi,theta;
  double asymPpM(0),asymPmM(0);
  int fillPhi=0;
  t->SetBranchAddress("evNr",&evNr);
  t->SetBranchAddress("primary",&primary);
  t->SetBranchAddress("x",&x);
  t->SetBranchAddress("xi",&xi);
  t->SetBranchAddress("y",&y);
  t->SetBranchAddress("z",&z);
  t->SetBranchAddress("zi",&zi);
  t->SetBranchAddress("E",&E);
  t->SetBranchAddress("angX",&angX);
  t->SetBranchAddress("angY",&angY);
  t->SetBranchAddress("angXi",&angXi);
  t->SetBranchAddress("angYi",&angYi);
  t->SetBranchAddress("polT",&polT);
  if(t->GetListOfBranches()->FindObject("phi")){
    t->SetBranchAddress("phi",&phi);
    t->SetBranchAddress("th",&theta);
    fillPhi=1;
  }
  if(t->GetListOfBranches()->FindObject("asymPpM")){
    t->SetBranchAddress("asymPpM",&asymPpM);
    t->SetBranchAddress("asymPmM",&asymPmM);
  }

  string outNm;
  if(suffix=="")
    outNm = Form("o_anaPE_%s_%s.root",barModel.c_str(),distModel.c_str());
  else
    outNm = Form("o_anaPE_%s_%s_%s.root",barModel.c_str(),distModel.c_str(),suffix.c_str());
  TFile *fout=new TFile(outNm.c_str(),"RECREATE");
  TH1D *hAng,*hAngCorrected,*hPos,*hPosCorrected;
  TH1D *hAngIDiff,*hPosIDiff;
  TH2D *fPos_iAng,*fPos_iAng_Corrected,*iAngOg_iAngCor;
  TH2D *iPos_iAng,*iPos_iAng_Corrected,*iPosProj_iAng_Corrected;
  if(correctInitial!=0){
    hAng = new TH1D("hAng","Original angle distribution; angle offset [deg]",200,-100,100);
    hAngCorrected = new TH1D("hAngCorrected","Corrected angle distribution; angle offset [deg]",200,-100,100);
    hPos = new TH1D("hPos","Original position distribution; position offset [cm]",400,-200,200);
    hPosCorrected = new TH1D("hPosCorrected","Corrected position offset distribution; position offset [cm]",400,-200,200);
    fPos_iAng=new TH2D("fPos_iAng","; position at Quartz [cm]; initial Angle [deg]",
		       200,-100,100,100,-10,10);
    fPos_iAng_Corrected=new TH2D("fPos_iAng_Corrected","; position at Quartz [cm]; initial Angle [deg]",
		       200,-100,100,100,-10,10);
    iPos_iAng=new TH2D("iPos_iAng","; position at Pb [cm]; initial Angle at Pb [deg]",
		       200,-100,100,100,-10,10);
    iPos_iAng_Corrected=new TH2D("iPos_iAng_Corrected",
				 "; position at Pb [cm]; initial Angle at Pb [deg]",
				 200,-100,100,100,-10,10);
    iPosProj_iAng_Corrected=new TH2D("iPosProj_iAng_Corrected",
				     "; position at Pb [cm]; initial Angle at Pb [deg]",
				     200,-100,100,100,-10,10);
    iAngOg_iAngCor=new TH2D("iAngOg_iAngCor",
			    "; original Angle at Pb [deg]; corrected initial angle at Pb [deg]",
			    100,-10,10,100,-10,10);
    hAngIDiff = new TH1D("hAngIDiff",";difference between calculated and original Initial angle [deg]",300,-150,150);
    hPosIDiff = new TH1D("hPosIDiff",";difference between calculated and originial Initial position offset [cm]",400,-200,200);
  }
  string lr[2]={"L","R"};
  string species[3]={"N","P","A"};

  TH1D *hTotPE=new TH1D("hTotPE","",4,0,4);
  hTotPE->GetXaxis()->SetBinLabel(1,"N left  Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(2,"N right Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(3,"P left  Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(4,"P right Total number of PEs");
  //[L/R][Primary/NonPrimary/All]
  const int nProcBins=20;
  TH1D *hpe[2][3],*posPE[2][3],*angPE[2][3],*phiPE[2][3],*hpeAvg[2][3],*hpeAvgProc[2][3][nProcBins];
  TH1D *angPEProc[2][3][nProcBins];
  for(int i=0;i<2;i++)
    for(int j=0;j<3;j++){
      hpe[i][j]=new TH1D(Form("hpe_%s_%s",lr[i].c_str(),species[j].c_str()),
			 Form("%s %s;number of PEs",lr[i].c_str(),species[j].c_str()),
			 300,0,300);
      double showerFactor(1);
      if(j!=1) showerFactor=20;
      hpeAvg[i][j]=new TH1D(Form("hpeAvg_%s_%s",lr[i].c_str(),species[j].c_str()),
			    Form("1k ev Avg %s %s;number of PEs",lr[i].c_str(),species[j].c_str()),
			    600,0,maxAvg*showerFactor);
      for(int k=0;k<nProcBins;k++){
	hpeAvgProc[i][j][k]=new TH1D(Form("hpeAvgProc_%s_%s_%d",lr[i].c_str(),species[j].c_str(),k),
				     Form("1k ev Avg %s %s;number of PEs",lr[i].c_str(),species[j].c_str()),
				     600,0,maxAvg*showerFactor);
	angPEProc[i][j][k]=new TH1D(Form("angPE_%s_%s_%d",lr[i].c_str(),species[j].c_str(),k),
				    Form("%s %s %d;angle in shower [deg]",lr[i].c_str(),species[j].c_str(),k),
				    400,-100,100);      
      }
      
      
      posPE[i][j]=new TH1D(Form("posPE_%s_%s",lr[i].c_str(),species[j].c_str()),
			   Form("%s %s;position along bar[cm]",lr[i].c_str(),species[j].c_str()),
			   400,-100,100);
      
      angPE[i][j]=new TH1D(Form("angPE_%s_%s",lr[i].c_str(),species[j].c_str()),
			   Form("%s %s;angle in shower [deg]",lr[i].c_str(),species[j].c_str()),
			   400,-100,100);      

      phiPE[i][j]=new TH1D(Form("phiPE_%s_%s",lr[i].c_str(),species[j].c_str()),
			   Form("%s %s;global phi [deg]",lr[i].c_str(),species[j].c_str()),
			   400,0,400);      
    }

  double TotPE[2][2]={{0,0},{0,0}};
  double AvgPE[2][2]={{0,0},{0,0}};

  long int stepEvNr(0),prevEvNr(0),currEvNr(0),realEvNr(0),recordNr(1000);
  float startProc=99.7,stopProc=101,currentProc=0,procStep=5;
  long int nev=t->GetEntries();
  cout<<"Total number of events: "<<nev<<endl;
  for(long int i=0;i<nev;i++){
    if( float(i+1)/nev*100 > currentProc ){
      cout<<" at event: "<<i<<"\t"<<float(i+1)/nev*100<<"% | time passed: "<< (double) ((clock() - tStart)/CLOCKS_PER_SEC)<<" s | iProc: "<<int(int( float(i+1)/nev*100 ) * nProcBins/100)<<endl;
      currentProc+=procStep;
    }
    //if( i>40000000) break;
    //if( float(i+1)/nev*100<startProc || float(i+1)/nev*100>stopProc ) continue;

    t->GetEntry(i);
    if(abs(z)<100)
      z=577.155;//fix for local z
    if( i>0 )
      prevEvNr=currEvNr;
    currEvNr=evNr;
    if( evNr<prevEvNr )
      stepEvNr += std::ceil(prevEvNr/100.)*100;
    realEvNr=evNr+stepEvNr;

    int iProc =  int( float(i+1)/nev*100 ) * nProcBins/100;
    
    if(realEvNr>recordNr){
      recordNr+=1000;
      for(int j=0;j<2;j++){
	for(int k=0;k<2;k++){
	  hpeAvg[j][k]->Fill(AvgPE[k][j]/1000.);
	  hpeAvgProc[j][k][iProc]->Fill(AvgPE[k][j]/1000.);
	}
	hpeAvg[j][2]->Fill((AvgPE[0][j]+AvgPE[1][j])/1000.);
	hpeAvgProc[j][2][iProc]->Fill((AvgPE[0][j]+AvgPE[1][j])/1000.);
      }

      for(int j=0;j<2;j++)
	for(int k=0;k<2;k++)
	  AvgPE[j][k]=0;
    }
    
    if(distModel == "mirror"){
      x = -x;
      angX = -x;
      xi = -xi;
      angXi = -angXi;
    }
    if(eCutLow>-1 && (E<eCutLow || E>=eCutHigh)) continue;
    
    double pes[2]={1,0};
    if(barModel == "tracks"){
      if(E<3) continue; //3 MeV cut from light parametrizations
      if(abs(angX) > 89) continue; //89 deg cut from light parametrizations
      if(abs(x) > 100) continue; //100 cm cut from light parametrizations
      if(x>=0) pes[0]=1;
      else if(x<0) pes[1]=1;
    }else{
      // -x,-angX so that we can be in the tracking frame
      // associate L to the R container so that we can match the proper optical parametrization
      if(barModel=="md8configMG_23"){
	if(!interpolator.getPEs(E,x,angX,pes[0],pes[1])) continue;
      }else{
	if(!interpolator.getPEs(E,-x,-angX,pes[1],pes[0])) continue;
      }
    }

    if( correctInitial != 0){
      hAng->Fill(angX-angXi);
      hPos->Fill(x-(xi+tan(angXi/180*pi)*abs(z-zi)));      
      fPos_iAng->Fill(x,angXi);
      iPos_iAng->Fill(xi,angXi);
      double angXiOg=angXi;
      double xiOg = xi;
      if( abs(correctInitial) == 1)
	getCorrectedInitialConditions(angX,x,z,zi,hcorrection,angXi,xi,correctInitial);
      else if( abs(correctInitial) == 2)
	getCorrectedInitialConditions(angX,x,z,zi,hcorrection,angXi,xi,correctInitial);
      else if( abs(correctInitial) == 3)
	getCorrectedInitialConditions(angX,x,angXi,xi,correctInitial);
      
      hAngCorrected->Fill(angX-angXi);
      hPosCorrected->Fill(x-(xi+tan(angXi/180*pi)*abs(z-zi)));      
      fPos_iAng_Corrected->Fill(x,angXi);
      iPos_iAng_Corrected->Fill(xi,angXi);
      iPosProj_iAng_Corrected->Fill((xi+tan(angXi/180*pi)*abs(z-zi)),angXi);
      iAngOg_iAngCor->Fill(angXiOg,angXi);
      hPosIDiff->Fill(xiOg - xi);
      hAngIDiff->Fill(angXiOg - angXi);
    }
    
    for(int j=0;j<2;j++){
      TotPE[primary][j]+=pes[j];
      AvgPE[primary][j]+=pes[j];

      hpe[j][primary]->Fill(pes[j]);
      posPE[j][primary]->Fill(x,pes[j]);
      angPE[j][primary]->Fill(angX-angXi,pes[j]);

      // if( x>60 && angX>40){
      // 	cout<<x<<" "<<angX<<endl;
      // 	cout<<"\t"<<hpe[j][primary]->GetName()<<" "<<pes[j]<<endl;
      // 	std::cin.ignore();
      // }
      
      hpe[j][2]->Fill(pes[j]);
      posPE[j][2]->Fill(x,pes[j]);
      angPE[j][2]->Fill(angX-angXi,pes[j]);

      if(iProc<20){
	angPEProc[j][primary][iProc]->Fill(angX-angXi,pes[j]);
	angPEProc[j][2][iProc]->Fill(angX-angXi,pes[j]);
      }

      if(fillPhi){
	double tmpPhi= phi < 0 ? 360 + phi : phi;
	phiPE[j][primary]->Fill(tmpPhi,pes[j]);
	phiPE[j][2]->Fill(tmpPhi,pes[j]);
      }      
    }
    
    
  }
  cout<<" finished loop "<<endl;
  for(int j=0;j<2;j++)
    for(int k=0;k<2;k++){
      hTotPE->SetBinContent(j*2+k+1,TotPE[j][k]);
    }
  cout<<" write out file "<<endl;
  
  fout->cd();
  hTotPE->Write();
  for(int i=0;i<2;i++)
    for(int j=0;j<3;j++){
      hpe[i][j]->Write();
      hpeAvg[i][j]->Write();
      for(int k=0;k<nProcBins;k++){
	hpeAvgProc[i][j][k]->Write();	
	angPEProc[i][j][k]->Write();
      }
      posPE[i][j]->Write();
      angPE[i][j]->Write();
      phiPE[i][j]->Write();
    }

  if(correctInitial!=0){
    hPos->Write();
    hAng->Write();
    hPosCorrected->Write();
    hAngCorrected->Write();
    fPos_iAng->Write();
    fPos_iAng_Corrected->Write();
    iPos_iAng->Write();
    iPos_iAng_Corrected->Write();
    iPosProj_iAng_Corrected->Write();
    iAngOg_iAngCor->Write();
    hPosIDiff->Write();
    hAngIDiff->Write();
  }
  fout->Close();
  cout<<" Running time[s]: "<< (double) ((clock() - tStart)/CLOCKS_PER_SEC)<<endl;

  return 0;
}

inline void getCorrectedInitialConditions(float angX, float x, float z, float zi,
					  TH1D *h, float &angXi, float &xi, int posAng){
  //   //for equation a*X + b =>JP det elog 117 
  // double a[8]={1.37e-3, 1.37e-3, 1.37e-3, 1.37e-3, 1.38e-3, 1.37e-3, 1.37e-3, 1.37e-3};
  // double b[8]={-1.8e-4, -1.9e-4,  1.8e-4,  3.1e-4, -2.0e-5,  1.6e-4,  2.2e-4,  1.1e-4};

  double a = 1.37e-3; //[rad/cm]
  double b = -1.8e-4; //[rad] //FIXME this does not match elog because I sampled ax-b
  if(abs(posAng)==1){
    angXi = angX - h->GetRandom();
    xi = (angXi/180*pi - b)/a ;
  }else{
    //h contains x - (xi + tan(angXi)*(z-zi))
    //beam always starts at the same zi so that value is correct
    double val = x - h->GetRandom();//[cm]
    double c = abs(z-zi);//[cm]
    xi = (val - c*b)/(1+a*c); //[cm]
    angXi = (xi*a + b)*180/pi;
  }
}

inline void getCorrectedInitialConditions(float angX, float x,
					  float &angXi, float &xi, int pol){
  double p0(0),p1(0);
  if(pol>0){
    p0 = -0.01015;
    p1 = 0.07785;
  }else{
    p0 = -0.01035;
    p1 = 0.07785;
  }  
  angXi = x*p1 + p0;
  //cout<<"\t"<<x<<"\t"<<angXi<<endl;
  
  double a = 1.37e-3; //[rad/cm]
  double b = -1.8e-4; //[rad] //FIXME this does not match elog because I sampled ax-b
  xi = (angXi/180*pi - b)/a ;
}
