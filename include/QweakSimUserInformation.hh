#ifndef QweakSimUserInformation_h
#define QweakSimUserInformation_h 

#include <vector>

//user includes
#include "QweakSimCerenkovDetector_PMTHit.hh"
#include "QweakSimUserPrimaryEvent.hh"

#include "G4PhysicsOrderedFreeVector.hh"

#include "QweakSimSystemOfUnits.hh"
#include "QweakSimPrimaryGeneratorAction.hh"

// forward declarations
class QweakSimEPEvent;

#define ELOSS_DEBUG 0

class QweakSimUserInformation 
{
public:
  
   QweakSimUserInformation();
  ~QweakSimUserInformation();
  
  G4double TargetCenterPositionZ;
  G4double TargetLength;
  G4double TargetEntranceWindowThickness;
  G4double TargetExitWindowThickness;
  G4double TargetExitWindowNippleThickness;
  G4double TargetUSDummyPositionOffsetZ;  // Offset from LH2 center
  G4double TargetDSDummyPositionOffsetZ;  // Offset from LH2 center
  // Dummy target Z positions are taken from the June 21, 2012 target survey

  G4double TargetThicknessUSALDummy1;
  G4double TargetThicknessUSALDummy2;
  G4double TargetThicknessUSALDummy4;
  G4double TargetThicknessDSALDummy2;
  G4double TargetThicknessDSALDummy4;
  G4double TargetThicknessDSALDummy8;
  G4double TargetThicknessUSCDummy;
  G4double TargetThicknessDSCDummy;

  G4double TargetLuminosityLH2;
  G4double TargetLuminosityUSALWindow;
  G4double TargetLuminosityDSALWindow;
  G4double TargetLuminosityUSALDummy1;
  G4double TargetLuminosityUSALDummy2;
  G4double TargetLuminosityUSALDummy4;
  G4double TargetLuminosityDSALDummy2;
  G4double TargetLuminosityDSALDummy4;
  G4double TargetLuminosityDSALDummy8;
  G4double TargetLuminosityUSCDummy;
  G4double TargetLuminosityDSCDummy;

  G4int    ReactionType;         // assign a number to which kind of reaction,e.g. 1 = elastic ep,
  G4int    ReactionRegion;
  G4int    EvtGenStatus;

  // clear the energy loss variables
  void ClearELoss(){
    dEIonIn= dEIonOut=0;
    dEBremIn= dEBremOut=0;
    dEMscIn= dEMscOut=0;
  }
  
  //setter functions
  void SetBeamPositionX(G4double x) { fPositionX.push_back(x); };
  void SetBeamPositionY(G4double y) { fPositionY.push_back(y); };
  void SetBeamPositionZ(G4double z) { fPositionZ.push_back(z); };
  void SetBeamDirectionX(G4double x) { fNormMomentumX.push_back(x); };
  void SetBeamDirectionY(G4double y) { fNormMomentumY.push_back(y); };
  
  //getter functions 
  void FixedPosCheckIndex(G4int i){
    if( G4int(fPositionX.size()) < i ){
      G4cerr<<" QweakSimUserInformation::FixedPosCheckIndex request for index "<<i<<
	"does is larger than size of the provided position data "<<fPositionX.size()<<G4endl;
      exit(-1);
    }	          
  }

  G4double    GetBeamPositionX(G4int i){FixedPosCheckIndex(i);return fPositionX[i];};  
  G4double    GetBeamPositionY(G4int i){FixedPosCheckIndex(i);return fPositionY[i];};
  G4double    GetBeamPositionZ(G4int i){FixedPosCheckIndex(i);return fPositionZ[i];};
  G4double    GetNormMomentumX(G4int i){FixedPosCheckIndex(i);return fNormMomentumX[i];};
  G4double    GetNormMomentumY(G4int i){FixedPosCheckIndex(i);return fNormMomentumY[i];};
  G4ThreeVector GetNormMomentum(G4int i){
    FixedPosCheckIndex(i);
    return G4ThreeVector(fNormMomentumX[i],
			 fNormMomentumY[i],
			 sqrt(1-fNormMomentumX[i]*fNormMomentumX[i]-fNormMomentumY[i]*fNormMomentumY[i]));
  }

