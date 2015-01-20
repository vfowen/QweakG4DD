//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimMagneticFieldMessenger.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:12:59 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:12:59 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimMagneticFieldMessenger.hh"

// user includes
#include "QweakSimMessengerDefinition.hh"
#include "QweakSimMagneticField.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimMagneticFieldMessenger::QweakSimMagneticFieldMessenger(QweakSimMagneticField* magneticfield)
  : fMagneticField(magneticfield)
{
  MagneticFieldDir = new G4UIdirectory("/MagneticField/");
  MagneticFieldDir->SetGuidance("Main Magnet control.");

  ReadCmd = new G4UIcmdWithAString("/MagneticField/ReadFieldMap",this);
  ReadCmd->SetGuidance("Read the specified magnetic field from file");
  ReadCmd->SetParameterName("file",true);
  ReadCmd->SetDefaultValue("MainMagnet_FieldMap.dat");
  ReadCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  PrintCmd = new G4UIcmdWith3VectorAndUnit("/MagneticField/PrintValue",this);
  PrintCmd->SetGuidance("Print the magnetic field value for specified position");
  PrintCmd->SetParameterName("x","y","z",false);
  PrintCmd->SetDefaultValue(G4ThreeVector(0.0,0.0,0.0));
  PrintCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  RefCurrentCmd = new G4UIcmdWithADouble("/MagneticField/SetReferenceCurrent",this);
  RefCurrentCmd->SetGuidance("Set reference current of read field map");
  RefCurrentCmd->SetParameterName("current",false);
  RefCurrentCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ActCurrentCmd = new G4UIcmdWithADouble("/MagneticField/SetActualCurrent",this);
  ActCurrentCmd->SetGuidance("Set actual current of the magnetic field for simulation");
  ActCurrentCmd->SetParameterName("current",false);
  ActCurrentCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ScaleCmd = new G4UIcmdWithADouble("/MagneticField/SetScale",this);
  ScaleCmd->SetGuidance("Set scale of the magnetic field for simulation");
  ScaleCmd->SetParameterName("bfil",false);
  ScaleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  RotationCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetRotation",this);
  RotationCmd->SetGuidance("Set rotation angle of the magnetic field to be read");
  RotationCmd->SetParameterName("rotation",false);
  RotationCmd->SetDefaultUnit("degree");
  RotationCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TranslationCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetTranslation",this);
  TranslationCmd->SetGuidance("Set translation angle of the magnetic field to be read");
  TranslationCmd->SetParameterName("translation",false);
  TranslationCmd->SetDefaultUnit("cm");
  TranslationCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  MinZCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetMinZ",this);
  MinZCmd->SetGuidance("Set the minimum z position of the field map grid to be read");
  MinZCmd->SetParameterName("min_r",false);
  MinZCmd->SetDefaultUnit("cm");
  MinZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  MaxZCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetMaxZ",this);
  MaxZCmd->SetGuidance("Set the maximum z position of the field map grid to be read");
  MaxZCmd->SetParameterName("max_r",false);
  MaxZCmd->SetDefaultUnit("cm");
  MaxZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  StepZCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetStepZ",this);
  StepZCmd->SetGuidance("Set the step z position of the field map grid to be read");
  StepZCmd->SetParameterName("step_r",false);
  StepZCmd->SetDefaultUnit("cm");
  StepZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  MinRCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetMinR",this);
  MinRCmd->SetGuidance("Set the minimum radius of the field map grid to be read");
  MinRCmd->SetParameterName("min_r",false);
  MinRCmd->SetDefaultUnit("cm");
  MinRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  MaxRCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetMaxR",this);
  MaxRCmd->SetGuidance("Set the maximum radius of the field map grid to be read");
  MaxRCmd->SetParameterName("max_r",false);
  MaxRCmd->SetDefaultUnit("cm");
  MaxRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  StepRCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetStepR",this);
  StepRCmd->SetGuidance("Set the step radius of the field map grid to be read");
  StepRCmd->SetParameterName("step_r",false);
  StepRCmd->SetDefaultUnit("cm");
  StepRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  MinPhiCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetMinPhi",this);
  MinPhiCmd->SetGuidance("Set the minimum phi of the field map grid to be read");
  MinPhiCmd->SetParameterName("min_phi",false);
  MinPhiCmd->SetDefaultUnit("degree");
  MinPhiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  MaxPhiCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetMaxPhi",this);
  MaxPhiCmd->SetGuidance("Set the maximum phi of the field map grid to be read");
  MaxPhiCmd->SetParameterName("max_phi",false);
  MaxPhiCmd->SetDefaultUnit("degree");
  MaxPhiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  StepPhiCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetStepPhi",this);
  StepPhiCmd->SetGuidance("Set the step phi of the field map grid to be read");
  StepPhiCmd->SetParameterName("step_phi",false);
  StepPhiCmd->SetDefaultUnit("degree");
  StepPhiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  WrapPhiCmd = new G4UIcmdWithAnInteger("/MagneticField/SetWrapPhi",this);
  WrapPhiCmd->SetGuidance("Set the wrap in phi of the field map grid to be read");
  WrapPhiCmd->SetParameterName("wrap_phi",false);
  WrapPhiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


  StepperCmd = new G4UIcmdWithAnInteger("/MagneticField/SetStepperType",this);
  StepperCmd->SetGuidance("Select stepper type for magnetic field");
  StepperCmd->SetParameterName("choice",true);
  StepperCmd->SetDefaultValue(4);
  StepperCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  MinStepCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetMinStep",this);
  MinStepCmd->SetGuidance("Define minimal step");
  MinStepCmd->SetParameterName("min step",false,false);
  MinStepCmd->SetDefaultUnit("mm");
  MinStepCmd->AvailableForStates(G4State_Idle);

  UpdateCmd = new G4UIcmdWithoutParameter("/MagneticField/Update",this);
  UpdateCmd->SetGuidance("Update Main Magnet geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimMagneticFieldMessenger::~QweakSimMagneticFieldMessenger()
{

  delete ScaleCmd;
  delete RefCurrentCmd;
  delete ActCurrentCmd;

  delete MinZCmd;
  delete MaxZCmd;
  delete StepZCmd;

  delete MinRCmd;
  delete MaxRCmd;
  delete StepRCmd;

  delete MinPhiCmd;
  delete MaxPhiCmd;
  delete StepPhiCmd;
  delete WrapPhiCmd;

  delete RotationCmd;
  delete TranslationCmd;

  delete StepperCmd;
  delete MinStepCmd;
  delete UpdateCmd;

  delete MagneticFieldDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimMagneticFieldMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if (command == ScaleCmd) {
    fMagneticField->SetScaleFactor(ScaleCmd->GetNewDoubleValue(newValue));
  } else if (command == ActCurrentCmd) {
    fMagneticField->SetActualCurrent(ScaleCmd->GetNewDoubleValue(newValue));
  } else if (command == RefCurrentCmd) {
    fMagneticField->SetReferenceCurrent(ScaleCmd->GetNewDoubleValue(newValue));
  } else if (command == MinZCmd) {
    fMagneticField->SetMinimum(MinZCmd->GetNewDoubleValue(newValue)/cm,0);
  } else if (command == MinRCmd) {
    fMagneticField->SetMinimum(MinRCmd->GetNewDoubleValue(newValue)/cm,1);
  } else if (command == MinPhiCmd) {
    fMagneticField->SetMinimum(MinPhiCmd->GetNewDoubleValue(newValue)/radian,2);
  } else if (command == MaxZCmd) {
    fMagneticField->SetMaximum(MaxZCmd->GetNewDoubleValue(newValue)/cm,0);
  } else if (command == MaxRCmd) {
    fMagneticField->SetMaximum(MaxRCmd->GetNewDoubleValue(newValue)/cm,1);
  } else if (command == MaxPhiCmd) {
    fMagneticField->SetMaximum(MaxPhiCmd->GetNewDoubleValue(newValue)/radian,2);
  } else if (command == StepZCmd) {
    fMagneticField->SetStep(StepZCmd->GetNewDoubleValue(newValue)/cm,0);
  } else if (command == StepRCmd) {
    fMagneticField->SetStep(StepRCmd->GetNewDoubleValue(newValue)/cm,1);
  } else if (command == StepPhiCmd) {
    fMagneticField->SetStep(StepPhiCmd->GetNewDoubleValue(newValue)/radian,2);
  } else if (command == WrapPhiCmd) {
    fMagneticField->SetWrap(WrapPhiCmd->GetNewIntValue(newValue),2);
  } else if (command == RotationCmd) {
    fMagneticField->SetRotation(RotationCmd->GetNewDoubleValue(newValue));
  } else if (command == TranslationCmd) {
    fMagneticField->SetTranslation(TranslationCmd->GetNewDoubleValue(newValue));
  } else if (command == PrintCmd) {
    G4ThreeVector vector = PrintCmd->GetNew3VectorValue(newValue);
    G4double point[4];
    point[0] = vector.x();
    point[1] = vector.y();
    point[2] = vector.z();
    point[3] = 0.0;
    fMagneticField->PrintFieldValue(point);
  } else if (command == ReadCmd) {
    fMagneticField->ReadFieldMap(newValue);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMagneticFieldMessenger.cc,v $
//      Revision 1.2  2005/12/27 19:12:59  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
