//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimCollimatorSupport.cc

   $Revision: 1.2 $	
   $Date: 2005/12/28 22:45:27 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/28 22:45:27 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimCollimatorSupport.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCollimatorSupport::QweakSimCollimatorSupport(QweakSimCollimator* Colli1, QweakSimCollimator* Colli2)
: FirstCollimator(Colli1), LastCollimator(Colli2)
{
    G4cout << G4endl << "###### Calling QweakSimCollimatorSupport::QweakCollimatorSupport() " << G4endl << G4endl;


  // Top Cover
  CollimatorSupport_TopCover_Logical  = NULL;
  CollimatorSupport_TopCover_Physical = NULL;

  G4double Start_CenterZPos = (FirstCollimator ->GetCollimatorHousing_CenterPositionInZ()) - 0.5*(FirstCollimator ->GetCollimatorHousing_FullLengthInZ());
  G4double End_CenterZPos   = (LastCollimator  ->GetCollimatorHousing_CenterPositionInZ()) + 0.5*(LastCollimator  ->GetCollimatorHousing_FullLengthInZ());

  TopCover_FullLength_Y    =  20.0*cm;
  TopCover_FullLength_Z    = End_CenterZPos - Start_CenterZPos;
  TopCover_FullLength_X    = FirstCollimator->GetCollimatorHousing_FullLengthInX() + 2*TopCover_FullLength_Y;

  TopCover_CenterXPosition =  0.0*cm;
  TopCover_CenterYPosition =  0.5*(FirstCollimator->GetCollimatorHousing_FullLengthInY()) + 0.5*TopCover_FullLength_Y;
  TopCover_CenterZPosition =  Start_CenterZPos + 0.5*TopCover_FullLength_Z;

  // Bottom Cover
  CollimatorSupport_BottomCover_Logical  = NULL;
  CollimatorSupport_BottomCover_Physical = NULL;

  BottomCover_FullLength_Y    = TopCover_FullLength_Y;
  BottomCover_FullLength_Z    = TopCover_FullLength_Z;
  BottomCover_FullLength_X    = TopCover_FullLength_X;

  BottomCover_CenterXPosition =  TopCover_CenterXPosition;
  BottomCover_CenterYPosition =  -0.5*(FirstCollimator->GetCollimatorHousing_FullLengthInY()) - 0.5*BottomCover_FullLength_Y;
  BottomCover_CenterZPosition =  TopCover_CenterZPosition;

  // Left Cover
  CollimatorSupport_LeftCover_Logical  = NULL;
  CollimatorSupport_LeftCover_Physical = NULL;
  
  LeftCover_FullLength_X    =  20.0*cm;
  LeftCover_FullLength_Z    = TopCover_FullLength_Z;
  LeftCover_FullLength_Y    = FirstCollimator->GetCollimatorHousing_FullLengthInY();
  
  LeftCover_CenterXPosition =  0.5*(FirstCollimator->GetCollimatorHousing_FullLengthInX()) + 0.5*LeftCover_FullLength_X;
  LeftCover_CenterYPosition =  0.0*cm;
  LeftCover_CenterZPosition =  TopCover_CenterZPosition;

  // Right Cover
  CollimatorSupport_RightCover_Logical  = NULL;
  CollimatorSupport_RightCover_Physical = NULL;
  
  RightCover_FullLength_X    = LeftCover_FullLength_X;
  RightCover_FullLength_Z    = LeftCover_FullLength_Z;
  RightCover_FullLength_Y    = LeftCover_FullLength_Y;

  RightCover_CenterXPosition =  -0.5*(FirstCollimator->GetCollimatorHousing_FullLengthInX()) - 0.5*RightCover_FullLength_X;
  RightCover_CenterYPosition =  0.0*cm;
  RightCover_CenterZPosition =  TopCover_CenterZPosition;



  //Collimator_Messenger = new QweakSimCollimatorMessenger(this);

 // get access to material definition
  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();

  G4cout << G4endl << "###### Leaving QweakSimCollimatorSupport::QweakCollimatorSupport() " << G4endl << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCollimatorSupport::~QweakSimCollimatorSupport()
{
    G4cout << G4endl << "###### Calling QweakSimCollimatorSupport::~QweakCollimatorSupport() " << G4endl << G4endl;

    if (pMaterial) delete pMaterial;
  
    G4cout << G4endl << "###### Calling QweakSimCollimatorSupport::~QweakCollimatorSupport() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCollimatorSupport::ConstructSupport(G4VPhysicalVolume* MotherVolume)
{
    G4cout << G4endl << "###### Calling QweakSimCollimatorSupport::ConstructSupport() " << G4endl << G4endl;

  // assign material
  // G4Material* CollimatorSupport_Material = pMaterial->GetMaterial("CDA943"); 
  G4Material* CollimatorSupport_Material = pMaterial->GetMaterial("ShieldingConcrete");


  //===========
  // Top Cover
  //===========
  G4ThreeVector positionCollimatorSupport_TopCover(TopCover_CenterXPosition,
			                           TopCover_CenterYPosition,
						   TopCover_CenterZPosition);

  //**********************************************************************************
  //Construct collimator support Top Cover
  G4Box* CollimatorSupport_TopCover_Solid    = new G4Box("CollimatorSupport_TopCover_Sol",
							   0.5 * TopCover_FullLength_X, 
							   0.5 * TopCover_FullLength_Y, 
							   0.5 * TopCover_FullLength_Z);
  
  //**********************************************************************************
  // Define collimator logical and physical volumes

  CollimatorSupport_TopCover_Logical  = new G4LogicalVolume( CollimatorSupport_TopCover_Solid,
							      CollimatorSupport_Material,
							      "CollimatorSupport_TopCover_Log",
							      0,0,0);

    CollimatorSupport_TopCover_Physical   = new G4PVPlacement(0, 
							    positionCollimatorSupport_TopCover, 
							    "CollimatorSupport_TopCover", 
							    CollimatorSupport_TopCover_Logical,
							    MotherVolume, 
							    false, 
							    0,
		                                            pSurfChk);
  //**********************************************************************************

  //==============
  // Bottom Cover
  //==============
  G4ThreeVector positionCollimatorSupport_BottomCover(BottomCover_CenterXPosition,
						      BottomCover_CenterYPosition,
						      BottomCover_CenterZPosition);

   //**********************************************************************************
  //Construct collimator support Bottom Cover
  G4Box* CollimatorSupport_BottomCover_Solid    = new G4Box("CollimatorSupport_BottomCover_Sol",
							    0.5 * BottomCover_FullLength_X, 
							    0.5 * BottomCover_FullLength_Y, 
							    0.5 * BottomCover_FullLength_Z);

  //**********************************************************************************
  // Define collimator logical and physical volumes

  CollimatorSupport_BottomCover_Logical  = new G4LogicalVolume( CollimatorSupport_BottomCover_Solid,
								CollimatorSupport_Material,
								"CollimatorSupport_BottomCover_Log",
								0,0,0);
  
  CollimatorSupport_BottomCover_Physical   = new G4PVPlacement(0, 
							       positionCollimatorSupport_BottomCover, 
							       "CollimatorSupport_BottomCover", 
							       CollimatorSupport_BottomCover_Logical,
							       MotherVolume, 
							       false, 
							       0,
							       pSurfChk);
  //**********************************************************************************


  //==============
  // Left Cover
  //==============
  G4ThreeVector positionCollimatorSupport_LeftCover(LeftCover_CenterXPosition,
						    LeftCover_CenterYPosition,
						    LeftCover_CenterZPosition);
  
   //**********************************************************************************
  //Construct collimator support Left Cover
  G4Box* CollimatorSupport_LeftCover_Solid    = new G4Box("CollimatorSupport_LeftCover_Sol",
							  0.5 * LeftCover_FullLength_X, 
							  0.5 * LeftCover_FullLength_Y, 
							  0.5 * LeftCover_FullLength_Z);
  
  //**********************************************************************************
  // Define collimator logical and physical volumes

  CollimatorSupport_LeftCover_Logical  = new G4LogicalVolume( CollimatorSupport_LeftCover_Solid,
							      CollimatorSupport_Material,
							      "CollimatorSupport_LeftCover_Log",
							      0,0,0);
  
  CollimatorSupport_LeftCover_Physical   = new G4PVPlacement(0, 
							     positionCollimatorSupport_LeftCover, 
							     "CollimatorSupport_LeftCover", 
							     CollimatorSupport_LeftCover_Logical,
							     MotherVolume, 
							     false, 
							     0,
							     pSurfChk);
  //**********************************************************************************



  //==============
  // Right Cover
  //==============
  G4ThreeVector positionCollimatorSupport_RightCover(RightCover_CenterXPosition,
						     RightCover_CenterYPosition,
						     RightCover_CenterZPosition);

   //**********************************************************************************
  //Construct collimator support Right Cover
  G4Box* CollimatorSupport_RightCover_Solid    = new G4Box("CollimatorSupport_RightCover_Sol",
							    0.5 * RightCover_FullLength_X, 
							    0.5 * RightCover_FullLength_Y, 
							    0.5 * RightCover_FullLength_Z);

  //**********************************************************************************
  // Define collimator logical and physical volumes

  CollimatorSupport_RightCover_Logical  = new G4LogicalVolume( CollimatorSupport_RightCover_Solid,
							       CollimatorSupport_Material,
							       "CollimatorSupport_RightCover_Log",
							       0,0,0);
  
  CollimatorSupport_RightCover_Physical   = new G4PVPlacement(0, 
							      positionCollimatorSupport_RightCover, 
							      "CollimatorSupport_RightCover", 
							      CollimatorSupport_RightCover_Logical,
							      MotherVolume, 
							      false, 
							      0,
							      pSurfChk);
  //**********************************************************************************


  //**********************************************************************************
  //Make it pretty...
  G4Colour  blue      (0.,0.,1.);
  G4Colour  mangenta  (237/255.,173/255.,255/255.);
  G4Colour  mangenta1 (104/255., 49/255., 94/255.);

  //**********************************************************************************
  G4VisAttributes* CollimatorSupport_TopCover_VisAtt = new G4VisAttributes(blue);
  CollimatorSupport_TopCover_VisAtt->SetVisibility(false);
  //  CollimatorSupport_TopCover_VisAtt->SetForceSolid(true);
  //  CollimatorSupport_TopCover_VisAtt->SetForceWireframe(true);
  CollimatorSupport_TopCover_Logical->SetVisAttributes(CollimatorSupport_TopCover_VisAtt); 
  //**********************************************************************************
  G4VisAttributes* CollimatorSupport_BottomCover_VisAtt = new G4VisAttributes(blue);
  CollimatorSupport_BottomCover_VisAtt->SetVisibility(false);
  //  CollimatorSupport_BottomCover_VisAtt->SetForceSolid(true);
  //  CollimatorSupport_BottomCover_VisAtt->SetForceWireframe(true);
  CollimatorSupport_BottomCover_Logical->SetVisAttributes(CollimatorSupport_BottomCover_VisAtt); 
  //**********************************************************************************
  G4VisAttributes* CollimatorSupport_LeftCover_VisAtt = new G4VisAttributes(blue);
  CollimatorSupport_LeftCover_VisAtt->SetVisibility(false);
  //  CollimatorSupport_LeftCover_VisAtt->SetVisibility(true);
  //  CollimatorSupport_LeftCover_VisAtt->SetForceSolid(true);
  //  CollimatorSupport_LeftCover_VisAtt->SetForceWireframe(true);
  CollimatorSupport_LeftCover_Logical->SetVisAttributes(CollimatorSupport_LeftCover_VisAtt); 
  //**********************************************************************************
  G4VisAttributes* CollimatorSupport_RightCover_VisAtt = new G4VisAttributes(blue);
  // CollimatorSupport_RightCover_VisAtt->SetVisibility(false);
  CollimatorSupport_RightCover_VisAtt->SetVisibility(false);
  //  CollimatorSupport_RightCover_VisAtt->SetForceSolid(true);
  //  CollimatorSupport_RightCover_VisAtt->SetForceWireframe(true);
  CollimatorSupport_RightCover_Logical->SetVisAttributes(CollimatorSupport_RightCover_VisAtt); 
  //**********************************************************************************


  G4cout << G4endl << "###### Leaving QweakSimCollimatorSupport::ConstructSupport() " << G4endl << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCollimatorSupport::SetCollimatorSupportMaterial(G4String materialName)
{
//---------------------------------------------------------------------------------------------
//! Sets the material of the Collimator Support
 /*!	
	
 \param materialName Name of the material defined in class QweakSimG4Material
    
 */
//---------------------------------------------------------------------------------------------

  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
    CollimatorSupport_TopCover_Logical->SetMaterial(pttoMaterial);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimCollimatorSupport.cc,v $
//      Revision 1.2  2005/12/28 22:45:27  grimm
//      Completed all cover plates (Top, Bottom, Left, Right)
//      Plate dimensions and location are extracted dynamically from the upstream and downstream collimator positions and sizes.
//
//      Revision 1.1  2005/12/28 18:30:04  grimm
//      First Version of a support/shielding of the 3 collimators.
//      At present only a top cover is implemented with rather arbitrary size and position.
//
//     

