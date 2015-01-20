//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTrackInformation.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:27:20 $
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
   \class QweakSimTrackInformation
    
   \brief Class with additional track information like Q2

   Placeholder for a long explaination
    
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimTrackInformation_h
#define QweakSimTrackInformation_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include <vector>

// geant4 includes
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4VUserTrackInformation.hh"

// geant4 classes
class G4Track;
class G4ParticleDefinition;

// user classes
class QweakSimTrackHistory;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimTrackInformation : public G4VUserTrackInformation 
{

public:

  QweakSimTrackInformation();
  QweakSimTrackInformation(const G4Track* aTrack);
  QweakSimTrackInformation(const QweakSimTrackInformation* aTrackInfo);
  virtual ~QweakSimTrackInformation();
  
  inline void *operator new(size_t);
  inline void  operator delete(void *aTrackInfo);
  inline int   operator ==(const QweakSimTrackInformation& right) const
  {return (this==&right);}
  
private:

  // TrackInfo which can derived from G4Track
  G4int                 primaryTrackID;
  G4ParticleDefinition* particleDefinition;
  G4ThreeVector         primaryPosition;
  G4ThreeVector         primaryMomentum;
  G4double              primaryEnergy;
  G4double              primaryKineticEnergy;
  G4double              primaryTime;

  std::vector <QweakSimTrackHistory*> theCerenkovTrackHistory;

  std::vector <G4ThreeVector> OriginVertex;
  std::vector <G4double> CerenkovHitEnergy;
  std::vector <G4ParticleDefinition*> ParticleHistory;
  std::vector <G4String> ParticleCreatorProcess;
  std::vector <G4double> ParentEnergy;   //Energy of parent at creation of
                                         //secondary.
                                         //For the primary particle this is
                                         //Set to the beam energy
  /*
  History    Parent Eenergy
  Vector     Vector

  e-         Beam Energy
  gamma      E_{e-}
  e+         E_{gamma}
  opt phot   E_{e+}
  */

  G4int                 trackingStatus;
  G4int                 trackIsPrimaryStatus;

  // trackingStatus = 1 : primary or secondary track which has not yet reached to calorimeter
  //                = 0 : track which or ancester of which has reached to calorimeter
  //                = 2 : track or its ancester had once reached to calorimeter and
  //                      then escaped from it
  // Information of the track which reached to the calorimeter boundary at the boundary surface
  // This information is valid only for trackingStatus = 0 or 2
  
  G4int                 sourceTrackID;
  G4ParticleDefinition* sourceDefinition;
  G4ThreeVector         sourcePosition;
  G4ThreeVector         sourceMomentum;
  G4double              sourceEnergy;
  G4double              sourceTime;
  G4ThreeVector         sourceOriginPosition;
  G4double              sourceOriginEnergy;

  G4int                 cerenkovImpactTrackID;
  G4ParticleDefinition* cerenkovImpactDefinition;
  G4ThreeVector         cerenkovImpactPosition;
  G4ThreeVector         cerenkovImpactMomentum;
  G4double              cerenkovImpactEnergy;
  G4double              cerenkovImpactTime;
  G4ThreeVector         cerenkovImpactOriginPosition;
  G4double              cerenkovImpactOriginEnergy;

public:

  void Initialize();
  void Print() const {;}
  void PrintPrimaryTrackInfo() const;
  void PrintSourceTrackInfo()  const;
  void PrintCerenkovImpactTrackInfo() const;
  
  //---------------------------------------------------------------------------
  
  void                StoreParticleDefinition(G4ParticleDefinition* pdef){ParticleHistory.push_back(pdef);};
  G4ParticleDefinition* GetParticleDefinitionAtIndex(G4int ind);
  G4int                 GetParticleHistoryLength() {return ParticleHistory.size();};
  
  void     StoreParentEnergy(G4double eng) {ParentEnergy.push_back(eng);};
  G4double   GetParentEnergyAtIndex(G4int ind);
  
  void   StoreCerenkovHitEnergy(G4int ind, G4double eng);
  G4double GetCerenkovHitEnergyAtIndex(G4int ind);
  
  void StoreCreatorProcess(G4String proc){ParticleCreatorProcess.push_back(proc);};
  G4String GetCreatorProcessAtIndex(G4int ind);
  
  void StoreOriginVertex(G4ThreeVector vert){OriginVertex.push_back(vert);};
  G4ThreeVector GetOriginVertex(G4int ind);

     //---------------------------------------------------------------------------

  void  StorePrimaryTrackID(G4int trackid) {primaryTrackID = trackid;}
  G4int   GetPrimaryTrackID() const {return primaryTrackID;}
  
