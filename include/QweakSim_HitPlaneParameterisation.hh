
#ifndef QweakSim_HitPlaneParameterisation_H
#define QweakSim_HitPlaneParameterisation_H 

#include "globals.hh"
#include "G4VPVParameterisation.hh"
#include "/data/local/include/geant4/G4Box.hh"
#include "/data/local/include/geant4/G4Trd.hh"
#include "/data/local/include/geant4/G4Trap.hh"
#include "/data/local/include/geant4/G4Cons.hh"
#include "/data/local/include/geant4/G4Para.hh"
#include "/data/local/include/geant4/G4Tubs.hh"
#include "/data/local/include/geant4/G4Polycone.hh"
#include "/data/local/include/geant4/G4Polyhedra.hh"
#include "/data/local/include/geant4/G4OpBoundaryProcess.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSim_HitPlaneParameterisation : public G4VPVParameterisation
{ 
public:
  
  QweakSim_HitPlaneParameterisation( G4int    NumberOfHitPlanes, 
				     G4double SpacingInZ,
				     G4double StartPosInZ,
				     G4double EndPosInZ );
  
  virtual ~QweakSim_HitPlaneParameterisation();
   
  void ComputeTransformation (const G4int copyNo,
			      G4VPhysicalVolume* physVol) const;
  
  
private:  // Dummy declarations to get rid of warnings ...
  
  void ComputeDimensions (G4Box&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Tubs&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
  void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}
  
private:
  
  G4int    myNumberOfHitPlanes; 
  G4double mySpacingInZ;        
  G4double myStartPosInZ;         
  G4double myEndPosInZ;         
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


