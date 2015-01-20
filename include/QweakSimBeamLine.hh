
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimBeamLine.hh
   $Revision: 1.2 $	
   $Date: 2011/10/19 12:44 $
   \author Peiqing Wang
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimBeamLine
    
   \brief Definition of the BeamLine

   Placeholder for a long explaination
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimBeamLine_h
#define QweakSimBeamLine_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// 
// geant4 includes
#include "G4Material.hh"
#include "G4LogicalVolume.hh"

// user includes
#include "QweakSimBeamLineMessenger.hh"
#include "QweakSimUserInformation.hh"
#include "QweakSimMaterial.hh"

// system classes
// class G4Tubs;
// class G4LogicalVolume;
// class G4VPhysicalVolume;
// class G4Material;
// class G4VisAttributes;

// user classes
class QweakSimMaterial;
class QweakSimBeamLineMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimBeamLine
{
public:
  QweakSimBeamLine(QweakSimUserInformation *myUI);
  ~QweakSimBeamLine();

  void ConstructComponent(G4VPhysicalVolume*);
  void DestroyComponent();
  
  void SetBeamLineCenterPositionInZ(G4double);
  G4double GetBeamLineCenterPositionInZ();
  
  void SetBeamLineMaterial(G4String);
  G4String GetBeamLineMaterial();
  
  //G4LogicalVolume*   getBeamLineLogicalVolume()    {return BeamLineContainer_Logical;} 
  //G4VPhysicalVolume* getBeamLinePhysicalVolume()   {return BeamLineContainer_Physical;} 
  
private:

  QweakSimMaterial* pMaterial;

  //G4LogicalVolume*   BeamLineContainer_Logical; 
  //G4VPhysicalVolume* BeamLineContainer_Physical; 
  //G4Material*        BeamLineContainer_Material;  

  G4Material*        BeamPipe_Material;  
  G4Material*        Shield_Material;
    
  G4LogicalVolume*   R1_Pipe_Logical;
  G4LogicalVolume*   R1_Flange_Logical;
  G4LogicalVolume*   DS_R1_Pipe_Logical;
  G4LogicalVolume*   DS_R1_Flange_Logical;
  G4LogicalVolume*   DS_R1_Bellow_Logical;
  G4LogicalVolume*   R2_Pipe_Logical;
  G4LogicalVolume*   R2_Flange_Logical;
  G4LogicalVolume*   DS_R2_Pipe_Logical;
  G4LogicalVolume*   R2_RotatorPipe_Logical;
  G4LogicalVolume*   R3_Pipe_Logical;
  G4LogicalVolume*   R3_Flange_Logical;
  G4LogicalVolume*   DS_R3_Pipe_Logical;
  G4LogicalVolume*   R3_US_Wall_Pipe_Logical;
  G4LogicalVolume*   Sub_LeadBox_in_Wall_Logical;
  G4LogicalVolume*   R3_Wall_Pipe_Logical;
  G4LogicalVolume*   Sub_LeadBox_Extent_Logical;
  G4LogicalVolume*   DS_18inch_Pipe1_Logical;
  G4LogicalVolume*   DS_18inch_Pipe2_Logical;
  G4LogicalVolume*   DS_24inch_Pipe_Logical;
  G4LogicalVolume*   DS_24inch_Pipe_Flange_Logical;
	
  G4double beamline_ZPos;
  
  QweakSimBeamLineMessenger* beamlineMessenger;  // pointer to the Messenger
  QweakSimUserInformation *myUserInfo;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
