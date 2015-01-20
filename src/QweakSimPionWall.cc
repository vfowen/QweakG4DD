
//=============================================================================
//
//  File     QweakSimPionWall.cc
//  Revision 1.0
//  Date     07/05/2012
//  Author   James Dowd
//
//=============================================================================

//  Pion Wall z=?

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimPionWall.hh"

static const G4double inch = 2.54*cm;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimPionWall::QweakSimPionWall()
{
  PionWall_Logical  = NULL;
  PionWall_Physical = NULL;
  PionWall_Solid    = NULL;
  PionWall_Material = NULL;
  PionWall_VisAtt   = NULL;
  
  PionWall_Length_X        = 22*4*inch;  //  22 bricks wide  (8" x 4" x 2")
  PionWall_Length_Y        =   10*inch;  //  8" tall brick + another on its side
  PionWall_Length_Z        =    4*inch;  //  4" thick (2 bricks)

  MD7_CenterYPosition = -335.17*cm;
  MD7_CenterZPosition = 577.88*cm;

  Offset_X = 0.0*cm;
  Offset_Y = 0.0*cm;
  Offset_Z = 0.0*cm;
  
  PionWall_CenterXPosition = 0*cm;
  PionWall_CenterYPosition = MD7_CenterYPosition + 1*inch;  //  MD7 center Y position + 1"
  PionWall_CenterZPosition = MD7_CenterZPosition       // MD 7 center Z position
                             - 6.5*cm                  // Center of Pb brick in front of PMT
                             - 1*inch                  // 1/2 Pb brick thickness
                             - 0.5*PionWall_Length_Z   // 1/2 pion wall thickness
                             - 0.5*cm;                 // extra space so the pion wall doesn't overlap MD volume

  //  This position places the PionWall 0.5 cm  upstream of the Pb PMT shielding of MD7
  //  in Z and flush in Y. (Flush along bottom of Pb PMT shielding)
  
  
  PionWall_Messenger = new QweakSimPionWallMessenger(this);
  
 // get access to material definition
  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();

}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimPionWall::~QweakSimPionWall()
{
  if (pMaterial)  delete pMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::ConstructPionWall(G4VPhysicalVolume* MotherVolume)
{
//-----------------------------------------------------------------------------
//!  Creates the Pion Wall
/*
  \param G4VPhysicalVolume* - The physical volume in which the pion wall will be placed
*/
//-----------------------------------------------------------------------------

  //  assign material
  PionWall_Material = pMaterial->GetMaterial("Lead");
  
  G4ThreeVector positionPionWall;
  
  
  //  Construct pion wall volume
  PionWall_Solid = new G4Box("PionWall_Sol", 
                    PionWall_Length_X*0.5, PionWall_Length_Y*0.5, PionWall_Length_Z*0.5);
  
  //***************************************************************************
  //  Define pion wall logical and physical volumes
  
  PionWall_Logical = new G4LogicalVolume(PionWall_Solid, 
                                         PionWall_Material,
                                         "PionWall_Log",
                                         0,0,0);
  
  positionPionWall = G4ThreeVector(PionWall_CenterXPosition + Offset_X,
                                   PionWall_CenterYPosition + Offset_Y,
                                   PionWall_CenterZPosition + Offset_Z);
  
  PionWall_Physical = new G4PVPlacement(0,
                                        positionPionWall,
                                        "PionWall",
                                        PionWall_Logical,
                                        MotherVolume,
                                        false,
                                        0,
                                        pSurfChk);
  //***************************************************************************
  
  //  Formating
  G4Color blue (0.,0.,1.);
  
  PionWall_VisAtt = new G4VisAttributes(blue);
  PionWall_VisAtt->SetVisibility(true);
  PionWall_Logical->SetVisAttributes(PionWall_VisAtt);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWallMaterial(G4String materialName)
{
  //  Sets pion wall material
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
  if (pttoMaterial)
    PionWall_Logical->SetMaterial(pttoMaterial);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_CenterPositionInX(G4double xPos)
{
  //  Sets X position of the pion wall
  PionWall_CenterXPosition = xPos;
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition + Offset_X,
                                                  PionWall_CenterYPosition + Offset_Y,
                                                  PionWall_CenterZPosition + Offset_Z));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_CenterPositionInY(G4double yPos)
{
  //  Sets Y position of the pion wall
  PionWall_CenterYPosition = yPos;
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition + Offset_X,
                                                  PionWall_CenterYPosition + Offset_Y,
                                                  PionWall_CenterZPosition + Offset_Z));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_CenterPositionInZ(G4double zPos)
{
  //  Sets Z position of the pion wall
  PionWall_CenterZPosition = zPos;
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition + Offset_X,
                                                  PionWall_CenterYPosition + Offset_Y,
                                                  PionWall_CenterZPosition + Offset_Z));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_Position_Offset_X(G4double xOff)
{
  //  Sets X position offset of the pion wall
  Offset_X = xOff;
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition + Offset_X,
                                                  PionWall_CenterYPosition + Offset_Y,
                                                  PionWall_CenterZPosition + Offset_Z));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_Position_Offset_Y(G4double yOff)
{
  //  Sets Y position offset of the pion wall
  Offset_Y = yOff;
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition + Offset_X,
                                                  PionWall_CenterYPosition + Offset_Y,
                                                  PionWall_CenterZPosition + Offset_Z));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_Position_Offset_Z(G4double zOff)
{
  //  Sets Z position offset of the pion wall
  Offset_Z = zOff;
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition + Offset_X,
                                                  PionWall_CenterYPosition + Offset_Y,
                                                  PionWall_CenterZPosition + Offset_Z));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_LengthInX(G4double dim)
{
  // Sets thickness in X of the Pion Wall 
  if (dim > 0.0){
    //G4double oldDim = PionWall_Length_X;
    PionWall_Length_X = dim;
    PionWall_Solid->SetXHalfLength(0.5*PionWall_Length_X);
    //SetPionWall_CenterPositionInZ(PionWall_CenterZPosition + 0.5*oldDim - 0.5*dim);
  } 
  else 
    G4cout << "Pion Wall:  Invalid thickness value" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_LengthInY(G4double dim)
{
  // Sets thickness in Y of the Pion Wall
  if (dim > 0.0){
    G4double oldDim = PionWall_Length_Y;
    PionWall_Length_Y = dim;
    PionWall_Solid->SetYHalfLength(0.5*PionWall_Length_Y);
    SetPionWall_CenterPositionInY(PionWall_CenterYPosition - 0.5*oldDim + 0.5*dim);
  } 
  else 
    G4cout << "Pion Wall:  Invalid thickness value" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_LengthInZ(G4double dim)
{
  // Sets thickness in Z of the Pion Wall and moves the Pion Wall to be flush with Pb MD7 PMT shielding blocks
  if (dim > 0.0){
    G4double oldDim = PionWall_Length_Z;
    PionWall_Length_Z = dim;
    PionWall_Solid->SetZHalfLength(0.5*PionWall_Length_Z);
    SetPionWall_CenterPositionInZ(PionWall_CenterZPosition + 0.5*oldDim - 0.5*dim);
  } 
  else 
    G4cout << "Pion Wall:  Invalid thickness value" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPionWall::SetPionWall_Material(G4String materialName)
{
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName); 
  PionWall_Logical->SetMaterial(pttoMaterial);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPionWall::SetEnabled()
{
  //  Enables the Pion Wall
  PionWall_VisAtt->SetVisibility(true);
  SetPionWall_Material(PionWall_Material->GetName());
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition + Offset_X,
                                                  PionWall_CenterYPosition + Offset_Y,
                                                  PionWall_CenterZPosition + Offset_Z));

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPionWall::SetDisabled()
{
  // Disables the Pion Wall by changing the material to air, 
  // moving the wall 5m into the floor and hiding it.
  PionWall_VisAtt->SetVisibility(true);
  SetPionWall_Material("Air");
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition,
                                                  PionWall_CenterYPosition,
                                                  PionWall_CenterZPosition + 400*cm));

}





