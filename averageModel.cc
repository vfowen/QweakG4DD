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
#include <TApplication.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TGraph.h>
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
void drawFunctions();
clock_t tStart;
double model(float val,int type);

const int nModels = 308;
const int rangeTst=0;
int nModelsEff(nModels-301);//default is only [0,6]
vector<vector<vector<double>>> asymLimits;
int withShower(0);

//gpr Cnt value and phase space functions 
vector<vector<double>> gprFcts;
vector<double> gprXcent,gprX;
void readGpr(string fnm);


std::vector<pmtdd_data*> avgValue(TString, TString, TString, float, Int_t, string);

int main(int argc, char** argv)
{
  tStart=clock();

  // Print help
  if( argc == 1 || (0 == strcmp("--help", argv[1]))) {
    cout << " usage: build/avgModel [options]" << endl
         << " --rootfile <path to rootfile>" << endl
         << " --barmodel ideal0, ideal23, ideal23_polish, ideal23_bevel, "
         << "ideal23_glue, ideal23_thickdiff, ideal23_RBevelEndcapCentralGlueSideOnly, ideal23_RBevelEndcapPMTSideOnly, ideal23_RBevelLongAxisOnly "
         << "md1config10_23, md1config16_model2_23, md1_model2_lightGuideMod md2config5_23, "
         << "md2config5_model2_23, md3config4_23, md4config4_23, md5config4_23, "
         << "md6config3_23, md7config2_23, md8config16_0 or md8config16_23"
         << endl
         << " --distmodel mirror (omit for as is)"
         << endl
         << " --scan (omit --rootfile since it will scan all 8 octant hit maps)"
         << endl
         << " --lightParaUncert (optional; instead of taking the central value for the PE(x,x',E) it sampled from a gaussian)"
         << endl
         << " --drawFctions <#> (optional; make output file with the effective model functions."
	 <<"\t if val==0 just draw and ignore the rest of the program. other values proceed as normal"
         << endl
         << " --scan1fct <fnm> <0/1> (optional; arg2==0 look in file \"fnm\" for the gprCentralValue as model 7. arg2==1 in addition to central value look for 300 TGraphs giving the phase space functions)"
         << endl
      	 << " --processShower (optional: if you have a hitmap with secondary hits this will scale the asymmetry appropriately)" << endl
      	 << " --suffix <name to append to outFile> (omit for default)" << endl;
    return 1;
  }
  
  // Read in command line paramaters
  TString barModel = "md8config16_23";
  TString distModel = "asIs";
  TString rootfile = "";
  Bool_t scan = kFALSE;
  float offset = 0;
  Int_t peUncert(0);
  string suffix = "";
  
  for(Int_t i = 1; i < argc; i++) {    
    if(0 == strcmp("--drawFctions", argv[i])) {
      drawFunctions();
      if(atoi(argv[i+1])==0)
	return 0;
    }else if(0 == strcmp("--scan1fct", argv[i])) {
      int fctBool=atoi(argv[i+2]);
      nModelsEff += 1 + fctBool*300;
      cout<<"start reading GPR. Number of effective models: "<<nModelsEff<<endl;
      readGpr(argv[i+1]);
    }else if(0 == strcmp("--barmodel", argv[i])) {
      barModel = argv[i+1];
    }else if(0 == strcmp("--processShower", argv[i])) {
      withShower=1;
    } else if(0 == strcmp("--distmodel", argv[i])) {
      distModel = argv[i+1];
    } else if(0 == strcmp("--rootfile", argv[i])) {
      rootfile = argv[i+1];
    } else if(0 == strcmp("--offset", argv[i])) {
      offset = atof(argv[i+1]);
    } else if(0 == strcmp("--scan", argv[i])) {
      scan = kTRUE;
    } else if(0 == strcmp("--lightParaUncert", argv[i])) {
      peUncert = 1;
    }else if(0 == strcmp("--suffix", argv[i])) {
      suffix = argv[i+1];
    }

  }

  //set Limits
  //model,R/L,Upper/Lower
  std::vector<double> dummyL={-0.500,-0.000};
  std::vector<double> dummyR={ 0.000, 0.500};
  std::vector<std::vector<double>> dummyLimit={dummyR,dummyL};
  for(int i=0;i<nModelsEff;i++)
    asymLimits.push_back(dummyLimit);

  TApplication *app = new TApplication("slopes", &argc, argv);

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
    std::vector<std::vector<double>> fom(6);
    std::vector<std::vector<double>> dfom(6);
    std::vector<std::vector<double>> dd(6);
    std::vector<std::vector<double>> ddd(6);
    std::vector<std::vector<double>> abias(6);
    std::vector<std::vector<double>> dabias(6);
    std::vector<double> octant = {1, 2, 3, 4, 5, 6, 7, 8};
    for(unsigned int i = 0; i < hitMaps.size(); i++) {
      std::vector<pmtdd_data*> pmtdd;
      pmtdd = avgValue(barModel, distModel, hitMaps[i], offset,peUncert,suffix);
      for(int j = 0; j < 6; j++) {
	    fom[j].push_back(pmtdd[j]->fom);
	    dfom[j].push_back(pmtdd[j]->dfom);
	    dd[j].push_back(pmtdd[j]->dd);
	    ddd[j].push_back(pmtdd[j]->ddd);
	    abias[j].push_back(pmtdd[j]->abias);
	    dabias[j].push_back(pmtdd[j]->dabias);
      }
      pmtdd.clear();
    }
    for(int j = 0; j < 6; j++) {
      std::cout << "The smallest element in model " << j+1 << " is " << *std::min_element(fom[j].begin(),fom[j].end()) << std::endl;
      std::cout << "The largest element in model " << j+1 << " is " << *std::max_element(fom[j].begin(),fom[j].end()) << std::endl;
      std::cout << "(max-min)/2 for model " << j+1 << " is " << (*std::max_element(fom[j].begin(),fom[j].end())-*std::min_element(fom[j].begin(),fom[j].end()))/2 << endl;
    }

    gStyle->SetPadGridX(kTRUE);
    gStyle->SetPadGridY(kTRUE);

    vector<TCanvas*> tc(3);
    vector<TPad*> pad1(3);
    vector<TPad*> pad2(3);
    vector<TPaveText*> text(3);
    vector<TGraphErrors*> tg1(3);
    vector<TGraphErrors*> tg2(3);
    vector<TGraphErrors*> tg3(3);
    vector<TGraphErrors*> tg4(3);
    vector<TGraphErrors*> tg5(3);
    vector<TGraphErrors*> tg6(3);
    vector<TMultiGraph*> mg(3);
    vector<TLegend*> leg(3);
    for(int i = 0; i < 3; i++) {
        tc[i] = new TCanvas(Form("tc%d",i));
        tc[i]->Draw();
        pad1[i] = new TPad(Form("pad1%d",i),Form("pad1%d",i),0.005,0.900,0.990,0.990);
        pad2[i] = new TPad(Form("pad2%d",i),Form("pad2%d",i),0.005,0.005,0.990,0.900);
        pad1[i]->SetFillColor(0);
        pad1[i]->Draw();
        pad2[i]->Draw();
        pad2[i]->SetFillColor(0);
        pad1[i]->cd();
        text[i] = new TPaveText(.05,.1,.95,.8);
        if(i == 0) {
            text[i]->AddText(Form("A_{bias}/DD for all 6 models, %s vs octant",barModel.Data()));
        }
        else if(i == 1) {
            text[i]->AddText(Form("DD for all 6 models, %s vs octant",barModel.Data()));
        }
        else if(i == 2) {
            text[i]->AddText(Form("A_{bias} for all 6 models, %s vs octant",barModel.Data()));
        }
        text[i]->Draw();
        pad2[i]->cd();

        if(i == 0) {
            tg1[i] = new TGraphErrors(octant.size(), &(octant[0]), &(fom[0][0]), 0, &(dfom[0][0]));
            tg2[i] = new TGraphErrors(octant.size(), &(octant[0]), &(fom[1][0]), 0, &(dfom[1][0]));
            tg3[i] = new TGraphErrors(octant.size(), &(octant[0]), &(fom[2][0]), 0, &(dfom[2][0]));
            tg4[i] = new TGraphErrors(octant.size(), &(octant[0]), &(fom[3][0]), 0, &(dfom[3][0]));
            tg5[i] = new TGraphErrors(octant.size(), &(octant[0]), &(fom[4][0]), 0, &(dfom[4][0]));
            tg6[i] = new TGraphErrors(octant.size(), &(octant[0]), &(fom[5][0]), 0, &(dfom[5][0]));
        }
        else if(i == 1) {
            tg1[i] = new TGraphErrors(octant.size(), &(octant[0]), &(dd[0][0]), 0, &(ddd[0][0]));
            tg2[i] = new TGraphErrors(octant.size(), &(octant[0]), &(dd[1][0]), 0, &(ddd[1][0]));
            tg3[i] = new TGraphErrors(octant.size(), &(octant[0]), &(dd[2][0]), 0, &(ddd[2][0]));
            tg4[i] = new TGraphErrors(octant.size(), &(octant[0]), &(dd[3][0]), 0, &(ddd[3][0]));
            tg5[i] = new TGraphErrors(octant.size(), &(octant[0]), &(dd[4][0]), 0, &(ddd[4][0]));
            tg6[i] = new TGraphErrors(octant.size(), &(octant[0]), &(dd[5][0]), 0, &(ddd[5][0]));
        }
        else if(i == 2) {
            tg1[i] = new TGraphErrors(octant.size(), &(octant[0]), &(abias[0][0]), 0, &(dabias[0][0]));
            tg2[i] = new TGraphErrors(octant.size(), &(octant[0]), &(abias[1][0]), 0, &(dabias[1][0]));
            tg3[i] = new TGraphErrors(octant.size(), &(octant[0]), &(abias[2][0]), 0, &(dabias[2][0]));
            tg4[i] = new TGraphErrors(octant.size(), &(octant[0]), &(abias[3][0]), 0, &(dabias[3][0]));
            tg5[i] = new TGraphErrors(octant.size(), &(octant[0]), &(abias[4][0]), 0, &(dabias[4][0]));
            tg6[i] = new TGraphErrors(octant.size(), &(octant[0]), &(abias[5][0]), 0, &(dabias[5][0]));
        }

        tg1[i]->SetMarkerColor(kBlack);     
        tg1[i]->SetMarkerStyle(kFullSquare);
        tg2[i]->SetMarkerColor(kRed);     
        tg2[i]->SetMarkerStyle(kFullSquare);
        tg3[i]->SetMarkerColor(kBlue);     
        tg3[i]->SetMarkerStyle(kFullSquare);
        tg4[i]->SetMarkerColor(kOrange);     
        tg4[i]->SetMarkerStyle(kFullSquare);
        tg5[i]->SetMarkerColor(kGray);     
        tg5[i]->SetMarkerStyle(kFullSquare);
        tg6[i]->SetMarkerColor(kBlack);     
        tg6[i]->SetMarkerStyle(kFullSquare);

        mg[i] = new TMultiGraph();
        // disable model 1
        //mg[i]->Add(tg1[i]);
        mg[i]->Add(tg2[i]);
        mg[i]->Add(tg3[i]);
        mg[i]->Add(tg4[i]);
        mg[i]->Add(tg5[i]);
        mg[i]->Add(tg6[i]);
        mg[i]->Draw("AP");
        //tg[i]->Fit("pol1");
        mg[i]->SetTitle("");
        mg[i]->GetXaxis()->SetTitle("octant (hit map)");
        if(i == 0) {
            mg[i]->GetYaxis()->SetTitle("A_{bias}/DD (%)");
        }
        else if(i == 1) {
            mg[i]->GetYaxis()->SetTitle("DD (ppm)");
        }
        else if(i == 2) {
            mg[i]->GetYaxis()->SetTitle("A_{bias} (ppm)");
        }

        leg[i] = new TLegend(0.6,0.7,0.9,0.9);
        //leg[i]->AddEntry(tg1[i],"model 1","p");
        leg[i]->AddEntry(tg2[i],"model 2","p");
        leg[i]->AddEntry(tg3[i],"model 3","p");
        leg[i]->AddEntry(tg4[i],"model 4","p");
        leg[i]->AddEntry(tg5[i],"model 5 (hybrid)","p");
        leg[i]->AddEntry(tg6[i],"model 6 (hybrid)","p");
        leg[i]->Draw();
    }
    /* TApplication crap. */
    app->Run();
  } else {
    std::vector<pmtdd_data*> pmtdd;
    pmtdd = avgValue(barModel, distModel, rootfile, offset,peUncert,suffix);
  }

  cout<<" Running time[s]: "<< (double) ((clock() - tStart)/CLOCKS_PER_SEC)<<endl;
  return 0;
}

