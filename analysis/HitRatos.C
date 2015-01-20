/***********************************************************
Programmer: Valerie Gray
Purpose:

To get out the ratio of the number of events fired in
   a certian octant with the number of event in a different octant

Also gets the ratio of the asymmetry fired in
   a certian octant with the asymmetry in a different octant

Also gets the ratio of the total number of PEs fired in
   a certian octant with the total number of PEs in a different octant

Calculates the ratio of the aysmmetry and number of PEs weighted
   by the Cross section

-------USEFUL DEFINITIONS-----

Active octant - the octant that the electrons are being fired into
   AKA - for active octant 1, I cut on position of all the scattered
         electrons so that they are only going into that active octant
         (1) in this example

in the final table I use

pos only - means I am cutting on the position of the incomming electrons
     or cutting to get the active octant

CS - means weighting by cross section

PE - means weighting by PE number

------------------------------

This outputs the numbers in a table and in HTML so it can be
   put into an elog with ease.

Entry Conditions:
  Axis - the axis of MD9 is moved along
  pos - the position of MD9
Date: 02-18-2013
Modified: 07-12-2013
Assisted By: Wouter Deconinck
*********************************************************/

#include "TSystem.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH1D.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "QweakSimUserMainEvent.hh"

//set up the significant figures right - &plusmn is for html change to +/- if not useing that
#define value_with_error(a,da) std::setiosflags(std::ios::fixed) \
  << std::setprecision((size_t) (std::log10((a)/(da)) - std::log10(a) + 1.5)) \
  << " "  << (a) << " &plusmn  " << (da) << std::resetiosflags(std::ios::fixed)

using namespace std;

//angle distribution around 0 deg in Phi of MD1
double MD1_phi_angle_range = 22.5;
double MD_bars_phi_angle[9] = {0, 0, 45, 90, 135, 180, -135, -90, -45};

