//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimPrimaryGeneratorActionMessenger.hh
   $Revision: 1.3 $	
   $Date: 2006/05/05 21:33:13 $
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
   \class QweakSimPrimaryGeneratorActionMessenger
    
   \brief Scans the input file for ...

   Placeholder for a long explaination
    
 */


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimPrimaryGeneratorActionMessenger_h
#define QweakSimPrimaryGeneratorActionMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimPrimaryGeneratorAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimPrimaryGeneratorActionMessenger: public G4UImessenger
{
public:  
   QweakSimPrimaryGeneratorActionMessenger(QweakSimPrimaryGeneratorAction* );
   virtual ~QweakSimPrimaryGeneratorActionMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:  
  
  QweakSimPrimaryGeneratorAction*     pPrimaryGeneratorAction;
  
  G4UIdirectory*           Dir;
  G4UIcmdWithAnInteger*    verboseCmd;
  G4UIcmdWithoutParameter* resetCmd;
  G4UIcmdWithAnInteger*    InitEventCounterCmd;
  G4UIcmdWithAString*      SetParticleType_Cmd;
  G4UIcmdWithAString*      SetPolarization_Cmd;

  G4UIcmdWithABool* SetFixedPosMom_Cmd;
  
  G4UIcmdWithADoubleAndUnit*    SetPositionX_Cmd;
  G4UIcmdWithADoubleAndUnit*    SetPositionY_Cmd;
  G4UIcmdWithADoubleAndUnit*    SetPositionZ_Cmd;

  G4UIcmdWithADoubleAndUnit*    SetDirectionX_Cmd;
  G4UIcmdWithADoubleAndUnit*    SetDirectionY_Cmd;

  G4UIcmdWithADoubleAndUnit*    SetRasterXmin_Cmd;
  G4UIcmdWithADoubleAndUnit*    SetRasterXmax_Cmd;
  G4UIcmdWithADoubleAndUnit*    SetRasterYmin_Cmd;
  G4UIcmdWithADoubleAndUnit*    SetRasterYmax_Cmd;

  G4double Xmin;
  G4double Xmax;
  G4double Ymin;
  G4double Ymax;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


