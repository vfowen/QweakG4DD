
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserCerenkov_PMTEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:29:20 $
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
   \class QweakSimUserCerenkov_PMTEvent
    
   \ingroup root

   \brief ROOT Subtree structure for Cerenkov PMTEvent
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserCerenkov_PMTEvent_h
#define QweakSimUserCerenkov_PMTEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root includes
#include "TObject.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserCerenkov_PMTEvent : public TObject
{

  private:

    Int_t NbOfHits;               ///< Number of hits in this detector

    std::vector<Int_t> PMTHasBeenHit;          ///< Has this PMT been hit? 0 = no, 5 = yes

    std::vector<Float_t> PMTTimeOfHits;
    std::vector<Float_t> PMTEnergyOfHits;
    std::vector<Int_t> PMTOctantOfHits;

    std::vector<Int_t> PMTLeftNbOfHits;        ///< Number of hits in left PMTs
    std::vector<Int_t> PMTRightNbOfHits;       ///< Number of hits in right PMTs
    std::vector<Int_t> PMTTotalNbOfHits;       ///< Number of hits in both PMTs

    std::vector<Float_t> PMTLeftNbOfPEs;       ///< Number of photo-electrons in left PMTs
    std::vector<Float_t> PMTRightNbOfPEs;      ///< Number of photo-electrons in right PMTs
    std::vector<Float_t> PMTTotalNbOfPEs;      ///< Number of photo-electrons in both PMTs

    std::vector<Float_t> PMTLeftRate;      ///< Total event rate in left PMTs
    std::vector<Float_t> PMTRightRate;     ///< Total event rate in right PMTs
    std::vector<Float_t> PMTTotalRate;     ///< Total event rate in both PMTs
    std::vector<Float_t> PMTLeftRateEL;    ///< Elastic event rate in left PMTs
    std::vector<Float_t> PMTRightRateEL;   ///< Elastic event rate in right PMTs
    std::vector<Float_t> PMTTotalRateEL;   ///< Elastic event rate in both PMTs
    std::vector<Float_t> PMTLeftRateDIS;   ///< DIS event rate in left PMTs
    std::vector<Float_t> PMTRightRateDIS;  ///< DIS event rate in right PMTs
    std::vector<Float_t> PMTTotalRateDIS;  ///< DIS event rate in both PMTs
    std::vector<Float_t> PMTLeftRateQE;    ///< Quasi-elastic event rate in left PMTs
    std::vector<Float_t> PMTRightRateQE;   ///< Quasi-elastic event rate in right PMTs
    std::vector<Float_t> PMTTotalRateQE;   ///< Quasi-elastic event rate in both PMTs
    std::vector<Float_t> PMTLeftRateELPeak;    ///< Elastic Peak event rate in left PMTs
    std::vector<Float_t> PMTRightRateELPeak;   ///< Elastic Peak event rate in right PMTs
    std::vector<Float_t> PMTTotalRateELPeak;   ///< Elastic Peak event rate in both PMTs

    std::vector<Float_t> PMTLeftYield;     ///< Total PE yield in left PMTs
    std::vector<Float_t> PMTRightYield;    ///< Total PE yield in right PMTs
    std::vector<Float_t> PMTTotalYield;    ///< Total PE yield in both PMTs
    std::vector<Float_t> PMTLeftYieldEL;   ///< Elastic PE yield in left PMTs
    std::vector<Float_t> PMTRightYieldEL;  ///< Elastic PE yield in right PMTs
    std::vector<Float_t> PMTTotalYieldEL;  ///< Elastic PE yield in both PMTs
    std::vector<Float_t> PMTLeftYieldDIS;  ///< Inelastic PE yield in left PMTs
    std::vector<Float_t> PMTRightYieldDIS; ///< Inelastic PE yield in right PMTs
    std::vector<Float_t> PMTTotalYieldDIS; ///< Inelastic PE yield in both PMTs
    std::vector<Float_t> PMTLeftYieldQE;   ///< Quasi-elastic PE yield in left PMTs
    std::vector<Float_t> PMTRightYieldQE;  ///< Quasi-elastic PE yield in right PMTs
    std::vector<Float_t> PMTTotalYieldQE;  ///< Quasi-elastic PE yield in both PMTs
    std::vector<Float_t> PMTLeftYieldELPeak;   ///< Elastic Peak PE yield in left PMTs
    std::vector<Float_t> PMTRightYieldELPeak;  ///< Elastic Peak PE yield in right PMTs
    std::vector<Float_t> PMTTotalYieldELPeak;  ///< Elastic Peak PE yield in both PMTs

  public:

    // Constructor
    QweakSimUserCerenkov_PMTEvent() { Initialize(); };
    // Destructor
    virtual ~QweakSimUserCerenkov_PMTEvent() { };

    // Initialization
    void Initialize();

  public:

    //-----------------
    void     StoreDetectorNbOfHits(Int_t nd)      { NbOfHits = nd; }
    Int_t      GetDetectorNbOfHits() const { return NbOfHits;}

    //-----------------
    void StorePMTHasBeenHit(std::vector<Int_t> np)      { PMTHasBeenHit = np; }
    std::vector<Int_t> GetPMTHasBeenHit() const  { return PMTHasBeenHit;}

    //-----------------
    void StorePMTTimeOfHits(std::vector<Float_t> time)   { PMTTimeOfHits = time; }
    std::vector<Float_t> GetPMTTimeOfHits() const  {return PMTTimeOfHits;}
    //-----------------
    void StorePMTEnergyOfHits(std::vector<Float_t> time)   { PMTEnergyOfHits = time; }
    std::vector<Float_t> GetPMTEnergyOfHits() const  {return PMTEnergyOfHits;}
    //-----------------
    void StorePMTOctantOfHits(std::vector<Int_t> octant) { PMTOctantOfHits = octant; }
    std::vector<Int_t> GetPMTOctantOfHits() const  {return PMTOctantOfHits;}

    //-----------------
    void StorePMTLeftNbOfHits(std::vector<Int_t> npl)    { PMTLeftNbOfHits = npl; }
    std::vector<Int_t> GetPMTLeftNbOfHits() const  {return PMTLeftNbOfHits;}

    void StorePMTRightNbOfHits(std::vector<Int_t> npr)   { PMTRightNbOfHits = npr; }
    std::vector<Int_t> GetPMTRightNbOfHits() const {return PMTRightNbOfHits;}

    void StorePMTTotalNbOfHits(std::vector<Int_t> npt)   { PMTTotalNbOfHits = npt; }
    std::vector<Int_t> GetPMTTotalNbOfHits() const {return PMTTotalNbOfHits;}
    //-----------------
    void StorePMTLeftNbOfPEs(std::vector<Float_t> npl)    { PMTLeftNbOfPEs = npl; }
    std::vector<Float_t> GetPMTLeftNbOfPEs() const  {return PMTLeftNbOfPEs;}

    void StorePMTRightNbOfPEs(std::vector<Float_t> npr)   { PMTRightNbOfPEs = npr; }
    std::vector<Float_t> GetPMTRightNbOfPEs() const {return PMTRightNbOfPEs;}

    void StorePMTTotalNbOfPEs(std::vector<Float_t> npt)   { PMTTotalNbOfPEs = npt; }
    std::vector<Float_t> GetPMTTotalNbOfPEs() const {return PMTTotalNbOfPEs;}

    //-----------------
    void StorePMTLeftRate(std::vector<Float_t> rl)    { PMTLeftRate = rl; }
    std::vector<Float_t> GetPMTLeftRate() const  {return PMTLeftRate;}

    void StorePMTRightRate(std::vector<Float_t> rr)   { PMTRightRate = rr; }
    std::vector<Float_t> GetPMTRightRate() const {return PMTRightRate;}

    void StorePMTTotalRate(std::vector<Float_t> rt)   { PMTTotalRate = rt; }
    std::vector<Float_t> GetPMTTotalRate() const {return PMTTotalRate;}


    void StorePMTLeftRateEL(std::vector<Float_t> rl)    { PMTLeftRateEL = rl; }
    std::vector<Float_t> GetPMTLeftRateEL() const  {return PMTLeftRateEL;}

    void StorePMTRightRateEL(std::vector<Float_t> rr)   { PMTRightRateEL = rr; }
    std::vector<Float_t> GetPMTRightRateEL() const {return PMTRightRateEL;}

    void StorePMTTotalRateEL(std::vector<Float_t> rt)   { PMTTotalRateEL = rt; }
    std::vector<Float_t> GetPMTTotalRateEL() const {return PMTTotalRateEL;}


    void StorePMTLeftRateDIS(std::vector<Float_t> rl)    { PMTLeftRateDIS = rl; }
    std::vector<Float_t> GetPMTLeftRateDIS() const  {return PMTLeftRateDIS;}

    void StorePMTRightRateDIS(std::vector<Float_t> rr)   { PMTRightRateDIS = rr; }
    std::vector<Float_t> GetPMTRightRateDIS() const {return PMTRightRateDIS;}

    void StorePMTTotalRateDIS(std::vector<Float_t> rt)   { PMTTotalRateDIS = rt; }
    std::vector<Float_t> GetPMTTotalRateDIS() const {return PMTTotalRateDIS;}


    void StorePMTLeftRateQE(std::vector<Float_t> rl)    { PMTLeftRateQE = rl; }
    std::vector<Float_t> GetPMTLeftRateQE() const  {return PMTLeftRateQE;}

    void StorePMTRightRateQE(std::vector<Float_t> rr)   { PMTRightRateQE = rr; }
    std::vector<Float_t> GetPMTRightRateQE() const {return PMTRightRateQE;}

    void StorePMTTotalRateQE(std::vector<Float_t> rt)   { PMTTotalRateQE = rt; }
    std::vector<Float_t> GetPMTTotalRateQE() const {return PMTTotalRateQE;}


    void StorePMTLeftRateELPeak(std::vector<Float_t> rl)    { PMTLeftRateELPeak = rl; }
    std::vector<Float_t> GetPMTLeftRateELPeak() const  {return PMTLeftRateELPeak;}

    void StorePMTRightRateELPeak(std::vector<Float_t> rr)   { PMTRightRateELPeak = rr; }
    std::vector<Float_t> GetPMTRightRateELPeak() const {return PMTRightRateELPeak;}

    void StorePMTTotalRateELPeak(std::vector<Float_t> rt)   { PMTTotalRateELPeak = rt; }
    std::vector<Float_t> GetPMTTotalRateELPeak() const {return PMTTotalRateELPeak;}


    //-----------------
    void StorePMTLeftYield(std::vector<Float_t> yl)    { PMTLeftYield = yl; }
    std::vector<Float_t> GetPMTLeftYield() const  {return PMTLeftYield;}

    void StorePMTRightYield(std::vector<Float_t> yr)   { PMTRightYield = yr; }
    std::vector<Float_t> GetPMTRightYield() const {return PMTRightYield;}

    void StorePMTTotalYield(std::vector<Float_t> yt)   { PMTTotalYield = yt; }
    std::vector<Float_t> GetPMTTotalYield() const {return PMTTotalYield;}


    void StorePMTLeftYieldEL(std::vector<Float_t> yl)    { PMTLeftYieldEL = yl; }
    std::vector<Float_t> GetPMTLeftYieldEL() const  {return PMTLeftYieldEL;}

    void StorePMTRightYieldEL(std::vector<Float_t> yr)   { PMTRightYieldEL = yr; }
    std::vector<Float_t> GetPMTRightYieldEL() const {return PMTRightYieldEL;}

    void StorePMTTotalYieldEL(std::vector<Float_t> yt)   { PMTTotalYieldEL = yt; }
    std::vector<Float_t> GetPMTTotalYieldEL() const {return PMTTotalYieldEL;}


    void StorePMTLeftYieldDIS(std::vector<Float_t> yl)    { PMTLeftYieldDIS = yl; }
    std::vector<Float_t> GetPMTLeftYieldDIS() const  {return PMTLeftYieldDIS;}

    void StorePMTRightYieldDIS(std::vector<Float_t> yr)   { PMTRightYieldDIS = yr; }
    std::vector<Float_t> GetPMTRightYieldDIS() const {return PMTRightYieldDIS;}

    void StorePMTTotalYieldDIS(std::vector<Float_t> yt)   { PMTTotalYieldDIS = yt; }
    std::vector<Float_t> GetPMTTotalYieldDIS() const {return PMTTotalYieldDIS;}


    void StorePMTLeftYieldQE(std::vector<Float_t> yl)    { PMTLeftYieldQE = yl; }
    std::vector<Float_t> GetPMTLeftYieldQE() const  {return PMTLeftYieldQE;}

    void StorePMTRightYieldQE(std::vector<Float_t> yr)   { PMTRightYieldQE = yr; }
    std::vector<Float_t> GetPMTRightYieldQE() const {return PMTRightYieldQE;}

    void StorePMTTotalYieldQE(std::vector<Float_t> yt)   { PMTTotalYieldQE = yt; }
    std::vector<Float_t> GetPMTTotalYieldQE() const {return PMTTotalYieldQE;}


    void StorePMTLeftYieldELPeak(std::vector<Float_t> yl)    { PMTLeftYieldELPeak = yl; }
    std::vector<Float_t> GetPMTLeftYieldELPeak() const  {return PMTLeftYieldELPeak;}

    void StorePMTRightYieldELPeak(std::vector<Float_t> yr)   { PMTRightYieldELPeak = yr; }
    std::vector<Float_t> GetPMTRightYieldELPeak() const {return PMTRightYieldELPeak;}

    void StorePMTTotalYieldELPeak(std::vector<Float_t> yt)   { PMTTotalYieldELPeak = yt; }
    std::vector<Float_t> GetPMTTotalYieldELPeak() const {return PMTTotalYieldELPeak;}


    // define a new Class known to ROOT
    ClassDef(QweakSimUserCerenkov_PMTEvent,2);

};  // end class QweakSimUserCerenkov_DetectorEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 
