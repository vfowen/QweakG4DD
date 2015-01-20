/*********************************************************** 
Programmer: Valerie Gray
Purpose: To Output the KE vertex values for simulated data for all the octants
and each octant individually

This code shows two differnt ways to calaulate the error on the mean
of a wieghted histogram

Entry Conditions: x and y position , x and y angle direction
Date: 04-11-2012
Modified:02-21-2013
Assisted By: Wouter Deconinck
*********************************************************/

#include "TSystem.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH1D.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

void SimPreScatter_KE (string posx, int posy, double anglex, int angley)
{
  // groups root files for a run together
  TChain* QweakSimG4_Tree = new TChain ("QweakSimG4_Tree");

  //add the root files to the chain the event_tree branches

  //LightWeighting
//AL
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_Al_US/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_Al_DS/*.root");

//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeight_Al_US_Run1/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeight_Al_DS_Run1/*.root");

//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeight_Al_US_Run2/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeight_Al_DS_Run2/*.root");


//Run 1 & 2
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeight_Run1_noDC/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeight_Run2_noDC/*.root");

//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_noDC/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_noHDC/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_noVDC/*.root");

//Magnetic Field Rotations
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot45deg/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot45deg_noDC/myLightWeightScan_MagRot45deg_noDC_*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot90deg/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot90deg_noDC/myLightWeightScan_MagRot90deg_noDC_*.root");

  //Qtor Scans
  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/myQtorScan/myQtorScan_%d_*.root", posy));

  //Position scan files
//  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/myPosDirScan/myPosDirScan_Position%s_%dum_Direction%s_%durad_*.root",posx.c_str(), posy, posx.c_str(), anglex));
//  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/myPosDirScan/myPosDirScan_Pos%s_%dum_Dir%s_%durad_*.root",posx.c_str(), posy, posx.c_str(), anglex));
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myPosDirScan/myPosDirScan_PositionX_0um_DirectionX_0urad_*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myPosDirScan/myPosDirScan_PositionY_0um_DirectionY_0urad_*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myPosDirScan/myPosDirScan_PosX_0um_DirX_0urad_*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myPosDirScan/myPosDirScan_PosY_0um_DirY_0urad_*.root");

  //MD9
//  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/MD9_Oct1_%s_%.2Fcm/*.root", posx.c_str(), anglex));

  //number of chunks
  Int_t n = 1000;

  //define vector of histograms
  std::vector < vector<TH1D*> >  KE; //[chunk #][octant]
  KE.resize(n+1);

  std::vector<TH1D*> KE_tot;//[oct]
  KE_tot.resize(10);

  for (size_t i = 0; i<KE.size();i++)
  {
     KE[i].resize(10);
     for (size_t j = 0; j<KE[i].size();j++)
     {
       //set the histogram for the KE 
       KE[i][j]= new TH1D (Form("KE[%d][%d]",i,j),Form("Sim PreScatter KE for Octant number %d, set %d",i,j),4000,0.0,2000.0);
       KE[i][j]->GetXaxis()->SetTitle("KE value (MeV)");
       KE[i][j]->GetYaxis()->SetTitle("Frequency");
     }
	}
  for (size_t j = 0; j<KE_tot.size();j++)
  {
     KE_tot[j] = new TH1D (Form("KE_tot[%d]",j),Form("Sim PreScatter KE for Octant number %d",j),4000,0.0,2000.0);
     KE_tot[j]->GetXaxis()->SetTitle("KE value (MeV)");
     KE_tot[j]->GetYaxis()->SetTitle("Frequency");
 	}

 //define a histogram to store all the means of the n histogram chunk 
  std::vector<TH1D*> h_KE_mean;//[oct]
  h_KE_mean.resize(10);

  for (size_t j = 0; j<h_KE_mean.size();j++)
  {
     h_KE_mean[j] = new TH1D (Form("h_KE_mean[%d]",j),Form("Mean PreScatter KE value distribution from the %d chunks for Octant number %d", n,j),4000,0.0,2000.0);
     h_KE_mean[j]->GetXaxis()->SetTitle("Mean KE value (MeV)");
     h_KE_mean[j]->GetYaxis()->SetTitle("Frequency");
 	}

  //define an array  for the mean and sigma of all the histograms
  //this will allow to get the proper mean - initalze all values to zero.
  //mean it the mean
  //sigma is the mean squared at this point (sorry for the bad naming)

  Double_t mean_KE[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Double_t sigma_KE[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  //divide the number of entries up
  Int_t nentries = QweakSimG4_Tree->GetEntries();
  Int_t step = nentries / n;

  for (Int_t i = 0; i < n; i++)
  {
    Int_t n1 = nentries / n * i;

    QweakSimG4_Tree->Draw(Form("Primary.PreScatteringKineticEnergy>>KE[%d][0]",i) ,"Primary.CrossSection \\
      * (Cerenkov.PMT.PMTTotalNbOfPEs[1] + Cerenkov.PMT.PMTTotalNbOfPEs[2] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[3] + Cerenkov.PMT.PMTTotalNbOfPEs[4] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[5] + Cerenkov.PMT.PMTTotalNbOfPEs[6] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[7] + Cerenkov.PMT.PMTTotalNbOfPEs[8] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[9])"," ", step ,n1 );
    mean_KE[0] += KE[i][0]->GetMean();
    sigma_KE[0] += KE[i][0]->GetMean() * KE[i][0]->GetMean();
    KE_tot[0]->Add(KE[i][0]);
    h_KE_mean[0]->Fill( KE[i][0]->GetMean() );

    //draw the KE graph for each octants
    for (size_t oct = 1; oct < KE[i].size(); oct ++)
    {
      QweakSimG4_Tree->Draw(Form("Primary.PreScatteringKineticEnergy>>KE[%d][%d]",i,oct),
        Form("Primary.CrossSection*Cerenkov.PMT.PMTTotalNbOfPEs[%d] * (Cerenkov.Detector.DetectorID==%d)/Cerenkov.Detector.NbOfHits",oct, oct), " ", step, n1 );
      mean_KE[oct] += KE[i][oct]->GetMean();
      sigma_KE[oct] += KE[i][oct]->GetMean() * KE[i][oct]->GetMean();
      KE_tot[oct]->Add(KE[i][oct]);
      h_KE_mean[oct]->Fill( KE[i][oct]->GetMean() );
    }

  }

  //define canvas
  TCanvas* c1 = new TCanvas ("c1","Sim KE Vetex");
  c1->Divide(3,3);
  c1->cd(9);
  KE_tot[0]->Draw();

  for (size_t oct = 1; oct < KE_tot.size(); oct ++)
    {
      c1->cd(oct);
      KE_tot[oct]->Draw();
    }

  TCanvas* c2 = new TCanvas ("c2","Mean Sim KE Vertex");
  c2->Divide(3,3);
  c2->cd(9);
  h_KE_mean[0]->Draw();

  for (size_t oct = 1; oct < h_KE_mean.size(); oct ++)
    {
      c2->cd(oct);
      h_KE_mean[oct]->Draw();
    }


  //calaulate out the right error and mean
  for (size_t oct = 0; oct < KE_tot.size(); oct++)
  {
    mean_KE[oct] /= n;
    //the extra  factor of sqrt(n) is to get the error on the mean not just the error of the distibution
    sigma_KE[oct] = sqrt(sigma_KE[oct] / n - mean_KE[oct] * mean_KE[oct]) / sqrt(n);
  }

  cout << "Oct \t " << "KE(calc) \t " << "error (calc) \t " <<  "KE (hist) \t " << "error (hist) \t all in MeV " << endl;
  cout << "All \t " << setprecision(7) << mean_KE[0] << " \t " <<  setprecision(4) << sigma_KE[0] << " \t "
     << setprecision(7) << h_KE_mean[0]->GetMean() << " \t " <<  setprecision(4) << h_KE_mean[0]->GetRMS()/sqrt(h_KE_mean[0]->GetEntries()) << endl;

  for (int oct = 1; oct < 10; oct ++)
  {
  cout << oct << " \t " << setprecision(7) << mean_KE[oct] << " \t " <<  setprecision(4) << sigma_KE[oct] << " \t "
     << setprecision(7) << h_KE_mean[oct]->GetMean() << " \t " <<  setprecision(4) << h_KE_mean[oct]->GetRMS()/sqrt(h_KE_mean[oct]->GetEntries()) << endl;
  }
  return;

}
