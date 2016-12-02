#ifndef QweakSimCerenkovDetector_h
#define QweakSimCerenkovDetector_h 

// system includes
#include <vector>

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimUserInformation.hh"
#include "QweakSimCerenkovDetectorMessenger.hh"
#include "QweakSimCerenkov_DetectorSD.hh"
#include "QweakSimCerenkovDetector_PMTSD.hh"
// #include "QweakSimPMTEntranceWindowSD.hh"

// user classes
class QweakSimCerenkovDetectorMessenger;
class QweakSimMaterial;

class QweakSimCerenkovDetector 
{
public:
  QweakSimCerenkovDetector(QweakSimUserInformation*);
  virtual ~QweakSimCerenkovDetector();
  
  void SetMotherVolume(G4VPhysicalVolume* mv) {theMotherPV = mv;}
  void PlacePVCerenkovMasterContainer();

  void ConstructComponent(G4VPhysicalVolume* MotherVolume);
  void DefineCerenkovGeometry();
  void DestroyComponent();

  void SetNumberOfDetectors(G4int number);

  void SetCerenkovDetectorMaterial(G4String materialName);
  void SetPreradiatorMaterial(G4String materialName);
  void SetContainerMaterial(G4String materialName);

  void SetCerenkovDetectorCenterPositionInX(G4double xPos, G4int octant);
  void SetCerenkovDetectorCenterPositionInY(G4double yPos, G4int octant);
  void SetCerenkovDetectorCenterPositionInZ(G4double zPos, G4int octant);
  void SetCerenkovDetectorTiltAngle(G4double tiltangle);
  void SetCerenkovDetectorThickness(G4double thickness);

  void SetCerenkovDetectorPbStepSize(G4double size){myUserInfo->geantStepSizeInPb = size;}
      
    

  void CerenkovGeometryPVUpdate();

  G4LogicalVolume*   GetCerenkovDetector_LogicalVolume()    {return ActiveArea_Logical;} 
  G4VPhysicalVolume* GetCerenkovDetector_PhysicalVolume()   {return ActiveArea_Physical;} 

  G4LogicalVolume*   GetPMT_LogicalVolume()    {return Cathode_Logical;} 
  G4VPhysicalVolume* GetPMT_PhysicalVolume()   {return Cathode_Physical;} 

private:

  QweakSimUserInformation *myUserInfo;

  std::vector< QweakSimCerenkovDetectorMessenger* >  CerenkovDetectorMessenger;  // pointer to the Messenger

  QweakSimMaterial*  pMaterial;

  G4VPhysicalVolume* theMotherPV;

  // Number of Cerenkov detectors
  G4int NumberOfCerenkovDetectors;

  // Needed for manual coil placement
  std::vector< G4VPhysicalVolume* > CerenkovMasterContainer_Physical;
  std::vector< G4ThreeVector >      Translation_CerenkovMasterContainer;
  std::vector< G4RotationMatrix* >  Rotation_CerenkovMasterContainer;

  std::vector< G4RotationMatrix* > Rotation_SideBracket;
  std::vector< G4ThreeVector > Position_SideBracket;

  std::vector< G4RotationMatrix* > Rotation_EndBracket;
  std::vector< G4ThreeVector > Position_EndBracket;

  std::vector< G4RotationMatrix* > Rotation_SideBracketPad;
  std::vector< G4ThreeVector > Position_SideBracketPad;

  std::vector< G4RotationMatrix* > Rotation_EndBracketPad;
  std::vector< G4ThreeVector > Position_EndBracketPad;


  G4LogicalVolume*   CerenkovContainer_Logical; 
  G4VPhysicalVolume* CerenkovContainer_Physical; 
  G4Material*        CerenkovContainer_Material;

  G4LogicalVolume*   ActiveArea_Logical; 
  G4VPhysicalVolume* ActiveArea_Physical; 
  G4Material*        ActiveArea_Material;

  G4LogicalVolume*   QuartzBar_LogicalLeft; 
  G4LogicalVolume*   QuartzBar_LogicalRight; 
  G4VPhysicalVolume* QuartzBar_PhysicalLeft; 
  G4VPhysicalVolume* QuartzBar_PhysicalRight; 
  G4Material*        QuartzBar_Material;

