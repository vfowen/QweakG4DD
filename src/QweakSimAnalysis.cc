//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**
 
   \file QweakSimAnalysis.cc

   $Revision: 1.4 $
   $Date: 2006/01/06 19:12:25 $

   \author Klaus Hans Grimm

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <ctime>

// geant4 includes
#include "G4Run.hh"

// user includes
#include "QweakSimAnalysis.hh"
#include "QweakSimUserInformation.hh"
#include "QweakSimUserRunInformation.hh"
#include "QweakSimUserMainEvent.hh"
#include "QweakSimAnalysisMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimAnalysis::QweakSimAnalysis(QweakSimUserInformation *userInfo)
: fRootFileStem("QwSim"),fRootFileName("")
{
  G4cout << "###### Calling QweakSimAnalysis::QweakSimAnalysis()" << G4endl;

  myUserInfo = userInfo;

  // Initialize
  fRootEvent    = NULL;
  fRootNtuple   = NULL;
  fRootBranch   = NULL;
  fRootFile     = NULL;

  // Create messenger
  pAnalysisMessenger = new QweakSimAnalysisMessenger(this);

  // Create user run data
  pUserRunInformation = new QweakSimUserRunInformation();

  G4cout << "###### Leaving QweakSimAnalysis::QweakSimAnalysis()" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimAnalysis::~QweakSimAnalysis()
{
  G4cout << "###### Calling QweakSimAnalysis::QweakSimAnalysis()" << G4endl;

  // Delete ROOT objects
  if (fRootEvent)    delete fRootEvent;
  if (fRootNtuple)   delete fRootNtuple;
  if (fRootBranch)   delete fRootBranch;
  if (fRootFile)     delete fRootFile;

  // Delete messenger
  if (pAnalysisMessenger) delete pAnalysisMessenger;

  G4cout << "###### Leaving QweakSimAnalysis::QweakSimAnalysis()" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// Get and set number of events in this run
void QweakSimAnalysis::SetNumberOfEventToBeProcessed(G4int n) {
  myUserInfo->SetNumberOfEventToBeProcessed(n);
}
G4int QweakSimAnalysis::GetNumberOfEventToBeProcessed() const {
  return myUserInfo->GetNumberOfEventToBeProcessed();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimAnalysis::BeginOfRun(const G4Run* aRun)
{
  // Get run number
  G4int runID = aRun->GetRunID();

  // Construct file name if not set explicitly
  if (fRootFileName.size() == 0)
    fRootFileName = fRootFileStem + "_" + Form("%d",runID) + ".root";

  // Create ROOT file
  G4cout << "###### Analysis: creating ROOT file " << fRootFileName << G4endl;
  fRootFile = new TFile(fRootFileName,"RECREATE","Qweak ROOT file");
  ConstructRootNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimAnalysis::EndOfRun(const G4Run* /*aRun*/)
{
  // Autosave one last time
  AutoSaveRootNtuple();

  // Write the data to the ROOT file
  G4cout << "###### Analysis: closing ROOT file " << fRootFileName << G4endl;
  fRootFile->Write(0,TObject::kOverwrite);
  fRootFile->Close();
  fRootFileName = "";
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimAnalysis::EndOfEvent(G4int flag)
{
  // This member is called at the end of every event
  if (!flag) return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimAnalysis::ConstructRootNtuple()
{
  // Create ROOT tree
  fRootNtuple = new TTree("QweakSimG4_Tree","Qweak Geant4 Simulation Tree");

  // Save the file after so many bytes. Avoids complete data loss after crash
  //fRootNtuple ->SetAutoSave(1000000);  //AutoSave after every 1 Mbyte written to disk

  // Instance of data structure to be written into ROOT file
  fRootEvent  = new QweakSimUserMainEvent();

  // Create a branch with the data structure defined by fRootEvent
  int bufsize = 64000;
  int split   = 99;
  fRootBranch = fRootNtuple->Branch("QweakSimUserMainEvent", "QweakSimUserMainEvent", &fRootEvent, bufsize, split);

  // Write run data
  pUserRunInformation->Write();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void QweakSimAnalysis::AutoSaveRootNtuple()
{
  // save the current ntuple:
  // In case your program crashes before closing the file holding this tree,
  // the file will be automatically recovered when you will connect the file
  // in UPDATE mode.
  // The Tree will be recovered at the status corresponding to the last AutoSave.
  //
  // if option contains "SaveSelf", gDirectory->SaveSelf() is called.
  // This allows another process to analyze the Tree while the Tree is being filled.
  //
  // see http://root.cern.ch/root/html/TTree.html#TTree:AutoSave

  // fRootNtuple -> AutoSave("SaveSelf");
  fRootNtuple -> AutoSave();
  gDirectory -> Purge(); //jpan: Purge old trees
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

