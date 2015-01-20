/***********************************************************
Programmer: Valerie Gray
Purpose: To Output the Theta vertex values for simulated data for all the octants
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

void SimVertexTheta (string posx, int posy, double anglex, int angley)
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
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_IdealPos/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_noDC/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_noHDC/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_noVDC/*.root");

//Magnetic Field Rotations
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot45deg/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot45deg_noDC/myLightWeightScan_MagRot45deg_noDC_*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot90deg/*.root");
//  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot90deg_noDC/myLightWeightScan_MagRot90deg_noDC_%d.root",i));

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
  std::vector < vector<TH1D*> >  Theta; //[chunk #][octant]
  Theta.resize(n+1);

  std::vector<TH1D*> Theta_tot;//[oct]
  Theta_tot.resize(10);

  for (size_t i = 0; i<Theta.size();i++)
  {
     Theta[i].resize(10);
     for (size_t j = 0; j<Theta[i].size();j++)
     {
       //set the histogram for the Theta 
       Theta[i][j]= new TH1D (Form("Theta[%d][%d]",i,j),Form("Sim Theta vertex for Octant number %d, set %d",i,j),100,0.0,18.0);
       Theta[i][j]->GetXaxis()->SetTitle("Theta value (degree)");
       Theta[i][j]->GetYaxis()->SetTitle("Frequency");
     }
	}
  for (size_t j = 0; j<Theta_tot.size();j++)
  {
     Theta_tot[j] = new TH1D (Form("Theta_tot[%d]",j),Form("Sim Theta vertex for Octant number %d",j),100,0.0,18.0);
     Theta_tot[j]->GetXaxis()->SetTitle("Theta value (degree)");
     Theta_tot[j]->GetYaxis()->SetTitle("Frequency");
 	}

 //define a histogram to store all the means of the n histogram chunk 
  std::vector<TH1D*> h_Theta_mean;//[oct]
  h_Theta_mean.resize(10);

  for (size_t j = 0; j<h_Theta_mean.size();j++)
  {
     h_Theta_mean[j] = new TH1D (Form("h_Theta_mean[%d]",j),Form("Mean Sim Theta value distribution from the %d chunks for Octant number %d", n,j),300,0.0,18.0);
     h_Theta_mean[j]->GetXaxis()->SetTitle("Mean Theta value (degree)");
     h_Theta_mean[j]->GetYaxis()->SetTitle("Frequency");
 	}

  //define an array  for the mean and sigma of all the histograms
  //this will allow to get the proper mean - initalze all values to zero.
  //mean it the mean
  //sigma is the mean squared at this point (sorry for the bad naming)

  Double_t mean_Theta[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Double_t sigma_Theta[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  //divide the number of entries up
  Int_t nentries = QweakSimG4_Tree->GetEntries();
  Int_t step = nentries / n;

  for (Int_t i = 0; i < n; i++)
  {
    Int_t n1 = nentries / n * i;

    QweakSimG4_Tree->Draw(Form("Primary.OriginVertexThetaAngle>>Theta[%d][0]",i) ,"Primary.CrossSection \\
      * (Cerenkov.PMT.PMTTotalNbOfPEs[1] + Cerenkov.PMT.PMTTotalNbOfPEs[2] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[3] + Cerenkov.PMT.PMTTotalNbOfPEs[4] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[5] + Cerenkov.PMT.PMTTotalNbOfPEs[6] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[7] + Cerenkov.PMT.PMTTotalNbOfPEs[8] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[9])","",step,n1);
    mean_Theta[0] += Theta[i][0]->GetMean();
    sigma_Theta[0] += Theta[i][0]->GetMean() * Theta[i][0]->GetMean();
    Theta_tot[0]->Add(Theta[i][0]);
    h_Theta_mean[0]->Fill( Theta[i][0]->GetMean() );

    //draw the Theta graph for each octants
    for (size_t oct = 1; oct < Theta[i].size(); oct ++)
    {
      QweakSimG4_Tree->Draw(Form("Primary.OriginVertexThetaAngle>>Theta[%d][%d]",i,oct),
        Form("Primary.CrossSection*Cerenkov.PMT.PMTTotalNbOfPEs[%d] * (Cerenkov.Detector.DetectorID==%d)/Cerenkov.Detector.NbOfHits",oct, oct), " ", step, n1 );
      mean_Theta[oct] += Theta[i][oct]->GetMean();
      sigma_Theta[oct] += Theta[i][oct]->GetMean() * Theta[i][oct]->GetMean();
      Theta_tot[oct]->Add(Theta[i][oct]);
      h_Theta_mean[oct]->Fill( Theta[i][oct]->GetMean() );
    }

  }

  //define canvas
  TCanvas* c1 = new TCanvas ("c1","Sim Theta Vetex");
  c1->Divide(3,3);
  c1->cd(9);
  Theta_tot[0]->Draw();

  for (size_t oct = 1; oct < Theta_tot.size(); oct ++)
    {
      c1->cd(oct);
      Theta_tot[oct]->Draw();
    }

  TCanvas* c2 = new TCanvas ("c2","Mean Sim Theta Vertex");
  c2->Divide(3,3);
  c2->cd(9);
  h_Theta_mean[0]->Draw();

  for (size_t oct = 1; oct < h_Theta_mean.size(); oct ++)
    {
      c2->cd(oct);
      h_Theta_mean[oct]->Draw();
    }


  //calaulate out the right error and mean
  for (size_t oct = 0; oct < Theta_tot.size(); oct++)
  {
    mean_Theta[oct] /= n;
    //the extra  factor of sqrt(n) is to get the error on the mean not just the error of the distibution
    sigma_Theta[oct] = sqrt(sigma_Theta[oct] / n - mean_Theta[oct] * mean_Theta[oct]) / sqrt(n);
  }

  cout << "Oct \t " << "Theta(calc) \t " << "error (calc) \t " <<  "Theta (hist) \t " << "error (hist) \t all in degrees " << endl;
  cout << "All \t " << setprecision(5) << mean_Theta[0] << " \t " <<  setprecision(4) << sigma_Theta[0] << " \t "
     << setprecision(5) << h_Theta_mean[0]->GetMean() << " \t " <<  setprecision(4) << h_Theta_mean[0]->GetRMS()/sqrt(h_Theta_mean[0]->GetEntries()) << endl;

  for (int oct = 1; oct < 10; oct ++)
  {
  cout << oct << " \t " << setprecision(5) << mean_Theta[oct] << " \t " <<  setprecision(4) << sigma_Theta[oct] << " \t "
     << setprecision(5) << h_Theta_mean[oct]->GetMean() << " \t " <<  setprecision(4) << h_Theta_mean[oct]->GetRMS()/sqrt(h_Theta_mean[oct]->GetEntries()) << endl;
  }
  return;

}
