//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimVDC_DriftCellParameterisation.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:19:38 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:19:38 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimVDC_DriftCellParameterisation.hh"

// geant4 includes
#include "G4ThreeVector.hh"
#include "G4VPhysicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimVDC_DriftCellParameterisation::QweakSimVDC_DriftCellParameterisation( G4int NumberOfDriftCells, G4double SpacingInX)
{
   myNumberOfDriftCells =  NumberOfDriftCells; 
   mySpacingInX         =  SpacingInX;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimVDC_DriftCellParameterisation::~QweakSimVDC_DriftCellParameterisation()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimVDC_DriftCellParameterisation::ComputeTransformation (const G4int copyNo, G4VPhysicalVolume* physVol) const
{
  // assuming ODD numbers of drift cells, because then we have
  // a wire going through the center of the wire plane

  G4double Xposition = (-0.5*(myNumberOfDriftCells - 1))*mySpacingInX + (copyNo * mySpacingInX);

  G4ThreeVector origin(Xposition,0,0);
  physVol->SetTranslation(origin);
  physVol->SetRotation(0);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDC_DriftCellParameterisation.cc,v $
//      Revision 1.2  2005/12/27 19:19:38  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
