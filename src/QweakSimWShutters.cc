//=============================================================================
//
//  File     QweakSimWShutters.cc
//  Revision 1.0
//  Date     02/06/2012
//  Author   Kurtis Bartlett
//
//=============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimWShutters.hh"

static const G4double inch = 2.54*cm;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimWShutters::QweakSimWShutters(G4int n)
{
	WShutters_Logical  = NULL;
	WShutters_Physical = NULL;
	WShutters_Box 	   = NULL;
	WShutters_Trap     = NULL;
	WShutters_Solid    = NULL;
	WShutters_Material = NULL;
	WShutters_VisAtt   = NULL;

	Rot = NULL;
	WRot = NULL;

	WShutters_Length_X        =   2.687*inch;
	WShutters_Length_Y        =   3.7*inch;
	WShutters_Length_Z        =    2.0*inch;



  WShutters_CenterXPosition = 0.5 * WShutters_Length_X + 2.625*inch;
  WShutters_CenterYPosition = 0.0*inch;
  WShutters_CenterZPosition = -(0.5 * WShutters_Length_Z)-220.939*inch;

  WShutters_Messenger = new QweakSimWShuttersMessenger(this,n);

 // get access to material definition
  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimWShutters::~QweakSimWShutters()
{
  if (pMaterial)  delete pMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimWShutters::ConstructWShutters(G4VPhysicalVolume* MotherVolume)
{

  //  assign material
	WShutters_Material = pMaterial->GetMaterial("TungstenAlloy");

  G4ThreeVector positionWShutters;
  G4ThreeVector Trans;



  Rot = new G4RotationMatrix;
  Rot->rotateY(-M_PI/2*rad);
  Trans = G4ThreeVector(-2.688*inch,0,0);

  WShutters_Box = new G4Box("WShutters_Box", WShutters_Length_X*0.5, WShutters_Length_Y*0.5, WShutters_Length_Z*0.5);
  WShutters_Trap = new G4Trap("WShutters_Trap", 0.5*WShutters_Length_Z, 0.5*WShutters_Length_Z, 0.5*2.125*inch, 0.5*WShutters_Length_Y,0.5*2.688*inch);
  WShutters_Solid = new G4UnionSolid("WShutters_Box+WShutters_Trap", WShutters_Box, WShutters_Trap, Rot, Trans);

  WRot = new G4RotationMatrix;
  WRot->rotateZ(M_PI*rad);

  //***************************************************************************
  //  Define WShutters logical and physical volumes

  WShutters_Logical = new G4LogicalVolume(WShutters_Solid,
		  	  	  	  	  	  	  	  	  WShutters_Material,
                                         "WShutters_Log",
                                         0,0,0);

  positionWShutters = G4ThreeVector(WShutters_CenterXPosition,
		  	  	  	  	  	  	  	WShutters_CenterYPosition,
		  	  	  	  	  	  	  	WShutters_CenterZPosition);

  if(WShutterNum==1){
	  WShutters_Physical = new G4PVPlacement(0,
                                        positionWShutters,
                                        "WShutters",
                                        WShutters_Logical,
                                        MotherVolume,
                                        false,
                                        0,
                                        pSurfChk);
  }else if(WShutterNum==2){
	  WShutters_Physical = new G4PVPlacement(WRot,
	                                          positionWShutters,
	                                          "WShutters",
	                                          WShutters_Logical,
	                                          MotherVolume,
	                                          false,
	                                          0,
	                                          pSurfChk);
  }
  //***************************************************************************

  //  Formating
  G4Color blue (0.,0.,1.);

  WShutters_VisAtt = new G4VisAttributes(blue);
  WShutters_VisAtt->SetVisibility(true);
  WShutters_Logical->SetVisAttributes(WShutters_VisAtt);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimWShutters::SetWShuttersMaterial(G4String materialName)
{
  //  Sets WShutters material
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
  if (pttoMaterial)
	  WShutters_Logical->SetMaterial(pttoMaterial);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimWShutters::SetWShutters_CenterPositionInX(G4double xPos)
{
  //  Sets X position of the WShutters
	WShutters_CenterXPosition = xPos;
	WShutters_Physical->SetTranslation(G4ThreeVector(WShutters_CenterXPosition,
													 WShutters_CenterYPosition,
													 WShutters_CenterZPosition));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimWShutters::SetWShutters_CenterPositionInY(G4double yPos)
{
  //  Sets Y position of the WShutters
	WShutters_CenterYPosition = yPos;
	WShutters_Physical->SetTranslation(G4ThreeVector(WShutters_CenterXPosition,
													 WShutters_CenterYPosition,
													 WShutters_CenterZPosition));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimWShutters::SetWShutters_CenterPositionInZ(G4double zPos)
{
  //  Sets Z position of the WShutters
	WShutters_CenterZPosition = zPos;
	WShutters_Physical->SetTranslation(G4ThreeVector(WShutters_CenterXPosition,
													 WShutters_CenterYPosition,
													 WShutters_CenterZPosition));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimWShutters::SetWShutters_Material(G4String materialName)
{
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
  WShutters_Logical->SetMaterial(pttoMaterial);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimWShutters::SetEnabled()
{
  //  Enables the WShutters
  WShutters_VisAtt->SetVisibility(true);
  SetWShutters_Material(WShutters_Material->GetName());
  WShutters_Physical->SetTranslation(G4ThreeVector(WShutters_CenterXPosition,
		  	  	  	  	  	  	  	  	  	  	   WShutters_CenterYPosition,
		  	  	  	  	  	  	  	  	  	  	   WShutters_CenterZPosition));


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimWShutters::SetDisabled()
{
  // Disables the WShutters by changing the material to air,
  // moving the wall 5m into the floor and hiding it.
	WShutters_VisAtt->SetVisibility(true);
  SetWShutters_Material("Air");
  WShutters_Physical->SetTranslation(G4ThreeVector(WShutters_CenterXPosition,
		  	  	  	  	  	  	  	  	  	  	   WShutters_CenterYPosition + 200*cm,
		  	  	  	  	  	  	  	  	  	  	   WShutters_CenterZPosition));

}
