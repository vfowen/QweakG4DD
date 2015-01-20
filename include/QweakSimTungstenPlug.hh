/**
 
   \file QweakSimTungstenPlug.hh
   \author Wouter Deconinck
     
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef QweakSimTungstenPlug_h
#define QweakSimTungstenPlug_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// geant4 includes
#include "G4LogicalVolume.hh"

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// user classes
class QweakSimMaterial;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimTungstenPlug
{

private:

  QweakSimMaterial* pMaterial;
  
  // W-Plug

  G4LogicalVolume*   WPlug_US_Logical;
  G4VPhysicalVolume* WPlug_US_Physical;
  G4LogicalVolume*   WPlug_DS_Logical;
  G4VPhysicalVolume* WPlug_DS_Physical;

  G4Material*        WPlug_Material;  
  G4Material*        WPlug_Material_Vac;  

public:
  //! Constructor
  QweakSimTungstenPlug();

  //! Destructor
  virtual ~QweakSimTungstenPlug();

  void ConstructTungstenPlug(G4VPhysicalVolume*);

  G4VPhysicalVolume* getTungstenPlugUSPhysicalVolume()   {return WPlug_US_Physical;}
  G4VPhysicalVolume* getTungstenPlugDSPhysicalVolume()   {return WPlug_DS_Physical;}
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

