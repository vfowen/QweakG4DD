// QweakSimPMTOnly.hh
// Marty McHugh
// 2013-06-11

/////// --------------------------------------------------------------------

#ifndef QweakSimPMTOnly_hh
#define QweakSimPMTOnly_hh 1

/////// --------------------------------------------------------------------

//--- geant4 includes
#include "G4LogicalVolume.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

//--- user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimPMTOnlyMessenger.hh"
#include "QweakSimUserInformation.hh"

/////// --------------------------------------------------------------------

//--- user classes
class QweakSimMaterial;
class QweakSimPMTOnlyMessenger;

/////// --------------------------------------------------------------------

class QweakSimPMTOnly
{
	
public:
	
    QweakSimPMTOnly(QweakSimUserInformation*);
    ~QweakSimPMTOnly();
	
    void ConstructComponent(G4VPhysicalVolume* MotherVolume);
    void DestroyComponent();
	
    void SetPMTOnly_Material(G4String);
	
    void SetPMTOnly_CenterPositionInX(G4double xPos);
    void SetPMTOnly_CenterPositionInY(G4double yPos);
    void SetPMTOnly_CenterPositionInZ(G4double zPos);
    
    void FindPMTOnly_MotherCenter();
    
    G4double GetPMTOnly_CenterPositionInX()    {return PMTOnly_CenterPosition_X+PMTOnlyContainer_CenterPosition_X;}
    G4double GetPMTOnly_CenterPositionInY()    {return PMTOnly_CenterPosition_Y+PMTOnlyContainer_CenterPosition_Y;}
    G4double GetPMTOnly_CenterPositionInZ()    {return PMTOnly_CenterPosition_Z+PMTOnlyContainer_CenterPosition_Z;}
	
    void SetPMTOnly_FullLengthInX(G4double dim)  {PMTOnly_FullLength_X = dim;}
    void SetPMTOnly_FullLengthInY(G4double dim)  {PMTOnly_FullLength_Y = dim;}
    void SetPMTOnly_FullLengthInZ(G4double dim)  {PMTOnly_FullLength_Z = dim;}
    
    G4double GetPMTOnly_FullLengthInX()          {return PMTOnly_FullLength_X;}
    G4double GetPMTOnly_FullLengthInY()          {return PMTOnly_FullLength_Y;}
    G4double GetPMTOnly_FullLengthInZ()          {return PMTOnly_FullLength_Z;}
    
    void SetPMTOnly_TiltAngleInX(G4double xTiltAngle);
    void SetPMTOnly_TiltAngleInY(G4double yTiltAngle);
    void SetPMTOnly_TiltAngleInZ(G4double zTiltAngle);
    
    G4double GetPMTOnly_TiltAngleInX()           {return PMTOnlyContainer_TiltAngle_X;}
    G4double GetPMTOnly_TiltAngleInY()           {return PMTOnlyContainer_TiltAngle_Y;}
    G4double GetPMTOnly_TiltAngleInZ()           {return PMTOnlyContainer_TiltAngle_Z;}
	
    void SetPMTOnly_Enabled();
    void SetPMTOnly_Disabled();
	
    G4LogicalVolume*   GetPMTOnly_LogicalVolume()  {return PMTOnly_Logical;}
    G4VPhysicalVolume* GetPMTOnly_PhysicalVolume() {return PMTOnly_Physical;}
	
private:
	
    QweakSimPMTOnlyMessenger* PMTOnlyMessenger;
	
    QweakSimMaterial* pMaterial;

    G4Box* 		PMTOnlyContainer_Solid;
    G4LogicalVolume*	PMTOnlyContainer_Logical;
    G4VPhysicalVolume*	PMTOnlyContainer_Physical;
    G4Material*		PMTOnlyContainer_Material;	
    G4VisAttributes*   	PMTOnlyContainer_VisAtt;

    G4Box*             	PMTOnly_Solid;
    G4LogicalVolume*   	PMTOnly_Logical;
    G4VPhysicalVolume* 	PMTOnly_Physical;
    G4Material*        	PMTOnly_Material;
    G4VisAttributes*   	PMTOnly_VisAtt;
    
    G4Tubs*		PMTOnlyQuartzOpticalFilm_Solid;
    G4LogicalVolume*   	PMTOnlyQuartzOpticalFilm_Logical;
    G4VPhysicalVolume* 	PMTOnlyQuartzOpticalFilm_Physical;
    G4Material*        	PMTOnlyQuartzOpticalFilm_Material;
    
    G4Tubs*		PMTOnlyEntranceWindow_Solid;
    G4LogicalVolume*   	PMTOnlyEntranceWindow_Logical; 
    G4VPhysicalVolume* 	PMTOnlyEntranceWindow_Physical; 
    G4Material*        	PMTOnlyEntranceWindow_Material;
    
    G4Tubs* 		PMTOnlyCathode_Solid;
    G4LogicalVolume*   	PMTOnlyCathode_Logical; 
    G4VPhysicalVolume* 	PMTOnlyCathode_Physical; 
    G4Material*        	PMTOnlyCathode_Material;
    
    //--- Mother sizes
    G4double PMTOnlyContainer_FullLength_X;
    G4double PMTOnlyContainer_FullLength_Y;
    G4double PMTOnlyContainer_FullLength_Z;
    
    //--- Mother position
    G4double PMTOnlyContainer_CenterPosition_X;
    G4double PMTOnlyContainer_CenterPosition_Y;
    G4double PMTOnlyContainer_CenterPosition_Z;
    G4ThreeVector PMTOnlyContainer_CenterPosition;
	
    //--- PMTOnly sizes
    G4double PMTOnly_FullLength_X;
    G4double PMTOnly_FullLength_Y;
    G4double PMTOnly_FullLength_Z;
	
    //--- PMTOnly position
    G4double PMTOnly_CenterPosition_X;
    G4double PMTOnly_CenterPosition_Y;
    G4double PMTOnly_CenterPosition_Z;
    G4ThreeVector PMTOnly_CenterPosition;
	
    //--- Mother rotation
    G4double PMTOnlyContainer_TiltAngle_X;
    G4double PMTOnlyContainer_TiltAngle_Y;
    G4double PMTOnlyContainer_TiltAngle_Z;
    G4RotationMatrix* PMTOnlyContainer_RotationMatrix;

    //--- MD5 position
    G4double MD5_CenterPosition_X;
    G4double MD5_CenterPosition_Y;
    G4double MD5_CenterPosition_Z;

    //--- PMT Stuff
    G4double PMTOnlyQuartzOpticalFilm_X;
    G4double PMTOnlyQuartzOpticalFilm_Y;
    G4double PMTOnlyQuartzOpticalFilm_Z;
    
    G4double PMTOnlyQuartzOpticalFilm_Diameter;
    G4double PMTOnlyQuartzOpticalFilm_Thickness;

    G4double PMTOnlyEntranceWindow_X;
    G4double PMTOnlyEntranceWindow_Y;
    G4double PMTOnlyEntranceWindow_Z;

    G4double PMTOnlyEntranceWindow_Diameter;
    G4double PMTOnlyEntranceWindow_Thickness;

    G4double PMTOnlyCathode_X;
    G4double PMTOnlyCathode_Y;    
    G4double PMTOnlyCathode_Z;

    G4double PMTOnlyCathode_Diameter;
    G4double PMTOnlyCathode_Thickness;

    //--- PMTOnly sensitive detector
    G4VSensitiveDetector* PMTOnlySD;
    
    G4VSensitiveDetector* PMTOnly_PMTSD;
    
    //--- QweakSimUserInformation
    QweakSimUserInformation* myUserInfo;
    
};


/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