  void                  StorePrimaryParticle(G4ParticleDefinition* pdef) {particleDefinition = pdef;}
  G4ParticleDefinition*   GetPrimaryParticle()              const {return particleDefinition;}
  
  void          StorePrimaryPosition(G4ThreeVector xyz) {primaryPosition = xyz;}
  G4ThreeVector   GetPrimaryPosition()     const {return primaryPosition;}
  
  void          StorePrimaryMomentum(G4ThreeVector pxyz) {primaryMomentum = pxyz;}
  G4ThreeVector   GetPrimaryMomentum()      const {return primaryMomentum;}
  
  void     StorePrimaryEnergy(G4double ekin) {primaryEnergy = ekin;}
  G4double   GetPrimaryEnergy() const {return primaryEnergy;}
  
  void     StorePrimaryKineticEnergy(G4double ekin) {primaryKineticEnergy = ekin;}
  G4double   GetPrimaryKineticEnergy() const {return primaryKineticEnergy;}
  
  void     StorePrimaryTime(G4double otime) {primaryTime = otime;}
  G4double   GetPrimaryTime()  const {return primaryTime;}
  
//   void     StorePrimaryQ2(G4double q2)   {primaryQ2 = q2;}
//   G4double   GetPrimaryQ2() const {return primaryQ2;}
//   
//   void     StoreCrossSection(G4double cs)   {crossSection = cs;}
//   G4double   GetCrossSection() const {return crossSection;}
// 
//   void     StoreCrossSectionWeight(G4double csw)   {crossSectionWeight = csw;}
//   G4double   GetCrossSectionWeight() const {return crossSectionWeight;}
//   
//   void     StorePrimaryEventNumber(G4int en)   {primaryEventNumber = en;}
//   G4int      GetPrimaryEventNumber() const {return primaryEventNumber;}
  
  //---------------------------------------------------------------------------
  
  inline void  SetTrackingStatus(G4int i)       {trackingStatus = i;}
  inline G4int GetTrackingStatus() const {return trackingStatus;}
  
  inline void  SetTrackIsPrimaryStatus(G4int i)       {trackIsPrimaryStatus = i;}
  inline G4int GetTrackIsPrimaryStatus() const {return trackIsPrimaryStatus;}
  
  //---------------------------------------------------------------------------
  void SetSourceTrackInformation(const G4Track* aTrack);
  
  inline G4int                 GetSourceTrackID()  const {return sourceTrackID;}
  inline G4ParticleDefinition* GetSourceParticle() const {return sourceDefinition;}
  inline G4ThreeVector         GetSourcePosition() const {return sourcePosition;}
  inline G4ThreeVector         GetSourceMomentum() const {return sourceMomentum;}
  inline G4double              GetSourceEnergy()   const {return sourceEnergy;}
  inline G4double              GetSourceTime()     const {return sourceTime;}
  inline G4ThreeVector         GetSourceOriginPosition() const {return sourceOriginPosition;}
  inline G4double              GetSourceOriginEnergy()   const {return sourceOriginEnergy;}
  //---------------------------------------------------------------------------
  
  void SetImpactTrackInformationForCerenkov(const G4Track* aTrack);
  
  inline G4int                 GetImpactTrackID()  const {return cerenkovImpactTrackID;}
  inline G4ParticleDefinition* GetImpactParticle() const {return cerenkovImpactDefinition;}
  inline G4ThreeVector         GetImpactPosition() const {return cerenkovImpactPosition;}
  inline G4ThreeVector         GetImpactMomentum() const {return cerenkovImpactMomentum;}
  inline G4double              GetImpactEnergy()   const {return cerenkovImpactEnergy;}
  inline G4double              GetImpactTime()     const {return cerenkovImpactTime;}
  inline G4ThreeVector         GetImpactOriginPosition() const {return cerenkovImpactOriginPosition;}
  inline G4double              GetImpactOriginEnergy()   const {return cerenkovImpactOriginEnergy;}
  //---------------------------------------------------------------------------
  
  void AddTrackInfoToCerenkovTrackHistory(const G4Track* aTrack);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

extern G4Allocator<QweakSimTrackInformation> aTrackInformationAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* QweakSimTrackInformation::operator new(size_t)
{ 
  void*  aTrackInfo;
         aTrackInfo = (void*) aTrackInformationAllocator.MallocSingle();
  return aTrackInfo;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void QweakSimTrackInformation::operator delete(void *aTrackInfo)
{ aTrackInformationAllocator.FreeSingle((QweakSimTrackInformation*)aTrackInfo);}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