void HitRatios (string axis, double pos)
{

  // groups root files for a run together
  TChain* QweakSimG4_Tree = new TChain ("QweakSimG4_Tree");

  //add the root files to the chain the event_tree branches
//  QweakSimG4_Tree->Add(Form("~/QwGeant4_clean/MD9_Run1_X_-72.86cm_LargeHut_1.root" /*, axis.c_str(), pos*/));
  QweakSimG4_Tree->Add(Form("~/QwGeant4_clean/MD9_Run2_X_-72.86cm_LargeHut_1.root" /*, axis.c_str(), pos*/));
//  QweakSimG4_Tree->Add(Form("~/QwGeant4_clean/MD9_Run2_X_-72.86cm_LargeHut_AlDS_1.root" /*, axis.c_str(), pos*/));
//  QweakSimG4_Tree->Add(Form("~/QwGeant4_clean/MD9_Run2_X_-72.86cm_LargeHut_AlUS_1.root" /*, axis.c_str(), pos*/));
//  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/MD9_Oct1_%s_%.2Fcm/*.root", axis.c_str(), pos));
//  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/MD9_Oct7_%s_%.2Fcm/*.root", axis.c_str(), pos));
//  QweakSimG4_Tree->Add(Form("/cache/mss/home/vmgray/rootfiles/MD9_Oct8_%s_%.2Fcm/*.root", axis.c_str(), pos));

//------------
  //define the needed histograms
  std::vector < vector <TH1D*> > h_asymmetry_hits; //[active oct][hits in MD for that actove octant]
  h_asymmetry_hits.resize(9);

  for (size_t i = 0; i < h_asymmetry_hits.size() ; i ++)
  {
    h_asymmetry_hits[i].resize(10);
    for (size_t j = 0; j < h_asymmetry_hits[i].size() ;j++)
    {
      h_asymmetry_hits[i][j]= new TH1D (Form("h_asymmetry_hits[%zu][%zu]",i,j),
        Form("Asymmetry in MD %zu for active octant %zu", j, i), 1000, -1, 1);
      h_asymmetry_hits[i][j]->GetYaxis()->SetTitle("Frequency");
      h_asymmetry_hits[i][j]->GetXaxis()->SetTitle("Asymmetry (ppm)");
    }
  }

  std::vector < vector <TH1D*> > h_PE_left; //[active oct][hits in MD for that actove octant]
  std::vector < vector <TH1D*> > h_PE_right; //[active oct][hits in MD for that actove octant]
  std::vector < vector <TH1D*> > h_PE_total; //[active oct][hits in MD for that actove octant]
  h_PE_left.resize(9);
  h_PE_right.resize(9);
  h_PE_total.resize(9);

  for (size_t i = 0; i < h_PE_total.size(); i ++)
  {
    h_PE_left[i].resize(10);
    h_PE_right[i].resize(10);
    h_PE_total[i].resize(10);
    for (size_t j = 0; j < h_PE_total[i].size(); j++)
    {
      h_PE_left[i][j]= new TH1D (Form("h_PE_left[%zu][%zu]",i,j),
        Form("Number of left PEs in octant %zu for active octant %zu", j, i), 1000, 0, 500);
      h_PE_left[i][j]->GetYaxis()->SetTitle("Frequency");
      h_PE_left[i][j]->GetXaxis()->SetTitle("Number of PEs");

      h_PE_right[i][j]= new TH1D (Form("h_PE_right[%zu][%zu]",i,j),
        Form("Number of right PEs in octant %zu for active octant %zu", j, i), 1000, 0, 500);
      h_PE_right[i][j]->GetYaxis()->SetTitle("Frequency");
      h_PE_right[i][j]->GetXaxis()->SetTitle("Number of PEs");

      h_PE_total[i][j]= new TH1D (Form("h_PE_total[%zu][%zu]",i,j),
         Form("Number of PEs in octant %zu for active octant %zu", j, i), 1000, 0, 500);
      h_PE_total[i][j]->GetYaxis()->SetTitle("Frequency");
      h_PE_total[i][j]->GetXaxis()->SetTitle("Number of PEs");
    }
  }

//-----------
  //define the histograms for the weighting histograms (need to cut into chuncks)
  //number of chunks
  Int_t nchunks = 10;

  //define vector of histograms
  std::vector < vector < vector <TH1D*> > >  h_asymmetry_hits_cs; //[chunk #][active octant][MD]
  h_asymmetry_hits_cs.resize(nchunks+1);

  //asymmetry, PE and CS
  std::vector < vector < vector <TH1D*> > >  h_asymmetry_PE_left_cs; //[chunk #][active octant][MD]
  h_asymmetry_PE_left_cs.resize(nchunks+1);

  std::vector < vector < vector <TH1D*> > >  h_asymmetry_PE_right_cs; //[chunk #][active octant][MD]
  h_asymmetry_PE_right_cs.resize(nchunks+1);

  std::vector < vector < vector <TH1D*> > >  h_asymmetry_PE_total_cs; //[chunk #][active octant][MD]
  h_asymmetry_PE_total_cs.resize(nchunks+1);

  //asymmetry, PE
  std::vector < vector < vector <TH1D*> > >  h_asymmetry_PE_left; //[chunk #][active octant][MD]
  h_asymmetry_PE_left.resize(nchunks+1);

  std::vector < vector < vector <TH1D*> > >  h_asymmetry_PE_right; //[chunk #][active octant][MD]
  h_asymmetry_PE_right.resize(nchunks+1);

  std::vector < vector < vector <TH1D*> > >  h_asymmetry_PE_total; //[chunk #][active octant][MD]
  h_asymmetry_PE_total.resize(nchunks+1);

  //PE, cs
  std::vector < vector < vector <TH1D*> > >  h_PE_left_cs; //[chunk #][active octant][MD]
  h_PE_left_cs.resize(nchunks+1);

  std::vector < vector < vector <TH1D*> > >  h_PE_right_cs; //[chunk #][active octant][MD]
  h_PE_right_cs.resize(nchunks+1);

  std::vector < vector < vector <TH1D*> > >  h_PE_total_cs; //[chunk #][active octant][MD]
  h_PE_total_cs.resize(nchunks+1);

  // Asymmerty histogram weighed by coross Section
  for (size_t i = 0; i<h_asymmetry_hits_cs.size();i++)
  {
     h_asymmetry_hits_cs[i].resize(9);
     for (size_t j = 0; j<h_asymmetry_hits_cs[i].size();j++)
     {
       h_asymmetry_hits_cs[i][j].resize(10);
       for (size_t k = 0;k< h_asymmetry_hits_cs[i][j].size();k++)
       {
         //set the histogram for the h_asymmetry_cs
         h_asymmetry_hits_cs[i][j][k]= new TH1D (Form("h_asymmetry_hits_cs[%zu][%zu][%zu]",i,j,k),
           Form("Cross Section Werighting Asymmetry in MD %zu for active octant %zu- chunk %zu",k,j,i),1000,-1,1);
         h_asymmetry_hits_cs[i][j][k]->GetXaxis()->SetTitle("Asymmetry (ppm)");
         h_asymmetry_hits_cs[i][j][k]->GetYaxis()->SetTitle("Frequency");
       }
     }
  }

  // Asymmerty histpgram weighed by cross Section and PEs
  for (size_t i = 0; i<h_asymmetry_PE_total_cs.size();i++)
  {
     h_asymmetry_PE_left_cs[i].resize(9);
     h_asymmetry_PE_right_cs[i].resize(9);
     h_asymmetry_PE_total_cs[i].resize(9);
     for (size_t j = 0; j<h_asymmetry_PE_total_cs[i].size();j++)
     {
       h_asymmetry_PE_left_cs[i][j].resize(10);
       h_asymmetry_PE_right_cs[i][j].resize(10);
       h_asymmetry_PE_total_cs[i][j].resize(10);
       for (size_t k = 0;k < h_asymmetry_PE_total_cs[i][j].size();k++)
       {
         //set the histogram for the h_asymmetry_PE_total_cs
         h_asymmetry_PE_left_cs[i][j][k]= new TH1D (Form("h_asymmetry_PE_left_cs[%zu][%zu][%zu]",i,j,k),
            Form("Cross Section and PE left Werighted Asymmetry in MD %zu for active octant %zu- chunk %zu",k,j,i),1000,-1,1);
         h_asymmetry_PE_left_cs[i][j][k]->GetXaxis()->SetTitle("Asymmetry (ppm)");
         h_asymmetry_PE_left_cs[i][j][k]->GetYaxis()->SetTitle("Frequency");

         h_asymmetry_PE_right_cs[i][j][k]= new TH1D (Form("h_asymmetry_PE_right_cs[%zu][%zu][%zu]",i,j,k),
            Form("Cross Section and right PE Werighted Asymmetry in MD %zu for active octant %zu- chunk %zu",k,j,i),1000,-1,1);
         h_asymmetry_PE_right_cs[i][j][k]->GetXaxis()->SetTitle("Asymmetry (ppm)");
         h_asymmetry_PE_right_cs[i][j][k]->GetYaxis()->SetTitle("Frequency");

         h_asymmetry_PE_total_cs[i][j][k]= new TH1D (Form("h_asymmetry_PE_total_cs[%zu][%zu][%zu]",i,j,k),
            Form("Cross Section and total PE Werighted Asymmetry in MD %zu for active octant %zu- chunk %zu",k,j,i),1000,-1,1);
         h_asymmetry_PE_total_cs[i][j][k]->GetXaxis()->SetTitle("Asymmetry (ppm)");
         h_asymmetry_PE_total_cs[i][j][k]->GetYaxis()->SetTitle("Frequency");
       }
     }
  }

  // Asymmerty histpgram weighed by  PEs
  for (size_t i = 0; i<h_asymmetry_PE_total.size();i++)
  {
     h_asymmetry_PE_total[i].resize(9);
     h_asymmetry_PE_left[i].resize(9);
     h_asymmetry_PE_right[i].resize(9);
     for (size_t j = 0; j<h_asymmetry_PE_total[i].size();j++)
     {
       h_asymmetry_PE_total[i][j].resize(10);
       h_asymmetry_PE_left[i][j].resize(10);
       h_asymmetry_PE_right[i][j].resize(10);
       for (size_t k = 0;k < h_asymmetry_PE_total[i][j].size();k++)
       {
         //set the histogram for the h_asymmetry_PE_total
         h_asymmetry_PE_left[i][j][k]= new TH1D (Form("h_asymmetry_PE_left[%zu][%zu][%zu]",i,j,k),
            Form("PE left Werighted Asymmetry in MD %zu for active octant %zu - chunk %zu",k,j,i),1000,-1,1);
         h_asymmetry_PE_left[i][j][k]->GetXaxis()->SetTitle("Asymmetry (ppm)");
         h_asymmetry_PE_left[i][j][k]->GetYaxis()->SetTitle("Frequency");

         h_asymmetry_PE_right[i][j][k]= new TH1D (Form("h_asymmetry_PE_right[%zu][%zu][%zu]",i,j,k),
            Form("right PE Werighted Asymmetry in MD %zu for active octant %zu- chunk %zu",k,j,i),1000,-1,1);
         h_asymmetry_PE_right[i][j][k]->GetXaxis()->SetTitle("Asymmetry (ppm)");
         h_asymmetry_PE_right[i][j][k]->GetYaxis()->SetTitle("Frequency");

         h_asymmetry_PE_total[i][j][k]= new TH1D (Form("h_asymmetry_PE_total[%zu][%zu][%zu]",i,j,k),
            Form("total PE Werighted Asymmetry in MD %zu for active octant %zu- chunk %zu",k,j,i),1000,-1,1);
         h_asymmetry_PE_total[i][j][k]->GetXaxis()->SetTitle("Asymmetry (ppm)");
         h_asymmetry_PE_total[i][j][k]->GetYaxis()->SetTitle("Frequency");
       }
     }
  }

  //PEs
  for (size_t i = 0; i<h_PE_total_cs.size();i++)
  {
     h_PE_total_cs[i].resize(9);
     h_PE_left_cs[i].resize(9);
     h_PE_right_cs[i].resize(9);
     for (size_t j = 0; j<h_PE_total_cs[i].size();j++)
     {
       h_PE_total_cs[i][j].resize(10);
       h_PE_left_cs[i][j].resize(10);
       h_PE_right_cs[i][j].resize(10);
       for (size_t k = 0;k< h_PE_total_cs[i][j].size();k++)
       {
         //set the histogram for the h_PEs_Blah_cs
         h_PE_left_cs[i][j][k]= new TH1D (Form("h_PE_left_cs[%zu][%zu][%zu]",i,j,k),
            Form("Cross Section Werighting left PEs in MD %zu for active octant %zu- chunk %zu",k,j,i),1000, 0, 500);
         h_PE_left_cs[i][j][k]->GetXaxis()->SetTitle("Number of PEs ");
         h_PE_left_cs[i][j][k]->GetYaxis()->SetTitle("Frequency");

         h_PE_right_cs[i][j][k]= new TH1D (Form("h_PE_right_cs[%zu][%zu][%zu]",i,j,k),
            Form("Cross Section Werighting right PEs in MD %zu for active octant %zu- chunk %zu",k,j,i),1000, 0, 500);
         h_PE_right_cs[i][j][k]->GetXaxis()->SetTitle("Number of PEs ");
         h_PE_right_cs[i][j][k]->GetYaxis()->SetTitle("Frequency");

         h_PE_total_cs[i][j][k]= new TH1D (Form("h_PE_total_cs[%zu][%zu][%zu]",i,j,k),
            Form("Cross Section total Werighting PEs in MD %zu for active octant %zu- chunk %zu",k,j,i),1000, 0, 500);
         h_PE_total_cs[i][j][k]->GetXaxis()->SetTitle("Number of PEs ");
         h_PE_total_cs[i][j][k]->GetYaxis()->SetTitle("Frequency");
       }
     }
  }

//----------

  // make arrays to store mean values and stuff to get the error

  //define an array  for the mean and sigma of all the histograms
  //this will allow to get the proPEr mean - initalze all values to zero.
  //mean it the mean
  //sigma is the mean squared at this point (sorry for the bad naming)

  std::vector<std::vector<Double_t> >  mean_asymmetry_hits_cs, sigma_asymmetry_hits_cs,
      mean_PE_left_cs, sigma_PE_left_cs, mean_PE_right_cs, sigma_PE_right_cs, mean_PE_total_cs, sigma_PE_total_cs,
      mean_asymmetry_PE_left, sigma_asymmetry_PE_left, mean_asymmetry_PE_right, sigma_asymmetry_PE_right, mean_asymmetry_PE_total, sigma_asymmetry_PE_total,
      mean_asymmetry_PE_left_cs, sigma_asymmetry_PE_left_cs, mean_asymmetry_PE_right_cs, sigma_asymmetry_PE_right_cs, mean_asymmetry_PE_total_cs, sigma_asymmetry_PE_total_cs;

  mean_asymmetry_hits_cs.resize(9);
  sigma_asymmetry_hits_cs.resize(9);
  mean_PE_left_cs.resize(9);
  sigma_PE_left_cs.resize(9);
  mean_PE_right_cs.resize(9);
  sigma_PE_right_cs.resize(9);
  mean_PE_total_cs.resize(9);
  sigma_PE_total_cs.resize(9);
  mean_asymmetry_PE_left.resize(9);
  sigma_asymmetry_PE_left.resize(9);
  mean_asymmetry_PE_right.resize(9);
  sigma_asymmetry_PE_right.resize(9);
  mean_asymmetry_PE_total.resize(9);
  sigma_asymmetry_PE_total.resize(9);
  mean_asymmetry_PE_left_cs.resize(9);
  sigma_asymmetry_PE_left_cs.resize(9);
  mean_asymmetry_PE_right_cs.resize(9);
  sigma_asymmetry_PE_right_cs.resize(9);
  mean_asymmetry_PE_total_cs.resize(9);
  sigma_asymmetry_PE_total_cs.resize(9);

  for (size_t i = 0; i < mean_asymmetry_hits_cs.size(); i++) {

    mean_asymmetry_hits_cs[i].resize(10,0);
    sigma_asymmetry_hits_cs[i].resize(10,0);
    mean_PE_left_cs[i].resize(10,0);
    mean_PE_left_cs[i].resize(10,0);
    sigma_PE_left_cs[i].resize(10,0);
    mean_PE_right_cs[i].resize(10,0);
    sigma_PE_right_cs[i].resize(10,0);
    mean_PE_total_cs[i].resize(10,0);
    sigma_PE_total_cs[i].resize(10,0);
    mean_asymmetry_PE_left[i].resize(10,0);
    sigma_asymmetry_PE_left[i].resize(10,0);
    mean_asymmetry_PE_right[i].resize(10,0);
    sigma_asymmetry_PE_right[i].resize(10,0);
    mean_asymmetry_PE_total[i].resize(10,0);
    sigma_asymmetry_PE_total[i].resize(10,0);
    mean_asymmetry_PE_left_cs[i].resize(10,0);
    sigma_asymmetry_PE_left_cs[i].resize(10,0);
    mean_asymmetry_PE_right_cs[i].resize(10,0);
    sigma_asymmetry_PE_right_cs[i].resize(10,0);
    mean_asymmetry_PE_total_cs[i].resize(10,0);
    sigma_asymmetry_PE_total_cs[i].resize(10,0);

  }

//----------
  //To fill weighted histograms and get errors we need to
  //divide the number of entries up
  Int_t nentries = QweakSimG4_Tree->GetEntries();
  Int_t step = nentries / nchunks;

//----------
  //now that the chain is defined (first lines) and the file(s) are connected
  //right away so accoring to the Deconinck loop ove events script the next thing
  //to do is to set the addresses of the leafs
  QweakSimUserMainEvent* event = 0;
  QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);

