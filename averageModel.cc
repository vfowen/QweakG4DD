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
#include <TApplication.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TLine.h>
#include <TLegend.h>
#include <TF1.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TColor.h>
#include <TLegend.h>
#include <TPaveText.h>
using namespace std;

struct pmtdd_data {
    double al;
    double dal;
    double ar;
    double dar;
    double dd;
    double ddd;
    double abias;
    double dabias;
    double fom;
    double dfom;

    void print(void);
};

void pmtdd_data::print(void) {
    cout << this->al << "\t" << this->dal << "\t" << this->ar << "\t" << this->dar << "\t"
    << this->dd << "\t" << this->ddd << "\t"
    << this->abias << "\t" << this->dabias <<"\t"
    << this->fom << "\t"
    << this->dfom << endl;
}

pmtdd_data* printInfo(TH1D *hl,TH1D *hr);

const int nModels = 8;
//0=                                     
//1= cnst*sgn(angX) for abs(angX)=[20,40]
//2= cnst*angX                           
//3= cnst*sgn(angX)*angX^2               
//4= cnst*angX^3                         
//5= distribution weighted with P
//6= distribution weighted with M
//7= [5]/[6] microscopic distribution

//model,R/L,Upper/Lower
const int rangeTst=0;
double asymLimits[nModels][2][2]={
  {{-0.350,-0.100},{ 0.100, 0.350}},
  {{-0.350,-0.100},{ 0.100, 0.350}},
  {{-0.350,-0.100},{ 0.100, 0.350}},
  {{-0.350,-0.100},{ 0.100, 0.350}},
  {{-0.350,-0.100},{ 0.100, 0.350}},
  {{-9.000, 9.000},{-9.000, 9.000}},
  {{-9.000, 9.000},{-9.000, 9.000}},
  {{-9.000, 9.000},{-9.000, 9.000}}
};

float model(float val,int type);

std::vector<pmtdd_data*> avgValue(TString, TString, TString, Int_t);

