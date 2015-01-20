
// QweakSimUserLeadGlass_PMTEvent.cc
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#include "QweakSimUserLeadGlass_PMTEvent.hh"



/////// --------------------------------------------------------------------

ClassImp(QweakSimUserLeadGlass_PMTEvent)



/////// --------------------------------------------------------------------

QweakSimUserLeadGlass_PMTEvent::QweakSimUserLeadGlass_PMTEvent()
{
    Initialize();
}



/////// --------------------------------------------------------------------

QweakSimUserLeadGlass_PMTEvent::~QweakSimUserLeadGlass_PMTEvent()
{;}



/////// --------------------------------------------------------------------

void QweakSimUserLeadGlass_PMTEvent::Initialize()
{
    TrackID                        = 0;
	
    PMTHasBeenHit                  = 0;
    PMTLeftNbOfHits                = 0;
    PMTRightNbOfHits               = 0;
    PMTTotalNbOfHits               = 0;
    PMTLeftNbOfPEs                 = 0;
    PMTRightNbOfPEs                = 0;
    PMTTotalNbOfPEs                = 0;
	
}



/////// --------------------------------------------------------------------

