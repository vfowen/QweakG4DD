
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserTriggerScintillator_PMTEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:31:07 $
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
   \class QweakSimUserTriggerScintillator_PMTEvent
    
   \ingroup root

   \brief ROOT Subtree structure for Trigger Scintillator PMTEvent
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:31:07 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserTriggerScintillator_PMTEvent_h
#define QweakSimUserTriggerScintillator_PMTEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root includes
#include "TObject.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserTriggerScintillator_PMTEvent : public TObject
{

private:

  Int_t TrackID;                ///< ID of the track from which this hit was generated

  Int_t PMTHasBeenHit;          ///< Has this PMT been hit? 0 = no, 5 = yes

  Int_t PMTLeftNbOfHits;        ///< Number of hits in the left PMT
  Int_t PMTRightNbOfHits;       ///< Number of hits in the right PMT
  Int_t PMTTotalNbOfHits;       ///< Number of hits in both PMTs

  Float_t PMTLeftNbOfPEs;       ///< Number of photo-electrons in the left PMT
  Float_t PMTRightNbOfPEs;      ///< Number of photo-electrons in the right PMT
  Float_t PMTTotalNbOfPEs;      ///< Number of photo-electrons in both PMTs

public:
  
  // Constructor
  QweakSimUserTriggerScintillator_PMTEvent();
  // Destructor 
  virtual ~QweakSimUserTriggerScintillator_PMTEvent();

  void Initialize();

  //-----------------
  void     StoreTrackID(Int_t tid)    { TrackID = tid; }
  Int_t      GetTrackID() const {return TrackID;}
   //-----------------
  void     StorePMTHasBeenHit(Int_t np)      { PMTHasBeenHit = np; }
  Int_t      GetPMTHasBeenHit() const {return  PMTHasBeenHit;}
  //-----------------
  void     StorePMTLeftNbOfHits(Int_t npl)      { PMTLeftNbOfHits = npl; }
  Int_t      GetPMTLeftNbOfHits() const {return   PMTLeftNbOfHits;}

  void     StorePMTRightNbOfHits(Int_t npr)      { PMTRightNbOfHits = npr; }
  Int_t      GetPMTRightNbOfHits() const {return   PMTRightNbOfHits;}

  void     StorePMTTotalNbOfHits(Int_t npt)      { PMTTotalNbOfHits = npt; }
  Int_t      GetPMTTotalNbOfHits() const {return   PMTTotalNbOfHits;}
  //-----------------
  void     StorePMTLeftNbOfPEs(Float_t npl)      { PMTLeftNbOfPEs = npl; }
  Float_t      GetPMTLeftNbOfPEs() const {return   PMTLeftNbOfPEs;}

  void     StorePMTRightNbOfPEs(Float_t npr)      { PMTRightNbOfPEs = npr; }
  Float_t    GetPMTRightNbOfPEs() const {return   PMTRightNbOfPEs;}

  void     StorePMTTotalNbOfPEs(Float_t npt)      { PMTTotalNbOfPEs = npt; }
  Float_t    GetPMTTotalNbOfPEs() const {return   PMTTotalNbOfPEs;}
 
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserTriggerScintillator_PMTEvent,1)

};  // end class QweakSimUserTriggerScintillator_PMTEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserTriggerScintillator_PMTEvent.hh,v $
//      Revision 1.2  2005/12/27 19:31:07  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

