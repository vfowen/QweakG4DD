//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimEPEvent.cc

   \author Jie Pan

*/
//=============================================================================

#include "QweakSimEPEvent.hh"

// geant4 includes
#include "Randomize.hh"

// user includes
#include "QweakSimEPEventMessenger.hh"
#include "QweakSimUserInformation.hh"

#include "wiser_pion.h"
#include "Alinel_crsec_gen.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

   const G4double QweakSimEPEvent::M_n = 939.5656*MeV; //neutron mass in MeV/c^2
   const G4double QweakSimEPEvent::M_p = 938.2796*MeV;  // proton mass in MeV/c^2

   const G4double QweakSimEPEvent::Theta_Min = 1.745329E-4;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimEPEvent::QweakSimEPEvent( QweakSimUserInformation* myUI)
: fLookupTable(0)
{
  G4cout << "###### Calling QweakSimEPEvent::QweakSimEPEvent () " << G4endl;

  Isotropy = 1;
  
  //SetPhiAngle_Min(-16.0*degree);
  //SetPhiAngle_Max(16.0*degree);

  //SetThetaAngle_Min(4.0*degree);
  //SetThetaAngle_Max(13.5*degree);

  //SetEPrime_Max(1.159*GeV);
  //SetEPrime_Min(0.059*GeV);
  
  //SetBeamEnergy(1.16*GeV);

  ElasticPeakDeltaE = 15*MeV;

  TypeSetting = 1;
  ReactionType = 1;
  ReactionRegion = 1;
  kActiveOctantNumber = 0;  //default octant all, choose from [0,8]

  myUserInfo = myUI;
  myUserInfo->SetEPEvent(this);

  EventGen_Messenger = new QweakSimEPEventMessenger(this);

  G4cout << "###### Leaving QweakSimEPEvent::QweakSimEPEvent () " << G4endl;
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimEPEvent::~QweakSimEPEvent()
{

  G4cout << "###### Calling QweakSimEPEvent::~QweakSimEPEvent () " << G4endl;

  if( EventGen_Messenger) delete EventGen_Messenger;

  G4cout << "Created a great many events: " << myUserInfo->GetNumberOfEventToBeProcessed() << G4endl;

  G4cout << "###### Leaving QweakSimEPEvent::~QweakSimEPEvent () " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double QweakSimEPEvent::GetVertexZ()
{
  /** \page reaction_region reaction region
   * There are a number of pre-set reaction regions.  These do not automatically set the
   * reaction type, so don't expect aluminum exit window simulations by setting reaction
   * region to 3...
   * \li 1: LH2 Target
   * \li 2: front entrance window
   * \li 3: back exit window
   * \li 4: Dummy Target (1% US Al)
   * \li 5: Dummy Target (2% US Al)
   * \li 6: Dummy Target (4% US Al)
   * \li 7: Dummy Target (2% DS Al)
   * \li 8: Dummy Target (4% DS Al)
   * \li 9: Dummy Target (8% DS Al)
   * \li 10: Dummy Target (US Carbon)
   * \li 11: Dummy Target (DS Carbon)
   * \li else: target
   */

  if (ReactionRegion == 1) // target
    myPositionZ =  myUserInfo->TargetCenterPositionZ + (G4UniformRand()-0.5)*(myUserInfo->TargetLength);

  else if (ReactionRegion == 2) // front entrance window
    myPositionZ =  myUserInfo->TargetCenterPositionZ - 0.5*(myUserInfo->TargetLength)
                   - (myUserInfo->TargetEntranceWindowThickness)*G4UniformRand();

  else if(ReactionRegion == 3) // back exit window
    myPositionZ =  myUserInfo->TargetCenterPositionZ + 0.5*(myUserInfo->TargetLength)
                   + (myUserInfo->TargetExitWindowNippleThickness)*G4UniformRand();

  else if(ReactionType == 7 && (ReactionRegion == 4 || ReactionRegion == 5 || ReactionRegion == 6 || ReactionRegion == 10)) // Generator 7 US Dummy Targets
    myPositionZ =  myUserInfo->TargetCenterPositionZ + myUserInfo->TargetUSDummyPositionOffsetZ;

  else if(ReactionType == 7 && (ReactionRegion == 7 || ReactionRegion == 8 || ReactionRegion == 9 || ReactionRegion == 11)) // Generator 7 DS Dummy Targets
    myPositionZ =  myUserInfo->TargetCenterPositionZ + myUserInfo->TargetDSDummyPositionOffsetZ;

  else if(ReactionRegion == 4 || ReactionRegion == 5 || ReactionRegion == 6 || ReactionRegion == 10) // Al US Dummy Targets
    myPositionZ =  myUserInfo->TargetCenterPositionZ - 0.5*(myUserInfo->TargetLength)
                   - (myUserInfo->TargetEntranceWindowThickness)*G4UniformRand();

  else if(ReactionRegion == 7 || ReactionRegion == 8 || ReactionRegion == 9 || ReactionRegion == 11) // Al DS Dummy Targets
    myPositionZ =  myUserInfo->TargetCenterPositionZ + 0.5*(myUserInfo->TargetLength)
                   + (myUserInfo->TargetExitWindowNippleThickness)*G4UniformRand();

  else
    myPositionZ =  myUserInfo->TargetCenterPositionZ + (G4UniformRand()-0.5)*(myUserInfo->TargetLength); //default region

  return myPositionZ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreeVector QweakSimEPEvent::GetMomentumDirection()
{

    // Generate flat phi distribution
  G4double PhiAngle =  GetPhiAngle_Min() + G4UniformRand()*(GetPhiAngle_Max() - GetPhiAngle_Min());
    // If active octant = 0, all octants are used
    if (kActiveOctantNumber == 0) PhiAngle += (G4RandFlat::shootInt(8) * 45.0 * degree);
    G4double cosPhi = cos(PhiAngle);
    G4double sinPhi = sin(PhiAngle);


    /** \page isotropy isotropy
     * The cross section used for weighting Monte Carlo events depends on how those
     * events are thrown.  There are two options in the Qweak Monte Carlo:
     * \li isotropy = 0: flat theta distribution, requires a modified weight for the cross section -> QweakSimUserPrimaryEvent::CrossSectionWeight
     * \li isotropy = 1: uniform spherical theta/phi distribution, use regular cross section -> QweakSimUserPrimaryEvent::CrossSection
     * \li else: not defined
     */

    G4double cosTheta   = 1.0;
    G4double sinTheta   = 0.0;
    G4double ThetaAngle = 0.0;
    G4double E_out      = 0.0;
    //G4double xsec       = 0.0;
    //G4int SuperElastic  = 1;

    //while (SuperElastic) {
      if (Isotropy == 0) {
        // Generate flat theta distribution
        ThetaAngle = GetThetaAngle_Min() + G4UniformRand()*(GetThetaAngle_Max() - GetThetaAngle_Min());
        cosTheta = cos(ThetaAngle);
        sinTheta = sin(ThetaAngle);

      } else if (Isotropy == 1) {
        // Generate uniform distribution on spherical surface. See for example
        // http://hypernews.slac.stanford.edu/HyperNews/geant4/get/particles/31/2.html
        // or more generally http://mathworld.wolfram.com/SpherePointPicking.html
        G4double cosThetaMax = cos(GetThetaAngle_Max());
        G4double cosThetaMin = cos(GetThetaAngle_Min());
        cosTheta = cosThetaMin + G4UniformRand()*(cosThetaMax - cosThetaMin);
        sinTheta = sqrt(1. - cosTheta * cosTheta);
        ThetaAngle = acos(cosTheta);

      } else {
        G4cerr << "Warning: unkown isotropy type.  Pick 0 or 1." << G4endl;
      }
      E_out = (G4UniformRand()*(GetEPrime_Max()-GetEPrime_Min()) + GetEPrime_Min());
      //SuperElastic = SuperElasticCheck(myUserInfo->GetBeamEnergy(), E_out, ThetaAngle, xsec);
      //}
    myUserInfo->SetEPrime(E_out);

    G4double ux = sinTheta * cosPhi;
    G4double uy = sinTheta * sinPhi;
    G4double uz = cosTheta;
    G4ThreeVector myNormMomentum(ux,uy,uz);
       
    // Rotate the momentum to the active octant (if octant = 0 all octants are used)
    if (kActiveOctantNumber > 8 )
    {
    	myNormMomentum.rotateZ( (kActiveOctantNumber-9 +4*G4RandFlat::shootInt(2))*45.0*degree);
    }else if (kActiveOctantNumber > 0){
      myNormMomentum.rotateZ( (kActiveOctantNumber-1)*45.0*degree);
    }

    return myNormMomentum; 
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimEPEvent::GetanEvent(G4double E_in,
                                 std::vector< G4double > &fCrossSection, 
                                 G4double &fWeightN,
                                 G4double &Q2,
                                 G4double &E_out,
                                 G4ThreeVector &OutgoingMomentumDirection,
                                 G4double &theta,
                                 G4double &phi,
				 G4double &Asymmetry)
{
  // incoming momentum
  G4ThreeVector IncomingMomentumDirection;
  if( myUserInfo->GetFixedPosMom() ){
    IncomingMomentumDirection = myUserInfo->GetNormMomentum(0);
  }else{
    IncomingMomentumDirection = myUserInfo->GetNormMomentum(myUserInfo->GetPrimaryEventNumber());
  }
    
    G4double IncomingMomentumDirectionMag = IncomingMomentumDirection.mag();

    
    // outgoing momentum
    OutgoingMomentumDirection = GetMomentumDirection();
    theta = OutgoingMomentumDirection.theta()/degree;
    phi = OutgoingMomentumDirection.phi()/degree;
    
    // relative theta angle
    
    G4double dot = OutgoingMomentumDirection.dot(IncomingMomentumDirection);
    
    G4double RelativeThetaAngle = acos(dot/IncomingMomentumDirectionMag);    


   if(ReactionType==0 || TypeSetting==0) // combination of all process, Random int [1,8]
      {
	TypeSetting = 0;
        ReactionType = G4int(G4UniformRand()*7.0+1.0+0.5);
      }
   else
      {
        TypeSetting = ReactionType;
      }

   //std::cout<<"ReactionType: "<<ReactionType<<", TypeSetting: "<<TypeSetting<<std::endl;

   /** \page reaction_type reaction type
    * There are a number of reaction types implemented in the Qweak Monte Carlo:
    * \li 0: random selection of some of these reaction types
    * \li 1: elastic scattering from hydrogen (see QweakSimEPEvent::Elastic_Cross_Section_Proton)
    * \li 2: elastic scattering from aluminum (see QweakSimEPEvent::Elastic_Cross_Section_Aluminum)
    * \li 3: quasi-elastic scattering from proton in aluminum (see QweakSimEPEvent::Elastic_Cross_Section_Proton)
    * \li 4: quasi-elastic scattering from neutron in aluminum (see QweakSimEPEvent::Quasi_Elastic_Neutron)
    * \li 5: Delta resonance (see QweakSimEPEvent::Delta_Resonance)
    * \li 6: Moller scattering (see QweakSimEPEvent::Moller_Scattering)
    * \li 7: Radiative Scattering (see QweakSimEPEvent::Radiative_Cross_Section_Proton)
    * \li 8: Quasielastic scattering from aluminum using the Bosted fit
    * \li 88: Pion photoprodcution
    * \li 9: Aluminum Nuclear inelastic Single Particle States
    * \li 10: Aluminum GDR
    * \li 11: Aluminum Nuclear Radiated Inelastic from Bosted fit
    * \li 12: Zn scattering approximation
    * \li 13: Mg scattering approximation
    * \li 14: Cu scattering approximation
    * \li 15: Cr scattering approximation
    * \li 16: Fe scattering approximation
    * \li 17: Si scattering approximation
    */

   if(ReactionType==1) //LH2 target
      {
       A = 1.0;
       Z = 1.0;
       Mass = Z*M_p+(A-Z)*M_n;
       fCrossSection[0] = Elastic_Cross_Section_Proton(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EP(RelativeThetaAngle, E_in);
      }
      
   else if(ReactionType==2) // Aluminum window
      {
       A = 27.0;
       Z = 13.0;
       Mass = Z*M_p+(A-Z)*M_n;
       fCrossSection[0] = Elastic_Cross_Section_Aluminum(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_AL(RelativeThetaAngle, E_in);
      }

   else if(ReactionType==3) // Aluminum window quasi-elastic proton (assume free proton)
      {
       A = 1.0;
       Z = 1.0;   
       Mass = M_p;    
       fCrossSection[0] = Elastic_Cross_Section_Proton(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EP(RelativeThetaAngle, E_in);
      }

   else if(ReactionType==4) // Aluminum window quasi-elastic neutron (assume free neutron)
      {
       A = 1.0;
       Z = 1.0;   // Z needs to be set to 1 for neutron quasi elastic scattering
       Mass = M_n;    
       fCrossSection[0] = Quasi_Elastic_Neutron(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EN(RelativeThetaAngle, E_in);
      }

   else if(ReactionType==5) // Delta resonances
      {
       fCrossSection[0] = Delta_Resonance(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       //std::cout<<E_in<<" "<<ThetaAngle/degree<<" "<<fWeightN<<" "<<Q2<<" "<<E_out<<std::endl;
       Asymmetry = GetAsymmetry_Pi(Q2);
      }
   else if(ReactionType==6) // Moller scattering
      {
	//  Peiqing, Dec 12, 2011
	//  Small angle recoil electrons are directly dumped for now.
       G4double E_recoil;
       G4double ThetaRecoil;
       fCrossSection[0] = Moller_Scattering(E_in, RelativeThetaAngle, E_out, 
					 E_recoil, ThetaRecoil, 
                                         Q2, fWeightN, Asymmetry);
      }      
   else if(ReactionType==7) // Radiative Cross Section Lookup Table
      {
       fCrossSection = Radiative_Cross_Section_Lookup(myUserInfo->GetBeamEnergy(), RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EP(RelativeThetaAngle, E_in);
      }
   else if(ReactionType==8) // Quasielastic Bosted - Aluminum
      {
         Z = 13;
         A = 27;
         fCrossSection[0] = Quasi_Elastic_Bosted(E_in, RelativeThetaAngle, Z, A, fWeightN, Q2, E_out);
      }	
   else if(ReactionType==88) //--- LH2 target, pion photo-production cross section 3.35 GeV
     {
       fCrossSection[0] = Pion_PhotoProduction(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
       Asymmetry = GetAsymmetry_EP(RelativeThetaAngle, E_in); //--- use the elastic asymmetry for now
     }
   else if(ReactionType==9) // Nuclear Inelastics Single Particle States - Aluminum
     {
       fCrossSection[0] = AlNuclInel(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
     }
   else if(ReactionType==10) // GDR - Aluminum
     {
       fCrossSection[0] = AlGDR(E_in, RelativeThetaAngle, fWeightN, Q2, E_out);
     }
   else if(ReactionType==11) // Nuclear Inelastic Bosted - Aluminum
     {
       Z = 13;
       A = 27;
       fCrossSection[0] = NuclearInelastic_Bosted(E_in, RelativeThetaAngle, Z, A, fWeightN, Q2, E_out);
     }
   else if(ReactionType==12) // Alloy: Zinc elastic scattering approximation
     {
       Z = 30;
       A = 64;
       fCrossSection[0] = AlloyScattering(E_in, RelativeThetaAngle, Z, A, fWeightN, Q2, E_out);
     }
   else if(ReactionType==13) // Alloy: Magnesium elastic scattering approximation
     {
       Z = 12;
       A = 24;
       fCrossSection[0] = AlloyScattering(E_in, RelativeThetaAngle, Z, A, fWeightN, Q2, E_out);
     }
   else if(ReactionType==14) // Alloy: Copper elastic scattering approximation
     {
       Z = 29;
       A = 65;
       fCrossSection[0] = AlloyScattering(E_in, RelativeThetaAngle, Z, A, fWeightN, Q2, E_out);
     }
   else if(ReactionType==15) // Alloy: Chromium elastic scattering approximation
     {
       Z = 24;
       A = 52;
       fCrossSection[0] = AlloyScattering(E_in, RelativeThetaAngle, Z, A, fWeightN, Q2, E_out);
     }
   else if(ReactionType==16) // Alloy: Iron elastic scattering approximation
     {
       Z = 26;
       A = 56;
       fCrossSection[0] = AlloyScattering(E_in, RelativeThetaAngle, Z, A, fWeightN, Q2, E_out);
     }
   else if(ReactionType==17) // Alloy: Silicon elastic scattering approximation
     {
       Z = 14;
       A = 28;
       fCrossSection[0] = AlloyScattering(E_in, RelativeThetaAngle, Z, A, fWeightN, Q2, E_out);
     }

   if      (ReactionRegion == 1)  SetLuminosity(myUserInfo->TargetLuminosityLH2);
   else if (ReactionRegion == 2)  SetLuminosity(myUserInfo->TargetLuminosityUSALWindow);
   else if (ReactionRegion == 3)  SetLuminosity(myUserInfo->TargetLuminosityDSALWindow);
   else if (ReactionRegion == 4)  SetLuminosity(myUserInfo->TargetLuminosityUSALDummy1);
   else if (ReactionRegion == 5)  SetLuminosity(myUserInfo->TargetLuminosityUSALDummy2);
   else if (ReactionRegion == 6)  SetLuminosity(myUserInfo->TargetLuminosityUSALDummy4);
   else if (ReactionRegion == 7)  SetLuminosity(myUserInfo->TargetLuminosityDSALDummy2);
   else if (ReactionRegion == 8)  SetLuminosity(myUserInfo->TargetLuminosityDSALDummy4);
   else if (ReactionRegion == 9)  SetLuminosity(myUserInfo->TargetLuminosityDSALDummy8);
   else if (ReactionRegion == 10) SetLuminosity(myUserInfo->TargetLuminosityUSCDummy);
   else if (ReactionRegion == 11) SetLuminosity(myUserInfo->TargetLuminosityDSCDummy);
   else                           SetLuminosity(myUserInfo->TargetLuminosityLH2);

   //G4double phase_space = (GetPhiAngle_Max()-GetPhiAngle_Min())*(cos(GetThetaAngle_Min())-cos(GetThetaAngle_Max()));  // units [Sr]

   G4double phase_space = (GetPhiAngle_Max()-GetPhiAngle_Min());

   if      (GetIsotropy() == 0) phase_space *= (GetThetaAngle_Max()-GetThetaAngle_Min());// * sin(RelativeThetaAngle);
   else if (GetIsotropy() == 1) phase_space *= (cos(GetThetaAngle_Min())-cos(GetThetaAngle_Max()));
   else                         phase_space *= (cos(GetThetaAngle_Min())-cos(GetThetaAngle_Max()));

   // For ReactionTypes that are differential in E'
   if (ReactionType == 7 || ReactionType == 88) phase_space *= (GetEPrime_Max()-GetEPrime_Min())/1000.0;  // units [Sr*GeV]
   // Delta_Resonance (reac 5) and Quasi_Elastic_Bosted (reac 8) are also
   // differential in Eprime, but the xsect returned by these functions 
   // already includes the additional phase space factor. - K.Mesick 13/May/14


   //  If events are being thrown in all octants, this increases the phase space accordingly
   if (!GetActiveOctantNumber()) phase_space *= 8.0; 


   SetPhaseSpace(phase_space);

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// jpan@nuclear.uwinnipeg.ca
//     calculate proton cross sections using the dipole fits to the form factors.
//     Angles are restricted to be greater than .01 deg to avoid
//     division by 0 when evaluating the Mott cross section.

G4double QweakSimEPEvent::Elastic_Cross_Section_Proton(G4double E_in,
                                                       G4double Theta,
                                                       G4double &fWeightN,
                                                       G4double &Q2,
                                                       G4double &E_out)
{
      G4double Lamda_2 = 0.710;
      G4double M_p = 938.2796;  // proton mass in MeV
      G4double mu = 2.793;
      G4double Z = 1.0;
      G4double A = 1.0;
      G4double M = M_p*A;
      G4double hbarc = 197.3269718;  // in MeV fm 
      G4double alpha = 1.0/137.035999074;
      G4double CC = hbarc*alpha/2.0;  // 0.719982242379

//    E_in units is MeV

      const G4double theta_min = 0.01 * degree;
      if (Theta < theta_min) {
	Theta = theta_min;
	G4cout << "Warning: Elastic_Cross_Section_Proton: theta less than " << theta_min << G4endl;
        G4cout << "Warning: Elastic_Cross_Section_Proton: theta was set to " << theta_min << G4endl;
      }

      G4double CTH = cos(Theta/2.);
      G4double STH = sin(Theta/2.);
      G4double T2THE = STH*STH/CTH/CTH;
      G4double ETA = 1.0+2.0*E_in*STH*STH/M;
      E_out = E_in/ETA;
      Q2 = 4.0*E_in*E_out*STH*STH;   // MeV^2
      G4double tau = Q2/4.0/M/M;
//    Mott scatering cross-section, including recoil correction
      G4double CrossSection = (Z*CC/E_in*CTH/STH/STH)*(Z*CC/E_in*CTH/STH/STH)/ETA;
//    Units: ub/sr
      G4double Mott = CrossSection*10000.0;
//    Cross section
      G4double GEP_DIPOLE = 1.0/(1.0+Q2/1.E6/Lamda_2)/(1.0+Q2/1.E6/Lamda_2);
      G4double GMP_DIPOLE = GEP_DIPOLE*mu;
      G4double FAC = 1.0/(1.0+tau);

      G4double Sigma_Dipole = Mott*(GEP_DIPOLE*GEP_DIPOLE*FAC+tau*GMP_DIPOLE*GMP_DIPOLE*(FAC+2.*T2THE));
      fWeightN = Sigma_Dipole*sin(Theta);
      return Sigma_Dipole;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// jpan@nuclear.uwinnipeg.ca
//     calculate Aluminum elastic cross sections

G4double QweakSimEPEvent::Elastic_Cross_Section_Aluminum(G4double E_in,
                                                         G4double Theta,
                                                         G4double &fWeightN,
                                                         G4double &Q2,
                                                         G4double &E_out)
{
      G4double Theta_Min = 1.745329E-4;
      G4double M_p = 938.2796;  // proton mass in MeV
      G4double Z = 13.0;
      G4double A = 27.0;
      G4double M = M_p*A;

//    harmonic oscillator well parameter a0 ~1.76 fm 
      G4double a = 2.98; //unit: fm
      G4double ap = sqrt(0.427);   //unit: fm 
      G4double a0 = sqrt((a*a-1.5*ap*ap)/(3.5-10/Z-1.5/A)); 

      G4double Q = 14.6;  //unit fm^(-2)
//    G4double J = 5.0/2.0;

//    G4double gamma = 2.792847351; //This is the magnetic moment
//    G4double Omega = -3/2*(1+2*gamma)*a0*a0; 
//    G4double Gamma = 15/4*gamma*pow(a0,4);
//    G4double mu = 3.69;  // This is NOT the magnetic moment
//    G4double Omega_mu = -6.36; // Omega/mu 
//    G4double Gamma_mu = 20.7;  // Gamma/mu

      if (Theta<Theta_Min)
           Theta = Theta_Min;

//    E_in unit is MeV, q2 unit is fm^(-2)   
      G4double CTH = cos(Theta/2.0);
      G4double STH = sin(Theta/2.0);
//    G4double T2THE = STH*STH/CTH/CTH;
      G4double ETA = 1.0+2.0*E_in*STH*STH/M;
      E_out = E_in/ETA;
   
      Q2 = 4*E_in*E_out*STH*STH;     //unit: MeV^2
      G4double q2 = Q2/1000000*(1.0/0.197)*(1.0/0.197);  //convert MeV^2 into fm^(-2)
      G4double x = (1.0/4.0)*q2*a0*a0;

//  std::ofstream EventDataFile("Event.dat", std::ios::app);
//  EventDataFile<<"E_f="<<E_f<<"  q2="<<q2<<"  "<<"x="<<x<<G4endl;

//    Electric form factor (data fit)
      G4double F0 = (1.0/Z)*( Z-4.0/3.0*(Z-5.0)*x+4.0/15.0*(Z-8.0)*x*x)*exp(-x);
      G4double F2 = (1.0-2.0/7.0*x)*exp(-x);
      G4double Fe = sqrt( F0*F0+(7.0/450.0)*q2*q2*(Q*Q/Z/Z)*F2*F2 );
      Fe=Fe*exp(-0.25*q2*ap*ap); //correction for finite proton size
      Fe=Fe*exp(x/A); //correction for center-of-well motion
      G4double Fe_2 = pow(Fe,2);


//  EventDataFile<<"F0="<<F0<<"  "<<"F2="<<F2<<"  "<<"Fe_2="<<Fe_2<<G4endl;

//    Magnetic form factor (theoretical)
//    G4double Fm1 = (1.0-2.0/5.0*(1.0+2.0*gamma)/(1.0+gamma/2.0)*x+6.0/35.0*gamma*x*x/(1.0+gamma/2.0))*exp(-x);
//    G4double Fm3 = (1.0-2.0/3.0*gamma*x/(1.0+2.0*gamma))*exp(-x);
//    G4double Fm5 = exp(-x);
//    G4double Fm_2 = Fm1*Fm1+(4.0/525.0)*pow(q2*Omega_mu*Fm3,2)+(2.0/33075.0)*pow(q2,4)*pow(Gamma_mu*Fm5,2);

//  EventDataFile<<"Fm1="<<Fm1<<"  "<<"Fm3="<<Fm3<<"  "<<"Fm5="<<Fm5<<"  "<<"Fm_2="<<Fm_2<<G4endl;

//    form factor square
//      G4double F_2 = Z*Z*Fe_2+(1.0+2.0*T2THE)*mu*mu/3.0*(J+1.0)/J*q2/4.0/pow((M_p/0.197),2)*Fm_2;
      G4double F_2 = Fe_2;//+(1.0+2.0*T2THE)*mu*mu/3.0*(J+1.0)/J*q2/4.0/pow((M_p/0.197),2)*Fm_2;

//  EventDataFile<<"F_2="<<F_2<<"  "<<G4endl;

//    cross section units: ub/sr
//    G4double SigmaMott = ((0.72/E_in)*cos(Theta/2)/(sin(Theta/2)^2))^2 /( 1+2*E_in/M*(sin(Theta/2)^2))*10000 ;
      G4double SigmaMott = pow(((0.72/E_in)*CTH/(STH*STH)),2)/(1+2*E_in/M*STH*STH)*10000 ;
      SigmaMott *= (Z*Z);

//  EventDataFile<<"SigmaMott="<<SigmaMott<<"  "<<"SigmaMott*F_2="<<SigmaMott*F_2<<"  "<<"weight_n="<<SigmaMott*F_2*sin(Theta)<<G4endl;

      G4double Xsect = SigmaMott*F_2;
      fWeightN = Xsect*sin(Theta);

      //      G4cout<< "q(1/fm)"<<sqrt(q2) <<"  SigmaMott="<<SigmaMott<<"  F_2="<<F_2<<"  SigmaMott*F_2="<<Xsect<<G4endl;
      return Xsect;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//jpan@nuclear.uwinnipeg.ca Sat Apr 18 11:28:18 CDT 2009
//     In this subroutine units are MeV

G4double QweakSimEPEvent::Quasi_Elastic_Neutron(G4double E_in,
                                                G4double Theta,
                                                G4double &fWeightN,
                                                G4double &Q2,
                                                G4double &E_out)
{
//  cout<<"===>>>>Calling Quasi_Elastic_Neutron"<<endl;
      G4double Theta_Min = 1.745329E-4;
      G4double Lamda_2 = 0.710;
      G4double M_p = 938.2796;  // proton mass in MeV
//      G4double mu = 2.793;
      G4double mu_n = -1.91;
      G4double Z = 1.0;
//      G4double A = 1.0;
      G4double M = M_p;

//    E_in units is MeV
      
      if (Theta<Theta_Min)
         Theta = Theta_Min;

      G4double CTH = cos(Theta/2.0);
      G4double STH = sin(Theta/2.0);
      G4double T2THE = STH*STH/CTH/CTH;
      G4double ETA = 1.0+2.0*E_in*STH*STH/M;
      E_out = E_in/ETA;
//    MeV^2
      Q2 = 4.*E_in*E_out*STH*STH;
      G4double tau = Q2/4./M/M;
//    Mott scatering
      G4double CrossSection = (Z*0.72/E_in*CTH/STH/STH)*(Z*0.72/E_in*CTH/STH/STH)/ETA;
//    Units: ub/sr
      G4double Mott = CrossSection*10000.0;

//    Cross section
      G4double GEP_DIPOLE = 1.0/(1.0+Q2/1.E6/Lamda_2)*(1.0+Q2/1.E6/Lamda_2);
//      G4double GMP_DIPOLE = GEP_DIPOLE*mu;
      G4double GEn_DIPOLE = 0.0;
      G4double GMn_DIPOLE = GEP_DIPOLE*mu_n;
      G4double FAC = 1.0/(1.0+tau);

//      G4double Sigma_Dipole_p = Mott*(GEP_DIPOLE*GEP_DIPOLE*FAC+tau*GMP_DIPOLE*GMP_DIPOLE*(FAC+2.*T2THE));
      G4double Sigma_Dipole_n = Mott*(GEn_DIPOLE*GEn_DIPOLE*FAC+tau*GMn_DIPOLE*GMn_DIPOLE*(FAC+2.*T2THE));
//      G4double Sigma_Dipole = Z*Sigma_Dipole_p + (A-Z)*Sigma_Dipole_n;

//  cout<<"===>>>>leaving Quasi_Elastic_Neutron"<<endl;
      fWeightN = Sigma_Dipole_n*sin(Theta);
      return Sigma_Dipole_n;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Inelastic generator interface
// Peiqing, Nov 30,2011

G4double QweakSimEPEvent::Delta_Resonance(G4double E_in,
                                          G4double Theta,
                                          G4double &fWeightN,
                                          G4double &Q2,
                                          G4double &E_out)
{
  G4double E_beam = myUserInfo->GetBeamEnergy();    // maximum energy (beam energy) in MeV
  G4double M_electron = 0.511;  // minimum energy (electron mass) in MeV
  
  // G4double Theta_Min = 1.745329E-4;
  if (Theta<Theta_Min)
      Theta = Theta_Min;

  // Generate flat energy distribution of outgoing electron
  E_out =  M_electron + G4UniformRand()*(E_beam - M_electron);
  
  // TODO: total energy phase space should be reduced to improve the efficiency.
  G4double xsect = Sigma_EEPrime(E_in/1000.0, E_out/1000.0, Theta, Q2);  // ub/sr/GeV
  Q2 = Q2*1e6;  // convert to MeV^2 for Q2

  //std::cout<<"Q2="<<Q2<<" xsect="<<xsect<<std::endl;
  xsect = xsect*(E_beam - M_electron)/1000.0;
  //std::cout<<"xsect*1.165 = "<<xsect<<std::endl;
  fWeightN = xsect*sin(Theta);
 
  if(xsect == 0)  // if E > E_max, reject the event
  {
     E_out = M_electron;
     Q2 = 0.0;
  }
  
  return xsect;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double QweakSimEPEvent::Sigma_EEPrime(G4double eni, G4double eprime, G4double theta, G4double &q2)
{

// Peiqing, Nov 28, 2011
// This is adopted from QWGEANT3 SUBROUTINE SIGMA_EEPRIME (ENI,EPRIME,THETA,WVAL,SIGMA_EEP)
// 
//	Calculates the differential cross section for inelastic
//	ep scattering into unit solid angle and scattered
//	electron energy EPRIME.  The cross section is
//	returned in microbarns/sr/GeV.

      G4double w2,xval1[51],xvalL[51];
      G4double sigT,sigL,epsilon;
      G4int i;

      G4double t2,epmax,xneu,gamma;
 
      G4double mp = 0.9382727;
      G4double mp2 = mp*mp;   
      G4double pi = 3.141593;
      G4double alpha = 1.0/137.036;
      G4double mpion = 0.135;
    
      G4double xval[101]={ 0,
       0.12286E+01,0.15200E+01,0.15053E+01,0.16960E+01,0.16466E+01,
       0.14055E+01,0.12247E+00,0.22000E+00,0.84591E-01,0.90400E-01,
       0.16956E+00,0.29002E+00,0.74046E+01,0.65122E+01,0.58506E+01,
       0.16990E+01,0.45729E+01,0.53546E+03,-.97628E+03,0.82539E+05,
       0.29494E+01,0.20352E+01,0.12422E+00,0.19560E+01,0.22333E+01,
       -.32484E+00,0.24212E+00,0.57737E-01,0.30497E+01,0.63111E+01,
       0.37579E+00,0.41100E+01,0.20668E-01,0.45490E+03,0.54493E-01,
       0.22565E+01,0.40369E+01,0.43734E+00,0.65625E+00,0.36182E+00,
       0.55216E-01,0.41789E+00,0.18104E+00,0.91306E+00,0.18116E+01,
       0.24152E+03,0.19329E+01,0.38000E+00,0.28732E+01,-.53116E+00,
       0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,
       0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,
       0.00000E+00,0.00000E+00,0.99495E+01,0.70370E-02,0.16172E+01,
       0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,
       0.20782E+05,0.79523E+04,0.54933E+00,0.00000E+00,0.68629E+01,
       0.10369E+01,0.88112E+00,0.00000E+00,0.35659E+03,0.20281E-02,
       0.40336E+02,0.00000E+00,0.45242E+00,0.20000E-01,0.28691E+00,
       0.00000E+00,0.25115E+03,0.10663E+01,0.55422E+01,0.30350E+00,
       0.10541E+01,0.20527E+01,0.00000E+00,0.00000E+00,0.13055E+02,
       0.27997E+01,0.39546E+00,0.46372E+00,0.49972E+01,0.00000E+00};

// Check that we are not above maximum allowed E assuming threshold W=Mp+Mpi
      t2 = theta/2.0;
      G4double sin_t2 = sin(t2);
      G4double tan_t2 = tan(t2);
      G4double sin2_t2 = sin_t2*sin_t2;
      G4double tan2_t2 = tan_t2*tan_t2;
      G4double sigma_eep = 0.0;
      epmax = eni-mpion*(1.0+0.5*mpion/mp);
      epmax = epmax/(1.0+(2.0*eni/mp)*sin2_t2);
      if (eprime>=epmax) 
        return 0; 

// Calculate Q**2, W**2, epsilon, gamma
      q2 = 4.0*eni*eprime*sin2_t2;
      xneu = eni-eprime;
      w2 = mp2 + 2.0*mp*xneu - q2;
      epsilon = 1.0/(1.0+2.0*(1.0+xneu*xneu/q2)*tan2_t2);
      gamma = alpha*eprime*(w2-mp2)/((2.0*pi)*(2.0*pi));
      gamma = gamma/(q2*mp*eni*(1.0-epsilon));
      // wval = sqrt(w2);
      
      for (i=1;i<=50;i++)
      {
        xval1[i] = xval[i];
        xvalL[i] = xval[50+i];
        if(i<=12) 
	  xvalL[i] = xval1[i];
      }
      
      xvalL[43] = xval1[47];
      xvalL[44] = xval1[48];
      xvalL[50] = xval1[50];
 
      sigT = ResMod507(1,w2,q2,&xval1[0]);
      sigL = ResMod507(2,w2,q2,&xvalL[0]);
      sigma_eep=sigT+epsilon*sigL;
      sigma_eep=sigma_eep*gamma;

      return sigma_eep;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4double QweakSimEPEvent::ResMod507(G4int sf, G4double w2, G4double q2, G4double* xval)
{
      G4double xb,mass[8],width[8];
      G4double height[8],rescoef[7][5];
      G4double nr_coef[4][5],sigr[8],sig_nr;
      G4double intwidth[8],k,kcm,kr[8],kcmr[8],ppicm,ppi2cm;
      G4double petacm,ppicmr[8],ppi2cmr[8],petacmr[8],epicmr[8],epi2cmr[8];
      G4double eetacmr[8],epicm,epi2cm,eetacm,br[8][4],ang[8];
      G4double pgam[8],pwid[8][4],x0[8],q20;
      G4double sig_res,t,xpr[3],m0;
      G4int i,j,num;

      G4double xt,p1,p2,p3;

      G4double mp = 0.9382727;
      G4double mpi = 0.135;
      G4double meta = 0.547;
      G4double mp2 = mp*mp;
      G4double w = sqrt(w2);
      //wdif[1] = w - (mp + mpi);
      //wdif[2] = w - (mp + 2.*mpi);

      m0 = 0.125;
      if(sf==2) 
	m0 = xval[49];

      if(sf==1) 
      {
        q20 = 0.05;
      }
      else
      {
        q20 = 0.300;
      }
   
//   single pion branching ratios
      br[1][1] = 1.0;      //   P33(1232)       
      br[2][1] = 0.45;     //   S11(1535)   
      br[3][1] = 0.65;     //   D13(1520)
      br[4][1] = 0.65;     //   F15(1680)
      br[5][1] = 0.4;      //   S11(1650)
      br[6][1] = 0.65;     //   P11(1440) roper 
      br[7][1] = 0.50;     //   F37(1950)

//  eta branching ratios
      br[1][3] = 0.0;      // !!!  P33(1232)
      br[2][3] = 0.45;     // !!!  S11(1535) 
      br[3][3] = 0.0;      // !!!  D13(1520)
      br[4][3] = 0.0;      // !!!  F15(1680)
      br[5][3] = 0.1;      // !!!  S11(1650)
      br[6][3] = 0.0;      // !!!  P11(1440) roper   
      br[7][3] = 0.0;      // !!!  F37(1950)

//  2-pion branching ratios
      for (i=1;i<=7;i++)
      {
        br[i][2] = 1.-br[i][1]-br[i][3];
      }

//   Meson angular momentum
      ang[1] = 1.;      //  P33(1232)
      ang[2] = 0.;      //  S11(1535)
      ang[3] = 2.;      //  D13(1520)
      ang[4] = 3.;      //  F15(1680)
      ang[5] = 0.;      //  S15(1650)
      ang[6] = 1.;      //  P11(1440) roper   
      ang[7] = 3.;      //  F37(1950)

      for( i=1;i<=7;i++)     // resonance damping parameter
        {
	  x0[i] = 0.145;
	}

      x0[1] = 0.130;

      for (i=1;i<=7;i++)
      {
        br[i][2] = 1.-br[i][1]-br[i][3];
      }         
    
      // dip = 1./((1.+q2/0.71)*(1.+q2/0.71));         //  Dipole parameterization
      // mon = 1./(1.+q2/0.71);

      xb = q2/(q2+w2-mp2);
      xpr[1] = 1.+(w2-(mp+mpi)*(mp+mpi))/(q2+q20);
      xpr[1] = 1./xpr[1];
      xpr[2] = 1.+(w2-(mp+mpi+mpi)*(mp+mpi+mpi))/(q2+q20);
      xpr[2] = 1./xpr[2];

      t = log(log((q2+m0)/0.330*0.330)/log(m0/0.330*0.330));

//    Calculate kinematics needed for threshold Relativistic B-W

      k = (w2 - mp2)/2./mp;
      kcm = (w2-mp2)/2./w;

      epicm = (w2 + mpi*mpi -mp2 )/2./w;
      ppicm = sqrt(fmax(0.0,(epicm*epicm - mpi*mpi)));
      epi2cm = (w2 + (2.*mpi)*(2.*mpi) -mp2 )/2./w;
      ppi2cm = sqrt(fmax(0.0,(epi2cm*epi2cm - (2.*mpi)*(2.*mpi))));
      eetacm = (w2 + meta*meta -mp2 )/2./w;
      petacm =  sqrt(fmax(0.0,(eetacm*eetacm - meta*meta)));

      num = 0;

      for (i=1;i<=6;i++)            //  Read in resonance masses
      {
        num = num + 1;
        mass[i] = xval[i];
      }
      
      for (i=1;i<=6;i++)            //  Read in resonance widths
      {
	num = num + 1;
        intwidth[i] = xval[num];
        width[i] = intwidth[i];
      }

      if(sf==2)         //  Put in 4th resonance region 
      {
        mass[7] = xval[43];
        intwidth[7] = xval[44];
        width[7] = intwidth[7];
      }
      else
      {
        mass[7] = xval[47];
        intwidth[7] = xval[48];
        width[7] = intwidth[7];
      }

      for (i=1;i<=7;i++)
      {
        kr[i] = (mass[i]*mass[i]-mp2)/2./mp;
        kcmr[i] = (mass[i]*mass[i]-mp2)/2./mass[i];
        epicmr[i] = (mass[i]*mass[i] + mpi*mpi -mp2 )/2./mass[i];
        ppicmr[i] = sqrt(fmax(0.0,(epicmr[i]*epicmr[i] - mpi*mpi)));
        epi2cmr[i] = (mass[i]*mass[i] + (2.*mpi)*(2.*mpi) -mp2 )/2./mass[i];
        ppi2cmr[i] = sqrt(fmax(0.0,(epi2cmr[i]*epi2cmr[i] - (2.*mpi)*(2.*mpi))));
        eetacmr[i] = (mass[i]*mass[i] + meta*meta -mp2 )/2./mass[i];
        petacmr[i] =  sqrt(fmax(0.0,(eetacmr[i]*eetacmr[i] - meta*meta)));

        // Calculate partial widths
        pwid[i][1] = intwidth[i]*pow(ppicm/ppicmr[i],(2.*ang[i]+1.))
                     *pow((ppicmr[i]*ppicmr[i]+x0[i]*x0[i])/(ppicm*ppicm+x0[i]*x0[i]),ang[i]);
        // 1-pion decay mode

        pwid[i][2] = intwidth[i]*pow(ppi2cm/ppi2cmr[i],(2.*ang[i]+4.))
                     *pow((ppi2cmr[i]*ppi2cmr[i]+x0[i]*x0[i])/(ppi2cm*ppi2cm+x0[i]*x0[i]),(ang[i]+2));   
        // 2-pion decay mode

        pwid[i][2] = w/mass[i]*pwid[i][2];
        pwid[i][3] = 0.;         // !!!  eta decay mode

        if(i==2 || i==5) 
	{
          pwid[i][3]=intwidth[i]*pow(petacm/petacmr[i],(2.*ang[i]+1.))
	            *pow((petacmr[i]*petacmr[i]+x0[i]*x0[i])/(petacm*petacm+x0[i]*x0[i]),ang[i]);
          // eta decay only for S11's 
	}

        pgam[i] = (kcm/kcmr[i])*(kcm/kcmr[i])*(kcmr[i]*kcmr[i]+x0[i]*x0[i])/(kcm*kcm+x0[i]*x0[i]);
        pgam[i] = intwidth[i]*pgam[i];
        width[i] = br[i][1]*pwid[i][1]+br[i][2]*pwid[i][2]+br[i][3]*pwid[i][3];
      }
 //    End resonance kinematics and Widths calculations

 //    Begin resonance Q^2 dependence calculations         
      for (i=1;i<=6;i++)
      {
        for (j=1;j<=4;j++)
	{
          num = num + 1;
          rescoef[i][j]=xval[num];
	}

        if(sf==1)
	{
          height[i] = rescoef[i][1]*(1.+rescoef[i][2]*q2/(1.+rescoef[i][3]*q2))/ pow(1.+q2/0.91,rescoef[i][4]);
	}
        else
	{
          height[i] = rescoef[i][1]*q2/(1.+rescoef[i][2]*q2)*exp(-1.*rescoef[i][3]*q2);
	}

        height[i] = height[i]*height[i];
      }


      if(sf==2)      //  4th resonance region 
      {
        height[7] = xval[45]*q2/(1.+xval[46]*q2)*exp(-1.*xval[47]*q2);
      }
      else
      {
        height[7] = xval[49]/(1.+q2/0.91); 
      }

      height[7] = height[7]*height[7];

//    End resonance Q^2 dependence calculations 
     
      for (i=1;i<=3;i++)        //  Non-Res coefficients 
      {
        for (j=1;j<=4;j++)
	{
          num = num + 1;
          nr_coef[i][j]=xval[num];
	}
      }

//   Calculate Breit-Wigners for all resonances  

      sig_res = 0.0;
      for (i=1;i<=7;i++)
      {
         sigr[i] = width[i]*pgam[i]/((w2 - mass[i]*mass[i])*(w2 - mass[i]*mass[i]) 
	            + (mass[i]*width[i])*(mass[i]*width[i]));
         sigr[i] = height[i]*kr[i]/k*kcmr[i]/kcm*sigr[i]/intwidth[i];
         sig_res = sig_res + sigr[i];
      }
      sig_res = sig_res*w;

//    Finish resonances / start non-res background calculation

      sig_nr = 0.;
      if(sf==1)
      {
        xt = (q2+xval[37])/(w2-1.15+q2+xval[37]);
        p2 = xval[38]*exp(-1.*xval[39]*q2)+xval[40]*log(q2/xval[41]+1.);
        p3 = xval[42]*exp(-1.*xval[43]*q2)+xval[44]*log(q2/xval[45]+1.);
        p1 = xval[46]*(1.+xval[50]*q2/(1.+0.534*q2)); 

        sig_nr = p1*pow(xt,p2)*pow(1.-xt,p3);
      }
      else if(sf==2)
      {

        for (i=1;i<=1;i++)
	{
          sig_nr = sig_nr + nr_coef[i][1]*pow(1.-xpr[i],(nr_coef[i][3]+nr_coef[i][2]*t)) /(1.-xb)/(q2+q20)
                   *pow(q2/(q2+q20), nr_coef[i][4]) *pow(xpr[i],(xval[41]+xval[42]*t));
	}
      }
      
      G4double sig = sig_res + sig_nr;   
      return sig;
}

////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
//     Peiqing, Dec. 11, 2011, Moller elastic scattering
//
//     kinematic relations and cross section formulae 
//     are from Wagner, et al. NIMA294 (1990) 541-548 
//     and Arrington, et al. NIMA311 (1992) 39-48, etc.

G4double QweakSimEPEvent::Moller_Scattering(G4double E_in, G4double theta1, 
                                            G4double &E_out1, G4double &E_out2, G4double &theta2, 
                                            G4double &q2, G4double &fWeightN, G4double &asymmetry)
{
      G4double alpha = 1.0/137.036;
      G4double G_F = 1.166e-11;     // Fermi constant in MeV^(-2)
      G4double M_electron = 0.511;  // Incident Electron mass in MeV
      G4double sin2_theta_W = 0.02381;  // sin2_theta_W at 0.026 GeV, taken from E158

      G4double theta_CM = 2.0*atan(tan(theta1)*sqrt((E_in+M_electron)/(2.*M_electron)));
      E_out1 = M_electron+(E_in-M_electron)*(cos(theta_CM/2.0)*cos(theta_CM/2.0));
      E_out2 = E_in - E_out1 + M_electron;
      theta2 = atan(2.0*M_electron/(E_in+M_electron)/tan(theta1));
      //G4double momentum = sqrt(E_out1*E_out1 - M_electron*M_electron);
      // compute q2 in MeV^2
      //q2 = 4.0*E_in*momentum*sin(theta1/2.0)*sin(theta1/2.0);
      q2 = 2*M_electron*(M_electron+E_in)*sin(theta_CM/2.0)*sin(theta_CM/2.0);  
    
  //  calculate Moller cross-section (units are ub/sr)
      G4double Xsect = pow((1+cos(theta_CM))*(3+cos(theta_CM)*cos(theta_CM)),2); 
      // Xsect = pow(alpha/2.0/M_electron,2)*Xsect/pow(sin(theta_CM),4); // alpha^2/(4m^2) = 0.199 b/Sr
      Xsect = (1.99e4)*Xsect/pow(sin(theta_CM),4);
      fWeightN = Xsect*sin(theta1);
      asymmetry = -M_electron*E_in*(G_F/(sqrt(2.0)*alpha*3.1415927))
                  *16*sin(theta_CM)*sin(theta_CM)/(3+cos(theta_CM)*cos(theta_CM))*(1-4*sin2_theta_W);
      asymmetry = asymmetry*1e6;  // in [ppm]

      //std::cout<<"E_in  E1  E2  theta1  theta2  Xsect  Weight  Q2  asym"<<std::endl;
      //std::cout<<E_in<<"  "<<E_out1<<"  "<<E_out2<<"  "<<theta1*180/3.14<<"  "
      //         <<theta2*180/3.14<<"  "<<Xsect<<"  "<<fWeightN<<"  "<<q2*1e-6<<"  "<<asymmetry<<std::endl;
      
      return Xsect;
}

////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Jim Dowd
// ---------------------------------------------------------
//      Calculates the Cross Section weighting factor for 
//      radiated scattering from a lookup table. 
// ---------------------------------------------------------
//
//  Beam Energy must be 3.35 GeV, 1.16 GeV, or 877 MeV

const std::vector< G4double > QweakSimEPEvent::Radiative_Cross_Section_Lookup(G4double E_in,
                                                         G4double Theta,
                                                         G4double &fWeightN,
                                                         G4double &Q2,
                                                         G4double &E_out)
{
  //G4int    SuperElastic = 1;
  //G4double xsec         = 0.0;
    Double_t       value[value_n] = {0.0};
    std::vector< G4double > CrossSection;
    G4double xsec = 0.0;
    if (Theta<GetThetaAngle_Min())
      Theta = GetThetaAngle_Min();

    //while (SuperElastic) {
    //E_out = (G4UniformRand()*(GetEPrime_Max()-GetEPrime_Min()) + GetEPrime_Min());
    //SuperElastic = SuperElasticCheck(E_in, E_out, Theta, xsec);
      //G4cout << "El XSec:  " << xsec << G4endl;
    //}

    E_out = myUserInfo->GetEPrime();

    Double_t Zpos;
  
    if ( ReactionRegion == 1 ) {
      Zpos = myUserInfo->GetOriginVertexPositionZ();
    } 
    else {
      Zpos = 0.0;
    }
    const Double_t pos[value_d]   = {Zpos,E_in,E_out,Theta};
    //Double_t       value[value_n] = {0.0};
    //std::vector< G4double > CrossSection;
   
    fLookupTable->GetValue(pos,value);
    Q2       = value[1];
    fWeightN = value[6]*sin(Theta*degree);
    //fWeightN = value[6];
    //G4cout << "Rad XSec: " << value[12]*0.001 << G4endl;
    //}

    CrossSection.push_back(value[6]*0.001);  // 0  total radiated cross section
    CrossSection.push_back(value[2]*0.001);  // 1  total born cross section
    CrossSection.push_back(value[3]*0.001);  // 2  inelastic born cross section
    CrossSection.push_back(value[4]*0.001);  // 3  quasi-elastic born cross section
    CrossSection.push_back(value[6]*0.001);  // 4  total radiated cross section
    CrossSection.push_back(value[7]*0.001);  // 5  elastic radiated cross section
    CrossSection.push_back(value[8]*0.001);  // 6  quasi-elastic radiated cross section
    CrossSection.push_back(value[9]*0.001);  // 7  deep-inelastic radiated cross section
    CrossSection.push_back(value[11]*0.001); // 8  total radiated cross section internal only
    CrossSection.push_back(value[12]*0.001); // 9  elastic radiated cross section internal only
    CrossSection.push_back(value[14]*0.001); // 10 quasi-elastic radiated cross section internal only
    CrossSection.push_back(value[13]*0.001); // 11 deep-inelastic radiated cross section internal only
    CrossSection.push_back(0.0);             // 12 elastic peak cross section

    if (SuperElasticCheck(myUserInfo->GetBeamEnergy(), E_out, Theta, xsec)) CrossSection[5] = 0.0;
    else if (SuperElasticCheck(myUserInfo->GetBeamEnergy(), E_out+ElasticPeakDeltaE, Theta, xsec)) {
       CrossSection[12] = xsec/(ElasticPeakDeltaE*0.001);
       CrossSection[5] = 0.0;
    }
    CrossSection[4] = CrossSection[5] + CrossSection[6] + CrossSection[7] + CrossSection[12];
    CrossSection[0] = CrossSection[4];

    return CrossSection;  //  units   [ub/sr/GeV]
}

////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Jim Dowd
// ---------------------------------------------------------
//      Checks the event to see if it is Super-Elastic or not. 
// ---------------------------------------------------------


G4int QweakSimEPEvent::SuperElasticCheck(G4double E_in, G4double E_out, G4double theta, G4double &xsec)
{
  if (myUserInfo->GetReactionType()!=7) return 0;  // Aborts if not using lookup table

  G4double Weight;   // dummy
  G4double Q2;       // dummy

  G4double E_elastic;

  xsec = Elastic_Cross_Section_Proton(E_in, theta, Weight, Q2, E_elastic);

  if (E_out > E_elastic) {
    //G4cout << "###################################################" << G4endl;
    //G4cout << "---------------------------------------------------" << G4endl;
    //G4cout << "E_in:     " << E_in  << G4endl;
    //G4cout << "E_out:    " << E_out << G4endl;
    //G4cout << "E_elastic:" << E_elastic << G4endl;
    //G4cout << "Theta:    " << theta*180.0/3.14159 << G4endl;
    //G4cout << "Event is SuperElestic! Generating new event." << G4endl;
    return 1;
  }
  else {
    //G4cout << "###################################################" << G4endl;
    //G4cout << "E_in:     " << E_in  << G4endl;
    //G4cout << "E_out:    " << E_out << G4endl;
    //G4cout << "E_elastic:" << E_elastic << G4endl;
    //G4cout << "Theta:    " << theta*180.0/3.14159 << G4endl;
    //G4cout << "Event is NOT SuperElastic" << G4endl;
    return 0;
  }
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Jim Dowd
// ---------------------------------------------------------
//      Creates lookup table for calculating elastic radiative 
//      cross sections on hydrogen. 
// ---------------------------------------------------------

void QweakSimEPEvent::CreateLookupTable()
{
  
    G4cout << "---> Calling CreateLookupTable() <---" << G4endl;
  
    G4double energy = GetBeamEnergy();
    if (energy != 3350*MeV && energy != 1160*MeV && energy != 877*MeV) {
      G4cout << "#### Current beam energy is not a valid choice for lookup table"  << G4endl;
      G4cout << "#### Setting beam energy to default value for lookup table (3.35 GeV)" << G4endl;
      energy = 3350*MeV;
      SetBeamEnergy(energy);
    }

    TString target;
    if (ReactionRegion == 1) target = "lh2";
    else if (ReactionRegion == 2) target = "USALWindow";
    else if (ReactionRegion == 3) target = "DSALWindow";
    else if (ReactionRegion == 4) target = "USALDummy1";
    else if (ReactionRegion == 5) target = "USALDummy2";
    else if (ReactionRegion == 6) target = "USALDummy4";
    else if (ReactionRegion == 7) target = "DSALDummy2";
    else if (ReactionRegion == 8) target = "DSALDummy4";
    else if (ReactionRegion == 9) target = "DSALDummy8";
    else if (ReactionRegion == 10) target = "USCDummy";
    else if (ReactionRegion == 11) target = "DSCDummy";
    
    TString filename =  "radiative_cross_section_";
    filename += target;
    filename += "_";
    filename += (Int_t)energy;
    filename += "MeV";
    if (ReactionRegion == 1 && energy != 3350*MeV) filename += "_v2";
    filename += ".dat";

    TString filepath = "./radiative_lookup_tables/";
    
    std::ifstream in;
    in.open(filepath + filename);
    if (!in.is_open()) { 
      G4cout << "#### Failed to open lookup table data file \"" << filepath << filename << "\"" << G4endl;
      return;
    }
    else
    {
      in.close();
      G4cout << "#### Found lookup table data file \"" << filepath << filename << "\"" << G4endl;
      if (fLookupTable != 0) delete fLookupTable;
      fLookupTable = new QweakSimFieldMap<value_t,value_n>(value_d);
      fLookupTable->ReadTextFile((filepath +filename).Data());
    }
    G4cout << "+++++++++++++++++++++++++++++" << G4endl;
    G4cout << "++ Lookup Table Parameters ++" << G4endl;
    G4cout << "+++++++++++++++++++++++++++++" << G4endl;
    G4cout << "Beam Energy:       " << fLookupTable->GetMinimum(1)/1000 << " GeV" << G4endl;
    G4cout << "Target:            " << target << G4endl;
    G4cout << "E\' Lower Bound:    " << fLookupTable->GetMinimum(2)/1000 << " GeV" << G4endl;
    G4cout << "E\' Upper Bound:    " << fLookupTable->GetMaximum(2)/1000 << " GeV" << G4endl;
    G4cout << "Theta Lower Bound: " << fLookupTable->GetMinimum(3)/degree << " degrees" << G4endl;
    G4cout << "Theta Upper Bound: " << fLookupTable->GetMaximum(3)/degree << " degrees" << G4endl;
    G4cout << "+++++++++++++++++++++++++++++" << G4endl;

    if (energy != GetBeamEnergy()) SetBeamEnergy(energy);
    else CheckLookupTableBounds();


    G4cout << "---> Leaving CreateLookupTable() <---" << G4endl;

    
    //********************************************************************

  /*
  // **********************************************************************
  // **********************************************************************
  // The code below is used to convert the raw output of the Bosted code
  // into a format the GEANT4 can read.  
  // **********************************************************************


  //G4int entries = 93610;
  G4int entries = 1;
  //G4int entries[3] = { 1295, 1665, 1073};

    coord_t coord[value_d] = {0.0};
    value_t field[value_n] = {0.0};
 
    std::vector< G4double > fMin;
    std::vector< G4double > fMax;
    std::vector< G4double > fStep;

    //std::vector< G4double > fMin[3];
    //std::vector< G4double > fMax[3];
    //std::vector< G4double > fStep[3];

    std::string target[10] = { "DSALDummy2",
                             "DSALDummy4",
                             "DSALDummy8",
                             "USALDummy1",
                             "USALDummy2",
                             "USALDummy4",
                             "DSALWindow",
                             "USALWindow",
                             "DSCDummy",
                             "USCDummy" };

    std::string energy_in[3] = { "877mev",
                               "1gev",
                               "3gev" };

    std::string energy_out[3] = { "877MeV",
                                "1160MeV",
                                "3350MeV" };

    std::string filepath = "/group/qweak/jdowd/externals_qweak/OUT/";
    std::string name, name1, name2, name3;

    //  Set min, max, and step size for each coordinate in the lookup table.
    //  Z position in radiation lengths
    fMin.push_back(myUserInfo->TargetCenterPositionZ - 0.5*myUserInfo->TargetLength);
    fMax.push_back(myUserInfo->TargetCenterPositionZ + 0.5*myUserInfo->TargetLength);
    fStep.push_back(myUserInfo->TargetLength/10.0);

    //fMin.push_back(0.0);
    //fMax.push_back(0.0);
    //fStep.push_back(1.0);
    
    //fMin[0].push_back(0.0);
    //fMax[0].push_back(0.0);
    //fStep[0].push_back(1.0);

    //fMin[1].push_back(0.0);
    //fMax[1].push_back(0.0);
    //fStep[1].push_back(1.0);

    //fMin[2].push_back(0.0);
    //fMax[2].push_back(0.0);
    //fStep[2].push_back(1.0);
    

    //  Beam Energy in GeV
    fMin.push_back(1.16*GeV);
    fMax.push_back(1.16*GeV);
    fStep.push_back(0.005*GeV);
    
    //fMin[0].push_back(0.877*GeV);
    //fMax[0].push_back(0.877*GeV);
    //fStep[0].push_back(0.05*GeV);

    //fMin[1].push_back(1.16*GeV);
    //fMax[1].push_back(1.16*GeV);
    //fStep[1].push_back(0.05*GeV);

    //fMin[2].push_back(3.35*GeV);
    //fMax[2].push_back(3.35*GeV);
    //fStep[2].push_back(0.05*GeV);
    
    //  E prime in GeV
    fMin.push_back(0.015*GeV);
    fMax.push_back(1.16*GeV);
    fStep.push_back(0.005*GeV);
    
    //fMin[0].push_back(0.026*GeV);
    //fMax[0].push_back(0.876*GeV);
    //fStep[0].push_back(0.025*GeV);

    //fMin[1].push_back(0.059*GeV);
    //fMax[1].push_back(1.159*GeV);
    //fStep[1].push_back(0.025*GeV);

    //fMin[2].push_back(0.150*GeV);
    //fMax[2].push_back(1.550*GeV);
    //fStep[2].push_back(0.050*GeV);
    
    //  Theta angle
    fMin.push_back(2.00*degree);
    fMax.push_back(20.0*degree);
    fStep.push_back(0.5*degree);
    
    //fMin[0].push_back(2.00*degree);
    //fMax[0].push_back(20.0*degree);
    //fStep[0].push_back(0.5*degree);

    //fMin[1].push_back(2.00*degree);
    //fMax[1].push_back(20.0*degree);
    //fStep[1].push_back(0.5*degree);

    //fMin[2].push_back(2.00*degree);
    //fMax[2].push_back(20.0*degree);
    //fStep[2].push_back(0.5*degree);
    
    //G4cout << "Target Min:      " << fMin[0] << G4endl;
    //G4cout << "Target Max:      " << fMax[0] << G4endl;
    
    for (Int_t n = 0; n < (Int_t)fStep.size(); n++) {
      entries *= (G4int)( (fMax[n]-fMin[n])/fStep[n] + 1.5 );
    }
    std::ifstream in;
    
    G4cout << "!!!!!!!!!!!!!!!!!!!!!!  Debug !!!!!!!!!!!!!!!!!!!!!!" << G4endl;
    G4cout << " fMin:   " << fMin[0] << "    " << fMin[1] << "    " << fMin[2] << "    " << fMin[3] << G4endl;
    G4cout << " fMax:   " << fMax[0] << "    " << fMax[1] << "    " << fMax[2] << "    " << fMax[3] << G4endl;
    G4cout << " fStep:  " << fStep[0]<< "    " << fStep[1]<< "    " << fStep[2]<< "    " << fStep[3]<< G4endl;
    G4cout << "===================================================================" << G4endl;

    //for (Int_t target_num = 0; target_num < 10; target_num++) {
    for (Int_t target_num = 0; target_num < 1; target_num++) {
      //for (Int_t energy_num = 0; energy_num < 3; energy_num++) {
      for (Int_t energy_num = 0; energy_num < 1; energy_num++) {
        //in.open("./radiative_lookup.dat");

        name = filepath + "lookup_" + target[target_num] + "_" + energy_out[energy_num] + ".out";

        in.open("./test_v2.out");
        //in.open(name.c_str());
        if (!in.is_open())  
            G4cout << "#### Failed to open data file for lookup table" << G4endl;
        else
        {
          G4cout << "#### Found lookup table data file"  << G4endl;
          if (fLookupTable != 0) delete fLookupTable;
          fLookupTable = new QweakSimFieldMap<value_t,value_n>(value_d);
          //fLookupTable->SetMinimumMaximumStep(fMin[energy_num],fMax[energy_num],fStep[energy_num]);
          fLookupTable->SetMinimumMaximumStep(fMin,fMax,fStep);


          //for (Int_t n = 0; n < (Int_t)fStep[energy_num].size(); n++) {
          //  entries *= (G4int)( (fMax[energy_num][n]-fMin[energy_num][n])/fStep[energy_num][n] + 1.5 );
          //}

          //  Filling Lookup Table
          //for (Int_t line = 0; line <  entries[energy_num]; line++) {
          for (Int_t line = 0; line <  entries; line++) {
            if (in.peek() == EOF) {
              G4cout << "#### Error reading \'elastic_lookup.dat\':  File contains only "
                     << line << " of " << entries << " expected lines. ####" << G4endl;
              break;
            }

            for (G4int i = 0; i < value_d; i++)  in >> coord[i];
            for (G4int j = 0; j < value_n; j++)  in >> field[j];

            //G4cout << "Initial:  " << coord[0] << "    " << coord[1] << "    " << coord[2] << "    " << coord[3] << G4endl;
   
            //  Add units
                                 // Z position converted from rad lengths to GEANT coords
            coord[0] = myUserInfo->TargetCenterPositionZ - 0.5*myUserInfo->TargetLength
                       + coord[0]*myUserInfo->TargetLength/0.0396;        
            coord[1] *= GeV;     // Beam Energy
            coord[2] *= GeV;     // E prime
            coord[3] *= degree;  // Theta

            //G4cout << "Final:    " << coord[0] << "    " << coord[1] << "    " << coord[2] << "    " << coord[3] << G4endl;
            //G4cout << "-----------------------------------------------------------------" << G4endl;

            //field[0]           // Bjorken x (unitless) // This value has too few sig figs
	    field[1] *= GeV*GeV; // Q2                   // This value has too few sig figs
	    //field[2]           // total born cross section (ub/Sr)
	    //field[3]           // inelastic born cross section(ub/Sr)
	    //field[4]           // quasi-elastic born cross section (ub/Sr)
	    //field[5]           // quasi-elastic factor
	    //field[6]           // total radiated cross section (ub/Sr)
	    //field[7]           // elastic radiated cross section (ub/Sr)
	    //field[8]           // quasi-elastic radiated cross section (ub/Sr)
	    //field[9]           // deep-inelastic radiated cross section (ub/Sr)
	    //field[10]          // charge correction
            //field[11]          // total radiated cross section internal only (ub/Sr)
	    //field[12]          // elastic radiated cross section internal only (ub/Sr)
	    //field[13]          // deep-inelastic radiated cross section internal only (ub/Sr)
	    //field[14]          // quasi-elastic radiated cross section internal only (ub/Sr)

            fLookupTable->Set(coord,field);
          }
          G4cout << "===== Filling of Lookup Table complete! =====" << G4endl;
        }
        in.close();
        fLookupTable->WriteTextFile("./radiative_lookup_1160_v2.out");

        name = filepath + "final/radiative_lookup_" + target[target_num] + "_" + energy_out[energy_num] + ".dat";
        
        //fLookupTable->WriteTextFile("./radiative_lookup_test.out");
        //fLookupTable->WriteTextFile(name.c_str());

        G4cout << "Wrote:  " << name << G4endl;

      }
   }
 */
}


////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Jim Dowd
// ---------------------------------------------------------
//      Checks the ranges of input parameters (E, E', and theta)
//      and insures they are within the lookup table bounds.  
// ---------------------------------------------------------

void QweakSimEPEvent::CheckLookupTableBounds()
{
  G4cout << "---> Calling CheckLookupTableBounds() <---" << G4endl;
  if (fLookupTable == 0) return;
  if (GetBeamEnergy() != (G4double)fLookupTable->GetMinimum(1) ) {
    G4cout << "!!!! Beam Energy is out of bounds" << G4endl;
    G4cout << "---> Changing Beam Energy to default value (" << fLookupTable->GetMinimum(1)/1000 << " GeV)" << G4endl;
    SetBeamEnergy(  (G4double)fLookupTable->GetMinimum(1) );
    CreateLookupTable();
    return;
  }
  
  if (GetEPrime_Min() < fLookupTable->GetMinimum(2) || GetEPrime_Min() > fLookupTable->GetMaximum(2)) {
    SetEPrime_Min(fLookupTable->GetMinimum(2));
    G4cout << "!!!! Minimum E\' is out of bounds" << G4endl;
    G4cout << "---> Changing Minimum E\' to lower bound (" << fLookupTable->GetMinimum(2)/1000 << " GeV)" << G4endl;      
  }
  if (GetEPrime_Max() > fLookupTable->GetMaximum(2) || GetEPrime_Max() < fLookupTable->GetMinimum(2)) {
    SetEPrime_Max(fLookupTable->GetMaximum(2));
    G4cout << "!!!! Maximum E\' is out of bounds" << G4endl;
    G4cout << "---> Changing Maximum E\' to upper bound (" << fLookupTable->GetMaximum(2)/1000 << " GeV)" << G4endl;      
  }
  if (GetEPrime_Min() > GetEPrime_Max()) {
    SetEPrime_Min(GetEPrime_Max());
    G4cout << "!!!! Minimum E\' greater than maximum E\'" << G4endl;
    G4cout << "---> Changing Minimum E\' to " << GetEPrime_Max()/1000 << " GeV" << G4endl;
  }
  
  if (GetThetaAngle_Min() < fLookupTable->GetMinimum(3) || GetThetaAngle_Min() > fLookupTable->GetMaximum(3)) {
    SetThetaAngle_Min(fLookupTable->GetMinimum(3));
    G4cout << "!!!! Minimum Theta is out of bounds" << G4endl;
    G4cout << "---> Changing Minimum Theta to lower bound (" << fLookupTable->GetMinimum(3)/degree << " degrees)" << G4endl;      
  }
  if (GetThetaAngle_Max() > fLookupTable->GetMaximum(3) || GetThetaAngle_Max() < fLookupTable->GetMinimum(3)) {
    SetThetaAngle_Max(fLookupTable->GetMaximum(3));
    G4cout << "!!!! Maximum Theta is out of bounds" << G4endl;
    G4cout << "---> Changing Maximum Theta to upper bound (" << fLookupTable->GetMaximum(3)/degree << " degrees)" << G4endl;      
  }
  if (GetThetaAngle_Min() > GetThetaAngle_Max()) {
    SetThetaAngle_Min(GetThetaAngle_Max());
    G4cout << "!!!! Minimum Theta greater than maximum Theta" << G4endl;
    G4cout << "---> Changing Minimum Theta to " << GetThetaAngle_Max() << " degrees" << G4endl;
  }
  G4cout << "---> Leaving CheckLookupTableBounds() <---" << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double QweakSimEPEvent::AlNuclInel(G4double E_in, // MeV
				     G4double Theta,  //radians
				     G4double &fWeightN,
				     G4double &Q2,
				     G4double &E_out)
{
  ///
  G4double M_p = 938.2796;  // proton mass in MeV
//G4double Z_Al = 13.0;
  G4double A_Al = 27.0;
  G4double M_Al = M_p*A_Al;

//G4double CTH = cos(Theta/2.0);
  G4double STH = sin(Theta/2.0);

  // now get qsq
  G4double ETA = 1.0+2.0*E_in*STH*STH/M_Al;
  E_out = E_in/ETA;
  
  Q2 = 4*E_in*E_out*STH*STH;     //unit: MeV^2

  Theta *= 180/3.14159;  //deg
  // in ub/sr
  G4double xsect = Alinel_crsec_gen(E_in,Theta);
  
  Theta *= 3.14159/180; // bk to radians

  fWeightN = xsect*sin(Theta);

  return xsect;
}

//////////////////////////
// GDR crsec
G4double QweakSimEPEvent::AlGDR(G4double E_in, //MeV
				G4double Theta,  // radians
				G4double &fWeightN,
				G4double &Q2,
				G4double &E_out){
  ///
  double M_p = 938.2796;  // proton mass in MeV
  double Z_Al = 13.0;
  double A_Al = 27.0;
  double M_Al = M_p*A_Al;

  //  double th = Theta*3.14159/180.;  // convert to radians
//double CTH = cos(Theta/2.0);
  double STH = sin(Theta/2.0);

  // now get qsq
  double ETA = 1.0+2.0*E_in*STH*STH/M_Al;
  E_out = E_in/ETA;
  
  Q2 = 4*E_in*E_out*STH*STH;     //unit: MeV^2
  // double hbarc = 197.3269631; // MeV fm
  // double q2 = Q2/(hbarc*hbarc);  //convert MeV^2 into fm^(-2)
  // double qq = sqrt(q2);

  // GDR peak energy
  Double_t E_peak = 20.8;  // MeV 

  double N_Al = 14;
  double mu = N_Al*Z_Al/A_Al*M_Al;
  double sig_GDR_el_Ratio = pow(N_Al/A_Al,2)/(2*mu)*Q2/E_peak; // dimensionless

  //  cout << "q(1/fm):: " << qq << endl;

  double fac = 6.5; // scale crsec to reflect integration in energy of the GDR peak

  double elasticAl = Elastic_Cross_Section_Aluminum(E_in,Theta,fWeightN,Q2,E_out);

  E_out = E_in/ETA;  
  Q2 = 4*E_in*E_out*STH*STH;     //unit: MeV^2

  double xsect = sig_GDR_el_Ratio*elasticAl*fac; //ub/sr

  fWeightN = xsect*sin(Theta);

  return xsect;
}


/////// --------------------------------------------------------------------
//
//--- Fang Guo
//
//---   Calculates the Cross Section weighting factor for 
//---   pion photo-production with the wiser code. 
//
// EPrime_Max, EPrime_Min in GeV
// E_in is in MeV, 
//
G4double QweakSimEPEvent::Pion_PhotoProduction(G4double E_in, //MeV
                                               G4double Theta, //radians
                                               G4double &fWeightN,
                                               G4double &Q2,
                                               G4double &E_out)
{
    const G4double Mpi = 0.13957*GeV;   ///--- GeV

    if (Theta<GetThetaAngle_Min())
      Theta = GetThetaAngle_Min();
	
    // need to evaluate Q2 properply, in order to evaluate 
    // the internal radiation length more accurately below
    Q2 = 0.026; 

    G4double tmp_EpMax = GetEPrime_Max();
    if(GetEPrime_Max() > E_in) tmp_EpMax = E_in;
	
    E_out = (G4UniformRand()*(tmp_EpMax - GetEPrime_Min()) + GetEPrime_Min());   //--- final total energy in GeV
    G4double pf = sqrt(pow(E_out,2) - pow(Mpi,2)); //--- final momentum in GeV

    //---
    //--- radiation length from page 12 of "The Qweak target design and safety document"
    //--- http://qweak.jlab.org/DocDB/0010/001041/002/Qweak%20Target%20PDR.pdf
    //---
    G4double lh2_length = myPositionZ - (myUserInfo->TargetCenterPositionZ) + 0.5*(myUserInfo->TargetLength);
    G4double intern_rad_len = 0.0204; // internal radiator from Mo/Tsai
    G4double rad_len = myUserInfo->TargetEntranceWindowThickness/(8.896*cm) + lh2_length/(871.9*cm) + intern_rad_len;   //--- radiation length
    //G4cout << "radiation length: " << rad_len << G4endl;

    G4int type = 1; //--- pi-
	
    // wiser_sigma() needs E_in & pf in GeV, Theta in radians,
    //  rad_len in fraction (not %)
    //  wiser_sigma returns crsec in nb/GeV/sr 
    G4double xsect = (1.0/1000.00) * wiser_sigma(E_in/GeV, pf/GeV, Theta, rad_len, type); //--- nanobarns/GeV/str --> ub/sr
	
    fWeightN = xsect*sin(Theta);

    //    G4cout << E_in/GeV <<"\t" << pf/GeV << "\t" << Theta <<"\t" << rad_len <<"\t" << type << G4endl;
    //    G4cout << "-- ** Pion crsec :: " << xsect << " ** --" << G4endl;

    return xsect;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Quasielastic fit from Bosted et al
// Added 19/March kamyers@jlab.org

G4double QweakSimEPEvent::Quasi_Elastic_Bosted(G4double E_in, //MeV
                                               G4double Theta,
                                               G4int Zin, 
                                               G4int Ain,
                                               G4double &fWeightN,
                                               G4double &Q2,
                                               G4double &E_out)
{

  G4double F1 = 0.0;
  G4double F2 = 0.0;
  G4double W1 = 0.0;
  G4double W2 = 0.0;
  G4double Wsq = 0.0;
  G4double xsect = 0.0;
  G4double Ein = 0.0;
  G4double Eout = 0.0;

  // In this subroutine units are in GeV, so
  Ein = E_in/1000.;                // maximum energy in GeV
  G4double M_electron = 0.000511;  // minimum energy (electron mass) in GeV
  G4double Mp = 0.93828;

  // G4double Theta_Min = 1.745329E-4;
  if (Theta<GetThetaAngle_Min())
    Theta = GetThetaAngle_Min();

  // Generate flat energy distribution of outgoing electron
  Eout =  M_electron + G4UniformRand()*(Ein - M_electron);

  G4double CTH = cos(Theta/2.0);
  G4double STH = sin(Theta/2.0);
  G4double T2THE = STH*STH/CTH/CTH;
  G4double Nu = Ein - Eout;
  Q2 = 4.0*Ein*Eout*STH*STH;
  Wsq = Mp*Mp + 2.0*Mp*Nu - Q2;

  // Mott scattering
  G4double MOTT = pow((0.00072/Ein*CTH/STH/STH),2);
  MOTT = MOTT*1.0E4; // Units: ub/sr/GeV

  //G4cout << "Ein, Eout, Nu, Theta: " << Ein << ", " << Eout << ", " << Nu << ", " << Theta/degree << G4endl;
  //G4cout << "Q2, W2, Mott: " << Q2 << ", " << Wsq << ", " << MOTT << G4endl;

  F1F2QE09(Zin, Ain, Q2, Wsq, F1, F2);
  W1 = F1/Mp;
  W2 = F2/Nu;

  xsect = MOTT*(W2 + 2.0*T2THE*W1)*(Ein - M_electron);
  //  G4cout << "F1, F2, W1, W2: " << F1 << ", " << F2 << ", " << W1 << ", " << W2 << G4endl;
 
  // In some cases a negative F2 is returned giving a negative cross section
  if (xsect <= 0) xsect = 0.0;

  // G4cout << "xsect: " << xsect << G4endl;

  fWeightN = xsect*sin(Theta);

  E_out = Eout*1000.;		// Convert back to MeV before leaving
  Q2 = Q2*1.0E6;		// Seems like this needs to be returned in MeV**2
  return xsect;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Nuclear inelastic fit from Bosted et al
// Added 14/May/2014 kamyers@jlab.org

G4double QweakSimEPEvent::NuclearInelastic_Bosted(G4double E_in, //MeV
                                               G4double Theta, //radians
                                               G4int Zin, 
                                               G4int Ain,
                                               G4double &fWeightN,
                                               G4double &Q2,
                                               G4double &E_out)
{

  G4double F1 = 0.0;
  G4double F2 = 0.0;
  G4double W1 = 0.0;
  G4double W2 = 0.0;
  G4double Wsq = 0.0;
  G4double xsect = 0.0;
  G4double Ein = 0.0;
  G4double Eout = 0.0;

  // In this subroutine units are in GeV, so
  Ein = E_in/1000.;                // maximum energy in GeV
  G4double M_electron = 0.000511;  // minimum energy (electron mass) in GeV
  G4double Mp = 0.93828;

  // G4double Theta_Min = 1.745329E-4;
  if (Theta<GetThetaAngle_Min())
    Theta = GetThetaAngle_Min();

  // Generate flat energy distribution of outgoing electron
  Eout =  M_electron + G4UniformRand()*(Ein - M_electron);

  G4double CTH = cos(Theta/2.0);
  G4double STH = sin(Theta/2.0);
  G4double T2THE = STH*STH/CTH/CTH;
  G4double Nu = Ein - Eout;
  Q2 = 4.0*Ein*Eout*STH*STH;
  Wsq = Mp*Mp + 2.0*Mp*Nu - Q2;

  // Mott scattering
  G4double MOTT = pow((0.00072/Ein*CTH/STH/STH),2);
  MOTT = MOTT*1.0E4; // Units: ub/sr/GeV

  //G4cout << "Ein, Eout, Nu, Theta: " << Ein << ", " << Eout << ", " << Nu << ", " << Theta/degree << G4endl;
  //G4cout << "Q2, W2, Mott: " << Q2 << ", " << Wsq << ", " << MOTT << G4endl;

  F1F2IN09(Zin, Ain, Q2, Wsq, F1, F2);
  W1 = F1/Mp;
  W2 = F2/Nu;

  xsect = MOTT*(W2 + 2.0*T2THE*W1)*(Ein - M_electron);
  //G4cout << "F1, F2, W1, W2: " << F1 << ", " << F2 << ", " << W1 << ", " << W2 << G4endl;

  // In some cases a negative F2 is returned giving a negative cross section
  if (xsect <= 0) xsect = 0.0;
  
  fWeightN = xsect*sin(Theta);
  //G4cout << "xsect, fweight: " << xsect << ", "<< fWeightN << G4endl;

  E_out = Eout*1000.;           // Convert back to MeV before leaving
  Q2 = Q2*1.0E6;                // Seems like this needs to be returned in MeV**2
  return xsect;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimEPEvent::F1F2QE09(G4int Z, G4int IA, G4double QSQ,
                               G4double wsq, G4double &F1, G4double &F2)
{
//=======================================================================
//      SUBROUTINE F1F2QE09(Z, A, QSQ, wsq, F1, F2)
//
// Calculates quasielastic A(e,e')X structure functions F1 and F2 PER NUCLEUS
// for A>2 uses superscaling from Sick, Donnelly, Maieron, nucl-th/0109032
// for A=2 uses pre-integrated Paris wave function (see ~bosted/smear.f)
// coded by P. Bosted August to October, 2006
//
// input: Z, A  (real*8) Z and A of nucleus (shoud be 2.0D0 for deueron)
//        Qsq (real*8) is 4-vector momentum transfer squared (positive in
//                     chosen metric)
//        Wsq (real*8) is invarinat mass squared of final state calculated
//                     assuming electron scattered from a free proton
//                 
// outputs: F1, F2 (real*8) are structure functions per nucleus
//
// Note: Deuteron agrees well with Laget (see ~bosted/eg1b/laget.f) for
// a) Q2<1 gev**2 and dsig > 1% of peak: doesnt describe tail at high W
// b) Q2>1 gev**2 on wings of q.e. peak. But, this model is up
//    to 50% too big at top of q.e. peak. BUT, F2 DOES agree very
//    nicely with Osipenko et al data from CLAS, up to 5 GeV**2
  
//  G4cout << "Z, A, Q2, W2: " << Z << ", " << IA << ", " << QSQ << ", " << wsq << G4endl;

  G4double avgN, Pauli_sup1, Pauli_sup2, GEP, GEN, GMP, GMN, Q, Q3, Q4;
  G4double amp = 0.93828;
  G4double amd = 1.8756;
  G4double RMUP = 2.792782;
  G4double RMUN = -1.913148;
  G4double pz, Nu, dpz, pznom, pzmin;
  G4double QV, TAU, FY, dwmin, w2p;
  G4double kappa, lam, lamp, taup, squigglef, psi, psip, nuL, nuT;
  G4double kf, Es, GM2bar, GE2bar, W2bar, Delta, GL, GT;
  G4int izz, izzmin, izp, izznom, izdif;

  // Look up tables for deuteron case
  G4double fyd[200] = {
    0.00001,0.00002,0.00003,0.00005,0.00006,0.00009,0.00010,0.00013,
    0.00015,0.00019,0.00021,0.00026,0.00029,0.00034,0.00038,0.00044,
    0.00049,0.00057,0.00062,0.00071,0.00078,0.00089,0.00097,0.00109,
    0.00119,0.00134,0.00146,0.00161,0.00176,0.00195,0.00211,0.00232,
    0.00252,0.00276,0.00299,0.00326,0.00352,0.00383,0.00412,0.00447,
    0.00482,0.00521,0.00560,0.00603,0.00648,0.00698,0.00747,0.00803,
    0.00859,0.00921,0.00985,0.01056,0.01126,0.01205,0.01286,0.01376,
    0.01467,0.01569,0.01671,0.01793,0.01912,0.02049,0.02196,0.02356,
    0.02525,0.02723,0.02939,0.03179,0.03453,0.03764,0.04116,0.04533,
    0.05004,0.05565,0.06232,0.07015,0.07965,0.09093,0.10486,0.12185,
    0.14268,0.16860,0.20074,0.24129,0.29201,0.35713,0.44012,0.54757,
    0.68665,0.86965,1.11199,1.43242,1.86532,2.44703,3.22681,4.24972,
    5.54382,7.04016,8.48123,9.40627,9.40627,8.48123,7.04016,5.54382,
    4.24972,3.22681,2.44703,1.86532,1.43242,1.11199,0.86965,0.68665,
    0.54757,0.44012,0.35713,0.29201,0.24129,0.20074,0.16860,0.14268,
    0.12185,0.10486,0.09093,0.07965,0.07015,0.06232,0.05565,0.05004,
    0.04533,0.04116,0.03764,0.03453,0.03179,0.02939,0.02723,0.02525,
    0.02356,0.02196,0.02049,0.01912,0.01793,0.01671,0.01569,0.01467,
    0.01376,0.01286,0.01205,0.01126,0.01056,0.00985,0.00921,0.00859,
    0.00803,0.00747,0.00698,0.00648,0.00603,0.00560,0.00521,0.00482,
    0.00447,0.00412,0.00383,0.00352,0.00326,0.00299,0.00276,0.00252,
    0.00232,0.00211,0.00195,0.00176,0.00161,0.00146,0.00134,0.00119,
    0.00109,0.00097,0.00089,0.00078,0.00071,0.00062,0.00057,0.00049,
    0.00044,0.00038,0.00034,0.00029,0.00026,0.00021,0.00019,0.00015,
    0.00013,0.00010,0.00009,0.00006,0.00005,0.00003,0.00002,0.00001};

  G4double avp2[200] = {
    1.0,0.98974,0.96975,0.96768,0.94782,0.94450,0.92494,0.92047,
    0.90090,0.89563,0.87644,0.87018,0.85145,0.84434,0.82593,0.81841,
    0.80021,0.79212,0.77444,0.76553,0.74866,0.73945,0.72264,0.71343,
    0.69703,0.68740,0.67149,0.66182,0.64631,0.63630,0.62125,0.61154,
    0.59671,0.58686,0.57241,0.56283,0.54866,0.53889,0.52528,0.51581,
    0.50236,0.49291,0.47997,0.47063,0.45803,0.44867,0.43665,0.42744,
    0.41554,0.40656,0.39511,0.38589,0.37488,0.36611,0.35516,0.34647,
    0.33571,0.32704,0.31656,0.30783,0.29741,0.28870,0.27820,0.26945,
    0.25898,0.25010,0.23945,0.23023,0.21943,0.20999,0.19891,0.18911,
    0.17795,0.16793,0.15669,0.14667,0.13553,0.12569,0.11504,0.10550,
    0.09557,0.08674,0.07774,0.06974,0.06184,0.05484,0.04802,0.04203,
    0.03629,0.03129,0.02654,0.02247,0.01867,0.01545,0.01251,0.01015,
    0.00810,0.00664,0.00541,0.00512,0.00512,0.00541,0.00664,0.00810,
    0.01015,0.01251,0.01545,0.01867,0.02247,0.02654,0.03129,0.03629,
    0.04203,0.04802,0.05484,0.06184,0.06974,0.07774,0.08674,0.09557,
    0.10550,0.11504,0.12569,0.13553,0.14667,0.15669,0.16793,0.17795,
    0.18911,0.19891,0.20999,0.21943,0.23023,0.23945,0.25010,0.25898,
    0.26945,0.27820,0.28870,0.29741,0.30783,0.31656,0.32704,0.33571,
    0.34647,0.35516,0.36611,0.37488,0.38589,0.39511,0.40656,0.41554,
    0.42744,0.43665,0.44867,0.45803,0.47063,0.47997,0.49291,0.50236,
    0.51581,0.52528,0.53889,0.54866,0.56283,0.57241,0.58686,0.59671,
    0.61154,0.62125,0.63630,0.64631,0.66182,0.67149,0.68740,0.69703,
    0.71343,0.72264,0.73945,0.74866,0.76553,0.77444,0.79212,0.80021,
    0.81841,0.82593,0.84434,0.85145,0.87018,0.87644,0.89563,0.90090,
    0.92047,0.92494,0.94450,0.94782,0.96768,0.96975,0.98974,1.0};

  // Peter Bosted's correction params
  /*
  G4double pb[20] = {
    0.1023E+02, 0.1052E+01, 0.2485E-01, 0.1455E+01,
    0.5650E+01,-0.2889E+00, 0.4943E-01,-0.8183E-01,
    -0.7495E+00, 0.8426E+00,-0.2829E+01, 0.1607E+01,
    0.1733E+00, 0.0000E+00, 0.0000E+00, 0.0000E+00,
    0.0000E+00, 0.0000E+00, 0.0000E+00, 0.0000E+00};
  */
  G4double y,R;

  G4double P[24] = {
     5.1377e-03,   9.8071e-01,   4.6379e-02,   1.6433e+00,
     6.9826e+00,  -2.2655e-01,   1.1095e-01,   2.7945e-02,
     4.0643e-01,   1.6076e+00,  -7.5460e+00,   4.4418e+00,
     -3.7464e-01,   1.0414e-01,  -2.6852e-01,   9.6653e-01,
     -1.9055e+00,   9.8965e-01,   2.0613e+02,  -4.5536e-02,
     2.4902e-01,  -1.3728e-01,   2.9201e+01,   4.9280e-03};

  // return if proton: future change this to allow for
  // equivalent W resolution
  F1 = 0.;
  F2 = 0.;
  avgN = A - Z;
  if (IA==1) return;

  // some kinematic factors. Return if Nu or QSQ is negative
  Nu = (wsq - amp*amp + QSQ) / 2. / amp;

  //G4cout << "In call... IA, Nu, QSQ = " << IA << ", " << Nu << ", " << QSQ << G4endl;
  if(Nu <= 0.0 || QSQ < 0.) return;
  TAU   = QSQ / 4.0 / amp / amp;                                 
  QV = sqrt(Nu*Nu + QSQ);

  // Bosted fit for nucleon form factors Phys. Rev. C 51, p. 409 (1995)
  Q = sqrt(QSQ);
  Q3 = QSQ * Q;
  Q4 = QSQ*QSQ;
  GEP = 1./  (1. + 0.14 * Q + 3.01 * QSQ + 0.02 * Q3 + 1.20 * Q4 + 0.32 * pow(Q,5));
  GMP = RMUP * GEP;
  GMN = RMUN / (1.- 1.74 * Q + 9.29 * QSQ - 7.63 * Q3 + 4.63 * Q4);
  GEN = 1.25 * RMUN * TAU / (1. + 18.3 * TAU) / pow((1. + QSQ / 0.71),2);

  //G4cout << "Form Factors: " << GEP << ", " << GMP << ", " << GEN << ", " << GMN << G4endl;

  // Get kf and Es from superscaling from Sick, Donnelly, Maieron,
    // nucl-th/0109032
    if(IA==2) kf=0.085;
    if(IA==2) Es=0.0022;
    // changed 4/09
    if(IA==3) kf=0.115;
    if(IA==3) Es=0.001 ;
    // changed 4/09
    if(IA>3) kf=0.19;
    if(IA>3) Es=0.017; 
    if(IA>7) kf=0.228;
    if(IA>7) Es=0.020;
    // changed 5/09
    if(IA>7) Es=0.0165;
    if(IA>16) kf=0.230;
    if(IA>16) Es=0.025;
    if(IA>25) kf=0.236;
    if(IA>25) Es=0.018;
    if(IA>38) kf=0.241;
    if(IA>38) Es=0.028;
    if(IA>55) kf=0.241;
    if(IA>55) Es=0.023;
    if(IA>60) kf=0.245;
    if(IA>60) Es=0.028;
    // changed 5/09 
    if(IA>55) Es=0.018;

  // Pauli suppression model from Tsai RMP 46,816(74) eq.B54
  if ((QV > 2.* kf) || (IA == 1)) {
    Pauli_sup2 =1.0;
  } else {
    Pauli_sup2 = 0.75 * (QV / kf) * (1.0 - (pow((QV / kf),2))/12.);
  }
  Pauli_sup1 = Pauli_sup2;

  //G4cout << "kf, Es, Paulisup1,2: " << kf << ", " << Es << ", " << Pauli_sup1 << ", " << Pauli_sup2 << G4endl;
  
  // structure functions with off shell factors
  kappa = QV / 2. / amp;
  lam = Nu / 2. / amp;
  lamp = lam - Es / 2. / amp;
  taup = kappa*kappa - lamp*lamp;
  squigglef = sqrt(1. + pow((kf/amp),2)) -1.;

  // Very close to treshold, could have a problem
  if(1.+lamp <= 0.) return;
  if(taup * (1. + taup) <= 0.) return;

  psi =  (lam  - TAU ) / sqrt(squigglef) / sqrt((1.+lam )* TAU + kappa * sqrt(TAU * (1. + TAU)));
  psip = (lamp - taup) / sqrt(squigglef) / sqrt((1.+lamp)*taup + kappa * sqrt(taup * (1. + taup)));
  nuL = pow((TAU / kappa / kappa),2);

  // changed definition of nuT from
  // nuT = TAU / 2. / kappa**2 + tan(thr/2.)**2
  // to this, in order to separate out F1 and F2 (F1 prop. to tan2 term)
  nuT = TAU / 2. / kappa / kappa;

  GM2bar = Pauli_sup1 * (Z * GMP*GMP + avgN * GMN*GMN);
  GE2bar = Pauli_sup2 * (Z * GEP*GEP + avgN * GEN*GEN);
  //G4double W1bar = TAU * GM2bar;
  W2bar = (GE2bar + TAU * GM2bar) / (1. + TAU);

  Delta = squigglef * (1. - psi*psi) * (sqrt(TAU * (1.+TAU)) / kappa + squigglef/3. *
     (1. - psi*psi) * TAU / kappa / kappa);
  GL = kappa*kappa / TAU * (GE2bar + Delta * W2bar) / 2. / kappa / (1. + squigglef * 
     (1. + psi*psi) / 2.);
  GT = (2. * TAU * GM2bar + Delta * W2bar) / 2. / kappa / (1. + squigglef * 
     (1. + psi*psi) / 2.);

  //G4cout << "nuL, nuT, GL, GT: " << nuL << ", " << nuT << ", " << GL << ", " << GT << G4endl;

  // added to prevent negative xsections:
  if (GT < 0) {
    GT = 0;
    //G4cout << "Reset GT to zero" << G4endl;
  }

  // from Maria Barbaro: see Amaro et al., PRC71,015501(2005).
  FY = 1.5576 / (1. + 1.7720*1.7720 * pow((psip + 0.3014),2)) / (1. + exp(-2.4291 * psip)) / kf;

// == Note: Below is for deuteron and haven't == //
// == verified if code conversion is correct  == //
  // Use PWIA and Paris W.F. for deuteron to get better FY
  if (IA == 2) {
    // value assuming average p2=0.
    pz = (QSQ - 2. * amp * Nu ) / 2. / QV;
    izz = int((pz + 1.0) / 0.01) + 1;
    if (izz < 1) izz = 1;
    if (izz > 200) izz = 200;
    izznom = izz;

    // ignoring energy term, estimate change in pz to compensate
    //! for avp2 term
    dpz = avp2[izznom] / 2. / QV;
    izdif = dpz * 150.;
    dwmin=1.E6;
    izzmin=0;  

    G4int izpmax;
    if ((izznom + izdif) < 1) izpmax = 1;
    if (izpmax > 200) izpmax = 200;
    for (izp = izznom; izp <= izpmax; izp++) {
      pz = -1. + 0.01 * (izp-0.5);
      // *** this version gives worse agreement with laget than
      //         w2p = (amd + Nu - sqrt(amp**2 + avp2(izp)))**2 - 
      //    >      QV**2 + 2. * QV * pz - avp2(izp)
      // this version!
      w2p = pow((amd + Nu - amp ),2) - QV*QV + 2. * QV * pz - avp2[izp];

      // if passed first minimum, quit looking so don't find second one
      if (abs(w2p - amp*amp) > dwmin) {
        if (izzmin < 2) izzmin = 2;
        if (izzmin > 199) izzmin = 199;
        izz = izzmin;
      } else if (abs(w2p - amp*amp) < dwmin) {
          dwmin = abs(w2p - amp*amp);
          izzmin = izp;
      }
    }

    // search for minimum in 1/10th bins locally
    pznom = -1. + 0.01 * (izz-0.5);
    dwmin=1.E6;
    for (izp = 1; izp <= 19; izp++) {
      pz = pznom - 0.01 + 0.001 * izp;
      // *** this version gives worse agreement with laget than
      //        w2p = (amd + Nu - sqrt(amp**2 + avp2(izz)))**2 - 
      //   >      QV**2 + 2. * QV * pz - avp2(izz)
      // this version!
      w2p = pow((amd + Nu - amp ),2) - QV*QV + 2. * QV * pz - avp2[izz];
      if (abs(w2p - amp*amp) < dwmin) {
        dwmin = abs(w2p - amp*amp);
        pzmin = pz;
      }
    }

    if (dwmin >= 1.e6 || abs(pznom-pzmin) > 0.01) { 
      //     >     write(6,'(1x,''error in dwmin,pzmin'',3i4,6f7.3)')
      //     >     izznom,izzmin,izz,QSQ,wsq,w2p,dwmin/1.e6,pzmin,pznom
      if (pzmin < pznom) FY = fyd[izz] - (fyd[izz-1] - fyd[izz]) * (pzmin - pznom) / 0.01;
      else FY = fyd[izz] + (fyd[izz+1] - fyd[izz]) * (pzmin - pznom) / 0.01;
    }
  }
// == To here == //

  // final results
  F2 = Nu * FY * (nuL * GL + nuT * GT);
  F1 = amp * FY * GT / 2.;

  //G4cout << "nu, Fy, nuL, GL, nuT, GT, amp: " << G4endl;
  //G4cout << Nu << ", " << FY << ", " << nuL << ", " << GL << ", " << nuT << ", " << GT << ", " << amp << G4endl;

  if (F1 < 0.0) F1 = 0.;
  if (Nu > 0. && F1 > 0.) R = (F2 / Nu) / (F1 / amp) * (1. + Nu*Nu / QSQ) - 1.0;
  else R = 0.4/QSQ;


  // apply correction factors
  if ( A > 2 ) {
    y = (wsq -amp*amp) / QV;
    //         F1 = F1 * (1. + pb(8) + pb(9) * y +
    //     >        pb(10)*y**2 + pb(11)*y**3 + pb(12)*y**4 )
    //         R = R * (1. + pb(13))
    //         F2 = Nu * F1/amp * (1. + R) / (1. + Nu**2/QSQ)

    // correction to correction Vahe
    if (wsq > 0.0) {
      F1=F1*(1.0+P[7]+P[8]*y+P[9]*y*y +P[10]*pow(y,3) +P[11]*pow(y,4));
      R = R * ( 1.0 + P[12] );
      F2 = Nu * F1/amp * (1. + R) / (1. + Nu*Nu/QSQ);
      if (F1 < 0.0) F1=0.0;
    }
  }

  return;
}

void QweakSimEPEvent::F1F2IN09(G4int Z, G4int IA, G4double qsq,
                               G4double wsq, G4double &F1, G4double &F2)
{
/*--------------------------------------------------------------------
 Fit to inelastic cross sections for A(e,e')X
 valid for all W<3 GeV and all Q2<10 GeV2
 
 Inputs: Z, A (real*8) are Z and A of nucleus 
         (use Z=0., A=1. to get free neutron)
         Qsq (real*8) is 4-vector momentum transfer squared (positive in
                     chosen metric)
         Wsq (real*8) is invarinat mass squared of final state calculated
                     assuming electron scattered from a free proton
                 
 outputs: F1, F2 (real*8) are structure functions per nucleus
 Version of 10/20/2006 P. Bosted
--------------------------------------------------------------------*/

  G4double W, x;
  G4double nu,siglp,sigtp,F1pp,F1dp;
  G4double W1,W2,sigt,Rc,sigl,F1d, F1p,qv;
  G4double DW2DPF,Wsqp,pf,kf,Es,dw2des,Fyuse;
  G4double x4, emcfac;
  G4int ism;
  G4double PM = 0.93828;
                   
  // This is for exp(-xx**2/2.), from teste.f
  G4double XXp[99] = {
      -3.000,-2.939,-2.878,-2.816,-2.755,-2.694,-2.633,-2.571,-2.510,
      -2.449,-2.388,-2.327,-2.265,-2.204,-2.143,-2.082,-2.020,-1.959,
      -1.898,-1.837,-1.776,-1.714,-1.653,-1.592,-1.531,-1.469,-1.408,
      -1.347,-1.286,-1.224,-1.163,-1.102,-1.041,-0.980,-0.918,-0.857,
      -0.796,-0.735,-0.673,-0.612,-0.551,-0.490,-0.429,-0.367,-0.306,
      -0.245,-0.184,-0.122,-0.061, 0.000, 0.061, 0.122, 0.184, 0.245,
       0.306, 0.367, 0.429, 0.490, 0.551, 0.612, 0.673, 0.735, 0.796,
       0.857, 0.918, 0.980, 1.041, 1.102, 1.163, 1.224, 1.286, 1.347,
       1.408, 1.469, 1.531, 1.592, 1.653, 1.714, 1.776, 1.837, 1.898,
       1.959, 2.020, 2.082, 2.143, 2.204, 2.265, 2.327, 2.388, 2.449,
       2.510, 2.571, 2.633, 2.694, 2.755, 2.816, 2.878, 2.939, 3.000};
  // these are 100x bigger for convenience
  G4double fyp[99] = {
      0.0272,0.0326,0.0390,0.0464,0.0551,0.0651,0.0766,0.0898,0.1049,
      0.1221,0.1416,0.1636,0.1883,0.2159,0.2466,0.2807,0.3182,0.3595,
      0.4045,0.4535,0.5066,0.5637,0.6249,0.6901,0.7593,0.8324,0.9090,
      0.9890,1.0720,1.1577,1.2454,1.3349,1.4254,1.5163,1.6070,1.6968,
      1.7849,1.8705,1.9529,2.0313,2.1049,2.1731,2.2350,2.2901,2.3379,
      2.3776,2.4090,2.4317,2.4454,2.4500,2.4454,2.4317,2.4090,2.3776,
      2.3379,2.2901,2.2350,2.1731,2.1049,2.0313,1.9529,1.8705,1.7849,
      1.6968,1.6070,1.5163,1.4254,1.3349,1.2454,1.1577,1.0720,0.9890,
      0.9090,0.8324,0.7593,0.6901,0.6249,0.5637,0.5066,0.4535,0.4045,
      0.3595,0.3182,0.2807,0.2466,0.2159,0.1883,0.1636,0.1416,0.1221,
      0.1049,0.0898,0.0766,0.0651,0.0551,0.0464,0.0390,0.0326,0.0272};

  // deuteron fit parameters
  G4double xvald0[50] = {
       0.1964E+01, 0.1086E+01, 0.5313E-02, 0.1265E+01, 0.8000E+01,
       0.2979E+00, 0.1354E+00, 0.2200E+00, 0.8296E-01, 0.9578E-01,
       0.1094E+00, 0.3794E+00, 0.8122E+01, 0.5189E+01, 0.3290E+01,
       0.1870E+01, 0.6110E+01,-0.3464E+02, 0.9000E+03, 0.1717E+01,
       0.4335E-01, 0.1915E+03, 0.2232E+00, 0.2119E+01, 0.2088E+01,
      -0.3029E+00, 0.2012E+00, 0.1104E-02, 0.2276E-01,-0.4562E+00,
       0.2397E+00, 0.1204E+01, 0.2321E-01, 0.5419E+03, 0.2247E+00,
       0.2168E+01, 0.2266E+03, 0.7649E-01, 0.1457E+01, 0.1318E+00,
      -0.7534E+02, 0.1776E+00, 0.1636E+01, 0.1350E+00,-0.5596E-02,
       0.5883E-02, 0.1934E+01, 0.3800E+00, 0.3319E+01, 0.1446E+00};
       
  G4double P[24] = {
     5.1377e-03,   9.8071e-01,   4.6379e-02,   1.6433e+00,
     6.9826e+00,  -2.2655e-01,   1.1095e-01,   2.7945e-02,
     4.0643e-01,   1.6076e+00,  -7.5460e+00,   4.4418e+00,
     -3.7464e-01,   1.0414e-01,  -2.6852e-01,   9.6653e-01,
     -1.9055e+00,   9.8965e-01,   2.0613e+02,  -4.5536e-02,
     2.4902e-01,  -1.3728e-01,   2.9201e+01,   4.9280e-03};
     
  G4double F1M;
  nu = (wsq - PM*PM + qsq) / 2. / PM;
  qv = sqrt(nu*nu + qsq);

  if (wsq <= 0.0) {
    W = 0.0;
  } else {
    W  = sqrt(wsq);
    x  = qsq / (2.0 * PM * nu);
  }
  if (wsq <= 0.0) x = 0.0;
  
  if (IA <= 2) return;
  
  // For nuclei
  if (IA > 2) {
    sigt = 0.;
    sigl = 0.;
    F1d = 0.;
    F1p = 0.;
  }
  
  // Modifed to use Superscaling from Sick, Donnelly, Maieron,
  // nucl-th/0109032
  if(IA==2) kf=0.085;
  if(IA==2) Es=0.0022;
  // changed 4/09
  if(IA==3) kf=0.115;
  if(IA==3) Es=0.001 ;
  // changed 4/09
  if(IA>3) kf=0.19;
  if(IA>3) Es=0.017; 
  if(IA>7) kf=0.228;
  if(IA>7) Es=0.020;
  // changed 5/09
  if(IA>7) Es=0.0165;
  if(IA>16) kf=0.230;
  if(IA>16) Es=0.025;
  if(IA>25) kf=0.236;
  if(IA>25) Es=0.018;
  if(IA>38) kf=0.241;
  if(IA>38) Es=0.028;
  if(IA>55) kf=0.241;
  if(IA>55) Es=0.023;
  if(IA>60) kf=0.245;
  if(IA>60) Es=0.028;
  // changed 5/09 
  if(IA>55) Es=0.018;
 
  // adjust pf to give right width based on kf
  pf = 0.5 * kf;
  // assume this is 2 * pf * qv
  DW2DPF = 2. * qv;
  dw2des = 2. * (nu + PM) ;
  // switched to using 99 bins!
  for (ism = 0; ism < 99; ism++) {
    Fyuse = fyp[ism]/100.;
    Wsqp = wsq + XXp[ism] * pf * DW2DPF - Es * dw2des;
    if (Wsqp > 1.159) {
      christy507(Wsqp,qsq,F1pp,Rc,sigtp,siglp);
      resmodd(Wsqp,qsq,xvald0,F1dp);
      F1d = F1d + F1dp * Fyuse;
      F1p = F1p + F1pp * Fyuse;
      sigt = sigt + sigtp * Fyuse;
      sigl = sigl + siglp * Fyuse;
    }
  }

  Rc = 0.;
  if(sigt > 0.) Rc = sigl / sigt;
  W1 = (2. * Z * F1d + (A - 2. * Z) * (2. * F1d - F1p)) / PM;
  W1= W1*(1.0+P[13]*x+P[14]*pow(x,2)+P[15]*pow(x,3)+P[16]*pow(x,4)+P[17]*pow(x,5));
      
  if(W > 0.0) {
    W1=W1*pow((1.0+(P[20]*W+P[21]*pow(W,2))/(1.0+P[22]*qsq)),2);
    F1M = MEC2009(A,qsq,wsq);
    W1 = W1 + F1M;
    if(wsq > 0.0 ) {
      Rc = Rc * ( 1.0 + P[6] + P[23]*A );
      W2 = W1 * (1. + Rc) / (1. + nu*nu / qsq);
    }
   }

  x4 = qsq / 2. / PM / nu;
  emcfac = fitemc(x4, IA);
  F1 = PM * W1 * emcfac; 
  F2 = nu * W2 * emcfac;
  
  return;
  
}

//-----------------------------------------------------------------//
void QweakSimEPEvent::christy507(G4double w2,G4double q2,G4double &F1,
                                 G4double &R, G4double &sigT, G4double &sigL)
{
//   M.E. Christy and P.E. Bosted, ``Empirical Fit to Precision 
//    Inclusive Electron-Proton Cross Sections in the Resonance Region'',
//    (arXiv:0712.3731). To be submitted to Phys. Rev. C.

  G4double xval1[50],xvalL[50];

  G4double mp = .9382727;
  G4double mp2 = mp*mp;
  G4double pi = 3.141593;
  G4double alpha = 1./137.036;

  G4double xval[100] = {
      0.12298E+01,0.15304E+01,0.15057E+01,0.16980E+01,0.16650E+01,
      0.14333E+01,0.13573E+00,0.22000E+00,0.82956E-01,0.95782E-01,
      0.10936E+00,0.37944E+00,0.77805E+01,0.42291E+01,0.12598E+01,
      0.21242E+01,0.63351E+01,0.68232E+04,0.33521E+05,0.25686E+01,
      0.60347E+00,0.21240E+02,0.55746E-01,0.24886E+01,0.23305E+01,
      -.28789E+00,0.18607E+00,0.63534E-01,0.19790E+01,-.56175E+00,
      0.38964E+00,0.54883E+00,0.22506E-01,0.46213E+03,0.19221E+00,
      0.19141E+01,0.24606E+03,0.67469E-01,0.13501E+01,0.12054E+00,
      -.89360E+02,0.20977E+00,0.15715E+01,0.90736E-01,-.38495E-02,
      0.10362E-01,0.19341E+01,0.38000E+00,0.34187E+01,0.14462E+00,
      0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,
      0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,0.00000E+00,
      0.00000E+00,0.00000E+00,0.29414E+02,0.19910E+02,0.22587E+00,
      0.00000E+00,0.00000E+00,0.38565E+04,0.65717E+00,0.00000E+00,
      0.15792E+03,0.97046E+02,0.31042E+00,0.00000E+00,0.42160E+01,
      0.38200E-01,0.12182E+01,0.00000E+00,0.13764E+02,0.31393E+00,
      0.29997E+01,0.00000E+00,0.55124E+01,0.53743E-01,0.13091E+01,
      0.00000E+00,0.86746E+02,0.40864E-04,0.40294E+01,0.31285E+01,
      0.33403E+00,0.49623E+01,0.00000E+00,0.00000E+00,0.11000E+02,
      0.18951E+01,0.51376E+00,0.00000E+00,0.42802E+01,0.00000E+00};

  for (G4int i = 0; i<50; i++) {
    xval1[i] = xval[i];
    xvalL[i] = xval[50+i] ;
    if(i < 12) xvalL[i] = xval1[i];
  }
  xvalL[42] = xval1[46];
  xvalL[43] = xval1[47];
  xvalL[49] = xval1[49];

  G4double xb = q2/(w2+q2-mp2);
  sigT = resmod507_v2(1,w2,q2,xval1);
  sigL = resmod507_v2(2,w2,q2,xvalL);

  F1 = sigT*(w2-mp2)/8./pi/pi/alpha/0.3894e3;
  //G4double FL = sigL*2.*xb*(w2-mp2)/8./pi/pi/alpha/0.3894e3;
  R = sigL/sigT;

  return;
}

// -------------------------------------------------------------------------//
void QweakSimEPEvent::resmodd(G4double w2, G4double q2, 
                             G4double xval[50], G4double &sig)
{
  //! returns F1 for average of free proton and neutron
  //! for given W2, Q2

  G4double W,mp,mp2,mass[7],width[7];
  G4double height[7],rescoef[6][4];
  G4double nr_coef[3][4],sigr[5000][7],wdif,sig_nr;
  G4double mpi,meta,intwidth[7],k,kcm,kr[7],kcmr[7],ppicm,ppi2cm;
  G4double petacm,ppicmr[7],ppi2cmr[7],petacmr[7],epicmr[7],epi2cmr[7];
  G4double eetacmr[7],epicm,epi2cm,eetacm,br[7][2],ang[7],sigrsv[7];
  G4double pgam[7],pwid[7][2],x0[7],dip;
  G4double sig_res,xpr,alpha,pi,F1;
  G4int i,j,num,iw;
  
  G4double xval0[12] = {
     0.12298E+01,0.15304E+01,0.15057E+01,0.16980E+01,0.16650E+01,
     0.14333E+01,0.13573E+00,0.22000E+00,0.82956E-01,0.95782E-01,
     0.10936E+00,0.37944E+00};
 
  G4double xvalold[50],w2sv;
  G4bool first = true;
  
  mp = 0.9382727;
  mpi = 0.135;
  meta = 0.547;
  mp2 = mp*mp;
  pi = 3.141593;
  alpha = 1./137.036;

  sig = 0.;

  if(w2 < 1.07327*1.07327 || w2 > 25 || q2 < 0.0 || q2 > 11.0) return;

  // do this if fitting masses or widths, else set first true in above
  first = false;
  if (xvalold[0] != xval[0] || xvalold[6] != xval[6]) first = true;
  xvalold[0]=xval[0];
  xvalold[6]=xval[6];

  if (first) {

    // ! branching ratios
    br[0][0] = 1.0;     
    br[1][0] = 0.5;
    br[2][0] = 0.65;
    br[3][0] = 0.65;
    br[4][0] = 0.4;
    br[5][0] = 0.65;
    br[6][0] = 0.6;

    // ! angular momenta
    ang[0] = 1.;      // !!!  P33(1232)
    ang[1] = 0.;      // !!!  S11(1535)
    ang[2] = 2.;      // !!!  D13(1520)
    ang[3] = 3.;      // !!!  F15(1680)
    ang[4] = 0.;      // !!!  S15(1650)
    ang[5] = 1.;      // !!!  P11(1440) roper   
    ang[6] = 3.;      // !!!  ? 4th resonance region

    // ! x0 parameter
    for (i = 0; i < 7; i++) {
      x0[i] = 0.215;
    }
    x0[0] = 0.1446;

    // ! out branching ratio
    for (i = 0; i < 7; i++) {
      br[i][1] = 1.-br[i][0];
    }
    
    // ! remember w2
    w2sv = w2;

    // ! uses xvals of 1-12, 47, and 48
    // ! move masses, wdiths into local variables
    // ! pyb changed to be fixed
    num = 0;
    for (i = 0; i < 6; i++) {
      num = num + 1;
      mass[i] = xval0[i];
    }
    for (i = 0; i < 6; i++) {          
      num = num + 1;
      intwidth[i] = xval0[num-1];
    }
    //! changed to allow delta width, mass to vary
    //! taken out again since xval[1] used in MEC
    mass[6] = 1.9341;
    intwidth[6] = 0.380;

    // ! precalculate w-dependent quantites in 0.1 MeV bins
    for (iw = 1073; iw <= 5000; iw++) {
      W = 0.001 * (iw+0.5);
      w2 = W*W;
      wdif = W - (mp + mpi);

      // ! Calculate kinematics needed for threshold Relativistic B-W 
      k = (w2 - mp2) / 2. / mp;
      kcm = (w2 - mp2) / 2. / W;
      epicm = (w2 + mpi*mpi -mp2 ) / 2. / W;
      ppicm = pow(std::max(0.0,(epicm*epicm - mpi*mpi)),0.5);
      epi2cm = (w2 + pow((2.*mpi),2) -mp2 ) / 2. / W;
      ppi2cm = pow(std::max(0.0,(epi2cm*epi2cm - pow((2.*mpi),2))),0.5);
      eetacm = (w2 + meta*meta -mp2 ) / 2. / W;
      petacm =  pow(std::max(0.0,(eetacm*eetacm - meta*meta)),0.5);
      for (i = 0; i < 7; i++) {
        kr[i] = (mass[i]*mass[i]-mp2)/2./mp;
        kcmr[i] = (mass[i]*mass[i]-mp2)/2./mass[i];
        epicmr[i] = (mass[i]*mass[i] + mpi*mpi -mp2 )/2./mass[i];
        ppicmr[i] = pow(std::max(0.0,(epicmr[i]*epicmr[i] - mpi*mpi)),0.5);
        epi2cmr[i] = (mass[i]*mass[i] + pow(2.*mpi,2) -mp2 )/2./mass[i];
        ppi2cmr[i] = pow(std::max(0.0,(epi2cmr[i]*epi2cmr[i] - pow((2.*mpi),2))),0.5);
        eetacmr[i] = (mass[i]*mass[i] + meta*meta -mp2 )/2./mass[i];
        petacmr[i] =  pow(std::max(0.0,(eetacmr[i]*eetacmr[i] - meta*meta)),0.5);
        
        // ! Calculate partial widths
        pwid[i][0] = intwidth[i]*pow((ppicm/ppicmr[i]),(2.*ang[i]+1.))*pow(((ppicmr[i]*ppicmr[i]+x0[i]*x0[i])/(ppicm*ppicm+x0[i]*x0[i])),ang[i]);
        
        if(i != 1) {
          pwid[i][1] = intwidth[i]*pow((ppi2cm/ppi2cmr[i]),(2.*ang[i]+4.))*pow(((ppi2cmr[i]*ppi2cmr[i]+x0[i]*x0[i])/(ppi2cm*ppi2cm+x0[i]*x0[i])),(ang[i]+2.))* W / mass[i];
        } else {
          pwid[i][1] =  intwidth[1]*pow((petacm/petacmr[i]),(2.*ang[i]+1.))*pow(((petacmr[i]*petacmr[i]+x0[i]*x0[i])/(petacm*petacm+x0[i]*x0[i])),ang[i]);
        }
        
        pgam[i] = pow((kcm/kcmr[i]),2)*(kcmr[i]*kcmr[i]+x0[i]*x0[i])/(kcm*kcm+x0[i]*x0[i]);
        pgam[i] = intwidth[i]*pgam[i];
        width[i] = br[i][0]*pwid[i][0]+br[i][1]*pwid[i][1];
        sigr[iw][i] = width[i] * pgam[i] / (pow(w2 - mass[i]*mass[i],2) + pow(mass[i]*width[i],2)) * kr[i] / k * kcmr[i] / kcm / intwidth[i];
      }
    }
    w2 = w2sv;
    first = false;
    for (i = 0; i < 50; i++) {
      xvalold[i] = xval[i];
    }
    
  }

  // ! get parameters into local variables
  num = 12;
  //! resonance height coefficients. xvals of 13-36
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 4; j++) {
      num = num + 1;
      rescoef[i][j]=xval[num-1];
    }
  }
  // !  Non-Res coefficients xvals of 37-44
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 4; j++) {
      num = num + 1;
      nr_coef[i][j]=xval[num-1];
    }
  }

  // ! Begin resonance Q^2 dependence calculations   CCC
  // ! uses xvals 49
  for (i = 0; i < 6; i++) {
    height[i] = rescoef[i][0]*(1.+rescoef[i][1] * q2 / (1. + rescoef[i][2] * q2))/pow((1. + q2/0.91),rescoef[i][3]);
  }
  dip = 1./pow((1. + q2 / 0.91),2);
  height[6] = xval[48]*dip;
  iw = G4int(1000.*pow(w2,0.5));
  sig_res = 0.;
      
  for (i = 0; i < 7; i++) { 
    sigrsv[i] =  height[i]*height[i] * sigr[iw][i];
    sig_res = sig_res + sigrsv[i];
  }

  sig_res = sig_res * pow(w2,0.5);

  //! Begin non-resonant part uses xvals 45, 46, 50
  //! Depends on both W2 and Q2 so can't easily precalculate
  sig_nr = 0.;
  xpr = 1.+(w2-pow(mp+mpi,2))/(q2+0.05);
  xpr = 1./xpr;
  W = pow(w2,0.5);
  wdif = W - (mp + mpi);
  for (i = 0; i < 2; i++) {
    sig_nr = sig_nr +(nr_coef[i][0]*pow(wdif,((2*(i+1)+1)/2.)))/pow(q2+nr_coef[i][1],(nr_coef[i][2]+nr_coef[i][3]*q2+xval[44+i]*q2*q2));
  }
  sig_nr = sig_nr * xpr;
  sig = sig_res + sig_nr;

  // ! changed to use F1 instead of sigt
  F1 = sig * (w2-mp2)/8./pi/pi/alpha/0.3894e3;
  sig = F1;

  return;
}

//------------------------------------------------------------------//
// Used for Aluminum inelastic...
G4double QweakSimEPEvent::resmod507_v2(G4double sf,G4double w2,
                                   G4double q2,G4double xval[50]) 
{

  G4double W,mp,mp2,xb;
  G4double mass[7] = {0,0,0,0,0,0,0};
  G4double width[7] = {0,0,0,0,0,0,0};
  G4double height[7] = {0,0,0,0,0,0,0};
  G4double intwidth[7] = {0,0,0,0,0,0,0};
  G4double rescoef[6][4];
  G4double nr_coef[3][4],sigr[7],wdif[2],sig_nr,h_nr[3];
  G4double mpi,meta,k,kcm,kr[7],kcmr[7],ppicm,ppi2cm;
  G4double petacm,ppicmr[7],ppi2cmr[7],petacmr[7],epicmr[7],epi2cmr[7];
  G4double eetacmr[7],epicm,epi2cm,eetacm,br[7][3],ang[7];
  G4double pgam[7],pwid[7][3],x0[7],q20;
  G4double sig_res,t,xpr[2],m0,sig;
  G4int i,j,num;
  
  mp = 0.9382727;
  mpi = 0.135;
  meta = 0.547;
  mp2 = mp*mp;
  W = sqrt(w2);
  wdif[0] = W - (mp + mpi);
  wdif[1] = W - (mp + 2.*mpi);

  m0 = 0.125;
  if(sf == 2) m0 = xval[48];
  if(sf == 1) {
    q20 = 0.05;
  } else {
    q20 = 0.125;
  }

  // single pion branching ratios  CCCC

  br[0][0] = 1.0;       //!!!  P33(1232)       
  br[1][0] = 0.45;      //!!!  S11(1535)   
  br[2][0] = 0.65;      //!!!  D13(1520)
  br[3][0] = 0.65;      //!!!  F15(1680)
  br[4][0] = 0.4;       //!!!  S11(1650)
  br[5][0] = 0.65;      //!!!  P11(1440) roper 
  br[6][0] = 0.50 ;     //!!!  F37(1950)

  br[0][2] = 0.0;       //!!!  P33(1232)
  br[1][2] = 0.45;      //!!!  S11(1535) 
  br[2][2] = 0.0;       //!!!  D13(1520)
  br[3][2] = 0.0;       //!!!  F15(1680)
  br[4][2] = 0.1;       //!!!  S11(1650)
  br[5][2] = 0.0;       //!!!  P11(1440) roper   
  br[6][2] = 0.0;       //!!!  F37(1950)

  // 2-pion branching ratios  CCCC

  for (i = 0; i < 7; i++) {
    br[i][1] = 1.-br[i][0]-br[i][2];
  }

  // Meson angular momentum   CCCC
  ang[0] = 1.;       //!!!  P33(1232)
  ang[1] = 0.;       //!!!  S11(1535)
  ang[2] = 2.;       //!!!  D13(1520)
  ang[3] = 3.;       //!!!  F15(1680)
  ang[4] = 0.;       //!!!  S15(1650)
  ang[5] = 1.;       //!!!  P11(1440) roper   
  ang[6] = 3.;       //!!!  F37(1950)

  for (i = 0; i < 7; i++) { //!!!  resonance damping parameter  !!!
    x0[i] = 0.215;
  }
  x0[0] = 0.15;
  x0[0] = xval[49];   

  xb = q2/(q2+w2-mp2);
  xpr[0] = 1.+(w2-pow((mp+mpi),2))/(q2+q20);
  xpr[0] = 1./xpr[0];
  xpr[1] = 1.+(w2-pow((mp+mpi+mpi),2))/(q2+q20);
  xpr[1] = 1./xpr[1];

  t = log(log((q2+m0)/0.330/0.330)/log(m0/0.330/0.330));

  // Calculate kinematics needed for threshold Relativistic B-W

  k = (w2 - mp2)/2./mp;
  kcm = (w2-mp2)/2./W;

  epicm = (w2 + mpi*mpi -mp2 )/2./W;
  ppicm = pow(std::max(0.0,(epicm*epicm - mpi*mpi)),0.5);
  epi2cm = (w2 + pow((2.*mpi),2) -mp2 )/2./W;
  ppi2cm = pow(std::max(0.0,(epi2cm*epi2cm - pow((2.*mpi),2))),0.5);
  eetacm = (w2 + meta*meta -mp2 )/2./W;
  petacm =  pow(std::max(0.0,(eetacm*eetacm - meta*meta)),0.5);

  num = 0;

  for (i = 0; i < 6; i++) { // !!!  Read in resonance masses     !!!
    num = num + 1;
    mass[i] = xval[i];
  }
  for (i = 0; i < 6; i++) { // !!!  Read in resonance widths     !!!
    num = num + 1;
    intwidth[i] = xval[num-1];
    width[i] = intwidth[i];
  }
  if (sf == 2) { //      !!!  Put in 4th resonance region  !!!
    mass[6] = xval[42];
    intwidth[6] = xval[43];
    width[6] = intwidth[6];
  } else {
    mass[6] = xval[46];
    intwidth[6] = xval[47];
    width[6] = intwidth[6];
  }

  for (i = 0; i < 7; i++) {
    kr[i] = (mass[i]*mass[i]-mp2)/2./mp;
    kcmr[i] = (mass[i]*mass[i]-mp2)/2./mass[i];
    epicmr[i] = (mass[i]*mass[i] + mpi*mpi -mp2 )/2./mass[i];
    ppicmr[i] = pow(std::max(0.0,(epicmr[i]*epicmr[i] - mpi*mpi)),0.5);
    epi2cmr[i] = (mass[i]*mass[i] + pow((2.*mpi),2) -mp2 )/2./mass[i];
    ppi2cmr[i] = pow(std::max(0.0,(epi2cmr[i]*epi2cmr[i] - pow((2.*mpi),2))),0.5);
    eetacmr[i] = (mass[i]*mass[i] + meta*meta -mp2 )/2./mass[i];
    petacmr[i] =  pow(std::max(0.0,(eetacmr[i]*eetacmr[i] - meta*meta)),0.5);

    // CCC   Calculate partial widths   CCC

    pwid[i][0] = intwidth[i]*pow((ppicm/ppicmr[i]),(2.*ang[i]+1.))*pow(((ppicmr[i]*ppicmr[i]+x0[i]*x0[i])/(ppicm*ppicm+x0[i]*x0[i])),ang[i]); //      !!!  1-pion decay mode

    pwid[i][1] = intwidth[i]*pow((ppi2cm/ppi2cmr[i]),(2.*ang[i]+4.))*pow(((ppi2cmr[i]*ppi2cmr[i]+x0[i]*x0[i])/(ppi2cm*ppi2cm+x0[i]*x0[i])),(ang[i]+2)); //  !!!  2-pion decay mode

    pwid[i][1] = W/mass[i]*pwid[i][1];
    pwid[i][2] = 0.; //          !!!  eta decay mode

    if(i == 1 || i == 4) {
      pwid[i][2] =  intwidth[i]*pow((petacm/petacmr[i]),(2.*ang[i]+1.))*pow(((petacmr[i]*petacmr[i]+x0[i]*x0[i])/(petacm*petacm+x0[i]*x0[i])),ang[i]); // !!!  eta decay only for S11's 
    }

    pgam[i] = pow((kcm/kcmr[i]),2)*(pow(kcmr[i],2)+x0[i]*x0[i])/(kcm*kcm+x0[i]*x0[i]);
    pgam[i] = intwidth[i]*pgam[i];
    width[i] = br[i][0]*pwid[i][0]+br[i][1]*pwid[i][1]+br[i][2]*pwid[i][2];
  }

  //CCC    End resonance kinematics and Widths calculations   CCC

  // CCC    Begin resonance Q^2 dependence calculations   CCC
           
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 4; j++) {
      num = num + 1;
      rescoef[i][j]=xval[num-1];
    }

    if(sf == 1) {
      height[i] = rescoef[i][0]*(1.+rescoef[i][1]*q2/(1.+rescoef[i][2]*q2))/pow((1.+q2/0.91),rescoef[i][3]);
    } else {
      height[i] = rescoef[i][0]*q2/(1.+rescoef[i][1]*q2)*exp(-1.*rescoef[i][2]*q2);
    }

    height[i] = height[i]*height[i];
  }

  if(sf == 2) { // !!!  4th resonance region  !!!
    height[6] = xval[44]*q2/(1.+xval[45]*q2)*exp(-1.*xval[46]*q2);
  } else {
    height[6] = xval[48]/(1.+q2/0.91);
  }
  
  height[6] = height[6]*height[6];

  // CCC    End resonance Q^2 dependence calculations   CCC

  for (i = 0; i < 3; i++) { // !!!  Non-Res coefficients  !!!
    for (j = 0; j < 4; j++) {
      num = num + 1;
      nr_coef[i][j]=xval[num-1];
    }
  }

  // CCC   Calculate Breit-Wigners for all resonances   CCC

  sig_res = 0.0;
  for (i = 0; i < 7; i++) {
    sigr[i] = width[i]*pgam[i]/(pow(w2 - mass[i]*mass[i],2.) + pow(mass[i]*width[i],2.));
    sigr[i] = height[i]*kr[i]/k*kcmr[i]/kcm*sigr[i]/intwidth[i];
    sig_res = sig_res + sigr[i];
  }
  sig_res = sig_res*W;
  // CCC    Finish resonances / start non-res background calculation   CCC
  sig_nr = 0.;
  if(sf == 1) {
    for (i = 0; i < 2; i++) {
      h_nr[i] = nr_coef[i][0]/pow(q2+nr_coef[i][1],nr_coef[i][2] + nr_coef[i][3]*q2+xval[44+i]*q2*q2);
      sig_nr = sig_nr +h_nr[i]*(pow(wdif[0],(2*(i+1)+1)/2.));
    }

    sig_nr = sig_nr*xpr[0];
    
  } else if (sf == 2) {
    for (i = 0; i < 1; i++) {
      sig_nr = sig_nr + nr_coef[i][0]*pow((1.-xpr[i]),(nr_coef[i][2]+nr_coef[i][1]*t))/(1.-xb)/(q2+q20);
      sig_nr = sig_nr*pow(q2/(q2+q20),nr_coef[i][3])*pow(xpr[i],(xval[40]+xval[41]*t));
    }
  }
  sig = sig_res + sig_nr;

  return sig;
}

G4double QweakSimEPEvent::MEC2009(G4int a, G4double q2,G4double w2)
{
  //! fit to low q2 dip region: purefly empirical
  //! assume contribution is pure transverse
  G4double f1 = 0.0;
  G4double am = 0.9383;
  G4double w,nu;

  G4double P[24] = {
     5.1377e-03,   9.8071e-01,   4.6379e-02,   1.6433e+00,
     6.9826e+00,  -2.2655e-01,   1.1095e-01,   2.7945e-02,
     4.0643e-01,   1.6076e+00,  -7.5460e+00,   4.4418e+00,
     -3.7464e-01,   1.0414e-01,  -2.6852e-01,   9.6653e-01,
     -1.9055e+00,   9.8965e-01,   2.0613e+02,  -4.5536e-02,
     2.4902e-01,  -1.3728e-01,   2.9201e+01,   4.9280e-03};
 
  G4double p18, x, f1corr;

  if (w2 <= 0.0) return 0;
  w  = pow(w2,0.5);
  nu = (w2 - am*am + q2) / 2. / am;
  x  = q2 / (2.0 * am * nu );

  if (a < 2.5) return 0;

  p18 = P[18];
  // ! special case for 3He
  if (a > 2.5 && a < 3.5) p18 = 70;
  // ! special case for 4He
  if (a > 3.5 && a < 4.5) p18 = 170;
  // ! new values for C, Al, Cu
  if(a > 4.5) p18 = 215;
  if(a > 20.) p18 = 235;
  if(a > 50.) p18 = 230;

       
  f1corr = P[0]*exp(-pow(w-P[1],2)/P[2])/(pow(1.0 + std::max(0.3,q2)/P[3],P[4]))*pow(nu,P[5])*(1.0 + p18 * pow(A,(1.0 + P[19] * x)));

  f1 = f1corr;

  if (f1 <= 1.0E-9 ) f1 = 0.0;

  return f1;
}

G4double QweakSimEPEvent::fitemc(G4double X, G4int A)       
{
  /*!---------------------------------------------------------------------  
    ! Fit to EMC effect.  Steve Rock 8/3/94                                 
    ! Funciton returns value of sigma(A)/sigma(d) 
    ! with no isoscalerity correction
    ! A= atomic number                                                      
    ! x = Bjorken x.                                                        
    !                                                                       
    ! Fit of sigma(A)/sigma(d) to form C*A**alpha where A is atomic number  
    ! First data at each x was fit to form C*A**alpha.  The point A=2(d)    
    !  was includded with a value of 1 and an error of about 2%.             
    ! For x>=.125 Javier Gomez fit of 7/93 to E139 data was used.           
    ! For .09 >=x>=.0085 NMC data from Amaudruz et al Z. Phys C. 51,387(91) 
    !  Steve did the fit for alpha and C to the He/d. C/d and Ca/d NMC data.
    ! Alpha(x) was fit to a 9 term polynomial a0 +a1*x +a2*x**2 + a3*x**3 ..
    ! C(x) was fit to a 3 term polynomial in natural logs as                
    !  Ln(C) = c0 + c1*Ln(x) + c2*[Ln(x)]**2.                               
    
    ! 6/2/98 *****  Bug (which set x= .00885 if x was out of range) fixed
    !                    also gave value at x=.0085 if x>.88
    ! 11/05 PYB PEB modified to use value at x=0.7 if x>0.7, because
    !    beyond that assume Fermi motion is giving the rise, and we
    !    already are taking that into account with the y-smearing of
    !    the inelastic
    !-----------------------------------------------------------------------
  */
  G4double ALPHA,C,LN_C,X_U;
  G4double fitval;

  // !Chisq=         19.   for 30 points
  // !Term    Coeficient
  G4double ALPHA_COEF[9] = {
     -6.98871401E-02,
      2.18888887E+00,
     -2.46673765E+01,
      1.45290967E+02,
     -4.97236711E+02,
      1.01312929E+03,
     -1.20839250E+03,
      7.75766802E+02,
     -2.05872410E+02};

  // !Chisq=         22.    for 30 points                                   
  // !Term    Coeficient                             
  G4double C_COEF[3] = {
     1.69029097E-02,
     1.80889367E-02,
     5.04268396E-03};

  fitval = 1.;
  if (A < 2.5) return 0;

  if ( (X > 0.70) || (X < 0.0085) ) {
    // !Out of range of fit   
    if (X < 0.0085) X_U =.0085;
    if (X > 0.70) X_U = 0.70;
  } else {
    X_U = X;
  }

  LN_C = C_COEF[0];
  for (G4int i = 1; i <= 2; i++) {
    LN_C = LN_C + C_COEF[i] * pow(log(X_U),i);
  }

  C = exp(LN_C);

  ALPHA = ALPHA_COEF[0];
  for (G4int i = 1; i <= 8; i++) {
    ALPHA = ALPHA + ALPHA_COEF[i] * pow(X_U,i);
  }

  fitval = C*pow(A,ALPHA);
  return fitval;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double QweakSimEPEvent::AlloyScattering(G4double E_in, //MeV
                                          G4double Theta,
                                          G4int Zin, 
                                          G4int Ain,
                                          G4double &fWeightN,
                                          G4double &Q2,
                                          G4double &E_out)
{
  G4double M_p = 938.2796;
  G4double mm = M_p*Ain;
  
  G4double STH = sin(Theta/2.);
  G4double CTH = cos(Theta/2.);

  E_out = E_in/(1+2*E_in/mm*STH*STH);
  Q2 = 4.*E_in*E_out*STH*STH; // MeV^2


  // Mott cross section
  G4double sigMott = pow(Zin*0.719982/E_in*CTH/(STH*STH),2);
  sigMott = sigMott/(1+2*E_in/mm*STH*STH)*10000;
  
  // Form factor
  G4int NUC_MODEL = 1; // USE Fourier-Bessel if available
  G4bool OUT_OF_RANGE = 0;
  //G4double eng = E_in/1e-3; // GeV // unused
  G4double qsq = Q2/1e6; // GeV^2
  M_p = M_p/1e-3;
  
  G4double FF = 1;
  
  if (Ain < 3) {
    G4cout << "** No generator fo A < 3 ** " << G4endl;
    return 0;
  } 
  else if (Ain >= 3) {
    OUT_OF_RANGE = 0;
    if (NUC_MODEL == 1) {
      FF = FF_BESSEL(Zin,Ain,qsq,OUT_OF_RANGE);// !only for some Nuclei,feor limited Q2
    }
    if (OUT_OF_RANGE || (NUC_MODEL == 0)) { //!use if FF_BESSEL out of range
      if (Ain == 3) { // !3HE  ! added 5/30/96  SER
        G4cout << "** No generator for He3 **" << G4endl;
        return 0;
      }
      else if (Ain <= 20) {
        FF  = Fshell(Zin,Ain,qsq);
      }
      else { //    !ia >20
        FF  = Fgauss(Zin,Ain,qsq);
      }
    }
  }

  G4double xsec = sigMott*FF*FF;
  fWeightN = xsec*sin(Theta);
  
  return xsec;
}

G4double QweakSimEPEvent::Fgauss(G4int /* iZ */ /* unused */, G4int iA, G4double T)
{
  //  cout << "** Calling Fgauss **" << endl;

  G4double fgauss = 0.;

  G4double avgA = iA;
  G4double radius = 1.07*pow(avgA,1./3.);  

  //! from H. de Vries: Nuclear Charge Density Distributions from Elastic Electron
  //!   Scattering. in Atomic Data and Nuclear Data Tables 36, 495(1987)
  //! 8/9/96
  if(iA==205)radius=5.470;
  if(iA==56) radius=3.729;    
  if(iA==28) radius=3.085;
  if(iA==27) radius=3.035;
  if(iA==24) radius=3.08;// Mg-24

  G4double x2     = (T/pow(.197328,2))*pow(radius,2);
  G4double CHARR   = (T/pow(.197328,2))*(2.4*2.4)/6.;

  //cout << "  T (Q^2), CHARR: " << T << ", " << CHARR << endl;
  //  cout << "** Fgauss CHARR:: " << CHARR << endl;
  if (CHARR<80) fgauss = exp(-CHARR)/(1.+x2/6.);
  
  return fgauss;
}

G4double QweakSimEPEvent::Fshell(G4int iZ, G4int iA, G4double T)
{
  //  cout << "** Calling Fshell **" << endl;

  G4double fshell = 0.;
  G4double avgA = iA;
  G4double radius = 1.07*pow(avgA,1./3.);
  //! from H. de Vries: Nuclear Charge Density Distributions from Elastic Electron
  //!   Scattering. in Atomic Data and Nuclear Data Tables 36, 495(1987)
  //!8/9/96
  if(iA==16) radius=2.737;
  if(iA==15) radius=2.611;
  if(iA==14) radius=2.540;
  if(iA==12) radius=2.464;
  if(iA== 9) radius=2.519;
  if(iA== 7) radius=2.39;
  if(iA== 6) radius=2.56;
  if(iA== 4) radius=1.676;
  G4double x2     = (T/pow(.197328,2))*pow(radius,2);
  G4double alp    = (iZ-2.)/3.;
  G4double CHARR   = x2*(2.+3.*alp)/(12.+30.*alp);

  //  cout << "** Fshell CHARR:: " << CHARR << endl;
  if (CHARR<80) fshell = exp(-CHARR)*(1.-alp*x2/(6.+15.*alp));

  return fshell;
}

G4double QweakSimEPEvent::FF_BESSEL (G4int iZ, G4int iA, 
                                     G4double T, G4bool &OUT_OF_RANGE)
{

  //  cout << "** Calling FF_BESSEL **" << endl;
  //C   Calculates PWBA form factor  for Si-28 or O-16 using 
  //C   Fourier-Bessel coefficients given by H. de Vries et al., 
  //C   Atomic Data and Nuclear Data Tables (1986).
  //C
  //C   Note: Other nuclides can be entered, but at this time this
  //C        is only good for 
  //C       He-3, C-12, N-15, O-16, Al-27, Si-28, Fe-56, Cu-65, Zn-64, Cr-52
  //!----------------------------------------------------------------
  //!3/28/03 Corrected for divide 0/0 when qm =0  - Steve Rock

  G4double a[20];
  //C
  //C     de Vries, de Vries & de Jager FB coefficients:

  //!3He
 G4double a3[] = {0.20020E-01, 0.41934E-01, 0.36254E-01, 0.17941E-01,
          0.46608E-02, 0.46834E-02, 0.52042E-02, 0.38280E-02,
          0.25661E-02, 0.14182E-02, 0.61390E-03, 0.22929E-03};
  //!12C
  G4double a12[] = {0.15721E-01, 0.38732E-01, 0.36808E-01, 0.14671E-01,
           -0.43277E-02,-0.97752E-02,-0.68908E-02,-0.27631E-02,
           -0.63568E-03, 0.71809E-04, 0.18441E-03, 0.75066E-04,
           0.51069E-04, 0.14308E-04, 0.23170E-05, 0.68465E-06};
  //!15N7
  G4double a15[] = {0.25491E-01, 0.50618E-01, 0.29822E-01, -0.55196E-02,
           -0.15913E-01,-0.76184E-02, -.23992E-02, -0.47940E-03};

  //!16 O8
  G4double a16[] = {0.20238E-01, 0.44793E-01, 0.33533E-01, 0.35030E-02,
           -0.12293E-01,-0.10329E-01,-0.34036E-02,-0.41627E-03,
           -0.94435E-03,-0.25571E-03, 0.23759E-03,-0.10603E-03,
           0.41480E-04, 0.00000E-03};
  //!27Al
  G4double a27[] = {0.43418E-01, 0.60298E-01,  0.28950E-02, -0.23522E-01,
           -0.79791E-02, 0.23010E-02,  0.10794E-02,  0.12574E-03,
           -0.13021E-03, 0.56563E-04, -0.18011E-04,  0.42869E-05};

  //!28Si
  G4double a28[] = {0.33495E-01, 0.59533E-01, 0.20979E-01,-0.16900E-01,
           -0.14998E-01,-0.93248E-03, 0.33266E-02, 0.59244E-03,
           -0.40013E-03, 0.12242E-03,-0.12994E-04,-0.92784E-05,
           0.72595E-05,-0.42096E-05};
  //!52Cr24
  G4double a52[] = {0.39287e-1,0.62477e-1,0.62482e-2,-0.32885e-1,
           -0.10648e-1,0.10520e-1,0.85478e-2,-0.24003e-3,-0.20499e-2,
           -0.12001e-2,-0.56649e-3};
  //!56Fe26
  G4double a56[] = {0.42018E-1, 0.62337E-1, 0.23995e-3,-0.32776E-1,-0.79941E-2,
           0.10844E-1, 0.49123e-2,-0.22144e-2,-0.18146E-3,0.37261E-3,
           -0.23296E-3,0.11494E-3,-0.50596E-4, 0.20652E-4,-0.79428E-5,
           0.28986E-5,-0.10075E-5};
  //!64Zn30
  G4double a64[] = {0.47038E-01, 0.61536E-01, -0.90045E-02, -0.30669E-01,
                -0.78705E-03, 0.10034E-01, 0.14053E-02, -0.20640E-02,
                0.35105E-03, 0.27303E-04, -0.63811E-04, 0.40893E-04, 
                -0.20311E-04, 0.88986E-05, -0.35849E-05, 0.13522E-05,
                -0.38635E-06};
  //!65Cu29
  G4double a65[] = {0.45444E-01, 0.59544E-01, -0.94968E-02, -0.31561e-01,
                0.22898E-03, 0.11189E-01, 0.37360E-02, -0.64873E-03,
                -0.51133E-03, 0.43765E-03, -0.24276E-03, 0.11507E-03,
                -0.49761E-04, 0.20140E-04, -0.76945E-05, 0.28055E-05,
                -0.97411E-06};
  //!196Pt78
  G4double a196[] = 
    {0.50218e-1,  0.53722e-1, -0.35015e-1, -0.34588e-1, 0.23564e-1,
     0.14340e-1, -0.13270e-1, -0.51212e-2,  0.56088e-2, 0.14890e-2,
     -0.10928e-2, 0.55662e-3, -0.50557e-4, -0.19708e-3, 0.24016e-3};
  //////

  //C   Change to units of fm**(-1)
  G4double qq = sqrt ( T ) / 0.197328; // used to be q

  //  cout << "q(1/fm):: " << qq << endl;

  G4double ff_bessel=0;

  if( qq <= 0.005 ){
    OUT_OF_RANGE=false; //! line added 4/29/98
    ff_bessel = 1.00000;
    return 0;
  }

  ff_bessel=0.0;
  OUT_OF_RANGE=false;
  Float_t R_max=0.;
  G4int n=0;

  if(iA == 28){ // 28Si
    if(qq>2.64)  OUT_OF_RANGE=true;
    //if(qq<0.25)  OUT_OF_RANGE=true;
    R_max = 8.;
    n = 14;
    for(G4int i=0;i<n;i++)
      a[i] = a28[i];
  }
  else if(iA == 16){ // 16O
    if(qq>2.77) OUT_OF_RANGE=true;
    R_max=8.;
    n = 13;
    for(G4int i=0;i<n;i++)
      a[i] = a16[i];
  }
  else if(iA == 3){ // 3He
    if(qq>10. ) OUT_OF_RANGE=true;
    R_max=5.;
    n = 12;
    for(G4int i=0;i<n;i++)
      a[i] = a3[i];
  }
  else if(iA == 12){ // 12C
    if(qq>4.01 ) OUT_OF_RANGE=true;
    R_max=8.;
    n = 16;
    for(G4int i=0;i<n;i++)
      a[i] = a12[i];
      //      cout << i << "\t" << a[i] << "\t" << a12[i] << endl;
  }
  else if(iA == 15){ // 15N7
    if(qq>3.17) OUT_OF_RANGE=true;
    R_max=7;
    n = 8;
    for(G4int i=0;i<n;i++)
      a[i] = a15[i];
  }
  else if(iA == 27){ // 27Al
    if(qq>2.70) OUT_OF_RANGE=true;
    //if(qq<0.47) OUT_OF_RANGE=true;
    R_max=7;
    n = 12;
    for(G4int i=0;i<n;i++)
      a[i] = a27[i];
  }
  else if(iA == 56){ // 56Fe26
    if(qq>2.22) OUT_OF_RANGE=true;
    //if(qq<0.51) OUT_OF_RANGE=true;
    R_max=9;
    n = 17;
    for(G4int i=0;i<n;i++)
      a[i] = a56[i];
  }
  else if(iA == 64){ // 64-Zn
    if(qq>2.22) OUT_OF_RANGE=true;
    //if(qq<0.51) OUT_OF_RANGE=true;
    R_max=9;
    n = 17;
    for(G4int i=0;i<n;i++)
      a[i] = a64[i];
  }
  else if(iA == 65){ // 65Cu29
    if(qq>2.22) OUT_OF_RANGE=true;
    //if(qq<0.51) OUT_OF_RANGE=true;
    R_max=9;
    n = 17;
    for(G4int i=0;i<n;i++)
      a[i] = a65[i];
  }
  else if(iA == 196){ // 196Pt78
    if(qq>2.28) OUT_OF_RANGE=true;
    if(qq<0.34) OUT_OF_RANGE=true;
    R_max=12;
    n = 15;
    for(G4int i=0;i<n;i++)
      a[i] = a196[i];
  }
  else if (iA == 52) {// 52-Cr
    if (qq>2.59) OUT_OF_RANGE=true;
    //if (qq<0.15) OUT_OF_RANGE=true;
    R_max=9.0;
    n=11;
    for(G4int i=0;i<n;i++)
      a[i] = a52[i];
  }
  else
    OUT_OF_RANGE=true;

  if(OUT_OF_RANGE || (R_max == 0.)){
    ff_bessel=0.;
    return 0;
  }

  G4double qmu = 3.14159265 / R_max;
  G4double ff=0.;
  G4double sinqR = sin(qq*R_max);
  G4double qmux,qm,qp;

  G4double PI4=12.56637062; //! 4*PI
  G4double PI2=6.28318531; //! 2*PI

  for(G4int j=0;j<n;j++){
    qmux = qmu * Float_t(j+1);
    qm =  qq - qmux;
    qp =  qq + qmux;
    if(fabs(qm)>1.E-6)
      ff = ff + a[j]*(pow((-1.),(j+1)))*sinqR/(qm*qp);
    else
      ff = ff + a[j]*pow(R_max,2)/(PI2*(j+1));
  }

  if((qq*R_max>1.E-20) && (ff<1.E20))
    ff_bessel = PI4/Float_t(iZ)/qq *ff;
  else
    ff_bessel = 0.;

  if (ff_bessel < 0) ff_bessel*=-1;

  return ff_bessel;
}

////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// ---------------------------------------------------------
//      Calculates the asymmetry weighting factor for elastic
//      scattering from the proton.  Asymmetry returned in ppm
// ---------------------------------------------------------

G4double QweakSimEPEvent::GetAsymmetry_EP(G4double theta, G4double energy)
{

    const G4double Mp=0.938;
    const G4double gf=0.0000116637;
    const G4double alpha=1./137.;
    //const G4double s2tw=0.231;
    const G4double s2tw_low=0.2387;
    const G4double qwp=0.0713;
    const G4double qwn=-0.988;
    //const G4double NT=14.;
    //const G4double ZT=13.;

//     Radiative correction factors [from Musolf's Phys. Rep. 1994]
    //const G4double rpv=-0.054;
    //const G4double rnv=-0.0143;
    //const G4double rt0a=0.0;
    const G4double rt1a=-0.23;
    //const G4double r0a=0.023;

//     Check for minimum theta
    const G4double theta_min = 1.745329E-4;
    if (theta<theta_min)
        theta = theta_min;

//     The energy is in MeV after the cross section subroutine -
//     change back to GeV
    energy=energy/1000.0;

//     Calculate Q2
    G4double Q2_ep=4*energy*energy*sin(theta/2.0)*sin(theta/2.0);
    Q2_ep=Q2_ep/(1.0+2.0*energy/Mp*sin(theta/2.0)*sin(theta/2.0));

//     Proton Asymmetry
//     Kinematic Factors
    G4double tau=Q2_ep/4.0/(Mp*Mp);
    G4double epsilon=1.0/(1.0+2.0*(1.0+tau)*tan(theta/2.0)*tan(theta/2.0));
    G4double epsilonp=sqrt(tau*(1.0+tau)*(1.0-epsilon*epsilon));

//     Form factor calculations
//     Form Factors: Electromagetic
    G4double gvd=1.0/( (1.0+Q2_ep/0.71)*(1.0+Q2_ep/0.71) );
    G4double gepg=gvd;
    G4double gmpg=2.793*gvd;
    G4double geng=1.91*tau*gvd/(1.+5.6*tau);
    G4double gmng=-1.91*gvd;

//    Form Factors: Neutral-weak, Axial
//     Assume: Gs_E,M=0, G8_A,Gs_A=0
    //G4double gad=1/((1.0+Q2_ep/1.001/1.001)*(1.0+Q2_ep/1.001/1.001));
    //G4double gsa=-0.12/((1.+Q2_ep/1.06/1.06)*(1.+Q2_ep/1.06/1.06));
    G4double gt1a=1.2695/((1+Q2_ep/1.001/1.001)*(1+Q2_ep/1.001/1.001));
    //G4double g8a=0.0;
    //gsa=0.0;

//      Use SM radiative correction factors
//      Since we use SM values for Qw(p) and Qw(n)
//      we no longer need the radiative corrections
//      on those quantities.
//       gepz=(1.-4.*s2tw)*(1.+rpv)*gepg-(1.+rnv)*geng
//       gmpz=(1.-4.*s2tw)*(1.+rpv)*gmpg-(1.+rnv)*gmng

    G4double gepz=qwp*gepg+qwn*geng;
    G4double gmpz=qwp*gmpg+qwn*gmng;
    G4double gapz=-(1.0+rt1a)*gt1a;

    G4double asym=-gf/(4.0*pi*alpha*sqrt(2.0))*Q2_ep*1e6;
    asym=asym/(epsilon*gepg*gepg+tau*gmpg*gmpg);
    asym=asym*(epsilon*gepg*gepz+tau*gmpg*gmpz-(1.0-4.0*s2tw_low)*epsilonp*gmpg*gapz);

    return asym;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//---------------------------------------------------------
//     Calculates the asymmetry weighting factor for elastic
//     e-Al scattering using a formula from Donnelly.  Returns
//     the asymmetry in units of ppm.
//
//    Qw(p) value from J. Erler, Phys. Rev. D72, 073003 (2005)
//    Qw(n) value from using C_1u and C_1d values from PDG2008
//
//---------------------------------------------------------

G4double QweakSimEPEvent::GetAsymmetry_AL (G4double theta, G4double energy)
{
//     Needed constants
    const G4double gf=0.0000116637;
    const G4double alpha=1./137.;
    const G4double qwp=0.0713;
    const G4double qwn=-0.988;
    const G4double NT=14.;
    const G4double ZT=13.;

//     The energy is in MeV after the cross section subroutine -
//     change back to GeV
    energy = energy/1000.0;

//     Claculate Q2
    G4double Q2=4*energy*energy*sin(theta/2.)*sin(theta/2.);

//     Correction for Coulomb distortion for Al
//    Q2=Q2*(1.+(3.*ZT*0.197/137./(2.*energy*2.98)))*(1.+(3.*ZT*0.197/137./(2.*energy*2.98)));

//     Aluminum Asymmetry
    G4double asym=-gf/(4.*pi*alpha*sqrt(2.))*1e6*Q2*(qwp+qwn*NT/ZT);

    return asym;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//---------------------------------------------------------
//     Calculates the asymmetry weighting factor for elastic
//     e-Be scattering using a formula from Donnelly.  Returns
//     the asymmetry in units of ppm.
//
//    Qw(p) value from J. Erler, Phys. Rev. D72, 073003 (2005)
//    Qw(n) value from using C_1u and C_1d values from PDG2008
//
//---------------------------------------------------------

G4double QweakSimEPEvent::GetAsymmetry_Be (G4double theta, G4double energy)
{
    const G4double Mp=0.938;
    const G4double gf=0.0000116637;
    const G4double alpha=1./137.;
    const G4double qwp=0.0713;
    const G4double qwn=-0.988;
    const G4double NT=5.;
    const G4double ZT=4.;

//     The energy is in MeV after the cross section subroutine -
//     change back to GeV
    energy = energy/1000.;

//     Claculate Q2
    G4double Q2=4*energy*energy*sin(theta/2.)*sin(theta/2.);
    Q2=Q2/(1.+2.*energy/(9.*Mp)*sin(theta/2.)*sin(theta/2.));

//     Correction for Coulomb distortion
    Q2=Q2*(1.+(3./2.*sqrt(3./5.)*ZT*0.197/137./(energy*1.77)))*(1.+(3./2.*sqrt(3./5.)*ZT*0.197/137./(energy*1.77)));

//     Beryllium Asymmetry
    G4double asym=-gf/(4.*pi*alpha*sqrt(2.))*1e6*Q2*(qwp+qwn*NT/ZT);

    return asym;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//    Calculates the asymmetry weighting factor for elastic
//    scattering from the neutron.

G4double QweakSimEPEvent::GetAsymmetry_EN(G4double theta, G4double energy)
{
  
    const G4double Mn= 0.939565; // Mp=0.938;
    const G4double gf=0.0000116637;
    const G4double alpha=1./137.;
    //const G4double s2tw=0.231;
    const G4double s2tw_low=0.2387;
    const G4double qwp=0.0713;
    const G4double qwn=-0.988;
    //const G4double NT=14.;
    //const G4double ZT=13.;

//     Radiative correction factors [from Musolf's Phys. Rep. 1994]
    //const G4double rpv=-0.054;
    //const G4double rnv=-0.0143;
    //const G4double rt0a=0.0;
    const G4double rt1a=-0.23;
    //const G4double r0a=0.023;

//     Check for minimum theta
    const G4double theta_min = 1.745329E-4;
    if (theta<theta_min)
        theta = theta_min;

//     The energy is in MeV after the cross section subroutine -
//     change back to GeV
    energy=energy/1000.0;

//     Calculate Q2
    G4double Q2_ep=4*energy*energy*sin(theta/2.0)*sin(theta/2.0);
    Q2_ep=Q2_ep/(1.0+2.0*energy/Mn*sin(theta/2.0)*sin(theta/2.0));

//     Proton Asymmetry
//     Kinematic Factors
    G4double tau=Q2_ep/4.0/(Mn*Mn);
    G4double epsilon=1.0/(1.0+2.0*(1.0+tau)*tan(theta/2.0)*tan(theta/2.0));
    G4double epsilonp=sqrt(tau*(1.0+tau)*(1.0-epsilon*epsilon));

//     Form factor calculations
//     Form Factors: Electromagetic
    G4double gvd=1.0/( (1.0+Q2_ep/0.71)*(1.0+Q2_ep/0.71) );
    G4double gepg=gvd;
    G4double gmpg=2.793*gvd;
    G4double geng=1.91*tau*gvd/(1.+5.6*tau);
    G4double gmng=-1.91*gvd;
    //G4double gesg= 0;
    //G4double gmsg= 0;

//    Form Factors: Neutral-weak, Axial
//     Assume: Gs_E,M=0, G8_A,Gs_A=0
    //G4double gad=1/((1.0+Q2_ep/1.001/1.001)*(1.0+Q2_ep/1.001/1.001));
    //G4double gsa=-0.12/((1.+Q2_ep/1.06/1.06)*(1.+Q2_ep/1.06/1.06));
    G4double gt1a=1.2695/((1+Q2_ep/1.001/1.001)*(1+Q2_ep/1.001/1.001));
    //G4double g8a=0.0;
    //gsa=0.0;

//      Use SM radiative correction factors
//      Since we use SM values for Qw(p) and Qw(n)
//      we no longer need the radiative corrections
//      on those quantities.
//       gepz=(1.-4.*s2tw)*(1.+rpv)*gepg-(1.+rnv)*geng
//       gmpz=(1.-4.*s2tw)*(1.+rpv)*gmpg-(1.+rnv)*gmng

    G4double gapz=-(1.0+rt1a)*gt1a;
    
//     G4double gepz=qwp*gepg+qwn*geng;
//     G4double gmpz=qwp*gmpg+qwn*gmng;   
//     G4double asym=-gf/(4.0*pi*alpha*sqrt(2.0))*Q2_ep*1e6;
//     asym=asym/(epsilon*gepg*gepg+tau*gmpg*gmpg);
//     asym=asym*(epsilon*gepg*gepz+tau*gmpg*gmpz-(1.0-4.0*s2tw_low)*epsilonp*gmpg*gapz);
//     //std::cout<<"asym_proton="<<asym<<std::endl;

    G4double genz=qwp*geng+qwn*gepg;
    G4double gmnz=qwp*gmng+qwn*gmpg;
    G4double asym_neutron = -gf/(4.0*pi*alpha*sqrt(2.0))*Q2_ep*1e6;
    asym_neutron =asym_neutron /(epsilon*geng*geng+tau*gmng*gmng);
    asym_neutron =asym_neutron *(epsilon*geng*genz+tau*gmng*gmnz-(1.0-4.0*s2tw_low)*epsilonp*gmng*gapz);
    //std::cout<<"asym_neutron="<<asym_neutron<<std::endl<<std::endl;

    return asym_neutron;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
//---------------------------------------------------------
//    Calculates the asymmetry weighting factor for inelastic
//    scattering from the proton.  The simple approximation
//    		A_LR = -100 (ppm/GeV^2) * Q^2
//    is used.  Returns asymmetry in units of ppm.
//    Reference:
//    H.-W. Hammer and D. Drechsel, Z. Phys. A353, 321-331 (1995)
//
//---------------------------------------------------------

G4double QweakSimEPEvent::GetAsymmetry_Pi(G4double Q2_pi)
{
//     Inelastic Asymmetry
    Q2_pi = Q2_pi/1e6;
    G4double asym=-100*Q2_pi;
    return asym;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//  Jim Dowd
// ---------------------------------------------------------
//      Setters and getters need to be defined here because
//      they call myUserInfo methods  
// ---------------------------------------------------------

void  QweakSimEPEvent::SetEPrime_Min(G4double energy)  {myUserInfo->SetEPrime_Min(energy); CheckLookupTableBounds();}
G4double  QweakSimEPEvent::GetEPrime_Min() {return myUserInfo->GetEPrime_Min();}

void  QweakSimEPEvent::SetEPrime_Max(G4double energy) {myUserInfo->SetEPrime_Max(energy); CheckLookupTableBounds();}
G4double  QweakSimEPEvent::GetEPrime_Max() {return myUserInfo->GetEPrime_Max();}

void  QweakSimEPEvent::SetThetaAngle_Min(G4double ang) {myUserInfo->SetThetaAngle_Min(ang); CheckLookupTableBounds();}
G4double  QweakSimEPEvent::GetThetaAngle_Min() {return myUserInfo->GetThetaAngle_Min();}

void  QweakSimEPEvent::SetThetaAngle_Max(G4double ang) {myUserInfo->SetThetaAngle_Max(ang); CheckLookupTableBounds();}
G4double  QweakSimEPEvent::GetThetaAngle_Max() {return myUserInfo->GetThetaAngle_Max();}

void  QweakSimEPEvent::SetPhiAngle_Min(G4double ang) {myUserInfo->SetPhiAngle_Min(ang);}
G4double  QweakSimEPEvent::GetPhiAngle_Min() {return myUserInfo->GetPhiAngle_Min();}

void  QweakSimEPEvent::SetPhiAngle_Max(G4double ang) {myUserInfo->SetPhiAngle_Max(ang);}
G4double  QweakSimEPEvent::GetPhiAngle_Max() {return myUserInfo->GetPhiAngle_Max();}

void  QweakSimEPEvent::SetLuminosity(G4double lum) {myUserInfo->SetLuminosity(lum);}
G4double  QweakSimEPEvent::GetLuminosity()  {return myUserInfo->GetLuminosity();}
  
void  QweakSimEPEvent::SetPhaseSpace(G4double ps) {myUserInfo->SetPhaseSpace(ps);}
G4double  QweakSimEPEvent::GetPhaseSpace()  {return myUserInfo->GetPhaseSpace();}

void QweakSimEPEvent::SetBeamEnergy(G4double energy) {
    if (energy>0) { 
      CheckLookupTableBounds();
      myUserInfo->SetBeamEnergy(energy); 
    }
    else {
      G4cout << G4endl << "##### Beam Energy must be greater than zero" << G4endl << G4endl;
    }
}
G4double  QweakSimEPEvent::GetBeamEnergy() {return myUserInfo->GetBeamEnergy();}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//jpan@nuclear.uwinnipeg.ca
//     To determine the energy of the electron incident on the scattering
//     vertex inside the target, the energy loss up to the scattering
//     event (inside the target material and walls) must be simulated.
//     The way this is done here is to first determine the scattering vertex
//     position, and find the path length of the electron, then calculate the
//     collision loss and radiation loss, which are added up to total energy
//     loss. 

/*
G4double QweakSimPrimaryGeneratorAction::PreTracking_Energy_Loss(G4double E_in, G4double Vertex_Z, G4double Target_A)
{
  //Incident energy E_in in units of MeV
  G4double E_Loss_Collision, E_Loss_Radiation, E_Loss;

  //part 1. energy loss by collision
  // Bethe-Bloch formula for electron collision energy loss, taken from Leo's eqn 2.66 and 2.26

  //define constant factor: Avagadro's Na=6.02e23; r=e*e/m/c/c is the classical electron radius;
  G4double 2_Pi_Na_re2_me_c2 = 0.1535; //units:[MeV cm^2/g]
 
  G4double m = 0.511; //electron mass in [MeV/c^2]
  G4double rho_H2 = 0.071; //density of H2, [g/cm^3]
  G4double rho_Al = 2.70; //density of Aluminum
  G4double I_H2 = 19.0; // mean excitation potential for H2, in units of [eV], 
                                   // I/Z = 12+7/Z [eV] if Z<13
  G4double I_Al = 166.0; // mean excitation potential for Aluminum, in units of [eV]
                                   // I/Z = 9.76+58.8*Z^(-1.19) [eV] if Z>=13

  // For relativistic electron: E = gamma*m*c^2
  // P = gamma*m*beta*c, E^2 = P^2*c^2 + m^2*c^4
  // => beta = sqrt(1-m^2/E^2)
  G4double beta = sqrt(1.0 - m*m/E_in/E_in) ;
  G4double gamma = E_in/m; 
  G4double eta = beta*gamma;

  G4double tau = E_in/m;   //kinetic energy of electron in units of [mc^2]

  //calculation for the density correction "delta", taken from Leo's 2.30
  // hnup = h*nu_p is the plasma frequency of the material
  G4double hnup_H2 = 28.816e-9 *sqrt(rho_H2*Z/A);
  G4double hnup_Al = 28.816e-9 *sqrt(rho_Al*Z/A);

  G4double C0_H2 = -(2.0*log(I_H2/(hnup_H2))+1.0);
  G4double delta_H2 = 4.6052*log10(eta)+C0_H2;

  G4double C0_Al = -(2.0*log(I_Al/(hnup_Al))+1.0);  //C0_Al = -4.24
  G4double delta_Al = 4.6052*log10(eta)+C0_Al;

  //calculation for the shell correction "C", taken from Leo's 2.33
  G4double C_H2 = (0.422377/eta/eta +0.0304043/eta/eta/eta/eta -0.00038106/eta/eta/eta/eta/eta/eta)*I_H2*I_H2*1.0e-6
                 + (3.850190/eta/eta -0.1667989/eta/eta/eta/eta +0.00157955/eta/eta/eta/eta/eta/eta)*I_H2*I_H2*1.0e-9;

  G4double C_Al = (0.422377/eta/eta +0.0304043/eta/eta/eta/eta -0.00038106/eta/eta/eta/eta/eta/eta)*I_Al*I_Al*1.0e-6
                 + (3.850190/eta/eta -0.1667989/eta/eta/eta/eta +0.00157955/eta/eta/eta/eta/eta/eta)*I_Al*I_Al*1.0e-9;

  G4double F_tau = 1-beta*beta+(tau*tau/8.0-(2*r+1)*log(2.0))/(tau+1.0)/(tau+1.0);
  G4double dE_dx_H2 = 2_Pi_Na_re2_me_c2*rho_H2*Z*A/beta/beta*(log(tau*tau*(tau+2.0)/2/(I_H2/m/c/c)/(I_H2/m/c/c))+F_tau-delta-2.0*C_H2/Z);
  G4double dE_dx_Al = 2_Pi_Na_re2_me_c2*rho_Al*Z*A/beta/beta*(log(tau*tau*(tau+2.0)/2/(I_Al/m/c/c)/(I_Al/m/c/c))+F_tau-delta-2.0*C_Al/Z);

  //Part 2. energy loss by radiation: Bremsstrahlung

  E_Loss = E_Loss_Collision + E_Loss_Radiation;
  return E_Loss;

}

*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
