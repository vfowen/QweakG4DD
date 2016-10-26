#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <algorithm>

#include "interpolatePEs.hh"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

using namespace std;

void calcAsym(TH1 *hp,TH1 *hm, TH1 *ha);

int main(int argc, char** argv){

  if( argc == 1 || (0 == strcmp("--help", argv[1]))) {
    cout << " usage: build/anaPEsWgt [options]" << endl
         << " --rootfile <path to rootfile>" << endl
         << " --barmodel tracks, ideal0, ideal23, ideal23_polish, ideal23_bevel, "
         << "md6config3_23, md7config2_23, md8config16_0 or md8config16_23"<<endl
         << "\t <tracks> is default and does not calculate PEs" << endl
         << " --distmodel mirror (omit for as is)" << endl;
    return 1;
  }
  
  // Read in command line paramaters
  string barModel = "tracks";
  string distModel = "asIs";
  string rootfile = "";
  int offset = 0;
  for(Int_t i = 1; i < argc; i++) {
    if(0 == strcmp("--barmodel", argv[i])) {
      barModel = argv[i+1];
    }else if(0 == strcmp("--distmodel", argv[i])) {
      distModel = argv[i+1];
    }else if(0 == strcmp("--rootfile", argv[i])) {
      rootfile = argv[i+1];
    }else if(0 == strcmp("--offset", argv[i])) {
      offset = atoi(argv[i+1]);
    }
  }
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
  float x,y,z,E,angX,angY,angXi,angYi,polT;
  float phi,theta;
  double asymInfo[2]={0,0};
  int fillPhi=0;
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
  if(t->GetListOfBranches()->FindObject("phi")){
    t->SetBranchAddress("phi",&phi);
    t->SetBranchAddress("th",&theta);
    fillPhi=1;
  }
  if(t->GetListOfBranches()->FindObject("asymPM")){
    t->SetBranchAddress("asymPP",&asymInfo[0]);
    t->SetBranchAddress("asymPM",&asymInfo[1]);
  }

  TFile *fout=new TFile(Form("o_anaWgt_%s_%s.root",barModel.c_str(),distModel.c_str()),"RECREATE");
  string lr[2]={"R","L"};
  string species[3]={"N","P","A"};
  string pm[2]={"p","m"};

  TH1D *hTotPE=new TH1D("hTotPE","",8,0,8);
  hTotPE->GetXaxis()->SetBinLabel(1,"Plus  N left  Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(2,"Plus  N right Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(3,"Plus  P left  Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(4,"Plus  P right Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(5,"Minus N left  Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(6,"Minus N right Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(7,"Minus P left  Total number of PEs");
  hTotPE->GetXaxis()->SetBinLabel(8,"Minus P right Total number of PEs");

  //[L|R][NonPrimary|Primary|All][Plus|Minus]
  TH1D *hpe[2][3][2],*posPE[2][3][2],*angPE[2][3][2],*phiPE[2][3][2],*hpeAvg[2][3][2];
  TH1D *posAs[2][3],*angAs[2][3],*phiAs[2][3],*avgAs[2][3];
  int incrementNr(10000),recordNr(10000);

  for(int i=0;i<2;i++)
    for(int j=0;j<3;j++){
      for(int ipm=0;ipm<2;ipm++){

	hpe[i][j][ipm]=new TH1D(Form("hpe_%s_%s_%s",pm[ipm].c_str(),lr[i].c_str(),species[j].c_str()),
				Form("%s %s %s;number of PEs",pm[ipm].c_str(),lr[i].c_str(),species[j].c_str()),
				300,0,300);
	
	double showerFactor(1);
	if(j!=1) showerFactor=20;
	hpeAvg[i][j][ipm]=new TH1D(Form("hpeAvg_%s_%s_%s",pm[ipm].c_str(),lr[i].c_str(),species[j].c_str()),
				   Form("%dk ev Avg %s %s %s;number of PEs",
					incrementNr/1000,pm[ipm].c_str(),lr[i].c_str(),species[j].c_str()),
				   600,0,maxAvg*showerFactor);
	
	posPE[i][j][ipm]=new TH1D(Form("posPE_%s_%s_%s",pm[ipm].c_str(),lr[i].c_str(),species[j].c_str()),
				  Form("%s %s %s;position along bar[cm]",pm[ipm].c_str(),lr[i].c_str(),species[j].c_str()),
				  400,-100,100);
      
	angPE[i][j][ipm]=new TH1D(Form("angPE_%s_%s_%s",pm[ipm].c_str(),lr[i].c_str(),species[j].c_str()),
				  Form("%s %s %s;angle in shower [deg]",pm[ipm].c_str(),lr[i].c_str(),species[j].c_str()),
				  400,-100,100);      

	phiPE[i][j][ipm]=new TH1D(Form("phiPE_%s_%s_%s",pm[ipm].c_str(),lr[i].c_str(),species[j].c_str()),
				  Form("%s %s %s;global phi [deg]",pm[ipm].c_str(),lr[i].c_str(),species[j].c_str()),
				  400,0,400);      
      }

      posAs[i][j]=new TH1D(Form("posAs_%s_%s",lr[i].c_str(),species[j].c_str()),
			   Form("asym %s %s;position along bar[cm]",lr[i].c_str(),species[j].c_str()),
			   400,-100,100);
      
      angAs[i][j]=new TH1D(Form("angAs_%s_%s",lr[i].c_str(),species[j].c_str()),
			   Form("Asym %s %s;angle in shower [deg]",lr[i].c_str(),species[j].c_str()),
			   400,-100,100);      
      
      phiAs[i][j]=new TH1D(Form("phiAs_%s_%s",lr[i].c_str(),species[j].c_str()),
			   Form("Asym %s %s;global phi [deg]",lr[i].c_str(),species[j].c_str()),
			   400,0,400);      
      avgAs[i][j]=new TH1D(Form("avgAs_%s_%s",lr[i].c_str(),species[j].c_str()),
			   Form("Avg asym %s %s",lr[i].c_str(),species[j].c_str()),
			   400,-2e-3,2e-3);      
    }

  //[N|P][R|L][plus|minus]
  double TotPE[2][2][2]={{{0,0},{0,0}},{{0,0},{0,0}}};
  double AvgPE[2][2][2]={{{0,0},{0,0}},{{0,0},{0,0}}};

  //double pmVal[2]={0,0};
  float startProc=0,stopProc=21,currentProc=1,procStep=10;
  int nev=t->GetEntries();
  for(int i=0;i<nev;i++){
    if( float(i+1)/nev*100 > currentProc ){
      cout<<" at event: "<<i<<"\t"<<float(i+1)/nev*100<<"%"<<endl;
      currentProc+=procStep;
    }

    //if( i>5000000) break;
    //if( float(i+1)/nev*100<startProc || float(i+1)/nev*100>stopProc ) continue;
    t->GetEntry(i);
    double wght[2]={2*asymInfo[0]/(asymInfo[0]+asymInfo[1]),2*asymInfo[1]/(asymInfo[0]+asymInfo[1])};
    if(!primary){
      wght[0]=1;
      wght[1]=1;
    }
    //if(recordNr == incrementNr ) recordNr=evNr;
    //if(abs(angX)>30) continue;
    
    if(evNr>recordNr){
      recordNr+=incrementNr;
      for(int j=0;j<2;j++){
	for(int k=0;k<2;k++){
	  for(int ipm=0;ipm<2;ipm++){
	    hpeAvg[k][j][ipm]->Fill(AvgPE[j][k][ipm]/(float)incrementNr);
	  }
	  
	  if( (AvgPE[j][k][0] + AvgPE[j][k][1]) > 0 )
	    avgAs[k][j]->Fill( (AvgPE[j][k][0] - AvgPE[j][k][1]) /  (AvgPE[j][k][0] + AvgPE[j][k][1]) );
	}
	hpeAvg[j][2][0]->Fill((AvgPE[0][j][0]+AvgPE[1][j][0])/(float)incrementNr);
	hpeAvg[j][2][1]->Fill((AvgPE[0][j][1]+AvgPE[1][j][1])/(float)incrementNr);
      }

      for(int j=0;j<2;j++)
	for(int k=0;k<2;k++)
	  for(int ipm=0;ipm<2;ipm++)
	    AvgPE[j][k][ipm]=0;
      
    }
    
    float flip(1.);
    if(distModel == "mirror")
      flip=-1.;
    
    double pes[2]={0,0};
    if(barModel == "tracks"){
      if(x>0) pes[0]=1;
      else if(x<0) pes[1]=1;
    }else{
      if(!interpolator.getPEs(E,flip*x,flip*angX,pes[0],pes[1])) continue;
    }

    for(int ipm=0;ipm<2;ipm++)
      for(int j=0;j<2;j++){
	TotPE[primary][j][ipm]+=pes[j]*wght[ipm];
	AvgPE[primary][j][ipm]+=pes[j]*wght[ipm];
	
	hpe[j][primary][ipm]->Fill(pes[j]*wght[ipm]);
	posPE[j][primary][ipm]->Fill(x,pes[j]*wght[ipm]);
	angPE[j][primary][ipm]->Fill(angX-angXi,pes[j]*wght[ipm]);

	hpe[j][2][ipm]->Fill(pes[j]*wght[ipm]);
	posPE[j][2][ipm]->Fill(x,pes[j]*wght[ipm]);
	angPE[j][2][ipm]->Fill(angX-angXi,pes[j]*wght[ipm]);

	if(fillPhi){
	  double tmpPhi= phi < 0 ? 360 + phi : phi;
	  phiPE[j][primary][ipm]->Fill(tmpPhi,pes[j]*wght[ipm]);
	  phiPE[j][2][ipm]->Fill(tmpPhi,pes[j]*wght[ipm]);
	}      
      }
    
    
  }

  for(int ipm=0;ipm<2;ipm++)
    for(int j=0;j<2;j++)
      for(int k=0;k<2;k++){
	hTotPE->SetBinContent(ipm*4+j*2+k+1,TotPE[j][k][ipm]);
      }

  fout->cd();
  hTotPE->Write();
  for(int i=0;i<2;i++)
    for(int j=0;j<3;j++){

      for(int ipm=0;ipm<2;ipm++){
	hpe[i][j][ipm]->Write();
	hpeAvg[i][j][ipm]->Write();
	posPE[i][j][ipm]->Write();
	angPE[i][j][ipm]->Write();
	phiPE[i][j][ipm]->Write();
      }

      calcAsym(posPE[i][j][0],posPE[i][j][1],posAs[i][j]);
      posAs[i][j]->Write();
      calcAsym(angPE[i][j][0],angPE[i][j][1],angAs[i][j]);
      angAs[i][j]->Write();
      calcAsym(phiPE[i][j][0],phiPE[i][j][1],phiAs[i][j]);
      phiAs[i][j]->Write();
      avgAs[i][j]->Write();
    }
  
  fout->Close();

}


void calcAsym(TH1 *hp,TH1 *hm, TH1 *ha){
  int nb=hp->GetXaxis()->GetNbins();
  for(int i=1;i<=nb;i++){
    double vp=hp->GetBinContent(i);
    double vm=hm->GetBinContent(i);
    if( vp+vm > 0 )
      ha->SetBinContent(i,(vp-vm)/(vp+vm));
  }
}
