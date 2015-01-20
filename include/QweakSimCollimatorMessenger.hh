
//=============================================================================
/**
 
   \file QweakSimCollimatorMessenger.hh
   
   \version 1.0
   \date  Wednesday 23 November 2005 , 23:17
 
   \author Klaus Hans Grimm

*/
//=============================================================================
/**
   \class QweakSimCollimator
    
   \brief Scans the input file for /Cerenkov/xyz commands

   Placeholder for a long explanation
    
 */
//=============================================================================
// 


#ifndef QweakSimCollimatorMessenger_h
#define QweakSimCollimatorMessenger_h 1

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimCollimator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimCollimatorMessenger: public G4UImessenger
{
public:
  QweakSimCollimatorMessenger(QweakSimCollimator*);
  ~QweakSimCollimatorMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  QweakSimCollimator*     myCollimator;
  
  G4UIdirectory*             CollimatorDir;
  
  G4UIcmdWithAString*        CollimatorMatCmd;
  G4UIcmdWithADoubleAndUnit* CollimatorZPosCmd;
  
  G4UIdirectory*             OctantCutOutDir;

  G4UIcmdWithADoubleAndUnit* OctantCutOut_RadialDistance_Cmd;
  G4UIcmdWithADoubleAndUnit* OctantCutOut_FullLengthFront_Cmd;
  G4UIcmdWithADoubleAndUnit* OctantCutOut_FullLengthBack_Cmd;
  G4UIcmdWithADoubleAndUnit* OctantCutOut_FullHeightFront_Cmd;
  G4UIcmdWithADoubleAndUnit* OctantCutOut_FullHeightBack_Cmd;
  G4UIcmdWithADoubleAndUnit* OctantCutOut_PolarAngle_Cmd;

  G4UIcmdWithoutParameter*   UpdateCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

