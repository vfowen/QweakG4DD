
// QweakSimPMTOnly.cc
// Marty McHugh 
// 2013-06-11

/////// --------------------------------------------------------------------

#include "QweakSimPMTOnly.hh"

//--- geant4 includes
#include "G4RunManager.hh"
#include "G4VisAttributes.hh"

//--- user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimPMTOnlyMessenger.hh"
#include "QweakSimPMTOnly_DetectorSD.hh"
#include "QweakSimPMTOnly_PMTSD.hh"
#include "QweakSimUserInformation.hh"

/////// --------------------------------------------------------------------

QweakSimPMTOnly::QweakSimPMTOnly(QweakSimUserInformation* userInfo)
{
    //--- Initialize Pointers
    myUserInfo		= userInfo;

    PMTOnlySD         	= NULL;
    PMTOnly_PMTSD	= NULL;
	
    PMTOnlyMessenger   	= NULL;
	
    pMaterial           = NULL;
    
    PMTOnlyContainer_Solid 	= NULL;
    PMTOnlyContainer_Logical	= NULL;
    PMTOnlyContainer_Physical	= NULL;
    PMTOnlyContainer_Material 	= NULL;
    PMTOnlyContainer_VisAtt	= NULL;

    PMTOnly_Solid     	= NULL;
    PMTOnly_Logical   	= NULL;
    PMTOnly_Physical  	= NULL;	
    PMTOnly_Material  	= NULL;
    PMTOnly_VisAtt    	= NULL;
    
    PMTOnlyQuartzOpticalFilm_Solid 	= NULL;
    PMTOnlyQuartzOpticalFilm_Logical	= NULL;
    PMTOnlyQuartzOpticalFilm_Physical	= NULL;
    PMTOnlyQuartzOpticalFilm_Material	= NULL;
    
    PMTOnlyEntranceWindow_Solid	= NULL;
    PMTOnlyEntranceWindow_Logical	= NULL;
    PMTOnlyEntranceWindow_Physical	= NULL;
    PMTOnlyEntranceWindow_Material	= NULL;
    
    PMTOnlyCathode_Solid	= NULL;
    PMTOnlyCathode_Logical	= NULL;
    PMTOnlyCathode_Physical	= NULL;
    PMTOnlyCathode_Material	= NULL;
    
    //--- Set Initial Values
    MD5_CenterPosition_X = -335.17*cm;
    MD5_CenterPosition_Y =     0.0*cm;
    MD5_CenterPosition_Z =  577.88*cm;

    PMTOnlyContainer_FullLength_X = 20.00*cm;
    PMTOnlyContainer_FullLength_Y = 20.00*cm;
    PMTOnlyContainer_FullLength_Z = 20.00*cm;

    PMTOnlyContainer_CenterPosition_X =  -320.0*cm; 	// Default:-320 cm
    PMTOnlyContainer_CenterPosition_Y =  -50.00*cm;	// Default: -50 cm
    PMTOnlyContainer_CenterPosition_Z =  775.00*cm;	// Default: 775 cm

    //--- All following coordinates are w.r.t.
    //--- the center of the Mother Volume.

    PMTOnly_FullLength_X = 18.00*cm;
    PMTOnly_FullLength_Y = 18.00*cm;
    PMTOnly_FullLength_Z = 1.25*cm;
    
    PMTOnly_CenterPosition_X =  0.00*cm;
    PMTOnly_CenterPosition_Y =  0.00*cm;
    PMTOnly_CenterPosition_Z =  0.00*cm;

    PMTOnlyContainer_TiltAngle_X =  0.00*degree;
    PMTOnlyContainer_TiltAngle_Y =  0.00*degree;
    PMTOnlyContainer_TiltAngle_Z =  0.00*degree;
    
    PMTOnlyQuartzOpticalFilm_Diameter = 12.70*cm;
    PMTOnlyQuartzOpticalFilm_Thickness = 0.10*mm;
    
    PMTOnlyQuartzOpticalFilm_X = 0.0*cm;
    PMTOnlyQuartzOpticalFilm_Y = 0.0*cm;
    PMTOnlyQuartzOpticalFilm_Z = 0.5*(PMTOnly_FullLength_Z + PMTOnlyQuartzOpticalFilm_Thickness);

    PMTOnlyEntranceWindow_Diameter = 12.70*cm;
    PMTOnlyEntranceWindow_Thickness = 1.00*mm;

    PMTOnlyEntranceWindow_X = 0.0*cm;
    PMTOnlyEntranceWindow_Y = 0.0*cm;
    PMTOnlyEntranceWindow_Z = PMTOnlyQuartzOpticalFilm_Z 
                             + 0.5*(PMTOnlyQuartzOpticalFilm_Thickness+PMTOnlyEntranceWindow_Thickness);

    G4double ReductionInPhotoPMTOnlyCathodeDiameter = 5*mm;
    
    PMTOnlyCathode_Thickness   = 1.0*mm;
    PMTOnlyCathode_Diameter    = PMTOnlyEntranceWindow_Diameter - ReductionInPhotoPMTOnlyCathodeDiameter; 

    PMTOnlyCathode_X = 0.0*cm;
    PMTOnlyCathode_Y = 0.0*cm;
    PMTOnlyCathode_Z = PMTOnlyEntranceWindow_Z 
                       + 0.5*(PMTOnlyEntranceWindow_Thickness + PMTOnlyCathode_Thickness);

    PMTOnlyMessenger = new QweakSimPMTOnlyMessenger(this);
	
    pMaterial = new QweakSimMaterial();
    pMaterial->DefineMaterials();  
	
}