std::vector<pmtdd_data*> avgValue(TString barModel, TString distModel, TString rootfile, float offset, Int_t peUncert, string suffix) {
  interpolatePEs interpolator(barModel.Data(),peUncert);
  //interpolator.verbosity=1;

  // Print out command line paramaters
  cout << "bar model:  " << barModel << endl
       << "distribution model:  " << distModel << endl
       << "using rootfile:  " << rootfile << endl
       << "using offset:  " << offset << endl;
  if(peUncert)
    cout<< "sampling PE values from Gaussian"<<endl;
  else
    cout<< "central PE values"<<endl;

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

  string outNm="";
  if(suffix=="")
    outNm=Form("o_avgModel_%s_%s_offset_%4.2f_Nmodels_%d.root", barModel.Data(),
	       distModel.Data(),offset,nModelsEff);
  else
    outNm=Form("o_avgModel_%s_%s_offset_%4.2f_Nmodels_%d_%s.root", barModel.Data(),
	       distModel.Data(),offset,nModelsEff,suffix.c_str());    
  TFile *fout=new TFile(outNm.c_str(),"RECREATE");

  string lr[2]={"R","L"};
  TH1D *hpe[2][nModels],*posPE[2][nModels],*angPE[2][nModels];
  TH1D *as[2][nModels];

  // Histogram for electron population (x)
  TH1D *x_pos = new TH1D("x_pos","electron population vs pos",200,-100,100);
  //t->Draw("x>>x_pos","primary == 1 && abs(angX) < 89 && abs(x) < 100 && E > 3","goff");
  
  for(int i=0;i<nModelsEff;i++)
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
  float currentProc=0,procStep=10;
  for(int i=0;i<nev;i++){
    t->GetEntry(i);

    if( !withShower && !primary ) continue;
    
    if( float(i+1)/nev*100 > currentProc ){
      cout<<" at event: "<<i<<"\t"<<float(i+1)/nev*100<<"% | time passed: "<< (double) ((clock() - tStart)/CLOCKS_PER_SEC)<<" s"<<endl;
      currentProc+=procStep;
    }
        
    if(float(i+1)/nev*100>currentStep){
      for(int imod=1;imod<nModelsEff;imod++){
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

    // SIGN FIX: This code will now use the tracking coordinates yt, angYt, and angYt_i. I also introduce angYt_rel as the relative angle.
    // the "flip" reverses the input distribution around the origin...
    float yt = -1.0*flip*x;
    float angYt = -1.0*flip*angX;
    float angYti = -1.0*flip*angXi;
    float angYt_rel = angYt - angYti;    

    // SIGN FIX: In Jie's light model, she compares left(x_sim) with right (y_track).  To fix this, we need to use her light model carefully:
    // lpe(yt) = rpe_jie(x), etc.   to do this, call with (E,x,angX,rpe,lpe) instead of (E,yt,angYt,lpe,rpe)
    double lpe(-1),rpe(-1);
    if(!interpolator.getPEs(E,x+offset,angX,rpe,lpe)) continue;
    //    if(!interpolator.getPEs(E,y+offset,angYt,lpe,rpe)) continue;  // use this line instead for light flip check: lpe_jie(y) = lpe(y), etc.
    
    for(int imod=0;imod<nModelsEff;imod++){
      double asym=1.;
      if(primary==1)
	// SIGN FIX: asymmetry should be positive for positive relative angles along the y-axis.
	asym=model(angYt_rel,imod);
      else if(imod!=0)
	asym=0;
      
      avgStepL[imod]+=asym*lpe;
      avgStepR[imod]+=asym*rpe;
      lAvgTotPE[imod]+=asym*lpe;
      rAvgTotPE[imod]+=asym*rpe;
      
      hpe[0][imod]->Fill((1.+asym)*rpe);
      posPE[0][imod]->Fill(yt,asym*rpe);
      angPE[0][imod]->Fill(angYt_rel,asym*rpe);

      hpe[1][imod]->Fill((1.+asym)*lpe);
      posPE[1][imod]->Fill(yt,asym*lpe);
      angPE[1][imod]->Fill(angYt_rel,asym*lpe);
      
    }        
  }
  
  cout<<endl<<"total PE average: A_L A_R DD A_ave A_ave/DD"<<endl;
  // SIGN FIX: not terribly relevent, but still: always take difference as R-L (not L-R)
  for(int imod=1;imod<nModelsEff;imod++)
    cout<<imod<<"\t"<<lAvgTotPE[imod]/lAvgTotPE[0]<<"\t"<<rAvgTotPE[imod]/rAvgTotPE[0]
	<<"\t"<<rAvgTotPE[imod]/rAvgTotPE[0]-lAvgTotPE[imod]/lAvgTotPE[0]
	<<"\t"<<(lAvgTotPE[imod]/lAvgTotPE[0]+rAvgTotPE[imod]/rAvgTotPE[0])/2
	<<"\t"<<
      ((lAvgTotPE[imod]/lAvgTotPE[0]+rAvgTotPE[imod]/rAvgTotPE[0])/2)/
      (rAvgTotPE[imod]/rAvgTotPE[0]-lAvgTotPE[imod]/lAvgTotPE[0])<<endl;
  fout->cd();
  TNamed* tn1;                              
  TNamed* tn2;                              
  TNamed* tn3;                              
  if("md1config10_23" == barModel) {
    tn1 = new TNamed("bar","md1config10");
    tn2 = new TNamed("angle","angle 23");
  }else if("md1config16_model2_23" == barModel) {
    tn1 = new TNamed("bar","md1config16_model2");
    tn2 = new TNamed("angle","angle 23");
  }else if("md1_model2_lightGuideMod" == barModel) {
    tn1 = new TNamed("bar","md1_model2_lightGuideMod");
    tn2 = new TNamed("angle","angle 23");
  }else if("md2config5_23" == barModel) {
    tn1 = new TNamed("bar","md2config5");
    tn2 = new TNamed("angle","angle 23");
  }else if("md2config5_model2_23" == barModel) {
    tn1 = new TNamed("bar","md2config5_model2");
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
  }else if("ideal23_glue" == barModel) {
    tn1 = new TNamed("bar","ideal bar with glue");
    tn2 = new TNamed("angle","angle 23");
  }else if("ideal23_thickdiff" == barModel) {
    tn1 = new TNamed("bar","ideal bar with thickness difference");
    tn2 = new TNamed("angle","angle 23");
  }else if("ideal23_RBevelEndcapCentralGlueSideOnly" == barModel) {
    tn1 = new TNamed("bar","ideal bar with bevel endcaps and central glue");
    tn2 = new TNamed("angle","angle 23");
  }else if("ideal23_RBevelEndcapPMTSideOnly" == barModel) {
    tn1 = new TNamed("bar","ideal bar with bevel PMT side");
    tn2 = new TNamed("angle","angle 23");
  }else if("ideal23_RBevelLongAxisOnly" == barModel) {
    tn1 = new TNamed("bar","ideal bar with bevel long axis only");
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
  x_pos->Write();
  for(int j=0;j<nModelsEff;j++){      
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
	cout<<"!!!!! underOver flow: R L: "<<endl;
	cout<<as[0][j]->GetBinContent(0)<<"\t"
	    <<as[0][j]->GetBinContent(as[0][j]->GetXaxis()->GetNbins()+1)<<"\t"
	    <<as[1][j]->GetBinContent(0)<<"\t"
	    <<as[1][j]->GetBinContent(as[1][j]->GetXaxis()->GetNbins()+1)<<endl;
      }
    }
  }

  fout->Close();
  return pmtdd;
}

//models go here
double model(float val,int type){
  //0=                                     
  //1= cnst*sgn(angX) for abs(angX)=[20,40]
  //2= cnst*angX                           
  //3= cnst*sgn(angX)*angX^2               
  //4= cnst*angX^3                         
  //5= -3.9  (M2)  + 5.8 (M3) -0.9 (M4)
  //6= -0.9  (M2)  + 2.8 (M3) -0.9 (M4)
  //7= microscopic model
  //8-308= GPR functions
  double showerScales[7]={1.,18.8,18.5,18.2,18.0,17.9,18.2};
  double showerFactor=1;
  if(withShower && type<7)
    showerFactor = showerScales[type];
  
  if(val==0 && type!=0) return 0;

  if(type>=nModelsEff) return 0;//set asymmetry to 0 if not using microscopic or GPR

  if(type==0)
    return 1;  
  else if(type==1){
    if( (abs(val)>=20 && abs(val)<40) )
      return 0.759 * 4e-6 * val/abs(val) * 290/478 * showerFactor;
    else
      return 0;
  }else if(type==2)
    return 0.713 * 4e-8 * val * 290/377 *showerFactor;
  else if(type==3)
    return 0.685 * 1.5e-9 * abs(pow(val,3))/val * 290/502 *showerFactor;
  else if(type==4)
    return 0.610 * 4e-11 * pow(val,3) * 290/561 *showerFactor;
  else if(type==5) 
    return
      (-3.9 * 0.713 * 4e-8 * val
       +5.8 * 0.685 * 1.5e-9 * abs(pow(val,3))/val
       -0.9 * 0.610 * 4e-11 * pow(val,3) ) * 290/934 *showerFactor;
  else if(type==6)
    return
      (-0.9 * 0.713 * 4e-8 * val
       +2.8 * 0.685 * 1.5e-9 * abs(pow(val,3))/val
       -0.9 * 0.610 * 4e-11 * pow(val,3) ) * 290/561 *showerFactor;
  else if(type==7){
    int nFct=type-7;    
    int bin = int(lower_bound(gprXcent.begin(),gprXcent.end(),abs(val)) - gprXcent.begin());
    double xL = gprXcent[bin-1];
    double xH = gprXcent[bin];
    double yL = gprFcts[nFct][bin-1];
    double yH = gprFcts[nFct][bin];
    return -val/abs(val)*(yL + (yH - yL)*(abs(val) - xL)/(xH - xL))/1e6 * 0.787;//FIXME 0.787 is for the wrong beam polarization factor
  }else if(type<308){
    int nFct=type-7;    
    int bin = int(lower_bound(gprX.begin(),gprX.end(),abs(val)) - gprX.begin());
    double xL = gprX[bin-1];
    double xH = gprX[bin];
    double yL = gprFcts[nFct][bin-1];
    double yH = gprFcts[nFct][bin];
    return -val/abs(val)*(yL + (yH - yL)*(abs(val) - xL)/(xH - xL))/1e6 * 0.787;//FIXME 0.787 is for the wrong beam polarization factor
  }else
    return 0;      

  return 0;
}

void readGpr(string fnm){

  std::vector<double> tst;

  int nBins(0);
  TFile *fin=TFile::Open(fnm.c_str(),"READ");
  TH1D *hin=(TH1D*)fin->Get("ho");
  nBins=hin->GetXaxis()->GetNbins();

  for(int i=1;i<=nBins;i++){
    double x,y;
    x = hin->GetBinCenter(i);
    y = hin->GetBinContent(i);
    if(x<0) continue;
    if(x>90) continue;

    gprXcent.push_back(x);
    tst.push_back(y);
  }

  gprFcts.push_back(tst);
  
  for(int j=8;j<nModelsEff;j++){
    tst.clear();
    int nFct=j-8;
    TGraph *gin=(TGraph*)fin->Get(Form("oneFct_%d",nFct));
    nBins=gin->GetN();
    for(int i=0;i<nBins;i++){
      double x,y;
      gin->GetPoint(i,x,y);
      if(x<0) continue;
      if(x>90) continue;

      if(j>8){
	int currentPnt=tst.size();
	if(gprX[currentPnt] != x){
	  cerr<<__PRETTY_FUNCTION__<<" line: "<<__LINE__<<endl
	      <<"\t x positions don't match for function "<<j<<" "<<currentPnt<<" <> "<<gprX[currentPnt]<<" "<<x<<endl;
	}
      }else
	gprX.push_back(x);
      
      tst.push_back(y);
    }
    gprFcts.push_back(tst);
  }

  cout<<"read a total of: "<<gprFcts.size()<<" functions"<<endl;
  fin->Close();  
}

pmtdd_data* printInfo(TH1D *hl,TH1D *hr){
  pmtdd_data* pmtdd = new pmtdd_data();
  pmtdd->al = hl->GetMean();
  pmtdd->dal = hl->GetMeanError();
  pmtdd->ar = hr->GetMean();
  pmtdd->dar = hr->GetMeanError();
  // Double difference and error
  // SIGN FIX: now aR-aL
  pmtdd->dd = pmtdd->ar-pmtdd->al;
  pmtdd->ddd = sqrt(pmtdd->dar*pmtdd->dar+pmtdd->dal*pmtdd->dal);
  // a_bias and error
  // SIGN FIX: A_bias= (pmtdd->ar+pmtdd->al)/2
  pmtdd->abias = (pmtdd->al+pmtdd->ar)/2;
  pmtdd->dabias = sqrt(pmtdd->dar*pmtdd->dar+pmtdd->dal*pmtdd->dal)/2;
  // figure of merit (a_bias/dd*100) and error
  pmtdd->fom = ((pmtdd->al+pmtdd->ar)/2)/(pmtdd->al-pmtdd->ar)*100;
  pmtdd->dfom = sqrt(pow(pmtdd->fom,2)*(pow(pmtdd->ddd/pmtdd->dd,2)+pow(pmtdd->dabias/pmtdd->abias,2)));
  pmtdd->print();

  return pmtdd;
}

void drawFunctions(){
  TFile *fout=new TFile("o_avgModelFction.root","RECREATE");
  int colors[8]={1,2,3,4,28,6,7,8};
  TGraph *gr[308];
  for(int i=0;i<nModelsEff;i++){
    gr[i]=new TGraph();
    for(int j=0;j<178;j++){      
      double val = -89 + j;
      gr[i]->SetPoint(j,val,model(val,i));
    }
    gr[i]->SetName(Form("model_%d",i));
    gr[i]->SetMarkerStyle(20);
    if(i<7){
      gr[i]->SetLineColor(colors[i]);
      gr[i]->SetMarkerColor(colors[i]);
    }else{
      gr[i]->SetLineColor(1);
      gr[i]->SetMarkerColor(1);
    }
    
    fout->cd();
    gr[i]->Write();
  }

  fout->Close();
}
