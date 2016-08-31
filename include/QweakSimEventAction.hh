//=============================================================================
/**

   \file QweakSimEventAction.hh
   $Revision: 1.4 $
   $Date: 2006/01/06 21:29:35 $
   \author Klaus Hans Grimm

*/
//=============================================================================
//
//=============================================================================
/**
   \class QweakSimEventAction

   \brief Mainly filling/storing the hit event structure at the end of an event

   Placeholder for a long explaination

 */
//=============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimEventAction_h
#define QweakSimEventAction_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include <vector>
#include <map>

// root includes
#include "Rtypes.h"
#include "TString.h"

// geant4 includes
#include "G4Types.hh"
#include "G4String.hh"
#include "G4ThreeVector.hh"
#include "G4UserEventAction.hh"

// user classes
class QweakSimAnalysis;
class QweakSimUserInformation;
class QweakSimEventActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

enum EQweakSimTriggerMode
  { kTriggerAll, kTrigger4Fold, kTrigger3Fold,
    kTriggerScint, kTriggerLeadGlass, kTriggerCer, kTriggerLumi,
    kTriggerHDC, kTriggerPMTOnly, kNumTriggers};

class QweakSimEventAction : public G4UserEventAction
{
public:
    //!Constructor
    QweakSimEventAction(std::vector<double>*asInfo,QweakSimAnalysis* AN, QweakSimUserInformation* myUI);

    //!Destructor
    virtual ~QweakSimEventAction();

public:

  void BeginOfEventAction(const G4Event* evt);
  void EndOfEventAction(const G4Event* evt);

  void ShowTrigger();
  void SetTrigger(const G4String value, const G4bool status);
  void EnableTrigger(const G4String value) { SetTrigger(value, true); };
  void DisableTrigger(const G4String value) { SetTrigger(value, false); };
  void SetPrintHits(bool value) {printhits = value;};
  void SetPhysicsProcFlag(int flag){asymInfo->at(3)=flag;}

private:

  void Initialize();
  G4double GetDistance(G4ThreeVector,G4ThreeVector);
  void CalculateKinematicVariables();
  G4double CalculateRate(G4double xsec, G4int PEs);

  bool printhits;

  // Event action messenger
  QweakSimEventActionMessenger* fEventActionMessenger;

  // Trigger mask
  std::vector<G4bool> fTrigger;
  std::vector<G4String> fTriggerName;
  std::map < G4String, EQweakSimTriggerMode > kMapTriggerMode;


  G4int TargetDetector_CollID;
  G4int GEM_WirePlane_CollID;
  G4int HDC_WirePlane_CollID;
  G4int VDC_WirePlane_CollID;
  G4int VDC_DriftCellFront_CollID;
  G4int VDC_DriftCellBack_CollID;
  G4int TriggerScintillatorDetector_CollID;
  G4int TriggerScintillatorPMT_CollID;
  G4int LeadGlassDetector_CollID;
  G4int LeadGlassPMT_CollID;
  G4int PMTOnlyDetector_CollID;
  G4int PMTOnlyDetectorPMT_CollID;
  G4int CerenkovDetector_CollID;
  G4int CerenkovDetectorPMT_CollID;
  G4int LumiDetector_CollID;
  G4int LumiDetectorPMT_CollID;

  QweakSimAnalysis*             analysis;
  QweakSimUserInformation*      myUserInfo;

  // Print hits for some subsystems during debugging
  //static const G4bool print_GEM_WirePlaneHit = false;
  static const G4bool print_VDC_WirePlaneHit = false;
  static const G4bool print_VDC_DriftCellHit = false;
  static const G4bool print_TriggerScintillator_DetectorHit = false;
  static const G4bool print_Cerenkov_DetectorHit = false;

  //-----------------------------------------

  static const int PmtMaxSize = 18;

  std::vector<double> *asymInfo;
  G4int  octantID;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

