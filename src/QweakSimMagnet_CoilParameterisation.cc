//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimMagnet_CoilParameterisation.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:12:32 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:12:32 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimMagnet_CoilParameterisation.hh"

// geant4 includes
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimMagnet_CoilParameterisation::QweakSimMagnet_CoilParameterisation( G4double RadialDistanceToBeamLine )
{
   myRadialDistanceToBeamLine  =  RadialDistanceToBeamLine;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimMagnet_CoilParameterisation::~QweakSimMagnet_CoilParameterisation()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimMagnet_CoilParameterisation::ComputeTransformation (const G4int copyNo, G4VPhysicalVolume* physVol) const
{

  G4double Angle_Coil = ((45.0*copyNo)+22.5)*degree;

  // confusion: angle def is different to ShieldingWall OctantCuts
  G4double myPositionInX = sin(Angle_Coil)*myRadialDistanceToBeamLine;
  G4double myPositionInY = cos(Angle_Coil)*myRadialDistanceToBeamLine;
  G4double myPositionInZ = 0.0*cm;

  G4RotationMatrix*  Rotation_Coil = new G4RotationMatrix();
  Rotation_Coil->rotateZ(Angle_Coil);

  G4ThreeVector origin(myPositionInX , myPositionInY, myPositionInZ);

  physVol->SetTranslation(origin);
  physVol->SetRotation(Rotation_Coil);

  // delete Rotation_Coil;

  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMagnet_CoilParameterisation.cc,v $
//      Revision 1.2  2005/12/27 19:12:32  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

