//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimGeometryMessenger.cc

   $Revision: 1.0 $
   $Date: 2009/10/12 13:32:26 $

   \author Wouter Deconinck

*/
//=============================================================================

#include "QweakSimGeometryMessenger.hh"

// user includes
#include "QweakSimGeometry.hh"
#include "QweakSimMessengerDefinition.hh"

// ----------------------------------------------------------------------------

QweakSimGeometryMessenger::QweakSimGeometryMessenger(QweakSimGeometry* aGeometry)
  : theGeometry(aGeometry)
{
  G4cout << G4endl << "###### Calling QweakSimGeometryMessenger::QweakSimGeometryMessenger() " << G4endl << G4endl;

  theGeometryDir = new G4UIdirectory( "/GDML/" );
  theGeometryDir->SetGuidance("GDML geometry control.");

  theReadCommand = new G4UIcmdWithAString("/GDML/Read", this);
  theReadCommand->SetGuidance("Read geometry from GDML file with given name");
  theReadCommand->SetParameterName("FileRead", false);
  theReadCommand->SetDefaultValue("GMDL/qweak.gdml");
  theReadCommand->AvailableForStates(G4State_PreInit);

  theWriteCommand = new G4UIcmdWithAString("/GDML/Write", this);
  theWriteCommand->SetGuidance("Write geometry to GDML file with given name");
  theWriteCommand->SetParameterName("FileWrite", false);
  theWriteCommand->SetDefaultValue("GDML/qweak_out.gdml");
  theWriteCommand->AvailableForStates(G4State_Idle);

  theDepthCommand = new G4UIcmdWithAnInteger("/GDML/WriteDepth", this);
  theDepthCommand->SetGuidance("Split GDML output in automatic modules");
  theDepthCommand->SetParameterName("WriteDepth", false);
  theDepthCommand->SetDefaultValue(2);
  theDepthCommand->AvailableForStates(G4State_Idle);

  theModuleCommand = new G4UIcmdWithABool("/GDML/WriteModule", this);
  theModuleCommand->SetGuidance("Split GDML output in user modules");
  theModuleCommand->SetParameterName("WriteModule", false);
  theModuleCommand->SetDefaultValue(false);
  theModuleCommand->AvailableForStates(G4State_Idle);

  G4cout << G4endl << "###### Leaving QweakSimGeometryMessenger::QweakSimGeometryMessenger() " << G4endl << G4endl;
}

// ----------------------------------------------------------------------------

QweakSimGeometryMessenger::~QweakSimGeometryMessenger()
{
  G4cout << G4endl << "###### Calling QweakSimGeometryMessenger::~QweakSimGeometryMessenger() " << G4endl << G4endl;

  if (theReadCommand)     delete theReadCommand;
  if (theWriteCommand)    delete theWriteCommand;
  if (theDepthCommand)    delete theDepthCommand;
  if (theModuleCommand)   delete theModuleCommand;
  if (theGeometryDir)     delete theGeometryDir;

  G4cout << G4endl << "###### Leaving QweakSimGeometryMessenger::~QweakSimGeometryMessenger() " << G4endl << G4endl;
}

// ----------------------------------------------------------------------------

void QweakSimGeometryMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == theReadCommand)
  {
    theGeometry->SetReadFile(newValue);
//    theGeometry->Read();
  }
  if (command == theWriteCommand)
  {
    theGeometry->SetWriteFile(newValue);
    theGeometry->Write();
  }
  if (command == theDepthCommand)
  {
    theGeometry->SetWriteModuleDepth(theDepthCommand->GetNewIntValue(newValue));
  }
  if (command == theModuleCommand)
  {
    theGeometry->SetWriteModuleUser(theModuleCommand->GetNewBoolValue(newValue));
  }
}
