//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimEPEvent.hh

   \author Jie Pan

*/
//=============================================================================

#ifndef QWEAKSIMEPEVENT_H
#define QWEAKSIMEPEVENT_H

// geant4 includes
#include "G4Types.hh"
#include "G4ThreeVector.hh"

//  user includes
#include "QweakSimFieldMap.hh"
#include "QweakSimSystemOfUnits.hh"
#include "Randomize.hh"

// user classes
class QweakSimEPEventMessenger;
class QweakSimUserInformation;

//template <class value_t, unsigned int value_n>
//class QweakSimFieldMap<value_t,value_n>;

class QweakSimEPEvent {

 private:
   //define target geometry parameter, 
   //TODO: these parameters will be acquired from QweakSimTarget

   static const G4double TargetLength;

   // definition of a mil = inch/1000
   static const G4double mil;
   static const G4double TargetWindowThickness;

   static const G4double M_n; //neutron mass in MeV/c^2
   static const G4double M_p;  // proton mass in MeV/c^2

   static const G4double Theta_Min;

   G4double A;  // mass number A, Al_A = 27.0
   G4double Z;  // charge number Z, Al_Z = 13.0

   G4double Mass;

   G4int TypeSetting;
   G4int ReactionType;          ///< \ref reaction_type used for event generation
   G4int ReactionRegion;        ///< \ref reaction_region used for event generation
   G4int kActiveOctantNumber;   ///< Active octant number in the simulation, 0 will enable all octants

   G4int Isotropy;              ///< \ref isotropy used for event generation
  //G4double PhiAngle_Min;
  //G4double PhiAngle_Max;
  //G4double ThetaAngle_Min;
  //G4double ThetaAngle_Max;
  //G4double EPrime_Min;
  //G4double EPrime_Max;
   G4double ElasticPeakDeltaE;
   G4double BeamEnergy;

   G4double myPositionZ;

  //  Lookup Table storage type
   typedef float value_t;      // type of all values stored  in the field

  //  Lookup Table field values
   static const G4int value_n = 15; // number of values at each point in the field
   static const G4int value_d = 4;  // number of dimensions of the coordinates
  //std::vector< G4double > fMin;
  //std::vector< G4double > fMax;
  //std::vector< G4double > fStep;

   QweakSimFieldMap<value_t,value_n> *fLookupTable;

   G4ThreeVector GetMomentumDirection();
  G4int    SuperElasticCheck(G4double E_in, G4double E_out, G4double theta, G4double &xsec);
   G4double ResMod507(G4int sf,G4double w2,G4double q2,G4double *xval);
   G4double Sigma_EEPrime(G4double eni,G4double eprime,G4double theta, G4double &q2);

   QweakSimEPEventMessenger *EventGen_Messenger;
   QweakSimUserInformation *myUserInfo;

 public:

  QweakSimEPEvent(QweakSimUserInformation* myUI);
  //QweakSimEPEvent();
  virtual ~QweakSimEPEvent();

  void SetActiveOctantNumber(G4int kaot) { kActiveOctantNumber = kaot; };
  G4int GetActiveOctantNumber( ) {return kActiveOctantNumber;};

  void SetIsotropy(G4int isot) { Isotropy = isot; };
  G4int GetIsotropy( ) {return Isotropy;};
  //------------------------------------------------------------------------  
  /*
  void SetEPrime_Min(G4double energy)  {myUserInfo->SetEPrime_Min(energy); CheckLookupTableBounds();};
  G4double GetEPrime_Min() {return myUserInfo->GetEPrime_Min();};

  void SetEPrime_Max(G4double energy) {myUserInfo->SetEPrime_Max(energy); CheckLookupTableBounds();};
  G4double GetEPrime_Max() {return myUserInfo->GetEPrime_Max();};

  void SetThetaAngle_Min(G4double ang) {myUserInfo->SetThetaAngle_Min(ang); CheckLookupTableBounds();};
  G4double GetThetaAngle_Min() {return myUserInfo->GetThetaAngle_Min();};

  void SetThetaAngle_Max(G4double ang) {myUserInfo->SetThetaAngle_Max(ang); CheckLookupTableBounds();};
  G4double GetThetaAngle_Max() {return myUserInfo->GetThetaAngle_Max();};

  void SetPhiAngle_Min(G4double ang) {myUserInfo->SetPhiAngle_Min(ang);};
  G4double GetPhiAngle_Min() {return myUserInfo->GetPhiAngle_Min();};

  void SetPhiAngle_Max(G4double ang) {myUserInfo->SetPhiAngle_Max(ang);};
  G4double GetPhiAngle_Max() {return myUserInfo->GetPhiAngle_Max();};

  void SetLuminosity(G4double lum) {myUserInfo->SetLuminosity(lum);};
  G4double GetLuminosity()  {return myUserInfo->GetLuminosity();};
  
  void SetPhaseSpace(G4double ps) {myUserInfo->SetPhaseSpace(ps);}
  G4double GetPhaseSpace()  {return myUserInfo->GetPhaseSpace();};

  void SetBeamEnergy(G4double energy = 1.160*GeV); 
  G4double GetBeamEnergy() {return myUserInfo->GetBeamEnergy();}
  */
  //----------------------------------------------------------------------
  void SetEPrime_Min(G4double energy);
  G4double GetEPrime_Min();

  void SetEPrime_Max(G4double energy);
  G4double GetEPrime_Max();

  void SetThetaAngle_Min(G4double ang);
  G4double GetThetaAngle_Min();

