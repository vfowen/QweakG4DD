//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimCerenkovDetectorMessenger.hh"

// user includes
#include "QweakSimCerenkovDetector.hh"
#include "QweakSimMessengerDefinition.hh"
#include <iostream>

// static variables
G4UIdirectory*             QweakSimCerenkovDetectorMessenger::Dir = 0;
G4UIcmdWithAnInteger*      QweakSimCerenkovDetectorMessenger::NumberOfDetectorsCmd = 0;
G4UIcmdWithAString*        QweakSimCerenkovDetectorMessenger::ContainerMatCmd = 0;
G4UIcmdWithAString*        QweakSimCerenkovDetectorMessenger::DetectorMatCmd = 0;
G4UIcmdWithAString*        QweakSimCerenkovDetectorMessenger::PreRadiatorMatCmd = 0;
G4UIcmdWithADoubleAndUnit* QweakSimCerenkovDetectorMessenger::ContainerThicknessCmd = 0;
G4UIcmdWithADoubleAndUnit* QweakSimCerenkovDetectorMessenger::TiltingAngleCmd = 0;
G4UIcmdWithADoubleAndUnit* QweakSimCerenkovDetectorMessenger::KinkAngleCmd = 0;
G4UIcmdWithADoubleAndUnit* QweakSimCerenkovDetectorMessenger::SetPbStepSizeCmd = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkovDetectorMessenger::QweakSimCerenkovDetectorMessenger(QweakSimCerenkovDetector* theCerenkovDetector, G4int octant)
:myCerenkovDetector(theCerenkovDetector),fOctant(octant)
{
  G4String Dir_name = "/Cerenkov";
  if (Dir == 0) {
    Dir = new  G4UIdirectory(Dir_name);
    Dir -> SetGuidance("Cerenkov Detector control.");
  }

  if (NumberOfDetectorsCmd == 0) {
    NumberOfDetectorsCmd = new G4UIcmdWithAnInteger(G4String(Dir_name + "/SetNumberOfDetectors"),this);
    NumberOfDetectorsCmd->SetGuidance("Set the number of detectors");
    NumberOfDetectorsCmd->SetParameterName("n",false);
    NumberOfDetectorsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  if (ContainerThicknessCmd == 0) {
    ContainerThicknessCmd =  new G4UIcmdWithADoubleAndUnit(G4String(Dir_name + "/SetThickness"),this);
    ContainerThicknessCmd->SetGuidance("Set the thickness (length in Z) of the Cherenkov container");
    ContainerThicknessCmd->SetParameterName("Size",true);
    ContainerThicknessCmd->SetUnitCategory("Length");
    ContainerThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  if (TiltingAngleCmd == 0) {
    TiltingAngleCmd =  new G4UIcmdWithADoubleAndUnit(G4String(Dir_name + "/SetTiltingAngle"),this);
    TiltingAngleCmd->SetGuidance("Set the tilting angle of the Cerenkov Detector");
    TiltingAngleCmd->SetParameterName("Angle",true);
    TiltingAngleCmd->SetDefaultUnit("degree");
    TiltingAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  if (KinkAngleCmd == 0) {
    KinkAngleCmd =  new G4UIcmdWithADoubleAndUnit(G4String(Dir_name + "/SetKinkAngle"),this);
    KinkAngleCmd->SetGuidance("Set the kink angle for the V-shape ");
    KinkAngleCmd->SetParameterName("Angle",true);
    KinkAngleCmd->SetDefaultUnit("degree");
    KinkAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  if (ContainerMatCmd == 0) {
    ContainerMatCmd = new G4UIcmdWithAString(G4String(Dir_name + "/SetContainerMaterial"),this);
    ContainerMatCmd->SetGuidance("Select Material of the Cerenkov Container.");
    ContainerMatCmd->SetParameterName("choice",false);
    ContainerMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  if (DetectorMatCmd == 0) {
    DetectorMatCmd = new G4UIcmdWithAString(G4String(Dir_name + "/SetCerenkovMaterial"),this);
    DetectorMatCmd->SetGuidance("Select Material of the Cerenkov Detector.");
    DetectorMatCmd->SetParameterName("choice",false);
    DetectorMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  if (PreRadiatorMatCmd == 0) {
    PreRadiatorMatCmd = new G4UIcmdWithAString(G4String(Dir_name + "/SetPreradiatorMaterial"),this);
    PreRadiatorMatCmd->SetGuidance("Select Material of the Pre-radiator.");
    PreRadiatorMatCmd->SetParameterName("choice",false);
    PreRadiatorMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  if (SetPbStepSizeCmd == 0) {
    SetPbStepSizeCmd =  new G4UIcmdWithADoubleAndUnit(G4String(Dir_name + "/SetPbStepSize"),this);
    SetPbStepSizeCmd->SetGuidance("Set max step size in the Pb preradiator ");
    SetPbStepSizeCmd->SetParameterName("StepLength",true);
    SetPbStepSizeCmd->SetDefaultUnit("mm");
    SetPbStepSizeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  
  G4String DirPerOctant_name = "/Cerenkov/Cerenkov" + G4UIcommand::ConvertToString(octant+1);
  DirPerOctant = new  G4UIdirectory(G4String(DirPerOctant_name + "/"));
  DirPerOctant -> SetGuidance("Individual Cerenkov detector control.");

  ContainerZPositionCmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerOctant_name + "/SetCenterPositionInZ"),this);
  ContainerZPositionCmd->SetGuidance("Set the Z position of the Cerenkov container center");
  ContainerZPositionCmd->SetParameterName("Size",true);
  ContainerZPositionCmd->SetUnitCategory("Length");
  ContainerZPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ContainerYPositionCmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerOctant_name + "/SetCenterPositionInY"),this);
  ContainerYPositionCmd->SetGuidance("Set the Y position of the Cerenkov container center");
  ContainerYPositionCmd->SetParameterName("Size",true);
  ContainerYPositionCmd->SetUnitCategory("Length");
  ContainerYPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ContainerXPositionCmd =  new G4UIcmdWithADoubleAndUnit(G4String(DirPerOctant_name + "/SetCenterPositionInX"),this);
  ContainerXPositionCmd->SetGuidance("Set the X position of the Cerenkov container center");
  ContainerXPositionCmd->SetParameterName("Size",true);
  ContainerXPositionCmd->SetUnitCategory("Length");
  ContainerXPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimCerenkovDetectorMessenger::~QweakSimCerenkovDetectorMessenger()
{
  if (ContainerXPositionCmd)      delete ContainerXPositionCmd;
  if (ContainerYPositionCmd)      delete ContainerYPositionCmd;
  if (ContainerZPositionCmd)      delete ContainerZPositionCmd;
  if (DirPerOctant)               delete DirPerOctant;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimCerenkovDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimCerenkovDetectorMessenger::SetNewValue() " << command->GetCommandName()
	 <<" "<<newValue << G4endl;
   
  if( command == NumberOfDetectorsCmd ){
    G4cout << "#### Messenger: Setting Number of Detectors to " << newValue << G4endl;
    myCerenkovDetector->SetNumberOfDetectors(NumberOfDetectorsCmd->GetNewIntValue(newValue));
  }else  if( command == ContainerThicknessCmd ){
    G4cout << "#### Messenger: Setting CerenkovDetector Container Thickness to " << newValue << G4endl;
    myCerenkovDetector->SetCerenkovDetectorThickness(ContainerThicknessCmd->GetNewDoubleValue(newValue));
  }else if( command == ContainerXPositionCmd ){
    G4cout << "#### Messenger: Setting CerenkovDetector Container X position to " << newValue <<" for octant "<<fOctant << G4endl;     
    myCerenkovDetector->SetCerenkovDetectorCenterPositionInX(ContainerXPositionCmd->GetNewDoubleValue(newValue), fOctant);
  }else if( command == ContainerYPositionCmd ){
    G4cout << "#### Messenger: Setting CerenkovDetector Container Y position to " << newValue <<" for octant "<<fOctant << G4endl;    
    myCerenkovDetector->SetCerenkovDetectorCenterPositionInY(ContainerYPositionCmd->GetNewDoubleValue(newValue), fOctant);
  }else if( command == ContainerZPositionCmd ){
    G4cout << "#### Messenger: Setting CerenkovDetector Container Z position to " << newValue <<" for octant "<<fOctant << G4endl;    
    myCerenkovDetector->SetCerenkovDetectorCenterPositionInZ(ContainerZPositionCmd->GetNewDoubleValue(newValue), fOctant);
  }else if( command == ContainerMatCmd ){ 
    G4cout << "#### Messenger: Setting CerenkovDetector Container Material to " << newValue << G4endl;    
    myCerenkovDetector->SetContainerMaterial(newValue);
  }else if( command == DetectorMatCmd ){ 
    G4cout << "#### Messenger: Setting Cerenkov Detector Material to " << newValue << G4endl;    
    myCerenkovDetector->SetCerenkovDetectorMaterial(newValue);
  }else if( command == PreRadiatorMatCmd ){ 
    G4cout << "#### Messenger: Setting PreRadiator Material to " << newValue << G4endl;    
    myCerenkovDetector->SetPreradiatorMaterial(newValue);
  }else if( command == TiltingAngleCmd ){ 
    G4cout << "#### Messenger: Setting Cerenkov Detector Tilting Angle to " << newValue << G4endl;
    myCerenkovDetector->SetCerenkovDetectorTiltAngle(TiltingAngleCmd->GetNewDoubleValue(newValue));
  }else if( command == KinkAngleCmd ){ 
    G4cout << "#### Messenger: Setting Cerenkov Detector Kink Angle to " << newValue << G4endl;
    // myCerenkovDetector->SetKinkAngle(newValue);
  }else if( command == SetPbStepSizeCmd ){
    G4cout << "!!~~ Messenger: Setting Pb preRadiator Step size to " << newValue << G4endl;
    myCerenkovDetector->SetCerenkovDetectorPbStepSize(SetPbStepSizeCmd->GetNewDoubleValue(newValue));
    std::cin.ignore();
  }else{
    G4cout<< G4endl << G4endl << __PRETTY_FUNCTION__ << G4endl
	  << " Error!!! Command not known. Value: "<<newValue<<G4endl;
    exit(1);      
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
