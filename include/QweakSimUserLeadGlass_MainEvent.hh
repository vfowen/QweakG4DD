
// QweakSimUserLeadGlass_MainEvent.hh
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#ifndef QweakSimUserLeadGlass_MainEvent_h
#define QweakSimUserLeadGlass_MainEvent_h

/////// --------------------------------------------------------------------

//--- system include
#include <vector>

//--- root include
#include "TObject.h"

//-- user include
#include "QweakSimUserLeadGlass_DetectorEvent.hh"
#include "QweakSimUserLeadGlass_PMTEvent.hh"

/////// --------------------------------------------------------------------

class QweakSimUserLeadGlass_MainEvent : public TObject
{
	
public:
	
    QweakSimUserLeadGlass_MainEvent();
    virtual ~QweakSimUserLeadGlass_MainEvent();
	
    ClassDef(QweakSimUserLeadGlass_MainEvent,1);
	
public:
	
    QweakSimUserLeadGlass_DetectorEvent  Detector;
	
private:
	
};

/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