  void SetThetaAngle_Max(G4double ang);
  G4double GetThetaAngle_Max();

  void SetPhiAngle_Min(G4double ang);
  G4double GetPhiAngle_Min();

  void SetPhiAngle_Max(G4double ang);
  G4double GetPhiAngle_Max();

  void SetLuminosity(G4double lum);
  G4double GetLuminosity();
  
  void SetPhaseSpace(G4double ps);
  G4double GetPhaseSpace();

  void SetBeamEnergy(G4double energy = 1.160*GeV); 
  G4double GetBeamEnergy();
  //-----------------------------------------------------------------

  void SetElasticPeakDeltaE(G4double energy = 15*MeV) { if (energy < 15*MeV) { energy = 15*MeV; G4cout << "***** Value Out of Range: ElasticPeakDeltaE set to : 15 MeV *****" << G4endl; } ElasticPeakDeltaE = energy; } ; 
  G4double GetElasticPeakDeltaE() { return ElasticPeakDeltaE; } ;

  //-----------------------------------------------------------------
  void  SetReactionType(G4int rt) { ReactionType = rt; TypeSetting = rt;};
  G4int GetReactionType() {return ReactionType; };

  void  SetReactionRegion(G4int rr) { ReactionRegion = rr; if(ReactionType==7) CreateLookupTable();};
  G4int GetReactionRegion() {return ReactionRegion; };

  G4double GetVertexZ();
  void GetanEvent(G4double E_in, 
                  std::vector< G4double > &CrossSection, 
                  G4double &weight_n,
                  G4double &Q2,
                  G4double &E_out,
                  G4ThreeVector &MomentumDirection,
                  G4double &theta,
                  G4double &phi,
		  G4double &Asymmetry);

  G4double Elastic_Cross_Section_Proton( G4double E_in,
                                         G4double Theta,
                                         G4double &fWeightN,
                                         G4double &Q2,
                                         G4double &E_out);

  G4double Elastic_Cross_Section_Aluminum( G4double E_in,
                                           G4double Theta,
                                           G4double &fWeightN,
                                           G4double &Q2,
                                           G4double &E_out);

  G4double Quasi_Elastic_Neutron( G4double E_in,
                                  G4double Theta,
                                  G4double &fWeightN,
                                  G4double &Q2,
                                  G4double &E_out);
  
  G4double Delta_Resonance(G4double E_in,
                           G4double Theta,
                           G4double &fWeightN,
                           G4double &Q2,
                           G4double &E_out);
  
  G4double Moller_Scattering(G4double E_in, G4double theta1, 
                             G4double &E_out1, G4double &E_out2, G4double &theta2, 
                             G4double &q2, G4double &fWeightN, G4double &asymmetry);
  
  const std::vector< G4double > Radiative_Cross_Section_Lookup( G4double E_in,
                                           G4double Theta,
                                           G4double &fWeightN,
                                           G4double &Q2,
                                           G4double &E_out);

  void CreateLookupTable();

  void CheckLookupTableBounds();
  
  G4double AlNuclInel(G4double E_in,
		      G4double Theta,
		      G4double &fWeightN,
		      G4double &Q2,
		      G4double &E_out);

  G4double AlGDR(G4double E_in,
		      G4double Theta,
		      G4double &fWeightN,
		      G4double &Q2,
		      G4double &E_out);
  
  G4double Pion_PhotoProduction(G4double E_in,
                                G4double Theta,
                                G4double &fWeightN,
                                G4double &Q2,
                                G4double &E_out);
	
  G4double Quasi_Elastic_Bosted(G4double E_in, G4double Theta, G4int Zin, 
                                G4int Ain, G4double &fWeightN, G4double &Q2, G4double &E_out);
  G4double NuclearInelastic_Bosted(G4double E_in, G4double Theta, 
                                   G4int Zin, G4int Ain, 
                                   G4double &fWeightN, G4double &Q2,
                                   G4double &E_out);
  void F1F2QE09(G4int Z, G4int A, G4double QSQ,
                G4double wsq, G4double &F1, G4double &F2);
  void F1F2IN09(G4int Z, G4int A, G4double QSQ,
                G4double wsq, G4double &F1, G4double &F2);
  
  void christy507(G4double wsq, G4double Q2, G4double &F1,
                  G4double &R, G4double &sigt, G4double &sigl);
  void resmodd(G4double w2, G4double q2, G4double xval[50], G4double &sig);
  G4double resmod507_v2(G4double sf,G4double w2, G4double q2,
                        G4double xval[50]);
  G4double MEC2009(G4int a, G4double q2,G4double w2);
  G4double fitemc(G4double X, G4int A);

  G4double AlloyScattering(G4double E_in, G4double Theta, G4int Zin, 
                           G4int Ain, G4double &fWeightN, G4double &Q2,
                           G4double &E_out);
  G4double Fshell(G4int Z, G4int A, G4double q2);
  G4double Fgauss(G4int Z, G4int A, G4double q2);
  G4double FF_BESSEL(G4int Z, G4int A, G4double q2, G4bool &ofr);
  
  G4double GetAsymmetry_EP(G4double theta, G4double energy);
  G4double GetAsymmetry_EN(G4double theta, G4double energy);
  G4double GetAsymmetry_AL(G4double theta, G4double energy);
  G4double GetAsymmetry_Be(G4double theta, G4double energy);
  G4double GetAsymmetry_Pi(G4double Q2_pi);

};

#endif
