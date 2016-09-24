//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**

   \file QweakSimDetectorConstruction.hh
   $Revision: 1.4 $
   $Date: 2006/05/02 00:58:26 $
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
   \class QweakSimDetectorConstruction

   \brief main class of QweakSim.
   All experiment components are are placed here.

   Placeholder for a long explaination

*/
//=============================================================================

#ifndef QweakSimDetectorConstruction_h
#define QweakSimDetectorConstruction_h 1

// geant4 includes
#include "G4VUserDetectorConstruction.hh"

// geant4 classes
class G4Box;
class G4LogicalVolume;
class G4Material;
class G4VisAttributes;
class G4FieldManager;
class G4ChordFinder;
class G4Mag_EqRhs;
class G4MagIntegratorStepper;

// user classes
class QweakSimDetectorMessenger;
class QweakSimMaterial;
class QweakSimGeometry;
class QweakSimGeometryMessenger;
class QweakSimTarget;
class QweakSimTargetMessenger;
class QweakSimBeamLine;
class QweakSimBeamLineMessenger;
class QweakSimTungstenPlug;
class QweakSimCollimator;
class QweakSimCollimatorSupport;
class QweakSimShieldingWall;
class QweakSimPionWall;
class QweakSimWShutters;
class QweakSimLeadGlass;
class QweakSimPMTOnly;
class QweakSimMainMagnet;
class QweakSimVDC;
class QweakSimVDCRotator;
class QweakSimHDC;
// class QweakSimGEM;
class QweakSimTriggerScintillator;
class QweakSimCerenkovDetector;
class QweakSimLumiDetector;
class QweakSimMagneticField;
class QweakSimUserInformation;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimDetectorConstruction : public G4VUserDetectorConstruction
{
public:

  QweakSimDetectorConstruction(QweakSimUserInformation*);
  ~QweakSimDetectorConstruction();

public:

  G4VPhysicalVolume* Construct();

  void UpdateGeometry();
  void SetGlobalMagneticField();
  void ShowHallFloor();
  void HideHallFloor();

  G4double   GetWorldFullLengthInX()    {return fWorldLengthInX;}
  G4double   GetWorldFullLengthInY()    {return fWorldLengthInY;}
  G4double   GetWorldFullLengthInZ()    {return fWorldLengthInZ;}

  void DumpGeometry(
		    G4bool surfchk = false,
		    G4VPhysicalVolume* aVolume = 0,
		    G4int depth = 0);

private:

  QweakSimUserInformation* myUserInfo;
  G4VPhysicalVolume*       ConstructQweak();

  QweakSimGeometry*          pGeometry;

  QweakSimMaterial*          pMaterial;

  QweakSimTarget*            pTarget;
  QweakSimBeamLine*          pBeamLine;

  QweakSimTungstenPlug*      pTungstenPlug;
  QweakSimCollimator*        pCollimator1;
  QweakSimCollimator*        pCollimator2;
  QweakSimCollimator*        pCollimator3;

  QweakSimCollimatorSupport* pCollimatorSupport;

  QweakSimShieldingWall*     pShieldingWall;
 
  QweakSimPionWall*          pPionWall;

  QweakSimWShutters*		 pWShutters1;
  QweakSimWShutters*		 pWShutters2;
	
  QweakSimLeadGlass*         pLeadGlass;

  QweakSimPMTOnly* 		pPMTOnly;

  QweakSimMainMagnet*        pMainMagnet;


  QweakSimVDC*                  pVDC;
  QweakSimHDC*                  pHDC;
  //QweakSimGEM*                  pGEM;

  QweakSimVDCRotator*           pVDCRotator;

  QweakSimTriggerScintillator*  pTriggerScintillator;
  QweakSimCerenkovDetector*     pCerenkovDetector;
  QweakSimLumiDetector*     pLumiDetector;
  //G4VReadOutGeometry*        pROHitPlane;

  QweakSimDetectorMessenger*      detectorMessenger;  // pointer to the Messenger

  G4Box*             experimentalHall_Solid;     // pointer to the solid envelope
  G4LogicalVolume*   experimentalHall_Logical;   // pointer to the logical envelope
  G4VPhysicalVolume* experimentalHall_Physical;  // pointer to the physical envelope
  G4Material*        experimentalHall_Material;

  G4Box*             HallFloor_Solid;     // pointer to the solid envelope
  G4LogicalVolume*   HallFloor_Logical;   // pointer to the logical envelope
  G4VPhysicalVolume* HallFloor_Physical;  // pointer to the physical envelope
  G4Material*        HallFloor_Material;
  G4VisAttributes*   HallFloor_VisAtt;

  G4double fWorldLength;               // Full length of the world volume
  G4double fWorldLengthInX;            // Full length of the world volume
  G4double fWorldLengthInY;            // Full length of the world volume
  G4double fWorldLengthInZ;            // Full length of the world volume

  G4double fFloorLengthInX;
  G4double fFloorLengthInY;
  G4double fFloorLengthInZ;
  G4double fFloorPositionInY;

  //----------------------
  // global magnet section
  //----------------------
  //
  QweakSimMagneticField*  pMagneticField;

  G4FieldManager*         fGlobalFieldManager;
  G4ChordFinder*          fGlobalChordFinder;
  G4Mag_EqRhs*            fGlobalEquation;
  G4MagIntegratorStepper* fGlobalStepper;

  G4double                fMinStep;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
//
//      $Revisions$
//      $Log: QweakSimDetectorConstruction.hh,v $
//      Revision 1.4  2006/05/02 00:58:26  grimm
//      Implemented VDC Rotator
//
//      Revision 1.3  2005/12/28 22:49:21  grimm
//      Added QweakSimCollimatorSupport into the world
//
//      Revision 1.2  2005/12/27 19:23:20  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
