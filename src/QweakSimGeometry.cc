//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimGeometry.cc

   $Revision: 1.0 $
   $Date: 2009/09/02 19:37:26 $

   \author Wouter Deconinck

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimGeometry.hh"

// geant4 includes
#ifdef G4LIB_USE_GDML
#include "G4GDMLParser.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimGeometry::QweakSimGeometry()
: fStoreReferences(true)
{
  G4cout << G4endl << "###### Calling QweakSimGeometry::QweakSimGeometry() " << G4endl << G4endl;

  // Filenames
  fReadFile  = "GDML/qweak.gdml";
  fWriteFile = "GDML/qweak_out.gdml";

  // Modules
  fModuleDepth = -1;
  fModuleUser = false;

#ifdef G4LIB_USE_GDML
#else
  G4cout << "No support for GDML geometry!" << G4endl;
#endif

  fGeometryMessenger = new QweakSimGeometryMessenger(this);

  G4cout << G4endl << "###### Leaving QweakSimGeometry::QweakSimGeometry() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimGeometry::~QweakSimGeometry()
{
  G4cout << G4endl << "###### Calling QweakSimGeometry::~QweakSimGeometry() " << G4endl << G4endl;

  if (fGeometryMessenger) delete fGeometryMessenger;

  G4cout << G4endl << "###### Leaving QweakSimGeometry::~QweakSimGeometry() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimGeometry::Write()
{
  G4cout << G4endl << "###### Calling QweakSimGeometry::Write() " << G4endl << G4endl;

#ifdef G4LIB_USE_GDML
  // If the module depth is non-negative, split according to this depth
  if (fModuleDepth >= 0)
    fGDMLParser.AddModule(fModuleDepth);
  // Write all geometry starting from the world volume
  fGDMLParser.Write(fWriteFile, fWorldVolume, fStoreReferences);
#else
  G4cout << "No support for GDML geometry!" << G4endl;
#endif

  G4cout << G4endl << "###### Leaving QweakSimGeometry::Write() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* QweakSimGeometry::Read()
{
  G4cout << G4endl << "###### Calling QweakSimGeometry::Read() " << G4endl << G4endl;

#ifdef G4LIB_USE_GDML
  fGDMLParser.SetOverlapCheck(true);
  fGDMLParser.Read(fReadFile);
  fGDMLParser.StripNamePointers();

  G4cout << *(G4Element::GetElementTable()) << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  G4VPhysicalVolume* worldvolume = fGDMLParser.GetWorldVolume();
#else
  G4cout << "No support for GDML geometry!" << G4endl;
  G4VPhysicalVolume* worldvolume = NULL;
#endif

  G4cout << G4endl << "###### Leaving QweakSimGeometry::Read() " << G4endl << G4endl;

  return worldvolume;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
