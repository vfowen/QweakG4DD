//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimDetectorConstruction.cc

   $Revision: 1.10 $
   $Date: 2006/05/05 21:40:08 $

   \author Klaus Hans Grimm

*/
//=============================================================================
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

 // Geometries and positions for collimators are double-checked and updated. 
 // -Peiqing  2011 Nov. 11

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimDetectorConstruction.hh"

// geant4 includes
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
//
#include "G4RunManager.hh"
#include "G4FieldManager.hh"
#include "G4GeometryManager.hh"
#include "G4TransportationManager.hh"
//
#include "G4Mag_UsualEqRhs.hh"
#include "G4Mag_SpinEqRhs.hh"
#include "G4PropagatorInField.hh"
#include "G4ChordFinder.hh"
#include "G4SimpleRunge.hh"


// user includes
#include "QweakSimSolids.hh"
#include "QweakSimDetectorMessenger.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimGeometry.hh"
#include "QweakSimGeometryMessenger.hh"
#include "QweakSimTarget.hh"
#include "QweakSimTargetMessenger.hh"
#include "QweakSimBeamLine.hh"
#include "QweakSimBeamLineMessenger.hh"
#include "QweakSimTungstenPlug.hh"
#include "QweakSimCollimator.hh"
#include "QweakSimCollimatorSupport.hh"
#include "QweakSimShieldingWall.hh"
#include "QweakSimPionWall.hh"
#include "QweakSimWShutters.hh"
#include "QweakSimLeadGlass.hh"
#include "QweakSimPMTOnly.hh"
#include "QweakSimMainMagnet.hh"
#include "QweakSimVDC.hh"
#include "QweakSimVDCRotator.hh"
#include "QweakSimHDC.hh"
//#include "QweakSimGEM.hh"
#include "QweakSimTriggerScintillator.hh"
#include "QweakSimCerenkovDetector.hh"
#include "QweakSimLumiDetector.hh"
#include "QweakSimMagneticField.hh"
#include "QweakSimUserInformation.hh"

static const G4double inch = 2.54*cm;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//===================================================================
//	Qweak *Geant4* Geometry Conventions:
//      The origin is at the center of the main toroidal magnet with
//	the z-axis pointing along the beam direction, the y-axis
//	pointing toward the ceiling, and the x-axis pointing toward
//	beam-left so as to form a right-handed coordinate system.
//	Octants are numbered from 1 to 8, clockwise with #1 at the
//	12 o-clock position.
//===================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimDetectorConstruction::QweakSimDetectorConstruction(QweakSimUserInformation *userInfo)
{
  // initialize pointers and variables
  experimentalHall_Solid    = NULL;
  experimentalHall_Logical  = NULL;
  experimentalHall_Physical = NULL;

  HallFloor_Solid    = NULL;
  HallFloor_Logical  = NULL;
  HallFloor_Physical = NULL;

  detectorMessenger = NULL;
  pMaterial         = NULL;
  pGeometry         = NULL;

  pMagneticField = NULL;

  pTriggerScintillator  = NULL;
  pCerenkovDetector     = NULL;
  pLumiDetector     = NULL;

  pTungstenPlug      = NULL;
  pCollimator1       = NULL;
  pCollimator2       = NULL;
  pCollimator3       = NULL;
  pCollimatorSupport = NULL;


  pShieldingWall     = NULL;
  
  pPionWall          = NULL;

  pWShutters1		 = NULL;
  pWShutters2		 = NULL;
	
  pLeadGlass         = NULL;
  
  pPMTOnly		 = NULL;

  // pGEM               = NULL;
  pHDC               = NULL;
  pVDC               = NULL;
  pVDCRotator        = NULL;

  pTarget            = NULL;
  pBeamLine          = NULL;
  pMainMagnet        = NULL;

  fWorldLengthInX = 0.0*cm;
  fWorldLengthInY = 0.0*cm;
  fWorldLengthInZ = 0.0*cm;

  fFloorLengthInX   = 0.0*cm;
  fFloorLengthInY   = 0.0*cm;
  fFloorLengthInZ   = 0.0*cm;
  fFloorPositionInY = 0.0*cm; // Top positon, not the center pos

  fGlobalEquation    = NULL;
  fGlobalStepper     = NULL;
  fGlobalChordFinder = NULL;

  HallFloor_VisAtt = NULL;
  HallFloor_VisAtt = new G4VisAttributes();

  myUserInfo = userInfo;

  detectorMessenger = new QweakSimDetectorMessenger(this);

  pMaterial         = new QweakSimMaterial();
  pMaterial->DefineMaterials();
}

