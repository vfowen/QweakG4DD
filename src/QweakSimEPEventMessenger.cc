//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimEPEventMessenger.cc

   \author Peiqing Wang

*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimEPEventMessenger.hh"

// user includes
#include "QweakSimEPEvent.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimEPEventMessenger::QweakSimEPEventMessenger(QweakSimEPEvent* pEPEvent)
:pQweakSimEPEvent(pEPEvent)
{
  G4cout << "###### Calling QweakSimEPEventMessenger::QweakSimEPEventMessenger() " << G4endl;

  EventGenDir = new G4UIdirectory("/EventGen/");
  EventGenDir->SetGuidance("Event generator control");
 
  verboseCmd = new G4UIcmdWithAnInteger("/EventGen/verbose",this);  
  verboseCmd->SetGuidance("set verbose for event generator");
  verboseCmd->SetParameterName("verbose",true);
  verboseCmd->SetDefaultValue(1);
  verboseCmd->SetRange("verbose>=0");
  verboseCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SelectOctant_Cmd = new G4UIcmdWithAnInteger("/EventGen/SelectOctant",this);
  SelectOctant_Cmd->SetGuidance("Select octant for primaries (zero for all)");
  SelectOctant_Cmd->SetParameterName("SelectOctant",true);
  SelectOctant_Cmd->SetDefaultValue(0);
  SelectOctant_Cmd->SetRange("SelectOctant>=0 && SelectOctant<=12");
  SelectOctant_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

// Isotropy:     0 - uniform phi angle and uniform theta angle, independent to each other
//               1 - uniform in any solid angle (i.e. uniform phi, but phi-denendent theta)
  SelectIsotropy_Cmd = new G4UIcmdWithAnInteger("/EventGen/SelectIsotropy",this);
  SelectIsotropy_Cmd->SetGuidance("Select isotropy for generator");
  SelectIsotropy_Cmd->SetParameterName("SelectIsotropy",true);
  SelectIsotropy_Cmd->SetDefaultValue(1);
  SelectIsotropy_Cmd->SetRange("SelectIsotropy>=0 && SelectIsotropy<=1");
  SelectIsotropy_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
//    ReactionType:            1 - LH2 elastic
//                             2 - Al window elastic
//                             3 - Al window quasi-elastic proton
//                             4 - Al window quasi-elastic neutron
//
//    ReactionRegion:          1 - LH2 target
//                             2 - entrance window
//                             3 - exit window

  SelectReactionType_Cmd = new G4UIcmdWithAnInteger("/EventGen/SelectReactionType",this);
  SelectReactionType_Cmd->SetGuidance("Select reaction type");
  SelectReactionType_Cmd->SetGuidance("0 - Combination of all reactions");
  SelectReactionType_Cmd->SetGuidance("1 - LH2 elastic (default)");
  SelectReactionType_Cmd->SetGuidance("2 - Al elastic");
  SelectReactionType_Cmd->SetGuidance("3 - Al quasi-elastic (proton)");
  SelectReactionType_Cmd->SetGuidance("4 - Al quasi-elastic (neutron)");
  SelectReactionType_Cmd->SetGuidance("5 - LH2 inelastic (delta resonance)");
  SelectReactionType_Cmd->SetGuidance("6 - Moller scattering");
  SelectReactionType_Cmd->SetGuidance("7 - LH2 radiative lookup table (3.35 GeV)");
  SelectReactionType_Cmd->SetGuidance("8 - Al quasi-elastic (Bosted)");
	
  SelectReactionType_Cmd->SetGuidance("88 - LH2 pion photo-production (3.35 GeV)");

  SelectReactionType_Cmd->SetParameterName("SelectReactionType",true);
  SelectReactionType_Cmd->SetDefaultValue(1);
  SelectReactionType_Cmd->SetRange("SelectReactionType>=0");
  SelectReactionType_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SelectReactionRegion_Cmd = new G4UIcmdWithAnInteger("/EventGen/SelectReactionRegion",this);
  SelectReactionRegion_Cmd->SetGuidance("Select reaction region");
  SelectReactionRegion_Cmd->SetGuidance("1 - target (default)");
  SelectReactionRegion_Cmd->SetGuidance("2 - entrance target window");
  SelectReactionRegion_Cmd->SetGuidance("3 - exit target window");
  SelectReactionRegion_Cmd->SetParameterName("SelectReactionRegion",true);
  SelectReactionRegion_Cmd->SetDefaultValue(1);
  SelectReactionRegion_Cmd->SetRange("SelectReactionRegion>=1");
  SelectReactionRegion_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  ThetaMinLimitCmd =  new G4UIcmdWithADoubleAndUnit("/EventGen/SetThetaMin",this);
  ThetaMinLimitCmd->SetGuidance("Set the minimum theta angle of event generator"); 
  ThetaMinLimitCmd->SetParameterName("ThetaMin",true);
  ThetaMinLimitCmd->SetUnitCategory("Angle");
  ThetaMinLimitCmd->SetDefaultUnit("degree");
  ThetaMinLimitCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ThetaMaxLimitCmd =  new G4UIcmdWithADoubleAndUnit("/EventGen/SetThetaMax",this);
  ThetaMaxLimitCmd->SetGuidance("Set the maximum theta angle of event generator"); 
  ThetaMaxLimitCmd->SetParameterName("ThetaMax",true);
  ThetaMaxLimitCmd->SetUnitCategory("Angle");
  ThetaMaxLimitCmd->SetDefaultUnit("degree");
  ThetaMaxLimitCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  PhiMinLimitCmd =  new G4UIcmdWithADoubleAndUnit("/EventGen/SetPhiMin",this);
  PhiMinLimitCmd->SetGuidance("Set the minimum theta angle of event generator"); 
  PhiMinLimitCmd->SetParameterName("PhiMin",true);
  PhiMinLimitCmd->SetUnitCategory("Angle");
  PhiMinLimitCmd->SetDefaultUnit("degree");
  PhiMinLimitCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  PhiMaxLimitCmd =  new G4UIcmdWithADoubleAndUnit("/EventGen/SetPhiMax",this);
  PhiMaxLimitCmd->SetGuidance("Set the maximum theta angle of event generator"); 
  PhiMaxLimitCmd->SetParameterName("PhiMax",true);
  PhiMaxLimitCmd->SetUnitCategory("Angle");
  PhiMaxLimitCmd->SetDefaultUnit("degree");
  PhiMaxLimitCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  EPrimeMinLimitCmd =  new G4UIcmdWithADoubleAndUnit("/EventGen/SetEPrimeMin",this);
  EPrimeMinLimitCmd->SetGuidance("Set the minimum E\' of event generator"); 
  EPrimeMinLimitCmd->SetParameterName("EPrimeMin",true);
  EPrimeMinLimitCmd->SetUnitCategory("Energy");
  EPrimeMinLimitCmd->SetDefaultUnit("GeV");
  EPrimeMinLimitCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  EPrimeMaxLimitCmd =  new G4UIcmdWithADoubleAndUnit("/EventGen/SetEPrimeMax",this);
  EPrimeMaxLimitCmd->SetGuidance("Set the maximum E\' of event generator"); 
  EPrimeMaxLimitCmd->SetParameterName("EPrimeMax",true);
  EPrimeMaxLimitCmd->SetUnitCategory("Energy");
  EPrimeMaxLimitCmd->SetDefaultUnit("GeV");
  EPrimeMaxLimitCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetBeamEnergyCmd = new G4UIcmdWithADoubleAndUnit("/EventGen/SetBeamEnergy",this);
  SetBeamEnergyCmd->SetGuidance("Set beam energy.");
  SetBeamEnergyCmd->SetParameterName("E_beam",true);
  SetBeamEnergyCmd->SetUnitCategory("Energy");
  SetBeamEnergyCmd->SetDefaultValue(1.160*GeV);
  //SetBeamEnergyCmd->SetRange("BeamEnergy>0");
  SetBeamEnergyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SetElasticPeakDeltaECmd = new G4UIcmdWithADoubleAndUnit("/EventGen/SetElasticPeakDeltaE",this);
  SetElasticPeakDeltaECmd->SetGuidance("Set elastic peak delta E range (Used in ReactionType 7).");
  SetElasticPeakDeltaECmd->SetParameterName("delta_E",true);
  SetElasticPeakDeltaECmd->SetUnitCategory("Energy");
  SetElasticPeakDeltaECmd->SetDefaultValue(15*MeV);
  SetElasticPeakDeltaECmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  G4cout << "###### Leaving QweakSimEPEventMessenger::QweakSimEPEventMessenger() " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimEPEventMessenger::~QweakSimEPEventMessenger()
{
  G4cout << "###### Calling QweakSimEPEventMessenger::~QweakSimEPEventMessenger() " << G4endl;

  delete SelectOctant_Cmd;
  delete SelectIsotropy_Cmd;
  delete SelectReactionType_Cmd;
  delete SelectReactionRegion_Cmd;
  delete verboseCmd;
  delete ThetaMinLimitCmd;
  delete ThetaMaxLimitCmd;
  delete PhiMinLimitCmd;
  delete PhiMaxLimitCmd;
  delete EPrimeMinLimitCmd;
  delete EPrimeMaxLimitCmd;
  delete SetBeamEnergyCmd;
  delete SetElasticPeakDeltaECmd;
  delete EventGenDir;

  G4cout << "###### Leaving QweakSimEPEventMessenger::~QweakSimEPEventMessenger() " << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimEPEventMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{

  if( command == SelectOctant_Cmd )
    { 
      G4cout << "% % ===> Changing active octant number to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetActiveOctantNumber(SelectOctant_Cmd->GetNewIntValue(newValue)); 
    }
  if( command == SelectIsotropy_Cmd )
    { 
      G4cout << "% % ===> Changing isotropy to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetIsotropy(SelectIsotropy_Cmd->GetNewIntValue(newValue)); 
    }
  if( command == SelectReactionType_Cmd )
    { 
      G4cout << "% % ===> Changing reaction type to: "<<newValue<< G4endl;
      G4int type = SelectReactionType_Cmd->GetNewIntValue(newValue); 
      pQweakSimEPEvent->SetReactionType(type);
      if (type == 7) pQweakSimEPEvent->CreateLookupTable(); 
    }

  if( command == SelectReactionRegion_Cmd )
    { 
      G4cout << "% % ===> Changing reaction region to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetReactionRegion(SelectReactionRegion_Cmd->GetNewIntValue(newValue)); 
    }
    
  if( command == ThetaMinLimitCmd )
    { 
      G4cout << "% % ===> Changing theta minimum to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetThetaAngle_Min(ThetaMinLimitCmd->GetNewDoubleValue(newValue)); 
    }

  if( command == ThetaMaxLimitCmd )
    { 
      G4cout << "% % ===> Changing theta maximum to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetThetaAngle_Max(ThetaMaxLimitCmd->GetNewDoubleValue(newValue)); 
    }

  if( command == PhiMinLimitCmd )
    { 
      G4cout << "% % ===> Changing phi minimum to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetPhiAngle_Min(PhiMinLimitCmd->GetNewDoubleValue(newValue)); 
    }

  if( command == PhiMaxLimitCmd )
    { 
      G4cout << "% % ===> Changing phi maximum to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetPhiAngle_Max(PhiMaxLimitCmd->GetNewDoubleValue(newValue)); 
    }

  if( command == EPrimeMinLimitCmd )
    { 
      G4cout << "% % ===> Changing E\' minimum to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetEPrime_Min(EPrimeMinLimitCmd->GetNewDoubleValue(newValue)); 
    }

  if( command == EPrimeMaxLimitCmd )
    { 
      G4cout << "% % ===> Changing E\' maximum to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetEPrime_Max(EPrimeMaxLimitCmd->GetNewDoubleValue(newValue)); 
    }

  if( command == SetBeamEnergyCmd )
    { 
      G4cout << "% % ===> Changing Beam Energy to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetBeamEnergy(SetBeamEnergyCmd->GetNewDoubleValue(newValue)); 
    }

  if( command == SetElasticPeakDeltaECmd )
    { 
      G4cout << "% % ===> Changing Elastic Peak Energy Range to: "<<newValue<< G4endl;
      pQweakSimEPEvent->SetElasticPeakDeltaE(SetElasticPeakDeltaECmd->GetNewDoubleValue(newValue)); 
    }

}
