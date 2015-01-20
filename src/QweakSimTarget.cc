//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimTarget.cc

   $Revision: 1.2 $
   $Date: 2005/12/27 19:15:13 $

   \author Klaus Hans Grimm

*/
//=============================================================================

// Oct. 2011. Added in details of target geometry. -peiqing

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTarget.hh"

// user classes
class QweakSimMaterial;
class QweakSimTargetMessenger;

// geant4 includes
#include "G4UserLimits.hh"

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimTargetMessenger.hh"
#include "QweakSimTarget_DetectorSD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTarget::QweakSimTarget(QweakSimUserInformation *myUI)
{
    G4cout << G4endl << "###### Calling QweakSimTarget::QweakTarget() " << G4endl << G4endl;

    myUserInfo = myUI;

    theMotherPV               = NULL;

    TargetContainer_Logical      = NULL;
    TargetContainer_Physical     = NULL;
    TargetContainer_Material     = NULL;

    TargetCell_Logical      = NULL;
    TargetCell_Physical     = NULL;
    TargetCell_Material     = NULL;

    TargetEntranceWindow_Logical      = NULL;
    TargetEntranceWindow_Physical     = NULL;
    TargetEntranceWindow_Material     = NULL;

    TargetExitWindow_Logical      = NULL;
    TargetExitWindow_Physical     = NULL;
    TargetExitWindow_Material     = NULL;

    TargetExitWindowNipple_Logical  = NULL;
    TargetExitWindowNipple_Physical = NULL;
    TargetExitWindowNipple_Material = NULL;

    ScatteringChamberWindow_Logical  = NULL;
    ScatteringChamberWindow_Physical = NULL;
    ScatteringChamberWindow_Material = NULL;

    TargetMaterial_Logical  = NULL;
    TargetMaterial_Physical = NULL;
    TargetMaterial_Material = NULL;


    // definition of a mil = inch/1000
    static const G4double mil = 0.001*2.54*cm;
    static const G4double inch = 2.54*cm;

    pMaterial = new QweakSimMaterial();
    pMaterial->DefineMaterials();

    TargetContainer_Material      = pMaterial->GetMaterial("Vacuum");
    TargetCell_Material           = pMaterial->GetMaterial("Aluminum");
    TargetEntranceWindow_Material = pMaterial->GetMaterial("Aluminum");
    TargetExitWindow_Material     = pMaterial->GetMaterial("Aluminum");
    TargetExitWindowNipple_Material = pMaterial->GetMaterial("Aluminum");
    ScatteringChamberWindow_Material = pMaterial->GetMaterial("Aluminum");
    TargetMaterial_Material       = pMaterial->GetMaterial("H2Liquid");

    // define target geometry values

    targetCellEntranceWindowThickness = 4.105*mil; //Avg of Run 1 & 2 (Greg's Target Elog 19)
    targetCellExitWindowThickness =  29.06*mil; //Greg's Target Elog 19 
    targetCellExitWindowNippleThickness =  5.165*mil; //Avg of Run 1 & 2 (Greg's Target Elog 19)
    targetCellWallThickness   = 10.0*mil;

    targetCellExitWindowNippleRadius = 0.5*0.622*inch;

    targetCellInnerLength     = myUserInfo->TargetLength;
    targetCellOuterLength     = targetCellInnerLength
                                + targetCellEntranceWindowThickness
                                + targetCellExitWindowThickness;  // Full length of Target

    targetCellFrontRadiusMin        =  0.0*cm;
    targetCellFrontOuterRadiusMax   =  0.5*2.730*inch;
    targetCellFrontInnerRadiusMax   = targetCellFrontOuterRadiusMax - targetCellWallThickness;

    targetCellBackRadiusMin        =  targetCellExitWindowNippleRadius;  //0.0*cm;
    targetCellBackOuterRadiusMax   =  0.5*7.5*inch;
    targetCellBackInnerRadiusMax   = targetCellBackOuterRadiusMax - targetCellWallThickness;

    targetCellStartingPhi =  0.0*deg;
    targetCellDeltaPhi    = 360*deg;

    targetZPos        = myUserInfo->TargetCenterPositionZ; //-650.0*cm;

    ScatteringChamberWindowRadius = 0.5*23.5*inch;
    ScatteringChamberWindowThickness = 35*mil;

    myUserInfo->TargetEntranceWindowThickness = targetCellEntranceWindowThickness;
    myUserInfo->TargetExitWindowThickness = targetCellExitWindowThickness;
    myUserInfo->TargetExitWindowNippleThickness = targetCellExitWindowNippleThickness;

    //Thicknesses taken from 2012 target survey (https://qweak.jlab.org/elog/Target/21)
    myUserInfo->TargetThicknessUSALDummy1    = 0.8812*mm;
    myUserInfo->TargetThicknessUSALDummy2    = 1.7987*mm;
    myUserInfo->TargetThicknessUSALDummy4    = 3.6030*mm;
    myUserInfo->TargetThicknessDSALDummy2    = 1.8637*mm;
    myUserInfo->TargetThicknessDSALDummy4    = 3.6828*mm;
    myUserInfo->TargetThicknessDSALDummy8    = 7.1980*mm;
    myUserInfo->TargetThicknessUSCDummy      = 0.9973*mm;
    myUserInfo->TargetThicknessDSCDummy      = 3.1876*mm;

    G4double densityLH2 = 0.0713 /(cm*cm*cm);  // [g/cm^3] 
    G4double densityAL  = 2.804   /(cm*cm*cm);  // Avg density, Greg's Target Elog 21
    G4double densityUSC = 1.70   /(cm*cm*cm);  //
    G4double densityDSC = 2.205  /(cm*cm*cm); //

    // Molar masses taken from PDG:  
    // J. Beringer et al. (Particle Data Group), Phys. Rev. D86, 010001 (2012).
    G4double massLH2 = 1.00794;    // [g/mol]
    G4double massAL  = 26.9815386; // [g/mol]
    G4double massC   = 12.0107;    // [g/mol]

    myUserInfo->TargetLuminosityLH2 = CalculateLuminosity(massLH2, densityLH2, myUserInfo->TargetLength);
    myUserInfo->TargetLuminosityUSALWindow = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetEntranceWindowThickness);
    myUserInfo->TargetLuminosityDSALWindow = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetExitWindowNippleThickness);
    myUserInfo->TargetLuminosityUSALDummy1 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessUSALDummy1);
    myUserInfo->TargetLuminosityUSALDummy2 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessUSALDummy2);
    myUserInfo->TargetLuminosityUSALDummy4 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessUSALDummy4);
    myUserInfo->TargetLuminosityDSALDummy2 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessDSALDummy2);
    myUserInfo->TargetLuminosityDSALDummy4 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessDSALDummy4);
    myUserInfo->TargetLuminosityDSALDummy8 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessDSALDummy8);
    myUserInfo->TargetLuminosityUSCDummy = CalculateLuminosity(massC, densityUSC, myUserInfo->TargetThicknessUSCDummy);
    myUserInfo->TargetLuminosityDSCDummy = CalculateLuminosity(massC, densityDSC, myUserInfo->TargetThicknessDSCDummy);

    TargetSD = NULL;

    targetMessenger = new QweakSimTargetMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTarget::~QweakSimTarget()
{
    delete pMaterial;
    delete targetMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
    G4cout << G4endl << "###### Calling QweakSimTarget::ConstructComponent() " << G4endl << G4endl;

    theMotherPV = MotherVolume;

    CalculateTargetPositions();

    ConstructTargetContainer(); // scattering chamber
    ConstructScatteringChamberWindow();

    ConstructTargetCell();      // Al cell without end caps
    ConstructTargetMaterial();  // LH2 for production target

    ConstructTargetEntranceWindow();
    ConstructTargetExitWindow();
    ConstructTargetExitWindowNipple();

//--------------------------------------

    G4cout << G4endl << "###### QweakSimTarget: Setting Attributes " << G4endl << G4endl;

    G4Colour  blue  (0.,0.,1.);
    G4Colour  red   (1.,0.,0.);

    G4VisAttributes* TargetContainer_VisAtt = new G4VisAttributes(red);
    TargetContainer_VisAtt -> SetVisibility(false);
    //TargetContainer_VisAtt -> SetForceWireframe(true);
    TargetContainer_Logical -> SetVisAttributes(TargetContainer_VisAtt);

    G4VisAttributes* TargetCell_VisAtt = new G4VisAttributes(blue);
    TargetCell_VisAtt -> SetVisibility(true);
    //TargetCell_VisAtt -> SetForceWireframe(true);
    TargetCell_Logical -> SetVisAttributes(TargetCell_VisAtt);

    G4VisAttributes* TargetWindow_VisAtt = new G4VisAttributes(blue);
    TargetWindow_VisAtt -> SetVisibility(true);
    //TargetWindow_VisAtt -> SetForceWireframe(true);
    TargetEntranceWindow_Logical -> SetVisAttributes(TargetWindow_VisAtt);
    TargetExitWindow_Logical -> SetVisAttributes(TargetWindow_VisAtt);

    G4VisAttributes* ScatteringChamberWindow_VisAtt = new G4VisAttributes(red);
    ScatteringChamberWindow_VisAtt -> SetVisibility(true);
    //ScatteringChamberWindow_VisAtt -> SetForceWireframe(true);
    ScatteringChamberWindow_Logical -> SetVisAttributes(ScatteringChamberWindow_VisAtt);

    G4VisAttributes* TargetMaterial_VisAtt = new G4VisAttributes(red);
    TargetMaterial_VisAtt -> SetVisibility(true);
    //TargetVisAtt -> SetForceWireframe(true);
    TargetMaterial_Logical -> SetVisAttributes(TargetMaterial_VisAtt);

    ///////////////////////////////////////////
    // Define Sensitive Detectors to Target  //
    ///////////////////////////////////////////

    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    TargetSD = new QweakSimTarget_DetectorSD("TargetSD");
    SDman->AddNewDetector(TargetSD);
    ScatteringChamberWindow_Logical->SetSensitiveDetector(TargetSD);


    G4cout << G4endl << "###### Leaving QweakSimTarget::ConstructComponent() " << G4endl << G4endl;

} // end of  QweakSimTarget::ConstructComponent()