  G4LogicalVolume*   LightGuide_LogicalLeft; 
  G4LogicalVolume*   LightGuide_LogicalRight; 
  G4VPhysicalVolume* LightGuide_PhysicalLeft; 
  G4VPhysicalVolume* LightGuide_PhysicalRight; 
  G4Material*        LightGuide_Material;     

  G4LogicalVolume*   QuartzGlue_Logical; 
  G4VPhysicalVolume* QuartzGlue_PhysicalLeft; 
  G4VPhysicalVolume* QuartzGlue_PhysicalCenter; 
  G4VPhysicalVolume* QuartzGlue_PhysicalRight; 
  G4Material*        QuartzGlue_Material;      

  G4LogicalVolume*   RadiatorStpLogical; 
  G4LogicalVolume*   RadiatorStdLogical; 
  //G4VPhysicalVolume* Radiator_Physical; 
  G4Material*        Radiator_Material;
  
  G4LogicalVolume*   PMT_PbShield_Logical; 
  G4VPhysicalVolume* PMT_PbShield_Physical; 
  G4Material*        PMT_PbShield_Material;

  G4LogicalVolume*   PMTContainer_Logical; 
  G4VPhysicalVolume* PMTContainer_PhysicalLeft; 
  G4VPhysicalVolume* PMTContainer_PhysicalRight; 
  G4Material*        PMTContainer_Material;

  G4LogicalVolume*   PMTQuartzOpticalFilm_Logical; 
  G4VPhysicalVolume* PMTQuartzOpticalFilm_Physical; 
  G4Material*        PMTQuartzOpticalFilm_Material;

  G4LogicalVolume*   PMTEntranceWindow_Logical; 
  G4VPhysicalVolume* PMTEntranceWindow_Physical; 
  G4Material*        PMTEntranceWindow_Material;

  G4LogicalVolume*   Cathode_Logical; 
  G4VPhysicalVolume* Cathode_Physical; 
  G4Material*        Cathode_Material;

  G4LogicalVolume*   Frame_Logical; 
  G4VPhysicalVolume* Frame_Physical; 
  G4Material*        Frame_Material;

  G4LogicalVolume*   CrossBar_Logical;
  G4VPhysicalVolume* CrossBarR_Physical; 
  G4VPhysicalVolume* CrossBarL_Physical; 

  G4LogicalVolume*   FrontWindow_Logical; 
  G4VPhysicalVolume* FrontWindow_Physical; 
  G4LogicalVolume*   BackWindow_Logical; 
  G4VPhysicalVolume* BackWindow_Physical; 
  G4Material*        Window_Material;

  G4LogicalVolume*   FrontClip_Logical; 
  G4VPhysicalVolume* FrontClip_Physical; 

  G4LogicalVolume*   BackClip_Logical; 
  G4VPhysicalVolume* BackClip_Physical; 

  G4LogicalVolume*   SquareFalange_Logical;
  G4VPhysicalVolume* SquareFalangeR_Physical; 
  G4VPhysicalVolume* SquareFalangeL_Physical; 

  G4LogicalVolume*   SquareFalangeSeal_Logical;
  G4VPhysicalVolume* SquareFalangeSealR_Physical; 
  G4VPhysicalVolume* SquareFalangeSealL_Physical;

  G4LogicalVolume*   PMTHousingWall_Logical;
  G4VPhysicalVolume* PMTHousingWallR_Physical; 
  G4VPhysicalVolume* PMTHousingWallL_Physical;

  G4LogicalVolume*   PMTHousingFalange_Logical;
  G4VPhysicalVolume* PMTHousingFalangeR_Physical; 
  G4VPhysicalVolume* PMTHousingFalangeL_Physical;

  G4LogicalVolume*   PMTHousingLid_Logical;
  G4VPhysicalVolume* PMTHousingLidR_Physical; 
  G4VPhysicalVolume* PMTHousingLidL_Physical;

  G4LogicalVolume*   SideBracket_Logical; 
  std::vector< G4VPhysicalVolume* >  SideBracket_Physical;

