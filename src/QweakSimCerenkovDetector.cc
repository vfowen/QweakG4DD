//
// p.wang: the components of main detector module are added in piece by piece, and holded by container.
// no assembly object.
//

#include "QweakSimCerenkovDetector.hh"

static const G4double inch = 2.54*cm;

QweakSimCerenkovDetector::QweakSimCerenkovDetector(QweakSimUserInformation *userInfo) {

    // initialize some pointers
    myUserInfo = userInfo;

    pMaterial                 = NULL;

    theMotherPV               = NULL;

    CerenkovContainer_Logical  = NULL;
    CerenkovContainer_Physical = NULL;
    CerenkovContainer_Material = NULL;

    Frame_Logical   = NULL;
    Frame_Physical  = NULL;
    Frame_Material  = NULL;

    SideBracket_Logical = NULL;
    SideBracketPad_Logical = NULL;

    ActiveArea_Logical         = NULL;
    ActiveArea_Physical        = NULL;
    ActiveArea_Material        = NULL;

    LightGuide_LogicalLeft     = NULL;
    LightGuide_LogicalRight    = NULL;
    LightGuide_PhysicalLeft    = NULL;
    LightGuide_PhysicalRight   = NULL;
    LightGuide_Material        = NULL;

    QuartzBar_LogicalLeft      = NULL;
    QuartzBar_LogicalRight     = NULL;
    QuartzBar_PhysicalLeft     = NULL;
    QuartzBar_PhysicalRight    = NULL;
    QuartzBar_Material         = NULL;

    QuartzGlue_Logical         = NULL;
    QuartzGlue_PhysicalLeft    = NULL;
    QuartzGlue_PhysicalCenter  = NULL;
    QuartzGlue_PhysicalRight   = NULL;
    QuartzGlue_Material        = NULL;

    PMTContainer_Logical  = NULL;
    PMTContainer_PhysicalLeft  = NULL;
    PMTContainer_PhysicalRight = NULL;
    PMTContainer_Material = NULL;

    PMTEntranceWindow_Logical  = NULL;
    PMTEntranceWindow_Physical = NULL;
    PMTEntranceWindow_Material = NULL;

    Cathode_Logical  = NULL;
    Cathode_Physical = NULL;
    Cathode_Material = NULL;

    PMTQuartzOpticalFilm_Logical  = NULL;
    PMTQuartzOpticalFilm_Physical = NULL;
    PMTQuartzOpticalFilm_Material = NULL;

    Rotation_CerenkovContainer = NULL;

    // pointer to the sensitive detector
    CerenkovDetectorSD      = NULL;
    CerenkovDetector_PMTSD  = NULL;

    // clear vector containing temp solids for boolean soild union
    LeftQuartz_Solid.clear();
    LeftQuartz_Solid.resize(4);  //need 4 chamfers on quartz bar proper
    RightQuartz_Solid.clear();
    RightQuartz_Solid.resize(4); //need 4 chamfers on quartz bar proper
    LeftGuide_Solid.clear();
    LeftGuide_Solid.resize(5); //need 4 chamfers + 1 angle cut on light guide
    RightGuide_Solid.clear();
    RightGuide_Solid.resize(5);  //need 4 chamfers + 1 angle cut on light guide

    mirror_logical.clear();
    mirror_physical.clear();

    mirror_logical.resize(8);
    mirror_physical.resize(8);

    SideBracket_Physical.clear();
    Rotation_SideBracket.clear();
    Position_SideBracket.clear();

    SideBracketPad_Physical.clear();
    Rotation_SideBracketPad.clear();
    Position_SideBracketPad.clear();

    pMaterial = new QweakSimMaterial();
    pMaterial->DefineMaterials();

    //CerenkovContainer_Material = pMaterial->GetMaterial("Air");
    CerenkovContainer_Material = pMaterial->GetMaterial("Air");
    ActiveArea_Material        = pMaterial->GetMaterial("Air");
    QuartzBar_Material         = pMaterial->GetMaterial("Quartz");
    LightGuide_Material        = pMaterial->GetMaterial("Quartz");
    PMTContainer_Material      = pMaterial->GetMaterial("Air"); //Vacuum
    PMTEntranceWindow_Material = pMaterial->GetMaterial("LimeGlass");
    PMTQuartzOpticalFilm_Material = pMaterial->GetMaterial("SiElast_Glue");
    Cathode_Material           = pMaterial->GetMaterial("Photocathode");
    Radiator_Material          = pMaterial->GetMaterial("PBA");
    PMT_PbShield_Material      = pMaterial->GetMaterial("Lead");
    QuartzGlue_Material        = pMaterial->GetMaterial("SiElast_Glue");
    mirror_material            = pMaterial->GetMaterial("Mirror");
    Frame_Material             = pMaterial->GetMaterial("Aluminum");
    Window_Material            = pMaterial->GetMaterial("Tyvek");
    BracketPad_Material        = pMaterial->GetMaterial("Tyvek");

    Container_Center_X         =  0.0*cm;
    Container_Center_Y         =  0.0*cm;
    Container_Center_Z         =  -4.25*cm;

    Container_Center = G4ThreeVector(Container_Center_X, Container_Center_Y, Container_Center_Z);

    Default_Position_CerenkovContainer_X =      0*cm;
    Default_Position_CerenkovContainer_Y = 335.17*cm;
    Default_Position_CerenkovContainer_Z = 577.88*cm-Container_Center_Z;

    LightGuide_FullLength      =   18.00*cm;
    LightGuide_FullWidth1      =   18.00*cm;
    LightGuide_FullWidth2      =   18.00*cm;
    LightGuide_FullThickness   =    1.25*cm;

    QuartzBar_FullLength       =  100.00*cm;    // Full X length
    QuartzBar_FullHeight       =   18.00*cm;    // Full Y length
    QuartzBar_FullThickness    =    1.25*cm;    // Full Z length

    GlueFilm_FullLength_X      =   0.1*mm;
    GlueFilm_FullLength_Y      =   18.00*cm;
    GlueFilm_FullLength_Z      =    1.25*cm;

    ActiveArea_FullLength_X    =    2.0*(LightGuide_FullLength + QuartzBar_FullLength +GlueFilm_FullLength_X) + GlueFilm_FullLength_X +2.0*mm;
    ActiveArea_FullLength_Y    =    QuartzBar_FullHeight + 1.0*mm;
    ActiveArea_FullLength_Z    =    QuartzBar_FullThickness + 2.0*mm;

    Container_FullLength_X     =  95.6*inch;
    Container_FullLength_Y     =  9.6*inch;
    Container_FullLength_Z     =  14.0*inch+2.0*Container_Center_Z;

    Chamfer_FullLength         =  120.00*cm;
    Chamfer_FullHeight         =    7.00*mm;
    Chamfer_FullThickness      =    7.00*mm;

    G4double ReductionInPhotocathodeDiameter = 5*mm;

    PMTQuartzOpticalFilm_Thickness=  0.1*mm;
    PMTQuartzOpticalFilm_Diameter =  12.7*cm;

    PMTEntranceWindow_Thickness   =  1.0*mm; // assumed PMT glass thickness
    PMTEntranceWindow_Diameter    =  12.7*cm;//QuartzBar_FullHeight;

    Cathode_Thickness   = 1.0*mm;
    Cathode_Diameter    = PMTEntranceWindow_Diameter - ReductionInPhotocathodeDiameter;

    PMTContainer_Diameter    =  PMTEntranceWindow_Diameter+1.0*mm;
    PMTContainer_FullLength_Z    =  2.0*mm+PMTEntranceWindow_Thickness+Cathode_Thickness;

    Tilting_Angle   =  0.0*degree;

    NumberOfCerenkovDetectors = 8;
    SetNumberOfDetectors(8); // needs to be at the end, updates geometry
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCerenkovDetector::~QweakSimCerenkovDetector() {
    delete pMaterial;
    for(size_t h=0; h<CerenkovDetectorMessenger.size(); h++){
      delete CerenkovDetectorMessenger[h];
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkovDetector::DefineCerenkovGeometry() {
    G4cout << G4endl << "###### Calling QweakSimCerenkovDetector::DefineCerenkovGeometry() " << G4endl << G4endl;
    G4cout << G4endl << "###### Leaving QweakSimCerenkovDetector::DefineCerenkovGeometry() " << G4endl << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkovDetector::ConstructComponent(G4VPhysicalVolume* MotherVolume) {
    //----------------------------------------------
    // save the pointer to the physical mothervolume
    //----------------------------------------------
    //
    theMotherPV = MotherVolume;


//****************************************************************************************************
//******************************Define Detector Container*********************************************/

//jpan@nuclear.uwinnipeg.ca
   //for(size_t g=0; g<Position_CerenkovContainer_X.size(); g++){
 
    //Position_CerenkovContainer  = G4ThreeVector(Position_CerenkovContainer_X[g],
    //                            Position_CerenkovContainer_Y[g],
    //                            Position_CerenkovContainer_Z[g]);

    //Rotation_CerenkovContainer = new G4RotationMatrix();

    //Rotation_CerenkovContainer->rotateX(Tilting_Angle);

    G4Box* CerenkovContainer_Solid  = new G4Box("CerenkovContainer_Solid",
            0.5 * Container_FullLength_X ,    // half X length required by Geant4
            0.5 * Container_FullLength_Y ,    // half Y length required by Geant4
            0.5 * Container_FullLength_Z );   // half Z length required by Geant4

    CerenkovContainer_Logical  = new G4LogicalVolume(CerenkovContainer_Solid,
            CerenkovContainer_Material,
            "CerenkovContainer_Logical",
            0,0,0);


//******************************Define Detector OuterFrame*************************

    Frame_FullLength_X = 95.5*inch;
    Frame_FullLength_Y = 9.5*inch;
    Frame_FullLength_Z = 2.0*inch;

    Frame_InnerFullLength_X = (95.5-0.75*2.0)*inch;
    Frame_InnerFullLength_Y = (9.5-0.75*2.0)*inch;
    Frame_InnerFullLength_Z = 2.0*inch+0.1*mm;  // a bit larger to avoid sharing surface with the outer which may cause vis-problem

    G4Box* OuterFrame  = new G4Box("OuterFrame",
                                   0.5 * Frame_FullLength_X ,
                                   0.5 * Frame_FullLength_Y ,
                                   0.5 * Frame_FullLength_Z );

    G4Box* InnerFrame  = new G4Box("InnerFrame",
                                   0.5 * Frame_InnerFullLength_X ,
                                   0.5 * Frame_InnerFullLength_Y ,
                                   0.5 * Frame_InnerFullLength_Z );

    G4SubtractionSolid* Frame_Solid = new G4SubtractionSolid("OuterFrame-InnerFrame", OuterFrame, InnerFrame);

    Frame_Logical  = new G4LogicalVolume(Frame_Solid,
                                         Frame_Material,
                                         "Frame_Log",
                                         0,0,0);

    G4ThreeVector Position_Frame  = G4ThreeVector(0,0,0.25*inch);

    Frame_Physical   = new G4PVPlacement(0,Position_Frame + Container_Center,
                                         Frame_Logical,
                                         "Frame_Physical",
                                         CerenkovContainer_Logical,
                                         false,0,
                                         pSurfChk);


//****************************************************************************************************
//******************************Define Side Bracket*******************************************

    SideBracketLength_X = 3.0*inch;
    SideBracketLength_Y = 0.75*inch;
    SideBracketLength_Z = 1.75*inch;

    SideBracketCutLength_X = 3.0*inch+0.1*mm;
    SideBracketCutLength_Y = 0.5*inch+0.1*mm;
    SideBracketCutLength_Z = 0.75*inch;

    G4Box* OuterSideBracket  = new G4Box("OuterSideBracket",
                                         0.5 * SideBracketLength_X,
                                         0.5 * SideBracketLength_Y,
                                         0.5 * SideBracketLength_Z);

    G4Box* InnerSideBracket  = new G4Box("InnerSideBracket",
                                         0.5 * SideBracketCutLength_X,
                                         0.5 * SideBracketCutLength_Y,
                                         0.5 * SideBracketCutLength_Z);

    G4RotationMatrix* cutRot = new G4RotationMatrix(0,0,0);
    G4ThreeVector cutTrans(0, 0.125*inch, -0.25*inch);

    G4SubtractionSolid* SideBracket_Solid = new G4SubtractionSolid("OuterSideBracket-InnerSideBracket",
            OuterSideBracket,
            InnerSideBracket,
            cutRot,
            cutTrans);

    SideBracket_Logical  = new G4LogicalVolume(SideBracket_Solid,
            Frame_Material,
            "SideBracket_Log",
            0,0,0);

    for (G4int i=0; i<12; i++) {
        Rotation_SideBracket.push_back(new G4RotationMatrix(0,0,0));
        if (i>=6)     Rotation_SideBracket[i]->rotateZ(180.0*degree);
    }

    Position_SideBracket.push_back (G4ThreeVector(3.0*inch,-3.625*inch,0.25*inch) );
    Position_SideBracket.push_back (G4ThreeVector(-3.0*inch,-3.625*inch,0.25*inch) );
    Position_SideBracket.push_back (G4ThreeVector(35.37*inch,-3.625*inch,0.25*inch) );
    Position_SideBracket.push_back (G4ThreeVector(-35.37*inch,-3.625*inch,0.25*inch) );
    Position_SideBracket.push_back (G4ThreeVector(43.62*inch,-3.625*inch,0.25*inch) );
    Position_SideBracket.push_back (G4ThreeVector(-43.62*inch,-3.625*inch,0.25*inch) );
    Position_SideBracket.push_back (G4ThreeVector(3.0*inch,3.625*inch,0.25*inch) );
    Position_SideBracket.push_back (G4ThreeVector(-3.0*inch,3.625*inch,0.25*inch) );
    Position_SideBracket.push_back (G4ThreeVector(35.37*inch,3.625*inch,0.25*inch) );
    Position_SideBracket.push_back (G4ThreeVector(-35.37*inch,3.625*inch,0.25*inch) );
    Position_SideBracket.push_back (G4ThreeVector(43.62*inch,3.625*inch,0.25*inch) );
    Position_SideBracket.push_back (G4ThreeVector(-43.62*inch,3.625*inch,0.25*inch) );


    for (G4int i = 0; i<12; i++) {
        SideBracket_Physical.push_back( new G4PVPlacement(Rotation_SideBracket.at(i),Position_SideBracket.at(i) + Container_Center,
                                        SideBracket_Logical,
                                        "SideBracket_Physical",
                                        CerenkovContainer_Logical,
                                        false,i,
                                        pSurfChk));

    }

//******************************Define Side Bracket Pad*******************************************

    SideBracketPadLength_X = SideBracketLength_X;
    SideBracketPadLength_Y = SideBracketCutLength_Y-0.2*mm;
    SideBracketPadLength_Z = SideBracketCutLength_Z-0.2*mm;

    SideBracketPadCutLength_X = SideBracketCutLength_X;
    SideBracketPadCutLength_Y = SideBracketCutLength_Y-5.0*mm;
    SideBracketPadCutLength_Z = QuartzBar_FullThickness;

    G4Box* OuterSideBracketPad  = new G4Box("OuterSideBracketPad",
                                         0.5 * SideBracketPadLength_X,
                                         0.5 * SideBracketPadLength_Y,
                                         0.5 * SideBracketPadLength_Z);

    G4Box* InnerSideBracketPad  = new G4Box("InnerSideBracketPad",
                                         0.5 * SideBracketPadCutLength_X,
                                         0.5 * SideBracketPadCutLength_Y,
                                         0.5 * SideBracketPadCutLength_Z);

    G4RotationMatrix* PadCutRot = new G4RotationMatrix(0,0,0);
    //G4ThreeVector PadCutTrans(0, 0.125*inch, -0.25*inch);
    // (front , bottom, back)
    G4ThreeVector PadCutTrans(0., 0.11*inch, 0.);

    G4SubtractionSolid* SideBracketPad_Solid = new G4SubtractionSolid("OuterSideBracketPad-InnerSideBracketPad",
            OuterSideBracketPad,
            InnerSideBracketPad,
            PadCutRot,
            PadCutTrans);

    SideBracketPad_Logical  = new G4LogicalVolume(SideBracketPad_Solid,
            BracketPad_Material,
            "SideBracketPad_Log",
            0,0,0);

    for (G4int i=0; i<12; i++) {
        Rotation_SideBracketPad.push_back(new G4RotationMatrix(0,0,0));
        if (i>=6)     Rotation_SideBracketPad[i]->rotateZ(180.0*degree);
    }

    Position_SideBracketPad.push_back (G4ThreeVector(3.0*inch,-3.5*inch,0.) );
    Position_SideBracketPad.push_back (G4ThreeVector(-3.0*inch,-3.5*inch,0.) );
    Position_SideBracketPad.push_back (G4ThreeVector(35.37*inch,-3.5*inch,0.) );
    Position_SideBracketPad.push_back (G4ThreeVector(-35.37*inch,-3.5*inch,0.) );
    Position_SideBracketPad.push_back (G4ThreeVector(43.62*inch,-3.5*inch,0.) );
    Position_SideBracketPad.push_back (G4ThreeVector(-43.62*inch,-3.5*inch,0.) );
    Position_SideBracketPad.push_back (G4ThreeVector(3.0*inch,3.5*inch,0.) );
    Position_SideBracketPad.push_back (G4ThreeVector(-3.0*inch,3.5*inch,0.) );
    Position_SideBracketPad.push_back (G4ThreeVector(35.37*inch,3.5*inch,0.) );
    Position_SideBracketPad.push_back (G4ThreeVector(-35.37*inch,3.5*inch,0.) );
    Position_SideBracketPad.push_back (G4ThreeVector(43.62*inch,3.5*inch,0.) );
    Position_SideBracketPad.push_back (G4ThreeVector(-43.62*inch,3.5*inch,0.) );


    for (G4int i = 0; i<12; i++) {
        SideBracketPad_Physical.push_back( new G4PVPlacement(Rotation_SideBracketPad.at(i),Position_SideBracketPad.at(i) + Container_Center,
                                        SideBracketPad_Logical,
                                        "SideBracketPad_Physical",
                                        CerenkovContainer_Logical,
                                        false,i,
                                        pSurfChk));

    }

//******************************Define End Bracket *******************************************

    EndBracketLength_X = 1.5*inch;
    EndBracketLength_Y = 0.75*inch;
    EndBracketLength_Z = 1.75*inch;

    EndBracketCutLength_X = 1.5*inch+0.1*mm;
    EndBracketCutLength_Y = 0.5*inch+0.1*mm;
    EndBracketCutLength_Z = 0.75*inch;

    G4Box* OuterEndBracket  = new G4Box("OuterEndBracket",
                                        0.5 * EndBracketLength_X,
                                        0.5 * EndBracketLength_Y,
                                        0.5 * EndBracketLength_Z);

    G4Box* InnerEndBracket  = new G4Box("InnerEndBracket",
                                        0.5 * EndBracketCutLength_X,
                                        0.5 * EndBracketCutLength_Y,
                                        0.5 * EndBracketCutLength_Z);

    //G4RotationMatrix* cutRot = new G4RotationMatrix(0,0,0);
    //G4ThreeVector cutTrans(0, 0.125*inch, -0.25*inch);

    G4SubtractionSolid* EndBracket_Solid = new G4SubtractionSolid("OuterEndBracket-InnerEndBracket",
            OuterEndBracket,
            InnerEndBracket,
            cutRot,
            cutTrans);

    EndBracket_Logical  = new G4LogicalVolume(EndBracket_Solid,
            Frame_Material,
            "EndBracket_Log",
            0,0,0);

    for (G4int i=0; i<4; i++) {
        Rotation_EndBracket.push_back(new G4RotationMatrix(0,0,0));
        if (i<2)     Rotation_EndBracket[i]->rotateZ(-90.0*degree);
        else         Rotation_EndBracket[i]->rotateZ(90.0*degree);
    }

    G4double Distance_EndBracketToBarCenter = Frame_InnerFullLength_X*0.5 - 0.375*inch;

    Position_EndBracket.push_back (G4ThreeVector(Distance_EndBracketToBarCenter,3.0*inch,0.25*inch) );
    Position_EndBracket.push_back (G4ThreeVector(Distance_EndBracketToBarCenter,-3.0*inch,0.25*inch) );
    Position_EndBracket.push_back (G4ThreeVector(-Distance_EndBracketToBarCenter,3.0*inch,0.25*inch) );
    Position_EndBracket.push_back (G4ThreeVector(-Distance_EndBracketToBarCenter,-3.0*inch,0.25*inch) );

    for (G4int i = 0; i<4; i++) {
        EndBracket_Physical.push_back( new G4PVPlacement(Rotation_EndBracket.at(i),Position_EndBracket.at(i) + Container_Center,
                                       EndBracket_Logical,
                                       "EndBracket_Physical",
                                       CerenkovContainer_Logical,
                                       false,i,
                                       pSurfChk));

    }

//******************************Define End Bracket Pad*******************************************

    EndBracketPadLength_X = EndBracketLength_X;
    EndBracketPadLength_Y = EndBracketCutLength_Y-0.1*mm;
    EndBracketPadLength_Z = EndBracketCutLength_Z-0.1*mm;

    EndBracketPadCutLength_X = EndBracketPadLength_X+0.1*mm;
    EndBracketPadCutLength_Y = EndBracketCutLength_Y-5.0*mm;
    EndBracketPadCutLength_Z = QuartzBar_FullThickness;;

    G4Box* OuterEndBracketPad  = new G4Box("OuterEndBracketPad",
                                        0.5 * EndBracketPadLength_X,
                                        0.5 * EndBracketPadLength_Y,
                                        0.5 * EndBracketPadLength_Z);

    G4Box* InnerEndBracketPad  = new G4Box("InnerEndBracketPad",
                                        0.5 * EndBracketPadCutLength_X,
                                        0.5 * EndBracketPadCutLength_Y,
                                        0.5 * EndBracketPadCutLength_Z);

    //G4RotationMatrix* cutRot = new G4RotationMatrix(0,0,0);
    //G4ThreeVector cutTrans(0, 0.125*inch, -0.25*inch);

    G4ThreeVector EndPadCutTrans(0., 0.19*inch, 0.);

    G4SubtractionSolid* EndBracketPad_Solid = new G4SubtractionSolid("OuterEndBracketPad-InnerEndBracketPad",
            OuterEndBracketPad,
            InnerEndBracketPad,
            PadCutRot,
            EndPadCutTrans);

    EndBracketPad_Logical  = new G4LogicalVolume(EndBracketPad_Solid,
            BracketPad_Material,
            "EndBracketPad_Log",
            0,0,0);

    for (G4int i=0; i<4; i++) {
        Rotation_EndBracketPad.push_back(new G4RotationMatrix(0,0,0));
        if (i<2)     Rotation_EndBracketPad[i]->rotateZ(-90.0*degree);
        else         Rotation_EndBracketPad[i]->rotateZ(90.0*degree);
    }

    G4double Distance_EndBracketPadToBarCenter = Frame_InnerFullLength_X*0.5 - 0.5*inch;

    Position_EndBracketPad.push_back (G4ThreeVector(Distance_EndBracketPadToBarCenter,3.0*inch,0.) );
    Position_EndBracketPad.push_back (G4ThreeVector(Distance_EndBracketPadToBarCenter,-3.0*inch,0.) );
    Position_EndBracketPad.push_back (G4ThreeVector(-Distance_EndBracketPadToBarCenter,3.0*inch,0.) );
    Position_EndBracketPad.push_back (G4ThreeVector(-Distance_EndBracketPadToBarCenter,-3.0*inch,0.) );

    for (G4int i = 0; i<4; i++) {
        EndBracketPad_Physical.push_back( new G4PVPlacement(Rotation_EndBracketPad.at(i),Position_EndBracketPad.at(i) + Container_Center,
                                       EndBracketPad_Logical,
                                       "EndBracketPad_Physical",
                                       CerenkovContainer_Logical,
                                       false,i,
                                       pSurfChk));
    }



//******************************Define the Cross Bar *******************************************

    G4double CrossBar_FullLength_X = 1.5*inch;
    G4double CrossBar_FullLength_Y = Frame_FullLength_Y - 0.75*2.0*inch;
    G4double CrossBar_FullLength_Z = 0.75*inch;

    G4Box* CrossBar_Solid  = new G4Box("CrossBar_Solid",
                                       0.5 * CrossBar_FullLength_X ,
                                       0.5 * CrossBar_FullLength_Y ,
                                       0.5 * CrossBar_FullLength_Z );

    CrossBar_Logical  = new G4LogicalVolume(CrossBar_Solid,
                                            Frame_Material,
                                            "CrossBar_Log",
                                            0,0,0);

    G4ThreeVector Position_CrossBar_R  = G4ThreeVector((47.75-8.25)*inch,0,0.25*inch+0.625*inch);
    G4ThreeVector Position_CrossBar_L  = G4ThreeVector(-(47.75-8.25)*inch,0,0.25*inch+0.625*inch);

    CrossBarR_Physical   = new G4PVPlacement(0,Position_CrossBar_R + Container_Center,
            CrossBar_Logical,
            "CrossBarR_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

    CrossBarL_Physical   = new G4PVPlacement(0,Position_CrossBar_L + Container_Center,
            CrossBar_Logical,
            "CrossBarL_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

//******************************Define Detector Windows *******************************************

    WindowThickness = 5.0*mm;

    G4Box* FrontWindow_Solid  = new G4Box("FrontWindow_Solid",
                                          0.5 * Frame_FullLength_X ,
                                          0.5 * Frame_FullLength_Y ,
                                          0.5 * WindowThickness );

    FrontWindow_Logical  = new G4LogicalVolume(FrontWindow_Solid,
            Window_Material,
            "FrontWindow_Log",
            0,0,0);

    G4ThreeVector Position_FrontWindow  = G4ThreeVector(0,0,0.25*inch-(1.0*inch+2.5*mm));

    FrontWindow_Physical   = new G4PVPlacement(0,Position_FrontWindow + Container_Center,
            FrontWindow_Logical,
            "FrontWindow_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);


    G4Box* BackWindow_Solid  = new G4Box("BackWindow_Solid",
                                         0.5 * Frame_FullLength_X - 8.25*inch,
                                         0.5 * Frame_FullLength_Y ,
                                         0.5 * WindowThickness );

    BackWindow_Logical  = new G4LogicalVolume(BackWindow_Solid,
            Window_Material,
            "BackWindow_Log",
            0,0,0);

    G4ThreeVector Position_BackWindow  = G4ThreeVector(0,0,0.25*inch+1.0*inch+2.5*mm);

    BackWindow_Physical   = new G4PVPlacement(0,Position_BackWindow + Container_Center,
            BackWindow_Logical,
            "BackWindow_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);


//******************************Define Front Window Clip*******************************************

    G4double FrontClip_FullLength_X = 95.5*inch;
    G4double FrontClip_FullLength_Y = 9.5*inch;
    G4double FrontClip_FullLength_Z = 0.38*inch;

    G4double FrontClip_InnerFullLength_X = (95.5-0.75*2.0)*inch;
    G4double FrontClip_InnerFullLength_Y = (9.5-0.75*2.0)*inch;
    G4double FrontClip_InnerFullLength_Z = 0.38*inch+1.0*mm;  // a bit larger to avoid sharing surface with the outer which may cause vis-problem

    G4Box* FrontClip_Outer  = new G4Box("FrontClip_Outer",
                                        0.5 * FrontClip_FullLength_X ,
                                        0.5 * FrontClip_FullLength_Y ,
                                        0.5 * FrontClip_FullLength_Z );

    G4Box* FrontClip_Inner  = new G4Box("FrontClip_Inner",
                                        0.5 * FrontClip_InnerFullLength_X ,
                                        0.5 * FrontClip_InnerFullLength_Y ,
                                        0.5 * FrontClip_InnerFullLength_Z );

    G4SubtractionSolid* FrontClip_Solid = new G4SubtractionSolid("FrontClip_Outer-FrontClip_Inner",
            FrontClip_Outer,
            FrontClip_Inner);

    FrontClip_Logical  = new G4LogicalVolume(FrontClip_Solid,
            Frame_Material,
            "FrontClip_Log",
            0,0,0);

    G4ThreeVector Position_FrontClip  = G4ThreeVector(0,0,0.25*inch -(1.0*inch+5.0*mm+0.38/2.0*inch));

    FrontClip_Physical   = new G4PVPlacement(0,Position_FrontClip + Container_Center,
            FrontClip_Logical,
            "FrontClip_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

//******************************Define Back Window Clip*******************************************

    G4double BackClip_FullLength_X = 95.5*inch - 8.25*2.0*inch;
    G4double BackClip_FullLength_Y = 9.5*inch;
    G4double BackClip_FullLength_Z = 0.38*inch;

    G4double BackClip_InnerFullLength_X = 95.5*inch - 9.0*2.0*inch;
    G4double BackClip_InnerFullLength_Y = (9.5-0.75*2.0)*inch;
    G4double BackClip_InnerFullLength_Z = 0.38*inch+0.1*mm;  // a bit larger to avoid sharing surface with the outer which may cause vis-problem

    G4Box* BackClip_Outer  = new G4Box("BackClip_Outer",
                                       0.5 * BackClip_FullLength_X ,
                                       0.5 * BackClip_FullLength_Y ,
                                       0.5 * BackClip_FullLength_Z );

    G4Box* BackClip_Inner  = new G4Box("BackClip_Inner",
                                       0.5 * BackClip_InnerFullLength_X ,
                                       0.5 * BackClip_InnerFullLength_Y ,
                                       0.5 * BackClip_InnerFullLength_Z );

    G4SubtractionSolid* BackClip_Solid = new G4SubtractionSolid("BackClip_Outer-BackClip_Inner",
            BackClip_Outer,
            BackClip_Inner);

    BackClip_Logical  = new G4LogicalVolume(BackClip_Solid,
                                            Frame_Material,
                                            "BackClip_Log",
                                            0,0,0);

    G4ThreeVector Position_BackClip  = G4ThreeVector(0,0,0.25*inch + 1.0*inch+5.0*mm+0.38/2.0*inch);

    BackClip_Physical   = new G4PVPlacement(0,Position_BackClip + Container_Center,
                                            BackClip_Logical,
                                            "BackClip_Physical",
                                            CerenkovContainer_Logical,
                                            false,0,
                                            pSurfChk);

//******************************Define Square Falange Seal*******************************************

    G4double SquareFalangeSeal_FullLength_X = 8.21*inch;
    G4double SquareFalangeSeal_FullLength_Y = 9.50*inch;
    G4double SquareFalangeSeal_FullLength_Z = 5.0*mm;

    G4Box* SquareSealOuter_Solid  = new G4Box("SquareSealOuter_Solid",
            0.5 * SquareFalangeSeal_FullLength_X,
            0.5 * SquareFalangeSeal_FullLength_Y,
            0.5 * SquareFalangeSeal_FullLength_Z);

    G4Box* SquareSealInner_Solid  = new G4Box("SquareSealInner_Solid",
            0.5 * SquareFalangeSeal_FullLength_X - 0.75*inch,
            0.5 * SquareFalangeSeal_FullLength_Y - 0.75*inch,
            0.5 * SquareFalangeSeal_FullLength_Z + 0.1*mm);

    G4SubtractionSolid* SquareFalangeSeal_Solid
    = new G4SubtractionSolid("SquareSealOuter_Solid-SquareSealInner_Solid",
                             SquareSealOuter_Solid,
                             SquareSealInner_Solid);

    SquareFalangeSeal_Logical  = new G4LogicalVolume(SquareFalangeSeal_Solid,
            Window_Material,
            "SquareFalangeSeal_Log",
            0,0,0);

    G4ThreeVector Position_SquareFalangeSeal_R = G4ThreeVector((47.75-8.21/2.0)*inch,
            0,
            0.25*inch + 1.0*inch+2.5*mm);

    G4ThreeVector Position_SquareFalangeSeal_L = G4ThreeVector(-(47.75-8.21/2.0)*inch,
            0,
            0.25*inch + 1.0*inch+2.5*mm);

    SquareFalangeSealR_Physical   = new G4PVPlacement(0,Position_SquareFalangeSeal_R + Container_Center,
            SquareFalangeSeal_Logical,
            "SquareFalangeSealR_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

    SquareFalangeSealL_Physical   = new G4PVPlacement(0,Position_SquareFalangeSeal_L + Container_Center,
            SquareFalangeSeal_Logical,
            "SquareFalangeSealL_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

//******************************Define Square Falange *******************************************

    G4double SquareFalange_FullLength_X = 8.21*inch;
    G4double SquareFalange_FullLength_Y = 9.50*inch;
    G4double SquareFalange_FullLength_Z = 0.38*inch;

    G4double CutOuterRadius = 5.75*0.5*inch;
    G4double CutInnerRadius = 0.0*inch;
    G4double CutThickness = 0.38*inch+0.1*mm;

    G4Box* SquareBase_Solid  = new G4Box("SquareBase_Solid",
                                         0.5 * SquareFalange_FullLength_X,
                                         0.5 * SquareFalange_FullLength_Y,
                                         0.5 * SquareFalange_FullLength_Z);

    G4Tubs* CylinderCut_Solid = new G4Tubs("CylinderCut_Solid",
                                           CutInnerRadius,
                                           CutOuterRadius,
                                           0.5 * CutThickness,
                                           0.0, 360.0*degree);

    G4SubtractionSolid* SquareFalange_Solid = new G4SubtractionSolid("SquareBase_Solid-CylinderCut_Solid",
            SquareBase_Solid,
            CylinderCut_Solid);

    SquareFalange_Logical  = new G4LogicalVolume(SquareFalange_Solid,
            Frame_Material,
            "SquareFalange_Log",
            0,0,0);

    G4ThreeVector Position_SquareFalange_R = G4ThreeVector((47.75-8.21/2.0)*inch,
            0,
            0.25*inch + 1.0*inch+5.0*mm+0.38/2.0*inch);

    G4ThreeVector Position_SquareFalange_L = G4ThreeVector(-(47.75-8.21/2.0)*inch,
            0,
            0.25*inch + 1.0*inch+5.0*mm+0.38/2.0*inch);

    SquareFalangeR_Physical   = new G4PVPlacement(0,Position_SquareFalange_R + Container_Center,
            SquareFalange_Logical,
            "SquareFalangeR_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

    SquareFalangeL_Physical   = new G4PVPlacement(0,Position_SquareFalange_L + Container_Center,
            SquareFalange_Logical,
            "SquareFalangeL_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

//******************************Define PMT Housing Wall *******************************************

    G4double PMTHousingWallOuterRadius = 6.63*0.5*inch;
    G4double PMTHousingWallInnerRadius = 6.07*0.5*inch;
    G4double PMTHousingWallLength = 3.53*inch;

    G4Tubs* PMTHousingWall_Solid = new G4Tubs("PMTHousingWall_Solid",
            PMTHousingWallInnerRadius,
            PMTHousingWallOuterRadius,
            0.5 * PMTHousingWallLength,
            0.0, 360.0*degree);

    PMTHousingWall_Logical  = new G4LogicalVolume(PMTHousingWall_Solid,
            Frame_Material,
            "PMTHousingWall_Log",
            0,0,0);

    G4ThreeVector Position_PMTHousingWall_R = G4ThreeVector((47.75-8.21/2.0)*inch,
            0,
            0.25*inch + 1.0*inch+5.0*mm+0.38*inch+PMTHousingWallLength*0.5);

    G4ThreeVector Position_PMTHousingWall_L = G4ThreeVector(-(47.75-8.21/2.0)*inch,
            0,
            0.25*inch + 1.0*inch+5.0*mm+0.38*inch+PMTHousingWallLength*0.5);

    PMTHousingWallR_Physical   = new G4PVPlacement(0,Position_PMTHousingWall_R + Container_Center,
            PMTHousingWall_Logical,
            "PMTHousingWallR_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

    PMTHousingWallL_Physical   = new G4PVPlacement(0,Position_PMTHousingWall_L + Container_Center,
            PMTHousingWall_Logical,
            "PMTHousingWallL_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

//******************************Define PMT Housing Falange ******************

    G4double PMTHousingFalangeOuterRadius = 7.88*0.5*inch;
    G4double PMTHousingFalangeInnerRadius = 5.75*0.5*inch;
    G4double PMTHousingFalangeLength = 0.75*inch;

    G4Tubs* PMTHousingFalange_Solid = new G4Tubs("PMTHousingFalange_Solid",
            PMTHousingFalangeInnerRadius,
            PMTHousingFalangeOuterRadius,
            0.5 * PMTHousingFalangeLength,
            0.0, 360.0*degree);

    PMTHousingFalange_Logical  = new G4LogicalVolume(PMTHousingFalange_Solid,
            Frame_Material,
            "PMTHousingFalange_Log",
            0,0,0);

    G4ThreeVector Position_PMTHousingFalange_R = G4ThreeVector((47.75-8.21/2.0)*inch,
            0,
            0.25*inch + 1.0*inch+5.0*mm+0.38*inch+PMTHousingWallLength+PMTHousingFalangeLength*0.5);

    G4ThreeVector Position_PMTHousingFalange_L = G4ThreeVector(-(47.75-8.21/2.0)*inch,
            0,
            0.25*inch + 1.0*inch+5.0*mm+0.38*inch+PMTHousingWallLength+PMTHousingFalangeLength*0.5);

    PMTHousingFalangeR_Physical   = new G4PVPlacement(0,Position_PMTHousingFalange_R + Container_Center,
            PMTHousingFalange_Logical,
            "PMTHousingFalangeR_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

    PMTHousingFalangeL_Physical   = new G4PVPlacement(0,Position_PMTHousingFalange_L + Container_Center,
            PMTHousingFalange_Logical,
            "PMTHousingFalangeL_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

//******************************Define PMT Housing Lid *******************************************

    G4double phiStart = 0.0;
    G4double phiTotal = 360*degree;
    G4int    numZPlanes = 9;
    G4double rInner[9] = { 6.5/2.0*inch, 6.5/2.0*inch, 2.52/2.0*inch, 2.52/2.0*inch, 2.52/2.0*inch, 2.52/2.0*inch, 2.52/2.0*inch, 2.52/2.0*inch, 2.52/2.0*inch};
    G4double rOuter[9] = { 7.88/2.0*inch, 7.88/2.0*inch, 7.88/2.0*inch, 7.88/2.0*inch, 2.75/2.0*inch, 2.75/2.0*inch, 3.0/2.0*inch, 3.0/2.0*inch, 2.99/2.0*inch,};
    G4double zPlane[9] = { 0.0, 0.37*inch, 0.38*inch, 0.39*inch, 0.5*inch, 0.69*inch, 0.70*inch, 0.85*inch, 0.86*inch };

    G4Polycone* PMTHousingLid_Solid = new G4Polycone("PMTHousingLid_Soild",
            phiStart,
            phiTotal,
            numZPlanes,
            zPlane,
            rInner,
            rOuter);

    PMTHousingLid_Logical  = new G4LogicalVolume(PMTHousingLid_Solid,
            Frame_Material,
            "PMTHousingLid_Log",
            0,0,0);

    G4ThreeVector Position_PMTHousingLid_R = G4ThreeVector( (47.75-8.21/2.0)*inch,
            0,
            0.25*inch+1.0*inch+5.0*mm+0.38*inch+PMTHousingWallLength+PMTHousingFalangeLength);

    G4ThreeVector Position_PMTHousingLid_L = G4ThreeVector( -(47.75-8.21/2.0)*inch,
            0,
            0.25*inch+1.0*inch+5.0*mm+0.38*inch+PMTHousingWallLength+PMTHousingFalangeLength);

    PMTHousingLidR_Physical   = new G4PVPlacement(0,Position_PMTHousingLid_R + Container_Center,
            PMTHousingLid_Logical,
            "PMTHousingLidR_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

    PMTHousingLidL_Physical   = new G4PVPlacement(0,Position_PMTHousingLid_L + Container_Center,
            PMTHousingLid_Logical,
            "PMTHousingLidL_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

//******************************Define Exo-Skelton Frame*************************

    ExoSkeltonFrame_X = Frame_FullLength_X+0.2*cm;
    ExoSkeltonFrame_Y = Frame_FullLength_Y+6.0*inch;
    ExoSkeltonFrame_Z = 3.0*inch;

    ExoSkeltonInnerFrame_X = ExoSkeltonFrame_X+0.2*mm;
    ExoSkeltonInnerFrame_Y = Frame_FullLength_Y+0.2*cm;
    ExoSkeltonInnerFrame_Z = ExoSkeltonFrame_Z+0.1*mm;  // a bit larger to avoid sharing surface with the outer which may cause vis-problem

    G4Box* ExoSkeltonOuterFrame  = new G4Box("ExoSkeltonOuterFrame",
                                   0.5 * ExoSkeltonFrame_X ,
                                   0.5 * ExoSkeltonFrame_Y ,
                                   0.5 * ExoSkeltonFrame_Z );

    G4Box* ExoSkeltonInnerFrame  = new G4Box("ExoSkeltonInnerFrame",
                                   0.5 * ExoSkeltonInnerFrame_X ,
                                   0.5 * ExoSkeltonInnerFrame_Y ,
                                   0.5 * ExoSkeltonInnerFrame_Z );

    G4SubtractionSolid* ExoSkeltonFrame_Solid = new G4SubtractionSolid("ExoSkeltonOuterFrame-ExoSkeltonInnerFrame", ExoSkeltonOuterFrame, ExoSkeltonInnerFrame);

    ExoSkeltonFrame_Logical  = new G4LogicalVolume(ExoSkeltonFrame_Solid,
                                         Frame_Material,
                                         "ExoSkeltonFrame_Log",
                                         0,0,0);

    G4ThreeVector Position_ExoSkeltonFrame  = G4ThreeVector(0,0,-1.0*inch);

    ExoSkeltonFrame_Physical   = new G4PVPlacement(0,Position_ExoSkeltonFrame + Container_Center,
                                         ExoSkeltonFrame_Logical,
                                         "ExoSkeltonFrame_Physical",
                                         CerenkovContainer_Logical,
                                         false,0,
                                         pSurfChk);


//****************************************************************************************************
    
    
//******************************Define Detector Active Area*******************************************

    G4Box* ActiveArea_Solid  = new G4Box("CerenkoDetector_Solid",
                                         0.5 * ActiveArea_FullLength_X ,
                                         0.5 * ActiveArea_FullLength_Y ,
                                         0.5 * ActiveArea_FullLength_Z );

    ActiveArea_Logical  = new G4LogicalVolume(ActiveArea_Solid,
            ActiveArea_Material,
            "ActiveArea_Log",
            0,0,0);

    G4ThreeVector Position_ActiveArea  = G4ThreeVector(0,0,0);

    ActiveArea_Physical   = new G4PVPlacement(0,Position_ActiveArea + Container_Center,
            ActiveArea_Logical,
            "ActiveArea_Physical",
            CerenkovContainer_Logical,
            false,0,
            pSurfChk);

//****************************************************************************************************
//****************************************************************************************************


    G4double PI = 4.0*std::atan(1.0);
    G4double ChamferRotation = 45.0*PI/180.0;
    G4double ChamferScew = 0.0;
    G4double delta = 0.0;

//****************************************************************************************************
//******************************Define Right Detector Quartz Bar With Chamfers************************


    G4Box* Chamfer_Solid    = new G4Box("Chamfer_Solid",
                                        0.5 * Chamfer_FullLength,       // half X length required by Geant4
                                        0.5 * Chamfer_FullHeight ,      // half Y length required by Geant4
                                        0.5 * Chamfer_FullThickness );

//     G4Box* QuartzBar_Solid  = new G4Box("QuartzBar_Solid",
//                                         0.5 * QuartzBar_FullLength,       // half X length required by Geant4
//                                         0.5 * QuartzBar_FullHeight,      // half Y length required by Geant4
//                                         0.5 * QuartzBar_FullThickness );  // half Z length required by Geant4

   G4Trd* QuartzBar_Solid  = new G4Trd("QuartzBar_Solid",
               0.5*QuartzBar_FullLength,
               0.5*QuartzBar_FullLength,
               0.5*QuartzBar_FullHeight+0.1*cm,
               0.5*QuartzBar_FullHeight-0.1*cm,
               0.5*QuartzBar_FullThickness);

    //Boolean Union:
    //Upper-upstream edge chamfer

    ChamferScew = 0.021486*PI/180.0;
    delta = 0.5*(Chamfer_FullHeight - 1.0*mm)/sqrt(2.0);
    G4double ChamferAdjRotZ = std::atan(sin(ChamferScew)*std::cos(PI/2.0 - ChamferRotation));
    G4double ChamferAdjRotY = std::atan(sin(ChamferScew)*std::sin(PI/2.0 - ChamferRotation));
    Position_Chamfer1.setX(0.0*cm);//33.333333*cm);
    Position_Chamfer1.setY(0.5*QuartzBar_FullHeight + delta);
    Position_Chamfer1.setZ(-(0.5*QuartzBar_FullThickness + delta));
    Rotation_Chamfer1.rotateX(45.0*degree);
    Rotation_Chamfer1.rotateY(ChamferAdjRotY*radian);
    Rotation_Chamfer1.rotateZ(ChamferAdjRotZ*radian);
    G4Transform3D Transform_Chamfer1(Rotation_Chamfer1,Position_Chamfer1);
    Rotation_Chamfer1.rotateZ(-ChamferAdjRotZ*radian);
    Rotation_Chamfer1.rotateY(-ChamferAdjRotY*radian);

    RightQuartz_Solid[0]=  new G4SubtractionSolid ("UpperUpstreamChamfer-RightQuartzBar",
            QuartzBar_Solid,
            Chamfer_Solid,
            Transform_Chamfer1);

    //Boolean Union:
    //Upper-downstream edge chamfer

    delta = 0.5*(Chamfer_FullHeight - 0.5*mm)/sqrt(2.0);
    ChamferScew = 0.0;//0.014*PI/180.0;
    ChamferAdjRotZ = std::atan(sin(ChamferScew)*std::cos(ChamferRotation));
    ChamferAdjRotY = std::atan(sin(ChamferScew)*std::sin(ChamferRotation));
    Position_Chamfer2.setX(0.0*mm);
    Position_Chamfer2.setY(0.5*QuartzBar_FullHeight + delta);
    Position_Chamfer2.setZ(0.5*QuartzBar_FullThickness + delta);
    Rotation_Chamfer2.rotateX(45.0*degree);
    Rotation_Chamfer2.rotateY(-ChamferAdjRotY*radian);
    Rotation_Chamfer2.rotateZ(ChamferAdjRotZ*radian);
    G4Transform3D Transform_Chamfer2(Rotation_Chamfer2,Position_Chamfer2);
    Rotation_Chamfer2.rotateZ(-ChamferAdjRotZ*radian);
    Rotation_Chamfer2.rotateY(ChamferAdjRotY*radian);

    RightQuartz_Solid[1] =  new G4SubtractionSolid ("UpperDownstreamChamfer-RightQuartzBar",
            RightQuartz_Solid[0],
            Chamfer_Solid,
            Transform_Chamfer2);

    //Boolean Union:
    //Lower-Upstream edge chamfer
    ChamferAdjRotZ = std::atan(sin(ChamferScew)*std::cos(ChamferRotation));
    ChamferAdjRotY = std::atan(sin(ChamferScew)*std::sin(ChamferRotation));
    Position_Chamfer3.setX(0.0*mm);
    Position_Chamfer3.setY(-(0.5*QuartzBar_FullHeight + delta));
    Position_Chamfer3.setZ(-(0.5*QuartzBar_FullThickness + delta));
    Rotation_Chamfer3.rotateX(45.0*degree);
    Rotation_Chamfer3.rotateY(ChamferAdjRotY*radian);
    Rotation_Chamfer3.rotateZ(-ChamferAdjRotZ*radian);
    G4Transform3D Transform_Chamfer3(Rotation_Chamfer3,Position_Chamfer3);
    Rotation_Chamfer3.rotateZ(ChamferAdjRotZ*radian);
    Rotation_Chamfer3.rotateY(-ChamferAdjRotY*radian);

    RightQuartz_Solid[2] =  new G4SubtractionSolid ("LowerUpstreamChamfer-RightQuartzBar",
            RightQuartz_Solid[1],Chamfer_Solid,
            Transform_Chamfer3);

    //Boolean Union:
    //Lower-Downstream edge chamfer
    ChamferAdjRotZ = std::atan(sin(ChamferScew)*std::cos(PI/2.0 - ChamferRotation));
    ChamferAdjRotY = std::atan(sin(ChamferScew)*std::sin(PI/2.0 - ChamferRotation));
    Position_Chamfer4.setX(0.0*mm);
    Position_Chamfer4.setY(-(0.5*QuartzBar_FullHeight + delta));
    Position_Chamfer4.setZ(0.5*QuartzBar_FullThickness + delta);
    Rotation_Chamfer4.rotateX(45.0*degree);
    Rotation_Chamfer4.rotateY(-ChamferAdjRotY*radian);
    Rotation_Chamfer4.rotateZ(-ChamferAdjRotZ*radian);
    G4Transform3D Transform_Chamfer4(Rotation_Chamfer4,Position_Chamfer4);
    Rotation_Chamfer4.rotateY(ChamferAdjRotY*radian);
    Rotation_Chamfer4.rotateZ(ChamferAdjRotZ*radian);

    RightQuartz_Solid[3] =  new G4SubtractionSolid ("LowerUpstreamChamfer-RightQuartzBar",
            RightQuartz_Solid[2], Chamfer_Solid,
            Transform_Chamfer4);


    QuartzBar_LogicalRight  = new G4LogicalVolume(RightQuartz_Solid[3],
            QuartzBar_Material,
            "QuartzBar_LogicalRight",
            0,0,0);

    G4ThreeVector Position_RightQuartzBar = G4ThreeVector(-0.5*(QuartzBar_FullLength+GlueFilm_FullLength_X),0,0);

    QuartzBar_PhysicalRight   = new G4PVPlacement(0,Position_RightQuartzBar,
            QuartzBar_LogicalRight,
            "QuartzBar_PhysicalRight",
            ActiveArea_Logical,
            false,0,
            pSurfChk);

//****************************************************************************************************
//****************************************************************************************************

//****************************************************************************************************
//******************************Define Center Quartz Glue Film ***************************************


    G4Box* CenterGlueFilm_Solid    = new G4Box("CenterGlueFilm_Solid",
            0.5 * GlueFilm_FullLength_X,
            0.5 * GlueFilm_FullLength_Y,
            0.5 * GlueFilm_FullLength_Z);

    QuartzGlue_Logical  = new G4LogicalVolume(CenterGlueFilm_Solid,
            QuartzGlue_Material,
            "CenterGlueFilm_Log",
            0,0,0);

    G4ThreeVector Position_CenterGlueFilm = G4ThreeVector(0,0,0);

    QuartzGlue_PhysicalCenter  = new G4PVPlacement(0,Position_CenterGlueFilm,
            QuartzGlue_Logical,
            "QuartzGlue_PhysicalCenter",
            ActiveArea_Logical,
            false,0,
            pSurfChk);

//****************************************************************************************************
//****************************************************************************************************

//****************************************************************************************************
//******************************Define Right Quartz Glue Film ****************************************

    G4ThreeVector Position_RightGlueFilm = G4ThreeVector(-1.0*(QuartzBar_FullLength+GlueFilm_FullLength_X),0,0);

    QuartzGlue_PhysicalRight  = new G4PVPlacement(0,Position_RightGlueFilm,
            QuartzGlue_Logical,
            "QuartzGlue_PhysicalRight",
            ActiveArea_Logical,
            false,1,
            pSurfChk);

//****************************************************************************************************
//****************************************************************************************************

//****************************************************************************************************
//******************************Define Left Detector Quartz Bar With Chamfers  ***********************


    //Boolean Union:
    //Upper-upstream edge chamfer

    ChamferScew = 0.021486*PI/180.0;
    delta = 0.5*(Chamfer_FullHeight - 1.0*mm)/sqrt(2.0);
    ChamferAdjRotZ = std::atan(sin(ChamferScew)*std::cos(PI/2.0 - ChamferRotation));
    ChamferAdjRotY = std::atan(sin(ChamferScew)*std::sin(PI/2.0 - ChamferRotation));
    Position_Chamfer1.setX(0.0*cm);//33.333333*cm);
    Position_Chamfer1.setY(0.5*QuartzBar_FullHeight + delta);
    Position_Chamfer1.setZ(-(0.5*QuartzBar_FullThickness + delta));
//   Rotation_Chamfer1.rotateX(45.0*degree);
    Rotation_Chamfer1.rotateY(ChamferAdjRotY*radian);
    Rotation_Chamfer1.rotateZ(ChamferAdjRotZ*radian);
    G4Transform3D Transform_Chamfer5(Rotation_Chamfer1,Position_Chamfer1);
    Rotation_Chamfer1.rotateZ(-ChamferAdjRotZ*radian);
    Rotation_Chamfer1.rotateY(-ChamferAdjRotY*radian);

    LeftQuartz_Solid[0]=  new G4SubtractionSolid ("UpperUpstreamChamfer-LeftQuartzBar",
            QuartzBar_Solid,
            Chamfer_Solid,
            Transform_Chamfer5);

    //Boolean Union:
    //Upper-downstream edge chamfer

    delta = 0.5*(Chamfer_FullHeight - 0.5*mm)/sqrt(2.0);
    ChamferScew = 0.0;//0.014*PI/180.0;
    ChamferAdjRotZ = std::atan(sin(ChamferScew)*std::cos(ChamferRotation));
    ChamferAdjRotY = std::atan(sin(ChamferScew)*std::sin(ChamferRotation));
    Position_Chamfer2.setX(0.0*mm);
    Position_Chamfer2.setY(0.5*QuartzBar_FullHeight + delta);
    Position_Chamfer2.setZ(0.5*QuartzBar_FullThickness + delta);
//   Rotation_Chamfer2.rotateX(45.0*degree);
    Rotation_Chamfer2.rotateY(-ChamferAdjRotY*radian);
    Rotation_Chamfer2.rotateZ(ChamferAdjRotZ*radian);
    G4Transform3D Transform_Chamfer6(Rotation_Chamfer2,Position_Chamfer2);
    Rotation_Chamfer2.rotateZ(-ChamferAdjRotZ*radian);
    Rotation_Chamfer2.rotateY(ChamferAdjRotY*radian);

    LeftQuartz_Solid[1] =  new G4SubtractionSolid ("UpperDownstreamChamfer-LeftQuartzBar",
            LeftQuartz_Solid[0],
            Chamfer_Solid,
            Transform_Chamfer6);

    //Boolean Union:
    //Lower-Upstream edge chamfer
    ChamferAdjRotZ = std::atan(sin(ChamferScew)*std::cos(ChamferRotation));
    ChamferAdjRotY = std::atan(sin(ChamferScew)*std::sin(ChamferRotation));
    Position_Chamfer3.setX(0.0*mm);
    Position_Chamfer3.setY(-(0.5*QuartzBar_FullHeight + delta));
    Position_Chamfer3.setZ(-(0.5*QuartzBar_FullThickness + delta));
//   Rotation_Chamfer3.rotateX(45.0*degree);
    Rotation_Chamfer3.rotateY(ChamferAdjRotY*radian);
    Rotation_Chamfer3.rotateZ(-ChamferAdjRotZ*radian);
    G4Transform3D Transform_Chamfer7(Rotation_Chamfer3,Position_Chamfer3);
    Rotation_Chamfer3.rotateZ(ChamferAdjRotZ*radian);
    Rotation_Chamfer3.rotateY(-ChamferAdjRotY*radian);

    LeftQuartz_Solid[2] =  new G4SubtractionSolid ("LowerUpstreamChamfer-LeftQuartzBar",
            LeftQuartz_Solid[1],Chamfer_Solid,
            Transform_Chamfer7);

    //Boolean Union:
    //Lower-Downstream edge chamfer
    ChamferAdjRotZ = std::atan(sin(ChamferScew)*std::cos(PI/2.0 - ChamferRotation));
    ChamferAdjRotY = std::atan(sin(ChamferScew)*std::sin(PI/2.0 - ChamferRotation));
    Position_Chamfer4.setX(0.0*mm);
    Position_Chamfer4.setY(-(0.5*QuartzBar_FullHeight + delta));
    Position_Chamfer4.setZ(0.5*QuartzBar_FullThickness + delta);
//   Rotation_Chamfer4.rotateX(45.0*degree);
    Rotation_Chamfer4.rotateY(-ChamferAdjRotY*radian);
    Rotation_Chamfer4.rotateZ(-ChamferAdjRotZ*radian);
    G4Transform3D Transform_Chamfer8(Rotation_Chamfer4,Position_Chamfer4);
    Rotation_Chamfer4.rotateY(ChamferAdjRotY*radian);
    Rotation_Chamfer4.rotateZ(ChamferAdjRotZ*radian);

    LeftQuartz_Solid[3] =  new G4SubtractionSolid ("LowerUpstreamChamfer-LeftQuartzBar",
            LeftQuartz_Solid[2], Chamfer_Solid,
            Transform_Chamfer8);


    QuartzBar_LogicalLeft  = new G4LogicalVolume(LeftQuartz_Solid[3],
            QuartzBar_Material,
            "QuartzBar_LogicalLeft",
            0,0,0);

    G4ThreeVector Position_LeftQuartzBar = G4ThreeVector(0.5*(QuartzBar_FullLength+GlueFilm_FullLength_X),0,0);

    QuartzBar_PhysicalLeft   = new G4PVPlacement(0,Position_LeftQuartzBar,
            QuartzBar_LogicalLeft,
            "QuartzBar_PhysicalLeft",
            ActiveArea_Logical,
            false,0,
            pSurfChk);

//****************************************************************************************************
//****************************************************************************************************

//****************************************************************************************************
//******************************Define Left Quartz Glue Film *****************************************

    G4ThreeVector Position_LeftGlueFilm = G4ThreeVector((QuartzBar_FullLength+GlueFilm_FullLength_X),0,0);

    QuartzGlue_PhysicalLeft  = new G4PVPlacement(0,Position_LeftGlueFilm,
            QuartzGlue_Logical,
            "QuartzGlue_PhysicalLeft",
            ActiveArea_Logical,
            false,1,
            pSurfChk);

//****************************************************************************************************
//****************************************************************************************************

//****************************************************************************************************
//******************************Define Light Guides With Chamfers And Any Sculpting*******************

    G4double redfr = 1.0; //0.5
    G4double pTheta = std::atan(LightGuide_FullThickness*(1 - redfr)/(2.0*LightGuide_FullLength));

    G4Trap* LightGuide_Solid = new G4Trap("LightGuide_Solid",
                                          0.5*LightGuide_FullLength,pTheta,0.0,
                                          0.5*LightGuide_FullWidth1,
                                          redfr*0.5*LightGuide_FullThickness,
                                          redfr*0.5*LightGuide_FullThickness,0.0,
                                          0.5*LightGuide_FullWidth2,
                                          0.5*LightGuide_FullThickness,
                                          0.5*LightGuide_FullThickness,
                                          0.0);

    LGAngCutXDim = 8.0*cm;
    LGAngCutYDim = LightGuide_FullWidth1+1.0*cm;
    LGAngCutZDim = 2.0*cm;

    G4Box* LGEdgeAngleCut_Solid = new G4Box("LGEdgeAngleCut_Solid",
                                            0.5*LGAngCutXDim,
                                            0.5*LGAngCutYDim,
                                            0.5*LGAngCutZDim);
    Double_t ad = 0.0; //45.0;  //0.0;
    Double_t ar = ad*4.0*std::atan(1.0)/180.0;
    Double_t dx = 0.5*LGAngCutZDim*std::cos(ar)-0.5*(LightGuide_FullThickness -
                  LGAngCutZDim*std::sin(ar))*std::tan(ar)
                  + LightGuide_FullThickness*(1 - redfr)*std::tan(ar);



//******************************Left Light Guide *****************************************************

    //Boolean Union:
    //Left Light Guide Angular cut-off at edge
    Position_AngCut1.setX(0.0*cm);
    Position_AngCut1.setY(0.0*cm);
    Position_AngCut1.setZ(-(0.5*LightGuide_FullLength+dx));
    Rotation_AngCut1.rotateY(ad*degree);
    G4Transform3D Transform_AngCut1(Rotation_AngCut1,Position_AngCut1);

    LeftGuide_Solid[0] =  new G4SubtractionSolid ("LGLeft-AngCut",
            LightGuide_Solid,
            LGEdgeAngleCut_Solid,
            Transform_AngCut1);

    delta = 0.5*(Chamfer_FullHeight - 0.5*mm)/sqrt(2.0);

    Position_Chamfer1.setX(-(0.5*QuartzBar_FullThickness + delta));
    Position_Chamfer1.setY(0.5*QuartzBar_FullHeight + delta);
    Position_Chamfer1.setZ(0.0);
    Rotation_Chamfer1.rotateY(90.0*degree);
    G4Transform3D Transform_Chamfer9(Rotation_Chamfer1,Position_Chamfer1);

    LeftGuide_Solid[1]=  new G4SubtractionSolid ("LeftLGChamfer1",
            LeftGuide_Solid[0],
            Chamfer_Solid,
            Transform_Chamfer9);


    Position_Chamfer2.setX(0.5*QuartzBar_FullThickness + delta);
    Position_Chamfer2.setY(0.5*QuartzBar_FullHeight + delta);
    Position_Chamfer2.setZ(0.0*cm);
    Rotation_Chamfer2.rotateY(90.0*degree);
    G4Transform3D Transform_Chamfer10(Rotation_Chamfer2,Position_Chamfer2);

    LeftGuide_Solid[2]=  new G4SubtractionSolid ("LeftLGChamfer2",
            LeftGuide_Solid[1],
            Chamfer_Solid,
            Transform_Chamfer10);


    Position_Chamfer3.setX(0.5*QuartzBar_FullThickness + delta);
    Position_Chamfer3.setY(-(0.5*QuartzBar_FullHeight + delta));
    Position_Chamfer3.setZ(0.0*cm);
    Rotation_Chamfer3.rotateY(90.0*degree);
    G4Transform3D Transform_Chamfer11(Rotation_Chamfer3,Position_Chamfer3);

    LeftGuide_Solid[3]=  new G4SubtractionSolid ("LeftLGChamfer3",
            LeftGuide_Solid[2],
            Chamfer_Solid,
            Transform_Chamfer11);

    Position_Chamfer4.setX(-(0.5*QuartzBar_FullThickness + delta));
    Position_Chamfer4.setY(-(0.5*QuartzBar_FullHeight + delta));
    Position_Chamfer4.setZ(0.0*cm);
    Rotation_Chamfer4.rotateY(90.0*degree);
    G4Transform3D Transform_Chamfer12(Rotation_Chamfer4,Position_Chamfer4);

    LeftGuide_Solid[4]=  new G4SubtractionSolid ("LeftLGChamfer4",
            LeftGuide_Solid[3],
            Chamfer_Solid,
            Transform_Chamfer12);



//******************************Right Light Guide ****************************************************


    //Boolean Union:
    //Right Light Guide Angular cut-off at edge
    Position_AngCut2.setX(0.0*cm);
    Position_AngCut2.setY(0.0*cm);
    Position_AngCut2.setZ(-(0.5*LightGuide_FullLength+dx));
    Rotation_AngCut2.rotateY(-ad*degree);
    G4Transform3D Transform_AngCut2(Rotation_AngCut2,Position_AngCut2);

    RightGuide_Solid[0] =  new G4SubtractionSolid ("LGRight-AngCut",
            LightGuide_Solid,
            LGEdgeAngleCut_Solid,
            Transform_AngCut2);

    G4Transform3D Transform_Chamfer13(Rotation_Chamfer1,Position_Chamfer1);

    RightGuide_Solid[1]=  new G4SubtractionSolid ("RightLGChamfer1",
            RightGuide_Solid[0],
            Chamfer_Solid,
            Transform_Chamfer13);


    G4Transform3D Transform_Chamfer14(Rotation_Chamfer2,Position_Chamfer2);

    RightGuide_Solid[2]=  new G4SubtractionSolid ("RightLGChamfer2",
            RightGuide_Solid[1],
            Chamfer_Solid,
            Transform_Chamfer14);


    G4Transform3D Transform_Chamfer15(Rotation_Chamfer3,Position_Chamfer3);

    RightGuide_Solid[3]=  new G4SubtractionSolid ("RightLGChamfer3",
            RightGuide_Solid[2],
            Chamfer_Solid,
            Transform_Chamfer15);

    G4Transform3D Transform_Chamfer16(Rotation_Chamfer4,Position_Chamfer4);

    RightGuide_Solid[4]=  new G4SubtractionSolid ("RightLGChamfer4",
            RightGuide_Solid[3],
            Chamfer_Solid,
            Transform_Chamfer16);

//****************************************************************************************************
//****************************************************************************************************



    //Boolean Union:
    //Left Light Guide
    Position_LGLeft.setX((QuartzBar_FullLength+0.5*LightGuide_FullLength+1.5*GlueFilm_FullLength_X));
    Position_LGLeft.setY(0.0*cm);
    Position_LGLeft.setZ(0.0*cm - LightGuide_FullThickness*(1 - redfr)/(4.0));
    Rotation_LGLeft.rotateY(-90.0*degree);
    G4Transform3D Transform_LGLeft(Rotation_LGLeft,Position_LGLeft);

    //Boolean Union:
    //Right Light Guide
    Position_LGRight.setX(-(QuartzBar_FullLength+0.5*LightGuide_FullLength+1.5*GlueFilm_FullLength_X));
    Position_LGRight.setY(0.0*cm);
    Position_LGRight.setZ(0.0*cm - LightGuide_FullThickness*(1 - redfr)/(4.0));
//   Rotation_LGRight.rotateY(-90.0*degree);
    Rotation_LGRight.rotateY(90.0*degree);
//   Rotation_LGRight.rotateZ(180.0*degree);
    G4Transform3D Transform_LGRight(Rotation_LGRight,Position_LGRight);


    LightGuide_LogicalLeft  = new G4LogicalVolume(LeftGuide_Solid[4],
            LightGuide_Material,
            "LightGuide_LogicalLeft",
            0,0,0);


    LightGuide_PhysicalLeft = new G4PVPlacement(Transform_LGLeft,
            LightGuide_LogicalLeft,
            "LightGuide_PhysicalLeft",
            ActiveArea_Logical,
            false,0,
            pSurfChk);


    LightGuide_LogicalRight  = new G4LogicalVolume(RightGuide_Solid[4],
            LightGuide_Material,
            "LightGuide_LogicalRight",
            0,0,0);


    LightGuide_PhysicalRight = new G4PVPlacement(Transform_LGRight,
            LightGuide_LogicalRight,
            "LightGuide_PhysicalRight",
            ActiveArea_Logical,
            false,0,
            pSurfChk);


    //******************************Face Mirrors***********************

//   G4Trd* LGFaceMirror_Solid = new G4Trd("LGFaceMirror_Solid",
// 					0.1*mm,0.1*mm,
// 					0.5*LightGuide_FullWidth1,
// 					0.5*LightGuide_FullWidth2,
// 					0.5*LightGuide_FullLength -
// 					0.5*LightGuide_FullThickness*std::tan(ar)+
// 					0.5*LightGuide_FullThickness*(1 - redfr)*std::tan(ar));


//   Position_LGFaceMirrorLeft.setX(0.5*(QuartzBar_FullLength+LightGuide_FullLength)-
// 				 0.5*LightGuide_FullThickness*std::tan(ar)+
// 				 0.5*LightGuide_FullThickness*(1 - redfr)*std::tan(ar));
//   Position_LGFaceMirrorLeft.setY(0.0*cm);
//   Position_LGFaceMirrorLeft.setZ(-0.5*LightGuide_FullThickness - 0.1*mm);
//   Rotation_LGFaceMirrorLeft.rotateY(-90.0*degree);
//   G4Transform3D Transform_LGFMLeft(Rotation_LGFaceMirrorLeft,Position_LGFaceMirrorLeft);


//   mirror_logical[0]  = new G4LogicalVolume(LGFaceMirror_Solid,
// 					   mirror_material,
// 					   "mirrorface_log1",
// 					   0,0,0);

//   mirror_physical[0] = new G4PVPlacement(Transform_LGFMLeft,
// 				     mirror_logical[0],
// 				     "mirrorface_physical1",
// 				     CerenkovContainer_Logical,
// 				     false,
// 				     0, // copy number for left PMTContainer
//                                   pSurfChk);

//******************************Face Mirrors******************


//******************************Edge Mirrors******************

    G4Box* LGEdgeMirror_Solid = new G4Box("LGEdgeMirror_Solid",
                                          0.1*mm,0.5*LightGuide_FullWidth1,
                                          redfr*0.5*LightGuide_FullThickness/std::cos(ar));

    Position_LGEdgeMirrorLeft.setX(1.5*GlueFilm_FullLength_X + QuartzBar_FullLength+LightGuide_FullLength+0.1*mm/std::cos(ar)-
                                   0.5*LightGuide_FullThickness*std::tan(ar)+
                                   0.5*LightGuide_FullThickness*(1 - redfr)*std::tan(ar));
    Position_LGEdgeMirrorLeft.setY(0.0*cm);
    Position_LGEdgeMirrorLeft.setZ(-0.5*LightGuide_FullThickness*(1-redfr));
    Rotation_LGEdgeMirrorLeft.rotateY(ad*degree);
    G4Transform3D Transform_LGEMLeft(Rotation_LGEdgeMirrorLeft,Position_LGEdgeMirrorLeft);


    mirror_logical[1]  = new G4LogicalVolume(LGEdgeMirror_Solid,
            mirror_material,
            "mirrorface_log2",
            0,0,0);

//     mirror_physical[1] = new G4PVPlacement(Transform_LGEMLeft,
//                                            mirror_logical[1],
//                                            "mirrorface_physical2",
//                                            ActiveArea_Logical,
//                                            false,
//                                            0,  // copy number for left PMTContainer
//                                            pSurfChk);

    Position_LGEdgeMirrorRight.setX(-1.5*GlueFilm_FullLength_X-QuartzBar_FullLength-LightGuide_FullLength-0.1*mm/std::cos(ar)+
                                    0.5*LightGuide_FullThickness*std::tan(ar)-
                                    0.5*LightGuide_FullThickness*(1 - redfr)*std::tan(ar));
    Position_LGEdgeMirrorRight.setY(0.0*cm);
    Position_LGEdgeMirrorRight.setZ(-0.5*LightGuide_FullThickness*(1-redfr));
    Rotation_LGEdgeMirrorRight.rotateY(-ad*degree);
    G4Transform3D Transform_LGEMRight(Rotation_LGEdgeMirrorRight,Position_LGEdgeMirrorRight);


    mirror_logical[3]  = new G4LogicalVolume(LGEdgeMirror_Solid,
            mirror_material,
            "mirrorface_log4",
            0,0,0);

//     mirror_physical[3] = new G4PVPlacement(Transform_LGEMRight,
//                                            mirror_logical[3],
//                                            "mirrorface_physical4",
//                                            ActiveArea_Logical,
//                                            false,
//                                            0,
//                                            pSurfChk);

//******************************Edge Mirrors**************************
//********************************************************************



//*********************************************************
//******************************Radiator*******************
    
  G4double Radiator_FullWidth = 8.62*inch;

  G4Box* RadiatorSolid = new G4Box("Radiator_Sol",
				   QuartzBar_FullLength,   // half X length required by Geant4
				   0.5*Radiator_FullWidth, // 0.5*Frame_FullLength_Y // half Y length required by Geant4
				   1.0*cm );  // half Z length required by Geant4

  Radiator_Logical  = new G4LogicalVolume(RadiatorSolid,
					  Radiator_Material,
					  "Radiator_Log",
					  0,0,0);

  G4ThreeVector Position_Radiator  = G4ThreeVector(0, 0,-5.0*cm);//-2.0*cm);

  Radiator_Physical   = new G4PVPlacement(0,Position_Radiator + Container_Center,
					  Radiator_Logical,
					  "Radiator_Physical",
					  CerenkovContainer_Logical,
					  false,
					  0,
					  pSurfChk);

//******************************Radiator****************************
//******************************************************************

//******************************PMT_PbShield*******************

  // Each Pb brick is 8x4x2 [inch], each PMT has 2 Pb bricks, i.e. 8x8x2 [inch]

  G4Box* PMT_PbShieldSolid = new G4Box("PMT_PbShield_Sol",
				   0.5*8.0*inch, // half X length required by Geant4
				   0.5*8.0*inch, // half Y length required by Geant4
				   0.5*2.0*inch );     // half Z length required by Geant4

  PMT_PbShield_Logical  = new G4LogicalVolume(PMT_PbShieldSolid,
					  PMT_PbShield_Material,
					  "PMT_PbShield_Log",
					  0,0,0);

  G4ThreeVector Position_PMT_PbShield_Left   = G4ThreeVector(-100.0*cm-4.0*inch, 0, -6.5*cm);
  G4ThreeVector Position_PMT_PbShield_Right  = G4ThreeVector( 100.0*cm+4.0*inch, 0, -6.5*cm);

  PMT_PbShield_Physical   = new G4PVPlacement(0,Position_PMT_PbShield_Left + Container_Center,
					  PMT_PbShield_Logical,
					  "PMT_PbShield_Physical",
					  CerenkovContainer_Logical,
					  false,
					  0,
                                          pSurfChk);

    PMT_PbShield_Physical   = new G4PVPlacement(0,Position_PMT_PbShield_Right + Container_Center,
					  PMT_PbShield_Logical,
					  "PMT_PbShield_Physical",
					  CerenkovContainer_Logical,
					  false,
					  1,
                                          pSurfChk);
//******************************Radiator****************************

  
    //-----------------------------------
    // define the PMTContainer
    //-----------------------------------

    G4double thetaY = std::atan(LightGuide_FullThickness*(1 - redfr)/(LightGuide_FullLength));
    G4double Xoffs = 0.0*cm;//7.0*cm;

    //Flat on guide face configuration
    G4double PMTContXShift = QuartzBar_FullLength + LightGuide_FullLength - 0.5*PMTEntranceWindow_Diameter - Xoffs;
    G4double PMTContYShift = 0.0;
    G4double PMTContZShift = 0.5*QuartzBar_FullThickness + 0.5*PMTContainer_FullLength_Z
                             - (LightGuide_FullLength - 0.5*PMTEntranceWindow_Diameter-Xoffs)*std::tan(thetaY);

    // relocation of the left Photon Detector Container
    Translation_PMTContainerLeft.setX(1.0*PMTContXShift);
    Translation_PMTContainerLeft.setY(1.0*PMTContYShift);
    Translation_PMTContainerLeft.setZ(1.0*PMTContZShift);

//   //On guide edge configuration
//   Rotation_PMTContainerLeft.rotateY(90.0*degree);

    //Flat on guide face configuration
    Rotation_PMTContainerLeft.rotateY(thetaY);
    G4Transform3D Transform3D_PMTContainerLeft(Rotation_PMTContainerLeft,
            Translation_PMTContainerLeft);

    // relocation of the right Photon Detector Container
    Translation_PMTContainerRight.setX(-1.0*PMTContXShift);
    Translation_PMTContainerRight.setY(1.0*PMTContYShift);
    Translation_PMTContainerRight.setZ(1.0*PMTContZShift);

//   //On guide edge configuration
//   Rotation_PMTContainerLeft.rotateY(-90.0*cm);

    //Flat on guide face configuration
    Rotation_PMTContainerRight.rotateY(-thetaY);
    G4Transform3D Transform3D_PMTContainerRight(Rotation_PMTContainerRight,
            Translation_PMTContainerRight);



    G4double PMTQuartzOpticalFilmZShift = 0.5*(PMTQuartzOpticalFilm_Thickness - PMTContainer_FullLength_Z);

    // relocation of the PMTEntranceWindow
    Translation_PMTQuartzOpticalFilm.setX(0.0*cm);
    Translation_PMTQuartzOpticalFilm.setY(0.0*cm);
    Translation_PMTQuartzOpticalFilm.setZ(PMTQuartzOpticalFilmZShift);

    //-------------------------------------------------------------------------------------
    // location and orientation of the PMT Entrance Window within the PMT Container
    //-------------------------------------------------------------------------------------

    G4double PMTEntWindZShift = 0.5*(PMTEntranceWindow_Thickness - PMTContainer_FullLength_Z)+PMTQuartzOpticalFilm_Thickness;

    // relocation of the PMTEntranceWindow
    Translation_PMTEntranceWindow.setX(0.0*cm);
    Translation_PMTEntranceWindow.setY(0.0*cm);
    Translation_PMTEntranceWindow.setZ(PMTEntWindZShift);

    //-------------------------------------------------------------------------------------
    // location and orientation of the cathode WITHIN the PMT
    //-------------------------------------------------------------------------------------

    G4double CathodeZShift = PMTEntranceWindow_Thickness + 0.5*(Cathode_Thickness - PMTContainer_FullLength_Z) + PMTQuartzOpticalFilm_Thickness;

    // location of the Photon Detector relative to  Photon Detector Container
    Translation_Cathode.setX(0.0*cm);
    Translation_Cathode.setY(0.0*cm);
    Translation_Cathode.setZ(CathodeZShift);


    //   G4Box* PMTContainer_Solid    = new G4Box("PMTContainer_Solid",
    // 					   0.5 * PMTContainer_FullLength_X,   // half X
    // 					   0.5 * PMTContainer_FullLength_Y ,  // half Y
    // 					   0.5 * PMTContainer_FullLength_Z);  // half Z
    G4Tubs* PMTContainer_Solid    = new G4Tubs("PMTContainer_Solid",0.0*cm,
            0.5 * PMTContainer_Diameter,
            0.5 * PMTContainer_FullLength_Z,
            0.0*degree,360.0*degree);


    PMTContainer_Logical  = new G4LogicalVolume(PMTContainer_Solid,
            PMTContainer_Material,
            "PMTContainer_Log",
            0,0,0);

    // left side
    PMTContainer_PhysicalLeft  = new G4PVPlacement(Transform3D_PMTContainerLeft,
            PMTContainer_Logical,
            "PMTContainer_Physical",
            ActiveArea_Logical,
            false,
            0, // copy number for left PMTContainer
            pSurfChk);

    // right side
    PMTContainer_PhysicalRight = new G4PVPlacement(Transform3D_PMTContainerRight,
            PMTContainer_Logical,
            "PMTContainer_Physical",
            ActiveArea_Logical,
            false,
            1, // copy number for right PMTContainer
            pSurfChk);


    //----------------------------------------
    // define the glue or grease or cookie layer
    //----------------------------------------


    G4Tubs* PMTQuartzOpticalFilm_Solid = new G4Tubs("PMTQuartzOpticalFilm_Solid",0.0*cm,
            0.5*PMTQuartzOpticalFilm_Diameter,
            0.5*PMTQuartzOpticalFilm_Thickness,
            0.0*degree,360.0*degree);

    PMTQuartzOpticalFilm_Logical  = new G4LogicalVolume(PMTQuartzOpticalFilm_Solid,
            PMTQuartzOpticalFilm_Material,
            "PMTQuartzOpticalFilm_Log",
            0,0,0);
    PMTQuartzOpticalFilm_Physical = new G4PVPlacement(0,Translation_PMTQuartzOpticalFilm,
            PMTQuartzOpticalFilm_Logical,
            "PMTQuartzOpticalFilm_Physical",
            PMTContainer_Logical,
            false, 0, pSurfChk); // copy number for left photon detector



    //----------------------------------------
    // define the PMTEntranceWindow
    //----------------------------------------

    G4Tubs* PMTEntranceWindow_Solid = new G4Tubs("PMTEntranceWindow_Solid",0.0*cm,
            0.5*PMTEntranceWindow_Diameter,
            0.5*PMTEntranceWindow_Thickness,
            0.0*degree,360.0*degree);

    PMTEntranceWindow_Logical  = new G4LogicalVolume(PMTEntranceWindow_Solid,
            PMTEntranceWindow_Material,
            "PMTEntranceWindow_Log",
            0,0,0);
    PMTEntranceWindow_Physical = new G4PVPlacement(0,Translation_PMTEntranceWindow,
            PMTEntranceWindow_Logical,
            "PMTEntranceWindow_Physical",
            PMTContainer_Logical,
            false, 0, pSurfChk); // copy number for left photon detector

    //---------------------------
    // define the Photon Detector
    //---------------------------

    G4Tubs* Cathode_Solid = new G4Tubs("Cathode_Solid",0.0*cm,0.5*Cathode_Diameter,
                                       0.5*Cathode_Thickness,0.0*degree,360.0*degree);

    Cathode_Logical  = new G4LogicalVolume(Cathode_Solid,Cathode_Material,"Cathode_Log",0,0,0);

    Cathode_Physical = new G4PVPlacement(0,Translation_Cathode,Cathode_Logical,"Cathode_Physical",PMTContainer_Logical,
                                         false, 0, pSurfChk); // copy number for left photon detector





    //=============================================================================================





    //=============================================================================================
    /*
    Position_CerenkovContainer  = G4ThreeVector(Position_CerenkovContainer_X[g],
                                                   Position_CerenkovContainer_Y[g],
                                                   Position_CerenkovContainer_Z[g]);

       // define Rotation matrix for Container orientated in MotherVolume
       Rotation_CerenkovContainer =  new G4RotationMatrix();
       Rotation_CerenkovContainer -> rotateX(Tilting_Angle);

       CerenkovContainer_Physical   = new G4PVPlacement(Rotation_CerenkovContainer,
                                                   Position_CerenkovContainer + Container_Center,
                                                   "CerenkovContainer_Physical",
                                                   CerenkovContainer_Logical,
                                                   MotherVolume,
                                                   false,
                                                   0,
                                                   pSurfChk);
     */
    //}
//----------------------------------------------


    //============================================================================
    // place the 8 CerenkovMasterContainer_Physical into the physical MotherVolume
    //============================================================================
    //
    PlacePVCerenkovMasterContainer();


// Setting Optical Properties

    const G4int nEntries = 11;
    G4double PhotonEnergy[nEntries] = {
        1.54986*eV,  //800.59 nm
        1.77127*eV,  //700.51 nm
        2.06648*eV,  //600.44 nm
        2.47978*eV,  //500.37 nm
        2.8178*eV,   //440.34 nm
        3.09973*eV,  //400.29 nm
        3.5424*eV,   //350.27 nm
        4.13297*eV,  //300.22 nm
        4.95956*eV,  //250.18 nm
        5.51063*eV,  //225.16 nm
        5.90424*eV   //210.15 nm
    };

    G4double Reflectivity[nEntries];
    G4double mylambda;
    for (G4int kk= 0; kk < nEntries; kk++) {
        // Nevens empiric formular for the reflectivity
        // lamda = h*c/E

        mylambda = (h_Planck*c_light/PhotonEnergy[kk])/nanometer;
        Reflectivity[kk] =  1.0 - 0.027*exp(-0.004608*mylambda);
        //Reflectivity[kk] =  1.0;
    };

    G4OpticalSurface* QuartzBarLeft_OpticalSurface = new G4OpticalSurface("QuartzBarLeftOpticalSurface");
    G4OpticalSurface* QuartzBarRight_OpticalSurface = new G4OpticalSurface("QuartzBarRightOpticalSurface");
    G4OpticalSurface* LightGuideLeft_OpticalSurface = new G4OpticalSurface("LightGuideLeftOpticalSurface");
    G4OpticalSurface* LightGuideRight_OpticalSurface = new G4OpticalSurface("LightGuideRightOpticalSurface");

    G4OpticalSurface* GlueFilmCenter_OpticalSurface = new G4OpticalSurface("GlueFilmCenterOpticalSurface");
    G4OpticalSurface* GlueFilmLeft_OpticalSurface = new G4OpticalSurface("GlueFilmLeftOpticalSurface");
    G4OpticalSurface* GlueFilmRight_OpticalSurface = new G4OpticalSurface("GlueFilmRightOpticalSurface");


/* wdc: commented out unused objects

    G4LogicalBorderSurface* QuartzBarLeft_BorderSurface
    = new G4LogicalBorderSurface("QuartzBarLeft_BorderSurface",
                                 QuartzBar_PhysicalLeft,
                                 ActiveArea_Physical,
                                 QuartzBarLeft_OpticalSurface);

    G4LogicalBorderSurface* QuartzBarRight_BorderSurface
    = new G4LogicalBorderSurface("QuartzBarRight_BorderSurface",
                                 QuartzBar_PhysicalRight,
                                 ActiveArea_Physical,
                                 QuartzBarRight_OpticalSurface);

    G4LogicalBorderSurface* LightGuideLeft_BorderSurface
    = new G4LogicalBorderSurface("LightGuideLeft_BorderSurface",
                                 LightGuide_PhysicalLeft,
                                 ActiveArea_Physical,
                                 LightGuideLeft_OpticalSurface);

    G4LogicalBorderSurface* LightGuideRight_BorderSurface
    = new G4LogicalBorderSurface("LightGuideRight_BorderSurface",
                                 LightGuide_PhysicalRight,
                                 ActiveArea_Physical,
                                 LightGuideRight_OpticalSurface);

    G4LogicalBorderSurface* GlueFilmRight_BorderSurface
    = new G4LogicalBorderSurface("GlueFilmRight_BorderSurface",
                                 QuartzGlue_PhysicalRight,
                                 ActiveArea_Physical,
                                 GlueFilmRight_OpticalSurface);

    G4LogicalBorderSurface* GlueFilmCenter_BorderSurface
    = new G4LogicalBorderSurface("GlueFilmCenter_BorderSurface",
                                 QuartzGlue_PhysicalCenter,
                                 ActiveArea_Physical,
                                 GlueFilmCenter_OpticalSurface);

    G4LogicalBorderSurface* GlueFilmLeft_BorderSurface
    = new G4LogicalBorderSurface("GlueFilmLeft_BorderSurface",
                                 QuartzGlue_PhysicalLeft,
                                 ActiveArea_Physical,
                                 GlueFilmLeft_OpticalSurface);
*/

// boundary optical properties between pad and quartz

    G4OpticalSurface* LeftEndPad_Quartz_OpticalSurface = new G4OpticalSurface("LeftEndPadQuartzOpticalSurface");
    G4OpticalSurface* RightEndPad_Quartz_OpticalSurface = new G4OpticalSurface("RightEndPadQuartzOpticalSurface");
    G4OpticalSurface* SidePad_LeftLightGuide_OpticalSurface
                                         = new G4OpticalSurface("SidePadLeftLightGuideOpticalSurface");
    G4OpticalSurface* SidePad_RightLightGuide_OpticalSurface
                                         = new G4OpticalSurface("SidePadRightLightGuideOpticalSurface");
    G4OpticalSurface* SidePad_QuartzBarLeft_OpticalSurface
                                         = new G4OpticalSurface("SidePadQuartzBarLeftOpticalSurface");
    G4OpticalSurface* SidePad_QuartzBarRight_OpticalSurface
                                         = new G4OpticalSurface("SidePadQuartzBarRightOpticalSurface");

    for(size_t i=0; i<EndBracketPad_Physical.size();i++) {
      
/* wdc: commented out unused objects

    //G4LogicalBorderSurface* LeftEndPad_Quartz_BorderSurface =
    new G4LogicalBorderSurface("LeftEndPad_Quartz_BS",
                                 LightGuide_PhysicalLeft,
                                 EndBracketPad_Physical[i],
                                 LeftEndPad_Quartz_OpticalSurface);

    //G4LogicalBorderSurface* RightEndPad_Quartz_BorderSurface =
    new G4LogicalBorderSurface("RightEndPad_Quartz_BS",
                                 LightGuide_PhysicalRight,
                                 EndBracketPad_Physical[i],
                                 RightEndPad_Quartz_OpticalSurface);
*/
    }

    for(size_t i=0; i<SideBracketPad_Physical.size();i++) {

/* wdc: commented out unused objects

    //G4LogicalBorderSurface* SidePad_LeftLightGuide_BorderSurface =
    new G4LogicalBorderSurface("SidePad_LeftLightGuide_BS",
                                 LightGuide_PhysicalLeft,
                                 SideBracketPad_Physical[i],
                                 SidePad_LeftLightGuide_OpticalSurface);

    //G4LogicalBorderSurface* SidePad_RightLightGuide_BorderSurface =
    new G4LogicalBorderSurface("SidePad_RightLightGuide_BS",
                                 LightGuide_PhysicalRight,
                                 SideBracketPad_Physical[i],
                                 SidePad_RightLightGuide_OpticalSurface);

    //G4LogicalBorderSurface* SidePad_QuartzBarLeft_BorderSurface =
    new G4LogicalBorderSurface("SidePad_QuartzBarLeft_BS",
                                 QuartzBar_PhysicalLeft,
                                 SideBracketPad_Physical[i],
                                 SidePad_QuartzBarLeft_OpticalSurface);

    //G4LogicalBorderSurface* SidePad_QuartzBarRight_BorderSurface =
    new G4LogicalBorderSurface("SidePad_QuartzBarRight_BS",
                                 QuartzBar_PhysicalRight,
                                 SideBracketPad_Physical[i],
                                 SidePad_QuartzBarRight_OpticalSurface);

*/
    }

    QuartzBarLeft_OpticalSurface->SetType(dielectric_dielectric);
    QuartzBarLeft_OpticalSurface->SetFinish(polished);
    QuartzBarLeft_OpticalSurface->SetPolish(0.997);
    QuartzBarLeft_OpticalSurface->SetModel(glisur);

    QuartzBarRight_OpticalSurface->SetType(dielectric_dielectric);
    QuartzBarRight_OpticalSurface->SetFinish(polished);
    QuartzBarRight_OpticalSurface->SetPolish(0.997);
    QuartzBarRight_OpticalSurface->SetModel(glisur);

    LightGuideLeft_OpticalSurface->SetType(dielectric_dielectric);
    LightGuideLeft_OpticalSurface->SetFinish(polished);
    LightGuideLeft_OpticalSurface->SetPolish(0.997);
    LightGuideLeft_OpticalSurface->SetModel(glisur);

    LightGuideRight_OpticalSurface->SetType(dielectric_dielectric);
    LightGuideRight_OpticalSurface->SetFinish(polished);
    LightGuideRight_OpticalSurface->SetPolish(0.997);
    LightGuideRight_OpticalSurface->SetModel(glisur);

    GlueFilmLeft_OpticalSurface->SetType(dielectric_dielectric);
    GlueFilmLeft_OpticalSurface->SetFinish(polished);
    GlueFilmLeft_OpticalSurface->SetPolish(0.9);
    GlueFilmLeft_OpticalSurface->SetModel(glisur);

    GlueFilmCenter_OpticalSurface->SetType(dielectric_dielectric);
    GlueFilmCenter_OpticalSurface->SetFinish(polished);
    GlueFilmCenter_OpticalSurface->SetPolish(0.9);
    GlueFilmCenter_OpticalSurface->SetModel(glisur);

    GlueFilmRight_OpticalSurface->SetType(dielectric_dielectric);
    GlueFilmRight_OpticalSurface->SetFinish(polished);
    GlueFilmRight_OpticalSurface->SetPolish(0.9);
    GlueFilmRight_OpticalSurface->SetModel(glisur);


//##############################################

    G4OpticalSurface* BracketPad_OpticalSurface = 
                         new G4OpticalSurface("BracketPad_Optical_Surface");
    BracketPad_OpticalSurface->SetType(dielectric_metal);
    BracketPad_OpticalSurface->SetFinish(ground);
    BracketPad_OpticalSurface->SetModel(glisur);
    new G4LogicalSkinSurface("SideBracketPad_SkinSurface",SideBracketPad_Logical,BracketPad_OpticalSurface);
    new G4LogicalSkinSurface("EndBracketPad_SkinSurface",EndBracketPad_Logical,BracketPad_OpticalSurface);

    G4double Pad_Reflectivity[nEntries]={0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
    G4MaterialPropertiesTable *BracketPad_MPT = new G4MaterialPropertiesTable();
    BracketPad_MPT->AddProperty("REFLECTIVITY",PhotonEnergy,Pad_Reflectivity,nEntries);
    BracketPad_OpticalSurface->SetMaterialPropertiesTable(BracketPad_MPT);

    LeftEndPad_Quartz_OpticalSurface->SetType(dielectric_metal);
    LeftEndPad_Quartz_OpticalSurface->SetFinish(polished);
    LeftEndPad_Quartz_OpticalSurface->SetPolish(0.9);
    LeftEndPad_Quartz_OpticalSurface->SetModel(glisur);
    LeftEndPad_Quartz_OpticalSurface->SetMaterialPropertiesTable(BracketPad_MPT);

    RightEndPad_Quartz_OpticalSurface->SetType(dielectric_metal);
    RightEndPad_Quartz_OpticalSurface->SetFinish(polished);
    LeftEndPad_Quartz_OpticalSurface->SetPolish(0.9);
    RightEndPad_Quartz_OpticalSurface->SetModel(glisur);
    RightEndPad_Quartz_OpticalSurface->SetMaterialPropertiesTable(BracketPad_MPT);

    SidePad_LeftLightGuide_OpticalSurface->SetType(dielectric_metal);
    SidePad_LeftLightGuide_OpticalSurface->SetFinish(polished);
    LeftEndPad_Quartz_OpticalSurface->SetPolish(0.9);
    SidePad_LeftLightGuide_OpticalSurface->SetModel(glisur);
    SidePad_LeftLightGuide_OpticalSurface->SetMaterialPropertiesTable(BracketPad_MPT);

    SidePad_RightLightGuide_OpticalSurface->SetType(dielectric_metal);
    SidePad_RightLightGuide_OpticalSurface->SetFinish(polished);
    LeftEndPad_Quartz_OpticalSurface->SetPolish(0.9);
    SidePad_RightLightGuide_OpticalSurface->SetModel(glisur);
    SidePad_RightLightGuide_OpticalSurface->SetMaterialPropertiesTable(BracketPad_MPT);

    SidePad_QuartzBarLeft_OpticalSurface->SetType(dielectric_metal);
    SidePad_QuartzBarLeft_OpticalSurface->SetFinish(polished);
    LeftEndPad_Quartz_OpticalSurface->SetPolish(0.9);
    SidePad_QuartzBarLeft_OpticalSurface->SetModel(glisur);
    SidePad_QuartzBarLeft_OpticalSurface->SetMaterialPropertiesTable(BracketPad_MPT);

    SidePad_QuartzBarRight_OpticalSurface->SetType(dielectric_metal);
    SidePad_QuartzBarRight_OpticalSurface->SetFinish(polished);
    LeftEndPad_Quartz_OpticalSurface->SetPolish(0.9);
    SidePad_QuartzBarRight_OpticalSurface->SetModel(glisur);
    SidePad_QuartzBarRight_OpticalSurface->SetMaterialPropertiesTable(BracketPad_MPT);

//#####################################################3

    G4MaterialPropertiesTable *quartzST = new G4MaterialPropertiesTable();
    quartzST->AddProperty("REFLECTIVITY",  PhotonEnergy , Reflectivity, nEntries);
    QuartzBarLeft_OpticalSurface->SetMaterialPropertiesTable(quartzST);
    QuartzBarRight_OpticalSurface->SetMaterialPropertiesTable(quartzST);
    LightGuideLeft_OpticalSurface->SetMaterialPropertiesTable(quartzST);
    LightGuideRight_OpticalSurface->SetMaterialPropertiesTable(quartzST);
    GlueFilmRight_OpticalSurface->SetMaterialPropertiesTable(quartzST);

    G4OpticalSurface* ActiveArea_OpticalSurface = new G4OpticalSurface("ActiveAreaOpticalSurface");
//     G4LogicalBorderSurface* ActiveArea_BorderSurface
//                             = new G4LogicalBorderSurface("ActiveArea_BorderSurface",
//                                                          ActiveArea_Physical,
//                                                          CerenkovMasterContainer_Physical,
//                                                          ActiveArea_OpticalSurface);

    ActiveArea_OpticalSurface->SetFinish(groundbackpainted); //new for wrapping test
//   ActiveArea_OpticalSurface->SetPolish(0.0);          //new for wrapping test
//   ActiveArea_OpticalSurface->SetModel(glisur);    	 //new for wrapping test
    ActiveArea_OpticalSurface->SetModel(unified);         //new for wrapping test
    ActiveArea_OpticalSurface->SetSigmaAlpha(0.25);        //new for wrapping test

    // for wrapping test
    G4double RefractiveIndex_Air[nEntries] = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
    G4double MilliPoreRefl[nEntries]       = {0.94,0.94,0.945,0.945,0.95,0.95,0.945,0.91,0.85,0.80,0.80};
    G4double specularlobe[nEntries]        = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
    G4double specularspike[nEntries]       = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};
    G4double backscatter[nEntries]         = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};

    G4MaterialPropertiesTable *myST = new G4MaterialPropertiesTable();

    myST->AddProperty("RINDEX",  PhotonEnergy , RefractiveIndex_Air, nEntries);     //new for wrapping test
    myST->AddProperty("REFLECTIVITY",  PhotonEnergy , MilliPoreRefl, nEntries);     //new for wrapping test
    myST->AddProperty("SPECULARLOBECONSTANT", PhotonEnergy ,specularlobe,nEntries); //new for wrapping test
    myST->AddProperty("SPECULARSPIKECONSTANT",PhotonEnergy,specularspike,nEntries); //new for wrapping test
    myST->AddProperty("BACKSCATTERCONSTANT",PhotonEnergy,backscatter,nEntries);     //new for wrapping test
//   myST->AddProperty("ABSLENGTH", PhotonEnergy, AbsorptionCoeff_Air, nEntries);    //new for wrapping test

    ActiveArea_OpticalSurface->SetMaterialPropertiesTable(myST);

    // Set Optical Properties for the Detector Windows
    G4OpticalSurface* Window_OpticalSurface = new G4OpticalSurface("Window_Optical_Surface");
    Window_OpticalSurface->SetType(dielectric_metal);
    Window_OpticalSurface->SetFinish(ground);
    Window_OpticalSurface->SetModel(glisur);
    new G4LogicalSkinSurface("FrontWindow_SkinSurface",FrontWindow_Logical,Window_OpticalSurface);
    new G4LogicalSkinSurface("BackWindow_SkinSurface",BackWindow_Logical,Window_OpticalSurface);

    G4double Tyvek_Reflectivity[nEntries]={0.95,0.95,0.95,0.95,0.95,0.95,0.95,0.90,0.90,0.85,0.85};
    G4MaterialPropertiesTable *Window_MPT = new G4MaterialPropertiesTable();
    Window_MPT->AddProperty("REFLECTIVITY",PhotonEnergy,Tyvek_Reflectivity,nEntries);
    Window_OpticalSurface->SetMaterialPropertiesTable(Window_MPT);

// set bracket optical properties
    G4OpticalSurface* Bracket_OpticalSurface = 
                         new G4OpticalSurface("Bracket_Optical_Surface");
    Bracket_OpticalSurface->SetType(dielectric_metal);
    Bracket_OpticalSurface->SetFinish(ground);
    Bracket_OpticalSurface->SetModel(glisur);
    new G4LogicalSkinSurface("SideBracket_SkinSurface",SideBracket_Logical,Bracket_OpticalSurface);
    new G4LogicalSkinSurface("EndBracket_SkinSurface",EndBracket_Logical,Bracket_OpticalSurface);

    G4double Bracket_Reflectivity[nEntries]={0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8};
    G4MaterialPropertiesTable *Bracket_MPT = new G4MaterialPropertiesTable();
    Bracket_MPT->AddProperty("REFLECTIVITY",PhotonEnergy,Bracket_Reflectivity,nEntries);
    Bracket_OpticalSurface->SetMaterialPropertiesTable(Bracket_MPT);


    //Setting Skin Optical Properties for GlueFilm
    G4OpticalSurface* GlueFilm_OpticalSurface = new G4OpticalSurface("GlueFilmOpticalSurface");
    GlueFilm_OpticalSurface->SetType(dielectric_dielectric);
    GlueFilm_OpticalSurface->SetFinish(polished);
    GlueFilm_OpticalSurface->SetPolish(0.9);
    GlueFilm_OpticalSurface->SetModel(glisur);
    new G4LogicalSkinSurface("GlueFilm_SkinSurface",QuartzGlue_Logical,GlueFilm_OpticalSurface);

    //Setting the Optical Properties of PMTs

    // peiqing, Dec. 20, 2011
    // if QE is processed in EventAction, set it to 100% here
    G4double Photocathode_Efficiency[nEntries]={0.0080,      //800.59 nm
                                          0.0298,      //700.51 nm
                                          0.0638,      //600.44 nm
                                          0.1240,      //500.37 nm
                                          0.1670,      //440.34 nm
                                          0.1770,      //400.29 nm
                                          0.1800,      //350.27 nm
                                          0.2110,      //300.22 nm
                                          0.1780,      //250.18 nm
                                          0.0890,      //225.16 nm
                                          0.0355       //210.15 nm
                                         };

//         G4double Photocathode_Efficiency[nEntries]={1,      //800.59 nm
//                                           1,      //700.51 nm
//                                           1,      //600.44 nm
//                                           1,      //500.37 nm
//                                           1,      //440.34 nm
//                                           1,      //400.29 nm
//                                           1,      //350.27 nm
//                                           1,      //300.22 nm
//                                           1,      //250.18 nm
//                                           1,      //225.16 nm
//                                           1       //210.15 nm
//                                          };
					 
//S20 reflectance taken from "Optics Communications, issue 180, 2000. p89–102"
//average of 40 degree incident angle assumed
////data below 400 nm, taken from //http://www.photek.com/support/Papers/
//Experimental%20data%20on%20the%20reflection%20and%20transmission%20spectral%20response%20of%20photocathodes.pdf
    G4double Photocathode_Reflectivity[nEntries]={
                                                  0.25, //800 nm
                                                  0.25, //700 nm
                                                  0.25, //600 nm
                                                  0.25, //500 nm
                                                  0.25, //440 nm
                                                  0.25, //400 nm
                                                  0.25, //350 nm
                                                  0.25, //300 nm
                                                  0.25, //250 nm
                                                  0.25, //225 nm
                                                  0.25  //210 nm
                                                  };

  G4OpticalSurface* Photocathode_OpticalSurface =  new G4OpticalSurface("Photocathode_OS");
  Photocathode_OpticalSurface ->SetType(dielectric_metal); 
  Photocathode_OpticalSurface ->SetFinish(polished); 
  Photocathode_OpticalSurface ->SetModel(glisur); 

    G4MaterialPropertiesTable* Photocathode_MPT = new G4MaterialPropertiesTable();
    Photocathode_MPT->AddProperty("REFLECTIVITY", PhotonEnergy, Photocathode_Reflectivity,nEntries);
    Photocathode_MPT->AddProperty("EFFICIENCY", PhotonEnergy, Photocathode_Efficiency,nEntries);
    Photocathode_OpticalSurface ->SetMaterialPropertiesTable(Photocathode_MPT);

    new G4LogicalBorderSurface("PMT_BorderSurface",
                               PMTEntranceWindow_Physical,
                               Cathode_Physical,
                               Photocathode_OpticalSurface);

    // Setting Sensitive detectors
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    CerenkovDetectorSD = new QweakSimCerenkov_DetectorSD("/CerenkovDetectorSD");
    SDman->AddNewDetector(CerenkovDetectorSD);
    ActiveArea_Logical->SetSensitiveDetector(CerenkovDetectorSD);

    CerenkovDetector_PMTSD = new QweakSimCerenkovDetector_PMTSD("/CerenkovPMTSD",myUserInfo);
    SDman->AddNewDetector(CerenkovDetector_PMTSD);
    Cathode_Logical->SetSensitiveDetector(CerenkovDetector_PMTSD);


    // Setting Vis Attributes
    G4cout << G4endl << "###### QweakSimCerenkovDetector: Setting Vis Attributes " << G4endl << G4endl;

    G4Colour  orange    ( 255/255., 127/255.,   0/255.);
    G4Colour  blue      (   0/255.,   0/255., 255/255.);
    G4Colour  magenta   ( 255/255.,   0/255., 255/255.);
    G4Colour  grey      ( 127/255., 127/255., 127/255.);
    G4Colour  lightblue   ( 139/255., 208/255., 255/255.);
    G4Colour  lightorange ( 255/255., 189/255., 165/255.);
    G4Colour  khaki3    ( 205/255., 198/255., 115/255.);
    G4Colour  brown     (178/255., 102/255., 26/255.);
    G4Colour  darkbrown     (100/255., 50/255., 10/255.);

//------------------------------------------
// Visual Attributes for:  Radiator
//------------------------------------------
    G4VisAttributes* RadiatorVisAtt = new G4VisAttributes(lightblue);
    RadiatorVisAtt->SetVisibility(true);
    Radiator_Logical->SetVisAttributes(RadiatorVisAtt);
    
    G4VisAttributes* PMT_PbShieldVisAtt = new G4VisAttributes(blue);
    PMT_PbShieldVisAtt->SetVisibility(true);
    PMT_PbShield_Logical->SetVisAttributes(PMT_PbShieldVisAtt);    
//------------------------------------------
// Visual Attributes for:  CerenkovContainer
//------------------------------------------
    G4VisAttributes* CerenkovContainerVisAtt = new G4VisAttributes(blue);
    CerenkovContainerVisAtt->SetVisibility(false);
//CerenkovContainerVisAtt->SetVisibility(true);
//CerenkovContainerVisAtt->SetForceWireframe(true);
//CerenkovContainerVisAtt->SetForceSolid(true);
    CerenkovContainer_Logical->SetVisAttributes(CerenkovContainerVisAtt);
    ActiveArea_Logical->SetVisAttributes(CerenkovContainerVisAtt);

//Visual Attributes for:  Exo-Skelton
    G4VisAttributes* ExoSkeltonFrameVisAtt = new G4VisAttributes(darkbrown);
    ExoSkeltonFrameVisAtt->SetVisibility(true);
//FrameVisAtt->SetForceWireframe(true);
//FrameVisAtt->SetForceSolid(true);
    ExoSkeltonFrame_Logical->SetVisAttributes(ExoSkeltonFrameVisAtt);
    
//------------------------------------------
// Visual Attributes for:  Detector Housing
//------------------------------------------
    G4VisAttributes* FrameVisAtt = new G4VisAttributes(grey);
    FrameVisAtt->SetVisibility(true);
//FrameVisAtt->SetForceWireframe(true);
//FrameVisAtt->SetForceSolid(true);
    Frame_Logical->SetVisAttributes(FrameVisAtt);

//------------------------------------------
// Visual Attributes for:  Side Brackets
//------------------------------------------
    G4VisAttributes* SideBracketVisAtt = new G4VisAttributes(blue);
    SideBracketVisAtt->SetVisibility(true);
//SideBracketVisAtt->SetForceWireframe(true);
//SideBracketVisAtt->SetForceSolid(true);
    SideBracket_Logical->SetVisAttributes(SideBracketVisAtt);

//------------------------------------------
// Visual Attributes for:  End Brackets
//------------------------------------------
    G4VisAttributes* EndBracketVisAtt = new G4VisAttributes(blue);
    EndBracketVisAtt->SetVisibility(true);
//EndBracketVisAtt->SetForceWireframe(true);
//EndBracketVisAtt->SetForceSolid(true);
    EndBracket_Logical->SetVisAttributes(EndBracketVisAtt);

//------------------------------------------
// Visual Attributes for:  Side Bracket Pads
//------------------------------------------
    G4VisAttributes* SideBracketPadVisAtt = new G4VisAttributes(brown);
    SideBracketPadVisAtt->SetVisibility(true);
//SideBracketPadVisAtt->SetForceWireframe(true);
    SideBracketPadVisAtt->SetForceSolid(true);
    SideBracketPad_Logical->SetVisAttributes(SideBracketPadVisAtt);

//------------------------------------------
// Visual Attributes for:  End Bracket Pads
//------------------------------------------
    G4VisAttributes* EndBracketPadVisAtt = new G4VisAttributes(brown);
    EndBracketPadVisAtt->SetVisibility(true);
//EndBracketPadVisAtt->SetForceWireframe(true);
EndBracketPadVisAtt->SetForceSolid(true);
    EndBracketPad_Logical->SetVisAttributes(EndBracketPadVisAtt);


//------------------------------------------
// Visual Attributes for:  Detector Window Clip
//------------------------------------------
    G4VisAttributes* ClipVisAtt = new G4VisAttributes(lightorange);
    ClipVisAtt->SetVisibility(true);
//ClipVisAtt->SetForceWireframe(true);
//ClipVisAtt->SetForceSolid(true);
    FrontClip_Logical->SetVisAttributes(ClipVisAtt);
    BackClip_Logical->SetVisAttributes(ClipVisAtt);

//-----------------------------------------
// Visual Attributes for:  CerenkovDetector
//-----------------------------------------
    G4VisAttributes* CerenkovDetectorVisAtt = new G4VisAttributes(orange);
    CerenkovDetectorVisAtt->SetVisibility(true);
// Needed for the correct visualization using Coin3D
//CerenkovDetectorVisAtt->SetForceSolid(true);
    CerenkovDetectorVisAtt->SetForceWireframe(true);
//  ActiveArea_Logical->SetVisAttributes(CerenkovDetectorVisAtt);
    QuartzBar_LogicalLeft->SetVisAttributes(CerenkovDetectorVisAtt);
    QuartzBar_LogicalRight->SetVisAttributes(CerenkovDetectorVisAtt);
    LightGuide_LogicalLeft->SetVisAttributes(CerenkovDetectorVisAtt);
    LightGuide_LogicalRight->SetVisAttributes(CerenkovDetectorVisAtt);
    QuartzGlue_Logical->SetVisAttributes(CerenkovDetectorVisAtt);

//------------------------------------------------
// Visual Attributes for:  PMTContainer
//------------------------------------------------
    G4VisAttributes* PMTContainerVisAtt = new G4VisAttributes(blue);
    PMTContainerVisAtt->SetVisibility(true);
    PMTContainerVisAtt->SetForceWireframe(true);
//PMTContainerVisAtt->SetForceSolid(true);
    PMTContainer_Logical->SetVisAttributes(PMTContainerVisAtt);

//-----------------------------------------------------
// Visual Attributes for:  PMTEntranceWindow
//-----------------------------------------------------
    G4VisAttributes* PMTEntranceWindowVisAtt = new G4VisAttributes(grey);
    PMTEntranceWindowVisAtt->SetVisibility(true);
//PMTEntranceWindowVisAtt->SetForceWireframe(true);
    PMTEntranceWindowVisAtt->SetForceSolid(true);
    PMTEntranceWindow_Logical->SetVisAttributes(PMTEntranceWindowVisAtt);

//---------------------------------------
// Visual Attributes for:  PMT
//---------------------------------------
    G4VisAttributes* PMTVisAtt = new G4VisAttributes(magenta);
    PMTVisAtt->SetVisibility(true);
//PMTVisAtt->SetForceWireframe(true);
    PMTVisAtt->SetForceSolid(true);
    Cathode_Logical->SetVisAttributes(PMTVisAtt);

    G4cout << G4endl << "###### Leaving QweakSimCerenkovDetector::ConstructComponent() " << G4endl << G4endl;

} // end of  QweakSimCerenkovDetector::ConstructComponent()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimCerenkovDetector::SetCerenkovDetectorMaterial(G4String materialName) {
    // search the material by its name
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial) {
        QuartzBar_LogicalLeft->SetMaterial(pttoMaterial);
        QuartzBar_LogicalRight->SetMaterial(pttoMaterial);
        LightGuide_LogicalLeft->SetMaterial(pttoMaterial);
        LightGuide_LogicalRight->SetMaterial(pttoMaterial);
        QuartzGlue_Logical->SetMaterial(pttoMaterial);
    } else {
        G4cerr << "==== ERROR: Changing Cerenkov Detector Material failed" << G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkovDetector::SetNumberOfDetectors(G4int number)
{
  // Delete pointers if resizing to something smaller
  if (number < NumberOfCerenkovDetectors) {
    for (size_t k = number; k < CerenkovDetectorMessenger.size(); k++) {
      delete CerenkovDetectorMessenger[k];
      delete CerenkovMasterContainer_Physical[k];
      delete Rotation_CerenkovMasterContainer[k];
    }
  }

  // Set number of detectors
  NumberOfCerenkovDetectors = number;

  // Resize objects and fill with zeros
  CerenkovDetectorMessenger.resize(NumberOfCerenkovDetectors,0);
  CerenkovMasterContainer_Physical.resize(NumberOfCerenkovDetectors,0);
  Rotation_CerenkovMasterContainer.resize(NumberOfCerenkovDetectors,0);
  Translation_CerenkovMasterContainer.resize(NumberOfCerenkovDetectors);

  // Resize positions and set to default values
  Position_CerenkovContainer_X.resize(NumberOfCerenkovDetectors,Default_Position_CerenkovContainer_X);
  Position_CerenkovContainer_Y.resize(NumberOfCerenkovDetectors,Default_Position_CerenkovContainer_Y);
  Position_CerenkovContainer_Z.resize(NumberOfCerenkovDetectors,Default_Position_CerenkovContainer_Z);

  // Creates a messenger for each of the new Cerenkov detectors
  for(size_t k = 0; k < CerenkovDetectorMessenger.size(); k++) {
    if (CerenkovDetectorMessenger[k] == 0) {
      CerenkovDetectorMessenger[k] = new QweakSimCerenkovDetectorMessenger(this, k);
    }
  }

  // Update geometry
  CerenkovGeometryPVUpdate();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimCerenkovDetector::SetPreradiatorMaterial(G4String materialName) {

    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial) {
        Radiator_Logical->SetMaterial(pttoMaterial);
    } else {
        G4cerr << "==== ERROR: Changing Preradiator Material failed" << G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimCerenkovDetector::SetContainerMaterial(G4String materialName) {

    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial) {
        CerenkovContainer_Logical->SetMaterial(pttoMaterial);
    } else {
        G4cerr << "==== ERROR: Changing Container Material failed" << G4endl;
    }

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimCerenkovDetector::DestroyComponent() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkovDetector::SetCerenkovDetectorThickness(G4double /*thickness*/) {
    G4cout << G4endl << "###### Calling QweakSimCerenkovDetector::SetCerenkovDetectorThickness() " << G4endl << G4endl;

//     G4Box *box = NULL;

//     Thickness = thickness;

//     if(CerenkovDetector_Logical)
//       box = (G4Box*)CerenkovDetector_Logical->GetSolid();
//     if(box)
//       box->SetZHalfLength(0.5*Thickness);

//     if(PMTContainer_Logical)
//       box = (G4Box*)PMTContainer_Logical->GetSolid();
//     if(box)
//       box->SetZHalfLength(0.5*Thickness);

//     if(PMTEntranceWindow_Logical)
//       box = (G4Box*)PMTEntranceWindow_Logical->GetSolid();
//     if(box)
//       box->SetZHalfLength(0.5*Thickness);

//     if(Cathode_Logical)
//       box = (G4Box*)Cathode_Logical->GetSolid();
//     if(box)
//       box->SetZHalfLength(0.5*Thickness);

//     G4RunManager::GetRunManager()->GeometryHasBeenModified();

    G4cout << G4endl << "###### Leaving QweakSimCerenkovDetector::SetCerenkovDetectorThickness() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkovDetector::SetCerenkovDetectorCenterPositionInX(G4double xPos, G4int octant) {
    G4cout << G4endl << "###### Calling QweakSimCerenkovDetector::SetCerenkovCenterPositionInX() " << G4endl << G4endl;

    Position_CerenkovContainer_X[octant] =xPos;

    CerenkovGeometryPVUpdate();

    G4cout << G4endl << "###### Leaving QweakSimCerenkovDetector::SetCerenkovCenterPositionInX() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkovDetector::SetCerenkovDetectorCenterPositionInY(G4double yPos, G4int octant) {
    G4cout << G4endl << "###### Calling QweakSimCerenkovDetector::SetCerenkovCenterPositionInY() " << G4endl << G4endl;

    Position_CerenkovContainer_Y[octant] = yPos;

    CerenkovGeometryPVUpdate();

    G4cout << G4endl << "###### Leaving QweakSimCerenkovDetector::SetCerenkovCenterPositionInY() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkovDetector::SetCerenkovDetectorCenterPositionInZ(G4double zPos, G4int octant) {
    G4cout << G4endl << "###### Calling QweakSimCerenkovDetector::SetCerenkovCenterPositionInZ() " << G4endl << G4endl;

    Position_CerenkovContainer_Z[octant] = zPos-Container_Center_Z;

    CerenkovGeometryPVUpdate();

    G4cout << G4endl << "###### Leaving QweakSimCerenkovDetector::SetCerenkovCenterPositionInZ() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkovDetector::SetCerenkovDetectorTiltAngle(G4double tiltangle) {
    G4cout << G4endl << "###### Calling QweakSimCerenkovDetector::SetCerenkovDetectorTiltAngle() " << G4endl << G4endl;

    // assign new tilting
    Tilting_Angle = tiltangle;

    CerenkovGeometryPVUpdate();

    G4cout << G4endl << "###### Leaving QweakSimCerenkovDetector::SetCerenkovDetectorTiltAngle() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkovDetector::CerenkovGeometryPVUpdate() {
    G4cout << G4endl << "###### Calling QweakSimCerenkovDetector::CerenkovGeometryPVUpdate()" << G4endl << G4endl;

    for (size_t i=0; i< CerenkovMasterContainer_Physical.size();i++) {
        if (CerenkovContainer_Logical)
          CerenkovContainer_Logical->RemoveDaughter(CerenkovMasterContainer_Physical[i]);

        delete CerenkovMasterContainer_Physical[i];
        CerenkovMasterContainer_Physical[i] = 0;

        delete Rotation_CerenkovMasterContainer[i];
        Rotation_CerenkovMasterContainer[i] = 0;
    }

    // Place the physical volume of the rods with the new phi angle
    PlacePVCerenkovMasterContainer();

    G4cout << G4endl << "###### Leaving QweakSimCerenkovDetector::CerenkovGeometryPVUpdate()" << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCerenkovDetector::PlacePVCerenkovMasterContainer() {
    // place 8  CerenkovContainer_Logical plates into the MotherVolume (around the global Z axis)
    for (size_t i = 0; i < Rotation_CerenkovMasterContainer.size(); i++) {

        // Phi angles of the 8 cerenkovs
        G4double AnglePhi_CerenkovMasterContainer = i * 45.0*degree;

        // since the CerenkovMasterContainer_Logical is defined for a vertical orientation
        // but the translation assumes a horizontal orientation, we have to subtract 90*deg
        Rotation_CerenkovMasterContainer[i] = new G4RotationMatrix();
        Rotation_CerenkovMasterContainer[i]->rotateZ(-AnglePhi_CerenkovMasterContainer + 90*degree);
        Rotation_CerenkovMasterContainer[i]->rotateX(Tilting_Angle);

        // set the vectors to the center of the CerenkovContainer
        // located at 12 o'clock. Then rotate the centerVector to the 8
        // positions and extract the new vector components
        // This procedure is easier than the calculation by hand for individual positions/orientations

        // define 12' o'clock start location
        G4ThreeVector centerVector;
        centerVector.setX(Position_CerenkovContainer_X[i]);
        centerVector.setY(Position_CerenkovContainer_Y[i]);
        centerVector.setZ(Position_CerenkovContainer_Z[i]);

        // rotate centerVector to the 8 positions
        centerVector.rotateZ(-AnglePhi_CerenkovMasterContainer);

        Translation_CerenkovMasterContainer[i].setX(centerVector.y());
        Translation_CerenkovMasterContainer[i].setY(centerVector.x());
        Translation_CerenkovMasterContainer[i].setZ(centerVector.z());

        CerenkovMasterContainer_Physical[i]   = new G4PVPlacement(
                Rotation_CerenkovMasterContainer[i],
                Translation_CerenkovMasterContainer[i],
                "CerenkovMasterContainer_Physical",
                CerenkovContainer_Logical,
                theMotherPV,
                false,
                i,
                pSurfChk);

    } // end of  for (size_t i=0; i < n; i++)
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