  void SetNumberOfEventToBeProcessed(G4int n) {
    fNumberOfEventToBeProcessed = n;
  }
  G4int GetNumberOfEventToBeProcessed() const {
    return fNumberOfEventToBeProcessed;
  }

  void SetFixedPosMom(G4bool val){fFixedPosMom=val;}
  G4bool GetFixedPosMom() const {return fFixedPosMom;}
  void ReadFixedPosMom();

private:

  G4int fNumberOfEventToBeProcessed;

  G4bool   fFixedPosMom;
  std::vector<G4double> fPositionX;
  std::vector<G4double> fPositionY;
  std::vector<G4double> fPositionZ;
  std::vector<G4double> fNormMomentumX;
  std::vector<G4double> fNormMomentumY;

  G4int    PrimaryEventNumber;
  G4int    PDGcode;              // particle data code/number for the primary particle, e.g. 11=electron
  G4int    TrackID;
  G4double GlobalTime;
  G4double PrimaryQ2;
  G4double CrossSection;
  G4double CrossSectionWeight;
  G4double CrossSectionBornTotal;
  G4double CrossSectionBornInelastic;
  G4double CrossSectionBornQE;
  G4double CrossSectionRadTotal;
  G4double CrossSectionRadElastic;
  G4double CrossSectionRadQE;
  G4double CrossSectionRadDIS;
  G4double CrossSectionRadTotalIntOnly;
  G4double CrossSectionRadElasticIntOnly;
  G4double CrossSectionRadQEIntOnly;
  G4double CrossSectionRadDISIntOnly;
  G4double CrossSectionRadElasticPeak;
  G4double Asymmetry;
  G4double OriginVertexPositionX;
  G4double OriginVertexPositionY;
  G4double OriginVertexPositionZ;
  G4double OriginVertexThetaAngle;
  G4double OriginVertexPhiAngle;
  G4double OriginVertexMomentumDirectionX;
  G4double OriginVertexMomentumDirectionY;
  G4double OriginVertexMomentumDirectionZ;
  G4double PreScatteringKineticEnergy;
  G4double OriginVertexKineticEnergy;
  G4double OriginVertexTotalEnergy;
  G4double OriginVertexKinematicQ2;
  G4double OriginVertexKinematicNu;
  G4double OriginVertexKinematicX;
  G4double OriginVertexKinematicW;
  
  G4double fPhiAngle_Min;
  G4double fPhiAngle_Max;
  G4double fThetaAngle_Min;
  G4double fThetaAngle_Max;
  G4double fEPrime_Min;
  G4double fEPrime_Max;

  G4double fBeamEnergy;
  G4double fEPrime;
  G4double fLuminosity;
  G4double fPhaseSpace;
  
  G4double EffectiveKinematicQ2;
  G4double EffectiveKinematicNu;
  G4double EffectiveKinematicX;
  G4double EffectiveKinematicW;

  G4double CerEngDep;
  
  // various energy losses at the target
  G4double dEIonIn, dEIonOut;
  G4double dEBremIn, dEBremOut;
  G4double dEMscIn, dEMscOut;

  G4int    edgeEventDetected;
  G4int    leftPMTHitValid;
  G4int    rightPMTHitValid;

  G4int    cerenkovSecondaryParticleCount;
  G4int    cerenkovSecondaryElectronCount;
  G4int    cerenkovSecondaryPhotonCount;
  G4int    cerenkovSecondaryPositronCount;
  G4int    cerenkovOpticalPhotonCount;

  G4PhysicsOrderedFreeVector* PMTQE_XP4572;
  G4PhysicsOrderedFreeVector* PMTQED753WKBS20;

