//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**

   \file QweakSimMainMagnet.hh
   $Revision: 1.7 $
   $Date: 2006/01/18 20:19:05 $
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
   \class QweakSimMainMagnet

   \brief Main Magnet solids like coils and support, no field

   Placeholder for a long explaination

 */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimMainMagnet_h
#define QweakSimMainMagnet_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include <vector>

// user includes
#include "QweakSimSolids.hh"

// user classes
class QweakSimMaterial;
class QweakSimMagnet_CoilParameterisation;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimMainMagnet
{
public:

   QweakSimMainMagnet();
  ~QweakSimMainMagnet();

  void ConstructComponent(G4VPhysicalVolume* MotherVolume);
  void Construct_UpstreamSpider(G4VPhysicalVolume* MotherVolume);
  void Construct_ClampPlates(G4VPhysicalVolume* MotherVolume);
  void Construct_UpStreamMiniClampPlates(G4VPhysicalVolume* MotherVolume);
  void Construct_CoilFrames(G4VPhysicalVolume* MotherVolume);
  void Construct_RadialMountingBlocks(G4VPhysicalVolume* MotherVolume);
  void Construct_SupportFrame(G4VPhysicalVolume* MotherVolume);
  void Construct_DownstreamSpider(G4VPhysicalVolume* MotherVolume);

  void DestroyComponent();

  void SetCenterPositionInZ(G4double myCenterPositionInZ);
  void SetSingleCoil_RadialCenterDistanceToBeamLine(G4double RadialDistance) { SingleCoil_CenterPositionInR = RadialDistance; }

  G4LogicalVolume*   getMainMagnetLogicalVolume()    {return MainMagnet_MasterContainer_Logical;}
  G4VPhysicalVolume* getMainMagnetPhysicalVolume()   {return MainMagnet_MasterContainer_Physical;}

private:



  //QweakSimMainMagnetMessenger*      fMainMagnetMessenger;

  QweakSimMaterial* pMaterial;

  G4VPVParameterisation* MM_SingleCoilParam;

  G4LogicalVolume*   MainMagnet_MasterContainer_Logical;
  G4VPhysicalVolume* MainMagnet_MasterContainer_Physical;
  G4Material*        MainMagnet_MasterContainer_Material;

  G4double MainMagnet_MasterContainer_FullLength_X;
  G4double MainMagnet_MasterContainer_FullLength_Y;
  G4double MainMagnet_MasterContainer_FullLength_Z;

  G4double MainMagnet_CenterPositionInZ;

   // SingleCoil MasterContainer
   G4LogicalVolume*   SingleCoil_MasterContainer_Logical;

   // needed for manual coil placement


   std::vector< G4double >           Angle_SingleCoil;
   std::vector< G4ThreeVector >      Translation_SingleCoil;
   std::vector< G4RotationMatrix* >  Rotation_SingleCoil;

   G4Material*        SingleCoil_MasterContainer_Material;

   G4double SingleCoil_MasterContainer_FullLength_X;
   G4double SingleCoil_MasterContainer_FullLength_Y;
   G4double SingleCoil_MasterContainer_FullLength_Z;

   G4double            SingleCoil_CenterPositionInR;
   G4double            SingleCoil_MinimalRadialDistance;
   G4double            SingleCoil_FullThickness;

   G4Material*         SingleCoil_Material;

    // SingleCoil plate shape,
    G4LogicalVolume*   SingleCoil_Plate_Logical;
    std::vector< G4VPhysicalVolume* > SingleCoil_UpperPlate_Physical;
    std::vector< G4VPhysicalVolume* > SingleCoil_LowerPlate_Physical;
    std::vector< G4ThreeVector >      Translation_SingleCoil_UpperPlate;
    std::vector< G4ThreeVector >      Translation_SingleCoil_LowerPlate;

    // SingleCoil wing shape,
    G4LogicalVolume*   SingleCoil_Wing_Logical;
    std::vector< G4VPhysicalVolume* > SingleCoil_LeftWing_Physical;
    std::vector< G4VPhysicalVolume* > SingleCoil_RightWing_Physical;
    std::vector< G4RotationMatrix* >  Rotation_SingleCoil_LeftWing;
    std::vector< G4RotationMatrix* >  Rotation_SingleCoil_RightWing;
    std::vector< G4ThreeVector >      Translation_SingleCoil_LeftWing;
    std::vector< G4ThreeVector >      Translation_SingleCoil_RightWing;

    // define a single C-coil: left wing
    G4double SingleCoil_Wing_DiameterMin;
    G4double SingleCoil_Wing_DiameterMax;
    G4double SingleCoil_Wing_PhiAngleStart;
    G4double SingleCoil_Wing_PhiDeltaAngle;

