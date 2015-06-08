#ifndef QweakSimSolids_h
#define QweakSimSolids_h

#include "QweakSimSystemOfUnits.hh"

// geant4 includes
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4Trd.hh"
#include "G4Cons.hh"
#include "G4Hype.hh"
#include "G4Para.hh"
#include "G4Trap.hh"
#include "G4Tubs.hh"
#include "G4Torus.hh"
#include "G4Sphere.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4PVPlacement.hh"
#include "G4OpticalSurface.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

// geant4 classes
class G4Box;
class G4Trd;
class G4Cons;
class G4Trap;
class G4Tubs;
class G4Polycone;
class G4Polyhedra;

// Global variable to enable overlapping volume checks
static const G4bool pSurfChk = false;

#endif
