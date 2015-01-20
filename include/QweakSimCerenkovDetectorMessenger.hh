//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimCerenkovDetectorMessenger.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:23:04 $
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
   \class QweakSimCerenkovDetectorMessenger
    
   \brief Scans the input file for /Cerenkov/xyz commands

   Placeholder for a long explaination
    
 */
//=============================================================================
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimCerenkovDetectorMessenger_h
#define QweakSimCerenkovDetectorMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

//user classes
class QweakSimCerenkovDetector;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimCerenkovDetectorMessenger: public G4UImessenger
{
  public:
    QweakSimCerenkovDetectorMessenger(QweakSimCerenkovDetector*, G4int octant = 1);
   ~QweakSimCerenkovDetectorMessenger();
    G4int GetOctant() {return fOctant;}
    void SetNewValue(G4UIcommand*, G4String);
    
    void CreateCommands(QweakSimCerenkovDetector*);

private:
  QweakSimCerenkovDetector*         myCerenkovDetector;
  
  static G4UIdirectory*             Dir;

  static G4UIcmdWithAString*        ContainerMatCmd;
  static G4UIcmdWithAString*        DetectorMatCmd;
  static G4UIcmdWithAString*        PreRadiatorMatCmd;

  static G4UIcmdWithADoubleAndUnit* ContainerThicknessCmd;

  static G4UIcmdWithADoubleAndUnit* TiltingAngleCmd;
  static G4UIcmdWithADoubleAndUnit* KinkAngleCmd;

  static G4UIcmdWithAnInteger*      NumberOfDetectorsCmd;

  G4int fOctant;
  G4UIdirectory*             DirPerOctant;

  G4UIcmdWithADoubleAndUnit* ContainerXPositionCmd;
  G4UIcmdWithADoubleAndUnit* ContainerYPositionCmd;
  G4UIcmdWithADoubleAndUnit* ContainerZPositionCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