/////// --------------------------------------------------------------------

QweakSimPMTOnly::~QweakSimPMTOnly()
{
    /* --- Delete Pointers	
    if (PMTOnlySD)		delete PMTOnlySD;

    if (pMaterial)		delete pMaterial;
    if (PMTOnlyMessenger)	delete PMTOnlyMessenger;
    
    if (PMTOnlyContainer_Solid)		delete PMTOnlyContainer_Solid;
    if (PMTOnlyContainer_Logical)	delete PMTOnlyContainer_Logical;
    if (PMTOnlyContainer_Physical)	delete PMTOnlyContainer_Physical;
    if (PMTOnlyContainer_Material)	delete PMTOnlyContainer_Material;
    if (PMTOnlyContainer_VisAtt)	delete PMTOnlyContainer_VisAtt;
    
    if (PMTOnly_VisAtt)		delete PMTOnly_VisAtt;
    if (PMTOnly_Material)	delete PMTOnly_Material;	
    if (PMTOnly_Physical)	delete PMTOnly_Physical;
    if (PMTOnly_Logical)	delete PMTOnly_Logical;
    if (PMTOnly_Solid)		delete PMTOnly_Solid;
    
    if (PMTOnlyQuartzOpticalFilm_Material)	delete PMTOnlyQuartzOpticalFilm_Material;	
    if (PMTOnlyQuartzOpticalFilm_Physical)	delete PMTOnlyQuartzOpticalFilm_Physical;
    if (PMTOnlyQuartzOpticalFilm_Logical)	delete PMTOnlyQuartzOpticalFilm_Logical;
    if (PMTOnlyQuartzOpticalFilm_Solid)	delete PMTOnlyQuartzOpticalFilm_Solid;
    
    if (PMTOnlyEntranceWindow_Material)	delete PMTOnlyEntranceWindow_Material;	
    if (PMTOnlyEntranceWindow_Physical)	delete PMTOnlyEntranceWindow_Physical;
    if (PMTOnlyEntranceWindow_Logical)	delete PMTOnlyEntranceWindow_Logical;
    if (PMTOnlyEntranceWindow_Solid)	delete PMTOnlyEntranceWindow_Solid;
    
    if (PMTOnlyCathode_Material)	delete PMTOnlyCathode_Material;	
    if (PMTOnlyCathode_Physical)	delete PMTOnlyCathode_Physical;
    if (PMTOnlyCathode_Logical)	delete PMTOnlyCathode_Logical;
    if (PMTOnlyCathode_Solid)		delete PMTOnlyCathode_Solid;
    */	
}