void QweakSimTarget::CalculateTargetPositions(){

    // define Target position
    positionTarget = G4ThreeVector(0,0,0);
    positionTargetEntranceWindow = G4ThreeVector(0,0,-0.5*targetCellInnerLength - 0.5*targetCellEntranceWindowThickness);
    positionTargetExitWindow = G4ThreeVector(0,0, 0.5*targetCellInnerLength + 0.5*targetCellExitWindowThickness);
    positionScatteringChamberWindow = G4ThreeVector(0,0,0.5*targetCellInnerLength + 0.5*targetCellExitWindowThickness + 45.0*cm); // Peiqing: should be located at z=-583.41 cm

    targetCellOuterLength     = targetCellInnerLength
                                + targetCellEntranceWindowThickness
                                + targetCellExitWindowThickness;  // Full length of Target
}


void QweakSimTarget::ConstructTargetContainer()
{
    G4cout << G4endl << "###### Calling QweakSimTarget::ConstructTargetContainer() " << G4endl << G4endl;

    G4Tubs* TargetContainer_Solid    = new G4Tubs("TargetContainer_Sol",
            0, //targetCellRadiusMin, jpan@nuclear.uwinnipeg.ca
            ScatteringChamberWindowRadius+0.1*cm,
            0.5*targetCellOuterLength+50.0*cm,
            targetCellStartingPhi,
            targetCellDeltaPhi);

    TargetContainer_Logical  = new G4LogicalVolume(TargetContainer_Solid,
            TargetContainer_Material,
            "TargetContainer_Log",
            0,0,0);

    TargetContainer_Physical   = new G4PVPlacement(0,
            positionTarget,
            "TargetContainer",
            TargetContainer_Logical,
            theMotherPV,
            false,
            0,
            pSurfChk);
    G4cout << G4endl << "###### Leaving QweakSimTarget::ConstructTargetContainer() " << G4endl << G4endl;
    
}

