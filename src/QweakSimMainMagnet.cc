//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimMainMagnet.cc

   $Revision: 1.8 $	
   $Date: 2006/01/20 21:14:33 $

   \author Klaus Hans Grimm   

*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimMainMagnet.hh"

// geant4 includes
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

// user includes
#include "QweakSimMaterial.hh"
#include "QweakSimMagnet_CoilParameterisation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimMainMagnet::QweakSimMainMagnet() 
{
    G4cout << G4endl << "###### Calling QweakSimMainMagnet::QweakSimMainMagnet() " << G4endl << G4endl;

    // initialize pointers here, order does NOT matter
    pMaterial                            = NULL;
    MM_SingleCoilParam                   = NULL;

    MainMagnet_MasterContainer_Logical   = NULL;
    MainMagnet_MasterContainer_Physical  = NULL;
    MainMagnet_MasterContainer_Material  = NULL;

    SingleCoil_MasterContainer_Logical   = NULL;
    SingleCoil_MasterContainer_Material  = NULL;

    SingleCoil_Material                  = NULL;

    SingleCoil_Plate_Logical             = NULL;
    SingleCoil_Wing_Logical              = NULL; 
  
    UpstreamSpider_Tube_Subtraction_Logical = NULL;
    UpstreamSpider_Box_Subtraction_Logical  = NULL;
    UpstreamSpider_Box_Union_Logical        = NULL;

    UpstreamSpider_Logical                  = NULL;
    UpstreamSpider_Physical                 = NULL;
    UpstreamSpider_Material                 = NULL;

    UpstreamSpider_LowThetaCutoutLeft_Logical    = NULL;
    UpstreamSpider_LowThetaCutoutLeft_Physical   = NULL;
    UpstreamSpider_LowThetaCutoutRight_Logical   = NULL;
    UpstreamSpider_LowThetaCutoutRight_Physical  = NULL;
    UpstreamSpider_LowThetaCutoutFinal_Logical   = NULL;
    UpstreamSpider_LowThetaCutoutFinal_Physical  = NULL;

    //---
    Angle_Lintel.clear();
    Angle_Lintel.resize(8);

    Rotation_Lintel.clear();
    Rotation_Lintel.resize(8);

    Translation_Lintel.clear();
    Translation_Lintel.resize(8);
    
    Lintel_Logical                   = NULL;
    Lintel_Material                  = NULL;
    
    Lintel_Physical.clear();
    Lintel_Physical.resize(8);
    
    //---
    Angle_SingleCoil.clear();
    Angle_SingleCoil.resize(8);

    Rotation_SingleCoil.clear();
    Rotation_SingleCoil.resize(8);

    Translation_SingleCoil.clear();
    Translation_SingleCoil.resize(8);

    //---

    SingleCoil_UpperPlate_Physical.clear();
    SingleCoil_UpperPlate_Physical.resize(8);

    Translation_SingleCoil_UpperPlate.clear();
    Translation_SingleCoil_UpperPlate.resize(8);

    SingleCoil_LowerPlate_Physical.clear();
    SingleCoil_LowerPlate_Physical.resize(8);

    Translation_SingleCoil_LowerPlate.clear();
    Translation_SingleCoil_LowerPlate.resize(8);

    //---
 
    SingleCoil_LeftWing_Physical.clear();
    SingleCoil_LeftWing_Physical.resize(8);

    Rotation_SingleCoil_LeftWing.clear();
    Rotation_SingleCoil_LeftWing.resize(8);

    Translation_SingleCoil_LeftWing.clear();
    Translation_SingleCoil_LeftWing.resize(8);


    SingleCoil_RightWing_Physical.clear();
    SingleCoil_RightWing_Physical.resize(8);

    Rotation_SingleCoil_RightWing.clear();
    Rotation_SingleCoil_RightWing.resize(8);

    Translation_SingleCoil_RightWing.clear();
    Translation_SingleCoil_RightWing.resize(8);

    SingleCoil_VisAtt = NULL;
    SingleCoil_VisAtt = new G4VisAttributes();
    
    Lintel_VisAtt = NULL;
    Lintel_VisAtt = new G4VisAttributes();

    //---

    // clear vector containing temp solids for boolean soild subtractions
    MyUpstreamSpider_Solid.clear();
    MyUpstreamSpider_Solid.resize(24); // 16 tube-holes + 8 plate-hole


    // clear vector containing temp solids for boolean soild subtractions
    MyUpstreamSpider_LowThetaCutout_Solid.clear();
    MyUpstreamSpider_LowThetaCutout_Solid.resize(3); // 2 union tubes

    // for merging radial struts to upstream spider 
    MyUpstreamSpider_StrutsUnion_Solid.clear();
    MyUpstreamSpider_StrutsUnion_Solid.resize(8);

    UpstreamSpider_VisAtt = NULL;
    UpstreamSpider_VisAtt = new G4VisAttributes();

    //---------------------
    // large clamp plates
    //---------------------
    SingleCoil_ClampPlate_Logical   = NULL;

    SingleCoil_ClampPlate_Material  = NULL;

    SingleCoil_LeftClampPlate_Physical.clear();
    SingleCoil_LeftClampPlate_Physical.resize(8);

    SingleCoil_RightClampPlate_Physical.clear();
    SingleCoil_RightClampPlate_Physical.resize(8);

    Translation_LeftClampPlate.clear();
    Translation_LeftClampPlate.resize(8);

    Translation_RightClampPlate.clear();
    Translation_RightClampPlate.resize(8);

    Angle_ClampPlate.clear();
    Angle_ClampPlate.resize(8);

    Rotation_ClampPlate.clear();
    Rotation_ClampPlate.resize(8);

    SingleCoil_ClampPlate_VisAtt = NULL; 
    SingleCoil_ClampPlate_VisAtt = new G4VisAttributes(); 

    //---------------------------
    // Upstream mini clamp plates
    //----------------------------
    SingleCoil_LeftMiniClampPlate_Logical    = NULL;
    SingleCoil_RightMiniClampPlate_Logical   = NULL;
    SingleCoil_MiniClampPlate_Material       = NULL;

    SingleCoil_LeftMiniClampPlate_Physical.clear();
    SingleCoil_LeftMiniClampPlate_Physical.resize(8);

    SingleCoil_RightMiniClampPlate_Physical.clear();
    SingleCoil_RightMiniClampPlate_Physical.resize(8);

    Translation_LeftMiniClampPlate.clear();
    Translation_LeftMiniClampPlate.resize(8);

    Translation_RightMiniClampPlate.clear();
    Translation_RightMiniClampPlate.resize(8);

    Angle_MiniClampPlate.clear();
    Angle_MiniClampPlate.resize(8);

    Rotation_MiniClampPlate.clear();
    Rotation_MiniClampPlate.resize(8);
    
    // clear vector containing temp solids for mini clamp chamfers
    MiniClampPlateTemp_Solid.clear();
    MiniClampPlateTemp_Solid.resize(4); //need 4 chamfers

    SingleCoil_MiniClampPlate_VisAtt = NULL; 
    SingleCoil_MiniClampPlate_VisAtt = new G4VisAttributes(); 

   //--------------------------------------------
   // Frame plate in which the coil is embedded
   //--------------------------------------------
   SingleCoil_FramePlate_Logical    = NULL;
   SingleCoil_FramePlate_Material   = NULL;

   SingleCoil_FramePlate_Physical.clear();
   SingleCoil_FramePlate_Physical.resize(8);
 
   Translation_FramePlate.clear();
   Translation_FramePlate.resize(8);
   
   Angle_FramePlate.clear();
   Angle_FramePlate.resize(8);
   
   Rotation_FramePlate.clear();
   Rotation_FramePlate.resize(8);
   
   // clear vector containing temp solids for mini clamp chamfers
   FramePlateTemp_Solid.clear();
   FramePlateTemp_Solid.resize(4); //need 4 solid for subtraction

   SingleCoil_FramePlate_VisAtt = NULL;
   SingleCoil_FramePlate_VisAtt = new G4VisAttributes(); 

   //--------------------------------------------
   // Radial Mounting Blocks 
   //--------------------------------------------
   //
   SingleCoil_RadialMountingBlock_Logical    = NULL;
   SingleCoil_RadialMountingBlock_Material   = NULL;

   SingleCoil_LeftRadialMountingBlock_Upstream_Physical.clear();
   SingleCoil_LeftRadialMountingBlock_Upstream_Physical.resize(8);

   SingleCoil_RightRadialMountingBlock_Upstream_Physical.clear();
   SingleCoil_RightRadialMountingBlock_Upstream_Physical.resize(8);
   
   SingleCoil_LeftRadialMountingBlock_Downstream_Physical.clear();
   SingleCoil_LeftRadialMountingBlock_Downstream_Physical.resize(8);

   SingleCoil_RightRadialMountingBlock_Downstream_Physical.clear();
   SingleCoil_RightRadialMountingBlock_Downstream_Physical.resize(8);

   Translation_LeftRadialMountingBlock_Upstream.clear();
   Translation_LeftRadialMountingBlock_Upstream.resize(8);

   Translation_RightRadialMountingBlock_Upstream.clear();
   Translation_RightRadialMountingBlock_Upstream.resize(8);
   
   Translation_LeftRadialMountingBlock_Downstream.clear();
   Translation_LeftRadialMountingBlock_Downstream.resize(8);

   Translation_RightRadialMountingBlock_Downstream.clear();
   Translation_RightRadialMountingBlock_Downstream.resize(8);
   
   Angle_RadialMountingBlock.clear();
   Angle_RadialMountingBlock.resize(8);
   
   Rotation_RadialMountingBlock.clear();
   Rotation_RadialMountingBlock.resize(8);

   SingleCoil_RadialMountingBlock_VisAtt = NULL; 
   SingleCoil_RadialMountingBlock_VisAtt = new G4VisAttributes(); 

   //--------------------------------------------
   // Downstream support frame , general
   //--------------------------------------------
   //
   SupportFrameSubtraction_TempSolid.clear();
   SupportFrameSubtraction_TempSolid.resize(10);

   SupportFrameUnion_TempSolid.clear();
   SupportFrameUnion_TempSolid.resize(10);

   //------------------------------------------------------------
   // Downstream Double-T-Beam orientated horizontal and vertical
   //------------------------------------------------------------
   //

   SupportFrame_DownstreamHorizontalDoubleTBeam_Logical = NULL;
   SupportFrame_DownstreamVerticalDoubleTBeam_Logical   = NULL;
   SupportFrame_Material                                = NULL;

   SupportFrame_DownstreamHorizontalDoubleTBeam_Physical.clear();
   SupportFrame_DownstreamHorizontalDoubleTBeam_Physical.resize(4); 

   SupportFrame_DownstreamVerticalDoubleTBeam_Physical.clear();
   SupportFrame_DownstreamVerticalDoubleTBeam_Physical.resize(4); 

   Translation_DownstreamHorizontalDoubleTBeam.clear();
   Translation_DownstreamHorizontalDoubleTBeam.resize(4);

   Translation_DownstreamVerticalDoubleTBeam.clear();
   Translation_DownstreamVerticalDoubleTBeam.resize(4);

   SupportFrame_DownstreamHorizontalDoubleTBeam_VisAtt = NULL;
   SupportFrame_DownstreamHorizontalDoubleTBeam_VisAtt = new G4VisAttributes();

   SupportFrame_DownstreamVerticalDoubleTBeam_VisAtt = NULL;
   SupportFrame_DownstreamVerticalDoubleTBeam_VisAtt = new G4VisAttributes();
   

   //------------------------------------------------------------
   // Downstream Double-T-Beam orientated at +-45 and +-135 deg
   //------------------------------------------------------------
   //
   SupportFrame_Downstream45DegDoubleTBeam_Logical = NULL;

   Translation_Downstream45DegDoubleTBeam.clear();
   Translation_Downstream45DegDoubleTBeam.resize(4);

   SupportFrame_Downstream45DegDoubleTBeam_Physical.clear();
   SupportFrame_Downstream45DegDoubleTBeam_Physical.resize(4);

   Angle_DoubleTBeam45Deg.clear();
   Angle_DoubleTBeam45Deg.resize(4);

   Rotation_DoubleTBeam45Deg.clear();
   Rotation_DoubleTBeam45Deg.resize(4);

   SupportFrame_Downstream45DegDoubleTBeam_VisAtt = NULL;
   SupportFrame_Downstream45DegDoubleTBeam_VisAtt = new G4VisAttributes();

   //------------------------------------------------------------
   // Downstream Spider and radial slabs
   //------------------------------------------------------------
   //
   DownstreamSpider_Logical  = NULL;
   DownstreamSpider_Physical = NULL;

   DownstreamSpider_VisAtt = NULL;
   DownstreamSpider_VisAtt = new G4VisAttributes();

   DownstreamSpider_TempSubtractionSolid.clear();
   DownstreamSpider_TempSubtractionSolid.resize(20);

   //-----

   DownstreamSpider_RadialSlab_VisAtt = NULL;
   DownstreamSpider_RadialSlab_VisAtt = new G4VisAttributes();

   DownstreamSpider_RadialSlab_Physical.clear();
   DownstreamSpider_RadialSlab_Physical.resize(8);

   Angle_DownstreamSpider_RadialSlab.clear();
   Angle_DownstreamSpider_RadialSlab.resize(8);

   Rotation_DownstreamSpider_RadialSlab.clear();
   Rotation_DownstreamSpider_RadialSlab.resize(8);

   Translation_DownstreamSpider_RadialSlab.clear();
   Translation_DownstreamSpider_RadialSlab.resize(8);

   //-------------------------------------------------------------------------------------


    // get access to material definition
  pMaterial = new QweakSimMaterial();
  pMaterial -> DefineMaterials();

  // get material
  MainMagnet_MasterContainer_Material      = pMaterial->GetMaterial("HeGas"); 
  SingleCoil_MasterContainer_Material      = pMaterial->GetMaterial("HeGas"); 
  SingleCoil_Material                      = pMaterial->GetMaterial("Copper"); 
  UpstreamSpider_Material                  = pMaterial->GetMaterial("Aluminum");
  SingleCoil_ClampPlate_Material           = pMaterial->GetMaterial("Aluminum"); 
  SingleCoil_MiniClampPlate_Material       = pMaterial->GetMaterial("Aluminum"); 
  SingleCoil_FramePlate_Material           = pMaterial->GetMaterial("Aluminum"); 
  SingleCoil_RadialMountingBlock_Material  = pMaterial->GetMaterial("Aluminum");
  SupportFrame_Material                    = pMaterial->GetMaterial("Aluminum");
  Lintel_Material                          = pMaterial->GetMaterial("PBA");
  
  // define MainMagnet_MasterContainer geometry values
  // The MainMagnet_MasterContainer contains everything related to the MiniTorus
  //
  MainMagnet_MasterContainer_FullLength_X = 800.0*cm;    // Full X length 
  MainMagnet_MasterContainer_FullLength_Y = 800.0*cm;    // Full Y length 
  MainMagnet_MasterContainer_FullLength_Z = 450.0*cm;    // Full Z length , Coil_diameter= 52.50*cm

  // set default for origin (taken from Juliette's euclid file) in MotherVolume
  MainMagnet_CenterPositionInZ = 0.0*cm;
  
  // define a single coil
  SingleCoil_FullThickness   =  11.842*cm; // without expoxy mold
  
  // Distance of Copper Plates to BeamLine : See SolidWorks
  SingleCoil_MinimalRadialDistance = 17.78*cm;
  
  SingleCoil_MasterContainer_FullLength_X = SingleCoil_FullThickness + 0.1*mm;
  SingleCoil_MasterContainer_FullLength_Y = 193.0*cm; 
  SingleCoil_MasterContainer_FullLength_Z = 435.0*cm; 

 // Distance of a Single Copper Coil Center to BeamLine : See SolidWorks
  SingleCoil_CenterPositionInR = 0.5*SingleCoil_MasterContainer_FullLength_Y + SingleCoil_MinimalRadialDistance;

// define a single coil disk for union
  SingleCoil_Wing_DiameterMin   =  2.0*21.6*cm;
  SingleCoil_Wing_DiameterMax   =  2.0*73.0*cm;
 
  //Left: downstream
  SingleCoil_Wing_PhiAngleStart  =   90.0*degree; // OK
  SingleCoil_Wing_PhiDeltaAngle  =  180.0*degree; //OK

  // part of the coil: plate
  // using the coodinate system as for SingleCoil_MasterContainer_FullLength
  // since I will place the plate into the MasterContainer
  SingleCoil_Plate_FullLength_X = SingleCoil_FullThickness;
  SingleCoil_Plate_FullLength_Y = 0.5*(SingleCoil_Wing_DiameterMax - SingleCoil_Wing_DiameterMin);
  SingleCoil_Plate_FullLength_Z = 220.0*cm;

//   SingleCoil_Plate_FullLength_X = 1.0*cm;
//   SingleCoil_Plate_FullLength_Y = 1.0*cm;
//   SingleCoil_Plate_FullLength_Z = 1.0*cm;


// define a single coil disk for union
  UpstreamSpider_DiameterMin    =  2.0* 6.5*2.56*cm; //SW: 13 inch inner diameter hole
  UpstreamSpider_DiameterMax    =  2.0*17.5*2.56*cm; //SW: 31 inch outer diameter + some extra inches for subtraction
  UpstreamSpider_FullThickness  =    1.0*2.56*cm; //SW
  UpstreamSpider_PhiAngleStart  =    0.0*degree; // OK
  UpstreamSpider_PhiDeltaAngle  =  360.0*degree;  //OK

  UpstreamSpider_CenterPositionInZ = -87.5625*2.54*cm; //SW


  // Large Clamp Plate mounted on both sides of a coil
  // values are checked with SW
  ClampPlate_FullLength_X      =     1.25*2.54*cm;  // thickness
  ClampPlate_FullLength_Y      =    36.00*2.54*cm;  // height
  ClampPlate_FullLength_Z      =   152.50*2.54*cm;  // length along beam axis
  ClampPlate_CenterPositionInR =  23.54*2.54*cm + SingleCoil_CenterPositionInR -0.5*(SingleCoil_MasterContainer_FullLength_Y - SingleCoil_Wing_DiameterMax) -0.1*mm; // from SW

  // Upstream Mini Clamp Plate mounted on both sides of a coil
  // values are checked with SW
  MiniClampPlate_FullLength_X      =  1.25*2.54*cm;  // thickness
  MiniClampPlate_FullLength_Y      =  9.00*2.54*cm;  // height
  MiniClampPlate_FullLength_Z      = 23.00*2.54*cm;  // length along beam axis

  MiniClampPlate_CenterPositionInR =  -22.25*2.54*cm + SingleCoil_CenterPositionInR -0.5*(SingleCoil_MasterContainer_FullLength_Y - SingleCoil_Wing_DiameterMax) ; // from SW

  //MiniClampPlate_CenterPositionInR =  30.0*cm; 
  MiniClampPlate_CenterPositionInZ =  -78.312*2.54*cm + 0.5*MiniClampPlate_FullLength_Z;  // from SW

  // dimension of mini clamp chamfer solid
  Chamfer_FullLength_X   =  sqrt(2.0)*1.27*cm;  // thickness 
  Chamfer_FullLength_Y   =   5.00*cm;  // height
  Chamfer_FullLength_Z   =  70.00*cm;  // length along beam axis



  //-------------------------------------------
  // outer plate in which the coil is embedded
  //-------------------------------------------

  // Large Plate 
  // values are checked with SW
  CoilFramePlate_FullLength_X      =     5.00*2.54*cm;  // thickness
  CoilFramePlate_FullLength_Y      =    76.00*2.54*cm;  // height
  CoilFramePlate_FullLength_Z      =   171.25*2.54*cm;  // length along beam axis

  // extracted from SW
  CoilFramePlate_CenterPositionInR =  10.00*2.54*cm + SingleCoil_CenterPositionInR -0.5*(SingleCoil_MasterContainer_FullLength_Y - SingleCoil_Wing_DiameterMax) -0.1*mm; 
  
  CoilFramePlate_CenterPositionInZ =  0.0*cm;  // from SW

  // dimension of solids for subtraction
  Subtraction_Cylinder_Diameter             =  29.75*2.54*cm;
  Subtraction_Cylinder_Height               =   6.00*2.54*cm ;

  Subtraction_CenterBox_FullLength_X        =     6.00*2.54*cm;
  Subtraction_CenterBox_FullLength_Y        =  2*29.75*2.54*cm;
  Subtraction_CenterBox_FullLength_Z        =    87.25*2.54*cm;

  Subtraction_DownstreamBox_FullLength_X    =   6.00*2.54*cm;
  Subtraction_DownstreamBox_FullLength_Y    =  CoilFramePlate_FullLength_Y;
  Subtraction_DownstreamBox_FullLength_Z    =  80.00*2.54*cm;  //arbitrary


  //------------------------
  // radial mounting blocks
  //------------------------

  RadialMountingBlock_FullLength_X             =  2.500*2.54*cm;  // horizontal thickness
  RadialMountingBlock_FullLength_Y             = 43.125*2.54*cm;  // vertical height
  RadialMountingBlock_FullLength_Z             =  5.000*2.54*cm;  // length along z

  RadialMountingBlock_CenterPositionInR        = 21.06*2.54*cm + SingleCoil_CenterPositionInR -0.5*(SingleCoil_MasterContainer_FullLength_Y - SingleCoil_Wing_DiameterMax);
  RadialMountingBlock_UpstreamPositionInZ      = -0.5*CoilFramePlate_FullLength_Z + 0.5*RadialMountingBlock_FullLength_Z - 1.000*2.54*cm;
  RadialMountingBlock_DownstreamPositionInZ    = +0.5*CoilFramePlate_FullLength_Z - 0.5*RadialMountingBlock_FullLength_Z + 1.000*2.54*cm;


  //-----------------------------------------
  // downstream support structure
  //-----------------------------------------
  //
  SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_X = 236.000*2.54*cm;
  SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Y =   7.000*2.54*cm;
  SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Z =  12.000*2.54*cm;

  SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_X   =   7.000*2.54*cm;
  SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Y   = 264.000*2.54*cm;
  SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Z   =  12.000*2.54*cm;

  SupportFrame_DownstreamDoubleTBeamSlab_Thickness          =   0.620*2.54*cm;
  SupportFrame_DownstreamDoubleTBeamRib_Thickness           =   0.310*2.54*cm;

  positionInZ_DownstreamDoubleTBeam                         = 94.188*2.54*cm;

  //------------------------------------------------------------
  // Downstream Double-T-Beam orientated at +-45 and +-135 deg
  //------------------------------------------------------------
  //
  // dimension before rotation, horizontal layout
  SupportFrame_Downstream45DegDoubleTBeam_FullLength_X     =  97.754*2.54*cm; // horizontal
  SupportFrame_Downstream45DegDoubleTBeam_FullLength_Y     =   7.000*2.54*cm; // vertical
  SupportFrame_Downstream45DegDoubleTBeam_FullLength_Z     =  12.000*2.54*cm; // along beam

  SupportFrame_Downstream45DegDoubleTBeamSlab_Thickness    = 0.620*2.54*cm;
  SupportFrame_Downstream45DegDoubleTBeamRib_Thickness     = 0.438*2.54*cm;

  positionInZ_Downstream45DegDoubleTBeam                   =  94.188*2.54*cm;
  DoubleTBeam45Deg_CenterPositionInR                       =  0.5*sqrt(2*(83.439 + 0.5*SupportFrame_Downstream45DegDoubleTBeam_FullLength_Y)
								    *(83.439 + 0.5*SupportFrame_Downstream45DegDoubleTBeam_FullLength_Y) )*2.54*cm;

  //------------------------------------
  // Downstream Spider and radial slabs 
  //------------------------------------
  //

  DownstreamSpider_DiameterMin    =   51.000*2.56*cm;   //SW
  DownstreamSpider_DiameterMax    =   75.000*2.56*cm;   //SW
  DownstreamSpider_FullThickness  =    1.000*2.56*cm;   //SW
  DownstreamSpider_PhiAngleStart  =    0.0*degree;      // OK
  DownstreamSpider_PhiDeltaAngle  =  360.0*degree;      //OK
 
  DownstreamSpider_CenterPositionInZ =  88.690*2.54*cm; //SW + safety gap
 
  //--- 
  // unrotated slab is orientated vertically
  //
  DownstreamSpider_RadialSlab_FullLength_X         =  11.500*2.54*cm; // horizontal == width 
  DownstreamSpider_RadialSlab_FullLength_Y         = 103.000*2.54*cm; // vertical   == height
  DownstreamSpider_RadialSlab_FullLength_Z         =   1.000*2.54*cm; // along z    == thickness
  
  DownstreamSpider_RadialSlab_CenterPositionInR    =  34.250*2.54*cm +0.5*DownstreamSpider_RadialSlab_FullLength_Y;
  DownstreamSpider_RadialSlab_CenterPositionInZ    =  87.680*2.54*cm; // original: 87.688
  
  Lintel_FullLength_X = 70.0*cm;
  Lintel_FullLength_Y = 16.0*cm;
  Lintel_FullLength_Z = 10.0*cm;
  Lintel_CenterPositionInR = -129.39*cm;
  Lintel_Tilt_Angle = -20.0*degree;
  //===============================================================================

  G4cout << G4endl << "###### Leaving QweakSimMainMagnet::QweakSimMainMagnet " << G4endl << G4endl;
}	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimMainMagnet::~QweakSimMainMagnet()
{  
G4cout << G4endl << "###### Calling QweakSimMainMagnet::~QweakSimMainMagnet() " << G4endl << G4endl;

      if (pMaterial) delete pMaterial;

G4cout << G4endl << "###### Leaving QweakSimMainMagnet::~QweakSimMainMagnet() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMainMagnet::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
G4cout << G4endl << "###### Calling QweakSimMainMagnet::ConstructComponent() " << G4endl << G4endl;

   // define center position of SingleCoil_MasterContainer inside the MainMagnet_MasterContainer
    G4ThreeVector positionSingleCoilContainer = G4ThreeVector(0,0,0);

    // define MainMagnet SingleCoil Container solid volume
    G4cout << G4endl << "###### QweakSimMainMagnet: Define MainMagnet_MasterContainer_Solid " << G4endl << G4endl;

    //----------------------------------------------------------
    
    G4double Offset_SingleCoilWithinMasterContainer =
	0.5*(SingleCoil_MasterContainer_FullLength_Y - SingleCoil_Wing_DiameterMax) -0.1*mm;
    
    G4Box* SingleCoil_Plate_Solid    = new G4Box("SingleCoil_Plate_Solid",
						 0.5 * SingleCoil_Plate_FullLength_X,    // horizontal == thickness
						 0.5 * SingleCoil_Plate_FullLength_Y,    // vertical == height
						 0.5 * SingleCoil_Plate_FullLength_Z );  // length
    
     
    SingleCoil_Plate_Logical  = new G4LogicalVolume( SingleCoil_Plate_Solid,
						      SingleCoil_Material,
                                                     "SingleCoil_Plate_Logical",
						      0,
						      0,0);
     

     // Y (or radial) offset of the upper/lowe plate relative to the local single coil origin
     G4double RadialOffset_Plate = 0.5*(SingleCoil_Plate_FullLength_Y + SingleCoil_Wing_DiameterMin);

     // Global position in R
     G4double SingleCoil_UpperPlate_CenterPositionInR = +1.0*RadialOffset_Plate - Offset_SingleCoilWithinMasterContainer + SingleCoil_CenterPositionInR; 
     G4double SingleCoil_LowerPlate_CenterPositionInR = -1.0*RadialOffset_Plate - Offset_SingleCoilWithinMasterContainer + SingleCoil_CenterPositionInR; 

     //----------------------------------------------------------

     G4cout << G4endl << "###### QweakSimMainMagnet: Define SingleCoil C Shape Solid" << G4endl << G4endl;

     G4Tubs*  SingleCoil_Wing_Solid    =  new G4Tubs("SingleCoil_Wing_Solid",
						     0.5*SingleCoil_Wing_DiameterMin,
						     0.5*SingleCoil_Wing_DiameterMax,
						     0.5*SingleCoil_FullThickness,
						     SingleCoil_Wing_PhiAngleStart,
						     SingleCoil_Wing_PhiDeltaAngle
						     );

     SingleCoil_Wing_Logical  = new G4LogicalVolume( SingleCoil_Wing_Solid,
						      SingleCoil_Material,
						     "SingleCoil_Wing_Log",
						     0,
						     0,0);


     // Global position in R
     G4double SingleCoil_Wings_CenterPositionInR =  SingleCoil_CenterPositionInR - Offset_SingleCoilWithinMasterContainer; 
     G4double HorizontalOffset_Wing              = 0.5*SingleCoil_Plate_FullLength_Z;

     //----------------------------------------------------------

     // place 8 SingleCoil_MasterContainer_Logical plates into the MotherVolume (around the global Z axis)
     for (G4int n=0; n<8; n++) {

	 Angle_SingleCoil[n] = n*45.0*degree + 22.5*degree;

	 Rotation_SingleCoil[n] = new G4RotationMatrix();
	 Rotation_SingleCoil[n]->rotateZ(Angle_SingleCoil[n]);

	 //----------------------------------------

	 Translation_SingleCoil_UpperPlate[n].setX(sin(Angle_SingleCoil[n])*SingleCoil_UpperPlate_CenterPositionInR);
	 Translation_SingleCoil_UpperPlate[n].setY(cos(Angle_SingleCoil[n])*SingleCoil_UpperPlate_CenterPositionInR);
	 Translation_SingleCoil_UpperPlate[n].setZ(0.0*cm);

         Translation_SingleCoil_LowerPlate[n].setX(sin(Angle_SingleCoil[n])*SingleCoil_LowerPlate_CenterPositionInR);
         Translation_SingleCoil_LowerPlate[n].setY(cos(Angle_SingleCoil[n])*SingleCoil_LowerPlate_CenterPositionInR);
         Translation_SingleCoil_LowerPlate[n].setZ(0.0*cm);


	 SingleCoil_UpperPlate_Physical[n] = new G4PVPlacement( Rotation_SingleCoil[n],
								Translation_SingleCoil_UpperPlate[n],
								"SingleCoil_UpperPlate_Physical",
								SingleCoil_Plate_Logical,
								MotherVolume,
								false,
								n,
								pSurfChk);


	 SingleCoil_LowerPlate_Physical[n] = new G4PVPlacement( Rotation_SingleCoil[n],
								Translation_SingleCoil_LowerPlate[n],
								"SingleCoil_LowerPlate_Physical",
								SingleCoil_Plate_Logical,
								MotherVolume,
								false,
								n,
								pSurfChk);

	 //----------------------------------------

	 Rotation_SingleCoil_LeftWing[n] = new G4RotationMatrix();
	 Rotation_SingleCoil_LeftWing[n]->rotateY(90.0*degree);
	 Rotation_SingleCoil_LeftWing[n]->rotateX(Angle_SingleCoil[n]);


	 Rotation_SingleCoil_RightWing[n] = new G4RotationMatrix();
	 Rotation_SingleCoil_RightWing[n]->rotateY(-90.0*degree);
	 Rotation_SingleCoil_RightWing[n]->rotateX(-1*Angle_SingleCoil[n]);
     

	 Translation_SingleCoil_LeftWing[n].setX(sin(Angle_SingleCoil[n])*SingleCoil_Wings_CenterPositionInR);
	 Translation_SingleCoil_LeftWing[n].setY(cos(Angle_SingleCoil[n])*SingleCoil_Wings_CenterPositionInR);
	 Translation_SingleCoil_LeftWing[n].setZ(-1.0*HorizontalOffset_Wing -0.1*mm);
	 
	 Translation_SingleCoil_RightWing[n].setX(sin(Angle_SingleCoil[n])*SingleCoil_Wings_CenterPositionInR);
	 Translation_SingleCoil_RightWing[n].setY(cos(Angle_SingleCoil[n])*SingleCoil_Wings_CenterPositionInR);
	 Translation_SingleCoil_RightWing[n].setZ(+1.0*HorizontalOffset_Wing + 0.1*mm);

	 SingleCoil_LeftWing_Physical[n] = new G4PVPlacement(Rotation_SingleCoil_LeftWing[n],
							     Translation_SingleCoil_LeftWing[n],
							     "SingleCoil_LeftWing_Physical",
							     SingleCoil_Wing_Logical,
							     MotherVolume,
							     false,
							     n,
							     pSurfChk);

        SingleCoil_RightWing_Physical[n] = new G4PVPlacement(Rotation_SingleCoil_RightWing[n],
							     Translation_SingleCoil_RightWing[n],
							     "SingleCoil_RightWing_Physical",
							     SingleCoil_Wing_Logical,
							     MotherVolume,
							     false,
							     n,
							     pSurfChk);
	 
	 //----------------------------------------

     } // end of  for (G4int n=0; n<8; n++)


    // Lintel geometry
    // Lintels are 16 cm high x 70 cm wide x 10 cm deep and are pitched
    // forward toward the beamline at an angle ~20 degrees.
    G4cout << G4endl << "###### QweakSimMainMagnet: Define Lintels." << G4endl << G4endl;

    G4Box* Lintel_Solid    = new G4Box("Lintel_Solid",
					0.5 * Lintel_FullLength_X,    // horizontal 70 cm
					0.5 * Lintel_FullLength_Y,    // vertical   16 cm
					0.5 * Lintel_FullLength_Z );  // length     10 cm
    
     
    Lintel_Logical  = new G4LogicalVolume( Lintel_Solid,
					Lintel_Material,
                                        "Lintel_Logical",
					0,
					0,0);

     // place 8 lintels into the MotherVolume
     for (G4int n=0; n<8; n++) {

	 Angle_Lintel[n] = n*45.0*degree;

	 Rotation_Lintel[n] = new G4RotationMatrix();
	 Rotation_Lintel[n]->rotateZ(Angle_Lintel[n]);
	 Rotation_Lintel[n]->rotateX(Lintel_Tilt_Angle);
	 Rotation_Lintel[n]->rotateY(0.0*degree);
	 
	 Translation_Lintel[n].setX(sin(Angle_Lintel[n])*Lintel_CenterPositionInR);
	 Translation_Lintel[n].setY(cos(Angle_Lintel[n])*Lintel_CenterPositionInR);
	 Translation_Lintel[n].setZ(-66.8*cm);

	 Lintel_Physical[n] =  new G4PVPlacement( Rotation_Lintel[n],
						Translation_Lintel[n],
						"Lintel_Physical",
						Lintel_Logical,
						MotherVolume,
						false,
						n,
						pSurfChk);

     } // end of place lintels
     
     G4Colour copper ( 184/255., 115/255., 51/255.);	
     G4Colour  mangenta  (237/255.,173/255.,255/255.);
     
     SingleCoil_VisAtt -> SetColor(copper); 
     SingleCoil_VisAtt -> SetVisibility(true);
     SingleCoil_Plate_Logical -> SetVisAttributes(SingleCoil_VisAtt); 
     SingleCoil_Wing_Logical  -> SetVisAttributes(SingleCoil_VisAtt); 

     Lintel_VisAtt -> SetColor(mangenta); 
     Lintel_VisAtt -> SetVisibility(true);
     Lintel_Logical -> SetVisAttributes(Lintel_VisAtt); 

 G4cout << G4endl << "###### Leaving QweakSimMainMagnet::ConstructComponent() " << G4endl << G4endl;
 
}    // end 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMainMagnet::DestroyComponent()
{
G4cout << G4endl << "###### Calling QweakSimMainMagnet::DestroyComponent() " << G4endl << G4endl;

G4cout << G4endl << "###### Leaving QweakSimMainMagnet::DestroyComponent() " << G4endl << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........

void QweakSimMainMagnet::SetCenterPositionInZ(G4double /*myCenterPositionInZ*/)
{
  G4cout << G4endl << "###### Calling QweakSimMainMagnet::SetCenterPositionInZ() " << G4endl << G4endl;

  //MainMagnet_MasterContainer_Physical->SetTranslation(G4ThreeVector(0.,0., myCenterPositionInZ));

  G4cout << G4endl << "###### Leaving QweakSimMainMagnet::SetCenterPositionInZ() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMainMagnet::Construct_UpstreamSpider(G4VPhysicalVolume* MotherVolume)
{

    G4Tubs*  UpstreamSpider_Solid   =  new G4Tubs("UpstreamSpider_Solid",
						  0.5*UpstreamSpider_DiameterMin,
						  0.5*UpstreamSpider_DiameterMax,
						  0.5*UpstreamSpider_FullThickness,
						  UpstreamSpider_PhiAngleStart,
						  UpstreamSpider_PhiDeltaAngle
						  );
    
    
    G4double UpstreamSpider_SubtractionTube_MinDiameter = 0.0*cm;
    G4double UpstreamSpider_SubtractionTube_MaxDiameter = 4.0*2.56*cm;
    G4double UpstreamSpider_SubtractionTubeLeft_Thickness    = 2.01*2.56*cm;
    G4double UpstreamSpider_SubtractionTubeRight_Thickness   = 2.02*2.56*cm;
    
    G4Tubs*  UpstreamSpider_SubtractionTubeLeft_Solid   =  new G4Tubs("UpstreamSpider_SubtractionTubeLeft_Solid",
								  0.5*UpstreamSpider_SubtractionTube_MinDiameter,
								  0.5*UpstreamSpider_SubtractionTube_MaxDiameter,
								  0.5*UpstreamSpider_SubtractionTubeLeft_Thickness,
								  0.0*degree,
								  360.0*degree
								  ); 

    G4Tubs*  UpstreamSpider_SubtractionTubeRight_Solid   =  new G4Tubs("UpstreamSpider_SubtractionTubeRight_Solid",
								  0.5*UpstreamSpider_SubtractionTube_MinDiameter,
								  0.5*UpstreamSpider_SubtractionTube_MaxDiameter,
								  0.5*UpstreamSpider_SubtractionTubeRight_Thickness,
								  0.0*degree,
								  360.0*degree
								  ); 



    G4double UpstreamSpider_SubtractionBox_FullLengthInX = 4.76*2.56*cm; // width
    G4double UpstreamSpider_SubtractionBox_FullLengthInY = 4.00*2.56*cm; // height
    G4double UpstreamSpider_SubtractionBox_FullLengthInZ = 2.00*2.56*cm; // thickness


  G4Box*  UpstreamSpider_SubtractionBox_Solid   = new G4Box(" UpstreamSpider_SubtractionBox_Solid",
							    0.5*UpstreamSpider_SubtractionBox_FullLengthInX,   // half X length required by Geant4
							    0.5*UpstreamSpider_SubtractionBox_FullLengthInY,   // half Y length required by Geant4
							    0.5*UpstreamSpider_SubtractionBox_FullLengthInZ);  // half Z length required by Geant4






// define left/right tube position for scooping out left/right corners
//   
//    |          |
//     \________/
// 
  G4ThreeVector position_LeftBottomTube  = G4ThreeVector( -0.5*UpstreamSpider_SubtractionBox_FullLengthInX, 
							  -0.5*UpstreamSpider_SubtractionBox_FullLengthInY + 0.5*UpstreamSpider_SubtractionTube_MaxDiameter,
							  0.0);
  
  G4ThreeVector position_RightBottomTube  = G4ThreeVector( 0.5*UpstreamSpider_SubtractionBox_FullLengthInX, 
							  -0.5*UpstreamSpider_SubtractionBox_FullLengthInY + 0.5*UpstreamSpider_SubtractionTube_MaxDiameter,
							   0.0);

  G4ThreeVector position_CutoutUnion  = G4ThreeVector(0.0*cm , 0.0*cm, 0.0*cm);

  

  MyUpstreamSpider_LowThetaCutout_Solid[0] =  new G4UnionSolid ("PlateAndLeftBottomTube",
								UpstreamSpider_SubtractionBox_Solid,
								UpstreamSpider_SubtractionTubeLeft_Solid, 
								0,
								position_LeftBottomTube); 
  
  MyUpstreamSpider_LowThetaCutout_Solid[1] =  new G4UnionSolid ("PlateAndRightBottomTube",
								MyUpstreamSpider_LowThetaCutout_Solid[0],
								UpstreamSpider_SubtractionTubeRight_Solid, 
								0,
								position_RightBottomTube); 

  G4double  OctantCutOut_Box_RadialDistance = 15.50*2.56*cm + 0.5*UpstreamSpider_SubtractionBox_FullLengthInY; // radial+ 1/2*BoxDimY


 // octant #1 location
  G4double         Angle_Octant1;
  G4ThreeVector    Translation_Octant1;
  G4RotationMatrix Rotation_Octant1_Left;  
  G4RotationMatrix Rotation_Octant1_Right;  

  Angle_Octant1 = 90.0*degree;
  Translation_Octant1.setX(cos(Angle_Octant1)*OctantCutOut_Box_RadialDistance);
  Translation_Octant1.setY(sin(Angle_Octant1)*OctantCutOut_Box_RadialDistance);
  Translation_Octant1.setZ(0.0*cm);
    
  Rotation_Octant1_Left.rotateZ(Angle_Octant1  -90.0*degree);
  Rotation_Octant1_Right.rotateZ(Angle_Octant1 +90.0*degree);
  
  G4Transform3D Transform3D_Octant1_Left(Rotation_Octant1_Left,Translation_Octant1); 
  G4Transform3D Transform3D_Octant1_Right(Rotation_Octant1_Right,Translation_Octant1); 

  // octant #2 location
  G4double         Angle_Octant2;
  G4ThreeVector    Translation_Octant2;
  G4RotationMatrix Rotation_Octant2_Left;  
  G4RotationMatrix Rotation_Octant2_Right;  

  Angle_Octant2 = 45.0*degree;
  Translation_Octant2.setX(cos(Angle_Octant2)*OctantCutOut_Box_RadialDistance);
  Translation_Octant2.setY(sin(Angle_Octant2)*OctantCutOut_Box_RadialDistance);
  Translation_Octant2.setZ(0.0*cm);
    
  Rotation_Octant2_Left.rotateZ(Angle_Octant2  -90.0*degree);
  Rotation_Octant2_Right.rotateZ(Angle_Octant2 +90.0*degree);

  G4Transform3D Transform3D_Octant2_Left(Rotation_Octant2_Left,Translation_Octant2); 
  G4Transform3D Transform3D_Octant2_Right(Rotation_Octant2_Right,Translation_Octant2); 

  // octant #3 location
   G4double         Angle_Octant3;
   G4ThreeVector    Translation_Octant3;
   G4RotationMatrix Rotation_Octant3_Left;  
   G4RotationMatrix Rotation_Octant3_Right;  

   Angle_Octant3 = 0.0*degree;
   Translation_Octant3.setX(cos(Angle_Octant3)*OctantCutOut_Box_RadialDistance);
   Translation_Octant3.setY(sin(Angle_Octant3)*OctantCutOut_Box_RadialDistance);
   Translation_Octant3.setZ(0.0*cm);

   Rotation_Octant3_Left.rotateZ(Angle_Octant3  -90.0*degree);
   Rotation_Octant3_Right.rotateZ(Angle_Octant3 +90.0*degree);

   G4Transform3D Transform3D_Octant3_Left(Rotation_Octant3_Left,Translation_Octant3); 
   G4Transform3D Transform3D_Octant3_Right(Rotation_Octant3_Right,Translation_Octant3); 

   // octant #4 location
   G4double         Angle_Octant4;
   G4ThreeVector    Translation_Octant4;
   G4RotationMatrix Rotation_Octant4_Left;  
   G4RotationMatrix Rotation_Octant4_Right;  

   Angle_Octant4 = 315.0*degree;
   Translation_Octant4.setX(cos(Angle_Octant4)*OctantCutOut_Box_RadialDistance);
   Translation_Octant4.setY(sin(Angle_Octant4)*OctantCutOut_Box_RadialDistance);
   Translation_Octant4.setZ(0.0*cm);

   Rotation_Octant4_Left.rotateZ(Angle_Octant4  -90.0*degree);
   Rotation_Octant4_Right.rotateZ(Angle_Octant4 +90.0*degree);

   G4Transform3D Transform3D_Octant4_Left(Rotation_Octant4_Left,Translation_Octant4); 
   G4Transform3D Transform3D_Octant4_Right(Rotation_Octant4_Right,Translation_Octant4); 

   // octant #5 location
   G4double         Angle_Octant5;
   G4ThreeVector    Translation_Octant5;
   G4RotationMatrix Rotation_Octant5_Left;  
   G4RotationMatrix Rotation_Octant5_Right;  

   Angle_Octant5 = 270.0*degree;
   Translation_Octant5.setX(cos(Angle_Octant5)*OctantCutOut_Box_RadialDistance);
   Translation_Octant5.setY(sin(Angle_Octant5)*OctantCutOut_Box_RadialDistance);
   Translation_Octant5.setZ(0.0*cm);

   Rotation_Octant5_Left.rotateZ(Angle_Octant5  -90.0*degree);
   Rotation_Octant5_Right.rotateZ(Angle_Octant5 +90.0*degree);

   G4Transform3D Transform3D_Octant5_Left(Rotation_Octant5_Left,Translation_Octant5); 
   G4Transform3D Transform3D_Octant5_Right(Rotation_Octant5_Right,Translation_Octant5); 

   // octant #6 location
   G4double         Angle_Octant6;
   G4ThreeVector    Translation_Octant6;
   G4RotationMatrix Rotation_Octant6_Left;  
   G4RotationMatrix Rotation_Octant6_Right;  

   Angle_Octant6 = 225.0*degree;
   Translation_Octant6.setX(cos(Angle_Octant6)*OctantCutOut_Box_RadialDistance);
   Translation_Octant6.setY(sin(Angle_Octant6)*OctantCutOut_Box_RadialDistance);
   Translation_Octant6.setZ(0.0*cm);

   Rotation_Octant6_Left.rotateZ(Angle_Octant6  -90.0*degree);
   Rotation_Octant6_Right.rotateZ(Angle_Octant6 +90.0*degree);

   G4Transform3D Transform3D_Octant6_Left(Rotation_Octant6_Left,Translation_Octant6); 
   G4Transform3D Transform3D_Octant6_Right(Rotation_Octant6_Right,Translation_Octant6); 

 // octant #7 location
   G4double         Angle_Octant7;
   G4ThreeVector    Translation_Octant7;
   G4RotationMatrix Rotation_Octant7_Left;  
   G4RotationMatrix Rotation_Octant7_Right;  

   Angle_Octant7 = 180.0*degree;
   Translation_Octant7.setX(cos(Angle_Octant7)*OctantCutOut_Box_RadialDistance);
   Translation_Octant7.setY(sin(Angle_Octant7)*OctantCutOut_Box_RadialDistance);
   Translation_Octant7.setZ(0.0*cm);

   Rotation_Octant7_Left.rotateZ(Angle_Octant7  -90.0*degree);
   Rotation_Octant7_Right.rotateZ(Angle_Octant7 +90.0*degree);

   G4Transform3D Transform3D_Octant7_Left(Rotation_Octant7_Left,Translation_Octant7); 
   G4Transform3D Transform3D_Octant7_Right(Rotation_Octant7_Right,Translation_Octant7); 

 // octant #8 location
   G4double         Angle_Octant8;
   G4ThreeVector    Translation_Octant8;
   G4RotationMatrix Rotation_Octant8_Left;  
   G4RotationMatrix Rotation_Octant8_Right;  

   Angle_Octant8 = 135.0*degree;
   Translation_Octant8.setX(cos(Angle_Octant8)*OctantCutOut_Box_RadialDistance);
   Translation_Octant8.setY(sin(Angle_Octant8)*OctantCutOut_Box_RadialDistance);
   Translation_Octant8.setZ(0.0*cm);

   Rotation_Octant8_Left.rotateZ(Angle_Octant8  -90.0*degree);
   Rotation_Octant8_Right.rotateZ(Angle_Octant8 +90.0*degree);

   
   G4Transform3D Transform3D_Octant8_Left(Rotation_Octant8_Left,Translation_Octant8); 
   G4Transform3D Transform3D_Octant8_Right(Rotation_Octant8_Right,Translation_Octant8); 



   // subtract octant hole from shielding wall
   MyUpstreamSpider_Solid[0] =  new G4SubtractionSolid ("Ring-Plate1",
							UpstreamSpider_Solid, 
							MyUpstreamSpider_LowThetaCutout_Solid[1],
							//UpstreamSpider_SubtractionBox_Solid,
							Transform3D_Octant1_Right ); 
   
   // subtract octant hole from previous G4StbtractionSolid
   MyUpstreamSpider_Solid[1] =  new G4SubtractionSolid ("Ring-Plate2",
							MyUpstreamSpider_Solid[0], 
							MyUpstreamSpider_LowThetaCutout_Solid[1],
							//UpstreamSpider_SubtractionBox_Solid,
							Transform3D_Octant2_Right ); 
   
   // subtract octant hole from previous G4StbtractionSolid
   MyUpstreamSpider_Solid[2] =  new G4SubtractionSolid ("Ring-Plate3",
							MyUpstreamSpider_Solid[1], 
							MyUpstreamSpider_LowThetaCutout_Solid[1],
							//UpstreamSpider_SubtractionBox_Solid,
							Transform3D_Octant3_Right ); 
   
   // subtract octant hole from previous G4StbtractionSolid
   MyUpstreamSpider_Solid[3] =  new G4SubtractionSolid ("Ring-Plate4",
							MyUpstreamSpider_Solid[2], 
							MyUpstreamSpider_LowThetaCutout_Solid[1], 
							//UpstreamSpider_SubtractionBox_Solid,
							Transform3D_Octant4_Right); 
   // subtract octant hole from previous G4StbtractionSolid
   MyUpstreamSpider_Solid[4] =  new G4SubtractionSolid ("Ring-Plate5",
							MyUpstreamSpider_Solid[3], 
							MyUpstreamSpider_LowThetaCutout_Solid[1],
							//UpstreamSpider_SubtractionBox_Solid,
							Transform3D_Octant5_Right ); 
   // subtract octant hole from previous G4StbtractionSolid
   MyUpstreamSpider_Solid[5] =  new G4SubtractionSolid ("Ring-Plate6",
							MyUpstreamSpider_Solid[4],
							MyUpstreamSpider_LowThetaCutout_Solid[1],
							//UpstreamSpider_SubtractionBox_Solid,
							Transform3D_Octant6_Right ); 
   // subtract octant hole from previous G4StbtractionSolid
   MyUpstreamSpider_Solid[6] =  new G4SubtractionSolid ("Ring-Plate7",
							MyUpstreamSpider_Solid[5], 
							MyUpstreamSpider_LowThetaCutout_Solid[1],
							//UpstreamSpider_SubtractionBox_Solid,
							Transform3D_Octant7_Right ); 
   // subtract octant hole from previous G4StbtractionSolid
   MyUpstreamSpider_Solid[7] =  new G4SubtractionSolid ("Ring-Plate8",
							MyUpstreamSpider_Solid[6], 
							MyUpstreamSpider_LowThetaCutout_Solid[1],
							//UpstreamSpider_SubtractionBox_Solid,
							Transform3D_Octant8_Right ); 

   /*
// define radial strut


   G4double UpstreamSpider_RadialStrut_FullLengthInX = 5.00*2.56*cm;
   G4double UpstreamSpider_RadialStrut_FullLengthInY = 20.0*2.56*cm;
   G4double UpstreamSpider_RadialStrut_FullLengthInZ = UpstreamSpider_FullThickness + 1*mm;

   G4Box*  UpstreamSpider_RadialStrut_Solid   = new G4Box(" UpstreamSpider_RadialStrut_Solid",
							  0.5*UpstreamSpider_RadialStrut_FullLengthInX,   // half X length required by Geant4
							  0.5*UpstreamSpider_RadialStrut_FullLengthInY,   // half Y length required by Geant4
							  0.5*UpstreamSpider_RadialStrut_FullLengthInZ);  // half Z length required by Geant4
   
  

   G4ThreeVector position_RadialStrut; 

//    position_RadialStrut.setX(0.0*cm);
//    position_RadialStrut.setY(33.25*2.56*cm - 0.5*UpstreamSpider_RadialStrut_FullLengthInY);
//    position_RadialStrut.setZ(0.0*cm);
//    position_RadialStrut.rotateZ(22.5*degree);
//
   position_RadialStrut.setX(0.0*cm);
   position_RadialStrut.setY(0.0*cm);
   position_RadialStrut.setZ(0.0*cm);
   position_RadialStrut.rotateZ(22.5*degree);

   
   G4RotationMatrix* Rotation_RadialStrut = new G4RotationMatrix();
   Rotation_RadialStrut->rotateZ(22.5*degree);


   MyUpstreamSpider_StrutsUnion_Solid[0] =  new G4UnionSolid ("SpiderAndRadialStrut1",
							      MyUpstreamSpider_Solid[22], 
							      UpstreamSpider_RadialStrut_Solid);

//                                                               Rotation_RadialStrut,
//                                                               position_RadialStrut);
*/

   // Solid of Spider is defined above. Now make a logical volume and place it in the 
   // MotherVolume of Qweak
   UpstreamSpider_Logical  = new G4LogicalVolume( //MyUpstreamSpider_Solid[7],
						  //MyUpstreamSpider_LowThetaCutout_Solid[1],
						   MyUpstreamSpider_Solid[7],
						   UpstreamSpider_Material,
						   "UpstreamSpider_Log",
						   0,
						   0,0);
    
    
    G4ThreeVector position_UpstreamSpider = G4ThreeVector(0.0,
							  0.0,
							  UpstreamSpider_CenterPositionInZ);
  
  
    UpstreamSpider_Physical = new G4PVPlacement( 0,
						 position_UpstreamSpider,
						  "UpstreamSpider_Physical",
						 UpstreamSpider_Logical,
						 MotherVolume,
						 false,
						 0,
						 pSurfChk);
        
    G4Colour aluminium ( 169/255., 172/255., 182/255.);
  
    UpstreamSpider_VisAtt -> SetColor(aluminium);
    UpstreamSpider_VisAtt -> SetVisibility(true);
    //UpstreamSpider_VisAtt->SetForceWireframe(true);
    UpstreamSpider_VisAtt -> SetForceSolid(true);

    UpstreamSpider_Logical                     -> SetVisAttributes(UpstreamSpider_VisAtt);
//     UpstreamSpider_LowThetaCutoutLeft_Logical  -> SetVisAttributes(UpstreamSpider_VisAtt);
//     UpstreamSpider_LowThetaCutoutRight_Logical -> SetVisAttributes(UpstreamSpider_VisAtt);
//     UpstreamSpider_LowThetaCutoutFinal_Logical -> SetVisAttributes(UpstreamSpider_VisAtt);
//

}	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimMainMagnet::Construct_ClampPlates(G4VPhysicalVolume* MotherVolume)
{
  // define center position of SingleCoil_ClampPlate inside the MotherVolume
    G4ThreeVector positionClampPlate = G4ThreeVector(0,0,0);

    // define MainMagnet SingleCoil Container solid volume
    G4cout << G4endl << "###### QweakSimMainMagnet: Define MainMagnet_ClampPlate_Solid " << G4endl << G4endl;


    G4Box* SingleCoil_ClampPlate_Solid    = new G4Box("MM_SingleCoil_ClampPlate_Solid",
						      0.5 * ClampPlate_FullLength_X ,  // half X length required by Geant4
						      0.5 * ClampPlate_FullLength_Y ,  // half Y length required by Geant4
						      0.5 * ClampPlate_FullLength_Z ); // half Z length required by Geant4


    // define SingleCoil_ClampPlate logical volume
    G4cout << G4endl << "###### QweakSimMainMagnet: Define SingleCoil_ClampPlate_Logical " << G4endl << G4endl;

    SingleCoil_ClampPlate_Logical  = new G4LogicalVolume(   SingleCoil_ClampPlate_Solid,
						   	    SingleCoil_ClampPlate_Material,
						  	    "MM_SingleCoil_ClampPlate_Logical",
							    0,
							    0,0);


    G4ThreeVector* leftcenter  = new G4ThreeVector();
    G4ThreeVector* rightcenter = new G4ThreeVector();

    // arbitrary gap distance: accounting for coil epoxy + wrapping etc
    //G4double GapBetweenClampPlateAndCoil = 1.0*mm; 

    // place 8 SingleCoil_ClampPlate_Logical plates into the MotherVolume (around the global Z axis)
    for (G4int n=0; n<8; n++) {

	 // set the vectors to the center of left and right clamp plate
	 // located at 12 o'clock. The rotate these vectors to the coil 
	 // positions and extract the new vector components
	 // This procedure is easier than the calculation by hand for individual
	 // clamp plate positions *before* Rotation_ClampPlate[n]
	 //
	 // the clamps are attachted to the CoilFramePlate which is thicker than the Coils
	 // Thickness CoilFramePlate: CoilFramePlate_FullLength_X
	 // Thickness Coil          : SingleCoil_FullThickness

	 leftcenter->setX( -0.5*(CoilFramePlate_FullLength_X + ClampPlate_FullLength_X));    
	 leftcenter->setY(ClampPlate_CenterPositionInR);    
	 leftcenter->setZ(0.0*cm);    

	 rightcenter->setX( 0.5*(CoilFramePlate_FullLength_X+ ClampPlate_FullLength_X));
	 rightcenter->setY(ClampPlate_CenterPositionInR);
	 rightcenter->setZ(0.0*cm);

	 // angles of the clamp plates
	 Angle_ClampPlate[n] = n*45.0*degree + 22.5*degree;

	 // rotate center vector to coils
         leftcenter  ->rotateZ(Angle_ClampPlate[n]);
	 rightcenter ->rotateZ(Angle_ClampPlate[n]);
	 
       
	 Translation_LeftClampPlate[n].setX( leftcenter->y() );
	 Translation_LeftClampPlate[n].setY( leftcenter->x() );
	 Translation_LeftClampPlate[n].setZ(0.0*cm);

	 Translation_RightClampPlate[n].setX( rightcenter->y() );
	 Translation_RightClampPlate[n].setY( rightcenter->x() );
	 Translation_RightClampPlate[n].setZ(0.0*cm);

	 // since the SingleCoil_ClampPlate_Logical is defined for a vertical orientation
	 // but the translation assumes a horizontal orinetation, we have to subtract 90*deg
	 Rotation_ClampPlate[n] = new G4RotationMatrix();
	 Rotation_ClampPlate[n]->rotateZ(Angle_ClampPlate[n] -90*degree);

   
	 SingleCoil_LeftClampPlate_Physical[n]   = new G4PVPlacement(Rotation_ClampPlate[n],
								     Translation_LeftClampPlate[n],
				        			     "MainMagnet_LeftClampPlate_Physical",
								     SingleCoil_ClampPlate_Logical,
								     MotherVolume,
								     false,
								     n,
								     pSurfChk);

	 SingleCoil_RightClampPlate_Physical[n]   = new G4PVPlacement(Rotation_ClampPlate[n],
								     Translation_RightClampPlate[n],
				        			     "MainMagnet_RightClampPlate_Physical",
								     SingleCoil_ClampPlate_Logical,
								     MotherVolume,
								     false,
								     n,
								     pSurfChk);


     } // end of  for (G4int n=0; n<8; n++)


     G4Colour blue      (0.,0.,1.);
     G4Colour aluminium ( 169/255., 172/255., 182/255.);
     G4Colour copper ( 184/255., 115/255., 51/255.);

     SingleCoil_ClampPlate_VisAtt -> SetColor(aluminium); 
     SingleCoil_ClampPlate_VisAtt -> SetVisibility(true);
     //SingleCoil_ClampPlate_VisAtt -> SetForceWireframe(true); 
     //SingleCoil_ClampPlate_VisAtt -> SetForceSolid(true); 
     SingleCoil_ClampPlate_Logical -> SetVisAttributes(SingleCoil_ClampPlate_VisAtt); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimMainMagnet::Construct_UpStreamMiniClampPlates(G4VPhysicalVolume* MotherVolume)
{

    // define MainMagnet SingleCoil Container solid volume
    G4cout << G4endl << "###### QweakSimMainMagnet: Define MainMagnet_MiniClampPlate_Solid " << G4endl << G4endl;


    G4Box* SingleCoil_MiniClampPlate_Solid = new G4Box("MM_SingleCoil_MiniClampPlate_Solid",
						       0.5 * MiniClampPlate_FullLength_X , 
						       0.5 * MiniClampPlate_FullLength_Y , 
						       0.5 * MiniClampPlate_FullLength_Z );

    
    G4Box* Chamfer_Solid                   = new G4Box("Chamfer_Solid",
						       0.5 * Chamfer_FullLength_X, 
						       0.5 * Chamfer_FullLength_Y ,  
						       0.5 * Chamfer_FullLength_Z );
    
    //------------------------------
    //Boolean Subtraction:
    //Right-Down-Edge chamfer
    //------------------------------
    Position_Chamfer1.setX( 0.5*MiniClampPlate_FullLength_X);  // left
    Position_Chamfer1.setY( 0.5*MiniClampPlate_FullLength_Y);  // down
    Position_Chamfer1.setZ(0.0*cm);
    Rotation_Chamfer1.rotateZ(45.0*degree);

    G4Transform3D Transform_Chamfer1(Rotation_Chamfer1,Position_Chamfer1);
    
    MiniClampPlateTemp_Solid[0] =  new G4SubtractionSolid ("MiniClamp-RightDownChamfer",
							   SingleCoil_MiniClampPlate_Solid,
							   Chamfer_Solid, 
							   Transform_Chamfer1); 



    Position_Chamfer2.setX( 0.5*MiniClampPlate_FullLength_X);  // left
    Position_Chamfer2.setY( -0.5*MiniClampPlate_FullLength_Y);  // down
    Position_Chamfer2.setZ(0.0*cm);
    Rotation_Chamfer2.rotateZ(-45.0*degree);


    G4Transform3D Transform_Chamfer2(Rotation_Chamfer2,Position_Chamfer2);

    MiniClampPlateTemp_Solid[1] =  new G4SubtractionSolid ("MiniClamp-RightUpChamfer",
							   MiniClampPlateTemp_Solid[0],
							   Chamfer_Solid,
							   Transform_Chamfer2);

    // define SingleCoil_RightMiniClampPlate logical volume
    G4cout << G4endl << "###### QweakSimMainMagnet: Define SingleCoil_RightMiniClampPlate_Logical " << G4endl << G4endl;
    
    SingleCoil_RightMiniClampPlate_Logical  = new G4LogicalVolume(  MiniClampPlateTemp_Solid[1],
								    SingleCoil_MiniClampPlate_Material,
								    "MM_SingleCoil_RightMiniClampPlate_Logical",
								    0,
								    0,0);

//     SingleCoil_RightMiniClampPlate_Logical  = new G4LogicalVolume(  SingleCoil_MiniClampPlate_Solid,
//                                                                     SingleCoil_MiniClampPlate_Material,
//                                                                     "MM_SingleCoil_RightMiniClampPlate_Logical",
//                                                                     0,
//                                                                     0,0);
    //------------------------------
    //Boolean Subtraction:
    //Left-Down-Edge chamfer
    //------------------------------
    Position_Chamfer3.setX( -0.5*MiniClampPlate_FullLength_X);  // left
    Position_Chamfer3.setY( 0.5*MiniClampPlate_FullLength_Y);  // down
    Position_Chamfer3.setZ(0.0*cm);
    Rotation_Chamfer3.rotateZ(-45.0*degree);
    
    G4Transform3D Transform_Chamfer3(Rotation_Chamfer3,Position_Chamfer3);
    

    MiniClampPlateTemp_Solid[2] =  new G4SubtractionSolid ("MiniClamp-LeftDownChamfer",
							   SingleCoil_MiniClampPlate_Solid,
							   Chamfer_Solid, 
							   Transform_Chamfer3); 

    Position_Chamfer4.setX( -0.5*MiniClampPlate_FullLength_X);  // left
    Position_Chamfer4.setY( -0.5*MiniClampPlate_FullLength_Y);  // down
    Position_Chamfer4.setZ(0.0*cm);
    Rotation_Chamfer4.rotateZ(45.0*degree);

    G4Transform3D Transform_Chamfer4(Rotation_Chamfer4,Position_Chamfer4);

    MiniClampPlateTemp_Solid[3] =  new G4SubtractionSolid ("MiniClamp-LeftUpChamfer",
							   MiniClampPlateTemp_Solid[2],
							   Chamfer_Solid,
							   Transform_Chamfer4);

    G4cout << G4endl << "###### QweakSimMainMagnet: Define SingleCoil_RightMiniClampPlate_Logical " << G4endl << G4endl;
    
    SingleCoil_LeftMiniClampPlate_Logical  = new G4LogicalVolume(  MiniClampPlateTemp_Solid[3],
								   SingleCoil_MiniClampPlate_Material,
								   "MM_SingleCoil_MiniClampPlate_Logical",
								   0,
								   0,0);

    //----------------------------------------------

    G4ThreeVector* leftcenter  = new G4ThreeVector();
    G4ThreeVector* rightcenter = new G4ThreeVector();

    // arbitrary gap distance: accounting for coil epoxy + wrapping etc
    //G4double GapBetweenClampPlateAndCoil = 1.0*mm; 

    // place 8 SingleCoil_ClampPlate_Logical plates into the MotherVolume (around the global Z axis)
    for (G4int n=0; n<8; n++) {

	 // set the vectors to the center of left and right clamp plate
	 // located at 12 o'clock. The rotate these vectors to the coil 
	 // positions and extract the new vector components
	 // This procedure is easier than the calculation by hand for individual
	 // clamp plate positions *before* Rotation_ClampPlate[n]

	 // the clamps are attachted to the CoilFramePlate which is thicker than the Coils
	 // Thickness CoilFramePlate: CoilFramePlate_FullLength_X
	 // Thickness Coil          : SingleCoil_FullThickness

	 leftcenter->setX( -0.5*( CoilFramePlate_FullLength_X + MiniClampPlate_FullLength_X) );    
	 leftcenter->setY(MiniClampPlate_CenterPositionInR);    
	 leftcenter->setZ(0.0*cm);    

	 rightcenter->setX( 0.5*(CoilFramePlate_FullLength_X + MiniClampPlate_FullLength_X));
	 rightcenter->setY(MiniClampPlate_CenterPositionInR);
	 rightcenter->setZ(0.0*cm);

	 // angles of the clamp plates
	 Angle_MiniClampPlate[n] = n*45.0*degree + 22.5*degree;

	 // rotate center vector to coils
         leftcenter  ->rotateZ(Angle_MiniClampPlate[n]);
	 rightcenter ->rotateZ(Angle_MiniClampPlate[n]);
	 
       
	 Translation_LeftMiniClampPlate[n].setX( leftcenter->y() );
	 Translation_LeftMiniClampPlate[n].setY( leftcenter->x() );
	 Translation_LeftMiniClampPlate[n].setZ(MiniClampPlate_CenterPositionInZ);

	 Translation_RightMiniClampPlate[n].setX( rightcenter->y() );
	 Translation_RightMiniClampPlate[n].setY( rightcenter->x() );
	 Translation_RightMiniClampPlate[n].setZ(MiniClampPlate_CenterPositionInZ);

	 // since the SingleCoil_ClampPlate_Logical is defined for a vertical orientation
	 // but the translation assumes a horizontal orinetation, we have to subtract 90*deg
	 Rotation_MiniClampPlate[n] = new G4RotationMatrix();
	 Rotation_MiniClampPlate[n]->rotateZ(Angle_MiniClampPlate[n] -90*degree);

   
	 SingleCoil_LeftMiniClampPlate_Physical[n]   = new G4PVPlacement(Rotation_MiniClampPlate[n],
									 Translation_LeftMiniClampPlate[n],
									 "MainMagnet_LeftMiniClampPlate_Physical",
									 SingleCoil_LeftMiniClampPlate_Logical,
									 MotherVolume,
									 false,
									 n,
									 pSurfChk);

	 SingleCoil_RightMiniClampPlate_Physical[n]  = new G4PVPlacement(Rotation_MiniClampPlate[n],
									 Translation_RightMiniClampPlate[n],
									 "MainMagnet_RightMiniClampPlate_Physical",
									 SingleCoil_RightMiniClampPlate_Logical,
									 MotherVolume,
									 false,
									 n,
									 pSurfChk);


     } // end of  for (G4int n=0; n<8; n++)


     G4Colour aluminium ( 169/255., 172/255., 182/255.);

     SingleCoil_MiniClampPlate_VisAtt -> SetColor(aluminium); 
     SingleCoil_MiniClampPlate_VisAtt -> SetVisibility(true);
     //SingleCoil_MiniClampPlate_VisAtt -> SetForceWireframe(true); 
     //SingleCoil_MiniClampPlate_VisAtt -> SetForceSolid(true); 
     SingleCoil_LeftMiniClampPlate_Logical  -> SetVisAttributes(SingleCoil_MiniClampPlate_VisAtt); 
     SingleCoil_RightMiniClampPlate_Logical -> SetVisAttributes(SingleCoil_MiniClampPlate_VisAtt); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimMainMagnet::Construct_CoilFrames(G4VPhysicalVolume* MotherVolume)
{

    // define MainMagnet SingleCoil Container solid volume
    G4cout << G4endl << "###### QweakSimMainMagnet: Define MainMagnet_MiniClampPlate_Solid " << G4endl << G4endl;


    G4Box* SingleCoil_FramePlate_Solid = new G4Box("MM_SingleCoil_FramePlate_Solid",
							0.5 * CoilFramePlate_FullLength_X, 
							0.5 * CoilFramePlate_FullLength_Y , 
							0.5 * CoilFramePlate_FullLength_Z );


   

    //-----------------------------------------------------------------------------------
        
    //------------------------------
    //Boolean Subtraction: CenterBox
    //------------------------------
    
    G4Box*   Subtraction_CenterBox_Solid  = new G4Box("Subtraction_CenterBox_Solid",
						      0.5 * Subtraction_CenterBox_FullLength_X, 
						      0.5 * CoilFramePlate_FullLength_Y,  
						      0.5 * Subtraction_CenterBox_FullLength_Z );
    
     Position_CenterBox.setX( 0.0*cm);  // left
     Position_CenterBox.setY( -18.0*2.54*cm);  // down
     Position_CenterBox.setZ(0.0*cm);

     //Rotation_Chamfer1.rotateZ(0.0*degree);

     G4Transform3D Transform_CenterBox(Rotation_SubtractionBox, Position_CenterBox);

     FramePlateTemp_Solid[0] =  new G4SubtractionSolid ("FramePlate-CenterBox",
							SingleCoil_FramePlate_Solid,
							Subtraction_CenterBox_Solid, 
							Transform_CenterBox); 



     //-----------------------------------------------------------------------------------

     //------------------------------
     //Boolean Subtraction: Upstream Cylinder
     //------------------------------
  
    G4Tubs*  Subtraction_UpstreamCylinder_Solid =  new G4Tubs("Subtraction_UpstreamCylinder_Solid",
							      0.0*cm,
							      29.75*2.54*cm,
							      6.0*2.54*cm,
							      0.0*degree,
							      360.0*degree );
    
    Rotation_SubtractionCylinder.rotateY(-90.0*degree);
    
    Position_UpstreamCylinder.setX( 0.0*cm);  // left
    Position_UpstreamCylinder.setY( (38.0-18.0-29.75)*2.54*cm);  // down
    //Position_UpstreamCylinder.setZ( -50.0*cm);  // down
    
    Position_UpstreamCylinder.setZ( -0.5*87.75*2.54*cm);
    
     
     
     G4Transform3D Transform_UpstreamCylinder(Rotation_SubtractionCylinder, Position_UpstreamCylinder);
     
     FramePlateTemp_Solid[1] =  new G4SubtractionSolid ("FramePlate-UpstreamCylinder",
							FramePlateTemp_Solid[0],
							Subtraction_UpstreamCylinder_Solid, 
							Transform_UpstreamCylinder); 


     //------------------------------
     //Boolean Subtraction: Upstream Cylinder
     //------------------------------
     
     G4Tubs*  Subtraction_DownstreamCylinder_Solid =  new G4Tubs("Subtraction_DownstreamCylinder_Solid",
								 0.0*cm,
								 29.75*2.54*cm,
								 6.0*2.54*cm,
								 0.0*degree,
								 360.0*degree );
    
     //Rotation_SubtractionCylinder.rotateY(-90.0*degree);
    
     Position_DownstreamCylinder.setX( 0.0*cm); 
     Position_DownstreamCylinder.setY( (38.0-18.0-29.75)*2.54*cm); 
     Position_DownstreamCylinder.setZ(  0.5*87.75*2.54*cm);
    
     G4Transform3D Transform_DownstreamCylinder(Rotation_SubtractionCylinder, Position_DownstreamCylinder);
     
     FramePlateTemp_Solid[2] =  new G4SubtractionSolid ("FramePlate-DownstreamCylinder",
							FramePlateTemp_Solid[1],
							Subtraction_DownstreamCylinder_Solid, 
							Transform_DownstreamCylinder); 



     //----------------------------------
     //Boolean Subtraction: DownstreamBox
     //-----------------------------------
     
     G4Box*   Subtraction_DownstreamBox_Solid  = new G4Box("Subtraction_DownstreamBox_Solid",
							   0.5 * Subtraction_DownstreamBox_FullLength_X, 
							   0.5 * CoilFramePlate_FullLength_Y,  
							   0.5 * Subtraction_DownstreamBox_FullLength_Z );
     
     Position_DownstreamBox.setX( 0.0*cm);                          // horizontal
     Position_DownstreamBox.setY( -59.0*2.54*cm);                   // vertical
     Position_DownstreamBox.setZ( 0.5*CoilFramePlate_FullLength_Z); // along beam line towards dump
     
     G4Transform3D Transform_DownstreamBox(Rotation_SubtractionBox, Position_DownstreamBox);
     
     FramePlateTemp_Solid[3] =  new G4SubtractionSolid ("FramePlate-DownstreamBox",
							FramePlateTemp_Solid[2],
							Subtraction_DownstreamBox_Solid, 
							Transform_DownstreamBox); 





     //-----------------------------------------------------------------------------------

     //--------------------------------
     // The final version of FramePlate
     //--------------------------------

     SingleCoil_FramePlate_Logical  = new G4LogicalVolume(  FramePlateTemp_Solid[3],
							    SingleCoil_FramePlate_Material,
							    "MM_SingleCoil_FramePlate_Logical",
							    0,
							    0,0);
    

  //-----------------------------------------------------------------------------------------------
  // place 8 SingleCoil_FramePlates_Logical plates into the MotherVolume (around the global Z axis)
  //-----------------------------------------------------------------------------------------------
  //
  for (G4int n=0; n<8; n++) {
      
	 Angle_FramePlate[n] = n*45.0*degree + 22.5*degree;
	 
	 Translation_FramePlate[n].setX(sin(Angle_FramePlate[n])*CoilFramePlate_CenterPositionInR);
	 Translation_FramePlate[n].setY(cos(Angle_FramePlate[n])*CoilFramePlate_CenterPositionInR);
	 Translation_FramePlate[n].setZ(0.0*cm);

	 // since the SingleCoil_MasterContainer_Logical is defined for a vertical orientation
	 // but the translation assumes a horizontal orinetation, we have to subtract 90*deg
	 Rotation_FramePlate[n] = new G4RotationMatrix();
	 Rotation_FramePlate[n]->rotateZ(Angle_FramePlate[n]);
   
	 SingleCoil_FramePlate_Physical[n]   = new G4PVPlacement(Rotation_FramePlate[n],
								 Translation_FramePlate[n],
								 "MainMagnet_FramePlate_Physical",
								 SingleCoil_FramePlate_Logical,
								 MotherVolume,
								 false,
								 n,
								 pSurfChk);

     } // end of  for (G4int n=0; n<8; n++)

     G4Colour aluminium     ( 169/255., 172/255., 182/255.);
     G4Colour copper        ( 184/255., 115/255.,  51/255.);	
     G4Color  green_yellow  ( 173/255., 255/255.,  47/255.);

     SingleCoil_FramePlate_VisAtt -> SetColor(green_yellow); 
     SingleCoil_FramePlate_VisAtt->SetVisibility(true);
     //SingleCoil_FramePlate_VisAtt->SetVisibility(false);
     //SingleCoil_FramePlate_VisAtt->SetForceWireframe(true); 
     //SingleCoil_FramePlate_VisAtt->SetForceSolid(true); 
     SingleCoil_FramePlate_Logical->SetVisAttributes(SingleCoil_FramePlate_VisAtt);

}	
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimMainMagnet::Construct_RadialMountingBlocks(G4VPhysicalVolume* MotherVolume)
{

    // define MainMagnet SingleCoil Container solid volume
    G4cout << G4endl << "###### QweakSimMainMagnet: Define MainMagnet_MountingBlock_Solid " << G4endl << G4endl;


    G4Box* SingleCoil_RadialMountingBlock_Solid = new G4Box("MM_SingleCoil_RadialMountingBlock_Solid",
							    0.5 * RadialMountingBlock_FullLength_X , 
							    0.5 * RadialMountingBlock_FullLength_Y , 
							    0.5 * RadialMountingBlock_FullLength_Z );

    // define SingleCoil_RadialMountingBlock logical volume
    G4cout << G4endl << "###### QweakSimMainMagnet: Define SingleCoil_RadialMountingBlock_Logical " << G4endl << G4endl;
    
    SingleCoil_RadialMountingBlock_Logical  = new G4LogicalVolume(  SingleCoil_RadialMountingBlock_Solid,
								    SingleCoil_RadialMountingBlock_Material,
								    "MM_SingleCoil_RadialMountingBlock_Logical",
								    0,
								    0,0);


    //----------------------------------------------

	 G4ThreeVector* leftcenter  = new G4ThreeVector();
	 G4ThreeVector* rightcenter = new G4ThreeVector();

     // place 8 SingleCoil_ClampPlate_Logical plates into the MotherVolume (around the global Z axis)
     for (G4int n=0; n<8; n++) {

	 // set the vectors to the center of left and right mounting block
	 // located at 12 o'clock. The rotate these vectors to the coil 
	 // positions and extract the new vector components
	 // This procedure is easier than the calculation by hand for individual
	 // clamp plate positions *before* Rotation_ClampPlate[n]

	 // the mounting blocks are attachted to the CoilFramePlate which is thicker than the Coils
	 // Thickness CoilFramePlate: CoilFramePlate_FullLength_X
	 // Thickness Coil          : SingleCoil_FullThickness

	 leftcenter->setX( -0.5*( CoilFramePlate_FullLength_X + RadialMountingBlock_FullLength_X) );    
	 leftcenter->setY(RadialMountingBlock_CenterPositionInR);    
	 leftcenter->setZ(0.0*cm);    

	 rightcenter->setX( 0.5*(CoilFramePlate_FullLength_X + RadialMountingBlock_FullLength_X));
	 rightcenter->setY(RadialMountingBlock_CenterPositionInR);
	 rightcenter->setZ(0.0*cm);

	 // angles of the clamp plates
	 Angle_RadialMountingBlock[n] = n*45.0*degree + 22.5*degree;

	 // rotate center vector to coils
         leftcenter  ->rotateZ(Angle_RadialMountingBlock[n]);
	 rightcenter ->rotateZ(Angle_RadialMountingBlock[n]);
	 
       
	 Translation_LeftRadialMountingBlock_Upstream[n].setX( leftcenter->y() );
	 Translation_LeftRadialMountingBlock_Upstream[n].setY( leftcenter->x() );
	 Translation_LeftRadialMountingBlock_Upstream[n].setZ(RadialMountingBlock_UpstreamPositionInZ); 

	 Translation_RightRadialMountingBlock_Upstream[n].setX( rightcenter->y() );
	 Translation_RightRadialMountingBlock_Upstream[n].setY( rightcenter->x() );
	 Translation_RightRadialMountingBlock_Upstream[n].setZ(RadialMountingBlock_UpstreamPositionInZ);

	 Translation_LeftRadialMountingBlock_Downstream[n].setX( leftcenter->y() );
	 Translation_LeftRadialMountingBlock_Downstream[n].setY( leftcenter->x() );
	 Translation_LeftRadialMountingBlock_Downstream[n].setZ(RadialMountingBlock_DownstreamPositionInZ); 

	 Translation_RightRadialMountingBlock_Downstream[n].setX( rightcenter->y() );
	 Translation_RightRadialMountingBlock_Downstream[n].setY( rightcenter->x() );
	 Translation_RightRadialMountingBlock_Downstream[n].setZ(RadialMountingBlock_DownstreamPositionInZ);



	 // since the SingleCoil_ClampPlate_Logical is defined for a vertical orientation
	 // but the translation assumes a horizontal orinetation, we have to subtract 90*deg
	 Rotation_RadialMountingBlock[n] = new G4RotationMatrix();
	 Rotation_RadialMountingBlock[n]->rotateZ(Angle_RadialMountingBlock[n] -90*degree);

   
	 SingleCoil_LeftRadialMountingBlock_Upstream_Physical[n]   = new G4PVPlacement(Rotation_RadialMountingBlock[n],
										       Translation_LeftRadialMountingBlock_Upstream[n],
										       "MainMagnet_LeftRadialMountingBlock_Upstream_Physical",
										       SingleCoil_RadialMountingBlock_Logical,
										       MotherVolume,
										       false,
										       n,
										       pSurfChk);

	 SingleCoil_RightRadialMountingBlock_Upstream_Physical[n]  = new G4PVPlacement(Rotation_RadialMountingBlock[n],
										       Translation_RightRadialMountingBlock_Upstream[n],
										       "MainMagnet_RightRadialMountingBlock_Upstream_Physical",
										       SingleCoil_RadialMountingBlock_Logical,
										       MotherVolume,
										       false,
										       n,
										       pSurfChk);
   
	 SingleCoil_LeftRadialMountingBlock_Downstream_Physical[n]   = new G4PVPlacement(Rotation_RadialMountingBlock[n],
											 Translation_LeftRadialMountingBlock_Downstream[n],
											 "MainMagnet_LeftRadialMountingBlock_Downstream_Physical",
											 SingleCoil_RadialMountingBlock_Logical,
											 MotherVolume,
											 false,
											 n,
											 pSurfChk);

	 SingleCoil_RightRadialMountingBlock_Downstream_Physical[n]  = new G4PVPlacement(Rotation_RadialMountingBlock[n],
											 Translation_RightRadialMountingBlock_Downstream[n],
											 "MainMagnet_RightRadialMountingBlock_Downstream_Physical",
											 SingleCoil_RadialMountingBlock_Logical,
											 MotherVolume,
											 false,
											 n,
											 pSurfChk);

     } // end of  for (G4int n=0; n<8; n++)


     G4Colour aluminium ( 169/255., 172/255., 182/255.);

     SingleCoil_RadialMountingBlock_VisAtt   -> SetColor(aluminium); 
     SingleCoil_RadialMountingBlock_VisAtt   -> SetVisibility(true);
     SingleCoil_RadialMountingBlock_Logical  -> SetVisAttributes(SingleCoil_RadialMountingBlock_VisAtt);
     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMainMagnet::Construct_SupportFrame(G4VPhysicalVolume* MotherVolume)
{

    // define MainMagnet SingleCoil Container solid volume
    G4cout << G4endl << "###### QweakSimMainMagnet: Define MainMagnet_DownstreamSupportBox_Solid " << G4endl << G4endl;



    //----------------------------------------------------------------------
    // Vertical cut of the *downstream* double-t frame support
    // 
    //   ------------->  electrom beam axis  
    //
    //        |   |     downstream frame plates:   z=88.498" and z=99.878"
    //        |---|
    //        |   |
    //        |---|
    //        /   |
    // 
    //     slab-rip-slab == a single "Double-T-Bean"
    //----------------------------------------------------------------------



    // First build a single vertical double-t-bean
    // cross scetion in global X-Z plane:
    //
    //      |  |          
    //      |--|         
    //      |  |                 -------> z-axis = beam          
    //

    //==================================================================================

    G4Box* DownstreamHorizontalDoubleTBeam_Solid = new G4Box("DownstreamHorizontalDoubleTBeam_Solid",
							     0.5 * SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_X,
							     0.5 * SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Y, 
							     0.5 * SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Z );
    
    G4Box* Subtract_DownstreamHorizontalDoubleTBeam_Solid = new G4Box("SubtractDownstreamHorizontalDoubleTBeam_Solid",
								      0.5 *  SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_X +1.0*cm, 
								      0.5 *  SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Y, 
								      0.5 * (SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Z - 
									      2.0*SupportFrame_DownstreamDoubleTBeamSlab_Thickness) );

    std::vector< G4ThreeVector >  LocalTranslation_HorizontalDoubleTBeam_Subtract;
    LocalTranslation_HorizontalDoubleTBeam_Subtract.clear();
    LocalTranslation_HorizontalDoubleTBeam_Subtract.resize(2);

    // Upstream Slab
    LocalTranslation_HorizontalDoubleTBeam_Subtract[0].setX(0.0*cm);
    LocalTranslation_HorizontalDoubleTBeam_Subtract[0].setY(0.5 * SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Y + 0.5*SupportFrame_DownstreamDoubleTBeamRib_Thickness);
    LocalTranslation_HorizontalDoubleTBeam_Subtract[0].setZ(0.0*cm);

    // Downstream Slab
    LocalTranslation_HorizontalDoubleTBeam_Subtract[1].setX(0.0*cm);
    LocalTranslation_HorizontalDoubleTBeam_Subtract[1].setY(-0.5 * SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Y - 0.5*SupportFrame_DownstreamDoubleTBeamRib_Thickness);
    LocalTranslation_HorizontalDoubleTBeam_Subtract[1].setZ(0.0*cm);

    // dummy rotation matrix
    G4RotationMatrix LocalRotation_Subtraction;

    G4Transform3D    Transform3D_TopSubtraction    (LocalRotation_Subtraction, LocalTranslation_HorizontalDoubleTBeam_Subtract[0] );
    G4Transform3D    Transform3D_BottomSubtraction (LocalRotation_Subtraction, LocalTranslation_HorizontalDoubleTBeam_Subtract[1] );


    SupportFrameSubtraction_TempSolid[0] =  new G4SubtractionSolid ("HorizontalBean-TopCutout",
								    DownstreamHorizontalDoubleTBeam_Solid,
								    Subtract_DownstreamHorizontalDoubleTBeam_Solid,
								    Transform3D_TopSubtraction); 
    
 
    SupportFrameSubtraction_TempSolid[1] =  new G4SubtractionSolid ("HorizontalBean-BottomCutout",
								    SupportFrameSubtraction_TempSolid[0],
								    Subtract_DownstreamHorizontalDoubleTBeam_Solid,
								    Transform3D_BottomSubtraction);

    //==================================================================================

    SupportFrame_DownstreamHorizontalDoubleTBeam_Logical = new G4LogicalVolume( SupportFrameSubtraction_TempSolid[1],
										SupportFrame_Material,
										"SupportFrame_DownstreamHorizontalDoubleTBeam_Logical",
										0,
										0,0);

   //==================================================================================

    // +Y : outer horizontal beam
    Translation_DownstreamHorizontalDoubleTBeam[0].setX(0.0*cm);                                                            // horizontal
    Translation_DownstreamHorizontalDoubleTBeam[0].setY(  0.5*SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Y       // vertical
							- 0.5*SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Y);
    Translation_DownstreamHorizontalDoubleTBeam[0].setZ(positionInZ_DownstreamDoubleTBeam);                                 // beam line

    // +Y : inner horizontal beam
    Translation_DownstreamHorizontalDoubleTBeam[1].setX(0.0*cm);                                                            // horizontal
    Translation_DownstreamHorizontalDoubleTBeam[1].setY(  0.5*SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Y       // vertical
							  - 1.5*SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Y);
    Translation_DownstreamHorizontalDoubleTBeam[1].setZ(positionInZ_DownstreamDoubleTBeam);                                 // beam line

   // -Y : inner horizontal beam
    Translation_DownstreamHorizontalDoubleTBeam[2].setX(0.0*cm);                                                            // horizontal
    Translation_DownstreamHorizontalDoubleTBeam[2].setY(  -0.5*SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Y       // vertical
							+ 0.5*SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Y);
    Translation_DownstreamHorizontalDoubleTBeam[2].setZ(positionInZ_DownstreamDoubleTBeam);                                 // beam line

    // -Y : outer horizontal beam
    Translation_DownstreamHorizontalDoubleTBeam[3].setX(0.0*cm);                                                            // horizontal
    Translation_DownstreamHorizontalDoubleTBeam[3].setY(   -0.5*SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Y       // vertical
							  + 1.5*SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_Y);
    Translation_DownstreamHorizontalDoubleTBeam[3].setZ(positionInZ_DownstreamDoubleTBeam);                                 // beam line

    // define physical volume
    G4cout << G4endl << "###### QweakSimMainManet: Define SupportFrame_DownstreamHorizontalDoubleTBeam_Physical" << G4endl << G4endl;

    SupportFrame_DownstreamHorizontalDoubleTBeam_Physical[0] = new G4PVPlacement(0,
										 Translation_DownstreamHorizontalDoubleTBeam[0],
										 "SupportFrame_DownstreamHorizontalDoubleTBeam_TopOuter_Physical",
										 SupportFrame_DownstreamHorizontalDoubleTBeam_Logical,
										 MotherVolume,
										 false,
										 0,
										 pSurfChk); // copy number


    SupportFrame_DownstreamHorizontalDoubleTBeam_Physical[1] = new G4PVPlacement(0,
										 Translation_DownstreamHorizontalDoubleTBeam[1],
										 "SupportFrame_DownstreamHorizontalDoubleTBeam_TopInner_Physical",
										 SupportFrame_DownstreamHorizontalDoubleTBeam_Logical,
										 MotherVolume,
										 false,
										 1,
										 pSurfChk); // copy number

    SupportFrame_DownstreamHorizontalDoubleTBeam_Physical[2] = new G4PVPlacement(0,
										 Translation_DownstreamHorizontalDoubleTBeam[2],
										 "SupportFrame_DownstreamHorizontalDoubleTBeam_BottomInner_Physical",
										 SupportFrame_DownstreamHorizontalDoubleTBeam_Logical,
										 MotherVolume,
										 false,
										 2,
										 pSurfChk); // copy number

    SupportFrame_DownstreamHorizontalDoubleTBeam_Physical[3] = new G4PVPlacement(0,
										 Translation_DownstreamHorizontalDoubleTBeam[3],
										 "SupportFrame_DownstreamHorizontalDoubleTBeam_BottomOuter_Physical",
										 SupportFrame_DownstreamHorizontalDoubleTBeam_Logical,
										 MotherVolume,
										 false,
										 3,
										 pSurfChk); // copy number


    //============================================================================================================================================================
    //============================================================================================================================================================


    // First build a single vertical double-t-bean
    // cross scetion in global X-Z plane:
    //
    //      |  |          
    //      |--|         
    //      |  |                 -------> z-axis = beam          
    //

    //==================================================================================

     G4Box* DownstreamVerticalDoubleTBeam_Solid = new G4Box("DownstreamVerticalDoubleTBeam_Solid",
							      0.5 * SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_X,
							      0.5 * SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Y, 
							      0.5 * SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Z );

     G4Box* Subtract_DownstreamVerticalDoubleTBeam_Solid = new G4Box("SubtractDownstreamVerticalDoubleTBeam_Solid",
								       0.5 *  SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_X, 
								       0.5 *  SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Y +1.0*cm, 
								       0.5 * (SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_Z - 
									       2.0*SupportFrame_DownstreamDoubleTBeamSlab_Thickness) );

     std::vector< G4ThreeVector >  LocalTranslation_VerticalDoubleTBeam_Subtract;
     LocalTranslation_VerticalDoubleTBeam_Subtract.clear();
     LocalTranslation_VerticalDoubleTBeam_Subtract.resize(2);

     // Left Slab (looking along z)
     LocalTranslation_VerticalDoubleTBeam_Subtract[0].setX(0.5 * SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_X + 0.5*SupportFrame_DownstreamDoubleTBeamRib_Thickness);
     LocalTranslation_VerticalDoubleTBeam_Subtract[0].setY(0.0*cm);
     LocalTranslation_VerticalDoubleTBeam_Subtract[0].setZ(0.0*cm);

     // Right Slab (looking along z)
     LocalTranslation_VerticalDoubleTBeam_Subtract[1].setX(-0.5 * SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_X - 0.5*SupportFrame_DownstreamDoubleTBeamRib_Thickness);
     LocalTranslation_VerticalDoubleTBeam_Subtract[1].setY(0.0*cm);
     LocalTranslation_VerticalDoubleTBeam_Subtract[1].setZ(0.0*cm);

     // dummy rotation matrix
     G4RotationMatrix LocalRotation_VerticalSubtraction;

     G4Transform3D    Transform3D_LeftSubtraction  (LocalRotation_VerticalSubtraction, LocalTranslation_VerticalDoubleTBeam_Subtract[0] );
     G4Transform3D    Transform3D_RightSubtraction (LocalRotation_VerticalSubtraction, LocalTranslation_VerticalDoubleTBeam_Subtract[1] );


     SupportFrameSubtraction_TempSolid[2] =  new G4SubtractionSolid ("VerticalBean-LeftCutout",
								     DownstreamVerticalDoubleTBeam_Solid,
								     Subtract_DownstreamVerticalDoubleTBeam_Solid,
								     Transform3D_LeftSubtraction); 


     SupportFrameSubtraction_TempSolid[3] =  new G4SubtractionSolid ("VerticalBean-RightCutout",
								     SupportFrameSubtraction_TempSolid[2],
								     Subtract_DownstreamVerticalDoubleTBeam_Solid,
								     Transform3D_RightSubtraction);

     //==================================================================================

     SupportFrame_DownstreamVerticalDoubleTBeam_Logical = new G4LogicalVolume( SupportFrameSubtraction_TempSolid[3],
										 SupportFrame_Material,
										 "SupportFrame_DownstreamVerticalDoubleTBeam_Logical",
										 0,
										 0,0);

    //==================================================================================

     // +X : outer Vertical beam
     Translation_DownstreamVerticalDoubleTBeam[0].setX(  0.5*SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_X     // horizontal
						       + 1.5*SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_X);
     Translation_DownstreamVerticalDoubleTBeam[0].setY(0.0*cm);                                                            // Vertical
     Translation_DownstreamVerticalDoubleTBeam[0].setZ(positionInZ_DownstreamDoubleTBeam);                                 // beam line

     // +X : inner Vertical beam
     Translation_DownstreamVerticalDoubleTBeam[1].setX(  0.5*SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_X    // horizontal
						       + 0.5*SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_X);
     Translation_DownstreamVerticalDoubleTBeam[1].setY(0.0*cm);                                                            // Vertical
     Translation_DownstreamVerticalDoubleTBeam[1].setZ(positionInZ_DownstreamDoubleTBeam);                                 // beam line

    // -X : inner Vertical beam
     Translation_DownstreamVerticalDoubleTBeam[2].setX(  -0.5*SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_X    // horizontal
							- 0.5*SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_X);
     Translation_DownstreamVerticalDoubleTBeam[2].setY(0.0*cm);                                                            // Vertical
     Translation_DownstreamVerticalDoubleTBeam[2].setZ(positionInZ_DownstreamDoubleTBeam);                                 // beam line

     // -X : outer Vertical beam
     Translation_DownstreamVerticalDoubleTBeam[3].setX(    -0.5*SupportFrame_DownstreamHorizontalDoubleTBeam_FullLength_X  // horizontal
							  - 1.5*SupportFrame_DownstreamVerticalDoubleTBeam_FullLength_X);
     Translation_DownstreamVerticalDoubleTBeam[3].setY(0.0*cm);                                                            // Vertical
     Translation_DownstreamVerticalDoubleTBeam[3].setZ(positionInZ_DownstreamDoubleTBeam);                                 // beam line

     // define physical volume
     G4cout << G4endl << "###### QweakSimMainManet: Define SupportFrame_DownstreamVerticalDoubleTBeam_Physical" << G4endl << G4endl;

     SupportFrame_DownstreamVerticalDoubleTBeam_Physical[0] = new G4PVPlacement(0,
										  Translation_DownstreamVerticalDoubleTBeam[0],
										  "SupportFrame_DownstreamVerticalDoubleTBeam_TopOuter_Physical",
										  SupportFrame_DownstreamVerticalDoubleTBeam_Logical,
										  MotherVolume,
										  false,
										  0,
										  pSurfChk); // copy number


     SupportFrame_DownstreamVerticalDoubleTBeam_Physical[1] = new G4PVPlacement(0,
										  Translation_DownstreamVerticalDoubleTBeam[1],
										  "SupportFrame_DownstreamVerticalDoubleTBeam_TopInner_Physical",
										  SupportFrame_DownstreamVerticalDoubleTBeam_Logical,
										  MotherVolume,
										  false,
										  1,
										  pSurfChk); // copy number

     SupportFrame_DownstreamVerticalDoubleTBeam_Physical[2] = new G4PVPlacement(0,
										  Translation_DownstreamVerticalDoubleTBeam[2],
										  "SupportFrame_DownstreamVerticalDoubleTBeam_BottomInner_Physical",
										  SupportFrame_DownstreamVerticalDoubleTBeam_Logical,
										  MotherVolume,
										  false,
										  2,
										  pSurfChk); // copy number

     SupportFrame_DownstreamVerticalDoubleTBeam_Physical[3] = new G4PVPlacement(0,
										  Translation_DownstreamVerticalDoubleTBeam[3],
										  "SupportFrame_DownstreamVerticalDoubleTBeam_BottomOuter_Physical",
										  SupportFrame_DownstreamVerticalDoubleTBeam_Logical,
										  MotherVolume,
										  false,
										  3,
										  pSurfChk); // copy number

     //---------------------------------------------------------------------------------------------------------------------------
     
     // First build a single horizontal Double-T-Bean
     // cross scetion in global X-Z plane:
     //
     //      |  |          
     //      |--|         
     //      |  |                 -------> z-axis = beam          
     //

    //==================================================================================

     G4Box* Downstream45DegDoubleTBeam_Solid = new G4Box("Downstream45DegHorizontalDoubleTBeam_Solid",
							 0.5 * SupportFrame_Downstream45DegDoubleTBeam_FullLength_X,
							 0.5 * SupportFrame_Downstream45DegDoubleTBeam_FullLength_Y, 
							 0.5 * SupportFrame_Downstream45DegDoubleTBeam_FullLength_Z );

     G4Box* Subtract_Downstream45DegDoubleTBeam_Solid = new G4Box("SubtractDownstream45DegDoubleTBeam_Solid",
								       0.5 *  SupportFrame_Downstream45DegDoubleTBeam_FullLength_X +1.0*cm, 
								       0.5 *  SupportFrame_Downstream45DegDoubleTBeam_FullLength_Y, 
								       0.5 * (SupportFrame_Downstream45DegDoubleTBeam_FullLength_Z - 
									  2.0*SupportFrame_Downstream45DegDoubleTBeamSlab_Thickness) );

     std::vector< G4ThreeVector >  LocalTranslation_45DegDoubleTBeam_Subtract;
     LocalTranslation_45DegDoubleTBeam_Subtract.clear();
     LocalTranslation_45DegDoubleTBeam_Subtract.resize(2);

     // Top Slab (looking along z)
     LocalTranslation_45DegDoubleTBeam_Subtract[0].setX( 0.0*cm);
     LocalTranslation_45DegDoubleTBeam_Subtract[0].setY( 0.5*SupportFrame_Downstream45DegDoubleTBeam_FullLength_Y + 0.5*SupportFrame_Downstream45DegDoubleTBeamRib_Thickness);
     LocalTranslation_45DegDoubleTBeam_Subtract[0].setZ( 0.0*cm);

     // Bottom Slab (looking along z)
     LocalTranslation_45DegDoubleTBeam_Subtract[1].setX( 0.0*cm);
     LocalTranslation_45DegDoubleTBeam_Subtract[1].setY(-0.5*SupportFrame_Downstream45DegDoubleTBeam_FullLength_Y - 0.5*SupportFrame_Downstream45DegDoubleTBeamRib_Thickness);
     LocalTranslation_45DegDoubleTBeam_Subtract[1].setZ( 0.0*cm);

     // dummy rotation matrix
     G4RotationMatrix LocalRotation_45DegSubtraction;

     G4Transform3D    Transform3D_45DegTopSubtraction    (LocalRotation_45DegSubtraction, LocalTranslation_45DegDoubleTBeam_Subtract[0] );
     G4Transform3D    Transform3D_45DegBottomSubtraction (LocalRotation_45DegSubtraction, LocalTranslation_45DegDoubleTBeam_Subtract[1] );


     SupportFrameSubtraction_TempSolid[4] =  new G4SubtractionSolid ("DoubleTBeam45Deg-TopCutout",
								     Downstream45DegDoubleTBeam_Solid,
								     Subtract_Downstream45DegDoubleTBeam_Solid,
								     Transform3D_45DegTopSubtraction); 


     SupportFrameSubtraction_TempSolid[5] =  new G4SubtractionSolid ("DoubleTBeam45Deg-BottomCutout",
								     SupportFrameSubtraction_TempSolid[4],
								     Subtract_Downstream45DegDoubleTBeam_Solid,
								     Transform3D_45DegBottomSubtraction);


     //==================================================================================

     G4Box* Subtract_Downstream45DegDoubleTBeam_Chamfer_Solid  = new G4Box("Subtract_Downstream45DegDoubleTBeam_Chamfer_Solid",
									   0.5 * 40.0*2.54*cm, 
									   0.5 * SupportFrame_Downstream45DegDoubleTBeam_FullLength_Y + 0.1*mm,  
									   0.5 * SupportFrame_Downstream45DegDoubleTBeam_FullLength_Z + 1.0*cm);



     std::vector< G4ThreeVector >  LocalTranslation_45DegDoubleTBeam_SubtractChamfer;
     LocalTranslation_45DegDoubleTBeam_SubtractChamfer.clear();
     LocalTranslation_45DegDoubleTBeam_SubtractChamfer.resize(2);

    // BeamLeft Chamfer
     LocalTranslation_45DegDoubleTBeam_SubtractChamfer[0].setX(  0.5 * SupportFrame_Downstream45DegDoubleTBeam_FullLength_X);
     LocalTranslation_45DegDoubleTBeam_SubtractChamfer[0].setY(  0.0*cm);
     LocalTranslation_45DegDoubleTBeam_SubtractChamfer[0].setZ(  0.0*cm);

     // BeamRight Chamfer
     LocalTranslation_45DegDoubleTBeam_SubtractChamfer[1].setX( -0.5 * SupportFrame_Downstream45DegDoubleTBeam_FullLength_X);
     LocalTranslation_45DegDoubleTBeam_SubtractChamfer[1].setY(  0.0*cm);
     LocalTranslation_45DegDoubleTBeam_SubtractChamfer[1].setZ(  0.0*cm);

     // rotation matrices
     G4RotationMatrix LocalRotation_45DegSubtraction_LeftChamfer;
                      LocalRotation_45DegSubtraction_LeftChamfer.rotateZ(-45.0*degree);

     G4RotationMatrix LocalRotation_45DegSubtraction_RightChamfer;
                      LocalRotation_45DegSubtraction_RightChamfer.rotateZ(45*degree);


     G4Transform3D    Transform3D_45DegLeftSubtractionChamfer  (LocalRotation_45DegSubtraction_LeftChamfer  , LocalTranslation_45DegDoubleTBeam_SubtractChamfer[0] );
     G4Transform3D    Transform3D_45DegRightSubtractionChamfer (LocalRotation_45DegSubtraction_RightChamfer , LocalTranslation_45DegDoubleTBeam_SubtractChamfer[1] );


     SupportFrameSubtraction_TempSolid[6] =  new G4SubtractionSolid ("DoubleTBeam45Deg-LeftChamfer",
								     SupportFrameSubtraction_TempSolid[5],
								     Subtract_Downstream45DegDoubleTBeam_Chamfer_Solid,
								     Transform3D_45DegLeftSubtractionChamfer); 


     SupportFrameSubtraction_TempSolid[7] =  new G4SubtractionSolid ("DoubleTBeam45Deg-RightChamfer",
								     SupportFrameSubtraction_TempSolid[6],
								     Subtract_Downstream45DegDoubleTBeam_Chamfer_Solid,
								     Transform3D_45DegRightSubtractionChamfer);



     //==================================================================================

     SupportFrame_Downstream45DegDoubleTBeam_Logical = new G4LogicalVolume( SupportFrameSubtraction_TempSolid[7],
									    SupportFrame_Material,
									    "SupportFrame_Downstream45DegDoubleTBeam_Logical",
									    0,
									    0,0);

     //==================================================================================


     //---------------------------------------------------------------------------------------------------------
     // place 4 SupportFrame_Downstream45DegDoubleTBeam_Logical into the MotherVolume (around the global Z axis)
     //---------------------------------------------------------------------------------------------------------
     //
     for (G4int n=0; n<4; n++) {
	 
	 Angle_DoubleTBeam45Deg[n] = n*90.0*degree + 45.0*degree;
	 
	 Translation_Downstream45DegDoubleTBeam[n].setX(sin(Angle_DoubleTBeam45Deg[n])*DoubleTBeam45Deg_CenterPositionInR);
	 Translation_Downstream45DegDoubleTBeam[n].setY(cos(Angle_DoubleTBeam45Deg[n])*DoubleTBeam45Deg_CenterPositionInR);
	 Translation_Downstream45DegDoubleTBeam[n].setZ(positionInZ_DownstreamDoubleTBeam);
	 
	 // since the SingleCoil_MasterContainer_Logical is defined for a vertical orientation
	 // but the translation assumes a horizontal orinetation, we have to subtract 90*deg
	 Rotation_DoubleTBeam45Deg[n] = new G4RotationMatrix();
	 Rotation_DoubleTBeam45Deg[n]->rotateZ(Angle_DoubleTBeam45Deg[n]);
	 
	 SupportFrame_Downstream45DegDoubleTBeam_Physical[n]   = new G4PVPlacement(Rotation_DoubleTBeam45Deg[n],
										   Translation_Downstream45DegDoubleTBeam[n],
										   "SupportFrame_Downstream45DegDoubleTBeam",
										   SupportFrame_Downstream45DegDoubleTBeam_Logical,
										   MotherVolume,
										   false,
										   n,
										   pSurfChk); // copy number

     } // end of  for (G4int n=0; n<4; n++)

     //==================================================================================

     //---------------------------------------------------------------------------------------------------------------------------

     G4cout << G4endl << "###### QweakSimMainMagnet: Setting Attributes for downstream support frame" << G4endl << G4endl;
     
     G4Colour  blue      (0.,0.,1.);
     
     SupportFrame_DownstreamHorizontalDoubleTBeam_VisAtt  -> SetColor(blue);
     SupportFrame_DownstreamHorizontalDoubleTBeam_VisAtt  -> SetVisibility(true);
     SupportFrame_DownstreamHorizontalDoubleTBeam_Logical -> SetVisAttributes(SupportFrame_DownstreamHorizontalDoubleTBeam_VisAtt); 
     
     SupportFrame_DownstreamVerticalDoubleTBeam_VisAtt  -> SetColor(blue);
     SupportFrame_DownstreamVerticalDoubleTBeam_VisAtt  -> SetVisibility(true);
     SupportFrame_DownstreamVerticalDoubleTBeam_Logical -> SetVisAttributes(SupportFrame_DownstreamVerticalDoubleTBeam_VisAtt); 

     SupportFrame_Downstream45DegDoubleTBeam_VisAtt  -> SetColor(blue);
     SupportFrame_Downstream45DegDoubleTBeam_VisAtt  -> SetVisibility(true);
     SupportFrame_Downstream45DegDoubleTBeam_Logical -> SetVisAttributes(SupportFrame_Downstream45DegDoubleTBeam_VisAtt); 

     //---------------------------------------------------------------------------------------------------------------------------

     G4cout << G4endl << "###### Leaving QweakSimMainMagnet::Construct_SupportFrame() " << G4endl << G4endl;

     //-----------------------------------------------------------------------------------
}

void QweakSimMainMagnet::Construct_DownstreamSpider(G4VPhysicalVolume* MotherVolume)
{

    // define downstream spider radial slabs volume
    G4cout << G4endl << "###### QweakSimMainMagnet: Define MainMagnet_DownstreamSpider_RadialSlabs_Solids " << G4endl << G4endl;

    G4Tubs*  DownstreamSpider_Solid   =  new G4Tubs("DowmstreamSpider_Solid",
						    0.5*DownstreamSpider_DiameterMin,
						    0.5*DownstreamSpider_DiameterMax,
						    0.5*DownstreamSpider_FullThickness,
						    DownstreamSpider_PhiAngleStart,
						    DownstreamSpider_PhiDeltaAngle );


    // Solid of Spider is defined above. Now make a logical volume and place it in the 
    // MotherVolume of Qweak
    DownstreamSpider_Logical  = new G4LogicalVolume( DownstreamSpider_Solid,
						     UpstreamSpider_Material,
						     "DownstreamSpider_Log",
						     0,
						     0,0);
    
    
    G4ThreeVector position_DownstreamSpider = G4ThreeVector(0.0,
							    0.0,
							    DownstreamSpider_CenterPositionInZ);
  
  
    DownstreamSpider_Physical = new G4PVPlacement( 0,
						   position_DownstreamSpider,
						   "DownstreamSpider_Physical",
						   DownstreamSpider_Logical,
						   MotherVolume,
						   false,
						   0,
						   pSurfChk);


    //--------------



    G4Box* DownstreamSpider_RadialSlab_Solid    = new G4Box("DownstreamSpider_RadialSlab_Solid",
							    0.5 * DownstreamSpider_RadialSlab_FullLength_X,    // horizontal
							    0.5 * DownstreamSpider_RadialSlab_FullLength_Y,    // vertical
							    0.5 * DownstreamSpider_RadialSlab_FullLength_Z );  // along beam
    
    
    DownstreamSpider_RadialSlab_Logical  = new G4LogicalVolume( DownstreamSpider_RadialSlab_Solid,
								SupportFrame_Material,
								"DownstreamSpider_RadialSlab_Logical",
								0,
								0,0);


    // place 8 DownstreamSpider_RadialSlab_Logical into the MotherVolume (around the global Z axis)
    for (G4int n=0; n<8; n++) {
	
	Angle_DownstreamSpider_RadialSlab[n] = n*45.0*degree + 22.5*degree;
	
	Rotation_DownstreamSpider_RadialSlab[n] = new G4RotationMatrix();
	Rotation_DownstreamSpider_RadialSlab[n]->rotateZ(Angle_DownstreamSpider_RadialSlab[n]);
	
	Translation_DownstreamSpider_RadialSlab[n].setX(sin(Angle_DownstreamSpider_RadialSlab[n])*DownstreamSpider_RadialSlab_CenterPositionInR);
	Translation_DownstreamSpider_RadialSlab[n].setY(cos(Angle_DownstreamSpider_RadialSlab[n])*DownstreamSpider_RadialSlab_CenterPositionInR);
	Translation_DownstreamSpider_RadialSlab[n].setZ(DownstreamSpider_RadialSlab_CenterPositionInZ);
	
	DownstreamSpider_RadialSlab_Physical[n] = new G4PVPlacement( Rotation_DownstreamSpider_RadialSlab[n],
								     Translation_DownstreamSpider_RadialSlab[n],
								     "DownstreamSpider_RadialSlab_Physical",
								     DownstreamSpider_RadialSlab_Logical,
								     MotherVolume,
								     false,
								     n,
								     pSurfChk);
	
	 } // end of  for (G4int n=0; n<8; n++)


    //--------------

    G4Colour aluminium ( 169/255., 172/255., 182/255.);
    G4Color  khaki3    ( 205/255., 198/255., 115/255.);


    DownstreamSpider_VisAtt  -> SetColor(khaki3);
    DownstreamSpider_VisAtt  -> SetVisibility(true);
    DownstreamSpider_Logical -> SetVisAttributes(DownstreamSpider_VisAtt);

    DownstreamSpider_RadialSlab_VisAtt  -> SetColor(aluminium);
    DownstreamSpider_RadialSlab_VisAtt  -> SetVisibility(true);
    DownstreamSpider_RadialSlab_Logical -> SetVisAttributes(DownstreamSpider_RadialSlab_VisAtt);
}		

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMainMagnet.cc,v $
//      Revision 1.8  2006/01/20 21:14:33  grimm
//      .
//
//      Revision 1.7  2006/01/18 20:18:49  grimm
//      Added downstream support structure and downstream spider
//
//      Revision 1.6  2006/01/13 00:28:33  grimm
//      Added Construct_RadialMountingBlocks()
//
//      Revision 1.5  2006/01/12 20:24:25  grimm
//      Included the 5" thick frame holder in which the coil is embedded. The whole code of coil placements had to be rewritten.
//      The coils are now placed directly into the MotherVolume and not in SingleCoil_MasterContainer (obsolete now like the function ConstructCoils() ).
//      The position and dimensions of the UpstreamMiniClamps and the big ClampPlates have been updated according to SolidWorks.
//
//      Revision 1.4  2005/12/29 02:50:33  grimm
//      Added upstream Mini Clamps including a chamfer according to drawings.
//      Included only the chamfer which avoids an overlap of the mini clamps at the given radius.
//
//      Revision 1.3  2005/12/28 23:08:03  grimm
//      Added the large clamp plates attached to both sides of each coil.
//      Dimensions and location are chosen rather arbirary, must be updated with SolidWorks information.
//
//      Revision 1.2  2005/12/27 19:13:16  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