  G4String StepVolumeName;
  G4ThreeVector cerenkovEventExitPos;
  G4ThreeVector *cerenkovSecondaryPartOrig;
  G4ThreeVector *cerenkovSecondaryPartMom;
  G4double *cerenkovSecondaryPartEng;
  G4double *cerenkovSecondaryPartCharge;

  std::vector <G4double> CerenkovPhotonEnergy;

  QweakSimCerenkovDetector_PMTHit *PMTHit;

  G4int PMTSide;

 private:
  QweakSimEPEvent* EPEvent;
 public:
  void SetEPEvent(QweakSimEPEvent* EP) { EPEvent = EP; };
  QweakSimEPEvent* GetEPEvent() { return EPEvent; };

 public:

  void Print() const;
  void PrintELoss();
  void Initialize();

  void     StoreTrackID(G4int tid)    { TrackID = tid; }
  G4int    GetTrackID() const {return TrackID;}

  void     StoreGlobalTime(G4double gtime) { GlobalTime = gtime; }
  G4double    GetGlobalTime()  const {return GlobalTime;}

  //G4double CalculateLuminosity(G4double mass, G4double density, G4double length);

  //-----------------
  void     StoreOriginVertexPositionX(G4double vx)   { OriginVertexPositionX = vx; }
  G4double    GetOriginVertexPositionX() const {return OriginVertexPositionX;}

  void     StoreOriginVertexPositionY(G4double vy)   { OriginVertexPositionY = vy; }
  G4double    GetOriginVertexPositionY() const {return OriginVertexPositionY;}

  void     StoreOriginVertexPositionZ(G4double vz)   { OriginVertexPositionZ = vz; }
  G4double    GetOriginVertexPositionZ() const {return OriginVertexPositionZ;}
  //-----------------
  void     StoreOriginVertexMomentumDirectionX(G4double vx)   { OriginVertexMomentumDirectionX = vx; }
  G4double    GetOriginVertexMomentumDirectionX() const {return OriginVertexMomentumDirectionX;}

  void     StoreOriginVertexMomentumDirectionY(G4double vy)   { OriginVertexMomentumDirectionY = vy; }
  G4double    GetOriginVertexMomentumDirectionY() const {return OriginVertexMomentumDirectionY;}

  void     StoreOriginVertexMomentumDirectionZ(G4double vz)   { OriginVertexMomentumDirectionZ = vz; }
  G4double    GetOriginVertexMomentumDirectionZ() const {return OriginVertexMomentumDirectionZ;}
  //-----------------
  void     StoreOriginVertexThetaAngle(G4double theta) { OriginVertexThetaAngle = theta; }
  G4double    GetOriginVertexThetaAngle() const  {return OriginVertexThetaAngle;}

  void     StoreOriginVertexPhiAngle(G4double phi)  { OriginVertexPhiAngle = phi; }
  G4double    GetOriginVertexPhiAngle() const {return OriginVertexPhiAngle;}
  //-----------------
  
  void     StorePreScatteringKineticEnergy(G4double ekin) { PreScatteringKineticEnergy = ekin; }
  G4double    GetPreScatteringKineticEnergy() const {return PreScatteringKineticEnergy;}
  
  void     StoreOriginVertexKineticEnergy(G4double ekin) { OriginVertexKineticEnergy = ekin; }
  G4double    GetOriginVertexKineticEnergy() const {return OriginVertexKineticEnergy;}

  void     StoreOriginVertexTotalEnergy(G4double etot) { OriginVertexTotalEnergy = etot; }
  G4double    GetOriginVertexTotalEnergy() const {return OriginVertexTotalEnergy;}
  //-----------------

  void     StoreOriginVertexKinematicQ2(G4double Q2) { OriginVertexKinematicQ2 = Q2; }
  G4double    GetOriginVertexKinematicQ2() const {return OriginVertexKinematicQ2;}

  void     StoreOriginVertexKinematicNu(G4double Nu) { OriginVertexKinematicNu = Nu; }
  G4double    GetOriginVertexKinematicNu() const {return OriginVertexKinematicNu;}