void QweakSimTarget::ConstructTargetCell()
{
    G4cout << G4endl << "###### Calling QweakSimTarget::ConstructTargetCell() " << G4endl << G4endl;

    if (TargetContainer_Logical)
          TargetContainer_Logical->RemoveDaughter(TargetCell_Physical);

    delete TargetCell_Physical;
    TargetCell_Physical = NULL;

    // define target solid volume
    G4cout << G4endl << "###### QweakSimTarget: Define TargetCell_Solid " << G4endl << G4endl;
    G4Cons* TargetCell_Solid = new G4Cons("QweakTargetCell_Sol",
                                          targetCellFrontInnerRadiusMax+0.000001*cm,// G4double  pRmin1,
                                          targetCellFrontOuterRadiusMax, // G4double  pRmax1,
                                          targetCellBackInnerRadiusMax+0.000001*cm, //G4double  pRmin2,
                                          targetCellBackOuterRadiusMax, //G4double  pRmax2,
                                          0.5*targetCellOuterLength,    //G4double  pDz,
                                          targetCellStartingPhi, //G4double  pSPhi,
                                          targetCellDeltaPhi);   //G4double  pDPhi)

    // define Target logical volume
    G4cout << G4endl << "###### QweakSimTarget: Define TargetCell_Logical " << G4endl << G4endl;

    TargetCell_Logical  = new G4LogicalVolume(TargetCell_Solid,
            TargetCell_Material,
            "QweakTargetCell_Log",
            0,0,0);
    // define Target physical volume
    G4cout << G4endl << "###### QweakSimTarget: Define TargetCell_Physical " << G4endl << G4endl;
    TargetCell_Physical   = new G4PVPlacement(0,
            positionTarget,
            "QweakTargetCell",
            TargetCell_Logical,
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);
    G4cout << G4endl << "###### Leaving QweakSimTarget::ConstructTargetCell() " << G4endl << G4endl;
    
}

