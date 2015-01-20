
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimVDCRotator.hh
   $Revision: 1.2 $	
   $Date: 2006/05/05 21:18:13 $
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
   \class QweakSimVDCRotator
    
   \brief Definition of the Support/Shielding of the Collimators

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
//  Update Date:      $Date: 2006/05/05 21:18:13 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef QweakSimVDCRotator_h
#define QweakSimVDCRotator_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <vector>

// geant4 includes
#include "G4Types.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include <TString.h>

// geant4 classes
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4SubtractionSolid;

// user classes
class QweakSimMaterial;
class QweakSimVDC;
class QweakSimVDCMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimVDCRotator
{

private:

  QweakSimMaterial* pMaterial;

  QweakSimVDC*       DualVDC;

  G4double           kAngle_GlobalRotation;

  G4VPhysicalVolume* theMotherVolume;
  
  G4VPhysicalVolume* RotatorMasterContainer_Physical;

  G4double kRing_RadiusMin;
  G4double kRing_RadiusMax;
  G4double kRing_FullThickness;
  G4double kRing_PhiAngleStart;
  G4double kRing_PhiAngleEnd;

  // Upstream Ring
  G4LogicalVolume*   UpstreamRing_Logical; 
  G4VPhysicalVolume* UpstreamRing_Physical; 

  G4double UpstreamRing_CenterXPosition;
  G4double UpstreamRing_CenterYPosition;
  G4double UpstreamRing_CenterZPosition;

  // Downstream Ring
  G4LogicalVolume*   DownstreamRing_Logical; 
  G4VPhysicalVolume* DownstreamRing_Physical; 

  G4double DownstreamRing_CenterXPosition;
  G4double DownstreamRing_CenterYPosition;
  G4double DownstreamRing_CenterZPosition;


  // Rails
  G4double kRail_FullLength_X;
  G4double kRail_FullLength_Y;
  G4double kRail_FullLength_Z;
  G4double kRail_CenterPositionInR;
  G4double kRail_CenterPositionInZ;

  G4ThreeVector      Translation_LeftRail;
  G4ThreeVector      Translation_RightRail;
  G4RotationMatrix*  Rotation_Rail;

  G4LogicalVolume*   Rail_Logical; 
  G4VPhysicalVolume* LeftRail_Physical; 
  G4VPhysicalVolume* RightRail_Physical; 

  //-----------------
  // Rods: Left/Right
  //-----------------
  G4double kRod_LR_RadiusMin;
  G4double kRod_LR_RadiusMax;
  G4double kRod_LR_FullThickness;
  G4double kRod_LR_PhiAngleStart;
  G4double kRod_LR_PhiAngleEnd;

  G4double kRod_LR_StubLength;
  G4double kRod_LR_Distance;

  G4double kRod_LR_CenterPositionInR;

  std::vector< G4double > kRod_LR_CenterPositionInX;
  std::vector< G4double > kRod_LR_CenterPositionInY;
  std::vector< G4double > kRod_LR_CenterPositionInZ;

  G4LogicalVolume*   Rod_LeftRight_Logical;
  
  std::vector< G4VPhysicalVolume* > Rod_LeftRight_Physical;
  
  G4ThreeVector Translation_RodLeftUpstream;
  G4ThreeVector Translation_RodLeftDownstream;
  G4ThreeVector Translation_RodRightUpstream;
  G4ThreeVector Translation_RodRightDownstream;
  
  G4RotationMatrix*  Rotation_Rod_LR;


  //-----------------
  // Slider Support
  //-----------------
  G4double kSliderSupport_FullLength_X;
  G4double kSliderSupport_FullLength_Y;
  G4double kSliderSupport_FullLength_Z;

  G4double kSliderSupport_CenterPositionInX;
  G4double kSliderSupport_CenterPositionInY;
  G4double kSliderSupport_CenterPositionInZ;

  G4ThreeVector      Translation_LeftSliderSupport;
  G4ThreeVector      Translation_RightSliderSupport;

  G4RotationMatrix*  Rotation_SliderSupportLeft;
  G4RotationMatrix*  Rotation_SliderSupportRight;

  G4LogicalVolume*   SliderSupportLeft_Logical; 
  std::vector <G4VPhysicalVolume*> SliderSupportLeft_Physical;

  G4LogicalVolume*   SliderSupportRight_Logical; 
  std::vector <G4VPhysicalVolume*> SliderSupportRight_Physical;

  // needed for shaping
  std::vector< G4SubtractionSolid* >  SliderSupportSubtraction_TempSolid;


 public:
    //!Constructor
  //QweakSimVDCRotator(QweakSimVDC*);
  QweakSimVDCRotator();

  //!Destructor
  ~QweakSimVDCRotator();

  void SetMotherVolume(G4VPhysicalVolume* mv) { theMotherVolume = mv;}
  void ConstructRotatorMasterContainer();
  void ConstructRings();
  void ConstructRails();
  void ConstructMount();
  void ConstructSliderSupport();

  void PlacePVSliderSupport(int pkg);
  void PlacePVRails();
  void PlacePVMount();

  void SetRingMaterial(G4String);
  void SetRotationAngleInPhi(G4double vdc_phiangle);

  G4LogicalVolume*   GetUpstreamRing_LogicalVolume()     {return UpstreamRing_Logical;} 
  G4VPhysicalVolume* GetUpstreamRing_PhysicalVolume()    {return UpstreamRing_Physical;} 

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDCRotator.hh,v $
//      Revision 1.2  2006/05/05 21:18:13  grimm
//      - The orientation of the rod for Left/Right alignment works now for all Phi angles
//      - More realistic G0 slider : subtraction of solids for building slider profile
//
//      Revision 1.1  2006/05/02 00:52:33  grimm
//      Initial Implementation of the VDC Rotator based on the design of Paulo Medeiros.
//