  G4LogicalVolume*   EndBracket_Logical; 
  std::vector< G4VPhysicalVolume* >  EndBracket_Physical;

  G4LogicalVolume*   SideBracketPad_Logical; 
  std::vector< G4VPhysicalVolume* >  SideBracketPad_Physical;

  G4LogicalVolume*   EndBracketPad_Logical; 
  std::vector< G4VPhysicalVolume* >  EndBracketPad_Physical;

  G4Material*        BracketPad_Material;

  G4LogicalVolume*   ExoSkeltonFrame_Logical; 
  G4VPhysicalVolume* ExoSkeltonFrame_Physical; 
  G4Material*        ExoSkeltonFrame_Material;

  //   G4Box             *QuartzBar_Solid;
  //   G4Box             *PMTEntranceWindow_Solid;
  //   G4Box             *PMT_Solid;
  //   G4Box             *PMTContainer_Solid;

  G4double Container_FullLength_X;
  G4double Container_FullLength_Y;
  G4double Container_FullLength_Z;

  G4double ExoSkeltonFrame_X;
  G4double ExoSkeltonFrame_Y;
  G4double ExoSkeltonFrame_Z;

  G4double ExoSkeltonInnerFrame_X;
  G4double ExoSkeltonInnerFrame_Y;
  G4double ExoSkeltonInnerFrame_Z;
  
  G4double Frame_FullLength_X;
  G4double Frame_FullLength_Y;
  G4double Frame_FullLength_Z;

  G4double Frame_InnerFullLength_X;
  G4double Frame_InnerFullLength_Y;
  G4double Frame_InnerFullLength_Z;

  G4double SideBracketLength_X;
  G4double SideBracketLength_Y;
  G4double SideBracketLength_Z;

  G4double SideBracketCutLength_X;
  G4double SideBracketCutLength_Y;
  G4double SideBracketCutLength_Z;

  G4double EndBracketLength_X;
  G4double EndBracketLength_Y;
  G4double EndBracketLength_Z;

  G4double EndBracketCutLength_X;
  G4double EndBracketCutLength_Y;
  G4double EndBracketCutLength_Z;

  G4double SideBracketPadLength_X;
  G4double SideBracketPadLength_Y;
  G4double SideBracketPadLength_Z;

  G4double SideBracketPadCutLength_X;
  G4double SideBracketPadCutLength_Y;
  G4double SideBracketPadCutLength_Z;

  G4double EndBracketPadLength_X;
  G4double EndBracketPadLength_Y;
  G4double EndBracketPadLength_Z;

  G4double EndBracketPadCutLength_X;
  G4double EndBracketPadCutLength_Y;
  G4double EndBracketPadCutLength_Z;

  G4double WindowThickness;

  G4double ActiveArea_FullLength_X;
  G4double ActiveArea_FullLength_Y;
  G4double ActiveArea_FullLength_Z;

  G4double GlueFilm_FullLength_X;
  G4double GlueFilm_FullLength_Y;
  G4double GlueFilm_FullLength_Z;

  G4double Chamfer_FullLength;
  G4double Chamfer_FullHeight;
  G4double Chamfer_FullThickness;

  G4double QuartzBar_FullLength;
  G4double QuartzBar_FullHeight;
  G4double QuartzBar_FullThickness;

  G4double LightGuide_FullLength;
  G4double LightGuide_FullWidth1;
  G4double LightGuide_FullWidth2;
  G4double LightGuide_FullThickness;

  G4double PMTContainer_Diameter;
  G4double PMTContainer_FullLength_Z;

  G4double PMTQuartzOpticalFilm_Diameter;
  G4double PMTQuartzOpticalFilm_Thickness;

  G4double PMTEntranceWindow_Diameter;
  G4double PMTEntranceWindow_Thickness;

  G4double Cathode_Diameter;
  G4double Cathode_Thickness;

  G4double CerenkovDetectorCenterZPosition;

  G4double LGAngCutXDim;
  G4double LGAngCutYDim;
  G4double LGAngCutZDim;


