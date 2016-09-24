
// QweakSimLeadGlass.cc
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#include "QweakSimLeadGlass.hh"

//--- geant4 includes
#include "G4RunManager.hh"
#include "G4VisAttributes.hh"

//--- user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimLeadGlassMessenger.hh"
#include "QweakSimLeadGlass_DetectorSD.hh"
#include "QweakSimLeadGlass_PMTSD.hh"



/////// --------------------------------------------------------------------

QweakSimLeadGlass::QweakSimLeadGlass()
{
    //--- Initialize Pointers
	
    LeadGlassMessenger  = NULL;
	
    pMaterial           = NULL;
	
    LeadGlass_Solid     = NULL;
    LeadGlass_Logical   = NULL;
    LeadGlass_Physical  = NULL;
	
    LeadGlass_Material  = NULL;
	
    LeadGlassSD         = NULL;
	
    LeadGlass_VisAtt    = NULL;
	
    //--- Set Initialize Values
	
    LeadGlass_FullLength_X = 19.10*cm;
    LeadGlass_FullLength_Y = 19.10*cm;
    LeadGlass_FullLength_Z = 30.50*cm;
	
    MD7_CenterPosition_X =     0.0*cm;
    MD7_CenterPosition_Y = -335.17*cm;
    MD7_CenterPosition_Z =  577.88*cm;
	
    LeadGlass_CenterPosition_X = 0.0*cm;     //-150.00*cm;
    LeadGlass_CenterPosition_Y = -315.00*cm; //-300.00*cm;
    LeadGlass_CenterPosition_Z =  530.00*cm;
	
    LeadGlass_TiltAngle_X =  0.00*degree;
    LeadGlass_TiltAngle_X =  0.00*degree;
    LeadGlass_TiltAngle_X =  0.00*degree;
	
    LeadGlassMessenger = new QweakSimLeadGlassMessenger(this);
	
    pMaterial = new QweakSimMaterial();
    pMaterial->DefineMaterials();  
	
}



/////// --------------------------------------------------------------------