/////// --------------------------------------------------------------------

void QweakSimPMTOnly::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
	
    //--- Materials
    PMTOnlyContainer_Material 		= pMaterial->GetMaterial("Air");    
    PMTOnly_Material 		        = pMaterial->GetMaterial("Quartz");
    PMTOnlyQuartzOpticalFilm_Material  = pMaterial->GetMaterial("SiElast_Glue");
    PMTOnlyEntranceWindow_Material 	= pMaterial->GetMaterial("LimeGlass");
    PMTOnlyCathode_Material 		= pMaterial->GetMaterial("Photocathode");

    //--- Define Mother Solid Volume;
    PMTOnlyContainer_Solid = new G4Box("PMTOnlyContainer_Solid",
    				0.5*PMTOnlyContainer_FullLength_X,
    				0.5*PMTOnlyContainer_FullLength_Y,
    				0.5*PMTOnlyContainer_FullLength_Z);
    				
    //--- Define Mother Logical Volume;
    PMTOnlyContainer_Logical = new G4LogicalVolume(PMTOnlyContainer_Solid,
                                            PMTOnlyContainer_Material,
                                            "PMTOnlyContainer_Logical",
                                             0,0,0);
    
    //--- Define Mother Placement and Physical Volume
    PMTOnlyContainer_CenterPosition = G4ThreeVector(PMTOnlyContainer_CenterPosition_X,
                                          PMTOnlyContainer_CenterPosition_Y,
                                          PMTOnlyContainer_CenterPosition_Z);
    PMTOnlyContainer_RotationMatrix = new G4RotationMatrix();
    PMTOnlyContainer_RotationMatrix -> rotateX(PMTOnlyContainer_TiltAngle_X);
	
    PMTOnlyContainer_Physical = new G4PVPlacement(PMTOnlyContainer_RotationMatrix,
                                        PMTOnlyContainer_CenterPosition,
                                        "PMTOnlyContainer_Physical",
                                        PMTOnlyContainer_Logical,
                                        MotherVolume,
                                        false,
                                        0);
	
    //--- Define PMTOnly Solid Volume	
    PMTOnly_Solid = new G4Box("PMTOnly_Solid",
                              0.5*PMTOnly_FullLength_X,     // X Length
                              0.5*PMTOnly_FullLength_Y,     // Y Length
                              0.5*PMTOnly_FullLength_Z);    // Z Length
	
    //--- Define PMTOnly Logical Volume	
    PMTOnly_Logical = new G4LogicalVolume(PMTOnly_Solid,
                                          PMTOnly_Material,
                                          "PMTOnly_Logical",
                                          0,0,0);
	
    //--- Define PMTOnly Physical Volume
    PMTOnly_CenterPosition = G4ThreeVector(PMTOnly_CenterPosition_X,
                                           PMTOnly_CenterPosition_Y,
                                           PMTOnly_CenterPosition_Z);

    PMTOnly_Physical = new G4PVPlacement(0,
                                         PMTOnly_CenterPosition,
                                         "PMTOnly_Physical",
                                         PMTOnly_Logical,
                                         PMTOnlyContainer_Physical,
                                         false,
                                         0);

    
    //--- Define PMTOnlyQuartzOpticalFilm Solid
    PMTOnlyQuartzOpticalFilm_Solid = new G4Tubs("PMTOnlyQuartzOpticalFilm_Solid", 
                                                0.00*cm,
                                                0.5*PMTOnlyQuartzOpticalFilm_Diameter,
                                                0.5*PMTOnlyQuartzOpticalFilm_Thickness,
                                                0.0*degree,
                                                360.0*degree);

    //--- Define PMTOnlyQuartzOpticaFilm Logical
    PMTOnlyQuartzOpticalFilm_Logical = new G4LogicalVolume(PMTOnlyQuartzOpticalFilm_Solid,
    						           PMTOnlyQuartzOpticalFilm_Material,
    						           "PMTOnlyQuartzOpticalFilm_Logical");
    
    //--- Define PMTOnlyQuartzOpticalFilm Physical Volume & Placement.
    G4ThreeVector PMTOnlyQuartzOpticalFilm_Position(PMTOnlyQuartzOpticalFilm_X,
                                                    PMTOnlyQuartzOpticalFilm_Y,
                                                    PMTOnlyQuartzOpticalFilm_Z); 
    
    PMTOnlyQuartzOpticalFilm_Physical = new G4PVPlacement(0,
    						          PMTOnlyQuartzOpticalFilm_Position,
    						          "PMTOnlyQuartzOpticalFilm_Physical",
    						          PMTOnlyQuartzOpticalFilm_Logical,    						   
    						          PMTOnlyContainer_Physical,
    						          false, 
    						          0);

    //--- Define PMTOnlyEntranceWindow Solid
    PMTOnlyEntranceWindow_Solid = new G4Tubs("PMTOnlyEntranceWindow_Solid",
    					     0.00*cm,
    					     0.5*PMTOnlyEntranceWindow_Diameter,
    					     0.5*PMTOnlyEntranceWindow_Thickness,
    					     0.0*degree, 
    					     360.0*degree);

    //--- Define PMTOnlyEntranceWindow Logical
    PMTOnlyEntranceWindow_Logical = new G4LogicalVolume(PMTOnlyEntranceWindow_Solid,
    						        PMTOnlyEntranceWindow_Material,
    						        "PMTOnlyEntranceWindow_Logical");

    //--- Define PMTOnlyEntranceWindow Physical Volume & Placement
    G4ThreeVector PMTOnlyEntranceWindow_Position(PMTOnlyEntranceWindow_X,
    						 PMTOnlyEntranceWindow_Y,
    						 PMTOnlyEntranceWindow_Z);

    PMTOnlyEntranceWindow_Physical = new G4PVPlacement(0,
    						       PMTOnlyEntranceWindow_Position,
    						       "PMTOnlyEntranceWindow_Physical",
    						       PMTOnlyEntranceWindow_Logical,
    						       PMTOnlyContainer_Physical,
    						       false,
    						       0);

    //--- Define PMTOnlyCathode Solid
    PMTOnlyCathode_Solid = new G4Tubs("PMTOnlyCathode_Solid",
			       	      0.00*cm,
			              0.5*PMTOnlyCathode_Diameter,
			              0.5*PMTOnlyCathode_Thickness,
			              0.0*degree,
			              360.0*degree);

    //--- Define PMTOnlyCathode Logical
    PMTOnlyCathode_Logical = new G4LogicalVolume(PMTOnlyCathode_Solid,
    					         PMTOnlyCathode_Material,
    					         "PMTOnlyCathode_Logical");

    //--- Define PMTOnlyCathode Placement & Physical Volume
    G4ThreeVector PMTOnlyCathode_Position(PMTOnlyCathode_X,
    					  PMTOnlyCathode_Y,
    					  PMTOnlyCathode_Z);
    
    PMTOnlyCathode_Physical = new G4PVPlacement(0,
    						PMTOnlyCathode_Position,
    						"PMTOnlyCathode_Physical",
	    					PMTOnlyCathode_Logical,
    						PMTOnlyContainer_Physical,
    						false,
    						0);

    ////////////////////////////
    //	Optical Photon Stuff  //
    ////////////////////////////
    
    // All code below copied from QweakSimCerenkov.cc
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

    G4double PhotoPMTOnlyCathode_Efficiency[nEntries] = {
        0.0080,      //800.59 nm
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
    
    G4double PhotoPMTOnlyCathode_Reflectivity[nEntries] = {
        0.25, 	//800 nm
        0.25, 	//700 nm
        0.25, 	//600 nm
        0.25, 	//500 nm
        0.25,	//440 nm
        0.25,	//400 nm
        0.25,	//350 nm
        0.25,	//300 nm
        0.25,	//250 nm
        0.25,	//225 nm
        0.25 	//210 nm
    };

    G4double Reflectivity[nEntries];
    for (G4int kk= 0; kk < nEntries; kk++) {
        G4double mylambda = (h_Planck*c_light/PhotonEnergy[kk])/nanometer;

        // Nevens empiric formular for the reflectivity
        Reflectivity[kk] =  1.0 - 0.027*exp(-0.004608*mylambda);	        
    };
    
    G4OpticalSurface* LightGuide_OpticalSurface = new G4OpticalSurface("LightGuideOpticalSurface");
    LightGuide_OpticalSurface->SetType(dielectric_dielectric);
    LightGuide_OpticalSurface->SetFinish(polished);
    LightGuide_OpticalSurface->SetPolish(0.997);
    LightGuide_OpticalSurface->SetModel(glisur);
    
    G4MaterialPropertiesTable *quartzST = new G4MaterialPropertiesTable();
    quartzST->AddProperty("REFLECTIVITY",  PhotonEnergy , Reflectivity, nEntries);
    LightGuide_OpticalSurface->SetMaterialPropertiesTable(quartzST);

    G4OpticalSurface* PhotoPMTOnlyCathode_OpticalSurface =  new G4OpticalSurface("PhotoPMTOnlyCathode_OS");
    PhotoPMTOnlyCathode_OpticalSurface ->SetType(dielectric_metal); 
    PhotoPMTOnlyCathode_OpticalSurface ->SetFinish(polished); 
    PhotoPMTOnlyCathode_OpticalSurface ->SetModel(glisur);

    G4MaterialPropertiesTable* PhotoPMTOnlyCathode_MPT = new G4MaterialPropertiesTable();
    PhotoPMTOnlyCathode_MPT->AddProperty("REFLECTIVITY", PhotonEnergy, PhotoPMTOnlyCathode_Reflectivity,nEntries);
    PhotoPMTOnlyCathode_MPT->AddProperty("EFFICIENCY", PhotonEnergy, PhotoPMTOnlyCathode_Efficiency,nEntries);
    PhotoPMTOnlyCathode_OpticalSurface->SetMaterialPropertiesTable(PhotoPMTOnlyCathode_MPT);

    new G4LogicalBorderSurface("PMT_BorderSurface",
                               PMTOnlyEntranceWindow_Physical,
                               PMTOnlyCathode_Physical,
                               PhotoPMTOnlyCathode_OpticalSurface);

    					
    ////////////////////////////////////
    // Define Visulization Attributes //
    ////////////////////////////////////
    
    PMTOnlyContainer_VisAtt = new G4VisAttributes(G4Colour::White());
    PMTOnlyContainer_VisAtt->SetVisibility(true);
    PMTOnlyContainer_VisAtt->SetForceWireframe(true);
    PMTOnlyContainer_Logical->SetVisAttributes(PMTOnlyContainer_VisAtt);

    PMTOnly_VisAtt = new G4VisAttributes(G4Colour::Blue());
    PMTOnly_VisAtt->SetVisibility(true);
    PMTOnly_Logical->SetVisAttributes(PMTOnly_VisAtt);

    G4VisAttributes* QuartzGlueFilm_VisAtt = new G4VisAttributes(G4Colour::White());
    QuartzGlueFilm_VisAtt->SetVisibility(true);
    PMTOnlyQuartzOpticalFilm_Logical->SetVisAttributes(QuartzGlueFilm_VisAtt);
    
    G4VisAttributes* PMTOnlyEntranceWindow_VisAtt = new G4VisAttributes(G4Colour::Grey());
    PMTOnlyEntranceWindow_VisAtt->SetVisibility(true);
    PMTOnlyEntranceWindow_Logical->SetVisAttributes(PMTOnlyEntranceWindow_VisAtt);
    
    G4VisAttributes* PMTOnlyCathode_VisAtt = new G4VisAttributes(G4Colour::Magenta());
    PMTOnlyCathode_VisAtt->SetVisibility(true);
    PMTOnlyCathode_Logical->SetVisAttributes(PMTOnlyCathode_VisAtt);

    ///////////////////////////////////////////
    // Define Sensitive Detectors to PMTOnly //
    ///////////////////////////////////////////
    
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    PMTOnlySD = new QweakSimPMTOnly_DetectorSD("PMTOnlySD");
    SDman -> AddNewDetector(PMTOnlySD);
    PMTOnly_Logical -> SetSensitiveDetector(PMTOnlySD);

    PMTOnly_PMTSD = new QweakSimPMTOnly_PMTSD("PMTOnly_PMTSD", myUserInfo);
    SDman -> AddNewDetector(PMTOnly_PMTSD);
    PMTOnlyCathode_Logical -> SetSensitiveDetector(PMTOnly_PMTSD);

}


