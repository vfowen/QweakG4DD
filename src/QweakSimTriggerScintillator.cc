//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimTriggerScintillator.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:15:51 $

   \author Klaus Hans Grimm   

*/
//=============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimTriggerScintillator.hh"

// geant4 includes
#include "G4RunManager.hh"

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimTriggerScintillatorMessenger.hh"
#include "QweakSimTriggerScintillator_DetectorSD.hh"
#include "QweakSimTriggerScintillator_PMTSD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimTriggerScintillator::QweakSimTriggerScintillator()
{	    	    
  // initialize some pointers
  TriggerScintillatorMessenger = NULL;
  pMaterial                 = NULL;
  
  TriggerScintillatorContainer_Logical  = NULL;
 // TriggerScintillatorContainer_Physical = NULL;
  TriggerScintillatorContainer_Physical.resize(2,0);
  TriggerScintillatorContainer_Material = NULL;
  
  TriggerScintillator_Logical   = NULL;
  TriggerScintillator_Physical  = NULL;
  TriggerScintillator_Material  = NULL;
  
  
  //Rotation_TriggerScintillatorContainer = NULL;
  
  // pointer to the sensitive detector
  TriggerScintillatorSD      = NULL;
    
   
  TriggerScintillatorMessenger = new QweakSimTriggerScintillatorMessenger(this); //Messenger for first TS Control
  TriggerScintillatorMessenger = new QweakSimTriggerScintillatorMessenger(this,1); // Messenger for second TS Control
  
  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();

  // get cerenkov material
  //CerenkovContainer_Material = pMaterial->GetMaterial("HeGas");  

  TriggerScintillatorContainer_Material = pMaterial->GetMaterial("Air");  
  TriggerScintillator_Material          = pMaterial->GetMaterial("Scintillator");  
   
  // define container values
  Container_FullLength_X = 220.0*cm;     // Full X length 
  Container_FullLength_Y =  60.0*cm;     // Full Y length 
  Container_FullLength_Z =   1.27*cm;     // Full Z length , just a bit thicker to get an air gap

 // define container values
  StraightBar_FullLength    =  210.00*cm;    // Full X length 
  StraightBar_FullHeight    =   58.00*cm;    // Full Y length 
  StraightBar_FullThickness =    1.00*cm;    // Full Z length 

   // tilting angle of V-shaped TriggerScintillator against the vertical plane    
  Tilting_Angle   =  0.0*degree;
  
  //Phi angle of TriggerScintillator of Package 1
  Phi_Angle	= 0.0*degree;

  Position_TriggerScintillatorContainer_X.resize(2,0);
  Position_TriggerScintillatorContainer_Y.resize(2,0);
  Position_TriggerScintillatorContainer_Z.resize(2,0);
  Rotation_TriggerScintillatorContainer.resize(2,0);
  for (size_t i=0; i< Position_TriggerScintillatorContainer_Z.size();i++)
  {
  // define center position of Container in MotherVolume
  Position_TriggerScintillatorContainer_X[i] =   0.0*cm;

//jpan@nuclear.uwinnipeg.ca
  //Position_TriggerScintillatorContainer_Y = 319.0*cm;
  Position_TriggerScintillatorContainer_Y[i] = 328.0*cm;

//jpan@nuclear.uwinnipeg.ca
  //Position_TriggerScintillatorContainer_Z = 555.0*cm; // adjusted by Jie
  Position_TriggerScintillatorContainer_Z[i] = 545.0*cm; // adjusted by Jie
  
  // define Rotation matrix for Container orientated in MotherVolume
  Rotation_TriggerScintillatorContainer[i] = new G4RotationMatrix();

  }
  
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTriggerScintillator::~QweakSimTriggerScintillator()
{

//    if (Rotation_TriggerScintillatorContainer)    delete Rotation_TriggerScintillatorContainer;

    if (TriggerScintillator_Physical)             delete TriggerScintillator_Physical;
    if (TriggerScintillator_Logical)              delete TriggerScintillator_Logical;

  //  if (TriggerScintillatorContainer_Physical)    delete TriggerScintillatorContainer_Physical;
    if (TriggerScintillatorContainer_Logical)     delete TriggerScintillatorContainer_Logical;


    if (pMaterial)                                delete pMaterial;
    if (TriggerScintillatorMessenger)             delete TriggerScintillatorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator::DefineTriggerScintillatorGeometry()
{
  G4cout << G4endl << "###### Calling QweakSimTriggerScintillator::DefineTriggerScintillatorGeometry() " << G4endl << G4endl;
  G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator::DefineTriggerScintillatorGeometry() " << G4endl << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
  G4cout << G4endl << "###### Calling QweakSimTriggerScintillator::ConstructComponent() " << G4endl << G4endl;
  theMotherPV = MotherVolume; //Saving pointer to the MotherVolume
  //-----------------------------------------------------------
  // location and orientation of the TriggerScintillator Container
  //-----------------------------------------------------------
  
  // I prefere to tilt the Detector inside its container rather than
  // tilting the container. Why? I don't know what to do if
  // I want to place 8 containers, each tilted by Tilting_Angle,
  // but to which axis then ?!
 // Rotation_TriggerScintillatorContainer->rotateX(Tilting_Angle);
  
  
  // define Container for the V shape Scintillator Detector
  G4cout << G4endl << "###### QweakSimTriggerScintillator: Define TriggerScintillatorContainer_Solid " << G4endl << G4endl;
  
  G4Box* TriggerScintillatorContainer_Solid  = new G4Box("TriggerScintillatorContainer_Solid",
					      0.5 * Container_FullLength_X ,    // half X length required by Geant4
					      0.5 * Container_FullLength_Y ,    // half Y length required by Geant4
					      0.5 * Container_FullLength_Z );   // half Z length required by Geant4
 
  // define Container logical volume
  G4cout << G4endl << "###### QweakSimTriggerScintillator: Define TriggerScintillatorContainer_Logical " << G4endl << G4endl;
  
  TriggerScintillatorContainer_Logical  = new G4LogicalVolume(TriggerScintillatorContainer_Solid,
							      TriggerScintillatorContainer_Material,
							      "TriggerScintillatorContainer_Logical",
							      0,0,0);


  // define ScintillatorContainer physical volume
  PlaceTriggerScintillator_MasterContainers();

  G4Box* StraightBar_Solid    = new G4Box("StraightBar_Sol",
					  0.5 * StraightBar_FullLength,       // half X length required by Geant4
					  0.5 * StraightBar_FullHeight,      // half Y length required by Geant4
					  0.5 * StraightBar_FullThickness );  // half Z length required by Geant4 


// Testing: use unly straight bar (w/o chambers)
 TriggerScintillator_Logical  = new G4LogicalVolume( StraightBar_Solid,
						     TriggerScintillator_Material,
						     "TriggerScintillator_Logical",
						     0,0,0);


  // define center position of TriggerScintillator within Container
  G4ThreeVector Position_TriggerScintillator  = G4ThreeVector(0,0,0);
  
  // define Scintillator physical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define TriggerScintillator Physical " << G4endl << G4endl;
  TriggerScintillator_Physical   = new G4PVPlacement(0,
						     Position_TriggerScintillator,
						     TriggerScintillator_Logical,
						     "TriggerScintillator_Physical",
						     TriggerScintillatorContainer_Logical,
						     false,
						     0,
						     pSurfChk);
 

  G4cout << G4endl << "###### QweakSimTriggerScintillator: Setting Sensitive Detectors " << G4endl << G4endl;

  // Sensitive detectors
  //------------------------------------------------ 
  // All managed (deleted) by SDManager

   G4SDManager* SDman = G4SDManager::GetSDMpointer();


   //#######################################################
   // define drift chamber elements as sensitiv detectors
   // "sensitivity" will be handled by class QweakSimVDCSD
   //#######################################################


   //***********************************************************
   TriggerScintillatorSD = new QweakSimTriggerScintillator_DetectorSD("/TriggerScintillatorSD");
   SDman->AddNewDetector(TriggerScintillatorSD);
   
   // add Scintillator detector as a sensitiv element
   //TriggerScintillator_Logical->SetSensitiveDetector(TriggerScintillatorSD);
   TriggerScintillatorContainer_Logical->SetSensitiveDetector(TriggerScintillatorSD);
   //***********************************************************


G4cout << G4endl << "###### QweakSimTriggerScintillator: Setting Attributes " << G4endl << G4endl;

 G4Colour  orange    ( 255/255., 127/255.,   0/255.);
 G4Colour  blue      (   0/255.,   0/255., 255/255.);
 // G4Colour  magenta   ( 255/255.,   0/255., 255/255.); 
 G4Colour  grey      ( 127/255., 127/255., 127/255.);
 G4Colour  lightblue   ( 139/255., 208/255., 255/255.);
 G4Colour  lightorange ( 255/255., 189/255., 165/255.);

 //------------------------------------------
 // Visual Attributes for:  ScintillatorContainer
 //------------------------------------------
 G4VisAttributes* TriggerScintillatorContainerVisAtt = new G4VisAttributes(blue);
 //TriggerScintillatorContainerVisAtt->SetVisibility(false);
 TriggerScintillatorContainerVisAtt->SetVisibility(true);
 TriggerScintillatorContainerVisAtt->SetForceWireframe(true);
 //TriggerScintillatorContainerVisAtt->SetForceSolid(true);
 TriggerScintillatorContainer_Logical->SetVisAttributes(TriggerScintillatorContainerVisAtt); 

 //-----------------------------------------
 // Visual Attributes for:  TriggerScintillator
 //-----------------------------------------
//  G4VisAttributes* TriggerScintillatorVisAtt = new G4VisAttributes(lightblue);
//  TriggerScintillatorVisAtt->SetVisibility(true);
//  // Needed for the correct visualization using Coin3D
//  //TriggerScintillatorVisAtt->SetForceSolid(true);
//  //TriggerScintillatorVisAtt->SetForceWireframe(true);
//  TriggerScintillator_Logical->SetVisAttributes(TriggerScintillatorVisAtt);
//
G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator::ConstructComponent() " << G4endl << G4endl;

} // end of  QweakSimTriggerScintillator::ConstructComponent()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTriggerScintillator::SetTriggerScintillatorMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing TriggerScintillator Detector Material: Looking up Material  " << G4endl; 
                TriggerScintillator_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing Scintillator detector  Material:  Now the TriggerScintillator is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing TriggerScintillator Detector Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTriggerScintillator::DestroyComponent()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator::SetTriggerScintillatorThickness(G4double thickness)
{
    G4cout << G4endl << "###### Calling QweakSimTriggerScintillator::SetTriggerScintillatorThickness() " << G4endl << G4endl;

    G4Box *box = NULL;

    Thickness = thickness;	 

    if(TriggerScintillator_Logical) 
      box = (G4Box*) TriggerScintillator_Logical->GetSolid();
    if(box) 
      box->SetZHalfLength(0.5*Thickness);
  
  
    G4RunManager::GetRunManager()->GeometryHasBeenModified();

    G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator::SetTriggerScintillatorThickness() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator::SetTriggerScintillatorCenterPositionInX(G4double xPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimTriggerScintillator::SetScintillatorCenterPositionInX() " << G4endl << G4endl;

    Position_TriggerScintillatorContainer_X[pkg] =xPos;
    TriggerScintillatorGeometryPVUpdate();

    G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator::SetTriggerScintillatorCenterPositionInX() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator::SetTriggerScintillatorCenterPositionInY(G4double yPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimTriggerScintillator::SetTriggerScintillatorCenterPositionInY() " << G4endl << G4endl;

    Position_TriggerScintillatorContainer_Y[pkg] = yPos;
    TriggerScintillatorGeometryPVUpdate();

 G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator::SetTriggerScintillatorCenterPositionInY() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator::SetTriggerScintillatorCenterPositionInZ(G4double zPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimTriggerScintillator::SetTriggerScintillatorCenterPositionInZ() " << G4endl << G4endl;

    Position_TriggerScintillatorContainer_Z[pkg] = zPos;
    TriggerScintillatorGeometryPVUpdate();
    
    G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator::SetTriggerScintillatorCenterPositionInZ() " << G4endl << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator::SetTriggerScintillatorTiltAngle(G4double tiltangle)
{
    G4cout << G4endl << "###### Calling QweakSimTriggerScintillator::SetTriggerScintillatorTiltAngle() " << G4endl << G4endl;

    // assign new tilting 
    Tilting_Angle = tiltangle;

    TriggerScintillatorGeometryPVUpdate();

    G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator::SetTriggerScintillatorTiltAngle() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator::SetTriggerScintillatorPhiAngle(G4double phiangle)
{
    //G4cout << G4endl << "###### Calling QweakSimTriggerScintillator::SetTriggerScintillatorPhiAngle() " << G4endl << G4endl;

       // assign new azimuthal angle
       Phi_Angle = phiangle -90.0*degree;

       TriggerScintillatorGeometryPVUpdate();

       G4cout << G4endl << "###### Leaving QweakSimTriggerScintillator::SetTriggerScintillatorPhiAngle() " << G4endl << G4endl;

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator::PlaceTriggerScintillator_MasterContainers()
{
	  G4cout << G4endl << "###### QweakSimTriggerScintillator: Define TriggerScintillatorContainer_Physical " << G4endl << G4endl;
	  for (size_t i=0; i< TriggerScintillatorContainer_Physical.size();i++)
	  {

	   G4double phi = Phi_Angle + i * 180.0 * degree;
	   Rotation_TriggerScintillatorContainer[i] = new G4RotationMatrix();
	   Rotation_TriggerScintillatorContainer[i]->rotateZ(-phi);
	   Rotation_TriggerScintillatorContainer[i]->rotateX(Tilting_Angle);

	   Position_TriggerScintillatorContainer  = G4ThreeVector(Position_TriggerScintillatorContainer_X[i],
									 Position_TriggerScintillatorContainer_Y[i],
									 Position_TriggerScintillatorContainer_Z[i]);

	   Position_TriggerScintillatorContainer.rotateZ(phi);

	   TriggerScintillatorContainer_Physical[i]   = new G4PVPlacement(Rotation_TriggerScintillatorContainer[i],
								      Position_TriggerScintillatorContainer,
								      "TriggerScintillatorContainer_Physical",
								      TriggerScintillatorContainer_Logical,
								      theMotherPV,
								      false,
								      i,
								      pSurfChk);
	  }
}
void QweakSimTriggerScintillator::TriggerScintillatorGeometryPVUpdate()
{
	  for (size_t i=0; i< TriggerScintillatorContainer_Physical.size();i++) {
	        if (TriggerScintillatorContainer_Logical)
	        	TriggerScintillatorContainer_Logical->RemoveDaughter(TriggerScintillatorContainer_Physical[i]);

	        delete TriggerScintillatorContainer_Physical[i];
	        TriggerScintillatorContainer_Physical[i] = 0;

	        delete Rotation_TriggerScintillatorContainer[i];
	        Rotation_TriggerScintillatorContainer[i] = 0;

	    }

	  PlaceTriggerScintillator_MasterContainers();
}
