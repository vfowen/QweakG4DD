/*

   \file QweakSimLumiDetector.cc
   \author Wade Duvall

*/

#include "QweakSimLumiDetector.hh"
#include "G4RunManager.hh"
#include "G4VisAttributes.hh"
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimLumi_DetectorSD.hh"
#include "QweakSimLumiMessenger.hh"


QweakSimLumiDetector::QweakSimLumiDetector()
{

    // Initialize pointers to objects
    LumiMessenger   = NULL;
    USLumi_Rot      = NULL;
    USLumi_Solid    = NULL;
    USLumi_Logical  = NULL;
    USLumi_Physical = NULL;
    DSLumi_Rot      = NULL;
    DSLumi_Solid    = NULL;
    DSLumi_Logical  = NULL;
    DSLumi_Physical = NULL;

    /* Geometries are for the detector in the 1 slot:
     * https://qweak.jlab.org/wiki/images/Qweak-Coordinate-Systems.png
     *
     * FIXME: These need to be double checked by me.
     */

    /* USLumi geometries */
    USLumi_Length_X = 7.0*cm;
    USLumi_Length_Y = 25.0*cm;
    USLumi_Length_Z = 2.0*cm;
    // DSLumi geometries
    DSLumi_Length_X = 2.0*cm;
    DSLumi_Length_Y = 6.0*cm;
    DSLumi_Length_Z = 4.0*cm;

    // USLumi positions
    USLumi_Position_X = 25.0*cm;
    USLumi_Position_Y = 0.0*cm;
    USLumi_Position_Z = -387.5*cm;
    // DSLumi positions
    DSLumi_Position_X = 0*cm;
    DSLumi_Position_Y = 0*cm;
    DSLumi_Position_Z = 0*cm;

    // Create lumi messenger
    LumiMessenger = new QweakSimLumiMessenger(this);

    // Access to material definition
    pMaterial = new QweakSimMaterial();
    pMaterial->DefineMaterials();

    // Get quartz for lumi bars
    QuartzBar = pMaterial->GetMaterial("Quartz");
}

QweakSimLumiDetector::~QweakSimLumiDetector()
{
    if (pMaterial) delete pMaterial;
}

void QweakSimLumiDetector::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
    // Create G4RotationMatrix and set rotation to zero for now
    USLumi_Rot = new G4RotationMatrix();
    DSLumi_Rot = new G4RotationMatrix();
    USLumi_Rot->rotateX(0);
    DSLumi_Rot->rotateX(0);

    // Create G4ThreeVector for lumi positions
    USLumi_XYZ = G4ThreeVector(USLumi_Position_X, USLumi_Position_Y, USLumi_Position_Z);
    DSLumi_XYZ = G4ThreeVector(DSLumi_Position_X, DSLumi_Position_Y, DSLumi_Position_Z);

    //DSLumi_Position = new G4PVPlacement(USLumi_Rot,G4ThreeVector(DSLumi_Position_X, DSLumi_Position_Y, DSLumi_Position_Z));

    // Create upstream lumi bar
    USLumi_Solid = new G4Box("USLumi",              // Object name
                             USLumi_Length_X/2.0,   // X size
                             USLumi_Length_Y/2.0,   // Y size
                             USLumi_Length_Z/2.0);  // Z Size

    // Place the lumi bar into a quartz lv
    USLumi_Logical = new G4LogicalVolume(USLumi_Solid,      // Solid placed in lv
                                         QuartzBar,         // Material for lv
                                         "USLumi_Logical",  // Name for object
                                         0,0,0);            // Set all options to zero for now

    //DSLumi_Logical = new G4LogicalVolume(DSLumi_Solid,      // Solid placed in lv
    //                                     QuartzBar,         // Material for lv
    //                                     "DSLumi_Logical",  // Name for object
    //                                     0,0,0);            // Set all options to zero for now

    // Create G4PVPlacement with uslumi position
    USLumi_Physical = new G4PVPlacement(USLumi_Rot,
                                        USLumi_XYZ,
                                        "USLumi_Physical",
                                        USLumi_Logical,
                                        MotherVolume,
                                        false,
                                        0,
                                        pSurfChk);

    // Create G4PVPlacement with dslumi position
    //DSLumi_Physical = new G4PVPlacement(DSLumi_Rot,
    //                                    DSLumi_XYZ,
    //                                    "DSLumi_Physical",
    //                                    DSLumi_Logical,
    //                                    MotherVolume,
    //                                    false,
    //                                    0);
    
    // Define sensitive detectors for USLumi and DSLumi
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    USLumiSD = new QweakSimLumi_DetectorSD("USLumiSD");
    SDman->AddNewDetector(USLumiSD);
    USLumi_Logical->SetSensitiveDetector(USLumiSD);

    //Make it pretty...
    G4Colour  red   (1.,0.,0.);
    G4Colour  blue      (0.,0.,1.);

    USLumi_VisAtt = new G4VisAttributes(red);
    //G4VisAttributes* DSLumi_VisAtt = new G4VisAttributes(blue);
    USLumi_VisAtt->SetVisibility(true);
    USLumi_Logical->SetVisAttributes(USLumi_VisAtt);

}

