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

  static G4UIcmdWithADoubleAndUnit* SetPbStepSizeCmd;

  G4int fOctant;
  G4UIdirectory*             DirPerOctant;

  G4UIcmdWithADoubleAndUnit* ContainerXPositionCmd;
  G4UIcmdWithADoubleAndUnit* ContainerYPositionCmd;
  G4UIcmdWithADoubleAndUnit* ContainerZPositionCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