void QweakSimTarget::ConstructTargetEntranceWindow()
{
    G4cout << G4endl << "###### Calling QweakSimTarget::ConstructTargetEntranceWindow() " << G4endl << G4endl;

    if (TargetContainer_Logical)
          TargetContainer_Logical->RemoveDaughter(TargetEntranceWindow_Physical);

    delete TargetEntranceWindow_Physical;
    TargetEntranceWindow_Physical = NULL;

//--------------------------------------
    // define target window solid volume (front, upstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetEntranceWindow_Solid " << G4endl << G4endl;

    G4Tubs* TargetEntranceWindow_Solid    = new G4Tubs("TargetEntranceWindow_Sol",
            targetCellFrontRadiusMin,
            targetCellFrontInnerRadiusMax,
            0.5*targetCellEntranceWindowThickness,
            targetCellStartingPhi,
            targetCellDeltaPhi);

    // define Target window logical volume (front, upstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetEntranceWindow_Logical " << G4endl << G4endl;

    TargetEntranceWindow_Logical  = new G4LogicalVolume(TargetEntranceWindow_Solid,
            TargetEntranceWindow_Material,
            "QweakTargetEntranceWindow_Log",
            0,0,0);

    G4double MaxStepInEntranceWindow = 0.1*targetCellEntranceWindowThickness;
    TargetEntranceWindow_Logical->SetUserLimits(new G4UserLimits(MaxStepInEntranceWindow));

    // define Target window physical volume (front, upstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetEntranceWindow_Physical " << G4endl << G4endl;
    TargetEntranceWindow_Physical   = new G4PVPlacement(0,
            positionTargetEntranceWindow,
            "QweakTargetEntranceWindow",
            TargetEntranceWindow_Logical,
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);
    G4cout << G4endl << "###### Leaving QweakSimTarget::ConstructTargetEntranceWindow() " << G4endl << G4endl;

}

void QweakSimTarget::ConstructTargetExitWindow()
{
    G4cout << G4endl << "###### Calling QweakSimTarget::ConstructTargetExitWindow() " << G4endl << G4endl;

    if (TargetContainer_Logical)
          TargetContainer_Logical->RemoveDaughter(TargetExitWindow_Physical);

    delete TargetExitWindow_Physical;
    TargetExitWindow_Physical = NULL;

    // define target window solid volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindow_Solid " << G4endl << G4endl;

    G4Tubs* TargetExitWindow_Solid    = new G4Tubs("TargetExitWindow_Sol",
            targetCellBackRadiusMin,
            targetCellBackInnerRadiusMax,
            0.5*targetCellExitWindowThickness,
            targetCellStartingPhi,
            targetCellDeltaPhi);

    // define Target window logical volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindow_Logical " << G4endl << G4endl;

    TargetExitWindow_Logical  = new G4LogicalVolume(TargetExitWindow_Solid,
            TargetExitWindow_Material,
            "QweakTargetExitWindow_Log",
            0,0,0);

    // Set max step size for a certain volume, see
//         http://geant4.web.cern.ch/geant4/G4UsersDocuments/UsersGuides/
//         ForApplicationDeveloper/html/TrackingAndPhysics/thresholdVScut.html
    G4double MaxStepInExitWindow = 0.1*targetCellExitWindowThickness;
    TargetExitWindow_Logical->SetUserLimits(new G4UserLimits(MaxStepInExitWindow));


    // define Target window physical volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindow_Physical " << G4endl << G4endl;
    TargetExitWindow_Physical   = new G4PVPlacement(0,
            positionTargetExitWindow,
            "QweakTargetExitWindow",
            TargetExitWindow_Logical,
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);
    G4cout << G4endl << "###### Leaving QweakSimTarget::ConstructTargetExitWindow() " << G4endl << G4endl;
    
}