QweakSimLeadGlass::~QweakSimLeadGlass()
{
    // --- Delete Pointers
	
    if (LeadGlass_VisAtt)          delete LeadGlass_VisAtt;
	
    //if (LeadGlassSD)               delete LeadGlassSD;
    
    if (LeadGlass_Material)        delete LeadGlass_Material;
	
    if (LeadGlass_Physical)        delete LeadGlass_Physical;
    if (LeadGlass_Logical)         delete LeadGlass_Logical;
    if (LeadGlass_Solid)           delete LeadGlass_Solid;
	
    if (pMaterial)                 delete pMaterial;
	
    if (LeadGlassMessenger)        delete LeadGlassMessenger;
	
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
	
    //--- Material
	
    LeadGlass_Material = pMaterial->GetMaterial("LeadGlass"); 
	
    //--- Define LeadGlass Solid Volume
	
    LeadGlass_Solid = new G4Box("LeadGlass_Solid",
                                 0.5*LeadGlass_FullLength_X,     // X Length
                                 0.5*LeadGlass_FullLength_Y,     // Y Length
                                 0.5*LeadGlass_FullLength_Z);    // Z Length
	
    //--- Define LeadGlass Logical Volume
	
    LeadGlass_Logical = new G4LogicalVolume(LeadGlass_Solid,
                                            LeadGlass_Material,
                                            "LeadGlass_Logical",
                                            0,0,0);
	
    //--- Define LeadGlass Physical Volume
	
    LeadGlass_CenterPosition = G4ThreeVector(LeadGlass_CenterPosition_X,
                                             LeadGlass_CenterPosition_Y,
                                             LeadGlass_CenterPosition_Z);
	
    LeadGlass_RotationMatrix = new G4RotationMatrix();
    LeadGlass_RotationMatrix -> rotateX(LeadGlass_TiltAngle_X);
	
    LeadGlass_Physical = new G4PVPlacement(LeadGlass_RotationMatrix,
                                           LeadGlass_CenterPosition,
                                           "LeadGlass_Phyical",
                                           LeadGlass_Logical,
                                           MotherVolume,
                                           false,
                                           0,
                                           pSurfChk);
	
    //--- Define Sensitive Detectors to LeadGlass
    
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
	
    LeadGlassSD = new QweakSimLeadGlass_DetectorSD("LeadGlassSD");
    SDman -> AddNewDetector(LeadGlassSD);
    LeadGlass_Logical -> SetSensitiveDetector(LeadGlassSD);
	
    //--- Define Visulization Attributes
	
    G4Colour blue (0/255., 0/255., 255/255.); 
    LeadGlass_VisAtt = new G4VisAttributes(blue);
    LeadGlass_VisAtt -> SetVisibility(true);
    LeadGlass_Logical -> SetVisAttributes(LeadGlass_VisAtt);
	
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass::DestroyComponent()
{
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass::SetLeadGlass_Material(G4String materialName)
{
    //--- Set LeadGlass Material
	
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    
    if (pttoMaterial)
    {
        G4cout << "=== Changing LeadGlass material: Look up material " << G4endl;
        LeadGlass_Logical -> SetMaterial(pttoMaterial);
        G4cout << "=== Changing LeadGlass material: Now the material is " << materialName << G4endl;
    }
    else 
        G4cerr << "=== Error: Changing LeadGlass material FAILED! " << G4endl << G4endl;

}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass::SetLeadGlass_CenterPositionInX(G4double xPos)
{
    //--- Set LeadGlass X Position
	
    G4cout << "=== Calling QweakSimLeadGlass::SetLeadGlass_CenterPositionInX() " << G4endl;
    LeadGlass_CenterPosition_X = xPos;	 
    LeadGlass_Physical->SetTranslation(G4ThreeVector(LeadGlass_CenterPosition_X,
                                                     LeadGlass_CenterPosition_Y, 
                                                     LeadGlass_CenterPosition_Z));
    G4cout << "=== Leaving QweakSimLeadGlass::SetLeadGlass_CenterPositionInX() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass::SetLeadGlass_CenterPositionInY(G4double yPos)
{    
    //--- Set LeadGlass Y Position
	
    G4cout << "=== Calling QweakSimLeadGlass::SetLeadGlass_CenterPositionInY() " << G4endl;
    LeadGlass_CenterPosition_Y = yPos;	 
    LeadGlass_Physical->SetTranslation(G4ThreeVector(LeadGlass_CenterPosition_X,
                                                     LeadGlass_CenterPosition_Y, 
                                                     LeadGlass_CenterPosition_Z));	
    G4cout << "=== Leaving QweakSimLeadGlass::SetLeadGlass_CenterPositionInY() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass::SetLeadGlass_CenterPositionInZ(G4double zPos)
{
    //--- Set LeadGlass Z Position
	
    G4cout << "=== Calling QweakSimLeadGlass::SetLeadGlass_CenterPositionInZ() " << G4endl;
    LeadGlass_CenterPosition_Z = zPos;	 	
    LeadGlass_Physical->SetTranslation(G4ThreeVector(LeadGlass_CenterPosition_X,
                                                     LeadGlass_CenterPosition_Y, 
                                                     LeadGlass_CenterPosition_Z));	
    G4cout << "=== Leaving QweakSimLeadGlass::SetLeadGlass_CenterPositionInZ() " << G4endl << G4endl;
}




/////// --------------------------------------------------------------------

void QweakSimLeadGlass::SetLeadGlass_TiltAngleInX(G4double xTiltAngle)
{
    //--- Set LeadGlass New X Tilting Angle
	
    G4cout << G4endl << "=== Calling QweakSimLeadGlass::SetLeadGlass_TiltAngleInX() " << G4endl;
	
    //--- rotate back with old angle
    LeadGlass_RotationMatrix->rotateX(-1.0*LeadGlass_TiltAngle_X);
    LeadGlass_Physical->SetRotation(LeadGlass_RotationMatrix);
	
    //--- assign new tilting angle
    LeadGlass_TiltAngle_X = xTiltAngle;
	
    //--- rotate to new angle
    LeadGlass_RotationMatrix->rotateX(LeadGlass_TiltAngle_X);
    LeadGlass_Physical->SetRotation(LeadGlass_RotationMatrix);
	
    G4cout << G4endl << "=== Leaving QweakSimLeadGlass::SetLeadGlass_TiltAngleInX() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass::SetLeadGlass_TiltAngleInY(G4double yTiltAngle)
{
    //--- Set LeadGlass New Y Tilting Angle
	
    G4cout << G4endl << "=== Calling QweakSimLeadGlass::SetLeadGlass_TiltAngleInY() " << G4endl;
	
    //--- rotate back with old angle
    LeadGlass_RotationMatrix->rotateY(-1.0*LeadGlass_TiltAngle_Y);
    LeadGlass_Physical->SetRotation(LeadGlass_RotationMatrix);
	
    //--- assign new tilting angle
    LeadGlass_TiltAngle_Y = yTiltAngle;
	
    //--- rotate to new angle
    LeadGlass_RotationMatrix->rotateY(LeadGlass_TiltAngle_Y);
    LeadGlass_Physical->SetRotation(LeadGlass_RotationMatrix);
	
    G4cout << G4endl << "=== Leaving QweakSimLeadGlass::SetLeadGlass_TiltAngleInY() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass::SetLeadGlass_TiltAngleInZ(G4double zTiltAngle)
{
    //--- Set LeadGlass New Z Tilting Angle
	
    G4cout << G4endl << "=== Calling QweakSimLeadGlass::SetLeadGlass_TiltAngleInZ() " << G4endl;
	
    //--- rotate back with old angle
    LeadGlass_RotationMatrix->rotateZ(-1.0*LeadGlass_TiltAngle_Z);
    LeadGlass_Physical->SetRotation(LeadGlass_RotationMatrix);
	
    //--- assign new tilting angle
    LeadGlass_TiltAngle_Z = zTiltAngle;
	
    //--- rotate to new angle
    LeadGlass_RotationMatrix->rotateZ(LeadGlass_TiltAngle_Z);
    LeadGlass_Physical->SetRotation(LeadGlass_RotationMatrix);
	
    G4cout << G4endl << "=== Leaving QweakSimLeadGlass::SetLeadGlass_TiltAngleInZ() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass::SetLeadGlass_Enabled()
{
    //--- Enable the LeadGlass
	
    G4cout << "=== Calling QweakSimLeadGlass::SetLeadGlass_Enabled() " << G4endl;
    LeadGlass_VisAtt -> SetVisibility(true);
    SetLeadGlass_Material(LeadGlass_Material -> GetName());
    LeadGlass_Physical->SetTranslation(G4ThreeVector(LeadGlass_CenterPosition_X,
                                                     LeadGlass_CenterPosition_Y, 
                                                     LeadGlass_CenterPosition_Z));
    G4cout << "=== Leaving QweakSimLeadGlass::SetLeadGlass_Enabled() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass::SetLeadGlass_Disabled()
{
    //--- Disable the LeadGlass
	
    G4cout << "=== Calling QweakSimLeadGlass::SetLeadGlass_Disabled() " << G4endl;
    LeadGlass_VisAtt -> SetVisibility(true);
    SetLeadGlass_Material("Air");
    LeadGlass_Physical->SetTranslation(G4ThreeVector(LeadGlass_CenterPosition_X,
                                                     LeadGlass_CenterPosition_Y, 
                                                     LeadGlass_CenterPosition_Z + 400.00*cm));
    G4cout << "=== Leaving QweakSimLeadGlass::SetLeadGlass_Disabled() " << G4endl << G4endl;
}


/////// --------------------------------------------------------------------


