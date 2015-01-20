//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTrackingActionMessenger.hh
   $Revision: 1.1 $	
   $Date: 2006/01/06 04:47:29 $
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
   \class QweakSimTrackingActionMessenger
    
   \brief Scans the input file for /TrackingAction/xyz commands

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
//  Update Date:      $Date: 2006/01/06 04:47:29 $
//  CVS/RCS Revision: $Revision: 1.1 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimTrackingActionMessenger_h
#define QweakSimTrackingActionMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimTrackingAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimTrackingActionMessenger: public G4UImessenger
{
  public:
    QweakSimTrackingActionMessenger(QweakSimTrackingAction*);
   ~QweakSimTrackingActionMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:

    QweakSimTrackingAction*    myTrackingAction;

    G4UIdirectory*             TrackingActionDir;

    G4UIcmdWithAnInteger*      TrackingFlag_Cmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTrackingActionMessenger.hh,v $
//      Revision 1.1  2006/01/06 04:47:29  grimm
//      Initial version. Allows to set a flag for the tracking of primary electrons.
//
//
// 