    // define a single coil plate
    G4double SingleCoil_Plate_FullLength_X;
    G4double SingleCoil_Plate_FullLength_Y;
    G4double SingleCoil_Plate_FullLength_Z;

    G4VisAttributes* SingleCoil_VisAtt;

    //-----------------------------
    // Upstream spider definition
        //-----------------------------
    G4LogicalVolume*   UpstreamSpider_Tube_Subtraction_Logical;
    G4LogicalVolume*   UpstreamSpider_Box_Subtraction_Logical;
    G4LogicalVolume*   UpstreamSpider_Box_Union_Logical;

    G4LogicalVolume*   UpstreamSpider_LowThetaCutoutLeft_Logical;
    G4VPhysicalVolume* UpstreamSpider_LowThetaCutoutLeft_Physical;

    G4LogicalVolume*   UpstreamSpider_LowThetaCutoutRight_Logical;
    G4VPhysicalVolume* UpstreamSpider_LowThetaCutoutRight_Physical;

    G4LogicalVolume*   UpstreamSpider_LowThetaCutoutFinal_Logical;
    G4VPhysicalVolume* UpstreamSpider_LowThetaCutoutFinal_Physical;

    G4LogicalVolume*   UpstreamSpider_Logical;
    G4VPhysicalVolume* UpstreamSpider_Physical;
    G4Material*        UpstreamSpider_Material;

    G4double UpstreamSpider_DiameterMin;
    G4double UpstreamSpider_DiameterMax;
    G4double UpstreamSpider_FullThickness;
    G4double UpstreamSpider_PhiAngleStart;
    G4double UpstreamSpider_PhiDeltaAngle;

    G4double UpstreamSpider_CenterPositionInZ;

    // needed for octant cuts in the shielding wall
     std::vector< G4SubtractionSolid* >  MyUpstreamSpider_Solid;
     std::vector< G4UnionSolid* >        MyUpstreamSpider_LowThetaCutout_Solid;
     std::vector< G4UnionSolid* >        MyUpstreamSpider_StrutsUnion_Solid;

     G4VisAttributes* UpstreamSpider_VisAtt;

     //-----------------------------------------
     // needed for the large coil clamp plates
     //-----------------------------------------
     //
     G4double           ClampPlate_FullLength_X;
     G4double           ClampPlate_FullLength_Y;
     G4double           ClampPlate_FullLength_Z;
     G4double           ClampPlate_CenterPositionInR;

     G4LogicalVolume*   SingleCoil_ClampPlate_Logical;
     G4Material*        SingleCoil_ClampPlate_Material;

     std::vector< G4VPhysicalVolume* > SingleCoil_LeftClampPlate_Physical;
     std::vector< G4VPhysicalVolume* > SingleCoil_RightClampPlate_Physical;

     std::vector< G4ThreeVector >      Translation_LeftClampPlate;
     std::vector< G4ThreeVector >      Translation_RightClampPlate;

     std::vector< G4double >           Angle_ClampPlate;
     std::vector< G4RotationMatrix* >  Rotation_ClampPlate;

     G4VisAttributes* SingleCoil_ClampPlate_VisAtt;

     //-----------------------------------------
     // needed for the upstream mini clamp plates
     //-----------------------------------------
     //
     G4double           MiniClampPlate_FullLength_X;
     G4double           MiniClampPlate_FullLength_Y;
     G4double           MiniClampPlate_FullLength_Z;

     G4double           MiniClampPlate_CenterPositionInR;
     G4double           MiniClampPlate_CenterPositionInZ;

     G4LogicalVolume*   SingleCoil_LeftMiniClampPlate_Logical;
     G4LogicalVolume*   SingleCoil_RightMiniClampPlate_Logical;
     G4Material*        SingleCoil_MiniClampPlate_Material;

     std::vector< G4VPhysicalVolume* > SingleCoil_LeftMiniClampPlate_Physical;
     std::vector< G4VPhysicalVolume* > SingleCoil_RightMiniClampPlate_Physical;

     std::vector< G4ThreeVector >      Translation_LeftMiniClampPlate;
     std::vector< G4ThreeVector >      Translation_RightMiniClampPlate;

     std::vector< G4double >           Angle_MiniClampPlate;
     std::vector< G4RotationMatrix* >  Rotation_MiniClampPlate;


     // needed for mini clamp chamfer
     std::vector< G4SubtractionSolid* >  MiniClampPlateTemp_Solid;

     // mini clamp chamfer dimensions
     G4double Chamfer_FullLength_X;
     G4double Chamfer_FullLength_Y;
     G4double Chamfer_FullLength_Z;


