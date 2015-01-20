/***********************************************************
Programmer: Valerie Gray
Purpose: To Output the Q2 values for simulated data for all the octants
and each octant individually

This code shows two differnt ways to calaulate the error on the mean
of a wieghted histogram

Also this output the number of entries in the histogram so that the
relative weights can be caluculated.  Please note that the number of entries
in a weighted histogram is not the correct number of entries, however
it works just fine for weighted histograms, since the relaitive rates is
what they are used for.

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

void SimQ2 (string posx, int posy, double anglex, int angley)
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

//    QweakSimG4_Tree->Add("/cache/mss/home/kbartlet/rootfiles/myUpstream_TargetWindow_Run1/*.root");

//Run 1 & 2
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeight_Run1_noDC/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeight_Run2_noDC/*.root");

//  QweakSimG4_Tree->Add("/cache/mss/home/wdconinc/rootfiles/myLightWeightScan_noDC/*.root");
  QweakSimG4_Tree->Add("/cache/mss/home/wdconinc/rootfiles/myLightWeightScan_MagRot45deg_noDC/myLightWeightScan_MagRot45deg_noDC_4???.root");
  QweakSimG4_Tree->Add("/cache/mss/home/wdconinc/rootfiles/myLightWeightScan_MagRot45deg_noDC/myLightWeightScan_MagRot45deg_noDC_5???.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/wdconinc/rootfiles/myLightWeightScan_MagRot90deg_noDC/myLightWeightScan_MagRot90deg_noDC_4???.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/wdconinc/rootfiles/myLightWeightScan_MagRot90deg_noDC/myLightWeightScan_MagRot90deg_noDC_5???.root");

//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_IdealPos/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_noDC/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_noHDC/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_noVDC/*.root");

//Magnetic Field Rotations
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot45deg/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot45deg_noDC/myLightWeightScan_MagRot45deg_noDC_*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot90deg/*.root");
//  QweakSimG4_Tree->Add("/cache/mss/home/vmgray/rootfiles/myLightWeightScan_MagRot90deg_noDC/myLightWeightScan_MagRot90deg_noDC_*.root");

  //Qtor Scans
//  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/myQtorScan/myQtorScan_%d_*.root", posy));

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
  std::vector < vector<TH1D*> >  q2; //[chunk #][octant]
  q2.resize(n+1);

  std::vector<TH1D*> q2_tot;//[oct]
  q2_tot.resize(10);

  for (size_t i = 0; i<q2.size();i++)
  {
     q2[i].resize(10);
     for (size_t j = 0; j<q2[i].size();j++)
     {
       //set the histogram for the q2 
       q2[i][j]= new TH1D (Form("q2[%d][%d]",i,j),Form("Sim Q2 for Octant number %d, set %d",i,j),100,0.0,0.12);
       q2[i][j]->GetXaxis()->SetTitle("Q2 value m(GeV)^2");
       q2[i][j]->GetYaxis()->SetTitle("Frequency");
     }
	}
  for (size_t j = 0; j<q2_tot.size();j++)
  {
     q2_tot[j] = new TH1D (Form("q2_tot[%d]",j),Form("Sim Q2 for Octant number %d",j),100,0.0,0.12);
     q2_tot[j]->GetXaxis()->SetTitle("Q2 value m(GeV)^2");
     q2_tot[j]->GetYaxis()->SetTitle("Frequency");
 	}

 //define a histogram to store all the means of the n histogram chunk 
  std::vector<TH1D*> h_q2_mean;//[oct]
  h_q2_mean.resize(10);

  for (size_t j = 0; j<h_q2_mean.size();j++)
  {
     h_q2_mean[j] = new TH1D (Form("h_q2_mean[%d]",j),Form("Mean Sim Q2 distribution from the %d chunks for Octant number %d", n,j),1200,0.0,120.0);
     h_q2_mean[j]->GetXaxis()->SetTitle("Mean Q2 value m(GeV)^2");
     h_q2_mean[j]->GetYaxis()->SetTitle("Frequency");
 	}

  //define an array  for the mean and sigma of all the histograms
  //this will allow to get the proper mean - initalze all values to zero.
  //mean it the mean
  //sigma is the mean squared at this point (sorry for the bad naming)

  Double_t mean_q2[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  Double_t sigma_q2[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  int Entries[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  //divide the number of entries up
  Int_t nentries = QweakSimG4_Tree->GetEntries();
  Int_t step = nentries / n;

  for (Int_t i = 0; i < n; i++)
  {
    Int_t n1 = nentries / n * i;

    QweakSimG4_Tree->Draw(Form("Primary.PrimaryQ2>>q2[%d][0]",i) ,"(Primary.CrossSection) \\
      * (Cerenkov.PMT.PMTTotalNbOfPEs[1] + Cerenkov.PMT.PMTTotalNbOfPEs[2] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[3] + Cerenkov.PMT.PMTTotalNbOfPEs[4] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[5] + Cerenkov.PMT.PMTTotalNbOfPEs[6] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[7] + Cerenkov.PMT.PMTTotalNbOfPEs[8] \\
      + Cerenkov.PMT.PMTTotalNbOfPEs[9])"," ", step ,n1 );
    mean_q2[0] += q2[i][0]->GetMean();
    sigma_q2[0] += q2[i][0]->GetMean() * q2[i][0]->GetMean();
    q2_tot[0]->Add(q2[i][0]);
    h_q2_mean[0]->Fill( 1000*q2[i][0]->GetMean() );
    Entries[0] += q2[i][0]->GetEntries();

    //draw the q2 graph for each octants
    for (size_t oct = 1; oct < q2[i].size(); oct ++)
    {
      QweakSimG4_Tree->Draw(Form("Primary.PrimaryQ2>>q2[%d][%d]",i,oct),
        Form("Primary.CrossSection*Cerenkov.PMT.PMTTotalNbOfPEs[%d] \\ 
          * (Cerenkov.Detector.DetectorID==%d)/Cerenkov.Detector.NbOfHits",oct, oct), " ", step, n1 );
      mean_q2[oct] += q2[i][oct]->GetMean();
      sigma_q2[oct] += q2[i][oct]->GetMean() * q2[i][oct]->GetMean();
      q2_tot[oct]->Add(q2[i][oct]);
      h_q2_mean[oct]->Fill( 1000*q2[i][oct]->GetMean() );
      Entries[oct] += q2[i][oct]->GetEntries();
   }
  }

//draw histograms for the chunkin' paper
//  TCanvas* c3 = new TCanvas ("c1","Sim Q2 - weighted");
//  q2_tot[0]->Draw();
//  c3->SaveAs("Weighted_SimQ2_for_chunkin_paper.png");

//  TCanvas* c4 = new TCanvas ("c1","Sim Q2 - weighted");
//  h_q2_mean[0]->Draw();
//  c4->SaveAs("Mean_of_chunks_SimQ2_for_chunkin_paper.png");

  //define canvas
  TCanvas* c1 = new TCanvas ("c1","Sim Q2");
  c1->Divide(3,3);
  c1->cd(9);
  q2_tot[0]->Draw();

  for (size_t oct = 1; oct < q2_tot.size(); oct ++)
    {
      c1->cd(oct);
      q2_tot[oct]->Draw();
    }

  TCanvas* c2 = new TCanvas ("c2","Mean Sim Q2");
  c2->Divide(3,3);
  c2->cd(9);
  h_q2_mean[0]->Draw();

  for (size_t oct = 1; oct < h_q2_mean.size(); oct ++)
    {
      c2->cd(oct);
      h_q2_mean[oct]->Draw();
    }


  //calaulate out the right error and mean
  for (size_t oct = 0; oct < q2_tot.size(); oct++)
  {
    mean_q2[oct] /= n;
    //the extra  factor of sqrt(n) is to get the error on the mean not just the error of the distibution
    sigma_q2[oct] = sqrt(sigma_q2[oct] / n - mean_q2[oct] * mean_q2[oct]) / sqrt(n);
  }

  cout << "Oct \t " << "Q2(calc) \t " << "error (calc) \t " <<  "Q2 (hist) \t " << "error (hist) \t # Entries \t all in m(Gev)^2 " << endl;
  cout << "All \t " << setprecision(5) << 1000*mean_q2[0] << " \t " <<  setprecision(4) << 1000*sigma_q2[0] << " \t "
     << setprecision(5) << h_q2_mean[0]->GetMean() << " \t " <<  setprecision(4) << h_q2_mean[0]->GetRMS()/sqrt(h_q2_mean[0]->GetEntries()) << " \t " << Entries[0] <<  endl;

  for (int oct = 1; oct < 10; oct ++)
  {
  cout << oct << " \t " << setprecision(5) << 1000*mean_q2[oct] << " \t " <<  setprecision(4) << 1000*sigma_q2[oct] << " \t "
     << setprecision(5) << h_q2_mean[oct]->GetMean() << " \t " <<  setprecision(4) << h_q2_mean[oct]->GetRMS()/sqrt(h_q2_mean[oct]->GetEntries()) << " \t " << Entries[oct] << endl;
  }
  return;

}
