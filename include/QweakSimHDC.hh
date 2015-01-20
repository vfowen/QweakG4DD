//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimHDC.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:24:35 $
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
   \class QweakSimHDC
    
   \brief Region 2 Horizontal Drift Chamber

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
//  Update Date:      $Date: 2005/12/27 19:24:35 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimHDC_h
#define QweakSimHDC_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimHDC_WirePlaneSD.hh"
#include <TString.h>

// user classes
class QweakSimHDCMessenger;
class QweakSimMaterial;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//class QweakSimHDC: public QweakSimVGeometryComponent
//class QweakSimHDC: public G4VUserDetectorConstruction
class QweakSimHDC
{
public:
  QweakSimHDC();
  ~QweakSimHDC();

  void ConstructComponent(G4VPhysicalVolume*);
  void DestroyComponent();

  //=============
  // Set function
  //=============

  void SetHDC_MasterContainerMaterial(G4String);
  void SetHDC_SubContainerMaterial(G4String);
  void SetHDC_FrameMaterial(G4String);
  void SetHDC_FoilMaterial(G4String);
  void SetHDC_WirePlaneMaterial(G4String);

  void SetFrontHDC_CenterPositionInX(G4double xPos, G4int pkg);
  void SetFrontHDC_CenterPositionInY(G4double yPos, G4int pkg);
  void SetFrontHDC_CenterPositionInZ(G4double zPos, G4int pkg);

  void SetBackHDC_CenterPositionInX(G4double xPos, G4int pkg);
  void SetBackHDC_CenterPositionInY(G4double yPos, G4int pkg);
  void SetBackHDC_CenterPositionInZ(G4double zPos, G4int pkg);

  void SetHDC_RotationAngleInPhi(G4double HDC_phiangle, G4int pkg);


  //=============
  // Get function
  //=============
  
  G4LogicalVolume*   getHDC_LogicalVolume()    {return HDC_MasterContainer_Logical;} 

  G4VPhysicalVolume* getHDCFront_PhysicalVolume()   {return HDC_MasterContainerFront_Physical[0];}
  G4VPhysicalVolume* getHDCBack_PhysicalVolume()    {return HDC_MasterContainerBack_Physical[0];}

  G4LogicalVolume*   getHDC_Frame_LogicalVolume()    {return HDC_Frame_Logical;} 
  G4VPhysicalVolume* getHDC_Frame_PhysicalVolume()   {return HDC_Frame_Physical;}


  G4LogicalVolume*   getHDC_Foil_LogicalVolume()    {return HDC_Foil_Logical;} 
  G4VPhysicalVolume* getHDC_Foil_PhysicalVolume()   {return HDC_Foil_Physical;} 

  G4LogicalVolume*   getHDC_WirePlane_LogicalVolume()    {return HDC_WirePlane_Logical;} 
  G4VPhysicalVolume* getHDC_WirePlane_PhysicalVolume()   {return HDC_WirePlane_Physical;} 


  G4double GetHDC_RotationAngleInPhi() {return HDC_RotationAngleInPhi[0];} 

private:

   void PlaceHDC_MasterContainers();

   // mean bending angle after MainMagnet
    G4double MeanTrackAngle;  // ~ 20.8*degree

  QweakSimMaterial*  pMaterial;

  G4VPhysicalVolume* theMotherPV;  //pointer to MotherVolume
  
  G4VPhysicalVolume* HDC_PackageContainer_Physical;

  std::vector<G4RotationMatrix*> Rotation_HDC; // for Phi angle orientation
  G4double          HDC_RotationAngleInPhi[2];

  G4LogicalVolume*   HDC_MasterContainer_Logical; 
  std::vector<G4VPhysicalVolume*> HDC_MasterContainerFront_Physical;
  std::vector<G4VPhysicalVolume*> HDC_MasterContainerBack_Physical;

  G4LogicalVolume*   HDC_SubContainer_Logical; 
  G4VPhysicalVolume* HDC_SubContainer_Physical; 

  G4LogicalVolume*   HDC_Frame_Logical; 
  G4VPhysicalVolume* HDC_Frame_Physical; 

  G4LogicalVolume*   HDC_Foil_Logical; 
  G4VPhysicalVolume* HDC_Foil_Physical; 

  G4LogicalVolume*   HDC_WirePlane_Logical; 
  G4VPhysicalVolume* HDC_WirePlane_Physical; 

  std::vector<QweakSimHDCMessenger*> HDC_Messenger;  // pointer to the Messenger

  G4double HDCFrame_Thickness; 
  G4double HDCFrame_OuterLength;
  G4double HDCFrame_OuterWidth; 
  G4double HDCFrame_InnerLength;
  G4double HDCFrame_InnerWidth; 
  G4double HDCFrame_BorderWidthInX; 
  G4double HDCFrame_BorderWidthInY; 

  G4double HDC_DriftCell_TotalThickness; 

  G4double AluFrame_Thickness; 
  G4double AluFrame_OuterLength;
  G4double AluFrame_OuterWidth; 
  G4double AluFrame_InnerLength;
  G4double AluFrame_InnerWidth; 

  G4double HDC_CenterPositionInZ;
  
  std::vector<G4double> HDC_CenterFront_XPos;
  std::vector<G4double> HDC_CenterFront_YPos;
  std::vector<G4double> HDC_CenterFront_ZPos;

  std::vector<G4double> HDC_CenterBack_XPos;
  std::vector<G4double> HDC_CenterBack_YPos;
  std::vector<G4double> HDC_CenterBack_ZPos;

 
  G4VisAttributes* HDC_MasterContainer_VisAtt;
  G4VisAttributes* HDC_SubContainer_VisAtt;
  G4VisAttributes* HDC_Frame_VisAtt;
  G4VisAttributes* HDC_Foil_VisAtt;
  G4VisAttributes* HDC_WirePlane_VisAtt;

  //  QweakSimHDCSD*  driftChamberSD; // pointer to the sensitive DC
  G4VSensitiveDetector* HdriftChamberSD;
 
  G4SubtractionSolid*   HDC_Frame_Solid;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimHDC.hh,v $
//      Revision 1.2  2005/12/27 19:24:35  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
