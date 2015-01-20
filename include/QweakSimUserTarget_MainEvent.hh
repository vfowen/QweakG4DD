
// QweakSimUserTarget_MainEvent.hh
// Wouter Deconinck
// 2014-10-07

/////// --------------------------------------------------------------------

#ifndef QweakSimUserTarget_MainEvent_h
#define QweakSimUserTarget_MainEvent_h

/////// --------------------------------------------------------------------

//--- root include
#include "TObject.h"

//-- user include
#include "QweakSimUserTarget_DetectorEvent.hh"

/////// --------------------------------------------------------------------

class QweakSimUserTarget_MainEvent : public TObject
{
	
public:
	
    QweakSimUserTarget_MainEvent() { };
    virtual ~QweakSimUserTarget_MainEvent() { };
	
    ClassDef(QweakSimUserTarget_MainEvent,1);
	
public:
	
    QweakSimUserTarget_DetectorEvent  Detector;
	
private:
	
};

/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------