  void     StoreOriginVertexKinematicX(G4double X) { OriginVertexKinematicX = X; }
  G4double    GetOriginVertexKinematicX() const {return OriginVertexKinematicX;}

  void     StoreOriginVertexKinematicW(G4double W) { OriginVertexKinematicW = W; }
  G4double    GetOriginVertexKinematicW() const {return OriginVertexKinematicW;}
  //-----------------

  void SetEPrime_Min(G4double energy) {fEPrime_Min = energy;}
  G4double GetEPrime_Min() {return fEPrime_Min;}

  void SetEPrime_Max(G4double energy) {fEPrime_Max = energy;}
  G4double GetEPrime_Max() {return fEPrime_Max;}

  void SetThetaAngle_Min(G4double ang) {fThetaAngle_Min = ang;}
  G4double GetThetaAngle_Min() {return fThetaAngle_Min;}

  void SetThetaAngle_Max(G4double ang) {fThetaAngle_Max = ang;}
  G4double GetThetaAngle_Max() {return fThetaAngle_Max;}

  void SetPhiAngle_Min(G4double ang) {fPhiAngle_Min = ang;}
  G4double GetPhiAngle_Min() {return fPhiAngle_Min;}

  void SetPhiAngle_Max(G4double ang) {fPhiAngle_Max = ang;}
  G4double GetPhiAngle_Max() {return fPhiAngle_Max;}

  //-----------------

  void     SetBeamEnergy(G4double energy) { fBeamEnergy = energy; }
  G4double    GetBeamEnergy() const {return fBeamEnergy;}

  void     SetEPrime(G4double energy) { fEPrime = energy; }
  G4double    GetEPrime() const {return fEPrime;}

  void     SetLuminosity(G4double lum) { fLuminosity = lum; }
  G4double    GetLuminosity() {return fLuminosity;}

  void     SetPhaseSpace(G4double ps) { fPhaseSpace = ps; }
  G4double    GetPhaseSpace() {return fPhaseSpace;}

  //-----------------

  void     StoreEffectiveKinematicQ2(G4double Q2) { EffectiveKinematicQ2 = Q2; }
  G4double    GetEffectiveKinematicQ2() const {return EffectiveKinematicQ2;}

  void     StoreEffectiveKinematicNu(G4double Nu) { EffectiveKinematicNu = Nu; }
  G4double    GetEffectiveKinematicNu() const {return EffectiveKinematicNu;}

  void     StoreEffectiveKinematicX(G4double X) { EffectiveKinematicX = X; }
  G4double    GetEffectiveKinematicX() const {return EffectiveKinematicX;}

  void     StoreEffectiveKinematicW(G4double W) { EffectiveKinematicW = W; }
  G4double    GetEffectiveKinematicW() const {return EffectiveKinematicW;}
  //-----------------

  void     StorePrimaryQ2(G4double pq2)  { PrimaryQ2 = pq2; }
  G4double    GetPrimaryQ2() const {return PrimaryQ2; }

  void     StoreCrossSection(G4double cs)  {CrossSection = cs;}
  G4double    GetCrossSection() const {return CrossSection; }

  void     StoreCrossSectionWeight(G4double csw)  {CrossSectionWeight = csw;}
  G4double    GetCrossSectionWeight() const {return CrossSectionWeight; }

  void     StoreAsymmetry(G4double asym)  {Asymmetry = asym;}
  G4double    GetAsymmetry() const {return Asymmetry; }

  void     StorePrimaryEventNumber(G4int pen)    { PrimaryEventNumber = pen; }
  G4int      GetPrimaryEventNumber() const {return PrimaryEventNumber; }
  //-----------------

  void     StoreCrossSectionBornTotal(G4double cs)  {CrossSectionBornTotal = cs;}
  G4double    GetCrossSectionBornTotal() const {return CrossSectionBornTotal; }

