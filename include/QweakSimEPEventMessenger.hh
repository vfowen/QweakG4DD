//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimEPEventMessenger.hh
   \author Peiqing Wang
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimEPEventMessenger
    
   \brief UI control for the event generator 
    
 */


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimEPEventMessenger_h
#define QweakSimEPEventMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimEPEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimEPEventMessenger: public G4UImessenger
{
public:  
   QweakSimEPEventMessenger(QweakSimEPEvent* );
  ~QweakSimEPEventMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:  
  
  QweakSimEPEvent*     pQweakSimEPEvent;
  
  G4UIdirectory*           EventGenDir;
  G4UIcmdWithAnInteger*    verboseCmd;
  G4UIcmdWithAnInteger*    SelectReactionType_Cmd;
  G4UIcmdWithAnInteger*    SelectReactionRegion_Cmd;
  G4UIcmdWithAnInteger*    SelectOctant_Cmd;
  G4UIcmdWithAnInteger*    SelectIsotropy_Cmd;
  
  G4UIcmdWithADoubleAndUnit* ThetaMinLimitCmd;
  G4UIcmdWithADoubleAndUnit* ThetaMaxLimitCmd;
  G4UIcmdWithADoubleAndUnit* PhiMinLimitCmd;
  G4UIcmdWithADoubleAndUnit* PhiMaxLimitCmd;
  G4UIcmdWithADoubleAndUnit* EPrimeMinLimitCmd;
  G4UIcmdWithADoubleAndUnit* EPrimeMaxLimitCmd;
  G4UIcmdWithADoubleAndUnit* SetBeamEnergyCmd;
  G4UIcmdWithADoubleAndUnit* SetElasticPeakDeltaECmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


