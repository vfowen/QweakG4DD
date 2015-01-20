#include <iostream>

#include "TCanvas.h"
#include "TChain.h"
#include "TH1D.h"

#include "QweakSimUserMainEvent.hh"

TH1D* hx;
TH1D* hy;

void LoopOverEvents()
{
  //add files
  TChain* QweakSimG4_Tree = new TChain("QweakSimG4_Tree");
  QweakSimG4_Tree->Add("../QwSim_0.root");

  //set addresses of leafs
  QweakSimUserMainEvent* event = 0;
  QweakSimG4_Tree->SetBranchAddress("QweakSimUserMainEvent",&event);

  //create histogram
  hx = new TH1D("hx","hx",100,-250.0,250.0);
  hy = new TH1D("hy","hy",100,-250.0,250.0);

  //loop over events
  for (int i = 0; i < QweakSimG4_Tree->GetEntries(); i++) {
    QweakSimG4_Tree->GetEntry(i);

    //loop over hits
    for (int hit = 0; hit < event->Cerenkov.Detector.NbOfHits; hit++) {
      hx->Fill(event->Cerenkov.Detector.HitGlobalPositionX[hit]);
      hy->Fill(event->Cerenkov.Detector.HitGlobalPositionY[hit]);
    }
  }

  //draw histograms
  TCanvas* c1 = new TCanvas();
  c1->Divide(2,1);
  c1->cd(1);
  hx->Draw();
  c1->cd(2);
  hy->Draw();
}
