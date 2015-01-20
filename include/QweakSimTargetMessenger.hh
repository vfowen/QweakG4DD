//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTargetMessenger.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:27:14 $
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
   \class QweakSimTargetMessenger
    
   \brief Scans the input file for /Target/xyz commands

   Placeholder for a long explaination
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:27:14 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimTargetMessenger_h
#define QweakSimTargetMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimTarget;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimTargetMessenger: public G4UImessenger
{
  public:
    QweakSimTargetMessenger(QweakSimTarget*);
   ~QweakSimTargetMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    QweakSimTarget*            myTarget;

    G4UIdirectory*             TargetDir;

    G4UIcmdWithAString*        TargCmd;
    G4UIcmdWithAString*        TargMatCmd;
    G4UIcmdWithAString*        TargCellMatCmd;
    G4UIcmdWithAString*	       TargEntWinMatCmd;
    G4UIcmdWithAString*        TargExtWinMatCmd;
    G4UIcmdWithAString*        TargExtWinNipMatCmd;
    G4UIcmdWithADoubleAndUnit* TargZPosCmd;

    G4UIcmdWithADoubleAndUnit* TargLenCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTargetMessenger.hh,v $
//      Revision 1.2  2005/12/27 19:27:14  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