  void     StoreCrossSectionBornInelastic(G4double cs)  {CrossSectionBornInelastic = cs;}
  G4double    GetCrossSectionBornInelastic() const {return CrossSectionBornInelastic; }

  void     StoreCrossSectionBornQE(G4double cs)  {CrossSectionBornQE = cs;}
  G4double    GetCrossSectionBornQE() const {return CrossSectionBornQE; }

  void     StoreCrossSectionRadTotal(G4double cs)  {CrossSectionRadTotal = cs;}
  G4double    GetCrossSectionRadTotal() const {return CrossSectionRadTotal; }

  void     StoreCrossSectionRadElastic(G4double cs)  {CrossSectionRadElastic = cs;}
  G4double    GetCrossSectionRadElastic() const {return CrossSectionRadElastic; }

  void     StoreCrossSectionRadQE(G4double cs)  {CrossSectionRadQE = cs;}
  G4double    GetCrossSectionRadQE() const {return CrossSectionRadQE; }

  void     StoreCrossSectionRadDIS(G4double cs)  {CrossSectionRadDIS = cs;}
  G4double    GetCrossSectionRadDIS() const {return CrossSectionRadDIS; }
  //-----------------
  
  void     StoreCrossSectionRadTotalIntOnly(G4double cs)  {CrossSectionRadTotalIntOnly = cs;}
  G4double    GetCrossSectionRadTotalIntOnly() const {return CrossSectionRadTotalIntOnly; }

  void     StoreCrossSectionRadElasticIntOnly(G4double cs)  {CrossSectionRadElasticIntOnly = cs;}
  G4double    GetCrossSectionRadElasticIntOnly() const {return CrossSectionRadElasticIntOnly; }

  void     StoreCrossSectionRadQEIntOnly(G4double cs)  {CrossSectionRadQEIntOnly = cs;}
  G4double    GetCrossSectionRadQEIntOnly() const {return CrossSectionRadQEIntOnly; }

  void     StoreCrossSectionRadDISIntOnly(G4double cs)  {CrossSectionRadDISIntOnly = cs;}
  G4double    GetCrossSectionRadDISIntOnly() const {return CrossSectionRadDISIntOnly; }
  //-----------------

  void     StoreCrossSectionRadElasticPeak(G4double cs)  {CrossSectionRadElasticPeak = cs;}
  G4double    GetCrossSectionRadElasticPeak() const {return CrossSectionRadElasticPeak; }
  //-----------------

  void     StoreReactionRegion(G4int rt)  { ReactionRegion = rt; }
  G4int      GetReactionRegion() const {return ReactionRegion; }

  void     StoreReactionType(G4int rt)  { ReactionType = rt; }
  G4int      GetReactionType() const {return ReactionType; }

  void     StorePDGcode(G4int code)  { PDGcode = code; }
  G4int      GetPDGcode() const {return PDGcode; }



  void     IncrementCerenkovOpticalPhotonCount() {cerenkovOpticalPhotonCount++;}
  G4int    GetCerenkovOpticalPhotonCount() {return cerenkovOpticalPhotonCount;}

  G4double GetNumberOfPhotoelectrons(G4double eng);
  G4double GetNumberOfPhotoelectronsS20(G4double eng);

  void     SetLeftPMTHitValid(G4int state) {leftPMTHitValid = state;};
  G4int    GetLeftPMTHitValid() {return leftPMTHitValid; leftPMTHitValid = 0;};
  void     SetRightPMTHitValid(G4int state){rightPMTHitValid = state;};
  G4int    GetRightPMTHitValid() {return rightPMTHitValid; rightPMTHitValid = 0;};

  void     StoreStepVolumeName(G4String name) {StepVolumeName = name;};
  G4String GetStoredStepVolumeName() {return StepVolumeName;};

  void     SetEdgeEventDetected(G4int det){edgeEventDetected = det;};
  G4int    GetEdgeEventDetected(){return edgeEventDetected;};

