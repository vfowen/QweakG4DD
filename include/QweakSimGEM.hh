//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimGEM.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:23:57 $
   \author Klaus Hans Grimm
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimGEM
    
   \brief Region 1 GEM (Gas Electron Multiplier)

   Placeholder for a long explaination
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:23:57 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimGEM_h
#define QweakSimGEM_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimGEM_WirePlaneSD.hh"

// user classes
class QweakSimGEMMessenger;
class QweakSimMaterial;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//class QweakSimGEM: public QweakSimVGeometryComponent
//class QweakSimGEM: public G4VUserDetectorConstruction
class QweakSimGEM
{
public:
  QweakSimGEM();
  ~QweakSimGEM();

  void ConstructComponent(G4VPhysicalVolume*);
  void DestroyComponent();

  //=============
  // Set function
  //=============

  void SetGEM_MasterContainerMaterial(G4String);
  void SetGEM_SubContainerMaterial(G4String);
  void SetGEM_FrameMaterial(G4String);
  //void SetGEM_FoilMaterial(G4String);
  //void SetGEM_WirePlaneMaterial(G4String);

  void SetFrontGEM_CenterPositionInX(G4double xPos);
  void SetFrontGEM_CenterPositionInY(G4double yPos);
  void SetFrontGEM_CenterPositionInZ(G4double zPos);

  void SetBackGEM_CenterPositionInX(G4double xPos);
  void SetBackGEM_CenterPositionInY(G4double yPos);
  void SetBackGEM_CenterPositionInZ(G4double zPos);

  void SetGEM_FrontChamber_RotationAngleInPhi(G4double GEM_phiangleFront);
  void SetGEM_BackChamber_RotationAngleInPhi(G4double GEM_phiangleBack);


  //=============
  // Get function
  //=============
  
  G4LogicalVolume*   getGEM_LogicalVolume()    {return GEM_MasterContainer_Logical;} 

  G4VPhysicalVolume* getGEMFront_PhysicalVolume()   {return GEM_MasterContainerFront_Physical;} 
  G4VPhysicalVolume* getGEMBack_PhysicalVolume()    {return GEM_MasterContainerBack_Physical;} 

  G4LogicalVolume*   getGEM_Frame_LogicalVolume()    {return GEM_Frame_Logical;} 
G4VPhysicalVolume*   getGEM_Frame_PhysicalVolume()   {return GEM_Frame_Physical;} 


  //G4LogicalVolume*   getGEM_Foil_LogicalVolume()    {return GEM_Foil_Logical;} 
  //G4VPhysicalVolume* getGEM_Foil_PhysicalVolume()   {return GEM_Foil_Physical;} 

  //G4LogicalVolume*   getGEM_WirePlane_LogicalVolume()    {return GEM_WirePlane_Logical;} 
  //G4VPhysicalVolume* getGEM_WirePlane_PhysicalVolume()   {return GEM_WirePlane_Physical;} 


  G4double GetGEM_FrontChamber_RotationAngleInPhi() {return GEM_FrontChamber_RotationAngleInPhi;} 
  G4double GetGEM_BackChamber_RotationAngleInPhi() {return GEM_BackChamber_RotationAngleInPhi;} 

private:


  QweakSimMaterial*  pMaterial;

  G4RotationMatrix* Rotation_FrontChamber_GEM; // for Phi angle orientation
  G4RotationMatrix* Rotation_BackChamber_GEM; // for Phi angle orientation

  G4double          GEM_FrontChamber_RotationAngleInPhi;
  G4double          GEM_BackChamber_RotationAngleInPhi;

  G4LogicalVolume*   GEM_MasterContainer_Logical; 
  G4VPhysicalVolume* GEM_MasterContainerFront_Physical; 
  G4VPhysicalVolume* GEM_MasterContainerBack_Physical; 

  G4LogicalVolume*   GEM_SubContainer_Logical; 
  G4VPhysicalVolume* GEM_SubContainer_Physical; 

  G4LogicalVolume*   GEM_Frame_Logical; 
  G4VPhysicalVolume* GEM_Frame_Physical; 

