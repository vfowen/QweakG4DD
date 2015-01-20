
// QweakSimUserPMTOnly_PMTEvent.hh
// Martin McHugh
// 2013-08-01

/////// --------------------------------------------------------------------

#ifndef QweakSimUserPMTOnly_PMTEvent_h
#define QweakSimUserPMTOnly_PMTEvent_h

/////// --------------------------------------------------------------------

//-- root includes
#include "TObject.h"

/////// --------------------------------------------------------------------

class QweakSimUserPMTOnly_PMTEvent : public TObject
{
	
  private:
	
    Float_t TrackID;
    
    Int_t NbOfHits;
	
    Int_t PMTHasBeenHit;
	
    Int_t PMTTotalNbOfHits;
	
    Float_t PMTTotalNbOfPEs;
	
  public:
	
    //--- Constructor
    QweakSimUserPMTOnly_PMTEvent();
	
    //--- Destructor 
    ~QweakSimUserPMTOnly_PMTEvent();
	
    void Initialize();
	
    //-----------------
	
    void     StoreTrackID(Float_t tid)    { TrackID = tid; }
    Float_t    GetTrackID() const {return TrackID;}

    //-----------------	
    
    void  StoreDetectorNbOfHits(Int_t nd)     { NbOfHits = nd; }
    Int_t   GetDetectorNbOfHits() const    {return  NbOfHits;}

    //-----------------
	
    void     StorePMTHasBeenHit(Int_t np)      { PMTHasBeenHit = np; }
    Int_t      GetPMTHasBeenHit() const {return  PMTHasBeenHit;}
	
    //-----------------
	
    void     StorePMTTotalNbOfHits(Int_t npt)      { PMTTotalNbOfHits = npt; }
    Int_t      GetPMTTotalNbOfHits() const {return   PMTTotalNbOfHits;}
	
    //-----------------
	
    void     StorePMTTotalNbOfPEs(Float_t npt)      { PMTTotalNbOfPEs = npt; }
    Float_t    GetPMTTotalNbOfPEs() const {return   PMTTotalNbOfPEs;}
	
    //--- define a new Class known to ROOT  
    ClassDef(QweakSimUserPMTOnly_PMTEvent,1)
	
};  //--- end class QweakSimUserPMTOnly_PMTEvent 

/////// --------------------------------------------------------------------

#endif 

/////// --------------------------------------------------------------------
