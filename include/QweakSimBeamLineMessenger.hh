//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimBeamLineMessenger.hh
   $Revision: 1.2 $	
   $Date: 2011/10/19 12:44 $
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
   \class QweakSimBeamLineMessenger
    
   \brief Placeholder for a long explaination
    
 */
//=============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimBeamLineMessenger_h
#define QweakSimBeamLineMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimBeamLine;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimBeamLineMessenger: public G4UImessenger
{
  public:
    QweakSimBeamLineMessenger(QweakSimBeamLine*);
   ~QweakSimBeamLineMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    QweakSimBeamLine*            myBeamLine;

    G4UIdirectory*             BeamLineDir;

    G4UIcmdWithAString*        BeamLineMatCmd;
    G4UIcmdWithADoubleAndUnit* BeamLineZPosCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
