//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimMagnet_CoilParameterisation.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:25:05 $
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
   \class QweakSimMagnet_CoilParameterisation
    
   \brief Parametrization of MainMagnet Coil orientation/setup

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
//  Update Date:      $Date: 2005/12/27 19:25:05 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimMagnet_CoilParameterisation_H
#define QweakSimMagnet_CoilParameterisation_H 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// geant4 includes
#include "G4VPVParameterisation.hh"

// system classes
//class G4VPhysicalVolume;

//// Dummy declarations to get rid of warnings ...
//class G4Box;
//class G4Trd;
//class G4Trap;
//class G4Cons;
//class G4Orb;
//class G4Sphere;
//class G4Torus;
//class G4Para;
//class G4Hype;
//class G4Tubs;
//class G4Polycone;
//class G4Polyhedra;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimMagnet_CoilParameterisation : public G4VPVParameterisation
{ 
public:
  
  QweakSimMagnet_CoilParameterisation( G4double RadialDistanceToBeamLine);
  
  virtual ~QweakSimMagnet_CoilParameterisation();
   
  void ComputeTransformation (const G4int copyNo,
			      G4VPhysicalVolume* physVol) const;
  
  
private:  // Dummy declarations to get rid of warnings ...
  
//  void ComputeDimensions (G4Box&,const G4int,const G4VPhysicalVolume*) const {}
//  void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
//  void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
//  void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
//  void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
//  void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
//  void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
//  void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
//  void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
//  void ComputeDimensions (G4Tubs&,const G4int,const G4VPhysicalVolume*) const {}
//  void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
//  void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}
  
private:
  
   G4double myRadialDistanceToBeamLine;   //  The distance between the drift cell center


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMagnet_CoilParameterisation.hh,v $
//      Revision 1.2  2005/12/27 19:25:05  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