int main(int argc, char** argv)
{

  TApplication *app = new TApplication("slopes", &argc, argv);
  // Print help
  if( argc == 1 || (0 == strcmp("--help", argv[1]))) {
    cout << " usage: build/avgModel [options]" << endl
         << " --rootfile <path to rootfile>" << endl
         << " --barmodel ideal0, ideal23, ideal23_polish, ideal23_bevel, "
         << "md1config10_23, md3config4_23, md4config4_23, md5config4_23, md6config3_23, "
         << "md7config2_23, md8config16_0 or md8config16_23"
         << endl
         << " --distmodel mirror (omit for as is)"
         << endl
         << " --scan (omit --rootfile since it will scan all 8 octant hit maps)"
         << endl;
    return 1;
  }
  
  // Read in command line paramaters
  TString barModel = "md8config16_23";
  TString distModel = "asIs";
  TString rootfile = "";
  Bool_t scan = kFALSE;
  Int_t offset = 0;
  for(Int_t i = 1; i < argc; i++) {
    if(0 == strcmp("--barmodel", argv[i])) {
      barModel = argv[i+1];
    } else if(0 == strcmp("--distmodel", argv[i])) {
      distModel = argv[i+1];
    } else if(0 == strcmp("--rootfile", argv[i])) {
      rootfile = argv[i+1];
    } else if(0 == strcmp("--offset", argv[i])) {
      offset = atoi(argv[i+1]);
    } else if(0 == strcmp("--scan", argv[i])) {
      scan = kTRUE;
    }
  }
  if(scan) {
      // List of all hitmaps to scan
      std::vector<TString> hitMaps = 
      {"hitmap/o_hits_sampled_MCoct1fixed_38e6Hits.root",
       "hitmap/o_hits_sampled_MCoct2fixed_38e6Hits.root",
       "hitmap/o_hits_sampled_MCoct3fixed_38e6Hits.root",
       "hitmap/o_hits_sampled_MCoct4fixed_38e6Hits.root",
       "hitmap/o_hits_sampled_MCoct5fixed_38e6Hits.root",
       "hitmap/o_hits_sampled_MCoct6fixed_38e6Hits.root",
       "hitmap/o_hits_sampled_MCoct7fixed_38e6Hits.root",
       "hitmap/o_hits_sampled_MCoct8fixed_38e6Hits.root"
      };
      // Vectors for plotting
      std::vector<std::vector<double>> fom(4);
      std::vector<std::vector<double>> dfom(4);
      std::vector<double> octant = {1, 2, 3, 4, 5, 6, 7, 8};
      for(unsigned int i = 0; i < hitMaps.size(); i++) {
          std::vector<pmtdd_data*> pmtdd;
          pmtdd = avgValue(barModel, distModel, hitMaps[i], offset);
          for(int j = 0; j < 4; j++) {
              fom[j].push_back(pmtdd[j]->fom);
              dfom[j].push_back(pmtdd[j]->dfom);
          }
          pmtdd.clear();
      }

      gStyle->SetPadGridX(kTRUE);
      gStyle->SetPadGridY(kTRUE);

      TCanvas* tc;
      tc = new TCanvas("tc");
      tc->Draw();
      TPad*pad1 = new TPad("pad1","pad1",0.005,0.900,0.990,0.990);
      TPad*pad2 = new TPad("pad2","pad2",0.005,0.005,0.990,0.900);
      pad1->SetFillColor(0);
      pad1->Draw();
      pad2->Draw();
      pad2->SetFillColor(0);
      pad1->cd();
      TPaveText *text = new TPaveText(.05,.1,.95,.8);
      text->AddText(Form("A_{bias}/DD for all 4 models, %s vs octant",barModel.Data()));
      text->Draw();
      pad2->cd();

      TGraphErrors *tg1 = new TGraphErrors(octant.size(), &(octant[0]), &(fom[0][0]), 0, &(dfom[0][0]));
      tg1->SetMarkerColor(kBlack);     
      tg1->SetMarkerStyle(kFullSquare);
      TGraphErrors *tg2 = new TGraphErrors(octant.size(), &(octant[0]), &(fom[1][0]), 0, &(dfom[1][0]));
      tg2->SetMarkerColor(kRed);     
      tg2->SetMarkerStyle(kFullSquare);
      TGraphErrors *tg3 = new TGraphErrors(octant.size(), &(octant[0]), &(fom[2][0]), 0, &(dfom[2][0]));
      tg3->SetMarkerColor(kBlue);     
      tg3->SetMarkerStyle(kFullSquare);
      TGraphErrors *tg4 = new TGraphErrors(octant.size(), &(octant[0]), &(fom[3][0]), 0, &(dfom[3][0]));
      tg4->SetMarkerColor(kOrange);     
      tg4->SetMarkerStyle(kFullSquare);

      TMultiGraph *mg = new TMultiGraph();
      mg->Add(tg1);
      mg->Add(tg2);
      mg->Add(tg3);
      mg->Add(tg4);
      mg->Draw("AP");
      //tg->Fit("pol1");
      mg->SetTitle("");
      mg->GetXaxis()->SetTitle("octant");
      mg->GetYaxis()->SetTitle("A_{bias}/DD (%)");

      TLegend *leg;                         
      leg = new TLegend(0.6,0.7,0.9,0.9);
      leg->AddEntry(tg1,"model 1","p");
      leg->AddEntry(tg2,"model 2","p");
      leg->AddEntry(tg3,"model 3","p");
      leg->AddEntry(tg4,"model 4","p");
      leg->Draw();

  } else {
      std::vector<pmtdd_data*> pmtdd;
      pmtdd = avgValue(barModel, distModel, rootfile, offset);
  }
    /* TApplication crap. */
    app->Run();
    return 0;
}

