
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimCollimatorSupport.hh
   $Revision: 1.2 $	
   $Date: 2005/12/28 22:45:44 $
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
   \class QweakSimCollimatorSupport
    
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
//  Update Date:      $Date: 2005/12/28 22:45:44 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef QweakSimCollimatorSupport_h
#define QweakSimCollimatorSupport_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// user includes
#include "QweakSimMaterial.hh"
#include "QweakSimCollimator.hh"

// user classes
class QweakSimMaterial;
class QweakSimCollimator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimCollimatorSupport
{

private:

  QweakSimMaterial* pMaterial;

  QweakSimCollimator* FirstCollimator;
  QweakSimCollimator* LastCollimator;

  // Top Cover
  G4LogicalVolume*   CollimatorSupport_TopCover_Logical; 
  G4VPhysicalVolume* CollimatorSupport_TopCover_Physical; 

  G4double TopCover_FullLength_X;
  G4double TopCover_FullLength_Y;
  G4double TopCover_FullLength_Z;

  G4double TopCover_CenterXPosition;
  G4double TopCover_CenterYPosition;
  G4double TopCover_CenterZPosition;

  // Bottom Cover
  G4LogicalVolume*   CollimatorSupport_BottomCover_Logical; 
  G4VPhysicalVolume* CollimatorSupport_BottomCover_Physical; 

  G4double BottomCover_FullLength_X;
  G4double BottomCover_FullLength_Y;
  G4double BottomCover_FullLength_Z;

  G4double BottomCover_CenterXPosition;
  G4double BottomCover_CenterYPosition;
  G4double BottomCover_CenterZPosition;

  // Left Cover
  G4LogicalVolume*   CollimatorSupport_LeftCover_Logical; 
  G4VPhysicalVolume* CollimatorSupport_LeftCover_Physical; 

  G4double LeftCover_FullLength_X;
  G4double LeftCover_FullLength_Y;
  G4double LeftCover_FullLength_Z;

  G4double LeftCover_CenterXPosition;
  G4double LeftCover_CenterYPosition;
  G4double LeftCover_CenterZPosition;

  // Right Cover
  G4LogicalVolume*   CollimatorSupport_RightCover_Logical; 
  G4VPhysicalVolume* CollimatorSupport_RightCover_Physical; 

  G4double RightCover_FullLength_X;
  G4double RightCover_FullLength_Y;
  G4double RightCover_FullLength_Z;

  G4double RightCover_CenterXPosition;
  G4double RightCover_CenterYPosition;
  G4double RightCover_CenterZPosition;


public:
    //!Constructor
  QweakSimCollimatorSupport(QweakSimCollimator* ,QweakSimCollimator* );

  //!Destructor
  ~QweakSimCollimatorSupport();


  void ConstructSupport(G4VPhysicalVolume*);
  void SetCollimatorSupportMaterial(G4String);


  G4LogicalVolume*   GetCollimatorSupport_TopCover_LogicalVolume()     {return CollimatorSupport_TopCover_Logical;} 
  G4VPhysicalVolume* GetCollimatorSupport_TopCover_PhysicalVolume()    {return CollimatorSupport_TopCover_Physical;} 

  G4LogicalVolume*   GetCollimatorSupport_BottomCover_LogicalVolume()  {return CollimatorSupport_BottomCover_Logical;} 
  G4VPhysicalVolume* GetCollimatorSupport_BottomCover_PhysicalVolume() {return CollimatorSupport_BottomCover_Physical;} 

  G4LogicalVolume*   GetCollimatorSupport_LeftCover_LogicalVolume()    {return CollimatorSupport_LeftCover_Logical;} 
  G4VPhysicalVolume* GetCollimatorSupport_LeftCover_PhysicalVolume()   {return CollimatorSupport_LeftCover_Physical;} 

  G4LogicalVolume*   GetCollimatorSupport_RightCover_LogicalVolume()   {return CollimatorSupport_RightCover_Logical;} 
  G4VPhysicalVolume* GetCollimatorSupport_RightCover_PhysicalVolume()  {return CollimatorSupport_RightCover_Physical;} 

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
//      $Log: QweakSimCollimatorSupport.hh,v $
//      Revision 1.2  2005/12/28 22:45:44  grimm
//      Completed all cover plates (Top, Bottom, Left, Right)
//      Plate dimensions and location are extracted dynamically from the upstream and downstream collimator positions and sizes.
//
//      Revision 1.1  2005/12/28 18:30:46  grimm
//      First Version of a support/shielding of the 3 collimators.
//      At present only a top cover is implemented with rather arbitrary size and position.
//
// 

