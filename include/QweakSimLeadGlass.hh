
// QweakSimLeadGlass.hh
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#ifndef QweakSimLeadGlass_h
#define QweakSimLeadGlass_h 1

/////// --------------------------------------------------------------------

//--- geant4 includes
#include "G4LogicalVolume.hh"

//--- user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimLeadGlassMessenger.hh"

/////// --------------------------------------------------------------------

//--- user classes
class QweakSimMaterial;
class QweakSimLeadGlassMessenger;

/////// --------------------------------------------------------------------

class QweakSimLeadGlass
{
	
public:
	
    QweakSimLeadGlass();
    ~QweakSimLeadGlass();
	
    void ConstructComponent(G4VPhysicalVolume* MotherVolume);
    void DestroyComponent();
	
    void SetLeadGlass_Material(G4String);
	
    void SetLeadGlass_CenterPositionInX(G4double xPos);
    void SetLeadGlass_CenterPositionInY(G4double yPos);
    void SetLeadGlass_CenterPositionInZ(G4double zPos);
    G4double GetLeadGlass_CenterPositionInX()    {return LeadGlass_CenterPosition_X;}
    G4double GetLeadGlass_CenterPositionInY()    {return LeadGlass_CenterPosition_Y;}
    G4double GetLeadGlass_CenterPositionInZ()    {return LeadGlass_CenterPosition_Z;}
	
    void SetLeadGlass_FullLengthInX(G4double dim)  {LeadGlass_FullLength_X = dim;}
    void SetLeadGlass_FullLengthInY(G4double dim)  {LeadGlass_FullLength_Y = dim;}
    void SetLeadGlass_FullLengthInZ(G4double dim)  {LeadGlass_FullLength_Z = dim;}
    G4double GetLeadGlass_FullLengthInX()          {return LeadGlass_FullLength_X;}
    G4double GetLeadGlass_FullLengthInY()          {return LeadGlass_FullLength_Y;}
    G4double GetLeadGlass_FullLengthInZ()          {return LeadGlass_FullLength_Z;}
    
    void SetLeadGlass_TiltAngleInX(G4double xTiltAngle);
    void SetLeadGlass_TiltAngleInY(G4double yTiltAngle);
    void SetLeadGlass_TiltAngleInZ(G4double zTiltAngle);
    G4double GetLeadGlass_TiltAngleInX()           {return LeadGlass_TiltAngle_X;}
    G4double GetLeadGlass_TiltAngleInY()           {return LeadGlass_TiltAngle_Y;}
    G4double GetLeadGlass_TiltAngleInZ()           {return LeadGlass_TiltAngle_Z;}
	
    void SetLeadGlass_Enabled();
    void SetLeadGlass_Disabled();
	
    G4LogicalVolume*   GetLeadGlass_LogicalVolume()  {return LeadGlass_Logical;}
    G4VPhysicalVolume* GetLeadGlass_PhysicalVolume() {return LeadGlass_Physical;}
	
private:
	
    QweakSimLeadGlassMessenger* LeadGlassMessenger;
	
    QweakSimMaterial* pMaterial;

    G4Box*             LeadGlass_Solid;
    G4LogicalVolume*   LeadGlass_Logical;
    G4VPhysicalVolume* LeadGlass_Physical;

    G4Material*        LeadGlass_Material;
	
    G4VisAttributes*   LeadGlass_VisAtt;
	
    //--- LeadGlass geometry
    G4double LeadGlass_FullLength_X;
    G4double LeadGlass_FullLength_Y;
    G4double LeadGlass_FullLength_Z;
	
    //--- LeadGlass position
    G4double MD7_CenterPosition_X;
    G4double MD7_CenterPosition_Y;
    G4double MD7_CenterPosition_Z;
	
    G4double LeadGlass_CenterPosition_X;
    G4double LeadGlass_CenterPosition_Y;
    G4double LeadGlass_CenterPosition_Z;
    G4ThreeVector LeadGlass_CenterPosition;
	
    //--- LeadGlass rotation
    G4double LeadGlass_TiltAngle_X;
    G4double LeadGlass_TiltAngle_Y;
    G4double LeadGlass_TiltAngle_Z;
    G4RotationMatrix* LeadGlass_RotationMatrix;
	
    //--- LeadGlass sensitive detector
    G4VSensitiveDetector* LeadGlassSD;
    
};



/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------