//fill unweighted histograms - weighted and cut up I have no idea how...
  //loop over chunks
  for(int ichunk = 0; ichunk < nchunks; ichunk++)
  {
    //loop over entries
    for(int i = 0; i < step; i++)
    {
      QweakSimG4_Tree->GetEntry(i + ichunk*step);

       Int_t octant = 0;
       if(abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[1])<MD1_phi_angle_range)
       {
         octant = 1;

       }else if(std::abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[2])<MD1_phi_angle_range)
         {
           octant = 2;

         }else if(std::abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[3])<MD1_phi_angle_range)
           {
             octant = 3;

           }else if(std::abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[4])<MD1_phi_angle_range)
             {
               octant = 4;

             }else if(abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[5])<MD1_phi_angle_range)
               {
                  octant = 5;

                }else if(abs(event->Primary.GetOriginVertexPhiAngle()+MD_bars_phi_angle[5])<MD1_phi_angle_range)
                 {
                    octant = 5;

                 }else if(abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[6])<MD1_phi_angle_range)
                   {
                     octant = 6;

                   }else if(abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[7])<MD1_phi_angle_range)
                     {
                       octant = 7;

                     }else if (abs(event->Primary.GetOriginVertexPhiAngle()-MD_bars_phi_angle[8])<MD1_phi_angle_range)
                       {
                         octant = 8;

                       }

     // everything hits weighted
     for(size_t nhit=0; nhit< (size_t) event->Cerenkov.Detector.NbOfHits; nhit++)
     {
        //unweighted histograms
        h_asymmetry_hits[octant][event->Cerenkov.Detector.GetDetectorID()[nhit]]->Fill(event->Primary.GetAsymmetry());

        //weightined histograms cross section only
        h_asymmetry_hits_cs[ichunk][octant][event->Cerenkov.Detector.GetDetectorID()[nhit]]->Fill(event->Primary.GetAsymmetry(),event->Primary.GetCrossSection());

     }

     // everything PE weighted
     for (size_t oct1 = 1; oct1 < 10; oct1++)
     {
       // number of PEs for each octant
       h_PE_left[octant][oct1]->Fill(event->Cerenkov.PMT.GetPMTLeftNbOfHits()[oct1]);
       h_PE_right[octant][oct1]->Fill(event->Cerenkov.PMT.GetPMTRightNbOfHits()[oct1]);
       h_PE_total[octant][oct1]->Fill(event->Cerenkov.PMT.GetPMTTotalNbOfHits()[oct1]);

       // weighted with cross section
       h_PE_left_cs[ichunk][octant][oct1]->Fill(event->Cerenkov.PMT.GetPMTLeftNbOfHits()[oct1], event->Primary.GetCrossSection());
       h_PE_right_cs[ichunk][octant][oct1]->Fill(event->Cerenkov.PMT.GetPMTRightNbOfHits()[oct1], event->Primary.GetCrossSection());
       h_PE_total_cs[ichunk][octant][oct1]->Fill(event->Cerenkov.PMT.GetPMTTotalNbOfHits()[oct1], event->Primary.GetCrossSection());

       // weightined histograms cross section and PE
       h_asymmetry_PE_left[ichunk][octant][oct1]->Fill(event->Primary.GetAsymmetry(),
         (event->Cerenkov.PMT.GetPMTLeftNbOfHits()[oct1]));
       h_asymmetry_PE_right[ichunk][octant][oct1]->Fill(event->Primary.GetAsymmetry(),
         (event->Cerenkov.PMT.GetPMTRightNbOfHits()[oct1]));
       h_asymmetry_PE_total[ichunk][octant][oct1]->Fill(event->Primary.GetAsymmetry(),
         (event->Cerenkov.PMT.GetPMTTotalNbOfHits()[oct1]));

       h_asymmetry_PE_left_cs[ichunk][octant][oct1]->Fill(event->Primary.GetAsymmetry(),
        (event->Primary.GetCrossSection()) * (event->Cerenkov.PMT.GetPMTLeftNbOfHits()[oct1]));
       h_asymmetry_PE_right_cs[ichunk][octant][oct1]->Fill(event->Primary.GetAsymmetry(),
         (event->Primary.GetCrossSection()) * (event->Cerenkov.PMT.GetPMTRightNbOfHits()[oct1]));
       h_asymmetry_PE_total_cs[ichunk][octant][oct1]->Fill(event->Primary.GetAsymmetry(),
         (event->Primary.GetCrossSection()) * (event->Cerenkov.PMT.GetPMTTotalNbOfHits()[oct1]));
    }
  }

   //fill the arrays to get the mean and proPEr error of a weighting histogram
   for (size_t oct1 = 0; oct1 < 9; oct1++)
   {
     for (size_t oct2 = 0; oct2 < 10; oct2++)
     {
      //for assymetry w/ CS
       mean_asymmetry_hits_cs[oct1][oct2] += h_asymmetry_hits_cs[ichunk][oct1][oct2]->GetMean();
       sigma_asymmetry_hits_cs[oct1][oct2] +=
         h_asymmetry_hits_cs[ichunk][oct1][oct2]->GetMean() * h_asymmetry_hits_cs[ichunk][oct1][oct2]->GetMean();

       //for asymetry with PEs and CS
       mean_asymmetry_PE_left_cs[oct1][oct2] += h_asymmetry_PE_left_cs[ichunk][oct1][oct2]->GetMean();
       sigma_asymmetry_PE_left_cs[oct1][oct2] +=
         h_asymmetry_PE_left_cs[ichunk][oct1][oct2]->GetMean() * h_asymmetry_PE_left_cs[ichunk][oct1][oct2]->GetMean();

       mean_asymmetry_PE_right_cs[oct1][oct2] += h_asymmetry_PE_right_cs[ichunk][oct1][oct2]->GetMean();
       sigma_asymmetry_PE_right_cs[oct1][oct2] +=
         h_asymmetry_PE_right_cs[ichunk][oct1][oct2]->GetMean() * h_asymmetry_PE_right_cs[ichunk][oct1][oct2]->GetMean();

       mean_asymmetry_PE_total_cs[oct1][oct2] += h_asymmetry_PE_total_cs[ichunk][oct1][oct2]->GetMean();
       sigma_asymmetry_PE_total_cs[oct1][oct2] +=
         h_asymmetry_PE_total_cs[ichunk][oct1][oct2]->GetMean() * h_asymmetry_PE_total_cs[ichunk][oct1][oct2]->GetMean();

       //for asymetry with PEs
       mean_asymmetry_PE_left[oct1][oct2] += h_asymmetry_PE_left[ichunk][oct1][oct2]->GetMean();
       sigma_asymmetry_PE_left[oct1][oct2] +=
         h_asymmetry_PE_left[ichunk][oct1][oct2]->GetMean() * h_asymmetry_PE_left[ichunk][oct1][oct2]->GetMean();

       mean_asymmetry_PE_right[oct1][oct2] += h_asymmetry_PE_right[ichunk][oct1][oct2]->GetMean();
       sigma_asymmetry_PE_right[oct1][oct2] +=
         h_asymmetry_PE_right[ichunk][oct1][oct2]->GetMean() * h_asymmetry_PE_right[ichunk][oct1][oct2]->GetMean();

       mean_asymmetry_PE_total[oct1][oct2] += h_asymmetry_PE_total[ichunk][oct1][oct2]->GetMean();
       sigma_asymmetry_PE_total[oct1][oct2] +=
         h_asymmetry_PE_total[ichunk][oct1][oct2]->GetMean() * h_asymmetry_PE_total[ichunk][oct1][oct2]->GetMean();

       //for PEs with CS
       mean_PE_left_cs[oct1][oct2] += h_PE_left_cs[ichunk][oct1][oct2]->GetMean();
       sigma_PE_left_cs[oct1][oct2] +=
         h_PE_left_cs[ichunk][oct1][oct2]->GetMean() * h_PE_left_cs[ichunk][oct1][oct2]->GetMean();

       mean_PE_right_cs[oct1][oct2] += h_PE_right_cs[ichunk][oct1][oct2]->GetMean();
       sigma_PE_right_cs[oct1][oct2] +=
         h_PE_right_cs[ichunk][oct1][oct2]->GetMean() * h_PE_right_cs[ichunk][oct1][oct2]->GetMean();

       mean_PE_total_cs[oct1][oct2] += h_PE_total_cs[ichunk][oct1][oct2]->GetMean();
       sigma_PE_total_cs[oct1][oct2] +=
         h_PE_total_cs[ichunk][oct1][oct2]->GetMean() * h_PE_total_cs[ichunk][oct1][oct2]->GetMean();

     }
    }
  }
