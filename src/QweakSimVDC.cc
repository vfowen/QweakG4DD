
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimVDC.cc

   $Revision: 1.7 $	
   $Date: 2006/05/05 21:48:53 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimVDC.hh"

// geant4 includes
#include "G4PVParameterised.hh"
#include "G4ProductionCuts.hh"
#include "G4RunManager.hh"

// root includes
#include "TMath.h"

// user includes
#include "QweakSimVDCMessenger.hh"
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimVDC_DriftCellFrontSD.hh"
#include "QweakSimVDC_DriftCellBackSD.hh"
#include "QweakSimVDC_DriftCellParameterisation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimVDC::QweakSimVDC()
{
  G4cout << G4endl << "###### Calling QweakSimVDC::QweakVDC() " << G4endl << G4endl;

  //===============================
  // cuts for G4Region and PAIModel
  //===============================
  fGammaCut    = 1*mm;
  fElectronCut = 1*mm;
  fPositronCut = 1*mm;

  fRegGasDet = NULL;

  //========================		
  //  DriftCell Array setup	
  //=======================	

 VDC_DriftCellMasterContainer_Logical  = NULL;
 //VDC_DriftCellMasterContainer_Physical = NULL;

 VDC_DriftCellFrontContainer_Logical  = NULL;
 VDC_DriftCellFrontContainer_Physical = NULL;

 VDC_DriftCellBackContainer_Logical  = NULL;
 VDC_DriftCellBackContainer_Physical = NULL;

 VDC_DriftCellFront_Solid    = NULL;
 VDC_DriftCellFront_Logical  = NULL;
 VDC_DriftCellFront_Physical = NULL;

 VDC_DriftCellBack_Solid    = NULL;  
 VDC_DriftCellBack_Logical  = NULL; 
 VDC_DriftCellBack_Physical = NULL;

 VDC_DriftCellFrontContainer_VisAtt = NULL;
 VDC_DriftCellBackContainer_VisAtt  = NULL;
 VDC_DriftCellFront_VisAtt          = NULL;
 VDC_DriftCellBack_VisAtt           = NULL;


//QweakSimVDC_DriftCellSD::SetNumberOfDriftCellsPerPlane(401);

  // define target geometry values
  G10Frame_Thickness        =   0.5*2.54*cm;
  G10Frame_BorderWidthInX   =  15.0*cm;
  G10Frame_BorderWidthInY   =  15.0*cm;
  G10Frame_InnerLength      = 210.0*cm; // 78 inch 
  G10Frame_InnerWidth       =  50.0*cm; // 18 inch

  G10Frame_OuterLength      = G10Frame_InnerLength + G10Frame_BorderWidthInX; 
  G10Frame_OuterWidth       = G10Frame_InnerWidth  + G10Frame_BorderWidthInY; 


  AluFrame_Thickness        =   0.5*2.54*cm; 
  AluFrame_OuterLength      = 240.0*cm; // to be checked with SW 
  AluFrame_OuterWidth       = 120.0*cm; // to be checked with SW 
  AluFrame_InnerLength      = 210.0*cm; 
  AluFrame_InnerWidth       =  50.0*cm; 

  VDC_CenterFront_XPos.resize(2,0);
  VDC_CenterFront_YPos.resize(2,0);
  VDC_CenterFront_ZPos.resize(2,0);
  VDC_CenterBack_XPos.resize(2,0);
  VDC_CenterBack_YPos.resize(2,0);
  VDC_CenterBack_ZPos.resize(2,0);

  for(int i = 0; i < 2; i++){//temp loop to assign values for package 2. Although same as package 1, will be rotated to different octant.
  VDC_CenterFront_XPos[i]        =   0.0*cm;
  VDC_CenterFront_YPos[i]        = 276.165*cm; // 280.0*cm;  // SW for 20.75 deg
  VDC_CenterFront_ZPos[i]        = 443.920*cm; //480.0*cm;   // SW: 330.0 +107.0
  //VDC_CenterFront_ZPos        = -700*cm;   // for testing

  VDC_FrontBackDistance       = 53.18*cm; // center to center
  // updated 2012-04-09 by wdconinc based on qwanalysis geometry
  SetVDC_BackVDC_CenterPosition(i);
  }
  MeanTrackAngle             =  24.43*degree;  //20.57*degree;  // also tilting angle of VDcs  // 
  VDC_RotationAngleInPhi[0]     =   0.0*degree;   // normally 0.0*degree = 12 o'clock = octant 1
  VDC_RotationAngleInPhi[1]     =  90*degree; //VDC_RotationAngleInPhi[0] + 180.0*degree;
  



  // How many drift cells per plane
  DriftCell_NumberPerPlane   =   341;
  DriftCell_FullWidthOnFrame =  11.1125*mm;
  DriftCell_FullHeight       =  70.0*cm;
  DriftCell_FullThickness    =   2.54*cm; 
  DriftCell_WireAngleFront   =  65.57; // 63.43*degree; // (90-26.57)*degree
  DriftCell_WireAngleBack    =  180.0 - DriftCell_WireAngleFront;

  DriftCell_MasterContainer_FullThickness    =    6.0*cm;   //extral large value
  DriftCell_MasterContainer_FullHeight       =   85.00*cm;  //extral large value
  DriftCell_MasterContainer_FullLength       =  600.00*cm;  //extral large value

  VDC_DriftCell_MasterContainer_XPos.resize(2,0);
  VDC_DriftCell_MasterContainer_YPos.resize(2,0);
  VDC_DriftCell_MasterContainer_ZPos.resize(2,0);

  SetVDC_DriftCell_MasterContainer_CenterPosition(0);
  SetVDC_DriftCell_MasterContainer_CenterPosition(1);
 


  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();



  //===============
  // new VDC setup
  //===============

  // define Rotation matrix for MasterContainer orientated in MotherVolume
  //Rotation_VDC_MasterContainer      = NULL;
  //Rotation_VDC_MasterContainer      = new G4RotationMatrix();

  VDC_MasterContainer_Logical       = NULL;
  //VDC_MasterContainerFront_Physical = NULL;
  //VDC_MasterContainerBack_Physical  = NULL;

  VDC_SubContainer_Logical          = NULL;
  VDC_SubContainer_Physical         = NULL;

  VDC_G10Frame_Logical              = NULL;
  VDC_G10Frame_Physical             = NULL;

  VDC_AluFrame_Logical              = NULL;
  VDC_AluTopFrame_Physical          = NULL;
  VDC_AluBottomFrame_Physical       = NULL;

  VDC_MasterContainer_VisAtt        = NULL;
  VDC_SubContainer_VisAtt           = NULL;
  VDC_G10Frame_VisAtt               = NULL;
  VDC_AluFrame_VisAtt               = NULL;

  VDC_WirePlane_Logical             = NULL;
  VDC_UPlane_Physical               = NULL;
  VDC_VPlane_Physical               = NULL;


  VDC_AluLayer_Thickness            = 1000*angstrom;   //   0.1um
  VDC_MylarFoil_Thickness           = 6.25*micrometer; //   1/4*mil

  //Resizing vectors and setting values to 0
  VDC_MasterContainerFront_Physical.resize(2,0);
  VDC_MasterContainerBack_Physical.resize(2,0);
  VDC_DriftCellMasterContainer_Physical.resize(2,0);
  Rotation_VDC_MasterContainer.resize(2,0);
  VDC_Messenger.resize(2,0);

  // Creates a messenger for each VDC package (0 for Package 1 and 1 for Package 2)
  for(size_t i = 0; i < VDC_Messenger.size(); i++){
    VDC_Messenger[i] = new QweakSimVDCMessenger(this, i);
    VDC_Messenger.at(i)->SetVDCRotator(myRotator);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimVDC::~QweakSimVDC()
{
  //if (driftChamberSD)   delete driftChamberSD;
  //if (driftCellFrontSD) delete driftCellFrontSD;
  //if (driftCellBackSD)  delete driftCellBackSD;

  if (VDC_DriftCellFront_VisAtt)           delete VDC_DriftCellFront_VisAtt;
  if (VDC_DriftCellBack_VisAtt)            delete VDC_DriftCellBack_VisAtt;
  if (VDC_DriftCellFrontContainer_VisAtt)  delete VDC_DriftCellFrontContainer_VisAtt;
  if (VDC_DriftCellBackContainer_VisAtt)   delete VDC_DriftCellBackContainer_VisAtt;
  if (VDC_DriftCellMasterContainer_VisAtt) delete VDC_DriftCellMasterContainer_VisAtt;

  if (VDC_WirePlane_VisAtt)                delete VDC_WirePlane_VisAtt;

  if (pMaterial)      delete pMaterial; 
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimVDC::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
  G4cout << G4endl << "###### Calling QweakSimVDC::ConstructComponent() " << G4endl << G4endl;
  theMotherPV = MotherVolume;

  // assign material-

  G4Material* VDC_DriftCell_Material                = pMaterial->GetMaterial("Vacuum");
  G4Material* VDC_DriftCellContainer_Material       = pMaterial->GetMaterial("Vacuum");

  G4Material* VDC_MasterContainer_Material          = pMaterial->GetMaterial("Air");
  G4Material* VDC_SubContainer_Material             = pMaterial->GetMaterial("Ar-C2H6_40-60");
  G4Material* VDC_G10Frame_Material                 = pMaterial->GetMaterial("NemaG10");
  G4Material* VDC_AluFrame_Material                 = pMaterial->GetMaterial("Aluminum");

  G4Material* VDC_WirePlane_Material                = pMaterial->GetMaterial("Vacuum");
  G4Material* VDC_AluLayer_Material                 = pMaterial->GetMaterial("Aluminum");
  G4Material* VDC_MylarFoil_Material                = pMaterial->GetMaterial("Mylar");

  //==========================================================================================================

  //============================
  // new code of the VDC setup
  //============================


  //----------------------------
  // Define VDC MasterContainer
  //----------------------------

  // define  MasterContainer 
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_MasterContainer_Solid" << G4endl << G4endl;

  G4double NumberOfG10FramesInsideVDC = 8;
  G4double NumberOfAluFramesInsideVDC = 2;


  G4Box* VDC_MasterContainer_Solid    = new G4Box("VDC_MasterContainer_Sol",
						  0.5* AluFrame_OuterLength + 1*mm,
						  0.5* AluFrame_OuterWidth  + 1*mm,
						  0.5* (G10Frame_Thickness*NumberOfG10FramesInsideVDC+ AluFrame_Thickness*NumberOfAluFramesInsideVDC) + 1*mm);
 
  // define VDC_MasterContainer_Logical volume of drift chamber container
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_MasterContainer_Logical " << G4endl << G4endl;
    
  VDC_MasterContainer_Logical  = new G4LogicalVolume(VDC_MasterContainer_Solid,	
						     VDC_MasterContainer_Material,
						     "VDC_MasterContainer_Log",
						     0,0,0);


  PlaceVDC_MasterContainers(); //Places physical volumes of VDCs
  //-----------------------
  // Define Stesalit frame
  //-----------------------

  //===============================================================================
  // Definition of the VDC Stesalit Frame ( symbolizes the stack of real frames )
  //===============================================================================

  // define outer frame solid
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_G10OuterFrame_Solid" << G4endl << G4endl;

  G4Box* VDC_G10OuterFrame_Solid    = new G4Box("VDC_G10OuterFrame_Sol",
						0.5* G10Frame_OuterLength,
						0.5* G10Frame_OuterWidth,
						0.5* G10Frame_Thickness*NumberOfG10FramesInsideVDC);

  // define inner frame solid
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_G10InnerFrame_Solid" << G4endl << G4endl;

  G4Box* VDC_G10InnerFrame_Solid    = new G4Box("VDC_G10InnerFrame_Sol",
						0.5* G10Frame_InnerLength,
						0.5* G10Frame_InnerWidth,
						0.5* G10Frame_Thickness*NumberOfG10FramesInsideVDC + 0.1*mm);


 // create frame by subtracting outer framebox from inner framebox
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_G10Frame_Solid" << G4endl << G4endl;

  VDC_G10Frame_Solid  =  new G4SubtractionSolid("VDC_G10Frame_Solid",
						VDC_G10OuterFrame_Solid,
						VDC_G10InnerFrame_Solid);


  G4cout << G4endl << "###### QweakSimVDC: Define VDC_G10Frame_Logical" << G4endl << G4endl;
  VDC_G10Frame_Logical  = new G4LogicalVolume(VDC_G10Frame_Solid,
					      VDC_G10Frame_Material,
					      "VDC_G10Frame_Log",
					      0,0,0);


  // define the position of the Frame within the VDC MasterContainer: put it in the center of MasterContainer
  G4ThreeVector position_G10Frame = G4ThreeVector(0. , 0. , 0.);

  G4cout << G4endl << "###### QweakSimVDC: Define VDC_G10Frame_Physical" << G4endl << G4endl;

  VDC_G10Frame_Physical =   new G4PVPlacement(0,                          // no rotation matrix needed
					      position_G10Frame,
					      VDC_G10Frame_Logical,
					      "VDC_G10Frame_Physical",
					      VDC_MasterContainer_Logical,
					      0,
					      0,
					      pSurfChk); //copy number: 0




  //-----------------------
  // Define Aluminum frame
  //-----------------------

  //=====================================================================================
  // Definition of the VDC Alu Frame ( symbolizes the top and bottom alu support frames)
  //=====================================================================================

  // define outer frame solid
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AluOuterFrame_Solid" << G4endl << G4endl;

  G4Box* VDC_AluOuterFrame_Solid    = new G4Box("VDC_AluOuterFrame_Sol",
						0.5* AluFrame_OuterLength,
						0.5* AluFrame_OuterWidth,
						0.5* AluFrame_Thickness);

  // define inner frame solid
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AluInnerFrame_Solid" << G4endl << G4endl;

  G4Box* VDC_AluInnerFrame_Solid    = new G4Box("VDC_AluInnerFrame_Sol",
						0.5* AluFrame_InnerLength,
						0.5* AluFrame_InnerWidth,
						0.5* AluFrame_Thickness + 0.1*mm);


  // create frame by subtracting outer framebox from inner framebox
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AluFrame_Solid" << G4endl << G4endl;

  VDC_AluFrame_Solid  =  new G4SubtractionSolid("VDC_AluFrame_Solid",
						VDC_AluOuterFrame_Solid,
						VDC_AluInnerFrame_Solid);


  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AluFrame_Logical" << G4endl << G4endl;

  VDC_AluFrame_Logical  = new G4LogicalVolume(VDC_AluFrame_Solid,
					      VDC_AluFrame_Material,
					      "VDC_AluFrame_Log",
					      0,0,0);


  // define the position of the Frame within the VDC MasterContainer: put it in the center of MasterContainer
  // AluTopFrame     = downstream side, looking to beam dunp
  // AluBottomFrame  = upstream side, looking to target

  G4ThreeVector position_AluTopFrame    = G4ThreeVector(0. , 0. ,  0.5*(G10Frame_Thickness*NumberOfG10FramesInsideVDC + AluFrame_Thickness));
  G4ThreeVector position_AluBottomFrame = G4ThreeVector(0. , 0. , -0.5*(G10Frame_Thickness*NumberOfG10FramesInsideVDC + AluFrame_Thickness));

  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AluTopFrame_Physical" << G4endl << G4endl;

  VDC_AluTopFrame_Physical =   new G4PVPlacement(0,                          // no rotation matrix needed
						 position_AluTopFrame,
						 VDC_AluFrame_Logical,
						 "VDC_AluTopFrame_Physical",
						 VDC_MasterContainer_Logical,
						 0,
						 0,
						 pSurfChk); //copy number: 0

  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AluBottomFrame_Physical" << G4endl << G4endl;

  VDC_AluBottomFrame_Physical =   new G4PVPlacement(0,                          // no rotation matrix needed
						    position_AluBottomFrame,
						    VDC_AluFrame_Logical,
						    "VDC_AluBottomFrame_Physical",
						    VDC_MasterContainer_Logical,
						    0,
						    1,
						    pSurfChk); //copy number: 1 , to be checked if necessary



  //======================================================================================
  // Definition of the VDC SubContainer holding the stack of foil planes and readout plane
  //======================================================================================
  

  // define outer frame solid
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_SubContainer_Solid" << G4endl << G4endl;
  
  G4Box* VDC_SubContainer_Solid    = new G4Box("VDC_OuterFrame_Sol",
					       0.5* G10Frame_InnerLength                          - 100.0*micrometer,   // X
					       0.5* G10Frame_InnerWidth                           - 100.0*micrometer,   // Y
					       0.5* G10Frame_Thickness*NumberOfG10FramesInsideVDC + 100.0*micrometer);  // Z
  
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_SubContainer_Logical" << G4endl << G4endl;
  
  VDC_SubContainer_Logical  = new G4LogicalVolume(VDC_SubContainer_Solid,
						  VDC_SubContainer_Material,
						  "VDC_SubContainer_Log",
						  0,0,0);


  // define the position of the SubContainer within the VDC MasterContainer: put it in the center
  G4ThreeVector position_SubContainer = G4ThreeVector(0. , 0. , 0.);
  
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_SubContainer_Physical" << G4endl << G4endl;
  
  VDC_SubContainer_Physical =   new G4PVPlacement(0,                          // no rotation matrix needed 
						  position_SubContainer, 
						  VDC_SubContainer_Logical, 
						  "VDC_SubContainer_Physical",
						  VDC_MasterContainer_Logical, 
						  0, 
						  0,
						  pSurfChk); //copy number: 0
  


  //====================================================================
  // Definition of the VDC Wire Plane 
  //====================================================================

   // define wire plane solid
   G4cout << G4endl << "###### QweakSimVDC: Define VDC_WirePlane_Solid" << G4endl << G4endl;

   G4Box* VDC_WirePlane_Solid    = new G4Box("VDC_WirePlane_Sol",
					     VDC_SubContainer_Solid->GetXHalfLength() -1.0*micrometer,
					     VDC_SubContainer_Solid->GetYHalfLength() -1.0*micrometer,
					     0.5* 10.0*micrometer);

   // define wire plane logical
   G4cout << G4endl << "###### QweakSimVDC: Define VDC_WirePlane_Logical" << G4endl << G4endl;

   VDC_WirePlane_Logical  = new G4LogicalVolume(VDC_WirePlane_Solid,
						VDC_WirePlane_Material,
						"VDC_WirePlane_Log",
						0,0,0);

   // define wire planes physical
   G4cout << G4endl << "###### QweakSimVDC: Define VDC_WirePlane_Physical" << G4endl << G4endl;


   // place two VDC_Plane_Logical alias U-Plane and V-Plane into the VDC SubContainer

  // define VDC Plane position relativ to container
  //  U Plane    = downstream side , looking to beam dunp
  //  V Plane    = upstream side   , looking to target

  G4ThreeVector position_Uplane    = G4ThreeVector( 0.0*cm, 0.0*cm, -1.0 * G10Frame_Thickness);
  G4ThreeVector position_Vplane    = G4ThreeVector( 0.0*cm, 0.0*cm,        G10Frame_Thickness);

  VDC_UPlane_Physical = new G4PVPlacement(0,
					  position_Uplane,
					  VDC_WirePlane_Logical,
					  "VDC_UPlane_Physical",
					  VDC_SubContainer_Logical,
					  0,
					  0,
					  pSurfChk); //copy number: 0

  VDC_VPlane_Physical = new G4PVPlacement(0,
					  position_Vplane,
					  VDC_WirePlane_Logical,
					  "VDC_VPlane_Physical",
					  VDC_SubContainer_Logical,
					  0,
					  1,
					  pSurfChk); //copy number: 1
  


  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  //====================================================================
  //             Definition of the VDC Foils
  //====================================================================

  //============================================
  // Define a 6.25 micrometer thick Mylar foil
  //============================================

  G4Box* VDC_MylarFoil_Solid    = new G4Box("VDC_MylarFoil_Sol",
					    VDC_SubContainer_Solid->GetXHalfLength() -20.0*micrometer ,
					    VDC_SubContainer_Solid->GetYHalfLength() -20.0*micrometer,
					    0.5* VDC_MylarFoil_Thickness);

  // define foil logical
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_MylarFoil_Logical" << G4endl << G4endl;

  VDC_MylarFoil_Logical  = new G4LogicalVolume(VDC_MylarFoil_Solid,
					       VDC_MylarFoil_Material,
					       "VDC_MylarFoil_Log",
					       0,0,0);


  //=========================================================
  // Define a 1000 Angstrom (= 0.1 micrometer) thick Alu layer
  //=========================================================

  // define solid
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AluLayer_Solid" << G4endl << G4endl;

  G4Box* VDC_AluLayer_Solid    =  new G4Box("VDC_AluLayer_Sol",
					    VDC_SubContainer_Solid->GetXHalfLength() -20.0*micrometer,
					    VDC_SubContainer_Solid->GetYHalfLength() -20.0*micrometer,
					    0.5* VDC_AluLayer_Thickness);

  // define logical
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AluFoil_Logical" << G4endl << G4endl;

  VDC_AluLayer_Logical  = new G4LogicalVolume(VDC_AluLayer_Solid,
					      VDC_AluLayer_Material,
					      "VDC_AluLayer_Log",
					      0,0,0);


  //====================================================================================================
  //                      create the double sided foil container : Alu-Mylar-Alu == AMA
  //
  // (define a container holding a 6.25um thick Mylar foil coated with 0.1um Aluminum on each side.
  //====================================================================================================


  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AMA_FoilContainer_Solid" << G4endl << G4endl;

  G4Box* VDC_AMA_FoilContainer_Solid    = new G4Box("VDC_AMA_FoilContainer_Sol",
						      VDC_SubContainer_Solid->GetXHalfLength() -10.0*micrometer,
						      VDC_SubContainer_Solid->GetYHalfLength() -10.0*micrometer,
						      0.5* (VDC_MylarFoil_Thickness + 2*VDC_AluLayer_Thickness) + 10.0*micrometer );

  // define foil logical
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AMA_FoilContainer_Logical" << G4endl << G4endl;

  VDC_AMA_FoilContainer_Logical  = new G4LogicalVolume(VDC_AMA_FoilContainer_Solid,
						       VDC_SubContainer_Material,
						       "VDC_AMA_FoilContainer_Log",
						       0,0,0);


  //========================================================================
  // Place the 6.25 micrometer thick Mylar foil inside VDC_AMA_FoilContainer
  //========================================================================


  // place 6.25um thick Mylar foil into VDC_DoubleSidedFoilContainer: center
  new G4PVPlacement(0,
      G4ThreeVector(0. , 0. , 0. ),
      VDC_MylarFoil_Logical,
      "VDC_MylarFoil_Physical",
		    VDC_AMA_FoilContainer_Logical,
		    0,
		    0,
		    pSurfChk); //copy number 0


  //=========================================================================================
  // Place the  1000 Angstrom (= 0.1 micrometer) thick Alu layers inside VDC_AMA_FoilContainer
  //=========================================================================================

  // define physical
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AluLayer_Physical" << G4endl << G4endl;

  // Z Location of the AluLayer within VDC_AMA_FoilContainer:
  // (first go to border of box and go half the alu layer thickness back)

  G4double _LocalPostionInZ_TopAluLayer =
      +  0.5*(VDC_MylarFoil_Thickness + 2*VDC_AluLayer_Thickness) - 0.5*  VDC_AluLayer_Thickness;

  G4double _LocalPostionInZ_BottomAluLayer =
      -  0.5*(VDC_MylarFoil_Thickness + 2*VDC_AluLayer_Thickness) + 0.5*  VDC_AluLayer_Thickness;


  G4cout << G4endl << "###### QweakSimVDC: Place Top AluLayer inside VDC_AMA_FoilContainer_Logical" << G4endl << G4endl;
  // place alu top layer
  new G4PVPlacement(0,
		    G4ThreeVector(0. , 0. , _LocalPostionInZ_TopAluLayer ),
		    VDC_AluLayer_Logical,
		    "VDC_TopAluLayer_Physical",
		    VDC_AMA_FoilContainer_Logical,
		    0,
		    0,
		    pSurfChk); //copy number for top layer

  G4cout << G4endl << "###### QweakSimVDC: Place Bottom AluLayer inside VDC_AMA_FoilContainer_Logical" << G4endl << G4endl;
  // place alu bottom layer
  new G4PVPlacement(0,
		    G4ThreeVector(0. , 0. , _LocalPostionInZ_BottomAluLayer ),
		    VDC_AluLayer_Logical,
		    "VDC_BottomAluLayer_Physical",
		    VDC_AMA_FoilContainer_Logical,
		    0,
		    1,
		    pSurfChk); //copy number for bottom layer



  //====================================================================================================
  //                      create the "AM" sided foil container: Alu-Mylar (alias "AM")
  //
  // (define a container holding a 6.25um thick Mylar foil coated with 0.1um Aluminum on top side.
  //====================================================================================================


  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AM_FoilContainer_Solid" << G4endl << G4endl;

  G4Box* VDC_AM_FoilContainer_Solid    = new G4Box("VDC_AM_FoilContainer_Sol",
						   VDC_SubContainer_Solid->GetXHalfLength() -10.0*micrometer,
						   VDC_SubContainer_Solid->GetYHalfLength() -10.0*micrometer,
						   0.5* (VDC_MylarFoil_Thickness + VDC_AluLayer_Thickness) );

  // define foil logical
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_AM_FoilContainer_Logical" << G4endl << G4endl;

  VDC_AM_FoilContainer_Logical  = new G4LogicalVolume(VDC_AM_FoilContainer_Solid,
						      VDC_SubContainer_Material,
						      "VDC_AM_FoilContainer_Log",
						      0,0,0);


  //=======================================================================
  // Place the 6.25 micrometer thick Mylar foil inside VDC_AM_FoilContainer
  //=======================================================================

  G4double position_MylarFoilInsideAMContainer_Z = -1*VDC_AM_FoilContainer_Solid->GetZHalfLength() + VDC_MylarFoil_Solid->GetZHalfLength();

  G4cout << G4endl << "###### QweakSimVDC: Place Mylar inside VDC_AM_FoilContainer_Logical" << G4endl << G4endl;

  new G4PVPlacement(0,
		    G4ThreeVector(0. , 0. , position_MylarFoilInsideAMContainer_Z ),
		    VDC_MylarFoil_Logical,
		    "VDC_MylarFoil_Physical",
		    VDC_AM_FoilContainer_Logical,
		    0,
		    0,
		    pSurfChk); //copy number


  //=======================================================================================
  // Place the 1000 Angstrom (= 0.1 micrometer) thick Alu layer inside VDC_AM_FoilContainer
  //=======================================================================================

  G4double position_AluLayerInsideAMContainer_Z = +1*VDC_AM_FoilContainer_Solid->GetZHalfLength() - VDC_AluLayer_Solid->GetZHalfLength();

  G4cout << G4endl << "###### QweakSimVDC: Place AluLayer inside VDC_AM_FoilContainer_Logical" << G4endl << G4endl;

  new G4PVPlacement(0,
		    G4ThreeVector(0. , 0. , position_AluLayerInsideAMContainer_Z),
		    VDC_AluLayer_Logical,
		    "VDC_TopAluLayer_Physical",
		    VDC_AM_FoilContainer_Logical,
		    0,
		    0,
		    pSurfChk); //copy number


  //====================================================================================================
  //                      create the "MA" sided foil container: Mylar-Alu (alias "MA")
  //
  // (define a container holding a 6.25um thick Mylar foil coated with 0.1um Aluminum on bottom side.
  //====================================================================================================


  G4cout << G4endl << "###### QweakSimVDC: Define VDC_MA_FoilContainer_Solid" << G4endl << G4endl;

  G4Box* VDC_MA_FoilContainer_Solid    = new G4Box("VDC_MA_FoilContainer_Sol",
						   VDC_SubContainer_Solid->GetXHalfLength() -10.0*micrometer,
						   VDC_SubContainer_Solid->GetYHalfLength() -10.0*micrometer,
						   0.5* (VDC_MylarFoil_Thickness + VDC_AluLayer_Thickness) );

  // define foil logical
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_MA_FoilContainer_Logical" << G4endl << G4endl;

  VDC_MA_FoilContainer_Logical  = new G4LogicalVolume(VDC_MA_FoilContainer_Solid,
						      VDC_SubContainer_Material,
						      "VDC_MA_FoilContainer_Log",
						      0,0,0);


  //=======================================================================
  // Place the 6.25 micrometer thick Mylar foil inside VDC_MA_FoilContainer
  //=======================================================================

  G4double position_MylarFoilInsideMAContainer_Z = 1*VDC_MA_FoilContainer_Solid->GetZHalfLength() - VDC_MylarFoil_Solid->GetZHalfLength();

  G4cout << G4endl << "###### QweakSimVDC: Place Mylar inside VDC_MA_FoilContainer_Logical" << G4endl << G4endl;

  new G4PVPlacement(0,
		    G4ThreeVector(0. , 0. , position_MylarFoilInsideMAContainer_Z ),
		    VDC_MylarFoil_Logical,
		    "VDC_MylarFoil_Physical",
		    VDC_MA_FoilContainer_Logical,
		    0,
		    0,
		    pSurfChk); //copy number


  //=======================================================================================
  // Place the 1000 Angstrom (= 0.1 micrometer) thick Alu layer inside VDC_MA_FoilContainer
  //=======================================================================================

  G4double position_AluLayerInsideMAContainer_Z = -1*VDC_MA_FoilContainer_Solid->GetZHalfLength() + VDC_AluLayer_Solid->GetZHalfLength();

  G4cout << G4endl << "###### QweakSimVDC: Place AluLayer inside VDC_MA_FoilContainer_Logical" << G4endl << G4endl;

  new G4PVPlacement(0,
		    G4ThreeVector(0. , 0. , position_AluLayerInsideMAContainer_Z),
		    VDC_AluLayer_Logical,
		    "VDC_TopAluLayer_Physical",
		    VDC_MA_FoilContainer_Logical,
		    0,
		    0,
		    pSurfChk); //copy number

  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  //----------------------------------------------------------------------------
  //
  //  Final assembly of AM, MA, and AMA FoilContainers within VDC_SubContainer
  //
  //----------------------------------------------------------------------------
  //
  // Foil Stack orientation (AM=Alu-Mylar, MA=Mylar-Alu, AMA=Alu-Mylar-Alu)
  //
  // Single sided gas foil  : AM   , zpos= 4*G10Frame_Thickness
  // Single sided HV  foil  : MA   , zpos= 2*G10Frame_Thickness
  // (U-Plane)
  // Double sided HV  foil  : AMA  , zpos= 0*G10Frame_Thickness
  // (V-Plane)
  // Single sided HV  foil  : AM   , zpos= -2*G10Frame_Thickness
  // Single sided gas foil  : MA   , zpos= -4*G10Frame_Thickness
  //
  //---------------------------------------------------------------------------

  G4cout << G4endl << "###### QweakSimVDC: Place VDC_TopGasFoilContainer_Physical inside VDC_SubContainer_Physical" << G4endl << G4endl;
  //
  VDC_TopGasFoilContainer_Physical  =
      new G4PVPlacement(0,
          G4ThreeVector(0. , 0. , 4*G10Frame_Thickness ),
          "VDC_TopGasFoilContainer_Physical",
          VDC_AM_FoilContainer_Logical,
			VDC_SubContainer_Physical,
			false,
			0,
			pSurfChk);

  G4cout << G4endl << "###### QweakSimVDC: Place VDC_TopHVFoilContainer_Physical inside VDC_SubContainer_Physical" << G4endl << G4endl;
  //
  VDC_TopHVFoilContainer_Physical  =
      new G4PVPlacement(0,
			G4ThreeVector(0. , 0. , 2*G10Frame_Thickness ),
			"VDC_TopHVFoilContainer_Physical",
			VDC_MA_FoilContainer_Logical,
			VDC_SubContainer_Physical,
			false,
			0,
			pSurfChk);


  G4cout << G4endl << "###### QweakSimVDC: Place VDC_CenterHVFoilContainer_Physical inside VDC_SubContainer_Physical" << G4endl << G4endl;
  //
  VDC_CenterHVFoilContainer_Physical  =
      new G4PVPlacement(0,
			G4ThreeVector(0. , 0. , 0. ),
			"VDC_CenterHVFoilContainer_Physical",
			VDC_AMA_FoilContainer_Logical,
			VDC_SubContainer_Physical,
			false,
			0,
			pSurfChk);

  G4cout << G4endl << "###### QweakSimVDC: PlaceVDC_BottomHVFoilContainer_Physical inside VDC_SubContainer_Physical" << G4endl << G4endl;
  //
  VDC_BottomHVFoilContainer_Physical  =
      new G4PVPlacement(0,
			G4ThreeVector(0. , 0. , -2*G10Frame_Thickness ),
			"VDC_TopHVFoilContainer_Physical",
			VDC_AM_FoilContainer_Logical,
			VDC_SubContainer_Physical,
			false,
			1,
			pSurfChk); // copy number 1 (second VDC_AM_FoilContainer_Logical placement inside SubContainer)

  G4cout << G4endl << "###### QweakSimVDC: Place VDC_BottomGasFoilContainer_Physical inside VDC_SubContainer_Physical" << G4endl << G4endl;
  //
  VDC_BottomGasFoilContainer_Physical  =
      new G4PVPlacement(0,
			G4ThreeVector(0. , 0. , -4*G10Frame_Thickness ),
			"VDC_TopHVFoilContainer_Physical",
			VDC_MA_FoilContainer_Logical,
			VDC_SubContainer_Physical,
			false,
			1,
			pSurfChk); // copy number 1 (second  VDC_MA_FoilContainer_Logical placement inside SubContainer)

  //==========================================================================================================



  //==========================================================
  //
  //        Define a master container which hold the 
  //        Front+Back Drift cell containers
  //
  //==========================================================
  
  //                   | DX1  |     <== half width of master container: Dx =DX1+DX2+ FullWidthOnFrame of following DCs    
  //                   |  _|_DX2          DX1 =  driftcell_halfheight*tan(wireangle)
  //                   | / / /            DX2 =  driftCell_halfWidthOnFrame
  //                   |/ / /
  //                   | / /
  //                  /|/ /
  //          -------------------------
  //                / /|/ 
  //               / / |
  //              / / /|
  //               - -

  // define  solid volume of the drift chamber container
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellMasteContainer_Solid" << G4endl << G4endl;


//   G4double myContainerX =   0.5*DriftCell_FullHeight*TMath::Tan( DriftCell_WireAngleFront/degree*TMath::DegToRad())
//                           + 0.5*DriftCell_FullWidthOnFrame
//                           + 0.5*(DriftCell_NumberPerPlane -1)*DriftCell_FullWidthOnFrame +1.0*mm;

// G4double myContainerX = 250*cm;




//  G4cout << "Half Length of DriftCellMasterContainer [cm] = " << myContainerX/cm << G4endl;


//   G4Box* VDC_DriftCellMasterContainer_Solid    = new G4Box("VDC_DriftCellMasterContainer_Solid",
//                                                            0.5*DriftCell_FullHeight*TMath::Tan( DriftCell_WireAngleFront
//                                                                                                *TMath::RadToDeg())
//                                                            + 0.5*DriftCell_FullWidthOnFrame
//                                                            + 0.5*(DriftCell_NumberPerPlane -1)*DriftCell_FullWidthOnFrame +1.0*mm,
//                                                            0.5* DriftCell_FullHeight,
//                                                            1.0* DriftCell_FullThickness);


  G4Box* VDC_DriftCellMasterContainer_Solid    = new G4Box("VDC_DriftCellMasterContainer_Solid",
							   0.5* DriftCell_MasterContainer_FullLength,
							   0.5* DriftCell_MasterContainer_FullHeight,
							   0.5* DriftCell_MasterContainer_FullThickness);

  // define VDC logical volume of drift chamber container
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellMasterContainer_Logical " << G4endl << G4endl;
  
  VDC_DriftCellMasterContainer_Logical  = new G4LogicalVolume(VDC_DriftCellMasterContainer_Solid,
							     VDC_DriftCellContainer_Material,
							     "VDC_DriftCellMasterContainer_Log",
							     0,0,0);
  


  PlaceVDC_DriftCellMasterContainers();


  //==========================================================
  //
  //               Front Drift cell container definition
  //
  //==========================================================


  // define  solid volume of the drift chamber container
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellFrontContainer_Solid" << G4endl << G4endl;
 
  G4Box* VDC_DriftCellFrontContainer_Solid    = new G4Box("VDC_DriftCellFrontContainer_Solid",
						     0.5* DriftCell_MasterContainer_FullLength,
						     0.5* DriftCell_MasterContainer_FullHeight,
						     0.5* (0.5*DriftCell_MasterContainer_FullThickness -0.01*mm) ); 

  // define VDC logical volume of drift chamber container
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellFrontContainer_Logical " << G4endl << G4endl;
  
  VDC_DriftCellFrontContainer_Logical  = new G4LogicalVolume(VDC_DriftCellFrontContainer_Solid,
							     VDC_DriftCellContainer_Material,
							     "VDC_DriftCellFrontContainer_Log",
							     0,0,0);
  
  // define VDC Drift Cell Container position within the master container
  G4ThreeVector position_DriftCellFrontContainer = G4ThreeVector(0, 
								 0,
								 -0.25* DriftCell_MasterContainer_FullThickness);

  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellFrontContainer_Physical " << G4endl << G4endl;
  // define VDC physical volume of drift chamber container
  VDC_DriftCellFrontContainer_Physical = new G4PVPlacement(0, 
							   position_DriftCellFrontContainer, 
							   VDC_DriftCellFrontContainer_Logical,
							   "VDC_DriftCellFrontContainer_Physical", 
							   VDC_DriftCellMasterContainer_Logical,   
							   false, 
							   0,
							   pSurfChk);
 
  //==========================================================
  //
  //           Front Drift cell  definition
  //
  //==========================================================

  // define  solid volume of the drift chamber drift cell
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellFront_Solid" << G4endl << G4endl;
  
  VDC_DriftCellFront_Solid    = new G4Para("VDC_DriftCellFront_Solid",
					   0.5* DriftCell_FullWidthOnFrame,
					   0.5* DriftCell_FullHeight,
					   0.5* DriftCell_FullThickness,
					   1.0* DriftCell_WireAngleFront,
					   0.0*degree,
					   0.0*degree); 
  
  // define VDC logical volume of drift cell container
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellFront_Logical " << G4endl << G4endl;
  
  VDC_DriftCellFront_Logical  = new G4LogicalVolume(VDC_DriftCellFront_Solid,
						    VDC_DriftCell_Material,
						    "VDC_DriftCellFront_Log",
						    0,0,0);


  //===============================================================================================


  //==========================================================
  //
  //    Back Drift cell container definition
  //
  //==========================================================



  // define  solid volume of the drift chamber container
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellBackContainer_Solid" << G4endl << G4endl;

  G4Box* VDC_DriftCellBackContainer_Solid    = new G4Box("VDC_DriftCellBackContainer_Solid",
							 0.5* DriftCell_MasterContainer_FullLength,
  							 0.5* DriftCell_MasterContainer_FullHeight,
							 0.5* (0.5*DriftCell_MasterContainer_FullThickness -0.01*mm )); 
  
  // define VDC logical volume of drift chamber container
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellBackContainer_Logical " << G4endl << G4endl;
  
  VDC_DriftCellBackContainer_Logical  = new G4LogicalVolume(VDC_DriftCellBackContainer_Solid,
							    VDC_DriftCellContainer_Material,
							    "VDC_DriftCellbackContainer_Log",
							    0,0,0);
  
  // define VDC Drift Cell Back Container position in MotherVolume
  G4ThreeVector position_DriftCellBackContainer = G4ThreeVector(0,
								0,
								0.25* DriftCell_MasterContainer_FullThickness);

   // define VDC physical volume of drift chamber container
  VDC_DriftCellBackContainer_Physical = new G4PVPlacement(0, 
							  position_DriftCellBackContainer, 
							  VDC_DriftCellBackContainer_Logical,
							  "VDC_DriftCellBackContainer_Physical", 
							  VDC_DriftCellMasterContainer_Logical,   
							  false, 
							  0,
							  pSurfChk);
  
  //==========================================================
  //
  //           Back Drift cell  definition
  //
  //==========================================================


  // define  solid volume of the drift chamber drift cell
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellBack_Solid" << G4endl << G4endl;

  VDC_DriftCellBack_Solid    = new G4Para("VDC_DriftCellBack_Solid",
					  0.5* DriftCell_FullWidthOnFrame,
					  0.5* DriftCell_FullHeight,
					  0.5* DriftCell_FullThickness,
					  1.0* DriftCell_WireAngleBack,
					  0.0* degree,
					  0.0* degree); 
  
  // define VDC logical volume of drift cell container
  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellBack_Logical " << G4endl << G4endl;
  
  VDC_DriftCellBack_Logical  = new G4LogicalVolume(VDC_DriftCellBack_Solid,
						   VDC_DriftCell_Material,
						   "VDC_DriftCellBack_Log",
						   0,0,0);

  //==========================================================
  //
  //           Front/Back Drift cell row definition
  //-
  //==========================================================


  G4VPVParameterisation* driftCellParam = new QweakSimVDC_DriftCellParameterisation( DriftCell_NumberPerPlane,
								        	     DriftCell_FullWidthOnFrame);

  //dummy value : kXAxis -- modified by parameterised volume
 
  VDC_DriftCellFront_Physical  = 
    new G4PVParameterised("VDC_DriftCellFront_Physical",         // their name
			    VDC_DriftCellFront_Logical,          // their logical volume
			    VDC_DriftCellFrontContainer_Logical, // Mother logical volume
			    kXAxis,                              // Are placed along this axis
			    DriftCell_NumberPerPlane,            // Number of drift cells
			    driftCellParam,                      // The parametrisation
			    pSurfChk);                           // Check overlaps


  VDC_DriftCellBack_Physical  = 
    new G4PVParameterised("VDC_DriftCellBack_Physical",          // their name
			    VDC_DriftCellBack_Logical,           // their logical volume
			    VDC_DriftCellBackContainer_Logical,  // Mother logical volume
			    kXAxis,                              // Are placed along this axis 
			    DriftCell_NumberPerPlane,            // Number of drift cells
			    driftCellParam,                      // The parametrisation
			    pSurfChk);                           // Check overlaps





  //==========================================================================================
  //
  // ------------------------------------------------------
  // Define a Region which is required for the PAI model
  // handling a precise energy loss of relativistic charged
  // particles crossing the drift chamber gas.
  // ------------------------------------------------------

  if (fEnablePAI) {

    if( fRegGasDet != 0 )  // remove obsolete root logical volume
    {
      fRegGasDet->RemoveRootLogicalVolume(VDC_DriftCellFront_Logical);
      fRegGasDet->RemoveRootLogicalVolume(VDC_DriftCellBack_Logical);
    }

    G4ProductionCuts* cuts = 0;

    if( fRegGasDet == 0 ) // First time - instantiate a region and a cut objects
    {
      fRegGasDet = new G4Region("DriftCellRegion_VDC");
      cuts = new G4ProductionCuts();
      fRegGasDet->SetProductionCuts(cuts);
    }
    else  // Second time - get a cut object from region
    {
      cuts = fRegGasDet->GetProductionCuts();
    }

    VDC_DriftCellFront_Logical->SetRegion(fRegGasDet);
    VDC_DriftCellBack_Logical->SetRegion(fRegGasDet);

    fRegGasDet->AddRootLogicalVolume(VDC_DriftCellFront_Logical);
    fRegGasDet->AddRootLogicalVolume(VDC_DriftCellBack_Logical);

    cuts->SetProductionCut(fGammaCut,"gamma");
    cuts->SetProductionCut(fElectronCut,"e-");
    cuts->SetProductionCut(fPositronCut,"e+");

  }

  //==========================================================================================



  G4cout << G4endl << "###### QweakSimVDC: Setting Sensitive Detectors " << G4endl << G4endl;

  // Sensitive detectors
  //------------------------------------------------ 
  // All managed (deleted) by SDManager

  G4SDManager* SDman = G4SDManager::GetSDMpointer();


  //#######################################################
  // define drift chamber elements as sensitiv detectors
  // "sensitivity" will be handled by class QweakSimVDCSD
  //#######################################################


  //***********************************************************
  driftChamberSD = new QweakSimVDC_WirePlaneSD("VDCWirePlaneSD");
  SDman->AddNewDetector(driftChamberSD);

  // add wire plane as a sensitive element
  VDC_WirePlane_Logical->SetSensitiveDetector(driftChamberSD);
  //***********************************************************


  //***********************************************************
  driftCellFrontSD = new QweakSimVDC_DriftCellFrontSD("VDCDriftCellFrontSD");
  SDman->AddNewDetector(driftCellFrontSD);

  // add Front Drift Cell as a sensitive element
  VDC_DriftCellFront_Logical->SetSensitiveDetector(driftCellFrontSD);
  //***********************************************************


  //***********************************************************
  driftCellBackSD = new QweakSimVDC_DriftCellBackSD("VDCDriftCellBackSD");
  SDman->AddNewDetector(driftCellBackSD);

  // add Back Drift Cell as a sensitive element
  VDC_DriftCellBack_Logical->SetSensitiveDetector(driftCellBackSD);
  //***********************************************************




  G4cout << G4endl << "###### QweakSimVDC: Setting Attributes " << G4endl << G4endl;

  G4Colour  orange       (241/255.,224/255.,0/255.);
  G4Colour  gray         (210/255.,213/255.,210/255.);

  G4Colour  red          (255/255.,   0/255.,0/255.);
  G4Colour  green        (  0/255., 255/255.,0/255.);
  G4Color   green_yellow (173/255., 255/255., 47/255.);

  VDC_DriftCellMasterContainer_VisAtt  = new G4VisAttributes(gray);
  VDC_DriftCellMasterContainer_VisAtt  -> SetVisibility(false);
  VDC_DriftCellMasterContainer_VisAtt  -> SetForceWireframe(true);
  VDC_DriftCellMasterContainer_Logical -> SetVisAttributes(VDC_DriftCellMasterContainer_VisAtt); 

  VDC_DriftCellFrontContainer_VisAtt = new G4VisAttributes(gray);
  VDC_DriftCellFrontContainer_VisAtt -> SetVisibility(false);
  VDC_DriftCellFrontContainer_Logical->SetVisAttributes(VDC_DriftCellFrontContainer_VisAtt); 

  VDC_DriftCellBackContainer_VisAtt = new G4VisAttributes(gray);
  VDC_DriftCellBackContainer_VisAtt -> SetVisibility(false);
  VDC_DriftCellBackContainer_Logical->SetVisAttributes(VDC_DriftCellBackContainer_VisAtt); 

  VDC_DriftCellFront_VisAtt = new G4VisAttributes(red);
  //VDC_DriftCellFront_VisAtt  -> SetVisibility(true);
  VDC_DriftCellFront_VisAtt  -> SetVisibility(false);
  VDC_DriftCellFront_VisAtt  -> SetForceWireframe(true);
  VDC_DriftCellFront_Logical -> SetVisAttributes(VDC_DriftCellFront_VisAtt); 

  VDC_DriftCellBack_VisAtt = new G4VisAttributes(green);
  //VDC_DriftCellBack_VisAtt  -> SetVisibility(true);
  VDC_DriftCellBack_VisAtt  -> SetVisibility(false);
  VDC_DriftCellBack_VisAtt -> SetForceWireframe(true);
  VDC_DriftCellBack_Logical -> SetVisAttributes(VDC_DriftCellBack_VisAtt); 

  //===============
  // new VDC setup
  //===============
  VDC_MasterContainer_VisAtt  = new G4VisAttributes(gray);
  VDC_MasterContainer_VisAtt  -> SetVisibility(false);
  VDC_MasterContainer_VisAtt  -> SetForceWireframe(true);
  VDC_MasterContainer_Logical -> SetVisAttributes(VDC_MasterContainer_VisAtt); 

  VDC_SubContainer_VisAtt  = new G4VisAttributes(orange);
  VDC_SubContainer_VisAtt  -> SetVisibility(false);
  //VDC_SubContainer_VisAtt  -> SetForceWireframe(true);
  VDC_SubContainer_Logical -> SetVisAttributes(VDC_SubContainer_VisAtt); 

  VDC_G10Frame_VisAtt  = new G4VisAttributes(green);
  VDC_G10Frame_VisAtt  -> SetVisibility(true);
  //VDC_G10Frame_VisAtt  -> SetForceWireframe(true);
  VDC_G10Frame_Logical -> SetVisAttributes(VDC_G10Frame_VisAtt);

  VDC_AluFrame_VisAtt  = new G4VisAttributes(gray);
  VDC_AluFrame_VisAtt  -> SetVisibility(true);
  //VDC_AluFrame_VisAtt  -> SetForceWireframe(true);
  VDC_AluFrame_Logical -> SetVisAttributes(VDC_AluFrame_VisAtt);

  VDC_AluLayer_VisAtt  = new G4VisAttributes(gray);
  VDC_AluLayer_VisAtt  -> SetVisibility(true);
  //VDC_AluLayer_VisAtt  -> SetForceWireframe(true);
  VDC_AluLayer_Logical -> SetVisAttributes(VDC_AluLayer_VisAtt);

  VDC_MylarFoil_VisAtt  = new G4VisAttributes(red);
  VDC_MylarFoil_VisAtt  -> SetVisibility(true);
  //VDC_MylarFoil_VisAtt  -> SetForceWireframe(true);
  VDC_MylarFoil_Logical -> SetVisAttributes(VDC_MylarFoil_VisAtt);

  VDC_AMA_FoilContainer_VisAtt  = new G4VisAttributes(gray);
  VDC_AMA_FoilContainer_VisAtt  -> SetVisibility(false);
  VDC_AMA_FoilContainer_VisAtt  -> SetForceWireframe(true);
  VDC_AMA_FoilContainer_Logical -> SetVisAttributes(VDC_AMA_FoilContainer_VisAtt);

  VDC_AM_FoilContainer_VisAtt  = new G4VisAttributes(gray);
  VDC_AM_FoilContainer_VisAtt  -> SetVisibility(false);
  VDC_AM_FoilContainer_VisAtt  -> SetForceWireframe(true);
  VDC_AM_FoilContainer_Logical -> SetVisAttributes(VDC_AM_FoilContainer_VisAtt);

  VDC_MA_FoilContainer_VisAtt  = new G4VisAttributes(gray);
  VDC_MA_FoilContainer_VisAtt  -> SetVisibility(false);
  VDC_MA_FoilContainer_VisAtt  -> SetForceWireframe(true);
  VDC_MA_FoilContainer_Logical -> SetVisAttributes(VDC_MA_FoilContainer_VisAtt);

  VDC_WirePlane_VisAtt = new G4VisAttributes(green_yellow);
  VDC_WirePlane_VisAtt -> SetVisibility(true);
  //VDC_MyWirePlane_VisAtt -> SetForceWireframe(true);
  VDC_WirePlane_Logical -> SetVisAttributes(VDC_WirePlane_VisAtt);


  G4cout << G4endl << "###### Leaving QweakSimVDC::ConstructComponent() " << G4endl << G4endl;

} // end of  QweakSimVDC::ConstructComponent()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_MasterContainerMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing VDC MasterContainer Material: Looking up Material  " << G4endl; 
                VDC_MasterContainer_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing VDC MasterContainer Material:  Now the VDC MasterContainer is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing VDC MasterConrainer Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_SubContainerMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing VDC SubContainer Material: Looking up Material  " << G4endl; 
                VDC_SubContainer_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing VDC SubContainer Material:  Now the VDC SubContainer is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing VDC SubConrainer Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_DriftCellMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing VDC DriftCell Material: Looking up Material  " << G4endl; 
                VDC_DriftCellFront_Logical->SetMaterial(pttoMaterial);
		VDC_DriftCellBack_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing VDC DriftCell Material:  Now the VDC DriftCells are made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing VDC DriftCell Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_FoilMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing VDC Foil Material: Looking up Material  " << G4endl; 
                VDC_MylarFoil_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing VDC Foil Material: Now the VDC Foils are made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing VDC Foil Material failed" << G4endl; 
  }

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_WirePlaneMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing VDC WirePlane Material: Looking up Material  " << G4endl; 
                VDC_WirePlane_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing VDC WirePlane Material:  Now the VDC WirePlane is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing VDC WirePlane Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_G10FrameMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing VDC G10Frame Material: Looking up Material  " << G4endl; 
                VDC_G10Frame_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing G10Frame Material:  Now the VDC G10Frame is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing VDC G10Frame Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_AluFrameMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing VDC AluFrame Material: Looking up Material  " << G4endl; 
                VDC_AluFrame_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing AluFrame Material:  Now the VDC AluFrame is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing VDC AluFrame Material failed" << G4endl; 
  }

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::DestroyComponent()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_DriftCellFrontWireAngle(G4double frontWireAngle)
{
  G4cout << G4endl << "###### Calling QweakSimVDC::SetVDC_DriftCellFrontWireAngle() " << G4endl << G4endl;

  DriftCell_WireAngleFront = frontWireAngle;

  QweakSimVDC_DriftCellFrontSD::StoreDCUPlaneWireAngle(DriftCell_WireAngleFront);
  QweakSimVDC_DriftCellBackSD::StoreDCUPlaneWireAngle(DriftCell_WireAngleFront);

  SetVDC_DriftCellGeometryUpdate();				 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_DriftCellBackWireAngle(G4double backWireAngle)
{
G4cout << G4endl << "###### Calling QweakSimVDC::SetVDC_DriftCellbackWireAngle() " << G4endl << G4endl;

 DriftCell_WireAngleBack = backWireAngle;

 QweakSimVDC_DriftCellFrontSD::StoreDCVPlaneWireAngle(DriftCell_WireAngleBack);
 QweakSimVDC_DriftCellBackSD::StoreDCVPlaneWireAngle(DriftCell_WireAngleBack);

 SetVDC_DriftCellGeometryUpdate();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_DriftCellFullHeight(G4double fullHeight)
{
G4cout << G4endl << "###### Calling QweakSimVDC::SetVDC_DriftCellFullHeight() " << G4endl << G4endl;

 DriftCell_FullHeight = fullHeight;
 SetVDC_DriftCellGeometryUpdate();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_DriftCellFullWidthOnFrame(G4double fullWidthOnFrame)
{
G4cout << G4endl << "###### Calling QweakSimVDC::SetVDC_DriftCellFullWidthOnFrame() " << G4endl << G4endl;

 DriftCell_FullWidthOnFrame = fullWidthOnFrame;

 QweakSimVDC_DriftCellFrontSD::StoreDCWidthOnFrame(DriftCell_FullWidthOnFrame);
 QweakSimVDC_DriftCellBackSD::StoreDCWidthOnFrame(DriftCell_FullWidthOnFrame);

 SetVDC_DriftCellGeometryUpdate();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_DriftCellFullThickness(G4double fullThickness)
{
G4cout << G4endl << "###### Calling QweakSimVDC::SetVDC_DriftCellFullThickness() " << G4endl << G4endl;

 DriftCell_FullThickness = fullThickness;

 QweakSimVDC_DriftCellFrontSD::StoreDCFullThickness(DriftCell_FullThickness);
 QweakSimVDC_DriftCellBackSD::StoreDCFullThickness(DriftCell_FullThickness);

 SetVDC_DriftCellGeometryUpdate();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_DriftCellNumberPerPlane(G4int numberPerPlane)
{
G4cout << G4endl << "###### Calling QweakSimVDC::SetVDC_DriftCellFullWidthOnFrame() " << G4endl << G4endl;

  DriftCell_NumberPerPlane   =   numberPerPlane;
  SetVDC_DriftCellGeometryUpdate();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimVDC::SetVDC_DriftCellGeometryUpdate()
{
G4cout << G4endl << "###### Calling QweakSimVDC::SetVDC_DriftCellGeometryUpdate() " << G4endl << G4endl;


// redefine the drift cells according to the changed parameters

 VDC_DriftCellFront_Solid->SetAllParameters( 0.5* DriftCell_FullWidthOnFrame,
					     0.5* DriftCell_FullHeight,
					     0.5* DriftCell_FullThickness,
					     1.0* DriftCell_WireAngleFront,
					     0.0* degree,
					     0.0* degree);					 

 VDC_DriftCellBack_Solid->SetAllParameters( 0.5* DriftCell_FullWidthOnFrame,
					    0.5* DriftCell_FullHeight,
					    0.5* DriftCell_FullThickness,
					    1.0* DriftCell_WireAngleBack,
					    0.0* degree,
					    0.0* degree);					 
 

 // if exist, remove the current drift cells with the old parameters
 if(VDC_DriftCellFront_Physical)
   {
     VDC_DriftCellFrontContainer_Logical->RemoveDaughter(VDC_DriftCellFront_Physical);
     delete VDC_DriftCellFront_Physical;
   }

 if(VDC_DriftCellBack_Physical)
   {
     VDC_DriftCellBackContainer_Logical->RemoveDaughter(VDC_DriftCellBack_Physical);
     delete VDC_DriftCellBack_Physical;
   }


 // and rebuild from scratch the new drift cells and their arrangement

  G4VPVParameterisation* driftCellParam = new QweakSimVDC_DriftCellParameterisation( DriftCell_NumberPerPlane,
										 DriftCell_FullWidthOnFrame);

  //dummy value : kXAxis -- modified by parameterised volume
 
  VDC_DriftCellFront_Physical  = 
    new G4PVParameterised("VDC_DriftCellFront_Physical",         // their name
			    VDC_DriftCellFront_Logical,          // their logical volume
			    VDC_DriftCellFrontContainer_Logical, // Mother logical volume
			    kXAxis,                              // Are placed along this axis
			    DriftCell_NumberPerPlane,            // Number of drift cells
			    driftCellParam,                      // The parametrisation
			    pSurfChk);                           // Check overlaps


  VDC_DriftCellBack_Physical  = 
    new G4PVParameterised("VDC_DriftCellBack_Physical",          // their name
			    VDC_DriftCellBack_Logical,           // their logical volume
			    VDC_DriftCellBackContainer_Logical,  // Mother logical volume
			    kXAxis,                              // Are placed along this axis 
			    DriftCell_NumberPerPlane,            // Number of drift cells
			    driftCellParam,                      // The parametrisation
			    pSurfChk);                           // Check overlaps

  // we have to update QweakSimVDC_DriftCellSD  about a possible new DriftCell_NumberPerPlane value
  QweakSimVDC_DriftCellFrontSD::SetNumberOfDriftCellsPerPlane(DriftCell_NumberPerPlane);
  QweakSimVDC_DriftCellBackSD::SetNumberOfDriftCellsPerPlane(DriftCell_NumberPerPlane);
  
  // tell G4RunManager that we have changed the geometry
  G4RunManager::GetRunManager()->GeometryHasBeenModified();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetFrontVDC_CenterPositionInX(G4double xPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimVDC::SetFrontVDC_CenterPositionInX() " << G4endl << G4endl;

    VDC_CenterFront_XPos[pkg] = xPos;

    SetVDC_BackVDC_CenterPosition(pkg);
    SetVDC_DriftCell_MasterContainer_CenterPosition(pkg);

    VDC_MasterContainerFront_Physical[pkg]->SetTranslation(G4ThreeVector(VDC_CenterFront_XPos[pkg],
								    VDC_CenterFront_YPos[pkg],
								    VDC_CenterFront_ZPos[pkg]));

    VDC_MasterContainerBack_Physical[pkg]->SetTranslation(G4ThreeVector(VDC_CenterBack_XPos[pkg],
								   VDC_CenterBack_YPos[pkg],
								   VDC_CenterBack_ZPos[pkg]));

    VDC_DriftCellMasterContainer_Physical[pkg]->SetTranslation(G4ThreeVector(VDC_DriftCell_MasterContainer_XPos[pkg],
									VDC_DriftCell_MasterContainer_YPos[pkg],
									VDC_DriftCell_MasterContainer_ZPos[pkg]));

    G4cout << G4endl << "###### Leaving QweakSimVDC::SetFrontVDC_CenterPositionInX() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetFrontVDC_CenterPositionInY(G4double yPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimVDC::SetFrontVDC_CenterPositionInY() " << G4endl << G4endl;

    VDC_CenterFront_YPos[pkg] = yPos;

    SetVDC_BackVDC_CenterPosition(pkg);
    SetVDC_DriftCell_MasterContainer_CenterPosition(pkg);

    VDC_MasterContainerFront_Physical[pkg]->SetTranslation(G4ThreeVector(VDC_CenterFront_XPos[pkg],
								    VDC_CenterFront_YPos[pkg],
								    VDC_CenterFront_ZPos[pkg]));

    VDC_MasterContainerBack_Physical[pkg]->SetTranslation(G4ThreeVector(VDC_CenterBack_XPos[pkg],
								   VDC_CenterBack_YPos[pkg],
								   VDC_CenterBack_ZPos[pkg]));

    VDC_DriftCellMasterContainer_Physical[pkg]->SetTranslation(G4ThreeVector(VDC_DriftCell_MasterContainer_XPos[pkg],
									VDC_DriftCell_MasterContainer_YPos[pkg],
									VDC_DriftCell_MasterContainer_ZPos[pkg]));


 G4cout << G4endl << "###### Leaving QweakSimVDC::SetFrontVDC_CenterPositionInY() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetFrontVDC_CenterPositionInZ(G4double zPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimVDC::SetFrontVDC_CenterPositionInZ() " << G4endl << G4endl;

    VDC_CenterFront_ZPos[pkg] = zPos;

    SetVDC_BackVDC_CenterPosition(pkg);
    SetVDC_DriftCell_MasterContainer_CenterPosition(pkg);


    VDC_MasterContainerFront_Physical[pkg]->SetTranslation(G4ThreeVector(VDC_CenterFront_XPos[pkg],
								    VDC_CenterFront_YPos[pkg],
								    VDC_CenterFront_ZPos[pkg]));

    VDC_MasterContainerBack_Physical[pkg]->SetTranslation(G4ThreeVector(VDC_CenterBack_XPos[pkg],
								   VDC_CenterBack_YPos[pkg],
								   VDC_CenterBack_ZPos[pkg]));

    VDC_DriftCellMasterContainer_Physical[pkg]->SetTranslation(G4ThreeVector(VDC_DriftCell_MasterContainer_XPos[pkg],
									VDC_DriftCell_MasterContainer_YPos[pkg],
									VDC_DriftCell_MasterContainer_ZPos[pkg]));

    G4cout << G4endl << "###### Leaving QweakSimVDC::SetFrontVDC_CenterPositionInZ() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_BackVDC_CenterPosition(G4int pkg)
{

  // define VDC ContainerBack position in MotherVolume
  VDC_CenterBack_XPos[pkg]   = VDC_CenterFront_XPos[pkg];
  VDC_CenterBack_YPos[pkg]   = VDC_CenterFront_YPos[pkg] + VDC_FrontBackDistance*TMath::Tan(MeanTrackAngle/degree*TMath::DegToRad());
  VDC_CenterBack_ZPos[pkg]   = VDC_CenterFront_ZPos[pkg] + VDC_FrontBackDistance;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::SetVDC_DriftCell_MasterContainer_CenterPosition(G4int pkg)
{
  VDC_DriftCell_MasterContainer_XPos[pkg] = VDC_CenterFront_XPos[pkg];
  VDC_DriftCell_MasterContainer_YPos[pkg] = VDC_CenterFront_YPos[pkg];
  VDC_DriftCell_MasterContainer_ZPos[pkg] = VDC_CenterFront_ZPos[pkg] + 15.0*cm;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// pkg = 0  for package one, pkg = 1 for package 2.
void QweakSimVDC::SetVDC_RotationAngleInPhi(G4double vdc_phiangle, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimVDC::SetVDC_RotationAngleInPhi() " << G4endl << G4endl;
       
    //------------------------------------------------------
    //   VDC related
    //------------------------------------------------------
    G4ThreeVector Translation_VDC_ContainerFront;
    G4double VDCFront_RadialDistance = sqrt(VDC_CenterFront_XPos[pkg]*VDC_CenterFront_XPos[pkg] + VDC_CenterFront_YPos[pkg]*VDC_CenterFront_YPos[pkg]);
    //
    Translation_VDC_ContainerFront.setX(cos(vdc_phiangle)*VDCFront_RadialDistance) ;
    Translation_VDC_ContainerFront.setY(sin(vdc_phiangle)*VDCFront_RadialDistance) ;
    Translation_VDC_ContainerFront.setZ(VDC_CenterFront_ZPos[pkg]) ;
    //---    
    G4ThreeVector Translation_VDC_ContainerBack;
    G4double VDCBack_RadialDistance = sqrt(VDC_CenterBack_XPos[pkg]*VDC_CenterBack_XPos[pkg] + VDC_CenterBack_YPos[pkg]*VDC_CenterBack_YPos[pkg]);
    //
    Translation_VDC_ContainerBack.setX(cos(vdc_phiangle)*VDCBack_RadialDistance) ;
    Translation_VDC_ContainerBack.setY(sin(vdc_phiangle)*VDCBack_RadialDistance) ;
    Translation_VDC_ContainerBack.setZ(VDC_CenterBack_ZPos[pkg]);
    //------------------------------------------------------

    //------------------------------------------------------
    //   DriftCell related
    //------------------------------------------------------
    G4ThreeVector Translation_DriftCell_MasterContainer;
    G4double DriftCell_MasterContainer_RadialDistance = sqrt(VDC_DriftCell_MasterContainer_XPos[pkg]*VDC_DriftCell_MasterContainer_XPos[pkg] + VDC_DriftCell_MasterContainer_YPos[pkg]*VDC_DriftCell_MasterContainer_YPos[pkg]);
    //
    Translation_DriftCell_MasterContainer.setX(cos(vdc_phiangle)*DriftCell_MasterContainer_RadialDistance) ;
    Translation_DriftCell_MasterContainer.setY(sin(vdc_phiangle)*DriftCell_MasterContainer_RadialDistance) ;
    Translation_DriftCell_MasterContainer.setZ(VDC_DriftCell_MasterContainer_ZPos[pkg]) ;
    //------------------------------------------------------


    // assign new phi tilting angle 
    VDC_RotationAngleInPhi[pkg] = vdc_phiangle;
    Rotation_VDC_MasterContainer[pkg]      -> setPhi(VDC_RotationAngleInPhi[pkg] -90*degree);

    // Rotation of VDCs
    VDC_MasterContainerFront_Physical[pkg] -> SetRotation(Rotation_VDC_MasterContainer[pkg]);
    VDC_MasterContainerBack_Physical[pkg]  -> SetRotation(Rotation_VDC_MasterContainer[pkg]);
    VDC_MasterContainerFront_Physical[pkg] -> SetTranslation(Translation_VDC_ContainerFront);
    VDC_MasterContainerBack_Physical[pkg]  -> SetTranslation(Translation_VDC_ContainerBack);

    // Rotation of DriftCells
    VDC_DriftCellMasterContainer_Physical[pkg] -> SetRotation(Rotation_VDC_MasterContainer[pkg]);
    VDC_DriftCellMasterContainer_Physical[pkg] -> SetTranslation(Translation_DriftCell_MasterContainer);



    G4cout << G4endl << "###### Leaving QweakSimVDC::SetVDC_RotationAngleInPhi() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::PlaceVDC_MasterContainers()
{
	 G4cout << G4endl << "###### Calling QweakSimVDC::PlaceHDC_MasterContainers() " << G4endl << G4endl;


	  G4cout << G4endl << "###### QweakSimVDC: Define VDC_MasterContainerFront Orientation" << G4endl << G4endl;

	  // define VDC Container Orientation in MotherVolume
	  for (size_t i = 0; i < Rotation_VDC_MasterContainer.size(); i++) {
	  Rotation_VDC_MasterContainer[i]      = new G4RotationMatrix();
	  G4double Angle_VDC_MasterContainer = (-90.0+45.0+20.82)*degree;
	  Rotation_VDC_MasterContainer[i]       ->rotateX(Angle_VDC_MasterContainer);
	  
	  }


	  for (size_t i=0; i< VDC_MasterContainerFront_Physical.size();i++) {

	  G4cout << G4endl << "###### QweakSimVDC: Define VDC_MasterContainerFront Position" << G4endl << G4endl;

	  // define VDC MasterContainer Front position in MotherVolume
	  //VDC_CenterFront_ZPos = -600*cm; // just make an z offset for display
	  //VDC_CenterBack_ZPos  = -560*cm; // just make an z offset for display



	  G4ThreeVector position_MasterContainerFront = G4ThreeVector(VDC_CenterFront_XPos[i],VDC_CenterFront_YPos[i],VDC_CenterFront_ZPos[i] );

	  // define VDC MasterContainer Back position in MotherVolume
	  SetVDC_BackVDC_CenterPosition(i);

	  G4ThreeVector position_MasterContainerBack = G4ThreeVector(VDC_CenterBack_XPos[i],VDC_CenterBack_YPos[i],VDC_CenterBack_ZPos[i] );


	  G4cout << G4endl << "###### QweakSimVDC: Define VDC_MasterContainerFront_Physical" << G4endl << G4endl;

	  // define VDC physical volume of drift chamber container
	  VDC_MasterContainerFront_Physical[i] = new G4PVPlacement(Rotation_VDC_MasterContainer[i],
								position_MasterContainerFront,
								Form("VDC_MasterContainerFront_Physical%ld",i+1),
								VDC_MasterContainer_Logical,
								theMotherPV,
								false,
								2*i,
								pSurfChk); // copy number for front

	  G4cout << G4endl << "###### QweakSimVDC: Define VDC_MasterContainerBack_Physical" << G4endl << G4endl;

	  // define VDC physical volume of drift chamber container
	  VDC_MasterContainerBack_Physical[i] = new G4PVPlacement(Rotation_VDC_MasterContainer[i],
							       position_MasterContainerBack,
							       Form("VDC_MasterContainerBack_Physical%ld",i+1),
							       VDC_MasterContainer_Logical,
							       theMotherPV,
							       false,
							       2*i+1,
							       pSurfChk);// copy number for back
	  }
  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimVDC::PlaceVDC_DriftCellMasterContainers()
{


	  for (size_t i=0; i< VDC_DriftCellMasterContainer_Physical.size();i++) {

		  // define VDC Drift Cell Container position in MotherVolume
		  SetVDC_DriftCell_MasterContainer_CenterPosition(i);

		  G4ThreeVector position_DriftCellMasterContainer = G4ThreeVector(VDC_DriftCell_MasterContainer_XPos[i],
										  VDC_DriftCell_MasterContainer_YPos[i],
										  VDC_DriftCell_MasterContainer_ZPos[i] );

	  G4cout << G4endl << "###### QweakSimVDC: Define VDC_DriftCellMasterContainer_Physical " << G4endl << G4endl;
	  // define VDC physical volume of drift chamber container
	  VDC_DriftCellMasterContainer_Physical[i] = new G4PVPlacement(Rotation_VDC_MasterContainer[i],
								    position_DriftCellMasterContainer,
								    "VDC_DriftCellMasterContainer_Physical",
								    VDC_DriftCellMasterContainer_Logical,
								    theMotherPV,
								    false,
								    i,
								    pSurfChk);
	  }

}
