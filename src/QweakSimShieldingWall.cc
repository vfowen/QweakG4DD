
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimShieldingWall.cc

   $Revision: 1.6 $	
   $Date: 2006/05/05 21:54:17 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//
// Updated to the geometry definition from geant3. This is the as-designed shielding wall.
// 
// The vertices for the window openings are (x, y, z)
// 
// front face: (197.85, +/- 67.95, 300)
// front face: (263.65, +/- 79.95, 300)
// 
// back face: (232.45, +/- 79.635, 380)
// back face: (291.75, +/- 90.45, 380) 
//
// -- Peiqing  2011 Nov 12
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimShieldingWall.hh"

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimShieldingWallMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimShieldingWall::QweakSimShieldingWall()
{
G4cout << G4endl << "###### Calling QweakSimShieldingWall::QweakSimShieldingWall() " << G4endl << G4endl;

static const G4double inch = 2.54*cm;

    pMaterial = new QweakSimMaterial();
    pMaterial->DefineMaterials();

//--------------------
// Front Shielding Wall related
//--------------------
// 
// initialize pointers
ShieldingWallHousing_Logical  = NULL;
ShieldingWallHousing_Physical = NULL;
ShieldingWallHousing_Material = NULL;

// clear vector containing temp solids for boolean soild subtractions
 MyShieldingWallHousing_Solid.clear();
 MyShieldingWallHousing_Solid.resize(9); // 8 octants + 1 beam hole

 // See report of Yongjuang : http://www.jlab.org/~yl0094a/Qweak_SCIN/status_report/status_09152005.html
 // values are for z=380cm (start wall) and z=430cm (end wall)

 // Update the z location.  - Peiqing 2011 Nov.
 // z= 300 - 380 cm, thickness = 80 cm
 
 OctantCutOut_Trap_RadialDistance   = 246.425*cm;
 OctantCutOut_Trap_PolarAngle       = -21.40*degree;
 OctantCutOut_Trap_AzimuthalAngle   = 90.0*degree;

 OctantCutOut_Trap_FullHeightFront  =  65.8*cm;
 OctantCutOut_Trap_FullLengthFront_Outer  = 79.95*2.0*cm;
 OctantCutOut_Trap_FullLengthFront_Inner  = 67.95*2.0*cm;
 
 OctantCutOut_Trap_FullHeightBack   =  59.3*cm;
 OctantCutOut_Trap_FullLengthBack_Outer  = 90.45*2.0*cm;
 OctantCutOut_Trap_FullLengthBack_Inner  = 79.635*2.0*cm;

 //---------------------------
 // Conical cutouts are not used anymore for the Shielding Wall
 // However I will leave the code here
 /*
 OctantCutOut_Cone_FrontInnerDiameter = 153.0*mm;
 OctantCutOut_Cone_FrontOuterDiameter = 500.0*mm;
 OctantCutOut_Cone_BackInnerDiameter  = 193.0*mm;
 OctantCutOut_Cone_BackOuterDiameter  = 600.0*mm;
 OctantCutOut_Cone_StartingPhiAngle   = -12.0*degree;
 OctantCutOut_Cone_DeltaPhiAngle      =  24.0*degree;
 */
  
 // define wall geometry values
 ShieldingWallHousing_FullLength_X = 670.56*cm;    // Full X length (264")
 ShieldingWallHousing_FullLength_Y = 670.56*cm;    // Full Y length 
 ShieldingWallHousing_FullLength_Z =  80.0*cm;    // Full Z length 

 ShieldingWallHousing_UpStreamWall_ZPosition = 340.0*cm;
 ShieldingWallHousing_CenterZPosition        = ShieldingWallHousing_UpStreamWall_ZPosition + 0.5*ShieldingWallHousing_FullLength_Z; 

 // get shielding wall material
 ShieldingWallHousing_Material = pMaterial->GetMaterial("ShieldingConcrete");  
 //ShieldingWallHousing_Material = pMaterial->GetMaterial("CDA943");  

 ShieldingWallHousing_VisAtt = NULL;
 ShieldingWallHousing_VisAtt = new G4VisAttributes();

 //--------------------
 // Hut area related
 //--------------------
 //
// InnerHut_FullLength_X = 312.50*inch; // horizontally, Paulo design 
// InnerHut_FullLength_Z = 148.35*inch; // along beam  , Paulo design

// Val's changes from Paulos design 2013-04-16
 InnerHut_FullLength_X = 446.0*inch; // horizontally, Paulo design 
 InnerHut_FullLength_Z = 233.26*inch; // along beam  , Paulo design


 //--------------------
 // Front Wall related
 //--------------------
 // 
 FrontWall_Logical  = NULL;
 FrontWall_Physical = NULL;
 FrontWall_Material = NULL;
 //
// FrontWall_FullLength_X = ShieldingWallHousing_FullLength_X + 2*60.0*inch; // adding left/right block x-dim
 FrontWall_FullLength_X = ShieldingWallHousing_FullLength_X + 2*140.0*inch; // Val's change based on Paulo design 2013-05-03
 FrontWall_FullLength_Y = ShieldingWallHousing_FullLength_X + 2*24.0*inch; 
 FrontWall_FullLength_Z = 36.0*inch;
 //
 FrontWallBeamCutout_FullLength_X = ShieldingWallHousing_FullLength_X +0.01*cm;
 FrontWallBeamCutout_FullLength_Y = FrontWallBeamCutout_FullLength_X;
 FrontWallBeamCutout_FullLength_Z = FrontWall_FullLength_Z + 1.0*inch;
 //
 // Upstream face of FrontWall is not in coincience with Upstream face of shielding wall
 DeltaZOffset_FrontWall_ShieldingWall = 12.4*cm; // from SW
 FrontWall_UpStreamWall_ZPosition     = ShieldingWallHousing_UpStreamWall_ZPosition - DeltaZOffset_FrontWall_ShieldingWall ;
 FrontWall_CenterZPosition            = FrontWall_UpStreamWall_ZPosition + 0.5*FrontWall_FullLength_Z; 
 //
 MyFrontWall_Solid = NULL;
 //
 FrontWall_Material = pMaterial->GetMaterial("ShieldingConcrete");  
 //
 FrontWall_VisAtt = NULL;
 FrontWall_VisAtt = new G4VisAttributes();
    
 //--------------------
 // Back Wall related
 //--------------------
 // 
 BackWall_Logical  = NULL;
 BackWall_Physical = NULL;
 BackWall_Material = NULL;
 //
// BackWall_FullLength_X = 312.0*inch;  // Paulo IDEAS
 BackWall_FullLength_X = 546.0*inch;  // Paulo's drawings!  Updated by Val 2013-05-03
 BackWall_FullLength_Y = 312.0*inch;  // Paulo IDEAS
 //BackWall_FullLength_Z =  48.0*inch;  // Paulo IDEAS
 BackWall_FullLength_Z =  52.0*inch;  // Paulo's drawings!  Updated by Val 2013-04-16
 //
 BackWallBeamCutout_FullLength_X = 29.0*inch +0.01*cm;
 BackWallBeamCutout_FullLength_Y = BackWallBeamCutout_FullLength_X;
 BackWallBeamCutout_FullLength_Z = BackWall_FullLength_Z + 1.0*inch;
 //
 BackWall_CenterZPosition        = FrontWall_CenterZPosition +0.5*FrontWall_FullLength_Z + InnerHut_FullLength_Z + 0.5*BackWall_FullLength_Z; 
 //
 MyBackWall_Solid = NULL;
 //
 BackWall_Material = pMaterial->GetMaterial("ShieldingConcrete");  
 //
 BackWall_VisAtt = NULL;
 BackWall_VisAtt = new G4VisAttributes();


 //------------------------------
 // Beam Left Side Wall related
 //------------------------------
 // 
 BeamLeftSideWall_Logical  = NULL;
 BeamLeftSideWall_Physical = NULL;
 BeamLeftSideWall_Material = NULL;
 //
 BeamLeftSideWall_FullLength_X =  48.0*inch;  // Paulo IDEAS
 BeamLeftSideWall_FullLength_Y = BackWall_FullLength_Y;  // Paulo IDEAS
// BeamLeftSideWall_FullLength_Z = InnerHut_FullLength_Z + 48.0*inch + 15*inch;  // Paulo IDEAS
 BeamLeftSideWall_FullLength_Z = InnerHut_FullLength_Z;// Paulo Drawing - Val change 2013-05-03

//
 BeamLeftSideWall_CenterXPosition = -1.0*(0.5*InnerHut_FullLength_X + 0.5*BeamLeftSideWall_FullLength_X); 
 BeamLeftSideWall_CenterZPosition = FrontWall_CenterZPosition + 0.5*FrontWall_FullLength_Z + 0.5*BeamLeftSideWall_FullLength_Z; 
 //
  BeamLeftSideWall_Material = pMaterial->GetMaterial("ShieldingConcrete");  
 //
 BeamLeftSideWall_VisAtt = NULL;
 BeamLeftSideWall_VisAtt = new G4VisAttributes();


 //------------------------------
 // Beam Right Side Wall related
 //------------------------------
 // 
 BeamRightSideWall_Logical  = NULL;
 BeamRightSideWall_Physical = NULL;
 BeamRightSideWall_Material = NULL;
 //
 BeamRightSideWall_FullLength_X =  BeamLeftSideWall_FullLength_X;
 BeamRightSideWall_FullLength_Y =  BeamLeftSideWall_FullLength_Y;
 BeamRightSideWall_FullLength_Z =  BeamLeftSideWall_FullLength_Z;
 //
 BeamRightSideWall_CenterXPosition = 0.5*InnerHut_FullLength_X + 0.5*BeamRightSideWall_FullLength_X; 
 BeamRightSideWall_CenterZPosition = BeamLeftSideWall_CenterZPosition;
 //
 BeamRightSideWall_Material = pMaterial->GetMaterial("ShieldingConcrete");  
 //
 BeamRightSideWall_VisAtt = NULL;
 BeamRightSideWall_VisAtt = new G4VisAttributes();

 //------------------------------
 // Top Wall related
 //------------------------------
 // 
 TopWall_Logical  = NULL;
 TopWall_Physical = NULL;
 TopWall_Material = NULL;
 //
 TopWall_FullLength_X = InnerHut_FullLength_X + BeamLeftSideWall_FullLength_X;
 TopWall_FullLength_Y =  20.0*inch;
// TopWall_FullLength_Z = BackWall_CenterZPosition - FrontWall_CenterZPosition;
 TopWall_FullLength_Z = BackWall_CenterZPosition - FrontWall_CenterZPosition + 4.0*inch; //Val's change to fit new Hut size 2013/05-03
 //
 TopWall_CenterYPosition = 0.5*BeamLeftSideWall_FullLength_Y + 0.5*TopWall_FullLength_Y; 
// TopWall_CenterZPosition = 0.5*(FrontWall_CenterZPosition + BackWall_CenterZPosition) - 18.0*inch;
 TopWall_CenterZPosition = 0.5*(FrontWall_CenterZPosition + BackWall_CenterZPosition) - 8.0*inch; //Val's change to fit new Hut size 2013/05-03
 //
 TopWall_Material = pMaterial->GetMaterial("ShieldingConcrete");  
 //
 TopWall_VisAtt = NULL;
 TopWall_VisAtt = new G4VisAttributes();

//--------------------------------------------------


ShieldingWallMessenger = NULL; 
ShieldingWallMessenger = new QweakSimShieldingWallMessenger(this);


//--------------------------------------------------

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimShieldingWall::~QweakSimShieldingWall()
{
  if (ShieldingWallMessenger) delete ShieldingWallMessenger;
  if (pMaterial)              delete pMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::DefineOctantCutOut_UsingATrapezoid()
{
G4cout << G4endl << "###### Calling QweakSimShieldingWall::DefineOctantCutOut() " << G4endl << G4endl;

  // definition of octant cut out
   OctantCutOut_Trap_Solid = new G4Trap("Octant_cut",
		    0.5 * ShieldingWallHousing_FullLength_Z +0.1*mm,     // Half-length along the z-axis
		    OctantCutOut_Trap_PolarAngle,                        // Polar angle of the line joining the centres of the 
					                                 // faces at -/+pDz
		    OctantCutOut_Trap_AzimuthalAngle,                    // Azimuthal angle of the line joining the centre  of the 
					                                 // face at -pDz to the centre of the face at +pDz
		    0.5*OctantCutOut_Trap_FullHeightFront,               // Half-length along y of the face at -pDz  
		    0.5*OctantCutOut_Trap_FullLengthFront_Outer,         // Half-length along x of the side at y=-pDy1 of the face 
					                                 // at -pDz
		    0.5*OctantCutOut_Trap_FullLengthFront_Inner,         // Half-length along x of the side at y=+pDy1 of the face 
					                                 // at -pDz
		    0.0*degree,                                          // Angle with respect to the y axis from the centre of the  
					                                 // side at y=-pDy1 to the centre at y=+pDy1 of the face 
					                                 // at -pDz
		    0.5*OctantCutOut_Trap_FullHeightBack,                // Half-length along y of the face at +pDz
		    0.5*OctantCutOut_Trap_FullLengthBack_Outer,          // Half-length along x of the side at y=-pDy2 of the face 
				                                         // at +pDz
		    0.5*OctantCutOut_Trap_FullLengthBack_Inner,          // Half-length along x of the side at y=+pDy2 of the face 
					                                 // at +pDz             
		    0.0*degree                                           // Angle with respect to the y axis from the centre of the 
					                                 // side at y=-pDy2 to the centre at y=+pDy2 of the face 
					                                 // at +pDz
 		    );
   
G4cout << G4endl << "###### Leaving QweakSimShieldingWall::DefineOctantCutOut() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::DefineOctantCutOut_UsingACone()
{
  G4cout << G4endl << "###### Calling QweakSimShieldingWall::DefineOctantCutOut() " << G4endl << G4endl;

  // definition of octant cut out
   OctantCutOut_Cone_Solid = new G4Cons("Octant_cut",
					 0.5*OctantCutOut_Cone_FrontInnerDiameter,
					 0.5*OctantCutOut_Cone_FrontOuterDiameter,
					 0.5*OctantCutOut_Cone_BackInnerDiameter,
					 0.5*OctantCutOut_Cone_BackOuterDiameter,
					 0.5*ShieldingWallHousing_FullLength_Z +0.1*mm,
					 OctantCutOut_Cone_StartingPhiAngle,
					 OctantCutOut_Cone_DeltaPhiAngle
					 );

  G4cout << G4endl << "###### Leaving QweakSimShieldingWall::DefineOctantCutOut() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimShieldingWall::ConstructShieldingWallHousing_UsingTrapezoids(G4VPhysicalVolume* MotherVolume)
{
G4cout << G4endl << "###### Calling QweakSimShieldingWall::ConstructComponent() " << G4endl << G4endl;

  // define center position
  positionShieldingWallHousing = G4ThreeVector(0.0*cm,0.0*cm,ShieldingWallHousing_CenterZPosition);

  
  // define shielding wall solid volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define ShieldingWall_Solid " << G4endl << G4endl;
  
  G4Box* ShieldingWallHousing_Solid    = new G4Box("ShieldingWallHousing_Sol",
					     0.5 * ShieldingWallHousing_FullLength_X ,    // half X length required by Geant4
					     0.5 * ShieldingWallHousing_FullLength_Y ,    // half Y length required by Geant4
					     0.5 * ShieldingWallHousing_FullLength_Z );   // half Z length required by Geant4



  // Cut in the the shielding wall due to beam line
  G4Tubs* BeamlimeHole = new G4Tubs("Beamline_cut",0.0*cm,50.0*cm,ShieldingWallHousing_FullLength_Z,0.0*degree,360.0*degree);


  // subtract beam linbe hole from shielding wall
  MyShieldingWallHousing_Solid[0] =  new G4SubtractionSolid("Wall-Hole",ShieldingWallHousing_Solid, BeamlimeHole); 


  // get the trapezoidal octant cut out solid
  DefineOctantCutOut_UsingATrapezoid();

  // I tried to use <vector> for a octant translation and rotation loop
  // but G4Transform3D is very stubborn to accept  a vector or matrix component as an argument....
  // So I do it 8x the very stupid way ....

  // octant #1 location
  G4double         Angle_Octant1;
  G4ThreeVector    Translation_Octant1;
  G4RotationMatrix Rotation_Octant1;  

  Angle_Octant1 = 90.0*degree;
  Translation_Octant1.setX(cos(Angle_Octant1)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant1.setY(sin(Angle_Octant1)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant1.setZ(0.0*cm);
    
  //Rotation_Octant1.rotateZ(Angle_Octant1);
  Rotation_Octant1.rotateZ(Angle_Octant1+90*degree);
  
  G4Transform3D Transform3D_Octant1(Rotation_Octant1,Translation_Octant1); 

  // octant #2 location
  G4double         Angle_Octant2;
  G4ThreeVector    Translation_Octant2;
  G4RotationMatrix Rotation_Octant2;  

  Angle_Octant2 = 45.0*degree;
  Translation_Octant2.setX(cos(Angle_Octant2)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant2.setY(sin(Angle_Octant2)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant2.setZ(0.0*cm);
    
  Rotation_Octant2.rotateZ(Angle_Octant2+90*degree);
  
  G4Transform3D Transform3D_Octant2(Rotation_Octant2,Translation_Octant2); 

  // octant #3 location
  G4double         Angle_Octant3;
  G4ThreeVector    Translation_Octant3;
  G4RotationMatrix Rotation_Octant3;  

  Angle_Octant3 = 0.0*degree;
  Translation_Octant3.setX(cos(Angle_Octant3)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant3.setY(sin(Angle_Octant3)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant3.setZ(0.0*cm);
    
  Rotation_Octant3.rotateZ(Angle_Octant3+90*degree);
  
  G4Transform3D Transform3D_Octant3(Rotation_Octant3,Translation_Octant3); 

  // octant #4 location
  G4double         Angle_Octant4;
  G4ThreeVector    Translation_Octant4;
  G4RotationMatrix Rotation_Octant4;  

  Angle_Octant4 = 315.0*degree;
  Translation_Octant4.setX(cos(Angle_Octant4)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant4.setY(sin(Angle_Octant4)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant4.setZ(0.0*cm);
    
  Rotation_Octant4.rotateZ(Angle_Octant4+90*degree);
  
  G4Transform3D Transform3D_Octant4(Rotation_Octant4,Translation_Octant4); 


  // octant #5 location
  G4double         Angle_Octant5;
  G4ThreeVector    Translation_Octant5;
  G4RotationMatrix Rotation_Octant5;  

  Angle_Octant5 = 270.0*degree;
  Translation_Octant5.setX(cos(Angle_Octant5)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant5.setY(sin(Angle_Octant5)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant5.setZ(0.0*cm);
    
  Rotation_Octant5.rotateZ(Angle_Octant5+90*degree);
  
  G4Transform3D Transform3D_Octant5(Rotation_Octant5,Translation_Octant5); 


  // octant #6 location
  G4double         Angle_Octant6;
  G4ThreeVector    Translation_Octant6;
  G4RotationMatrix Rotation_Octant6;  

  Angle_Octant6 = 225.0*degree;
  Translation_Octant6.setX(cos(Angle_Octant6)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant6.setY(sin(Angle_Octant6)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant6.setZ(0.0*cm);
    
  Rotation_Octant6.rotateZ(Angle_Octant6+90*degree);
  
  G4Transform3D Transform3D_Octant6(Rotation_Octant6,Translation_Octant6); 

 
// octant #7 location
  G4double         Angle_Octant7;
  G4ThreeVector    Translation_Octant7;
  G4RotationMatrix Rotation_Octant7;  

  Angle_Octant7 = 180.0*degree;
  Translation_Octant7.setX(cos(Angle_Octant7)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant7.setY(sin(Angle_Octant7)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant7.setZ(0.0*cm);
    
  Rotation_Octant7.rotateZ(Angle_Octant7+90*degree);
  
  G4Transform3D Transform3D_Octant7(Rotation_Octant7,Translation_Octant7);

// octant #8 location
  G4double         Angle_Octant8;
  G4ThreeVector    Translation_Octant8;
  G4RotationMatrix Rotation_Octant8;  

  Angle_Octant8 = 135.0*degree;
  Translation_Octant8.setX(cos(Angle_Octant8)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant8.setY(sin(Angle_Octant8)*OctantCutOut_Trap_RadialDistance);
  Translation_Octant8.setZ(0.0*cm);
    
  Rotation_Octant8.rotateZ(Angle_Octant8+90*degree);
  
  G4Transform3D Transform3D_Octant8(Rotation_Octant8,Translation_Octant8);


   // subtract octant hole from shielding wall
   MyShieldingWallHousing_Solid[1] =  new G4SubtractionSolid ("Wall-Octant1",
						       MyShieldingWallHousing_Solid[0], 
						       OctantCutOut_Trap_Solid,
						       Transform3D_Octant1 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[2] =  new G4SubtractionSolid ("Wall-Octant2",
						       MyShieldingWallHousing_Solid[1], 
						       OctantCutOut_Trap_Solid,
						       Transform3D_Octant2 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[3] =  new G4SubtractionSolid ("Wall-Octant3",
						       MyShieldingWallHousing_Solid[2], 
						       OctantCutOut_Trap_Solid,
						       Transform3D_Octant3 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[4] =  new G4SubtractionSolid ("Wall-Octant4",
						       MyShieldingWallHousing_Solid[3], 
						       OctantCutOut_Trap_Solid,
						       Transform3D_Octant4 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[5] =  new G4SubtractionSolid ("Wall-Octant5",
						       MyShieldingWallHousing_Solid[4], 
						       OctantCutOut_Trap_Solid,
						       Transform3D_Octant5 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[6] =  new G4SubtractionSolid ("Wall-Octant6",
						       MyShieldingWallHousing_Solid[5], 
						       OctantCutOut_Trap_Solid,
						       Transform3D_Octant6 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[7] =  new G4SubtractionSolid ("Wall-Octant7",
						       MyShieldingWallHousing_Solid[6], 
						       OctantCutOut_Trap_Solid,
						       Transform3D_Octant7 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[8] =  new G4SubtractionSolid ("Wall-Octant8",
						       MyShieldingWallHousing_Solid[7], 
						       OctantCutOut_Trap_Solid,
						       Transform3D_Octant8 ); 



 
  // define Shielding logical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define ShieldingWall_Logical " << G4endl << G4endl;
  
  ShieldingWallHousing_Logical  = new G4LogicalVolume(MyShieldingWallHousing_Solid[8],
				       ShieldingWallHousing_Material,
				       "ShieldingWallHousing_Log",
				       0,0,0);




  // define shielding wall physical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define ShieldingWall_Physical " << G4endl << G4endl;
     ShieldingWallHousing_Physical   = new G4PVPlacement(0, 
				       positionShieldingWallHousing, 
				       "ShieldingWallHousing", 
				       ShieldingWallHousing_Logical,
				       MotherVolume, 
				       false, 
				       0,
				       pSurfChk);
// jpan@nuclear.uwinnipeg.ca

G4cout << G4endl << "###### QweakSimShieldingWall: Setting Attributes " << G4endl << G4endl;

  G4Colour  blue      (0.,0.,1.);
  G4Colour  mangenta  (237/255.,173/255.,255/255.);
  G4Colour  mangenta1 (104/255., 49/255., 94/255.);

  ShieldingWallHousing_VisAtt->SetColor(mangenta1);
  ShieldingWallHousing_VisAtt->SetVisibility(true);
  //ShieldingWallHousing_VisAtt->SetVisibility(false);
  //ShieldingWallHousing_VisAtt->SetForceWireframe(true);
  ShieldingWallHousing_VisAtt->SetForceSolid(true);
  ShieldingWallHousing_Logical->SetVisAttributes(ShieldingWallHousing_VisAtt); 

G4cout << G4endl << "###### Leaving QweakSimShieldingWall::ConstructComponent() " << G4endl << G4endl;

} // end of  QweakSimShieldingWall::ConstructComponent()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimShieldingWall::SetCollimatorWallMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing CollimatorWall Material: Looking up Material  " << G4endl; 
                ShieldingWallHousing_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing CollimatorWall Material:  Now the CollimatorWall is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing CollimatorWall Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimShieldingWall::DestroyComponent()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimShieldingWall::SetCollimatorWall_CenterPositionInZ(G4double zPos)
{
G4cout << G4endl << "###### Calling QweakSimShieldingWall::SetCollimatorWall_CenterPositionInZ() " << G4endl << G4endl;

 ShieldingWallHousing_Physical->SetTranslation(G4ThreeVector(0.,0., zPos));

G4cout << G4endl << "###### Leaving QweakSimShieldingWall::SetCollimatorWall_CenterPositionInZ() " << G4endl << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetOctantCutOut_Trap_RadialDistance(G4double myRadialDistance)
{
G4cout << "###### Calling QweakSimShieldingWall::SetOctantCutOut_RadialDistance() " << G4endl << G4endl;
  OctantCutOut_Trap_RadialDistance = myRadialDistance;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetOctantCutOut_Trap_FullLengthFront_Outer(G4double myFullLengthFront)
{
G4cout << "###### Calling QweakSimShieldingWall::SetOctantCutOut_FullLengthFront_Outer() " << G4endl << G4endl;
  OctantCutOut_Trap_FullLengthFront_Outer = myFullLengthFront;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetOctantCutOut_Trap_FullLengthFront_Inner(G4double myFullLengthFront)
{
G4cout << "###### Calling QweakSimShieldingWall::SetOctantCutOut_FullLengthFront_Inner() " << G4endl << G4endl;
  OctantCutOut_Trap_FullLengthFront_Inner = myFullLengthFront;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetOctantCutOut_Trap_FullLengthBack_Outer(G4double myFullLengthBack)
{
G4cout << "###### Calling QweakSimShieldingWall::SetOctantCutOut_FullLengthBack_Outer() " << G4endl << G4endl;
  OctantCutOut_Trap_FullLengthBack_Outer = myFullLengthBack;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetOctantCutOut_Trap_FullLengthBack_Inner(G4double myFullLengthBack)
{
G4cout << "###### Calling QweakSimShieldingWall::SetOctantCutOut_FullLengthBack_Inner() " << G4endl << G4endl;
  OctantCutOut_Trap_FullLengthBack_Inner = myFullLengthBack;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetOctantCutOut_Trap_FullHeightFront(G4double myFullHeightFront)
{
G4cout << "###### Calling QweakSimShieldingWall::SetOctantCutOut_FullHeightFront() " << G4endl << G4endl;
  OctantCutOut_Trap_FullHeightFront = myFullHeightFront;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetOctantCutOut_Trap_FullHeightBack(G4double myFullHeightBack)
{
G4cout << "###### Calling QweakSimShieldingWall::SetOctantCutOut_FullHeightBack() " << G4endl << G4endl;
  OctantCutOut_Trap_FullHeightBack = myFullHeightBack;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetOctantCutOut_Trap_PolarAngle(G4double myPolarAngle)
{
G4cout << "###### Calling QweakSimShieldingWall::SetOctantCutOut_PolarAngle() " << G4endl << G4endl;
  OctantCutOut_Trap_PolarAngle = myPolarAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetOctantCutOut_Trap_AzimuthalAngle(G4double myAzimuthalAngle)
{
G4cout << "###### Calling QweakSimShieldingWall::SetOctantCutOut_AzimuthalAngle() " << G4endl << G4endl;
  OctantCutOut_Trap_AzimuthalAngle = myAzimuthalAngle;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetCollimatorWall_FullLengthInX(G4double myFullLengthInX)
{
  G4cout << "###### Calling QweakSimShieldingWall::SetCollimatorWall_FullLengthInX() " << G4endl << G4endl;
ShieldingWallHousing_FullLength_X = myFullLengthInX;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetCollimatorWall_FullLengthInY(G4double myFullLengthInY)
{
  G4cout << "###### Calling QweakSimShieldingWall::SetCollimatorWall_FullLengthInY() " << G4endl << G4endl;
ShieldingWallHousing_FullLength_Y = myFullLengthInY;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::SetCollimatorWall_FullLengthInZ(G4double myFullLengthInZ)
{
  G4cout << "###### Calling QweakSimShieldingWall::SetCollimatorWall_FullLengthInZ() " << G4endl << G4endl;
ShieldingWallHousing_FullLength_Z = myFullLengthInZ;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimShieldingWall::ConstructShieldingWallHousing_UsingCones(G4VPhysicalVolume* MotherVolume)
{
G4cout << G4endl << "###### Calling QweakSimShieldingWall::ConstructComponent() " << G4endl << G4endl;

  // define center position
  positionShieldingWallHousing = G4ThreeVector(0,0,ShieldingWallHousing_CenterZPosition);

  
  // define shielding wall solid volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define ShieldingWall_Solid " << G4endl << G4endl;
  
  G4Box* ShieldingWallHousing_Solid    = new G4Box("ShieldingWallHousing_Sol",
					     0.5 * ShieldingWallHousing_FullLength_X ,    // half X length required by Geant4
					     0.5 * ShieldingWallHousing_FullLength_Y ,    // half Y length required by Geant4
					     0.5 * ShieldingWallHousing_FullLength_Z );   // half Z length required by Geant4



  // Cut in the the shielding wall due to beam line
  G4Tubs* BeamlimeHole = new G4Tubs("Beamline_cut",0.0*cm, 0.5*10.158*cm,ShieldingWallHousing_FullLength_Z,0.0*degree,360.0*degree);


  // subtract beam linbe hole from shielding wall
  MyShieldingWallHousing_Solid[0] =  new G4SubtractionSolid("Wall-Hole",ShieldingWallHousing_Solid, BeamlimeHole); 


  // get the trapezoidal octant cut out solid
  DefineOctantCutOut_UsingACone();

  // I tried to use <vector> for a octant translation and rotation loop
  // but G4Transform3D is very stubborn to accept  a vector or matrix component as an argument....
  // So I do it 8x the very stupid way ....

  // octant #1 location
  G4double         Angle_Octant1;
  G4ThreeVector    Translation_Octant1;
  G4RotationMatrix Rotation_Octant1;  

  Angle_Octant1 = 90.0*degree;
  Translation_Octant1.setX(0.0*cm);
  Translation_Octant1.setY(0.0*cm);
  Translation_Octant1.setZ(0.0*cm);
    
  Rotation_Octant1.rotateZ(Angle_Octant1);
  
  G4Transform3D Transform3D_Octant1(Rotation_Octant1,Translation_Octant1); 

  // octant #2 location
  G4double         Angle_Octant2;
  G4ThreeVector    Translation_Octant2;
  G4RotationMatrix Rotation_Octant2;  

  Angle_Octant2 = 45.0*degree;
  Translation_Octant2.setX(0.0*cm);
  Translation_Octant2.setY(0.0*cm);
  Translation_Octant2.setZ(0.0*cm);
    
  Rotation_Octant2.rotateZ(Angle_Octant2);
  
  G4Transform3D Transform3D_Octant2(Rotation_Octant2,Translation_Octant2); 

  // octant #3 location
  G4double         Angle_Octant3;
  G4ThreeVector    Translation_Octant3;
  G4RotationMatrix Rotation_Octant3;  

  Angle_Octant3 = 0.0*degree;
  Translation_Octant3.setX(0.0*cm);
  Translation_Octant3.setY(0.0*cm);
  Translation_Octant3.setZ(0.0*cm);
    
  Rotation_Octant3.rotateZ(Angle_Octant3);
  
  G4Transform3D Transform3D_Octant3(Rotation_Octant3,Translation_Octant3); 

  // octant #4 location
  G4double         Angle_Octant4;
  G4ThreeVector    Translation_Octant4;
  G4RotationMatrix Rotation_Octant4;  

  Angle_Octant4 = 315.0*degree;
  Translation_Octant4.setX(0.0*cm);
  Translation_Octant4.setY(0.0*cm);
  Translation_Octant4.setZ(0.0*cm);
    
  Rotation_Octant4.rotateZ(Angle_Octant4);
  
  G4Transform3D Transform3D_Octant4(Rotation_Octant4,Translation_Octant4); 


  // octant #5 location
  G4double         Angle_Octant5;
  G4ThreeVector    Translation_Octant5;
  G4RotationMatrix Rotation_Octant5;  

  Angle_Octant5 = 270.0*degree;
  Translation_Octant5.setX(0.0*cm);
  Translation_Octant5.setY(0.0*cm);
  Translation_Octant5.setZ(0.0*cm);
    
  Rotation_Octant5.rotateZ(Angle_Octant5);
  
  G4Transform3D Transform3D_Octant5(Rotation_Octant5,Translation_Octant5); 


  // octant #6 location
  G4double         Angle_Octant6;
  G4ThreeVector    Translation_Octant6;
  G4RotationMatrix Rotation_Octant6;  

  Angle_Octant6 = 225.0*degree;
  Translation_Octant6.setX(0.0*cm);
  Translation_Octant6.setY(0.0*cm);
  Translation_Octant6.setZ(0.0*cm);
    
  Rotation_Octant6.rotateZ(Angle_Octant6);
  
  G4Transform3D Transform3D_Octant6(Rotation_Octant6,Translation_Octant6); 

 
// octant #7 location
  G4double         Angle_Octant7;
  G4ThreeVector    Translation_Octant7;
  G4RotationMatrix Rotation_Octant7;  

  Angle_Octant7 = 180.0*degree;
  Translation_Octant7.setX(0.0*cm);
  Translation_Octant7.setY(0.0*cm);
  Translation_Octant7.setZ(0.0*cm);
    
  Rotation_Octant7.rotateZ(Angle_Octant7);
  
  G4Transform3D Transform3D_Octant7(Rotation_Octant7,Translation_Octant7);

// octant #8 location
  G4double         Angle_Octant8;
  G4ThreeVector    Translation_Octant8;
  G4RotationMatrix Rotation_Octant8;  

  Angle_Octant8 = 135.0*degree;
  Translation_Octant8.setX(0.0*cm);
  Translation_Octant8.setY(0.0*cm);
  Translation_Octant8.setZ(0.0*cm);
    
  Rotation_Octant8.rotateZ(Angle_Octant8);
  
  G4Transform3D Transform3D_Octant8(Rotation_Octant8,Translation_Octant8);


   // subtract octant hole from shielding wall
   MyShieldingWallHousing_Solid[1] =  new G4SubtractionSolid ("Wall-Octant1",
						       MyShieldingWallHousing_Solid[0], 
						       OctantCutOut_Cone_Solid,
						       Transform3D_Octant1 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[2] =  new G4SubtractionSolid ("Wall-Octant2",
						       MyShieldingWallHousing_Solid[1], 
						       OctantCutOut_Cone_Solid,
						       Transform3D_Octant2 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[3] =  new G4SubtractionSolid ("Wall-Octant3",
						       MyShieldingWallHousing_Solid[2], 
						       OctantCutOut_Cone_Solid,
						       Transform3D_Octant3 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[4] =  new G4SubtractionSolid ("Wall-Octant4",
						       MyShieldingWallHousing_Solid[3], 
						       OctantCutOut_Cone_Solid,
						       Transform3D_Octant4 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[5] =  new G4SubtractionSolid ("Wall-Octant5",
						       MyShieldingWallHousing_Solid[4], 
						       OctantCutOut_Cone_Solid,
						       Transform3D_Octant5 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[6] =  new G4SubtractionSolid ("Wall-Octant6",
						       MyShieldingWallHousing_Solid[5], 
						       OctantCutOut_Cone_Solid,
						       Transform3D_Octant6 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[7] =  new G4SubtractionSolid ("Wall-Octant7",
						       MyShieldingWallHousing_Solid[6], 
						       OctantCutOut_Cone_Solid,
						       Transform3D_Octant7 ); 

  // subtract octant hole from previous G4StbtractionSolid
   MyShieldingWallHousing_Solid[8] =  new G4SubtractionSolid ("Wall-Octant8",
						       MyShieldingWallHousing_Solid[7], 
						       OctantCutOut_Cone_Solid,
						       Transform3D_Octant8 ); 



 
  // define Shielding logical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define ShieldingWall_Logical " << G4endl << G4endl;
  
  ShieldingWallHousing_Logical  = new G4LogicalVolume(MyShieldingWallHousing_Solid[8],
				       ShieldingWallHousing_Material,
				       "ShieldingWallHousing_Log",
				       0,0,0);




  // define shielding wall physical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define ShieldingWall_Physical " << G4endl << G4endl;
  ShieldingWallHousing_Physical   = new G4PVPlacement(0, 
				       positionShieldingWallHousing, 
				       "ShieldingWallHousing", 
				       ShieldingWallHousing_Logical,
				       MotherVolume, 
				       false, 
				       0,
				       pSurfChk);


G4cout << G4endl << "###### QweakSimShieldingWall: Setting Attributes " << G4endl << G4endl;

  G4Colour  blue      (0.,0.,1.);
  G4Colour  mangenta  (237/255.,173/255.,255/255.);
  G4Colour  mangenta1 (104/255., 49/255., 94/255.);
  G4Colour  orange    (1.0, 0.5, 0.0);

  ShieldingWallHousing_VisAtt->SetColor(orange);
  ShieldingWallHousing_VisAtt->SetVisibility(true);
  //ShieldingWallHousing_VisAtt->SetForceWireframe(true);
  ShieldingWallHousing_VisAtt->SetForceSolid(true);
  ShieldingWallHousing_Logical->SetVisAttributes(ShieldingWallHousing_VisAtt); 

G4cout << G4endl << "###### Leaving QweakSimShieldingWall::ConstructComponent() " << G4endl << G4endl;

} // end of  QweakSimShieldingWall::ConstructComponent()


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::ConstructFrontWall(G4VPhysicalVolume* MotherVolume)
{
 // define center position
  positionFrontWall = G4ThreeVector(0.0*cm,0.0*cm, FrontWall_CenterZPosition);

  
  // define frontwall solid volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define ShieldingWall_Solid " << G4endl << G4endl;
  
  G4Box* FrontWall_Solid    = new G4Box("FrontWall_Sol",
					     0.5 * FrontWall_FullLength_X ,    // half X length required by Geant4
					     0.5 * FrontWall_FullLength_Y ,    // half Y length required by Geant4
					     0.5 * FrontWall_FullLength_Z );   // half Z length required by Geant4



  // Cut in the the front wall due to lead box (shielding the beam line)
  G4Box* FrontWallBeamCutout_Solid    = new G4Box("FrontWallBeamCutout_Sol",
					       0.5 * FrontWallBeamCutout_FullLength_X ,    // half X length required by Geant4
					       0.5 * FrontWallBeamCutout_FullLength_Y ,    // half Y length required by Geant4
					       0.5 * FrontWallBeamCutout_FullLength_Z );   // half Z length required by Geant4



  // subtract beam linbe hole from shielding wall
  MyFrontWall_Solid =  new G4SubtractionSolid("FrontWall-Hole", FrontWall_Solid, FrontWallBeamCutout_Solid ); 


 // define front wall logical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define FrontWall_Logical " << G4endl << G4endl;
  
  FrontWall_Logical  = new G4LogicalVolume(MyFrontWall_Solid,
					   FrontWall_Material,
					   "FrontWall_Log",
					   0,0,0);

  // define front wall physical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define FrontWall_Physical " << G4endl << G4endl;
  FrontWall_Physical   = new G4PVPlacement(0, 
					   positionFrontWall, 
					   "FrontWall", 
					   FrontWall_Logical,
					   MotherVolume, 
					   false, 
					   0,
					   pSurfChk);

G4cout << G4endl << "###### QweakSimShieldingWall: Setting Attributes for Front Wall" << G4endl << G4endl;

  G4Colour  grey      ( 127/255., 127/255., 127/255.);
  G4Colour  orange    (1.0, 0.5, 0.0);

  FrontWall_VisAtt->SetColor(orange);
  FrontWall_VisAtt->SetVisibility(true);
  //FrontWall_VisAtt->SetForceWireframe(true);
  //FrontWall_VisAtt->SetForceSolid(true);
  FrontWall_Logical->SetVisAttributes(FrontWall_VisAtt); 

G4cout << G4endl << "###### Leaving QweakSimShieldingWall::ConstructFrontWall() " << G4endl << G4endl;


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::ConstructBackWall(G4VPhysicalVolume* MotherVolume)
{
 // define center position
  positionBackWall = G4ThreeVector(0.0*cm,0.0*cm, BackWall_CenterZPosition);

  
  // define Backwall solid volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define ShieldingWall_Solid " << G4endl << G4endl;
  
  G4Box* BackWall_Solid    = new G4Box("BackWall_Sol",
					     0.5 * BackWall_FullLength_X ,    // half X length required by Geant4
					     0.5 * BackWall_FullLength_Y ,    // half Y length required by Geant4
					     0.5 * BackWall_FullLength_Z );   // half Z length required by Geant4



  // Cut in the the Back wall due to lead box (shielding the beam line)
  G4Box* BackWallBeamCutout_Solid    = new G4Box("BackWallBeamCutout_Sol",
					       0.5 * BackWallBeamCutout_FullLength_X ,    // half X length required by Geant4
					       0.5 * BackWallBeamCutout_FullLength_Y ,    // half Y length required by Geant4
					       0.5 * BackWallBeamCutout_FullLength_Z );   // half Z length required by Geant4



  // subtract beam linbe hole from shielding wall
  MyBackWall_Solid =  new G4SubtractionSolid("BackWall-Hole", BackWall_Solid, BackWallBeamCutout_Solid ); 


 // define Back wall logical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define BackWall_Logical " << G4endl << G4endl;
  
  BackWall_Logical  = new G4LogicalVolume(MyBackWall_Solid,
					   BackWall_Material,
					   "BackWall_Log",
					   0,0,0);

  // define Back wall physical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define BackWall_Physical " << G4endl << G4endl;
  BackWall_Physical   = new G4PVPlacement(0, 
					   positionBackWall, 
					   "BackWall", 
					   BackWall_Logical,
					   MotherVolume, 
					   false, 
					   0,
					   pSurfChk);

G4cout << G4endl << "###### QweakSimShieldingWall: Setting Attributes for Back Wall" << G4endl << G4endl;

  G4Colour  grey1      ( 157/255., 157/255., 157/255.);
  G4Colour  orange    (1.0, 0.5, 0.0);

  BackWall_VisAtt->SetColor(orange);
  BackWall_VisAtt->SetVisibility(true);
  //BackWall_VisAtt->SetForceWireframe(true);
  //BackWall_VisAtt->SetForceSolid(true);
  BackWall_Logical->SetVisAttributes(BackWall_VisAtt); 

G4cout << G4endl << "###### Leaving QweakSimShieldingWall::ConstructBackWall() " << G4endl << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::ConstructBeamLeftSideWall(G4VPhysicalVolume* MotherVolume)
{
 // define center position
  positionBeamLeftSideWall = G4ThreeVector(BeamLeftSideWall_CenterXPosition ,0.0*cm, BeamLeftSideWall_CenterZPosition);
  
  // define BeamLeftSidewall solid volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define BeamLeftSideWall_Solid " << G4endl << G4endl;
  
  G4Box* BeamLeftSideWall_Solid    = new G4Box("BeamLeftSideWall_Sol",
					     0.5 * BeamLeftSideWall_FullLength_X ,    // half X length required by Geant4
					     0.5 * BeamLeftSideWall_FullLength_Y ,    // half Y length required by Geant4
					     0.5 * BeamLeftSideWall_FullLength_Z );   // half Z length required by Geant4

 // define BeamLeftSide wall logical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define BeamLeftSideWall_Logical " << G4endl << G4endl;
  
  BeamLeftSideWall_Logical  = new G4LogicalVolume(BeamLeftSideWall_Solid,
						  BeamLeftSideWall_Material,
						  "BeamLeftSideWall_Log",
						  0,0,0);

  // define BeamLeftSide wall physical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define BeamLeftSideWall_Physical " << G4endl << G4endl;
  BeamLeftSideWall_Physical   = new G4PVPlacement(0, 
					   positionBeamLeftSideWall, 
					   "BeamLeftSideWall", 
					   BeamLeftSideWall_Logical,
					   MotherVolume, 
					   false, 
					   0,
					   pSurfChk);

  G4cout << G4endl << "###### QweakSimShieldingWall: Setting Attributes for BeamLeftSide Wall" << G4endl << G4endl;

  G4Colour  grey1      ( 157/255., 157/255., 157/255.);
  G4Colour  orange    (1.0, 0.5, 0.0);

  BeamLeftSideWall_VisAtt->SetColor(orange);
  BeamLeftSideWall_VisAtt->SetVisibility(true);
  //BeamLeftSideWall_VisAtt->SetForceWireframe(true);
  //BeamLeftSideWall_VisAtt->SetForceSolid(true);
  BeamLeftSideWall_Logical->SetVisAttributes(BeamLeftSideWall_VisAtt); 

  G4cout << G4endl << "###### Leaving QweakSimShieldingWall::ConstructBeamLeftSideWall() " << G4endl << G4endl;


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::ConstructBeamRightSideWall(G4VPhysicalVolume* MotherVolume)
{
 // define center position
  positionBeamRightSideWall = G4ThreeVector(BeamRightSideWall_CenterXPosition ,0.0*cm, BeamRightSideWall_CenterZPosition);
  
  // define BeamRightSidewall solid volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define BeamRightSideWall_Solid " << G4endl << G4endl;
  
  G4Box* BeamRightSideWall_Solid    = new G4Box("BeamRightSideWall_Sol",
					     0.5 * BeamRightSideWall_FullLength_X ,    // half X length required by Geant4
					     0.5 * BeamRightSideWall_FullLength_Y ,    // half Y length required by Geant4
					     0.5 * BeamRightSideWall_FullLength_Z );   // half Z length required by Geant4

 // define BeamRightSide wall logical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define BeamRightSideWall_Logical " << G4endl << G4endl;
  
  BeamRightSideWall_Logical  = new G4LogicalVolume(BeamRightSideWall_Solid,
						  BeamRightSideWall_Material,
						  "BeamRightSideWall_Log",
						  0,0,0);

  // define BeamRightSide wall physical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define BeamRightSideWall_Physical " << G4endl << G4endl;
  BeamRightSideWall_Physical   = new G4PVPlacement(0, 
					   positionBeamRightSideWall, 
					   "BeamRightSideWall", 
					   BeamRightSideWall_Logical,
					   MotherVolume, 
					   false, 
					   0,
					   pSurfChk);

  G4cout << G4endl << "###### QweakSimShieldingWall: Setting Attributes for BeamRightSide Wall" << G4endl << G4endl;

  G4Colour  grey1      ( 157/255., 157/255., 157/255.);
  G4Colour  orange    (1.0, 0.5, 0.0);

  BeamRightSideWall_VisAtt->SetColor(orange);
  BeamRightSideWall_VisAtt->SetVisibility(true);
  //BeamRightSideWall_VisAtt->SetForceWireframe(true);
  //BeamRightSideWall_VisAtt->SetForceSolid(true);
  BeamRightSideWall_Logical->SetVisAttributes(BeamRightSideWall_VisAtt); 

  G4cout << G4endl << "###### Leaving QweakSimShieldingWall::ConstructBeamRightSideWall() " << G4endl << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::ConstructTopWall(G4VPhysicalVolume* MotherVolume)
{
 // define center position
  positionTopWall = G4ThreeVector(0.0*cm, TopWall_CenterYPosition ,TopWall_CenterZPosition);
  
  // define Topwall solid volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define TopWall_Solid " << G4endl << G4endl;
  
  G4Box* TopWall_Solid    = new G4Box("TopWall_Sol",
					     0.5 * TopWall_FullLength_X ,    // half X length required by Geant4
					     0.5 * TopWall_FullLength_Y ,    // half Y length required by Geant4
					     0.5 * TopWall_FullLength_Z );   // half Z length required by Geant4

 // define Top wall logical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define TopWall_Logical " << G4endl << G4endl;
  
  TopWall_Logical  = new G4LogicalVolume(TopWall_Solid,
					 TopWall_Material,
					 "TopWall_Log",
					 0,0,0);

  // define Top wall physical volume
  G4cout << G4endl << "###### QweakSimShieldingWall: Define TopWall_Physical " << G4endl << G4endl;
  TopWall_Physical   = new G4PVPlacement(0, 
					 positionTopWall, 
					 "TopWall", 
					 TopWall_Logical,
					 MotherVolume, 
					   false, 
					 0,
					 pSurfChk);
  
  G4cout << G4endl << "###### QweakSimShieldingWall: Setting Attributes for Top Wall" << G4endl << G4endl;
  
  G4Colour  grey1      ( 157/255., 157/255., 157/255.);
  G4Colour  orange    (1.0, 0.5, 0.0);
  
  TopWall_VisAtt->SetColor(orange);
  TopWall_VisAtt->SetVisibility(true);
  //TopWall_VisAtt->SetForceWireframe(true);
  //TopWall_VisAtt->SetForceSolid(true);
  TopWall_Logical->SetVisAttributes(TopWall_VisAtt); 

  G4cout << G4endl << "###### Leaving QweakSimShieldingWall::ConstructTopWall() " << G4endl << G4endl;
  

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::ShowCollimatorWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::ShowCollimatorWall() " << G4endl << G4endl;

  ShieldingWallHousing_VisAtt->SetVisibility(true);

  G4cout << "###### Leaving QweakSimShieldingWall::ShowCollimatorWall() " << G4endl << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::HideCollimatorWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::HideCollimatorWall() " << G4endl << G4endl;

  ShieldingWallHousing_VisAtt->SetVisibility(false);

  G4cout << "###### Leaving QweakSimShieldingWall::HideCollimatorWall() " << G4endl << G4endl;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::ShowFrontWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::ShowFrontWall() " << G4endl << G4endl;

  FrontWall_VisAtt->SetVisibility(true);

  G4cout << "###### Leaving QweakSimShieldingWall::ShowFrontWall() " << G4endl << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::HideFrontWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::HideFrontWall() " << G4endl << G4endl;

  FrontWall_VisAtt->SetVisibility(false);

  G4cout << "###### Leaving QweakSimShieldingWall::HideFrontWall() " << G4endl << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::ShowBackWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::ShowBackWall() " << G4endl << G4endl;

  BackWall_VisAtt->SetVisibility(true);

  G4cout << "###### Leaving QweakSimShieldingWall::ShowBackWall() " << G4endl << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::HideBackWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::HideBackWall() " << G4endl << G4endl;

  BackWall_VisAtt->SetVisibility(false);

  G4cout << "###### Leaving QweakSimShieldingWall::HideBackWall() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::ShowBeamLeftSideWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::ShowBeamLeftSideWall() " << G4endl << G4endl;

  BeamLeftSideWall_VisAtt->SetVisibility(true);

  G4cout << "###### Leaving QweakSimShieldingWall::ShowBeamLeftSideWall() " << G4endl << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::HideBeamLeftSideWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::HideBeamLeftSideWall() " << G4endl << G4endl;

  BeamLeftSideWall_VisAtt->SetVisibility(false);

  G4cout << "###### Leaving QweakSimShieldingWall::HideBeamLeftSideWall() " << G4endl << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::ShowBeamRightSideWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::ShowBeamRightSideWall() " << G4endl << G4endl;

  BeamRightSideWall_VisAtt->SetVisibility(true);

  G4cout << "###### Leaving QweakSimShieldingWall::ShowBeamRightSideWall() " << G4endl << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::HideBeamRightSideWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::HideBeamRightSideWall() " << G4endl << G4endl;

  BeamRightSideWall_VisAtt->SetVisibility(false);

  G4cout << "###### Leaving QweakSimShieldingWall::HideBeamRightSideWall() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::ShowTopWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::ShowTopWall() " << G4endl << G4endl;

  TopWall_VisAtt->SetVisibility(true);

  G4cout << "###### Leaving QweakSimShieldingWall::ShowTopWall() " << G4endl << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimShieldingWall::HideTopWall()
{
  G4cout << "###### Calling QweakSimShieldingWall::HideTopWall() " << G4endl << G4endl;

  TopWall_VisAtt->SetVisibility(false);

  G4cout << "###### Leaving QweakSimShieldingWall::HideTopWall() " << G4endl << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimShieldingWall.cc,v $
//      Revision 1.6  2006/05/05 21:54:17  grimm
//      The ShieldingWallHousing_UpStreamWall_ZPosition moved from 380*cm down to 330.0*cm
//      according to Paulo's drawings. Frees some space needed by the VDCs.
//
//      To be checked: Octant Cutouts
//
//      Revision 1.5  2006/04/26 20:01:57  grimm
//      The shielding wall has been extended to a shielding detector hut
//
//      Revision 1.4  2006/01/18 20:20:34  grimm
//      Added visibility functions: ShowShieldingWall(), HideShieldingWall()
//
//      Revision 1.3  2005/12/28 23:27:28  grimm
//      Changed material from CDA* used for the collimators to concrete.
//
//      Revision 1.2  2005/12/27 19:14:36  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
