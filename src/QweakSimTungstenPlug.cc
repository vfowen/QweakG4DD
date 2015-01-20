/**
 
   \file QweakSimTungstenPlug.cc

   \author Wouter Deconinck

*/
//=============================================================================

#include "QweakSimTungstenPlug.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTungstenPlug::QweakSimTungstenPlug()
{
  // W-Plug
  WPlug_US_Logical      = NULL;
  WPlug_US_Physical     = NULL;
  WPlug_DS_Logical      = NULL;
  WPlug_DS_Physical     = NULL;
  
  // get access to material definition
  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();

  // WPlug Material
  WPlug_Material = pMaterial->GetMaterial("G4_W");  // For now...I thought this was an alloy....
  WPlug_Material_Vac = pMaterial->GetMaterial("Vacuum");  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTungstenPlug::~QweakSimTungstenPlug()
{
  if (pMaterial) delete pMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTungstenPlug::ConstructTungstenPlug(G4VPhysicalVolume* MotherVolume)
{
  // define W plug
  G4Cons *WPlug_Solid_US = new G4Cons("WPlug_Solid_US",
				      0.7455*cm,
				      4.14*cm,
				      0.8763*cm,
				      4.14*cm,  // 4.20  
				      4.13766*cm,  // 7.62
				      0,
				      360*degree);    
  
  G4Cons *WPlug_Solid_US_Vac = new G4Cons("WPlug_Solid_US_Vac",
					  0.0*cm,
					  0.7455*cm,
					  0.0*cm,
					  0.8763*cm,  // 4.20  
					  4.14*cm,  // 7.62
					  0,
					  360*degree);  
  
  G4SubtractionSolid* WPlug_US_Solid = new G4SubtractionSolid("WPlug_Solid_US - WPlug_Solid_US_Vac", 
								   WPlug_Solid_US, 
								   WPlug_Solid_US_Vac);
    
  
  G4Tubs *WPlug_Solid_DS = new G4Tubs("WPlug_Solid_DS",
				      1.905*cm,
				      4.2*cm,
				      6.34*cm,
				      0,
				      360*degree);    
  G4Tubs *WPlug_Solid_DS_Vac = new G4Tubs("WPlug_Solid_DS_Vac",
					  0,
					  1.905*cm,
					  6.34*cm,
					  0,
					  360*degree);    
  
  G4SubtractionSolid* WPlug_DS_Solid = new G4SubtractionSolid("WPlug_Solid_DS - WPlug_Solid_DS_Vac", 
								   WPlug_Solid_DS, 
								   WPlug_Solid_DS_Vac);
  
  WPlug_US_Logical = new G4LogicalVolume(WPlug_US_Solid,
					 WPlug_Material,
					 "WPlug_US_Logical");
  
  WPlug_DS_Logical = new G4LogicalVolume(WPlug_DS_Solid,
					 WPlug_Material,
					 "WPlug_DS_Logical");
  
  WPlug_US_Physical = new G4PVPlacement(0,                  // rotation
					G4ThreeVector(0,0*cm,-575.7895*cm-3.5*cm),   // plug position
					"WPlugContainer_US",
					WPlug_US_Logical,
					MotherVolume,
					false,
					0,
					pSurfChk);
  
  WPlug_DS_Physical = new G4PVPlacement(0,                  // rotation
					G4ThreeVector(0,0*cm,-575.7895*cm+6.98*cm),   // plug position
					"WPlugContainer_DS",
					WPlug_DS_Logical,
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

  G4VisAttributes* WPlug_VisAtt = new G4VisAttributes(red);
  WPlug_VisAtt -> SetVisibility(true);
  WPlug_US_Logical -> SetVisAttributes(WPlug_VisAtt);
  WPlug_US_Logical->SetVisAttributes(WPlug_VisAtt);
  WPlug_DS_Logical -> SetVisAttributes(WPlug_VisAtt);
  WPlug_DS_Logical->SetVisAttributes(WPlug_VisAtt);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