QweakSimDetectorConstruction::~QweakSimDetectorConstruction()
{
  // I'm deleting the objects in the reverse order they were created (~FILO)

  if (pMagneticField) delete pMagneticField;

  if (pVDCRotator) delete pVDCRotator;
  // if (pGEM)        delete pGEM;
  if (pHDC)        delete pHDC;
  if (pVDC)        delete pVDC;

  if (pLumiDetector)    delete pLumiDetector;
  if (pCerenkovDetector)    delete pCerenkovDetector;
  if (pTriggerScintillator) delete pTriggerScintillator;

  if (pTungstenPlug)        delete pTungstenPlug;
  if (pCollimator1)         delete pCollimator1;
  if (pCollimator2)         delete pCollimator2;
  if (pCollimator3)         delete pCollimator3;
  if (pCollimatorSupport)   delete pCollimatorSupport;


  if (pShieldingWall)       delete pShieldingWall;
  
  if (pPionWall)            delete pPionWall;

  if (pWShutters1)            delete pWShutters1;
  if (pWShutters2)            delete pWShutters2;

  if (pLeadGlass)            delete pLeadGlass;
  
  if (pPMTOnly)		    delete pPMTOnly;

  if (pTarget)              delete pTarget;
  if (pBeamLine)            delete pBeamLine;
  if (pMainMagnet)          delete pMainMagnet;

  if (detectorMessenger)    delete detectorMessenger;
  if (pMaterial)            delete pMaterial;
  if (pGeometry)            delete pGeometry;

}


G4VPhysicalVolume* QweakSimDetectorConstruction::Construct()
{
  return ConstructQweak();
}