   //--------------------
  G4LogicalVolume*   GEM_MiddleFoilContainer_Logical;
  G4VPhysicalVolume* GEM_MiddleFoilContainer_Physical;
  //
  G4LogicalVolume*   GEM_KaptonMiddleFoil_Logical;
  G4VPhysicalVolume* GEM_KaptonMiddleFoil_Physical;
  //
  G4LogicalVolume*   GEM_CopperMiddleFoil_Logical;
  G4VPhysicalVolume* GEM_TopCopperMiddleFoil_Physical;
  G4VPhysicalVolume* GEM_BottomCopperMiddleFoil_Physical;
  //--------------------
  // 
  //--------------------
  G4LogicalVolume*   GEM_AnodeReadoutPlaneContainer_Logical;
  G4VPhysicalVolume* GEM_AnodeReadoutPlaneContainer_Physical;
  //
  G4LogicalVolume*   GEM_AnodeReadoutBoard_Logical;
  G4VPhysicalVolume* GEM_AnodeReadoutBoard_Physical;
  //
  G4LogicalVolume*   GEM_AnodeCopperLayer_Logical;
  G4VPhysicalVolume* GEM_AnodeCopperLayer_Physical;
  //--------------------
  // 
  //--------------------
  G4LogicalVolume*   GEM_CathodeHVPlaneContainer_Logical;
  G4VPhysicalVolume* GEM_CathodeHVPlaneContainer_Physical;
  //
  G4LogicalVolume*   GEM_CathodeHVCopperLayer_Logical;
  G4VPhysicalVolume* GEM_CathodeHVCopperLayer_Physical;
  //--------------------

  QweakSimGEMMessenger* GEM_Messenger;  // pointer to the Messenger

  G4double GEMFrame_Thickness; 
  G4double GEMFrame_OuterLength;
  G4double GEMFrame_OuterWidth; 
  G4double GEMFrame_InnerLength;
  G4double GEMFrame_InnerWidth; 
  G4double GEMFrame_BorderWidthInX; 
  G4double GEMFrame_BorderWidthInY; 

  G4double GEM_KaptonCathodeFoil_Thickness; 
  G4double GEM_KaptonMiddleFoil_Thickness; 
  G4double GEM_KaptonAnodeFoil_Thickness; 

  G4double GEM_G10AnodeBoard_Thickness; 
  G4double GEM_CopperLayer_Thickness; 

  G4double AluFrame_Thickness; 
  G4double AluFrame_OuterLength;
  G4double AluFrame_OuterWidth; 
  G4double AluFrame_InnerLength;
  G4double AluFrame_InnerWidth; 

  G4double GEM_CenterFront_XPos;
  G4double GEM_CenterFront_YPos;
  G4double GEM_CenterFront_ZPos;

  G4double GEM_CenterBack_XPos;
  G4double GEM_CenterBack_YPos;
  G4double GEM_CenterBack_ZPos;

 
  G4VisAttributes* GEM_MasterContainer_VisAtt;
  G4VisAttributes* GEM_SubContainer_VisAtt;
  G4VisAttributes* GEM_Frame_VisAtt;

  G4VisAttributes* GEM_MiddleFoilContainer_VisAtt;
  G4VisAttributes* GEM_KaptonMiddleFoil_VisAtt;
  G4VisAttributes* GEM_CopperMiddleFoil_VisAtt;

  G4VisAttributes* GEM_AnodeReadoutPlaneContainer_VisAtt;
  G4VisAttributes* GEM_AnodeReadoutBoard_VisAtt;
  G4VisAttributes* GEM_AnodeCopperLayer_VisAtt;
  G4VisAttributes* GEM_CathodeHVPlaneContainer_VisAtt;
  G4VisAttributes* GEM_CathodeHVCopperLayer_VisAtt;


  //  QweakSimGEMSD*  driftChamberSD; // pointer to the sensitive DC
  G4VSensitiveDetector* GEMdriftChamberSD;
 
  G4SubtractionSolid*   GEM_Frame_Solid;


  // cuts for G4Region and PAIModel
  G4double    fGammaCut; 
  G4double    fElectronCut; 
  G4double    fPositronCut; 
  G4Region*   fRegGasDet;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
 
//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimGEM.hh,v $
//      Revision 1.2  2005/12/27 19:23:57  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