std::vector<pmtdd_data*> avgValue(TString barModel, TString distModel, TString rootfile, Int_t offset) {
  interpolatePEs interpolator(barModel.Data());
  //interpolator.verbosity=1;
  
  // Print out command line paramaters
  cout << "bar model:  " << barModel << endl
       << "distribution model:  " << distModel << endl
       << "using rootfile:  " << rootfile << endl
       << "using offset:  " << offset << endl;

  TFile *fin=TFile::Open(rootfile.Data(),"READ");
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
  
  TFile *fout=new TFile(Form("o_avgModel_%s_%s_offset_%d.root", barModel.Data(),
                             distModel.Data(),offset),"RECREATE");

  string lr[2]={"R","L"};
  TH1D *hpe[2][nModels],*posPE[2][nModels],*angPE[2][nModels];
  TH1D *as[2][nModels];
  
  for(int i=0;i<nModels;i++)
    for(int j=0;j<2;j++){
      as[j][i]=new TH1D(Form("as%s_%d",lr[j].c_str(),i),Form("model %d %s PMT;asymmetry [ppm]",i,lr[j].c_str()),
			400,asymLimits[i][j][0],asymLimits[i][j][1]);      
      hpe[j][i] = new TH1D(Form("pe%s_%d",lr[j].c_str(),i),Form("model %d %s #PEs",i,lr[j].c_str()),
			   500,0,500);
      posPE[j][i] = new TH1D(Form("pe%s_pos_%d",lr[j].c_str(),i),
			     Form("model %d %s #PEs;position [cm]",i,lr[j].c_str()),
			     200,-100,100);
      angPE[j][i] = new TH1D(Form("pe%s_ang_%d",lr[j].c_str(),i),
			     Form("model %d %s #PEs;angle [deg]",i,lr[j].c_str()),
			     240,-120,120);
    }
    
  std::vector<double> avgStepL(nModels,0);
  std::vector<double> avgStepR(nModels,0);
  std::vector<double> lAvgTotPE(nModels,0);
  std::vector<double> rAvgTotPE(nModels,0);
  
  double stepSize=0.2;
  double currentStep=stepSize;

  int nev=t->GetEntries();

  for(int i=0;i<nev;i++){
    t->GetEntry(i);
    if(i%1000000==1) cout<<" at event: "<<i<<" "<<float(i+1)/nev*100<<"%"<<endl;

    if(float(i+1)/nev*100>currentStep){
      for(int imod=1;imod<nModels;imod++){
	if(avgStepR[0]>0 && avgStepL[0]>0){
	  as[0][imod]->Fill( avgStepR[imod]/avgStepR[0]*1e6 );
	  as[1][imod]->Fill( avgStepL[imod]/avgStepL[0]*1e6 );
	  if(rangeTst){
	    cout<<i<<" "<<imod<<" R "<<avgStepR[imod]<<" "<<avgStepR[0]<<" "<<avgStepR[imod]/avgStepR[0]*1e6<<endl;
	    cout<<i<<" "<<imod<<" L "<<avgStepL[imod]<<" "<<avgStepL[0]<<" "<<avgStepL[imod]/avgStepL[0]*1e6<<endl;
	  }
	}
	avgStepL[imod]=0;
	avgStepR[imod]=0;
      }
      avgStepL[0]=0;
      avgStepR[0]=0;
	
      currentStep+=stepSize;
    }
    
    if(i>1000000 && rangeTst) break;

    float flip(1.);
    if(distModel == "mirror")
      flip=-1.;

    double lpe(-1),rpe(-1);
    if(!interpolator.getPEs(E,flip*x+offset,flip*angX,lpe,rpe)) continue;
    // cout<<" asdf L R "<<lpe<<" "<<rpe<<endl;
    // std::cin.ignore();
    
    //nModels-1 because microscopic is special and done at the end
    for(int imod=0;imod<nModels-1;imod++){

      double asym=model(angX-angXi,imod);
      if(imod>4){
	double P=(asymPpM+asymPmM)/2;
	double M=(asymPpM-asymPmM)/2;
	if(imod==5){
	  asym=P;
	}else if(imod==6)
	  asym=M;

	if(distModel == "mirror" ) asym=-asym;
      }

      avgStepL[imod]+=asym*lpe;
      avgStepR[imod]+=asym*rpe;
      lAvgTotPE[imod]+=asym*lpe;
      rAvgTotPE[imod]+=asym*rpe;
      
      hpe[0][imod]->Fill((1.+asym)*rpe);
      posPE[0][imod]->Fill(x,asym*rpe);
      angPE[0][imod]->Fill(angX-angXi,asym*rpe);
      hpe[1][imod]->Fill((1.+asym)*lpe);
      posPE[1][imod]->Fill(x,asym*lpe);
      angPE[1][imod]->Fill(angX-angXi,asym*lpe);
      
    }        
  }

  int posBin=posPE[0][7]->GetXaxis()->GetNbins();
  int angBin=angPE[0][7]->GetXaxis()->GetNbins();
  for(int j=0;j<2;j++){
    for(int i=1;i<=posBin;i++){
      double a=posPE[j][5]->GetBinContent(i);
      double b=posPE[j][6]->GetBinContent(i);
      if(a+b>0)
	posPE[j][7]->SetBinContent(i, (a-b)/(a+b) );
    }
    for(int i=1;i<=angBin;i++){
      double a=angPE[j][5]->GetBinContent(i);
      double b=angPE[j][6]->GetBinContent(i);
      if(a+b>0)
	angPE[j][7]->SetBinContent(i, (a-b)/(a+b) );
    }
  }
  
  cout<<endl<<"total PE average: A_L A_R DD A_ave A_ave/DD"<<endl;
  for(int imod=1;imod<nModels;imod++)
    cout<<imod<<"\t"<<lAvgTotPE[imod]/lAvgTotPE[0]<<"\t"<<rAvgTotPE[imod]/rAvgTotPE[0]
	<<"\t"<<lAvgTotPE[imod]/lAvgTotPE[0]-rAvgTotPE[imod]/rAvgTotPE[0]
	<<"\t"<<(lAvgTotPE[imod]/lAvgTotPE[0]+rAvgTotPE[imod]/rAvgTotPE[0])/2
	<<"\t"<<
      ((lAvgTotPE[imod]/lAvgTotPE[0]+rAvgTotPE[imod]/rAvgTotPE[0])/2)/
      (lAvgTotPE[imod]/lAvgTotPE[0]-rAvgTotPE[imod]/rAvgTotPE[0])<<endl;
  fout->cd();
  TNamed* tn1;                              
  TNamed* tn2;                              
  TNamed* tn3;                              
  if("md1config10_23" == barModel) {
      tn1 = new TNamed("bar","md1config10");
      tn2 = new TNamed("angle","angle 23");
  }else if("md3config4_23" == barModel) {
      tn1 = new TNamed("bar","md3config4");
      tn2 = new TNamed("angle","angle 23");
  }else if("md4config4_23" == barModel) {
      tn1 = new TNamed("bar","md4config4");
      tn2 = new TNamed("angle","angle 23");
  }else if("md5config4_23" == barModel) {
      tn1 = new TNamed("bar","md5config4");
      tn2 = new TNamed("angle","angle 23");
  }else if("md6config3_23" == barModel) {
      tn1 = new TNamed("bar","md6config3");
      tn2 = new TNamed("angle","angle 23");
  }else if("md7config2_23" == barModel) {
      tn1 = new TNamed("bar","md7config2");
      tn2 = new TNamed("angle","angle 23");
  }else if("md8config16_0" == barModel) {
      tn1 = new TNamed("bar","md8config16");
      tn2 = new TNamed("angle","angle 0");
  }else if("md8config16_23" == barModel) {
      tn1 = new TNamed("bar","md8config16");
      tn2 = new TNamed("angle","angle 23");
  }else if("ideal0" == barModel) {
      tn1 = new TNamed("bar","ideal bar");
      tn2 = new TNamed("angle","angle 0");
  }else if("ideal23" == barModel) {
      tn1 = new TNamed("bar","ideal bar");
      tn2 = new TNamed("angle","angle 23");
  }else if("ideal23_polish" == barModel) {
      tn1 = new TNamed("bar","ideal bar with polish");
      tn2 = new TNamed("angle","angle 23");
  }else if("ideal23_bevel" == barModel) {
      tn1 = new TNamed("bar","ideal bar with bevel");
      tn2 = new TNamed("angle","angle 23");
  }else{
    cout<<"not sure what bar model you beam by: "<<barModel<<endl;
    exit(3);
  }
  
  if("mirror" == distModel) {
	  tn3 = new TNamed("distribution", "mirror");
  }
  else {
	  tn3 = new TNamed("distribution", "as is");
  }
  tn1->Write();                              
  tn2->Write();                              
  tn3->Write();

  cout<<endl<<" average asymmetry histogram results: A_L dA_L A_R dA_R DD dDD A_bias dA_bia A_bias/DD*100"<<endl;
  vector< pmtdd_data* > pmtdd;
  for(int j=0;j<nModels;j++){      
    for(int i=0;i<2;i++){
      hpe[i][j]->Write();
      posPE[i][j]->Write();
      angPE[i][j]->Write();
      as[i][j]->Write();
    }

    if(j>0){
      cout<<j<<"\t";
      pmtdd.push_back(printInfo(as[1][j],as[0][j]));
      if(as[0][j]->GetBinContent(0)>0 || as[0][j]->GetBinContent(as[0][j]->GetXaxis()->GetNbins()+1)>0 ||
	 as[1][j]->GetBinContent(0)>0 || as[1][j]->GetBinContent(as[1][j]->GetXaxis()->GetNbins()+1)>0){
	cout<<"!!!!! overUnder flow: R L: "<<endl;
	cout<<as[0][j]->GetBinContent(0)<<"\t"
	    <<as[0][j]->GetBinContent(as[0][j]->GetXaxis()->GetNbins()+1)<<"\t"
	    <<as[1][j]->GetBinContent(0)<<"\t"
	    <<as[1][j]->GetBinContent(as[1][j]->GetXaxis()->GetNbins()+1)<<endl;
      }
    }
  }

  for(unsigned int i = 0; i < pmtdd.size(); i++) {

  }

  fout->Close();
  return pmtdd;
}