/////// --------------------------------------------------------------------

void QweakSimPMTOnly::DestroyComponent()
{
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_Material(G4String materialName)
{
    //--- Set PMTOnly Material
	
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    
    if (pttoMaterial)
    {
        G4cout << "=== Changing PMTOnly material: Look up material " << G4endl;
        PMTOnly_Logical -> SetMaterial(pttoMaterial);
        G4cout << "=== Changing PMTOnly material: Now the material is " << materialName << G4endl;
    }
    else 
        G4cerr << "=== Error: Changing PMTOnly material FAILED! " << G4endl << G4endl;

}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_CenterPositionInX(G4double xPos)
{
    //--- Set PMTOnly X Position
	
    G4cout << "=== Calling QweakSimPMTOnly::SetPMTOnly_CenterPositionInX() " << G4endl;
    PMTOnlyContainer_CenterPosition_X = xPos;
    PMTOnlyContainer_Physical->SetTranslation(G4ThreeVector(PMTOnlyContainer_CenterPosition_X,
                                                     PMTOnlyContainer_CenterPosition_Y,
                                                     PMTOnlyContainer_CenterPosition_Z));
    G4cout << "=== Leaving QweakSimPMTOnly::SetPMTOnly_CenterPositionInX() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_CenterPositionInY(G4double yPos)
{    
    //--- Set PMTOnly Y Position
	
    G4cout << "=== Calling QweakSimPMTOnly::SetPMTOnly_CenterPositionInY() " << G4endl;
    PMTOnlyContainer_CenterPosition_Y = yPos;
    PMTOnlyContainer_Physical->SetTranslation(G4ThreeVector(PMTOnlyContainer_CenterPosition_X,
                                                     PMTOnlyContainer_CenterPosition_Y,
                                                     PMTOnlyContainer_CenterPosition_Z));
    G4cout << "=== Leaving QweakSimPMTOnly::SetPMTOnly_CenterPositionInY() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_CenterPositionInZ(G4double zPos)
{
    //--- Set PMTOnly Z Position
	
    G4cout << "=== Calling QweakSimPMTOnly::SetPMTOnly_CenterPositionInZ() " << G4endl;
    PMTOnlyContainer_CenterPosition_Z = zPos;
    PMTOnlyContainer_Physical->SetTranslation(G4ThreeVector(PMTOnlyContainer_CenterPosition_X,
                                                     PMTOnlyContainer_CenterPosition_Y,
                                                     PMTOnlyContainer_CenterPosition_Z));
    G4cout << "=== Leaving QweakSimPMTOnly::SetPMTOnly_CenterPositionInZ() " << G4endl << G4endl;
}


/////// --------------------------------------------------------------------

void QweakSimPMTOnly::FindPMTOnly_MotherCenter()
{
    //--- Find PMTOnly Center Position
    G4double x = GetPMTOnly_CenterPositionInX();
    G4double y = GetPMTOnly_CenterPositionInY();
    G4double z = GetPMTOnly_CenterPositionInZ();
    
    G4cout << "PMTOnly_X: " << x << G4endl;
    G4cout << "PMTOnly_Y: " << y << G4endl;
    G4cout << "PMTOnly_Z: " << z << G4endl;
}

/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_TiltAngleInX(G4double xTiltAngle)
{
    //--- Set PMTOnly New X Tilting Angle
	
    G4cout << G4endl << "=== Calling QweakSimPMTOnly::SetPMTOnly_TiltAngleInX() " << G4endl;
	
    //--- rotate back with old angle
    PMTOnlyContainer_RotationMatrix->rotateX(-1.0*PMTOnlyContainer_TiltAngle_X);
    PMTOnlyContainer_Physical->SetRotation(PMTOnlyContainer_RotationMatrix);
	
    //--- assign new tilting angle
    PMTOnlyContainer_TiltAngle_X = xTiltAngle;
	
    //--- rotate to new angle
    PMTOnlyContainer_RotationMatrix->rotateX(PMTOnlyContainer_TiltAngle_X);
    PMTOnlyContainer_Physical->SetRotation(PMTOnlyContainer_RotationMatrix);
	
    G4cout << G4endl << "=== Leaving QweakSimPMTOnly::SetPMTOnly_TiltAngleInX() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_TiltAngleInY(G4double yTiltAngle)
{
    //--- Set PMTOnly New Y Tilting Angle
	
    G4cout << G4endl << "=== Calling QweakSimPMTOnly::SetPMTOnly_TiltAngleInY() " << G4endl;
	
    //--- rotate back with old angle
    PMTOnlyContainer_RotationMatrix->rotateY(-1.0*PMTOnlyContainer_TiltAngle_Y);
    PMTOnlyContainer_Physical->SetRotation(PMTOnlyContainer_RotationMatrix);
	
    //--- assign new tilting angle
    PMTOnlyContainer_TiltAngle_Y = yTiltAngle;
	
    //--- rotate to new angle
    PMTOnlyContainer_RotationMatrix->rotateY(PMTOnlyContainer_TiltAngle_Y);
    PMTOnlyContainer_Physical->SetRotation(PMTOnlyContainer_RotationMatrix);
	
    G4cout << G4endl << "=== Leaving QweakSimPMTOnly::SetPMTOnly_TiltAngleInY() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_TiltAngleInZ(G4double zTiltAngle)
{
    //--- Set PMTOnly New Z Tilting Angle
	
    G4cout << G4endl << "=== Calling QweakSimPMTOnly::SetPMTOnly_TiltAngleInZ() " << G4endl;
	
    //--- rotate back with old angle
    PMTOnlyContainer_RotationMatrix->rotateZ(-1.0*PMTOnlyContainer_TiltAngle_Z);
    PMTOnlyContainer_Physical->SetRotation(PMTOnlyContainer_RotationMatrix);
	
    //--- assign new tilting angle
    PMTOnlyContainer_TiltAngle_Z = zTiltAngle;
	
    //--- rotate to new angle
    PMTOnlyContainer_RotationMatrix->rotateZ(PMTOnlyContainer_TiltAngle_Z);
    PMTOnlyContainer_Physical->SetRotation(PMTOnlyContainer_RotationMatrix);
	
    G4cout << G4endl << "=== Leaving QweakSimPMTOnly::SetPMTOnly_TiltAngleInZ() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_Enabled()
{
    //--- Enable the PMTOnly
	
    G4cout << "=== Calling QweakSimPMTOnly::SetPMTOnly_Enabled() " << G4endl;
    PMTOnly_VisAtt -> SetVisibility(true);
    PMTOnlyContainer_Physical->SetTranslation(G4ThreeVector(PMTOnlyContainer_CenterPosition_X,
                                                     PMTOnlyContainer_CenterPosition_Y,
                                                     PMTOnlyContainer_CenterPosition_Z));
    G4cout << "=== Leaving QweakSimPMTOnly::SetPMTOnly_Enabled() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_Disabled()
{
    //--- Disable the PMTOnly
	
    G4cout << "=== Calling QweakSimPMTOnly::SetPMTOnly_Disabled() " << G4endl;
    PMTOnly_VisAtt -> SetVisibility(false);
    PMTOnlyContainer_Physical->SetTranslation(G4ThreeVector(PMTOnlyContainer_CenterPosition_X,
                                                     PMTOnlyContainer_CenterPosition_Y,
                                                     PMTOnlyContainer_CenterPosition_Z + 400.00*cm));
    G4cout << "=== Leaving QweakSimPMTOnly::SetPMTOnly_Disabled() " << G4endl << G4endl;
}


/////// --------------------------------------------------------------------

