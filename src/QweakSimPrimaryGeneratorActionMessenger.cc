//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimPrimaryGeneratorActionMessenger.hh"

// user includes
#include "QweakSimPrimaryGeneratorAction.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPrimaryGeneratorActionMessenger::QweakSimPrimaryGeneratorActionMessenger(QweakSimPrimaryGeneratorAction* pPhys)
:pPrimaryGeneratorAction(pPhys)
{
  Xmin = 0.0;
  Xmax = 0.0;
  Ymin = 0.0;
  Ymax = 0.0;

  Dir = new G4UIdirectory("/PrimaryEvent/");
  Dir->SetGuidance("Primary event control");
 
  verboseCmd = new G4UIcmdWithAnInteger("/PrimaryEvent/verbose",this);  
  verboseCmd->SetGuidance("set verbose for primary generator");
  verboseCmd->SetParameterName("verbose",true);
  verboseCmd->SetDefaultValue(1);
  verboseCmd->SetRange("verbose>=0");
  verboseCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  SetParticleType_Cmd = new G4UIcmdWithAString("/PrimaryEvent/SetParticleType",this);
  SetParticleType_Cmd->SetGuidance("set particle type for primary generator");
  SetParticleType_Cmd->SetParameterName("type",true);
  SetParticleType_Cmd->SetDefaultValue("e-");
  SetParticleType_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetPolarization_Cmd = new G4UIcmdWithAString("/PrimaryEvent/SetPolarization",this);
  SetPolarization_Cmd->SetGuidance("set particle polarization for primary generator (L, H, V, mL, mH, mV, 0, f)");
  SetPolarization_Cmd->SetGuidance("if f then read the polarization values from a file");
  SetPolarization_Cmd->SetParameterName("polarization",true);
  SetPolarization_Cmd->SetDefaultValue("L");
  SetPolarization_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetFixedPosMom_Cmd = new G4UIcmdWithABool("/PrimaryEvent/SetFixedPosMom",this);
  SetFixedPosMom_Cmd->SetGuidance("Choise : true, false");
  SetFixedPosMom_Cmd->SetGuidance(" should events be generated from the same position and with the same momentum?");
  SetFixedPosMom_Cmd->SetGuidance(" true: sample from distributions from real data");
  SetFixedPosMom_Cmd->SetParameterName("fixedPosMom",true);
  SetFixedPosMom_Cmd->SetDefaultValue(true);

  SetPositionX_Cmd = new G4UIcmdWithADoubleAndUnit("/PrimaryEvent/SetBeamPositionX",this);
  SetPositionX_Cmd->SetGuidance("Set beam position in x");
  SetPositionX_Cmd->SetParameterName("x",true);
  SetPositionX_Cmd->SetUnitCategory("Length");
  SetPositionX_Cmd->SetDefaultValue(0.0*mm);
  SetPositionX_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetPositionY_Cmd = new G4UIcmdWithADoubleAndUnit("/PrimaryEvent/SetBeamPositionY",this);
  SetPositionY_Cmd->SetGuidance("Set beam position in y");
  SetPositionY_Cmd->SetParameterName("y",true);
  SetPositionY_Cmd->SetUnitCategory("Length");
  SetPositionY_Cmd->SetDefaultValue(0.0*mm);
  SetPositionY_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetPositionZ_Cmd = new G4UIcmdWithADoubleAndUnit("/PrimaryEvent/SetBeamPositionZ",this);
  SetPositionZ_Cmd->SetGuidance("Set beam position in z");
  SetPositionZ_Cmd->SetParameterName("z",true);
  SetPositionZ_Cmd->SetUnitCategory("Length");
  SetPositionZ_Cmd->SetDefaultValue(0.0*mm);
  SetPositionZ_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetDirectionX_Cmd = new G4UIcmdWithADoubleAndUnit("/PrimaryEvent/SetBeamDirectionX",this);
  SetDirectionX_Cmd->SetGuidance("Set beam direction in x");
  SetDirectionX_Cmd->SetParameterName("x",true);
  SetDirectionX_Cmd->SetUnitCategory("Angle");
  SetDirectionX_Cmd->SetDefaultValue(0.0*mrad);
  SetDirectionX_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetDirectionY_Cmd = new G4UIcmdWithADoubleAndUnit("/PrimaryEvent/SetBeamDirectionY",this);
  SetDirectionY_Cmd->SetGuidance("Set beam direction in y");
  SetDirectionY_Cmd->SetParameterName("y",true);
  SetDirectionY_Cmd->SetUnitCategory("Angle");
  SetDirectionY_Cmd->SetDefaultValue(0.0*mrad);
  SetDirectionY_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetRasterXmin_Cmd = new G4UIcmdWithADoubleAndUnit("/PrimaryEvent/SetRasterXmin",this);
  SetRasterXmin_Cmd->SetGuidance("Set beam rastering region (x min.)");
  SetRasterXmin_Cmd->SetParameterName("Xmin",true);
  SetRasterXmin_Cmd->SetUnitCategory("Length");
  SetRasterXmin_Cmd->SetDefaultValue(-2.0*mm);
  //SetRasterXmin_Cmd->SetRange("Xmin>=-10");
  SetRasterXmin_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetRasterXmax_Cmd = new G4UIcmdWithADoubleAndUnit("/PrimaryEvent/SetRasterXmax",this);
  SetRasterXmax_Cmd->SetGuidance("Set beam rastering region (x max.)");
  SetRasterXmax_Cmd->SetParameterName("Xmax",true);
  SetRasterXmax_Cmd->SetUnitCategory("Length");
  SetRasterXmax_Cmd->SetDefaultValue(2.0*mm);
  //SetRasterXmax_Cmd->SetRange("Xmax<=10");
  SetRasterXmax_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  SetRasterYmin_Cmd = new G4UIcmdWithADoubleAndUnit("/PrimaryEvent/SetRasterYmin",this);
  SetRasterYmin_Cmd->SetGuidance("Set beam rastering region (y min.)");
  SetRasterYmin_Cmd->SetParameterName("Ymin",true);
  SetRasterYmin_Cmd->SetUnitCategory("Length");
  SetRasterYmin_Cmd->SetDefaultValue(-2.0*mm);
  //SetRasterYmin_Cmd->SetRange("Ymin>=-10");
  SetRasterYmin_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  SetRasterYmax_Cmd = new G4UIcmdWithADoubleAndUnit("/PrimaryEvent/SetRasterYmax",this);
  SetRasterYmax_Cmd->SetGuidance("Set beam rastering region (y max.)");
  SetRasterYmax_Cmd->SetParameterName("Ymax",true);
  SetRasterYmax_Cmd->SetUnitCategory("Length");
  SetRasterYmax_Cmd->SetDefaultValue(2.0*mm);
  //SetRasterYmax_Cmd->SetRange("Ymax<10");
  SetRasterYmax_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPrimaryGeneratorActionMessenger::~QweakSimPrimaryGeneratorActionMessenger()
{
  delete SetRasterXmin_Cmd;
  delete SetRasterXmax_Cmd;
  delete SetRasterYmin_Cmd;
  delete SetRasterYmax_Cmd;
  delete SetPolarization_Cmd;
  delete verboseCmd;
  delete Dir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{       
  //if( command == verboseCmd )
    //{ pPrimaryGeneratorAction->SetVerbose(verboseCmd->GetNewIntValue(newValue));}
   
  if( command == SetParticleType_Cmd )
    { pPrimaryGeneratorAction->SetParticleType(newValue); }

  if( command == SetPolarization_Cmd )
    {
      G4cout << "#### Messenger: Polarization set to: " << newValue << G4endl;
      pPrimaryGeneratorAction->SetPolarization(newValue);
      if(newValue=="f"){
	pPrimaryGeneratorAction->GetUserInfo()->ReadInitialPolarization();
      }
    }

  if( command == SetFixedPosMom_Cmd )
    {
      G4cout << "#### Messenger: Fixed beam position: " << newValue << G4endl;
      G4bool fixed = SetFixedPosMom_Cmd->GetNewBoolValue(newValue);
      pPrimaryGeneratorAction->GetUserInfo()->SetFixedPosMom(fixed);
      if(!fixed)
	pPrimaryGeneratorAction->GetUserInfo()->ReadInitialPositionMomentum();
    }
  if( command == SetPositionX_Cmd )
    {
      G4cout << "#### Messenger: Setting Beam Position in X to " << newValue << G4endl;
      G4double x = SetPositionX_Cmd->GetNewDoubleValue(newValue);
      pPrimaryGeneratorAction->GetUserInfo()->SetBeamPositionX(x);
    }
  if( command == SetPositionY_Cmd )
    {
      G4cout << "#### Messenger: Setting Beam Position in Y to " << newValue << G4endl;
      G4double y = SetPositionY_Cmd->GetNewDoubleValue(newValue);
      pPrimaryGeneratorAction->GetUserInfo()->SetBeamPositionY(y);
    }
  if( command == SetPositionZ_Cmd )
    {
      G4cout << "#### Messenger: Setting Beam Position in Z to " << newValue << G4endl;
      G4double z = SetPositionZ_Cmd->GetNewDoubleValue(newValue);
      pPrimaryGeneratorAction->GetUserInfo()->SetBeamPositionZ(z);
    }
  if( command == SetDirectionX_Cmd )
    {
      G4cout << "#### Messenger: Setting Beam Direction in X to " << newValue << G4endl;
      G4double x = SetPositionX_Cmd->GetNewDoubleValue(newValue);
      pPrimaryGeneratorAction->GetUserInfo()->SetBeamDirectionX(x);
    }
  if( command == SetDirectionY_Cmd )
    {
      G4cout << "#### Messenger: Setting Beam Direction in Y to " << newValue << G4endl;
      G4double y = SetPositionX_Cmd->GetNewDoubleValue(newValue);
      pPrimaryGeneratorAction->GetUserInfo()->SetBeamDirectionY(y);
    }


  if( command == SetRasterXmin_Cmd )
    { 
      G4cout << "#### Messenger: Setting Raster min. X to " << newValue << G4endl;
      Xmin = SetRasterXmin_Cmd->GetNewDoubleValue(newValue);
      pPrimaryGeneratorAction->SetBeamRasteringRegion(Xmin, Xmax, Ymin, Ymax); 
    }
  if( command == SetRasterXmax_Cmd )
    { 
      G4cout << "#### Messenger: Setting Raster max. X to " << newValue << G4endl;
      Xmax = SetRasterXmax_Cmd->GetNewDoubleValue(newValue);
      pPrimaryGeneratorAction->SetBeamRasteringRegion(Xmin, Xmax, Ymin, Ymax); 
    }
  if( command == SetRasterYmin_Cmd )
    { 
      G4cout << "#### Messenger: Setting Raster min. Y to " << newValue << G4endl;
      Ymin = SetRasterYmin_Cmd->GetNewDoubleValue(newValue);
      pPrimaryGeneratorAction->SetBeamRasteringRegion(Xmin, Xmax, Ymin, Ymax); 
    }
  if( command == SetRasterYmax_Cmd )
    { 
      G4cout << "#### Messenger: Setting Raster max. Y to " << newValue << G4endl;
      Ymax = SetRasterYmax_Cmd->GetNewDoubleValue(newValue);
      pPrimaryGeneratorAction->SetBeamRasteringRegion(Xmin, Xmax, Ymin, Ymax); 
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