G4VPhysicalVolume* QweakSimDetectorConstruction::ConstructQweak()
{
  pTarget              = new QweakSimTarget(myUserInfo);
  pBeamLine            = new QweakSimBeamLine(myUserInfo);
  
  pTungstenPlug        = new QweakSimTungstenPlug();
  pCollimator1         = new QweakSimCollimator();
  pCollimator2         = new QweakSimCollimator();
  pCollimator3         = new QweakSimCollimator();
  pCollimatorSupport   = new QweakSimCollimatorSupport(pCollimator1,pCollimator3);

  pShieldingWall       = new QweakSimShieldingWall();
  
  pPionWall            = new QweakSimPionWall();

  pWShutters1		   = new QweakSimWShutters(1);
  pWShutters2		   = new QweakSimWShutters(2);
	
  pLeadGlass           = new QweakSimLeadGlass();
  
  pPMTOnly 	       = new QweakSimPMTOnly(myUserInfo);

  pMainMagnet          = new QweakSimMainMagnet(); // QTOR Geometry (decoupled from field)

  //pGEM                 = new QweakSimGEM();
  pHDC                 = new QweakSimHDC();
  pVDC                 = new QweakSimVDC();
  pVDCRotator          = new QweakSimVDCRotator();

  pCerenkovDetector    = new QweakSimCerenkovDetector(myUserInfo);
  pLumiDetector        = new QweakSimLumiDetector();

  pTriggerScintillator = new QweakSimTriggerScintillator();


  //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------

//  fWorldLengthInX =  10.0*m;
//  fWorldLengthInY =  10.0*m;
//  fWorldLengthInZ =  20.0*m;

//Val's Changes so correct shielding hut lengths fit in the world 2013-05-03
  fWorldLengthInX =  20.0*m; //Val's Changes so correct shielding hut lengths fit in the world
  fWorldLengthInY =  20.0*m; //Val's Changes so correct shielding hut lengths fit in the world
  fWorldLengthInZ =  40.0*m; //Val's Changes so correct shielding hut lengths fit in the world


  // experimentalHall_Material   = pMaterial->GetMaterial("HeGas");
  // Note: experimentalHall_Material was HeGas all the time up to 12-28-2005 !!!

  experimentalHall_Material   = pMaterial->GetMaterial("Air");

  experimentalHall_Solid = new G4Box("ExpHall_Sol",
				     0.5* fWorldLengthInX ,
				     0.5* fWorldLengthInY ,
				     0.5* fWorldLengthInZ );

  experimentalHall_Logical = new G4LogicalVolume( experimentalHall_Solid,
						  experimentalHall_Material,
						  "ExpHall_Logical",
						  0, 0, 0);

  //  Must place the World Physical volume unrotated at (0,0,0).
  //
  experimentalHall_Physical = new G4PVPlacement(0,               // no rotation
						G4ThreeVector(), // at (0,0,0)
						experimentalHall_Logical,      // its logical volume
						"ExpHall_Physical",         // its name
						0,               // its mother  volume
						false,           // no boolean operations
						0,               // no field specific to volume
						pSurfChk);       // check for overlaps

  // Get the geometry, which defines the world volume
  //
  pGeometry = new QweakSimGeometry();
  pGeometry->SetWorldVolume(experimentalHall_Physical);

  //==========================
  // Defining the Hall Floor
  //==========================

//  fFloorLengthInX =  12.0*m;
//  fFloorLengthInY =   1.0*m;
//  fFloorLengthInZ =  28.0*m;

//Val's Changes so correct shielding hut lengths will be on the floor 2013-05-03
  fFloorLengthInX =  16.0*m;
  fFloorLengthInY =   1.0*m;
  fFloorLengthInZ =  32.0*m;

  fFloorPositionInY =  -396.25*cm; // Top positon, not the center pos


  HallFloor_Material   = pMaterial->GetMaterial("ShieldingConcrete");

  HallFloor_Solid = new G4Box("HallFloor_Sol",
			      0.5* fFloorLengthInX ,
			      0.5* fFloorLengthInY ,
			      0.5* fFloorLengthInZ );

  HallFloor_Logical = new G4LogicalVolume( HallFloor_Solid,
					   HallFloor_Material,
					   "HallFloor_Logical",
					   0, 0, 0);

  //  Must place the World Physical volume unrotated at (0,0,0).
  //
  HallFloor_Physical = new G4PVPlacement(0,               // no rotation
					 G4ThreeVector(0.,fFloorPositionInY -0.5* fFloorLengthInY,0.),
					 "HallFloor_Physical",          // its name
					 HallFloor_Logical,             // its logical volume
					 experimentalHall_Physical ,    // its physical mother volume
					 false,                         // no boolean operations
					 0,                             // no field specific to volume
					 pSurfChk);                     // check for overlaps


  G4cout << G4endl << "###### QweakSimDetectorConstruction: Setting Attributes " << G4endl << G4endl;

  G4Colour  grey      ( 127/255., 127/255., 127/255.);

  HallFloor_VisAtt->SetColor(grey);
  HallFloor_VisAtt->SetVisibility(true);
  //HallFloor_VisAtt->SetVisibility(false);
  //HallFloor_VisAtt->SetForceWireframe(true);
  //HallFloor_VisAtt->SetForceSolid(true);
  HallFloor_Logical->SetVisAttributes(HallFloor_VisAtt);

  //============================================
  // create/place target body into MotherVolume
  //============================================
  //
  if (pTarget) {
    pTarget -> ConstructComponent(experimentalHall_Physical);
    //    pTarget -> SetTargetCenterPositionInZ(-650.0*cm);
    pTarget -> SetTargetCenterPositionInZ(myUserInfo->TargetCenterPositionZ);
    //
    pGeometry->AddModule(pTarget->getTargetPhysicalVolume());
  }

  //============================================
  // create/place beamline body into MotherVolume
  //============================================
  //
  if (pBeamLine) {
    pBeamLine -> ConstructComponent(experimentalHall_Physical);
    //pBeamLine -> SetBeamLineCenterPositionInZ(300.0*cm);
    //pGeometry->AddModule(pBeamLine->getBeamLinePhysicalVolume());
  }
  
  //================================================
  // create/place MainMagnet body into MotherVolume
  //================================================
  //
  if(pMainMagnet) {
    pMainMagnet -> ConstructComponent(experimentalHall_Physical);
    pMainMagnet -> SetCenterPositionInZ(0.0*cm);
    pMainMagnet -> Construct_UpstreamSpider(experimentalHall_Physical);
    pMainMagnet -> Construct_ClampPlates(experimentalHall_Physical);
    pMainMagnet -> Construct_UpStreamMiniClampPlates(experimentalHall_Physical);
    pMainMagnet -> Construct_CoilFrames(experimentalHall_Physical);
    pMainMagnet -> Construct_RadialMountingBlocks(experimentalHall_Physical);
    pMainMagnet -> Construct_SupportFrame(experimentalHall_Physical);
    pMainMagnet -> Construct_DownstreamSpider(experimentalHall_Physical);
    //
    pGeometry->AddModule(pMainMagnet->getMainMagnetPhysicalVolume());
  }

   //================================================
   // create/place Tungsten plug body into MotherVolume
   //================================================
   //
  if (pTungstenPlug) {
    pTungstenPlug->ConstructTungstenPlug(experimentalHall_Physical);
    //
    pGeometry->AddModule(pTungstenPlug->getTungstenPlugUSPhysicalVolume());
    pGeometry->AddModule(pTungstenPlug->getTungstenPlugDSPhysicalVolume());
  }

  //jpan@nuclear.uwinnipeg.ca: Fri Jun  5 12:24:18 CDT 2009
  //update collimators' geometry parameters according to the drawings from //http://qweak.jlab.org/doc-private/ShowDocument?docid=745

  // Collimator 1 configuration
  if (pCollimator1) {

    // TODO: the little high-theta corners of collimator 1 are not implemented
    // TODO: the slanted region of collimator 1 is implemented with a single slope, not a double slope (see drawings)
    pCollimator1->SetCollimatorNumber(1);
    pCollimator1->SetCollimatorHousing_FullLengthInX(86.36*cm);
    pCollimator1->SetCollimatorHousing_FullLengthInY(86.36*cm);
    pCollimator1->SetCollimatorHousing_FullLengthInZ(15.24*cm);

    pCollimator1->SetOctantCutOutFrontFullLength_Y(5.04*cm);
    pCollimator1->SetOctantCutOutFrontFullLength_X1(2.0*3.19*cm);
    pCollimator1->SetOctantCutOutFrontFullLength_X2(2.0*3.19*cm);
    pCollimator1->SetOctantCutOutBackFullLength_Y(5.83*cm);
    pCollimator1->SetOctantCutOutBackFullLength_X1(2.0*3.65*cm);
    pCollimator1->SetOctantCutOutBackFullLength_X2(2.0*3.65*cm);

    pCollimator1->SetBeamlineCutoutDiameter(8.3*cm);

    pCollimator1->SetOctantCutOutFrontInnerDiameter(2.0*5.21*cm);
    pCollimator1->SetOctantCutOutFrontOuterDiameter(2.0*10.69*cm);
    pCollimator1->SetOctantCutOutBackInnerDiameter(2.0*7.03*cm);
    pCollimator1->SetOctantCutOutBackOuterDiameter(2.0*12.63*cm);
    pCollimator1->SetOctantCutOutStartingPhiAngle((-16.61+90.0)*degree);
    pCollimator1->SetOctantCutOutDeltaPhiAngle(2.0*16.61*degree);
    pCollimator1->SetOctantCutOutRadialOffset(0.0*cm);

    pCollimator1->ConstructCollimator(experimentalHall_Physical);

    pCollimator1->SetCollimatorHousing_CenterPositionInZ(-575.7895*cm);
    pCollimator1->SetCollimatorHousingMaterial("PBA"); //housing material - Lead with 5% Antimony
    //
    pGeometry->AddModule(pCollimator1->getCollimatorHousingPhysicalVolume());
  }

  // Collimator 2 configuration
  if (pCollimator2) {
    pCollimator2->SetCollimatorNumber(2);
    pCollimator2->SetCollimatorHousing_FullLengthInX(142.2*cm);
    pCollimator2->SetCollimatorHousing_FullLengthInY(142.2*cm);
    pCollimator2->SetCollimatorHousing_FullLengthInZ(15.00*cm);

    pCollimator2->SetOctantCutOutFrontFullLength_Y(15.40*cm);
    pCollimator2->SetOctantCutOutFrontFullLength_X1(18.37*cm);
    pCollimator2->SetOctantCutOutFrontFullLength_X2(18.37*cm);//(upper edge)
    pCollimator2->SetOctantCutOutBackFullLength_Y(16.60*cm);
    pCollimator2->SetOctantCutOutBackFullLength_X1(18.37*cm);
    pCollimator2->SetOctantCutOutBackFullLength_X2(18.37*cm);

    pCollimator2->SetBeamlineCutoutDiameter(27.0*cm);

    //   pCollimator2->SetOctantCutOutFrontInnerDiameter(57.12*cm);
    //   pCollimator2->SetOctantCutOutFrontOuterDiameter(71.62*cm);
    //   pCollimator2->SetOctantCutOutBackInnerDiameter(61.14*cm);
    //   pCollimator2->SetOctantCutOutBackOuterDiameter(74.14*cm);
    //   pCollimator2->SetOctantCutOutStartingPhiAngle((-14.38+90.0)*degree); // between 12.21 deg to 14.38 deg
    //   pCollimator2->SetOctantCutOutDeltaPhiAngle(2.0*14.38*degree);  // take the average of 13.3 deg ? - Peiqing
    //   pCollimator2->SetOctantCutOutRadialOffset(0.0*cm);

    // redefine it here. -Peiqing, 2011 Nov 11
    pCollimator2->SetOctantCutOutFrontInnerDiameter(2.0*14.935*cm);
    pCollimator2->SetOctantCutOutFrontOuterDiameter(2.0*(14.935+7.25)*cm);
    pCollimator2->SetOctantCutOutBackInnerDiameter(33.89*cm);
    pCollimator2->SetOctantCutOutBackOuterDiameter(46.89*cm);
    pCollimator2->SetOctantCutOutStartingPhiAngle((-22.479+90.0)*degree);
    pCollimator2->SetOctantCutOutDeltaPhiAngle(2.0*22.479*degree);
    pCollimator2->SetOctantCutOutRadialOffset(13.625*cm);

    pCollimator2->ConstructCollimator(experimentalHall_Physical);

    pCollimator2->SetCollimatorHousing_CenterPositionInZ(-378.2195*cm);
    pCollimator2->SetCollimatorHousingMaterial("PBA");
    //
    pGeometry->AddModule(pCollimator2->getCollimatorHousingPhysicalVolume());
  }

  // Collimator 3 configuration
  if (pCollimator3) {
    pCollimator3->SetCollimatorNumber(3);
    pCollimator3->SetCollimatorHousing_FullLengthInX(240.0*cm);//should be updated to 238.76*cm
    pCollimator3->SetCollimatorHousing_FullLengthInY(240.0*cm);
    pCollimator3->SetCollimatorHousing_FullLengthInZ(11.23*cm);

    pCollimator3->SetOctantCutOutFrontFullLength_Y(24.00*cm);
    pCollimator3->SetOctantCutOutFrontFullLength_X1(29.00*cm);
    pCollimator3->SetOctantCutOutFrontFullLength_X2(29.00*cm);
    pCollimator3->SetOctantCutOutBackFullLength_Y(26.495*cm);
    pCollimator3->SetOctantCutOutBackFullLength_X1(29.00*cm);
    pCollimator3->SetOctantCutOutBackFullLength_X2(29.00*cm);

    pCollimator3->SetBeamlineCutoutDiameter(32.54*cm);

    //   pCollimator3->SetOctantCutOutFrontInnerDiameter(2.0*39.0*cm);
    //   pCollimator3->SetOctantCutOutFrontOuterDiameter(2.0*51.0*cm);
    //   pCollimator3->SetOctantCutOutBackInnerDiameter(2.0*39.954*cm);
    //   pCollimator3->SetOctantCutOutBackOuterDiameter(2.0*51.0*cm);
    //   pCollimator3->SetOctantCutOutStartingPhiAngle((-16.390+90.0)*degree);
    //   pCollimator3->SetOctantCutOutDeltaPhiAngle(2.0*16.390*degree);
    //   pCollimator3->SetOctantCutOutRadialOffset(0.0*cm);

    // redefine it here -Peiqing 2011 Nov 11
    pCollimator3->SetOctantCutOutFrontInnerDiameter(2.0*(39.0-16.2)*cm);
    pCollimator3->SetOctantCutOutFrontOuterDiameter(2.0*(51.0-16.2)*cm);
    pCollimator3->SetOctantCutOutBackInnerDiameter(2.0*(39.954-16.2)*cm);
    pCollimator3->SetOctantCutOutBackOuterDiameter(2.0*(51.0-16.2)*cm);
    pCollimator3->SetOctantCutOutStartingPhiAngle((-22.6+90.0)*degree);
    pCollimator3->SetOctantCutOutDeltaPhiAngle(2.0*22.6*degree);
    pCollimator3->SetOctantCutOutRadialOffset(16.2*cm);

    pCollimator3->ConstructCollimator(experimentalHall_Physical);

    pCollimator3->SetCollimatorHousing_CenterPositionInZ(-266.244*cm);
    pCollimator3->SetCollimatorHousingMaterial("PBA");
    //
    pGeometry->AddModule(pCollimator3->getCollimatorHousingPhysicalVolume());
  }

  //================================================
  // create/place Collimator Support body into MotherVolume
  //================================================
  //
  if (pCollimatorSupport) {
    pCollimatorSupport -> ConstructSupport(experimentalHall_Physical);
  }

  //===================================================
  // create/place ShieldingWall body into MotherVolume
  //===================================================
  //
  if (pShieldingWall) {
    pShieldingWall->SetCollimatorWall_FullLengthInX(670.56*cm);
    pShieldingWall->SetCollimatorWall_FullLengthInY(670.56*cm);
    pShieldingWall->SetCollimatorWall_FullLengthInZ( 80.0*cm);

    // Peiqing: updated it according to as-designed geometry. 2011 Nov 12
    pShieldingWall->SetOctantCutOut_Trap_RadialDistance  (246.425*cm);
    pShieldingWall->SetOctantCutOut_Trap_PolarAngle      (-21.40*degree);
    pShieldingWall->SetOctantCutOut_Trap_AzimuthalAngle  (90.0*degree);

    pShieldingWall->SetOctantCutOut_Trap_FullHeightFront       (65.8*cm);
    pShieldingWall->SetOctantCutOut_Trap_FullLengthFront_Outer (79.95*2.0*cm);
    pShieldingWall->SetOctantCutOut_Trap_FullLengthFront_Inner (67.95*2.0*cm);

    pShieldingWall->SetOctantCutOut_Trap_FullHeightBack        (59.3*cm);
    pShieldingWall->SetOctantCutOut_Trap_FullLengthBack_Outer  (90.45*2.0*cm);
    pShieldingWall->SetOctantCutOut_Trap_FullLengthBack_Inner  (79.635*2.0*cm);

    pShieldingWall->ConstructShieldingWallHousing_UsingTrapezoids(experimentalHall_Physical);
    pShieldingWall->SetCollimatorWall_CenterPositionInZ(340.0*cm);

    pShieldingWall->SetCollimatorWallMaterial("ShieldingConcrete");

    pShieldingWall->ConstructFrontWall(experimentalHall_Physical);
    pShieldingWall->ConstructBackWall(experimentalHall_Physical);
    pShieldingWall->ConstructBeamLeftSideWall(experimentalHall_Physical);
    pShieldingWall->ConstructBeamRightSideWall(experimentalHall_Physical);
    pShieldingWall->ConstructTopWall(experimentalHall_Physical);
    pShieldingWall->ConstructFrontWall(experimentalHall_Physical);
    //
    pGeometry->AddModule(pShieldingWall->getShieldingWallHousingPhysicalVolume());
  }

  //===================================================
  // create/place Pion Wall body into MotherVolume
  //===================================================
  //
  if (pPionWall) {
    pPionWall->ConstructPionWall(experimentalHall_Physical);
  }

  //===================================================
  // create/place WShutters body into MotherVolume
  //===================================================
  //
    if (pWShutters1) {
    	pWShutters1->SetWShuttersNumber(1);
    	pWShutters1->ConstructWShutters(experimentalHall_Physical);
    	//pWShutters1->SetWShuttersNumber(1);
    	pWShutters1->SetWShutters_CenterPositionInX ((6.657*inch));
    	pWShutters1->SetWShutters_CenterPositionInY (0.0*inch);
    	pWShutters1->SetWShutters_CenterPositionInZ (-221.939*inch);
    	pWShutters1->SetWShutters_Material ("TungstenAlloy");
	pWShutters1->SetDisabled();
    }
    if (pWShutters2) {
    	pWShutters2->SetWShuttersNumber(2);
    	pWShutters2->ConstructWShutters(experimentalHall_Physical);
    	//pWShutters2->SetWShuttersNumber(2);
    	pWShutters2->SetWShutters_CenterPositionInX (-6.657*inch);
     	pWShutters2->SetWShutters_CenterPositionInY (0.0*inch);
     	pWShutters2->SetWShutters_CenterPositionInZ (-221.939*inch);
       	pWShutters2->SetWShutters_Material ("TungstenAlloy");
	pWShutters2->SetDisabled();
    	}
  //===================================================
  // create/place LeadGlass into MotherVolume
  //===================================================
  //
  if (pLeadGlass){
    pLeadGlass->ConstructComponent(experimentalHall_Physical);
    pGeometry->AddModule(pLeadGlass->GetLeadGlass_PhysicalVolume());
  }
  
  //===================================================
  // create/place PMTOnly into MotherVolume
  //===================================================
  //
  if (pPMTOnly){
    pPMTOnly->ConstructComponent(experimentalHall_Physical);
    pGeometry->AddModule(pPMTOnly->GetPMTOnly_PhysicalVolume());
  }
	
  //===============================================
  // create/place Drift Chambers into MotherVolume
  //===============================================
  //
  //if (pGEM) {
  //  pGEM->ConstructComponent(experimentalHall_Physical);
  //  pGeometry->AddModule(pGEM->getGEMFront_PhysicalVolume());
  //  pGeometry->AddModule(pGEM->getGEMBack_PhysicalVolume());
  //}
  //
  if (pHDC) {
    pHDC->ConstructComponent(experimentalHall_Physical);
    pGeometry->AddModule(pHDC->getHDCFront_PhysicalVolume());
    pGeometry->AddModule(pHDC->getHDCBack_PhysicalVolume());
  }
  //===============================================
  // create/place VDC Rotator into MotherVolume
  //===============================================
  //
  if (pVDCRotator) {
    pVDCRotator->SetMotherVolume(experimentalHall_Physical);
    pVDCRotator->ConstructRotatorMasterContainer();
    pVDCRotator->ConstructRings();
    pVDCRotator->ConstructRails();
    pVDCRotator->ConstructMount();
    pVDCRotator->ConstructSliderSupport();
    pVDCRotator->SetRotationAngleInPhi( 90.0*degree);
  }


  //=====================================================
  // create/place Trigger Scintillator into MotherVolume
  //=====================================================
  //
  if (pTriggerScintillator) {
    pTriggerScintillator->ConstructComponent(experimentalHall_Physical);
    //
    pGeometry->AddModule(pTriggerScintillator->GetTriggerScintillator_PhysicalVolume());
  }

  //
  if (pVDC) {
    pVDC->ConstructComponent(experimentalHall_Physical);
    pGeometry->AddModule(pVDC->getVDCFront_PhysicalVolume());
    pGeometry->AddModule(pVDC->getVDCBack_PhysicalVolume());
    pVDC->SetVDCRotator(pVDCRotator);
    pVDC->SetTriggerScintillator(pTriggerScintillator);
    pVDC->SetVDC_RotationAngleInPhi(90.0*degree,0);
    pVDC->SetVDC_RotationAngleInPhi(270.0*degree,1);
  }


  //=========================================
  // create/place Cerenkov into MotherVolume
  //=========================================
  //
  if (pCerenkovDetector) {
    pCerenkovDetector->ConstructComponent(experimentalHall_Physical);
    //
    pGeometry->AddModule(pCerenkovDetector->GetCerenkovDetector_PhysicalVolume());
  }

  //=========================================
  // create/place Lumis into MotherVolume
  //=========================================
  //
  if (pLumiDetector) {
    pLumiDetector->ConstructComponent(experimentalHall_Physical);
    
    pGeometry->AddModule(pLumiDetector->getUSLumiPhysicalVolume());
    //pGeometry->AddModule(pLumiDetector->getDSLumiPhysicalVolume());
  }

  //--------- Visualization attributes -------------------------------

  // Invisible Volume
  experimentalHall_Logical->SetVisAttributes (G4VisAttributes::Invisible);

  //--------- Load magnetic field  -------------------------------

  SetGlobalMagneticField();


  G4cout << G4endl << "###### Leaving QweakSimDetectorConstruction::Construct() " << G4endl << G4endl;

  // Construct() *MUST* return the pointer of the physical World !!!
  return experimentalHall_Physical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimDetectorConstruction::DumpGeometry(G4bool surfchk, G4VPhysicalVolume* aVolume,G4int depth)
{
  // Null volume
  if (aVolume == 0) aVolume = experimentalHall_Physical;

  // Print spaces
  for(int isp=0;isp<depth;isp++)
  { G4cout << "  "; }
  // Print name
  G4cout << aVolume->GetName() << "[" << aVolume->GetCopyNo() << "] "
         << aVolume->GetLogicalVolume()->GetName() << " "
         << aVolume->GetLogicalVolume()->GetNoDaughters() << " "
         << aVolume->GetLogicalVolume()->GetMaterial()->GetName();
  // Print sensitive detector
  if(aVolume->GetLogicalVolume()->GetSensitiveDetector())
  {
    G4cout << " " << aVolume->GetLogicalVolume()->GetSensitiveDetector()
                            ->GetFullPathName();
  }
  G4cout << G4endl;

  // Check overlapping volumes
  if (pSurfChk || surfchk) aVolume->CheckOverlaps();

  // Descend down the tree
  for(int i=0;i<aVolume->GetLogicalVolume()->GetNoDaughters();i++)
  { DumpGeometry(surfchk, aVolume->GetLogicalVolume()->GetDaughter(i),depth+1); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimDetectorConstruction::UpdateGeometry()
{
  G4cout << G4endl << "###### Calling QweakDetectorConstruction::UpdateGeometry() " << G4endl << G4endl;

  // taken from LXe example
  G4GeometryManager::GetInstance()->OpenGeometry();

  // clean up previous geometry
  G4PhysicalVolumeStore  ::GetInstance()->Clean();
  G4LogicalVolumeStore   ::GetInstance()->Clean();
  G4SolidStore           ::GetInstance()->Clean();
  G4LogicalBorderSurface ::CleanSurfaceTable();


  // define new geometry
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructQweak());
  G4RunManager::GetRunManager()->GeometryHasBeenModified();


  G4cout << G4endl << "###### Leaving QweakDetectorConstruction::UpdateGeometry() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimDetectorConstruction::SetGlobalMagneticField()
{

  //--------- Magnetic Field -------------------------------

  //============================================
  //  Define the global magnet field Manager
  //============================================
  pMagneticField = new QweakSimMagneticField();

  // Get transportation, field, and propagator  managers
  fGlobalFieldManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();

  // perform navigation/propagation in a general non-uni-form magnetic field
  //G4PropagatorInField* pGlobalFieldPropagator = G4TransportationManager::GetTransportationManager()->GetPropagatorInField();

  // G4double minEps =  1.0e-5;
  // G4double maxEps =  1.0e-4;

  //pGlobalFieldPropagator->SetMinimumEpsilonStep(minEps);
  //pGlobalFieldPropagator->SetMaximumEpsilonStep(maxEps);


  fGlobalFieldManager->SetDetectorField(pMagneticField);

#define TRACK_ELECTRON_SPIN
#ifdef  TRACK_ELECTRON_SPIN
  fGlobalEquation = new G4Mag_SpinEqRhs(pMagneticField);
  G4int numberOfVariables = 12;
#else
  fGlobalEquation = new G4Mag_UsualEqRhs(pMagneticField);
  G4int numberOfVariables = 6;
#endif

  // taken from one of the Geant4 presentation:
  // - If the field is calculated from a field map, a lower order stepper
  //   is recommended: the less smooth the field is, the lower the order of the
  //   stepper that should be used. For very rough fields one should use 1st order
  //   stepper, for a somewhat smooth field one must choose between 1st and 2nd
  //   order stepper.

  //fGlobalStepper  = new G4ClassicalRK4(fGlobalEquation, numberOfVariables);  // classical 4th order stepper
  //fGlobalStepper  = new G4ExplicitEuler(fGlobalEquation, numberOfVariables); //           1st order stepper
  //fGlobalStepper  = new G4ImplicitEuler(fGlobalEquation, numberOfVariables); //           2nd order stepper
  fGlobalStepper  = new G4SimpleRunge(fGlobalEquation, numberOfVariables);   //           2nd order stepper


  // Provides a driver that talks to the Integrator Stepper, and insures that
  //   the error is within acceptable bounds.
  G4MagInt_Driver* fGlobalIntgrDriver = new G4MagInt_Driver(0.1*mm,  //1.0e-3*mm,
							    fGlobalStepper,
							    fGlobalStepper->GetNumberOfVariables());

  fGlobalChordFinder = new G4ChordFinder(fGlobalIntgrDriver);



  //       G4bool fieldChangesEnergy = false;
  //       G4FieldManager* pFieldMgr = new G4FieldManager(myField,pChordFinder,FieldChangeEnergy);
  //       LocalLogicalVolume = new G4LogicalVolume(shape, material,"name",pFieldMgr,0,0);

  //   // minimal step of 1 mm is default
  //   fMinStep = 0.01*mm ;
  //
  //   fGlobalChordFinder = new G4ChordFinder (pGlobalMagnetField,
  //                                           fMinStep,
  //                                           fGlobalStepper);

  fGlobalFieldManager->SetChordFinder(fGlobalChordFinder);

//=====================================================================================
// you can use this in DetectorConstruction class to make more smooth visulisation:

  G4TransportationManager* tmanager = G4TransportationManager::GetTransportationManager();
  tmanager->GetPropagatorInField()->SetLargestAcceptableStep(1*mm);
//=====================================================================================
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimDetectorConstruction::ShowHallFloor()
{
  G4cout << "###### Calling QweakSimDetectorConstruction::ShowHallFloor() " << G4endl << G4endl;

  HallFloor_VisAtt->SetVisibility(true);

  G4cout << "###### Leaving QweakSimDetectorConstruction::ShowHallFloor() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimDetectorConstruction::HideHallFloor()
{
  G4cout << "###### Calling QweakSimDetectorConstruction::HideHallFloor() " << G4endl << G4endl;

  HallFloor_VisAtt->SetVisibility(false);

  G4cout << "###### Leaving QweakSimDetectorConstruction::HideHallFloor() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