  // needed for boolean union
  std::vector< G4SubtractionSolid* >  RightQuartz_Solid;
  std::vector< G4SubtractionSolid* >  LeftQuartz_Solid;
  std::vector< G4SubtractionSolid* >  LeftGuide_Solid;
  std::vector< G4SubtractionSolid* >  RightGuide_Solid;

  // std::vector< G4Box* >  mirror_solid;
  G4Material* mirror_material;
  std::vector< G4LogicalVolume* > mirror_logical;
  std::vector< G4VPhysicalVolume* > mirror_physical;
 
  G4double Tilting_Angle;      // total tilting angle towards mean track
  G4double Kink_Angle;         // Vshape angle
  G4double Thickness; 
  G4double maxStepInPbRadiator;
  
  // placing the container
  G4ThreeVector    Position_CerenkovContainer;
  G4RotationMatrix* Rotation_CerenkovContainer;  

  // placing the chamfers
  G4ThreeVector    Position_Chamfer1;
  G4RotationMatrix Rotation_Chamfer1;  
  G4ThreeVector    Position_Chamfer2;
  G4RotationMatrix Rotation_Chamfer2;  
  G4ThreeVector    Position_Chamfer3;
  G4RotationMatrix Rotation_Chamfer3;  
  G4ThreeVector    Position_Chamfer4;
  G4RotationMatrix Rotation_Chamfer4;  

  G4ThreeVector    Position_AngCut1;
  G4RotationMatrix Rotation_AngCut1;
  
  G4ThreeVector    Position_AngCut2;
  G4RotationMatrix Rotation_AngCut2;  

  G4ThreeVector    Position_LGRight;
  G4RotationMatrix Rotation_LGRight;  
  G4ThreeVector    Position_LGLeft;
  G4RotationMatrix Rotation_LGLeft;  

  G4ThreeVector    Position_LGFaceMirrorLeft;
  G4RotationMatrix Rotation_LGFaceMirrorLeft;  

  G4ThreeVector    Position_LGEdgeMirrorLeft;
  G4RotationMatrix Rotation_LGEdgeMirrorLeft;  

  G4ThreeVector    Position_LGFaceMirrorRight;
  G4RotationMatrix Rotation_LGFaceMirrorRight;  

  G4ThreeVector    Position_LGEdgeMirrorRight;
  G4RotationMatrix Rotation_LGEdgeMirrorRight;  

  // placing the left SingleBar
  G4ThreeVector    Translation_SingleBarLeft;
  G4RotationMatrix Rotation_SingleBarLeft;  

  // placing the right SingleBar
  G4ThreeVector    Translation_SingleBarRight; 
  G4RotationMatrix Rotation_SingleBarRight; 

  // placing the left PMTContainer
  G4ThreeVector     Translation_PMTContainerLeft;
  G4RotationMatrix Rotation_PMTContainerLeft; 

  // placing the right PMTContainer
  G4ThreeVector     Translation_PMTContainerRight;
  G4RotationMatrix Rotation_PMTContainerRight; 

  // placing the  PMT
  G4ThreeVector    Translation_Cathode;
  G4RotationMatrix Rotation_Cathode;

  // placing the  PMTEntranceWindow
  G4ThreeVector    Translation_PMTQuartzOpticalFilm;
  G4RotationMatrix Rotation_PMTQuartzOpticalFilm;  

  G4ThreeVector    Translation_PMTEntranceWindow;
  G4RotationMatrix Rotation_PMTEntranceWindow;
 
  // pointer to the sensitive detector
  G4VSensitiveDetector* CerenkovDetectorSD;
  G4VSensitiveDetector* CerenkovDetector_PMTSD;

  // Cerenkov Position variable now a vector for eight positions
  std::vector< G4double > Position_CerenkovContainer_X;
  std::vector< G4double > Position_CerenkovContainer_Y;
  std::vector< G4double > Position_CerenkovContainer_Z;

  // Default values for position
  G4double Default_Position_CerenkovContainer_X;
  G4double Default_Position_CerenkovContainer_Y;
  G4double Default_Position_CerenkovContainer_Z;
  
  // Repositions the center point that all components are built around
  G4double Container_Center_X;
  G4double Container_Center_Y;
  G4double Container_Center_Z;

  G4ThreeVector Container_Center;

};
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