//models go here
float model(float val,int type){

  if(type==0)
    return 1;  
  else if(type==1 && (abs(val)>=20 && abs(val)<40) )
    return 4e-6*val/abs(val);
  else if(type==2)
    return 4e-8*val;
  else if(type==3)
    return 1.5e-9*val/abs(val)*pow(val,2);
  else if(type==4)
    return 4e-11*pow(val,3);
  else if(type==5)
    return 0; //reserved for microscopic model

  return 0;
}

pmtdd_data* printInfo(TH1D *hl,TH1D *hr){
    pmtdd_data* pmtdd = new pmtdd_data();
    pmtdd->al = hl->GetMean();
    pmtdd->dal = hl->GetMeanError();
    pmtdd->ar = hr->GetMean();
    pmtdd->dar = hr->GetMeanError();
    // Double difference and error
    pmtdd->dd = pmtdd->al-pmtdd->ar;
    pmtdd->ddd = sqrt(pmtdd->dar*pmtdd->dar+pmtdd->dal*pmtdd->dal);
    // a_bias and error
    pmtdd->abias = (pmtdd->al+pmtdd->ar)/2;
    pmtdd->dabias = sqrt(pmtdd->dar*pmtdd->dar+pmtdd->dal*pmtdd->dal)/2;
    // figure of merit (a_bias/dd*100) and error
    pmtdd->fom = ((pmtdd->al+pmtdd->ar)/2)/(pmtdd->al-pmtdd->ar)*100;
    pmtdd->dfom = sqrt(pow(pmtdd->fom,2)*(pow(pmtdd->ddd/pmtdd->dd,2)+pow(pmtdd->dabias/pmtdd->abias,2)));
    pmtdd->print();

    return pmtdd;
}
