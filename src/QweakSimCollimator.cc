//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimCollimator.cc

   $Revision: 1.10 $	
   $Date: 2005/12/28 22:40:43 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

// jpan:
// collimator 1: z=-575.7895+/-7.62 cm
//            2: z=-378.2195+/-7.50 cm
//            3: z=-266.244+/-5.615 cm

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimCollimator.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCollimator::QweakSimCollimator()
{
  CollimatorHousing_Logical  = NULL;
  CollimatorHousing_Physical = NULL;


  CollimatorHousing_CenterZPosition = -575.7895*cm;//-579.79*cm
  CollimatorHousing_FullLength_X    = 120.0*cm;//should be update to 86.36*cm
  CollimatorHousing_FullLength_Y    = 120.0*cm;//86.36*cm
  CollimatorHousing_FullLength_Z    = 15.24*cm;

  BeamlineCutoutDiameter            = 8.3*cm;//8.0*cm

  OctantCutOutFrontFullLength_Y     = 5.04*cm;//3.28*cm
  OctantCutOutFrontFullLength_X1    = 6.38*cm;//7.66*cm
  OctantCutOutFrontFullLength_X2    = 6.38*cm;//7.66*cm
  OctantCutOutBackFullLength_Y      = 5.83*cm;//6.25*cm
  OctantCutOutBackFullLength_X1     = 7.30*cm;//7.66*cm
  OctantCutOutBackFullLength_X2     = 7.30*cm;//7.66*cm
  OctantCutOutFrontInnerDiameter    = 10.42*cm;//10.0*cm
  OctantCutOutFrontOuterDiameter    = 21.38*cm;//26.14*cm
  OctantCutOutBackInnerDiameter     = 14.06*cm;//12.40*cm
  OctantCutOutBackOuterDiameter     = 25.26*cm;//26.14*cm
  OctantCutOutStartingPhiAngle      = (-16.61 + 90.0)*degree;//(-16.344+90)*degree
  OctantCutOutDeltaPhiAngle         = 2.0*16.61*degree;//2.0*16.344*degree
  OctantCutOutRadialOffset          = 0.0*cm;

  // get access to material definition
  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimCollimator::~QweakSimCollimator()
{
  if (pMaterial) delete pMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCollimator::DestroyComponent()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCollimator::ConstructCollimator(G4VPhysicalVolume* MotherVolume)
{

  //---------------------------------------------------------------------------------------------
  //! Creates a Collimator with 8 cutouts
  /**

   \param MotherVolume The physical volume in which the collimator will be placed

   */
  //---------------------------------------------------------------------------------------------

  G4double PI                                = 3.14159265359;     //probably defined
                                                                    //somewhere else, but
                                                                    //what the heck

  // assign material
  G4Material* CollimatorHousing_Material = pMaterial->GetMaterial("PBA");


  std::vector< G4SubtractionSolid* >  Solids;
  Solids.clear();
  Solids.resize(17); //1 for beamline 2*8 for acceptance cutouts
  G4ThreeVector positionCollimatorHousing;


  //**********************************************************************************
  //Construct collimator main volume
  G4Box* CollimatorHousing_Solid    = new G4Box("CollimatorHousing_Sol",
						0.5 * CollimatorHousing_FullLength_X - 0.05*cm, 
						0.5 * CollimatorHousing_FullLength_Y - 0.05*cm, 
						0.5 * CollimatorHousing_FullLength_Z - 0.05*cm);
  //**********************************************************************************




  //**********************************************************************************
  //Construct beam line cutout
  G4Tubs* BeamlimeHole = new G4Tubs("Beamline_cut",0.0*cm, 
				    BeamlineCutoutDiameter/2.0,
				    0.5*CollimatorHousing_FullLength_Z,
				    0.0*degree,360.0*degree);
  //**********************************************************************************



  //**********************************************************************************
  //Construct the pie shape cutout for collimator acceptance
  G4double zPlanes[2] = {-1.0*CollimatorHousing_FullLength_Z/2.0,
			 CollimatorHousing_FullLength_Z/2.0};
  G4double rInner[2]  = {OctantCutOutFrontInnerDiameter/2.0,
			 OctantCutOutBackInnerDiameter/2.0};
  G4double rOuter[2]  = {OctantCutOutFrontOuterDiameter/2.0,
			 OctantCutOutBackOuterDiameter/2.0};
  G4Polyhedra *Octant1Acceptance_p1 = new G4Polyhedra("Oct1Accept_p1",
						      OctantCutOutStartingPhiAngle,
						      OctantCutOutDeltaPhiAngle,
						      1,2,zPlanes,rInner,rOuter);
  //**********************************************************************************




  
  //**********************************************************************************
  //Construct weired shape cutout on top of pie, for collimator acceptance

 // G4double theta  = std::atan((OctantCutOutBackFullLength_Y-
//			       OctantCutOutFrontFullLength_Y)/
//			      CollimatorHousing_FullLength_Z/2.0)*180/PI*degree;

  G4double theta  = std::atan((OctantCutOutBackFullLength_Y-OctantCutOutFrontFullLength_Y                            +OctantCutOutBackOuterDiameter-OctantCutOutFrontOuterDiameter)/
			      CollimatorHousing_FullLength_Z/2.0)*180/PI*degree; 
  //Theta here should be defined as the polar angle of the line joining the centres of the faces at +/-Dz of the trapezoid - corrected by Jie Pan 2009/06/17

  G4double phi    = 90.0*degree;
  G4double alpha1 = 0.0*degree;
  G4double alpha2 = 0.0*degree;
  
  G4double radLoc = (OctantCutOutRadialOffset - 0.01*cm +
		     (OctantCutOutFrontOuterDiameter+
		      OctantCutOutFrontFullLength_Y + 
		      std::tan(theta)*CollimatorHousing_FullLength_Z)/2.0);
  
  //   Keep this to cuddle up to on rainy days...
  //
  //   G4Trap *Octant1Acceptance_p2 = new G4Trap("Oct1Accept_p2",
  // 					    OctantCutOutFrontFullLength_X,
  // 					    CollimatorHousing_FullLength_Z+0.2*mm,
  // 					    OctantCutOutBackFullLength_Y,
  // 					    OctantCutOutFrontFullLength_Y); //must rotate around z by 90 degrees

  G4Trap *Octant1Acceptance_p2 = new G4Trap("Oct1Accept_p2",
					    CollimatorHousing_FullLength_Z/2.0,
					    theta,phi,
					    OctantCutOutFrontFullLength_Y/2.0,
					    OctantCutOutFrontFullLength_X1/2.0,
					    OctantCutOutFrontFullLength_X2/2.0,
					    alpha1,
					    OctantCutOutBackFullLength_Y/2.0,
					    OctantCutOutBackFullLength_X1/2.0,
					    OctantCutOutBackFullLength_X2/2.0,
					    alpha2); 
  //**********************************************************************************




  //**********************************************************************************
  //**********************************************************************************
  //Place cutouts w.r.t. main collimator volume and subtract 

  //**********************************************************************************
  //Do Beamline first
  Solids[0] =  new G4SubtractionSolid("Beamline_Hole",
				      CollimatorHousing_Solid, 
				      BeamlimeHole); 
  //**********************************************************************************


  //**********************************************************************************
  //Cutouts
  char              Name[50];
  int               cnt = 0;
  G4ThreeVector     Translation;
  G4RotationMatrix *Rotation[16];

  printf("Octant   Rotation1   Solid1   Rotation2   Solid2\n\n");
 
  for(int oct = 0; oct < 8; oct++){
    G4double zRot = (oct*45.0)*degree;

    Translation.setX(std::sin(zRot)*OctantCutOutRadialOffset);
    Translation.setY(std::cos(zRot)*OctantCutOutRadialOffset);
    Translation.setZ(0.0*cm-0.01*cm);
    Rotation[2*oct] = new G4RotationMatrix(); 
    Rotation[2*oct]->rotateZ(zRot);

    sprintf(Name,"Coll_%d_Oct_%d_1",GetCollimatorNumber(),oct+1);
    Solids[2*oct+1] =  new G4SubtractionSolid(Name,Solids[2*oct],Octant1Acceptance_p1,
					      Rotation[2*oct],Translation); 


    Translation.setX(std::sin(zRot)*radLoc);
    Translation.setY(std::cos(zRot)*radLoc);
    Translation.setZ(0.0*cm+0.01*cm);
    Rotation[2*oct+1] = new G4RotationMatrix(); 
    Rotation[2*oct+1]->rotateZ(zRot);

    sprintf(Name,"Coll_%d_Oct_%d_2",GetCollimatorNumber(),oct+1);
    Solids[2*oct+2] =  new G4SubtractionSolid(Name,Solids[2*oct+1],Octant1Acceptance_p2,
					      Rotation[2*oct+1],Translation);
//     printf("Octant    Rotation1    Solid1     Rotation2      Solid2\n\n");
    printf("     %d          %02d      %02d          %02d        %02d\n",oct,2*oct,2*oct+1,2*oct+1,2*oct+2);
    cnt++;
  }
  //End cutouts
  //**********************************************************************************



  //**********************************************************************************
  // Define collimator logical and physical volumes

  CollimatorHousing_Logical  = new G4LogicalVolume(Solids[2*cnt],
						   CollimatorHousing_Material,
						   "CollimatorHousing_Log",
						   0,0,0);

  positionCollimatorHousing = G4ThreeVector(0,0,CollimatorHousing_CenterZPosition);
  CollimatorHousing_Physical   = new G4PVPlacement(0, 
						   positionCollimatorHousing, 
						   "CollimatorHousing", 
						   CollimatorHousing_Logical,
						   MotherVolume, 
						   false, 
						   0,
					           pSurfChk);

  //**********************************************************************************
  //Make it pretty...
  G4Colour  red   (1.,0.,0.);
  G4Colour  blue      (0.,0.,1.);
  G4Colour  mangenta  (237/255.,173/255.,255/255.);
  G4Colour  mangenta1 (104/255., 49/255., 94/255.);

  G4VisAttributes* CollimatorHousingVisAtt = new G4VisAttributes(mangenta1);
  CollimatorHousingVisAtt->SetVisibility(true);
  //CollimatorHousingVisAtt->SetForceSolid(true);//comment out by Jie
  //CollimatorHousingVisAtt->SetForceWireframe(true);
  CollimatorHousing_Logical->SetVisAttributes(CollimatorHousingVisAtt); 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCollimator::SetCollimatorHousingMaterial(G4String materialName)
{
//---------------------------------------------------------------------------------------------
//! Sets the material of the Collimator Housing
 /*!	
	
 \param materialName Name of the material defined in class QweakSimG4Material
    
 */
//---------------------------------------------------------------------------------------------



  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
    CollimatorHousing_Logical->SetMaterial(pttoMaterial);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimCollimator::SetCollimatorHousing_CenterPositionInZ(G4double zPos)
{
//---------------------------------------------------------------------------------------------
//! Sets the Z position of the Collimator Housing Center
 /*!	
	
 \param zPos Z position along beam line
    
 */
//---------------------------------------------------------------------------------------------

 CollimatorHousing_CenterZPosition = zPos;

 CollimatorHousing_Physical->SetTranslation(G4ThreeVector(0.,0., CollimatorHousing_CenterZPosition));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

