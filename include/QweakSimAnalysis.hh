//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**

   \file QweakSimAnalysis.hh
   $Revision: 1.2 $
   $Date: 2005/12/27 19:22:16 $
   \author Klaus Hans Grimm

*/
//=============================================================================
//
//=============================================================================
//
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimAnalysis

   \brief Handling of the output ROOT file

   Placeholder for a long explaination

 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimAnalysis_h
#define QweakSimAnalysis_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// geant4 includes
#include "G4Types.hh"
#include "G4String.hh"

// root includes
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

// geant4 classes
class G4Run;

// user classes
class QweakSimUserInformation;
class QweakSimUserRunInformation;
class QweakSimUserMainEvent;
class QweakSimAnalysisMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimAnalysis {
public:

  QweakSimAnalysis(QweakSimUserInformation*);
  virtual ~QweakSimAnalysis();

public:

  void BeginOfRun(const G4Run* aRun);
  void EndOfRun(const G4Run* aRun);
  void EndOfEvent(G4int flag);

  // Get and set number of events in this run
  void SetNumberOfEventToBeProcessed(G4int n);
  G4int GetNumberOfEventToBeProcessed() const;

  // Set ROOT file stem or name
  void SetRootFileStem(const G4String& stem) { fRootFileStem = stem; }
  void SetRootFileName(const G4String& name) { fRootFileName = name; }

  void FillRootNtuple() { fRootNtuple->Fill(); }
  void AutoSaveRootNtuple();

  QweakSimUserMainEvent* fRootEvent;

private:

  QweakSimAnalysisMessenger* pAnalysisMessenger;

  QweakSimUserInformation* myUserInfo;

  QweakSimUserRunInformation* pUserRunInformation;

  G4String fRootFileStem;
  G4String fRootFileName;

  void ConstructRootNtuple();

  TTree*   fRootNtuple;
  TBranch* fRootBranch;
  TFile*   fRootFile;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

