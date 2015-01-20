
// QweakSimUserLumi_MainEvent.hh

/////// --------------------------------------------------------------------

#ifndef QweakSimUserLumi_MainEvent_h
#define QweakSimUserLumi_MainEvent_h

/////// --------------------------------------------------------------------

//--- system include
#include <vector>

//--- root include
#include "TObject.h"

//-- user include
#include "QweakSimUserLumi_DetectorEvent.hh"
//#include "QweakSimUserLumi_PMTEvent.hh"

/////// --------------------------------------------------------------------

class QweakSimUserLumi_MainEvent : public TObject
{
	
public:
	
    QweakSimUserLumi_MainEvent();
    virtual ~QweakSimUserLumi_MainEvent();
	
    ClassDef(QweakSimUserLumi_MainEvent,1);
	
public:
	
    QweakSimUserLumi_DetectorEvent  Detector;
	
private:
	
};

/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