void QweakSimTarget::ConstructTargetExitWindowNipple()
{
    G4cout << G4endl << "###### Calling QweakSimTarget::ConstructTargetExitWindowNipple() " << G4endl << G4endl;

    if (TargetContainer_Logical)
          TargetContainer_Logical->RemoveDaughter(TargetExitWindowNipple_Physical);

    delete TargetExitWindowNipple_Physical;
    TargetExitWindowNipple_Physical = NULL;   

    // define target window Nipple solid volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindowNipple_Solid " << G4endl << G4endl;

    G4Tubs* TargetExitWindowNipple_Solid    = new G4Tubs("TargetExitWindowNipple_Sol",
            0.,
            targetCellExitWindowNippleRadius,
	//            targetCellExitWindowNippleRadius-0.00001*mm,
            0.5*targetCellExitWindowNippleThickness,
            targetCellStartingPhi,
            targetCellDeltaPhi);

    // define Target window logical volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindowNipple_Logical " << G4endl << G4endl;

    TargetExitWindowNipple_Logical  = new G4LogicalVolume(TargetExitWindowNipple_Solid,
            TargetExitWindowNipple_Material,
            "QweakTargetExitWindowNipple_Log",
            0,0,0);

    G4double MaxStepInExitWindowNipple = 0.1*targetCellExitWindowNippleThickness;
    TargetExitWindowNipple_Logical->SetUserLimits(new G4UserLimits(MaxStepInExitWindowNipple));

    // define Target window nipple physical volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindowNipple_Physical " << G4endl << G4endl;
    TargetExitWindowNipple_Physical   = new G4PVPlacement(0,
            positionTargetExitWindow,
            "QweakTargetExitWindowNipple_Physical",
            TargetExitWindowNipple_Logical,
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);
    G4cout << G4endl << "###### Leaving QweakSimTarget::ConstructTargetExitWindowNipple() " << G4endl << G4endl;

}

void QweakSimTarget::ConstructScatteringChamberWindow()
{
    G4cout << G4endl << "###### Calling QweakSimTarget::ConstructScatteringChamberWindow() " << G4endl << G4endl;

    //*********************** Define Target scattering chamber Vacuum Window ************************
    G4cout << G4endl << "###### QweakSimTarget: Define ScatteringChamberWindow_Solid " << G4endl << G4endl;
    G4Tubs* ScatteringChamberWindow_Solid    = new G4Tubs("ScatteringChamberWindow_Sol",
            0.,
            ScatteringChamberWindowRadius,
            0.5*ScatteringChamberWindowThickness,
            targetCellStartingPhi,
            targetCellDeltaPhi);

    // define ScatteringChamberWindow logical volume
    G4cout << G4endl << "###### QweakSimTarget: Define ScatteringChamberWindow_Logical " << G4endl << G4endl;

    ScatteringChamberWindow_Logical  = new G4LogicalVolume(ScatteringChamberWindow_Solid,
            ScatteringChamberWindow_Material,
            "ScatteringChamberWindow_Log",
            0,0,0);

    // define Target vacuum window physical volume
    G4cout << G4endl << "###### QweakSimTarget: Define ScatteringChamberWindow_Physical " << G4endl << G4endl;
    ScatteringChamberWindow_Physical   = new G4PVPlacement(0,
            positionScatteringChamberWindow,
            "ScatteringChamberWindow",
            ScatteringChamberWindow_Logical,
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);
    G4cout << G4endl << "###### Leaving QweakSimTarget::ConstructScatteringChamberWindow() " << G4endl << G4endl;

//*************************End of Target Vacuum Window *****************************
}

//--------------------------------------

