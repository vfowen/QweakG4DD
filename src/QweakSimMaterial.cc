#include "QweakSimMaterial.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimMaterial::DefineMaterials()
{
  G4cout << G4endl << "###### Calling QweakSimMaterial::DefineMaterials() " << G4endl << G4endl;

  // Define required materials

  G4double A;        // atomic mass
  G4double Z;        // atomic number
  G4double density;  // density

  G4double temperature;
  G4double pressure;
  G4double fractionmass;

  G4String name;
  G4String symbol;

  G4int natoms;
  G4int ncomponents;
  G4int nelements;


  //
  // Define general elements
  //

  G4Element* elH  = fNistManager->FindOrBuildElement("H");
  G4Element* elHe = fNistManager->FindOrBuildElement("He");
  //G4Element* elBe = fNistManager->FindOrBuildElement("Be");
  //G4Element* elB  = fNistManager->FindOrBuildElement("B");
  G4Element* elC  = fNistManager->FindOrBuildElement("C");
  G4Element* elN  = fNistManager->FindOrBuildElement("N");
  G4Element* elO  = fNistManager->FindOrBuildElement("O");
  //G4Element* elF  = fNistManager->FindOrBuildElement("F");
  //G4Element* elNa = fNistManager->FindOrBuildElement("Na");
  G4Element* elMg = fNistManager->FindOrBuildElement("Mg");
  G4Element* elAl = fNistManager->FindOrBuildElement("Al");
  G4Element* elSi = fNistManager->FindOrBuildElement("Si");
  //G4Element* elCl = fNistManager->FindOrBuildElement("Cl");
  G4Element* elAr = fNistManager->FindOrBuildElement("Ar");
  G4Element* elK  = fNistManager->FindOrBuildElement("K");
  G4Element* elCa = fNistManager->FindOrBuildElement("Ca");
  G4Element* elFe = fNistManager->FindOrBuildElement("Fe");
  G4Element* elNi = fNistManager->FindOrBuildElement("Ni");
  G4Element* elMn = fNistManager->FindOrBuildElement("Mn");
  G4Element* elCr = fNistManager->FindOrBuildElement("Cr");
  G4Element* elXe = fNistManager->FindOrBuildElement("Xe");
  //G4Element* elSb = fNistManager->FindOrBuildElement("Sb");
  //G4Element* elPb = fNistManager->FindOrBuildElement("Pb");
  G4Element* elZn = fNistManager->FindOrBuildElement("Zn");
	
  // elements for the LeadGlass
  G4Element* elPb = fNistManager->FindOrBuildElement("Pb");
  G4Element* elTi = fNistManager->FindOrBuildElement("Ti");
  G4Element* elAs = fNistManager->FindOrBuildElement("As");
	
  //elements for the TungstenAlloy
  G4Element* elW = fNistManager->FindOrBuildElement("W");
  G4Element* elCu = fNistManager->FindOrBuildElement("Cu");

  //define Kryptonite
  // this material will kill every tracks that touch it
  name      = "Kryptonite";
  density   = 0.00000001*mg/cm3;
  nelements = 1;
  G4Material* __attribute__ ((unused))
  matKryptonite = new G4Material(name, density, nelements);
  matKryptonite -> AddElement(elAr,1);


  //matLiquidHydrogen -> GetIonisation() -> SetMeanExcitationEnergy(21.8*eV);
//  G4Material *Kryptonite = new G4Material("Kryptonite", density= 0.00000001*mg/cm3);
//  Kryptonite->AddElement(elAr, 100.*perCent);

  // Let's get Tungsten.  This is not the alooy to be used
  // but it is fine for a test.

  //G4Element* elW = fNistManager->FindOrBuildElement("W");


  //
  // define simple materials
  //
  //
  // The G4Material class describes the macroscopic properties of the matter:
  // density, state, temperature, pressure, radiation length, mean free path,
  // dE/dx ...
  //
  // My name convention: all materials start with matXyz
  //
  // Sorted by Z

  // Liquid H2
  name      = "H2Liquid";
  density   = 0.071287*g/cm3; // From Greg, this is the density at 20 k and 32.5 psia
  nelements = 1;
  G4Material* __attribute__ ((unused))
  matLiquidHydrogen = new G4Material(name, density, nelements);
  matLiquidHydrogen -> AddElement(elH,1);
  //matLiquidHydrogen -> GetIonisation() -> SetMeanExcitationEnergy(21.8*eV);

  // Helium gas
  name      = "HeGas";
  density   = 0.1787*mg/cm3;
  nelements = 1;
  G4Material* __attribute__ ((unused))
  matGasHelium = new G4Material(name,density,nelements, kStateGas, 273.15*kelvin,1.*atmosphere);
  matGasHelium ->AddElement(elHe,1);

  // Liquid Helium 4
  name      = "HeLiquid";
  density   = 0.1249*g/cm3;
  nelements = 1;
  G4Material* __attribute__ ((unused))
  matLiquidHelium = new G4Material(name, density, nelements);
  matLiquidHelium -> AddElement(elHe,1);

  // Al material
  name      = "Aluminum";
  density   = 2.700*g/cm3;
  nelements = 1;
  G4Material* __attribute__ ((unused))
  matAl = new G4Material(name,density,nelements);
  matAl -> AddElement(elAl,1);
  //matAl -> GetIonisation() -> SetMeanExcitationEnergy(166*eV);

  // Al Alloy material
  name      = "AlAlloy";
  density   = 2.804*g/cm3; //Mean density from Greg's Target Elog 21
  ncomponents = 9;
  G4Material* __attribute__ ((unused))
    matAlAlloy = new G4Material(name,density,ncomponents);
	//Element composition breakdown from Greg's Target Elog 22
  matAlAlloy-> AddElement(elAl   , fractionmass = 0.897);
  matAlAlloy-> AddElement(elZn   , fractionmass = 0.058);
  matAlAlloy-> AddElement(elMg   , fractionmass = 0.0255);
  matAlAlloy-> AddElement(elCu   , fractionmass = 0.016);
	matAlAlloy-> AddElement(elCr	 , fractionmass = 0.0019);
  matAlAlloy-> AddElement(elFe   , fractionmass = 0.0013);
  matAlAlloy-> AddElement(elSi   , fractionmass = 0.0001);
	matAlAlloy-> AddElement(elTi 	 , fractionmass = 0.0001);
	matAlAlloy-> AddElement(elMn	 , fractionmass = 0.0001);
	//Note that the last three elements in the alloy have their %s modified to make the total 100%.

  // USCarbon material
  name      = "USCarbon";
  density   = 1.700*g/cm3;
  nelements = 1;
  G4Material* __attribute__ ((unused))
  matUSC = new G4Material(name,density,nelements);
  matUSC -> AddElement(elC,1);

  // DSCarbon material
  name      = "DSCarbon";
  density   = 2.205*g/cm3;
  nelements = 1;
  G4Material* __attribute__ ((unused))
  matDSC = new G4Material(name,density,nelements);
  matDSC -> AddElement(elC,1);

  // gaseous Argon
  name      = "ArgonGas";
  density   = 1.7836*mg/cm3; // STP
  nelements = 1;
  G4Material* __attribute__ ((unused))
  matArgonGas = new G4Material(name,density,nelements, kStateGas, 273.15*kelvin,1.*atmosphere);
  matArgonGas -> AddElement(elAr, 1);
  //matArgonGas -> GetIonisation() -> SetMeanExcitationEnergy(188*eV);

  // Iron material
  name    = "Iron";
  A       = 55.85*g/mole;
  Z       = 26.;
  density = 7.87*g/cm3;
  G4Material* __attribute__ ((unused))
  matIron = new G4Material(name,Z,A,density);

  // Copper material
  name    = "Copper";
  A       = 63.54*g/mole;
  Z       = 29.;
  density = 8.96*g/cm3;
  G4Material* __attribute__ ((unused))
  matCopper = new G4Material(name,Z,A,density);

  // Tin material
  name    = "Tin";
  A       = 118.69*g/mole;
  Z       = 50.;
  density =  7.28*g/cm3;
  G4Material* __attribute__ ((unused))
  matSn = new G4Material(name,Z,A,density);

  // Antimony material (added June-10-09 by Jie Pan)
  name    = "Sb";
  A       = 121.76*g/mole;
  Z       = 51.;
  density =  6.68*g/cm3;
  G4Material* __attribute__ ((unused))
  matSb = new G4Material(name,Z,A,density);

  // Lead material
  name    = "Lead";
  A       = 207.19*g/mole;
  Z       = 82.;
  density = 11.35*g/cm3;
  G4Material* __attribute__ ((unused))
  matPb = new G4Material(name,Z,A,density);

  // Photocathode material, approximated as elemental cesium
  name      = "Photocathode";
  density   = 5.0*g/cm3; // true??
  nelements = 1;
  G4Material* __attribute__ ((unused))
  matPhotocathode =  new G4Material(name,density,nelements);
  matPhotocathode -> AddElement(elK, 1);

  //=============================================================
  //
  // define a material from elements.   case 1: chemical molecule
  //
  //=============================================================

  // Xe gas
  name        = "XenonGas";
  density     = 5.458*mg/cm3;
  ncomponents = 1;
  G4Material* __attribute__ ((unused))
  matXe =  new G4Material(name,density, ncomponents, kStateGas,273.15*kelvin,1.*atmosphere);
  matXe -> AddElement(elXe,1);

  // CO2 , STP
  name        = "CO2";
  density     = 1.818*mg/cm3;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matCO2 = new G4Material(name,density, ncomponents, kStateGas,273.15*kelvin,1.*atmosphere);
  matCO2-> AddElement(elC, natoms=1);
  matCO2-> AddElement(elO, natoms=2);
  matCO2-> GetIonisation() -> SetMeanExcitationEnergy(85*eV);

  // Water
  name        = "Water" ;
  density     = 1.000*g/cm3;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matH2O = new G4Material(name,density ,ncomponents);
  matH2O -> AddElement(elH,natoms=2);
  matH2O -> AddElement(elO,natoms=1);
  matH2O -> GetIonisation() -> SetMeanExcitationEnergy(75.0*eV);

  // Scintillator
  name        = "Scintillator";
  density     = 1.032*g/cm3;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matScint = new G4Material(name, density, ncomponents);
  matScint->AddElement(elC, natoms=9);
  matScint->AddElement(elH, natoms=10);

  // Quartz SiO2 (e.g. Spectrosil 2000), optical properties will be added
  name        = "Quartz";
  density     = 2.200*g/cm3;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matQuartz = new G4Material(name,density, ncomponents);
  matQuartz->AddElement(elSi, natoms=1);
  matQuartz->AddElement(elO , natoms=2);

  // Quartz SiO2 (e.g. Spectrosil 2000) without optical properties
  name        = "SiO2";
  density     = 2.200*g/cm3;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matSiO2 = new G4Material(name,density, ncomponents);
  matSiO2->AddElement(elSi, natoms=1);
  matSiO2->AddElement(elO , natoms=2);

  // SiElast_Glue  The glue used to glue together the quartz pieces
  name        = "SiElast_Glue";
  density     = 2.200*g/cm3;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matSiElast = new G4Material(name,density, ncomponents);
  matSiElast->AddElement(elSi, natoms=1);
  matSiElast->AddElement(elO , natoms=2);

  // Lime Glass
  name        = "LimeGlass";
  density     = 2.200*g/cm3;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matLimeGlass = new G4Material(name,density, ncomponents);
  matLimeGlass->AddElement(elSi, natoms=1);
  matLimeGlass->AddElement(elO , natoms=2);

  // Mylar
  name        = "Mylar";
  density     = 1.397 *g/cm3;
  ncomponents = 3;
  G4Material* __attribute__ ((unused))
  matMylar = new G4Material(name,density , ncomponents);
  matMylar -> AddElement(elH, natoms= 8);
  matMylar -> AddElement(elC, natoms=10);
  matMylar -> AddElement(elO, natoms= 4);

  // Mirror
  name        = "Mirror";
  density     = 1.397 *g/cm3;
  ncomponents = 3;
  G4Material* __attribute__ ((unused))
  matMirror = new G4Material(name,density , ncomponents);
  matMirror -> AddElement(elH, natoms= 8);
  matMirror -> AddElement(elC, natoms=10);
  matMirror -> AddElement(elO, natoms= 4);

  // Tyvek (High density Polyethylene)
  //  (...-CH2-CH2-...)*n
  name        = "Tyvek";
  density     = 0.96 *g/cm3;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matTyvek = new G4Material(name,density , ncomponents);
  matTyvek -> AddElement(elH, natoms= 2);
  matTyvek -> AddElement(elC, natoms= 1);

  // Kevlar
  // (-NH-C6H4-NH-CO-C6H4-CO-)*n
  name        =	"Kevlar";
  density     = 1.44 *g/cm3;
  ncomponents = 4;
  G4Material* __attribute__ ((unused))
  matKevlar = new G4Material(name,density , ncomponents);
  matKevlar -> AddElement(elH, natoms=10 );
  matKevlar -> AddElement(elC, natoms=14);
  matKevlar -> AddElement(elO, natoms= 2);
  matKevlar -> AddElement(elN, natoms= 2);

  //
  //    ---  H        O  -----
  //        -N-(CH2)5-C-
  //
  name        = "Nylon";
  density     = 0.805*g/cm3;
  ncomponents = 4;
  G4Material* __attribute__ ((unused))
  matNylon = new G4Material(name,density , ncomponents);
  matNylon -> AddElement(elH, natoms=11 );
  matNylon -> AddElement(elC, natoms= 6);
  matNylon -> AddElement(elO, natoms= 1);
  matNylon -> AddElement(elN, natoms= 1);

  //     H H
  //  ---C-C---
  //     H COOCH3
  name        = "Acrylic";
  density     = 1.14*g/cm3;
  ncomponents = 3;
  G4Material* __attribute__ ((unused))
  matAcrylic = new G4Material(name,density , ncomponents);
  matAcrylic -> AddElement(elH, natoms= 6);
  matAcrylic -> AddElement(elC, natoms= 4);
  matAcrylic -> AddElement(elO, natoms= 2);

  //
  //  Nema grade G10 or FR4
  //
  name        = "NemaG10";
  density     = 1.70*g/cm3;
  ncomponents = 4;
  G4Material* __attribute__ ((unused))
  matG10 = new G4Material(name,density , ncomponents);
  matG10 -> AddElement(elSi, natoms=1);
  matG10 -> AddElement(elO , natoms=2);
  matG10 -> AddElement(elC , natoms=3);
  matG10 -> AddElement(elH , natoms=3);


  //======================================================================
  //
  // define a material from elements.   case 2: mixture by fractional mass
  //
  //======================================================================

  // Air material: Air 18 degr.C and 58% humidity
  name        = "Air";
  density     = 1.214*mg/cm3;
  ncomponents = 4;
  G4Material* __attribute__ ((unused))
  matAir = new G4Material(name,density,ncomponents);
  matAir -> AddElement(elN,  fractionmass=0.7494);
  matAir -> AddElement(elO,  fractionmass=0.2369);
  matAir -> AddElement(elAr, fractionmass=0.0129);
  matAir -> AddElement(elH,  fractionmass=0.0008);
  //matAir -> GetIonisation() -> SetMeanExcitationEnergy(85.7*eV);

  // Kapton
  name        = "Kapton";
  density     = 1.42*g/cm3;
  ncomponents = 4;
  G4Material* __attribute__ ((unused))
  matKapton = new G4Material(name,density, ncomponents);
  matKapton -> AddElement(elH, fractionmass = 0.0273);
  matKapton -> AddElement(elC, fractionmass = 0.7213);
  matKapton -> AddElement(elN, fractionmass = 0.0765);
  matKapton -> AddElement(elO, fractionmass = 0.1749);
  matKapton -> GetIonisation() -> SetMeanExcitationEnergy(79.6*eV);

  // Polyethylene
  name        = "Polyethylene";
  density     = 0.94 * g/cm3;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matPolyethylene = new G4Material(name,density, ncomponents);
  matPolyethylene -> AddElement(elH, fractionmass=0.14);
  matPolyethylene -> AddElement(elC, fractionmass=0.86);

  // Polyacrylate
  name        = "Polyacrylate";
  density     = 1.19 * g/cm3;
  ncomponents = 3;
  G4Material* __attribute__ ((unused))
  matPolyacrylate = new G4Material(name,density,ncomponents);
  matPolyacrylate -> AddElement(elH, fractionmass=0.08);
  matPolyacrylate -> AddElement(elC, fractionmass=0.60);
  matPolyacrylate -> AddElement(elO, fractionmass=0.32);

  // VDC ArCO2 80/20
  name        = "ArCO2";
  density     = 0.0018*g/cm3; // to be checked
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matArCO2 = new G4Material(name,density,ncomponents);
  matArCO2->AddMaterial(matArgonGas, fractionmass = 0.8);
  matArCO2->AddMaterial(matCO2,      fractionmass = 0.2);

  // ShieldingConcrete (The receipe is modified 06/19/2009 by Jie pan)
  name        = "ShieldingConcrete";
  density     = 2.7*g/cm3;
  ncomponents = 6;
  G4Material* __attribute__ ((unused))
  matConcrete = new G4Material(name,density,ncomponents);
  matConcrete -> AddElement(elO,  fractionmass = 0.509);
  matConcrete -> AddElement(elSi, fractionmass = 0.345);
  matConcrete -> AddElement(elCa, fractionmass = 0.070);
  matConcrete -> AddElement(elH, fractionmass = 0.004);
  matConcrete -> AddElement(elFe, fractionmass = 0.038);
  matConcrete -> AddElement(elAl, fractionmass = 0.034);
  matConcrete -> GetIonisation() -> SetMeanExcitationEnergy(135.2*eV);

  // The material used in the final collimator design is Lead Antimony (~95% Lead and 5% Antimony)
  // Added June-10-09 by Jie Pan
  name        = "PBA";
  density     = 11.005 * g/cm3;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matCollimator = new G4Material(name,density,ncomponents);
  matCollimator-> AddMaterial(matPb, fractionmass = 0.955);
  matCollimator-> AddMaterial(matSb, fractionmass = 0.045);

  // Material for the collimators: High Leaded Tin Bronze
  // Copper Alloy No. C94300
  // see http://www/anchorbronze.com/c94300.html
  //name        = "CDA943";
  //density     = 9.29 * g/cm3;
  //ncomponents = 3;
  //G4Material* __attribute__ ((unused))
  //matCollimator = new G4Material(name,density,ncomponents);
  //matCollimator-> AddMaterial(matCopper, fractionmass = 0.695);
  //matCollimator-> AddMaterial(matPb    , fractionmass = 0.25);
  //matCollimator-> AddMaterial(matSn    , fractionmass = 0.055);

  // Stainless steel (Medical Physics, Vol 25, No 10, Oct 1998)
  name        = "StainlessSteel";
  density     = 8.02 * g/cm3;
  ncomponents = 5;
  G4Material* __attribute__ ((unused))
  matStainlessSteel = new G4Material(name,density,ncomponents);
  matStainlessSteel-> AddElement(elMn   , fractionmass = 0.01);
  matStainlessSteel-> AddElement(elSi   , fractionmass = 0.02);
  matStainlessSteel-> AddElement(elCr   , fractionmass = 0.19);
  matStainlessSteel-> AddElement(elNi   , fractionmass = 0.10);
  matStainlessSteel-> AddElement(elFe   , fractionmass = 0.68);

  // TRT_CH2
  name        = "CH2";
  density     = 0.935*g/cm3;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matCH2 = new G4Material(name, density, ncomponents);
  matCH2->AddElement(elC, natoms=1);
  matCH2->AddElement(elH, natoms=2);

  // Vacuum
  name        = "Vacuum";
  A           = 1.01*g/mole;
  Z           = 1.;
  density     = 1.e-25 *g/cm3;
  pressure    = 3.e-18*pascal;
  temperature = 2.73*kelvin;
  G4Material* __attribute__ ((unused))
  matVacuum = new G4Material("Vacuum", Z, A, density,kStateGas,temperature,pressure);
	
  // LeadGlass  
  // --- Added 2012/09/07 by Fang Guo
  name         = "LeadGlass";
  density      = 6.220 * g/cm3;
  ncomponents  = 5;
  G4Material* __attribute__ ((unused))
  matLeadGlass = new G4Material(name, density, ncomponents);
  matLeadGlass -> AddElement(elPb, fractionmass = 0.751938);
  matLeadGlass -> AddElement(elO , fractionmass = 0.156453);
  matLeadGlass -> AddElement(elSi, fractionmass = 0.080866);
  matLeadGlass -> AddElement(elTi, fractionmass = 0.008092);
  matLeadGlass -> AddElement(elAs, fractionmass = 0.002651);
	
  //Tungsten Alloy for WShutters
  //Added Kurtis Bartlett 02/06/2012
  //Mitech CW 68 Tungsten Alloy
  name 			= "TungstenAlloy";
  density		= 13.93 *g/cm3;
  ncomponents 	= 2;
  G4Material* __attribute__ ((unused))
  matTungstenAlloy = new G4Material(name, density, ncomponents);
  matTungstenAlloy -> AddElement(elW, fractionmass = 0.68);
  matTungstenAlloy -> AddElement(elCu , fractionmass = 0.32);

  //========================================
  // Hydrocarbones, metane and others
  //========================================

  // CH4: Metane, STP
  name        = "Methane";
  density     = 0.7174*mg/cm3 ;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matMetane = new G4Material(name,density,ncomponents);
  matMetane->AddElement(elC, natoms= 1) ;
  matMetane->AddElement(elH, natoms= 4) ;

  // C3H8: Propane, STP
  name        = "Propane";
  density     = 2.005*mg/cm3 ;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matPropane = new G4Material(name,density,ncomponents);
  matPropane->AddElement(elC, natoms= 3) ;
  matPropane->AddElement(elH, natoms= 8) ;

  // C4H10 : iso-Butane (methylpropane), STP
  name        = "IsoButane";
  density     = 2.67*mg/cm3 ;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matIsobutane = new G4Material(name,density,ncomponents);
  matIsobutane->AddElement(elC,natoms=  4) ;
  matIsobutane->AddElement(elH,natoms= 10) ;

  // C2H6 : Ethane, STP
  name        = "Ethane";
  density     = 1.356*mg/cm3 ;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matEthane = new G4Material(name,density,ncomponents);
  matEthane -> AddElement(elC, natoms= 2) ;
  matEthane -> AddElement(elH, natoms= 6) ;
  matEthane -> GetIonisation() -> SetMeanExcitationEnergy(45.4*eV);

  // Argon-Ethane40-60 by mass, STP
  name        = "Ar-C2H6_40-60";
  density     = 1.46920*mg/cm3 ;
  ncomponents = 2;
  G4Material* __attribute__ ((unused))
  matVDCGas = new G4Material(name,density,ncomponents);
  matVDCGas -> AddMaterial(matArgonGas , fractionmass = 0.40) ;
  matVDCGas -> AddMaterial(matEthane   , fractionmass = 0.60) ;


  // Print out Material Table
  //G4cout << *(G4Material::GetMaterialTable()) << G4endl;

  //============================================================================================
  //                          Optical Propeties
  //============================================================================================

  const G4int nEntries = 9;

  G4double PhotonEnergy[nEntries] =
    { 1.54986*eV,  // 800 nm 
      1.77127*eV,  // 700 nm
      2.06648*eV,  // 600 nm
      2.47978*eV,  // 500 nm
      3.09973*eV,  // 400 nm
      4.13297*eV,  // 300 nm
      4.95956*eV,  // 250 nm
      5.51063*eV,  // 225 nm
      5.90424*eV   // 210 nm
    };

//===========================
//  Optical Properties of Air
//===========================

// exact values can be taken from KamLAND code

  G4double RefractiveIndex_Air[nEntries] =
            {     1.00, // 800 nm 
	          1.00, // 700 nm
	          1.00, // 600 nm
	          1.00, // 500 nm
	          1.00, // 400 nm
	          1.00, // 300 nm
	          1.00, // 250 nm
                  1.00, // 225 nm
	          1.00  // 210 nm
	    };

  // normally air is very transparent to light in the visual spectrum,
  // but there I'm suppressing the optical tracking in air:
  // Don't show the cerenkov light leakage (detector->air)
//   G4double  AbsorptionCoeff_Air[nEntries] =
//             {     1e-3*m, // 800 nm 
// 	          1e-3*m, // 700 nm
// 	          1e-3*m, // 600 nm
// 	          1e-3*m, // 500 nm
// 	          1e-3*m, // 400 nm
// 	          1e-3*m, // 300 nm
// 	          1e-3*m, // 250 nm
//                   1e-3*m, // 225 nm
// 	          1e-3*m  // 210 nm
// 	    };
  G4double  AbsorptionCoeff_Air[nEntries] ={
    1e1*m, // 800 nm 
    1e1*m, // 700 nm
    1e1*m, // 600 nm
    1e1*m, // 500 nm
    1e1*m, // 400 nm
    1e1*m, // 300 nm
    1e1*m, // 250 nm
    1e1*m, // 225 nm
    1e1*m  // 210 nm
  };

  G4MaterialPropertiesTable* myMPT_Air = new G4MaterialPropertiesTable();
  myMPT_Air->AddProperty("RINDEX",    PhotonEnergy, RefractiveIndex_Air, nEntries);
  myMPT_Air->AddProperty("ABSLENGTH", PhotonEnergy, AbsorptionCoeff_Air, nEntries);

   matAir->SetMaterialPropertiesTable(myMPT_Air);


//=======================================
//  Optical Properties of Soda Lime Glass
//=======================================

   //*************************************************
   // could not find anything in the literature + web
   // about the optical properties of lime glass ...
   // so here we have only "educated guesses"
   //**************************************************

// values taken from KamLAND code

  G4double RefractiveIndex_LimeGlass[nEntries] =
        { 1.52, // 800 nm  
	  1.52, // 700 nm
	  1.52, // 600 nm  pretty close
	  1.52, // 500 nm
	  1.52, // 400 nm  pretty close
	  1.52, // 300 nm
	  1.52, // 250 nm
	  1.52, // 225 nm  fiction
	  1.52  // 210 nm
      };


  G4double  AbsorptionCoeff_LimeGlass[nEntries] =
        { 1.0e3*m, // 800 nm 
	  1.0e3*m, // 700 nm
	  1.0e3*m, // 600 nm
	  1.0e3*m, // 500 nm
	  1.0e3*m, // 400 nm
	  1.0e3*m, // 300 nm
	  1.0e3*m, // 250 nm
	  1.0e3*m, // 225 nm
	  1.0e3*m  // 210 nm
	};

  G4MaterialPropertiesTable* myMPT_LimeGlass = new G4MaterialPropertiesTable();
  myMPT_LimeGlass->AddProperty("RINDEX",    PhotonEnergy, RefractiveIndex_LimeGlass , nEntries);
  myMPT_LimeGlass->AddProperty("ABSLENGTH", PhotonEnergy, AbsorptionCoeff_LimeGlass , nEntries);

  matLimeGlass->SetMaterialPropertiesTable(myMPT_LimeGlass);


//====================================
//  Optical Properties of Fused Silica
//====================================

  // Fused Silica (Spectrosil 2000) for the Cerenkov Detector
  // See Elog entry #43, Software
  G4double RefractiveIndex_FusedSilica[nEntries] =
    { 1.45338,  // 800 nm 
      1.45536,  // 700 nm
      1.45810,  // 600 nm
      1.46239,  // 500 nm
      1.47018,  // 400 nm
      1.48786,  // 300 nm
      1.50751,  // 250 nm
      1.52422,  // 225 nm
      1.53842   // 210 nm
    };

  // Given by the BaBar Collaboration for the DIRC bar
  // BaBar Note #220
//   G4double AbsorptionCoeff_FusedSilica[nEntries] =
//            {1/0.0038*m,   // 800 nm pi*thumb extrapolated 
// 	    1/0.0040*m,   // 700 nm pi*thumb extrapolated
// 	    1/0.0044*m,   // 600 nm
// 	    1/0.0050*m,   // 500 nm
// 	    1/0.0076*m,   // 400 nm
// 	    1/0.0620*m,   // 300 nm
// 	    1/1.3500*m,   // 250 nm
// 	    1/8.0000*m,   // 225 nm
//             1/100.00*m    // 210 nm
// 	    };

  G4double AbsorptionCoeff_FusedSilica[nEntries] =
           { 263.16*m,   // 800 nm pi*thumb extrapolated 
	     250.00*m,   // 700 nm pi*thumb extrapolated
	     227.27*m,   // 600 nm
	     200.00*m,   // 500 nm
	     131.58*m,   // 400 nm
	      16.13*m,   // 300 nm
	       0.74*m,   // 250 nm
	       0.125*m,   // 225 nm
               0.010*m    // 210 nm
	    };

  G4MaterialPropertiesTable* myMPT_FusedSilica = new G4MaterialPropertiesTable();
  myMPT_FusedSilica->AddProperty("RINDEX",    PhotonEnergy, RefractiveIndex_FusedSilica , nEntries);
  myMPT_FusedSilica->AddProperty("ABSLENGTH", PhotonEnergy, AbsorptionCoeff_FusedSilica , nEntries);

  matQuartz->SetMaterialPropertiesTable(myMPT_FusedSilica);

  //*************************************************************************************************


//====================================
//  Optical Properties of Silicon Elastomer Glue
//====================================

  // Fused Silica (Spectrosil 2000) for the Cerenkov Detector
  // See Elog entry #43, Software
  G4double RefractiveIndex_SilElast[nEntries] =
    { 1.405,  // 800 nm 
      1.405,  // 700 nm
      1.405,  // 600 nm
      1.405,  // 500 nm
      1.405,  // 400 nm
      1.405,  // 300 nm
      1.405,  // 250 nm
      1.405,  // 225 nm
      1.405   // 210 nm
    };


  G4double AbsorptionCoeff_SilElast[nEntries] =
           { 263.16*m,   // 800 nm pi*thumb extrapolated 
	     250.00*m,   // 700 nm pi*thumb extrapolated
	     227.27*m,   // 600 nm
	     200.00*m,   // 500 nm
	     131.58*m,   // 400 nm
	      16.13*m,   // 300 nm
	       0.74*m,   // 250 nm
	       0.125*m,   // 225 nm
               0.010*m    // 210 nm
	    };

  G4MaterialPropertiesTable* myMPT_SilElast = new G4MaterialPropertiesTable();
  myMPT_SilElast->AddProperty("RINDEX",    PhotonEnergy, RefractiveIndex_SilElast , nEntries);
  myMPT_SilElast->AddProperty("ABSLENGTH", PhotonEnergy, AbsorptionCoeff_SilElast , nEntries);

  matSiElast->SetMaterialPropertiesTable(myMPT_SilElast);

  //*************************************************************************************************


  G4double reflind_Mirror[nEntries] ={ 
    1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0
  };
  G4double refrind_Mirror[nEntries] ={ 
    0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0
  };

  G4double abslength_Mirror[nEntries] ={ 
    1.0e3*m,1.0e3*m,1.0e3*m,1.0e3*m,1.0e3*m,1.0e3*m,1.0e3*m,1.0e3*m,1.0e3*m
  };

  G4MaterialPropertiesTable* myMPT_Mirror = new G4MaterialPropertiesTable();
  myMPT_Mirror->AddProperty("REFLECTIVITY", PhotonEnergy, reflind_Mirror, nEntries);
  myMPT_Mirror->AddProperty("RINDEX",    PhotonEnergy, refrind_Mirror, nEntries);
  myMPT_Mirror->AddProperty("ABSLENGTH", PhotonEnergy, abslength_Mirror, nEntries);

  matMirror->SetMaterialPropertiesTable(myMPT_Mirror);

//   G4double reflind_Photocathode[nEntries] ={ 
//     1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0
//   };
//   G4double refrind_Photocathode[nEntries] ={ 
//     1.52,1.52,1.52,1.52,1.52,1.52,1.52,1.52,1.52
//   };

//   G4double abslength_Photocathode[nEntries] ={ 
//     1.0e-3*m,1.0e-3*m,1.0e-3*m,1.0e-3*m,1.0e-3*m,1.0e-3*m,1.0e-3*m,1.0e-3*m,1.0e-3*m
//   };

//   G4MaterialPropertiesTable* myMPT_Photocathode = new G4MaterialPropertiesTable();
// //   myMPT_Photocathode->AddProperty("REFLECTIVITY", PhotonEnergy, reflind_Photocathode, nEntries);
//   myMPT_Photocathode->AddProperty("RINDEX",    PhotonEnergy, refrind_Photocathode, nEntries);
//   myMPT_Photocathode->AddProperty("ABSLENGTH", PhotonEnergy, abslength_Photocathode, nEntries);

//   matPhotocathode->SetMaterialPropertiesTable(myMPT_Photocathode);

  G4cout << G4endl << "###### Leaving QweakSimMaterial::DefineMaterials() " << G4endl << G4endl;

}