     // placing the chamfers
     G4ThreeVector    Position_Chamfer1;
     G4RotationMatrix Rotation_Chamfer1;
     G4ThreeVector    Position_Chamfer2;
     G4RotationMatrix Rotation_Chamfer2;
     G4ThreeVector    Position_Chamfer3;
     G4RotationMatrix Rotation_Chamfer3;
     G4ThreeVector    Position_Chamfer4;
     G4RotationMatrix Rotation_Chamfer4;

     G4VisAttributes* SingleCoil_MiniClampPlate_VisAtt;

     //---------------------------------------

     //-----------------------------------------
     // needed for the outer coil plate
     //-----------------------------------------
     //
      G4double           CoilFramePlate_FullLength_X;
      G4double           CoilFramePlate_FullLength_Y;
      G4double           CoilFramePlate_FullLength_Z;

      G4double           CoilFramePlate_CenterPositionInR;
      G4double           CoilFramePlate_CenterPositionInZ;

      G4LogicalVolume*   SingleCoil_FramePlate_Logical;
      G4Material*        SingleCoil_FramePlate_Material;

      std::vector< G4VPhysicalVolume* > SingleCoil_FramePlate_Physical;

      std::vector< G4ThreeVector >      Translation_FramePlate;

      std::vector< G4double >           Angle_FramePlate;
      std::vector< G4RotationMatrix* >  Rotation_FramePlate;

      // needed for mini clamp chamfer
      std::vector< G4SubtractionSolid* >  FramePlateTemp_Solid;

      // mini clamp chamfer dimensions
      G4RotationMatrix Rotation_SubtractionCylinder;
      G4RotationMatrix Rotation_SubtractionBox;

      G4double         Subtraction_Cylinder_Diameter;
      G4double         Subtraction_Cylinder_Height;

      G4double         Subtraction_CenterBox_FullLength_X;
      G4double         Subtraction_CenterBox_FullLength_Y;
      G4double         Subtraction_CenterBox_FullLength_Z;

      G4double         Subtraction_DownstreamBox_FullLength_X;
      G4double         Subtraction_DownstreamBox_FullLength_Y;
      G4double         Subtraction_DownstreamBox_FullLength_Z;


      // placing the solids for subtraction
      G4ThreeVector    Position_UpstreamCylinder; // upstream
      G4ThreeVector    Position_DownstreamCylinder; // downstream
      G4ThreeVector    Position_CenterBox;
      G4ThreeVector    Position_DownstreamBox;

      G4VisAttributes* SingleCoil_FramePlate_VisAtt;

     //---------------------------------------

      //-----------------------------------------
      // needed for the radial mounting blocks
      //-----------------------------------------
      //
      G4double           RadialMountingBlock_FullLength_X;
      G4double           RadialMountingBlock_FullLength_Y;
      G4double           RadialMountingBlock_FullLength_Z;

      G4double           RadialMountingBlock_CenterPositionInR;
      G4double           RadialMountingBlock_UpstreamPositionInZ;
      G4double           RadialMountingBlock_DownstreamPositionInZ;

      G4LogicalVolume*   SingleCoil_RadialMountingBlock_Logical;
      G4Material*        SingleCoil_RadialMountingBlock_Material;


      std::vector< G4VPhysicalVolume* > SingleCoil_LeftRadialMountingBlock_Upstream_Physical;
      std::vector< G4VPhysicalVolume* > SingleCoil_RightRadialMountingBlock_Upstream_Physical;

      std::vector< G4VPhysicalVolume* > SingleCoil_LeftRadialMountingBlock_Downstream_Physical;
      std::vector< G4VPhysicalVolume* > SingleCoil_RightRadialMountingBlock_Downstream_Physical;

      std::vector< G4ThreeVector >      Translation_LeftRadialMountingBlock_Upstream;
      std::vector< G4ThreeVector >      Translation_RightRadialMountingBlock_Upstream;

      std::vector< G4ThreeVector >      Translation_LeftRadialMountingBlock_Downstream;
      std::vector< G4ThreeVector >      Translation_RightRadialMountingBlock_Downstream;

      std::vector< G4double >           Angle_RadialMountingBlock;
      std::vector< G4RotationMatrix* >  Rotation_RadialMountingBlock;

      G4VisAttributes* SingleCoil_RadialMountingBlock_VisAtt;

      //-----------------------------------------
      // needed for the support structure
      //-----------------------------------------
      //
      G4double SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_X;
      G4double SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Y;
      G4double SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Z;

      G4double SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_X;
      G4double SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Y;
      G4double SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Z;


      G4double SupportFrame_DownstreamDoubleTBeamSlab_Thickness;
      G4double SupportFrame_DownstreamDoubleTBeamRib_Thickness;

      G4double positionInZ_DownstreamDoubleTBeam;


