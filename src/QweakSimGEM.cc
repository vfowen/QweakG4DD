//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimGEM.cc

   $Revision: 1.3 $	
   $Date: 2005/12/29 01:00:11 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimGEM.hh"

// geant4 includes
#include "G4ProductionCuts.hh"

// user includes
#include "QweakSimMaterial.hh"
#include "QweakSimGEMMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimGEM::QweakSimGEM()
{
G4cout << G4endl << "###### Calling QweakSimGEM::QweakGEM() " << G4endl << G4endl;


 //---------------------------------------------------------------------------------------------------

//===============================
// cuts for G4Region and PAIModel
//===============================
fGammaCut    = 1*mm;    
fElectronCut = 1*mm; 
fPositronCut = 1*mm; 

fRegGasDet = NULL;



// initialize pointers

 Rotation_FrontChamber_GEM    = NULL;		
 Rotation_BackChamber_GEM     = NULL;		

 //---------------------------------------
 GEM_MasterContainer_Logical        = NULL;
 GEM_MasterContainerFront_Physical  = NULL;	
 GEM_MasterContainerBack_Physical   = NULL;

 GEM_SubContainer_Logical  = NULL;
 GEM_SubContainer_Physical = NULL;

 GEM_Frame_Logical      = NULL;
 GEM_Frame_Physical     = NULL;

 GEM_MiddleFoilContainer_Logical = NULL;
 GEM_MiddleFoilContainer_Physical = NULL;

 GEM_KaptonMiddleFoil_Logical  = NULL;
 GEM_KaptonMiddleFoil_Physical = NULL;

 GEM_CopperMiddleFoil_Logical        = NULL;
 GEM_TopCopperMiddleFoil_Physical    = NULL;
 GEM_BottomCopperMiddleFoil_Physical = NULL;

 GEM_AnodeReadoutPlaneContainer_Logical   = NULL;
 GEM_AnodeReadoutPlaneContainer_Physical  = NULL;

 GEM_AnodeReadoutBoard_Logical  = NULL;
 GEM_AnodeReadoutBoard_Physical = NULL;

 GEM_AnodeCopperLayer_Logical  = NULL;
 GEM_AnodeCopperLayer_Physical = NULL;

 GEM_CathodeHVPlaneContainer_Logical  = NULL;
 GEM_CathodeHVPlaneContainer_Physical = NULL;

 GEM_CathodeHVCopperLayer_Logical  = NULL;
 GEM_CathodeHVCopperLayer_Physical = NULL;
 //--------------------------------------------

 GEM_Messenger = NULL;

 //---------------------------------------------
 GEM_MasterContainer_VisAtt              = NULL;  
 GEM_SubContainer_VisAtt                 = NULL;  
 GEM_Frame_VisAtt                        = NULL;
 
 GEM_MiddleFoilContainer_VisAtt          = NULL;
 GEM_KaptonMiddleFoil_VisAtt             = NULL;
 GEM_CopperMiddleFoil_VisAtt             = NULL;

 GEM_AnodeReadoutPlaneContainer_VisAtt   = NULL;
 GEM_AnodeReadoutBoard_VisAtt            = NULL;
 GEM_AnodeCopperLayer_VisAtt             = NULL;

 GEM_CathodeHVPlaneContainer_VisAtt      = NULL;
 GEM_CathodeHVCopperLayer_VisAtt         = NULL;
 //---------------------------------------------

 GEMdriftChamberSD = NULL;
 GEM_Frame_Solid   = NULL;

 //---------------------------------------------------------------------------------------------------
  
 // define target geometry value
 // Geometry taken from Norm's GEM talk in Vancouver 2005

  GEMFrame_Thickness               =  30*mm; // 

  GEMFrame_InnerLength             =  300*mm; // X  
  GEMFrame_InnerWidth              =  300*mm; // Y

  GEMFrame_OuterLength             =  350*mm; // X
  GEMFrame_OuterWidth              =  350*mm; // Y

  GEMFrame_BorderWidthInX          =  0.5*( GEMFrame_OuterLength - GEMFrame_InnerLength )*cm;
  GEMFrame_BorderWidthInY          =  0.5*( GEMFrame_OuterWidth  - GEMFrame_InnerWidth  )*cm;


  GEM_KaptonCathodeFoil_Thickness  = 0.050*mm; //  50um 
  GEM_KaptonMiddleFoil_Thickness   = 0.050*mm; //  50um 
  GEM_KaptonAnodeFoil_Thickness    = 0.050*mm; //  50um
  GEM_G10AnodeBoard_Thickness      = 0.300*mm; // 300um 
  GEM_CopperLayer_Thickness        = 0.005*mm; //   5um


  // Tony Forest did not mention it, but I suppose that the GEM will
  // sandwiched between 2 alu plates for stability.
  AluFrame_Thickness        =  1.0*cm; 
  AluFrame_OuterLength      =  GEMFrame_OuterLength;
  AluFrame_OuterWidth       =  GEMFrame_OuterWidth;
  AluFrame_InnerLength      =  GEMFrame_InnerLength;
  AluFrame_InnerWidth       =  GEMFrame_InnerWidth;

  GEM_CenterFront_XPos        =    0.0*cm;
  GEM_CenterFront_YPos        =   25.0*cm; //15.0*cm; 
  GEM_CenterFront_ZPos        = -543.170*cm; // Allena's keepout info 

  GEM_CenterBack_XPos        =    0.0*cm;
  GEM_CenterBack_YPos        =   25.0*cm; //17.0*cm; 
  GEM_CenterBack_ZPos        = -535.0*cm; 

  
  // define Rotation matrix for Container orientated in MotherVolume
  Rotation_FrontChamber_GEM  = new G4RotationMatrix();
  Rotation_BackChamber_GEM   = new G4RotationMatrix();

  GEM_FrontChamber_RotationAngleInPhi  =   90.0*degree;   // normally 90.0*degree = 12 o'clock = octant 1
  GEM_BackChamber_RotationAngleInPhi   =   90.0*degree;   // normally 90.0*degree = 12 o'clock = octant 1



  GEM_Messenger = new QweakSimGEMMessenger(this);
  
  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();

 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimGEM::~QweakSimGEM()
{
 
    // delete pointers


 

  //----------------------
  if (GEM_KaptonMiddleFoil_VisAtt)              delete GEM_KaptonMiddleFoil_VisAtt;
  if (GEM_CopperMiddleFoil_VisAtt)              delete GEM_CopperMiddleFoil_VisAtt;
  if (GEM_MiddleFoilContainer_VisAtt)           delete GEM_MiddleFoilContainer_VisAtt; 
  //
  if (GEM_AnodeReadoutBoard_VisAtt)             delete GEM_AnodeReadoutBoard_VisAtt;            
  if (GEM_AnodeCopperLayer_VisAtt)              delete GEM_AnodeCopperLayer_VisAtt;          
  if (GEM_AnodeReadoutPlaneContainer_VisAtt)    delete GEM_AnodeReadoutPlaneContainer_VisAtt;
  //
  if (GEM_CathodeHVCopperLayer_VisAtt)          delete GEM_CathodeHVCopperLayer_VisAtt;      
  if (GEM_CathodeHVPlaneContainer_VisAtt)       delete GEM_CathodeHVPlaneContainer_VisAtt;    
  //
  if (GEM_Frame_VisAtt)                         delete GEM_Frame_VisAtt;
  if (GEM_SubContainer_VisAtt)                  delete GEM_SubContainer_VisAtt;
  if (GEM_MasterContainer_VisAtt)               delete GEM_MasterContainer_VisAtt;
  //----------------------

  //----------------------
  if (GEM_KaptonMiddleFoil_Physical)             delete GEM_KaptonMiddleFoil_Physical;
  if (GEM_KaptonMiddleFoil_Logical)              delete GEM_KaptonMiddleFoil_Logical;
  //
  if (GEM_TopCopperMiddleFoil_Physical)          delete GEM_TopCopperMiddleFoil_Physical; 
  if (GEM_BottomCopperMiddleFoil_Physical)       delete GEM_BottomCopperMiddleFoil_Physical;
  if (GEM_CopperMiddleFoil_Logical)              delete GEM_CopperMiddleFoil_Logical;
  //
  if (GEM_MiddleFoilContainer_Physical)          delete GEM_MiddleFoilContainer_Physical;
  if (GEM_MiddleFoilContainer_Logical)           delete GEM_MiddleFoilContainer_Logical;
  //----------------------
  //
  //----------------------
  if (GEM_AnodeCopperLayer_Physical)             delete GEM_AnodeCopperLayer_Physical;
  if (GEM_AnodeCopperLayer_Logical)              delete GEM_AnodeCopperLayer_Logical;
  //
  if (GEM_AnodeReadoutBoard_Physical)            delete GEM_AnodeReadoutBoard_Physical;
  if (GEM_AnodeReadoutBoard_Logical)             delete GEM_AnodeReadoutBoard_Logical;
  //
  if (GEM_AnodeReadoutPlaneContainer_Physical)   delete GEM_AnodeReadoutPlaneContainer_Physical;
  if (GEM_AnodeReadoutPlaneContainer_Logical)    delete GEM_AnodeReadoutPlaneContainer_Logical; 
  //----------------------
  //
  //--------------------------------------------
  if (GEM_CathodeHVCopperLayer_Physical)         delete GEM_CathodeHVCopperLayer_Physical;
  if (GEM_CathodeHVCopperLayer_Logical)          delete GEM_CathodeHVCopperLayer_Logical;
  //
  if (GEM_CathodeHVPlaneContainer_Physical)      delete GEM_CathodeHVPlaneContainer_Physical; 
  if (GEM_CathodeHVPlaneContainer_Logical)       delete GEM_CathodeHVPlaneContainer_Logical; 
  //--------------------------------------------
  //
  //---------------------------------------
  if (GEM_Frame_Physical)                        delete GEM_Frame_Physical;
  if (GEM_Frame_Logical)                         delete GEM_Frame_Logical;
  //
  if (GEM_SubContainer_Physical)                 delete GEM_SubContainer_Physical;
  if (GEM_SubContainer_Logical)                  delete GEM_SubContainer_Logical; 
  //
  if (GEM_MasterContainerFront_Physical)         delete GEM_MasterContainerFront_Physical; 
  if (GEM_MasterContainerBack_Physical)          delete GEM_MasterContainerBack_Physical;
  if (GEM_MasterContainer_Logical)               delete GEM_MasterContainer_Logical;
  //---------------------------------------
  
  if (Rotation_FrontChamber_GEM)                delete Rotation_FrontChamber_GEM;   
  if (Rotation_BackChamber_GEM)                 delete Rotation_BackChamber_GEM;
 
  if (GEM_Frame_Solid)                          delete GEM_Frame_Solid; 	
      
  if (pMaterial)                                delete pMaterial; 
  if (GEM_Messenger)                            delete GEM_Messenger;
  
  //if (GEMdriftChamberSD)                        delete GEMdriftChamberSD; // causes crash

  //---------------------------------------

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimGEM::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
  G4cout << G4endl << "###### Calling QweakSimGEM::ConstructComponent() " << G4endl << G4endl;
 
  // definition of a mil = inch/1000
  //static const G4double mil = 0.001*2.54*cm;


  // assign material
  G4Material* GEM_MasterContainer_Material    = pMaterial->GetMaterial("Air");   
  G4Material* GEM_SubContainer_Material       = pMaterial->GetMaterial("ArCO2");   
  G4Material* GEM_Frame_Material              = pMaterial->GetMaterial("NemaG10");  
  G4Material* GEM_Foil_Material               = pMaterial->GetMaterial("Kapton"); 
  G4Material* GEM_CopperLayer_Material        = pMaterial->GetMaterial("Copper"); 


  // define  solid volume of the drift chamber container
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_MasterContainer_Solid" << G4endl << G4endl;
  
  G4Box* GEM_MasterContainer_Solid    = new G4Box("GEM_MasterContainer_Sol",
						  0.5* GEMFrame_OuterLength,
						  0.5* GEMFrame_OuterWidth,
						  0.5* GEMFrame_Thickness +0.1*mm); 

  // define GEM logical volume of drift chamber container
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_MasterContainer_Logical " << G4endl << G4endl;
  
  GEM_MasterContainer_Logical  = new G4LogicalVolume(GEM_MasterContainer_Solid,
						     GEM_MasterContainer_Material,
						     "GEM_MasterContainer_Log",
						     0,0,0);

  // define GEM MasterContainer positions in MotherVolume
  G4ThreeVector position_MasterContainerFront = G4ThreeVector(GEM_CenterFront_XPos , GEM_CenterFront_YPos , GEM_CenterFront_ZPos );
  G4ThreeVector position_MasterContainerBack  = G4ThreeVector(GEM_CenterBack_XPos  , GEM_CenterBack_YPos  , GEM_CenterBack_ZPos );


  // define GEM Container Orientation in MotherVolume
  G4double roationAngleInTheta = 0.0*degree;
  Rotation_FrontChamber_GEM -> rotateX(roationAngleInTheta);
  Rotation_BackChamber_GEM  -> rotateX(roationAngleInTheta);

  // define GEM physical volume of drift chamber container
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_MasterContainerFront_Physical" << G4endl << G4endl;

  GEM_MasterContainerFront_Physical = new G4PVPlacement(Rotation_FrontChamber_GEM, 
							position_MasterContainerFront, 
							"GEM_MasterContainerFront_Physical", 
							GEM_MasterContainer_Logical,
							MotherVolume,   
							false, 
							0,
							pSurfChk); // copy number for front



  // define GEM physical volume of drift chamber container
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_MasterContainerBack_Physical" << G4endl << G4endl;

  GEM_MasterContainerBack_Physical = new G4PVPlacement(Rotation_BackChamber_GEM, 
						       position_MasterContainerBack, 
						       "GEM_MasterContainerBack_Physical", 
						       GEM_MasterContainer_Logical,
						       MotherVolume,   
						       false, 
						       1,
						       pSurfChk);// copy number for back


  //====================================================================
  // Definition of the GEM Frame ( symbolizes the stack of real frames )
  //====================================================================

  // define outer frame solid
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_OuterFrame_Solid" << G4endl << G4endl;

  G4Box* GEM_OuterFrame_Solid    = new G4Box("GEM_OuterFrame_Sol",
					     0.5* GEMFrame_OuterLength,
					     0.5* GEMFrame_OuterWidth,
					     0.5* GEMFrame_Thickness); 

  // define inner frame solid
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_InnerFrame_Solid" << G4endl << G4endl;

  G4Box* GEM_InnerFrame_Solid    = new G4Box("GEM_InnerFrame_Sol",
					     0.5* GEMFrame_InnerLength,
					     0.5* GEMFrame_InnerWidth,
					     0.5* GEMFrame_Thickness + 0.1*mm); 


 // create frame by subtracting outer framebox from inner framebox
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_Frame_Solid" << G4endl << G4endl;

  GEM_Frame_Solid  =  new G4SubtractionSolid("GEM_Frame",
					     GEM_OuterFrame_Solid, 
					     GEM_InnerFrame_Solid); 


  G4cout << G4endl << "###### QweakSimGEM: Define GEM_Frame_Logical" << G4endl << G4endl;
  GEM_Frame_Logical  = new G4LogicalVolume(GEM_Frame_Solid,
					   GEM_Frame_Material,
					   "GEM_Frame_Log",
					   0,0,0);


  // define the position of the Frame within the GEM Container: put it in the center of GEM container 
  G4ThreeVector position_Frame = G4ThreeVector(0. , 0. , 0.);
  
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_Frame_Physical" << G4endl << G4endl;
  
  GEM_Frame_Physical =   new G4PVPlacement(0,                          // no rotation matrix needed 
					   position_Frame, 
					   GEM_Frame_Logical, 
					   "GEM_Frame_Physical",
					   GEM_MasterContainer_Logical, 
					   0, 
					   0,
					   pSurfChk); //copy number: 0


  //======================================================================================
  // Definition of the GEM SubContainer holding the stack of foil planes and readout plane
  //======================================================================================
  

  // define outer frame solid
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_SubContainer_Solid" << G4endl << G4endl;
  
  G4Box* GEM_SubContainer_Solid    = new G4Box("GEM_OuterFrame_Sol",
					       0.5* GEMFrame_InnerLength, // X
					       0.5* GEMFrame_InnerWidth,  // Y
					       0.5* GEMFrame_Thickness);  // Z
  
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_SubContainer_Logical" << G4endl << G4endl;
  
  GEM_SubContainer_Logical  = new G4LogicalVolume(GEM_SubContainer_Solid,
						  GEM_SubContainer_Material,
						  "GEM_SubContainer_Log",
						  0,0,0);
  

 // define the position of the SubContainer within the GEM Container: put it in the center of GEM container 
  G4ThreeVector position_SubContainer = G4ThreeVector(0. , 0. , 0.);
  
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_SubContainer_Physical" << G4endl << G4endl;
  
  GEM_SubContainer_Physical =   new G4PVPlacement(0,                          // no rotation matrix needed 
						  position_SubContainer, 
						  GEM_SubContainer_Logical, 
						  "GEM_SubContainer_Physical",
						  GEM_MasterContainer_Logical, 
						  0, 
						  0,
						  pSurfChk); //copy number: 0



  //====================================================================
  //             Definition of the GEM Foils 
  //====================================================================


  // define a container holding a 50um thick Kapton foil coated with 5um Copper
  // on each side.
  // Construction: create 60um thick copper box and insert a 50um thick Kapton box

  G4cout << G4endl << "###### QweakSimGEM: Define GEM_MiddleFoilContainer_Solid" << G4endl << G4endl;
  
  G4Box* GEM_MiddleFoilContainer_Solid    = new G4Box("GEM_MiddleFoilContainer_Sol",
						      0.5* GEMFrame_InnerLength,
						      0.5* GEMFrame_InnerWidth,
						      0.5* (GEM_KaptonMiddleFoil_Thickness+2*GEM_CopperLayer_Thickness) ); 

  // define foil logical
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_MiddleFoilContainer_Logical" << G4endl << G4endl;
  
  GEM_MiddleFoilContainer_Logical  = new G4LogicalVolume(GEM_MiddleFoilContainer_Solid,
							 GEM_SubContainer_Material,
							 "GEM_MiddleFoilContainer_Log",
							 0,0,0);

  //==================================
  // create the 50um thick Kapton foil 
  //==================================
  G4Box* GEM_KaptonMiddleFoil_Solid    = new G4Box("GEM_KaptonMiddleFoil_Sol",
						   0.5* GEMFrame_InnerLength,
						   0.5* GEMFrame_InnerWidth,
						   0.5* GEM_KaptonMiddleFoil_Thickness); 
  
  // define foil logical
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_KaptonMiddleFoil_Logical" << G4endl << G4endl;

  GEM_KaptonMiddleFoil_Logical  = new G4LogicalVolume(GEM_KaptonMiddleFoil_Solid,
						      GEM_Foil_Material,
						      "GEM_KaptonMiddleFoil_Log",
						      0,0,0);
  
  // place 50um thick Kapton box into the 60um thick Copper box
  GEM_KaptonMiddleFoil_Physical  =  new G4PVPlacement(0, 
						      G4ThreeVector(0. , 0. , 0. ), 
						      GEM_KaptonMiddleFoil_Logical, 
						      "GEM_KaptonMiddleFoil_Physical",
						      GEM_MiddleFoilContainer_Logical, 
						      0, 
						      0,
						      pSurfChk); //copy number 0

  //=====================================
  // define 5um thick Middle GEM foil copper layer
  //====================================

  // define solid
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_CopperLayer_Solid" << G4endl << G4endl;
    
  G4Box* GEM_CopperLayer_Solid    =  new G4Box("GEM_CopperLayer_Sol",
					       0.5* GEMFrame_InnerLength,
					       0.5* GEMFrame_InnerWidth,
					       0.5* GEM_CopperLayer_Thickness); 

  // define logical
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_CopperMiddleFoil_Logical" << G4endl << G4endl;
  
  GEM_CopperMiddleFoil_Logical  = new G4LogicalVolume(GEM_CopperLayer_Solid,
						      GEM_CopperLayer_Material,
						      "GEM_CopperMiddleFoil_Log",
						      0,0,0);

 // define physical
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_CopperMiddleFoil_Physical" << G4endl << G4endl;

  // Z Location of the CopperLayer within GEM_MiddleFoilContainer:
  // (first go to border of box and go half the copper layer thickness back)
  G4double _LocalPostionInZ_TopCopperLayer =
      +  0.5*(GEM_KaptonMiddleFoil_Thickness+2*GEM_CopperLayer_Thickness) - 0.5*  GEM_CopperLayer_Thickness; 

  G4double _LocalPostionInZ_BottomCopperLayer =
      -  0.5*(GEM_KaptonMiddleFoil_Thickness+2*GEM_CopperLayer_Thickness) + 0.5*  GEM_CopperLayer_Thickness; 



  // place copper top layer
 GEM_TopCopperMiddleFoil_Physical =  
     new G4PVPlacement(0, 
		       G4ThreeVector(0. , 0. , _LocalPostionInZ_TopCopperLayer ), 
		       GEM_CopperMiddleFoil_Logical, 
		       "GEM_TopCopperMiddleFoil_Physical",
		       GEM_MiddleFoilContainer_Logical, 
		       0, 
		       0,
		       pSurfChk); //copy number for top layer

   // place copper bottom layer
 GEM_BottomCopperMiddleFoil_Physical =
     new G4PVPlacement(0, 		
		       G4ThreeVector(0. , 0. , _LocalPostionInZ_BottomCopperLayer ), 
		       GEM_CopperMiddleFoil_Logical, 
		       "GEM_BottomCopperMiddleFoil_Physical",
		       GEM_MiddleFoilContainer_Logical, 
		       0, 
		       0,
		       pSurfChk); //copy number for bottom layer



  // Z Location of the double sided copper coated Kapton foils in the GEM stack
  // 0.0*mm: Bottom side of Readout Frame, 30*mm: Top side of window frame
  G4double GEM_MiddleFoil_PositionInZ[3] = {7*mm, 9*mm, 11*mm};
 
  // define foil physical
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_MiddleFoilContainer_Physical" << G4endl << G4endl;

  for( G4int index = 0; index < 3; index++){
      
      new G4PVPlacement(0, 
			G4ThreeVector(0. , 0. , -1.0*GEM_MiddleFoil_PositionInZ[index] + 0.5*GEMFrame_Thickness), 
			GEM_MiddleFoilContainer_Logical, 
			"GEM_MiddleFoilContainer_Physical",
			GEM_SubContainer_Logical, 
			0, 
			index,
			pSurfChk); //copy number
      
    } // end for
  
  //====================================================================
  // Definition of the GEM Readout Plane 
  //====================================================================
  
  // Readout Plane contains: 300um G10 board (beam downstream) 
  //                         50um Kapton,
  //                         5um Copper      (beam upstream) 
  // 
  // Construction: create 355um thick Kapton box, 
  //               place G10 board inside to bottom side, place copper box inside to to side 
  
  // define solid
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_AnodeReadoutPlaneContainer_Solid" << G4endl << G4endl;
  
  G4Box* GEM_AnodeReadoutPlaneContainer_Solid    = 
      new G4Box("GEM_AnodeReadoutPlaneContainer_Sol",
		0.5* GEMFrame_InnerLength,
		0.5* GEMFrame_InnerWidth,
		0.5* (GEM_G10AnodeBoard_Thickness + GEM_CopperLayer_Thickness + GEM_KaptonAnodeFoil_Thickness) ); 
  
  // define logical
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_AnodeReadoutPlaneContainer_Logical" << G4endl << G4endl;
  
  GEM_AnodeReadoutPlaneContainer_Logical  = new G4LogicalVolume(GEM_AnodeReadoutPlaneContainer_Solid,
								GEM_Foil_Material,
								"GEM_AnodeReadoutPlaneContainer_Log",
								0,0,0);

  //=============================
  // define 300um thick G10 board
  //=============================
  
  // define solid
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_AnodeReadoutBoard_Solid" << G4endl << G4endl;
  
  G4Box* GEM_AnodeReadoutBoard_Solid    =  new G4Box("GEM_AnodeReadoutBoard_Sol",
						     0.5* GEMFrame_InnerLength,
						     0.5* GEMFrame_InnerWidth,
						     0.5* GEM_G10AnodeBoard_Thickness); 
  
  // define logical
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_AnodeReadoutBoard_Logical" << G4endl << G4endl;
  
  GEM_AnodeReadoutBoard_Logical  = new G4LogicalVolume(GEM_AnodeReadoutBoard_Solid,
						       GEM_Frame_Material,
						       "GEM_AnodeReadoutBoard_Log",
						       0,0,0);
  
  // define physical
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_AnodeReadoutBoard_Physical" << G4endl << G4endl;
  
  // Z Location of the AnodeReadoutBoard within GEM_AnodeReadoutPlaneContainer: +0.5*355um - 0.5*300um  
  // (first go to border of box and go half the G10 board thickness back)

  G4double _LocalPostionInZ_AnodeReadoutBoard =
      +0.5* (GEM_G10AnodeBoard_Thickness + GEM_CopperLayer_Thickness + GEM_KaptonAnodeFoil_Thickness)
     - 0.5*  GEM_G10AnodeBoard_Thickness; 

  GEM_AnodeReadoutBoard_Physical  =  new G4PVPlacement(0, 
						       G4ThreeVector(0. , 0. , _LocalPostionInZ_AnodeReadoutBoard ), 
						       GEM_AnodeReadoutBoard_Logical, 
						       "GEM_AnodeReadoutBoard_Physical",
						       GEM_AnodeReadoutPlaneContainer_Logical, 
						       0, 
						       0,
						       pSurfChk); //copy number
  

  //=====================================
  // define 5um thick Anode copper layer
  //====================================

  // define solid
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_AnodeCopperLayer_Solid" << G4endl << G4endl;
    
  G4Box* GEM_AnodeCopperLayer_Solid    =  new G4Box("GEM_AnodeCopperLayer_Sol",
						    0.5* GEMFrame_InnerLength,
						    0.5* GEMFrame_InnerWidth,
						    0.5* GEM_CopperLayer_Thickness); 

  // define logical
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_AnodeCopperLayer_Logical" << G4endl << G4endl;
  
  GEM_AnodeCopperLayer_Logical  = new G4LogicalVolume(GEM_AnodeCopperLayer_Solid,
						      GEM_CopperLayer_Material,
						      "GEM_AnodeCopperLayer_Log",
						      0,0,0);

 // define physical
  G4cout << G4endl << "###### QweakSimGEM: Define GEM_AnodeCopperLayer_Physical" << G4endl << G4endl;

  // Z Location of the AnodeCopperLayer within GEM_AnodeReadoutPlaneContainer: -0.5*355um + 0.5*5um  
  // (first go to border of box and go half the (G10 board thickness + copper layer thickness) back
  // )
  G4double _LocalPostionInZ_AnodeCopperLayer =
      -0.5* (GEM_G10AnodeBoard_Thickness + GEM_CopperLayer_Thickness + GEM_KaptonAnodeFoil_Thickness)
     + 0.5*  GEM_CopperLayer_Thickness; 


   GEM_AnodeCopperLayer_Physical  =  new G4PVPlacement(0, 
						       G4ThreeVector(0. , 0. , _LocalPostionInZ_AnodeCopperLayer ), 
						       GEM_AnodeCopperLayer_Logical, 
						       "GEM_AnodeCopperLayer_Physical",
						       GEM_AnodeReadoutPlaneContainer_Logical, 
						       0, 
						       0,
						       pSurfChk); //copy number



   //===========================================================
   // finally place the GEM Readout Plane within the foil stack
   //===========================================================
   //
   // Z Location of the AnodeCopperLayer within GEM_AnodeReadoutPlaneContainer: +0.5*355um - 0.5*5um  
   // (first go to border of box and go half the copper layer thickness back)


  G4double _LocalPostionInZ_AnodeReadoutPlaneContainer =
      (   -5*mm 
	+ 0.5* (GEM_G10AnodeBoard_Thickness + GEM_CopperLayer_Thickness + GEM_KaptonAnodeFoil_Thickness))
        + 0.5*GEMFrame_Thickness ; 

   GEM_AnodeReadoutPlaneContainer_Physical  =  
       new G4PVPlacement(0, 
			 G4ThreeVector(0. , 0. , _LocalPostionInZ_AnodeReadoutPlaneContainer ), 
			 GEM_AnodeReadoutPlaneContainer_Logical, 
			 "GEM_AnodeReadoutPlaneContainer_Physical",
			 GEM_SubContainer_Logical, 
			 0, 
			 0,
			 pSurfChk); //copy number


   //====================================================================
   // Definition of the GEM cathode HV Plane 
   //====================================================================
   
   // Cathode HV Plane contains: 50um Kapton,    (beam upstream)
   //                            5um Copper      (beam downstream) 
   // 
   // Construction: create 55um thick Kapton box, 
   //               place 5um copper box within touching the downstream border 
   
   // define solid
   G4cout << G4endl << "###### QweakSimGEM: Define GEM_CathodeHVPlaneContainer_Solid" << G4endl << G4endl;
   
   G4Box* GEM_CathodeHVPlaneContainer_Solid    = 
       new  G4Box("GEM_CathodeHVPlaneContainer_Sol",
		  0.5* GEMFrame_InnerLength,
		  0.5* GEMFrame_InnerWidth,
		  0.5* (GEM_CopperLayer_Thickness + GEM_KaptonCathodeFoil_Thickness) ); 

   // define logical
   G4cout << G4endl << "###### QweakSimGEM: Define GEM_CathodeHVPlaneContainer_Logical" << G4endl << G4endl;
   
   GEM_CathodeHVPlaneContainer_Logical  = new G4LogicalVolume(GEM_CathodeHVPlaneContainer_Solid,
								 GEM_Foil_Material,
								 "GEM_CathodeHVPlaneContainer_Log",
								 0,0,0);

   //========================================
   // define 5um thick Cathode copper layer
   //============================--========

   // define solid
   G4cout << G4endl << "###### QweakSimGEM: Define GEM_CathodeCopperLayer_Solid" << G4endl << G4endl;
   
   G4Box* GEM_CathodeHVCopperLayer_Solid    =  new G4Box("GEM_CathodeHVCopperLayer_Sol",
						       0.5* GEMFrame_InnerLength,
						       0.5* GEMFrame_InnerWidth,
						       0.5* GEM_CopperLayer_Thickness); 
   
   // define logical
   G4cout << G4endl << "###### QweakSimGEM: Define GEM_CathodeHVCopperLayer_Logical" << G4endl << G4endl;
   
   GEM_CathodeHVCopperLayer_Logical  = new G4LogicalVolume(GEM_CathodeHVCopperLayer_Solid,
							 GEM_CopperLayer_Material,
							 "GEM_CathodeHVCopperLayer_Log",
							 0,0,0);
   
   // define physical
   G4cout << G4endl << "###### QweakSimGEM: Define GEM_CathodeCopperLayer_Physical" << G4endl << G4endl;
   
   // Z Location of the AnodeCopperLayer within GEM_AnodeReadoutPlaneContainer: +0.5*55um - 0.5*5um  
   // (first go to border of box and go half the copper layer thickness back
   // )
  G4double _LocalPostionInZ_CathodeHVCopperLayer =
       0.5* (GEM_CopperLayer_Thickness + GEM_KaptonCathodeFoil_Thickness)
     - 0.5*  GEM_CopperLayer_Thickness; 
  
  GEM_CathodeHVCopperLayer_Physical  =  new G4PVPlacement(0, 
							G4ThreeVector(0. , 0. , _LocalPostionInZ_CathodeHVCopperLayer ), 
							GEM_CathodeHVCopperLayer_Logical, 
							"GEM_CathodeHVCopperLayer_Physical",
							GEM_CathodeHVPlaneContainer_Logical, 
							0, 
							0,
							pSurfChk); //copy number



  //===========================================================
  // finally place the GEM Cathode HV Plane within the foil stack
  //===========================================================
  //
  // Z Location of the CathodeHVPlaneLayer within Container:
  // (first go to border of box and go half the copper layer thickness back)


  G4double _LocalPostionInZ_CathodeHVPlaneContainer = -14*mm + 0.5*GEMFrame_Thickness ; 

   GEM_CathodeHVPlaneContainer_Physical  =  
       new G4PVPlacement(0, 
			 G4ThreeVector(0. , 0. , _LocalPostionInZ_CathodeHVPlaneContainer ), 
			 GEM_CathodeHVPlaneContainer_Logical, 
			 "GEM_CathodeHVPlaneContainer_Physical",
			 GEM_SubContainer_Logical, 
			 0, 
			 0,
			 pSurfChk); //copy number


//================================================================================================


G4cout << G4endl << "###### QweakSimGEM: Setting Sensitive Detectors " << G4endl << G4endl;

  // Sensitive detectors
  //------------------------------------------------ 
  // All managed (deleted) by SDManager

   G4SDManager* SDman = G4SDManager::GetSDMpointer();


   //#######################################################
   // define drift chamber elements as sensitiv detectors
   // "sensitivity" will be handled by class QweakSimGEMSD
   //#######################################################


   //***********************************************************
   GEMdriftChamberSD = new QweakSimGEM_WirePlaneSD("GEMWirePlaneSD");
   SDman->AddNewDetector(GEMdriftChamberSD);
   
   // add wire plane as a sensitiv element
   GEM_AnodeCopperLayer_Logical->SetSensitiveDetector(GEMdriftChamberSD);
   //***********************************************************


G4cout << G4endl << "###### QweakSimGEM: Setting Attributes " << G4endl << G4endl;

  G4Colour  orange (241/255.,224/255.,0/255.);
  G4Colour  gray   (210/255.,213/255.,210/255.);

  G4Colour  red   (255/255.,   0/255.,0/255.);
  G4Colour  green (  0/255., 255/255.,0/255.);
  G4Color   green_yellow (173/255., 255/255., 47/255.);


  GEM_MasterContainer_VisAtt  =  new G4VisAttributes(orange);
  GEM_MasterContainer_VisAtt  -> SetVisibility(false);
  GEM_MasterContainer_Logical -> SetVisAttributes(GEM_MasterContainer_VisAtt); 

  GEM_SubContainer_VisAtt  =  new G4VisAttributes(red);
  GEM_SubContainer_VisAtt  -> SetVisibility(false);
  GEM_SubContainer_Logical -> SetVisAttributes(GEM_SubContainer_VisAtt); 

  GEM_Frame_VisAtt  =  new G4VisAttributes(green);
  GEM_Frame_VisAtt  -> SetVisibility(true);
  GEM_Frame_Logical -> SetVisAttributes(GEM_Frame_VisAtt); 

  //------------------------------------------------------------------------------
  GEM_MiddleFoilContainer_VisAtt  =  new G4VisAttributes(gray);
  GEM_MiddleFoilContainer_VisAtt  -> SetVisibility(false);
  GEM_MiddleFoilContainer_Logical -> SetVisAttributes(GEM_MiddleFoilContainer_VisAtt);
  //
  GEM_KaptonMiddleFoil_VisAtt  =  new G4VisAttributes(gray);
  GEM_KaptonMiddleFoil_VisAtt  -> SetVisibility(true);
  GEM_KaptonMiddleFoil_Logical -> SetVisAttributes(GEM_KaptonMiddleFoil_VisAtt);
  //
  GEM_CopperMiddleFoil_VisAtt  =  new G4VisAttributes(orange);
  GEM_CopperMiddleFoil_VisAtt  -> SetVisibility(true);
  GEM_CopperMiddleFoil_Logical -> SetVisAttributes(GEM_CopperMiddleFoil_VisAtt);
  //------------------------------------------------------------------------------
  GEM_AnodeReadoutPlaneContainer_VisAtt  =  new G4VisAttributes(gray);
  GEM_AnodeReadoutPlaneContainer_VisAtt  -> SetVisibility(false);
  GEM_AnodeReadoutPlaneContainer_VisAtt  -> SetForceWireframe(true);
  GEM_AnodeReadoutPlaneContainer_Logical -> SetVisAttributes(GEM_AnodeReadoutPlaneContainer_VisAtt);

  GEM_AnodeReadoutBoard_VisAtt  =  new G4VisAttributes(green_yellow);
  GEM_AnodeReadoutBoard_VisAtt  -> SetVisibility(true);
  GEM_AnodeReadoutBoard_Logical -> SetVisAttributes(GEM_AnodeReadoutBoard_VisAtt);

  GEM_AnodeCopperLayer_VisAtt  =  new G4VisAttributes(orange);
  GEM_AnodeCopperLayer_VisAtt  -> SetVisibility(true);
  GEM_AnodeCopperLayer_Logical -> SetVisAttributes(GEM_AnodeCopperLayer_VisAtt);
  //------------------------------------------------------------------------------
  GEM_CathodeHVPlaneContainer_VisAtt  =  new G4VisAttributes(gray);
  GEM_CathodeHVPlaneContainer_VisAtt  -> SetVisibility(true);
  GEM_CathodeHVPlaneContainer_Logical -> SetVisAttributes(GEM_CathodeHVPlaneContainer_VisAtt);

  GEM_CathodeHVCopperLayer_VisAtt  =  new G4VisAttributes(orange);
  GEM_CathodeHVCopperLayer_VisAtt  -> SetVisibility(true);
  GEM_CathodeHVCopperLayer_Logical -> SetVisAttributes(GEM_CathodeHVCopperLayer_VisAtt);


  //==========================================================================================
  //
  // ------------------------------------------------------
  // Define a Region which is required for the PAI model
  // handling a precise energy loss of relativistic charged
  // particles crossing the drift chamber gas.
  // ------------------------------------------------------

  if( fRegGasDet != 0 )  // remove obsolete root logical volume
  {
      fRegGasDet->RemoveRootLogicalVolume(GEM_SubContainer_Logical);
  }

  G4ProductionCuts* cuts = 0;
  
  if( fRegGasDet == 0 ) // First time - instantiate a region and a cut objects
  {    
      fRegGasDet = new G4Region("DriftCellRegion_GEM");
      cuts = new G4ProductionCuts();
      fRegGasDet->SetProductionCuts(cuts);
    
  }
  else  // Second time - get a cut object from region
  {   
      cuts = fRegGasDet->GetProductionCuts();
  }

  fRegGasDet->AddRootLogicalVolume(GEM_SubContainer_Logical);                               
   
  cuts->SetProductionCut(fGammaCut,"gamma");
  cuts->SetProductionCut(fElectronCut,"e-");
  cuts->SetProductionCut(fPositronCut,"e+");
  

//==========================================================================================





G4cout << G4endl << "###### Leaving QweakSimGEM::ConstructComponent() " << G4endl << G4endl;

} // end of  QweakSimGEM::ConstructComponent()



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::SetGEM_MasterContainerMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing GEM MasterContainer Material: Looking up Material  " << G4endl; 
                GEM_MasterContainer_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing GEM MasterContainer Material:  Now the GEM MasterContainer is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing GEM MasterContainer Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::SetGEM_SubContainerMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing GEM SubContainer Material: Looking up Material  " << G4endl; 
                GEM_SubContainer_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing GEM SubContainer Material:  Now the GEM SubContainer is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing GEM SubContainer Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::SetGEM_FrameMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing GEM Frame Material: Looking up Material  " << G4endl; 
                GEM_Frame_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing GEM Frame Material:  Now the GEM Plane is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing GEM Frame Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// void QweakSimGEM::SetGEM_FoilMaterial(G4String materialName)
// {
//   // search the material by its name
//   G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
//   if (pttoMaterial)
//      {
//   G4cout << "==== Changing GEM Foil Material: Looking up Material  " << G4endl;
//                 GEM_Foil_Logical->SetMaterial(pttoMaterial);
//   G4cout << "==== Changing GEM Foil Material:  Now the GEM Foil is made of " << materialName << G4endl;
//      }
//   else {
//       G4cerr << "==== ERROR: Changing GEM Foil Material failed" << G4endl;
//   }
//
// }
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// void QweakSimGEM::SetGEM_WirePlaneMaterial(G4String materialName)
// {
//   // search the material by its name
//   G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
//   if (pttoMaterial)
//      {
//   G4cout << "==== Changing GEM WirePlane Material: Looking up Material  " << G4endl;
//                 GEM_WirePlane_Logical->SetMaterial(pttoMaterial);
//   G4cout << "==== Changing GEM WirePlane Material:  Now the GEM WirePlane is made of " << materialName << G4endl;
//      }
//   else {
//       G4cerr << "==== ERROR: Changing GEM WirePlane Material failed" << G4endl;
//   }
//
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::DestroyComponent()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::SetFrontGEM_CenterPositionInX(G4double xPos)
{
    G4cout << G4endl << "###### Calling QweakSimGEM::SetFrontGEM_CenterPositionInX() " << G4endl << G4endl;

    GEM_CenterFront_XPos = xPos;	 
 
    GEM_MasterContainerFront_Physical->SetTranslation(G4ThreeVector(GEM_CenterFront_XPos,
								    GEM_CenterFront_YPos, 
								    GEM_CenterFront_ZPos));
 
    G4cout << G4endl << "###### Leaving QweakSimGEM::SetFrontGEM_CenterPositionInX() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::SetFrontGEM_CenterPositionInY(G4double yPos)
{
    G4cout << G4endl << "###### Calling QweakSimGEM::SetFrontGEM_CenterPositionInY() " << G4endl << G4endl;

    GEM_CenterFront_YPos = yPos;

    GEM_MasterContainerFront_Physical->SetTranslation(G4ThreeVector(GEM_CenterFront_XPos,
								    GEM_CenterFront_YPos, 
								    GEM_CenterFront_ZPos));

 G4cout << G4endl << "###### Leaving QweakSimGEM::SetFrontGEM_CenterPositionInY() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::SetFrontGEM_CenterPositionInZ(G4double zPos)
{
    G4cout << G4endl << "###### Calling QweakSimGEM::SetFrontGEM_CenterPositionInZ() " << G4endl << G4endl;

    GEM_CenterFront_ZPos = zPos;

    GEM_MasterContainerFront_Physical->SetTranslation(G4ThreeVector(GEM_CenterFront_XPos,
								    GEM_CenterFront_YPos, 
								    GEM_CenterFront_ZPos));

    G4cout << G4endl << "###### Leaving QweakSimGEM::SetFrontGEM_CenterPositionInZ() " << G4endl << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::SetBackGEM_CenterPositionInX(G4double xPos)
{
    G4cout << G4endl << "###### Calling QweakSimGEM::SetBackGEM_CenterPositionInX() " << G4endl << G4endl;

    GEM_CenterBack_XPos = xPos;	 
 
    GEM_MasterContainerBack_Physical->SetTranslation(G4ThreeVector(GEM_CenterBack_XPos,
								   GEM_CenterBack_YPos, 
								   GEM_CenterBack_ZPos));
 
    G4cout << G4endl << "###### Leaving QweakSimGEM::SetBackGEM_CenterPositionInX() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::SetBackGEM_CenterPositionInY(G4double yPos)
{
    G4cout << G4endl << "###### Calling QweakSimGEM::SetBackGEM_CenterPositionInY() " << G4endl << G4endl;

    GEM_CenterBack_YPos = yPos;

    GEM_MasterContainerBack_Physical->SetTranslation(G4ThreeVector(GEM_CenterBack_XPos,
								   GEM_CenterBack_YPos, 
								   GEM_CenterBack_ZPos));

 G4cout << G4endl << "###### Leaving QweakSimGEM::SetBackGEM_CenterPositionInY() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::SetBackGEM_CenterPositionInZ(G4double zPos)
{
    G4cout << G4endl << "###### Calling QweakSimGEM::SetBackGEM_CenterPositionInZ() " << G4endl << G4endl;

    GEM_CenterBack_ZPos = zPos;

    GEM_MasterContainerBack_Physical->SetTranslation(G4ThreeVector(GEM_CenterBack_XPos,
								   GEM_CenterBack_YPos, 
								   GEM_CenterBack_ZPos));

    G4cout << G4endl << "###### Leaving QweakSimGEM::SetBackGEM_CenterPositionInZ() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::SetGEM_FrontChamber_RotationAngleInPhi(G4double GEM_phiangle)
{
    G4cout << G4endl << "###### Calling QweakSimGEM::SetGEM_FrontChamber_RotationAngleInPhi() " << G4endl << G4endl;

    G4ThreeVector Translation_MasterContainerFront;
    G4double GEMFront_RadialDistance = sqrt(GEM_CenterFront_XPos*GEM_CenterFront_XPos + GEM_CenterFront_YPos*GEM_CenterFront_YPos);
    
    Translation_MasterContainerFront.setX(cos(GEM_phiangle)*GEMFront_RadialDistance) ;
    Translation_MasterContainerFront.setY(sin(GEM_phiangle)*GEMFront_RadialDistance) ;
    Translation_MasterContainerFront.setZ(GEM_CenterFront_ZPos) ;
	    
    // assign new tilting 
    GEM_FrontChamber_RotationAngleInPhi = GEM_phiangle;

    Rotation_FrontChamber_GEM         -> setPhi(GEM_FrontChamber_RotationAngleInPhi -90*degree);
    GEM_MasterContainerFront_Physical -> SetRotation(Rotation_FrontChamber_GEM);
    GEM_MasterContainerFront_Physical -> SetTranslation(Translation_MasterContainerFront);
    
    G4cout << G4endl << "###### Leaving QweakSimGEM::SetGEM_RotationAngleInPhi() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGEM::SetGEM_BackChamber_RotationAngleInPhi(G4double GEM_phiangle)
{
    G4cout << G4endl << "###### Calling QweakSimGEM::SetGEM_BackChamber_RotationAngleInPhi() " << G4endl << G4endl;

    G4ThreeVector Translation_MasterContainerBack;
    G4double GEMBack_RadialDistance = sqrt(GEM_CenterBack_XPos*GEM_CenterBack_XPos + GEM_CenterBack_YPos*GEM_CenterBack_YPos);
    
    Translation_MasterContainerBack.setX(cos(GEM_phiangle)*GEMBack_RadialDistance) ;
    Translation_MasterContainerBack.setY(sin(GEM_phiangle)*GEMBack_RadialDistance) ;
    Translation_MasterContainerBack.setZ(GEM_CenterBack_ZPos);

    // assign new tilting 
    GEM_BackChamber_RotationAngleInPhi = GEM_phiangle;

    Rotation_BackChamber_GEM          -> setPhi(GEM_BackChamber_RotationAngleInPhi -90*degree);
    GEM_MasterContainerBack_Physical  -> SetRotation(Rotation_BackChamber_GEM);
    GEM_MasterContainerBack_Physical  -> SetTranslation(Translation_MasterContainerBack);

    G4cout << G4endl << "###### Leaving QweakSimGEM::SetGEM_BackChamber_RotationAngleInPhi() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

