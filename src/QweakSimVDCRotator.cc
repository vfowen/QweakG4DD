//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**

 
   \file QweakSimVDCRotator.cc

   $Revision: 1.2 $	
   $Date: 2006/05/05 21:17:42 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:17:42 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimVDCRotator.hh"

// geant4 includes
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"

// user includes
#include "QweakSimMaterial.hh"
#include "QweakSimVDC.hh"
#include "QweakSimVDCMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// QweakSimVDCRotator::QweakSimVDCRotator(QweakSimVDC* theVDC)
// : DualVDC(theVDC)
 QweakSimVDCRotator::QweakSimVDCRotator()
{
    G4cout << G4endl << "###### Calling QweakSimVDCRotator::QweakCollimatorSupport() " << G4endl << G4endl;

    theMotherVolume = NULL;

  kAngle_GlobalRotation = 90.0*degree;

  // Upstream Ring
  UpstreamRing_Logical  = NULL;
  UpstreamRing_Physical = NULL;

  DownstreamRing_Logical  = NULL;
  DownstreamRing_Physical = NULL;

  kRing_RadiusMax      = 1168.0*mm;
  kRing_RadiusMin      = 1016.0*mm;
  kRing_FullThickness  =  2.0*2.54*cm;
  kRing_PhiAngleStart  =    0.0*degree;
  kRing_PhiAngleEnd    =  360.0*degree;

  UpstreamRing_CenterXPosition =  0.0*cm;
  UpstreamRing_CenterYPosition =  0.0*cm;
  UpstreamRing_CenterZPosition =  4310.36*mm;

  DownstreamRing_CenterXPosition =  0.0*cm;
  DownstreamRing_CenterYPosition =  0.0*cm;
  DownstreamRing_CenterZPosition =  5088.23*mm;

  //==========
  // Rails
  //==========

  Rail_Logical       = NULL;
  LeftRail_Physical  = NULL;
  RightRail_Physical = NULL;

  Rotation_Rail      = NULL;

  kRail_FullLength_X =   1.75*2.54*cm;
  kRail_FullLength_Y = 114.00*2.54*cm;
  kRail_FullLength_Z =   5.00*2.54*cm;

  kRail_CenterPositionInR = (49.1314*2.54*cm + 0.5*kRail_FullLength_X);
  kRail_CenterPositionInZ = 0.5*(DownstreamRing_CenterZPosition + UpstreamRing_CenterZPosition);



  //==================
  // Rods: Left/Right
  //==================

  Rod_LeftRight_Logical   = NULL;
  Rotation_Rod_LR         = NULL;
  
  kRod_LR_RadiusMin      = 0.0*cm;
  kRod_LR_RadiusMax      = 1.0220*2.54*cm;
  kRod_LR_FullThickness  = 2.8250*2.54*cm;
  kRod_LR_PhiAngleStart  =   0.0*degree;
  kRod_LR_PhiAngleEnd    = 360.0*degree;

  //----------------------
  // [0]: Upstream,Left    rod
  // [1]: Downstream,Left  rod
  // [2]: Upstream,Right   rod
  // [3]: Downstream,Right rod
   //----------------------
  kRod_LR_StubLength =  2.8250*2.54*cm;
  kRod_LR_Distance   = 12.5000*2.54*cm;

  kRod_LR_CenterPositionInX.clear(); 
  kRod_LR_CenterPositionInX.resize(4); 
  kRod_LR_CenterPositionInX[0] = -1.0*(61.0371*2.54*cm - 0.5*kRod_LR_StubLength); 
  kRod_LR_CenterPositionInX[1] = -1.0*(61.0371*2.54*cm - 0.5*kRod_LR_StubLength); 
  kRod_LR_CenterPositionInX[2] =  1.0*(61.0371*2.54*cm - 0.5*kRod_LR_StubLength); 
  kRod_LR_CenterPositionInX[3] =  1.0*(61.0371*2.54*cm - 0.5*kRod_LR_StubLength); 

  kRod_LR_CenterPositionInY.clear(); 
  kRod_LR_CenterPositionInY.resize(4); 
  kRod_LR_CenterPositionInY[0] = 111.7677*2.54*cm;
  kRod_LR_CenterPositionInY[1] = 111.7677*2.54*cm;
  kRod_LR_CenterPositionInY[2] = 111.7677*2.54*cm;
  kRod_LR_CenterPositionInY[3] = 111.7677*2.54*cm;

  kRod_LR_CenterPositionInZ.clear(); 
  kRod_LR_CenterPositionInZ.resize(4); 
  kRod_LR_CenterPositionInZ[0] = 178.8866*2.54*cm;
  kRod_LR_CenterPositionInZ[1] = 178.8866*2.54*cm + kRod_LR_Distance;
  kRod_LR_CenterPositionInZ[2] = 178.8866*2.54*cm;
  kRod_LR_CenterPositionInZ[3] = 178.8866*2.54*cm + kRod_LR_Distance;

  //----------------------
  // [0]: Upstream    rod
  // [1]: Downstream  rod
  //----------------------
  //
  Rod_LeftRight_Physical.clear();
  Rod_LeftRight_Physical.resize(4);


  //===============
  // Slider Support
  //===============
  kSliderSupport_FullLength_X =  203.20*mm;
  kSliderSupport_FullLength_Y = 1930.40*mm;
  kSliderSupport_FullLength_Z =  356.97*mm;

  kSliderSupport_CenterPositionInX = 1343.49*mm;
  kSliderSupport_CenterPositionInY = 1714.95*mm;
  kSliderSupport_CenterPositionInZ = 4699.29*mm;

  Rotation_SliderSupportLeft  = NULL;
  Rotation_SliderSupportRight = NULL;

  SliderSupportLeft_Logical   = NULL;
  SliderSupportLeft_Physical.clear();
  SliderSupportLeft_Physical.resize(2);

  SliderSupportRight_Logical  = NULL; 
  SliderSupportRight_Physical.clear();
  SliderSupportRight_Physical.resize(2);

  // needed for shaping
  SliderSupportSubtraction_TempSolid.clear();
  SliderSupportSubtraction_TempSolid.resize(16);


  //==================================
  // get access to material definition
  //==================================
  //
  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();

  G4cout << G4endl << "###### Leaving QweakSimVDCRotator::QweakCollimatorSupport() " << G4endl << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimVDCRotator::~QweakSimVDCRotator()
{
    G4cout << G4endl << "###### Calling QweakSimVDCRotator::~QweakCollimatorSupport() " << G4endl << G4endl;

    if (pMaterial)             delete pMaterial;

    G4cout << G4endl << "###### Calling QweakSimVDCRotator::~QweakCollimatorSupport() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDCRotator::ConstructRotatorMasterContainer()
{
    G4cout << G4endl << "###### Calling QweakSimVDCRotator::RotatorMasterContainer() " << G4endl << G4endl;
   
   G4Box* RotatorMasterContainer_Solid = new G4Box("RotatorMasterContainer_Solid",
				 0.5 * (6.6*m),
				 0.5 * (2.0*kRail_CenterPositionInR+50.0*cm),
				 0.5 * (kSliderSupport_FullLength_Z +2.0*cm ));
   
   G4LogicalVolume* RotatorMasterContainer_Logical  = new G4LogicalVolume(  RotatorMasterContainer_Solid,
					 pMaterial->GetMaterial("Air"),
					 "RotatorMasterContainer_Logical",
					 0,
					 0,0);

  G4Colour  aluminum      ( 169/255. , 172/255. , 182/255.);
  G4VisAttributes* RotatorMasterContainer_VisAtt = new G4VisAttributes(aluminum);
  RotatorMasterContainer_VisAtt->SetForceWireframe(true);
  RotatorMasterContainer_VisAtt->SetVisibility(false);
  RotatorMasterContainer_Logical->SetVisAttributes(RotatorMasterContainer_VisAtt); 

  // Place the physical volume into theMotherVolume

   G4ThreeVector Translation_RotatorMasterContainer;
   Translation_RotatorMasterContainer.setZ(kRail_CenterPositionInZ);

   G4RotationMatrix* Rotation_RotatorMasterContainer = new G4RotationMatrix();
   Rotation_RotatorMasterContainer->rotateZ(kAngle_GlobalRotation);
   
   RotatorMasterContainer_Physical   = new G4PVPlacement(Rotation_RotatorMasterContainer,
					   Translation_RotatorMasterContainer,
					   "RotatorMasterContainer_Physical",
					   RotatorMasterContainer_Logical,
					   theMotherVolume,
					   false,
					   0,
					   pSurfChk);
   
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDCRotator::ConstructRings()
{
    G4cout << G4endl << "###### Calling QweakSimVDCRotator::ConstructSupport() " << G4endl << G4endl;

  // assign material
  G4Material* Ring_Material = pMaterial->GetMaterial("StainlessSteel"); 


  //===============
  // Upstream Ring
  //===============
  G4ThreeVector positionUpstreamRing(UpstreamRing_CenterXPosition,
				     UpstreamRing_CenterYPosition,
				     UpstreamRing_CenterZPosition);

  //**********************************************************************************
  //Construct 
  G4Tubs* UpstreamRing_Solid    = new G4Tubs("UpstreamRing_Sol",
					         kRing_RadiusMin ,
					         kRing_RadiusMax ,
					     0.5*kRing_FullThickness,
					         kRing_PhiAngleStart,
					         kRing_PhiAngleEnd
					   ); 

  //**********************************************************************************
  // Define UpstreamRing logical and physical volumes

  UpstreamRing_Logical  = new G4LogicalVolume( UpstreamRing_Solid,
					       Ring_Material,
					       "UpstreamRing_Log",
					       0,0,0);

  UpstreamRing_Physical   = new G4PVPlacement(0, 
					      positionUpstreamRing, 
					      "UpstreamRing", 
					      UpstreamRing_Logical,
					      theMotherVolume, 
					      false, 
					      0,
					      pSurfChk);

  //**********************************************************************************

  //===============
  // Downstream Ring
  //===============
  G4ThreeVector positionDownstreamRing(DownstreamRing_CenterXPosition,
				       DownstreamRing_CenterYPosition,
				       DownstreamRing_CenterZPosition);

  //**********************************************************************************
  //Construct 
  G4Tubs* DownstreamRing_Solid    = new G4Tubs("DownstreamRing_Sol",
					         kRing_RadiusMin ,
					         kRing_RadiusMax ,
					     0.5*kRing_FullThickness,
					         kRing_PhiAngleStart,
					         kRing_PhiAngleEnd
					   ); 

  //**********************************************************************************
  // Define DownsreamRing logical and physical volumes

  DownstreamRing_Logical  = new G4LogicalVolume( DownstreamRing_Solid,
						 Ring_Material,
						 "DownstreamRing_Log",
						 0,0,0);
  
  DownstreamRing_Physical   = new G4PVPlacement(0, 
						positionDownstreamRing, 
						"UpstreamRing", 
						DownstreamRing_Logical,
						theMotherVolume, 
						false, 
						0,
						pSurfChk);

  //Make it pretty...
  G4Colour  blue      (0.,0.,1.);
  G4Colour  mangenta  (237/255.,173/255.,255/255.);
  G4Colour  mangenta1 (104/255., 49/255., 94/255.);
  G4Colour  aluminum      ( 169/255. , 172/255. , 182/255.);
  G4Color   lightsteelblue ( 176/255. , 196/255. , 222/255.);

   //**********************************************************************************
  G4VisAttributes* Ring_VisAtt = new G4VisAttributes(aluminum);
  Ring_VisAtt->SetVisibility(true);
  //  Ring_VisAtt->SetForceSolid(true);
  //  Ring_VisAtt->SetForceWireframe(true);
  UpstreamRing_Logical   ->SetVisAttributes(Ring_VisAtt); 
  DownstreamRing_Logical ->SetVisAttributes(Ring_VisAtt); 
  //**********************************************************************************


  G4cout << G4endl << "###### Leaving QweakSimVDCRotator::ConstructSupport() " << G4endl << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDCRotator::ConstructRails()
{
    G4cout << G4endl << "###### Calling QweakSimVDCRotator::ConstructRails() " << G4endl << G4endl;

   // assign material
   G4Material* Rail_Material = pMaterial->GetMaterial("StainlessSteel"); 

   
   G4Box* Rail_Solid = new G4Box("Rail_Solid",
				 0.5 * kRail_FullLength_X , 
				 0.5 * kRail_FullLength_Y , 
				 0.5 * kRail_FullLength_Z );


   Rail_Logical  = new G4LogicalVolume(  Rail_Solid,
					 Rail_Material,
					 "Rail_Logical",
					 0,
					 0,0);

      //Make it pretty...
  G4Colour  blue      (0.,0.,1.);
  G4Colour  mangenta  (237/255.,173/255.,255/255.);
  G4Colour  mangenta1 (104/255., 49/255., 94/255.);
  G4Colour  aluminum      ( 169/255. , 172/255. , 182/255.);
  G4Color   lightsteelblue ( 176/255. , 196/255. , 222/255.);
  //**********************************************************************************
  G4VisAttributes* Rails_VisAtt = new G4VisAttributes(blue);
  Rails_VisAtt->SetVisibility(true);
  //  Rails_VisAtt->SetForceSolid(true);
  //  Ring_VisAtt->SetForceWireframe(true);
  Rail_Logical   ->SetVisAttributes(Rails_VisAtt); 
  //**********************************************************************************

  // Place the physical volume of the rails into theMotherVolume
  PlacePVRails();

} // end of ConstructRails()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDCRotator::PlacePVRails()
{

   G4ThreeVector* CenterRailLeft  = new G4ThreeVector();
   G4ThreeVector* CenterRailRight = new G4ThreeVector();

   CenterRailLeft->setX(-1.0*kRail_CenterPositionInR);    
   CenterRailLeft->setY(0.0*cm);    
   CenterRailLeft->setZ(0.0*cm);    
   
   CenterRailRight->setX(1.0*kRail_CenterPositionInR);
   CenterRailRight->setY(0.0*cm);
   CenterRailRight->setZ(0.0*cm);

   // rotate center vectors of rails
   // CenterRailLeft  ->rotateZ(kAngle_GlobalRotation);
   // CenterRailRight ->rotateZ(kAngle_GlobalRotation);

   Translation_LeftRail.setX( CenterRailLeft->y() );
   Translation_LeftRail.setY( CenterRailLeft->x() );
   //Translation_LeftRail.setZ(kRail_CenterPositionInZ);
   
   Translation_RightRail.setX( CenterRailRight->y() );
   Translation_RightRail.setY( CenterRailRight->x() );
   //Translation_RightRail.setZ(kRail_CenterPositionInZ);
   
   // since the SingleCoil_ClampPlate_Logical is defined for a vertical orientation
   // but the translation assumes a horizontal orinetation, we have to subtract 90*deg
   Rotation_Rail = new G4RotationMatrix();
   //Rotation_Rail->rotateZ(kAngle_GlobalRotation -90*degree);
   Rotation_Rail->rotateZ( -90*degree);
   

   LeftRail_Physical   = new G4PVPlacement(Rotation_Rail,
					   Translation_LeftRail,
					   "LeftRail_Physical",
					   Rail_Logical,
					   RotatorMasterContainer_Physical,
					   false,
					   0,
					   pSurfChk);

   RightRail_Physical   = new G4PVPlacement(Rotation_Rail,
					    Translation_RightRail,
					    "RightRail_Physical",
					    Rail_Logical,
					    RotatorMasterContainer_Physical,
					    false,
					    0,
					    pSurfChk);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDCRotator::ConstructMount()
{

   G4cout << G4endl << "###### Calling QweakSimVDCRotator::ConstructMount() " << G4endl << G4endl;

   // assign material
   G4Material* Rod_LeftRight_Material = pMaterial->GetMaterial("StainlessSteel"); 


     
  //**********************************************************************************
  //Construct 
  G4Tubs* Rod_LeftRight_Solid    = new G4Tubs("Rod_LR_Sol",
					         kRod_LR_RadiusMin ,
					         kRod_LR_RadiusMax ,
					     0.5*kRod_LR_FullThickness,
					         kRod_LR_PhiAngleStart,
					         kRod_LR_PhiAngleEnd
					   ); 

  //**********************************************************************************
  // Define UpstreamRing logical and physical volumes

  Rod_LeftRight_Logical  = new G4LogicalVolume(  Rod_LeftRight_Solid,
						 Rod_LeftRight_Material,
						 "Rod_LeftRight_Logical",
						 0,
						 0,0);

  //**********************************************************************************

  //Make it pretty...
  G4Colour  blue      (0.,0.,1.);
  G4Colour  mangenta  (237/255.,173/255.,255/255.);
  G4Colour  mangenta1 (104/255., 49/255., 94/255.);
  G4Colour  aluminum      ( 169/255. , 172/255. , 182/255.);
  G4Color   lightsteelblue ( 176/255. , 196/255. , 222/255.);
  //**********************************************************************************
  G4VisAttributes* Rod_LeftRight_VisAtt = new G4VisAttributes(mangenta);
  Rod_LeftRight_VisAtt  ->SetVisibility(true);
  Rod_LeftRight_Logical ->SetVisAttributes(Rod_LeftRight_VisAtt); 
  //**********************************************************************************

  // Place the physical volume(s) into the MotherVolume
  PlacePVMount();

} // end of ConstructMount()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDCRotator::PlacePVMount()
{

  G4ThreeVector* CenterRodLeftUpstream    = new G4ThreeVector();
  G4ThreeVector* CenterRodLeftDownstream  = new G4ThreeVector();

  G4ThreeVector* CenterRodRightUpstream    = new G4ThreeVector();
  G4ThreeVector* CenterRodRightDownstream  = new G4ThreeVector();
 

  CenterRodLeftUpstream->setX(kRod_LR_CenterPositionInX[0]);
  CenterRodLeftUpstream->setY(kRod_LR_CenterPositionInY[0]);
  //CenterRodLeftUpstream->setZ(kRod_LR_CenterPositionInZ[0]);
  //
  CenterRodLeftDownstream->setX(kRod_LR_CenterPositionInX[1]);
  CenterRodLeftDownstream->setY(kRod_LR_CenterPositionInY[1]);
  //CenterRodLeftDownstream->setZ(kRod_LR_CenterPositionInZ[1]);


  CenterRodRightUpstream->setX(kRod_LR_CenterPositionInX[2]);
  CenterRodRightUpstream->setY(kRod_LR_CenterPositionInY[2]);
  //CenterRodRightUpstream->setZ(kRod_LR_CenterPositionInZ[2]);
  //
  CenterRodRightDownstream->setX(kRod_LR_CenterPositionInX[3]);
  CenterRodRightDownstream->setY(kRod_LR_CenterPositionInY[3]);
  //CenterRodRightDownstream->setZ(kRod_LR_CenterPositionInZ[3]);



   // rotate center vectors of rails
//   CenterRodLeftUpstream    ->rotateZ(kAngle_GlobalRotation);
//   CenterRodLeftDownstream  ->rotateZ(kAngle_GlobalRotation);
//   CenterRodRightUpstream   ->rotateZ(kAngle_GlobalRotation);
//   CenterRodRightDownstream ->rotateZ(kAngle_GlobalRotation);


  Translation_RodLeftUpstream.setX( CenterRodLeftUpstream->y() );
  Translation_RodLeftUpstream.setY( CenterRodLeftUpstream->x() );
  //Translation_RodLeftUpstream.setZ( CenterRodLeftUpstream->z() );
  //
  Translation_RodLeftDownstream.setX( CenterRodLeftDownstream->y() );
  Translation_RodLeftDownstream.setY( CenterRodLeftDownstream->x() );
  //Translation_RodLeftDownstream.setZ( CenterRodLeftDownstream->z() );


  Translation_RodRightUpstream.setX( CenterRodRightUpstream->y() );
  Translation_RodRightUpstream.setY( CenterRodRightUpstream->x() );
  //Translation_RodRightUpstream.setZ( CenterRodRightUpstream->z() );
  //
  Translation_RodRightDownstream.setX( CenterRodRightDownstream->y() );
  Translation_RodRightDownstream.setY( CenterRodRightDownstream->x() );
  //Translation_RodRightDownstream.setZ( CenterRodRightDownstream->z() );

 

  Rotation_Rod_LR = new G4RotationMatrix();
  Rotation_Rod_LR->rotateY(90*degree);
  //Rotation_Rod_LR->rotateX(kAngle_GlobalRotation -90*degree);
  Rotation_Rod_LR->rotateX(-90*degree);
 

  
  Rod_LeftRight_Physical[0]   = new G4PVPlacement(Rotation_Rod_LR,
						   Translation_RodLeftUpstream,
						   "RodLR_LeftUpstream_Physical",
						   Rod_LeftRight_Logical,
						   RotatorMasterContainer_Physical,
						   false,
						   0,
						   pSurfChk);

  Rod_LeftRight_Physical[1]   = new G4PVPlacement(Rotation_Rod_LR,
						    Translation_RodRightUpstream,
						    "RodLR_RightUpstream_Physical",
						    Rod_LeftRight_Logical,
						    RotatorMasterContainer_Physical,
						    false,
						    0,
						    pSurfChk);

  Rod_LeftRight_Physical[2]   = new G4PVPlacement(Rotation_Rod_LR,
						    Translation_RodLeftDownstream,
						    "RodLR_LeftDownstream_Physical",
						    Rod_LeftRight_Logical,
						    RotatorMasterContainer_Physical,
						    false,
						    0,
						    pSurfChk);
  
  Rod_LeftRight_Physical[3]   = new G4PVPlacement(Rotation_Rod_LR,
						    Translation_RodRightDownstream,
						    "RodLR_RightDownstream_Physical",
						    Rod_LeftRight_Logical,
						    RotatorMasterContainer_Physical,
						    false,
						    0,
						    pSurfChk);

}  // end of PlacePVMount()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDCRotator::ConstructSliderSupport()
{
   G4cout << G4endl << "###### Calling QweakSimVDCRotator::ConstructSliderSupport() " << G4endl << G4endl;

   // assign material
   G4Material* SliderSupport_Material = pMaterial->GetMaterial("StainlessSteel");


   G4Box* SliderSupportLeft_Solid = new G4Box("SliderSupportLeft_Solid",
					      0.5 * kSliderSupport_FullLength_X , 
					      0.5 * kSliderSupport_FullLength_Y , 
					      0.5 * kSliderSupport_FullLength_Z );

   G4Box* SliderSupportRight_Solid = new G4Box("SliderSupportRight_Solid",
					      0.5 * kSliderSupport_FullLength_X , 
					      0.5 * kSliderSupport_FullLength_Y , 
					      0.5 * kSliderSupport_FullLength_Z );


   //-------------------------------------------------------------------------------------------------------------------------------
 
   G4Box* SubtractInnerBox_Solid  = new G4Box("SubtractInnerBox_Solid",
					      0.5 * 2*4.00*2.54*cm, 
					      0.5 * kSliderSupport_FullLength_Y +0.1*mm,  
					      0.5 * 3.50*2.54*cm);


   std::vector< G4ThreeVector >  LocalTranslation_InnerBox_Subtract;
   LocalTranslation_InnerBox_Subtract.clear();
   LocalTranslation_InnerBox_Subtract.resize(4);

   // Left Slider: Upstream Inner Box 
   LocalTranslation_InnerBox_Subtract[0].setX(-1.0*(0.5*203.20*mm));
   LocalTranslation_InnerBox_Subtract[0].setY(0.0*cm);
   LocalTranslation_InnerBox_Subtract[0].setZ(-1.0*(1.0+0.5*3.50)*2.54*cm);

   // Left Slider: Downstream Inner Box 
   LocalTranslation_InnerBox_Subtract[1].setX(-1.0*(0.5*203.20*mm));
   LocalTranslation_InnerBox_Subtract[1].setY(0.0*cm);
   LocalTranslation_InnerBox_Subtract[1].setZ(+1.0*(1.0+0.5*3.50)*2.54*cm);


   // Right Slider: Upstream Inner Box 
   LocalTranslation_InnerBox_Subtract[2].setX(+1.0*(0.5*203.20*mm));
   LocalTranslation_InnerBox_Subtract[2].setY(0.0*cm);
   LocalTranslation_InnerBox_Subtract[2].setZ(-1.0*(1.0+0.5*3.50)*2.54*cm);
   
   // Right Slider: Downstream Inner Box 
   LocalTranslation_InnerBox_Subtract[3].setX(+1.0*(0.5*203.20*mm));
   LocalTranslation_InnerBox_Subtract[3].setY(0.0*cm);
   LocalTranslation_InnerBox_Subtract[3].setZ(+1.0*(1.0+0.5*3.50)*2.54*cm);

   
   // dummy rotation matrix
   G4RotationMatrix LocalRotation_InnerBox_Subtraction;

   G4Transform3D    Transform3D_InnerUpstreamSubtraction_LeftSlider(LocalRotation_InnerBox_Subtraction, LocalTranslation_InnerBox_Subtract[0] );
   //
   SliderSupportSubtraction_TempSolid[4] =  new G4SubtractionSolid ("SliderLeft-InnerUpstreamBox",
								    SliderSupportLeft_Solid, 
								    //SliderSupportSubtraction_TempSolid[1],
								    SubtractInnerBox_Solid, 
								    Transform3D_InnerUpstreamSubtraction_LeftSlider); 

   G4Transform3D    Transform3D_InnerUpstreamSubtraction_RightSlider(LocalRotation_InnerBox_Subtraction, LocalTranslation_InnerBox_Subtract[2] );
   //
   SliderSupportSubtraction_TempSolid[5] =  new G4SubtractionSolid ("SliderRight-InnerUpstreamBox",
								    SliderSupportRight_Solid, 
								    //SliderSupportSubtraction_TempSolid[1],
								    SubtractInnerBox_Solid, 
								    Transform3D_InnerUpstreamSubtraction_RightSlider); 


   G4Transform3D    Transform3D_InnerDownstreamSubtraction_LeftSlider(LocalRotation_InnerBox_Subtraction, LocalTranslation_InnerBox_Subtract[1] );
   //
   SliderSupportSubtraction_TempSolid[6] =  new G4SubtractionSolid ("SliderLeft-InnerDownstreamBox",
								    SliderSupportSubtraction_TempSolid[4],
								    SubtractInnerBox_Solid, 
								    Transform3D_InnerDownstreamSubtraction_LeftSlider); 

   G4Transform3D    Transform3D_InnerDownstreamSubtraction_RightSlider(LocalRotation_InnerBox_Subtraction, LocalTranslation_InnerBox_Subtract[3] );
   //
   SliderSupportSubtraction_TempSolid[7] =  new G4SubtractionSolid ("SliderRight-InnerDownstreamBox",
								    SliderSupportSubtraction_TempSolid[5],
								    SubtractInnerBox_Solid, 
								    Transform3D_InnerDownstreamSubtraction_RightSlider); 


  //-------------------------------------------------------------------------------------------------------------------------------
   G4Box* SubtractBottomBox_Solid  = new G4Box("SubtractBottomBox_Solid",
					       0.5 * 2*3.25*2.54*cm, 
					       0.5 * kSliderSupport_FullLength_Y +0.1*mm,  
					       0.5 * 9.00*2.54*cm);


   std::vector< G4ThreeVector >  LocalTranslation_BottomBox_Subtract;
   LocalTranslation_BottomBox_Subtract.clear();
   LocalTranslation_BottomBox_Subtract.resize(2);

   // Left Slider: Bottom Box 
   LocalTranslation_BottomBox_Subtract[0].setX(+1.0*(0.5*203.20*mm));
   LocalTranslation_BottomBox_Subtract[0].setY(0.0*cm);
   LocalTranslation_BottomBox_Subtract[0].setZ(0.0*cm);

   // Right Slider: Bottom Box 
   LocalTranslation_BottomBox_Subtract[1].setX(-1.0*(0.5*203.20*mm));
   LocalTranslation_BottomBox_Subtract[1].setY(0.0*cm);
   LocalTranslation_BottomBox_Subtract[1].setZ(0.0*cm);
   

   
   // dummy rotation matrix
   G4RotationMatrix LocalRotation_BottomBox_Subtraction;

   G4Transform3D    Transform3D_BottomSubtraction_LeftSlider(LocalRotation_BottomBox_Subtraction, LocalTranslation_BottomBox_Subtract[0] );
   //
   SliderSupportSubtraction_TempSolid[8] =  new G4SubtractionSolid ("SliderLeft-BottomBox",
								    //SliderSupportLeft_Solid, 
								    SliderSupportSubtraction_TempSolid[6],
								    SubtractBottomBox_Solid, 
								    Transform3D_BottomSubtraction_LeftSlider); 
   
   G4Transform3D    Transform3D_BottomSubtraction_RightSlider(LocalRotation_BottomBox_Subtraction, LocalTranslation_BottomBox_Subtract[1] );
   //
   SliderSupportSubtraction_TempSolid[9] =  new G4SubtractionSolid ("SliderRight-BottomBox",
								    //SliderSupportRight_Solid, 
								    SliderSupportSubtraction_TempSolid[7],
								    SubtractBottomBox_Solid, 
								    Transform3D_BottomSubtraction_RightSlider); 
   //-------------------------------------------------------------------------------------------------------------------------------
  G4Box* SubtractOuterBox_Solid  = new G4Box("SubtractOuterBox_Solid",
					      0.5 * 6.82*2.54*cm + 0.1*mm, 
					      0.5 * kSliderSupport_FullLength_Y +0.1*mm,  
					      0.5 * (2*1.937)*2.54*cm);


   std::vector< G4ThreeVector >  LocalTranslation_OuterBox_Subtract;
   LocalTranslation_OuterBox_Subtract.clear();
   LocalTranslation_OuterBox_Subtract.resize(2);

   // Upstream Outer Box 
   LocalTranslation_OuterBox_Subtract[0].setX(0.0*cm);
   LocalTranslation_OuterBox_Subtract[0].setY(0.0*cm);
   LocalTranslation_OuterBox_Subtract[0].setZ(-1.0*(4.50+2.527)*2.54*cm);
   
   // Downstream Outer Box 
   LocalTranslation_OuterBox_Subtract[1].setX(0.0*cm);
   LocalTranslation_OuterBox_Subtract[1].setY(0.0*cm);
   LocalTranslation_OuterBox_Subtract[1].setZ(+1.0*(4.50+2.527)*2.54*cm);

   
   // dummy rotation matrix
   G4RotationMatrix LocalRotation_OuterBox_Subtraction;

   G4Transform3D    Transform3D_OuterUpstreamSubtraction(LocalRotation_OuterBox_Subtraction, LocalTranslation_OuterBox_Subtract[0] );
   
   SliderSupportSubtraction_TempSolid[0] =  new G4SubtractionSolid ("SliderLeft-OuterUpstreamBox",
								    //SliderSupportLeft_Solid,
								    SliderSupportSubtraction_TempSolid[8],
								    SubtractOuterBox_Solid, 
								    Transform3D_OuterUpstreamSubtraction); 

   SliderSupportSubtraction_TempSolid[1] =  new G4SubtractionSolid ("SliderRight-OuterUpstreamBox",
								     //SliderSupportRight_Solid,
								     SliderSupportSubtraction_TempSolid[9],
								     SubtractOuterBox_Solid, 
								     Transform3D_OuterUpstreamSubtraction); 
    
   G4Transform3D    Transform3D_OuterDownstreamSubtraction(LocalRotation_OuterBox_Subtraction, LocalTranslation_OuterBox_Subtract[1] );
   
   SliderSupportSubtraction_TempSolid[2] =  new G4SubtractionSolid ("SliderLeft-OuterDownstreamBox",
								    SliderSupportSubtraction_TempSolid[0],
								    SubtractOuterBox_Solid, 
								    Transform3D_OuterDownstreamSubtraction);
   
   SliderSupportSubtraction_TempSolid[3] =  new G4SubtractionSolid ("SliderRight-OuterDownstreamBox",
								    SliderSupportSubtraction_TempSolid[1],
								    SubtractOuterBox_Solid, 
								    Transform3D_OuterDownstreamSubtraction);
   

   //-------------------------------------------------------------------------------------------------------------------------------



   //==================================================================================================
   //                       Define final SliderSupport logical volume
   //==================================================================================================
    G4cout << G4endl << "###### QweakSimVDCRotator: Define SliderSupport_Logical " << G4endl << G4endl;
    
    SliderSupportLeft_Logical  = new G4LogicalVolume(  SliderSupportSubtraction_TempSolid[2],
						       SliderSupport_Material,
						       "SliderSupportLeft_Logical",
						       0,
						       0,0);

    SliderSupportRight_Logical  = new G4LogicalVolume(  SliderSupportSubtraction_TempSolid[3],
							SliderSupport_Material,
							"SliderSupportRight_Logical",
							0,
							0,0);
    //==================================================================================================

    //Make it pretty...
    G4Colour  blue      (0.,0.,1.);
    G4Colour  mangenta  (237/255.,173/255.,255/255.);
    G4Colour  mangenta1 (104/255., 49/255., 94/255.);
    G4Colour  aluminum      ( 169/255. , 172/255. , 182/255.);
    G4Color   lightsteelblue ( 176/255. , 196/255. , 222/255.);
    //**********************************************************************************
    G4VisAttributes* SliderSupport_VisAtt = new G4VisAttributes(lightsteelblue);
    SliderSupport_VisAtt       ->SetVisibility(true);
    SliderSupportLeft_Logical  ->SetVisAttributes(SliderSupport_VisAtt); 
    SliderSupportRight_Logical ->SetVisAttributes(SliderSupport_VisAtt); 
    //**********************************************************************************

    PlacePVSliderSupport(1);
    PlacePVSliderSupport(2);

} // end of ConstructSliderSupport()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// pkg = 1 or pkg = 2

void QweakSimVDCRotator::PlacePVSliderSupport(int pkg)
{

   G4ThreeVector* leftcenter  = new G4ThreeVector();
   G4ThreeVector* rightcenter = new G4ThreeVector();

   
   // set the vectors to the center of left and right slider support
   // located at 12 o'clock. Then rotate these vectors to the final 
   // positions and extract the new vector components
   // This procedure is easier than the calculation by hand 


     leftcenter->setX(-1.0*kSliderSupport_CenterPositionInX);    
     leftcenter->setY(     kSliderSupport_CenterPositionInY);    
     //leftcenter->setZ(     kSliderSupport_CenterPositionInZ);

     rightcenter->setX(    kSliderSupport_CenterPositionInX);
     rightcenter->setY(    kSliderSupport_CenterPositionInY);
     //rightcenter->setZ(    kSliderSupport_CenterPositionInZ);

     // rotate center vector to coils
     //leftcenter  ->rotateZ(kAngle_GlobalRotation);
     //rightcenter ->rotateZ(kAngle_GlobalRotation);


     double reverser = 1.0;
     if(pkg == 2)
       reverser = -1.0;
     
     Translation_LeftSliderSupport.setX( reverser*leftcenter->y() );
     Translation_LeftSliderSupport.setY( reverser*leftcenter->x() );
     //Translation_LeftSliderSupport.setZ( leftcenter->z() );

     Translation_RightSliderSupport.setX( reverser*rightcenter->y() );
     Translation_RightSliderSupport.setY( reverser*rightcenter->x() );
     //Translation_RightSliderSupport.setZ( rightcenter->z() );


     // since the SingleCoil_ClampPlate_Logical is defined for a vertical orientation
     // but the translation assumes a horizontal orinetation, we have to subtract 90*deg
     Rotation_SliderSupportLeft = new G4RotationMatrix();
     //Rotation_SliderSupportLeft->rotateZ(kAngle_GlobalRotation -90*degree + (pkg-1)*180.0*degree);
     Rotation_SliderSupportLeft->rotateZ( -90*degree + (pkg-1)*180.0*degree);

     Rotation_SliderSupportRight = new G4RotationMatrix();
     //Rotation_SliderSupportRight->rotateZ(kAngle_GlobalRotation -90*degree + (pkg-1)*180.0*degree);
     Rotation_SliderSupportRight->rotateZ( -90*degree + (pkg-1)*180.0*degree);


     //place sliders for package 1, 2

     SliderSupportLeft_Physical.at(pkg-1)   = new G4PVPlacement(Rotation_SliderSupportLeft,
						      Translation_LeftSliderSupport,
						      Form("SliderSupportLeft_Pkg%d_Physical",pkg),
						      SliderSupportLeft_Logical,
						      RotatorMasterContainer_Physical,
						      false,
						      0,
						      pSurfChk);
   
     SliderSupportRight_Physical.at(pkg-1)   = new G4PVPlacement(Rotation_SliderSupportRight,
						       Translation_RightSliderSupport,
						       Form("SliderSupportRight_Pkg%d_Physical",pkg),
						       SliderSupportRight_Logical,
						       RotatorMasterContainer_Physical,
						       false,
						       0,
						       pSurfChk);

}  // end of PlacePV_SliderSupport()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDCRotator::SetRingMaterial(G4String materialName)
{
//---------------------------------------------------------------------------------------------
//! Sets the material of the skider rings
 /*!	
	
 \param materialName Name of the material defined in class QweakSimG4Material
    
 */
//---------------------------------------------------------------------------------------------

  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  

  if (pttoMaterial) 
      {
      UpstreamRing_Logical   ->SetMaterial(pttoMaterial);
      DownstreamRing_Logical ->SetMaterial(pttoMaterial);
  }
}		

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDCRotator::SetRotationAngleInPhi(G4double vdc_phiangle)
{
    G4cout << G4endl << "###### Calling QweakSimVDCRotator::SetRotationAngleInPhi() " << G4endl << G4endl;

    kAngle_GlobalRotation = vdc_phiangle -90.0*degree;
 
 G4RotationMatrix* Rotation_RotatorMasterContainer = new G4RotationMatrix();
 Rotation_RotatorMasterContainer->setPhi(vdc_phiangle);
 RotatorMasterContainer_Physical->SetRotation(Rotation_RotatorMasterContainer);
 
}	
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDCRotator.cc,v $
//      Revision 1.2  2006/05/05 21:17:42  grimm
//      - The orientation of the rod for Left/Right alignment works now for all Phi angles
//      - More realistic G0 slider : subtraction of solids for building slider profile
//
//      Revision 1.1  2006/05/02 00:47:21  grimm
//      Initial Implementation of the VDC Rotator based on the design of Paulo Medeiros.
//

