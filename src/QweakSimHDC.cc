//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimHDC.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:10:29 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimHDC.hh"

// geant4 includes
#include "G4VisAttributes.hh"

// user includes
#include "QweakSimMaterial.hh"
#include "QweakSimHDCMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//===================================================================
//	Qweak Geometry Conventions:
//      The origin is at the center of the main toroidal magnet with
//	the z-axis pointing along the beam direction, the x-axis
//	pointing toward the ceiling, and the y-axis pointing toward
//	beam-right so as to form a right-handed coordinate system.
//	Octants are numbered from 1 to 8, clockwise with #1 at the 
//	12 o-clock position.  
//===================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimHDC::QweakSimHDC()
{
  G4cout << G4endl << "###### Calling QweakSimHDC::QweakHDC() " << G4endl << G4endl;

  // initialize pointers
  HDC_MasterContainer_Logical        = NULL;
  //HDC_MasterContainerFront_Physical  = NULL;
  //HDC_MasterContainerBack_Physical   = NULL;

  HDC_SubContainer_Physical = NULL;
  HDC_SubContainer_Logical  = NULL;

//  Rotation_HDC              = NULL;

  HDC_Frame_Logical      = NULL;
  HDC_Frame_Physical     = NULL;

  HDC_Foil_Logical       = NULL;
  HDC_Foil_Physical      = NULL;

  HDC_WirePlane_Logical  = NULL;
  HDC_WirePlane_Physical = NULL;


  HDC_MasterContainer_VisAtt         = NULL;
  HDC_SubContainer_VisAtt            = NULL;
  HDC_Frame_VisAtt                   = NULL;
  HDC_Foil_VisAtt                    = NULL;
  HDC_WirePlane_VisAtt               = NULL;


  // define target geometry value
  // Geometry taken from Norm's HDC talk in Vancouver 2005

  HDC_DriftCell_TotalThickness = 19.8*mm;  // Distance: 2*(HVplane to WirePlane)
  // updated 2012-04-09 wdconinc based on input Mark Pitt

  HDCFrame_Thickness        =  17.20*cm; // Allena's keepout info

  HDCFrame_InnerLength      =  30.00*cm; // X  
  HDCFrame_InnerWidth       =  45.09*cm; // Y

  HDCFrame_OuterLength      =  43.97*cm; // X
  HDCFrame_OuterWidth       =  59.06*cm; // Y

  HDCFrame_BorderWidthInX   =  0.5*( HDCFrame_OuterLength - HDCFrame_InnerLength )*cm;
  HDCFrame_BorderWidthInY   =  0.5*( HDCFrame_OuterWidth  - HDCFrame_InnerWidth  )*cm;


  // Norm did not mention it, but I suppose that the HDC will
  // sandwiched between 2 alu plates for stability.
  AluFrame_Thickness        =  1.0*cm; 
  AluFrame_OuterLength      =  HDCFrame_OuterLength;
  AluFrame_OuterWidth       =  HDCFrame_OuterWidth;
  AluFrame_InnerLength      =  HDCFrame_InnerLength;
  AluFrame_InnerWidth       =  HDCFrame_InnerWidth;

  HDC_CenterFront_XPos.resize(2,0);
  HDC_CenterFront_YPos.resize(2,0);
  HDC_CenterFront_ZPos.resize(2,0);

  HDC_CenterBack_XPos.resize(2,0);
  HDC_CenterBack_YPos.resize(2,0);
  HDC_CenterBack_ZPos.resize(2,0);

  for(int i = 0; i < 2; i++){ //temporary loop, setting both HDC packages to same coordinates, but pkg2 will be rotated.
  HDC_CenterFront_XPos[i]      =      0.0*cm;
  HDC_CenterFront_YPos[i]      =     51.0*cm;
  HDC_CenterFront_ZPos[i]      = -337.355*cm; //-325.459*cm;  // Allena's keepout info
  // updated 2012-04-09 wdconinc based on input Mark Pitt

  HDC_CenterBack_XPos[i]       =      0.0*cm;
  HDC_CenterBack_YPos[i]       =     54.9*cm;
  HDC_CenterBack_ZPos[i]       = -294.655*cm;
  // updated 2012-04-09 wdconinc based on input Mark Pitt
  
  HDC_RotationAngleInPhi[i]     =   90.0*degree;   // normally 0.0*degree = 12 o'clock = octant 1
    
  if(i==1)
  {
      HDC_CenterFront_XPos[i]      =      0.0*cm;
      HDC_CenterFront_YPos[i]      =    -51.0*cm;
      
      HDC_CenterBack_XPos[i]       =      0.0*cm;
      HDC_CenterBack_YPos[i]       =    -54.9*cm;
      
      HDC_RotationAngleInPhi[i]     =   270.0*degree;   // normally 0.0*degree = 12 o'clock = octant 1
  }

  }
  
  // define Rotation matrix for Container orientated in MotherVolume
//  Rotation_HDC  = new G4RotationMatrix();

  
  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();

  //Resizing vectors and setting values to 0
  HDC_MasterContainerFront_Physical.resize(2,0);
  HDC_MasterContainerBack_Physical.resize(2,0);
  Rotation_HDC.resize(2,0);
  HDC_Messenger.resize(2,0);
 
  // Creates a messenger for each VDC package (0 for Package 1 and 1 for Package 2)
  for(size_t i = 0; i < HDC_Messenger.size(); i++)
	  HDC_Messenger[i] = new QweakSimHDCMessenger(this, i);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimHDC::~QweakSimHDC()
{

    //if (HdriftChamberSD)                     delete HdriftChamberSD;

    if (HDC_Frame_VisAtt)                    delete HDC_Frame_VisAtt;
    if (HDC_WirePlane_VisAtt)                delete HDC_WirePlane_VisAtt;
    if (HDC_Foil_VisAtt)                     delete HDC_Foil_VisAtt;
    if (HDC_SubContainer_VisAtt)             delete HDC_SubContainer_VisAtt;
    if (HDC_MasterContainer_VisAtt)          delete HDC_MasterContainer_VisAtt;

    if (HDC_WirePlane_Physical)              delete HDC_WirePlane_Physical ;
    if (HDC_WirePlane_Logical)               delete HDC_WirePlane_Logical;

    if (HDC_Foil_Physical)                   delete HDC_Foil_Physical;
    if (HDC_Foil_Logical)                    delete HDC_Foil_Logical;

    if (HDC_Frame_Physical)                  delete HDC_Frame_Physical ;
    if (HDC_Frame_Logical)                   delete HDC_Frame_Logical ; 

    if (HDC_SubContainer_Physical)           delete HDC_SubContainer_Physical ;
    if (HDC_SubContainer_Logical)            delete HDC_SubContainer_Logical;

    //if (HDC_MasterContainerFront_Physical)   delete HDC_MasterContainerFront_Physical ;
    //if (HDC_MasterContainerBack_Physical)    delete HDC_MasterContainerBack_Physical;
    if (HDC_MasterContainer_Logical)         delete HDC_MasterContainer_Logical;

    if (HDC_Frame_Solid)                     delete HDC_Frame_Solid;

    //if (Rotation_HDC)                        delete Rotation_HDC ;

    if (pMaterial)                           delete pMaterial; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimHDC::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
G4cout << G4endl << "###### Calling QweakSimHDC::ConstructComponent() " << G4endl << G4endl;

theMotherPV = MotherVolume;
 
// definition of a mil = inch/1000
static const G4double mil = 0.001*2.54*cm;


// assign material
 G4Material* HDC_MasterContainer_Material    = pMaterial->GetMaterial("Air");   
 G4Material* HDC_SubContainer_Material       = pMaterial->GetMaterial("ArCO2");   
 G4Material* HDC_Frame_Material              = pMaterial->GetMaterial("NemaG10");  
 G4Material* HDC_Foil_Material               = pMaterial->GetMaterial("Mylar"); 
 G4Material* HDC_WirePlane_Material          = pMaterial->GetMaterial("ArCO2"); 




  // define  solid volume of the drift chamber container
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_MasterContainer_Solid" << G4endl << G4endl;
  
  G4Box* HDC_MasterContainer_Solid    = new G4Box("HDC_MasterContainer_Sol",
						  0.5* HDCFrame_OuterLength,
						  0.5* HDCFrame_OuterWidth,
						  0.5* HDCFrame_Thickness + 1.0*mm); 

  // define HDC logical volume of drift chamber container
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_MasterContainer_Logical " << G4endl << G4endl;
  
  HDC_MasterContainer_Logical  = new G4LogicalVolume(HDC_MasterContainer_Solid,
						     HDC_MasterContainer_Material,
						     "HDC_MasterContainer_Log",
						     0,0,0);


  PlaceHDC_MasterContainers();


  //====================================================================
  // Definition of the HDC Frame ( symbolizes the stack of real frames )
  //====================================================================

  // define outer frame solid
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_OuterFrame_Solid" << G4endl << G4endl;

  G4Box* HDC_OuterFrame_Solid    = new G4Box("HDC_OuterFrame_Sol",
					     0.5* HDCFrame_OuterLength,
					     0.5* HDCFrame_OuterWidth,
					     0.5* HDCFrame_Thickness); 

  // define inner frame solid
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_InnerFrame_Solid" << G4endl << G4endl;

  G4Box* HDC_InnerFrame_Solid    = new G4Box("HDC_InnerFrame_Sol",
					     0.5* HDCFrame_InnerLength,
					     0.5* HDCFrame_InnerWidth,
					     0.5* HDCFrame_Thickness + 0.1*mm); 


 // create frame by subtracting outer framebox from inner framebox
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_Frame_Solid" << G4endl << G4endl;

  HDC_Frame_Solid  =  new G4SubtractionSolid("HDC_Frame",
					     HDC_OuterFrame_Solid, 
					     HDC_InnerFrame_Solid); 


  G4cout << G4endl << "###### QweakSimHDC: Define HDC_Frame_Logical" << G4endl << G4endl;
  HDC_Frame_Logical  = new G4LogicalVolume(HDC_Frame_Solid,
					   HDC_Frame_Material,
					   "HDC_Frame_Log",
					   0,0,0);


  // define the position of the Frame within the HDC Container: put it in the center of HDC container 
  G4ThreeVector position_Frame = G4ThreeVector(0. , 0. , 0.);
  
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_Frame_Physical" << G4endl << G4endl;
  
  HDC_Frame_Physical =   new G4PVPlacement(0,                          // no rotation matrix needed 
					   position_Frame, 
					   HDC_Frame_Logical, 
					   "HDC_Frame_Physical",
					   HDC_MasterContainer_Logical, 
					   0, 
					   0,
					   pSurfChk); //copy number: 0


  //====================================================================================
  // Definition of the HDC SubContainer holding the stack of foil planes and wire planes
  //====================================================================================
  

  // define outer frame solid
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_SubContainer_Solid" << G4endl << G4endl;
  
  G4Box* HDC_SubContainer_Solid    = new G4Box("HDC_OuterFrame_Sol",
					       0.5* HDCFrame_InnerLength, // X
					       0.5* HDCFrame_InnerWidth,  // Y
					       0.5* HDCFrame_Thickness);  // Z
  
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_SubContainer_Logical" << G4endl << G4endl;
  
  HDC_SubContainer_Logical  = new G4LogicalVolume(HDC_SubContainer_Solid,
						  HDC_SubContainer_Material,
						  "HDC_SubContainer_Log",
						  0,0,0);
  

 // define the position of the SubContainer within the HDC Container: put it in the center of HDC container 
  G4ThreeVector position_SubContainer = G4ThreeVector(0. , 0. , 0.);
  
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_SubContainer_Physical" << G4endl << G4endl;
  
  HDC_SubContainer_Physical =   new G4PVPlacement(0,                          // no rotation matrix needed 
						  position_SubContainer, 
						  HDC_SubContainer_Logical, 
						  "HDC_SubContainer_Physical",
						  HDC_MasterContainer_Logical, 
						  0, 
						  0,
						  pSurfChk); //copy number: 0



  //====================================================================
  // Definition of the HDC Foil plane ( for gas window and HV plane )
  //====================================================================


  // define foil solid
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_Foil_Solid" << G4endl << G4endl;
  
  G4Box* HDC_Foil_Solid    = new G4Box("HDC_OuterFrame_Sol",
				       0.5* HDCFrame_InnerLength,
				       0.5* HDCFrame_InnerWidth,
				       0.5* 0.5*mil); 

  // define foil logical
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_Foil_Logical" << G4endl << G4endl;
  
  HDC_Foil_Logical  = new G4LogicalVolume(HDC_Foil_Solid,
					  HDC_Foil_Material,
					  "HDC_Foil_Log",
					  0,0,0);

  // Z Location of the foils in the HDC stack in units of a quarter full drift cell height (=1.9mm /4)
  //G4double HDC_Foil_PositionIndexInZ[10] = { -17.0 , -13.0 , -9.0 , -5.0 , -1.0 , 1.0 , 5.0 , 9.0 , 13.0 , 17.0 };
  // updated 2012-04-09 wdconinc based on input Mark Pitt
  G4double HDC_Foil_PositionIndexInZ[9] = { -14.0 , -12.0 , -8.0 , -4.0 , 0.0 , 4.0 , 8.0 , 12.0 , 14.0 };

  // define foil physical
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_Foil_Physical" << G4endl << G4endl;

  for( G4int index = 0; index < 9; index++){
      
      new G4PVPlacement(0, 
			G4ThreeVector(0. , 0. , HDC_Foil_PositionIndexInZ[index]*1/4*HDC_DriftCell_TotalThickness ), 
			HDC_Foil_Logical, 
			"HDC_Foil_Physical",
			HDC_SubContainer_Logical, 
			0, 
			index,
			pSurfChk); //copy number
      
    } // end for
  
  //====================================================================
  // Definition of the HDC Wire Plane 
  //====================================================================

  // define wire plane solid
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_WirePlane_Solid" << G4endl << G4endl;
    
  G4Box* HDC_WirePlane_Solid    = new G4Box("HDC_WirePlane_Sol",
					    0.5* HDCFrame_InnerLength,
					    0.5* HDCFrame_InnerWidth,
					    0.5* 1.0*mil); 

  // define wire plane logical
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_WirePlane_Logical" << G4endl << G4endl;
  
  HDC_WirePlane_Logical  = new G4LogicalVolume(HDC_WirePlane_Solid,
					       HDC_WirePlane_Material,
					       "HDC_WirePlane_Log",
					       0,0,0);
  
  // Z Location of the wire planes in the HDC stack in units of a quarter full drift cell height (=1.9mm /4)
  //G4double HDC_WirePlane_PositionIndexInZ[6] = { -11.0 , -7.0 , -3.0 , 3.0 , 7.0 , 11.0 };
  // updated 2012-04-09 wdconinc based on input Mark Pitt
  G4double HDC_WirePlane_PositionIndexInZ[6] = { -10.0 , -6.0 , -2.0 , 2.0 , 6.0 , 10.0 };

  // define wire planes physical
  G4cout << G4endl << "###### QweakSimHDC: Define HDC_WirePlane_Physical" << G4endl << G4endl;

  for( G4int index = 0; index < 6; index++){

      new G4PVPlacement(0, 
			G4ThreeVector(0. , 0. , HDC_WirePlane_PositionIndexInZ[index]*1/4*HDC_DriftCell_TotalThickness ), 
			HDC_WirePlane_Logical, 
			"HDC_WirePlane_Physical",
			HDC_SubContainer_Logical, 
			0, 
			index,
			pSurfChk); //copy number
  } // end for

//================================================================================================


G4cout << G4endl << "###### QweakSimHDC: Setting Sensitive Detectors " << G4endl << G4endl;

  // Sensitive detectors
  //------------------------------------------------ 
  // All managed (deleted) by SDManager

   G4SDManager* SDman = G4SDManager::GetSDMpointer();


   //#######################################################
   // define drift chamber elements as sensitiv detectors
   // "sensitivity" will be handled by class QweakSimHDCSD
   //#######################################################


   //***********************************************************
   HdriftChamberSD = new QweakSimHDC_WirePlaneSD("/HDCWirePlaneSD");
   SDman->AddNewDetector(HdriftChamberSD);
   
   // add wire plane as a sensitiv element
   HDC_WirePlane_Logical->SetSensitiveDetector(HdriftChamberSD);
   //***********************************************************


G4cout << G4endl << "###### QweakSimHDC: Setting Attributes " << G4endl << G4endl;

  G4Colour  orange (241/255.,224/255.,0/255.);
  G4Colour  gray   (210/255.,213/255.,210/255.);

  G4Colour  red   (255/255.,   0/255.,0/255.);
  G4Colour  green (  0/255., 255/255.,0/255.);

  HDC_MasterContainer_VisAtt  =  new G4VisAttributes(orange);
  HDC_MasterContainer_VisAtt  -> SetVisibility(false);
  HDC_MasterContainer_Logical -> SetVisAttributes(HDC_MasterContainer_VisAtt); 

  HDC_SubContainer_VisAtt  =  new G4VisAttributes(red);
  HDC_SubContainer_VisAtt  -> SetVisibility(false);
  HDC_SubContainer_Logical -> SetVisAttributes(HDC_SubContainer_VisAtt); 

  HDC_Frame_VisAtt  =  new G4VisAttributes(green);
  HDC_Frame_VisAtt  -> SetVisibility(true);
  HDC_Frame_Logical -> SetVisAttributes(HDC_Frame_VisAtt); 

  HDC_Foil_VisAtt  =  new G4VisAttributes(orange);
  HDC_Foil_VisAtt  -> SetVisibility(true);
  HDC_Foil_Logical -> SetVisAttributes(HDC_Foil_VisAtt); 

  HDC_WirePlane_VisAtt  =  new G4VisAttributes(gray);
  HDC_WirePlane_VisAtt  -> SetVisibility(true);
  HDC_WirePlane_Logical -> SetVisAttributes(HDC_WirePlane_VisAtt); 


G4cout << G4endl << "###### Leaving QweakSimHDC::ConstructComponent() " << G4endl << G4endl;

} // end of  QweakSimHDC::ConstructComponent()



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetHDC_MasterContainerMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing HDC MasterContainer Material: Looking up Material  " << G4endl; 
                HDC_MasterContainer_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing HDC MasterContainer Material:  Now the HDC MasterContainer is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing HDC MasterContainer Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetHDC_SubContainerMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing HDC SubContainer Material: Looking up Material  " << G4endl; 
                HDC_SubContainer_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing HDC SubContainer Material:  Now the HDC SubContainer is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing HDC SubContainer Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetHDC_FrameMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing HDC Frame Material: Looking up Material  " << G4endl; 
                HDC_Frame_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing HDC Frame Material:  Now the HDC Plane is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing HDC Frame Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetHDC_FoilMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing HDC Foil Material: Looking up Material  " << G4endl; 
                HDC_Foil_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing HDC Foil Material:  Now the HDC Foil is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing HDC Foil Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetHDC_WirePlaneMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing HDC WirePlane Material: Looking up Material  " << G4endl; 
                HDC_WirePlane_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing HDC WirePlane Material:  Now the HDC WirePlane is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing HDC WirePlane Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::DestroyComponent()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetFrontHDC_CenterPositionInX(G4double xPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimHDC::SetFrontHDC_CenterPositionInX() " << G4endl << G4endl;

    HDC_CenterFront_XPos[pkg] = xPos;
 
    HDC_MasterContainerFront_Physical[pkg]->SetTranslation(G4ThreeVector(HDC_CenterFront_XPos[pkg],
								    HDC_CenterFront_YPos[pkg],
								    HDC_CenterFront_ZPos[pkg]-HDC_CenterPositionInZ));
 
    G4cout << G4endl << "###### Leaving QweakSimHDC::SetFrontHDC_CenterPositionInX() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetFrontHDC_CenterPositionInY(G4double yPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimHDC::SetFrontHDC_CenterPositionInY() " << G4endl << G4endl;

    HDC_CenterFront_YPos[pkg] = yPos;

    HDC_MasterContainerFront_Physical[pkg]->SetTranslation(G4ThreeVector(HDC_CenterFront_XPos[pkg],
								    HDC_CenterFront_YPos[pkg],
								    HDC_CenterFront_ZPos[pkg]-HDC_CenterPositionInZ));

 G4cout << G4endl << "###### Leaving QweakSimHDC::SetFrontHDC_CenterPositionInY() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetFrontHDC_CenterPositionInZ(G4double zPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimHDC::SetFrontHDC_CenterPositionInZ() " << G4endl << G4endl;

    HDC_CenterFront_ZPos[pkg] = zPos;

    HDC_MasterContainerFront_Physical[pkg]->SetTranslation(G4ThreeVector(HDC_CenterFront_XPos[pkg],
								    HDC_CenterFront_YPos[pkg],
								    HDC_CenterFront_ZPos[pkg]-HDC_CenterPositionInZ));

    G4cout << G4endl << "###### Leaving QweakSimHDC::SetFrontHDC_CenterPositionInZ() " << G4endl << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetBackHDC_CenterPositionInX(G4double xPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimHDC::SetBackHDC_CenterPositionInX() " << G4endl << G4endl;

    HDC_CenterBack_XPos[pkg] = xPos;
 
    HDC_MasterContainerBack_Physical[pkg]->SetTranslation(G4ThreeVector(HDC_CenterBack_XPos[pkg],
								   HDC_CenterBack_YPos[pkg],
								   HDC_CenterBack_ZPos[pkg]-HDC_CenterPositionInZ));
 
    G4cout << G4endl << "###### Leaving QweakSimHDC::SetBackHDC_CenterPositionInX() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetBackHDC_CenterPositionInY(G4double yPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimHDC::SetBackHDC_CenterPositionInY() " << G4endl << G4endl;

    HDC_CenterBack_YPos[pkg] = yPos;

    HDC_MasterContainerBack_Physical[pkg]->SetTranslation(G4ThreeVector(HDC_CenterBack_XPos[pkg],
								   HDC_CenterBack_YPos[pkg],
								   HDC_CenterBack_ZPos[pkg]-HDC_CenterPositionInZ));

 G4cout << G4endl << "###### Leaving QweakSimHDC::SetBackHDC_CenterPositionInY() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetBackHDC_CenterPositionInZ(G4double zPos, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimHDC::SetBackHDC_CenterPositionInZ() " << G4endl << G4endl;

    HDC_CenterBack_ZPos[pkg] = zPos;
    HDC_MasterContainerBack_Physical[pkg]->SetTranslation(G4ThreeVector(HDC_CenterBack_XPos[pkg],
								   HDC_CenterBack_YPos[pkg],
								   HDC_CenterBack_ZPos[pkg]-HDC_CenterPositionInZ));

    G4cout << G4endl << "###### Leaving QweakSimHDC::SetBackHDC_CenterPositionInZ() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::SetHDC_RotationAngleInPhi(G4double HDC_phiangle, G4int pkg)
{
    G4cout << G4endl << "###### Calling QweakSimHDC::SetHDC_RotationAngleInPhi() " << G4endl << G4endl;

    // assign new azimuthal angle 
    G4double kAngle_GlobalRotation = HDC_phiangle -90.0*degree;
    
    if(pkg==1)
       kAngle_GlobalRotation += 180*degree;
    
    G4RotationMatrix* Rotation_HDCPackageContainer = new G4RotationMatrix();
    Rotation_HDCPackageContainer->setPhi(kAngle_GlobalRotation);
    HDC_PackageContainer_Physical->SetRotation(Rotation_HDCPackageContainer);

    G4cout << G4endl << "###### Leaving QweakSimHDC::SetHDC_RotationAngleInPhi() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimHDC::PlaceHDC_MasterContainers()
{
    G4Box* HDC_PackageContainer_Solid = new G4Box("HDC_PackageContainer_Solid",
				 0.5 * (3.0*m), 
				 0.5 * (7.0*m),
				 0.5 * (0.7*m));
   
   G4LogicalVolume* HDC_PackageContainer_Logical  = new G4LogicalVolume(  HDC_PackageContainer_Solid,
					 pMaterial->GetMaterial("Air"),
					 "HDC_PackageContainer_Logical",
					 0,
					 0,0);

  G4Colour  aluminum      ( 169/255. , 172/255. , 182/255.);
  G4VisAttributes* HDC_PackageContainer_VisAtt = new G4VisAttributes(aluminum);
  HDC_PackageContainer_VisAtt->SetForceWireframe(true);
  HDC_PackageContainer_VisAtt->SetVisibility(false);
  HDC_PackageContainer_Logical->SetVisAttributes(HDC_PackageContainer_VisAtt); 

  // Place the physical volume into theMotherVolume

   HDC_CenterPositionInZ = 0.5*(HDC_CenterBack_ZPos[0]+HDC_CenterFront_ZPos[0]);
   G4ThreeVector Translation_HDC_PackageContainer;
   Translation_HDC_PackageContainer.setZ(HDC_CenterPositionInZ);

   G4RotationMatrix* Rotation_HDC_PackageContainer = new G4RotationMatrix();
   //Rotation_HDC_PackageContainer->rotateZ(-90.0*deg);
   
   HDC_PackageContainer_Physical   = new G4PVPlacement(Rotation_HDC_PackageContainer,
					   Translation_HDC_PackageContainer,
					   "HDC_PackageContainer_Physical",
					   HDC_PackageContainer_Logical,
					   theMotherPV,
					   false,
					   0,
					   pSurfChk);


	  for (size_t i=0; i< HDC_MasterContainerFront_Physical.size();i++) {

	  Rotation_HDC[i]  = new G4RotationMatrix();
	  //Rotation_HDC[i]->setPhi(HDC_RotationAngleInPhi[i]-90.0*deg);

	  // define HDC MasterContainer positions in MotherVolume
	  G4ThreeVector position_MasterContainerFront(HDC_CenterFront_XPos[i], 
						      HDC_CenterFront_YPos[i], 
					              HDC_CenterFront_ZPos[i]-HDC_CenterPositionInZ );
	  
	  G4ThreeVector position_MasterContainerBack(HDC_CenterBack_XPos[i], 
						     HDC_CenterBack_YPos[i], 
					             HDC_CenterBack_ZPos[i]-HDC_CenterPositionInZ );

	  // define HDC physical volume of drift chamber container
	  G4cout << G4endl << "###### QweakSimHDC: Define HDC_MasterContainerFront_Physical" << G4endl << G4endl;

	  HDC_MasterContainerFront_Physical[i] = new G4PVPlacement(Rotation_HDC[i],
								position_MasterContainerFront,
								Form("HDC_MasterContainerFront_Physical%ld",i),
								HDC_MasterContainer_Logical,
								HDC_PackageContainer_Physical,
								false,
								2*i,
								pSurfChk); // copy number for front



	  // define HDC physical volume of drift chamber container

	  HDC_MasterContainerBack_Physical[i] = new G4PVPlacement(Rotation_HDC[i],
			  	  	  	  	       position_MasterContainerBack,
							       Form("HDC_MasterContainerBack_Physical%ld",i),
							       HDC_MasterContainer_Logical,
							       HDC_PackageContainer_Physical,
							       false,
							       2*i+1,
							       pSurfChk);// copy number for back
	  
	  }


}