//---------
  //output the data I have gatered
  //write out the ratios of the hits and aymmetries to the screen
  cout << "Active Oct  \t " << "MD # \t"  << "ratio hits \t" << "ratio asymmetry \t" << "ratio asymmetry Weight (CS) \t" <<
    "ratio asymmetry Weight (L PE) \t" << "ratio asymmetry Weight (R PE) \t" << "ratio asymmetry Weight (T PE) \t" <<
    "ratio asymmetry Weight (L PE& CS) \t" << "ratio asymmetry Weight (R PE & CS) \t" << "ratio asymmetry Weight (T PE & CS) \t" <<
    "L PE ratio \t" << "R PE ratio \t" << "T PE ratio \t" <<
    "L PE ratio Weight (CS) \t" << "R PE ratio Weight (CS) \t" << "T PE ratio Weight (CS) \t" <<  endl;
  for (size_t oct = 1; oct < h_asymmetry_hits.size(); oct ++)
  {
    cout << "Active Oct " << oct << endl;

    for (size_t oct2 = 1; oct2 < h_asymmetry_hits[oct].size(); oct2++)
    {
     //FOR NO WEIGHTING
      // caluculate the hit ratio and the error on that ratio
      Double_t hit_entries1 = h_asymmetry_hits[oct][oct2]->GetEntries();
      Double_t dhit_entries1 = sqrt(hit_entries1);
      Double_t hit_entries2 = h_asymmetry_hits[oct][oct]->GetEntries();
      Double_t dhit_entries2 = sqrt(dhit_entries2);
      Double_t hit_ratio = hit_entries1/hit_entries2;
      Double_t dhit_ratio = sqrt(pow(dhit_entries1/hit_entries2,2) + pow(hit_entries1*dhit_entries2/hit_entries2/hit_entries2,2));

      // Calucate the asymmerty and the error on that
      Double_t a_h_mean1 = h_asymmetry_hits[oct][oct2]->GetMean();
      Double_t da_h_mean1 = h_asymmetry_hits[oct][oct2]->GetRMS()/ sqrt(h_asymmetry_hits[oct][oct2]->GetEntries());
      Double_t a_h_mean2 = h_asymmetry_hits[oct][oct]->GetMean();
      Double_t da_h_mean2 = h_asymmetry_hits[oct][oct]->GetRMS()/ sqrt(h_asymmetry_hits[oct][oct]->GetEntries());
      Double_t a_h_ratio = a_h_mean1/a_h_mean2;
      Double_t da_h_ratio = sqrt(pow(da_h_mean1/a_h_mean2,2) + pow(a_h_mean1*da_h_mean2/a_h_mean2/a_h_mean2,2));

      // Calucate the Left PE and the error on that
      Double_t PE_l_mean1 = h_PE_left[oct][oct2]->GetMean();
      Double_t dPE_l_mean1 = h_PE_left[oct][oct2]->GetRMS()/ sqrt(h_PE_left[oct][oct2]->GetEntries());
      Double_t PE_l_mean2 = h_PE_left[oct][oct]->GetMean();
      Double_t dPE_l_mean2 = h_PE_left[oct][oct]->GetRMS()/ sqrt(h_PE_left[oct][oct]->GetEntries());
      Double_t PE_l_ratio = PE_l_mean1/PE_l_mean2;
      Double_t dPE_l_ratio = sqrt(pow(dPE_l_mean1/PE_l_mean2,2) + pow(PE_l_mean1*dPE_l_mean2/PE_l_mean2/PE_l_mean2,2));

      // Calucate the Right PE and the error on that
      Double_t PE_r_mean1 = h_PE_right[oct][oct2]->GetMean();
      Double_t dPE_r_mean1 = h_PE_right[oct][oct2]->GetRMS()/ sqrt(h_PE_right[oct][oct2]->GetEntries());
      Double_t PE_r_mean2 = h_PE_right[oct][oct]->GetMean();
      Double_t dPE_r_mean2 = h_PE_right[oct][oct]->GetRMS()/ sqrt(h_PE_right[oct][oct]->GetEntries());
      Double_t PE_r_ratio = PE_r_mean1/PE_r_mean2;
      Double_t dPE_r_ratio = sqrt(pow(dPE_r_mean1/PE_r_mean2,2) + pow(PE_r_mean1*dPE_r_mean2/PE_r_mean2/PE_r_mean2,2));

      // Calucate the Total PE and the error on that
      Double_t PE_t_mean1 = h_PE_total[oct][oct2]->GetMean();
      Double_t dPE_t_mean1 = h_PE_total[oct][oct2]->GetRMS()/ sqrt(h_PE_total[oct][oct2]->GetEntries());
      Double_t PE_t_mean2 = h_PE_total[oct][oct]->GetMean();
      Double_t dPE_t_mean2 = h_PE_total[oct][oct]->GetRMS()/ sqrt(h_PE_total[oct][oct]->GetEntries());
      Double_t PE_t_ratio = PE_t_mean1/PE_t_mean2;
      Double_t dPE_t_ratio = sqrt(pow(dPE_t_mean1/PE_t_mean2,2) + pow(PE_t_mean1*dPE_t_mean2/PE_t_mean2/PE_t_mean2,2));

     //FOR WEIGHTING
      // Calucate the asymmerty and the error on that (CS only)
      Double_t a_cs_mean1 = mean_asymmetry_hits_cs[oct][oct2] / nchunks;
      Double_t da_cs_mean1 = sqrt(sigma_asymmetry_hits_cs[oct][oct2] / nchunks
          - mean_asymmetry_hits_cs[oct][oct2] / nchunks * mean_asymmetry_hits_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_cs_mean2 = mean_asymmetry_hits_cs[oct][oct]/ nchunks;
      Double_t da_cs_mean2 = sqrt(sigma_asymmetry_hits_cs[oct][oct]/nchunks
          - mean_asymmetry_hits_cs[oct][oct] / nchunks * mean_asymmetry_hits_cs[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_cs_ratio = a_cs_mean1/a_cs_mean2;
      Double_t da_cs_ratio = sqrt(pow(da_cs_mean1/a_cs_mean2,2) + pow(a_cs_mean1*da_cs_mean2/a_cs_mean2/a_cs_mean2,2));

      // Calucate the asymmerty and the error on that (L PE only)
      Double_t a_PE_l_mean1 = mean_asymmetry_PE_left[oct][oct2] / nchunks;
      Double_t da_PE_l_mean1 = sqrt(sigma_asymmetry_PE_left[oct][oct2] / nchunks
          - mean_asymmetry_PE_left[oct][oct2] / nchunks * mean_asymmetry_PE_left[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_l_mean2 = mean_asymmetry_PE_left[oct][oct]/ nchunks;
      Double_t da_PE_l_mean2 = sqrt(sigma_asymmetry_PE_left[oct][oct]/nchunks
          - mean_asymmetry_PE_left[oct][oct] / nchunks * mean_asymmetry_PE_left[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_l_ratio = a_PE_l_mean1/a_PE_l_mean2;
      Double_t da_PE_l_ratio = sqrt(pow(da_PE_l_mean1/a_PE_l_mean2,2) + pow(a_PE_l_mean1*da_PE_l_mean2/a_PE_l_mean2/a_PE_l_mean2,2));

      // Calucate the asymmerty and the error on that (R PE only)
      Double_t a_PE_r_mean1 = mean_asymmetry_PE_right[oct][oct2] / nchunks;
      Double_t da_PE_r_mean1 = sqrt(sigma_asymmetry_PE_right[oct][oct2] / nchunks
          - mean_asymmetry_PE_right[oct][oct2] / nchunks * mean_asymmetry_PE_right[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_r_mean2 = mean_asymmetry_PE_right[oct][oct]/ nchunks;
      Double_t da_PE_r_mean2 = sqrt(sigma_asymmetry_PE_right[oct][oct]/nchunks
          - mean_asymmetry_PE_right[oct][oct] / nchunks * mean_asymmetry_PE_right[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_r_ratio = a_PE_r_mean1/a_PE_r_mean2;
      Double_t da_PE_r_ratio = sqrt(pow(da_PE_r_mean1/a_PE_r_mean2,2)
          + pow(a_PE_r_mean1*da_PE_r_mean2/a_PE_r_mean2/a_PE_r_mean2,2));

      // Calucate the asymmerty and the error on that (T PE only)
      Double_t a_PE_t_mean1 = mean_asymmetry_PE_total[oct][oct2] / nchunks;
      Double_t da_PE_t_mean1 = sqrt(sigma_asymmetry_PE_total[oct][oct2] / nchunks
          - mean_asymmetry_PE_total[oct][oct2] / nchunks * mean_asymmetry_PE_total[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_t_mean2 = mean_asymmetry_PE_total[oct][oct]/ nchunks;
      Double_t da_PE_t_mean2 = sqrt(sigma_asymmetry_PE_total[oct][oct]/nchunks
          - mean_asymmetry_PE_total[oct][oct] / nchunks * mean_asymmetry_PE_total[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_t_ratio = a_PE_t_mean1/a_PE_t_mean2;
      Double_t da_PE_t_ratio = sqrt(pow(da_PE_t_mean1/a_PE_t_mean2,2)
          + pow(a_PE_t_mean1*da_PE_t_mean2/a_PE_t_mean2/a_PE_t_mean2,2));

      // Calucate the asymmerty and the error on that (L PE & CS)
      Double_t a_PE_l_cs_mean1 = mean_asymmetry_PE_left_cs[oct][oct2] / nchunks;
      Double_t da_PE_l_cs_mean1 = sqrt(sigma_asymmetry_PE_left_cs[oct][oct2] / nchunks
          - mean_asymmetry_PE_left_cs[oct][oct2] / nchunks * mean_asymmetry_PE_left_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_l_cs_mean2 = mean_asymmetry_PE_left_cs[oct][oct]/ nchunks;
      Double_t da_PE_l_cs_mean2 = sqrt(sigma_asymmetry_PE_left_cs[oct][oct]/nchunks
          - mean_asymmetry_PE_left_cs[oct][oct] / nchunks * mean_asymmetry_PE_left_cs[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_l_cs_ratio = a_PE_l_cs_mean1/a_PE_l_cs_mean2;
      Double_t da_PE_l_cs_ratio = sqrt(pow(da_PE_l_cs_mean1/a_PE_l_cs_mean2,2)
          + pow(a_PE_l_cs_mean1*da_PE_l_cs_mean2/a_PE_l_cs_mean2/a_PE_l_cs_mean2,2));

      // Calucate the asymmerty and the error on that (R PE & CS)
      Double_t a_PE_r_cs_mean1 = mean_asymmetry_PE_right_cs[oct][oct2] / nchunks;
      Double_t da_PE_r_cs_mean1 = sqrt(sigma_asymmetry_PE_right_cs[oct][oct2] / nchunks
          - mean_asymmetry_PE_right_cs[oct][oct2] / nchunks * mean_asymmetry_PE_right_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_r_cs_mean2 = mean_asymmetry_PE_right_cs[oct][oct]/ nchunks;
      Double_t da_PE_r_cs_mean2 = sqrt(sigma_asymmetry_PE_right_cs[oct][oct]/nchunks
          - mean_asymmetry_PE_right_cs[oct][oct] / nchunks * mean_asymmetry_PE_right_cs[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_r_cs_ratio = a_PE_r_cs_mean1/a_PE_r_cs_mean2;
      Double_t da_PE_r_cs_ratio = sqrt(pow(da_PE_r_cs_mean1/a_PE_r_cs_mean2,2)
          + pow(a_PE_r_cs_mean1*da_PE_r_cs_mean2/a_PE_r_cs_mean2/a_PE_r_cs_mean2,2));

      // Calucate the asymmerty and the error on that (T PE & CS)
      Double_t a_PE_t_cs_mean1 = mean_asymmetry_PE_total_cs[oct][oct2] / nchunks;
      Double_t da_PE_t_cs_mean1 = sqrt(sigma_asymmetry_PE_total_cs[oct][oct2] / nchunks
          - mean_asymmetry_PE_total_cs[oct][oct2] / nchunks * mean_asymmetry_PE_total_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_t_cs_mean2 = mean_asymmetry_PE_total_cs[oct][oct]/ nchunks;
      Double_t da_PE_t_cs_mean2 = sqrt(sigma_asymmetry_PE_total_cs[oct][oct]/nchunks
          - mean_asymmetry_PE_total_cs[oct][oct] / nchunks * mean_asymmetry_PE_total_cs[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_t_cs_ratio = a_PE_t_cs_mean1/a_PE_t_cs_mean2;
      Double_t da_PE_t_cs_ratio = sqrt(pow(da_PE_t_cs_mean1/a_PE_t_cs_mean2,2)
          + pow(a_PE_t_cs_mean1*da_PE_t_cs_mean2/a_PE_t_cs_mean2/a_PE_t_cs_mean2,2));

// **********************************************************************
      // Calucate the L PEs with CS  and the error on that
      Double_t PE_l_cs_mean1 = mean_PE_left_cs[oct][oct2] / nchunks;
      Double_t dPE_l_cs_mean1 = sqrt(sigma_PE_left_cs[oct][oct2] / nchunks
          - mean_PE_left_cs[oct][oct2] / nchunks * mean_PE_left_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t PE_l_cs_mean2 = mean_PE_left_cs[oct][oct] / nchunks;
      Double_t dPE_l_cs_mean2 = sqrt(sigma_PE_left_cs[oct][oct]/nchunks
          - mean_PE_left_cs[oct][oct] / nchunks * mean_PE_left_cs[oct][oct]
          / nchunks)/ sqrt(nchunks);
      Double_t PE_l_cs_ratio = PE_l_cs_mean1/PE_l_cs_mean2;
      Double_t dPE_l_cs_ratio = sqrt(pow(dPE_l_cs_mean1/PE_l_cs_mean2,2)
          + pow(PE_l_cs_mean1*dPE_l_cs_mean2/PE_l_cs_mean2/PE_l_cs_mean2,2));

      // Calucate the R PEs with CS  and the error on that
      Double_t PE_r_cs_mean1 = mean_PE_right_cs[oct][oct2] / nchunks;
      Double_t dPE_r_cs_mean1 = sqrt(sigma_PE_right_cs[oct][oct2] / nchunks
          - mean_PE_right_cs[oct][oct2] / nchunks * mean_PE_right_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t PE_r_cs_mean2 = mean_PE_right_cs[oct][oct] / nchunks;
      Double_t dPE_r_cs_mean2 = sqrt(sigma_PE_right_cs[oct][oct]/nchunks
          - mean_PE_right_cs[oct][oct] / nchunks * mean_PE_right_cs[oct][oct]
          / nchunks)/ sqrt(nchunks);
      Double_t PE_r_cs_ratio = PE_r_cs_mean1/PE_r_cs_mean2;
      Double_t dPE_r_cs_ratio = sqrt(pow(dPE_r_cs_mean1/PE_r_cs_mean2,2)
          + pow(PE_r_cs_mean1*dPE_r_cs_mean2/PE_r_cs_mean2/PE_r_cs_mean2,2));

      // Calucate the T PEs with CS  and the error on that
      Double_t PE_t_cs_mean1 = mean_PE_total_cs[oct][oct2] / nchunks;
      Double_t dPE_t_cs_mean1 = sqrt(sigma_PE_total_cs[oct][oct2] / nchunks
          - mean_PE_total_cs[oct][oct2] / nchunks * mean_PE_total_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t PE_t_cs_mean2 = mean_PE_total_cs[oct][oct] / nchunks;
      Double_t dPE_t_cs_mean2 = sqrt(sigma_PE_total_cs[oct][oct]/nchunks
          - mean_PE_total_cs[oct][oct] / nchunks * mean_PE_total_cs[oct][oct]
          / nchunks)/ sqrt(nchunks);
      Double_t PE_t_cs_ratio = PE_t_cs_mean1/PE_t_cs_mean2;
      Double_t dPE_t_cs_ratio = sqrt(pow(dPE_t_cs_mean1/PE_t_cs_mean2,2)
          + pow(PE_t_cs_mean1*dPE_t_cs_mean2/PE_t_cs_mean2/PE_t_cs_mean2,2));


      //Double_t dratio = ratio * sqrt((dn1/n1)^2 + (dn2/n2)^2);
      cout << oct << " \t" << oct2 <<
          " \t" << std::setprecision(5)  << hit_ratio << " +/- " <<  dhit_ratio <<
          " \t \t " << std::setprecision(5)  << a_h_ratio << " +/- " <<  da_h_ratio <<
          " \t \t " << std::setprecision(5)  << a_cs_ratio << " +/- " <<  da_cs_ratio <<

          " \t \t " << std::setprecision(5)  << a_PE_l_ratio << " +/- " <<  da_PE_l_ratio <<
          " \t \t " << std::setprecision(5)  << a_PE_r_ratio << " +/- " <<  da_PE_r_ratio <<
          " \t \t " << std::setprecision(5)  << a_PE_t_ratio << " +/- " <<  da_PE_t_ratio <<

          " \t \t " << std::setprecision(5)  << a_PE_l_cs_ratio << " +/- " <<  da_PE_l_cs_ratio <<
          " \t \t " << std::setprecision(5)  << a_PE_r_cs_ratio << " +/- " <<  da_PE_r_cs_ratio <<
          " \t \t " << std::setprecision(5)  << a_PE_t_cs_ratio << " +/- " <<  da_PE_t_cs_ratio <<

          " \t \t " << std::setprecision(5)  << PE_l_ratio << " +/- " <<  dPE_l_ratio <<
          " \t \t " << std::setprecision(5)  << PE_r_ratio << " +/- " <<  dPE_r_ratio <<
          " \t \t " << std::setprecision(5)  << PE_t_ratio << " +/- " <<  dPE_t_ratio <<

          " \t \t " << std::setprecision(5)  << PE_l_cs_ratio << " +/- " <<  dPE_l_cs_ratio <<
          " \t \t " << std::setprecision(5)  << PE_r_cs_ratio << " +/- " <<  dPE_r_cs_ratio <<
          " \t \t " << std::setprecision(5)  << PE_t_cs_ratio << " +/- " <<  dPE_t_cs_ratio << endl;

//        "\t" << h_asymmetry[oct][oct2]->GetEntries() << " \t " << h_asymmetry[oct][oct]->GetEntries() << endl;
    }
  }

  //write out the ratios of the hits and aymmetries to the screen in HTML so that it can be imported to the elong with ease
  cout << "<table border = \"1\">" << endl;
  cout << "<tr><td align=\"center\" > Active Oct \
          </td><td align=\"center\"> MD # \
          </td><td align=\"center\"> ratio hits \
          </td><td align=\"center\"> ratio asymmetry \
          </td><td align=\"center\"> ratio asymmetry Weight (CS) \
          </td><td align=\"center\"> ratio asymmetry Weight (L PE) \
          </td><td align=\"center\"> ratio asymmetry Weight (R PE) \
          </td><td align=\"center\"> ratio asymmetry Weight (T PE) \
          </td><td align=\"center\"> ratio asymmetry Weight (L PE& CS) \
          </td><td align=\"center\"> ratio asymmetry Weight (R PE & CS) \
          </td><td align=\"center\"> ratio asymmetry Weight (T PE & CS) \
          </td><td align=\"center\"> L PE ratio \
          </td><td align=\"center\"> R PE ratio \
          </td><td align=\"center\"> T PE ratio \
          </td><td align=\"center\"> L PE ratio Weight (CS) \
          </td><td align=\"center\"> R PE ratio Weight (CS) \
          </td><td align=\"center\"> T PE ratio Weight (CS) </td></tr>" <<  endl;

  for (size_t oct = 1; oct < h_asymmetry_hits.size(); oct ++)
  {
    cout << "<tr><td colspan = \"17\" align=\"center\" >Active Oct " << oct << "</td></tr>" << endl;

    for (size_t oct2 = 1; oct2 < h_asymmetry_hits[oct].size(); oct2++)
    {

     //FOR NO WEIGHTING
      // caluculate the hit ratio and the error on that ratio
      Double_t hit_entries1 = h_asymmetry_hits[oct][oct2]->GetEntries();
      Double_t dhit_entries1 = sqrt(hit_entries1);
      Double_t hit_entries2 = h_asymmetry_hits[oct][oct]->GetEntries();
      Double_t dhit_entries2 = sqrt(dhit_entries2);
      Double_t hit_ratio = hit_entries1/hit_entries2;
      Double_t dhit_ratio = sqrt(pow(dhit_entries1/hit_entries2,2) + pow(hit_entries1*dhit_entries2/hit_entries2/hit_entries2,2));

      // Calucate the asymmerty and the error on that
      Double_t a_h_mean1 = h_asymmetry_hits[oct][oct2]->GetMean();
      Double_t da_h_mean1 = h_asymmetry_hits[oct][oct2]->GetRMS()/ sqrt(h_asymmetry_hits[oct][oct2]->GetEntries());
      Double_t a_h_mean2 = h_asymmetry_hits[oct][oct]->GetMean();
      Double_t da_h_mean2 = h_asymmetry_hits[oct][oct]->GetRMS()/ sqrt(h_asymmetry_hits[oct][oct]->GetEntries());
      Double_t a_h_ratio = a_h_mean1/a_h_mean2;
      Double_t da_h_ratio = sqrt(pow(da_h_mean1/a_h_mean2,2) + pow(a_h_mean1*da_h_mean2/a_h_mean2/a_h_mean2,2));

      // Calucate the Left PE and the error on that
      Double_t PE_l_mean1 = h_PE_left[oct][oct2]->GetMean();
      Double_t dPE_l_mean1 = h_PE_left[oct][oct2]->GetRMS()/ sqrt(h_PE_left[oct][oct2]->GetEntries());
      Double_t PE_l_mean2 = h_PE_left[oct][oct]->GetMean();
      Double_t dPE_l_mean2 = h_PE_left[oct][oct]->GetRMS()/ sqrt(h_PE_left[oct][oct]->GetEntries());
      Double_t PE_l_ratio = PE_l_mean1/PE_l_mean2;
      Double_t dPE_l_ratio = sqrt(pow(dPE_l_mean1/PE_l_mean2,2) + pow(PE_l_mean1*dPE_l_mean2/PE_l_mean2/PE_l_mean2,2));

      // Calucate the Right PE and the error on that
      Double_t PE_r_mean1 = h_PE_right[oct][oct2]->GetMean();
      Double_t dPE_r_mean1 = h_PE_right[oct][oct2]->GetRMS()/ sqrt(h_PE_right[oct][oct2]->GetEntries());
      Double_t PE_r_mean2 = h_PE_right[oct][oct]->GetMean();
      Double_t dPE_r_mean2 = h_PE_right[oct][oct]->GetRMS()/ sqrt(h_PE_right[oct][oct]->GetEntries());
      Double_t PE_r_ratio = PE_r_mean1/PE_r_mean2;
      Double_t dPE_r_ratio = sqrt(pow(dPE_r_mean1/PE_r_mean2,2) + pow(PE_r_mean1*dPE_r_mean2/PE_r_mean2/PE_r_mean2,2));

      // Calucate the Total PE and the error on that
      Double_t PE_t_mean1 = h_PE_total[oct][oct2]->GetMean();
      Double_t dPE_t_mean1 = h_PE_total[oct][oct2]->GetRMS()/ sqrt(h_PE_total[oct][oct2]->GetEntries());
      Double_t PE_t_mean2 = h_PE_total[oct][oct]->GetMean();
      Double_t dPE_t_mean2 = h_PE_total[oct][oct]->GetRMS()/ sqrt(h_PE_total[oct][oct]->GetEntries());
      Double_t PE_t_ratio = PE_t_mean1/PE_t_mean2;
      Double_t dPE_t_ratio = sqrt(pow(dPE_t_mean1/PE_t_mean2,2) + pow(PE_t_mean1*dPE_t_mean2/PE_t_mean2/PE_t_mean2,2));

     //FOR WEIGHTING
      // Calucate the asymmerty and the error on that (CS only)
      Double_t a_cs_mean1 = mean_asymmetry_hits_cs[oct][oct2] / nchunks;
      Double_t da_cs_mean1 = sqrt(sigma_asymmetry_hits_cs[oct][oct2] / nchunks
          - mean_asymmetry_hits_cs[oct][oct2] / nchunks * mean_asymmetry_hits_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_cs_mean2 = mean_asymmetry_hits_cs[oct][oct]/ nchunks;
      Double_t da_cs_mean2 = sqrt(sigma_asymmetry_hits_cs[oct][oct]/nchunks
          - mean_asymmetry_hits_cs[oct][oct] / nchunks * mean_asymmetry_hits_cs[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_cs_ratio = a_cs_mean1/a_cs_mean2;
      Double_t da_cs_ratio = sqrt(pow(da_cs_mean1/a_cs_mean2,2) + pow(a_cs_mean1*da_cs_mean2/a_cs_mean2/a_cs_mean2,2));

      // Calucate the asymmerty and the error on that (L PE only)
      Double_t a_PE_l_mean1 = mean_asymmetry_PE_left[oct][oct2] / nchunks;
      Double_t da_PE_l_mean1 = sqrt(sigma_asymmetry_PE_left[oct][oct2] / nchunks
          - mean_asymmetry_PE_left[oct][oct2] / nchunks * mean_asymmetry_PE_left[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_l_mean2 = mean_asymmetry_PE_left[oct][oct]/ nchunks;
      Double_t da_PE_l_mean2 = sqrt(sigma_asymmetry_PE_left[oct][oct]/nchunks
          - mean_asymmetry_PE_left[oct][oct] / nchunks * mean_asymmetry_PE_left[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_l_ratio = a_PE_l_mean1/a_PE_l_mean2;
      Double_t da_PE_l_ratio = sqrt(pow(da_PE_l_mean1/a_PE_l_mean2,2) + pow(a_PE_l_mean1*da_PE_l_mean2/a_PE_l_mean2/a_PE_l_mean2,2));

      // Calucate the asymmerty and the error on that (R PE only)
      Double_t a_PE_r_mean1 = mean_asymmetry_PE_right[oct][oct2] / nchunks;
      Double_t da_PE_r_mean1 = sqrt(sigma_asymmetry_PE_right[oct][oct2] / nchunks
          - mean_asymmetry_PE_right[oct][oct2] / nchunks * mean_asymmetry_PE_right[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_r_mean2 = mean_asymmetry_PE_right[oct][oct]/ nchunks;
      Double_t da_PE_r_mean2 = sqrt(sigma_asymmetry_PE_right[oct][oct]/nchunks
          - mean_asymmetry_PE_right[oct][oct] / nchunks * mean_asymmetry_PE_right[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_r_ratio = a_PE_r_mean1/a_PE_r_mean2;
      Double_t da_PE_r_ratio = sqrt(pow(da_PE_r_mean1/a_PE_r_mean2,2)
          + pow(a_PE_r_mean1*da_PE_r_mean2/a_PE_r_mean2/a_PE_r_mean2,2));

      // Calucate the asymmerty and the error on that (T PE only)
      Double_t a_PE_t_mean1 = mean_asymmetry_PE_total[oct][oct2] / nchunks;
      Double_t da_PE_t_mean1 = sqrt(sigma_asymmetry_PE_total[oct][oct2] / nchunks
          - mean_asymmetry_PE_total[oct][oct2] / nchunks * mean_asymmetry_PE_total[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_t_mean2 = mean_asymmetry_PE_total[oct][oct]/ nchunks;
      Double_t da_PE_t_mean2 = sqrt(sigma_asymmetry_PE_total[oct][oct]/nchunks
          - mean_asymmetry_PE_total[oct][oct] / nchunks * mean_asymmetry_PE_total[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_t_ratio = a_PE_t_mean1/a_PE_t_mean2;
      Double_t da_PE_t_ratio = sqrt(pow(da_PE_t_mean1/a_PE_t_mean2,2)
          + pow(a_PE_t_mean1*da_PE_t_mean2/a_PE_t_mean2/a_PE_t_mean2,2));

      // Calucate the asymmerty and the error on that (L PE & CS)
      Double_t a_PE_l_cs_mean1 = mean_asymmetry_PE_left_cs[oct][oct2] / nchunks;
      Double_t da_PE_l_cs_mean1 = sqrt(sigma_asymmetry_PE_left_cs[oct][oct2] / nchunks
          - mean_asymmetry_PE_left_cs[oct][oct2] / nchunks * mean_asymmetry_PE_left_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_l_cs_mean2 = mean_asymmetry_PE_left_cs[oct][oct]/ nchunks;
      Double_t da_PE_l_cs_mean2 = sqrt(sigma_asymmetry_PE_left_cs[oct][oct]/nchunks
          - mean_asymmetry_PE_left_cs[oct][oct] / nchunks * mean_asymmetry_PE_left_cs[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_l_cs_ratio = a_PE_l_cs_mean1/a_PE_l_cs_mean2;
      Double_t da_PE_l_cs_ratio = sqrt(pow(da_PE_l_cs_mean1/a_PE_l_cs_mean2,2)
          + pow(a_PE_l_cs_mean1*da_PE_l_cs_mean2/a_PE_l_cs_mean2/a_PE_l_cs_mean2,2));

      // Calucate the asymmerty and the error on that (R PE & CS)
      Double_t a_PE_r_cs_mean1 = mean_asymmetry_PE_right_cs[oct][oct2] / nchunks;
      Double_t da_PE_r_cs_mean1 = sqrt(sigma_asymmetry_PE_right_cs[oct][oct2] / nchunks
          - mean_asymmetry_PE_right_cs[oct][oct2] / nchunks * mean_asymmetry_PE_right_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_r_cs_mean2 = mean_asymmetry_PE_right_cs[oct][oct]/ nchunks;
      Double_t da_PE_r_cs_mean2 = sqrt(sigma_asymmetry_PE_right_cs[oct][oct]/nchunks
          - mean_asymmetry_PE_right_cs[oct][oct] / nchunks * mean_asymmetry_PE_right_cs[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_r_cs_ratio = a_PE_r_cs_mean1/a_PE_r_cs_mean2;
      Double_t da_PE_r_cs_ratio = sqrt(pow(da_PE_r_cs_mean1/a_PE_r_cs_mean2,2)
          + pow(a_PE_r_cs_mean1*da_PE_r_cs_mean2/a_PE_r_cs_mean2/a_PE_r_cs_mean2,2));

      // Calucate the asymmerty and the error on that (T PE & CS)
      Double_t a_PE_t_cs_mean1 = mean_asymmetry_PE_total_cs[oct][oct2] / nchunks;
      Double_t da_PE_t_cs_mean1 = sqrt(sigma_asymmetry_PE_total_cs[oct][oct2] / nchunks
          - mean_asymmetry_PE_total_cs[oct][oct2] / nchunks * mean_asymmetry_PE_total_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_t_cs_mean2 = mean_asymmetry_PE_total_cs[oct][oct]/ nchunks;
      Double_t da_PE_t_cs_mean2 = sqrt(sigma_asymmetry_PE_total_cs[oct][oct]/nchunks
          - mean_asymmetry_PE_total_cs[oct][oct] / nchunks * mean_asymmetry_PE_total_cs[oct][oct]
          / nchunks) / sqrt(nchunks);
      Double_t a_PE_t_cs_ratio = a_PE_t_cs_mean1/a_PE_t_cs_mean2;
      Double_t da_PE_t_cs_ratio = sqrt(pow(da_PE_t_cs_mean1/a_PE_t_cs_mean2,2)
          + pow(a_PE_t_cs_mean1*da_PE_t_cs_mean2/a_PE_t_cs_mean2/a_PE_t_cs_mean2,2));

// **********************************************************************
      // Calucate the L PEs with CS  and the error on that
      Double_t PE_l_cs_mean1 = mean_PE_left_cs[oct][oct2] / nchunks;
      Double_t dPE_l_cs_mean1 = sqrt(sigma_PE_left_cs[oct][oct2] / nchunks
          - mean_PE_left_cs[oct][oct2] / nchunks * mean_PE_left_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t PE_l_cs_mean2 = mean_PE_left_cs[oct][oct] / nchunks;
      Double_t dPE_l_cs_mean2 = sqrt(sigma_PE_left_cs[oct][oct]/nchunks
          - mean_PE_left_cs[oct][oct] / nchunks * mean_PE_left_cs[oct][oct]
          / nchunks)/ sqrt(nchunks);
      Double_t PE_l_cs_ratio = PE_l_cs_mean1/PE_l_cs_mean2;
      Double_t dPE_l_cs_ratio = sqrt(pow(dPE_l_cs_mean1/PE_l_cs_mean2,2)
          + pow(PE_l_cs_mean1*dPE_l_cs_mean2/PE_l_cs_mean2/PE_l_cs_mean2,2));

      // Calucate the R PEs with CS  and the error on that
      Double_t PE_r_cs_mean1 = mean_PE_right_cs[oct][oct2] / nchunks;
      Double_t dPE_r_cs_mean1 = sqrt(sigma_PE_right_cs[oct][oct2] / nchunks
          - mean_PE_right_cs[oct][oct2] / nchunks * mean_PE_right_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t PE_r_cs_mean2 = mean_PE_right_cs[oct][oct] / nchunks;
      Double_t dPE_r_cs_mean2 = sqrt(sigma_PE_right_cs[oct][oct]/nchunks
          - mean_PE_right_cs[oct][oct] / nchunks * mean_PE_right_cs[oct][oct]
          / nchunks)/ sqrt(nchunks);
      Double_t PE_r_cs_ratio = PE_r_cs_mean1/PE_r_cs_mean2;
      Double_t dPE_r_cs_ratio = sqrt(pow(dPE_r_cs_mean1/PE_r_cs_mean2,2)
          + pow(PE_r_cs_mean1*dPE_r_cs_mean2/PE_r_cs_mean2/PE_r_cs_mean2,2));

      // Calucate the T PEs with CS  and the error on that
      Double_t PE_t_cs_mean1 = mean_PE_total_cs[oct][oct2] / nchunks;
      Double_t dPE_t_cs_mean1 = sqrt(sigma_PE_total_cs[oct][oct2] / nchunks
          - mean_PE_total_cs[oct][oct2] / nchunks * mean_PE_total_cs[oct][oct2]
          / nchunks) / sqrt(nchunks);
      Double_t PE_t_cs_mean2 = mean_PE_total_cs[oct][oct] / nchunks;
      Double_t dPE_t_cs_mean2 = sqrt(sigma_PE_total_cs[oct][oct]/nchunks
          - mean_PE_total_cs[oct][oct] / nchunks * mean_PE_total_cs[oct][oct]
          / nchunks)/ sqrt(nchunks);
      Double_t PE_t_cs_ratio = PE_t_cs_mean1/PE_t_cs_mean2;
      Double_t dPE_t_cs_ratio = sqrt(pow(dPE_t_cs_mean1/PE_t_cs_mean2,2)
          + pow(PE_t_cs_mean1*dPE_t_cs_mean2/PE_t_cs_mean2/PE_t_cs_mean2,2));


      //Double_t dratio = ratio * sqrt((dn1/n1)^2 + (dn2/n2)^2);
      cout << "<tr><td align=\"center\"> " << oct << " </td><td align=\"center\"> " << oct2 <<
          " </td><td align=\"center\"> " << value_with_error(hit_ratio,dhit_ratio) <<
          " </td><td align=\"center\"> " << value_with_error(a_h_ratio,da_h_ratio) <<
          " </td><td align=\"center\"> " << value_with_error(a_cs_ratio,da_cs_ratio) <<

          " </td><td align=\"center\"> " << value_with_error(a_PE_l_ratio, da_PE_l_ratio) <<
          " </td><td align=\"center\"> " << value_with_error(a_PE_r_ratio, da_PE_r_ratio) <<
          " </td><td align=\"center\"> " << value_with_error(a_PE_t_ratio, da_PE_t_ratio) <<

          " </td><td align=\"center\"> " << value_with_error(a_PE_l_cs_ratio, da_PE_l_cs_ratio) <<
          " </td><td align=\"center\"> " << value_with_error(a_PE_r_cs_ratio, da_PE_r_cs_ratio) <<
          " </td><td align=\"center\"> " << value_with_error(a_PE_t_cs_ratio, da_PE_t_cs_ratio) <<

          " </td><td align=\"center\"> " << value_with_error(a_PE_l_ratio, da_PE_l_ratio) <<
          " </td><td align=\"center\"> " << value_with_error(a_PE_r_ratio, da_PE_r_ratio) <<
          " </td><td align=\"center\"> " << value_with_error(a_PE_t_ratio, da_PE_t_ratio) <<

          " </td><td align=\"center\"> " << value_with_error(PE_l_ratio, dPE_l_ratio) <<
          " </td><td align=\"center\"> " << value_with_error(PE_r_ratio, dPE_r_ratio) <<
          " </td><td align=\"center\"> " << value_with_error(PE_t_ratio, dPE_t_ratio) << endl;

//        "\t" << h_asymmetry[oct][oct2]->GetEntries() << " \t " << h_asymmetry[oct][oct]->GetEntries() << endl;
    }
  }
  cout << "</table>" << endl;

  return;
}