  void     StoreLocalCerenkovExitPosition(G4ThreeVector ep) {cerenkovEventExitPos = ep;};
  G4ThreeVector GetLocalCerenkovExitPosition() {return cerenkovEventExitPos;};

  void     StoreCerenkovSecondaryParticleInfo(G4ThreeVector ep, G4ThreeVector ee, G4double eng, G4double charge);
  void     ResetCerenkovSecondaryParticleInfo();
  G4ThreeVector GetCerenkovSecondaryParticleOrigin(G4int indx);
  G4ThreeVector GetCerenkovSecondaryParticleMomentum(G4int indx);
  G4double GetCerenkovSecondaryParticleEnergy(G4int indx);
  G4double GetCerenkovSecondaryParticleCharge(G4int indx);
  G4int    GetCerenkovSecondaryParticleCount() {return  cerenkovSecondaryParticleCount;};
  G4int    GetCerenkovSecondaryElectronCount() {return  cerenkovSecondaryElectronCount;};
  G4int    GetCerenkovSecondaryPhotonCount() {return  cerenkovSecondaryPhotonCount;};
  G4int    GetCerenkovSecondaryPositronCount() {return  cerenkovSecondaryPositronCount;};
  
  void SetCurrentPMTHit(QweakSimCerenkovDetector_PMTHit* hit, G4int side){PMTHit = hit; PMTSide = side;};
  QweakSimCerenkovDetector_PMTHit *GetCurrentPMTHit(){return PMTHit;};
  G4int GetCurrentPMTSide() {return PMTSide;};

  void     AddCerenkovEnergyDeposit(G4double eng){CerEngDep += eng;};
  G4double GetCerenkovEnergyDeposit(G4bool zero = true){G4double tmp = CerEngDep; if(zero) CerEngDep = 0.0; return tmp;};

  void StoreCerenkovPhotonEnergy(G4double eng) {CerenkovPhotonEnergy.push_back(eng);};
  G4double GetCerenkovPhotonEnergyAtIndex(G4int ind) {return CerenkovPhotonEnergy[ind];};

  //   // store various Elosses at the target
  void StoredEIonIn(G4double dE){dEIonIn=dE;}
  void StoredEIonOut(G4double dE){dEIonOut=dE;}
  void StoredEBremIn(G4double dE){dEBremIn=dE;}
  void StoredEBremOut(G4double dE){dEBremOut=dE;}
  void StoredEMscIn(G4double dE){dEMscIn=dE;}
  void StoredEMscOut(G4double dE){dEMscOut=dE;}
  ///
  void AddTodEIonIn(G4double dE){dEIonIn+=dE;}
  void AddTodEIonOut(G4double dE){dEIonOut+=dE;}
  void AddTodEBremIn(G4double dE){dEBremIn+=dE;}
  void AddTodEBremOut(G4double dE){dEBremOut+=dE;}
  void AddTodEMscIn(G4double dE){dEMscIn+=dE;}
  void AddTodEMscOut(G4double dE){dEMscOut+=dE;}
  ////////
  G4double GetdEIonIn(){return dEIonIn;}
  G4double GetdEIonOut(){return dEIonOut;}
  G4double GetdEIonTot(){return dEIonIn + dEIonOut;}
  G4double GetdEBremIn(){return dEBremIn;}
  G4double GetdEBremOut(){return dEBremOut;}
  G4double GetdEBremTot(){return dEBremIn + dEBremOut;}
  G4double GetdEMscIn(){return dEMscIn;}
  G4double GetdEMscOut(){return dEMscOut;}
  G4double GetdEMscTot(){return dEMscIn + dEMscOut;}
  G4double GetdETotIn(){return dEIonIn + dEBremIn + dEMscIn;}
  G4double GetdETotOut(){return dEIonOut + dEBremOut + dEMscOut;}
  G4double GetdETot(){return dEIonIn + dEBremIn + dEMscIn + dEIonOut + dEBremOut + dEMscOut;}
  ///////

};

#endif
