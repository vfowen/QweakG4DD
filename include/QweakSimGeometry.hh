//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**

   \file QweakSimGeometry.hh
   $Revision: 0.1 $
   $Date: 2009/09/02 19:37:26 $
   \author Wouter Deconinck

*/
//=============================================================================
//
//=============================================================================
//
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimGeometry

   \brief main class of QweakSim.
    All passive elements are are read from the GDML files.

 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
//
//  Last Update:      $Author: wdconinc $
//  Update Date:      $Date: 2009/09/02 19:37:26 $
//  CVS/RCS Revision: $Revision: 1.0 $
//  Status:           $State: Exp $
//
//=============================================================================

#ifndef QweakSimGeometry_h
#define QweakSimGeometry_h 1

// geant4 includes
#include "G4VPhysicalVolume.hh"
#ifdef G4LIB_USE_GDML
#include "G4GDMLParser.hh"
#endif

// user includes
#include "QweakSimGeometryMessenger.hh"

// user classes
class QweakSimGeometryMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimGeometry
{
  public:

    QweakSimGeometry();
   ~QweakSimGeometry();

    // Set world volume
    //
    void SetWorldVolume(G4VPhysicalVolume* worldvolume) { fWorldVolume = worldvolume; };

    // Reading and writing file name
    //
    void SetReadFile(const G4String& file)  { fReadFile = file; };
    void SetWriteFile(const G4String& file) { fWriteFile = file; };

    // Writing user or automatic modules
    //
    void SetWriteModuleDepth(const G4int& depth) { fModuleDepth = depth; };
    void SetWriteModuleUser(const G4bool& flag)  { fModuleUser = flag; };

    // Adding modules
    void AddModule(G4VPhysicalVolume* physvol) {
      if (fModuleUser) {
        if (physvol) {
          #ifdef G4LIB_USE_GDML
            fGDMLParser.AddModule(physvol);
          #endif
        }
      }
    }

    // Read and write GDML files
    //
    G4VPhysicalVolume* Read();
    void Write();

  private:

    // World volume
    //
    G4VPhysicalVolume* fWorldVolume;

    // Modules
    //
    G4int fModuleDepth;
    G4bool fModuleUser;

    // Append pointer address to names
    G4bool fStoreReferences;

    // Read and write file names
    //
    G4String fReadFile;
    G4String fWriteFile;

#ifdef G4LIB_USE_GDML
    // GDMLparser
    //
    G4GDMLParser fGDMLParser;
#endif

    // Geometry Messenger
    //
    QweakSimGeometryMessenger* fGeometryMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
