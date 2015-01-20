
// QweakSimUserLeadGlass_PMTEvent.hh
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#ifndef QweakSimUserLeadGlass_PMTEvent_h
#define QweakSimUserLeadGlass_PMTEvent_h



/////// --------------------------------------------------------------------

//-- root includes
#include "TObject.h"



/////// --------------------------------------------------------------------

class QweakSimUserLeadGlass_PMTEvent : public TObject
{
	
private:
	
    Float_t TrackID;
	
    Int_t PMTHasBeenHit;
	
    Int_t PMTLeftNbOfHits;
    Int_t PMTRightNbOfHits;
    Int_t PMTTotalNbOfHits;
	
    Float_t PMTLeftNbOfPEs;
    Float_t PMTRightNbOfPEs;
    Float_t PMTTotalNbOfPEs;
	
public:
	
    //--- Constructor
    QweakSimUserLeadGlass_PMTEvent();
	
    //--- Destructor 
    virtual ~QweakSimUserLeadGlass_PMTEvent();
	
    void Initialize();
	
    //-----------------
	
    void     StoreTrackID(Float_t tid)    { TrackID = tid; }
    Float_t    GetTrackID() const {return TrackID;}
	
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
	
    //--- define a new Class known to ROOT  
    ClassDef(QweakSimUserLeadGlass_PMTEvent,1)
	
};  //--- end class QweakSimUserLeadGlass_PMTEvent 


/////// --------------------------------------------------------------------

#endif 

/////// --------------------------------------------------------------------