void QweakSimTarget::ConstructTargetMaterial()
{
      // define target material solid volume
    G4cout << G4endl << "###### Calling QweakSimTarget::ConstructTargetMaterial() " << G4endl << G4endl;

    if (TargetContainer_Logical)
          TargetContainer_Logical->RemoveDaughter(TargetMaterial_Physical);

    delete TargetMaterial_Physical;
    TargetMaterial_Physical = NULL;

    G4Cons* TargetMaterial_Solid = new G4Cons("QweakTargetMaterial_Sol",
            0., //targetCellFrontRadiusMin, // G4double  pRmin1,
            targetCellFrontInnerRadiusMax, // G4double  pRmax1,
            0., //targetCellBackRadiusMin, //G4double  pRmin2,
            targetCellBackInnerRadiusMax, //G4double  pRmax2,
            0.5*targetCellInnerLength,    //G4double  pDz,
            targetCellStartingPhi, //G4double  pSPhi,
            targetCellDeltaPhi);   //G4double  pDPhi)


    // define Target logical volume
    G4cout << G4endl << "###### QweakSimTarget: Define Target_Logical " << G4endl << G4endl;

    TargetMaterial_Logical  = new G4LogicalVolume(TargetMaterial_Solid,
            TargetMaterial_Material,
            "QweakTargetMaterial_Log",
            0,0,0);

    // set max step size for LH2 target
    G4double MaxStepInTarget = 0.05*targetCellInnerLength; //step size < 20% of target length
    TargetMaterial_Logical->SetUserLimits(new G4UserLimits(MaxStepInTarget));

    // define Target material physical volume
    G4cout << G4endl << "###### QweakSimTarget: Define TargetMaterial_Physical " << G4endl << G4endl;
    TargetMaterial_Physical   = new G4PVPlacement(0,
            positionTarget,
            "QweakTargetMaterial",
            TargetMaterial_Logical,
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);
    G4cout << G4endl << "###### Leaving QweakSimTarget::ConstructTargetMaterial() " << G4endl << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTarget(G4String targName)
{ // NOTE: Can only make one call at a time.  To change targets you must
  // make a new run, otherwise the positions of the dummy target will be wrong.
  
  double zlength = 0.0; // Use for setting dummy position such that
                        // US face's are aligned (see Target ELOG 18).
  // Technically the US targets are on average 1.39 mm upstream of the entrance window
  // and the DS targets are on average 2.97 mm upstream of the exit window.  For simplicity
  // just align the US faces at -(+)17.173 cm for the US(DS) targets.
  // K.E. Mesick 23/September/2014
  
  if (strcmp(targName,"LH2")==0)
    {
      G4cout << "==== Target is LH2 by default!! " << G4endl;
    }
  else if (strcmp(targName,"USAl1p")==0)
    {
      G4cout << "==== Changing Target to " << targName << G4endl;
      zlength = targetCellInnerLength - 2.0*myUserInfo->TargetThicknessUSALDummy1;
      SetTargetEntranceWindowMaterial("Aluminum");
      SetTargetEntranceWindowLength(myUserInfo->TargetThicknessUSALDummy1);
      SetTargetLength(zlength);
      SetTargetMaterial("Vacuum");
      SetTargetExitWindowMaterial("Vacuum");
      SetTargetExitWindowNippleMaterial("Vacuum");
      G4cout << "==== Changing Target :  Now the Target is " << targName << G4endl;
    }
  else if (strcmp(targName,"USAl2p")==0)
    {
      G4cout << "==== Changing Target to " << targName << G4endl;
      zlength = targetCellInnerLength - 2.0*myUserInfo->TargetThicknessUSALDummy2;
      SetTargetEntranceWindowMaterial("Aluminum");
      SetTargetEntranceWindowLength(myUserInfo->TargetThicknessUSALDummy2);
      SetTargetLength(zlength);
      SetTargetMaterial("Vacuum");
      SetTargetExitWindowMaterial("Vacuum");
      SetTargetExitWindowNippleMaterial("Vacuum");
      G4cout << "==== Changing Target :  Now the Target is " << targName << G4endl;
    }
  else if (strcmp(targName,"USAl4p")==0)
    {
      G4cout << "==== Changing Target to " << targName << G4endl;
      zlength = targetCellInnerLength - 2.0*myUserInfo->TargetThicknessUSALDummy4;
      SetTargetEntranceWindowMaterial("Aluminum");
      SetTargetEntranceWindowLength(myUserInfo->TargetThicknessUSALDummy4);
      SetTargetLength(zlength);
      SetTargetMaterial("Vacuum");
      SetTargetExitWindowMaterial("Vacuum");
      SetTargetExitWindowNippleMaterial("Vacuum");
      G4cout << "==== Changing Target :  Now the Target is " << targName << G4endl;
    }  
  else if (strcmp(targName,"USC")==0)
    {
      G4cout << "==== Changing Target to " << targName << G4endl;
      zlength = targetCellInnerLength - 2.0*myUserInfo->TargetThicknessUSCDummy;
      SetTargetEntranceWindowMaterial("USCarbon");
      SetTargetEntranceWindowLength(myUserInfo->TargetThicknessUSCDummy);
      SetTargetLength(zlength);
      SetTargetMaterial("Vacuum");
      SetTargetExitWindowMaterial("Vacuum");
      SetTargetExitWindowNippleMaterial("Vacuum");
      G4cout << "==== Changing Target :  Now the Target is " << targName << G4endl;
    }
  else if (strcmp(targName,"DSAl2p")==0)
    {
      G4cout << "==== Changing Target to " << targName << G4endl;
      zlength = targetCellInnerLength;
      SetTargetEntranceWindowMaterial("Vacuum");
      SetTargetLength(zlength);
      SetTargetMaterial("Vacuum");
      SetTargetExitWindowLength(myUserInfo->TargetThicknessDSALDummy2);
      SetTargetExitWindowNippleLength(myUserInfo->TargetThicknessDSALDummy2);
      SetTargetExitWindowMaterial("Aluminum"); 
      SetTargetExitWindowNippleMaterial("Aluminum");
      G4cout << "==== Changing Target :  Now the Target is " << targName << G4endl;
    }
  else if (strcmp(targName,"DSAl4p")==0)
    {
      G4cout << "==== Changing Target to " << targName << G4endl;
      zlength = targetCellInnerLength;
      SetTargetEntranceWindowMaterial("Vacuum");
      SetTargetLength(zlength);
      SetTargetMaterial("Vacuum");
      SetTargetExitWindowLength(myUserInfo->TargetThicknessDSALDummy4);
      SetTargetExitWindowNippleLength(myUserInfo->TargetThicknessDSALDummy4);
      SetTargetExitWindowMaterial("Aluminum"); 
      SetTargetExitWindowNippleMaterial("Aluminum");
      G4cout << "==== Changing Target :  Now the Target is " << targName << G4endl;
    }
  else if (strcmp(targName,"DSAl8p")==0)
    {
      G4cout << "==== Changing Target to " << targName << G4endl;
      zlength = targetCellInnerLength;
      SetTargetEntranceWindowMaterial("Vacuum");
      SetTargetLength(zlength);
      SetTargetMaterial("Vacuum");
      SetTargetExitWindowLength(myUserInfo->TargetThicknessDSALDummy8);
      SetTargetExitWindowNippleLength(myUserInfo->TargetThicknessDSALDummy8);
      SetTargetExitWindowMaterial("Aluminum"); 
      SetTargetExitWindowNippleMaterial("Aluminum");
      G4cout << "==== Changing Target :  Now the Target is " << targName << G4endl;
    }
  else if (strcmp(targName,"DSC")==0)
    {
      G4cout << "==== Changing Target to " << targName << G4endl;
      zlength = targetCellInnerLength;
      SetTargetEntranceWindowMaterial("Vacuum");
      SetTargetLength(zlength);
      SetTargetMaterial("Vacuum");
      SetTargetExitWindowLength(myUserInfo->TargetThicknessDSCDummy);
      SetTargetExitWindowNippleLength(myUserInfo->TargetThicknessDSCDummy);
      SetTargetExitWindowMaterial("DSCarbon"); 
      SetTargetExitWindowNippleMaterial("DSCarbon");
      G4cout << "==== Changing Target :  Now the Target is " << targName << G4endl;
    }
    else {
        G4cerr << "==== ERROR: Changing Target failed" << G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTargetMaterial(G4String materialName)
{
    // search the material by its name
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial)
    {
        G4cout << "==== Changing Target Material: Looking up Material  " << G4endl;
        TargetMaterial_Logical->SetMaterial(pttoMaterial);
        G4cout << "==== Changing Target Material:  Now the Target is made of " << materialName << G4endl;
    }
    else {
        G4cerr << "==== ERROR: Changing Target Material failed" << G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTargetCellMaterial(G4String materialName)
{
    // search the material by its name
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial)
    {
        G4cout << "==== Changing Target Cell Material: Looking up Material  " << G4endl;
        TargetCell_Logical->SetMaterial(pttoMaterial);
        G4cout << "==== Changing Target Cell Material:  Now the Target Cell is made of " << materialName << G4endl;
    }
    else {
        G4cerr << "==== ERROR: Changing Target Cell Material failed" << G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTargetEntranceWindowMaterial(G4String materialName)
{
    // search the material by its name
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial)
    {
        G4cout << "==== Changing Target Entrance Window Material: Looking up Material  " << G4endl;
        TargetEntranceWindow_Logical->SetMaterial(pttoMaterial);
        G4cout << "==== Changing Target Entrance Window Material:  Now the Target Entrance Window is made of " << materialName << G4endl;
    }
    else {
        G4cerr << "==== ERROR: Changing Target Entrance Window Material failed" << G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTargetExitWindowMaterial(G4String materialName)
{
    // search the material by its name
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial)
    {
        G4cout << "==== Changing Target Exit Window Material: Looking up Material  " << G4endl;
        TargetExitWindow_Logical->SetMaterial(pttoMaterial);
        G4cout << "==== Changing Target Exit Window Material:  Now the Target Exit Window is made of " << materialName << G4endl;
    }
    else {
        G4cerr << "==== ERROR: Changing Target Exit Window Material failed" << G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTargetExitWindowNippleMaterial(G4String materialName)
{
    // search the material by its name
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial)
    {
        G4cout << "==== Changing Target Exit Window Nipple Material: Looking up Material  " << G4endl;
        TargetExitWindowNipple_Logical->SetMaterial(pttoMaterial);
        G4cout << "==== Changing Target Exit Window Nipple Material:  Now the Target Exit Window Nipple is made of " << materialName << G4endl;
    }
    else {
        G4cerr << "==== ERROR: Changing Target Exit Window Nipple Material failed" << G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::DestroyComponent()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTargetCenterPositionInZ(G4double zPos)
{
    G4cout << G4endl << "###### Calling QweakSimTarget::SetTargetCenterPositionInZ() " << G4endl << G4endl;

    targetZPos = zPos;
    myUserInfo->TargetCenterPositionZ = zPos;
    TargetContainer_Physical->SetTranslation(G4ThreeVector(0.,0., zPos));
    G4cout << "==== Changing Target CenterPositionZ:  Now the Target Center Position in Z is " << zPos/cm << " cm" << G4endl;
}

G4double QweakSimTarget::GetTargetCenterPositionInZ()
{
    G4cout << G4endl << "###### Calling QweakSimTarget::GetTargetCenterPositionInZ() " << G4endl << G4endl;
    return targetZPos;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTarget::SetTargetLength(G4double len)
{
    G4cout << G4endl << "###### Calling QweakSimTarget::SetTargetLength() " << G4endl << G4endl;

    targetCellInnerLength = len;
    myUserInfo->TargetLength = len;
    G4cout << "==== Changing Target Length:  Now the Target Length is " << len/cm << " cm" << G4endl;

    CalculateTargetPositions();

    // construct target cell/material of appropriate length
    ConstructTargetCell();      // Al cell without end caps
    ConstructTargetMaterial();  // LH2 for production target

    // construct the end caps at the correct location
    ConstructTargetEntranceWindow(); 
    ConstructTargetExitWindow();
    ConstructTargetExitWindowNipple();

    G4cout << G4endl << "###### Leaving QweakSimTarget::SetTargetLength() " << G4endl << G4endl;
}

G4double QweakSimTarget::GetTargetLength()
{
    G4cout << G4endl << "###### Calling QweakSimTarget::GetTargetLength() " << G4endl << G4endl;
    return targetCellInnerLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTarget::SetTargetEntranceWindowLength(G4double len)
{
  G4cout << G4endl << "###### Calling QweakSimTarget::SetTargetEntranceWindowLength() " << G4endl << G4endl;
  
  myUserInfo->TargetEntranceWindowThickness = len;
  targetCellEntranceWindowThickness = len;

  G4cout << "==== Changing Target Entrance Window Length:  Now the Target Entrance Window Length is " << len/mm << " mm" << G4endl;

  CalculateTargetPositions();
  ConstructTargetEntranceWindow();

  G4cout << G4endl << "###### Leaving QweakSimTarget::SetTargetEntranceWindowLength() " << G4endl << G4endl;
}

void QweakSimTarget::SetTargetExitWindowLength(G4double len)
{
  G4cout << G4endl << "###### Calling QweakSimTarget::SetTargetExitWindowLength() " << G4endl << G4endl;

  myUserInfo->TargetExitWindowThickness = len;
  targetCellExitWindowThickness = len; 
  G4cout << "==== Changing Target Exit Window Length:  Now the Target Exit Window Length is " << len/mm << " mm" << G4endl;

  CalculateTargetPositions();
  ConstructTargetExitWindow();

  G4cout << G4endl << "###### Leaving QweakSimTarget::SetTargetExitWindowLength() " << G4endl << G4endl;
}

void QweakSimTarget::SetTargetExitWindowNippleLength(G4double len)
{
  G4cout << G4endl << "###### Calling QweakSimTarget::SetTargetExitWindowNippleLength() " << G4endl << G4endl;

  myUserInfo->TargetExitWindowNippleThickness = len;
  targetCellExitWindowNippleThickness = len; 
  G4cout << "==== Changing Target Exit Window Nipple Length:  Now the Target Exit Window Nipple Length is " << len/mm << " mm" << G4endl;

  CalculateTargetPositions();
  ConstructTargetExitWindowNipple();

  G4cout << G4endl << "###### Leaving QweakSimTarget::SetTargetExitWindowNippleLength() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double QweakSimTarget::CalculateLuminosity(G4double mass, G4double density, G4double length)
{
  G4double Lum = 0.0;            // Luminosity
  G4double N_b = 6.241e12;       // [Hz/uA] # of particles in the beam (from definition of ampere)
  G4double N_A = 6.02214129e23;  // Avagadro's number

  Lum = N_b*length*density*N_A/mass;  //  units [Hz/(uA*mm^2)]

  Lum *= 1e-31;  //  Conversion from [Hz/(uA*mm^2)] -> [kHz/(uA*ub)]

  return Lum;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
