
// QweakSimUserPMTOnly_MainEvent.hh
// Martin McHugh
// 2013-07-20

/////// --------------------------------------------------------------------

#ifndef QweakSimUserPMTOnly_MainEvent_h
#define QweakSimUserPMTOnly_MainEvent_h

/////// --------------------------------------------------------------------

//--- system include
#include <vector>

//--- root include
#include "TObject.h"

//-- user include
#include "QweakSimUserPMTOnly_DetectorEvent.hh"
#include "QweakSimUserPMTOnly_PMTEvent.hh"

/////// --------------------------------------------------------------------

class QweakSimUserPMTOnly_MainEvent : public TObject
{
	
public:
	
    QweakSimUserPMTOnly_MainEvent();
    virtual ~QweakSimUserPMTOnly_MainEvent();
	
    ClassDef(QweakSimUserPMTOnly_MainEvent,1);
	
public:
	
    QweakSimUserPMTOnly_DetectorEvent  Detector;
    QweakSimUserPMTOnly_PMTEvent       PMT;                      ///< PMT hit information
	
private:
	
};

/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
