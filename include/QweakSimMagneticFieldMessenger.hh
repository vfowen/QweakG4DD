//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**

   \file QweakSimMagneticFieldMessenger.hh
   $Revision: 1.2 $
   $Date: 2005/12/27 19:25:29 $
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
   \class QweakSimMagneticFieldMessenger

   \brief Scans input file for /MagnetField/xyz commands

    Not used yet. Intended to set the StepperType and SetMinStep for the magnet fields.

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
//  Update Date:      $Date: 2005/12/27 19:25:29 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
//
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef QweakSimMagneticFieldMessenger_h
#define QweakSimMagneticFieldMessenger_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimMagneticField;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimMagneticFieldMessenger: public G4UImessenger
{
  public:
    QweakSimMagneticFieldMessenger(QweakSimMagneticField* );
   ~QweakSimMagneticFieldMessenger();

    void SetNewValue(G4UIcommand* command, G4String newValue);

  private:

    QweakSimMagneticField*     fMagneticField;

    G4UIdirectory*             MagneticFieldDir;

    G4UIcmdWithAString*        ReadCmd;

    G4UIcmdWith3VectorAndUnit* PrintCmd;

    G4UIcmdWithADoubleAndUnit* RotationCmd;
    G4UIcmdWithADoubleAndUnit* TranslationCmd;

    G4UIcmdWithADoubleAndUnit* MinZCmd;
    G4UIcmdWithADoubleAndUnit* MaxZCmd;
    G4UIcmdWithADoubleAndUnit* StepZCmd;

    G4UIcmdWithADoubleAndUnit* MinRCmd;
    G4UIcmdWithADoubleAndUnit* MaxRCmd;
    G4UIcmdWithADoubleAndUnit* StepRCmd;

    G4UIcmdWithADoubleAndUnit* MinPhiCmd;
    G4UIcmdWithADoubleAndUnit* MaxPhiCmd;
    G4UIcmdWithADoubleAndUnit* StepPhiCmd;
    G4UIcmdWithAnInteger*      WrapPhiCmd;

    G4UIcmdWithADouble*        ScaleCmd;
    G4UIcmdWithADouble*        RefCurrentCmd;
    G4UIcmdWithADouble*        ActCurrentCmd;

    G4UIcmdWithAnInteger*      StepperCmd;
    G4UIcmdWithADoubleAndUnit* MinStepCmd;
    G4UIcmdWithoutParameter*   UpdateCmd;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
//
//      $Revisions$
//      $Log: QweakSimMagneticFieldMessenger.hh,v $
//      Revision 1.2  2005/12/27 19:25:29  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
