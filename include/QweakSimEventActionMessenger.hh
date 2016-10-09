//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimEventActionMessenger.hh

   $Revision: 1.0 $
   $Date: 2009/10/17 20:02:16 $

   \author Wouter Deconinck

*/
//=============================================================================
//
//=============================================================================
//
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimEventActionMessenger

   \brief Messenger for filling//storing the hit event structure at the end of an event

   Placeholder for a long explanation

 */
//=============================================================================

#ifndef QweakSimEventActionMessenger_h
#define QweakSimEventActionMessenger_h 1

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimEventAction;

// ----------------------------------------------------------------------------

class QweakSimEventActionMessenger: public G4UImessenger
{

  public:

    QweakSimEventActionMessenger(QweakSimEventAction*);
   ~QweakSimEventActionMessenger();

    void SetNewValue( G4UIcommand*, G4String );
    void SetNewValue( G4UIcommand*, G4int );

  private:

    QweakSimEventAction*       theEventAction;
    G4UIdirectory*             theTriggerDir;
    G4UIcmdWithoutParameter*   theTriggerShowCommand;
    G4UIcmdWithAString*        theTriggerEnableCommand;
    G4UIcmdWithAString*        theTriggerDisableCommand;
    G4UIcmdWithABool*          thePrintHitsCommand;
    G4UIcmdWithAnInteger*      physProcCmd;
    G4UIcmdWithAnInteger*      physProcAnCmd;
};

// ----------------------------------------------------------------------------

#endif