void QweakSimLumiDetector::SetUSLumi_PositionInX(G4double xPos) {
    /* Set USLumi X position. */

    G4cout << "=== Calling QweakSimLumi::SetUSLumi_PositionInX() " << G4endl;
    USLumi_Position_X = xPos;                                                               
    USLumi_Physical->SetTranslation(G4ThreeVector(USLumi_Position_X,
                USLumi_Position_Y,
                USLumi_Position_Z));
    G4cout << "=== Leaving QweakSimLumi::SetUSLumi_PositionInX() " << G4endl << G4endl;
}

void QweakSimLumiDetector::SetUSLumi_PositionInY(G4double yPos) {
    /* Set USLumi Y position. */

    G4cout << "=== Calling QweakSimLumi::SetUSLumi_PositionInY() " << G4endl;
    USLumi_Position_Y = yPos;                                                               
    USLumi_Physical->SetTranslation(G4ThreeVector(USLumi_Position_Y,
                USLumi_Position_Y,
                USLumi_Position_Z));
    G4cout << "=== Leaving QweakSimLumi::SetUSLumi_PositionInY() " << G4endl << G4endl;
}

void QweakSimLumiDetector::SetUSLumi_PositionInZ(G4double zPos) {
    /* Set USLumi Z position. */

    G4cout << "=== Calling QweakSimLumi::SetUSLumi_PositionInZ() " << G4endl;
    USLumi_Position_Z = zPos;                                                               
    USLumi_Physical->SetTranslation(G4ThreeVector(USLumi_Position_Z,
                USLumi_Position_Y,
                USLumi_Position_Z));
    G4cout << "=== Leaving QweakSimLumi::SetUSLumi_PositionInZ() " << G4endl << G4endl;
}

void QweakSimLumiDetector::SetUSLumi_Material(G4String materialName) {
    //--- Set USLumi Material
    
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    
    if (pttoMaterial)
    {
        G4cout << "=== Changing USLumi material: Look up material " << G4endl;
        USLumi_Logical -> SetMaterial(pttoMaterial);
        G4cout << "=== Changing USLumi material: Now the material is " << materialName << G4endl;
    }
    else 
        G4cerr << "=== Error: Changing USLumi material FAILED! " << G4endl << G4endl;

}

void QweakSimLumiDetector::SetUSLumi_Enabled() {
    //--- Enable the USLumi
    
    G4cout << "=== Calling QweakSimLumi::SetUSLumi_Enabled() " << G4endl;
    USLumi_VisAtt->SetVisibility(true);
    SetUSLumi_Material(QuartzBar -> GetName());
    USLumi_Physical->SetTranslation(G4ThreeVector(USLumi_Position_X,
                                                  USLumi_Position_Y, 
                                                  USLumi_Position_Z));
    G4cout << "=== Leaving QweakSimLumi::SetUSLumi_Enabled() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimLumiDetector::SetUSLumi_Disabled() {
    //--- Disable the USLumi
    
    G4cout << "=== Calling QweakSimLumi::SetUSLumi_Disabled() " << G4endl;
    USLumi_VisAtt -> SetVisibility(false);
    SetUSLumi_Material("Air");
    USLumi_Physical->SetTranslation(G4ThreeVector(USLumi_Position_X,
                                                  USLumi_Position_Y, 
                                                  USLumi_Position_Z));
    G4cout << "=== Leaving QweakSimLumi::SetLumi_Disabled() " << G4endl << G4endl;
}