      G4LogicalVolume* SupportFrame_DownstreamHorizontalDoubleTBeam_Logical;
      G4LogicalVolume* SupportFrame_DownstreamVerticalDoubleTBeam_Logical;

      G4Material*      SupportFrame_Material;

      std::vector< G4SubtractionSolid* >  SupportFrameSubtraction_TempSolid;
      std::vector< G4UnionSolid* >        SupportFrameUnion_TempSolid;

      std::vector< G4ThreeVector >        Translation_DownstreamHorizontalDoubleTBeam;
      std::vector< G4ThreeVector >        Translation_DownstreamVerticalDoubleTBeam;


      std::vector< G4VPhysicalVolume* >   SupportFrame_DownstreamHorizontalDoubleTBeam_Physical;
      std::vector< G4VPhysicalVolume* >   SupportFrame_DownstreamVerticalDoubleTBeam_Physical;

      G4VisAttributes* SupportFrame_DownstreamHorizontalDoubleTBeam_VisAtt;
      G4VisAttributes* SupportFrame_DownstreamVerticalDoubleTBeam_VisAtt;

      //------------------------------------------------------------
      // Downstream Double-T-Beam orientated at +-45 and +-135 deg
      //------------------------------------------------------------

      G4double SupportFrame_Downstream45DegDoubleTBeam_FullLength_X;
      G4double SupportFrame_Downstream45DegDoubleTBeam_FullLength_Y;
      G4double SupportFrame_Downstream45DegDoubleTBeam_FullLength_Z;

      G4double SupportFrame_Downstream45DegDoubleTBeamSlab_Thickness;
      G4double SupportFrame_Downstream45DegDoubleTBeamRib_Thickness;

      G4double positionInZ_Downstream45DegDoubleTBeam;
      G4double DoubleTBeam45Deg_CenterPositionInR;

      G4LogicalVolume* SupportFrame_Downstream45DegDoubleTBeam_Logical;

      std::vector< G4ThreeVector >        Translation_Downstream45DegDoubleTBeam;
      std::vector< G4VPhysicalVolume* >   SupportFrame_Downstream45DegDoubleTBeam_Physical;

      std::vector< G4double >             Angle_DoubleTBeam45Deg;
      std::vector< G4RotationMatrix* >    Rotation_DoubleTBeam45Deg;

      G4VisAttributes* SupportFrame_Downstream45DegDoubleTBeam_VisAtt;

      //------------------------------------
      // Downstream Spider and radial slabs
      //------------------------------------
      //
      G4double DownstreamSpider_DiameterMin;
      G4double DownstreamSpider_DiameterMax;
      G4double DownstreamSpider_FullThickness;
      G4double DownstreamSpider_PhiAngleStart;
      G4double DownstreamSpider_PhiDeltaAngle;

      G4double DownstreamSpider_CenterPositionInZ;

      std::vector< G4SubtractionSolid* >  DownstreamSpider_TempSubtractionSolid;

      G4LogicalVolume*                    DownstreamSpider_Logical;
      G4VPhysicalVolume*                  DownstreamSpider_Physical;

      // for lintels, Peiqing Mar. 2012 
      G4double Lintel_FullLength_X;
      G4double Lintel_FullLength_Y;
      G4double Lintel_FullLength_Z;
      G4double Lintel_CenterPositionInR;
      G4double Lintel_Tilt_Angle;
      G4LogicalVolume*   Lintel_Logical;
      G4Material*        Lintel_Material;
      std::vector< G4VPhysicalVolume* > Lintel_Physical;
      std::vector< G4ThreeVector >      Translation_Lintel;
      std::vector< G4double >           Angle_Lintel;
      std::vector< G4RotationMatrix* >  Rotation_Lintel;
      G4VisAttributes* Lintel_VisAtt;
      
      G4VisAttributes* DownstreamSpider_VisAtt;

      //------

      G4double DownstreamSpider_RadialSlab_FullLength_X;
      G4double DownstreamSpider_RadialSlab_FullLength_Y;
      G4double DownstreamSpider_RadialSlab_FullLength_Z;

      G4double DownstreamSpider_RadialSlab_CenterPositionInR;
      G4double DownstreamSpider_RadialSlab_CenterPositionInZ;

      G4LogicalVolume*                    DownstreamSpider_RadialSlab_Logical;

      std::vector< G4ThreeVector >        Translation_DownstreamSpider_RadialSlab;
      std::vector< G4VPhysicalVolume* >   DownstreamSpider_RadialSlab_Physical;

      std::vector< G4double >             Angle_DownstreamSpider_RadialSlab;
      std::vector< G4RotationMatrix* >    Rotation_DownstreamSpider_RadialSlab;

      G4VisAttributes* DownstreamSpider_RadialSlab_VisAtt;
      

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

