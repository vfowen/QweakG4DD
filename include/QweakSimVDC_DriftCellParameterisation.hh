
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimVDC_DriftCellParameterisation.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:32:20 $
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
   \class QweakSimVDC_DriftCellParameterisation
    
   \brief Parameterisation of the VDC Drift Cell locations

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
//  Update Date:      $Date: 2005/12/27 19:32:20 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimVDC_DriftCellParameterisation_H
#define QweakSimVDC_DriftCellParameterisation_H 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// geant4 includes
#include "G4VPVParameterisation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimVDC_DriftCellParameterisation : public G4VPVParameterisation
{ 
public:
  
  QweakSimVDC_DriftCellParameterisation( G4int    NumberOfDriftCells, 
				     G4double SpacingInX);
  
  virtual ~QweakSimVDC_DriftCellParameterisation();
   
  void ComputeTransformation (const G4int copyNo,
			      G4VPhysicalVolume* physVol) const;
  

private:
  
  G4int    myNumberOfDriftCells; // Number DriftCells to be placed  
  G4double mySpacingInX;         //  The distance between the drift cell center
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimVDC_DriftCellParameterisation.hh,v $
//      Revision 1.2  2005/12/27 19:32:20  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

