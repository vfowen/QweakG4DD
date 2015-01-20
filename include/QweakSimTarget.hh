
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTarget.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:27:07 $
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
   \class QweakSimTarget
    
   \brief Definition of the Target

   Placeholder for a long explaination
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimTarget_h
#define QweakSimTarget_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// 
// geant4 includes
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

// system includes
//#include "cpp_include.h"
//#include "Root_include.h"
//#include "Geant4_include.hh" 

// user includes
#include "QweakSimTargetMessenger.hh"
#include "QweakSimUserInformation.hh"
#include "QweakSimMaterial.hh"

// system classes
// class G4Tubs;
// class G4LogicalVolume;
// class G4VPhysicalVolume;
// class G4Material;
// class G4VisAttributes;

// user classes
class QweakSimMaterial;
class QweakSimTargetMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimTarget
{
public:
  QweakSimTarget(QweakSimUserInformation *myUI);
  ~QweakSimTarget();

  void ConstructComponent(G4VPhysicalVolume*);
  void DestroyComponent();
  
  void SetTargetCenterPositionInZ(G4double);
  G4double GetTargetCenterPositionInZ();
  
  void SetTargetMaterial(G4String);
  G4String GetTargetMaterial();
  
  void SetTargetCellMaterial(G4String);
  G4String GetTargetCellMaterial();

  void SetTargetEntranceWindowMaterial(G4String);
  G4String GetTargetEntranceMaterial();
  
  void SetTargetExitWindowMaterial(G4String);
  G4String GetTargetExitWindowMaterial();
  
  void SetTargetExitWindowNippleMaterial(G4String);
  G4String GetTargetExitWindowNippleMaterial();
  
  G4LogicalVolume*   getTargetLogicalVolume()    {return TargetMaterial_Logical;} 
  G4VPhysicalVolume* getTargetPhysicalVolume()   {return TargetMaterial_Physical;} 

  void SetTargetLength(G4double);
  G4double GetTargetLength();

  void SetTarget(G4String);
  void SetTargetEntranceWindowLength(G4double);
  void SetTargetExitWindowLength(G4double);
  void SetTargetExitWindowNippleLength(G4double);

  G4double CalculateLuminosity(G4double mass, G4double density, G4double length);

private:

  G4VPhysicalVolume* theMotherPV;

  QweakSimMaterial* pMaterial;

  G4LogicalVolume*   TargetCell_Logical; 
  G4VPhysicalVolume* TargetCell_Physical; 
  G4Material*        TargetCell_Material;  

  G4LogicalVolume*   TargetEntranceWindow_Logical; 
  G4VPhysicalVolume* TargetEntranceWindow_Physical; 
  G4Material*        TargetEntranceWindow_Material;  
  
  G4LogicalVolume*   TargetExitWindow_Logical; 
  G4VPhysicalVolume* TargetExitWindow_Physical;
  G4Material*        TargetExitWindow_Material;  
  
  G4LogicalVolume*   TargetExitWindowNipple_Logical; 
  G4VPhysicalVolume* TargetExitWindowNipple_Physical;
  G4Material*        TargetExitWindowNipple_Material;  
  
  G4LogicalVolume*   ScatteringChamberWindow_Logical;
  G4VPhysicalVolume* ScatteringChamberWindow_Physical;
  G4Material*        ScatteringChamberWindow_Material;
  
  G4LogicalVolume*   TargetMaterial_Logical;
  G4VPhysicalVolume* TargetMaterial_Physical;
  G4Material*        TargetMaterial_Material;

  G4LogicalVolume*   TargetContainer_Logical;
  G4VPhysicalVolume* TargetContainer_Physical;
  G4Material*        TargetContainer_Material;

  G4double targetCellEntranceWindowThickness;
  G4double targetCellExitWindowThickness;
  G4double targetCellExitWindowNippleThickness;
  G4double targetCellWallThickness;

  G4double targetCellInnerLength;               
  G4double targetCellOuterLength;

  G4double targetCellFrontRadiusMin;
  G4double targetCellFrontInnerRadiusMax;
  G4double targetCellFrontOuterRadiusMax;

  G4double targetCellBackRadiusMin;
  G4double targetCellBackInnerRadiusMax;
  G4double targetCellBackOuterRadiusMax;

  G4double targetCellExitWindowNippleRadius;
  
  G4double ScatteringChamberWindowRadius;
  G4double ScatteringChamberWindowThickness;
  
  G4double targetCellStartingPhi;
  G4double targetCellDeltaPhi;
  G4double targetZPos;

  QweakSimTargetMessenger* targetMessenger;  // pointer to the Messenger
  QweakSimUserInformation *myUserInfo;

  G4ThreeVector positionTarget;
  G4ThreeVector positionTargetEntranceWindow;
  G4ThreeVector positionTargetExitWindow;
  G4ThreeVector positionScatteringChamberWindow;

  G4VSensitiveDetector* TargetSD;

  void CalculateTargetPositions();

  void ConstructTargetContainer(); // scattering chamber
  void ConstructScatteringChamberWindow();

  void ConstructTargetCell(); // Al cell without end caps
  void ConstructTargetMaterial();  // LH2 for production target

  void ConstructTargetEntranceWindow();
  void ConstructTargetExitWindow();
  void ConstructTargetExitWindowNipple();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
